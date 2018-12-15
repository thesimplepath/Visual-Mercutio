#if !defined(AFX_ZDWORKSPACEWIZARDTEMPLATEDOCUMENT_H__DE01D157_C8C5_4B20_BF67_C3ED34217103__INCLUDED_)
#define AFX_ZDWORKSPACEWIZARDTEMPLATEDOCUMENT_H__DE01D157_C8C5_4B20_BF67_C3ED34217103__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZDWorkspaceWizardTemplateDocument.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZBWorkspaceWizardTemplateMg.h"


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
// ZDWorkspaceWizardTemplateDocument document

class AFX_EXT_CLASS ZDWorkspaceWizardTemplateDocument : public CDocument
{
    DECLARE_DYNCREATE(ZDWorkspaceWizardTemplateDocument)
public:
    ZDWorkspaceWizardTemplateDocument();           // protected constructor used by dynamic creation
    virtual ~ZDWorkspaceWizardTemplateDocument();

// Operations
public:
    bool ReadFromFile( const CString Filename );
    bool SaveToFile( const CString Filename );

    ZBWorkspaceWizardTemplateMg& GetWorkspaceTemplates()
    {
        return m_WorkspaceTemplates;
    };
    bool IsLoaded() const
    {
        return m_IsLoaded;
    };

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDWorkspaceWizardTemplateDocument)
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
    //{{AFX_MSG(ZDWorkspaceWizardTemplateDocument)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ZBWorkspaceWizardTemplateMg    m_WorkspaceTemplates;
    bool                        m_IsLoaded;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDWORKSPACEWIZARDTEMPLATEDOCUMENT_H__DE01D157_C8C5_4B20_BF67_C3ED34217103__INCLUDED_)
