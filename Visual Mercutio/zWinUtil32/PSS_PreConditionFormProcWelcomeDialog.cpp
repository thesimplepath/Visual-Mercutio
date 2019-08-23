/****************************************************************************
 * ==> PSS_PreConditionFormProcWelcomeDialog -------------------------------*
 ****************************************************************************
 * Description : Provides a pre-condition form process welcome dialog box   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PreConditionFormProcWelcomeDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PreConditionFormProcWelcomeDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_PreConditionFormProcWelcomeDialog)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PreConditionFormProcWelcomeDialog
//---------------------------------------------------------------------------
PSS_PreConditionFormProcWelcomeDialog::PSS_PreConditionFormProcWelcomeDialog(const CString& activityName, CWnd* pParent) :
    PSS_WizardDialog(PSS_PreConditionFormProcWelcomeDialog::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZPREACTIVITYTITLE_WZ,
                     IDS_WZPREACTIVITYTITLE_T),
    m_ActivityName(_T(activityName))
{}
//---------------------------------------------------------------------------
void PSS_PreConditionFormProcWelcomeDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PreConditionFormProcWelcomeDialog)
    DDX_Text(pDX, IDC_ACTIVITYNAME, m_ActivityName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_PreConditionFormProcWelcomeDialog::OnNext()
{
    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
