//////////////////////////////////////
// ZBDragEdit.h : header file
//

#if !defined(AFX_ZBDragEdit_H_INCLUDED_)
#define AFX_ZBDragEdit_H_INCLUDED_


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



/////////////////////////////////////////////////////////////////////////////
// ZBDragEdit window
#ifndef __AFXOLE_H__
	#include <afxole.h>
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


class ZBDragEdit;

class AFX_EXT_CLASS ZBEditDropTarget : public COleDropTarget
{
public:
    ZBEditDropTarget()
        {
        m_bBeginDrop=FALSE;
        m_pEditCtl=NULL;
        }
    BOOL        Register(ZBDragEdit* pEdit);
    BOOL        OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
    DROPEFFECT  OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    void        OnDragLeave(CWnd* pWnd);
    DROPEFFECT  OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    DROPEFFECT  OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point);

private:
    BOOL        m_bBeginDrop;
    ZBDragEdit*  m_pEditCtl;
};

class AFX_EXT_CLASS ZBEditDataSource : public COleDataSource
{
};



#define	ZBDragEditBase	CEdit

class AFX_EXT_CLASS ZBDragEdit : public ZBDragEditBase
{
// Construction
public:
	ZBDragEdit();
	virtual ~ZBDragEdit();

// Attributes
public:
    enum {  DE_ENABLE_DRAG=1, 
            DE_ENABLE_DROP=2
    };

// Operations
public:
    BOOL    Init(int nFlags=(DE_ENABLE_DRAG|DE_ENABLE_DROP));

    BOOL    IsInDragging()                  {return m_bInDragging;}
    void    SetDropEqualDrag(BOOL bEqual)   {m_bDropEqualDrag=bEqual;}
    void    SetDropPos(int nLine, int nPos) {m_nDropPtLine=nLine, 
                                             m_nDropPtPos=nPos;}

    BOOL    GetCurRange(int& nLine1, int& nPos1, int& nLine2, int& nPos2);
    BOOL    GetLinePosByCursor(int& nLine, int& nPos);

    BOOL    SetCaretByCursor();
    BOOL    SetCaret(int nLine, int nPos);

	// Deselects all text in the control
	void SetSelNone()		
	{ 
		SetSel(-1, 0); 
	};
	// Selects all text in the control
	void SetSelAll()		
	{ 
		SetSel(0, -1); 
	};

    BOOL    DrawCaretByCursor();

    CPoint  GetPosFromLinePos(int nLine, int nPos)  
                {return PosFromChar(_LinePosToChar(nLine,nPos));}
    //we reimpelmented this function for fixing SDK's bug
    CPoint  PosFromChar(UINT uChar);

    BOOL    IsInSelRange();

    BOOL    EnableDrag()    
                {return (m_nEnableFlags & DE_ENABLE_DRAG) ? TRUE : FALSE;}
    BOOL    EnableDrop()    
                {return (m_nEnableFlags & DE_ENABLE_DROP) ? TRUE : FALSE;}
    

	// Generated message map functions
protected:
	//{{AFX_MSG(ZBDragEdit)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	void DoDelete();
	void NotifyParent(UINT uiCode);

private:
    BOOL    _GetSelText(CString& str);
    void    _CharToLinePos(int nChar, int* pnLine, int* pnPos)
                {
                if (nChar<0) nChar=0;
                *pnLine=LineFromChar(nChar);
                *pnPos=nChar-LineIndex(*pnLine);
                }
    int     _LinePosToChar(int nLine, int nPos) {return LineIndex(nLine)+nPos;}
	void	_ReplaceSelString(LPCTSTR pcszNew, int iStart, int iStop, CString& str) const;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZBDragEdit)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

private:
    static  BOOL    m_bOleInit;

    BOOL            m_bDragInit;

    int             m_nEnableFlags;

    BOOL            m_bInDragging;

    BOOL            m_bDropEqualDrag;
    int             m_nDropPtLine;
    int             m_nDropPtPos;

	ZBEditDropTarget	m_dropTarget;
	ZBEditDataSource	m_dropSource;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZBDragEdit_H_INCLUDED_)
