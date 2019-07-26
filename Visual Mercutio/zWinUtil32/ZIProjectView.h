#if !defined(AFX_ZIPROJECTVIEW_H__E7935803_E783_11D3_96D3_0000B45D7C6F__INCLUDED_)
#define AFX_ZIPROJECTVIEW_H__E7935803_E783_11D3_96D3_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_ProjectTree.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIProjectView view

class AFX_EXT_CLASS ZIProjectView : public CTreeView
{
protected:
    ZIProjectView();           // protected constructor used by dynamic creation
    DECLARE_DYNCREATE(ZIProjectView)

// Operations
public:
    void Initialize( BOOL OnlyVisible );

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIProjectView)
    protected:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    //}}AFX_VIRTUAL

// Implementation
protected:
    virtual ~ZIProjectView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(ZIProjectView)
    afx_msg LRESULT OnDocumentHasBeenSelected( WPARAM wParam, LPARAM lParam );
    afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    BOOL            m_OnlyVisible;
    PSS_ProjectTree m_ProjectTree;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIPROJECTVIEW_H__E7935803_E783_11D3_96D3_0000B45D7C6F__INCLUDED_)
