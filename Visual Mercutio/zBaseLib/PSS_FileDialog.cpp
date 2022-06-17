/****************************************************************************
 * ==> PSS_FileDialog ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file dialog                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FileDialog.h"

// processsoft
#include <AfxDlgs.h>
#include <Dlgs.h>

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FileDialog, CFileDialog)
    //{{AFX_MSG_MAP(PSS_FileDialog)
    // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FileDialog
//---------------------------------------------------------------------------
PSS_FileDialog::PSS_FileDialog(const CString& title,
                               const CString& filters,
                               int            filterCount,
                               const CString& initialDir,
                               const CString& defExtension,
                               BOOL           openStyleBox) :
    CFileDialog(openStyleBox, defExtension),
    m_Title(title),
    m_InitialDir(initialDir),
    m_Filters(filters),
    m_FilterCount(filterCount)
{}
//---------------------------------------------------------------------------
PSS_FileDialog::PSS_FileDialog(UINT           titleID,
                               const CString& filters,
                               int            filterCount,
                               const CString& initialDir,
                               const CString& defExtension,
                               BOOL           openStyleBox) :
    CFileDialog(openStyleBox, defExtension),
    m_InitialDir(initialDir),
    m_Filters(filters),
    m_FilterCount(filterCount)
{
    if (titleID)
        m_Title.LoadString(titleID);
}
//---------------------------------------------------------------------------
PSS_FileDialog::PSS_FileDialog(const PSS_FileDialog& other) :
    CFileDialog(TRUE)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_FileDialog::~PSS_FileDialog()
{}
//---------------------------------------------------------------------------
const PSS_FileDialog& PSS_FileDialog::operator = (const PSS_FileDialog& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_FileDialog::DoModal()
{
    CWnd* pWnd = ::AfxGetMainWnd();

    if (!pWnd)
        return IDABORT;

    m_ofn.nMaxCustFilter += m_FilterCount;
    m_ofn.lpstrFilter     = m_Filters;
    m_ofn.hwndOwner       = pWnd->GetSafeHwnd();
    m_ofn.lpstrTitle      = m_Title;

    // set the initial directory
    m_ofn.lpstrInitialDir = m_InitialDir;

    BOOL result;

    try
    {
        m_ofn.lpstrFile = m_FileName.GetBuffer(_MAX_PATH);
        result          = CFileDialog::DoModal();
    }
    catch (...)
    {
        m_FileName.ReleaseBuffer();
        throw;
    }

    m_FileName.ReleaseBuffer();
    return result;
}
//---------------------------------------------------------------------------
#ifdef _WIN32
    BOOL PSS_FileDialog::OnFileNameOK()
    {
        m_PathName = GetFolderPath();
        return CFileDialog::OnFileNameOK();
    }
#endif
//---------------------------------------------------------------------------
