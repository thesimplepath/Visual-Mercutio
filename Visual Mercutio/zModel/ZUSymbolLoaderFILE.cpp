// ZUSymbolLoaderFILE.cpp: implementation of the ZUSymbolLoaderFILE class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUSymbolLoaderFILE.h"

#include "zBaseLib\PSS_File.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUSymbolLoaderFILE::ZUSymbolLoaderFILE()
{}

ZUSymbolLoaderFILE::~ZUSymbolLoaderFILE()
{}

int ZUSymbolLoaderFILE::LoadSymbol(const CString Location, PSS_SymbolEntity::IEntitySet& CompSet)
{
    // Check the existence of file
    if (!PSS_File::Exist(Location))
        return 0;

    PSS_SymbolEntity entity;
    if (!entity.ReadFromFile(Location))
        return 0;

    CompSet.Add(entity.Clone());
    return CompSet.GetSize();
}

int ZUSymbolLoaderFILE::LoadSymbols(const CString Location, PSS_SymbolEntity::IEntitySet& CompSet, bool LoadSubFolders /*= false*/)
{
    return 0;
}
