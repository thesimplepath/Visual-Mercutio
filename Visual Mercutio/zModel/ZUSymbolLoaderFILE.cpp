// ZUSymbolLoaderFILE.cpp: implementation of the ZUSymbolLoaderFILE class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUSymbolLoaderFILE.h"

#include "zBaseLib\File.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUSymbolLoaderFILE::ZUSymbolLoaderFILE()
{

}

ZUSymbolLoaderFILE::~ZUSymbolLoaderFILE()
{

}


int ZUSymbolLoaderFILE::LoadSymbol( const CString Location, ZBSymbolEntitySet& CompSet )
{
    // Check the existence of file
    if (!ZFile::Exist(Location))
        return 0;

    ZBSymbolEntity    Entity;
    if (!Entity.ReadFromFile( Location ))
        return 0;
    CompSet.Add( Entity.Clone() );
    return CompSet.GetSize();
}


int ZUSymbolLoaderFILE::LoadSymbols( const CString Location, ZBSymbolEntitySet& CompSet, bool LoadSubFolders /*= false*/ )
{
    return 0;
}


