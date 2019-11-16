#if !defined(AFX_ZDUserEntityDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_)
#define AFX_ZDUserEntityDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_

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

#include "ZBUserGroupEntity.h"

// BaseDoc
#include "zBaseLib\PSS_BaseDocument.h"

#ifdef _ZMODELEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 7 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZDUserEntityDocument document

class AFX_EXT_CLASS ZDUserEntityDocument : public PSS_BaseDocument
{
    DECLARE_DYNCREATE( ZDUserEntityDocument )

public:

    // Inherited feature
    typedef PSS_BaseDocument inherited;

    ZDUserEntityDocument();           // Public constructor since not used by dynamic creation
    virtual ~ZDUserEntityDocument();

// Operations
public:

    bool ReadFromFile    ( const CString fileName );
    bool SaveToFile        ( const CString fileName );

    ZBUserGroupEntity& GetUserGroupEnvironment()
    {
        return m_UserGroupEnvironment;
    };

    bool IsLoaded() const
    {
        return m_IsLoaded;
    };

    void SetLoaded( bool value = true )
    {
        m_IsLoaded = value;
    };

    virtual BOOL IsModified()
    {
        return CDocument::IsModified() || m_UserGroupEnvironment.IsModified();
    };

    virtual void SetModifiedFlag( BOOL bModified = TRUE )
    {
        CDocument::SetModifiedFlag( bModified );
        m_UserGroupEnvironment.SetModifiedFlag( bModified );
    };

    bool IsBeta1Format() const
    {
        return m_Beta1Format;
    };

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDUserEntityDocument)
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

    //{{AFX_MSG(ZDUserEntityDocument)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    ZBUserGroupEntity    m_UserGroupEnvironment;
    bool                m_IsLoaded;

    // Unique GUID for this file.
    // Other file using this file can save this GUID
    // to be sure they are using the right file.
    CString                m_GUID;

    // Used only in for migrating Beta1 format to Beta 2
    // We derive this class from ZDBaseDocument which implement
    // the stamp.
    bool                m_Beta1Format;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDUserEntityDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_)