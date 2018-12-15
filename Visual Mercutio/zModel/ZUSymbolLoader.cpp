// ZUSymbolLoader.cpp: implementation of the ZUSymbolLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUSymbolLoader.h"


#include "ZUSymbolLoaderFILE.h"
#include "ZUSymbolLoaderFTP.h"
#include "ZUSymbolLoaderHTTP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUSymbolLoader::ZUSymbolLoader()
{

}

ZUSymbolLoader::~ZUSymbolLoader()
{

}


int ZUSymbolLoader::LoadSymbol( const CString Location, ZBSymbolEntitySet& CompSet, ConnectionType Conx /*= FileConnection*/ )
{
    switch (Conx)
    {
        case FileConnection:
        {
            return ZUSymbolLoaderFILE::LoadSymbol( Location, CompSet );
        }
        case FTPConnection:
        {
            return ZUSymbolLoaderFTP::LoadSymbol( Location, CompSet );
        }
        case HTTPConnection:
        {
            return ZUSymbolLoaderHTTP::LoadSymbol( Location, CompSet );
        }
    }
    return 0;
}


int ZUSymbolLoader::LoadSymbols( const CString Location, ZBSymbolEntitySet& CompSet, bool LoadSubFolders /*= false*/, ConnectionType Conx /*= FileConnection*/ )
{
    switch (Conx)
    {
        case FileConnection:
        {
            return ZUSymbolLoaderFILE::LoadSymbols( Location, CompSet, LoadSubFolders );
        }
        case FTPConnection:
        {
            return ZUSymbolLoaderFTP::LoadSymbols( Location, CompSet, LoadSubFolders );
        }
        case HTTPConnection:
        {
            return ZUSymbolLoaderHTTP::LoadSymbols( Location, CompSet, LoadSubFolders );
        }
    }
    return 0;
}
