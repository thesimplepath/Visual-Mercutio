/****************************************************************************
 * ==> PSS_CalculationPage -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a page containing calculation options for the     *
 *               system                                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_CalculationPage.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_CalculationPage, ZIGenericPropPage)
    //{{AFX_MSG_MAP(PSS_CalculationPage)
    ON_BN_CLICKED(IDC_AUTOCALCULATION, OnAutocalculation)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_CalculationPage
//---------------------------------------------------------------------------
PSS_CalculationPage::PSS_CalculationPage(ZAApplicationOption* pApplicationOptions) :
    ZIGenericPropPage(PSS_CalculationPage::IDD, pApplicationOptions)
{}
//---------------------------------------------------------------------------
PSS_CalculationPage::PSS_CalculationPage(const PSS_CalculationPage& other) :
    ZIGenericPropPage(PSS_CalculationPage::IDD, NULL)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_CalculationPage::~PSS_CalculationPage()
{}
//---------------------------------------------------------------------------
const PSS_CalculationPage& PSS_CalculationPage::operator = (const PSS_CalculationPage& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_CalculationPage::SaveValuesToObject()
{
    if (::IsWindow(GetSafeHwnd()))
        UpdateData(TRUE);

    ((ZAApplicationOption&)GetObject()).SetbAutoCalculate(GetAutoCalculate());
}
//---------------------------------------------------------------------------
void PSS_CalculationPage::DoDataExchange (CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(ZICalculationPage)
    DDX_Check(pDX, IDC_AUTOCALCULATION, m_AutoCalculate);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_CalculationPage::OnInitDialog()
{
    // set initialisation flag
    SetInitialized();

    m_AutoCalculate = ((ZAApplicationOption&)GetObject()).GetbAutoCalculate();

    CDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_CalculationPage::OnAutocalculation()
{
    UpdateData();
}
//---------------------------------------------------------------------------
void PSS_CalculationPage::OnOK()
{
    if (HasBeenInitialized())
        SaveValuesToObject();
}
//---------------------------------------------------------------------------
