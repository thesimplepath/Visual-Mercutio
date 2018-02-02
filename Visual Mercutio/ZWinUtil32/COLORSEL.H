// colorsel.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


/////////////////////////////////////////////////////////////////////////////
// ZIColorSelection window
const		size_t	m_SizeSquare = 12;
const		size_t	m_NbSquare = 4;
const		size_t	m_SizeBorder = 3;
const		size_t	m_NbColor = 24;

const		int		ErrorSelection = -2;

#ifndef TBX_FONT_SIZE
#define TBX_FONT_SIZE -8
#endif

#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


class AFX_EXT_CLASS ZIColorSelection : public CWnd
{
  DECLARE_DYNAMIC(ZIColorSelection);
// Construction
public:
	ZIColorSelection( COLORREF	col = defCOLOR_BLACK );
	BOOL 	Create();      // create the color window
    void	ChooseColor();
    BOOL	ColorHasChanged() const { return m_Col != m_OldCol; };
	COLORREF	GetColor() const { return m_Col; };
    
// Attributes
public:

// Operations
private:
	void 	DrawColor( CDC& dc, int x, int y, COLORREF col, BOOL bHighLight = FALSE );
	int 	FindColor( CPoint point, CRect& rect );
	int 	FindColorRect( CRect& rect );
	void 	DisplayHighlight( CDC& dc, CRect& rect, BOOL bDisplay );

// Implementation
public:
	virtual ~ZIColorSelection();

// Attributes
private:  
  	static CString near m_strClassName;  // colorselection window class name
	static CFont   near m_fntFont;       // colorselection window font
	COLORREF			m_Col;
	COLORREF			m_OldCol;
	BOOL				m_bChoosed;
	size_t				m_CurrentX;
	size_t				m_CurrentY;
	static COLORREF		m_ColorTable[24];
	CPen	m_BlackPen;
	CPen	m_WhitePen;
	CPen	m_GrayPen;
protected:
	// Generated message map functions
	//{{AFX_MSG(ZIColorSelection)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
