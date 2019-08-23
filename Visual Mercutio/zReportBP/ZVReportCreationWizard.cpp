// ZVReportCreationWizard.cpp: implementation of the ZVReportCreationWizard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZVReportCreationWizard.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 6 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZVReportCreationWizard::ZVReportCreationWizard(bool EnableIncludeMonthDetail    /*= true*/,
                                               bool EnableExcelFormat            /*= false*/)
    : m_EnableIncludeMonthDetail(EnableIncludeMonthDetail),
    m_EnableExcelFormat(EnableExcelFormat)
{}

ZVReportCreationWizard::~ZVReportCreationWizard()
{}

int    ZVReportCreationWizard::DoModal()
{
    ZVReportCreationStart Start(m_EnableIncludeMonthDetail, m_EnableExcelFormat);

    if (Start.DoModal() == IDCANCEL)
    {
        return IDCANCEL;
    }

    // Save options
    m_ExcelFormat = (Start.GetExcelFormat() == TRUE) ? true : false;
    m_IncludeMonthDetail = (Start.GetIncludeMonthDetail() == TRUE) ? true : false;

    return IDOK;
}

/////////////////////////////////////////////////////////////////////////////
// ZVReportCreationStart dialog

BEGIN_MESSAGE_MAP(ZVReportCreationStart, PSS_WizardDialog)
    //{{AFX_MSG_MAP(ZVReportCreationStart)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVReportCreationStart::ZVReportCreationStart(bool    EnableIncludeMonthDetail    /*= true*/,
                                             bool    EnableExcelFormat            /*= false*/,
                                             CWnd*    pParent                        /*=NULL*/) :
    PSS_WizardDialog(ZVReportCreationStart::IDD,
                     IDB_WIZ_REPORT,
                     0,
                     0,
                     IDS_WZ_REPORTGENERATION_ST_S,
                     IDS_WZ_REPORTGENERATION_ST_T),
    m_EnableIncludeMonthDetail(EnableIncludeMonthDetail),
    m_EnableExcelFormat(EnableExcelFormat)
{
    //{{AFX_DATA_INIT(ZVReportCreationStart)
    m_ExcelFormat = FALSE;
    m_IncludeMonthDetail = FALSE;
    //}}AFX_DATA_INIT
}

void ZVReportCreationStart::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVReportCreationStart)
    DDX_Check(pDX, IDC_EXCEL_FORMAT, m_ExcelFormat);
    DDX_Check(pDX, IDC_INCLUDE_MONTHDETAILS, m_IncludeMonthDetail);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVReportCreationStart message handlers

BOOL ZVReportCreationStart::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    if (GetDlgItem(IDC_INCLUDE_MONTHDETAILS))
    {
        GetDlgItem(IDC_INCLUDE_MONTHDETAILS)->EnableWindow((m_EnableIncludeMonthDetail == true) ? TRUE : FALSE);
    }

    if (GetDlgItem(IDC_EXCEL_FORMAT))
    {
        GetDlgItem(IDC_EXCEL_FORMAT)->EnableWindow((m_EnableExcelFormat == true) ? TRUE : FALSE);
    }

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVReportCreationStart::OnOK()
{
    PSS_WizardDialog::OnOK();
}

void ZVReportCreationStart::OnNext()
{
    EndDialog(IDNEXT);
}
