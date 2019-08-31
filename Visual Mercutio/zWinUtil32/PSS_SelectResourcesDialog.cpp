/****************************************************************************
 * ==> PSS_SelectResourcesDialog -------------------------------------------*
 ****************************************************************************
 * Description : Provides a select resources dialog box                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectResourcesDialog.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\ZBTokenizer.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SelectResourcesDialog, ZIDialog)
    //{{AFX_MSG_MAP(PSS_SelectResourcesDialog)
    ON_BN_CLICKED(IDC_ADDRESOURCE, OnAddResource)
    ON_BN_CLICKED(IDC_REMOVERESOURCE, OnRemoveResource)
    ON_NOTIFY(TVN_SELCHANGED, IDC_RESOURCE_TREE, OnSelchangedResourceTree)
    ON_LBN_SELCHANGE(IDC_RESOURCE_LIST, OnSelchangeResourceList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SelectResourcesDialog
//---------------------------------------------------------------------------
PSS_SelectResourcesDialog::PSS_SelectResourcesDialog(PSS_UserManager& userManager, CWnd* pParent) :
    ZIDialog(PSS_SelectResourcesDialog::IDD, TRUE, pParent),
    m_UserManager(userManager)
{}
//---------------------------------------------------------------------------
void PSS_SelectResourcesDialog::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVChooseResources)
    DDX_Control(pDX, IDC_RESOURCE_TREE, m_ResourceTree);
    DDX_Control(pDX, IDC_RESOURCE_LIST, m_ResourceList);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_SelectResourcesDialog::OnInitDialog()
{
    ZIDialog::OnInitDialog();

    m_ResourceTree.Initialize(&m_UserManager);
    CheckControlState();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_SelectResourcesDialog::OnAddResource()
{
    // check if not null and not already in the list
    if (m_ResourceTree.GetSelectedUser() &&
        m_ResourceList.FindString(-1, m_ResourceTree.GetSelectedUser()->GetUserName()) == LB_ERR)
        m_ResourceList.AddString(m_ResourceTree.GetSelectedUser()->GetUserName());

    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_SelectResourcesDialog::OnRemoveResource()
{
    const int curSel = m_ResourceList.GetCurSel();

    if (curSel != LB_ERR)
        m_ResourceList.DeleteString(curSel);

    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_SelectResourcesDialog::OnSelchangedResourceTree(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    CheckControlState();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_SelectResourcesDialog::OnSelchangeResourceList()
{
    CheckControlState();
}
//---------------------------------------------------------------------------
void PSS_SelectResourcesDialog::OnOK()
{
    const int count = m_ResourceList.GetCount();

    if (count <= 0)
    {
        PSS_MsgBox mBox;

        // show warning message
        if (mBox.Show(IDS_LISTOFUSEREMPTY_CONTINUE, MB_YESNO) == IDNO)
            return;
    }

    m_UserListString.Empty();

    CString     text;
    ZBTokenizer tokenizer(';');

    // build the user string
    for (int index = 0; index < count; ++index)
    {
        m_ResourceList.GetText(index, text);
        tokenizer.AddToken(text);
    }

    m_UserListString = tokenizer.GetString();

    ZIDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_SelectResourcesDialog::CheckControlState()
{
    if (GetDlgItem(IDC_ADDRESOURCE))
       GetDlgItem(IDC_ADDRESOURCE)->EnableWindow(BOOL(m_ResourceTree.GetSelectedUser()));

    if (GetDlgItem(IDC_REMOVERESOURCE))
       GetDlgItem(IDC_REMOVERESOURCE)->EnableWindow(m_ResourceList.GetCurSel() != LB_ERR);
}
//---------------------------------------------------------------------------
