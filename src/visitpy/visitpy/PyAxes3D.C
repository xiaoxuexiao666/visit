// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <PyAxes3D.h>
#include <ObserverToCallback.h>
#include <stdio.h>
#include <Py2and3Support.h>
#include <PyAxisAttributes.h>
#include <PyAxisAttributes.h>
#include <PyAxisAttributes.h>

// ****************************************************************************
// Module: PyAxes3D
//
// Purpose:
//   Contains the properties for the 3D axes.
//
// Note:       Autogenerated by xml2python. Do not modify by hand!
//
// Programmer: xml2python
// Creation:   omitted
//
// ****************************************************************************

//
// This struct contains the Python type information and a Axes3D.
//
struct Axes3DObject
{
    PyObject_HEAD
    Axes3D *data;
    bool        owns;
    PyObject   *parent;
};

//
// Internal prototypes
//
static PyObject *NewAxes3D(int);
std::string
PyAxes3D_ToString(const Axes3D *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    if(atts->GetVisible())
        snprintf(tmpStr, 1000, "%svisible = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%svisible = 0\n", prefix);
    str += tmpStr;
    if(atts->GetAutoSetTicks())
        snprintf(tmpStr, 1000, "%sautoSetTicks = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%sautoSetTicks = 0\n", prefix);
    str += tmpStr;
    if(atts->GetAutoSetScaling())
        snprintf(tmpStr, 1000, "%sautoSetScaling = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%sautoSetScaling = 0\n", prefix);
    str += tmpStr;
    snprintf(tmpStr, 1000, "%slineWidth = %d\n", prefix, atts->GetLineWidth());
    str += tmpStr;
    const char *tickLocation_names = "Inside, Outside, Both";
    switch (atts->GetTickLocation())
    {
      case Axes3D::Inside:
          snprintf(tmpStr, 1000, "%stickLocation = %sInside  # %s\n", prefix, prefix, tickLocation_names);
          str += tmpStr;
          break;
      case Axes3D::Outside:
          snprintf(tmpStr, 1000, "%stickLocation = %sOutside  # %s\n", prefix, prefix, tickLocation_names);
          str += tmpStr;
          break;
      case Axes3D::Both:
          snprintf(tmpStr, 1000, "%stickLocation = %sBoth  # %s\n", prefix, prefix, tickLocation_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    const char *axesType_names = "ClosestTriad, FurthestTriad, OutsideEdges, StaticTriad, StaticEdges";
    switch (atts->GetAxesType())
    {
      case Axes3D::ClosestTriad:
          snprintf(tmpStr, 1000, "%saxesType = %sClosestTriad  # %s\n", prefix, prefix, axesType_names);
          str += tmpStr;
          break;
      case Axes3D::FurthestTriad:
          snprintf(tmpStr, 1000, "%saxesType = %sFurthestTriad  # %s\n", prefix, prefix, axesType_names);
          str += tmpStr;
          break;
      case Axes3D::OutsideEdges:
          snprintf(tmpStr, 1000, "%saxesType = %sOutsideEdges  # %s\n", prefix, prefix, axesType_names);
          str += tmpStr;
          break;
      case Axes3D::StaticTriad:
          snprintf(tmpStr, 1000, "%saxesType = %sStaticTriad  # %s\n", prefix, prefix, axesType_names);
          str += tmpStr;
          break;
      case Axes3D::StaticEdges:
          snprintf(tmpStr, 1000, "%saxesType = %sStaticEdges  # %s\n", prefix, prefix, axesType_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    if(atts->GetTriadFlag())
        snprintf(tmpStr, 1000, "%striadFlag = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%striadFlag = 0\n", prefix);
    str += tmpStr;
    if(atts->GetBboxFlag())
        snprintf(tmpStr, 1000, "%sbboxFlag = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%sbboxFlag = 0\n", prefix);
    str += tmpStr;
    { // new scope
        std::string objPrefix(prefix);
        objPrefix += "xAxis.";
        str += PyAxisAttributes_ToString(&atts->GetXAxis(), objPrefix.c_str());
    }
    { // new scope
        std::string objPrefix(prefix);
        objPrefix += "yAxis.";
        str += PyAxisAttributes_ToString(&atts->GetYAxis(), objPrefix.c_str());
    }
    { // new scope
        std::string objPrefix(prefix);
        objPrefix += "zAxis.";
        str += PyAxisAttributes_ToString(&atts->GetZAxis(), objPrefix.c_str());
    }
    if(atts->GetSetBBoxLocation())
        snprintf(tmpStr, 1000, "%ssetBBoxLocation = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%ssetBBoxLocation = 0\n", prefix);
    str += tmpStr;
    {   const double *bboxLocation = atts->GetBboxLocation();
        snprintf(tmpStr, 1000, "%sbboxLocation = (", prefix);
        str += tmpStr;
        for(int i = 0; i < 6; ++i)
        {
            snprintf(tmpStr, 1000, "%g", bboxLocation[i]);
            str += tmpStr;
            if(i < 5)
            {
                snprintf(tmpStr, 1000, ", ");
                str += tmpStr;
            }
        }
        snprintf(tmpStr, 1000, ")\n");
        str += tmpStr;
    }
    {   const int *triadColor = atts->GetTriadColor();
        snprintf(tmpStr, 1000, "%striadColor = (", prefix);
        str += tmpStr;
        for(int i = 0; i < 3; ++i)
        {
            snprintf(tmpStr, 1000, "%d", triadColor[i]);
            str += tmpStr;
            if(i < 2)
            {
                snprintf(tmpStr, 1000, ", ");
                str += tmpStr;
            }
        }
        snprintf(tmpStr, 1000, ")\n");
        str += tmpStr;
    }
    snprintf(tmpStr, 1000, "%striadLineWidth = %g\n", prefix, atts->GetTriadLineWidth());
    str += tmpStr;
    snprintf(tmpStr, 1000, "%striadFont = %d\n", prefix, atts->GetTriadFont());
    str += tmpStr;
    if(atts->GetTriadBold())
        snprintf(tmpStr, 1000, "%striadBold = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%striadBold = 0\n", prefix);
    str += tmpStr;
    if(atts->GetTriadItalic())
        snprintf(tmpStr, 1000, "%striadItalic = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%striadItalic = 0\n", prefix);
    str += tmpStr;
    if(atts->GetTriadSetManually())
        snprintf(tmpStr, 1000, "%striadSetManually = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%striadSetManually = 0\n", prefix);
    str += tmpStr;
    return str;
}

static PyObject *
Axes3D_Notify(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    obj->data->Notify();
    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_SetVisible(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the visible in the object.
    obj->data->SetVisible(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetVisible(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetVisible()?1L:0L);
    return retval;
}

/*static*/ PyObject *
Axes3D_SetAutoSetTicks(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the autoSetTicks in the object.
    obj->data->SetAutoSetTicks(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetAutoSetTicks(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetAutoSetTicks()?1L:0L);
    return retval;
}

/*static*/ PyObject *
Axes3D_SetAutoSetScaling(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the autoSetScaling in the object.
    obj->data->SetAutoSetScaling(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetAutoSetScaling(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetAutoSetScaling()?1L:0L);
    return retval;
}

/*static*/ PyObject *
Axes3D_SetLineWidth(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the lineWidth in the object.
    obj->data->SetLineWidth(ival);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetLineWidth(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetLineWidth()));
    return retval;
}

/*static*/ PyObject *
Axes3D_SetTickLocation(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the tickLocation in the object.
    if(ival >= 0 && ival < 3)
        obj->data->SetTickLocation(Axes3D::Location(ival));
    else
    {
        fprintf(stderr, "An invalid tickLocation value was given. "
                        "Valid values are in the range of [0,2]. "
                        "You can also use the following names: "
                        "Inside, Outside, Both.");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetTickLocation(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetTickLocation()));
    return retval;
}

/*static*/ PyObject *
Axes3D_SetAxesType(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the axesType in the object.
    if(ival >= 0 && ival < 5)
        obj->data->SetAxesType(Axes3D::Axes(ival));
    else
    {
        fprintf(stderr, "An invalid axesType value was given. "
                        "Valid values are in the range of [0,4]. "
                        "You can also use the following names: "
                        "ClosestTriad, FurthestTriad, OutsideEdges, StaticTriad, StaticEdges"
                        ".");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetAxesType(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetAxesType()));
    return retval;
}

/*static*/ PyObject *
Axes3D_SetTriadFlag(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the triadFlag in the object.
    obj->data->SetTriadFlag(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetTriadFlag(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetTriadFlag()?1L:0L);
    return retval;
}

/*static*/ PyObject *
Axes3D_SetBboxFlag(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the bboxFlag in the object.
    obj->data->SetBboxFlag(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetBboxFlag(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetBboxFlag()?1L:0L);
    return retval;
}

/*static*/ PyObject *
Axes3D_SetXAxis(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    PyObject *newValue = NULL;
    if(!PyArg_ParseTuple(args, "O", &newValue))
        return NULL;
    if(!PyAxisAttributes_Check(newValue))
    {
        fprintf(stderr, "The xAxis field can only be set with AxisAttributes objects.\n");
        return NULL;
    }

    obj->data->SetXAxis(*PyAxisAttributes_FromPyObject(newValue));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetXAxis(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    // Since the new object will point to data owned by this object,
    // we need to increment the reference count.
    Py_INCREF(self);

    PyObject *retval = PyAxisAttributes_Wrap(&obj->data->GetXAxis());
    // Set the object's parent so the reference to the parent can be decref'd
    // when the child goes out of scope.
    PyAxisAttributes_SetParent(retval, self);

    return retval;
}

/*static*/ PyObject *
Axes3D_SetYAxis(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    PyObject *newValue = NULL;
    if(!PyArg_ParseTuple(args, "O", &newValue))
        return NULL;
    if(!PyAxisAttributes_Check(newValue))
    {
        fprintf(stderr, "The yAxis field can only be set with AxisAttributes objects.\n");
        return NULL;
    }

    obj->data->SetYAxis(*PyAxisAttributes_FromPyObject(newValue));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetYAxis(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    // Since the new object will point to data owned by this object,
    // we need to increment the reference count.
    Py_INCREF(self);

    PyObject *retval = PyAxisAttributes_Wrap(&obj->data->GetYAxis());
    // Set the object's parent so the reference to the parent can be decref'd
    // when the child goes out of scope.
    PyAxisAttributes_SetParent(retval, self);

    return retval;
}

/*static*/ PyObject *
Axes3D_SetZAxis(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    PyObject *newValue = NULL;
    if(!PyArg_ParseTuple(args, "O", &newValue))
        return NULL;
    if(!PyAxisAttributes_Check(newValue))
    {
        fprintf(stderr, "The zAxis field can only be set with AxisAttributes objects.\n");
        return NULL;
    }

    obj->data->SetZAxis(*PyAxisAttributes_FromPyObject(newValue));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetZAxis(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    // Since the new object will point to data owned by this object,
    // we need to increment the reference count.
    Py_INCREF(self);

    PyObject *retval = PyAxisAttributes_Wrap(&obj->data->GetZAxis());
    // Set the object's parent so the reference to the parent can be decref'd
    // when the child goes out of scope.
    PyAxisAttributes_SetParent(retval, self);

    return retval;
}

/*static*/ PyObject *
Axes3D_SetSetBBoxLocation(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the setBBoxLocation in the object.
    obj->data->SetSetBBoxLocation(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetSetBBoxLocation(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetSetBBoxLocation()?1L:0L);
    return retval;
}

/*static*/ PyObject *
Axes3D_SetBboxLocation(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    double *dvals = obj->data->GetBboxLocation();
    if(!PyArg_ParseTuple(args, "dddddd", &dvals[0], &dvals[1], &dvals[2], &dvals[3], &dvals[4], &dvals[5]))
    {
        PyObject     *tuple;
        if(!PyArg_ParseTuple(args, "O", &tuple))
            return NULL;

        if(PyTuple_Check(tuple))
        {
            if(PyTuple_Size(tuple) != 6)
                return NULL;

            PyErr_Clear();
            for(int i = 0; i < PyTuple_Size(tuple); ++i)
            {
                PyObject *item = PyTuple_GET_ITEM(tuple, i);
                if(PyFloat_Check(item))
                    dvals[i] = PyFloat_AS_DOUBLE(item);
                else if(PyInt_Check(item))
                    dvals[i] = double(PyInt_AS_LONG(item));
                else if(PyLong_Check(item))
                    dvals[i] = PyLong_AsDouble(item);
                else
                    dvals[i] = 0.;
            }
        }
        else
            return NULL;
    }

    // Mark the bboxLocation in the object as modified.
    obj->data->SelectBboxLocation();

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetBboxLocation(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    // Allocate a tuple the with enough entries to hold the bboxLocation.
    PyObject *retval = PyTuple_New(6);
    const double *bboxLocation = obj->data->GetBboxLocation();
    for(int i = 0; i < 6; ++i)
        PyTuple_SET_ITEM(retval, i, PyFloat_FromDouble(bboxLocation[i]));
    return retval;
}

/*static*/ PyObject *
Axes3D_SetTriadColor(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int *ivals = obj->data->GetTriadColor();
    if(!PyArg_ParseTuple(args, "iii", &ivals[0], &ivals[1], &ivals[2]))
    {
        PyObject     *tuple;
        if(!PyArg_ParseTuple(args, "O", &tuple))
            return NULL;

        if(PyTuple_Check(tuple))
        {
            if(PyTuple_Size(tuple) != 3)
                return NULL;

            PyErr_Clear();
            for(int i = 0; i < PyTuple_Size(tuple); ++i)
            {
                PyObject *item = PyTuple_GET_ITEM(tuple, i);
                if(PyFloat_Check(item))
                    ivals[i] = int(PyFloat_AS_DOUBLE(item));
                else if(PyInt_Check(item))
                    ivals[i] = int(PyInt_AS_LONG(item));
                else if(PyLong_Check(item))
                    ivals[i] = int(PyLong_AsDouble(item));
                else
                    ivals[i] = 0;
            }
        }
        else
            return NULL;
    }

    // Mark the triadColor in the object as modified.
    obj->data->SelectTriadColor();

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetTriadColor(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    // Allocate a tuple the with enough entries to hold the triadColor.
    PyObject *retval = PyTuple_New(3);
    const int *triadColor = obj->data->GetTriadColor();
    for(int i = 0; i < 3; ++i)
        PyTuple_SET_ITEM(retval, i, PyInt_FromLong(long(triadColor[i])));
    return retval;
}

/*static*/ PyObject *
Axes3D_SetTriadLineWidth(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    float fval;
    if(!PyArg_ParseTuple(args, "f", &fval))
        return NULL;

    // Set the triadLineWidth in the object.
    obj->data->SetTriadLineWidth(fval);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetTriadLineWidth(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyFloat_FromDouble(double(obj->data->GetTriadLineWidth()));
    return retval;
}

/*static*/ PyObject *
Axes3D_SetTriadFont(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the triadFont in the object.
    obj->data->SetTriadFont((int)ival);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetTriadFont(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetTriadFont()));
    return retval;
}

/*static*/ PyObject *
Axes3D_SetTriadBold(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the triadBold in the object.
    obj->data->SetTriadBold(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetTriadBold(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetTriadBold()?1L:0L);
    return retval;
}

/*static*/ PyObject *
Axes3D_SetTriadItalic(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the triadItalic in the object.
    obj->data->SetTriadItalic(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetTriadItalic(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetTriadItalic()?1L:0L);
    return retval;
}

/*static*/ PyObject *
Axes3D_SetTriadSetManually(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the triadSetManually in the object.
    obj->data->SetTriadSetManually(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
Axes3D_GetTriadSetManually(PyObject *self, PyObject *args)
{
    Axes3DObject *obj = (Axes3DObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetTriadSetManually()?1L:0L);
    return retval;
}



PyMethodDef PyAxes3D_methods[AXES3D_NMETH] = {
    {"Notify", Axes3D_Notify, METH_VARARGS},
    {"SetVisible", Axes3D_SetVisible, METH_VARARGS},
    {"GetVisible", Axes3D_GetVisible, METH_VARARGS},
    {"SetAutoSetTicks", Axes3D_SetAutoSetTicks, METH_VARARGS},
    {"GetAutoSetTicks", Axes3D_GetAutoSetTicks, METH_VARARGS},
    {"SetAutoSetScaling", Axes3D_SetAutoSetScaling, METH_VARARGS},
    {"GetAutoSetScaling", Axes3D_GetAutoSetScaling, METH_VARARGS},
    {"SetLineWidth", Axes3D_SetLineWidth, METH_VARARGS},
    {"GetLineWidth", Axes3D_GetLineWidth, METH_VARARGS},
    {"SetTickLocation", Axes3D_SetTickLocation, METH_VARARGS},
    {"GetTickLocation", Axes3D_GetTickLocation, METH_VARARGS},
    {"SetAxesType", Axes3D_SetAxesType, METH_VARARGS},
    {"GetAxesType", Axes3D_GetAxesType, METH_VARARGS},
    {"SetTriadFlag", Axes3D_SetTriadFlag, METH_VARARGS},
    {"GetTriadFlag", Axes3D_GetTriadFlag, METH_VARARGS},
    {"SetBboxFlag", Axes3D_SetBboxFlag, METH_VARARGS},
    {"GetBboxFlag", Axes3D_GetBboxFlag, METH_VARARGS},
    {"SetXAxis", Axes3D_SetXAxis, METH_VARARGS},
    {"GetXAxis", Axes3D_GetXAxis, METH_VARARGS},
    {"SetYAxis", Axes3D_SetYAxis, METH_VARARGS},
    {"GetYAxis", Axes3D_GetYAxis, METH_VARARGS},
    {"SetZAxis", Axes3D_SetZAxis, METH_VARARGS},
    {"GetZAxis", Axes3D_GetZAxis, METH_VARARGS},
    {"SetSetBBoxLocation", Axes3D_SetSetBBoxLocation, METH_VARARGS},
    {"GetSetBBoxLocation", Axes3D_GetSetBBoxLocation, METH_VARARGS},
    {"SetBboxLocation", Axes3D_SetBboxLocation, METH_VARARGS},
    {"GetBboxLocation", Axes3D_GetBboxLocation, METH_VARARGS},
    {"SetTriadColor", Axes3D_SetTriadColor, METH_VARARGS},
    {"GetTriadColor", Axes3D_GetTriadColor, METH_VARARGS},
    {"SetTriadLineWidth", Axes3D_SetTriadLineWidth, METH_VARARGS},
    {"GetTriadLineWidth", Axes3D_GetTriadLineWidth, METH_VARARGS},
    {"SetTriadFont", Axes3D_SetTriadFont, METH_VARARGS},
    {"GetTriadFont", Axes3D_GetTriadFont, METH_VARARGS},
    {"SetTriadBold", Axes3D_SetTriadBold, METH_VARARGS},
    {"GetTriadBold", Axes3D_GetTriadBold, METH_VARARGS},
    {"SetTriadItalic", Axes3D_SetTriadItalic, METH_VARARGS},
    {"GetTriadItalic", Axes3D_GetTriadItalic, METH_VARARGS},
    {"SetTriadSetManually", Axes3D_SetTriadSetManually, METH_VARARGS},
    {"GetTriadSetManually", Axes3D_GetTriadSetManually, METH_VARARGS},
    {NULL, NULL}
};

//
// Type functions
//

static void
Axes3D_dealloc(PyObject *v)
{
   Axes3DObject *obj = (Axes3DObject *)v;
   if(obj->parent != 0)
       Py_DECREF(obj->parent);
   if(obj->owns)
       delete obj->data;
}

static PyObject *Axes3D_richcompare(PyObject *self, PyObject *other, int op);
PyObject *
PyAxes3D_getattr(PyObject *self, char *name)
{
    if(strcmp(name, "visible") == 0)
        return Axes3D_GetVisible(self, NULL);
    if(strcmp(name, "autoSetTicks") == 0)
        return Axes3D_GetAutoSetTicks(self, NULL);
    if(strcmp(name, "autoSetScaling") == 0)
        return Axes3D_GetAutoSetScaling(self, NULL);
    if(strcmp(name, "lineWidth") == 0)
        return Axes3D_GetLineWidth(self, NULL);
    if(strcmp(name, "tickLocation") == 0)
        return Axes3D_GetTickLocation(self, NULL);
    if(strcmp(name, "Inside") == 0)
        return PyInt_FromLong(long(Axes3D::Inside));
    if(strcmp(name, "Outside") == 0)
        return PyInt_FromLong(long(Axes3D::Outside));
    if(strcmp(name, "Both") == 0)
        return PyInt_FromLong(long(Axes3D::Both));

    if(strcmp(name, "axesType") == 0)
        return Axes3D_GetAxesType(self, NULL);
    if(strcmp(name, "ClosestTriad") == 0)
        return PyInt_FromLong(long(Axes3D::ClosestTriad));
    if(strcmp(name, "FurthestTriad") == 0)
        return PyInt_FromLong(long(Axes3D::FurthestTriad));
    if(strcmp(name, "OutsideEdges") == 0)
        return PyInt_FromLong(long(Axes3D::OutsideEdges));
    if(strcmp(name, "StaticTriad") == 0)
        return PyInt_FromLong(long(Axes3D::StaticTriad));
    if(strcmp(name, "StaticEdges") == 0)
        return PyInt_FromLong(long(Axes3D::StaticEdges));

    if(strcmp(name, "triadFlag") == 0)
        return Axes3D_GetTriadFlag(self, NULL);
    if(strcmp(name, "bboxFlag") == 0)
        return Axes3D_GetBboxFlag(self, NULL);
    if(strcmp(name, "xAxis") == 0)
        return Axes3D_GetXAxis(self, NULL);
    if(strcmp(name, "yAxis") == 0)
        return Axes3D_GetYAxis(self, NULL);
    if(strcmp(name, "zAxis") == 0)
        return Axes3D_GetZAxis(self, NULL);
    if(strcmp(name, "setBBoxLocation") == 0)
        return Axes3D_GetSetBBoxLocation(self, NULL);
    if(strcmp(name, "bboxLocation") == 0)
        return Axes3D_GetBboxLocation(self, NULL);
    if(strcmp(name, "triadColor") == 0)
        return Axes3D_GetTriadColor(self, NULL);
    if(strcmp(name, "triadLineWidth") == 0)
        return Axes3D_GetTriadLineWidth(self, NULL);
    if(strcmp(name, "triadFont") == 0)
        return Axes3D_GetTriadFont(self, NULL);
    if(strcmp(name, "triadBold") == 0)
        return Axes3D_GetTriadBold(self, NULL);
    if(strcmp(name, "triadItalic") == 0)
        return Axes3D_GetTriadItalic(self, NULL);
    if(strcmp(name, "triadSetManually") == 0)
        return Axes3D_GetTriadSetManually(self, NULL);

    return Py_FindMethod(PyAxes3D_methods, self, name);
}

int
PyAxes3D_setattr(PyObject *self, char *name, PyObject *args)
{
    // Create a tuple to contain the arguments since all of the Set
    // functions expect a tuple.
    PyObject *tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(tuple, 0, args);
    Py_INCREF(args);
    PyObject *obj = NULL;

    if(strcmp(name, "visible") == 0)
        obj = Axes3D_SetVisible(self, tuple);
    else if(strcmp(name, "autoSetTicks") == 0)
        obj = Axes3D_SetAutoSetTicks(self, tuple);
    else if(strcmp(name, "autoSetScaling") == 0)
        obj = Axes3D_SetAutoSetScaling(self, tuple);
    else if(strcmp(name, "lineWidth") == 0)
        obj = Axes3D_SetLineWidth(self, tuple);
    else if(strcmp(name, "tickLocation") == 0)
        obj = Axes3D_SetTickLocation(self, tuple);
    else if(strcmp(name, "axesType") == 0)
        obj = Axes3D_SetAxesType(self, tuple);
    else if(strcmp(name, "triadFlag") == 0)
        obj = Axes3D_SetTriadFlag(self, tuple);
    else if(strcmp(name, "bboxFlag") == 0)
        obj = Axes3D_SetBboxFlag(self, tuple);
    else if(strcmp(name, "xAxis") == 0)
        obj = Axes3D_SetXAxis(self, tuple);
    else if(strcmp(name, "yAxis") == 0)
        obj = Axes3D_SetYAxis(self, tuple);
    else if(strcmp(name, "zAxis") == 0)
        obj = Axes3D_SetZAxis(self, tuple);
    else if(strcmp(name, "setBBoxLocation") == 0)
        obj = Axes3D_SetSetBBoxLocation(self, tuple);
    else if(strcmp(name, "bboxLocation") == 0)
        obj = Axes3D_SetBboxLocation(self, tuple);
    else if(strcmp(name, "triadColor") == 0)
        obj = Axes3D_SetTriadColor(self, tuple);
    else if(strcmp(name, "triadLineWidth") == 0)
        obj = Axes3D_SetTriadLineWidth(self, tuple);
    else if(strcmp(name, "triadFont") == 0)
        obj = Axes3D_SetTriadFont(self, tuple);
    else if(strcmp(name, "triadBold") == 0)
        obj = Axes3D_SetTriadBold(self, tuple);
    else if(strcmp(name, "triadItalic") == 0)
        obj = Axes3D_SetTriadItalic(self, tuple);
    else if(strcmp(name, "triadSetManually") == 0)
        obj = Axes3D_SetTriadSetManually(self, tuple);

    if(obj != NULL)
        Py_DECREF(obj);

    Py_DECREF(tuple);
    if( obj == NULL)
        PyErr_Format(PyExc_RuntimeError, "Unable to set unknown attribute: '%s'", name);
    return (obj != NULL) ? 0 : -1;
}

static int
Axes3D_print(PyObject *v, FILE *fp, int flags)
{
    Axes3DObject *obj = (Axes3DObject *)v;
    fprintf(fp, "%s", PyAxes3D_ToString(obj->data, "").c_str());
    return 0;
}

PyObject *
Axes3D_str(PyObject *v)
{
    Axes3DObject *obj = (Axes3DObject *)v;
    return PyString_FromString(PyAxes3D_ToString(obj->data,"").c_str());
}

//
// The doc string for the class.
//
#if PY_MAJOR_VERSION > 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5)
static const char *Axes3D_Purpose = "Contains the properties for the 3D axes.";
#else
static char *Axes3D_Purpose = "Contains the properties for the 3D axes.";
#endif

//
// Python Type Struct Def Macro from Py2and3Support.h
//
//         VISIT_PY_TYPE_OBJ( VPY_TYPE,
//                            VPY_NAME,
//                            VPY_OBJECT,
//                            VPY_DEALLOC,
//                            VPY_PRINT,
//                            VPY_GETATTR,
//                            VPY_SETATTR,
//                            VPY_STR,
//                            VPY_PURPOSE,
//                            VPY_RICHCOMP,
//                            VPY_AS_NUMBER)

//
// The type description structure
//

VISIT_PY_TYPE_OBJ(Axes3DType,         \
                  "Axes3D",           \
                  Axes3DObject,       \
                  Axes3D_dealloc,     \
                  Axes3D_print,       \
                  PyAxes3D_getattr,   \
                  PyAxes3D_setattr,   \
                  Axes3D_str,         \
                  Axes3D_Purpose,     \
                  Axes3D_richcompare, \
                  0); /* as_number*/

//
// Helper function for comparing.
//
static PyObject *
Axes3D_richcompare(PyObject *self, PyObject *other, int op)
{
    // only compare against the same type 
    if ( Py_TYPE(self) != &Axes3DType
         || Py_TYPE(other) != &Axes3DType)
    {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }

    PyObject *res = NULL;
    Axes3D *a = ((Axes3DObject *)self)->data;
    Axes3D *b = ((Axes3DObject *)other)->data;

    switch (op)
    {
       case Py_EQ:
           res = (*a == *b) ? Py_True : Py_False;
           break;
       case Py_NE:
           res = (*a != *b) ? Py_True : Py_False;
           break;
       default:
           res = Py_NotImplemented;
           break;
    }

    Py_INCREF(res);
    return res;
}

//
// Helper functions for object allocation.
//

static Axes3D *defaultAtts = 0;
static Axes3D *currentAtts = 0;

static PyObject *
NewAxes3D(int useCurrent)
{
    Axes3DObject *newObject;
    newObject = PyObject_NEW(Axes3DObject, &Axes3DType);
    if(newObject == NULL)
        return NULL;
    if(useCurrent && currentAtts != 0)
        newObject->data = new Axes3D(*currentAtts);
    else if(defaultAtts != 0)
        newObject->data = new Axes3D(*defaultAtts);
    else
        newObject->data = new Axes3D;
    newObject->owns = true;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

static PyObject *
WrapAxes3D(const Axes3D *attr)
{
    Axes3DObject *newObject;
    newObject = PyObject_NEW(Axes3DObject, &Axes3DType);
    if(newObject == NULL)
        return NULL;
    newObject->data = (Axes3D *)attr;
    newObject->owns = false;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

///////////////////////////////////////////////////////////////////////////////
//
// Interface that is exposed to the VisIt module.
//
///////////////////////////////////////////////////////////////////////////////

PyObject *
Axes3D_new(PyObject *self, PyObject *args)
{
    int useCurrent = 0;
    if (!PyArg_ParseTuple(args, "i", &useCurrent))
    {
        if (!PyArg_ParseTuple(args, ""))
            return NULL;
        else
            PyErr_Clear();
    }

    return (PyObject *)NewAxes3D(useCurrent);
}

//
// Plugin method table. These methods are added to the visitmodule's methods.
//
static PyMethodDef Axes3DMethods[] = {
    {"Axes3D", Axes3D_new, METH_VARARGS},
    {NULL,      NULL}        /* Sentinel */
};

static Observer *Axes3DObserver = 0;

std::string
PyAxes3D_GetLogString()
{
    std::string s("Axes3D = Axes3D()\n");
    if(currentAtts != 0)
        s += PyAxes3D_ToString(currentAtts, "Axes3D.");
    return s;
}

static void
PyAxes3D_CallLogRoutine(Subject *subj, void *data)
{
    typedef void (*logCallback)(const std::string &);
    logCallback cb = (logCallback)data;

    if(cb != 0)
    {
        std::string s("Axes3D = Axes3D()\n");
        s += PyAxes3D_ToString(currentAtts, "Axes3D.");
        cb(s);
    }
}

void
PyAxes3D_StartUp(Axes3D *subj, void *data)
{
    if(subj == 0)
        return;

    currentAtts = subj;
    PyAxes3D_SetDefaults(subj);

    //
    // Create the observer that will be notified when the attributes change.
    //
    if(Axes3DObserver == 0)
    {
        Axes3DObserver = new ObserverToCallback(subj,
            PyAxes3D_CallLogRoutine, (void *)data);
    }

}

void
PyAxes3D_CloseDown()
{
    delete defaultAtts;
    defaultAtts = 0;
    delete Axes3DObserver;
    Axes3DObserver = 0;
}

PyMethodDef *
PyAxes3D_GetMethodTable(int *nMethods)
{
    *nMethods = 1;
    return Axes3DMethods;
}

bool
PyAxes3D_Check(PyObject *obj)
{
    return (obj->ob_type == &Axes3DType);
}

Axes3D *
PyAxes3D_FromPyObject(PyObject *obj)
{
    Axes3DObject *obj2 = (Axes3DObject *)obj;
    return obj2->data;
}

PyObject *
PyAxes3D_New()
{
    return NewAxes3D(0);
}

PyObject *
PyAxes3D_Wrap(const Axes3D *attr)
{
    return WrapAxes3D(attr);
}

void
PyAxes3D_SetParent(PyObject *obj, PyObject *parent)
{
    Axes3DObject *obj2 = (Axes3DObject *)obj;
    obj2->parent = parent;
}

void
PyAxes3D_SetDefaults(const Axes3D *atts)
{
    if(defaultAtts)
        delete defaultAtts;

    defaultAtts = new Axes3D(*atts);
}

