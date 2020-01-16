/****************************************************************************
 * ==> PSS_FTPSymbolLoader -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a ftp symbol loader                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FTPSymbolLoader.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_FTPSymbolLoader
//---------------------------------------------------------------------------
PSS_FTPSymbolLoader::PSS_FTPSymbolLoader()
{}
//---------------------------------------------------------------------------
PSS_FTPSymbolLoader::~PSS_FTPSymbolLoader()
{}
//---------------------------------------------------------------------------
int PSS_FTPSymbolLoader::LoadSymbol(const CString& location, PSS_SymbolEntity::IEntitySet& compSet)
{
    return 0;
}
//---------------------------------------------------------------------------
int PSS_FTPSymbolLoader::LoadSymbols(const CString& location, PSS_SymbolEntity::IEntitySet& compSet, bool loadSubFolders)
{
    return 0;
}
//---------------------------------------------------------------------------
