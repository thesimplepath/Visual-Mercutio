#if !defined(AFX_ZDLogicalSystemDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_)
#define AFX_ZDLogicalSystemDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_

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

#include "ZBLogicalSystemEntity.h"

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

// JMR-MODIF - Le 14 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZDLogicalSystemDocument document

class AFX_EXT_CLASS ZDLogicalSystemDocument : public ZDBaseDocument
{
    DECLARE_DYNCREATE( ZDLogicalSystemDocument )

public:

    // Inherited feature
    typedef ZDBaseDocument inherited;

    // Public constructor since not used by dynamic creation
    ZDLogicalSystemDocument();
    virtual ~ZDLogicalSystemDocument();

// Operations
public:

    bool ReadFromFile( const CString Filename );
    bool SaveToFile( const CString Filename );

    ZBLogicalSystemEntity& GetLogicalSystemEnvironment()
    {
        return m_LogicalSystemEnvironment;
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
        return CDocument::IsModified() || m_LogicalSystemEnvironment.IsModified();
    };

    virtual void SetModifiedFlag( BOOL bModified = TRUE )
    {
        CDocument::SetModifiedFlag( bModified );
        m_LogicalSystemEnvironment.SetModifiedFlag( bModified );
    };

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDLogicalSystemDocument)
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

    //{{AFX_MSG(ZDLogicalSystemDocument)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    // Unique GUID for this file.
    // Other file using this file can save this GUID
    // to be sure they are using the right file.
    CString                    m_GUID;

    ZBLogicalSystemEntity    m_LogicalSystemEnvironment;
    bool                    m_IsLoaded;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDLogicalSystemDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_)
