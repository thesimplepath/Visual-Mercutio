// opendird.cpp : implementation file
//

#include "stdafx.h"
#include "opendird32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIOpenDirDlg 


ZIOpenDirDlg::ZIOpenDirDlg(CString Title, CWnd* pParentWnd)
: m_Title(Title), m_pParentWnd(pParentWnd)
{
}

ZIOpenDirDlg::ZIOpenDirDlg(UINT nID, CWnd* pParentWnd)
: m_pParentWnd(pParentWnd)
{
    if (nID > 0)
        m_Title.LoadString( nID );
}


CString    ZIOpenDirDlg::ProcessDirectory()
{
    CSHFileInfo sfi;
    if (!m_Title.IsEmpty())
        sfi.m_strTitle = _T(m_Title);
    else
        sfi.m_strTitle = _T("...");
    if (sfi.BrowseForFolder( (m_pParentWnd) ? m_pParentWnd : CWnd::GetDesktopWindow() ) == IDOK) 
    {
        m_strDirectory = sfi.m_strPath;
    }
    return m_strDirectory;
}

