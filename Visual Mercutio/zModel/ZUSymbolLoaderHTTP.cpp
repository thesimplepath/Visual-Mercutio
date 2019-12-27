// ZUSymbolLoaderHTTP.cpp: implementation of the ZUSymbolLoaderHTTP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUSymbolLoaderHTTP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUSymbolLoaderHTTP::ZUSymbolLoaderHTTP()
{}

ZUSymbolLoaderHTTP::~ZUSymbolLoaderHTTP()
{}

int ZUSymbolLoaderHTTP::LoadSymbol(const CString Location, PSS_SymbolEntity::IEntitySet& CompSet)
{
    return 0;
}

int ZUSymbolLoaderHTTP::LoadSymbols(const CString Location, PSS_SymbolEntity::IEntitySet& CompSet, bool LoadSubFolders /*= false*/)
{
    return 0;
}
