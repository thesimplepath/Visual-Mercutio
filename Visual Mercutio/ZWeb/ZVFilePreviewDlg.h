#if !defined(AFX_ZVFILEPREVIEWDLG_H__5A19BA63_23FC_11D4_972A_0000B45D7C6F__INCLUDED_)
#define AFX_ZVFILEPREVIEWDLG_H__5A19BA63_23FC_11D4_972A_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ZVFilePreviewDlg.h : header file

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "ZWebBrowser.h"
#include "ZWebRes.h"

#ifdef _ZWEBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 26 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

/////////////////////////////////////////////////////////////////////////////
// ZVFilePreviewDlg dialog

class AFX_EXT_CLASS ZVFilePreviewDlg : public CDialog
{
// Construction
public:

    ZVFilePreviewDlg( UINT nResID, CWnd* pParent = NULL );
    ZVFilePreviewDlg( LPCTSTR lpszURL, BOOL bRes, CWnd* pParent = NULL );

    virtual ~ZVFilePreviewDlg();

private:

    // Dialog Data
    //{{AFX_DATA(ZVFilePreviewDlg)
    enum { IDD = IDD_BROWSER_FILEPREVIEW };
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVFilePreviewDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVFilePreviewDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    void SizeControl();

private:

    ZWebBrowser*    m_pBrowser;
    CString            m_strURL;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVFILEPREVIEWDLG_H__5A19BA63_23FC_11D4_972A_0000B45D7C6F__INCLUDED_)