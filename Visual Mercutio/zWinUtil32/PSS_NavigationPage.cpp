/****************************************************************************
 * ==> PSS_NavigationPage --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigation page                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_NavigationPage.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_NavigationPage, PSS_GenericPropPage)
    //{{AFX_MSG_MAP(PSS_NavigationPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_NavigationPage
//---------------------------------------------------------------------------
PSS_NavigationPage::PSS_NavigationPage(ZAApplicationOption* pApplicationOptions) :
    PSS_GenericPropPage(PSS_NavigationPage::IDD, pApplicationOptions),
    m_GoNextEdit(FALSE)
{}
//---------------------------------------------------------------------------
PSS_NavigationPage::PSS_NavigationPage(const PSS_NavigationPage& other) :
    PSS_GenericPropPage(PSS_NavigationPage::IDD, NULL)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_NavigationPage::~PSS_NavigationPage()
{}
//---------------------------------------------------------------------------
const PSS_NavigationPage& PSS_NavigationPage::operator = (const PSS_NavigationPage& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_NavigationPage::SaveValuesToObject()
{
    if (::IsWindow(GetSafeHwnd()))
        UpdateData(TRUE);

    ((ZAApplicationOption&)GetObject()).SetGoNextEdit(m_GoNextEdit);
}
//---------------------------------------------------------------------------
void PSS_NavigationPage::DoDataExchange (CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_NavigationPage)
    DDX_Check(pDX, IDC_GONEXTEDIT, m_GoNextEdit);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_NavigationPage::OnInitDialog()
{
    // set initialisation flag
    SetInitialized();
      
    m_GoNextEdit = ((ZAApplicationOption&)GetObject()).GetGoNextEdit();
    CDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_NavigationPage::OnOK()
{
    if (Initialized())
        SaveValuesToObject();
}
//---------------------------------------------------------------------------
