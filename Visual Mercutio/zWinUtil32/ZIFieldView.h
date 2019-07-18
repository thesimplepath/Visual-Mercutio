#if !defined(AFX_ZIFieldView_H__E7935803_E783_11D3_96D3_0000B45D7C6F__INCLUDED_)
#define AFX_ZIFieldView_H__E7935803_E783_11D3_96D3_0000B45D7C6F__INCLUDED_

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
#include "zBaseLib\ZITreeView.h"
#include "fieldtreei.h"

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
// ZIFieldView view

class AFX_EXT_CLASS ZIFieldView : public ZITreeView
{
protected:
    DECLARE_DYNCREATE(ZIFieldView)

public:
    ZIFieldView();           // protected constructor used by dynamic creation
    virtual ~ZIFieldView();

// Operations
public:
    void Initialize( ZDDocument* pDoc, ZBFieldRepository* pFieldRepository = NULL );

protected:
    virtual int            GetIndexOfNoDropImage() const;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIFieldView)
    protected:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    virtual void PostNcDestroy();
    //}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(ZIFieldView)
    afx_msg LRESULT OnInitializeFieldRepository( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnDocumentHasBeenSelected( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnReloadFieldList( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnFieldAdded( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnFieldRemoved( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnFieldRenamed( WPARAM wParam, LPARAM lParam );
    afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ZDDocument*            m_pDoc;
    ZBFieldRepository*    m_pFieldRepository;
    ZIFieldTree            m_FieldTree;

};


inline int ZIFieldView::GetIndexOfNoDropImage() const
{
    return 20;
}


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIFieldView_H__E7935803_E783_11D3_96D3_0000B45D7C6F__INCLUDED_)
