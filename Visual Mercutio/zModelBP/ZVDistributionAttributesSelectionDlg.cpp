// ZVDistributionAttributesSelectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVDistributionAttributesSelectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVDistributionAttributesSelectionDlg dialog


ZVDistributionAttributesSelectionDlg::ZVDistributionAttributesSelectionDlg(ZBDistributionAttributeManager* pDistribManager, 
                                                                           ZBDynamicPropertiesManager* pPropManager, 
                                                                           ZBUserGroupEntity* pMainUserGroup,
                                                                           CWnd* pParent /*=NULL*/)
: CDialog(ZVDistributionAttributesSelectionDlg::IDD, pParent),
  m_pDistribManager(pDistribManager),
  m_pPropManager(pPropManager),
  m_pMainUserGroup(pMainUserGroup)
{
    //{{AFX_DATA_INIT(ZVDistributionAttributesSelectionDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void ZVDistributionAttributesSelectionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVDistributionAttributesSelectionDlg)
    DDX_Control(pDX, IDC_DISTRIBUTIONATTRIBUTE_LIST, m_List);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVDistributionAttributesSelectionDlg, CDialog)
    //{{AFX_MSG_MAP(ZVDistributionAttributesSelectionDlg)
    ON_NOTIFY(NM_CLICK, IDC_DISTRIBUTIONATTRIBUTE_LIST, OnClickDistribattributeList)
    ON_NOTIFY(NM_DBLCLK, IDC_DISTRIBUTIONATTRIBUTE_LIST, OnDblclkDistribattributeList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void ZVDistributionAttributesSelectionDlg::CheckControlState()
{
    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow( (GetSelectedDistributionAttribute() || GetSelectedDistributionRule()) ? TRUE : FALSE );
}


/////////////////////////////////////////////////////////////////////////////
// ZVDistributionAttributesSelectionDlg message handlers


BOOL ZVDistributionAttributesSelectionDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    m_List.Initialize( m_pDistribManager, m_pPropManager, m_pMainUserGroup, NULL, true );  
    
    CheckControlState();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void ZVDistributionAttributesSelectionDlg::OnClickDistribattributeList(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CheckControlState();
    
    *pResult = 0;
}

void ZVDistributionAttributesSelectionDlg::OnDblclkDistribattributeList(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CheckControlState();
    
    *pResult = 0;
}

void ZVDistributionAttributesSelectionDlg::OnOK() 
{
    // TODO: Add extra validation here
    
    CDialog::OnOK();
}

