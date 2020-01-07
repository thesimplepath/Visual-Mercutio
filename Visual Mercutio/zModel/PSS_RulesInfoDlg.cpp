/****************************************************************************
 * ==> PSS_RulesInfoDlg ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a rules information dialog box                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RulesInfoDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\zBaseLibRes.h"
#include "PSS_LogicalRulesEntity.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_RulesInfoDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_RulesInfoDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_RulesInfoDlg
//---------------------------------------------------------------------------
PSS_RulesInfoDlg::PSS_RulesInfoDlg(UINT                    titleID,
                                   PSS_LogicalRulesEntity* pLogicalRule,
                                   const CString&          name,
                                   const CString&          description,
                                   bool                    modifyMode,
                                   CWnd*                   pParent) :
    CDialog(PSS_RulesInfoDlg::IDD, pParent),
    m_pRule(pLogicalRule),
    m_Name(name),
    m_Description(description),
    m_ModifyMode(modifyMode)
{
    // set the title
    if (titleID != -1)
        m_Title.LoadString(titleID);
}
//---------------------------------------------------------------------------
PSS_RulesInfoDlg::~PSS_RulesInfoDlg()
{}
//---------------------------------------------------------------------------
void PSS_RulesInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_RulesInfoDlg)
    DDX_Text(pDX, IDC_RULE_NAME,        m_Name);
    DDX_Text(pDX, IDC_RULE_DESCRIPTION, m_Description);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_RulesInfoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    if (m_ModifyMode)
    {
        CWnd* pItem = GetDlgItem(IDC_RULE_NAME);

        if (pItem)
            pItem->EnableWindow(FALSE);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_RulesInfoDlg::OnOK()
{
    UpdateData(TRUE);

    if (!m_ModifyMode)
        if (m_pRule && m_pRule->RuleExist(m_Name))
        {
            // already exists
            PSS_MsgBox mBox;
            mBox.Show(IDS_RULE_ALREADYEXIST, MB_OK);
            return;
        }

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
