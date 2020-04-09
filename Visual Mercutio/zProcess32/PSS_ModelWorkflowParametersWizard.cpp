/****************************************************************************
 * ==> PSS_ModelWorkflowParametersWizard -----------------------------------*
 ****************************************************************************
 * Description : Provides a model workflow parameters wizard                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ModelWorkflowParametersWizard.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zWinUtil32\PSS_TemplateCopyDialog.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ModelWorkflowParametersWizard
//---------------------------------------------------------------------------
PSS_ModelWorkflowParametersWizard::PSS_ModelWorkflowParametersWizard(BOOL                      modify,
                                                                     PSS_ProcessGraphModelDoc* pDoc,
                                                                     PSS_TemplateManager*      pTemplateManager,
                                                                     const CString&            fileExtension,
                                                                     CWnd*                     pParent) :
    m_pDoc(pDoc),
    m_pTemplateManager(pTemplateManager),
    m_FileExtension(fileExtension),
    m_Modify(modify),
    m_CheckConsistency(false),
    m_SaveModelInWkfFile(false),
    m_FileExist(false)
{}
//---------------------------------------------------------------------------
PSS_ModelWorkflowParametersWizard::~PSS_ModelWorkflowParametersWizard()
{}
//---------------------------------------------------------------------------
int PSS_ModelWorkflowParametersWizard::DoModal()
{
    PSS_ModelWorkflowParamsWelcomeDlg welcome;

    if (welcome.DoModal() == IDCANCEL)
        return IDCANCEL;

    // ask for process file destination
    PSS_TemplateCopyDialog templateCopyDialog(m_pTemplateManager, m_FileExtension, &m_FolderStamp, TRUE);

    if (templateCopyDialog.DoModal() == IDCANCEL)
        return IDCANCEL;

    PSS_ModelWorkflowParamsOptionsDlg options(m_Modify, *m_pDoc);

    if (options.DoModal() == IDCANCEL)
        return IDCANCEL;

    // save options
    m_CheckConsistency   = options.GetCheckConsistency();
    m_SaveModelInWkfFile = options.GetSaveModelInWorkflow();

    // save template information 
    m_FolderStamp.SetTemplate(templateCopyDialog.GetFileName());
    m_FolderStamp.SetTemplate(templateCopyDialog.GetFileName());
    m_FolderStamp.SetDescription(templateCopyDialog.GetDescription());
    m_FolderStamp.SetTitle(templateCopyDialog.GetTitle());

    // set the file exist flag
    m_FileExist = templateCopyDialog.SelectedFileExists();

    return IDOK;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ModelWorkflowParamsWelcomeDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_ModelWorkflowParamsWelcomeDlg)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ModelWorkflowParamsWelcomeDlg
//---------------------------------------------------------------------------
PSS_ModelWorkflowParamsWelcomeDlg::PSS_ModelWorkflowParamsWelcomeDlg(CWnd* pParent) :
    PSS_WizardDialog(PSS_ModelWorkflowParamsWelcomeDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WIZARDACTIVITYATTRIBUTION_WT,
                     IDS_WIZARDACTIVITYATTRIBUTION_T)
{}
//---------------------------------------------------------------------------
PSS_ModelWorkflowParamsWelcomeDlg::~PSS_ModelWorkflowParamsWelcomeDlg()
{}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowParamsWelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ModelWorkflowParamsWelcomeDlg)
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ModelWorkflowParamsWelcomeDlg::OnInitDialog()
{
    return PSS_WizardDialog::OnInitDialog();
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowParamsWelcomeDlg::OnNext()
{
    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowParamsWelcomeDlg::OnOK()
{
    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ModelWorkflowParamsOptionsDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_ModelWorkflowParamsOptionsDlg)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ModelWorkflowParamsOptionsDlg
//---------------------------------------------------------------------------
PSS_ModelWorkflowParamsOptionsDlg::PSS_ModelWorkflowParamsOptionsDlg(BOOL                      modify,
                                                                     PSS_ProcessGraphModelDoc& doc,
                                                                     CWnd*                     pParent) :
    PSS_WizardDialog(PSS_ModelWorkflowParamsOptionsDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WIZARDACTIVITYATTRIBUTION_WT,
                     IDS_WIZARDACTIVITYATTRIBUTION_T),
    m_Doc(doc),
    m_CheckConsistency(FALSE),
    m_SaveModelInWkfFile(FALSE),
    m_Modify(modify)
{
    m_CheckConsistency   = m_Doc.GetCheckConsistency();
    m_SaveModelInWkfFile = m_Doc.GetSaveModelInWorkflow();
}
//---------------------------------------------------------------------------
PSS_ModelWorkflowParamsOptionsDlg::~PSS_ModelWorkflowParamsOptionsDlg()
{}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowParamsOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ModelWorkflowParamsOptionsDlg)
    DDX_Check(pDX, IDC_CHECK_CONSISTENCY, m_CheckConsistency);
    DDX_Check(pDX, IDC_SAVEWKF_INFILE,    m_SaveModelInWkfFile);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ModelWorkflowParamsOptionsDlg::OnInitDialog()
{
    return PSS_WizardDialog::OnInitDialog();
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowParamsOptionsDlg::OnNext()
{
    UpdateData(TRUE);
    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowParamsOptionsDlg::OnOK()
{
    UpdateData(TRUE);
    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
