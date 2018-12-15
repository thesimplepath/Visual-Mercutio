// ZBSearchSymbolLogLine.h: interface for the ZBSearchSymbolLogLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSEARCHSYMBOLLOGLINE_H__22ADCFD1_E459_4A93_87BF_DDC6E4F853FD__INCLUDED_)
#define AFX_ZBSEARCHSYMBOLLOGLINE_H__22ADCFD1_E459_4A93_87BF_DDC6E4F853FD__INCLUDED_

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


#include "ZBGenericSymbolErrorLine.h"

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


class AFX_EXT_CLASS ZBSearchSymbolLogLine : public ZBGenericSymbolErrorLine  
{
public:
    ZBSearchSymbolLogLine();

    ZBSearchSymbolLogLine( const CString symbolname,
                           const CString symbolpath, 
                           const CString message = "" );
    ZBSearchSymbolLogLine( const CString symbolname,
                           const CString symbolpath, 
                           UINT nIDSmessage );
    
    virtual ~ZBSearchSymbolLogLine();



};

#endif // !defined(AFX_ZBSEARCHSYMBOLLOGLINE_H__22ADCFD1_E459_4A93_87BF_DDC6E4F853FD__INCLUDED_)
