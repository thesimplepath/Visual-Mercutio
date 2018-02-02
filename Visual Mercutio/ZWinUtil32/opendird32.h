// opendird32.h : header file
//

#ifndef _WIN32
	extern "C" extern void WINAPI InitZWinUtilDLL();
	extern AFX_EXTENSION_MODULE NEAR extensionZWinUtilDLL;
	#define	AFX_EXT_CLASS
#else // Only in 16bit
	extern AFX_EXTENSION_MODULE extensionZWinUtil32DLL;
#endif // Only in 32bit


#include "zBaseLib\ZIDialog.h"
#include "DirTreeCtrl.h"

#ifndef _WIN32
	#include "ZWinUtil.h"
#endif
#ifdef _WIN32
	#include "ZWinUtil32.h"
#endif
/////////////////////////////////////////////////////////////////////////////
// ZIOpenDirDlg dialog


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZIOpenDirDlg
{
// Construction
public:
	ZIOpenDirDlg(CString Title = "", CWnd* pParentWnd = NULL);
	ZIOpenDirDlg(UINT nID, CWnd* pParentWnd = NULL);
    CString     GetDirectory();
	CString		ProcessDirectory();

// Data
protected:
	CWnd*		m_pParentWnd;
	CString		m_strDirectory;
	CString		m_Title;

};




inline    CString     ZIOpenDirDlg::GetDirectory( )
{ 
	return m_strDirectory; 
}

#undef AFX_DATA
#define AFX_DATA

