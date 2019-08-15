/****************************************************************************
 * ==> PSS_FolderInfoDialog ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a folder info dialog box                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FolderInfoDialog.h"

// processsoft
#include "zBaseLib\MsgBox.h"
#include "zRes32\Zres.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FolderInfoDialog, ZIDialog)
    //{{AFX_MSG_MAP(PSS_FolderInfoDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FolderInfoDialog
//---------------------------------------------------------------------------
PSS_FolderInfoDialog::PSS_FolderInfoDialog(PSS_FolderStamp* pFolderStamp, BOOL readOnly, CWnd* pParent) :
    ZIDialog(PSS_FolderInfoDialog::IDD, TRUE, pParent),
    m_pFolderStamp(pFolderStamp),
    m_ReadOnly(readOnly)
{
    if (m_pFolderStamp)
    {
        m_FolderName        = m_pFolderStamp->GetFolderName();
        m_FolderDescription = m_pFolderStamp->GetFolderDescription();
    }
}
//---------------------------------------------------------------------------
void PSS_FolderInfoDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_FolderInfoDialog)
    DDX_Text(pDX, IDC_FOLDERNAME,        m_FolderName);
    DDX_Text(pDX, IDC_FOLDERDESCRIPTION, m_FolderDescription);
    #ifdef _WIN32
        DDX_Control(pDX, IDC_LIST_INFORMATION, m_ListInformation);
    #endif
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_FolderInfoDialog::OnInitDialog()
{
    ZIDialog::OnInitDialog();
    
    if (m_ReadOnly)
    {
        if (GetDlgItem(IDC_FOLDERNAME))
            GetDlgItem(IDC_FOLDERNAME)->EnableWindow(FALSE);

        if (GetDlgItem(IDC_FOLDERDESCRIPTION))
            GetDlgItem(IDC_FOLDERDESCRIPTION)->EnableWindow(FALSE);

        if (GetDlgItem(IDCANCEL))
            GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

        if (GetDlgItem(IDOK))
        {
            CString title;
            title.LoadString(IDS_CLOSE_TEXT);
            GetDlgItem(IDOK)->SetWindowText(title);
        }
    }

    #ifdef _WIN32
        m_ListInformation.Initialize(m_pFolderStamp, FALSE, !m_ReadOnly);
    #endif

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_FolderInfoDialog::OnOK()
{
    UpdateData();

    if (!m_ReadOnly && m_pFolderStamp)
    {
        m_pFolderStamp->SetFolderName(m_FolderName);
        m_pFolderStamp->SetFolderDescription(m_FolderDescription);
    }

    ZIDialog::OnOK();
}
//---------------------------------------------------------------------------
