/****************************************************************************
 * ==> PSS_PublishModelSelDirDialog ----------------------------------------*
 ****************************************************************************
 * Description : Dialog box allowing to select the model publication dir    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PublishModelSelDirDialog.h"

// processsoft
#include "zBaseLib\ZDirectory.h"
#include "zBaseLib\PSS_MsgBox.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message loop
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PublishModelSelDirDialog, ZIWizardDialog)
    //{{AFX_MSG_MAP(ZVPublishModelSelectDirectory)
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREEOFDIRECTORY, OnSelchangedDirectory)
    ON_NOTIFY(NM_DBLCLK, IDC_TREEOFDIRECTORY, OnDblclkDirectory)
    ON_NOTIFY(NM_CLICK, IDC_TREEOFDIRECTORY, OnClickDirectory)
    ON_EN_CHANGE(IDC_DIRECTORYCHOOSED, OnChangeServerChoosed)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PublishModelSelDirDialog
//---------------------------------------------------------------------------
PSS_PublishModelSelDirDialog::PSS_PublishModelSelDirDialog(const CString& lastPathName,
                                                           CStringArray*  pArrayOfAddress,
                                                           CWnd*          pParent) :
    ZIWizardDialog(PSS_PublishModelSelDirDialog::IDD,
                   IDB_WZBMP1,
                   0,
                   0,
                   IDS_PUBLISHMODELSELDIR_S,
                   IDS_PUBLISHMODELSELDIR_T),
    m_Directory(lastPathName),
    m_pArrayOfAddress(pArrayOfAddress)
{}
//---------------------------------------------------------------------------
void PSS_PublishModelSelDirDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PublishModelSelDirDialog)
    DDX_Control(pDX, IDC_TREEOFDIRECTORY,  m_DirTreeCtrl);
    DDX_Control(pDX, IDC_DIRECTORYCHOOSED, m_CbDirectory);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_PublishModelSelDirDialog::CheckControlStates()
{
    UpdateData();

    if (GetDlgItem(IDOK))
    {
        m_CbDirectory.GetWindowText(m_Directory);
        GetDlgItem(IDOK)->EnableWindow(!m_DirTreeCtrl.GetSelectedDirectory().IsEmpty() || !m_Directory.IsEmpty());
    }
}
//---------------------------------------------------------------------------
void PSS_PublishModelSelDirDialog::ReflectChangedDirectory()
{
    CheckControlStates();

    if (m_DirTreeCtrl.IsValid())
    {
        m_Directory = m_DirTreeCtrl.GetSelectedDirectory();
        m_CbDirectory.SetWindowText(m_Directory);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_PublishModelSelDirDialog::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();
    
    // initialize the directory tree control
    m_DirTreeCtrl.Initialize();

    // load the address edit
    m_CbDirectory.Initialize(m_pArrayOfAddress);
    m_CbDirectory.SetWindowText(m_Directory);

    CheckControlStates();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PublishModelSelDirDialog::OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult)
{
    ReflectChangedDirectory();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_PublishModelSelDirDialog::OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult)
{
    ReflectChangedDirectory();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_PublishModelSelDirDialog::OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult)
{
    ReflectChangedDirectory();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_PublishModelSelDirDialog::OnChangeServerChoosed()
{
    CheckControlStates();
}
//---------------------------------------------------------------------------
void PSS_PublishModelSelDirDialog::OnOK()
{
    UpdateData(TRUE);
    m_CbDirectory.GetWindowText(m_Directory);

    if (!ZDirectory::Exist(m_Directory))
    {
        PSS_MsgBox mBox;

        // ask the user to create the directory
        if (mBox.Show(IDS_DIR_NEEDCREATE, MB_YESNO) == IDNO)
            return;

        // try to create it
        ZDirectory::CreateDirectory(m_Directory);

        // if still not created, show an error message
        if (!ZDirectory::Exist(m_Directory))
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_DIR_FAILCREATE, MB_OK);
            return;
        }
    }

    ZIWizardDialog::OnOK();
}
//---------------------------------------------------------------------------
