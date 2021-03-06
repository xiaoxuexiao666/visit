// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <PlainTextPluginInfo.h>
#include <avtPlainTextFileFormat.h>
#include <avtSTSDFileFormatInterface.h>
#include <avtGenericDatabase.h>
#include <avtPlainTextOptions.h>

// ****************************************************************************
//  Method:  PlainTextCommonPluginInfo::GetDatabaseType
//
//  Purpose:
//    Returns the type of a PlainText database.
//
//  Programmer:  generated by xml2info
//  Creation:    omitted
//
// ****************************************************************************
DatabaseType
PlainTextCommonPluginInfo::GetDatabaseType()
{
    return DB_TYPE_STSD;
}

// ****************************************************************************
//  Method: PlainTextCommonPluginInfo::SetupDatabase
//
//  Purpose:
//      Sets up a PlainText database.
//
//  Arguments:
//      list    A list of file names.
//      nList   The number of timesteps in list.
//      nBlocks The number of blocks in the list.
//
//  Returns:    A PlainText database from list.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************
avtDatabase *
PlainTextCommonPluginInfo::SetupDatabase(const char *const *list,
                                   int nList, int nBlock)
{
    int nTimestep = nList / nBlock;
    avtSTSDFileFormat ***ffl = new avtSTSDFileFormat**[nTimestep];
    for (int i = 0; i < nTimestep; i++)
    {
        ffl[i] = new avtSTSDFileFormat*[nBlock];
        for (int j = 0; j < nBlock; j++)
        {
            ffl[i][j] = new avtPlainTextFileFormat(list[i*nBlock + j], readOptions);
        }
    }
    avtSTSDFileFormatInterface *inter
           = new avtSTSDFileFormatInterface(ffl, nTimestep, nBlock);
    return new avtGenericDatabase(inter);
}

// ****************************************************************************
//  Method: PlainTextCommonPluginInfo::GetReadOptions
//
//  Purpose:
//      Gets the read options.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

DBOptionsAttributes *
PlainTextCommonPluginInfo::GetReadOptions() const
{
    return GetPlainTextReadOptions();
}

// ****************************************************************************
//  Method: PlainTextCommonPluginInfo::GetWriteOptions
//
//  Purpose:
//      Gets the write options.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

DBOptionsAttributes *
PlainTextCommonPluginInfo::GetWriteOptions() const
{
    return GetPlainTextWriteOptions();
}

