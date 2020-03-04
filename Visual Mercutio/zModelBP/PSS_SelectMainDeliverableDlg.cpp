/****************************************************************************
 * ==> PSS_SelectMainDeliverableDlg ----------------------------------------*
 ****************************************************************************
 * Description : Provides a select the main deliverable dialog box          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectMainDeliverableDlg.h"

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
BEGIN_MESSAGE_MAP(PSS_SelectMainDeliverableDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_SelectMainDeliverableDlg)
    ON_LBN_SELCHANGE(IDC_LISTOFDELIVERABLE, OnSelchangeListOfDeliverable)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectMainDeliverableDlg
//---------------------------------------------------------------------------
PSS_SelectMainDeliverableDlg::PSS_SelectMainDeliverableDlg(const CString& deliverables,
                                                           const CString& main,
                                                           CWnd*          pParent) :
    CDialog(PSS_SelectMainDeliverableDlg::IDD, pParent),
    m_Deliverables(deliverables),
    m_Main(main)
{}
//---------------------------------------------------------------------------
PSS_SelectMainDeliverableDlg::~PSS_SelectMainDeliverableDlg()
{}
//---------------------------------------------------------------------------
void PSS_SelectMainDeliverableDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_SelectMainDeliverableDlg)
    DDX_Control(pDX, IDC_LISTOFDELIVERABLE, m_ListOfDeliverables);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectMainDeliverableDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    DelivToListBox(m_Deliverables, m_ListOfDeliverables);

    // set the maximum horizontal scroll
    m_ListOfDeliverables.SetHorizontalExtent(1000);

    CheckState();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectMainDeliverableDlg::OnSelchangeListOfDeliverable()
{
    CheckState();
}
//---------------------------------------------------------------------------
void PSS_SelectMainDeliverableDlg::OnOK()
{
    const int curSel = m_ListOfDeliverables.GetCurSel();

    if (curSel != LB_ERR)
        m_ListOfDeliverables.GetText(curSel, m_Main);

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_SelectMainDeliverableDlg::DelivToListBox(const CString& deliv, CListBox& lb)
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
void PSS_SelectMainDeliverableDlg::CheckState()
{
    const int curSel = m_ListOfDeliverables.GetCurSel();

    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(curSel != LB_ERR);
}
//---------------------------------------------------------------------------
