// MskEdit.h : implementation file
//

#ifndef __ZMaskEdit_h__
#define __ZMaskEdit_h__

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


class ZMaskEditChar
{
public:    
    ZMaskEditChar() { m_bStaticChar = false; }
    ZMaskEditChar(CString strChars)
    {
        m_strValids = strChars;
        m_bStaticChar = false;
    }
    ZMaskEditChar(CString strChars, bool bStaticChar)
    {
        m_strValids = strChars;
        m_bStaticChar = bStaticChar;
    }
    
    CString m_strValids;
    CString m_strData;
    bool    m_bStaticChar;
};

#define  MAX_CHARS  256


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


class AFX_EXT_CLASS ZMaskEdit : public CEdit
{
public:
    ZMaskEdit();
    virtual ~ZMaskEdit();

    bool    Init(CString strMask, CString strInitialData = "");
    CString GetFormatedBuffer(CString strMask, CString strInitialData = "");

    bool    SetPromptChar(CString strPromptChar);

    void    SetData(const CString& data);
    CString GetData();

    //{{AFX_VIRTUAL(ZMaskEdit)
    protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

protected:
    bool            m_bInit;
    CString         m_strPrompt;
    ZMaskEditChar*     m_Char[MAX_CHARS];
    int             m_iNumChars;
    int             m_iCurrentChar;
    bool            m_bShiftDown;

    bool    Parse(const CString& strMask);
    bool    SetValidChars(const CString& strMask, bool OnWindow = true);
    CString GetRange(CString szLow, CString szHigh);
    CString FormatedBuffer(const CString& data);
    //CString GetText(bool bDataOnly = false);
    //CString GetData() { return GetText(true); }
    int     FindNextChar(int iStartPos, bool bStatic, bool bForward);

    //{{AFX_MSG(ZMaskEdit)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
    DECLARE_DYNCREATE(ZMaskEdit)
};

AFX_EXT_API void AFXAPI DDX_ZMaskEdit(CDataExchange* pDX, int nIDC, ZMaskEdit& rControl, CString& data);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
