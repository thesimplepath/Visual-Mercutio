// ZBWorkspaceWizardTemplateMg.h: interface for the ZBWorkspaceWizardTemplateMg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBWORKSPACEWIZARDTEMPLATEMG_H__105D2B6D_42D1_473E_B4F3_E0CE45610DE8__INCLUDED_)
#define AFX_ZBWORKSPACEWIZARDTEMPLATEMG_H__105D2B6D_42D1_473E_B4F3_E0CE45610DE8__INCLUDED_

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

// Forward class declaration
class ZBWorkspaceWizardTemplateItem;

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

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBWorkspaceWizardTemplateItemSet | An array of ZBWorkspaceWizardTemplateItem pointers.
//@iex typedef CCArray_T<ZBWorkspaceWizardTemplateItem*,ZBWorkspaceWizardTemplateItem*> ZBWorkspaceWizardTemplateItemSet;
typedef CCArray_T<ZBWorkspaceWizardTemplateItem*, ZBWorkspaceWizardTemplateItem*> ZBWorkspaceWizardTemplateItemSet;

//@type ZBWorkspaceWizardTemplateItemIterator | An iterator for ZBWorkspaceWizardTemplateItemSet collections.
//@iex typedef Iterator_T<ZBWorkspaceWizardTemplateItem*> ZBWorkspaceWizardTemplateItemIterator;
typedef Iterator_T<ZBWorkspaceWizardTemplateItem*> ZBWorkspaceWizardTemplateItemIterator;

class AFX_EXT_CLASS ZBWorkspaceWizardTemplateMg : public CObject  
{
	DECLARE_SERIAL( ZBWorkspaceWizardTemplateMg )

public:
	ZBWorkspaceWizardTemplateMg();
	virtual ~ZBWorkspaceWizardTemplateMg();

	bool AddTemplateItem( ZBWorkspaceWizardTemplateItem* Item )
	{
		m_Set.Add( Item );
		return true;
	};

	ZBWorkspaceWizardTemplateItem* GetTemplateItemAt( size_t Index )
	{
		return ( (int)Index < m_Set.GetSize() ) ? m_Set.GetAt( Index ) : NULL;
	};

	size_t GetItemCount() const
	{
		return m_Set.GetSize();
	};

	ZBWorkspaceWizardTemplateItemSet* GetTemplateItemSet()
	{
		return &m_Set;
	};

	// Serialization mechanism
	virtual void Serialize( CArchive& ar );		// overridden for document i/o

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

private:
	ZBWorkspaceWizardTemplateItemSet m_Set;
};

#endif // !defined(AFX_ZBWORKSPACEWIZARDTEMPLATEMG_H__105D2B6D_42D1_473E_B4F3_E0CE45610DE8__INCLUDED_)