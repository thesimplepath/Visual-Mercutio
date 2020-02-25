// ZVDistributionAttributesDefinitionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVDistributionAttributesDefinitionDlg.h"

#include "PSS_DistributionAttributes.h"
#include "zProperty\ZBDynamicPropertiesManager.h"

#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_UserRoleEntity.h"
#include "zModel\PSS_SelectUserGroupDlg.h"

#include "ZVDistributionRuleDef.h"

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
// ZVDistributionAttributesDefinitionDlg dialog


ZVDistributionAttributesDefinitionDlg::ZVDistributionAttributesDefinitionDlg(PSS_DistributionAttributeManager* pDistributionManager,
                                                                             ZBDynamicPropertiesManager* pPropManager,
                                                                             ZBPropertySet* pSet,
                                                                             PSS_UserGroupEntity* pMainUserGroup,
                                                                             const CString GroupGUID /*= ""*/,
                                                                             PSS_DistributionAttribute* pDistributionAttr /*= NULL*/,
                                                                             CWnd* pParent /*=NULL*/)
    : CDialog(ZVDistributionAttributesDefinitionDlg::IDD, pParent),
    m_pDistributionManager(pDistributionManager),
    m_pPropManager(pPropManager),
    m_pSet(pSet),
    m_pMainUserGroup(pMainUserGroup),
    m_GroupGUID(GroupGUID),
    m_pDistributionAttr(pDistributionAttr),
    m_Allocated(false)

{
    //{{AFX_DATA_INIT(ZVDistributionAttributesDefinitionDlg)
    m_DynamicAttributeName = _T("");
    m_GroupName = _T("");
    //}}AFX_DATA_INIT
}

ZVDistributionAttributesDefinitionDlg::~ZVDistributionAttributesDefinitionDlg()
{
    if (m_Allocated &&
        m_pDistributionAttr)
    {
        delete m_pDistributionAttr;
        m_pDistributionAttr = NULL;
    }
}

void ZVDistributionAttributesDefinitionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVDistributionAttributesDefinitionDlg)
    DDX_Control(pDX, IDC_DISTRIBLIST, m_List);
    DDX_Text(pDX, IDC_DYNATTRIB, m_DynamicAttributeName);
    DDX_Text(pDX, IDC_USERGROUPNAME, m_GroupName);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVDistributionAttributesDefinitionDlg, CDialog)
    //{{AFX_MSG_MAP(ZVDistributionAttributesDefinitionDlg)
    ON_BN_CLICKED(IDC_CHOOSE_DYNATTR, OnChooseDynattr)
    ON_BN_CLICKED(IDC_CHOOSE_USERGROUP, OnChooseUsergroup)
    ON_BN_CLICKED(IDC_ADDRULE_BUTTON, OnAddruleButton)
    ON_BN_CLICKED(IDC_DELRULE_BUTTON, OnDelruleButton)
    ON_BN_CLICKED(IDC_MODRULE_BUTTON, OnModruleButton)
    ON_NOTIFY_EX(NM_CLICK, IDC_DISTRIBLIST, (BOOL(CCmdTarget::*)(UINT, NMHDR *, LRESULT *))OnClickDistriblist)
    ON_NOTIFY_EX(NM_DBLCLK, IDC_DISTRIBLIST, (BOOL(CCmdTarget::*)(UINT, NMHDR *, LRESULT *))OnDblclkDistriblist)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


void ZVDistributionAttributesDefinitionDlg::CheckControlState()
{
    /*
    if (GetDlgItem(IDC_DELRULE_BUTTON))
        GetDlgItem(IDC_DELRULE_BUTTON)->EnableWindow( (GetSelectedDistributionRule()) ? TRUE : FALSE );
    if (GetDlgItem(IDC_MODRULE_BUTTON))
        GetDlgItem(IDC_MODRULE_BUTTON)->EnableWindow( (GetSelectedDistributionRule()) ? TRUE : FALSE );

    if (GetDlgItem(IDC_ADDRULE_BUTTON))
        GetDlgItem(IDC_ADDRULE_BUTTON)->EnableWindow( (GetSelectedDistributionRuleForRole()) ? TRUE : FALSE );
    */
}

/////////////////////////////////////////////////////////////////////////////
// ZVDistributionAttributesDefinitionDlg message handlers

void ZVDistributionAttributesDefinitionDlg::OnOK()
{
    if (m_DynamicAttributeName.IsEmpty())
    {
        // A dynamic attributes must be chosen
        PSS_MsgBox mBox;
        mBox.Show(IDS_DYNAMICATTRIBUTES_REQUIRED, MB_OK);
        return;
    }

    if (m_GroupName.IsEmpty())
    {
        // A group must be chosen
        PSS_MsgBox mBox;
        mBox.Show(IDS_DISTRIBUTIONGROUP_REQUIRED, MB_OK);
        return;
    }

    CDialog::OnOK();
}

