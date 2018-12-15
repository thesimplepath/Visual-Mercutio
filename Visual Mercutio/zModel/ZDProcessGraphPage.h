// ZDProcessGraphPage.h: interface for the ZDProcessGraphPage class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZDProcessGraphPage_H__3D6120F1_F8CF_4120_8F8E_5A6338BEFC4B__INCLUDED_)
#define AFX_ZDProcessGraphPage_H__3D6120F1_F8CF_4120_8F8E_5A6338BEFC4B__INCLUDED_

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

#include "ProcGraphModelMdl.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 29 septembre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

class AFX_EXT_CLASS ZDProcessGraphPage : public CObject
{
    DECLARE_SERIAL( ZDProcessGraphPage )

public:

    ZDProcessGraphPage( const CString PageName = _T( "" ), ZDProcessGraphModelMdl* pModel = NULL );
    virtual ~ZDProcessGraphPage();

    CString GetPageName() const;
    void SetPageName( CString value );

    ZDProcessGraphModelMdl* GetpModel() const
    {
        return m_pModel;
    }

    void SetpModel( ZDProcessGraphModelMdl* value )
    {
        m_pModel = value;
    }

    //////////////////////////////////////////////////
    // Overrides

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDProcessGraphPage)
    public:
    virtual void Serialize(CArchive& ar);
    //}}AFX_VIRTUAL

    //////////////////////////////////////////////////
    // Implementation

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif // _DEBUG

protected:

    CString                        m_PageName;
    CString                        m_ModelName;
    ZDProcessGraphModelMdl*        m_pModel;
};

inline CString ZDProcessGraphPage::GetPageName() const
{
    return m_PageName;
}

inline void ZDProcessGraphPage::SetPageName( CString value )
{
    m_PageName = value;

    // Bug found when renaming the page name
    // Must be applied to the model name also
    if ( m_pModel )
    {
        m_pModel->SetModelName( m_PageName );
    }
}

#endif // !defined(AFX_ZDProcessGraphPage_H__3D6120F1_F8CF_4120_8F8E_5A6338BEFC4B__INCLUDED_)