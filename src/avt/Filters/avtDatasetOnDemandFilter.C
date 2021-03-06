// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                         avtDatasetOnDemandFilter.C                        //
// ************************************************************************* //

#include <avtDatasetOnDemandFilter.h>

#include <vtkDataSet.h>

#include <avtCallback.h>
#include <avtCommonDataFunctions.h>
#include <avtDatabase.h>
#include <avtDataTree.h>
#include <avtExtents.h>
#include <avtOriginatingSource.h>
#include <avtPointSelection.h>
#include <vtkVisItCellLocator.h>

#include <ImproperUseException.h>
#include <IncompatibleDomainListsException.h>
#include <InvalidFilesException.h>
#include <DebugStream.h>

#include <vector>


// ****************************************************************************
//  Method: avtDatasetOnDemandFilter constructor
//
//  Programmer: Hank Childs
//  Creation:   March 1, 2008
//
// Modifications:
//   Dave Pugmire, Thu Mar 13 08:44:18 EDT 2008
//   Set default for maxQueueLength.
//
//   Hank Childs, Thu Jun 12 16:08:41 PDT 2008
//   Initialize operatingOnDemand.
//   
//    Dave Pugmire, Mon Jan 26 13:04:56 EST 2009
//    Initialize purgeDSCount.
//
//    Dave Pugmire, Tue Feb  3 11:05:24 EST 2009
//    Initialize loadDSCount.
//
// ****************************************************************************

avtDatasetOnDemandFilter::avtDatasetOnDemandFilter()
{
    maxQueueLength = 2;
    operatingOnDemand = false;
    purgeDSCount = 0;
    loadDSCount = 0;
}


// ****************************************************************************
//  Method: avtDatasetOnDemandFilter destructor
//
//  Programmer: Hank Childs
//  Creation:   March 1, 2008
//
// Modifications:
//   Dave Pugmire, Thu Mar 13 08:44:18 EDT 2008
//   Change domain cache from map to list.
//
//    Dave Pugmire, Wed Mar 25 09:15:23 EDT 2009
//    Add domain caching for point decomposed domains.
//
//    Gunther H. Weber, Fri Apr  3 17:37:18 PDT 2009
//    Moved vtkCellLocator from map to DomainCacheEntry data structure.
//
//    Hank Childs, Sat Apr 11 23:27:56 CDT 2009
//    Remove some Delete calls, as they are now handled by the 
//    DomainCacheEntry struct directly.
//
// ****************************************************************************

avtDatasetOnDemandFilter::~avtDatasetOnDemandFilter()
{
   EmptyQueue();
}

// ****************************************************************************
//  Method: EmptyQueue
//
//  Purpose:
//      Empty the vtk data cache.
//
//  Programmer: David Camp
//  Creation:   Mon Mar  5 14:04:42 PST 2012
//
// Modifications:
//
// ****************************************************************************

void
avtDatasetOnDemandFilter::EmptyQueue()
{
    while ( ! domainQueue.empty() )
    {
        domainQueue.pop_front();
    }
}

// ****************************************************************************
//  Method: avtDatasetOnDemandFilter::GetDomain
//
//  Purpose:
//      Forces a pipeline update to fetch a single domain.
//
//  Programmer: Hank Childs
//  Creation:   March 1, 2008
//
// Modifications:
//
//   Dave Pugmire, Thu Mar 13 08:44:18 EDT 2008
//   Change domain cache from map to list. Purge queue if it grows beyond max len.
//
//   Hank Childs, Thu Jun 12 11:08:55 PDT 2008
//   Tell the contract we are streaming.
//
//    Dave Pugmire, Mon Jan 26 13:04:56 EST 2009
//    Increment purgeDSCount when a DS is purged.
//
//    Dave Pugmire, Tue Feb  3 11:05:24 EST 2009
//    Increment loadDSCount when a DS is loaded.
//
//    Dave Pugmire, Tue Mar 10 12:41:11 EDT 2009
//    Added support for time/domain.
//
//    Dave Pugmire, Sat Mar 28 09:42:15 EDT 2009
//    Counter to keep track of how many times a domain is loaded.
//
//    Hank Childs, Sat Apr 11 23:27:56 CDT 2009
//    Remove some Delete calls, as they are now handled by the 
//    DomainCacheEntry struct directly.
//
//    Hank Childs, Mon Feb  1 14:23:46 PST 2010
//    Fix encoding of two 32 bit ints into one 64 bit int.
//
//    David Camp, Mon Aug 15 09:36:04 PDT 2011
//    Need to remove the domain reference from the PIC locator cache.
//
//    Hank Childs/David Camp, Tue Mar 13 12:43:15 PDT 2012
//    Make sure we are dealing with the right SIL restriction.
//
// ****************************************************************************

