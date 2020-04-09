/****************************************************************************
 * ==> PSS_ProcessNameDialog -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a process name dialog box                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessNameDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessNameDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_ProcessNameDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessNameDialog
//---------------------------------------------------------------------------
PSS_ProcessNameDialog::PSS_ProcessNameDialog(CWnd* pParent) :
    CDialog(PSS_ProcessNameDialog::IDD, pParent)
{}
//---------------------------------------------------------------------------
PSS_ProcessNameDialog::~PSS_ProcessNameDialog()
{}
//---------------------------------------------------------------------------
void PSS_ProcessNameDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ProcessNameDialog)
    DDX_Text(pDX, IDC_PROCESSNAME_MODEL, m_ProcessName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_ProcessNameDialog::OnOK()
{
    CDialog::OnOK();
}
//---------------------------------------------------------------------------
