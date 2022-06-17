/****************************************************************************
 * ==> PSS_UnitInfoDlg -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an unit info dialog                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UnitInfoDlg.h"

// processsoft
#include "zBaseLib\PSS_Directory.h"

// resources
#include "Resources.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_UnitInfoDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_UnitInfoDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UnitInfoDlg
//---------------------------------------------------------------------------
PSS_UnitInfoDlg::PSS_UnitInfoDlg(const CString& name,
                                 const CString& directory,
                                 bool           showOnly,
                                 CWnd*          pParent) :
    CDialog(PSS_UnitInfoDlg::IDD, pParent),
    m_UnitName(name),
    m_Directory(directory),
    m_ShowOnly(showOnly)
{
    m_UnitDirectory.SetSearchType(PSS_SearchEditButton::IEType::IE_T_Directory, "", m_Directory);

    // if the directory is empty, use the current one
    if (m_Directory.IsEmpty())
        ::GetCurrentDirectory(500, m_Directory.GetBuffer(500));

}
//---------------------------------------------------------------------------
PSS_UnitInfoDlg::~PSS_UnitInfoDlg()
{}
//---------------------------------------------------------------------------
void PSS_UnitInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_UnitInfoDlg)
    DDX_Control(pDX, IDC_UNITDIR,  m_UnitDirectory);
    DDX_Text   (pDX, IDC_UNITNAME, m_UnitName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_UnitInfoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (m_ShowOnly)
    {
        if (GetDlgItem(IDC_UNITNAME))
            GetDlgItem(IDC_UNITNAME)->EnableWindow(FALSE);

        if (GetDlgItem(IDC_UNITDIR))
            GetDlgItem(IDC_UNITDIR)->EnableWindow(FALSE);

        CString text;
        text.LoadString(IDS_CLOSE_TEXT);

        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->SetWindowText(text);

    }
    m_UnitDirectory.SetWindowText(m_Directory);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_UnitInfoDlg::OnOK()
{
    UpdateData(TRUE);

    if (!m_ShowOnly)
    {
        if (m_UnitName.IsEmpty())
            return;

        m_UnitDirectory.GetWindowText(m_Directory);
        m_Directory = PSS_Directory::NormalizeDirectory(m_Directory);
    }

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
