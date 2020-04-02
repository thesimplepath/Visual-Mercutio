/****************************************************************************
 * ==> PSS_ReportCreationWizard --------------------------------------------*
 ****************************************************************************
 * Description : Provides a report creation wizard                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ReportCreationWizard.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ReportCreationWizard
//---------------------------------------------------------------------------
PSS_ReportCreationWizard::PSS_ReportCreationWizard(bool enableIncludeMonthDetail, bool enableExcelFormat) :
    m_EnableIncludeMonthDetail(enableIncludeMonthDetail),
    m_EnableExcelFormat(enableExcelFormat),
    m_IncludeMonthDetail(false),
    m_ExcelFormat(false)
{}
//---------------------------------------------------------------------------
PSS_ReportCreationWizard::~PSS_ReportCreationWizard()
{}
//---------------------------------------------------------------------------
int PSS_ReportCreationWizard::DoModal()
{
    PSS_ReportCreationStartDlg startDlg(m_EnableIncludeMonthDetail, m_EnableExcelFormat);

    if (startDlg.DoModal() == IDCANCEL)
        return IDCANCEL;

    // get the selected options
    m_ExcelFormat        = startDlg.GetExcelFormat();
    m_IncludeMonthDetail = startDlg.GetIncludeMonthDetail();

    return IDOK;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ReportCreationStartDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_ReportCreationStartDlg)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ReportCreationStartDlg
//---------------------------------------------------------------------------
PSS_ReportCreationStartDlg::PSS_ReportCreationStartDlg(bool  enableIncludeMonthDetail,
                                                       bool  enableExcelFormat,
                                                       CWnd* pParent) :
    PSS_WizardDialog(PSS_ReportCreationStartDlg::IDD,
                     IDB_WIZ_REPORT,
                     0,
                     0,
                     IDS_WZ_REPORTGENERATION_ST_S,
                     IDS_WZ_REPORTGENERATION_ST_T),
    m_IncludeMonthDetail(FALSE),
    m_ExcelFormat(FALSE),
    m_EnableIncludeMonthDetail(enableIncludeMonthDetail),
    m_EnableExcelFormat(enableExcelFormat)
{}
//---------------------------------------------------------------------------
PSS_ReportCreationStartDlg::~PSS_ReportCreationStartDlg()
{}
//---------------------------------------------------------------------------
void PSS_ReportCreationStartDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PSS_ReportCreationStartDlg)
    DDX_Check(pDX, IDC_INCLUDE_MONTHDETAILS, m_IncludeMonthDetail);
    DDX_Check(pDX, IDC_EXCEL_FORMAT,         m_ExcelFormat);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ReportCreationStartDlg::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    if (GetDlgItem(IDC_INCLUDE_MONTHDETAILS))
        GetDlgItem(IDC_INCLUDE_MONTHDETAILS)->EnableWindow(m_EnableIncludeMonthDetail);

    if (GetDlgItem(IDC_EXCEL_FORMAT))
        GetDlgItem(IDC_EXCEL_FORMAT)->EnableWindow(m_EnableExcelFormat);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ReportCreationStartDlg::OnNext()
{
    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
void PSS_ReportCreationStartDlg::OnOK()
{
    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
