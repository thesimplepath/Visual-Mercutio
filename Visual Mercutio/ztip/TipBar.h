// TipBar.h : header file
//  

#if !defined(TIPBAR_H_INCLUDED)
#define TIPBAR_H_INCLUDED

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


#include "zWeb\ZWebBrowser.h"



#ifdef _ZTIPEXPORT
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
// ZTipOfDayBar class

class AFX_EXT_CLASS ZTipOfDayBar : public SECControlBar
{
// Construction
public:
	ZTipOfDayBar();

// Attributes
public:

// Operations
public:
	void SetURL(UINT nResID, HINSTANCE hInstance = NULL);
	void SetURL(LPCTSTR lpszURL, BOOL bRes, HINSTANCE hInstance = NULL);
	void SetURL(UINT nResID, LPCTSTR lpszParam, HINSTANCE hInstance = NULL);
	void SetURL(LPCTSTR lpszURL, BOOL bRes, LPCTSTR lpszParam, HINSTANCE hInstance = NULL);
	void Navigate();
	void Navigate(UINT nResID, HINSTANCE hInstance = NULL);
	void Navigate(LPCTSTR lpszURL, BOOL bRes, HINSTANCE hInstance = NULL);
	void Navigate(UINT nResID, LPCTSTR lpszParam, HINSTANCE hInstance = NULL);
	void Navigate(LPCTSTR lpszURL, BOOL bRes, LPCTSTR lpszParam, HINSTANCE hInstance = NULL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZTipOfDayBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ZTipOfDayBar();

// Generated message map functions
protected:
	//{{AFX_MSG(ZTipOfDayBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	ZWebBrowser*	m_pBrowser;

};

/////////////////////////////////////////////////////////////////////////////

inline void ZTipOfDayBar::SetURL(UINT nResID, HINSTANCE hInstance) 
{ 
	if (m_pBrowser)
		m_pBrowser->SetURL( nResID, hInstance ); 
}

inline void ZTipOfDayBar::SetURL(LPCTSTR lpszURL, BOOL bRes, HINSTANCE hInstance)
{
	if (m_pBrowser)
		m_pBrowser->SetURL( lpszURL, bRes, hInstance ); 
}

inline void ZTipOfDayBar::SetURL(UINT nResID, LPCTSTR lpszParam, HINSTANCE hInstance /*= NULL*/)
{
	if (m_pBrowser)
		m_pBrowser->SetURL(nResID, lpszParam, hInstance);
}
inline void ZTipOfDayBar::SetURL(LPCTSTR lpszURL, BOOL bRes, LPCTSTR lpszParam, HINSTANCE hInstance /*= NULL*/)
{
	if (m_pBrowser)
		m_pBrowser->SetURL(lpszURL, bRes, lpszParam, hInstance);
}

inline void ZTipOfDayBar::Navigate()
{
	if (m_pBrowser)
		m_pBrowser->Navigate();
}

inline void ZTipOfDayBar::Navigate(UINT nResID, HINSTANCE hInstance /*= NULL*/)
{
	if (m_pBrowser)
		m_pBrowser->Navigate(nResID, hInstance);
}

inline void ZTipOfDayBar::Navigate(LPCTSTR lpszURL, BOOL bRes, HINSTANCE hInstance /*= NULL*/)
{
	if (m_pBrowser)
		m_pBrowser->Navigate(lpszURL, bRes, hInstance);
}

inline void ZTipOfDayBar::Navigate(UINT nResID, LPCTSTR lpszParam, HINSTANCE hInstance /*= NULL*/)
{
	if (m_pBrowser)
		m_pBrowser->Navigate(nResID, lpszParam, hInstance);
}

inline void ZTipOfDayBar::Navigate(LPCTSTR lpszURL, BOOL bRes, LPCTSTR lpszParam, HINSTANCE hInstance /*= NULL*/)
{
	if (m_pBrowser)
		m_pBrowser->Navigate(lpszURL, bRes, lpszParam, hInstance);
}


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(TIPBAR_H_INCLUDED)

