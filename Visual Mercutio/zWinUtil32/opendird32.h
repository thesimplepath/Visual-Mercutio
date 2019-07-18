// opendird32.h : header file
//

// processsoft
#include "zBaseLib\ZIDialog.h"
#include "DirTreeCtrl.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifndef _WIN32
    // 16 bit only
    extern "C" extern void WINAPI InitZWinUtilDLL();
    extern AFX_EXTENSION_MODULE NEAR extensionZWinUtilDLL;
    #define AFX_EXT_CLASS
#else
    // 32 bit only
    extern AFX_EXTENSION_MODULE extensionZWinUtil32DLL;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIOpenDirDlg dialog

class AFX_EXT_CLASS ZIOpenDirDlg
{
// Construction
public:
    ZIOpenDirDlg(CString Title = "", CWnd* pParentWnd = NULL);
    ZIOpenDirDlg(UINT nID, CWnd* pParentWnd = NULL);
    CString     GetDirectory();
    CString        ProcessDirectory();

// Data
protected:
    CWnd*        m_pParentWnd;
    CString        m_strDirectory;
    CString        m_Title;

};




inline    CString     ZIOpenDirDlg::GetDirectory( )
{ 
    return m_strDirectory; 
}

#undef AFX_DATA
#define AFX_DATA

