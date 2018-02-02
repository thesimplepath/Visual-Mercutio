// ZVPublishModelAttributes.h : header file

#if !defined(AFX_ZVPublishModelAttributes_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
#define AFX_ZVPublishModelAttributes_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\ZWizard.h"
#include "zModelWebRes.h"

// ZCSymbolAttributesTreeCtrl
#include "zModel\ZCSymbolAttributesTreeCtrl.h"

// JMR-MODIF - Le 2 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBPropertyAttributes;

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelAttributes dialog

class ZVPublishModelAttributes : public ZIWizardDialog
{
// Construction
public:

	// Standard constructor
	ZVPublishModelAttributes( ZBPropertyAttributes*	pPropAttributes	= NULL,
							  ZBPropertySet*		pPropSet		= NULL,
							  CWnd*					pParent			= NULL );

private:

	// Dialog Data
	//{{AFX_DATA(ZVPublishModelAttributes)
	enum { IDD = IDD_WZPUBMODEL_ATTRIBUTE };
	ZCSymbolAttributesTreeCtrl	m_Attributes;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVPublishModelAttributes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVPublishModelAttributes)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	ZBPropertyAttributes*	m_pPropAttributes;
	ZBPropertySet*			m_pPropSet;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVPublishModelAttributes_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
