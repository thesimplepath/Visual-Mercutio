#if !defined(AFX_ZIHtmlView_H__674DDCC6_D6E4_11D3_96BF_0000B45D7C6F__INCLUDED_)
#define AFX_ZIHtmlView_H__674DDCC6_D6E4_11D3_96BF_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZIHtmlView.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


/////////////////////////////////////////////////////////////////////////////
// ZIHtmlView html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>


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

class AFX_EXT_CLASS ZIHtmlView : public CHtmlView
{
public:
    ZIHtmlView();           // protected constructor used by dynamic creation
    DECLARE_DYNCREATE(ZIHtmlView)

// html Data
public:
    //{{AFX_DATA(ZIHtmlView)
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

// Attributes
public:

// Operations
public:
    void Navigate(UINT nResID, DWORD dwFlags = 0, LPCTSTR lpszTargetFrameName = NULL);
    void Navigate(LPCTSTR lpszURL, BOOL bRes, DWORD dwFlags = 0, LPCTSTR lpszTargetFrameName = NULL);
    const CString GetCurrentURL() const { return m_strURL; };

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIHtmlView)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    virtual ~ZIHtmlView();

    void    ResourceToURL(LPCTSTR lpszURL);

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
    //{{AFX_MSG(ZIHtmlView)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    CString m_strURL;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIHtmlView_H__674DDCC6_D6E4_11D3_96BF_0000B45D7C6F__INCLUDED_)
