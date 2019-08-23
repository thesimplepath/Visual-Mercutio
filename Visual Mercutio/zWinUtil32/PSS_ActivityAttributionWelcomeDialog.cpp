/****************************************************************************
 * ==> PSS_ActivityAttributionWelcomeDialog --------------------------------*
 ****************************************************************************
 * Description : Provides the activity attribution welcome dialog box       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_ActivityAttributionWelcomeDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ActivityAttributionWelcomeDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_ActivityAttributionWelcomeDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ActivityAttributionWelcomeDialog
//---------------------------------------------------------------------------
PSS_ActivityAttributionWelcomeDialog::PSS_ActivityAttributionWelcomeDialog(ZActivity* pActivity, CWnd* pParent) :
    PSS_WizardDialog(PSS_ActivityAttributionWelcomeDialog::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_ATTRIBUTIONTITLEST_WZ,
                     IDS_ATTRIBUTIONSTTEXTE_WZ),
    m_pActivity(pActivity)
{}
//---------------------------------------------------------------------------
void PSS_ActivityAttributionWelcomeDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityAttributionWelcomeDialog::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    CString prompt;
    AfxFormatString1(prompt, IDS_ATTRIBUTIONACTIVITY_WTEXT, m_pActivity->GetName());

    if (GetDlgItem(IDC_STATIC_TEXTATTR))
       GetDlgItem(IDC_STATIC_TEXTATTR)->SetWindowText(prompt);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
