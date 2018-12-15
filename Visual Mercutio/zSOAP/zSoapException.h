/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module zSoapException.h | Interface of the <c zSoapException> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:             Gaya
// <nl>Created:         05/2002
// <nl>Description:  exception class container
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __PSOAPEXCEPTION_HDR_
#define __PSOAPEXCEPTION_HDR_

#include "zSOAPRes.h"

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZSOAPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZBSoapException
{
public:

    ZBSoapException( int            mExceptionCode,
                     const char*    mExceptionInfo            = NULL,
                     const char*    mExceptionRaisedInFile    = NULL,
                     int            mExceptionRaisedAtLine    = -1 );

    int getCode() const;
    int getFileLine() const;

    const CString getMessage() const;
    const CString getInfo() const;
    const CString getFileName() const;

private:

    void dump();    
    CString getMessageByCode( int mcode );

    int        m_code;
    int        m_fileline;

    CString    m_message;
    CString    m_info;
    CString    m_filename;
};

#endif