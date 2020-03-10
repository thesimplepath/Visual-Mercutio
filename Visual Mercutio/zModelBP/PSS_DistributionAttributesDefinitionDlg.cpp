/****************************************************************************
 * ==> PSS_DistributionAttributesDefinitionDlg -----------------------------*
 ****************************************************************************
 * Description : Provides a distribution attributes definition dialog box   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DistributionAttributesDefinitionDlg.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_UserRoleEntity.h"
#include "zModel\PSS_SelectUserGroupDlg.h"
#include "zModel\PSS_DynamicAttributesManipulator.h"
#include "zProperty\PSS_DynamicPropertiesManager.h"
#include "zPtyMgr\ZVChoosePropertyDlg.h"
#include "PSS_DistributionAttributes.h"
#include "PSS_DistributionRuleDefDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DistributionAttributesDefinitionDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_DistributionAttributesDefinitionDlg)
    ON_BN_CLICKED(IDC_CHOOSE_DYNATTR, OnChooseDynattr)
    ON_BN_CLICKED(IDC_CHOOSE_USERGROUP, OnChooseUsergroup)
    ON_BN_CLICKED(IDC_ADDRULE_BUTTON, OnAddruleButton)
    ON_BN_CLICKED(IDC_DELRULE_BUTTON, OnDelruleButton)
    ON_BN_CLICKED(IDC_MODRULE_BUTTON, OnModruleButton)
    ON_NOTIFY_EX(NM_CLICK, IDC_DISTRIBLIST, (BOOL(CCmdTarget::*)(UINT, NMHDR *, LRESULT *))OnClickDistriblist)
    ON_NOTIFY_EX(NM_DBLCLK, IDC_DISTRIBLIST, (BOOL(CCmdTarget::*)(UINT, NMHDR *, LRESULT *))OnDblclkDistriblist)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DistributionAttributesDefinitionDlg
//---------------------------------------------------------------------------
PSS_DistributionAttributesDefinitionDlg::PSS_DistributionAttributesDefinitionDlg(PSS_DistributionAttributeManager* pDistributionManager,
                                                                                 PSS_DynamicPropertiesManager*     pPropManager,
                                                                                 ZBPropertySet*                    pSet,
                                                                                 PSS_UserGroupEntity*              pMainUserGroup,
                                                                                 const CString&                    groupGUID,
                                                                                 PSS_DistributionAttribute*        pDistributionAttr,
                                                                                 CWnd*                             pParent) :
    CDialog(PSS_DistributionAttributesDefinitionDlg::IDD, pParent),
    m_pDistributionManager(pDistributionManager),
    m_pPropManager(pPropManager),
    m_pMainUserGroup(pMainUserGroup),
    m_pDistributionAttr(pDistributionAttr),
    m_pSet(pSet),
    m_GroupGUID(groupGUID),
    m_CategoryID(-1),
    m_ItemID(-1),
    m_Allocated(false)
{}
//---------------------------------------------------------------------------
PSS_DistributionAttributesDefinitionDlg::~PSS_DistributionAttributesDefinitionDlg()
{
    if (m_Allocated && m_pDistributionAttr)
        delete m_pDistributionAttr;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesDefinitionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_DistributionAttributesDefinitionDlg)
    DDX_Control(pDX, IDC_DISTRIBLIST,   m_List);
    DDX_Text   (pDX, IDC_DYNATTRIB,     m_DynamicAttributeName);
    DDX_Text   (pDX, IDC_USERGROUPNAME, m_GroupName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_DistributionAttributesDefinitionDlg::OnInitDialog()
{
    if (!m_pDistributionAttr)
    {
        m_Allocated         = true;
        m_pDistributionAttr = new PSS_DistributionAttribute();

        // if a group is defined, assign its id to the distribution attribute
        if (!m_GroupGUID.IsEmpty() && m_pDistributionAttr)
            m_pDistributionAttr->SetUserGroupGUID(m_GroupGUID);
    }

    if (m_pDistributionAttr && m_pPropManager)
    {
        PSS_Property* pProp = m_pPropManager->GetPropertyItem(m_pDistributionAttr->GetCategoryID(),
                                                              m_pDistributionAttr->GetItemID());

        if (pProp)
        {
            m_CategoryID           = pProp->GetCategoryID();
            m_ItemID               = pProp->GetItemID();
            m_DynamicAttributeName = pProp->GetLabel();
        }

        // first level is the role name
        PSS_UserEntity* pEntity = m_pMainUserGroup->FindGroupByGUID(m_pDistributionAttr->GetUserGroupGUID(), true);
        m_GroupName             = pEntity ? pEntity->GetEntityName() : _T("");

        // on starting, check the distribution role for the distribution attribute
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
        if (GetDlgItem(IDC_CHOOSE_USERGROUP))
            GetDlgItem(IDC_CHOOSE_USERGROUP)->EnableWindow(FALSE);

    CheckControlState();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesDefinitionDlg::OnChooseDynattr()
{
    ZVChoosePropertyDlg selectPropDlg(m_pSet, 2);

    if (selectPropDlg.DoModal() == IDOK)
    {
        PSS_Property* pProp = selectPropDlg.GetSelectedProperty();

        if (pProp)
        {
            m_CategoryID           = pProp->GetCategoryID();
            m_ItemID               = pProp->GetItemID();
            m_DynamicAttributeName = pProp->GetLabel();

            // push to dialog data
            UpdateData(FALSE);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesDefinitionDlg::OnChooseUsergroup()
{
    if (!m_pMainUserGroup || !m_pDistributionManager)
        return;

    PSS_SelectUserGroupDlg selectGroupDlg(IDS_CHOOSEDISTRIBGROUP_TITLE, m_pMainUserGroup, true, false);

    if (selectGroupDlg.DoModal() == IDOK)
    {
        PSS_UserGroupEntity* pEntity = dynamic_cast<PSS_UserGroupEntity*>(selectGroupDlg.GetSelectedUserEntity());

        if (pEntity)
        {
            m_GroupName = pEntity->GetEntityName();
            m_GroupGUID = pEntity->GetGUID();
            m_pDistributionAttr->SetUserGroupGUID(m_GroupGUID);

            const int size       = pEntity->GetEntityCount();
            bool      foundCount = false;

            for (int i = 0; i < size; ++i)
            {
                PSS_UserEntity* pUserEntity = dynamic_cast<PSS_UserGroupEntity*>(pEntity)->GetEntityAt(i);

                if (pUserEntity)
                {
                    foundCount = true;
                    break;
                }
            }

            // fill the roles by default
            if (foundCount)
                // on starting, check the distribution role for the distribution attribute
                m_pDistributionManager->CheckDistributionRole(m_pDistributionAttr, m_pMainUserGroup);
            else
            {
                PSS_MsgBox mBox;
                mBox.Show(IDS_USERGROUP_HASNOROLE, MB_OK);
            }

            // push to dialog data
            UpdateData(FALSE);

            m_List.Refresh();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesDefinitionDlg::OnAddruleButton()
{
    PSS_DistributionRulesForRole* pRole = GetSelectedDistributionRuleForRole();

    if (!pRole)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_SELECTROLE_MSG, MB_OK);
        return;
    }

    ASSERT(m_pDistributionAttr);

    PSS_DistributionRuleDefDlg dlg;

    if (dlg.DoModal() == IDOK)
    {
        m_pDistributionAttr->AddDistributionRulesForRole(pRole->GetRoleGUID(),
                                                         dlg.GetOperator(),
                                                         dlg.GetValue(),
                                                         dlg.GetLogicalOperator() - 1);

        // refresh the list
        m_List.Refresh();
    }
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesDefinitionDlg::OnDelruleButton()
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

        // refresh the list
        m_List.Refresh();
    }
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesDefinitionDlg::OnModruleButton()
{
    PSS_DistributionRule* pRule = GetSelectedDistributionRule();

    if (!pRule)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_SELECTRULE_MSG, MB_OK);
        return;
    }

    PSS_DistributionRuleDefDlg dlg(pRule);

    if (dlg.DoModal() == IDOK)
    {
        pRule->SetOperator(dlg.GetOperator());
        pRule->SetValue(dlg.GetValue());
        pRule->SetLogicalOperator(dlg.GetLogicalOperator() - 1);

        // refresh the list
        m_List.Refresh();
    }
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesDefinitionDlg::OnClickDistriblist(NMHDR* pNMHDR, LRESULT* pResult)
{
    CheckControlState();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesDefinitionDlg::OnDblclkDistriblist(NMHDR* pNMHDR, LRESULT* pResult)
{
    CheckControlState();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesDefinitionDlg::OnOK()
{
    if (m_DynamicAttributeName.IsEmpty())
    {
        // s dynamic attributes must be selected
        PSS_MsgBox mBox;
        mBox.Show(IDS_DYNAMICATTRIBUTES_REQUIRED, MB_OK);
        return;
    }

    if (m_GroupName.IsEmpty())
    {
        // a group must be selected
        PSS_MsgBox mBox;
        mBox.Show(IDS_DISTRIBUTIONGROUP_REQUIRED, MB_OK);
        return;
    }

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_DistributionAttributesDefinitionDlg::CheckControlState()
{}
//---------------------------------------------------------------------------
