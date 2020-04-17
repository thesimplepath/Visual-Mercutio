/****************************************************************************
 * ==> PSS_ConceptorReportOptionsDlg ---------------------------------------*
 ****************************************************************************
 * Description : Provides a Conceptor report option dialog box              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ConceptorReportOptionsDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ConceptorReportOptionsDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_ConceptorReportOptionsDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ConceptorReportOptionsDlg
//---------------------------------------------------------------------------
PSS_ConceptorReportOptionsDlg::PSS_ConceptorReportOptionsDlg(CWnd* pParent) :
    PSS_WizardDialog(PSS_ConceptorReportOptionsDlg::IDD,
                     IDB_WIZ_REPORT,
                     0,
                     0,
                     IDS_WZ_REPORTGENERATION_ST_S,
                     IDS_WZ_REPORTGENERATION_ST_T),
    m_Deliverables(TRUE),
    m_Details(TRUE)
{}
//---------------------------------------------------------------------------
PSS_ConceptorReportOptionsDlg::~PSS_ConceptorReportOptionsDlg()
{}
//---------------------------------------------------------------------------
void PSS_ConceptorReportOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ConceptorReportOptionsDlg)
    DDX_Check(pDX, IDC_DELIVERABLE, m_Deliverables);
    DDX_Check(pDX, IDC_DETAIL,      m_Details);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_ConceptorReportOptionsDlg::OnOK()
{
    UpdateData();

    if (!m_Deliverables && !m_Details)
    {
        // warn the user
        PSS_MsgBox mBox;
        mBox.Show(IDS_ONEOPTIONREQUIRED, MB_OK);
        return;
    }

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
