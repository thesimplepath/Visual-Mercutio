/****************************************************************************
 * ==> PSS_DistributionRuleDefDlg ------------------------------------------*
 ****************************************************************************
 * Description : Provides a distribution rule definition dialog box         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DistributionRuleDefDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "PSS_DistributionRules.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DistributionRuleDefDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_DistributionRuleDefDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DistributionRuleDefDlg
//---------------------------------------------------------------------------
PSS_DistributionRuleDefDlg::PSS_DistributionRuleDefDlg(PSS_DistributionRule* pRule, CWnd* pParent) :
    CDialog(PSS_DistributionRuleDefDlg::IDD, pParent),
    m_pRule(pRule),
    m_Operator(0),
    m_LogicalOperator(0)
{}
//---------------------------------------------------------------------------
PSS_DistributionRuleDefDlg::~PSS_DistributionRuleDefDlg()
{}
//---------------------------------------------------------------------------
void PSS_DistributionRuleDefDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_DistributionRuleDefDlg)
    DDX_CBIndex(pDX, IDC_OPERATOR_RULE,        m_Operator);
    DDX_Text   (pDX, IDC_VALUE_RULE,           m_Value);
    DDX_CBIndex(pDX, IDC_LOGICALOPERATOR_RULE, m_LogicalOperator);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_DistributionRuleDefDlg::OnInitDialog()
{
    if (m_pRule)
    {
        m_Value           = m_pRule->GetValue();
        m_Operator        = m_pRule->GetOperator();
        m_LogicalOperator = m_pRule->GetLogicalOperator() + 1;
    }

    CDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DistributionRuleDefDlg::OnOK()
{
    UpdateData(TRUE);

    if (m_Operator <= 0)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_OPERATORRULE_MISSING, MB_OK);
        return;
    }

    if (m_Value.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_OPERATORVALUE_MISSING, MB_OK);
        return;
    }

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
