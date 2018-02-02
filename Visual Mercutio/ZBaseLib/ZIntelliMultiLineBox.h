#if !defined(AFX__ZCInternalMultiLineEdit_H__85036D1D_E0AF_4249_9C4A_469775DEE39B__INCLUDED_)
#define AFX__ZCInternalMultiLineEdit_H__85036D1D_E0AF_4249_9C4A_469775DEE39B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// _ZCInternalMultiLineEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZIntelliMultiLineBox;
class ZCMultiLineEdit;


/////////////////////////////////////////////////////////////////////////////
// _ZCInternalMultiLineEdit window

class _ZCInternalMultiLineEdit : public CEdit
{
// Construction
public:
	_ZCInternalMultiLineEdit(ZCMultiLineEdit* pEditCtrl = NULL, ZIntelliMultiLineBox* pParent = NULL);


// Operations
public:
	void	SetEditControl( ZCMultiLineEdit* pEditCtrl, ZIntelliMultiLineBox* pParent = NULL );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(_ZCInternalMultiLineEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~_ZCInternalMultiLineEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(_ZCInternalMultiLineEdit)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void	TranslateSelectionToEditControl();

private:
	ZCMultiLineEdit*		m_pEditCtrl;
	ZIntelliMultiLineBox*	m_pParent;
};

/////////////////////////////////////////////////////////////////////////////


class ZIntelliMultiLineBox : public CWnd
{
  DECLARE_DYNAMIC(ZIntelliMultiLineBox);
// Construction
public:
	ZIntelliMultiLineBox(ZCMultiLineEdit* pEditCtrl = NULL, CSize* pSize = NULL);
	BOOL 	Create( ZCMultiLineEdit* pEditCtrl, CSize* pSize = NULL );      // create the intelli multi line edit window
    
	void	SetEditControl( ZCMultiLineEdit* pEditCtrl, CSize* pSize = NULL );

	// CEdit wrapper functions
	BOOL CanUndo() const
	{
		return m_Edit.CanUndo();
	};
	int GetLineCount() const
	{
		return m_Edit.GetLineCount();
	};
	BOOL GetModify() const
	{
		return m_Edit.GetModify();
	};
	void SetModify(BOOL bModified = TRUE)
	{
		m_Edit.SetModify(bModified);
	};
	void GetRect(LPRECT lpRect) const
	{
		m_Edit.GetRect(lpRect);
	};
	DWORD GetSel() const
	{
		return m_Edit.GetSel();
	};
	void GetSel(int& nStartChar, int& nEndChar) const
	{
		m_Edit.GetSel(nStartChar,nEndChar);
	};
	HLOCAL GetHandle() const
	{
		return m_Edit.GetHandle();
	};
	void SetHandle(HLOCAL hBuffer)
	{
		m_Edit.SetHandle(hBuffer);
	};
#if (WINVER >= 0x400)
	void SetMargins(UINT nLeft, UINT nRight)
	{
		m_Edit.SetMargins(nLeft,nRight);
	};
	DWORD GetMargins() const
	{
		return m_Edit.GetMargins();
	};
	void SetLimitText(UINT nMax)
	{
		m_Edit.SetLimitText(nMax);
	};
	UINT GetLimitText() const
	{
		return m_Edit.GetLimitText();
	};
	CPoint PosFromChar(UINT nChar) const
	{
		return m_Edit.PosFromChar(nChar);
	};
	int CharFromPos(CPoint pt) const
	{
		return m_Edit.CharFromPos(pt);
	};
#endif

	int GetLine(int nIndex, LPTSTR lpszBuffer) const
	{
		return m_Edit.GetLine(nIndex, lpszBuffer);
	};
	int GetLine(int nIndex, LPTSTR lpszBuffer, int nMaxLength) const
	{
		return m_Edit.GetLine(nIndex, lpszBuffer, nMaxLength);
	};
	void EmptyUndoBuffer()
	{
		m_Edit.EmptyUndoBuffer();
	};
	BOOL FmtLines(BOOL bAddEOL)
	{
		return m_Edit.FmtLines(bAddEOL);
	};

	void LimitText(int nChars = 0)
	{
		m_Edit.LimitText(nChars);
	};
	int LineFromChar(int nIndex = -1) const
	{
		return m_Edit.LineFromChar(nIndex);
	};
	int LineIndex(int nLine = -1) const
	{
		return m_Edit.LineIndex(nLine);
	};
	int LineLength(int nLine = -1) const
	{
		return m_Edit.LineLength(nLine);
	};
	void LineScroll(int nLines, int nChars = 0)
	{
		m_Edit.LineScroll(nLines,nChars);
	};
	void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo = FALSE)
	{
		m_Edit.ReplaceSel(lpszNewText,bCanUndo);
	};
	void SetPasswordChar(TCHAR ch)
	{
		m_Edit.SetPasswordChar(ch);
	};
	void SetRect(LPCRECT lpRect)
	{
		m_Edit.SetRect(lpRect);
	};
	void SetRectNP(LPCRECT lpRect)
	{
		m_Edit.SetRectNP(lpRect);
	};
	void SetSel(DWORD dwSelection, BOOL bNoScroll = FALSE)
	{
		m_Edit.SetSel(dwSelection,bNoScroll);
	};
	void SetSel(int nStartChar, int nEndChar, BOOL bNoScroll = FALSE)
	{
		m_Edit.SetSel(nStartChar,nEndChar,bNoScroll);
	};
	BOOL SetTabStops(int nTabStops, LPINT rgTabStops)
	{
		return m_Edit.SetTabStops(nTabStops, rgTabStops);
	};
	void SetTabStops()
	{
		m_Edit.SetTabStops();
	};
	BOOL SetTabStops(const int& cxEachStop)    // takes an 'int'
	{
		return m_Edit.SetTabStops(cxEachStop);
	};

	BOOL Undo()
	{
		return m_Edit.Undo();
	};
	void Clear()
	{
		m_Edit.Clear();
	};
	void Copy()
	{
		m_Edit.Copy();
	};
	void Cut()
	{
		m_Edit.Cut();
	};
	void Paste()
	{
		m_Edit.Paste();
	};

	BOOL SetReadOnly(BOOL bReadOnly = TRUE)
	{
		return m_Edit.SetReadOnly(bReadOnly);
	};
	int GetFirstVisibleLine() const
	{
		return m_Edit.GetFirstVisibleLine();
	};
	TCHAR GetPasswordChar() const
	{
		return m_Edit.GetPasswordChar();
	};


// Implementation
public:
	virtual ~ZIntelliMultiLineBox();

// Attributes
private:  
  	static CString near m_strClassName;  // colorselection window class name
protected:
	// Generated message map functions
	//{{AFX_MSG(ZIntelliMultiLineBox)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	UINT GetNextID(CWnd* pWnd) const;

private:
	_ZCInternalMultiLineEdit m_Edit;
	ZCMultiLineEdit* m_pEditCtrl;
	CSize m_Size;
	int	m_MultiLineEditBoxHeight;


};

/////////////////////////////////////////////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__ZCInternalMultiLineEdit_H__85036D1D_E0AF_4249_9C4A_469775DEE39B__INCLUDED_)
