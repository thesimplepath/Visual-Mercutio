// ZVWorkspaceGroupNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVWorkspaceGroupNameDlg.h"

#include "ZBWorkspaceGroupEntity.h"

#include "PSS_MsgBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceGroupNameDlg dialog


ZVWorkspaceGroupNameDlg::ZVWorkspaceGroupNameDlg(ZBWorkspaceGroupEntity* pRootGroup /*= NULL*/,
                                                 const CString GroupName /*= ""*/,
                                                 const CString ExtensionList /*= ""*/,
                                                 CWnd* pParent /*=NULL*/)
    : CDialog(ZVWorkspaceGroupNameDlg::IDD, pParent),
    m_pRootGroup(pRootGroup)
{
    //{{AFX_DATA_INIT(ZVWorkspaceGroupNameDlg)
    m_Extensions = ExtensionList;
    m_GroupName = GroupName;
    //}}AFX_DATA_INIT

    m_Modify = (m_GroupName.IsEmpty()) ? false : true;
}


void ZVWorkspaceGroupNameDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVWorkspaceGroupNameDlg)
    DDX_Text(pDX, IDC_WKS_EXTENSIONS, m_Extensions);
    DDX_Text(pDX, IDC_WKS_GROUPNAME, m_GroupName);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVWorkspaceGroupNameDlg, CDialog)
    //{{AFX_MSG_MAP(ZVWorkspaceGroupNameDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceGroupNameDlg message handlers

void ZVWorkspaceGroupNameDlg::OnOK()
{
    UpdateData(TRUE);
    if (!m_Modify &&
        m_pRootGroup &&
        m_pRootGroup->GroupExist(m_GroupName))
    {
        // Already exists
        PSS_MsgBox mBox;
        mBox.Show(IDS_WKS_GROUP_ALREADYEXIST, MB_OK);
        return;
    }

    if (m_Extensions.FindOneOf(",.-/") != -1)
    {
        // Illegal char in extension set
        PSS_MsgBox mBox;
        mBox.Show(IDS_WKS_ILLEGAL_EXTENSION_LIST, MB_OK);
        return;
    }

    CDialog::OnOK();
}

BOOL ZVWorkspaceGroupNameDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (m_Modify)
    {
        if (GetDlgItem(IDC_WKS_GROUPNAME))
            GetDlgItem(IDC_WKS_GROUPNAME)->EnableWindow(FALSE);
        // Change the title for properties
        CString s;
        s.LoadString(IDS_WKS_PROPGROUP_T);
        SetWindowText(s);
    }

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
