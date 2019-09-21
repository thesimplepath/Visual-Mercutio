#if !defined(AFX_ZDHistoricValueDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_)
#define AFX_ZDHistoricValueDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZDHistoricValueDocument.h : header file
//

// ZBHistoricValueManager
#include "PSS_HistoricValueManager.h"


/////////////////////////////////////////////////////////////////////////////
// ZDHistoricValueDocument document

class ZDHistoricValueDocument : public CDocument
{
    DECLARE_DYNCREATE(ZDHistoricValueDocument)
public:
    ZDHistoricValueDocument();           // Public constructor since not used by dynamic creation
    virtual ~ZDHistoricValueDocument();

// Operations
public:
    bool ReadFromFile( const CString Filename );
    bool SaveToFile( const CString Filename );

    PSS_HistoricValueManager& GetHistoricValueManager()
    {
        return m_HistoricValueManager;
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
        return CDocument::IsModified();
    };

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDHistoricValueDocument)
    public:
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    protected:
    virtual BOOL OnNewDocument();
    //}}AFX_VIRTUAL

// Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(ZDHistoricValueDocument)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    PSS_HistoricValueManager m_HistoricValueManager;
    bool                     m_IsLoaded;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDHistoricValueDocument_H__6325FCF2_2A96_4A88_81CB_EEF32C4B5FE9__INCLUDED_)
