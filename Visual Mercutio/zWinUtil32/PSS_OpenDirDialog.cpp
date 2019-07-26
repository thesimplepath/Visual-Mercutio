/****************************************************************************
 * ==> PSS_OpenDirDialog ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an open directory dialog box                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_OpenDirDialog.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_OpenDirDialog
//---------------------------------------------------------------------------
PSS_OpenDirDialog::PSS_OpenDirDialog(const CString& title, CWnd* pParentWnd) :
    m_Title(title), 
    m_pParentWnd(pParentWnd)
{}
//---------------------------------------------------------------------------
PSS_OpenDirDialog::PSS_OpenDirDialog(UINT id, CWnd* pParentWnd) :
    m_pParentWnd(pParentWnd)
{
    if (id > 0)
        m_Title.LoadString(id);
}
//---------------------------------------------------------------------------
CString PSS_OpenDirDialog::ProcessDirectory()
{
    CSHFileInfo fileInfo;

    if (!m_Title.IsEmpty())
        fileInfo.m_strTitle = _T(m_Title);
    else
        fileInfo.m_strTitle = _T("...");

    if (fileInfo.BrowseForFolder(m_pParentWnd ? m_pParentWnd : CWnd::GetDesktopWindow()) == IDOK)
        m_Directory = fileInfo.m_strPath;

    return m_Directory;
}
//---------------------------------------------------------------------------