BOOL ZVDistributionAttributesDefinitionDlg::OnInitDialog()
{
    if (!m_pDistributionAttr)
    {
        m_Allocated = true;
        m_pDistributionAttr = new PSS_DistributionAttribute();
        // If we do have a group defined
        // then assign the group id to the distribution attribute
        if (!m_GroupGUID.IsEmpty() &&
            m_pDistributionAttr)
            m_pDistributionAttr->SetUserGroupGUID(m_GroupGUID);
    }
    if (m_pDistributionAttr &&
        m_pPropManager)
    {
        ZBProperty*  pProp = m_pPropManager->GetPropertyItem(m_pDistributionAttr->GetCategoryID(), m_pDistributionAttr->GetItemID());

        if (pProp)
        {
            m_CategoryID = pProp->GetCategoryID();
            m_ItemID = pProp->GetItemID();
            m_DynamicAttributeName = pProp->GetLabel();
        }

        // First level is the role name
        PSS_UserEntity* pEntity = m_pMainUserGroup->FindGroupByGUID(m_pDistributionAttr->GetUserGroupGUID(), true);
        m_GroupName = (pEntity) ? pEntity->GetEntityName() : _T("");

        // When starting, check the distribution role for a given distribution attribute
        m_pDistributionManager->CheckDistributionRole(m_pDistributionAttr, m_pMainUserGroup);

    }

    CDialog::OnInitDialog();

    m_List.Initialize(m_pDistributionManager, m_pPropManager, m_pMainUserGroup, m_pDistributionAttr, true);

    if (!m_Allocated)
    {
        if (GetDlgItem(IDC_CHOOSE_DYNATTR))
            GetDlgItem(IDC_CHOOSE_DYNATTR)->EnableWindow(FALSE);
        if (GetDlgItem(IDC_CHOOSE_USERGROUP))
            GetDlgItem(IDC_CHOOSE_USERGROUP)->EnableWindow(FALSE);

    }
    else
        if (!m_GroupGUID.IsEmpty())
        {
            if (GetDlgItem(IDC_CHOOSE_USERGROUP))
                GetDlgItem(IDC_CHOOSE_USERGROUP)->EnableWindow(FALSE);
        }

    CheckControlState();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void ZVDistributionAttributesDefinitionDlg::OnChooseDynattr()
{
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

void ZVDistributionAttributesDefinitionDlg::OnChooseUsergroup()
{
    if (!m_pMainUserGroup ||
        !m_pDistributionManager)
        return;

    PSS_SelectUserGroupDlg choose(IDS_CHOOSEDISTRIBGROUP_TITLE, m_pMainUserGroup,
                                true, // Allow group selection
                                false);    // Allow role selection
    if (choose.DoModal() == IDOK)
    {
        PSS_UserEntity* pEntity = choose.GetSelectedUserEntity();
        if (pEntity &&
            ISA(pEntity, PSS_UserGroupEntity))
        {
            m_GroupName = pEntity->GetEntityName();
            m_GroupGUID = pEntity->GetGUID();
            m_pDistributionAttr->SetUserGroupGUID(m_GroupGUID);


            int Size = dynamic_cast<PSS_UserGroupEntity*>(pEntity)->GetEntityCount();
            bool FoundCount = false;
            for (int i = 0; i < Size; ++i)
            {
                PSS_UserEntity* pUserEntity = dynamic_cast<PSS_UserGroupEntity*>(pEntity)->GetEntityAt(i);

                if (ISA(pUserEntity, PSS_UserRoleEntity))
                {
                    FoundCount = true;
                    break;
                }

            }
            // Fill the roles by default
            if (FoundCount)
            {
                // When starting, check the distribution role for a given distribution attribute
                m_pDistributionManager->CheckDistributionRole(m_pDistributionAttr, m_pMainUserGroup);
            }
            else
            {
                PSS_MsgBox mBox;
                mBox.Show(IDS_USERGROUP_HASNOROLE, MB_OK);
            }

            // Push to dialog data
            UpdateData(FALSE);

            m_List.Refresh();
        }
    }
}

void ZVDistributionAttributesDefinitionDlg::OnAddruleButton()
{
    PSS_DistributionRulesForRole* pRole = GetSelectedDistributionRuleForRole();
    if (!pRole)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_SELECTROLE_MSG, MB_OK);
        return;
    }
    ASSERT(m_pDistributionAttr);

    ZVDistributionRuleDef dlg;
    if (dlg.DoModal() == IDOK)
    {
        m_pDistributionAttr->AddDistributionRulesForRole(pRole->GetRoleGUID(), dlg.GetOperator(), dlg.GetValue(), dlg.GetLogicalOperator() - 1);
        // Refresh the list
        m_List.Refresh();
    }
}

void ZVDistributionAttributesDefinitionDlg::OnDelruleButton()
{
    PSS_DistributionRule* pRule = GetSelectedDistributionRule();

    if (!pRule)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_SELECTRULE_MSG, MB_OK);
        return;
    }

    PSS_MsgBox mBox;

    if (mBox.Show(IDS_DELETERULE_CONFIRM, MB_YESNO) == IDYES)
    {
        m_pDistributionManager->DeleteDistributionRule(pRule);
        // Refresh the list
        m_List.Refresh();
    }
}

void ZVDistributionAttributesDefinitionDlg::OnModruleButton()
{
    PSS_DistributionRule* pRule = GetSelectedDistributionRule();

    if (!pRule)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_SELECTRULE_MSG, MB_OK);
        return;
    }

    ZVDistributionRuleDef dlg(pRule);

    if (dlg.DoModal() == IDOK)
    {
        pRule->SetOperator(dlg.GetOperator());
        pRule->SetValue(dlg.GetValue());
        pRule->SetLogicalOperator(dlg.GetLogicalOperator() - 1);
        // Refresh the list
        m_List.Refresh();
    }
}

void ZVDistributionAttributesDefinitionDlg::OnClickDistriblist(NMHDR* pNMHDR, LRESULT* pResult)
{
    CheckControlState();

    *pResult = 0;
}

void ZVDistributionAttributesDefinitionDlg::OnDblclkDistriblist(NMHDR* pNMHDR, LRESULT* pResult)
{
    CheckControlState();

    *pResult = 0;
}
