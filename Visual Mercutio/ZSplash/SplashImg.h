#if !defined(AFX_SPLASHIMG_H__F4409589_94AB_4962_85CF_A7A09B96FD36__INCLUDED_)
#define AFX_SPLASHIMG_H__F4409589_94AB_4962_85CF_A7A09B96FD36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplashImg.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT




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
// ZSplashImage window

class AFX_EXT_CLASS ZSplashImage
{
// Construction
public:
    ZSplashImage( UINT nResID = 0, const CString Info = "", CWnd* pParentWnd = NULL );
    ZSplashImage( LPCTSTR szFilename, const CString Info = "", CWnd* pParentWnd = NULL );

// Operations
public:
    bool Display(LPCTSTR szFilename, const CString Info = "", CWnd* pParentWnd = NULL);
    bool Display(UINT nResID, const CString Info = "", CWnd* pParentWnd = NULL);
    bool Display(const CString Info = "");


// Implementation
public:
    virtual ~ZSplashImage();

private:
    bool ProcessDisplay();

private:
    CString            m_BitmapFilename;
    UINT            m_BitmapResID;
    CString            m_Info;
    CWnd*            m_pParentWnd;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASHIMG_H__F4409589_94AB_4962_85CF_A7A09B96FD36__INCLUDED_)
