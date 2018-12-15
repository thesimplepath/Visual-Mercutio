// ZUSymbolLoader.h: interface for the ZUSymbolLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSYMBOLLOADER_H__35AD884D_BEF1_414D_A895_405DBB8EC020__INCLUDED_)
#define AFX_ZUSYMBOLLOADER_H__35AD884D_BEF1_414D_A895_405DBB8EC020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


// ZBSymbolEntity
#include "ZBSymbolEntity.h"


#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZUSymbolLoader  
{
public:
    enum ConnectionType { FileConnection, FTPConnection, HTTPConnection };
    ZUSymbolLoader();
    virtual ~ZUSymbolLoader();

    // Return the number of element loaded
    // 0 if no element loaded
    static int LoadSymbol( const CString Location, ZBSymbolEntitySet& CompSet, ConnectionType Conx = FileConnection );
    static int LoadSymbols( const CString Location, ZBSymbolEntitySet& CompSet, bool LoadSubFolders = false, ConnectionType Conx = FileConnection );

private:

};

#endif // !defined(AFX_ZUSYMBOLLOADER_H__35AD884D_BEF1_414D_A895_405DBB8EC020__INCLUDED_)
