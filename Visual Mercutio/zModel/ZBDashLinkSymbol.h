// ZBDashLinkSymbol.h: interface for the ZBDashLinkSymbol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBDASHLINKSYMBOL_H__6807A781_8BEE_441D_9827_9919B29E690D__INCLUDED_)
#define AFX_ZBDASHLINKSYMBOL_H__6807A781_8BEE_441D_9827_9919B29E690D__INCLUDED_

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

// processsoft
#include "PSS_LinkSymbol.h"

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


class AFX_EXT_CLASS ZBDashLinkSymbol : public PSS_LinkSymbol
{
public:
    ZBDashLinkSymbol();
    virtual ~ZBDashLinkSymbol();
};

#endif
