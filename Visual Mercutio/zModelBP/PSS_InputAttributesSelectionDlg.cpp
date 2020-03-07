/****************************************************************************
 * ==> PSS_InputAttributesSelectionDlg -------------------------------------*
 ****************************************************************************
 * Description : Provides an input attributes selection dialog box          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InputAttributesSelectionDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InputAttributesSelectionDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_InputAttributesSelectionDlg)
    ON_NOTIFY(NM_CLICK, IDC_INPUTATTRIBUTE_LIST, OnClickInputattributeList)
    ON_NOTIFY(NM_DBLCLK, IDC_INPUTATTRIBUTE_LIST, OnDblclkInputattributeList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InputAttributesSelectionDlg
//---------------------------------------------------------------------------
PSS_InputAttributesSelectionDlg::PSS_InputAttributesSelectionDlg(PSS_InputAttributeManager*  pInputManager,
                                                                 ZBDynamicPropertiesManager* pPropManager,
                                                                 CWnd*                       pParent) :
    CDialog(PSS_InputAttributesSelectionDlg::IDD, pParent),
    m_pInputManager(pInputManager),
    m_pPropManager(pPropManager)
{}
//---------------------------------------------------------------------------
PSS_InputAttributesSelectionDlg::~PSS_InputAttributesSelectionDlg()
{}
//---------------------------------------------------------------------------
void PSS_InputAttributesSelectionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_InputAttributesSelectionDlg)
    DDX_Control(pDX, IDC_INPUTATTRIBUTE_LIST, m_List);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_InputAttributesSelectionDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_List.Initialize(m_pInputManager, m_pPropManager, true);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_InputAttributesSelectionDlg::OnClickInputattributeList(NMHDR* pNMHDR, LRESULT* pResult)
{
    CheckControlState();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_InputAttributesSelectionDlg::OnDblclkInputattributeList(NMHDR* pNMHDR, LRESULT* pResult)
{
    CheckControlState();
    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_InputAttributesSelectionDlg::OnOK()
{
    CDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_InputAttributesSelectionDlg::CheckControlState()
{
    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(GetSelectedInputAttribute() ? TRUE : FALSE);
}
//---------------------------------------------------------------------------
