#if !defined(AFX_ZVSPANWND_H__010C740E_0070_4502_A22E_9697019AB358__INCLUDED_)
#define AFX_ZVSPANWND_H__010C740E_0070_4502_A22E_9697019AB358__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVSpanWnd.h : header file
//

#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZVSpanView; 



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
// ZVSpanWnd window

class AFX_EXT_CLASS ZVSpanWnd : public CWnd
{
    friend class ZVSpanView;
// Construction
public:
	/* Constructs an ZVSpanWnd overview window object.*/
	ZVSpanWnd(ZVSpanView *pPanView = NULL);
	virtual ~ZVSpanWnd();

// Operations
public:
	/* Creates the overview window and specifies its initial position and size.*/
    virtual BOOL Create(CRect rectCreate, CWnd* pParent, UINT nID, LPCTSTR lpszTitle = NULL);

	void AssignPanView(ZVSpanView *pView);

	//@cmember
	/* Implements the overview window’s style settings at creation.*/
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//@Access Operations
	//@cmember
	/* Sets the rectangle representing the overview window.*/
    void SetPanRect(CRect rectNewPan);

	//@cmember
	/* Draws the rectangle representing the overview window.*/
    void DrawPanRect(CDC * pDC);

	void InvalidateOverviewWnd(CRect * rectUpdate  = NULL );

	//@cmember
	/* Updates the overview window when the user scrolls or updates the panning view.*/
    void OnUpdate(CView * pSender, LPARAM lHint, CObject * pHint);

// Implementation
public:
#ifdef _DEBUG
	void Dump(CDumpContext  &dc);
	void AssertValid();
#endif //_DEBUG
    ZVSpanView*  m_pPanView;        //Back pointer to view
    CRect        m_rectLogPan;      //The current viewport
    CSize        m_szLogDrag;       //The size of the rect being dragged
    BOOL         m_bCaptured;       //Is the mosue captured
    HCURSOR      m_hCurrentOverviewCursor; //Keeps the current overview cursor
    HCURSOR      m_hOverviewCursor; //Cursor for dragging the overview rect
	HCURSOR      m_hOverviewOnMoveCursor; //Cursor when on the overview rect
	BOOL		 m_bClipVerified;	//Has the success of ClipOverviewCursor() been verified
	
    //Impementation specific helper functions for overview wnd.
    void ClipOverviewCursor();
    void OverviewDPtoLP(CPoint *);
    
    // Generated message map functions
protected:
    //{{AFX_MSG(SECPanWnd)
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnClose();
	//}}AFX_MSG
    afx_msg void OnPaint();
    
    DECLARE_MESSAGE_MAP();
    

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZVSpanWnd)
	//}}AFX_VIRTUAL

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVSPANWND_H__010C740E_0070_4502_A22E_9697019AB358__INCLUDED_)
