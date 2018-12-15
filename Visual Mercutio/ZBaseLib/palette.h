// palette.h : interface of the ZIPaletteBar class

#if !defined(__PALETTE_H)
#define __PALETTE_H

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#ifndef _WIN32
#include "toolbarx.h"
#endif // Only in 16bit

#define        ID_PALMENU_PROP            WM_USER + 0x200
#define        ID_PALMENU_HIDE            ID_PALMENU_PROP+1


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


class AFX_EXT_CLASS ZIPaletteBar : public CToolBar
{
// Constructor
public:
    ZIPaletteBar();

    void SetColumns(UINT nColumns);
    UINT GetColumns() { return m_nColumns; };
    void SetSizes(SIZE sizeButton, SIZE sizeImage, UINT nColumns = 1);
    BOOL SetButtons(const UINT FAR* lpIDArray, int nIDCount, UINT nColumns = 1);

#ifndef _WIN32
    BOOL Create(CWnd* pOwnerWnd, int x, int y);
#endif


// Attributes
public:

// Operations
public:

// Implementation
public:
    virtual ~ZIPaletteBar();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    UINT    m_nColumns;

protected:
#ifndef _WIN32
    // overridden from CToolBar implementation
    virtual void GetItemRect(int nIndex, LPRECT lpRect) const;
    virtual int HitTest(CPoint point);
    virtual void DoPaint(CDC* pDC);

    void InvertTracker(CPoint point);
    void RecalcLayout(UINT nButtonCount);

protected:
    BOOL    m_bTrackMove;
    CPoint  m_ptMouse, m_ptLast;
    CWnd*   m_pOwnerWnd;
    UINT    m_cxRightBorder;

private:
    CMenu    m_Menu;
#endif // Only in 16bit

    // Generated message map functions
protected:
#ifndef _WIN32
    //{{AFX_MSG(ZIPaletteBar)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg    LONG OnPropriety( UINT, LONG );
    afx_msg    LONG OnHide( UINT, LONG );
    //}}AFX_MSG
#endif // Only in 16bit
    DECLARE_MESSAGE_MAP()
};


#endif // __PALETTE_H


/////////////////////////////////////////////////////////////////////////////
