// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                           avtVerdictExpression.C                          //
// ************************************************************************* //

#include <avtVerdictExpression.h>

#include <verdict.h>

#include <vtkCell.h>
#include <vtkDataSet.h>
#include <vtkPoints.h>

#include <avtCallback.h>
#include <avtDataTree.h>
#include <avtDataRepresentation.h>

#include <ExpressionException.h>
#include <ImproperUseException.h>
#include <DebugStream.h>

struct SizeData
{
    double hexSize;
    double tetSize;
    double triSize;
    double quadSize;

    int hexCount;
    int tetCount;
    int triCount;
    int quadCount;

    void Clear()
    {
        hexSize = tetSize = triSize = quadSize = 0;
        hexCount = tetCount = triCount = quadCount = 0;
    }
};

SizeData VerdictSizeData;

void SumSize(avtDataRepresentation &, void *, bool &);

inline void
Swap1(double &a, double &b)
{
    double tmp = a;
    a = b;
    b = tmp;
}

inline void
Swap3(double c[][3], int a, int b)
{
    Swap1(c[a][0], c[b][0]);
    Swap1(c[a][1], c[b][1]);
    Swap1(c[a][2], c[b][2]);
}

// ****************************************************************************
//  Method: avtVerdictExpression::avtVerdictExpression
//
//  Purpose:
//      Constructor. Only purpose is to throw an exception if verdict is not
//      installed.
//
//  Programmer:   Akira Haddox
//  Creation:     June 11, 2002
//
//  Modifications:
//
//  Alister Maguire, Thu Jun 18 10:02:58 PDT 2020
//  Set canApplyToDirectDatabaseQOT to false.
//
// ****************************************************************************

avtVerdictExpression::avtVerdictExpression()
{
    #ifndef HAVE_VERDICT
    EXCEPTION1(ExpressionException, "Verdict was not distributed with this "
                                    "release of VisIt.");
    #endif

    canApplyToDirectDatabaseQOT = false;
}


// ****************************************************************************
//  Method: avtVerdictExpression destructor
//
//  Purpose:
//      Defines the destructor.  Note: this should not be inlined in the header
//      because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   February 5, 2004
//
// ****************************************************************************

avtVerdictExpression::~avtVerdictExpression()
{
    ;
}


// ****************************************************************************
//  Method: avtVerdictExpression::DeriveVariable
//
//  Purpose:
//      Derives a variable based on the input dataset, using a metric call.
//
//  Arguments:
//      in_ds     The input dataset.
//
//  Returns:      The derived variable.  The calling class must free this
//                memory.
//
//  Programmer:   Akira Haddox
//  Creation:     June 11, 2002
//
//
//  Modifications:
//
//    Akira Haddox, Wed Jul  2 08:26:30 PDT 2003
//    Added conversion from pixel cell type.
//
//    Hank Childs, Thu May 19 10:47:08 PDT 2005
//    Allow for sub-types to speed up execution by operating directly on the
//    mesh.
//
//    Hank Childs, Sat Oct  6 15:10:10 PDT 2007
//    Turn hex-20s into hex-8s.
//
//    Hank Childs, Thu Jul 24 12:38:34 PDT 2008
//    Add support for polygons and polyhedrons.
//
//    Jeremy Meredith, Thu Aug  7 14:30:46 EDT 2008
//    Made string literal const char*, not char*.
//
//   Dave Pugmire, Fri Jul 22 07:21:02 EDT 2011
//   vtkIdType != int.
//
// ****************************************************************************

