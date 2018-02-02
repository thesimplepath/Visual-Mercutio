#if !defined(AFX_HOVERBUTTON_H__1155737E_628E_11D2_81B5_0020AFC24C58__INCLUDED_)
#define AFX_HOVERBUTTON_H__1155737E_628E_11D2_81B5_0020AFC24C58__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HoverButton.h : header file
//
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT




#ifdef _ZWINUTIL32EXPORT
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
// ZUHoverButton window
enum BUTTON_STATE{ BUTTON_OFF, BUTTON_ON, BUTTON_OVER, BUTTON_GREYED};

class AFX_EXT_CLASS ZUHoverButton : public CBitmapButton
{
// Construction
public:
	// Constructor: default is to use buttons defined in our resources
	ZUHoverButton();
// Attributes
public:
	// The only way of accessing data from outside this class is to call these 2 functions
	BUTTON_STATE GetButtonState(void) {	return(m_ButtonState);};
	BUTTON_STATE SetButtonState(BUTTON_STATE nState);

private:
	BOOL			m_bMouseTracking;
	BUTTON_STATE	m_ButtonState;
	CBitmap			m_bmpButtonDown;
	CBitmap			m_bmpButtonFocussed;
	CBitmap			m_bmpButtonUp;
	CBitmap			m_bmpButtonDisabled;
	HWND			m_hWndOld;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZUHoverButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL
private:
	// Called by OnMouseMove() when entering/leaving the button
	void OnMouseLeave(void);
	void OnMouseEnter(void);

// Implementation
public:
	virtual ~ZUHoverButton();
	BOOL LoadBitmaps(UINT nBitmapUp, UINT nBitmapDown, UINT nBitmapFocus, UINT nBitmapDisabled);
	BOOL LoadBitmaps(LPCSTR lpszBitmapUp, LPCSTR lpszBitmapDown, LPCSTR lpszBitmapFocus, LPCSTR lpszBitmapDisabled);

	// Generated message map functions
protected:
	//{{AFX_MSG(ZUHoverButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//#undef  AFX_DATA
//#define AFX_DATA

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOVERBUTTON_H__1155737E_628E_11D2_81B5_0020AFC24C58__INCLUDED_)

