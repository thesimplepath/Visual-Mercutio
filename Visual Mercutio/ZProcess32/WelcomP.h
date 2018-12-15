#if !defined(AFX_WELCOMP_H__798CD2E7_31E3_11D3_95D5_0000B45D7C6F__INCLUDED_)
#define AFX_WELCOMP_H__798CD2E7_31E3_11D3_95D5_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zWinUtil32\ZIWelcom.h"
#include "Resource.h"

// JMR-MODIF - Le 17 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIWelcomeProcess dialog

class ZIWelcomeProcess : public ZIWelcomeDialog
{
// Construction
public:

    // standard constructor
    ZIWelcomeProcess( ZAApplicationOption* pApplicationOptions, BOOL EnableMoveToGeneral = FALSE, CWnd* pParent = NULL );

// Dialog Data
#ifndef _WIN32
    enum { IDD = IDD_WELCOME_PROCESS };
    CButton    m_OpenModel;
    CButton    m_OpenProject;
    CButton    m_CreateNewModel;
    CButton    m_CreateNewProject;
#endif

#ifdef _WIN32
// Dialog Data
    //{{AFX_DATA(ZIWelcomeProcess)
    enum { IDD = IDD_WELCOME_PROCESS };
    ZUHoverButton    m_OpenModel;
    ZUHoverButton    m_OpenProject;
    ZUHoverButton    m_CreateNewModel;
    ZUHoverButton    m_CreateNewProject;
    //}}AFX_DATA
#endif    

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIWelcomeProcess)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZIWelcomeProcess)
    afx_msg void OnWelcomeCreateNewModel();
    afx_msg void OnWelcomeCreateNewProject();
    afx_msg void OnWelcomeOpenModel();
    afx_msg void OnWelcomeOpenProject();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOMP_H__798CD2E7_31E3_11D3_95D5_0000B45D7C6F__INCLUDED_)