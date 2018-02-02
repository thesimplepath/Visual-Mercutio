/****************************************************************************************************************
 *										  Classe ZVDynamicAttributesCreation									*
 ****************************************************************************************************************
 * Cette classe, intégrant deux sous-classes (ZVDynamicAttributesCreationS1 et ZVDynamicAttributesCreationS2),	*
 * permet à l'utilisateur de créer un nouvel attribut dynamique, en suivant les instructions données par les	*
 * boîtes de dialogues contenues dans chacune des classes ZVDynamicAttributesCreationSx.						*
 ****************************************************************************************************************/

#if !defined(AFX_ZVDYNAMICATTRIBUTESCREATION_H__7CD0522A_A41A_456A_A5A9_52FB2F9B6BA1__INCLUDED_)
#define AFX_ZVDYNAMICATTRIBUTESCREATION_H__7CD0522A_A41A_456A_A5A9_52FB2F9B6BA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zBaseLib\ZWizard.h"
#include "zModel\zModelRes.h"

#include "zProperty\ZBProperty.h"

// **************************************************************************************************************
// *											 Forward class declaration										*
// **************************************************************************************************************
class ZDProcessGraphModelDoc;

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// **************************************************************************************************************
// *										 Classe ZVDynamicAttributesCreation									*
// **************************************************************************************************************
class ZVDynamicAttributesCreation  
{
public:

	ZVDynamicAttributesCreation( ZDProcessGraphModelDoc* pModelDoc, bool SymbolSelected );
	virtual ~ZVDynamicAttributesCreation();

	CString	GetCategoryName() const
	{
		return m_CategoryName;
	};

	CString	GetAttributeName() const
	{
		return m_AttributeName;
	};

	CString	GetAttributeDescription() const
	{
		return m_AttributeDescription;
	};

	ZBProperty::PropertyType GetPropertyType() const
	{
		return m_PropertyType;
	};

	int GetVisibility() const
	{
		return m_Visibility;
	};

	int		DoModal();

private:

	ZDProcessGraphModelDoc*	 m_pModelDoc;

	CString					 m_CategoryName;
	CString					 m_AttributeDescription;
	CString					 m_AttributeName;

	ZBProperty::PropertyType m_PropertyType;

	int						 m_Visibility;

	bool					 m_SymbolSelected;
};

// **************************************************************************************************************
// *									  ZVDynamicAttributesCreationS1 dialog									*
// **************************************************************************************************************
class ZVDynamicAttributesCreationS1 : public ZIWizardDialog
{
// Construction
public:

	ZVDynamicAttributesCreationS1(ZDProcessGraphModelDoc* pModelDoc, CWnd* pParent = NULL);   // standard constructor

	CString	GetCategoryName() const
	{
		return m_CategoryName;
	};

private:

	// Dialog Data
	//{{AFX_DATA(ZVDynamicAttributesCreationS1)
	enum { IDD = IDD_WZ_DYNAMICATTR_S1 };
	CListBox	m_CategoryList;
	CString	m_CategoryName;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVDynamicAttributesCreationS1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVDynamicAttributesCreationS1)
	virtual void OnOK();
	afx_msg void OnNext();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeCategoryName();
	afx_msg void OnSelchangeCategoryList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	bool CheckData();

private:

	bool					m_InternalNameChange;

	ZDProcessGraphModelDoc*	m_pModelDoc;

	CStringArray			m_StaticAttribArray;
	CStringArray			m_DynamicAttribArray;
};

// **************************************************************************************************************
// *									 ZVDynamicAttributesCreationS2 dialog									*
// **************************************************************************************************************
class ZVDynamicAttributesCreationS2 : public ZIWizardDialog
{
// Construction
public:

	ZVDynamicAttributesCreationS2( ZDProcessGraphModelDoc*	pModelDoc,
								   const CString			Category,
								   bool						SymbolSelected,
								   CWnd*					pParent			= NULL );   // standard constructor

	CString	GetAttributeDescription() const
	{
		return m_AttributeDescription;
	};

	CString	GetAttributeName() const
	{
		return m_AttributeName;
	};

	ZBProperty::PropertyType GetPropertyType() const
	{
		return m_PropertyType;
	};

	int GetVisibility() const
	{
		return m_Visibility;
	};

private:

	// Dialog Data
	//{{AFX_DATA(ZVDynamicAttributesCreationS2)
	enum { IDD = IDD_WZ_DYNAMICATTR_S2 };
	CComboBox	m_AttributeVisibility;
	CComboBox	m_AttributeType;
	CString	m_AttributeDescription;
	CString	m_AttributeName;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVDynamicAttributesCreationS2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZVDynamicAttributesCreationS2)
	virtual void OnOK();
	afx_msg void OnNext();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	bool CheckData();

private:

	ZDProcessGraphModelDoc*  m_pModelDoc;

	CString					 m_Category;

	ZBProperty::PropertyType m_PropertyType;

	int						 m_Visibility;

	bool					 m_SymbolSelected;
};

#endif // !defined(AFX_ZVDYNAMICATTRIBUTESCREATION_H__7CD0522A_A41A_456A_A5A9_52FB2F9B6BA1__INCLUDED_)