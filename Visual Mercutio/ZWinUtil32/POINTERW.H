// pointerw.h : header file
//
#if !defined(__POINTERW_H)
#define __POINTERW_H



#include "zWinUtil32\ZWinUtil32.h"

#include "Message.h"

#ifndef _WIN32
	extern "C" extern void WINAPI InitZWinUtilDLL();
	extern AFX_EXTENSION_MODULE NEAR extensionZWinUtilDLL;
	#define	AFX_EXT_CLASS
#else // Only in 16bit
	extern AFX_EXTENSION_MODULE extensionZWinUtil32DLL;
#endif // Only in 32bit





/////////////////////////////////////////////////////////////////////////////
// ZIPointerWnd window

class AFX_EXT_CLASS ZIPointerWnd : public CWnd
{
	DECLARE_DYNAMIC(ZIPointerWnd)
// Construction
public:
	ZIPointerWnd();
	void	Create(CWnd *pWndMessage, CRect& Rect, CWnd* pParent);
	void	AssignMessageWnd(CWnd *pWndMessage);
	
// Attributes
private:
	HCURSOR 		m_hcurPointer;
	UINT			m_uID;
	BOOL			m_bStartPointer;
	CWnd*			m_pWndMessage;
// Operations
public:

// Implementation
public:
	virtual ~ZIPointerWnd();

protected:
	// Generated message map functions
	//{{AFX_MSG(ZIPointerWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // __POINTERW_H
