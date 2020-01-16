/****************************************************************************
 * ==> PSS_FileSymbolLoader ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file symbol loader                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FileSymbolLoader.h"

// processsoft
#include "zBaseLib\PSS_File.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_FileSymbolLoader
//---------------------------------------------------------------------------
PSS_FileSymbolLoader::PSS_FileSymbolLoader()
{}
//---------------------------------------------------------------------------
PSS_FileSymbolLoader::~PSS_FileSymbolLoader()
{}
//---------------------------------------------------------------------------
int PSS_FileSymbolLoader::LoadSymbol(const CString& location, PSS_SymbolEntity::IEntitySet& compSet)
{
    // check if the file exists
    if (!PSS_File::Exist(location))
        return 0;

    PSS_SymbolEntity entity;

    // read the file content
    if (!entity.ReadFromFile(location))
        return 0;

    compSet.Add(entity.Clone());
    return compSet.GetSize();
}
//---------------------------------------------------------------------------
int PSS_FileSymbolLoader::LoadSymbols(const CString& location, PSS_SymbolEntity::IEntitySet& compSet, bool loadSubFolders)
{
    return 0;
}
//---------------------------------------------------------------------------
