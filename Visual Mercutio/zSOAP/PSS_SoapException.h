/****************************************************************************
 * ==> PSS_SoapException ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides the soap exceptions                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef __PSOAPEXCEPTION_HDR_
#define __PSOAPEXCEPTION_HDR_

#include "zSOAPRes.h"

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZSOAPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
*
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapException
{
    public:
        PSS_SoapException(int         exceptionCode,
                          const char* exceptionInfo         =  NULL,
                          const char* exceptionRaisedInFile =  NULL,
                          int         exceptionRaisedAtLine = -1);

        virtual int GetCode() const;
        virtual int GetFileLine() const;

        virtual const CString GetMessage() const;
        virtual const CString GetInfo() const;
        virtual const CString GetFileName() const;

    private:
        int     m_Code;
        int     m_FileLine;
        CString m_Message;
        CString m_Info;
        CString m_FileName;

        void Dump();
        CString getMessageByCode(int mcode);
};

#endif