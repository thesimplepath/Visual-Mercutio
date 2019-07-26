/****************************************************************************
 * ==> PSS_ProcessTakeOwnershipActionsDialog -------------------------------*
 ****************************************************************************
 * Description : Provides a process take ownership actions dialog box       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessTakeOwnershipActionsDialog.h"

// processsoft
#include "zBaseLib\File.h"
#include "zBaseLib\ZAGlobal.h"
#include "ZVFormFilePreviewDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessTakeOwnershipActionsDialog, ZIDialog)
    //{{AFX_MSG_MAP(PSS_ProcessTakeOwnershipActionsDialog)
    ON_BN_CLICKED(IDC_VISUALIZE, OnViewCommand)
    ON_BN_CLICKED(IDC_CANCELCOMMAND, OnCancelCommand)
    ON_BN_CLICKED(IDC_TAKEOWNERSHIP, OnAcceptCommand)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessTakeOwnershipActionsDialog
//---------------------------------------------------------------------------
PSS_ProcessTakeOwnershipActionsDialog::PSS_ProcessTakeOwnershipActionsDialog(const CString& fileName,
                                                                             const CString& activityName,
                                                                             CWnd*          pParent) :
    ZIDialog(PSS_ProcessTakeOwnershipActionsDialog::IDD, TRUE, pParent),
    m_FileName(fileName),
    m_ActivityName(activityName)
{}
//---------------------------------------------------------------------------
void PSS_ProcessTakeOwnershipActionsDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ProcessTakeOwnershipActionsDialog)
    DDX_Control(pDX, IDC_VISUALIZE,     m_ViewCommandBtn);
    DDX_Control(pDX, IDC_CANCELCOMMAND, m_CancelCommandBtn);
    DDX_Control(pDX, IDC_TAKEOWNERSHIP, m_AcceptCommandBtn);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessTakeOwnershipActionsDialog::OnInitDialog()
{
    ZIDialog::OnInitDialog();

    if (GetDlgItem(IDC_OWNERSHIP_TEXT))
    {
        CString text;
        GetDlgItem(IDC_OWNERSHIP_TEXT)->GetWindowText(text);

        CString prompt;
        prompt.Format(text, m_ActivityName);

        GetDlgItem(IDC_OWNERSHIP_TEXT)->SetWindowText(prompt);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ProcessTakeOwnershipActionsDialog::OnViewCommand()
{
    ZFile file(m_FileName);

    // launch the file in preview
    if (file.Exist())
    {
        ZVFormFilePreviewDlg filePreviewDlg(m_FileName, ZAGlobal::GetpProcessDocTemplate());
        filePreviewDlg.DoModal();
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessTakeOwnershipActionsDialog::OnAcceptCommand()
{
    EndDialog(IDOK);
}
//---------------------------------------------------------------------------
void PSS_ProcessTakeOwnershipActionsDialog::OnCancelCommand()
{
    EndDialog(IDCANCEL);
}
//---------------------------------------------------------------------------
