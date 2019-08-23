/****************************************************************************
 * ==> PSS_PublishModelOptionsDialog ---------------------------------------*
 ****************************************************************************
 * Description : Dialog box allowing to select the model options to publish *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PublishModelOptionsDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message loop
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PublishModelOptionsDialog, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_PublishModelOptionsDialog)
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_PUBLISH_CONCEPTOR, OnBnClickedPublishConceptor)
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PublishModelOptionsDialog
//---------------------------------------------------------------------------
PSS_PublishModelOptionsDialog::PSS_PublishModelOptionsDialog(BOOL      visualize,
                                                             BOOL      publishConceptorIsChecked,
                                                             BOOL      publishConceptorDetailsIsChecked,
                                                             BOOL      publishConceptorDeliverablesIsChecked,
                                                             BOOL      publishProcessIsChecked,
                                                             BOOL      publishRuleBookIsChecked,
                                                             ELanguage initialLanguage,
                                                             CWnd*     pParent) :
    PSS_WizardDialog(PSS_PublishModelOptionsDialog::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_PUBLISHMODELOPTIONS_S,
                     IDS_PUBLISHMODELOPTIONS_T),
    m_Language(initialLanguage),
    m_Visualize(visualize),
    m_PublishConceptorIsChecked(publishConceptorIsChecked),
    m_PublishConceptorDetailsIsChecked(publishConceptorDetailsIsChecked),
    m_PublishConceptorDeliverablesIsChecked(publishConceptorDeliverablesIsChecked),
    m_PublishProcessIsChecked(publishProcessIsChecked),
    m_PublishRuleBookIsChecked(publishRuleBookIsChecked)
{}
//---------------------------------------------------------------------------
void PSS_PublishModelOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PublishModelOptionsDialog)
    DDX_Control(pDX, IDC_LANGUAGE,               m_CbLanguage);
    DDX_Check  (pDX, IDC_VISUALIZERESULT,        m_Visualize);
    DDX_Check  (pDX, IDC_PUBLISH_CONCEPTOR,      m_PublishConceptorIsChecked);
    DDX_Check  (pDX, IDC_CONCEPTOR_DETAILS,      m_PublishConceptorDetailsIsChecked);
    DDX_Check  (pDX, IDC_CONCEPTOR_DELIVERABLES, m_PublishConceptorDeliverablesIsChecked);
    DDX_Check  (pDX, IDC_PUBLISH_PROCESS,        m_PublishProcessIsChecked);
    DDX_Check  (pDX, IDC_PUBLISH_RULEBOOK,       m_PublishRuleBookIsChecked);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_PublishModelOptionsDialog::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    // initialize the language combo box
    m_CbLanguage.Initialize(m_Language);

    // update the buttons states
    OnBnClickedPublishConceptor();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PublishModelOptionsDialog::OnOK()
{
    UpdateData();

    // save the selected language
    m_Language = m_CbLanguage.GetLanguage();

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_PublishModelOptionsDialog::OnBnClickedPublishConceptor()
{
    CWnd* m_pIncludeDetailsCheckBox      = GetDlgItem(IDC_CONCEPTOR_DETAILS);
    CWnd* m_pIncludeDeliverablesCheckBox = GetDlgItem(IDC_CONCEPTOR_DELIVERABLES);

    if (m_pIncludeDetailsCheckBox && IDC_CONCEPTOR_DELIVERABLES)
    {
        m_pIncludeDetailsCheckBox->EnableWindow(IsDlgButtonChecked(IDC_PUBLISH_CONCEPTOR));
        m_pIncludeDeliverablesCheckBox->EnableWindow(IsDlgButtonChecked(IDC_PUBLISH_CONCEPTOR));
    }
}
//---------------------------------------------------------------------------
