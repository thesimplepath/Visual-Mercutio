/****************************************************************************
 * ==> PSS_ExportPage ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an export options page                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ExportPage.h"

// processsoft
#include "zBaseLib\PSS_FileDialog.h"
#include "zBaseLib\PSS_Export.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ExportPage, PSS_GenericPropPage)
    //{{AFX_MSG_MAP(PSS_ExportPage)
    //ON_BN_CLICKED(IDC_SELECT, OnSelect)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ExportPage
//---------------------------------------------------------------------------
PSS_ExportPage::PSS_ExportPage(PSS_ApplicationOption* pApplicationOptions) :
    PSS_GenericPropPage(PSS_ExportPage::IDD, pApplicationOptions)
{}
//---------------------------------------------------------------------------
PSS_ExportPage::PSS_ExportPage(const PSS_ExportPage& other) :
    PSS_GenericPropPage(PSS_ExportPage::IDD, NULL)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ExportPage::~PSS_ExportPage()
{}
//---------------------------------------------------------------------------
const PSS_ExportPage& PSS_ExportPage::operator = (const PSS_ExportPage& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ExportPage::SaveValuesToObject()
{
    if (::IsWindow(GetSafeHwnd()))
        UpdateData(TRUE);

    // get application options container
    PSS_ApplicationOption& appOpt = (PSS_ApplicationOption&)GetObject();

    appOpt.SetExportSchemaName(m_SchemaName);
    appOpt.SetEmptyWhenZero(m_EmptyWhenZero);

    switch (m_Propagation)
    {
        case 0:  appOpt.SetExportPropagationMode(g_LocatePageOnly);    break;
        case 1:  appOpt.SetExportPropagationMode(g_LocateForwardPage); break;
        case 2:  appOpt.SetExportPropagationMode(g_LocateAllPages);    break;
        default: appOpt.SetExportPropagationMode(g_LocateForwardPage); break;
    }
}
//---------------------------------------------------------------------------
void PSS_ExportPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ExportPage)
    DDX_Radio(pDX, IDC_PROPAGATION,   m_Propagation);
    DDX_Text (pDX, IDC_SCHEMANAME,    m_SchemaName);
    DDX_Check(pDX, IDC_EMPTYWHENZERO, m_EmptyWhenZero);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ExportPage::OnInitDialog()
{
    // set initialisation flag
    SetInitialized();

    // get application options container
    PSS_ApplicationOption& appOpt = (PSS_ApplicationOption&)GetObject();

    // update options
    m_SchemaName    = appOpt.GetExportSchemaName();
    m_EmptyWhenZero = appOpt.GetEmptyWhenZero();
    
    switch (appOpt.GetExportPropagationMode())
    {
        case g_LocatePageOnly:    m_Propagation = 0; break;
        case g_LocateForwardPage: m_Propagation = 1; break;
        case g_LocateAllPages:    m_Propagation = 2; break;
        default:                  m_Propagation = 1; break;
    }

    CDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ExportPage::OnOK()
{
    if (Initialized())
        SaveValuesToObject();
}
//---------------------------------------------------------------------------
