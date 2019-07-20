/****************************************************************************
 * ==> PSS_ConfirmDeleteMessageDialog --------------------------------------*
 ****************************************************************************
 * Description : Provides a confirm delete message dialog box               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ConfirmDeleteMessageDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ConfirmDeleteMessageDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_ConfirmDeleteMessageDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_CalendarWindowDialog
//---------------------------------------------------------------------------
PSS_ConfirmDeleteMessageDialog::PSS_ConfirmDeleteMessageDialog(ZBEventActivity& eventActivity, CWnd* pParent) :
    ZIDialog(PSS_ConfirmDeleteMessageDialog::IDD, TRUE, pParent),
    m_ActivityName(eventActivity.GetActivityName()),
    m_Message(eventActivity.GetComments()),
    m_ProcessName(eventActivity.GetProcessName()),
    m_Status(eventActivity.GetActivityStatusString())
{}
//---------------------------------------------------------------------------
void PSS_ConfirmDeleteMessageDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ConfirmDeleteMessageDialog)
    DDX_Control(pDX, IDOK, m_Delete);
    DDX_Control(pDX, IDCANCEL, m_DoNotDelete);
    DDX_Text(pDX, IDC_ACTIVITY_NAME, m_ActivityName);
    DDX_Text(pDX, IDC_MESSAGE_TEXT, m_Message);
    DDX_Text(pDX, IDC_PROCESS_NAME, m_ProcessName);
    DDX_Text(pDX, IDC_STATUS_TEXT, m_Status);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