vtkDataSet *
avtDatasetOnDemandFilter::GetDomain(int domainId,
                                    int timeStep)
{
    if (DebugStream::Level5())
    {
        debug5<<"avtDatasetOnDemandFilter::GetDomain("<<domainId<<", "<<timeStep<<");"<<endl;
    }
    if ( ! OperatingOnDemand() )
        EXCEPTION0(ImproperUseException);

    if ( domainId < 0 )
        return NULL;

    // See if it is already in the cache.  If so, just return it.
    std::list<DomainCacheEntry>::iterator it;
    for ( it = domainQueue.begin(); it != domainQueue.end(); it++ )
    {
        // Found it. Move it to the front of the list.
        if (it->domainID == domainId &&
            it->timeStep == timeStep)
        {
            DomainCacheEntry entry;
            entry = *it;
            //Remove, then move to front.
            domainQueue.erase( it );
            domainQueue.push_front( entry );
            return entry.ds;
        }
    }

    avtSILRestriction_p silr;
    if (timeStep == firstContract->GetDataRequest()->GetTimestep())
    {
        silr = firstContract->GetDataRequest()->GetRestriction();
    }
    else if ((*lastUsedContract != NULL) && 
             (timeStep == lastUsedContract->GetDataRequest()->GetTimestep()))
    {
        silr = lastUsedContract->GetDataRequest()->GetRestriction();
    }
    else
    {
        // The SIL restriction associated with the contract may be for the wrong
        // time step.  Go get the correct one.
        std::string db = GetInput()->GetInfo().GetAttributes().GetFullDBName();
        ref_ptr<avtDatabase> dbp = avtCallback::GetDatabase(db, 0, NULL);
        if (*dbp == NULL)
            EXCEPTION1(InvalidFilesException, db.c_str());

        std::string mesh = GetInput()->GetInfo().GetAttributes().GetMeshname();
        avtDataObject_p dob = dbp->GetOutput(mesh.c_str(), timeStep);
        lastUsedContract = dob->GetOriginatingSource()->GetGeneralContract();
        silr = lastUsedContract->GetDataRequest()->GetRestriction();
   }

    avtDataRequest_p new_dr = new avtDataRequest(firstContract->GetDataRequest(), silr);
    avtContract_p new_contract = new avtContract(firstContract, new_dr);

    if (DebugStream::Level5())
    {
        debug5<<"     Update->GetDomain "<<domainId<<" time= "<<timeStep<<endl;
    }
    std::vector<int> domains;
    domains.push_back(domainId);
    new_contract->GetDataRequest()->GetRestriction()->TurnOnAll();
    new_contract->GetDataRequest()->GetRestriction()->RestrictDomains(domains);
    new_contract->GetDataRequest()->SetTimestep(timeStep);
    new_contract->SetOnDemandStreaming(true);

    GetInput()->Update(new_contract);
    vtkDataSet *rv = GetInputDataTree()->GetSingleLeaf();
    if (rv == NULL)
    {
        // This issue has been known to occur when: 
        //  -- the SIL is time varying
        //  -- the domain requested doesn't exist for the initial time step
        //     (which is the one where the SIL is created from).
        EXCEPTION1(VisItException, "Failure retrieving a data set while "
                     "advecting particles.  Please report this to a VisIt "
                     "developer.");
    }

    // Add it to the cache.
    DomainCacheEntry entry;
    entry.domainID = domainId;
    entry.timeStep = timeStep;
    entry.ds = rv;
    rv->Register(NULL);
    loadDSCount++;

    //Update the domainLoadCount.
    //Turn two ints into a long. Put timeStep in upper, domain in lower.
    unsigned long long A =  (((unsigned long long)timeStep)<<32);
    unsigned long long B =  ((unsigned long long)domainId);
    unsigned long long idx = A | B;

    if (domainLoadCount.find(idx) == domainLoadCount.end())
    {
        domainLoadCount[idx] = 1;
    }
    else
    {
        domainLoadCount[idx] ++;
    }

    domainQueue.push_front(entry);
    if ( domainQueue.size() > (size_t)maxQueueLength )
    {
        DomainCacheEntry tmp = domainQueue.back();
        PurgeDomain( tmp.domainID, tmp.timeStep );
        domainQueue.pop_back();
        purgeDSCount++;
    }

    return rv;
}

