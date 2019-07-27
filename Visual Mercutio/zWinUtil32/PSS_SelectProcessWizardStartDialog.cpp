/****************************************************************************
 * ==> PSS_SelectProcessWizardStartDialog ----------------------------------*
 ****************************************************************************
 * Description : Provides a select process Wizard start dialog box          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectProcessWizardStartDialog.h"

// processsoft
#include "zBaseLib\MsgBox.h"

// resources
#include "zRes32\Zres.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectProcessWizardStartDialog, ZIWizardDialog)
    //{{AFX_MSG_MAP(PSS_SelectProcessWizardStartDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectProcessWizardStartDialog
//---------------------------------------------------------------------------
PSS_SelectProcessWizardStartDialog::PSS_SelectProcessWizardStartDialog(const CString& processName, CWnd* pParent) :
    ZIWizardDialog(PSS_SelectProcessWizardStartDialog::IDD,
                   IDB_WZBMP1,
                   0,
                   0,
                   IDS_SELECTIONPROCESSST_S,
                   IDS_SELECTIONPROCESSST_T),
    m_ProcessName(_T(processName))
{}
//---------------------------------------------------------------------------
void PSS_SelectProcessWizardStartDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectProcessWizardStartDialog)
    DDX_Text(pDX, IDC_PROCESSNAME, m_ProcessName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
