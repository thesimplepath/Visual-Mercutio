/****************************************************************************
 * ==> PSS_AddRemoveCombinationDeliverableDlg ------------------------------*
 ****************************************************************************
 * Description : Provides an add/remove deliverable combinations dialog box *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_AddRemoveCombinationDeliverableDlg.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_AddRemoveCombinationDeliverableDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_AddRemoveCombinationDeliverableDlg)
    ON_BN_CLICKED(IDC_ADD_DELIV, OnAddDeliv)
    ON_BN_CLICKED(IDC_DEL_DELIV, OnDelDeliv)
    ON_LBN_SELCHANGE(IDC_COMB_DELIV, OnSelchangeCombDeliv)
    ON_LBN_SELCHANGE(IDC_REMAIN_DELIV, OnSelchangeRemainDeliv)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_AddRemoveCombinationDeliverableDlg
//---------------------------------------------------------------------------
PSS_AddRemoveCombinationDeliverableDlg::PSS_AddRemoveCombinationDeliverableDlg(const CString& remainingDeliverables,
                                                                               const CString& deliverables,
                                                                               CWnd*          pParent) :
    CDialog(PSS_AddRemoveCombinationDeliverableDlg::IDD, pParent),
    m_Deliverables(deliverables),
    m_RemainingDeliverables(remainingDeliverables)
{}
//---------------------------------------------------------------------------
PSS_AddRemoveCombinationDeliverableDlg::~PSS_AddRemoveCombinationDeliverableDlg()
{}
//---------------------------------------------------------------------------
void PSS_AddRemoveCombinationDeliverableDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_AddRemoveCombinationDeliverableDlg)
    DDX_Control(pDX, IDC_COMB_DELIV,   m_CombinationDeliverablesLB);
    DDX_Control(pDX, IDC_REMAIN_DELIV, m_RemainingDeliverablesLB);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_AddRemoveCombinationDeliverableDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    DelivToListBox(m_RemainingDeliverables, m_RemainingDeliverablesLB);
    DelivToListBox(m_Deliverables,          m_CombinationDeliverablesLB);

    // set the maximum horizontal scroll
    m_CombinationDeliverablesLB.SetHorizontalExtent(1000);
    m_RemainingDeliverablesLB.SetHorizontalExtent(1000);

    CheckState();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_AddRemoveCombinationDeliverableDlg::OnAddDeliv()
{
    const int curSel = m_RemainingDeliverablesLB.GetCurSel();

    if (curSel != LB_ERR)
    {
        CString str;
        m_RemainingDeliverablesLB.GetText(curSel, str);
        AddStringToListBox(str, m_CombinationDeliverablesLB);
        RemoveStringFromListBox(str, m_RemainingDeliverablesLB);
    }

    CheckState();
}
//---------------------------------------------------------------------------
void PSS_AddRemoveCombinationDeliverableDlg::OnDelDeliv()
{
    const int curSel = m_CombinationDeliverablesLB.GetCurSel();

    if (curSel != LB_ERR)
    {
        CString str;
        m_CombinationDeliverablesLB.GetText(curSel, str);
        AddStringToListBox(str, m_RemainingDeliverablesLB);
        RemoveStringFromListBox(str, m_CombinationDeliverablesLB);
    }

    CheckState();
}
//---------------------------------------------------------------------------
void PSS_AddRemoveCombinationDeliverableDlg::OnSelchangeCombDeliv()
{
    CheckState();
}
//---------------------------------------------------------------------------
void PSS_AddRemoveCombinationDeliverableDlg::OnSelchangeRemainDeliv()
{
    CheckState();
}
//---------------------------------------------------------------------------
void PSS_AddRemoveCombinationDeliverableDlg::OnOK()
{
    ListBoxToString(m_CombinationDeliverablesLB, m_Deliverables);

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_AddRemoveCombinationDeliverableDlg::DelivToListBox(const CString& deliv, CListBox& lb)
{
    // initialize the token with ; as separator
    PSS_Tokenizer token;
    CString       str = token.GetFirstToken(deliv);

    // iterate through all tokens
    while (!str.IsEmpty())
    {
        // add the string to the list
        lb.AddString(str);

        // get the next token
        str = token.GetNextToken();
    }
}
//---------------------------------------------------------------------------
void PSS_AddRemoveCombinationDeliverableDlg::ListBoxToString(CListBox& lb, CString& deliv)
{
    // initialize the token with ; as separator
    PSS_Tokenizer token;
    CString       str;
    const int     count = lb.GetCount();

    // iterate through the list box elements and build the string
    for (int i = 0; i < count; ++i)
    {
        lb.GetText(i, str);
        token.AddToken(str);
    }

    // assign the return string
    deliv = token.GetString();
}
//---------------------------------------------------------------------------
void PSS_AddRemoveCombinationDeliverableDlg::AddStringToListBox(const CString& str, CListBox& lb)
{
    lb.AddString(str);
}
//---------------------------------------------------------------------------
void PSS_AddRemoveCombinationDeliverableDlg::RemoveStringFromListBox(const CString& str, CListBox& lb)
{
    const int index = lb.FindString(0, str);

    if (index != LB_ERR)
        lb.DeleteString(index);
}
//---------------------------------------------------------------------------
void PSS_AddRemoveCombinationDeliverableDlg::CheckState()
{
    int curSel = m_RemainingDeliverablesLB.GetCurSel();

    if (GetDlgItem(IDC_ADD_DELIV))
        GetDlgItem(IDC_ADD_DELIV)->EnableWindow(curSel != LB_ERR);

    curSel = m_CombinationDeliverablesLB.GetCurSel();

    if (GetDlgItem(IDC_DEL_DELIV))
        GetDlgItem(IDC_DEL_DELIV)->EnableWindow(curSel != LB_ERR);
}
//---------------------------------------------------------------------------
