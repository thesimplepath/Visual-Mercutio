// SingleInstanceApp.h : main header file for the ZPUBLISHER application

#if !defined(ZASINGLEINSTANCEAPPLICATION_H__4DAE1EA2_2F04_11D3_9832_00C04FB4D0D7__INCLUDED_)
#define ZASINGLEINSTANCEAPPLICATION_H__4DAE1EA2_2F04_11D3_9832_00C04FB4D0D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ddeml.h"    // DDE definition

// JMR-MODIF - Le 31 décembre 2006 - Ajout de l'en-tête zMediatorZAApp.h
#include "zMediator\zMediatorZAApp.h"

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 31 décembre 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZASingleInstanceApplication:

class AFX_EXT_CLASS ZASingleInstanceApplication : public zMediatorZAApp
{
public:

    ZASingleInstanceApplication();

public:

    HDDEDATA AppDdeCallback( WORD, WORD, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD );

// Overrides
public:

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZASingleInstanceApplication)
    public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    //}}AFX_VIRTUAL

// Implementation
public:

    //{{AFX_MSG(ZASingleInstanceApplication)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:

    CString m_CppServerName;
    CString m_CppTopicName;

private:

    bool    isRun;
    DWORD    idInst;
    HSZ        hszCppServer;
    HSZ        hszCppTopic;
    HCONV    hconvCppServer;
    DWORD    dderesult;
};

HDDEDATA CALLBACK DdeCallback( WORD, WORD, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD );

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(ZASINGLEINSTANCEAPPLICATION_H__4DAE1EA2_2F04_11D3_9832_00C04FB4D0D7__INCLUDED_)
