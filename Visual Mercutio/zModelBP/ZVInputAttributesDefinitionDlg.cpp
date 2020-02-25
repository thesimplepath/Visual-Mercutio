// ZVInputAttributesDefinitionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVInputAttributesDefinitionDlg.h"

#include "PSS_InputAttributes.h"
#include "zProperty\ZBDynamicPropertiesManager.h"

// Symbol Properties
#include "zPtyMgr\ZVChoosePropertyDlg.h"
#include "zModel\PSS_DynamicAttributesManipulator.h"

#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVInputAttributesDefinitionDlg dialog


ZVInputAttributesDefinitionDlg::ZVInputAttributesDefinitionDlg(ZBDynamicPropertiesManager* pPropManager, ZBPropertySet* pSet, PSS_InputAttribute* pInputAttr /*= NULL*/, CWnd* pParent /*=NULL*/)
    : CDialog(ZVInputAttributesDefinitionDlg::IDD, pParent),
    m_pPropManager(pPropManager),
    m_pSet(pSet),
    m_pInputAttr(pInputAttr),
    m_CategoryID(-1),
    m_ItemID(-1),
    m_Visibility(-1),
    m_Flag(-1)

{
    //{{AFX_DATA_INIT(ZVInputAttributesDefinitionDlg)
    m_DefaultValue = _T("");
    m_DynamicAttributeName = _T("");
    //}}AFX_DATA_INIT
}


void ZVInputAttributesDefinitionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVInputAttributesDefinitionDlg)
    DDX_Control(pDX, IDC_INPATTR_VISIBILITY, m_VisibilityList);
    DDX_Control(pDX, IDC_INPATTR_FLAG, m_FlagList);
    DDX_Text(pDX, IDC_INPATTR_DEFVALUE, m_DefaultValue);
    DDX_Text(pDX, IDC_DYNATTRIB, m_DynamicAttributeName);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVInputAttributesDefinitionDlg, CDialog)
    //{{AFX_MSG_MAP(ZVInputAttributesDefinitionDlg)
    ON_COMMAND(IDC_CHOOSE_DYNATTR, OnChooseDynAttr)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVInputAttributesDefinitionDlg message handlers

void ZVInputAttributesDefinitionDlg::OnOK()
{
    UpdateData(TRUE);

    if (m_DynamicAttributeName.IsEmpty())
    {
        // A dynamic attributes must be chosen
        PSS_MsgBox mBox;
        mBox.Show(IDS_DYNAMICATTRIBUTES_REQUIRED, MB_OK);

    }

    m_Visibility = m_VisibilityList.GetCurSel();
    m_Flag = m_FlagList.GetCurSel();

    CDialog::OnOK();
}

BOOL ZVInputAttributesDefinitionDlg::OnInitDialog()
{
    if (m_pInputAttr &&
        m_pPropManager)
    {
        ZBProperty*  pProp = m_pPropManager->GetPropertyItem(m_pInputAttr->GetCategoryID(), m_pInputAttr->GetItemID());

        if (pProp)
        {
            m_CategoryID = pProp->GetCategoryID();
            m_ItemID = pProp->GetItemID();
            m_DynamicAttributeName = pProp->GetLabel();
        }
        m_DefaultValue = m_pInputAttr->GetDefaultValue();
    }

    CDialog::OnInitDialog();

    if (m_pInputAttr)
    {
        if (GetDlgItem(IDC_CHOOSE_DYNATTR))
            GetDlgItem(IDC_CHOOSE_DYNATTR)->EnableWindow(FALSE);

        m_FlagList.SetCurSel(m_pInputAttr->GetFlag());
        m_VisibilityList.SetCurSel((m_pInputAttr->GetSymbolRef() != -1) ? 0 : 1);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVInputAttributesDefinitionDlg::OnChooseDynAttr()
{
    if (!m_pSet)
        return;

    ZVChoosePropertyDlg choose(m_pSet, 2);
    if (choose.DoModal() == IDOK)
    {
        ZBProperty* pProp = choose.GetSelectedProperty();
        if (pProp)
        {
            m_CategoryID = pProp->GetCategoryID();
            m_ItemID = pProp->GetItemID();
            m_DynamicAttributeName = pProp->GetLabel();

            // Push to dialog data
            UpdateData(FALSE);
        }

    }

}