// ****************************************************************************
//  Method: avtDatasetOnDemandFilter::CopyCache
//
//  Purpose:
//    Copies the cache from one DoD filter to another.
//
//  Programmer: Hank Childs
//  Creation:  January 17, 2009
//
// ****************************************************************************

void
avtDatasetOnDemandFilter::CopyCache(avtDatasetOnDemandFilter *f)
{
    domainQueue = f->domainQueue;
}

// ****************************************************************************
//  Method: avtDatasetOnDemandFilter::GetDataAroundPoint
//
//  Purpose:
//      Forces a pipeline update to fetch the data around a point.
//
//  Programmer: Hank Childs
//  Creation:   March 22, 2009
//
//  Modifications:
//    Dave Pugmire, Wed Mar 25 09:15:23 EDT 2009
//    Add domain caching for point decomposed domains.
//
//    Gunther H. Weber, Fri Apr  3 17:38:12 PDT 2009
//    Enabled Dave's caching code. Since we currently use the same domain id
//    for all requests of data around points, using a map from the domain id
//    to a cell locator would not have worked. Thus, I moved the entry to
//    the DataCacheEntry instead.
//
//    Hank Childs, Sat Apr 11 23:27:56 CDT 2009
//    Remove some Delete calls, as they are now handled by the 
//    DomainCacheEntry struct directly.
//
//    David Camp, Mon Aug 15 09:36:04 PDT 2011
//    Need to remove the domain reference from the PIC locator cache.
//
// ****************************************************************************

