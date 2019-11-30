// MdlWkfParam.cpp : implementation file
//

#include "stdafx.h"
#include "MdlWkfParam.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zWinUtil32\PSS_TemplateCopyDialog.h"
#include "zModel\ProcGraphModelDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParameters class

ZVModelWorkflowParameters::ZVModelWorkflowParameters(BOOL Modify, PSS_ProcessGraphModelDoc* pDoc, PSS_TemplateManager* pTemplateManager, CString FileExtension, CWnd* pParent /*=NULL*/)
    : m_Modify(Modify),
    m_pDoc(pDoc),
    m_pTemplateManager(pTemplateManager),
    m_FileExtension(FileExtension),
    m_CheckConsistency(false),
    m_SaveModelInWkfFile(false),
    m_FileExist(false)
{}

int ZVModelWorkflowParameters::DoModal()
{

    ZVModelWorkflowParametersWelcome    Welcome;

    if (Welcome.DoModal() == IDCANCEL)
        return IDCANCEL;

    // ask for process file destination
    PSS_TemplateCopyDialog templateCopyDialog(m_pTemplateManager, m_FileExtension, &m_FolderStamp, TRUE);

    if (templateCopyDialog.DoModal() == IDCANCEL)
        return IDCANCEL;

    ZVModelWorkflowParametersOptions    Options(m_Modify, *m_pDoc);

    if (Options.DoModal() == IDCANCEL)
        return IDCANCEL;

    // save options
    m_CheckConsistency = Options.GetCheckConsistency();
    m_SaveModelInWkfFile = Options.GetSaveModelInWorkflow();

    // save template information 
    m_FolderStamp.SetTemplate(templateCopyDialog.GetFileName());
    m_FolderStamp.SetTemplate(templateCopyDialog.GetFileName());
    m_FolderStamp.SetDescription(templateCopyDialog.GetDescription());
    m_FolderStamp.SetTitle(templateCopyDialog.GetTitle());

    // set the file exist flag
    m_FileExist = templateCopyDialog.SelectedFileExists();

    return IDOK;
}




/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParametersWelcome dialog


ZVModelWorkflowParametersWelcome::ZVModelWorkflowParametersWelcome(CWnd* pParent /*=NULL*/) :
    PSS_WizardDialog(ZVModelWorkflowParametersWelcome::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WIZARDACTIVITYATTRIBUTION_WT,
                     IDS_WIZARDACTIVITYATTRIBUTION_T)
{
    //{{AFX_DATA_INIT(ZVModelWorkflowParametersWelcome)
    //}}AFX_DATA_INIT
}

ZVModelWorkflowParametersWelcome::~ZVModelWorkflowParametersWelcome()
{}


void ZVModelWorkflowParametersWelcome::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVModelWorkflowParametersWelcome)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZVModelWorkflowParametersWelcome, PSS_WizardDialog)
    //{{AFX_MSG_MAP(ZVModelWorkflowParametersWelcome)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParametersWelcome message handlers


BOOL ZVModelWorkflowParametersWelcome::OnInitDialog()
{
    return PSS_WizardDialog::OnInitDialog();
}


void ZVModelWorkflowParametersWelcome::OnOK()
{
    PSS_WizardDialog::OnOK();
}

void ZVModelWorkflowParametersWelcome::OnNext()
{
    EndDialog(IDNEXT);
}




/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParametersOptions dialog


ZVModelWorkflowParametersOptions::ZVModelWorkflowParametersOptions(BOOL Modify, PSS_ProcessGraphModelDoc& Doc, CWnd* pParent /*=NULL*/) :
    PSS_WizardDialog(ZVModelWorkflowParametersOptions::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WIZARDACTIVITYATTRIBUTION_WT,
                     IDS_WIZARDACTIVITYATTRIBUTION_T),
    m_Modify(Modify),
    m_Doc(Doc)
{
    //{{AFX_DATA_INIT(ZVModelWorkflowParametersOptions)
    m_CheckConsistency = m_Doc.GetCheckConsistency();
    m_SaveModelInWkfFile = m_Doc.GetSaveModelInWorkflow();
    //}}AFX_DATA_INIT
}

ZVModelWorkflowParametersOptions::~ZVModelWorkflowParametersOptions()
{}


void ZVModelWorkflowParametersOptions::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVModelWorkflowParametersOptions)
    DDX_Check(pDX, IDC_CHECK_CONSISTENCY, m_CheckConsistency);
    DDX_Check(pDX, IDC_SAVEWKF_INFILE, m_SaveModelInWkfFile);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZVModelWorkflowParametersOptions, PSS_WizardDialog)
    //{{AFX_MSG_MAP(ZVModelWorkflowParametersOptions)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParametersOptions message handlers


BOOL ZVModelWorkflowParametersOptions::OnInitDialog()
{
    return PSS_WizardDialog::OnInitDialog();
}


void ZVModelWorkflowParametersOptions::OnOK()
{
    UpdateData(TRUE);
    PSS_WizardDialog::OnOK();
}

void ZVModelWorkflowParametersOptions::OnNext()
{
    UpdateData(TRUE);
    EndDialog(IDNEXT);
}
