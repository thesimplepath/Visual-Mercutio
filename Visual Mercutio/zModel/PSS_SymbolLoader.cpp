/****************************************************************************
 * ==> PSS_SymbolLoader ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol loader                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SymbolLoader.h"

// processsoft
#include "PSS_FileSymbolLoader.h"
#include "PSS_FTPSymbolLoader.h"
#include "PSS_HTTPSymbolLoader.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_SymbolLoader
//---------------------------------------------------------------------------
PSS_SymbolLoader::PSS_SymbolLoader()
{}
//---------------------------------------------------------------------------
PSS_SymbolLoader::~PSS_SymbolLoader()
{}
//---------------------------------------------------------------------------
int PSS_SymbolLoader::LoadSymbol(const CString& location, PSS_SymbolEntity::IEntitySet& compSet, IEConnectionType connType)
{
    switch (connType)
    {
        case IEConnectionType::IE_CT_FileConnection: return PSS_FileSymbolLoader::LoadSymbol(location, compSet);
        case IEConnectionType::IE_CT_FTPConnection:  return PSS_FTPSymbolLoader::LoadSymbol (location, compSet);
        case IEConnectionType::IE_CT_HTTPConnection: return PSS_HTTPSymbolLoader::LoadSymbol(location, compSet);
    }

    return 0;
}
//---------------------------------------------------------------------------
int PSS_SymbolLoader::LoadSymbols(const CString&                location,
                                  PSS_SymbolEntity::IEntitySet& compSet,
                                  bool                          loadSubFolders,
                                  IEConnectionType              connType)
{
    switch (connType)
    {
        case IEConnectionType::IE_CT_FileConnection: return PSS_FileSymbolLoader::LoadSymbols(location, compSet, loadSubFolders);
        case IEConnectionType::IE_CT_FTPConnection:  return PSS_FTPSymbolLoader::LoadSymbols (location, compSet, loadSubFolders);
        case IEConnectionType::IE_CT_HTTPConnection: return PSS_HTTPSymbolLoader::LoadSymbols(location, compSet, loadSubFolders);
    }
    return 0;
}
//---------------------------------------------------------------------------
