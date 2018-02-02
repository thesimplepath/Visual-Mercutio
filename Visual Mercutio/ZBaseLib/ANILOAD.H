// aniload.h : header file

#if !defined(__ANILOAD_H)
#define __ANILOAD_H

#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

extern AFX_EXTENSION_MODULE ZBaseLibDLL;

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 31 décembre 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIStatusBar view

class AFX_EXT_CLASS ZIStatusBar : public SECStatusBar
{
	DECLARE_DYNCREATE( ZIStatusBar )

public:

	// Protected constructor used by dynamic creation
	ZIStatusBar();

	virtual ~ZIStatusBar();

// Operations
public:

	void	SetCurrentPercentage( int iPerc );
	void	BeginAniPercentage();
	void	EndAniPercentage();
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );

// Generated message map functions
protected:

	//{{AFX_MSG(ZIStatusBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Implementation
private:

	CFont	m_Font;
	BOOL	m_bIsStarted;
	int		m_iPerc;
	int		m_iImage;
	CRect	m_ItemRect;
	int		m_iBackWidth;
	int		m_iLeftStart;
	int		m_iStep;
	DWORD	m_dwTickCount;
	BOOL	m_SwapLight;
	static	HBITMAP	m_hBtmBack;
	static	HBITMAP	m_hBtmGreenLight;
	static	HBITMAP	m_hBtmRedLight;
	CBrush	m_LtBlueBrush;
	CPen	m_BlackPen;
	CPen	m_WhitePen;
};

#endif  // __ANILOAD_H