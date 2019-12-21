// ******************************************************************************************************************
// *                                      Classe ZDLogicalPrestationsDocument                                        *
// ******************************************************************************************************************
// * JMR-MODIF - Le 7 octobre 2005 - Ajout de la classe ZDLogicalPrestationsDocument.                                *
// ******************************************************************************************************************
// * Cette classe représente le document utilisé pour gérer le groupe des prestations.                                *
// ******************************************************************************************************************

#if !defined(AFX_ZDLogicalPrestationsDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_)
#define AFX_ZDLogicalPrestationsDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_

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

#include "PSS_LogicalPrestationsEntity.h"

// BaseDoc
#include "zBaseLib\PSS_BaseDocument.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZDLogicalPrestationsDocument : public PSS_BaseDocument
{
    DECLARE_DYNCREATE( ZDLogicalPrestationsDocument )

public:

    // Inherited feature
    typedef PSS_BaseDocument inherited;

    ZDLogicalPrestationsDocument();
    ~ZDLogicalPrestationsDocument();

// Operations
public:

    bool ReadFromFile    ( const CString fileName );
    bool SaveToFile        ( const CString fileName );

    PSS_LogicalPrestationsEntity& GetPrestationsEnvironment()
    {
        return m_PrestationsEnvironment;
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
        return CDocument::IsModified() || m_PrestationsEnvironment.IsModified();
    }

    virtual void SetModifiedFlag( BOOL bModified = TRUE )
    {
        CDocument::SetModifiedFlag( bModified );
        m_PrestationsEnvironment.SetModifiedFlag( bModified );
    }

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDPrestationsDocument)
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

    //{{AFX_MSG(ZDPrestationsDocument)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    // Unique GUID for this file.
    // Other file using this file can save this GUID
    // to be sure they are using the right file.
    CString                      m_GUID;

    PSS_LogicalPrestationsEntity m_PrestationsEnvironment;
    bool                         m_IsLoaded;
};

#endif
