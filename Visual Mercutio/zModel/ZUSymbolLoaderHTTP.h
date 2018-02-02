// ZUSymbolLoaderHTTP.h: interface for the ZUSymbolLoaderHTTP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSYMBOLLOADERHTTP_H__D573D671_6ACC_4671_ABF3_BF9B68193741__INCLUDED_)
#define AFX_ZUSYMBOLLOADERHTTP_H__D573D671_6ACC_4671_ABF3_BF9B68193741__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ZBSymbolEntity
#include "ZBSymbolEntity.h"

// This is an helper class of ZUSymbolLoader, privately used by
class ZUSymbolLoaderHTTP  
{
public:
	ZUSymbolLoaderHTTP();
	virtual ~ZUSymbolLoaderHTTP();

	// Return the number of element loaded
	// 0 if no element loaded
	static int LoadSymbol( const CString Location, ZBSymbolEntitySet& CompSet );
	static int LoadSymbols( const CString Location, ZBSymbolEntitySet& CompSet, bool LoadSubFolders = false );
};

#endif // !defined(AFX_ZUSYMBOLLOADERHTTP_H__D573D671_6ACC_4671_ABF3_BF9B68193741__INCLUDED_)
