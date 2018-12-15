// ZBSolidLinkSymbol.h: interface for the ZBSolidLinkSymbol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSOLIDLINKSYMBOL_H__5E36A170_1309_40A0_921E_21E59A1D4936__INCLUDED_)
#define AFX_ZBSOLIDLINKSYMBOL_H__5E36A170_1309_40A0_921E_21E59A1D4936__INCLUDED_

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


#include "ZBLinkSymbol.h"


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


class AFX_EXT_CLASS ZBSolidLinkSymbol : public ZBLinkSymbol  
{
public:
    ZBSolidLinkSymbol();
    virtual ~ZBSolidLinkSymbol();

};

#endif // !defined(AFX_ZBSOLIDLINKSYMBOL_H__5E36A170_1309_40A0_921E_21E59A1D4936__INCLUDED_)
