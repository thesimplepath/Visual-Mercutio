/****************************************************************************
 * ==> PSS_SelectLogicalSystemDlg ------------------------------------------*
 ****************************************************************************
 * Description : Provides a select logical system dialog box                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectLogicalSystemDlg.h"

// processsoft
#include "PSS_LogicalSystemEntity.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectLogicalSystemDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_SelectLogicalSystemDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_LOGICALSYSTEM_TREE, OnSelchangedLogicalSystemTree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectLogicalSystemDlg
//---------------------------------------------------------------------------
PSS_SelectLogicalSystemDlg::PSS_SelectLogicalSystemDlg(const CString&           title,
                                                       PSS_LogicalSystemEntity* pMainLogicalSystemGroup,
                                                       CWnd*                    pParent) :
    CDialog(PSS_SelectLogicalSystemDlg::IDD, pParent),
    m_pMainLogicalSystemGroup(pMainLogicalSystemGroup),
    m_pSystemEntity(NULL),
    m_Title(title)
{}
//---------------------------------------------------------------------------
PSS_SelectLogicalSystemDlg::PSS_SelectLogicalSystemDlg(UINT                     titleID,
                                                       PSS_LogicalSystemEntity* pMainLogicalSystemGroup,
                                                       CWnd*                    pParent) :
    CDialog(PSS_SelectLogicalSystemDlg::IDD, pParent),
    m_pMainLogicalSystemGroup(pMainLogicalSystemGroup),
    m_pSystemEntity(NULL)
{
    m_Title.LoadString(titleID);
}
//---------------------------------------------------------------------------
PSS_SelectLogicalSystemDlg::~PSS_SelectLogicalSystemDlg()
{
    // NOTE the fully qualified name is used here to avoid to call a pure virtual function during the destruction
    PSS_SelectLogicalSystemDlg::Release();
}
//---------------------------------------------------------------------------
void PSS_SelectLogicalSystemDlg::Release()
{
    m_Title.Empty();
    m_Ctrl.Release();
}
//---------------------------------------------------------------------------
void PSS_SelectLogicalSystemDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectLogicalSystemDlg)
    DDX_Control(pDX, IDC_LOGICALSYSTEM_TREE, m_Ctrl);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectLogicalSystemDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    CString text;
    text.LoadString(IDS_LOGICALSYSTEM_ROOT_T);
    m_Ctrl.Initialize(text, m_pMainLogicalSystemGroup);

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(FALSE);

    // return TRUE unless you set the focus to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectLogicalSystemDlg::OnSelchangedLogicalSystemTree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(m_Ctrl.GetSelectedSystemEntity() != NULL);

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_SelectLogicalSystemDlg::OnOK()
{
    // save the selected item
    m_pSystemEntity = m_Ctrl.GetSelectedSystemEntity();

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
