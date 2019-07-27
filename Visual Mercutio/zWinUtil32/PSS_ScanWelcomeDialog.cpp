/****************************************************************************
 * ==> PSS_ScanWelcomeDialog -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a scan welcome dialog box                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ScanWelcomeDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ScanWelcomeDialog, ZIWizardDialog)
    //{{AFX_MSG_MAP(PSS_ScanWelcomeDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ScanWelcomeDialog
//---------------------------------------------------------------------------
PSS_ScanWelcomeDialog::PSS_ScanWelcomeDialog(CWnd* pParent) :
    ZIWizardDialog(PSS_ScanWelcomeDialog::IDD,
                   IDB_WZBMP3,
                   0,
                   0,
                   IDS_SCANNINGWLC_S,
                   IDS_SCANNINGWLC_T)
{}
//---------------------------------------------------------------------------
void PSS_ScanWelcomeDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ScanWelcomeDialog)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ScanWelcomeDialog::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
