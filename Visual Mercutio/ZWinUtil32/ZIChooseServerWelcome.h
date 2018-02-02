// ZIChooseServerWelcome.h : header file

#if !defined(AFX_ZICHOOSESERVERWELCOME_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
#define AFX_ZICHOOSESERVERWELCOME_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\ZWizard.h"
#include "DirTreeCtrl.h"

#include "zWinUtil32\ZWinUtil32.h"

// JMR-MODIF - Le 9 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIChooseServerWelcome dialog

class ZIChooseServerWelcome : public ZIWizardDialog
{
// Construction
public:

	// Standard constructor
	ZIChooseServerWelcome( BOOL Local = TRUE, CWnd* pParent = NULL);

	// Dialog Data
	//{{AFX_DATA(ZIChooseServerWelcome)
	enum { IDD = IDD_WZCHOOSESRV_WELCOME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIChooseServerWelcome)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZIChooseServerWelcome)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	BOOL m_Local;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZICHOOSESERVERWELCOME_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
