/****************************************************************************
 * ==> PSS_HTTPSymbolLoader ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a network (HTTP) symbol loader                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_HTTPSymbolLoader.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_HTTPSymbolLoader
//---------------------------------------------------------------------------
PSS_HTTPSymbolLoader::PSS_HTTPSymbolLoader()
{}
//---------------------------------------------------------------------------
PSS_HTTPSymbolLoader::~PSS_HTTPSymbolLoader()
{}
//---------------------------------------------------------------------------
int PSS_HTTPSymbolLoader::LoadSymbol(const CString& location, PSS_SymbolEntity::IEntitySet& compSet)
{
    return 0;
}
//---------------------------------------------------------------------------
int PSS_HTTPSymbolLoader::LoadSymbols(const CString& location, PSS_SymbolEntity::IEntitySet& compSet, bool loadSubFolders)
{
    return 0;
}
//---------------------------------------------------------------------------
