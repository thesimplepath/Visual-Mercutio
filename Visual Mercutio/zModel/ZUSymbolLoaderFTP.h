// ZUSymbolLoaderFTP.h: interface for the ZUSymbolLoaderFTP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSYMBOLLOADERFTP_H__1B7C6F92_B63F_413F_9A18_9336C6B208B9__INCLUDED_)
#define AFX_ZUSYMBOLLOADERFTP_H__1B7C6F92_B63F_413F_9A18_9336C6B208B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// processsoft
#include "PSS_SymbolEntity.h"

// This is an helper class of ZUSymbolLoader, privately used by
class ZUSymbolLoaderFTP
{
public:
    ZUSymbolLoaderFTP();
    virtual ~ZUSymbolLoaderFTP();

    // Return the number of element loaded
    // 0 if no element loaded
    static int LoadSymbol(const CString Location, PSS_SymbolEntity::IEntitySet& CompSet);
    static int LoadSymbols(const CString Location, PSS_SymbolEntity::IEntitySet& CompSet, bool LoadSubFolders = false);
};

#endif
