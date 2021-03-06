// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                             avtVsOptions.h                              //
// ************************************************************************* //

#ifndef AVT_Vs_OPTIONS_H
#define AVT_Vs_OPTIONS_H

class DBOptionsAttributes;


// ****************************************************************************
//  Functions: avtVsOptions
//
//  Purpose:
//      Creates the options for  Vs readers and/or writers.
//
//  Programmer: allen -- generated by xml2avt
//  Creation:   Wed Aug 11 13:45:13 PST 2010
//
// ****************************************************************************

DBOptionsAttributes *GetVsReadOptions(void);
DBOptionsAttributes *GetVsWriteOptions(void);


#endif
