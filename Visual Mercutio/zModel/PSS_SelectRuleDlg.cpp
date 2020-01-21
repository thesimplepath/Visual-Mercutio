/****************************************************************************
 * ==> PSS_SelectRuleDlg ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a select a rule dialog box                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectRuleDlg.h"

// processsoft
#include "PSS_LogicalRulesEntity.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectRuleDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_SelectRuleDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_RULES_TREE, OnSelchangedRulesTree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectRuleDlg
//---------------------------------------------------------------------------
PSS_SelectRuleDlg::PSS_SelectRuleDlg(const CString&          title,
                                     PSS_LogicalRulesEntity* pMainRule,
                                     bool                    allowRuleSelection,
                                     CWnd*                   pParent) :
    CDialog(PSS_SelectRuleDlg::IDD, pParent),
    m_pRuleEntity(NULL),
    m_pMainRule(pMainRule),
    m_Title(title),
    m_AllowRuleSelection(allowRuleSelection)
{}
//---------------------------------------------------------------------------
PSS_SelectRuleDlg::PSS_SelectRuleDlg(UINT                    titleID,
                                     PSS_LogicalRulesEntity* pMainRule,
                                     bool                    allowRuleSelection,
                                     CWnd*                   pParent) :
    CDialog(PSS_SelectRuleDlg::IDD, pParent),
    m_pRuleEntity(NULL),
    m_pMainRule(pMainRule),
    m_AllowRuleSelection(allowRuleSelection)
{
    m_Title.LoadString(titleID);
}
//---------------------------------------------------------------------------
PSS_SelectRuleDlg::~PSS_SelectRuleDlg()
{
    // NOTE the fully qualified name is used here to avoid to call a pure virtual function during the destruction
    Release();
}
//---------------------------------------------------------------------------
void PSS_SelectRuleDlg::Release()
{
    m_Title.Empty();
    m_Ctrl.Release();
}
//---------------------------------------------------------------------------
void PSS_SelectRuleDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectRuleDlg)
    DDX_Control(pDX, IDC_RULES_TREE, m_Ctrl);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectRuleDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    CString text;
    text.LoadString(IDS_RULE_ROOT_T);
    m_Ctrl.Initialize(text, m_pMainRule);

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(FALSE);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectRuleDlg::OnSelchangedRulesTree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(m_AllowRuleSelection &&
                                       dynamic_cast<PSS_LogicalRulesEntity*>(m_Ctrl.GetSelectedRuleEntity()));

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_SelectRuleDlg::OnOK()
{
    // save the selected item
    m_pRuleEntity = m_Ctrl.GetSelectedRuleEntity();

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
