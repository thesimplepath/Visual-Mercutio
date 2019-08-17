/****************************************************************************
 * ==> PSS_GenericFormPage -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic form page                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_GenericFormPage.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "planfin.hdf"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_GenericFormPage, CPropertyPage)
    //{{AFX_MSG_MAP(PSS_GenericFormPage)
    ON_LBN_SELCHANGE(IDC_LISTPLANFIN, OnSelChangeList)
    ON_LBN_DBLCLK(IDC_LISTPLANFIN, OnDblclkListOfForms)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_GenericFormPage
//---------------------------------------------------------------------------
PSS_GenericFormPage::PSS_GenericFormPage() :
    CPropertyPage(PSS_GenericFormPage::IDD),
    m_pTemplateManager(NULL)
{}
//---------------------------------------------------------------------------
PSS_GenericFormPage::PSS_GenericFormPage(CWnd* pMain, const CString& title, ZDTemplateManager* pTemplateManager) :
    CPropertyPage(PSS_GenericFormPage::IDD),
    m_pTemplateManager(pTemplateManager)
{
    ASSERT(m_pTemplateManager);

    m_strCaption = title;

    #ifdef _WIN32
        m_psp.dwFlags  |= PSP_USETITLE;
        m_psp.pszTitle  = title;
    #endif
}
//---------------------------------------------------------------------------
PSS_GenericFormPage::~PSS_GenericFormPage()
{}
//---------------------------------------------------------------------------
BOOL PSS_GenericFormPage::OnSetActive()
{
    ASSERT(m_pTemplateManager);

    const BOOL result = CPropertyPage::OnSetActive();

    // copy values to the CListBox
    m_CtlListOfPlan.ResetContent();

          ZDTemplateDir* pTemplateDir  = m_pTemplateManager->FindTemplateDir(m_strCaption);
    const std::size_t    templateCount = pTemplateDir->GetSize();

    // iterate through all template directory
    for (std::size_t i = 0; i < templateCount; ++i)
    {
        ZDTemplateFile* pTemplateFile = pTemplateDir->GetTemplateFileAt(i);

        if (pTemplateFile)
            m_CtlListOfPlan.AddString(pTemplateFile->GetTitle());
    }

    GetParent()->GetParent()->PostMessage(UM_FORMACTIVATE);

    return result;
}
//---------------------------------------------------------------------------
void PSS_GenericFormPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_GenericFormPage)
    DDX_Control(pDX, IDC_LISTPLANFIN, m_CtlListOfPlan);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_GenericFormPage::OnSelChangeList()
{
    // set the commentary
    const int currentSelection = m_CtlListOfPlan.GetCurSel();

    if (currentSelection != LB_ERR && GetParent() && GetParent()->GetParent())
        GetParent()->GetParent()->PostMessage(UM_SETCOMMENT, currentSelection);
}
//---------------------------------------------------------------------------
void PSS_GenericFormPage::OnDblclkListOfForms()
{
    if (GetParent() && GetParent()->GetParent())
        GetParent()->GetParent()->PostMessage(UM_FORMS_SELECTED);
}
//---------------------------------------------------------------------------
