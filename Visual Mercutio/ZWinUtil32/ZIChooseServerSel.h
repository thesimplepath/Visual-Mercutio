// ZIChooseServerSel.h : header file

#if !defined(AFX_ZICHOOSESERVERSEL_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
#define AFX_ZICHOOSESERVERSEL_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\ZWizard.h"
#include "DirTreeCtrl.h"

#include "zWinUtil32\ZWinUtil32.h"

// JMR-MODIF - Le 9 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIChooseServerSelect dialog

class ZIChooseServerSelect : public ZIWizardDialog
{
// Construction
public:

    // Standard constructor
    ZIChooseServerSelect( BOOL Local = TRUE, CWnd* pParent = NULL );

    CString GetDirectory() const
    {
        return m_Directory;
    };

private:

    // Dialog Data
    //{{AFX_DATA(ZIChooseServerSelect)
    enum { IDD = IDD_WZCHOOSESRV_SEL };
    ZIDirTreeCtrl    m_DirTreeCtrl;
    CString    m_Directory;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIChooseServerSelect)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZIChooseServerSelect)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnOK();
    afx_msg void OnChangeServerChoosed();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    void CheckControlStates();
    void ReflectChangedDirectory();

private:

    BOOL m_Local;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZICHOOSESERVERSEL_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
