// PrcClsAc.cpp : implementation file
//

#include "stdafx.h"
#include "PrcClsAc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIProcessCloseActions dialog


ZIProcessCloseActions::ZIProcessCloseActions(BOOL SendCommand, BOOL AcceptRejectCommand, BOOL SuspendCommand, CWnd* pParent /*=NULL*/)
    : ZIDialog(ZIProcessCloseActions::IDD, TRUE, pParent),
    m_SendCommand(SendCommand), m_AcceptRejectCommand(AcceptRejectCommand), m_SuspendCommand(SuspendCommand)
{
    //{{AFX_DATA_INIT(ZIProcessCloseActions)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void ZIProcessCloseActions::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIProcessCloseActions)
    DDX_Control(pDX, IDC_ABORTCOMMAND, m_AbortCommand);
    DDX_Control(pDX, IDC_TRASHCOMMAND, m_TrashCommandBtn);
    DDX_Control(pDX, IDC_SUSPENDCOMMAND, m_SuspendCommandBtn);
    DDX_Control(pDX, IDC_SENDCOMMAND, m_SendCommandBtn);
    DDX_Control(pDX, IDC_REJECTCOMMAND, m_RejectCommandBtn);
    DDX_Control(pDX, IDC_CANCELCOMMAND, m_CancelCommandBtn);
    DDX_Control(pDX, IDC_ACCEPTCOMMAND, m_AcceptCommandBtn);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIProcessCloseActions, ZIDialog)
    //{{AFX_MSG_MAP(ZIProcessCloseActions)
    ON_BN_CLICKED(IDC_ACCEPTCOMMAND, OnAcceptCommand)
    ON_BN_CLICKED(IDC_REJECTCOMMAND, OnRejectCommand)
    ON_BN_CLICKED(IDC_SENDCOMMAND, OnSendCommand)
    ON_BN_CLICKED(IDC_SUSPENDCOMMAND, OnSuspendCommand)
    ON_BN_CLICKED(IDC_TRASHCOMMAND, OnTrashCommand)
    ON_BN_CLICKED(IDC_CANCELCOMMAND, OnCancelCommand)
    ON_BN_CLICKED(IDC_ABORTCOMMAND, OnAbortCommand)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIProcessCloseActions message handlers

void ZIProcessCloseActions::OnAcceptCommand() 
{
    EndDialog( IDACCEPTCOMMAND );
}

void ZIProcessCloseActions::OnRejectCommand() 
{
    EndDialog( IDREJECTCOMMAND );
}

void ZIProcessCloseActions::OnSendCommand() 
{
    EndDialog( IDSENDCOMMAND );
}

void ZIProcessCloseActions::OnSuspendCommand() 
{
    EndDialog( IDSUSPENDCOMMAND );
}

void ZIProcessCloseActions::OnTrashCommand() 
{
    EndDialog( IDTRASHCOMMAND );
}

void ZIProcessCloseActions::OnAbortCommand() 
{
    EndDialog( IDABORTCOMMAND );
}

void ZIProcessCloseActions::OnCancelCommand() 
{
    EndDialog( IDCANCELCOMMAND );
}

BOOL ZIProcessCloseActions::OnInitDialog() 
{
    ZIDialog::OnInitDialog();
    
    if (!m_SendCommand)
    {
        if (GetDlgItem(IDC_SENDCOMMAND))
           GetDlgItem(IDC_SENDCOMMAND)->EnableWindow( FALSE );
        m_SendCommandBtn.SetButtonState(BUTTON_GREYED);

    }
    if (!m_AcceptRejectCommand)
    {
        if (GetDlgItem(IDC_ACCEPTCOMMAND))
           GetDlgItem(IDC_ACCEPTCOMMAND)->EnableWindow( FALSE );
        m_AcceptCommandBtn.SetButtonState(BUTTON_GREYED);
        if (GetDlgItem(IDC_REJECTCOMMAND))
           GetDlgItem(IDC_REJECTCOMMAND)->EnableWindow( FALSE );
        m_RejectCommandBtn.SetButtonState(BUTTON_GREYED);
    }
    if (!m_SuspendCommand)
    {
        if (GetDlgItem(IDC_SUSPENDCOMMAND))
           GetDlgItem(IDC_SUSPENDCOMMAND)->EnableWindow( FALSE );
        m_SendCommandBtn.SetButtonState(BUTTON_GREYED);
    }
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


