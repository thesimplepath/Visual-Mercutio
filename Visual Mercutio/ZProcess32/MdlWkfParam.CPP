// MdlWkfParam.cpp : implementation file
//

#include "stdafx.h"
#include "MdlWkfParam.h"

#include "zWinUtil32\TmplSava.h"
#include "zModel\ProcGraphModelDoc.h"

#include "zBaseLib\MsgBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParameters class


ZVModelWorkflowParameters::ZVModelWorkflowParameters(BOOL Modify, ZDProcessGraphModelDoc* pDoc, ZDTemplateManager* pTemplateManager, CString FileExtension, CWnd* pParent /*=NULL*/)
    : m_Modify(Modify),
      m_pDoc(pDoc),
      m_pTemplateManager(pTemplateManager), 
      m_FileExtension(FileExtension),
      m_CheckConsistency(false),
      m_SaveModelInWkfFile(false),
      m_FileExist(false)
{
}


int    ZVModelWorkflowParameters::DoModal()
{

    ZVModelWorkflowParametersWelcome    Welcome;
    
    if (Welcome.DoModal() == IDCANCEL)
        return IDCANCEL;

    // Ask for process file destination
    ZITemplateCopyDlg    TemplateCopyDlg( m_pTemplateManager, m_FileExtension, &m_FolderStamp, TRUE );

    if (TemplateCopyDlg.DoModal() == IDCANCEL)
        return IDCANCEL;

    ZVModelWorkflowParametersOptions    Options( m_Modify, *m_pDoc );
    
    if (Options.DoModal() == IDCANCEL)
        return IDCANCEL;
            
    // Save options
    m_CheckConsistency = Options.GetCheckConsistency();
    m_SaveModelInWkfFile = Options.GetSaveModelInWorkflow();
    // Save template information 
    m_FolderStamp.SetTemplate ( TemplateCopyDlg.GetFilename() );
    m_FolderStamp.SetTemplate( TemplateCopyDlg.GetFilename() );
    m_FolderStamp.SetExplanation( TemplateCopyDlg.GetDescription() );
    m_FolderStamp.SetTitle( TemplateCopyDlg.GetTitle() );
    // Set the file exist flag
    m_FileExist = TemplateCopyDlg.FileChooseExists();


    return IDOK;    
}




/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParametersWelcome dialog


ZVModelWorkflowParametersWelcome::ZVModelWorkflowParametersWelcome(CWnd* pParent /*=NULL*/)
    : ZIWizardDialog(ZVModelWorkflowParametersWelcome::IDD, IDB_WZBMP1, 0, 0, IDS_WIZARDACTIVITYATTRIBUTION_WT, IDS_WIZARDACTIVITYATTRIBUTION_T )
{
    //{{AFX_DATA_INIT(ZVModelWorkflowParametersWelcome)
    //}}AFX_DATA_INIT
}

ZVModelWorkflowParametersWelcome::~ZVModelWorkflowParametersWelcome()
{
}


void ZVModelWorkflowParametersWelcome::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVModelWorkflowParametersWelcome)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZVModelWorkflowParametersWelcome, ZIWizardDialog)
    //{{AFX_MSG_MAP(ZVModelWorkflowParametersWelcome)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParametersWelcome message handlers


BOOL ZVModelWorkflowParametersWelcome::OnInitDialog()
{
    return ZIWizardDialog::OnInitDialog();
}


void ZVModelWorkflowParametersWelcome::OnOK()
{
    ZIWizardDialog::OnOK();
}

void ZVModelWorkflowParametersWelcome::OnNext()
{
    EndDialog( IDNEXT );
}




/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParametersOptions dialog


ZVModelWorkflowParametersOptions::ZVModelWorkflowParametersOptions(BOOL Modify, ZDProcessGraphModelDoc& Doc, CWnd* pParent /*=NULL*/)
    : ZIWizardDialog(ZVModelWorkflowParametersOptions::IDD, IDB_WZBMP1, 0, 0, IDS_WIZARDACTIVITYATTRIBUTION_WT, IDS_WIZARDACTIVITYATTRIBUTION_T ),
      m_Modify(Modify),
      m_Doc(Doc)
{
    //{{AFX_DATA_INIT(ZVModelWorkflowParametersOptions)
    m_CheckConsistency = m_Doc.GetCheckConsistency();
    m_SaveModelInWkfFile = m_Doc.GetSaveModelInWorkflow();
    //}}AFX_DATA_INIT
}

ZVModelWorkflowParametersOptions::~ZVModelWorkflowParametersOptions()
{
}


void ZVModelWorkflowParametersOptions::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVModelWorkflowParametersOptions)
    DDX_Check(pDX, IDC_CHECK_CONSISTENCY, m_CheckConsistency);
    DDX_Check(pDX, IDC_SAVEWKF_INFILE, m_SaveModelInWkfFile);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZVModelWorkflowParametersOptions, ZIWizardDialog)
    //{{AFX_MSG_MAP(ZVModelWorkflowParametersOptions)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZVModelWorkflowParametersOptions message handlers


BOOL ZVModelWorkflowParametersOptions::OnInitDialog()
{
    return ZIWizardDialog::OnInitDialog();
}


void ZVModelWorkflowParametersOptions::OnOK()
{
    UpdateData( TRUE );
    ZIWizardDialog::OnOK();
}

void ZVModelWorkflowParametersOptions::OnNext()
{
    UpdateData( TRUE );
    EndDialog( IDNEXT );
}
