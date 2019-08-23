/****************************************************************************
 * ==> PSS_SelectServerWelcomeDialog ---------------------------------------*
 ****************************************************************************
 * Description : Provides a select a server welcome dialog box              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectServerWelcomeDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectServerWelcomeDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_SelectServerWelcomeDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectServerWelcomeDialog
//---------------------------------------------------------------------------
PSS_SelectServerWelcomeDialog::PSS_SelectServerWelcomeDialog(BOOL local, CWnd* pParent) :
    PSS_WizardDialog(PSS_SelectServerWelcomeDialog::IDD,
                     IDB_WZBMP3,
                     0,
                     0,
                     IDS_SELECTIONSERVERWLC_SL,
                     IDS_SELECTIONSERVERWLC_TL),
    m_Local(local)
{
    if (!m_Local)
    {
        SetWizardSubjectText(IDS_SELECTIONSERVERWLC_SG);
        SetWizardBodyText(IDS_SELECTIONSERVERWLC_TG);
    }
}
//---------------------------------------------------------------------------
void PSS_SelectServerWelcomeDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectServerWelcomeDialog)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectServerWelcomeDialog::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    if (GetDlgItem(IDC_STATIC_LOCAL))
        GetDlgItem(IDC_STATIC_LOCAL)->ShowWindow(m_Local ? SW_SHOW : SW_HIDE);

    if (GetDlgItem(IDC_STATIC_GLOBAL))
        GetDlgItem(IDC_STATIC_GLOBAL)->ShowWindow(m_Local ? SW_HIDE : SW_SHOW);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
