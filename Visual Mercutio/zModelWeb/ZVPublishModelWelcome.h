// ZVPublishModelWelcome.h : header file

#if !defined(AFX_ZVPublishModelWelcome_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
#define AFX_ZVPublishModelWelcome_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\ZWizard.h"
#include "zModelWebRes.h"

// JMR-MODIF - Le 8 août 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelWelcome dialog

class ZVPublishModelWelcome : public ZIWizardDialog
{
// Construction
public:

    // Standard constructor
    ZVPublishModelWelcome( CWnd* pParent = NULL );

    // Dialog Data
    //{{AFX_DATA(ZVPublishModelWelcome)
    enum { IDD = IDD_WZPUBMODEL_WELCOME };
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVPublishModelWelcome)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVPublishModelWelcome)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVPublishModelWelcome_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
