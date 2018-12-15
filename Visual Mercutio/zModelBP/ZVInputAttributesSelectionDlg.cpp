// ZVInputAttributesSelectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVInputAttributesSelectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVInputAttributesSelectionDlg dialog


ZVInputAttributesSelectionDlg::ZVInputAttributesSelectionDlg(ZBInputAttributeManager* pInputManager, ZBDynamicPropertiesManager* pPropManager, CWnd* pParent /*=NULL*/)
: CDialog(ZVInputAttributesSelectionDlg::IDD, pParent),
  m_pInputManager(pInputManager),
  m_pPropManager(pPropManager)
{
    //{{AFX_DATA_INIT(ZVInputAttributesSelectionDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void ZVInputAttributesSelectionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVInputAttributesSelectionDlg)
    DDX_Control(pDX, IDC_INPUTATTRIBUTE_LIST, m_List);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVInputAttributesSelectionDlg, CDialog)
    //{{AFX_MSG_MAP(ZVInputAttributesSelectionDlg)
    ON_NOTIFY(NM_CLICK, IDC_INPUTATTRIBUTE_LIST, OnClickInputattributeList)
    ON_NOTIFY(NM_DBLCLK, IDC_INPUTATTRIBUTE_LIST, OnDblclkInputattributeList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void ZVInputAttributesSelectionDlg::CheckControlState()
{
    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow( (GetSelectedInputAttribute()) ? TRUE : FALSE );
}


/////////////////////////////////////////////////////////////////////////////
// ZVInputAttributesSelectionDlg message handlers


BOOL ZVInputAttributesSelectionDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    m_List.Initialize( m_pInputManager, m_pPropManager, true );  
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void ZVInputAttributesSelectionDlg::OnClickInputattributeList(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CheckControlState();
    
    *pResult = 0;
}

void ZVInputAttributesSelectionDlg::OnDblclkInputattributeList(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CheckControlState();
    
    *pResult = 0;
}

void ZVInputAttributesSelectionDlg::OnOK() 
{
    // TODO: Add extra validation here
    
    CDialog::OnOK();
}

