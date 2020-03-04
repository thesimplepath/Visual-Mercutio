/****************************************************************************
 * ==> PSS_AddRemoveDeliveryDeliverablesDlg --------------------------------*
 ****************************************************************************
 * Description : Provides an add/remove deliverable delivery dialog box     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_AddRemoveDeliveryDeliverablesDlg.h"

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
BEGIN_MESSAGE_MAP(PSS_AddRemoveDeliveryDeliverablesDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_AddRemoveDeliveryDeliverablesDlg)
    ON_BN_CLICKED(IDC_ADD_DELIV, OnAddDeliv)
    ON_BN_CLICKED(IDC_DEL_DELIV, OnDelDeliv)
    ON_LBN_SELCHANGE(IDC_SELECTED_DELIV, OnSelchangeSelectedDeliv)
    ON_LBN_SELCHANGE(IDC_AVAILABLE_DELIV, OnSelchangeAvailableDeliv)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_AddRemoveDeliveryDeliverablesDlg
//---------------------------------------------------------------------------
PSS_AddRemoveDeliveryDeliverablesDlg::PSS_AddRemoveDeliveryDeliverablesDlg(const CString& availableDeliverables,
                                                                           const CString& selectedDeliverables,
                                                                           CWnd*          pParent) :
    CDialog(PSS_AddRemoveDeliveryDeliverablesDlg::IDD, pParent),
    m_SelectedDeliverables(selectedDeliverables),
    m_AvailableDeliverables(availableDeliverables)
{}
//---------------------------------------------------------------------------
PSS_AddRemoveDeliveryDeliverablesDlg::~PSS_AddRemoveDeliveryDeliverablesDlg()
{}
//---------------------------------------------------------------------------
void PSS_AddRemoveDeliveryDeliverablesDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_AddRemoveDeliveryDeliverablesDlg)
    DDX_Control(pDX, IDC_SELECTED_DELIV,  m_SelectedDeliverablesLB);
    DDX_Control(pDX, IDC_AVAILABLE_DELIV, m_AvailableDeliverablesLB);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_AddRemoveDeliveryDeliverablesDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    DelivToListBox(m_AvailableDeliverables, m_AvailableDeliverablesLB);
    DelivToListBox(m_SelectedDeliverables,  m_SelectedDeliverablesLB);

    // set the maximum horizontal scroll
    m_SelectedDeliverablesLB.SetHorizontalExtent(1000);
    m_AvailableDeliverablesLB.SetHorizontalExtent(1000);

    CheckState();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_AddRemoveDeliveryDeliverablesDlg::OnAddDeliv()
{
    const int curSel = m_AvailableDeliverablesLB.GetCurSel();

    if (curSel != LB_ERR)
    {
        CString str;
        m_AvailableDeliverablesLB.GetText(curSel, str);

        if (!EntryExist(str))
            AddStringToListBox(str, m_SelectedDeliverablesLB);
    }

    CheckState();
}
//---------------------------------------------------------------------------
void PSS_AddRemoveDeliveryDeliverablesDlg::OnDelDeliv()
{
    const int curSel = m_SelectedDeliverablesLB.GetCurSel();

    if (curSel != LB_ERR)
    {
        CString str;
        m_SelectedDeliverablesLB.GetText(curSel, str);
        RemoveStringFromListBox(str, m_SelectedDeliverablesLB);
    }

    CheckState();
}
//---------------------------------------------------------------------------
void PSS_AddRemoveDeliveryDeliverablesDlg::OnSelchangeSelectedDeliv()
{
    CheckState();
}
//---------------------------------------------------------------------------
void PSS_AddRemoveDeliveryDeliverablesDlg::OnSelchangeAvailableDeliv()
{
    CheckState();
}
//---------------------------------------------------------------------------
void PSS_AddRemoveDeliveryDeliverablesDlg::OnOK()
{
    ListBoxToString(m_SelectedDeliverablesLB, m_SelectedDeliverables);

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_AddRemoveDeliveryDeliverablesDlg::DelivToListBox(const CString& deliv, CListBox& lb)
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
void PSS_AddRemoveDeliveryDeliverablesDlg::ListBoxToString(CListBox& lb, CString& deliv)
{
    // initialize the token with ; as separator
    PSS_Tokenizer token;
    CString       str;

    const int count = lb.GetCount();

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
void PSS_AddRemoveDeliveryDeliverablesDlg::AddStringToListBox(const CString& str, CListBox& lb)
{
    lb.AddString(str);
}
//---------------------------------------------------------------------------
void PSS_AddRemoveDeliveryDeliverablesDlg::RemoveStringFromListBox(const CString& str, CListBox& lb)
{
    const int index = lb.FindString(0, str);

    if (index != LB_ERR)
        lb.DeleteString(index);
}
//---------------------------------------------------------------------------
void PSS_AddRemoveDeliveryDeliverablesDlg::CheckState()
{
    int curSel = m_AvailableDeliverablesLB.GetCurSel();

    if (GetDlgItem(IDC_ADD_DELIV))
        GetDlgItem(IDC_ADD_DELIV)->EnableWindow(curSel != LB_ERR);

    curSel = m_SelectedDeliverablesLB.GetCurSel();

    if (GetDlgItem(IDC_DEL_DELIV))
        GetDlgItem(IDC_DEL_DELIV)->EnableWindow(curSel != LB_ERR);
}
//---------------------------------------------------------------------------
BOOL PSS_AddRemoveDeliveryDeliverablesDlg::EntryExist(const CString& entryValue)
{
    const int count = m_SelectedDeliverablesLB.GetCount();

    for (int i = 0; i < count; ++i)
    {
        CString compStr;
        m_SelectedDeliverablesLB.GetText(i, compStr);

        if (compStr == entryValue)
            return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
