/****************************************************************************
 * ==> PSS_DistributionAttributesSelectionDlg ------------------------------*
 ****************************************************************************
 * Description : Provides a distribution attributes selection dialog box    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DistributionAttributesSelectionDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DistributionAttributesSelectionDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_DistributionAttributesSelectionDlg)
    ON_NOTIFY(NM_CLICK, IDC_DISTRIBUTIONATTRIBUTE_LIST, OnClickDistribattributeList)
    ON_NOTIFY(NM_DBLCLK, IDC_DISTRIBUTIONATTRIBUTE_LIST, OnDblclkDistribattributeList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DistributionAttributesSelectionDlg
//---------------------------------------------------------------------------
PSS_DistributionAttributesSelectionDlg::PSS_DistributionAttributesSelectionDlg(PSS_DistributionAttributeManager* pDistribManager,
                                                                               ZBDynamicPropertiesManager*       pPropManager, 
                                                                               PSS_UserGroupEntity*              pMainUserGroup,
                                                                               CWnd*                             pParent) :
    CDialog(PSS_DistributionAttributesSelectionDlg::IDD, pParent),
    m_pDistribManager(pDistribManager),
    m_pPropManager(pPropManager),
    m_pMainUserGroup(pMainUserGroup)
{}
//---------------------------------------------------------------------------
PSS_DistributionAttributesSelectionDlg::~PSS_DistributionAttributesSelectionDlg()
{}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesSelectionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_DistributionAttributesSelectionDlg)
    DDX_Control(pDX, IDC_DISTRIBUTIONATTRIBUTE_LIST, m_List);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesSelectionDlg::OnOK()
{
    CDialog::OnOK();
}
//---------------------------------------------------------------------------
BOOL PSS_DistributionAttributesSelectionDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_List.Initialize(m_pDistribManager, m_pPropManager, m_pMainUserGroup, NULL, true);

    CheckControlState();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesSelectionDlg::OnClickDistribattributeList(NMHDR* pNMHDR, LRESULT* pResult)
{
    CheckControlState();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesSelectionDlg::OnDblclkDistribattributeList(NMHDR* pNMHDR, LRESULT* pResult)
{
    CheckControlState();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesSelectionDlg::CheckControlState()
{
    if (GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow(GetSelectedDistributionAttribute() || GetSelectedDistributionRule());
}
//---------------------------------------------------------------------------
