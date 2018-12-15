// ZCFormTemplateTree.h : header file

#if !defined(AFX_ZCFormTemplateTree_H__1D455413_ED45_11D3_96D8_0000B45D7C6F__INCLUDED_)
#define AFX_ZCFormTemplateTree_H__1D455413_ED45_11D3_96D8_0000B45D7C6F__INCLUDED_

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

// ZCTemplateTreeCtrl
#include "TmplTree.h"

#ifdef _ZWINUTIL32EXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 14 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZCFormTemplateTree view

class AFX_EXT_CLASS ZCFormTemplateTree : public ZCTemplateTreeCtrl
{
public:

    DECLARE_DYNCREATE( ZCFormTemplateTree )

    ZCFormTemplateTree();
    virtual ~ZCFormTemplateTree();

// Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCFormTemplateTree)
    protected:
    //}}AFX_VIRTUAL

// Implementation
protected:

// Generated message map functions
protected:

    //{{AFX_MSG(ZCFormTemplateTree)
    afx_msg LRESULT OnReloadTemplateManager( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnInitializeTemplateManager( WPARAM wParam, LPARAM lParam );
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZCFormTemplateTree_H__1D455413_ED45_11D3_96D8_0000B45D7C6F__INCLUDED_)
