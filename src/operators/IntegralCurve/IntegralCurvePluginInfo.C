// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ****************************************************************************
//  File: IntegralCurvePluginInfo.C
// ****************************************************************************

#include <IntegralCurvePluginInfo.h>
#include <IntegralCurveAttributes.h>

#include <visit-config.h>
VISIT_PLUGIN_VERSION(IntegralCurve,OP_EXPORT)

VISIT_OPERATOR_PLUGIN_ENTRY(IntegralCurve,General)

// ****************************************************************************
//  Method: IntegralCurveGeneralPluginInfo::GetName
//
//  Purpose:
//    Return the name of the operator plugin.
//
//  Returns:    A pointer to the name of the operator plugin.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

const char *
IntegralCurveGeneralPluginInfo::GetName() const
{
    return "IntegralCurve";
}

// ****************************************************************************
//  Method: IntegralCurveGeneralPluginInfo::GetVersion
//
//  Purpose:
//    Return the version of the operator plugin.
//
//  Returns:    A pointer to the version of the operator plugin.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

const char *
IntegralCurveGeneralPluginInfo::GetVersion() const
{
    return "1.0";
}

// ****************************************************************************
//  Method: IntegralCurveGeneralPluginInfo::GetID
//
//  Purpose:
//    Return the id of the operator plugin.
//
//  Returns:    A pointer to the id of the operator plugin.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

const char *
IntegralCurveGeneralPluginInfo::GetID() const
{
    return "IntegralCurve_1.0";
}
// ****************************************************************************
//  Method: IntegralCurveGeneralPluginInfo::EnabledByDefault
//
//  Purpose:
//    Return true if this plugin should be enabled by default; false otherwise.
//
//  Returns:    true/false
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

bool
IntegralCurveGeneralPluginInfo::EnabledByDefault() const
{
    return true;
}

// ****************************************************************************
//  Method: IntegralCurveGeneralPluginInfo::GetCategoryName
//
//  Purpose:
//    Return the category name to which the operator belongs.
//
//  Returns:    Return the category name to which the operator belongs.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

const char *
IntegralCurveGeneralPluginInfo::GetCategoryName() const
{
    return "Integral Curves";
}
