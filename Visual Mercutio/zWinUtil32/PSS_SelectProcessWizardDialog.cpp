/****************************************************************************
 * ==> PSS_SelectProcessWizardDialog ---------------------------------------*
 ****************************************************************************
 * Description : Provides a select process Wizard dialog box                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectProcessWizardDialog.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectProcessWizardDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_SelectProcessWizardDialog)
    ON_NOTIFY(NM_CLICK, IDC_ACTIVITYPROC_LIST, OnClickActivityProcList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectProcessWizardDialog
//---------------------------------------------------------------------------
PSS_SelectProcessWizardDialog::PSS_SelectProcessWizardDialog(ZProcess& process, CWnd* pParent) :
    PSS_WizardDialog(PSS_SelectProcessWizardDialog::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_SELECTIONPROCESSCS_S,
                     IDS_SELECTIONPROCESSCS_T),
      m_Process(process)
{
    m_ProcessName = _T(m_Process.GetName());
}
//---------------------------------------------------------------------------
void PSS_SelectProcessWizardDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectProcessWizardDialog)
    DDX_Control(pDX, IDC_ACTIVITYPROC_LIST, m_ActivityProcList);
    DDX_Text   (pDX, IDC_PROCESSNAME,       m_ProcessName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectProcessWizardDialog::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    m_ActivityProcList.Initialize(&m_Process);

    CheckControlStates();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectProcessWizardDialog::OnClickActivityProcList(NMHDR* pNMHDR, LRESULT* pResult)
{
    CheckControlStates();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_SelectProcessWizardDialog::OnOK()
{
    UpdateData();

    // assign the selected activity name
    m_BaseActivityName = m_ActivityProcList.GetSelectedActivity();

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_SelectProcessWizardDialog::CheckControlStates()
{
    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(!m_ActivityProcList.GetSelectedActivity().IsEmpty());
}
//---------------------------------------------------------------------------
