/****************************************************************************
 * ==> PSS_ProcessCloseActionsDialog ---------------------------------------*
 ****************************************************************************
 * Description : Provides a process close actions dialog box                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessCloseActionsDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const UINT g_AcceptCommandID  = 10;
const UINT g_RejectCommandID  = 11;
const UINT g_SendCommandID    = 12;
const UINT g_SuspendCommandID = 13;
const UINT g_TrashCommandID   = 14;
const UINT g_CancelCommandID  = 15;
const UINT g_AbortCommandID   = 16;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessCloseActionsDialog, PSS_Dialog)
    //{{AFX_MSG_MAP(PSS_ProcessCloseActionsDialog)
    ON_BN_CLICKED(IDC_ACCEPTCOMMAND, OnAcceptCommand)
    ON_BN_CLICKED(IDC_REJECTCOMMAND, OnRejectCommand)
    ON_BN_CLICKED(IDC_SENDCOMMAND, OnSendCommand)
    ON_BN_CLICKED(IDC_SUSPENDCOMMAND, OnSuspendCommand)
    ON_BN_CLICKED(IDC_TRASHCOMMAND, OnTrashCommand)
    ON_BN_CLICKED(IDC_CANCELCOMMAND, OnCancelCommand)
    ON_BN_CLICKED(IDC_ABORTCOMMAND, OnAbortCommand)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessCloseActionsDialog
//---------------------------------------------------------------------------
PSS_ProcessCloseActionsDialog::PSS_ProcessCloseActionsDialog(BOOL  sendCommand,
                                                             BOOL  acceptRejectCommand,
                                                             BOOL  suspendCommand,
                                                             CWnd* pParent) :
    PSS_Dialog(PSS_ProcessCloseActionsDialog::IDD, TRUE, pParent),
    m_SendCommand(sendCommand),
    m_AcceptRejectCommand(acceptRejectCommand),
    m_SuspendCommand(suspendCommand)
{}
//---------------------------------------------------------------------------
void PSS_ProcessCloseActionsDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ProcessCloseActionsDialog)
    DDX_Control(pDX, IDC_ABORTCOMMAND,   m_AbortCommand);
    DDX_Control(pDX, IDC_TRASHCOMMAND,   m_TrashCommandBtn);
    DDX_Control(pDX, IDC_SUSPENDCOMMAND, m_SuspendCommandBtn);
    DDX_Control(pDX, IDC_SENDCOMMAND,    m_SendCommandBtn);
    DDX_Control(pDX, IDC_REJECTCOMMAND,  m_RejectCommandBtn);
    DDX_Control(pDX, IDC_CANCELCOMMAND,  m_CancelCommandBtn);
    DDX_Control(pDX, IDC_ACCEPTCOMMAND,  m_AcceptCommandBtn);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessCloseActionsDialog::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    if (!m_SendCommand)
    {
        if (GetDlgItem(IDC_SENDCOMMAND))
            GetDlgItem(IDC_SENDCOMMAND)->EnableWindow(FALSE);

        m_SendCommandBtn.SetButtonState(EHoverButtonState::E_HB_Greyed);
    }

    if (!m_AcceptRejectCommand)
    {
        if (GetDlgItem(IDC_ACCEPTCOMMAND))
            GetDlgItem(IDC_ACCEPTCOMMAND)->EnableWindow(FALSE);

        m_AcceptCommandBtn.SetButtonState(EHoverButtonState::E_HB_Greyed);

        if (GetDlgItem(IDC_REJECTCOMMAND))
            GetDlgItem(IDC_REJECTCOMMAND)->EnableWindow(FALSE);

        m_RejectCommandBtn.SetButtonState(EHoverButtonState::E_HB_Greyed);
    }

    if (!m_SuspendCommand)
    {
        if (GetDlgItem(IDC_SUSPENDCOMMAND))
            GetDlgItem(IDC_SUSPENDCOMMAND)->EnableWindow(FALSE);

        m_SendCommandBtn.SetButtonState(EHoverButtonState::E_HB_Greyed);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ProcessCloseActionsDialog::OnAcceptCommand()
{
    EndDialog(g_AcceptCommandID);
}
//---------------------------------------------------------------------------
void PSS_ProcessCloseActionsDialog::OnRejectCommand()
{
    EndDialog(g_RejectCommandID);
}
//---------------------------------------------------------------------------
void PSS_ProcessCloseActionsDialog::OnSendCommand()
{
    EndDialog(g_SendCommandID);
}
//---------------------------------------------------------------------------
void PSS_ProcessCloseActionsDialog::OnSuspendCommand()
{
    EndDialog(g_SuspendCommandID);
}
//---------------------------------------------------------------------------
void PSS_ProcessCloseActionsDialog::OnTrashCommand()
{
    EndDialog(g_TrashCommandID);
}
//---------------------------------------------------------------------------
void PSS_ProcessCloseActionsDialog::OnCancelCommand()
{
    EndDialog(g_CancelCommandID);
}
//---------------------------------------------------------------------------
void PSS_ProcessCloseActionsDialog::OnAbortCommand()
{
    EndDialog(g_AbortCommandID);
}
//---------------------------------------------------------------------------
