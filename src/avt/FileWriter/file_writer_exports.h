// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#ifndef AVTFILEWRITER_EXPORTS_H
#define AVTFILEWRITER_EXPORTS_H

#if defined(_WIN32)
#if defined(AVTWRITER_EXPORTS) || defined(avtwriter_ser_EXPORTS) || defined(avtwriter_par_EXPORTS)
#define AVTFILEWRITER_API __declspec(dllexport)
#else
#define AVTFILEWRITER_API __declspec(dllimport)
#endif
#if defined(_MSC_VER)
// Turn off warning about lack of DLL interface
#pragma warning(disable:4251)
// Turn off warning non-dll class is base for dll-interface class.
#pragma warning(disable:4275)
// Turn off warning about identifier truncation
#pragma warning(disable:4786)
#endif
#else
# if __GNUC__ >= 4 && (defined(AVTWRITER_EXPORTS) || defined(avtwriter_ser_EXPORTS) || defined(avtwriter_par_EXPORTS))
#   define AVTFILEWRITER_API __attribute__ ((visibility("default")))
# else
#   define AVTFILEWRITER_API /* hidden by default */
# endif
#endif

#endif
