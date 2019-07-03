// PreCFPW.cpp : implementation file
//

#include "stdafx.h"
#include "PreCFPW.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIPreConditionFormProcWelcome dialog


ZIPreConditionFormProcWelcome::ZIPreConditionFormProcWelcome(CString ActivityName, CWnd* pParent /*=NULL*/)
    : ZIWizardDialog(ZIPreConditionFormProcWelcome::IDD, // Dialog template
                     IDB_WZBMP1,    // Bitmap to display
                     0,                // Icon do display
                     0,                    // Window Title
                     IDS_WZPREACTIVITYTITLE_WZ, // Wizard title
                     IDS_WZPREACTIVITYTITLE_T    // Wizard text
                     )
{
    //{{AFX_DATA_INIT(ZIPreConditionFormProcWelcome)
    m_ActivityName = _T(ActivityName);
    //}}AFX_DATA_INIT
}


void ZIPreConditionFormProcWelcome::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIPreConditionFormProcWelcome)
    DDX_Text(pDX, IDC_ACTIVITYNAME, m_ActivityName);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIPreConditionFormProcWelcome, ZIWizardDialog)
    //{{AFX_MSG_MAP(ZIPreConditionFormProcWelcome)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIPreConditionFormProcWelcome message handlers

void ZIPreConditionFormProcWelcome::OnNext() 
{
    EndDialog( IDNEXT );    
}
