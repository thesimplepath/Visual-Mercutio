#if !defined(AFX_ZIUserView_H__1D455413_ED45_11D3_96D8_0000B45D7C6F__INCLUDED_)
#define AFX_ZIUserView_H__1D455413_ED45_11D3_96D8_0000B45D7C6F__INCLUDED_

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
#include "UserTreeI.h"

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
// ZIUserView view

class AFX_EXT_CLASS ZIUserView : public ZITreeView
{
public:
    DECLARE_DYNCREATE(ZIUserView)
    ZIUserView();           
    virtual ~ZIUserView();


// Operations
public:
    void                Initialize (ZUUserManager* pUserManager);
    void                ReInitialize (ZUUserManager* pUserManager);
    void                Refresh();
    ZUser*                GetSelectedUser();
    CString                GetSelectedDepartement();

    virtual    void        OnSelChangedEvent() {};
    virtual    void        OnClickEvent() {};
    virtual    void        OnDblClickEvent() {};
    virtual    void        OnRightClickEvent() {};
    virtual    void        OnRightDblClickEvent() {};

protected:
    virtual int            GetIndexOfNoDropImage() const;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIUserView)
    protected:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    //}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(ZIUserView)
    afx_msg LRESULT OnInitializeUserManager( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnReloadUserManager( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnRefreshUserManager( WPARAM wParam, LPARAM lParam );
    afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRightClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRightDblClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
protected:
      ZIUserTree            m_UserTree;
      ZUUserManager*        m_pUserManager;
};

inline int ZIUserView::GetIndexOfNoDropImage() const
{
    return 4;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIUserView_H__1D455413_ED45_11D3_96D8_0000B45D7C6F__INCLUDED_)