vtkDataArray *
avtVerdictExpression::DeriveVariable(vtkDataSet *in_ds, int currentDomainsIndex)
{
    vtkIdType nCells = in_ds->GetNumberOfCells();

    //
    // Set up a VTK variable reflecting the results we have calculated.
    //
    vtkDataArray *dv = CreateArrayFromMesh(in_ds);
    dv->SetNumberOfTuples(nCells);

    //
    // Iterate over each cell in the mesh and if it matches a
    // testData prerequisites, run the corresponding metric
    //
    if (OperateDirectlyOnMesh(in_ds))
    {
        MetricForWholeMesh(in_ds, dv);
    }
    else
    {
        const int MAXPOINTS = 100;
        double coordinates[MAXPOINTS][3];
        for (vtkIdType i = 0; i < nCells; i++)    
        {
            vtkCell *cell = in_ds->GetCell(i);
            
            vtkIdType numPointsForThisCell = cell->GetNumberOfPoints();
            // Grab a pointer to the cell's points' underlying data array
            vtkDataArray *pointData = cell->GetPoints()->GetData();
    
            int cellType = cell->GetCellType();
            if (cellType == VTK_POLYGON)
            {
                double total = 0.;
                if (SummationValidForOddShapes())
                {
                    int numTris = numPointsForThisCell-2;
                    pointData->GetTuple(0,coordinates[0]);
                    for (int j = 0 ; j < numTris ; j++)
                    {
                        pointData->GetTuple(j+1,coordinates[1]);
                        pointData->GetTuple(j+2,coordinates[2]);
                        total += Metric(coordinates, VTK_TRIANGLE);
                    }
                }
                else
                {
                    static bool issuedWarning = false;
                    if (!issuedWarning)
                    {
                        const char *warning = "The mesh quality expression you"
                            " asked for cannot be applied to polygons.  VisIt"
                            " will assign to zero to all polygons for this "
                            "metric.  This warning will not be issued again "
                            "during this session, but keep in mind that "
                            "zeros will be placed silently from here on out.";
                        avtCallback::IssueWarning(warning);
                        issuedWarning = true;
                    }
                }
                dv->SetTuple1(i, total);
                continue;
            }
            
            //
            // Since the Verdict functions make their own copy of the data
            // anyway it would be nice to get the coordinate data without
            // copying (to cut down on unneeded copying). However, this might 
            // be infeasible since Verdict expects doubles, and vtk 
            // (potentially) uses floats.
            //
            
            if (pointData->GetNumberOfComponents() != 3)
            {
                EXCEPTION0(ImproperUseException);
            }
    
            // Fortunately, Verdict will convert to a double[3] for us
            for (int j = 0; j < numPointsForThisCell; j++)
            {
                coordinates[j][2] = 0; // In case of 2d coordinates
                pointData->GetTuple(j,coordinates[j]);
            }
    
            // Convert Voxel format into hexahedron format.
            if (cellType == VTK_VOXEL)
            {
                Swap3(coordinates, 2,3);
                Swap3(coordinates, 6,7);
            }
    
            // Convert Pixel format into quad format.
            if (cellType == VTK_PIXEL)
            {
                Swap3(coordinates, 2, 3);
                cellType = VTK_QUAD;
            }
    
            // Convert Pixel format into quad format.
            if (cellType == VTK_QUADRATIC_HEXAHEDRON)
            {
                cellType = VTK_HEXAHEDRON;
                // Leave points 9-20 in place; they are ignored.
            }
    
            double result = Metric(coordinates, cellType);
            dv->SetTuple1(i, result);
        }
    }
    
    return dv;
}

// ****************************************************************************
//  Method: avtVerdictExpression::PreExecute
//
//  Purpose:
//      If this metric requires size calculation, then before the tree is
//      executed, this function will calculate and set the verdict size
//      variables.
//
//  Arguments:
//      in_ds     The input dataset.
//
//  Returns:      The derived variable.  The calling class must free this
//                memory.
//
//  Programmer:   Akira Haddox
//  Creation:     June 11, 2002
//
//  Modifications:
//
//    Hank Childs, Thu Oct 17 08:07:53 PDT 2002
//    Update for new verdict interface.
//
//    Jeremy Meredith, Thu Feb 15 11:54:16 EST 2007
//    Execute inherited PreExecute unconditionally before everything else.
//
//    Hank Childs, Sun Jan 13 13:39:05 PST 2008
//    Call PreExecute of immediate base class.
//
// ****************************************************************************

void
avtVerdictExpression::PreExecute()
{
    avtSingleInputExpressionFilter::PreExecute();

#ifdef HAVE_VERDICT
    if (!RequiresSizeCalculation())
        return;

    VerdictSizeData.Clear();

    avtDataTree_p tree = GetInputDataTree();
    bool suc;
    tree->Traverse(SumSize,NULL,suc);

    if (VerdictSizeData.hexCount)
        v_set_hex_size(VerdictSizeData.hexSize/
                     (double)(VerdictSizeData.hexCount));
    if (VerdictSizeData.tetCount)
        v_set_tet_size(VerdictSizeData.tetSize/
                     (double)(VerdictSizeData.tetCount));
    if (VerdictSizeData.triCount)
        v_set_tri_size(VerdictSizeData.triSize/
                     (double)(VerdictSizeData.triCount));
    if (VerdictSizeData.quadCount)
        v_set_quad_size(VerdictSizeData.quadSize/
                      (double)(VerdictSizeData.quadCount));
#endif
}


