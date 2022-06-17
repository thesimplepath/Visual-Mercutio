/****************************************************************************
 * ==> PSS_StopSymbolBP ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a stop symbol for banking process                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_StopSymbolBP.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseSym\zBaseSymRes.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_ModelGlobal.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_SelectUserGroupDlg.h"
#define _ZMODELEXPORT
    #include "zModel\PSS_BasicProperties.h"
#undef _ZMODELEXPORT
#include "zProperty\PSS_PropertyAttributes.h"
#include "PSS_UnitPropertiesBP_Beta1.h"
#include "PSS_ProcessGraphModelControllerBP.h"
#include "PSS_ProcessGraphModelMdlBP.h"
#include "PSS_RiskOptionsDlg.h"

// resources
#include "zModel\zModelRes.h"
#include "zModelBPRes.h"
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const std::size_t g_MaxRulesSize = 20;
const std::size_t g_MaxRisksSize = 20;
//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static CMenu g_RulesMenu;
static CMenu g_RiskMenu;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_StopSymbolBP, PSS_Symbol, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_StopSymbolBP
//---------------------------------------------------------------------------
PSS_StopSymbolBP::PSS_StopSymbolBP(const CString& name) :
    PSS_Symbol()
{
    PSS_Symbol::SetSymbolName(name);

    // configure what to show first
    ShowNameArea(true);
    ShowDescriptionArea(false);
    ShowAttributeArea(true);

    CreateSymbolProperties();
}
//---------------------------------------------------------------------------
PSS_StopSymbolBP::PSS_StopSymbolBP(const PSS_StopSymbolBP& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_StopSymbolBP::~PSS_StopSymbolBP()
{}
//---------------------------------------------------------------------------
PSS_StopSymbolBP& PSS_StopSymbolBP::operator = (const PSS_StopSymbolBP& other)
{
    PSS_Symbol::operator = ((const PSS_Symbol&)other);

    m_UnitProp = other.m_UnitProp;
    m_Rules    = other.m_Rules;
    m_Risks    = other.m_Risks;

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_StopSymbolBP::Create(const CString& name)
{
    BOOL result = FALSE;

    try
    {
        m_IsInCreationProcess = true;
        result                = PSS_Symbol::Create(IDR_BP_STOP,
                                                   ::AfxFindResourceHandle(MAKEINTRESOURCE(IDR_UML_END_SYM),
                                                                           _T("Symbol")),
                                                   name);

        if (!CreateSymbolProperties())
            result = FALSE;
    }
    catch (...)
    {
        m_IsInCreationProcess = false;
        throw;
    }

    m_IsInCreationProcess = false;
    return result;
}
//---------------------------------------------------------------------------
CODComponent* PSS_StopSymbolBP::Dup() const
{
    return new PSS_StopSymbolBP(*this);
}
//---------------------------------------------------------------------------
void PSS_StopSymbolBP::CopySymbolDefinitionFrom(const CODSymbolComponent& src)
{
    PSS_Symbol::CopySymbolDefinitionFrom(src);

    const PSS_StopSymbolBP* pSymbol = dynamic_cast<const PSS_StopSymbolBP*>(&src);

    if (pSymbol)
    {
        m_UnitProp = pSymbol->m_UnitProp;
        m_Rules    = pSymbol->m_Rules;
        m_Risks    = pSymbol->m_Risks;
    }
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    // don't allow the drop if the symbol isn't local
    if (!IsLocal())
        return false;

    if (pObj)
    {
        // is an user entity?
        if (ISA(pObj, PSS_UserGroupEntity))
            return true;

        // is a rule entity?
        if (ISA(pObj, PSS_LogicalRulesEntity))
            return true;
    }

    return PSS_Symbol::AcceptDropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::DropItem(CObject* pObj, const CPoint& point)
{
    PSS_UserGroupEntity* pUserGroupEntity = dynamic_cast<PSS_UserGroupEntity*>(pObj);

    if (pUserGroupEntity)
    {
        PSS_ProcessGraphModelMdl* pRootModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

        // is the user group valid?
        if (pRootModel && !pRootModel->MainUserGroupIsValid())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_USERGROUPNOTINLINE, MB_OK);
            return false;
        }

        SetUnitGUID(pUserGroupEntity->GetGUID());
        SetUnitName(pUserGroupEntity->GetEntityName());

        // change the unit cost
        SetUnitCost(pUserGroupEntity->GetEntityCost());

        // set the symbol as modified
        SetModifiedFlag(TRUE);

        // refresh the attribute area and redraw the symbol
        RefreshAttributeTextArea(true);
        return true;
    }

    PSS_LogicalRulesEntity* pRuleEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pObj);

    if (pRuleEntity)
    {
        PSS_ProcessGraphModelMdl* pRootModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

        // is the rule valid?
        if (pRootModel && !pRootModel->MainLogicalRulesIsValid())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_RULENOTINLINE, MB_OK);
            return false;
        }

        std::unique_ptr<PSS_RulesPropertiesBP> pNewRule(new PSS_RulesPropertiesBP());
        pNewRule->SetRuleName       (pRuleEntity->GetEntityName());
        pNewRule->SetRuleDescription(pRuleEntity->GetEntityDescription());
        pNewRule->SetRuleGUID       (pRuleEntity->GetGUID());
        m_Rules.AddRule(pNewRule.get());
        pNewRule.release();

        // set the symbol as modified
        SetModifiedFlag(TRUE);

        // refresh the attribute area and redraw the symbol
        RefreshAttributeTextArea(true);
        return true;
    }

    return PSS_Symbol::DropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::CreateSymbolProperties()
{
    if (!PSS_Symbol::CreateSymbolProperties())
        return false;

    PSS_UnitPropertiesBP_Beta1 propUnit;
    AddProperty(propUnit);

    m_Risks.CreateInitialProperties();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::FillProperties(PSS_Properties::IPropertySet& propSet, bool numericValues, bool groupValues)
{
    if (!PSS_Symbol::FillProperties(propSet, numericValues, groupValues))
        return false;

    // only local symbol may access to properties
    if (!IsLocal())
        return true;

    PSS_ProcessGraphModelMdl* pProcessGraphModel  =                      dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());
    PSS_ProcessGraphModelDoc* pProcessGraphMdlDoc = pProcessGraphModel ? dynamic_cast<PSS_ProcessGraphModelDoc*>(pProcessGraphModel->GetDocument()) : NULL;

    // initialize the currency symbol with the user local currency symbol defined in the control panel
    CString currencySymbol = PSS_Global::GetLocaleCurrency();

    // update the currency symbol according to the user selection
    if (pProcessGraphMdlDoc)
        currencySymbol = pProcessGraphMdlDoc->GetCurrencySymbol();

    std::unique_ptr<PSS_Property> pProp;

    // if the rule menu isn't loaded, load it
    if (!g_RulesMenu.GetSafeHmenu())
        g_RulesMenu.LoadMenu(IDR_RULES_MENU);

    const int ruleCount = m_Rules.GetRulesCount();

    if (ruleCount > 0)
    {
        CString ruleSectionTitle;
        ruleSectionTitle.LoadString(IDS_Z_RULES_TITLE);

        CString ruleDesc;
        ruleDesc.LoadString(IDS_Z_RULES_DESC);

        PSS_ProcessGraphModelMdlBP* pOwnerModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(GetOwnerModel());
        PSS_LogicalRulesEntity*     pMainRule   = NULL;

        // get the main rule
        if (pOwnerModel)
        {
            PSS_ProcessGraphModelControllerBP* pModelCtrl =
                    dynamic_cast<PSS_ProcessGraphModelControllerBP*>(pOwnerModel->GetController());

            if (pModelCtrl)
            {
                PSS_ProcessGraphModelDoc* pDocument = dynamic_cast<PSS_ProcessGraphModelDoc*>(pModelCtrl->GetDocument());

                if (pDocument)
                    pMainRule = pDocument->GetMainLogicalRules();
            }
        }

        // iterate through rules
        for (int i = 0; i < ruleCount; ++i)
        {
            // the rule check can only be performed if the rules are synchronized with the referential
            if (pProcessGraphModel && pProcessGraphModel->MainLogicalRulesIsValid())
            {
                const CString safeName = GetRuleNameByGUID(pMainRule, m_Rules.GetRuleGUID(i));

                if (!safeName.IsEmpty() && safeName != m_Rules.GetRuleName(i))
                    m_Rules.SetRuleName(i, safeName);
            }

            CString ruleName;
            ruleName.Format(IDS_Z_RULES_NAME, i + 1);

            // the "Rule x" property of the "Rules" group
            pProp.reset(new PSS_Property(ruleSectionTitle,
                                         ZS_BP_PROP_RULES,
                                         ruleName,
                                         M_Rule_Name_ID + (i * g_MaxRulesSize),
                                         ruleDesc,
                                         m_Rules.GetRuleName(i),
                                         PSS_Property::IEType::IE_T_EditMenu,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_General),
                                         NULL,
                                         &g_RulesMenu));

            pProp->EnableDragNDrop();
            propSet.Add(pProp.get());
            pProp.release();
        }
    }

    // if the risk menu isn't loaded, load it
    if (!g_RiskMenu.GetSafeHmenu())
        g_RiskMenu.LoadMenu(IDR_RISK_MENU);

    CString riskTitle;
    riskTitle.LoadString(IDS_ZS_BP_PROP_RISK_TITLE);

    CString   riskName;
    CString   riskDesc;
    const int riskCount = GetRiskCount();

    for (int i = 0; i < riskCount; ++i)
    {
        CString finalRiskTitle;
        finalRiskTitle.Format(_T("%s (%d)"), riskTitle, i + 1);

        riskName.LoadString(IDS_Z_RISK_NAME_NAME);
        riskDesc.LoadString(IDS_Z_RISK_NAME_DESC);

        // the "Title" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Name_ID : (M_Risk_Name_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     GetRiskName(i),
                                     PSS_Property::IEType::IE_T_EditMenu,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_General),
                                     NULL,
                                     &g_RiskMenu));

        propSet.Add(pProp.get());
        pProp.release();

        riskName.LoadString(IDS_Z_RISK_DESC_NAME);
        riskDesc.LoadString(IDS_Z_RISK_DESC_DESC);

        // the "Description" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Desc_ID : (M_Risk_Desc_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     GetRiskDesc(i),
                                     PSS_Property::IEType::IE_T_EditExtended));

        propSet.Add(pProp.get());
        pProp.release();

        riskName.LoadString(IDS_Z_RISK_TYPE_NAME);
        riskDesc.LoadString(IDS_Z_RISK_TYPE_DESC);

        CString noRiskType;
        noRiskType.LoadString(IDS_NO_RISK_TYPE);

        // the "Type" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Type_ID : (M_Risk_Type_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     GetRiskType(i).IsEmpty() ? noRiskType : GetRiskType(i),
                                     PSS_Property::IEType::IE_T_EditExtendedReadOnly));

        propSet.Add(pProp.get());
        pProp.release();

        PSS_Application* pApp      = PSS_Application::Instance();
        PSS_MainForm*    pMainForm = NULL;
        CString          riskImpact;

        // get the impact value
        if (pApp)
        {
            pMainForm = pApp->GetMainForm();

            if (pMainForm)
            {
                PSS_RiskImpactContainer* pContainer = pMainForm->GetRiskImpactContainer();

                if (pContainer)
                    riskImpact = pContainer->GetElementAt(GetRiskImpact(i));
            }
        }

        riskName.LoadString(IDS_Z_RISK_IMPACT_NAME);
        riskDesc.LoadString(IDS_Z_RISK_IMPACT_DESC);

        // the "Impact" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Impact_ID : (M_Risk_Impact_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     riskImpact,
                                     PSS_Property::IEType::IE_T_EditExtendedReadOnly));

        propSet.Add(pProp.get());
        pProp.release();

        CString riskProbability;

        if (pMainForm)
        {
            PSS_RiskProbabilityContainer* pContainer = pMainForm->GetRiskProbabilityContainer();

            if (pContainer)
                riskProbability = pContainer->GetElementAt(GetRiskProbability(i));
        }

        riskName.LoadString(IDS_Z_RISK_PROBABILITY_NAME);
        riskDesc.LoadString(IDS_Z_RISK_PROBABILITY_DESC);

        // the "Probability" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Probability_ID : (M_Risk_Probability_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     riskProbability,
                                     PSS_Property::IEType::IE_T_EditExtendedReadOnly));

        propSet.Add(pProp.get());
        pProp.release();

        riskName.LoadString(IDS_Z_RISK_SEVERITY_NAME);
        riskDesc.LoadString(IDS_Z_RISK_SEVERITY_DESC);

        // the "Severity" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Severity_ID : (M_Risk_Severity_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     double(GetRiskSeverity(i)),
                                     PSS_Property::IEType::IE_T_EditNumberReadOnly));

        propSet.Add(pProp.get());
        pProp.release();

        riskName.LoadString(IDS_Z_RISK_UE_NAME);
        riskDesc.LoadString(IDS_Z_RISK_UE_DESC);

        // the "Unit. est." property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_UE_ID : (M_Risk_UE_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     GetRiskUE(i),
                                     PSS_Property::IEType::IE_T_EditNumber,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Currency, true, 2, currencySymbol)));

        propSet.Add(pProp.get());
        pProp.release();

        riskName.LoadString(IDS_Z_RISK_POA_NAME);
        riskDesc.LoadString(IDS_Z_RISK_POA_DESC);

        // the "POA" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_POA_ID : (M_Risk_POA_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     GetRiskPOA(i),
                                     PSS_Property::IEType::IE_T_EditNumber,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Currency, true, 2, currencySymbol)));

        propSet.Add(pProp.get());
        pProp.release();

        riskName.LoadString(IDS_Z_RISK_ACTION_NAME);
        riskDesc.LoadString(IDS_Z_RISK_ACTION_DESC);

        // the "Action" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Action_ID : (M_Risk_Action_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     GetRiskAction(i) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo(),
                                     PSS_Property::IEType::IE_T_ComboStringReadOnly,
                                     TRUE,
                                     PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

        propSet.Add(pProp.get());
        pProp.release();
    }

    bool groupEnabled = true;

    // check if the user group is valid
    if (pProcessGraphModel && !pProcessGraphModel->MainUserGroupIsValid())
        groupEnabled = false;

    // the "Guid" property of the "Processing unit" group. This property isn't enabled, just used for write the unit GUID.
    // NOTE "GUID" and "Name" properties should appear in Conceptor
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_UNIT_TITLE,
                                 ZS_BP_PROP_UNIT,
                                 IDS_Z_UNIT_GUID_NAME,
                                 M_Unit_GUID_ID,
                                 IDS_Z_UNIT_GUID_DESC,
                                 GetUnitGUID(),
                                 PSS_Property::IEType::IE_T_EditExtendedReadOnly,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    bool          error;
    const CString unitName = RetrieveUnitName(GetUnitGUID(), error);

    // the "Name" property of the "Processing unit" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_UNIT_TITLE,
                                 ZS_BP_PROP_UNIT,
                                 IDS_Z_UNIT_NAME_NAME,
                                 M_Unit_Name_ID,
                                 IDS_Z_UNIT_NAME_DESC,
                                 unitName,
                                 groupEnabled ? PSS_Property::IEType::IE_T_EditExtendedReadOnly : PSS_Property::IEType::IE_T_EditStringReadOnly));

    propSet.Add(pProp.get());
    pProp.release();

    // the unit cost properties should appear only in Messenger
    if (pProcessGraphModel && pProcessGraphModel->GetIntegrateCostSimulation())
    {
        const float unitCost = RetrieveUnitCost(GetUnitGUID(), error);

        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_UNIT_TITLE,
                                     ZS_BP_PROP_UNIT,
                                     IDS_Z_UNIT_COST_NAME,
                                     M_Unit_Cost_ID,
                                     IDS_Z_UNIT_COST_DESC,
                                     unitCost,
                                     PSS_Property::IEType::IE_T_EditNumberReadOnly));

        propSet.Add(pProp.get());
        pProp.release();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::SaveProperties(PSS_Properties::IPropertySet& propSet)
{
    if (!PSS_Symbol::SaveProperties(propSet))
        return false;

    PSS_Properties::IPropertyIterator it(&propSet);

    // iterate through the risk values
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        const int categoryID = pProp->GetCategoryID();

        if (categoryID >= ZS_BP_PROP_RISK && categoryID <= ZS_BP_PROP_RISK + GetRiskCount())
        {
            const int i = categoryID - ZS_BP_PROP_RISK;

            if (pProp->GetItemID() == M_Risk_Name_ID + (i * g_MaxRisksSize))
                SetRiskName(i, pProp->GetValueString());

            if (pProp->GetItemID() == M_Risk_Desc_ID + (i * g_MaxRisksSize))
                SetRiskDesc(i, pProp->GetValueString());

            if (pProp->GetItemID() == M_Risk_UE_ID + (i * g_MaxRisksSize))
                SetRiskUE(i, pProp->GetValueFloat());

            if (pProp->GetItemID() == M_Risk_POA_ID + (i * g_MaxRisksSize))
                SetRiskPOA(i, pProp->GetValueFloat());

            if (pProp->GetItemID() == M_Risk_Action_ID + (i * g_MaxRisksSize))
                SetRiskAction(i, (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo() ? 1 : 0));
        }
    }

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        const int categoryID = pProp->GetCategoryID();

        if (categoryID == ZS_BP_PROP_UNIT)
            switch (pProp->GetValueType())
            {
                case PSS_Property::IEValueType::IE_VT_Double: m_UnitProp.SetValue(pProp->GetItemID(), float(pProp->GetValueDouble())); break;
                case PSS_Property::IEValueType::IE_VT_Float:  m_UnitProp.SetValue(pProp->GetItemID(), pProp->GetValueFloat());         break;
                case PSS_Property::IEValueType::IE_VT_String: m_UnitProp.SetValue(pProp->GetItemID(), pProp->GetValueString());        break;
            }
    }

    RefreshAttributeTextArea(true);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::SaveProperty(PSS_Property& prop)
{
    if (!PSS_Symbol::SaveProperty(prop))
        return false;

    // only local symbol may access to properties
    if (!IsLocal())
        return true;

    const int categoryID = prop.GetCategoryID();

    // update the risk properties
    if (categoryID >= ZS_BP_PROP_RISK && categoryID <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        const int i = prop.GetCategoryID() - ZS_BP_PROP_RISK;

        if (prop.GetItemID() == M_Risk_Name_ID + (i * g_MaxRisksSize))
            SetRiskName(i, prop.GetValueString());

        if (prop.GetItemID() == M_Risk_Desc_ID + (i * g_MaxRisksSize))
            SetRiskDesc(i, prop.GetValueString());

        if (prop.GetItemID() == M_Risk_UE_ID + (i * g_MaxRisksSize))
            SetRiskUE(i, prop.GetValueFloat());

        if (prop.GetItemID() == M_Risk_POA_ID + (i * g_MaxRisksSize))
            SetRiskPOA(i, prop.GetValueFloat());

        if (prop.GetItemID() == M_Risk_Action_ID + (i * g_MaxRisksSize))
            SetRiskAction(i, (prop.GetValueString() == PSS_Global::GetYesFromArrayYesNo() ? 1 : 0));
    }

    // check if the user modified a rule, if yes, restore the original name
    if (categoryID == ZS_BP_PROP_RULES)
    {
        const int index = (prop.GetItemID() - M_Rule_Name_ID) / g_MaxRulesSize;

        if (m_Rules.GetRuleName(index) != prop.GetValueString())
            prop.SetValueString(m_Rules.GetRuleName(index));
    }

    // set the symbol as modified
    SetModifiedFlag();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::CheckPropertyValue(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props)
{
    return PSS_Symbol::CheckPropertyValue(prop, value, props);
}
//---------------------------------------------------------------------------
CString PSS_StopSymbolBP::GetRuleNameByGUID(PSS_LogicalRulesEntity* pRule, const CString& ruleGUID)
{
    if (!pRule)
        return _T("");

    if (pRule->GetGUID() == ruleGUID)
        return pRule->GetEntityName();

    if (pRule->ContainEntity())
    {
        const std::size_t count = pRule->GetEntityCount();

        for (std::size_t i = 0; i < count; ++i)
        {
            PSS_LogicalRulesEntity* pRuleEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pRule->GetEntityAt(i));

            if (!pRuleEntity)
                continue;

            const CString name = GetRuleNameByGUID(pRuleEntity, ruleGUID);

            if (!name.IsEmpty())
                return name;
        }
    }

    return _T("");
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::ProcessExtendedInput(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props, bool& refresh)
{
    const int categoryID = prop.GetCategoryID();

    // process the risks
    if (categoryID >= ZS_BP_PROP_RISK && categoryID <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        const int                 i              = categoryID - ZS_BP_PROP_RISK;
        PSS_ProcessGraphModelMdl* pModel         = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());
        CString                   currencySymbol = PSS_Global::GetLocaleCurrency();

        // get the model currency symbol
        if (pModel)
        {
            PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pModel->GetDocument());

            if (pDoc)
                currencySymbol = pDoc->GetCurrencySymbol();
        }

        CString noRiskType;
        noRiskType.LoadString(IDS_NO_RISK_TYPE);

        PSS_RiskOptionsDlg riskOptions(GetRiskName(i),
                                       GetRiskDesc(i),
                                       GetRiskType(i).IsEmpty() ? noRiskType : GetRiskType(i),
                                       GetRiskImpact(i),
                                       GetRiskProbability(i),
                                       GetRiskUE(i),
                                       GetRiskPOA(i),
                                       GetRiskAction(i),
                                       currencySymbol);

        if (riskOptions.DoModal() == IDOK)
        {
            SetRiskName       (i, riskOptions.GetRiskTitle());
            SetRiskDesc       (i, riskOptions.GetRiskDescription());
            SetRiskType       (i, riskOptions.GetRiskType());
            SetRiskImpact     (i, riskOptions.GetRiskImpact());
            SetRiskProbability(i, riskOptions.GetRiskProbability());
            SetRiskSeverity   (i, riskOptions.GetRiskSeverity());
            SetRiskUE         (i, riskOptions.GetRiskUE());
            SetRiskPOA        (i, riskOptions.GetRiskPOA());
            SetRiskAction     (i, riskOptions.GetRiskAction());

            SetModifiedFlag(TRUE);
            refresh = true;

            return true;
        }
    }

    // process the units
    if (categoryID == ZS_BP_PROP_UNIT && prop.GetItemID() == M_Unit_Name_ID)
    {
        PSS_ProcessGraphModelMdl* pOwnerModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetOwnerModel());

        if (pOwnerModel)
        {
            PSS_SelectUserGroupDlg dlg(IDS_SELECTAGROUP_T, pOwnerModel->GetMainUserGroup(), true, false);

            if (dlg.DoModal() == IDOK)
            {
                PSS_UserEntity* pUserEntity = dlg.GetSelectedUserEntity();

                if (pUserEntity)
                {
                    value = pUserEntity->GetEntityName();

                    PSS_Properties::IPropertyIterator it(&props);

                    // change the disabled properties unit GUID
                    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                        if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == M_Unit_GUID_ID)
                        {
                            pProp->SetValueString(pUserEntity->GetGUID());
                            break;
                        }

                    return true;
                }
            }
        }
    }

    return PSS_Symbol::ProcessExtendedInput(prop, value, props, refresh);
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::ProcessMenuCommand(int                           menuCmdID,
                                          PSS_Property&                 prop,
                                          CString&                      value,
                                          PSS_Properties::IPropertySet& props,
                                          bool&                         refresh)
{
    const int categoryID = prop.GetCategoryID();

    // process the risks
    if (categoryID >= ZS_BP_PROP_RISK && categoryID <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        switch (menuCmdID)
        {
            case ID_ADD_NEWRISK:     OnAddNewRisk    (prop, value, props, refresh); break;
            case ID_DEL_CURRENTRISK: OnDelCurrentRisk(prop, value, props, refresh); break;
            default:                                                                break;
        }

        return true;
    }

    if (categoryID == ZS_BP_PROP_RULES)
    {
        switch (menuCmdID)
        {
            case ID_DEL_CURRENTRULE:
            {
                const int index = (prop.GetItemID() - M_Rule_Name_ID) / g_MaxRulesSize;

                m_Rules.DeleteRule(index);

                refresh = true;
                break;
            }

            default:
                break;
        }
    }

    return PSS_Symbol::ProcessMenuCommand(menuCmdID, prop, value, props, refresh);
}
//---------------------------------------------------------------------------
CString PSS_StopSymbolBP::GetAttributeString(PSS_PropertyAttributes* pAttributes) const
{
    return PSS_Symbol::GetAttributeString(pAttributes);
}
//---------------------------------------------------------------------------
BOOL PSS_StopSymbolBP::ContainsRule(const CString& ruleName) const
{
    const int ruleCount = m_Rules.GetRulesCount();

    for (int i = 0; i < ruleCount; ++i)
        if (m_Rules.GetRuleName(i) == ruleName)
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
CString PSS_StopSymbolBP::GetRuleGUID(std::size_t index) const
{
    if (index < m_Rules.GetRulesCount())
        return m_Rules.GetRuleGUID(index);

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_StopSymbolBP::GetRiskType(std::size_t index) const
{
    PSS_Application* pApp = PSS_Application::Instance();

    if (!pApp)
        return _T("");

    PSS_MainForm* pMainForm = pApp->GetMainForm();

    if (!pMainForm)
        return _T("");

    PSS_RiskTypeContainer* pContainer = pMainForm->GetRiskTypeContainer();

    if (!pContainer)
        return _T("");

    const int     count    = pContainer->GetElementCount();
    const CString riskType = m_Risks.GetRiskType(index);

    for (int i = 0; i < count; ++i)
        if (riskType == pContainer->GetElementAt(i))
            return m_Risks.GetRiskType(index);

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_StopSymbolBP::Serialize(CArchive& ar)
{
    PSS_Symbol::Serialize(ar);

    // only if the object is serialize from or to a document
    if (ar.m_pDocument)
    {
        PSS_BaseDocument* pBaseDoc = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

        if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 27)
            m_Risks.Serialize(ar);

        if (ar.IsStoring() || (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 19))
            m_UnitProp.Serialize(ar);
        else
        {
            // transfer the properties to new format
            PSS_UnitPropertiesBP_Beta1* pUnitProps = static_cast<PSS_UnitPropertiesBP_Beta1*>(GetProperty(ZS_BP_PROP_UNIT));

            if (pUnitProps)
            {
                SetUnitName(pUnitProps->GetUnitName());
                SetUnitCost(pUnitProps->GetUnitCost());
            }
        }

        if (ar.IsStoring())
            m_Rules.Serialize(ar);
        else
        if (pBaseDoc && pBaseDoc->GetDocumentStamp().GetInternalVersion() >= 26)
            m_Rules.Serialize(ar);
    }
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::OnPostPropertyChanged(PSS_Property& prop, PSS_Properties::IPropertySet& props, bool& refresh)
{
    bool result = false;

    if (prop.GetCategoryID() == ZS_BP_PROP_UNIT && prop.GetItemID() == M_Unit_Name_ID)
    {
        PSS_Properties::IPropertyIterator it(&props);
        CString                           guid;

        // iterate through the properties and search for the matching guid
        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == M_Unit_GUID_ID)
            {
                guid = pProp->GetValueString();
                break;
            }

        // iterate through the properties and update the unit cost
        if (!guid.IsEmpty())
            for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == M_Unit_Cost_ID)
                {
                    bool        error;
                    const float unitCost = RetrieveUnitCost(guid, error);

                    if (!error)
                    {
                        pProp->SetValueFloat(unitCost);
                        result = true;
                    }

                    break;
                }
    }

    if (!result)
        return PSS_Symbol::OnPostPropertyChanged(prop, props, refresh);

    return result;
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::OnDropInternalPropertyItem(PSS_Property&                 srcProperty,
                                                  PSS_Property&                 dstProperty,
                                                  bool                          top2Down,
                                                  PSS_Properties::IPropertySet& props)
{
    if (!::SwapInternalPropertyItem(srcProperty, dstProperty, top2Down, props, ZS_BP_PROP_RULES))
        return false;

    const int srcIndex = (srcProperty.GetItemID() - M_Rule_Name_ID) / g_MaxRulesSize;
    const int dstIndex = (dstProperty.GetItemID() - M_Rule_Name_ID) / g_MaxRulesSize;

    const CString srcRuleName = m_Rules.GetRuleName       (srcIndex);
    const CString srcRuleDesc = m_Rules.GetRuleDescription(srcIndex);
    const CString srcRuleGUID = m_Rules.GetRuleGUID       (srcIndex);

    const CString dstRuleName = m_Rules.GetRuleName       (dstIndex);
    const CString dstRuleDesc = m_Rules.GetRuleDescription(dstIndex);
    const CString dstRuleGUID = m_Rules.GetRuleGUID       (dstIndex);

    m_Rules.SetRuleName       (srcIndex, dstRuleName);
    m_Rules.SetRuleDescription(srcIndex, dstRuleDesc);
    m_Rules.SetRuleGUID       (srcIndex, dstRuleGUID);

    m_Rules.SetRuleName       (dstIndex, srcRuleName);
    m_Rules.SetRuleDescription(dstIndex, srcRuleDesc);
    m_Rules.SetRuleGUID       (dstIndex, srcRuleGUID);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::OnFillDefaultAttributes(PSS_PropertyAttributes* pAttributes)
{
    if (!pAttributes)
        return false;

    // if global attributes were defined, copy them
    if (PSS_ModelGlobal::GetGlobalPropertyAttributes(GetObjectTypeID()).GetAttributeCount() > 0)
        *pAttributes = PSS_ModelGlobal::GetGlobalPropertyAttributes(GetObjectTypeID());
    else
    {
        // add the reference number
        pAttributes->AddAttribute(ZS_BP_PROP_BASIC, M_Symbol_Number_ID);

        // add the unit name
        pAttributes->AddAttribute(ZS_BP_PROP_UNIT, M_Unit_Name_ID);

        // no item labels
        pAttributes->SetShowTitleText(false);
    }

    return PSS_Symbol::OnFillDefaultAttributes(pAttributes);
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::OnChangeAttributes(PSS_PropertyAttributes* pAttributes)
{
    return PSS_Symbol::OnChangeAttributes(pAttributes);
}
//---------------------------------------------------------------------------
BOOL PSS_StopSymbolBP::OnDoubleClick()
{
    return FALSE;
}
//---------------------------------------------------------------------------
bool PSS_StopSymbolBP::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    toolTipText.Format(IDS_FS_BPSTOP_TOOLTIP,
                       (const char*)GetSymbolName(),
                       (const char*)GetSymbolComment(),
                       (const char*)GetSymbolReferenceNumberStr());

    if (mode == PSS_Symbol::IEToolTipMode::IE_TT_Design)
    {
        // todo -cFeature -oJean: need to implement the result of the control checking
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_StopSymbolBP::OnAddNewRisk(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props, bool& refresh)
{
    // add a new risk
    if (AddNewRisk() >= 0)
    {
        // set the symbol as modified
        refresh = true;
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_StopSymbolBP::OnDelCurrentRisk(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props, bool& refresh)
{
    const int count = GetRiskCount();

    if (count <= 1)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOTDELETE_ALLRISKS, MB_OK);
        return;
    }

    // delete the currently selected risk
    const int index = prop.GetCategoryID() - ZS_BP_PROP_RISK;

    if (DeleteRisk(index))
    {
        // set the symbol as modified
        refresh = true;
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
