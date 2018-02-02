// ZVPublishModelOptions.h : header file

#if !defined(AFX_ZVPublishModelOptions_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
#define AFX_ZVPublishModelOptions_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\ZWizard.h"
#include "zModelWebRes.h"

#include "zWinUtil32\ZCLanguageCombo.h"

// JMR-MODIF - Le 8 août 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelOptions dialog

// ******************************************************************************************************************
// * JMR-MODIF - Le 4 juillet 2005 - Supprimé l'option de publication HTML en chemin relatif ou absolu. Ajouté		*
// * l'option de publication du rapport Conceptor.																	*
// ******************************************************************************************************************

class ZVPublishModelOptions : public ZIWizardDialog
{
// Construction
public:

	// Standard constructor
	ZVPublishModelOptions( BOOL		Visualize								= TRUE,
						   BOOL		PublishConceptorIsChecked				= TRUE,
						   BOOL		PublishConceptorDetailsIsChecked		= FALSE,
						   BOOL		PublishConceptorDeliverablesIsChecked	= FALSE,
						   BOOL		PublishProcessIsChecked					= TRUE,
						   BOOL		PublishRuleBookIsChecked				= FALSE,
						   Language	InitialLanguage							= UnknownLang,
						   CWnd*	pParent									= NULL );

	BOOL GetVisualize() const
	{
		return m_Visualize;
	}

	Language GetLanguage() const
	{
		return m_Language;
	}

	// JMR-MODIF - Le 5 juillet 2005 - Ajout de la fonction GetPublishConceptor.
	BOOL GetPublishConceptor() const
	{
		return m_PublishConceptorIsChecked;
	}

	// JMR-MODIF - Le 5 août 2005 - Ajout de la fonction GetPublishConceptorDetails.
	BOOL GetPublishConceptorDetails() const
	{
		return m_PublishConceptorDetailsIsChecked;
	}

	// JMR-MODIF - Le 5 août 2005 - Ajout de la fonction GetPublishConceptorDeliverables.
	BOOL GetPublishConceptorDeliverables() const
	{
		return m_PublishConceptorDeliverablesIsChecked;
	}

	// JMR-MODIF - Le 2 mars 2006 - Ajout de la fonction GetPublishProcess.
	BOOL GetPublishProcess() const
	{
		return m_PublishProcessIsChecked;
	}

	// JMR-MODIF - Le 14 janvier 2007 - Ajout de la fonction GetPublishRuleBook.
	BOOL GetPublishRuleBook() const
	{
		return m_PublishRuleBookIsChecked;
	}

private:

	// Dialog Data
	//{{AFX_DATA(ZVPublishModelOptions)
	enum { IDD = IDD_WZPUBMODEL_OPTIONS };
	ZCLanguageCombo	m_cbLanguage;
	BOOL			m_Visualize;
	BOOL			m_PublishConceptorIsChecked;
	BOOL			m_PublishConceptorDetailsIsChecked;
	BOOL			m_PublishConceptorDeliverablesIsChecked;
	BOOL			m_PublishProcessIsChecked;
	BOOL			m_PublishRuleBookIsChecked;
	//}}AFX_DATA

// Implementation
protected:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVPublishModelOptions)
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(ZVPublishModelOptions)
	afx_msg void OnBnClickedPublishConceptor();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	Language m_Language;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVPublishModelOptions_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
