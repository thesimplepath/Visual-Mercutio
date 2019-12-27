// ZUSymbolLoaderFILE.h: interface for the ZUSymbolLoaderFILE class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSYMBOLLOADERFILE_H__FA976F5B_BE62_4531_9D29_C81EBF4A4C7E__INCLUDED_)
#define AFX_ZUSYMBOLLOADERFILE_H__FA976F5B_BE62_4531_9D29_C81EBF4A4C7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// processsoft
#include "PSS_SymbolEntity.h"


// This is an helper class of ZUSymbolLoader, privately used by
class ZUSymbolLoaderFILE
{
public:
    ZUSymbolLoaderFILE();
    virtual ~ZUSymbolLoaderFILE();

    // Return the number of element loaded
    // 0 if no element loaded
    static int LoadSymbol(const CString Location, PSS_SymbolEntity::IEntitySet& CompSet);
    static int LoadSymbols(const CString Location, PSS_SymbolEntity::IEntitySet& CompSet, bool LoadSubFolders = false);
};

#endif
