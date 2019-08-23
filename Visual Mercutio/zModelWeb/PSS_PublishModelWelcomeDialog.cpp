/****************************************************************************
 * ==> PSS_PublishModelWelcomeDialog ---------------------------------------*
 ****************************************************************************
 * Description : Dialog box showing the publication process welcome page    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PublishModelWelcomeDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message loop
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PublishModelWelcomeDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_PublishModelWelcomeDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PublishModelWelcomeDialog
//---------------------------------------------------------------------------
PSS_PublishModelWelcomeDialog::PSS_PublishModelWelcomeDialog(CWnd* pParent) :
    PSS_WizardDialog(PSS_PublishModelWelcomeDialog::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_PUBLISHMODELWELCOME_S,
                     IDS_PUBLISHMODELWELCOME_T)
{}
//---------------------------------------------------------------------------
void PSS_PublishModelWelcomeDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);
}
//---------------------------------------------------------------------------
BOOL PSS_PublishModelWelcomeDialog::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control. NOTE OCX Property Pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
