/****************************************************************************
 * ==> PSS_ImportProcessDlg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an import process dialog                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ImportProcessDlg.h"

// processsoft
#include "zBaseLib\PSS_FileDialog.h"
#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ImportProcessDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_ImportProcessDlg)
    ON_BN_CLICKED(IDC_SELECT, OnSelect)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ImportProcessDlg
//---------------------------------------------------------------------------
PSS_ImportProcessDlg::PSS_ImportProcessDlg(const CString& fileName, BOOL doImport, CWnd* pParent) :
    PSS_Dialog(PSS_ImportProcessDlg::IDD, TRUE, pParent),
    m_InitialFileName(fileName),
    m_Import(doImport)
{
    m_FileName = m_InitialFileName;
}
//---------------------------------------------------------------------------
PSS_ImportProcessDlg::~PSS_ImportProcessDlg()
{}
//---------------------------------------------------------------------------
void PSS_ImportProcessDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ImportProcessDlg)
    DDX_Text(pDX, IDC_FILETOIMPORT, m_FileName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ImportProcessDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    if (!m_Import)
    {
        CString title;
        title.LoadString(IDS_EXPORTPROCESS_TITLE);
        SetWindowText(title);

        if (GetDlgItem(IDOK))
        {
            title.LoadString(IDS_EXPORTPROCESS_BUTTON);
            GetDlgItem(IDOK)->SetWindowText(title);
        }
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ImportProcessDlg::OnSelect()
{
    CString title;

    if (m_Import)
        title.LoadString(IDS_IMPORTFILE_CHOOSETITLE);
    else
        title.LoadString(IDS_EXPORTPROCESSFILE_CHOOSETITLE);

    // set the "*.txt" files filter
    CString filter;
    VERIFY(filter.LoadString(AFX_IDS_ALLFILTER));
    filter += (char)'\0';
    filter += "*.*";
    filter += (char)'\0';

    PSS_FileDialog fileDialog(title, filter, 1);

    if (fileDialog.DoModal() == IDOK)
    {
        m_FileName = fileDialog.GetFileName();
        UpdateData(FALSE);
    }
}
//---------------------------------------------------------------------------
void PSS_ImportProcessDlg::OnOK()
{
    UpdateData();

    if (m_FileName.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_FILENAMEMISSING, MB_OK);
        return;
    }

    PSS_Dialog::OnOK();
}
//---------------------------------------------------------------------------
