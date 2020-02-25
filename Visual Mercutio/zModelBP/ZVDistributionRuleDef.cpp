// ZVDistributionRuleDef.cpp : implementation file
//

#include "stdafx.h"
#include "ZVDistributionRuleDef.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "PSS_DistributionRules.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVDistributionRuleDef dialog


ZVDistributionRuleDef::ZVDistributionRuleDef(PSS_DistributionRule* pRule /*= NULL*/, CWnd* pParent /*= NULL*/)
    : CDialog(ZVDistributionRuleDef::IDD, pParent),
    m_pRule(pRule)
{
    //{{AFX_DATA_INIT(ZVDistributionRuleDef)
    m_Operator = 0;
    m_Value = _T("");
    m_LogicalOperator = 0;
    //}}AFX_DATA_INIT
}


void ZVDistributionRuleDef::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVDistributionRuleDef)
    DDX_CBIndex(pDX, IDC_OPERATOR_RULE, m_Operator);
    DDX_Text(pDX, IDC_VALUE_RULE, m_Value);
    DDX_CBIndex(pDX, IDC_LOGICALOPERATOR_RULE, m_LogicalOperator);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVDistributionRuleDef, CDialog)
    //{{AFX_MSG_MAP(ZVDistributionRuleDef)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVDistributionRuleDef message handlers

void ZVDistributionRuleDef::OnOK()
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

BOOL ZVDistributionRuleDef::OnInitDialog()
{
    if (m_pRule)
    {
        m_Value           = m_pRule->GetValue();
        m_Operator        = m_pRule->GetOperator();
        m_LogicalOperator = m_pRule->GetLogicalOperator() + 1;

    }

    CDialog::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
