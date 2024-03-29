/****************************************************************************
 * ==> PSS_ViewPage --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a view page                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ViewPage.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ViewPage, PSS_GenericPropPage)
    //{{AFX_MSG_MAP(PSS_ViewPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ViewPage
//---------------------------------------------------------------------------
PSS_ViewPage::PSS_ViewPage(PSS_ApplicationOption* pApplicationOptions) :
    PSS_GenericPropPage(PSS_ViewPage::IDD, pApplicationOptions),
    m_CalculatedField(FALSE),
    m_ShowHiddenField(FALSE),
    m_AnimationShow(FALSE),
    m_ShowBoundsRect(FALSE),
    m_AutomaticCreateFieldName(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ViewPage::PSS_ViewPage(const PSS_ViewPage& other) :
    PSS_GenericPropPage(PSS_ViewPage::IDD, NULL)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ViewPage::~PSS_ViewPage()
{}
//---------------------------------------------------------------------------
const PSS_ViewPage& PSS_ViewPage::operator = (const PSS_ViewPage& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ViewPage::SaveValuesToObject()
{
    if (::IsWindow(GetSafeHwnd()))
        UpdateData(TRUE);

    // get application options container
    PSS_ApplicationOption& appOpt = (PSS_ApplicationOption&)GetObject();

    // update options
    appOpt.SetShowAnimation             (m_AnimationShow);
    appOpt.SetShowCalculateField        (m_CalculatedField);
    appOpt.SetShowHiddenField           (m_ShowHiddenField);
    appOpt.SetShowBoundsRect            (m_ShowBoundsRect);
    appOpt.SetAutomaticFieldNameCreation(m_AutomaticCreateFieldName);
}
//---------------------------------------------------------------------------
void PSS_ViewPage::DoDataExchange (CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ViewPage)
    DDX_Check(pDX, IDC_CALCULATEDFIELD,     m_CalculatedField);
    DDX_Check(pDX, IDC_SHOWHIDDENFIELDS,    m_ShowHiddenField);
    DDX_Check(pDX, IDC_ANIMATION,           m_AnimationShow);
    DDX_Check(pDX, IDC_SHOWBOUNDSRECT,      m_ShowBoundsRect);
    DDX_Check(pDX, IDC_AUTOCREATEFIELDNAME, m_AutomaticCreateFieldName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ViewPage::OnInitDialog()
{
    // set initialisation flag
    SetInitialized();

    // get application options container
    PSS_ApplicationOption& appOpt = (PSS_ApplicationOption&)GetObject();

    // update options
    m_CalculatedField          = appOpt.GetShowCalculateField();
    m_ShowHiddenField          = appOpt.GetShowHiddenField();
    m_AnimationShow            = appOpt.GetShowAnimation();
    m_ShowBoundsRect           = appOpt.GetShowBoundsRect();
    m_AutomaticCreateFieldName = appOpt.GetAutomaticFieldNameCreation();

    CDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ViewPage::OnOK()
{
    if (Initialized())
        SaveValuesToObject();
}
//---------------------------------------------------------------------------
