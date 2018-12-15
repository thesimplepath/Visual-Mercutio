#if !defined(AFX_ZIEMPTYVIEW_H__AAF85200_4018_11D3_9843_00C04FB4D0D7__INCLUDED_)
#define AFX_ZIEMPTYVIEW_H__AAF85200_4018_11D3_9843_00C04FB4D0D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZIEmptyView.h : header file
//

#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


/////////////////////////////////////////////////////////////////////////////
// ZIEmptyView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

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


class AFX_EXT_CLASS ZIEmptyView : public CFormView
{
protected:
    ZIEmptyView();           // protected constructor used by dynamic creation
    DECLARE_DYNCREATE(ZIEmptyView)

// Form Data
public:
    //{{AFX_DATA(ZIEmptyView)
    enum { IDD = IDD_EMPTYVIEW };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIEmptyView)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    virtual ~ZIEmptyView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
    //{{AFX_MSG(ZIEmptyView)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIEMPTYVIEW_H__AAF85200_4018_11D3_9843_00C04FB4D0D7__INCLUDED_)
