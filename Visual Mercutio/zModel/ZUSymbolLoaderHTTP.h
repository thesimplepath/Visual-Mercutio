// ZUSymbolLoaderHTTP.h: interface for the ZUSymbolLoaderHTTP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSYMBOLLOADERHTTP_H__D573D671_6ACC_4671_ABF3_BF9B68193741__INCLUDED_)
#define AFX_ZUSYMBOLLOADERHTTP_H__D573D671_6ACC_4671_ABF3_BF9B68193741__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

// processsoft
#include "PSS_SymbolEntity.h"

// This is an helper class of ZUSymbolLoader, privately used by
class ZUSymbolLoaderHTTP
{
public:
    ZUSymbolLoaderHTTP();
    virtual ~ZUSymbolLoaderHTTP();

    // Return the number of element loaded
    // 0 if no element loaded
    static int LoadSymbol(const CString Location, PSS_SymbolEntity::IEntitySet& CompSet);
    static int LoadSymbols(const CString Location, PSS_SymbolEntity::IEntitySet & CompSet, bool LoadSubFolders = false);
};

#endif
