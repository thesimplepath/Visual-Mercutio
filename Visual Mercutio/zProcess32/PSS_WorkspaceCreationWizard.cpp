/****************************************************************************
 * ==> PSS_WorkspaceCreationWizard -----------------------------------------*
 ****************************************************************************
 * Description : Provides the workspace creation wizard                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceCreationWizard.h"

// processsoft
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\PSS_Directory.h"
#include "zBaseLib\PSS_WorkspaceWizardTemplateManager.h"
#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_WorkspaceCreationWizard
//---------------------------------------------------------------------------
PSS_WorkspaceCreationWizard::PSS_WorkspaceCreationWizard(PSS_WorkspaceWizardTemplateManager* pWorkspaceTemplateManager,
                                                         const CString&                      initialDirectory,
                                                         const CString&                      workspaceExtension,
                                                         bool                                modify) :
    m_pWorkspaceTemplateManager(pWorkspaceTemplateManager),
    m_InitialDirectory(initialDirectory),
    m_WorkspaceExtension(workspaceExtension),
    m_Modify(modify)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceCreationWizard::~PSS_WorkspaceCreationWizard()
{}
//---------------------------------------------------------------------------
int PSS_WorkspaceCreationWizard::DoModal()
{
    PSS_WorkspaceStartDlg startDlg(m_InitialDirectory, m_WorkspaceExtension, m_Modify);

    if (startDlg.DoModal() == IDCANCEL)
        return IDCANCEL;

    PSS_WorkspaceTemplateDlg templateDlg(m_pWorkspaceTemplateManager);

    if (templateDlg.DoModal() == IDCANCEL)
        return IDCANCEL;

    // save options
    m_WorkspaceName     = startDlg.GetWorkspaceName();
    m_Directory         = startDlg.GetDirectory();
    m_WorkspaceFileName = startDlg.GetWorkspaceFileName();

    return IDOK;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WorkspaceStartDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_WorkspaceStartDlg)
    ON_BN_CLICKED(IDNEXT, OnNext)
    ON_EN_CHANGE(IDC_WORKSPACE_NAME, OnChangeWorkspaceName)
    ON_EN_CHANGE(IDC_WORKSPACE_FOLDER, OnChangeWorkspaceFolder)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WorkspaceStartDlg
//---------------------------------------------------------------------------
PSS_WorkspaceStartDlg::PSS_WorkspaceStartDlg(const CString& initialDirectory,
                                             const CString& workspaceExtension,
                                             bool           modify,
                                             CWnd*          pParent) :
    PSS_WizardDialog(PSS_WorkspaceStartDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_WORKSPACE_ST_S,
                     IDS_WZ_WORKSPACE_ST_T),
    m_InitialDirectory(initialDirectory),
    m_WorkspaceExtension(workspaceExtension),
    m_Modify(modify),
    m_HasChanged(false)
{
    // set the edit to search for file
    m_Directory.SetSearchType(PSS_SearchEditButton::IE_T_Directory, IDS_SELWORKSPACE_DIR_T, initialDirectory);
}
//---------------------------------------------------------------------------
PSS_WorkspaceStartDlg::~PSS_WorkspaceStartDlg()
{}
//---------------------------------------------------------------------------
void PSS_WorkspaceStartDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_WorkspaceStartDlg)
    DDX_Control(pDX, IDC_WORKSPACE_FOLDER, m_Directory);
    DDX_Text   (pDX, IDC_WORKSPACE_NAME,   m_WorkspaceName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceStartDlg::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    PSS_Directory::NormalizeDirectory(m_InitialDirectory);
    m_InitialDirectory += _T("\\");
    m_Directory.SetWindowText(m_InitialDirectory);

    m_HasChanged = false;

    if (!m_Modify)
        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->ShowWindow(SW_HIDE);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceStartDlg::OnChangeWorkspaceName()
{
    // if the directory has not changed, continue to add the entered caracters to the directory
    if (!m_HasChanged)
        if (GetDlgItem(IDC_WORKSPACE_NAME))
        {
            CString name;
            GetDlgItem(IDC_WORKSPACE_NAME)->GetWindowText(name);

            // add the entered name
            m_Directory.SetWindowText(m_InitialDirectory + name);

            // OnChange() event was called because of the SetWindowText() function, so the has changed
            // flag should be reseted. If the dir was modified by the user, the flag will not be reset
            m_HasChanged = false;
        }
}
//---------------------------------------------------------------------------
void PSS_WorkspaceStartDlg::OnChangeWorkspaceFolder()
{
    m_HasChanged = true;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceStartDlg::OnNext()
{
    if (!Validate())
        return;

    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
void PSS_WorkspaceStartDlg::OnOK()
{
    if (!Validate())
        return;

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceStartDlg::Validate()
{
    UpdateData(TRUE);

    // cannot be empty
    if (m_WorkspaceName.IsEmpty())
        return false;

    m_Directory.GetWindowText(m_DirectoryStr);

    // normalize the directory
    PSS_Directory::NormalizeDirectory(m_DirectoryStr);

    // build the workspace file name
    m_WorkspaceFileName  = PSS_Directory::NormalizeDirectory(m_DirectoryStr) + _T("\\");
    m_WorkspaceFileName += m_WorkspaceName;
    m_WorkspaceFileName += m_WorkspaceExtension;

    if (!PSS_Directory::Exist(m_DirectoryStr))
    {
        // ask the user to create the directory
        PSS_MsgBox mBox;

        if (mBox.Show(IDS_WKSPACE_DIR_NEEDCREATE, MB_YESNO) == IDNO)
            return false;

        // create it
        PSS_Directory::CreateDirectory(m_DirectoryStr);

        // still not created?
        if (!PSS_Directory::Exist(m_DirectoryStr))
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_WKSPACE_DIR_FAILCREATE, MB_OK);
            return false;
        }
    }
    else
    // check if the workspace already exists. If yes, ask to replace
    if (PSS_File::Exist(m_WorkspaceFileName))
    {
        PSS_MsgBox mBox;

        if (mBox.Show(IDS_WKSPACE_ALREADYEXIST, MB_YESNO) == IDNO)
            return false;
    }

    return true;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WorkspaceTemplateDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_WorkspaceTemplateDlg)
    ON_NOTIFY(NM_CLICK, IDC_WKS_TEMPLATELIST, OnClickWksTemplatelist)
    ON_NOTIFY(NM_DBLCLK, IDC_WKS_TEMPLATELIST, OnDblclkWksTemplatelist)
    ON_NOTIFY(NM_RCLICK, IDC_WKS_TEMPLATELIST, OnRclickWksTemplatelist)
    ON_NOTIFY(NM_RDBLCLK, IDC_WKS_TEMPLATELIST, OnRdblclkWksTemplatelist)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WorkspaceTemplateDlg
//---------------------------------------------------------------------------
PSS_WorkspaceTemplateDlg::PSS_WorkspaceTemplateDlg(PSS_WorkspaceWizardTemplateManager* pWorkspaceTemplateManager, CWnd* pParent) :
    PSS_WizardDialog(PSS_WorkspaceTemplateDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_WORKSPACE_TMPL_S,
                     IDS_WZ_WORKSPACE_TMPL_T),
    m_pWorkspaceTemplateManager(pWorkspaceTemplateManager)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceTemplateDlg::~PSS_WorkspaceTemplateDlg()
{}
//---------------------------------------------------------------------------
void PSS_WorkspaceTemplateDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_WorkspaceTemplateDlg)
    DDX_Control(pDX, IDC_WKS_TEMPLATELIST, m_TemplateList);
    DDX_Text   (pDX, IDC_WKS_COMMENT,      m_Comment);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceTemplateDlg::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    m_TemplateList.Initialize(m_pWorkspaceTemplateManager);
    m_TemplateList.SetCurSel(0);
    SelChanged();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTemplateDlg::OnClickWksTemplatelist(NMHDR* pNMHDR, LRESULT* pResult)
{
    SelChanged();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTemplateDlg::OnDblclkWksTemplatelist(NMHDR* pNMHDR, LRESULT* pResult)
{
    SelChanged();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTemplateDlg::OnRclickWksTemplatelist(NMHDR* pNMHDR, LRESULT* pResult)
{
    SelChanged();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTemplateDlg::OnRdblclkWksTemplatelist(NMHDR* pNMHDR, LRESULT* pResult)
{
    SelChanged();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTemplateDlg::OnOK()
{
    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_WorkspaceTemplateDlg::SelChanged()
{
    PSS_WorkspaceWizardTemplateItem* pItem = m_TemplateList.GetSelectedItem();

    if (pItem)
    {
        m_Comment = pItem->GetTemplateDescription();
        UpdateData(FALSE);
    }
}
//---------------------------------------------------------------------------
