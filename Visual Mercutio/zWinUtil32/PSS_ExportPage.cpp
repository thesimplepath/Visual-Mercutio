/****************************************************************************
 * ==> PSS_ExportPage ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an export options page                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ExportPage.h"

// processsoft
#include "zBaseLib\FileDlg.h"
#include "zBaseLib\Export.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ExportPage, ZIGenericPropPage)
    //{{AFX_MSG_MAP(PSS_ExportPage)
    //ON_BN_CLICKED(IDC_SELECT, OnSelect)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ExportPage
//---------------------------------------------------------------------------
PSS_ExportPage::PSS_ExportPage(ZAApplicationOption* pApplicationOptions) :
    ZIGenericPropPage(PSS_ExportPage::IDD, pApplicationOptions)
{}
//---------------------------------------------------------------------------
PSS_ExportPage::PSS_ExportPage(const PSS_ExportPage& other) :
    ZIGenericPropPage(PSS_ExportPage::IDD, NULL)
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

    ((ZAApplicationOption&)GetObject()).SetExportSchemaName(m_SchemaName);
    ((ZAApplicationOption&)GetObject()).SetEmptyWhenZero(m_EmptyWhenZero);

    switch (m_Propagation)
    {
        case 0:  ((ZAApplicationOption&)GetObject()).SetExportPropagationMode(g_LocatePageOnly);    break;
        case 1:  ((ZAApplicationOption&)GetObject()).SetExportPropagationMode(g_LocateForwardPage); break;
        case 2:  ((ZAApplicationOption&)GetObject()).SetExportPropagationMode(g_LocateAllPages);    break;
        default: ((ZAApplicationOption&)GetObject()).SetExportPropagationMode(g_LocateForwardPage); break;
    }
}
//---------------------------------------------------------------------------
void PSS_ExportPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ExportPage)
    DDX_Radio(pDX, IDC_PROPAGATION, m_Propagation);
    DDX_Text(pDX, IDC_SCHEMANAME, m_SchemaName);
    DDX_Check(pDX, IDC_EMPTYWHENZERO, m_EmptyWhenZero);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ExportPage::OnInitDialog()
{
    // set initialisation flag
    SetInitialized();

    m_SchemaName    = ((ZAApplicationOption&)GetObject()).GetExportSchemaName();
    m_EmptyWhenZero = ((ZAApplicationOption&)GetObject()).GetEmptyWhenZero();
    
    switch (((ZAApplicationOption&)GetObject()).GetExportPropagationMode())
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
    if (HasBeenInitialized())
        SaveValuesToObject();
}
//---------------------------------------------------------------------------
