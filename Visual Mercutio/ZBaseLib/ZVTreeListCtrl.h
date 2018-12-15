#if !defined(_ZVTREELISTCTRL_H__)
#define _ZVTREELISTCTRL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVTreeListCtrl.h : header file
//

#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZIListCtrl.h"

#include <vector>

using namespace std;



#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


/////////////////////////////////////////////////////////////////////////////
// ZVTreeListCtrl window


class _TreeListInfo
{
public:
    int                m_nLevel;
    int                m_nImage;
    vector<CString>    m_lstCols;
    bool            m_bCollapsed;
    int                m_nItem;
    LPARAM            m_pParam;
};

class AFX_EXT_CLASS ZVTreeListCtrl: public ZIListCtrl
{
// Construction
public:
    ZVTreeListCtrl();
    virtual    ~ZVTreeListCtrl();

// Operations
public:
    BOOL            Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
    int                AddItem(LPCTSTR lpszItem, int nImage, int nLevel, LPARAM pParam = NULL);
    BOOL            SetItemText( int nItem, int nSubItem, LPCTSTR lpszText );
    LPARAM            GetParam( int nItem );
    BOOL            DeleteAllItems( BOOL DeleteImageList = FALSE );
                    
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVTreeListCtrl)
    protected:
    virtual void    PreSubclassWindow();
    //}}AFX_VIRTUAL


    // Generated message map functions
protected:
    //{{AFX_MSG(ZVTreeListCtrl)
    afx_msg void    OnClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void    OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

protected:
    int                InsertItem(int nItem, int nPosArray, _TreeListInfo& info);
    void            Collapse(int nPos, int nItem);
    int                Expand(int nItem, bool bRecursive, int& nCounterInsert);
    
protected:
    CImageList                m_ilState;
    vector<_TreeListInfo>    m_TreeCtrl;
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_ZVTREELISTCTRL_H__)
