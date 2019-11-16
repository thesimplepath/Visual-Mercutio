// **************************************************************************************************************
// *                                             Classe ZVRiskNewFileDlg                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 12 juillet 2007 - Ajout de la classe ZVRiskNewFileDlg.                                        *
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de créer un nouveau fichier pour les éléments des menus des risques.    *
// **************************************************************************************************************

#if !defined(AFX_ZVRISKNEWFILEDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
#define AFX_ZVRISKNEWFILEDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zModelBPRes.h"
#include "afxwin.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVRiskNewFileDlg dialog

class AFX_EXT_CLASS ZVRiskNewFileDlg : public CDialog
{
// Construction / Destruction
public:

    ZVRiskNewFileDlg( CString Extension, CWnd* pParent = NULL );

public:

    CString GetDirectory();
    CString GetFileName();

private:

    void CheckUserEntry();

private:

    // Dialog Data
    //{{AFX_DATA(ZVRiskNewFileDlg)
    enum { IDD = IDD_NEW_RISK_FILE };
    CString m_FileName;
    CString m_Directory;
    CEdit m_FileName_Ctrl;
    CEdit m_Directory_Ctrl;
    CButton m_OK_Ctrl;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVRiskNewFileDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVRiskNewFileDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedDirectorySelect();
    afx_msg void OnEnChangeFileName();
    afx_msg void OnEnChangeDirectory();
    afx_msg void OnBnClickedOk();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    CString m_Extension;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVRISKNEWFILEDLG_H__F8225CF5_FC88_4006_829D_3079998B03A7__INCLUDED_)
