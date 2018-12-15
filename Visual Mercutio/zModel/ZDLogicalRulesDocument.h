// ******************************************************************************************************************
// *                                   Classe ZDLogicalRulesDocument                                                *
// ******************************************************************************************************************
// * JMR-MODIF - Le 15 novembre 2006 - Ajout de la classe ZDLogicalRulesDocument.                                    *
// ******************************************************************************************************************
// * Cette classe représente le document utilisé pour gérer le groupe des règles.                                    *
// ******************************************************************************************************************

#if !defined(AFX_ZDLogicalRulesDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_)
#define AFX_ZDLogicalRulesDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_

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

#include "ZBLogicalRulesEntity.h"

// BaseDoc
#include "zBaseLib\BaseDoc.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZDLogicalRulesDocument : public ZDBaseDocument
{
    DECLARE_DYNCREATE( ZDLogicalRulesDocument )

public:

    // Inherited feature
    typedef ZDBaseDocument inherited;

    ZDLogicalRulesDocument();
    ~ZDLogicalRulesDocument();

// Operations
public:

    bool ReadFromFile    ( const CString Filename );
    bool SaveToFile        ( const CString Filename );

    ZBLogicalRulesEntity& GetRulesEnvironment()
    {
        return m_RulesEnvironment;
    }

    bool IsLoaded() const
    {
        return m_IsLoaded;
    }

    void SetLoaded( bool value = true )
    {
        m_IsLoaded = value;
    }

    virtual BOOL IsModified()
    {
        return CDocument::IsModified() || m_RulesEnvironment.IsModified();
    }

    virtual void SetModifiedFlag( BOOL bModified = TRUE )
    {
        CDocument::SetModifiedFlag( bModified );
        m_RulesEnvironment.SetModifiedFlag( bModified );
    }

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDRulesDocument)
    public:
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    protected:
    virtual BOOL OnNewDocument();
    //}}AFX_VIRTUAL

// Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

// Generated message map functions
protected:

    //{{AFX_MSG(ZDRulesDocument)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    // Unique GUID for this file.
    // Other file using this file can save this GUID
    // to be sure they are using the right file.
    CString                    m_GUID;

    ZBLogicalRulesEntity    m_RulesEnvironment;
    bool                    m_IsLoaded;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDRulesDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_)
