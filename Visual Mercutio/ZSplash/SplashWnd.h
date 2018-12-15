#if !defined(AFX_SPLASHWND_H__DA398130_9E64_11D3_987E_00C04FB4D0D7__INCLUDED_)
#define AFX_SPLASHWND_H__DA398130_9E64_11D3_987E_00C04FB4D0D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplashWnd.h : header file
//



#include "zBaseLib\ZBitmap.h"



/////////////////////////////////////////////////////////////////////////////
// ZSplashWnd window

class ZSplashWnd : public CWnd
{
// Construction
public:
    ZSplashWnd();

// Operations
public:
    bool CreateSplashWindow( bool IncludeProgress, CWnd* pParentWnd );
    bool Display();
    bool EndDisplay();
    void Process();
    void AssignParentWindow(CWnd* pParentWnd);

    void SetText(const CString value);
    void SetText(UINT nResID);
    void SetProgress(size_t value);
    bool LoadBitmapImage( LPCTSTR szFilename );
    bool LoadBitmapImage( UINT nResID );

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZSplashWnd)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~ZSplashWnd();

    // Generated message map functions
protected:
    //{{AFX_MSG(ZSplashWnd)
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()



private:
    bool            m_IncludeProgress;
private:
    CRect            m_ProgressRect;
    CRect            m_TextRect;
    ZBitmap            m_Bitmap;
    CProgressCtrl    m_ProgressControl;
    CString            m_Text;
    CFont            m_Font;
    COLORREF        m_clrFont;
    COLORREF        m_clrBackground;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASHWND_H__DA398130_9E64_11D3_987E_00C04FB4D0D7__INCLUDED_)
