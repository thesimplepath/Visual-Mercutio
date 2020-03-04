/****************************************************************************
 * ==> PSS_RiskNewFileDlg --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a create a new risk file dialog box               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RiskNewFileDlg.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\PSS_TextFile.h"
#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_RiskNewFileDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_RiskNewFileDlg)
    ON_BN_CLICKED(IDC_DIRECTORY_SELECT, OnBnClickedDirectorySelect)
    ON_EN_CHANGE(IDC_FILENAME, OnEnChangeFileName)
    ON_EN_CHANGE(IDC_DIRECTORY, OnEnChangeDirectory)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_RiskNewFileDlg
//---------------------------------------------------------------------------
PSS_RiskNewFileDlg::PSS_RiskNewFileDlg(const CString& extension, CWnd* pParent) :
    CDialog(PSS_RiskNewFileDlg::IDD, pParent),
    m_Extension(extension)
{}
//---------------------------------------------------------------------------
PSS_RiskNewFileDlg::~PSS_RiskNewFileDlg()
{}
//---------------------------------------------------------------------------
CString PSS_RiskNewFileDlg::GetDirectory()
{
    return m_Directory;
}
//---------------------------------------------------------------------------
CString PSS_RiskNewFileDlg::GetFileName()
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_RiskNewFileDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_RiskNewFileDlg)
    DDX_Text   (pDX, IDC_FILENAME,  m_FileName);
    DDX_Text   (pDX, IDC_DIRECTORY, m_Directory);
    DDX_Control(pDX, IDC_FILENAME,  m_FileName_Ctrl);
    DDX_Control(pDX, IDC_DIRECTORY, m_Directory_Ctrl);
    DDX_Control(pDX, IDOK,          m_OK_Ctrl);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_RiskNewFileDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    PSS_Application* pApplication = PSS_Application::Instance();

    if (pApplication)
    {
        PSS_MainForm* pMainForm = pApplication->GetMainForm();

        if (pMainForm)
        {
            m_Directory = pMainForm->GetApplicationDir() + g_RiskDirectory;
            m_Directory_Ctrl.SetWindowText(m_Directory);
        }
    }

    m_OK_Ctrl.EnableWindow(FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_RiskNewFileDlg::OnBnClickedDirectorySelect()
{
    CSHFileInfo fileInfo;
    fileInfo.m_strTitle = _T(m_Directory);

    if (fileInfo.BrowseForFolder(GetParent()) == IDOK)
    {
        m_Directory = fileInfo.m_strPath;
        m_Directory_Ctrl.SetWindowText(m_Directory);
    }
}
//---------------------------------------------------------------------------
void PSS_RiskNewFileDlg::OnEnChangeFileName()
{
    m_FileName_Ctrl.GetWindowText(m_FileName);
    CheckUserEntry();
}
//---------------------------------------------------------------------------
void PSS_RiskNewFileDlg::OnEnChangeDirectory()
{
    m_Directory_Ctrl.GetWindowText(m_Directory);
    CheckUserEntry();
}
//---------------------------------------------------------------------------
void PSS_RiskNewFileDlg::OnBnClickedOk()
{
    PSS_File file;

    if (!file.Exist(m_Directory))
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_BAD_DIRECTORY, MB_OK);
        return;
    }

    if (file.Exist(m_Directory + _T("\\") + m_FileName + m_Extension))
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_RISK_FILE_ALREADY_EXIST, MB_OK);
        return;
    }

    OnOK();
}
//---------------------------------------------------------------------------
void PSS_RiskNewFileDlg::CheckUserEntry()
{
    if (!m_FileName.IsEmpty() && !m_Directory.IsEmpty())
        m_OK_Ctrl.EnableWindow(TRUE);
    else
        m_OK_Ctrl.EnableWindow(FALSE);
}
//---------------------------------------------------------------------------