// ****************************************************************************
//  Method: avtVerdictExpression::MetricForWholeMesh
//
//  Purpose:
//      Calculates a metric for the whole mesh.  This should be re-defined
//      by derived types that re-define OperateDirectlyOnMesh to return true.
//
//  Programmer: Hank Childs
//  Creation:   May 19, 2005
//
// ****************************************************************************

void
avtVerdictExpression::MetricForWholeMesh(vtkDataSet *ds, vtkDataArray *rv)
{
    EXCEPTION0(ImproperUseException);
}


// ****************************************************************************
//  Function: SumSize
//
//  Purpose:
//      Used for data tree traversal to collect sums of area/volume && quantity
//      of different cell types. Stores information in VerdictSizeData.
//
//  Arguments:
//      adr       The data.
//      <not used>
//      <not used>
//
//  Returns:      The derived variable.  The calling class must free this
//                memory.
//
//  Programmer:   Akira Haddox
//  Creation:     June 11, 2002
//
//  Modifications:
//
//    Hank Childs, Thu Oct 17 08:07:53 PDT 2002
//    Update for new verdict interface.
//
//    Akira Haddox, Wed Jul  2 08:26:30 PDT 2003
//    Added conversion from pixel cell type.
//
//    Hank Childs, Sat Oct  6 15:20:25 PDT 2007
//    Add support for hex-20s.
//
// ****************************************************************************

void SumSize(avtDataRepresentation &adr, void *, bool &)
{
#ifdef HAVE_VERDICT
    vtkDataSet *in_ds = adr.GetDataVTK();

    vtkIdType nCells = in_ds->GetNumberOfCells();

    double *results = new double[nCells];

    const int MAXPOINTS = 100;
    double coordinates[MAXPOINTS][3];
    for (vtkIdType i = 0; i < nCells; i++)    
    {
        vtkCell *cell = in_ds->GetCell(i);
        
        vtkIdType numPointsForThisCell = cell->GetNumberOfPoints();
        // Grab a pointer to the cell's points' underlying data array
        vtkDataArray *pointData = cell->GetPoints()->GetData();

        if (pointData->GetNumberOfComponents() != 3)
        {
            EXCEPTION0(ImproperUseException);
        }

        // Fortunately, Verdict will convert to a double[3] for us
        for (vtkIdType j = 0; j < numPointsForThisCell; j++)
        {
            coordinates[j][2] = 0; // In case of 2d coordinates
            pointData->GetTuple(j,coordinates[j]);
        }

        // Convert Voxel format into hexahedron format.
        if (cell->GetCellType() == VTK_VOXEL)
        {
                Swap3(coordinates, 2,3);
                Swap3(coordinates, 6,7);
        }

        // Convert Pixel format into quad format.
        if (cell->GetCellType() == VTK_PIXEL)
        {
            Swap3(coordinates, 2, 3);
        }

        switch (cell->GetCellType())
        {
            case VTK_VOXEL:
            case VTK_HEXAHEDRON:
            case VTK_QUADRATIC_HEXAHEDRON:
                ++VerdictSizeData.hexCount;
                VerdictSizeData.hexSize+=v_hex_volume(8, coordinates);
                break;
            case VTK_TETRA:
                ++VerdictSizeData.tetCount;
                VerdictSizeData.tetSize+=v_tet_volume(4, coordinates);
                break;
            case VTK_TRIANGLE:
                ++VerdictSizeData.triCount;
                VerdictSizeData.triSize+=v_tri_area(3, coordinates);
                break;
            case VTK_PIXEL:
            case VTK_QUAD:
                ++VerdictSizeData.quadCount;
                VerdictSizeData.quadSize+=v_quad_area(3, coordinates);
            default:
                break;
        }
    }
    delete []results;
#endif
}
