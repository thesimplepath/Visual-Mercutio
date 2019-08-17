// ZVUserGroupInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVUserGroupInfoDlg.h"

#include "ZBUserGroupEntity.h"

#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVUserGroupInfoDlg dialog


ZVUserGroupInfoDlg::ZVUserGroupInfoDlg(UINT nTitleID /*= -1*/,
                                       ZBUserGroupEntity* pGroup /*= NULL*/,
                                       const CString Name /*= ""*/,
                                       const CString Description /*= ""*/,
                                       const float Cost /*= 0*/,
                                       bool IsARole /*= false*/,
                                       bool ModifyMode /*= false*/,
                                       CWnd* pParent /*=NULL*/)
    : CDialog(ZVUserGroupInfoDlg::IDD, pParent),
    m_pGroup(pGroup), m_IsARole(IsARole), m_ModifyMode(ModifyMode)
{
    //{{AFX_DATA_INIT(ZVUserGroupInfoDlg)
    m_Description = Description;
    m_Name = Name;
    if (m_IsARole)
        m_Cost = _T("");
    else
        m_Cost.Format("%3.2f", Cost);
    //}}AFX_DATA_INIT
    // Assigns also the initial cost
    m_fCost = Cost;
    if (nTitleID != -1)
        m_Title.LoadString(nTitleID);
}


void ZVUserGroupInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVUserGroupInfoDlg)
    DDX_Text(pDX, IDC_UGP_DESCRIPTION, m_Description);
    DDX_Text(pDX, IDC_UGP_NAME, m_Name);
    DDX_Text(pDX, IDC_UGP_COST, m_Cost);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVUserGroupInfoDlg, CDialog)
    //{{AFX_MSG_MAP(ZVUserGroupInfoDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVUserGroupInfoDlg message handlers

void ZVUserGroupInfoDlg::OnOK()
{
    UpdateData(TRUE);
    if (!m_ModifyMode)
    {
        if (m_pGroup && m_pGroup->GroupExist(m_Name))
        {
            // Already exists
            PSS_MsgBox mBox;
            mBox.Show(IDS_UGP_GROUP_ALREADYEXIST, MB_OK);
            return;
        }
    }
    // If not a role, converts the cost entered
    if (!m_IsARole)
        m_fCost = static_cast<float>(atof(m_Cost));

    CDialog::OnOK();
}

BOOL ZVUserGroupInfoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (!m_Title.IsEmpty())
        SetWindowText(m_Title);

    // Cost is not allowed for a role
    if (m_IsARole)
    {
        if (GetDlgItem(IDC_COST_STATIC))
            GetDlgItem(IDC_COST_STATIC)->EnableWindow(FALSE);
        if (GetDlgItem(IDC_UGP_COST))
            GetDlgItem(IDC_UGP_COST)->EnableWindow(FALSE);
    }
    if (m_ModifyMode)
    {
        if (GetDlgItem(IDC_UGP_NAME))
            GetDlgItem(IDC_UGP_NAME)->EnableWindow(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