vtkDataSet *
avtDatasetOnDemandFilter::GetDataAroundPoint(double X, double Y, double Z,
                                             int timeStep)
{
    if (DebugStream::Level1()) 
    {
        debug1<<"avtDatasetOnDemandFilter::GetDataAroundPoint("<<X<<", "<<Y<<", "<<Z<<", "<<timeStep<<");"<<endl;
    }
    if ( ! OperatingOnDemand() )
    {
        EXCEPTION0(ImproperUseException);
    }

    int domainId = 0; //Need to hash XYZ to domainId ???
    // FIXME: For the moment we just use one domain ID (0) for all points. This choice will cause
    // the following for loop to test *all* cache entries whether they contain the point location.
    // This strategy is not very efficient, but better than a pipeline re-execute.

    if (DebugStream::Level5())
    {
        debug5<<"Look in cache: "<<domainId<<" sz= "<<domainQueue.size()<<endl;
    }
    //See if it's in the cache.
    std::list<DomainCacheEntry>::iterator it;
    int foundPos = 0;
    for ( it = domainQueue.begin(); it != domainQueue.end(); it++ )
    {
        // Found it. Move it to the front of the list.
        if (it->domainID == domainId &&
            it->timeStep == timeStep)
        {
            //Do a bbox check.
            double bbox[6];
            it->ds->GetBounds(bbox);
            if (DebugStream::Level5()) 
            {
                debug5<<"BBOX ["<<bbox[0]<<", "<<bbox[1]<<"]["<<bbox[2]<<", "<<bbox[3]<<"]["<<bbox[4]<<", "<<bbox[5]<<"]"<<endl;
            }
            if (! (X >= bbox[0] && X <= bbox[1] &&
                   Y >= bbox[2] && Y <= bbox[3] &&
                   Z >= bbox[4] && Z <= bbox[5]))
                continue;
            
            bool foundIt = false;
            
            // If rectilinear, we found the domain.
            if (it->ds->GetDataObjectType() == VTK_RECTILINEAR_GRID)
                foundIt = true;
            else
            {
                //Do a cell check....
                if (DebugStream::Level5())
                {
                    debug5<<"It's in the bbox. Check the cell.\n";
                }
                vtkVisItCellLocator *cellLocator = it->cl;
                if ( cellLocator == NULL )
                {
                    cellLocator = vtkVisItCellLocator::New();
                    cellLocator->SetDataSet(it->ds);
                    cellLocator->IgnoreGhostsOn();
                    cellLocator->BuildLocator();
                    it->cl = cellLocator;
                }
                
                double rad = 1e-6, dist=0.0;
                double p[3] = {X,Y,Z}, resPt[3]={0.0,0.0,0.0};
                vtkIdType foundCell = -1;
                int subId = 0;

                if (cellLocator->FindClosestPointWithinRadius(p, rad, resPt,
                                                              foundCell, subId, dist))
                {
                    foundIt = true;
                    if (DebugStream::Level5())
                    {
                        debug5<<"Cell locate: We found the domain!\n";
                    }
                }
            }

            if (foundIt)
            {
                if (DebugStream::Level5())
                {
                    debug5<<"Found data in cace, returning cache entry " << foundPos << std::endl;
                }
                DomainCacheEntry entry;
                entry = *it;

                //Remove, then move to front.
                domainQueue.erase( it );
                domainQueue.push_front( entry );
                return entry.ds;
            }
        }
    }

    if (DebugStream::Level5())
    {
        debug5<<"     Update->GetDataAroundPoint, time= "<<timeStep<<endl;
    }
    avtContract_p new_contract = new avtContract(firstContract);
    new_contract->GetDataRequest()->GetRestriction()->TurnOnAll();
    avtPointSelection *ptsel = new avtPointSelection;
    double p[3] = { X, Y, Z };
    ptsel->SetPoint(p);

    // data selection will be deleted by contract.
    new_contract->GetDataRequest()->AddDataSelection(ptsel);

    new_contract->GetDataRequest()->SetTimestep(timeStep);
    new_contract->SetOnDemandStreaming(true);

    GetInput()->Update(new_contract);
    vtkDataSet *rv = GetInputDataTree()->GetSingleLeaf();

    if( rv )
    {
        // Add it to the cache.
        DomainCacheEntry entry;
        entry.domainID = domainId;
        entry.timeStep = timeStep;
        entry.ds = rv;
        entry.cl = NULL;
        rv->Register(NULL);
        loadDSCount++;

        domainQueue.push_front(entry);
        if ( domainQueue.size() > (size_t)maxQueueLength )
        {
            DomainCacheEntry tmp = domainQueue.back();
            PurgeDomain( tmp.domainID, tmp.timeStep );
            domainQueue.pop_back();
            purgeDSCount++;
        }
    }

    return rv;
}

// ****************************************************************************
//  Method: avtDatasetOnDemandFilter::DomainLoaded
//
//  Purpose:
//      Query if domain is loaded.
//
//  Programmer: Dave Pugmire
//  Creation:   March 13, 2008
//
//  Modifications:
//
//    Dave Pugmire, Tue Mar 10 12:41:11 EDT 2009
//    Added support for time/domain.
//
// ****************************************************************************
bool
avtDatasetOnDemandFilter::DomainLoaded(int domainID, int timeStep) const
{
    if ( ! OperatingOnDemand() )
        EXCEPTION0(ImproperUseException);
    
    if ( domainID >= 0 )
    {
        std::list<DomainCacheEntry>::const_iterator it;
        for (it = domainQueue.begin(); it != domainQueue.end(); it++)
            if (it->domainID == domainID &&
                it->timeStep == timeStep)
                return true;
    }
    return false;
}

