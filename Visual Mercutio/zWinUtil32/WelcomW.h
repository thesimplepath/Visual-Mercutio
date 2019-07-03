#if !defined(AFX_WELCOMW_H__798CD2E8_31E3_11D3_95D5_0000B45D7C6F__INCLUDED_)
#define AFX_WELCOMW_H__798CD2E8_31E3_11D3_95D5_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WelcomW.h : header file
//

#include "ZIWelcom.h"

/////////////////////////////////////////////////////////////////////////////
// ZIWelcomeWriter dialog

class AFX_EXT_CLASS ZIWelcomeWriter : public ZIWelcomeDialog
{
// Construction
public:
    ZIWelcomeWriter(ZAApplicationOption* pApplicationOptions, BOOL EnableMoveToGeneral = FALSE, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
#ifndef _WIN32
    enum { IDD = IDD_WELCOME_PROCESS };
    CButton    m_FileOpenProcess;
    CButton    m_StartProcess;
    CButton    m_StartForm;
    CButton    m_FileOpen;
#endif
#ifdef _WIN32
// Dialog Data
    //{{AFX_DATA(ZIWelcomeWriter)
    enum { IDD = IDD_WELCOME_WRITER };
    ZUHoverButton    m_FileOpenProcess;
    ZUHoverButton    m_StartProcess;
    ZUHoverButton    m_StartForm;
    ZUHoverButton    m_FileOpen;
    //}}AFX_DATA
#endif    


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIWelcomeWriter)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZIWelcomeWriter)
    afx_msg void OnWelcomeFileOpen();
    afx_msg void OnWelcomeSartFormulaire();
    afx_msg void OnWelcomeStartProcess();
    afx_msg void OnWelcomeProcessFileOpen();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOMW_H__798CD2E8_31E3_11D3_95D5_0000B45D7C6F__INCLUDED_)
