/****************************************************************************
 * ==> PSS_DocumentPageSetupDlg --------------------------------------------*
 ****************************************************************************
 * Description : Provides a document page setup dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DocumentPageSetupDlg.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

 //---------------------------------------------------------------------------
 // Dynamic creation
 //---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_DocumentPageSetupDlg, PSS_WizardDialog)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DocumentPageSetupDlg, PSS_WizardDialog)
    ON_BN_CLICKED(IDC_PORTRAIT, OnBnClickedPortrait)
    ON_BN_CLICKED(IDC_LANDSCAPE, OnBnClickedLandscape)
    ON_BN_CLICKED(IDC_BT_OPENFILE, OnBnClickedBtOpenfile)
    ON_EN_CHANGE(IDC_EDIT_FILENAME, OnEnChangeEditFileName)
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DocumentPageSetupDlg
//---------------------------------------------------------------------------
PSS_DocumentPageSetupDlg::PSS_DocumentPageSetupDlg(CWnd* pParent) :
    PSS_WizardDialog(PSS_DocumentPageSetupDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_PAGESETUP_S,
                     IDS_WZ_PAGESETUP_T),
    m_PaperSize(g_DefaultPaperSize),
    m_StandardSize(g_DefaultStandardSize),
    m_Orientation(g_DefaultOrientation)
{}
//---------------------------------------------------------------------------
PSS_DocumentPageSetupDlg::~PSS_DocumentPageSetupDlg()
{}
//---------------------------------------------------------------------------
CString PSS_DocumentPageSetupDlg::GetBackgroundFileName() const
{
    return m_BgName;
}
//---------------------------------------------------------------------------
CSize PSS_DocumentPageSetupDlg::GetPaperSize() const
{
    return m_PaperSize;
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetupDlg::SetPaperSize(const CSize& paperSize)
{
    m_PaperSize = paperSize;
}
//---------------------------------------------------------------------------
short PSS_DocumentPageSetupDlg::GetStandardSize() const
{
    return m_StandardSize;
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetupDlg::SetStandardSize(short standardSize)
{
    m_StandardSize = standardSize;
}
//---------------------------------------------------------------------------
short PSS_DocumentPageSetupDlg::GetOrientation() const
{
    return m_Orientation;
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetupDlg::SetOrientation(short orientation)
{
    m_Orientation = orientation;
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetupDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentPageSetupDlg::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    UpdateDatas();

    CWnd* m_pFileNameTxtBox = GetDlgItem(IDC_EDIT_FILENAME);
    m_pFileNameTxtBox->SetWindowText(_T(""));

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetupDlg::OnBnClickedPortrait()
{
    if (m_Orientation == DMORIENT_LANDSCAPE)
    {
        CSize m_TmpPaperSize;

        m_TmpPaperSize = m_PaperSize;
        m_PaperSize.cx = m_TmpPaperSize.cy;
        m_PaperSize.cy = m_TmpPaperSize.cx;
    }

    m_Orientation = DMORIENT_PORTRAIT;

    CheckDlgButton(IDC_PORTRAIT,  TRUE);
    CheckDlgButton(IDC_LANDSCAPE, FALSE);
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetupDlg::OnBnClickedLandscape()
{
    if (m_Orientation == DMORIENT_PORTRAIT)
    {
        CSize m_TmpPaperSize;

        m_TmpPaperSize = m_PaperSize;
        m_PaperSize.cx = m_TmpPaperSize.cy;
        m_PaperSize.cy = m_TmpPaperSize.cx;
    }

    m_Orientation = DMORIENT_LANDSCAPE;

    CheckDlgButton(IDC_PORTRAIT,  FALSE);
    CheckDlgButton(IDC_LANDSCAPE, TRUE);
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetupDlg::OnBnClickedBtOpenfile()
{
    const CString filterJpg = _T("Images au format jpeg (*.jpg)|*.jpg|");
    const CString filterGif = _T("Images au format gif (*.gif)|*.gif|");
    const CString filterPcx = _T("Images au format pcx (*.pcx)|*.pcx|");
    const CString filterDib = _T("Images au format dib (*.dib)|*.dib|");
    const CString filterTga = _T("Images au format tga (*.tga)|*.tga|");
    const CString filterTif = _T("Images au format tif (*.tif)|*.tif|");

    const CString filters = filterJpg + filterGif + filterPcx + filterDib + filterTga + filterTif + _T("|");

    CFileDialog m_FileDialog(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, filters);

    if (m_FileDialog.DoModal() == IDOK)
    {
        m_BgName = m_FileDialog.GetPathName();

        CWnd* m_pFileNameTxtBox = GetDlgItem(IDC_EDIT_FILENAME);
        m_pFileNameTxtBox->SetWindowText(m_BgName);
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetupDlg::OnEnChangeEditFileName()
{
    CWnd* m_pFileNameTxtBox = GetDlgItem(IDC_EDIT_FILENAME);
    m_pFileNameTxtBox->GetWindowText(m_BgName);
}
//---------------------------------------------------------------------------
void PSS_DocumentPageSetupDlg::UpdateDatas()
{
    if (m_Orientation == DMORIENT_PORTRAIT)
    {
        CheckDlgButton(IDC_PORTRAIT,  TRUE);
        CheckDlgButton(IDC_LANDSCAPE, FALSE);
    }
    else
    {
        CheckDlgButton(IDC_PORTRAIT,  FALSE);
        CheckDlgButton(IDC_LANDSCAPE, TRUE);
    }
}
//---------------------------------------------------------------------------