// ****************************************************************************
//  Method: avtDatasetOnDemandFilter::GetLoadedDomains
//
//  Purpose:
//      Return a list of domains that are loaded.
//
//  Programmer: Dave Pugmire
//  Creation:   March 19, 2008
//
//  Modifications:
//
//    Dave Pugmire, Tue Mar 10 12:41:11 EDT 2009
//    Added support for time/domain.
//
// ****************************************************************************
void
avtDatasetOnDemandFilter::GetLoadedDomains(std::vector<std::vector<int> > &domains)
{
    if (DebugStream::Level1())
    {
        debug1<<"avtDatasetOnDemandFilter::GetLoadedDomains()\n";
    }
    if ( ! OperatingOnDemand() )
        EXCEPTION0(ImproperUseException);


    domains.resize(0);
    std::list<DomainCacheEntry>::const_iterator it;
    for ( it = domainQueue.begin(); it != domainQueue.end(); it++ )
    {
        std::vector<int> dom(2);
        dom[0] = it->domainID;
        dom[1] = it->timeStep;
        domains.push_back(dom);
    }
}


// ****************************************************************************
//  Method: avtDatasetOnDemandFilter::ModifyContract
//
//  Purpose:
//      Modifies the contract that steers pipeline execution.
//
//  Programmer: Hank Childs
//  Creation:   March 1, 2008
//
//  Modifications:
//
//    Hank Childs, Thu Jun 12 16:12:04 PDT 2008
//    Add support for where on-demand is not possible.
//
//    Hank Childs, Sun Jun 21 17:22:43 PDT 2015
//    Don't request streaming if upstream filter has disabled it.
//
// ****************************************************************************

avtContract_p
avtDatasetOnDemandFilter::ModifyContract(avtContract_p in_contract)
{
    firstContract = in_contract;

    // There is a serious architectural problem here.  The CanDoStreaming
    // method will interrogate the contract to see if ghost data is needed.
    // The contract at this point may believe that it is not needed ... but
    // someone upstream may decide that it is.  We could somehow try to defer
    // the decision, but this filter wants to turn off all of the domains, 
    // which may change the decisions other filters make.  
    //
    // One way out would be to always request ghost data, but that would 
    // preclude a lot of on demand processing, which defeats the purpose.
    //
    // I'm putting my head in the sand right now.  If you are running into
    // a problem, have your derived type of filter re-define ModifyContract
    // and always request ghost data.
    operatingOnDemand = 
            GetInput()->GetOriginatingSource()->CanDoStreaming(in_contract)
         && (GetInput()->GetInfo().GetValidity().IsStreamingPossible() == true)
         && CheckOnDemandViability();

    avtContract_p out_contract = new avtContract(in_contract);

    if (operatingOnDemand)
    {
        // Turn off the processing of all data
        // ... send in an empty domains list
        std::vector<int> domains;
        out_contract->GetDataRequest()->GetRestriction()
                                                   ->RestrictDomains(domains);
    }

    return out_contract;
}


// ****************************************************************************
//  Method: avtDatasetOnDemandFilter::UpdateDataObjectInfo
//
//  Purpose:
//      Tells the data object info that we are no longer streaming.
//
//  Programmer: Hank Childs
//  Creation:   March 9, 2008
//
// ****************************************************************************

void
avtDatasetOnDemandFilter::UpdateDataObjectInfo(void)
{
    // We won't be streaming on demand after this filter executes.
    avtDataValidity &out_atts = GetOutput()->GetInfo().GetValidity();
    out_atts.SetWhetherStreaming(false);
}


