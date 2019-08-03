/****************************************************************************
 * ==> PSS_ProcessOpenActionsDialog ----------------------------------------*
 ****************************************************************************
 * Description : Provides a process open actions dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessOpenActionsDialog.h"

// processsoft
#include "zBaseLib\File.h"
#include "zBaseLib\ZAGlobal.h"
#include "PSS_FileFormPreviewDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessOpenActionsDialog, ZIDialog)
    //{{AFX_MSG_MAP(PSS_ProcessOpenActionsDialog)
    ON_BN_CLICKED(IDC_VISUALIZE, OnViewCommand)
    ON_BN_CLICKED(IDC_CANCELCOMMAND, OnCancelCommand)
    ON_BN_CLICKED(IDC_OPENPROCESS, OnAcceptCommand)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessOpenActionsDialog
//---------------------------------------------------------------------------
PSS_ProcessOpenActionsDialog::PSS_ProcessOpenActionsDialog(const CString& fileName,
                                                           const CString& activityName,
                                                           CWnd*          pParent) :
    ZIDialog(PSS_ProcessOpenActionsDialog::IDD, TRUE, pParent),
    m_FileName(fileName),
    m_ActivityName(activityName)
{}
//---------------------------------------------------------------------------
void PSS_ProcessOpenActionsDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ProcessOpenActionsDialog)
    DDX_Control(pDX, IDC_VISUALIZE,     m_ViewCommandBtn);
    DDX_Control(pDX, IDC_CANCELCOMMAND, m_CancelCommandBtn);
    DDX_Control(pDX, IDC_OPENPROCESS,   m_AcceptCommandBtn);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessOpenActionsDialog::OnInitDialog()
{
    ZIDialog::OnInitDialog();

    if (GetDlgItem(IDC_OPENADMIN_TEXT))
    {
        CString text;
        GetDlgItem(IDC_OPENADMIN_TEXT)->GetWindowText(text);

        CString prompt;
        prompt.Format(text, m_ActivityName);

        GetDlgItem(IDC_OPENADMIN_TEXT)->SetWindowText(prompt);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ProcessOpenActionsDialog::OnViewCommand()
{
    ZFile file(m_FileName);

    // launch the file in preview
    if (file.Exist())
    {
        PSS_FileFormPreviewDialog filePreviewDlg(m_FileName, ZAGlobal::GetpProcessDocTemplate());
        filePreviewDlg.DoModal();
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessOpenActionsDialog::OnAcceptCommand()
{
    EndDialog(IDOK);
}
//---------------------------------------------------------------------------
void PSS_ProcessOpenActionsDialog::OnCancelCommand()
{
    EndDialog(IDCANCEL);
}
//---------------------------------------------------------------------------
