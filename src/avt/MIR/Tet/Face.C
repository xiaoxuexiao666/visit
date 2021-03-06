// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include "Face.h"

// ****************************************************************************
//  Method:  Face::HashFunction
//
//  Purpose:
//    Hash function for Face's
//
//  Arguments:
//    face       the face
//
//  Programmer:  Jeremy Meredith
//  Creation:    December 12, 2000
//
// ****************************************************************************
unsigned int
Face::HashFunction(Face &face)
{
    return ((face.a<<8)^(face.b<<4))^face.c;
}
