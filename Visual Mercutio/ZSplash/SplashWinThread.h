#if !defined(AFX_SPLASHWINTHREAD_H__F55593A0_A1B5_11D3_987E_00C04FB4D0D7__INCLUDED_)
#define AFX_SPLASHWINTHREAD_H__F55593A0_A1B5_11D3_987E_00C04FB4D0D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplashWinThread.h : header file
//

#include "SplashWnd.h"


/////////////////////////////////////////////////////////////////////////////
// ZSplashWinThread thread

class ZSplashWinThread : public CWinThread
{
    DECLARE_DYNCREATE(ZSplashWinThread)
public:
    ZSplashWinThread(size_t MaxTime = 20, bool IncludeProgress = true, CWnd* pParentWnd = NULL);
    ZSplashWinThread(LPCTSTR szFilename, size_t MaxTime = 20, bool IncludeProgress = true, CWnd* pParentWnd = NULL);
    ZSplashWinThread(UINT nResID, size_t MaxTime = 20, bool IncludeProgress = true, CWnd* pParentWnd = NULL);
    virtual ~ZSplashWinThread();
    void SetProgress(size_t value);
    void SetText(const CString value);
    void SetText(UINT nResID);
    void AssignParentWindow(CWnd* pParentWnd);

// Operations
public:
    void KillThread();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZSplashWinThread)
    public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZSplashWinThread)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    virtual int Run( );

    
private:
    void Delete();

private:
    ZSplashWnd        m_SplashWnd;
    HANDLE            m_hEventKill;
    HANDLE            m_hEventDead;
    COleDateTime    m_StartTime;
    size_t            m_MaxTime;
    CString            m_BitmapFile;
    UINT            m_nResID;
    CWnd*            m_pParentWnd;
    bool            m_IncludeProgress;
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASHWINTHREAD_H__F55593A0_A1B5_11D3_987E_00C04FB4D0D7__INCLUDED_)
