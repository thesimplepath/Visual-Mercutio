/****************************************************************************
 * ==> PSS_SingleInstanceApplication ---------------------------------------*
 ****************************************************************************
 * Description : Provides a single instance application structure           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SingleInstanceApplicationH
#define PSS_SingleInstanceApplicationH

#if _MSC_VER > 1000
    #pragma once
#endif

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zMediator\PSS_MainForm.h"

// windows
#include "ddeml.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Single instance application structure
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SingleInstanceApplication : public PSS_MainForm
{
    public:
        PSS_SingleInstanceApplication();

        /**
        * DDE callback
        *@param type - data type
        *@param format - data format
        *@param hConv - conversation handle
        *@param hszTopic - topic handle
        *@param hszItem - item handle
        *@param hData - DDE data handle
        *@param data1 - custom user data 1
        *@param data2 - custom user data 2
        *@return DDE data handle, depends on the transaction class, on error return NULL
        */
        HDDEDATA AppDdeCallback(WORD     type,
                                WORD     format,
                                HCONV    hConv,
                                HSZ      hszTopic,
                                HSZ      hszItem,
                                HDDEDATA hData,
                                DWORD    data1,
                                DWORD    data2);

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SingleInstanceApplication)
        virtual BOOL InitInstance();
        virtual int ExitInstance();
        //}}AFX_VIRTUAL

        //{{AFX_MSG(PSS_SingleInstanceApplication)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    protected:
        CString m_CppServerName;
        CString m_CppTopicName;

    private:
        HSZ   m_hSzCppServer;
        HSZ   m_hSzCppTopic;
        HCONV m_hConvCppServer;
        DWORD m_IdInst;
        DWORD m_DDEResult;
        bool  m_IsRun;
};

/**
* DDE callback
*@param type - data type
*@param format - data format
*@param hConv - conversation handle
*@param hszTopic - topic handle
*@param hszItem - item handle
*@param hData - DDE data handle
*@param data1 - custom user data 1
*@param data2 - custom user data 2
*@return DDE data handle, depends on the transaction class, on error return NULL
*/
HDDEDATA CALLBACK DdeCallback(WORD     type,
                              WORD     format,
                              HCONV    hConv,
                              HSZ      hszTopic,
                              HSZ      hszItem,
                              HDDEDATA hData,
                              DWORD    data1,
                              DWORD    data2);

#endif
