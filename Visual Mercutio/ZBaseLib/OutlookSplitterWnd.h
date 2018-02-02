// OutlookSplitterWnd.h : header file
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(OUTLOOKSPLITTERWND_H_INCLUDED)
#define OUTLOOKSPLITTERWND_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



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
// ZIOutlookSplitterWnd class

class AFX_EXT_CLASS ZIOutlookSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(ZIOutlookSplitterWnd)

// Construction
public:
	ZIOutlookSplitterWnd();

// Attributes
public:
	COLORREF m_clrBtnHLit;
	COLORREF m_clrBtnShad;
	COLORREF m_clrBtnFace;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZIOutlookSplitterWnd)
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ZIOutlookSplitterWnd();

// Generated message map functions
protected:
	//{{AFX_MSG(ZIOutlookSplitterWnd)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(OUTLOOKSPLITTERWND_H_INCLUDED)

