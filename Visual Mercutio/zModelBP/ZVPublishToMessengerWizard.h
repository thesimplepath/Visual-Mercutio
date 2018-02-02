// ZVPublishToMessengerWizard.h: interface for the ZVPublishToMessengerWizard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVPublishToMessengerWizard_H__5DA4C599_18FB_4411_B32C_FA6E5C4462DB__INCLUDED_)
#define AFX_ZVPublishToMessengerWizard_H__5DA4C599_18FB_4411_B32C_FA6E5C4462DB__INCLUDED_

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

#include "zBaseLib\ZWizard.h"
#include "zModelBP\zModelBPRes.h"
#include "zBaseLib\ZCIntelliEdit.h"

//////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZDProcessGraphModelDoc;
class ZBPublishMessengerModelInformation;
class ZILog;

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 24 janvier 2006 - Ajout des d�corations Unicode _T(), nettoyage du code inutile.

/////////////////////////////////////////////////////////////////////////////
// ZVPublishToMessengerWizard publish the document model to messenger.
class AFX_EXT_CLASS ZVPublishToMessengerWizard
{
public:

	ZVPublishToMessengerWizard( ZDProcessGraphModelDoc* pModelDoc,
								ZILog*					pLog		= NULL,
								const CString			IniFile		= _T( "" ) );

	virtual ~ZVPublishToMessengerWizard();

	int DoModal();

private:

	ZDProcessGraphModelDoc* m_pModelDoc;
	ZILog*					m_pLog;
	CString					m_IniFile;
};

/////////////////////////////////////////////////////////////////////////////
// ZVPublishToMessengerStart dialog.
// JMR-MODIF - Le 21 juin 2006 - Suppression des groupes "inclure mod�le HTML" et "Inclure les attributs",
// ajout de la propri�t� permettant de sp�cifier un alias.

class ZVPublishToMessengerStart : public ZIWizardDialog
{
public:

	// Standard constructor
	ZVPublishToMessengerStart( const CString IniFile = _T( "" ), CWnd* pParent = NULL );

	BOOL GetIncludeModel() const
	{
		return m_IncludeModel;
	};

	BOOL GetIncludeGroups() const
	{
		return m_IncludeGroups;
	};

	BOOL GetIncludeSystems() const
	{
		return m_IncludeSystems;
	};

	// JMR-MODIF - Le 30 mai 2006 - Ajout de la fonction GetIncludePrestations.
	BOOL GetIncludePrestations() const
	{
		return m_IncludePrestations;
	}

	CString GetMessengerAddress() const
	{
		return m_MessengerAddress;
	};

	// JMR-MODIF - Le 21 juin 2006 - Ajout de la fonction GetMessengerAlias.
	CString GetMessengerAlias() const
	{
		return m_MessengerAlias;
	};

private:

	// Dialog Data
	//{{AFX_DATA(ZVPublishToMessengerStart)
	enum { IDD = IDD_WZ_PUBLISHTOMESSENGER_START };
	ZCIntelliEdit	m_MessengerAddressEdit;
	ZCIntelliEdit	m_MessengerAliasEdit;
	BOOL			m_IncludeModel;
	BOOL			m_IncludeGroups;
	BOOL			m_IncludeSystems;
	BOOL			m_IncludePrestations;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVPublishToMessengerStart)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVPublishToMessengerStart)
	virtual BOOL OnInitDialog();
	afx_msg void OnNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	bool LoadStateFromIniFile();
	bool SaveStateToIniFile();

private:

	// JMR-MODIF - Le 21 juin 2006 - Ajout de la variable m_MessengerAlias.
	CString			m_MessengerAlias;

	CString			m_MessengerAddress;
	CString			m_IniFile;
	CStringArray	m_ArrayOfAddress;
};

/////////////////////////////////////////////////////////////////////////////
// ZVPublishToMessengerLogon dialog.
class ZVPublishToMessengerLogon : public ZIWizardDialog
{
public:

	// Standard constructor
	ZVPublishToMessengerLogon( ZBPublishMessengerModelInformation* pInfo, CWnd* pParent = NULL );

	// JMR-MODIF - Le 19 juin 2006 - Ajout de la fonction GetBeginDate.
	CString GetBeginDate()
	{
		return m_Date_Begin;
	}

	// JMR-MODIF - Le 21 juin 2006 - Ajout de la fonction GetEndDate.
	CString GetEndDate()
	{
		return m_Date_End;
	}

private:

	// Dialog Data
	//{{AFX_DATA(ZVPublishToMessengerLogon)
	enum { IDD = IDD_WZ_PUBLISHTOMESSENGER_AUTH };
	CString	m_Password;
	CString	m_Username;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVPublishToMessengerLogon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVPublishToMessengerLogon)
	virtual BOOL OnInitDialog();
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	// JMR-MODIF - Le 19 juin 2006 - Ajout des variables m_Date_Begin et m_Date_End.
	CString								m_Date_Begin;
	CString								m_Date_End;

	ZBPublishMessengerModelInformation*	m_pInfo;
};

#endif // !defined(AFX_ZVPublishToMessengerWizard_H__5DA4C599_18FB_4411_B32C_FA6E5C4462DB__INCLUDED_)