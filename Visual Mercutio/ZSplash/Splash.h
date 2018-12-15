#if !defined(AFX_SPLASH_H__DA398130_9E64_11D3_987E_00C04FB4D0D7__INCLUDED_)
#define AFX_SPLASH_H__DA398130_9E64_11D3_987E_00C04FB4D0D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Splash.h : header file
//


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



#include "SplashWinThread.h"


#ifdef _ZSPLASHEXPORT
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
// ZSplash class

class AFX_EXT_CLASS ZSplash
{
// Construction
public:
    ZSplash();

// Operations
public:
    bool Display( LPCTSTR szFilename, size_t MaxTime = 20, bool IncludeProgress = true, CWnd* pParentWnd = NULL );
    bool Display( UINT nResID, size_t MaxTime = 20, bool IncludeProgress = true, CWnd* pParentWnd = NULL );
    bool EndDisplay();
    void SetProgress(size_t value);
    void SetText(const CString value);
    void SetText(UINT nResID);
    void AssignParentWindow(CWnd* pParentWnd);

// Implementation
public:
    virtual ~ZSplash();



private:
    ZSplashWinThread*    m_pThread;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASH_H__DA398130_9E64_11D3_987E_00C04FB4D0D7__INCLUDED_)
