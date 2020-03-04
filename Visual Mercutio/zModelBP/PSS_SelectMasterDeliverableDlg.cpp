/****************************************************************************
 * ==> PSS_SelectMasterDeliverableDlg --------------------------------------*
 ****************************************************************************
 * Description : Provides a select the master deliverable dialog box        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectMasterDeliverableDlg.h"

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
BEGIN_MESSAGE_MAP(PSS_SelectMasterDeliverableDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_SelectMasterDeliverableDlg)
    ON_LBN_SELCHANGE(IDC_LISTOFDELIVERABLE, OnSelchangeListOfDeliverable)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectMasterDeliverableDlg
//---------------------------------------------------------------------------
PSS_SelectMasterDeliverableDlg::PSS_SelectMasterDeliverableDlg(const CString& deliverables,
                                                               const CString& master,
                                                               CWnd*          pParent) :
    CDialog(PSS_SelectMasterDeliverableDlg::IDD, pParent),
    m_Deliverables(deliverables),
    m_Master(master)
{}
//---------------------------------------------------------------------------
PSS_SelectMasterDeliverableDlg::~PSS_SelectMasterDeliverableDlg()
{}
//---------------------------------------------------------------------------
void PSS_SelectMasterDeliverableDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectMasterDeliverableDlg)
    DDX_Control(pDX, IDC_LISTOFDELIVERABLE, m_ListOfDeliverables);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectMasterDeliverableDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    DelivToListBox(m_Deliverables, m_ListOfDeliverables);

    // set the maximum horizontal scroll
    m_ListOfDeliverables.SetHorizontalExtent(1000);

    CheckState();

    // return TRUE unless you set the focus to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectMasterDeliverableDlg::OnSelchangeListOfDeliverable()
{
    CheckState();
}
//---------------------------------------------------------------------------
void PSS_SelectMasterDeliverableDlg::OnOK()
{
    const int curSel = m_ListOfDeliverables.GetCurSel();

    if (curSel != LB_ERR)
        m_ListOfDeliverables.GetText(curSel, m_Master);

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_SelectMasterDeliverableDlg::DelivToListBox(const CString& deliv, CListBox& lb)
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
void PSS_SelectMasterDeliverableDlg::CheckState()
{
    const int curSel = m_ListOfDeliverables.GetCurSel();

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(curSel != LB_ERR);
}
//---------------------------------------------------------------------------
