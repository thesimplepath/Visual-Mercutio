/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceWizardTemplateItem.h : interface for the ZBWorkspaceWizardTemplateItem class
//
// ProcessSoft Classes
// Copyright (C) 2001 ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// Description:  XXXClass frame window support
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBWORKSPACEWIZARDTEMPLATEITEM_H__81C3034D_3B0C_4B42_A41B_7C69A55E84C0__INCLUDED_)
#define AFX_ZBWORKSPACEWIZARDTEMPLATEITEM_H__81C3034D_3B0C_4B42_A41B_7C69A55E84C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

class AFX_EXT_CLASS ZBWorkspaceWizardTemplateItem : public CObject  
{
	DECLARE_SERIAL(ZBWorkspaceWizardTemplateItem)
public:
	ZBWorkspaceWizardTemplateItem( CString TemplateName = "",
								   CString TemplateDescription = "",
								   CString IconFile = "",
								   int IconIndex = -1 );

	virtual ~ZBWorkspaceWizardTemplateItem();


	CString	GetTemplateName() const
	{
		return m_TemplateName;
	};
	void SetTemplateName( CString value )
	{
		m_TemplateName = value;
	};

	CString GetTemplateDescription() const
	{
		return m_TemplateDescription;
	};
	void SetTemplateDescription( CString value )
	{
		m_TemplateDescription = value;
	};

	CString GetIconFile() const
	{
		return m_IconFile;
	};
	void SetIconFile( CString value )
	{
		m_IconFile = value;
	};

	int		GetIconIndex() const
	{
		return m_IconIndex;
	};
	void SetIconIndex( int	 value )
	{
		m_IconIndex = value;
	};

	HICON	GetIcon() const
	{
		return m_Icon;
	};
	void SetIcon( HICON value )
	{
		m_Icon = value;
	};

	// Serialization mechanism
	virtual void Serialize(CArchive& ar);   // overridden for document i/o

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	void LoadIconFile();

private:
	CString	m_TemplateName;
	CString m_TemplateDescription;
	CString m_IconFile;
	int		m_IconIndex;
	HICON	m_Icon;
};

#endif // !defined(AFX_ZBWORKSPACEWIZARDTEMPLATEITEM_H__81C3034D_3B0C_4B42_A41B_7C69A55E84C0__INCLUDED_)
