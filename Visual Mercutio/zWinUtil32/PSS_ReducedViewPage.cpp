/****************************************************************************
 * ==> PSS_ReducedViewPage -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a reduced view page                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ReducedViewPage.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ReducedViewPage, PSS_GenericPropPage)
    //{{AFX_MSG_MAP(PSS_ReducedViewPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ReducedViewPage
//---------------------------------------------------------------------------
PSS_ReducedViewPage::PSS_ReducedViewPage(ZAApplicationOption* pApplicationOptions) :
    PSS_GenericPropPage(PSS_ReducedViewPage::IDD, pApplicationOptions),
    m_CalculatedField(FALSE),
    m_ShowHiddenField(FALSE),
    m_AnimationShow(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ReducedViewPage::PSS_ReducedViewPage(const PSS_ReducedViewPage& other) :
    PSS_GenericPropPage(PSS_ReducedViewPage::IDD, NULL)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ReducedViewPage::~PSS_ReducedViewPage()
{}
//---------------------------------------------------------------------------
const PSS_ReducedViewPage& PSS_ReducedViewPage::operator = (const PSS_ReducedViewPage& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ReducedViewPage::SaveValuesToObject()
{
    if (::IsWindow(GetSafeHwnd()))
        UpdateData(TRUE);

    ((ZAApplicationOption&)GetObject()).SetbAnimationShow(m_AnimationShow);
    ((ZAApplicationOption&)GetObject()).SetbCalculateFieldShow(m_CalculatedField);
    ((ZAApplicationOption&)GetObject()).SetbShowHiddenField(m_ShowHiddenField);
}
//---------------------------------------------------------------------------
void PSS_ReducedViewPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ReducedViewPage)
    DDX_Check(pDX, IDC_CALCULATEDFIELD,  m_CalculatedField);
    DDX_Check(pDX, IDC_SHOWHIDDENFIELDS, m_ShowHiddenField);
    DDX_Check(pDX, IDC_ANIMATION,        m_AnimationShow);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ReducedViewPage::OnInitDialog()
{
    // set initialisation flag
    SetInitialized();

    m_CalculatedField = ((ZAApplicationOption&)GetObject()).GetbCalculateFieldShow();
    m_ShowHiddenField = ((ZAApplicationOption&)GetObject()).GetbShowHiddenField();
    m_AnimationShow   = ((ZAApplicationOption&)GetObject()).GetbAnimationShow();
      
    CDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ReducedViewPage::OnOK()
{
    if (Initialized())
        SaveValuesToObject();
}
//---------------------------------------------------------------------------
