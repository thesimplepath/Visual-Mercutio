/****************************************************************************
 * ==> PSS_SelectServerDialog ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a select a server dialog box                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectServerDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectServerDialog, ZIWizardDialog)
    //{{AFX_MSG_MAP(PSS_SelectServerDialog)
    ON_NOTIFY(TVN_SELCHANGED, IDC_SERVERDIRECTORY, OnSelchangedDirectory)
    ON_NOTIFY(NM_DBLCLK, IDC_SERVERDIRECTORY, OnDblclkDirectory)
    ON_NOTIFY(NM_CLICK, IDC_SERVERDIRECTORY, OnClickDirectory)
    ON_EN_CHANGE(IDC_SERVERCHOOSED, OnServerSelected)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectServerDialog
//---------------------------------------------------------------------------
PSS_SelectServerDialog::PSS_SelectServerDialog(BOOL local, CWnd* pParent) :
    ZIWizardDialog(PSS_SelectServerDialog::IDD,
                   IDB_WZBMP3,
                   0,
                   0,
                   IDS_SELECTIONSERVERWLC_SL,
                   IDS_SELECTIONSERVERWLC_TL),
    m_Local(local)
{
    if (!m_Local)
    {
        SetWizardSubjectText(IDS_SELECTIONSERVERWLC_SG);
        SetWizardBodyText(IDS_SELECTIONSERVERWLC_TG);
    }
}
//---------------------------------------------------------------------------
void PSS_SelectServerDialog::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );

    //{{AFX_DATA_MAP(PSS_SelectServerDialog)
    DDX_Control(pDX, IDC_SERVERDIRECTORY, m_DirTreeCtrl);
    DDX_Text   (pDX, IDC_SERVERCHOOSED,   m_Directory);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectServerDialog::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    m_DirTreeCtrl.Initialize();
    CheckControlStates();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectServerDialog::OnSelchangedDirectory(NMHDR* pNMHDR, LRESULT* pResult)
{
    ReflectChangedDirectory();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_SelectServerDialog::OnClickDirectory(NMHDR* pNMHDR, LRESULT* pResult)
{
    ReflectChangedDirectory();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_SelectServerDialog::OnDblclkDirectory(NMHDR* pNMHDR, LRESULT* pResult)
{
    ReflectChangedDirectory();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_SelectServerDialog::OnServerSelected()
{
    // todo -cFeature -oJean: if this is a RICHEDIT control, it will not send this notification unless overridding
    //                        the ZIDialog::OnInitDialog() function and calling CRichEditCtrl().SetEventMask()
    //                        with the ENM_CHANGE flag set in the mask
    CheckControlStates();
}
//---------------------------------------------------------------------------
void PSS_SelectServerDialog::OnOK()
{
    m_Directory = m_DirTreeCtrl.GetSelectedDirectory();
    ZIWizardDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_SelectServerDialog::CheckControlStates()
{
    UpdateData();

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(!m_DirTreeCtrl.GetSelectedDirectory().IsEmpty() || !m_Directory.IsEmpty());
}
//---------------------------------------------------------------------------
void PSS_SelectServerDialog::ReflectChangedDirectory()
{
    CheckControlStates();

    if (m_DirTreeCtrl.IsValid())
    {
        m_Directory = m_DirTreeCtrl.GetSelectedDirectory();
        UpdateData(FALSE);
    }
}
//---------------------------------------------------------------------------
