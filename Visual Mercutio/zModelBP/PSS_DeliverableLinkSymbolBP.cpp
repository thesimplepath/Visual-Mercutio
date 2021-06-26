/****************************************************************************
 * ==> PSS_DeliverableLinkSymbolBP -----------------------------------------*
 ****************************************************************************
 * Description : Provides a deliverable link symbol for banking process     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DeliverableLinkSymbolBP.h"

// stringray studio
#include <Views\OdLineOrientation.h>

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_SymbolLabel.h"
#include "zModel\PSS_ODSymbolManipulator.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_SelectUserGroupDlg.h"
#include "zModel\PSS_SelectModelSymbolDlg.h"
#include "PSS_ProcessGraphModelMdlBP.h"
#include "PSS_RuleListPropertiesBP.h"
#include "PSS_TextItemListPropertiesBP.h"
#include "PSS_CostPropertiesDeliverableBP_Beta1.h"
#include "PSS_AnnualNumberPropertiesBP.h"
#include "PSS_SimPropertiesDeliverableBP.h"
#include "PSS_DoorSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "PSS_StopSymbolBP.h"
#include "PSS_ProcessGraphModelControllerBP.h"
#include "PSS_EqualizeQuantityDlg.h"
#include "PSS_RiskOptionsDlg.h"

// resources
#include "PSS_ModelResIDs.h"
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const std::size_t g_MaxRuleListSize     = 20;
const std::size_t g_MaxTextItemListSize = 20;
const std::size_t g_MaxRulesSize        = 20;
const std::size_t g_MaxRisksSize        = 20;
//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static CMenu g_RulesMenu;
static CMenu g_RiskMenu;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_DeliverableLinkSymbolBP, PSS_LinkSymbol, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DeliverableLinkSymbolBP
//---------------------------------------------------------------------------
PSS_DeliverableLinkSymbolBP::PSS_DeliverableLinkSymbolBP() :
    PSS_LinkSymbol()
{
    // don't use dynamic area
    SetUseDynamicArea(false);
    CreateSymbolProperties();
}
//---------------------------------------------------------------------------
PSS_DeliverableLinkSymbolBP::PSS_DeliverableLinkSymbolBP(const PSS_DeliverableLinkSymbolBP& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_DeliverableLinkSymbolBP::~PSS_DeliverableLinkSymbolBP()
{}
//---------------------------------------------------------------------------
PSS_DeliverableLinkSymbolBP& PSS_DeliverableLinkSymbolBP::operator = (const PSS_DeliverableLinkSymbolBP& other)
{
    PSS_LinkSymbol::operator = ((const PSS_LinkSymbol&)other);

    m_Quantity                  = other.m_Quantity;
    m_SimProperties             = other.m_SimProperties;
    m_CostDeliverableProperties = other.m_CostDeliverableProperties;
    m_UnitProp                  = other.m_UnitProp;
    m_Rules                     = other.m_Rules;
    m_Risks                     = other.m_Risks;

    const int arrayCount = other.m_UnitDoubleValidationTypeArray.GetSize();

    for (int i = 0; i < arrayCount; ++i)
        m_UnitDoubleValidationTypeArray.Add(other.m_UnitDoubleValidationTypeArray.GetAt(i));

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliverableLinkSymbolBP::Create(int style, int pointSize, COLORREF color, int transparent)
{
    BOOL result = FALSE;

    try
    {
        m_IsInCreationProcess = true;
        result                = PSS_LinkSymbol::Create(style, pointSize, color, transparent);

        if (result)
            SetTargetEndpoint(new CODArrowEndpoint());

        if (!CreateSymbolProperties())
            result = FALSE;

        if (!CreateSymbolName())
            result = FALSE;

        // set the default line color for the label
        SetInitialLabelLineColor(defCOLOR_LTLTGRAY);

        // adjust the element position for symbols
        AdjustElementPosition();
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
BOOL PSS_DeliverableLinkSymbolBP::CreateOrthogonal(int style, int pointSize, COLORREF color, int transparent)
{
    BOOL result = FALSE;

    try
    {
        m_IsInCreationProcess = true;

        result = PSS_LinkSymbol::CreateOrthogonal(style, pointSize, color, transparent);

        if (result)
            SetTargetEndpoint(new CODArrowEndpoint());

        if (!CreateSymbolProperties())
            result = FALSE;

        if (!CreateSymbolName())
            result = FALSE;

        // Set the visual information in relation with the percentage
        SetVisualInfo(100);

        // set the default line color for the label
        SetInitialLabelLineColor(defCOLOR_LTLTGRAY);

        // adjust the element position for symbols
        AdjustElementPosition();
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
CODComponent* PSS_DeliverableLinkSymbolBP::Dup() const
{
    return new PSS_DeliverableLinkSymbolBP(*this);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::CopySymbolDefinitionFrom(const CODSymbolComponent& src)
{
    PSS_LinkSymbol::CopySymbolDefinitionFrom(src);

    const PSS_DeliverableLinkSymbolBP* pSymbol = dynamic_cast<const PSS_DeliverableLinkSymbolBP*>(&src);

    if (pSymbol)
    {
        m_Quantity                  = pSymbol->m_Quantity;
        m_SimProperties             = pSymbol->m_SimProperties;
        m_CostDeliverableProperties = pSymbol->m_CostDeliverableProperties;
        m_UnitProp                  = pSymbol->m_UnitProp;
        m_Rules                     = pSymbol->m_Rules;
        m_Risks                     = pSymbol->m_Risks;

        const int arrayCount = pSymbol->m_UnitDoubleValidationTypeArray.GetSize();

        for (int i = 0; i < arrayCount; ++i)
            m_UnitDoubleValidationTypeArray.Add(pSymbol->m_UnitDoubleValidationTypeArray.GetAt(i));
    }
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::CanEditNonDynamicName() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    // don't allow the drop if the symbol isn't local
    if (!IsLocal())
        return false;

    if (pObj && ISA(pObj, PSS_LogicalRulesEntity))
        return true;

    return PSS_LinkSymbol::AcceptDropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::DropItem(CObject* pObj, const CPoint& point)
{
    PSS_LogicalRulesEntity* pRule = dynamic_cast<PSS_LogicalRulesEntity*>(pObj);

    // drop a rule
    if (pRule)
    {
        PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

        // check the rules are valid
        if (pModel && !pModel->MainLogicalRulesIsValid())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_RULENOTINLINE, MB_OK);
            return false;
        }

        std::unique_ptr<PSS_RulesPropertiesBP> pNewRule(new PSS_RulesPropertiesBP());
        pNewRule->SetRuleName       (pRule->GetEntityName());
        pNewRule->SetRuleDescription(pRule->GetEntityDescription());
        pNewRule->SetRuleGUID       (pRule->GetGUID());
        m_Rules.AddRule(pNewRule.get());
        pNewRule.release();

        // set the symbol as modified
        SetModifiedFlag(TRUE);

        // redraw the symbol
        RedrawSymbol();
        return true;
    }

    return PSS_LinkSymbol::DropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::AcceptExtApp() const
{
    PSS_ProcessGraphModelMdl* pModel =
            dynamic_cast<PSS_ProcessGraphModelMdl*>(const_cast<PSS_DeliverableLinkSymbolBP*>(this)->GetRootModel());

    if (pModel && pModel->GetUseWorkflow())
        return true;

    // external app should appear in conceptor
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::AcceptExtFile() const
{
    PSS_ProcessGraphModelMdl* pModel =
            dynamic_cast<PSS_ProcessGraphModelMdl*>(const_cast<PSS_DeliverableLinkSymbolBP*>(this)->GetRootModel());

    if (pModel && pModel->GetUseWorkflow())
        return true;

    // external file should appear in conceptor
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::FillProperties(PSS_Properties::IPropertySet& propSet, bool numericValues, bool groupValues)
{
    CODModel* pModel = GetRootModel();

    // if no file, add a new one
    if (!GetExtFileCount())
        AddNewExtFile();

    // the "Name", "Description" and "Reference" properties of the "General" group can be found in the base class.
    // The "External Files" and "External Apps" properties are also available from there
    if (!PSS_LinkSymbol::FillProperties(propSet, numericValues, groupValues))
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

    bool groupEnabled = true;

    if (pProcessGraphModel && !pProcessGraphModel->MainUserGroupIsValid())
        groupEnabled = false;

    std::unique_ptr<PSS_Property> pProp;

    // if the rule menu isn't loaded, load it
    if (!g_RulesMenu.GetSafeHmenu())
        g_RulesMenu.LoadMenu(IDR_RULES_MENU);

    const int ruleCount = m_Rules.GetRulesCount();

    // fill the rule properties
    if (ruleCount)
    {
        CString ruleSectionTitle;
        ruleSectionTitle.LoadString(IDS_Z_RULES_TITLE);

        CString ruleDesc;
        ruleDesc.LoadString(IDS_Z_RULES_DESC);

        PSS_ProcessGraphModelMdlBP* pOwnerModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(GetOwnerModel());
        PSS_LogicalRulesEntity*     pMainRule   = NULL;

        if (pOwnerModel)
        {
            PSS_ProcessGraphModelControllerBP* pModelCtrl =
                    dynamic_cast<PSS_ProcessGraphModelControllerBP*>(pOwnerModel->GetController());

            if (pModelCtrl)
            {
                PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pModelCtrl->GetDocument());

                if (pDoc && pDoc->GetMainLogicalRules())
                    pMainRule = pDoc->GetMainLogicalRules();
            }
        }

        // iterate through the rules and add their properties
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
                                         PSS_Property::IE_T_EditMenu,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                         NULL,
                                         &g_RulesMenu));

            pProp->EnableDragNDrop();
            propSet.Add(pProp.get());
            pProp.reset();
        }
    }

    // NOTE BE CAREFUL the previous rules architecture below has now changed, and is designed as controls, because
    // they became obsolete after the new rules system was implemented since November 2006. But as the two architectures
    // are too different one from the other, and the both needed to cohabit together, for compatibility reasons with the
    // previous serialization process, the texts referencing to the previous architecture were modified, and the "Rules"
    // words were replaced by "Controls" in the text resources, however the code side was not updated, due to a too huge
    // work to apply the changes. So if a new modification should be applied in the code, please be aware about this point
    PSS_RuleListPropertiesBP* pRulesProps;

    // add the rule
    if ((pRulesProps = static_cast<PSS_RuleListPropertiesBP*>(GetProperty(ZS_BP_PROP_RULELIST))) == NULL)
    {
        PSS_RuleListPropertiesBP propRules;
        AddProperty(propRules);

        // get it back
        pRulesProps = static_cast<PSS_RuleListPropertiesBP*>(GetProperty(ZS_BP_PROP_RULELIST));

        if (!pRulesProps)
            return false;
    }

    CString propTitle;
    propTitle.LoadString(IDS_ZS_BP_PROP_RULELST_TITLE);
    CStringArray* pValueArray = PSS_Global::GetHistoricValueManager().GetFieldHistory(propTitle);

    CString propName;
    propName.LoadString(IDS_Z_RULE_LIST_NAME);

    CString propDesc;
    propDesc.LoadString(IDS_Z_RULE_LIST_DESC);

    CString finalPropName;

    int count = GetRuleCount() + 1;

    // iterate through all control properties, and define at least one control
    for (int i = 0; i < g_MaxRuleListSize; ++i)
    {
        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // add control, if count is reached continue to add empty control until reaching the maximum size
        if (i < count)
            // the "Control x" property of the "Controls" group
            pProp.reset(new PSS_Property(propTitle,
                                         ZS_BP_PROP_RULELIST,
                                         finalPropName,
                                         M_Rule_List_ID + (i * g_MaxRuleListSize),
                                         propDesc,
                                         GetRuleAt(i),
                                         PSS_Property::IE_T_EditIntelli,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                         pValueArray));
        else
            // the "Control X" of the "Controls" group, but it is empty and not shown
            pProp.reset(new PSS_Property(propTitle,
                                         ZS_BP_PROP_RULELIST,
                                         finalPropName,
                                         M_Rule_List_ID + (i * g_MaxRuleListSize),
                                         propDesc,
                                         _T(""),
                                         PSS_Property::IE_T_EditIntelli,
                                         false,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                         pValueArray));

        pProp->EnableDragNDrop();
        propSet.Add(pProp.get());
        pProp.release();
    }

    // load the risk menu if still not exists
    if (!g_RiskMenu.GetSafeHmenu())
        g_RiskMenu.LoadMenu(IDR_RISK_MENU);

    CString riskTitle;
    riskTitle.LoadString(IDS_ZS_BP_PROP_RISK_TITLE);

    // iterate through the risks and add their properties
    for (int i = 0; i < GetRiskCount(); ++i)
    {
        CString finalRiskTitle;
        finalRiskTitle.Format(_T("%s (%d)"), riskTitle, i + 1);

        CString riskName;
        riskName.LoadString(IDS_Z_RISK_NAME_NAME);

        CString riskDesc;
        riskDesc.LoadString(IDS_Z_RISK_NAME_DESC);

        // the "Risk title" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Name_ID : (M_Risk_Name_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     GetRiskName(i),
                                     PSS_Property::IE_T_EditMenu,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
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
                                     PSS_Property::IE_T_EditExtended));

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
                                     PSS_Property::IE_T_EditExtendedReadOnly));

        propSet.Add(pProp.get());
        pProp.release();

        riskName.LoadString(IDS_Z_RISK_IMPACT_NAME);
        riskDesc.LoadString(IDS_Z_RISK_IMPACT_DESC);

        PSS_Application* pApplication = PSS_Application::Instance();
        PSS_MainForm*    pMainForm = NULL;
        CString          riskImpact;

        // get the risk impact string
        if (pApplication)
        {
            pMainForm = pApplication->GetMainForm();

            if (pMainForm)
            {
                PSS_RiskImpactContainer* pContainer = pMainForm->GetRiskImpactContainer();

                if (pContainer)
                    riskImpact = pContainer->GetElementAt(GetRiskImpact(i));
            }
        }

        // the "Impact" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Impact_ID : (M_Risk_Impact_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     riskImpact,
                                     PSS_Property::IE_T_EditExtendedReadOnly));

        propSet.Add(pProp.get());
        pProp.release();

        riskName.LoadString(IDS_Z_RISK_PROBABILITY_NAME);
        riskDesc.LoadString(IDS_Z_RISK_PROBABILITY_DESC);

        CString riskProbability;

        if (pMainForm)
        {
            PSS_RiskProbabilityContainer* pContainer = pMainForm->GetRiskProbabilityContainer();

            if (pContainer)
                riskProbability = pContainer->GetElementAt(GetRiskProbability(i));
        }

        // the "Probability" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Probability_ID : (M_Risk_Probability_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     riskProbability,
                                     PSS_Property::IE_T_EditExtendedReadOnly));

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
                                     PSS_Property::IE_T_EditNumberReadOnly));

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
                                     PSS_Property::IE_T_EditNumber,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol)));

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
                                     PSS_Property::IE_T_EditNumber,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol)));

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
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     TRUE,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

        propSet.Add(pProp.get());
        pProp.release();
    }

    // text item list
    PSS_TextItemListPropertiesBP* pTextItemProps =
            static_cast<PSS_TextItemListPropertiesBP*>(GetProperty(ZS_BP_PROP_TEXTITEMLIST));

    if (!pTextItemProps)
        return false;

    count       = GetTextItemCount() + 1;
    propTitle.LoadString(IDS_ZS_BP_PROP_PROCEDURE_ITMTXTLST_TITLE);
    pValueArray = PSS_Global::GetHistoricValueManager().GetFieldHistory(propTitle);

    propName.LoadString(IDS_Z_TEXTITEM_LIST_NAME);
    propDesc.LoadString(IDS_Z_TEXTITEM_LIST_DESC);

    // iterate through all info properties, and define at least one info
    for (int i = 0; i < g_MaxTextItemListSize; ++i)
    {
        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // add info, if count is reached continue to add empty info until reaching the maximum size
        if (i < count)
            // the "Info x" property of the "Info list" group
            pProp.reset(new PSS_Property(propTitle,
                                         ZS_BP_PROP_TEXTITEMLIST,
                                         finalPropName,
                                         M_TextItem_List_ID + (i * g_MaxTextItemListSize),
                                         propDesc,
                                         GetTextItemAt(i),
                                         PSS_Property::IE_T_EditIntelli,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                         pValueArray));
        else
            // the "Info x" property of the "Info list" group, but it is empty and not shown
            pProp.reset(new PSS_Property(propTitle,
                                         ZS_BP_PROP_TEXTITEMLIST,
                                         finalPropName,
                                         M_TextItem_List_ID + (i * g_MaxTextItemListSize),
                                         propDesc,
                                         _T(""),
                                         PSS_Property::IE_T_EditIntelli,
                                         false,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                         pValueArray));

        pProp->EnableDragNDrop();
        propSet.Add(pProp.get());
        pProp.release();
    }

    int hourPerDay  = -1;
    int dayPerWeek  = -1;
    int dayPerMonth = -1;
    int dayPerYear  = -1;

    // get the standard time
    if (pProcessGraphMdlDoc)
    {
        hourPerDay  = pProcessGraphMdlDoc->GetHourPerDay();
        dayPerWeek  = pProcessGraphMdlDoc->GetDayPerWeek();
        dayPerMonth = pProcessGraphMdlDoc->GetDayPerMonth();
        dayPerYear  = pProcessGraphMdlDoc->GetDayPerYear();
    }

    // do add the processing unit properties?
    if (pProcessGraphModel && pProcessGraphModel->GetIntegrateCostSimulation())
    {
        // the "Standard time" property of the "Deliverable" group
        if (numericValues)
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                         ZS_BP_PROP_DELIVERABLE_COST,
                                         IDS_Z_COST_PROCESSING_TIME_NAME,
                                         M_Cost_Deliv_Processing_Time_ID,
                                         IDS_Z_COST_PROCESSING_TIME_DESC,
                                         GetProcessingTime(),
                                         PSS_Property::IE_T_EditNumber));
        else
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                         ZS_BP_PROP_DELIVERABLE_COST,
                                         IDS_Z_COST_PROCESSING_TIME_NAME,
                                         M_Cost_Deliv_Processing_Time_ID,
                                         IDS_Z_COST_PROCESSING_TIME_DESC,
                                         PSS_Duration(GetProcessingTime(),
                                                      hourPerDay,
                                                      dayPerWeek,
                                                      dayPerMonth,
                                                      dayPerYear),
                                         PSS_Property::IE_T_EditDuration,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();
    }

    // the "Workload percent" property of the "Deliverable" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                 ZS_BP_PROP_DELIVERABLE_COST,
                                 IDS_Z_COST_OUT_WORKLOAD_PERCENT_NAME,
                                 M_Cost_Deliv_Out_Workload_Percent_ID,
                                 IDS_Z_COST_OUT_WORKLOAD_PERCENT_DESC,
                                 GetOutWorkloadPercent(),
                                 PSS_Property::IE_T_EditNumber,
                                 true,
                                 PSS_StringFormat(PSS_StringFormat::IE_FT_Percentage)));

    propSet.Add(pProp.get());
    pProp.release();

    // do add the deliverable cost properties?
    if (pProcessGraphModel && pProcessGraphModel->GetIntegrateCostSimulation())
    {
        // the "Unitary cost" property of the "Deliverable" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                     ZS_BP_PROP_DELIVERABLE_COST,
                                     IDS_Z_COST_UNITARY_COST_NAME,
                                     M_Cost_Deliv_Unitary_Cost_ID,
                                     IDS_Z_COST_UNITARY_COST_DESC,
                                     GetUnitaryCost(),
                                     PSS_Property::IE_T_EditNumber,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Case duration (weighted)" property of the "Deliverable" group
        if (numericValues)
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                         ZS_BP_PROP_DELIVERABLE_COST,
                                         IDS_Z_COST_CASE_DURATION_NAME,
                                         M_Cost_Deliv_Case_Duration_ID,
                                         IDS_Z_COST_CASE_DURATION_DESC,
                                         GetCaseDuration(),
                                         PSS_Property::IE_T_EditNumber));
        else
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                         ZS_BP_PROP_DELIVERABLE_COST,
                                         IDS_Z_COST_CASE_DURATION_NAME,
                                         M_Cost_Deliv_Case_Duration_ID,
                                         IDS_Z_COST_CASE_DURATION_DESC,
                                         PSS_Duration(GetCaseDuration(),
                                                      hourPerDay,
                                                      dayPerWeek,
                                                      dayPerMonth,
                                                      dayPerYear),
                                         PSS_Property::IE_T_EditDurationReadOnly,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Case duration max" property of the "Deliverable" group
        if (numericValues)
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                         ZS_BP_PROP_DELIVERABLE_COST,
                                         IDS_Z_COST_CASE_DURATIONMAX_NAME,
                                         M_Cost_Deliv_Case_Duration_ID,
                                         IDS_Z_COST_CASE_DURATIONMAX_DESC,
                                         GetCaseDurationMax(),
                                         PSS_Property::IE_T_EditNumber));
        else
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                         ZS_BP_PROP_DELIVERABLE_COST,
                                         IDS_Z_COST_CASE_DURATIONMAX_NAME,
                                         M_Cost_Deliv_Case_Duration_ID,
                                         IDS_Z_COST_CASE_DURATIONMAX_DESC,
                                         PSS_Duration(GetCaseDurationMax(),
                                                      hourPerDay,
                                                      dayPerWeek,
                                                      dayPerMonth,
                                                      dayPerYear),
                                         PSS_Property::IE_T_EditDurationReadOnly,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Target duration" property of the "Deliverable" group
        if (numericValues)
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                         ZS_BP_PROP_DELIVERABLE_COST,
                                         IDS_Z_COST_TARGET_DURATION_NAME,
                                         M_Cost_Deliv_Target_Duration_ID,
                                         IDS_Z_COST_TARGET_DURATION_DESC,
                                         GetTargetDuration(),
                                         PSS_Property::IE_T_EditNumber));
        else
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                         ZS_BP_PROP_DELIVERABLE_COST,
                                         IDS_Z_COST_TARGET_DURATION_NAME,
                                         M_Cost_Deliv_Target_Duration_ID,
                                         IDS_Z_COST_TARGET_DURATION_DESC,
                                         PSS_Duration(GetTargetDuration(),
                                                      hourPerDay,
                                                      dayPerWeek,
                                                      dayPerMonth,
                                                      dayPerYear),
                                         PSS_Property::IE_T_EditDuration,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Green line duration" property of the "Deliverable" group
        if (numericValues)
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                         ZS_BP_PROP_DELIVERABLE_COST,
                                         IDS_Z_COST_GREENLINE_DURATION_NAME,
                                         M_Cost_Deliv_Green_Line_Duration_ID,
                                         IDS_Z_COST_GREENLINE_DURATION_DESC,
                                         GetGreenLineDuration(),
                                         PSS_Property::IE_T_EditNumber));
        else
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_COST_DELIV_TITLE,
                                         ZS_BP_PROP_DELIVERABLE_COST,
                                         IDS_Z_COST_GREENLINE_DURATION_NAME,
                                         M_Cost_Deliv_Green_Line_Duration_ID,
                                         IDS_Z_COST_GREENLINE_DURATION_DESC,
                                         PSS_Duration(GetGreenLineDuration(),
                                                      hourPerDay,
                                                      dayPerWeek,
                                                      dayPerMonth,
                                                      dayPerYear),
                                         PSS_Property::IE_T_EditDuration,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();
    }

    // the "Year quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_YEAR_NAME,
                                 M_Number_Year_ID,
                                 IDS_Z_NUMBER_YEAR_DESC,
                                 GetQuantityYear(),
                                 PSS_Property::IE_T_EditExtended,
                                 true,
                                 PSS_StringFormat(PSS_StringFormat::IE_FT_Accounting, true, 0)));

    propSet.Add(pProp.get());
    pProp.release();

    CString value = GetLockQuantityYear() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock year" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_YEAR_NAME,
                                     M_Locked_Year_ID,
                                     IDS_Z_LOCKED_YEAR_DESC,
                                     GetLockQuantityYear() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_YEAR_NAME,
                                     M_Locked_Year_ID,
                                     IDS_Z_LOCKED_YEAR_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetForceEqualizer() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Force equalizer" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_FORCE_EQUALIZER_NAME,
                                     M_Force_Equalizer_ID,
                                     IDS_Z_FORCE_EQUALIZER_DESC,
                                     GetForceEqualizer() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_FORCE_EQUALIZER_NAME,
                                     M_Force_Equalizer_ID,
                                     IDS_Z_FORCE_EQUALIZER_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // the "January quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_JANUARY_NAME,
                                 M_Number_January_ID,
                                 IDS_Z_NUMBER_JANUARY_DESC,
                                 GetQuantityJanuary(),
                                 PSS_Property::IE_T_EditNumber,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetLockQuantityJanuary() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock January" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_JANUARY_NAME,
                                     M_Locked_January_ID,
                                     IDS_Z_LOCKED_JANUARY_DESC,
                                     GetLockQuantityJanuary() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_JANUARY_NAME,
                                     M_Locked_January_ID,
                                     IDS_Z_LOCKED_JANUARY_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // the "Feburuary quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_FEBRUARY_NAME,
                                 M_Number_February_ID,
                                 IDS_Z_NUMBER_FEBRUARY_DESC,
                                 GetQuantityFebruary(),
                                 PSS_Property::IE_T_EditNumber,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetLockQuantityFebruary() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock February" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_FEBRUARY_NAME,
                                     M_Locked_February_ID,
                                     IDS_Z_LOCKED_FEBRUARY_DESC,
                                     GetLockQuantityFebruary() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_FEBRUARY_NAME,
                                     M_Locked_February_ID,
                                     IDS_Z_LOCKED_FEBRUARY_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // the "March quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_MARCH_NAME,
                                 M_Number_March_ID,
                                 IDS_Z_NUMBER_MARCH_DESC,
                                 GetQuantityMarch(),
                                 PSS_Property::IE_T_EditNumber,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetLockQuantityMarch() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock March" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_MARCH_NAME,
                                     M_Locked_March_ID,
                                     IDS_Z_LOCKED_MARCH_DESC,
                                     GetLockQuantityMarch() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_MARCH_NAME,
                                     M_Locked_March_ID,
                                     IDS_Z_LOCKED_MARCH_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // the "Abril quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_APRIL_NAME,
                                 M_Number_April_ID,
                                 IDS_Z_NUMBER_APRIL_DESC,
                                 GetQuantityApril(),
                                 PSS_Property::IE_T_EditNumber,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetLockQuantityApril() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock Abril" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_APRIL_NAME,
                                     M_Locked_April_ID,
                                     IDS_Z_LOCKED_APRIL_DESC,
                                     GetLockQuantityApril() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_APRIL_NAME,
                                     M_Locked_April_ID,
                                     IDS_Z_LOCKED_APRIL_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // the "May quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_MAY_NAME,
                                 M_Number_May_ID,
                                 IDS_Z_NUMBER_MAY_DESC,
                                 GetQuantityMay(),
                                 PSS_Property::IE_T_EditNumber,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetLockQuantityMay() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock May" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_MAY_NAME,
                                     M_Locked_May_ID,
                                     IDS_Z_LOCKED_MAY_DESC,
                                     GetLockQuantityMay() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_MAY_NAME,
                                     M_Locked_May_ID,
                                     IDS_Z_LOCKED_MAY_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // the "June quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_JUNE_NAME,
                                 M_Number_June_ID,
                                 IDS_Z_NUMBER_JUNE_DESC,
                                 GetQuantityJune(),
                                 PSS_Property::IE_T_EditNumber,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetLockQuantityJune() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock June" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_JUNE_NAME,
                                     M_Locked_June_ID,
                                     IDS_Z_LOCKED_JUNE_DESC,
                                     GetLockQuantityJune() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_JUNE_NAME,
                                     M_Locked_June_ID,
                                     IDS_Z_LOCKED_JUNE_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // the "July quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_JULY_NAME,
                                 M_Number_July_ID,
                                 IDS_Z_NUMBER_JULY_DESC,
                                 GetQuantityJuly(),
                                 PSS_Property::IE_T_EditNumber,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetLockQuantityJuly() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock July" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_JULY_NAME,
                                     M_Locked_July_ID,
                                     IDS_Z_LOCKED_JULY_DESC,
                                     GetLockQuantityJuly() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_JULY_NAME,
                                     M_Locked_July_ID,
                                     IDS_Z_LOCKED_JULY_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // the "August quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_AUGUST_NAME,
                                 M_Number_August_ID,
                                 IDS_Z_NUMBER_AUGUST_DESC,
                                 GetQuantityAugust(),
                                 PSS_Property::IE_T_EditNumber,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetLockQuantityAugust() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock August" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_AUGUST_NAME,
                                     M_Locked_August_ID,
                                     IDS_Z_LOCKED_AUGUST_DESC,
                                     GetLockQuantityAugust() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_AUGUST_NAME,
                                     M_Locked_August_ID,
                                     IDS_Z_LOCKED_AUGUST_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // the "September quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_SEPTEMBER_NAME,
                                 M_Number_September_ID,
                                 IDS_Z_NUMBER_SEPTEMBER_DESC,
                                 GetQuantitySeptember(),
                                 PSS_Property::IE_T_EditNumber,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetLockQuantitySeptember() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock September" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_SEPTEMBER_NAME,
                                     M_Locked_September_ID,
                                     IDS_Z_LOCKED_SEPTEMBER_DESC,
                                     GetLockQuantitySeptember() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_SEPTEMBER_NAME,
                                     M_Locked_September_ID,
                                     IDS_Z_LOCKED_SEPTEMBER_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // the "October quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_OCTOBER_NAME,
                                 M_Number_October_ID,
                                 IDS_Z_NUMBER_OCTOBER_DESC,
                                 GetQuantityOctober(),
                                 PSS_Property::IE_T_EditNumber,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetLockQuantityOctober() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock October" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_OCTOBER_NAME,
                                     M_Locked_October_ID,
                                     IDS_Z_LOCKED_OCTOBER_DESC,
                                     GetLockQuantityOctober() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_OCTOBER_NAME,
                                     M_Locked_October_ID,
                                     IDS_Z_LOCKED_OCTOBER_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // the "November quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_NOVEMBER_NAME,
                                 M_Number_November_ID,
                                 IDS_Z_NUMBER_NOVEMBER_DESC,
                                 GetQuantityNovember(),
                                 PSS_Property::IE_T_EditNumber,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetLockQuantityNovember() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock November" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_NOVEMBER_NAME,
                                     M_Locked_November_ID,
                                     IDS_Z_LOCKED_NOVEMBER_DESC,
                                     GetLockQuantityNovember() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_NOVEMBER_NAME,
                                     M_Locked_November_ID,
                                     IDS_Z_LOCKED_NOVEMBER_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // the "December quantity" property of the "Quantities" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                 ZS_BP_PROP_QUANTITY,
                                 IDS_Z_NUMBER_DECEMBER_NAME,
                                 M_Number_December_ID,
                                 IDS_Z_NUMBER_DECEMBER_DESC,
                                 GetQuantityDecember(),
                                 PSS_Property::IE_T_EditNumber,
                                 false));

    propSet.Add(pProp.get());
    pProp.release();

    value = GetLockQuantityDecember() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo();

    // the "Lock December" property of the "Quantities" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_DECEMBER_NAME,
                                     M_Locked_December_ID,
                                     IDS_Z_LOCKED_DECEMBER_DESC,
                                     GetLockQuantityDecember() ? 1.0 : 0.0));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_NUMBER_TITLE,
                                     ZS_BP_PROP_QUANTITY,
                                     IDS_Z_LOCKED_DECEMBER_NAME,
                                     M_Locked_December_ID,
                                     IDS_Z_LOCKED_DECEMBER_DESC,
                                     value,
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     PSS_Global::GetArrayYesNo()));

    propSet.Add(pProp.get());
    pProp.release();

    // do add the cost properties?
    if (pProcessGraphModel && pProcessGraphModel->GetIntegrateCostSimulation())
    {
        // the "Cost" property of the "Calculations and forecasts" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_DELIVERABLE,
                                     ZS_BP_PROP_SIM_DELIVERABLE,
                                     IDS_Z_SIM_DELIV_COST_NAME,
                                     M_Sim_Deliv_Cost_ID,
                                     IDS_Z_SIM_DELIV_COST_DESC,
                                     double(GetCost()),
                                     PSS_Property::IE_T_EditNumberReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Workload forecast" property of the "Calculations and forecasts" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_DELIVERABLE,
                                     ZS_BP_PROP_SIM_DELIVERABLE,
                                     IDS_Z_SIM_DELIV_WORKLOAD_FORECAST_NAME,
                                     M_Sim_Deliv_Workload_Forecast_ID,
                                     IDS_Z_SIM_DELIV_WORKLOAD_FORECAST_DESC,
                                     PSS_Duration(double(GetWorkloadForecast()),
                                                  hourPerDay,
                                                  dayPerWeek,
                                                  dayPerMonth,
                                                  dayPerYear),
                                     PSS_Property::IE_T_EditDurationReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Guid" property of the "Process unit" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_UNIT_TITLE,
                                     ZS_BP_PROP_UNIT,
                                     IDS_Z_UNIT_GUID_NAME,
                                     M_Unit_GUID_ID,
                                     IDS_Z_UNIT_GUID_DESC,
                                     GetUnitGUID(),
                                     PSS_Property::IE_T_EditExtendedReadOnly,
                                     false));

        propSet.Add(pProp.get());
        pProp.release();

        bool    error;
        CString unitName = RetrieveUnitName(GetUnitGUID(), error);

        // the "Unit" property of the "Process unit" group (not visible)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_UNIT_TITLE,
                                     ZS_BP_PROP_UNIT,
                                     IDS_Z_UNIT_NAME_NAME,
                                     M_Unit_Name_ID,
                                     IDS_Z_UNIT_NAME_DESC,
                                     unitName,
                                     groupEnabled ? PSS_Property::IE_T_EditExtendedReadOnly : PSS_Property::IE_T_EditStringReadOnly,
                                     false));

        propSet.Add(pProp.get());
        pProp.release();

        const float unitCost = RetrieveUnitCost(GetUnitGUID(), error);

        // the "Group cost" property of the "Process unit" group (not visible)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_UNIT_TITLE,
                                     ZS_BP_PROP_UNIT,
                                     IDS_Z_UNIT_COST_NAME,
                                     M_Unit_Cost_ID,
                                     IDS_Z_UNIT_COST_DESC,
                                     unitCost,
                                     PSS_Property::IE_T_EditNumberReadOnly,
                                     false,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol),
                                     false));

        propSet.Add(pProp.get());
        pProp.release();
    }

    // the "Double validation" property of the "Process unit" group
    if (numericValues)
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_UNIT_TITLE,
                                     ZS_BP_PROP_UNIT,
                                     IDS_Z_UNIT_DOUBLE_VALIDATION_NAME,
                                     M_Unit_Double_Validation_ID,
                                     IDS_Z_UNIT_DOUBLE_VALIDATION_DESC,
                                     double(GetUnitDoubleValidationType())));
    else
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_UNIT_TITLE,
                                     ZS_BP_PROP_UNIT,
                                     IDS_Z_UNIT_DOUBLE_VALIDATION_NAME,
                                     M_Unit_Double_Validation_ID,
                                     IDS_Z_UNIT_DOUBLE_VALIDATION_DESC,
                                     GetUnitDoubleValidationTypeString(GetUnitDoubleValidationType()),
                                     PSS_Property::IE_T_ComboStringReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     &m_UnitDoubleValidationTypeArray));

    propSet.Add(pProp.get());
    pProp.release();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::SaveProperties(PSS_Properties::IPropertySet& propSet)
{
    if (!PSS_LinkSymbol::SaveProperties(propSet))
        return false;

    // only local symbol may access to properties
    if (!IsLocal())
        return true;

    // get the rules
    PSS_RuleListPropertiesBP* pRulesProps = static_cast<PSS_RuleListPropertiesBP*>(GetProperty(ZS_BP_PROP_RULELIST));

    if (!pRulesProps)
        return false;

    // empty the task list
    SetRuleList(_T(""));

    PSS_Properties::IPropertyIterator it(&propSet);

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_RULELIST)
            switch (pProp->GetValueType())
            {
                case PSS_Property::IE_VT_String:
                    // if not empty, add this new task
                    if (!pProp->GetValueString().IsEmpty())
                        AddRule(pProp->GetValueString());

                    break;
            }

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_DELIVERABLE_COST)
        {
            const int itemID = pProp->GetItemID();

            switch (pProp->GetValueType())
            {
                case PSS_Property::IE_VT_String:   m_CostDeliverableProperties.SetValue(itemID,            pProp->GetValueString());    break;
                case PSS_Property::IE_VT_Double:   m_CostDeliverableProperties.SetValue(itemID, float(     pProp->GetValueDouble()));   break;
                case PSS_Property::IE_VT_Float:    m_CostDeliverableProperties.SetValue(itemID,            pProp->GetValueFloat());     break;
                case PSS_Property::IE_VT_Date:     m_CostDeliverableProperties.SetValue(itemID, float(DATE(pProp->GetValueDate())));    break;
                case PSS_Property::IE_VT_TimeSpan: m_CostDeliverableProperties.SetValue(itemID, double(    pProp->GetValueTimeSpan())); break;
                case PSS_Property::IE_VT_Duration: m_CostDeliverableProperties.SetValue(itemID, double(    pProp->GetValueDuration())); break;
            }
        }

    SavePropertiesToQuantity(propSet);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        const int categoryID = pProp->GetCategoryID();

        if (categoryID >= ZS_BP_PROP_RISK && categoryID <= ZS_BP_PROP_RISK + GetRiskCount())
        {
            const int itemID = pProp->GetItemID();
            const int i      = categoryID - ZS_BP_PROP_RISK;

            if (itemID == M_Risk_Name_ID + (i * g_MaxRisksSize))
                SetRiskName(i, pProp->GetValueString());

            if (itemID == M_Risk_Desc_ID + (i * g_MaxRisksSize))
                SetRiskDesc(i, pProp->GetValueString());

            if (itemID == M_Risk_UE_ID + (i * g_MaxRisksSize))
                SetRiskUE(i, pProp->GetValueFloat());

            if (itemID == M_Risk_POA_ID + (i * g_MaxRisksSize))
                SetRiskPOA(i, pProp->GetValueFloat());

            if (itemID == M_Risk_Action_ID + (i * g_MaxRisksSize))
                SetRiskAction(i, (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo() ? 1 : 0));
        }
    }

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_SIM_DELIVERABLE)
            switch (pProp->GetValueType())
            {
                case PSS_Property::IE_VT_String:   m_SimProperties.SetValue(pProp->GetItemID(), pProp->GetValueString());            break;
                case PSS_Property::IE_VT_Double:   m_SimProperties.SetValue(pProp->GetItemID(), pProp->GetValueDouble());            break;
                case PSS_Property::IE_VT_Float:    m_SimProperties.SetValue(pProp->GetItemID(), pProp->GetValueFloat());             break;
                case PSS_Property::IE_VT_Date:     m_SimProperties.SetValue(pProp->GetItemID(), float(DATE(pProp->GetValueDate()))); break;
                case PSS_Property::IE_VT_TimeSpan: m_SimProperties.SetValue(pProp->GetItemID(), double(pProp->GetValueTimeSpan()));  break;
                case PSS_Property::IE_VT_Duration: m_SimProperties.SetValue(pProp->GetItemID(), double(pProp->GetValueDuration()));  break;
            }

    PSS_TextItemListPropertiesBP* pTextItemProps =
            static_cast<PSS_TextItemListPropertiesBP*>(GetProperty(ZS_BP_PROP_TEXTITEMLIST));

    if (!pTextItemProps)
        return false;

    // empty the text item list
    SetTextItemList(_T(""));

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_TEXTITEMLIST)
            switch (pProp->GetValueType())
            {
                case PSS_Property::IE_VT_String:
                    // if not empty, add this new text item
                    if (!pProp->GetValueString().IsEmpty())
                        AddTextItem(pProp->GetValueString());

                    break;
            }

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT)
        {
            const int itemID = pProp->GetItemID();

            // Check if a flag
            if (itemID == M_Unit_Double_Validation_ID)
                m_UnitProp.SetValue(itemID, ConvertUnitDoubleValidationString2Type(pProp->GetValueString()));
            else
                switch (pProp->GetValueType())
                {
                    case PSS_Property::IE_VT_Double: m_UnitProp.SetValue(itemID, float(pProp->GetValueDouble())); break;
                    case PSS_Property::IE_VT_Float:  m_UnitProp.SetValue(itemID,       pProp->GetValueFloat());   break;
                    case PSS_Property::IE_VT_String: m_UnitProp.SetValue(itemID,       pProp->GetValueString());  break;
                }
        }

    RefreshAttributeTextArea(true);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::SaveProperty(PSS_Property& prop)
{
    if (!PSS_LinkSymbol::SaveProperty(prop))
        return false;

    // only local symbol may access to properties
    if (!IsLocal())
        return true;

    const int categoryID = prop.GetCategoryID();

    // process the risk properties
    if (categoryID >= ZS_BP_PROP_RISK && categoryID <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        const int itemID = prop.GetItemID();
        const int i      = categoryID - ZS_BP_PROP_RISK;

        if (itemID == M_Risk_Name_ID + (i * g_MaxRisksSize))
            SetRiskName(i, prop.GetValueString());

        if (itemID == M_Risk_Desc_ID + (i * g_MaxRisksSize))
            SetRiskDesc(i, prop.GetValueString());

        if (itemID == M_Risk_UE_ID + (i * g_MaxRisksSize))
            SetRiskUE(i, prop.GetValueFloat());

        if (itemID == M_Risk_POA_ID + (i * g_MaxRisksSize))
            SetRiskPOA(i, prop.GetValueFloat());

        if (itemID == M_Risk_Action_ID + (i * g_MaxRisksSize))
            SetRiskAction(i, (prop.GetValueString() == PSS_Global::GetYesFromArrayYesNo() ? 1 : 0));
    }

    // check if the user tried to rename a rule, if yes revert to previous name
    if (categoryID == ZS_BP_PROP_RULES)
    {
        const int index = (prop.GetItemID() - M_Rule_Name_ID) / g_MaxRulesSize;

        if (m_Rules.GetRuleName(index) != prop.GetValueString())
            prop.SetValueString(m_Rules.GetRuleName(index));
    }

    // if not empty, add this new rule
    if (categoryID == ZS_BP_PROP_RULELIST)
        if (!prop.GetValueString().IsEmpty())
            AddRule(prop.GetValueString());

    // if not empty, add this new text item
    if (categoryID == ZS_BP_PROP_TEXTITEMLIST)
        if (!prop.GetValueString().IsEmpty())
            AddTextItem(prop.GetValueString());

    // set the symbol as modified
    SetModifiedFlag();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::CheckPropertyValue(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props)
{
    if (prop.GetCategoryID() == ZS_BP_PROP_QUANTITY && prop.GetItemID() == M_Number_Year_ID)
    {
        // check if the value entered is less than the sum of locked item
        const double newTotal = std::atol(value);

        if (newTotal < m_Quantity.GetSumOfLockedNumbers())
        {
            // warn the user and revert to the old value
            PSS_MsgBox mBox;
            mBox.Show(IDS_LOCKEDTOTAL_GREATERINPUT, MB_OK);

            // assign the old value
            value.Format(_T("%f"), prop.GetValueDouble());

            return false;
        }

        return true;
    }

    return PSS_LinkSymbol::CheckPropertyValue(prop, value, props);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::ProcessExtendedInput(PSS_Property&                 prop,
                                                       CString&                      value,
                                                       PSS_Properties::IPropertySet& props,
                                                       bool&                         refresh)
{
    const int categoryID = prop.GetCategoryID();

    // process the risks
    if (categoryID >= ZS_BP_PROP_RISK && categoryID <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        int                       i              = categoryID - ZS_BP_PROP_RISK;
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

    if (categoryID == ZS_BP_PROP_UNIT && prop.GetItemID() == M_Unit_Name_ID)
    {
        PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetOwnerModel());

        if (pModel)
        {
            PSS_SelectUserGroupDlg dlg(IDS_SELECTAGROUP_T, pModel->GetMainUserGroup(), true, false);

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
    else
    if (categoryID == ZS_BP_PROP_QUANTITY && prop.GetItemID() == M_Number_Year_ID)
    {
        // set the new value and equalize the information
        m_Quantity.SetAndCalculateQuantitiesBasedOnYear(prop.GetValueDouble());

        // save the equalizer value to the properties to avoid to work with wrong equalizer values
        SaveEqualizerToProperties(props);

        PSS_EqualizeQuantityDlg equalize(&props);

        if (equalize.DoModal() == IDOK)
        {
            value.Format(_T("%.0f"), equalize.GetQuantityYear());

            SavePropertiesToQuantity(props);
            return true;
        }
    }

    return PSS_LinkSymbol::ProcessExtendedInput(prop, value, props, refresh);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::ProcessMenuCommand(int                           menuCmdID,
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

    return PSS_LinkSymbol::ProcessMenuCommand(menuCmdID, prop, value, props, refresh);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::CreateSymbolProperties()
{
    if (!PSS_LinkSymbol::CreateSymbolProperties())
        return false;

    PSS_RuleListPropertiesBP propRules;
    AddProperty(propRules);

    PSS_TextItemListPropertiesBP textItemList;
    AddProperty(textItemList);

    PSS_CostPropertiesDeliverableBP_Beta1 propCost;
    AddProperty(propCost);

    // fill the unit double validation type array
    m_UnitDoubleValidationTypeArray.RemoveAll();
    GetUnitDoubleValidationTypeStringArray(m_UnitDoubleValidationTypeArray);

    // add at least a risk
    m_Risks.CreateInitialProperties();

    return true;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliverableLinkSymbolBP::MovePort(CODPortComponent* pPort, const int offsetX, const int offsetY)
{
    BOOL RetValue = PSS_LinkSymbol::MovePort(pPort, offsetX, offsetY);

    // check the status in order to set the right color
    CheckDeliverableStatus();

    return RetValue;
}
//---------------------------------------------------------------------------
CString PSS_DeliverableLinkSymbolBP::GetRuleList() const
{
    PSS_RuleListPropertiesBP* pProps = static_cast<PSS_RuleListPropertiesBP*>(GetProperty(ZS_BP_PROP_RULELIST));

    if (!pProps)
        return _T("");

    return pProps->GetRuleList();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetRuleList(const CString& rules)
{
    PSS_RuleListPropertiesBP* pProps = static_cast<PSS_RuleListPropertiesBP*>(GetProperty(ZS_BP_PROP_RULELIST));

    if (pProps)
    {
        PSS_RuleListPropertiesBP props(*pProps);
        props.SetRuleList(rules);
        SetProperty(&props);
    }
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::AddRule(const CString& rule)
{
    // initialize the token with the task list and with the default ; as separator
    PSS_Tokenizer token(GetRuleList());

    // if the new task was added correctly, update the task list
    if (token.AddUniqueToken(rule))
    {
        // add the value to the history
        CString key;
        key.LoadString(IDS_ZS_BP_PROP_RULELST_TITLE);
        PSS_Global::GetHistoricValueManager().AddHistoryValue(key, rule);

        // set the new task string
        SetRuleList(token.GetString());
    }
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::RemoveRule(const CString& rule)
{
    // initialize the token with the task list and with the default ; as separator
    PSS_Tokenizer token(GetRuleList());

    // if the new task was removed correctly, update the task list
    if (token.RemoveToken(rule))
        SetRuleList(token.GetString());
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::RuleExist(const CString& rule)
{
    // initialize the token with the task list and with the default ; as separator
    PSS_Tokenizer token(GetRuleList());

    return token.TokenExist(rule);
}
//---------------------------------------------------------------------------
CString PSS_DeliverableLinkSymbolBP::GetRuleAt(std::size_t index) const
{
    // initialize the token with the task list and with the default ; as separator
    PSS_Tokenizer token(GetRuleList());
    CString       value;

    // get the specific indexed token
    if (token.GetTokenAt(index, value))
        return value;

    return _T("");
}
//---------------------------------------------------------------------------
std::size_t PSS_DeliverableLinkSymbolBP::GetRuleCount() const
{
    // initialize the token with the task list and with the default ; as separator
    PSS_Tokenizer token(GetRuleList());
    return token.GetTokenCount();
}
//---------------------------------------------------------------------------
CString PSS_DeliverableLinkSymbolBP::GetTextItemList() const
{
    PSS_TextItemListPropertiesBP* pProps = static_cast<PSS_TextItemListPropertiesBP*>(GetProperty(ZS_BP_PROP_TEXTITEMLIST));

    if (!pProps)
        return _T("");

    return pProps->GetTextItemList();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetTextItemList(const CString& items)
{
    PSS_TextItemListPropertiesBP* pProps = static_cast<PSS_TextItemListPropertiesBP*>(GetProperty(ZS_BP_PROP_TEXTITEMLIST));

    if (pProps)
    {
        PSS_TextItemListPropertiesBP props(*pProps);
        props.SetTextItemList(items);
        SetProperty(&props);
    }
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::AddTextItem(const CString& item)
{
    // initialize the token with the list and with the default ; as separator
    PSS_Tokenizer token(GetTextItemList());

    // if the new task was added correctly, update the task list
    if (token.AddUniqueToken(item))
    {
        // add the value to the history
        CString key;
        key.LoadString(IDS_ZS_BP_PROP_PROCEDURE_ITMTXTLST_TITLE);
        PSS_Global::GetHistoricValueManager().AddHistoryValue(key, item);

        // set the new list string
        SetTextItemList(token.GetString());
    }
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::RemoveTextItem(const CString& item)
{
    // initialize the token with the list and with the default ; as separator
    PSS_Tokenizer token(GetTextItemList());

    // if the new task was removed correctly, update the task list
    if (token.RemoveToken(item))
        SetTextItemList(token.GetString());
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::TextItemExist(const CString& item) const
{
    // initialize the token with the list and with the default ; as separator
    PSS_Tokenizer token(GetTextItemList());

    return token.TokenExist(item);
}
//---------------------------------------------------------------------------
CString PSS_DeliverableLinkSymbolBP::GetTextItemAt(std::size_t index) const
{
    // initialize the token with the list and with the default ; as separator
    PSS_Tokenizer token(GetTextItemList());
    CString       value;

    // get the specific indexed token
    if (token.GetTokenAt(index, value))
        return value;

    return _T("");
}
//---------------------------------------------------------------------------
std::size_t PSS_DeliverableLinkSymbolBP::GetTextItemCount() const
{
    // initialize the token with the list and with the default ; as separator
    PSS_Tokenizer token(GetTextItemList());
    return token.GetTokenCount();
}
//---------------------------------------------------------------------------
CString PSS_DeliverableLinkSymbolBP::GetCombinationName() const
{
    // get the destination procedure
    PSS_ProcedureSymbolBP* pProcedure = GetTargetProcedure();

    if (!pProcedure)
        return _T("");

    // from this procedure, search the owning combination
    const std::size_t count = pProcedure->GetCombinationCount();

    for (std::size_t i = 0; i < count; ++i)
        if (pProcedure->IsDeliverableInString(pProcedure->GetCombinationDeliverables(i),
                                              const_cast<PSS_DeliverableLinkSymbolBP*>(this)->GetSymbolName()))
            return pProcedure->GetCombinationName(i);

    // not found otherwise
    return _T("");
}
//---------------------------------------------------------------------------
float PSS_DeliverableLinkSymbolBP::GetCombinationMaxPercentage() const
{
    // get the destination procedure
    PSS_ProcedureSymbolBP* pProcedure = GetTargetProcedure();

    // check if it's a local symbol
    if (pProcedure && !pProcedure->IsLocal())
        // search the local symbol
        pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pProcedure->GetLocalSymbol());

    if (!pProcedure)
        return float(INT_MAX);

    // from this procedure, search the owning combination
    const std::size_t count = pProcedure->GetCombinationCount();

    for (std::size_t i = 0; i < count; ++i)
        if (pProcedure->IsDeliverableInString(pProcedure->GetCombinationDeliverables(i),
                                              const_cast<PSS_DeliverableLinkSymbolBP*>(this)->GetSymbolName()))
            return pProcedure->GetCombinationActivationPerc(i);

    // not found otherwise
    return float(INT_MAX);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::IsMasterOfCombination() const
{
    // get the destination procedure
    PSS_ProcedureSymbolBP* pProcedure = GetTargetProcedure();

    // check if it's a local symbol
    if (pProcedure && !pProcedure->IsLocal())
        // search the local symbol
        pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pProcedure->GetLocalSymbol());

    if (!pProcedure)
        return false;

    // from this procedure, search the owning combination
    const std::size_t count = pProcedure->GetCombinationCount();

    for (std::size_t i = 0; i < count; ++i)
        if (pProcedure->GetCombinationMaster(i) == const_cast<PSS_DeliverableLinkSymbolBP*>(this)->GetSymbolName())
            return true;

    // not a master otherwise
    return false;
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetVisualInfo(int percent)
{
    // check if the percentage value doesn't exceed 100%, and convert the value to allow to select the style
    const int style = percent <= 100 ? ((2 * percent) / 100) : 2;

    // on 100% the line is solid, otherwise it's dotted (0 to 49%) or dashed (50-99%)
    if (style == 2)
        PSS_LinkSymbol::SetCurrentLineStyle(PS_SOLID);
    else
        switch (style)
        {
            case 0: PSS_LinkSymbol::SetCurrentLineStyle(PS_DOT);  break;
            case 1: PSS_LinkSymbol::SetCurrentLineStyle(PS_DASH); break;
        }
}
//---------------------------------------------------------------------------
PSS_ProcedureSymbolBP* PSS_DeliverableLinkSymbolBP::GetSourceProcedure() const
{
    // get the source connected symbol
    CODComponent* pComp = GetSourceComponent();

    PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pComp);

    if (pProcedure)
        return pProcedure;

    PSS_DoorSymbolBP* pDoor = dynamic_cast<PSS_DoorSymbolBP*>(pComp);

    if (pDoor)
    {
        // locate the twin symbol previous connection
        if (!(pComp = pDoor->GetTwinDoorSymbol()))
            return NULL;

        CODEdgeArray      enteringEdges;
        const std::size_t enteringLinkCount = pDoor->GetEdgesEntering_Up(enteringEdges);

        if (enteringLinkCount > 0)
        {
            // get the link
            IODEdge*                     pIEdge = enteringEdges.GetAt(0);
            PSS_DeliverableLinkSymbolBP* pLink  =
                    dynamic_cast<PSS_DeliverableLinkSymbolBP*>(static_cast<CODLinkComponent*>(pIEdge));

            if (!pLink)
                return NULL;

            // call the same function from the twin deliverable
            return pLink->GetSourceProcedure();
        }

        // error, no connection found
        return NULL;
    }

    PSS_PageSymbolBP* pPage = dynamic_cast<PSS_PageSymbolBP*>(pComp);

    if (pPage)
    {
        // locate the twin symbol previous connection
        if (!(pComp = pPage->GetTwinPageSymbol()))
            return NULL;

        CODEdgeArray      enteringEdges;
        const std::size_t enteringLinkCount = pPage->GetEdgesEntering_Up(enteringEdges);

        if (enteringLinkCount > 0)
        {
            // get the link
            IODEdge*                     pIEdge = enteringEdges.GetAt(0);
            PSS_DeliverableLinkSymbolBP* pLink  =
                    dynamic_cast<PSS_DeliverableLinkSymbolBP*>(static_cast<CODLinkComponent*>(pIEdge));

            if (!pLink)
                return NULL;

            // call the same function from the twin deliverable
            return pLink->GetSourceProcedure();
        }
    }

    // error, no connection found
    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcedureSymbolBP* PSS_DeliverableLinkSymbolBP::GetTargetProcedure() const
{
    // get the target connected symbol
    CODComponent* pComp = GetTargetComponent();

    PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<PSS_ProcedureSymbolBP*>(pComp);

    if (pProcedure)
        return pProcedure;

    PSS_DoorSymbolBP* pDoor = dynamic_cast<PSS_DoorSymbolBP*>(pComp);

    if (pDoor)
    {
        // locate the twin symbol previous connection
        if (!(pComp = pDoor->GetTwinDoorSymbol()))
            return NULL;

        CODEdgeArray      leavingEdges;
        const std::size_t leavingLinkCount = pDoor->GetEdgesLeaving_Down(leavingEdges);

        if (leavingLinkCount > 0)
        {
            // get the link
            IODEdge*                     pIEdge = leavingEdges.GetAt(0);
            PSS_DeliverableLinkSymbolBP* pLink  =
                    dynamic_cast<PSS_DeliverableLinkSymbolBP*>(static_cast<CODLinkComponent*>(pIEdge));

            if (!pLink)
                return NULL;

            // call the same function from the twin deliverable
            return pLink->GetTargetProcedure();
        }

        // error, no connection found
        return NULL;
    }

    PSS_PageSymbolBP* pPage = dynamic_cast<PSS_PageSymbolBP*>(pComp);

    if (pPage)
    {
        // locate the twin symbol previous connection
        if (!(pComp = pPage->GetTwinPageSymbol()))
            return NULL;

        CODEdgeArray      leavingEdges;
        const std::size_t leavingLinkCount = pPage->GetEdgesLeaving_Down(leavingEdges);

        if (leavingLinkCount > 0)
        {
            // get the link
            IODEdge*                     pIEdge = leavingEdges.GetAt(0);
            PSS_DeliverableLinkSymbolBP* pLink  =
                    dynamic_cast<PSS_DeliverableLinkSymbolBP*>(static_cast<CODLinkComponent*>(pIEdge));

            if (!pLink)
                return NULL;

            // call the same function from the twin deliverable
            return pLink->GetTargetProcedure();
        }
    }

    // error, no connection found
    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_DeliverableLinkSymbolBP::GetComingFromModel() const
{
    // get the source connected symbol
    CODComponent* pComp = GetSourceComponent();

    PSS_DoorSymbolBP* pDoor = dynamic_cast<PSS_DoorSymbolBP*>(pComp);

    if (pDoor)
    {
        // locate the twin symbol previous connection
        PSS_DoorSymbolBP* pSrcDoor = pDoor->GetTwinDoorSymbol();

        if (pSrcDoor)
            return pSrcDoor->GetDoorModel();
    }

    // error, no connection found
    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessSymbolBP* PSS_DeliverableLinkSymbolBP::GetComingFromProcess() const
{
    // get the coming from model
    PSS_ProcessGraphModelMdl* pModel = GetComingFromModel();

    if (pModel)
    {
        PSS_ProcessGraphModelMdl* pRootModel =
                dynamic_cast<PSS_ProcessGraphModelMdl*>(const_cast<PSS_DeliverableLinkSymbolBP*>(this)->GetRootModel());

        if (pRootModel)
        {
            // find the symbol linked with the door model
            CODComponentSet* pSet = pRootModel->FindSymbol(pModel);

            if (pSet)
            {
                const int count = pSet->GetSize();

                for (int i = 0; i < count; ++i)
                {
                    PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pSet->GetAt(i));

                    if (pProcess)
                        return pProcess;
                }
            }
        }
    }

    // error, no connection found
    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_DeliverableLinkSymbolBP::GetGoingToModel() const
{
    // get the target connected symbol
    CODComponent* pComp = GetTargetComponent();

    PSS_DoorSymbolBP* pDoor = dynamic_cast<PSS_DoorSymbolBP*>(pComp);

    if (pDoor)
    {
        // locate the previous twin symbol connection
        PSS_DoorSymbolBP* pSrcDoor = pDoor->GetTwinDoorSymbol();

        if (pSrcDoor)
            return pSrcDoor->GetDoorModel();
    }

    // error, no connection found
    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessSymbolBP* PSS_DeliverableLinkSymbolBP::GetGoingToProcess() const
{
    // get the going to model
    PSS_ProcessGraphModelMdl* pModel = GetGoingToModel();

    if (pModel)
    {
        PSS_ProcessGraphModelMdl* pRootModel =
                dynamic_cast<PSS_ProcessGraphModelMdl*>(const_cast<PSS_DeliverableLinkSymbolBP*>(this)->GetRootModel());

        if (pRootModel)
        {
            // find the symbol linked with the door model
            CODComponentSet* pSet = pRootModel->FindSymbol(pModel);

            if (pSet)
            {
                const int count = pSet->GetSize();

                for (int i = 0; i < count; ++i)
                {
                    PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pSet->GetAt(i));

                    if (pProcess)
                        return pProcess;
                }
            }
        }
    }

    // error, no connection found
    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::IsInitial() const
{
    // get the source connected symbol
    return dynamic_cast<PSS_StartSymbolBP*>(GetSourceComponent());
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::IsFinal() const
{
    // get the target connected symbol
    return dynamic_cast<PSS_StopSymbolBP*>(GetTargetComponent());
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::IsInterProcess() const
{
    // get the source and target connected doors
    return (dynamic_cast<PSS_DoorSymbolBP*>(GetSourceComponent()) || dynamic_cast<PSS_DoorSymbolBP*>(GetTargetComponent()));
}
//---------------------------------------------------------------------------
CODLabelComponent* PSS_DeliverableLinkSymbolBP::CreateLabel(const LPCTSTR          pText,
                                                            const OD_CONTROL_POINT ctrlPoint,
                                                            CDC*                   pDC)
{
    if (!UseDynamicArea())
        return PSS_LinkSymbol::CreateLabel(pText, ctrlPoint, pDC);

    std::unique_ptr<CODLabelComponent> pLabelComp(new PSS_SymbolLabel(ctrlPoint, true));
    pLabelComp->SetText(pText);

    if (!pLabelComp->Create(pDC))
        return NULL;

    pLabelComp->SetOrientationFlag(TRUE);
    pLabelComp->SetOrientation(ctrlPoint);

    CODLineOrientation propLineOrientation;
    pLabelComp->AddProperty(propLineOrientation);

    AddLabel(pLabelComp.get());

    return pLabelComp.release();
}
//---------------------------------------------------------------------------
BOOL PSS_DeliverableLinkSymbolBP::ContainsRule(const CString& ruleName) const
{
    const int ruleCount = m_Rules.GetRulesCount();

    for (int i = 0; i < ruleCount; ++i)
        if (m_Rules.GetRuleName(i) == ruleName)
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::CheckRulesSync(CStringArray& rulesList)
{
    CODModel* pModel = GetRootModel();

    if (!pModel)
        return;

    const int ruleCount = m_Rules.GetRulesCount();

    if (ruleCount > 0)
    {
        PSS_ProcessGraphModelMdlBP* pOwnerModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(GetOwnerModel());

        if (!pOwnerModel)
            return;

        PSS_LogicalRulesEntity* pMainRule = pOwnerModel->GetMainLogicalRules();

        for (int i = 0; i < ruleCount; ++i)
        {
            const CString safeName = GetRuleNameByGUID(pMainRule, m_Rules.GetRuleGUID(i));

            if (safeName.IsEmpty())
                rulesList.Add(m_Rules.GetRuleName(i));
        }
    }
}
//---------------------------------------------------------------------------
CString PSS_DeliverableLinkSymbolBP::GetRiskType(std::size_t index) const
{
    PSS_Application* pApplication = PSS_Application::Instance();

    if (!pApplication)
        return _T("");

    PSS_MainForm* pMainForm = pApplication->GetMainForm();

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
void PSS_DeliverableLinkSymbolBP::Serialize(CArchive& ar)
{
    // serialize the link symbol
    PSS_LinkSymbol::Serialize(ar);

    // only if the object is serialize from or to a document
    if (ar.m_pDocument)
    {
        m_Quantity.Serialize(ar);
        m_SimProperties.Serialize(ar);

        PSS_BaseDocument* pDoc = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

        if (pDoc && pDoc->GetDocumentStamp().GetInternalVersion() >= 27)
            m_Risks.Serialize(ar);

        if (ar.IsStoring() || (pDoc && pDoc->GetDocumentStamp().GetInternalVersion() >= 19))
            m_CostDeliverableProperties.Serialize(ar);
        else
        {
            // transfer the properties to new format
            PSS_CostPropertiesDeliverableBP_Beta1* pCostProps =
                    static_cast<PSS_CostPropertiesDeliverableBP_Beta1*>(GetProperty(ZS_BP_PROP_DELIVERABLE_COST));

            if (pCostProps)
            {
                SetProcessingTime    (pCostProps->GetProcessingTime());
                SetInWorkloadPercent (pCostProps->GetInWorkloadPercent());
                SetOutWorkloadPercent(pCostProps->GetOutWorkloadPercent());
                SetUnitaryCost       (pCostProps->GetUnitaryCost());
            }
        }

        if (ar.IsStoring())
        {
            m_UnitProp.Serialize(ar);
            m_Rules.Serialize(ar);
        }
        else
        {
            if (pDoc && pDoc->GetDocumentStamp().GetInternalVersion() >= 20)
                m_UnitProp.Serialize(ar);

            if (pDoc && pDoc->GetDocumentStamp().GetInternalVersion() >= 26)
                m_Rules.Serialize(ar);
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::OnPostCreation(CODModel* pModel, CODController* pCtrl)
{
    if (!PSS_LinkSymbol::OnPostCreation(pModel, pCtrl))
        return false;

    // check the symbols attached to the deliverable
    CODSymbolComponent* pDst = GetFollowingSymbol();
    CODSymbolComponent* pSrc = GetEnteringSymbol();

    if (pSrc && pDst)
    {
        PSS_DoorSymbolBP*      pDoorSrc      = dynamic_cast<PSS_DoorSymbolBP*>(pSrc);
        PSS_ProcedureSymbolBP* pProcedureDst = dynamic_cast<PSS_ProcedureSymbolBP*>(pDst);

        // check for door to procedure
        if (pDoorSrc && pProcedureDst)
        {
            DoDoorProcedureConnection(pDoorSrc, pProcedureDst, pModel);

            // check the status in order to set the right color
            CheckDeliverableStatus();
            return true;
        }

        PSS_ProcedureSymbolBP* pProcedureSrc = dynamic_cast<PSS_ProcedureSymbolBP*>(pSrc);
        PSS_DoorSymbolBP*      pDoorDst      = dynamic_cast<PSS_DoorSymbolBP*>(pDst);

        // check for procedure to door
        if (pProcedureSrc && pDoorDst)
        {
            DoProcedureDoorConnection(pProcedureSrc, pDoorDst, pModel);

            // check the status in order to set the right color
            CheckDeliverableStatus();
            return true;
        }

        PSS_PageSymbolBP* pPageSrc = dynamic_cast<PSS_PageSymbolBP*>(pSrc);

        // check for page to procedure
        if (pPageSrc && pProcedureDst)
        {
            DoPageProcedureConnection(pPageSrc, pProcedureDst, pModel);

            // check the status in order to set the right color
            CheckDeliverableStatus();
            return true;
        }

        PSS_PageSymbolBP* pPageDst = dynamic_cast<PSS_PageSymbolBP*>(pDst);

        // check for procedure to page
        if (pProcedureSrc && pPageDst)
        {
            DoProcedurePageConnection(pProcedureSrc, pPageDst, pModel);

            // check the status in order to set the right color
            CheckDeliverableStatus();
            return true;
        }

        PSS_ProcessSymbolBP* pProcessSrc = dynamic_cast<PSS_ProcessSymbolBP*>(pSrc);
        PSS_ProcessSymbolBP* pProcessDst = dynamic_cast<PSS_ProcessSymbolBP*>(pDst);

        // check for process to process
        if (pProcessSrc && pProcessDst)
        {
            DoProcessProcessConnection(pProcessSrc, pProcessDst, pModel);

            // check the status in order to set the right color
            CheckDeliverableStatus();
            return true;
        }
    }

    // check the status in order to set the right color
    CheckDeliverableStatus();
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::OnPreDelete(CODModel* pModel, CODController* pCtrl)
{
    PSS_Symbol* pDst = dynamic_cast<PSS_Symbol*>(GetFollowingSymbol());

    if (pDst)
        pDst->OnLinkDisconnect(this);

    PSS_Symbol* pSrc = dynamic_cast< PSS_Symbol*>(GetEnteringSymbol());

    if (pSrc)
        pSrc->OnLinkDisconnect(this);

    return true;
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::OnSymbolNameChange(const CString& oldName, const CString& newName)
{
    NotifyNameChange(oldName, newName);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::OnDropInternalPropertyItem(PSS_Property&                 srcProperty,
                                                             PSS_Property&                 dstProperty,
                                                             bool                          top2Down,
                                                             PSS_Properties::IPropertySet& props)
{
    // swap the rule list property items
    bool result = ::SwapInternalPropertyItem(srcProperty, dstProperty, top2Down, props, ZS_BP_PROP_RULELIST);

    // on success, return
    if (result)
        return true;

    // swap the rule property items
    result = ::SwapInternalPropertyItem(srcProperty, dstProperty, top2Down, props, ZS_BP_PROP_RULES);

    // succeeded?
    if (result)
    {
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

    // swap the text property items
    return ::SwapInternalPropertyItem(srcProperty, dstProperty, top2Down, props, ZS_BP_PROP_TEXTITEMLIST);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::OnPrePropertyChanged(const CString&                newValue,
                                                       PSS_Property&                 prop,
                                                       PSS_Properties::IPropertySet& props)
{
    // only local symbol may access to properties
    if (!IsLocal())
        return true;

    return PSS_LinkSymbol::OnPrePropertyChanged(newValue, prop, props);
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::OnPostPropertyChanged(PSS_Property& prop, PSS_Properties::IPropertySet& props, bool& refresh)
{
    // only local symbol may access to properties
    if (!IsLocal())
        return true;

    bool result = false;

    if (prop.GetCategoryID() == ZS_BP_PROP_TEXTITEMLIST)
    {
        PSS_Properties::IPropertyIterator it(&props);
        std::size_t                       counterEnableEmpty = 0;

        // iterate through the properties
        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            if (pProp->GetCategoryID() == ZS_BP_PROP_TEXTITEMLIST)
            {
                // if the string is not empty, enable the property
                if (!pProp->GetValueString().IsEmpty())
                    pProp->SetEnabled(true);

                // otherwise, check if the property was already enabled, and count it if yes
                if (pProp->GetValueString().IsEmpty())
                {
                    if (pProp->GetEnabled())
                        ++counterEnableEmpty;
                    else
                    if (counterEnableEmpty < 1)
                    {
                        pProp->SetEnabled(true);
                        ++counterEnableEmpty;
                    }

                    // if the counter is greather than 1, disable the empty property
                    if (counterEnableEmpty > 1)
                    {
                        --counterEnableEmpty;
                        pProp->SetEnabled(false);
                    }
                }
            }

        result = true;
    }
    else
    if (prop.GetCategoryID() == ZS_BP_PROP_RULELIST)
    {
        PSS_Properties::IPropertyIterator it(&props);
        std::size_t                       counterEnableEmpty = 0;

        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            if (pProp->GetCategoryID() == ZS_BP_PROP_RULELIST)
            {
                // if the string is not empty, enable the property
                if (!pProp->GetValueString().IsEmpty())
                    pProp->SetEnabled(true);

                // otherwise, check if the property was already enabled, and count it if yes
                if (pProp->GetValueString().IsEmpty())
                {
                    if (pProp->GetEnabled() == true)
                        ++counterEnableEmpty;
                    else
                    if (counterEnableEmpty < 1)
                    {
                        pProp->SetEnabled(true);
                        ++counterEnableEmpty;
                    }

                    // if the counter is greather than 1, disable the empty property
                    if (counterEnableEmpty > 1)
                    {
                        --counterEnableEmpty;
                        pProp->SetEnabled(false);
                    }
                }
            }

        result = true;
    }
    else
    if (prop.GetCategoryID() == ZS_BP_PROP_QUANTITY && prop.GetItemID() == M_Number_Year_ID)
    {
        // set the new value and equalize the information
        m_Quantity.SetAndCalculateQuantitiesBasedOnYear(prop.GetValueDouble());

        // save the equalizer value to the properties to avoidto work with wrong values in the equalizer
        SaveEqualizerToProperties(props);
        result = true;
    }
    else
    if (prop.GetCategoryID() == ZS_BP_PROP_UNIT && prop.GetItemID() == M_Unit_Name_ID)
    {
        PSS_Properties::IPropertyIterator it(&props);
        CString                           guid;

        // iterate through the properties and get the GUID
        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == M_Unit_GUID_ID)
            {
                guid = pProp->GetValueString();
                break;
            }

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
    else
    if (prop.GetCategoryID() == ZS_BP_PROP_DELIVERABLE_COST && prop.GetItemID() == M_Cost_Deliv_Out_Workload_Percent_ID)
    {
        SetVisualInfo(int(prop.GetValueFloat() * 100.0f));
        RedrawSymbol();
    }

    if (!result)
        return PSS_LinkSymbol::OnPostPropertyChanged(prop, props, refresh);

    return result;
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::OnConnect(CODConnection* pConnection)
{
    PSS_LinkSymbol::OnConnect(pConnection);

    PSS_Symbol* pDst = dynamic_cast<PSS_Symbol*>(GetFollowingSymbol());

    if (pDst && pDst->GetDependentPortOnConnection(pConnection))
        pDst->OnLinkConnect(this);
    else
    {
        PSS_Symbol* pSrc = dynamic_cast<PSS_Symbol*>(GetEnteringSymbol());

        if (pSrc && pSrc->GetDependentPortOnConnection(pConnection))
            pSrc->OnLinkConnect(this);
    }

    // check the status in order to set the right color
    CheckDeliverableStatus();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::OnDisconnect(CODConnection* pConnection)
{
    PSS_Symbol* pDst = dynamic_cast<PSS_Symbol*>(GetFollowingSymbol());

    if (pDst && pDst->GetDependentPortOnConnection(pConnection))
        pDst->OnLinkDisconnect(this);
    else
    {
        PSS_Symbol* pSrc = dynamic_cast<PSS_Symbol*>(GetEnteringSymbol());

        if (pSrc && pSrc->GetDependentPortOnConnection(pConnection))
            pSrc->OnLinkDisconnect(this);
    }

    PSS_LinkSymbol::OnDisconnect(pConnection);

    // check the status in order to set the right color
    CheckDeliverableStatus();
}
//---------------------------------------------------------------------------
BOOL PSS_DeliverableLinkSymbolBP::OnConnectionMove(CODConnection* pConnection)
{
    const BOOL result = PSS_LinkSymbol::OnConnectionMove(pConnection);

    // check the status in order to set the right color
    CheckDeliverableStatus();

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_DeliverableLinkSymbolBP::OnRemoveDependent(CODConnection* pConnection)
{
    const BOOL result = PSS_LinkSymbol::OnRemoveDependent(pConnection);

    // check the status in order to set the right color
    CheckDeliverableStatus();

    return result;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    toolTipText.Format(IDS_FS_BPDELIVERABLE_TOOLTIP,
                       (const char*)GetSymbolName(),
                       (const char*)GetSymbolComment(),
                       (const char*)GetSymbolReferenceNumberStr());

    if (mode == PSS_ToolTip::IE_TT_Design)
    {
        const bool notConnectedFollowing = !GetFollowingSymbol();
        const bool notConnectedEntering  = !GetEnteringSymbol();

        if (notConnectedFollowing || notConnectedEntering)
        {
            toolTipText += _T("\n");

            if (notConnectedEntering)
            {
                CString str;
                str.LoadString(IDS_FS_BPDELIVERABLE_MISSING_INCONX_TOOLTIP);
                toolTipText += (str + _T("\n"));
            }

            if (notConnectedFollowing)
            {
                CString str;
                str.LoadString(IDS_FS_BPDELIVERABLE_MISSING_OUTCONX_TOOLTIP);
                toolTipText += str;
            }
        }
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::OnAddNewRisk(PSS_Property&                 prop,
                                               CString&                      value,
                                               PSS_Properties::IPropertySet& props,
                                               bool&                         refresh)
{
    // add a new risk
    if (AddNewRisk() >= 0)
    {
        // set the refresh flag to true
        refresh = true;
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::OnDelCurrentRisk(PSS_Property&                 prop,
                                                   CString&                      value,
                                                   PSS_Properties::IPropertySet& props,
                                                   bool&                         refresh)
{
    const int count = GetRiskCount();

    if (count <= 1)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOTDELETE_ALLRISKS, MB_OK);
        return;
    }

    const int index = prop.GetCategoryID() - ZS_BP_PROP_RISK;

    // delete the currently selected risk
    if (DeleteRisk(index))
    {
        refresh = true;
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::NotifyNameChange(const CString&              oldName,
                                                   const CString&              newName,
                                                   PSS_ProcessGraphModelMdlBP* pRootModel)
{
    // nothing to do if names are empty
    if (oldName.IsEmpty() || newName.IsEmpty())
        return;

    // if the source model is empty, search in the entire document
    if (!pRootModel)
        // get the root model controller
        pRootModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(GetRootModel());

    if (!pRootModel)
        return;

    // get the pages contained in the model controller
    PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pRootModel->GetPageSet();

    if (!pSet)
        return;

    PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(pSet);

    // iterate through children pages contained in the model controller
    for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
    {
        // get the current page model controller
        PSS_ProcessGraphModelMdlBP* pCurModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

        if (pCurModel)
        {
            // get the symbols contained in the model controller
            CODComponentSet* pCompSet = pCurModel->GetComponents();

            if (pCompSet)
                // iterate through the symbols
                for (int i = 0; i < pCompSet->GetSize(); ++i)
                {
                    PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pCompSet->GetAt(i));

                    // is a valid process?
                    if (pProcess)
                    {
                        // get the process model controller
                        PSS_ProcessGraphModelMdlBP* pChildModel =
                                dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcess->GetModel());

                        // call recursively the NotifyNameChange() function until all pages were visited
                        NotifyNameChange(oldName, newName, pChildModel);

                        // notify the process that the deliverable name changed
                        pProcess->OnDeliverableNameChange(oldName, newName);
                    }
                }
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::CreateSymbolName()
{
    // create the area box as a label
    CODLabelComponent* pLabelComp = CODLinkComponent::CreateLabel(_T(""));

    if (!pLabelComp)
        return false;

    // use dynamic area?
    if (UseDynamicArea())
    {
        pLabelComp->SetName(M_EditAreaComponentControlLabel);
        pLabelComp->SetValue(OD_PROP_AUTOSIZE, TRUE);
        pLabelComp->SetValue(OD_PROP_WORDBREAK, TRUE);
        pLabelComp->SetValue(OD_PROP_MULTILINE, TRUE);
        pLabelComp->SetValue(OD_PROP_TRANSPARENT, TRUE);
        pLabelComp->SetTextBox(CRect(0, 0, 100, 40));

        CODFontProperties* pFontProp = static_cast<CODFontProperties*>(pLabelComp->GetProperty(OD_PROP_FONT));

        if (pFontProp)
        {
            std::unique_ptr<CODFontProperties> pNewFontProp(new CODFontProperties(*pFontProp));
            pNewFontProp->SetFaceName(_T("Arial"));
            pNewFontProp->SetWeight(FW_BOLD);
            pNewFontProp->SetPointSize(8);
            pLabelComp->SetProperty(pNewFontProp.get());
            pNewFontProp.release();
        }

        CODFillProperties* pFillProps = static_cast<CODFillProperties*>(pLabelComp->GetProperty(OD_PROP_FILL));

        if (pFillProps)
        {
            std::unique_ptr<CODFillProperties> pNewFillProps(new CODFillProperties(*pFillProps));
            pNewFillProps->SetTransparent(TRUE);
            pLabelComp->SetProperty(pNewFillProps.get());
            pNewFillProps.release();
        }

        // create the symbol name text component
        std::unique_ptr<CODTextComponent> pTextComp(new CODTextComponent());
        pTextComp->Create(pLabelComp->GetBounds(), NULL);
        pTextComp->SetName(M_SymbolNameComponentControlLabel);

        // create the symbol line component
        std::unique_ptr<CODLineProperties> pLineProps(new CODLineProperties());
        pLineProps->SetTransparent(TRUE);
        pTextComp->SetProperty(pLineProps.get());
        pLineProps.release();

        // can't be selected
        CODEditProperties* pEdit = static_cast<CODEditProperties*>(pTextComp->GetProperty(OD_PROP_EDIT));

        if (pEdit)
        {
            std::unique_ptr<CODEditProperties> pNewEditProps(new CODEditProperties(*pEdit));
            pNewEditProps->SetCanSelect(FALSE);
            pTextComp->SetProperty(pNewEditProps.get());
            pNewEditProps.release();
        }

        // change the fill color
        pFillProps = static_cast<CODFillProperties*>(pTextComp->GetProperty(OD_PROP_FILL));

        if (pFillProps)
        {
            std::unique_ptr<CODFillProperties> pFillProps(new CODFillProperties(*pFillProps));
            pFillProps->SetColor(RGB(192, 220, 192));
            pTextComp->SetProperty(pFillProps.get());
            pFillProps.release();
        }

        pTextComp->SetValue(OD_PROP_AUTOSIZE, TRUE);
        pTextComp->SetValue(OD_PROP_WORDBREAK, TRUE);
        pTextComp->SetValue(OD_PROP_MULTILINE, TRUE);
        pTextComp->SetValue(OD_PROP_TRANSPARENT, TRUE);
        pTextComp->SetTextBox(CRect(0, 0, 100, 40));

        pFontProp = static_cast<CODFontProperties*>(pTextComp->GetProperty(OD_PROP_FONT));

        if (pFontProp)
        {
            std::unique_ptr<CODFontProperties> pNewFontProp(new CODFontProperties(*pFontProp));
            pNewFontProp->SetFaceName(_T("Arial"));
            pNewFontProp->SetWeight(FW_BOLD);
            pNewFontProp->SetPointSize(8);
            pTextComp->SetProperty(pNewFontProp.get());
            pNewFontProp.release();
        }

        AppendChild(pTextComp.get());
        pTextComp.release();

        // create the symbol comment text component
        pTextComp.reset(new CODTextComponent());
        pTextComp->Create(pLabelComp->GetBounds(), NULL);
        pTextComp->SetName(M_CommentComponentControlLabel);

        pLineProps.reset(new CODLineProperties());
        pLineProps->SetTransparent(TRUE);
        pTextComp->SetProperty(pLineProps.get());
        pLineProps.release();

        // can't be selected
        pEdit = static_cast<CODEditProperties*>(pTextComp->GetProperty(OD_PROP_EDIT));

        if (pEdit)
        {
            std::unique_ptr<CODEditProperties> pNewEditProps(new CODEditProperties(*pEdit));
            pNewEditProps->SetCanSelect(FALSE);
            pTextComp->SetProperty(pNewEditProps.get());
            pNewEditProps.release();
        }

        // Change the fill color
        pFillProps = static_cast<CODFillProperties*>(pTextComp->GetProperty(OD_PROP_FILL));

        if (pFillProps)
        {
            std::unique_ptr<CODFillProperties> pNewFillProps(new CODFillProperties(*pFillProps));
            pNewFillProps->SetColor(RGB(192, 220, 192));
            pTextComp->SetProperty(pNewFillProps.get());
            pNewFillProps.release();
        }

        pTextComp->SetValue(OD_PROP_AUTOSIZE, TRUE);
        pTextComp->SetValue(OD_PROP_WORDBREAK, TRUE);
        pTextComp->SetValue(OD_PROP_MULTILINE, TRUE);
        pTextComp->SetValue(OD_PROP_TRANSPARENT, TRUE);
        pTextComp->SetTextBox(CRect(0, 0, 100, 40));

        pFontProp = static_cast<CODFontProperties*>(pTextComp->GetProperty(OD_PROP_FONT));

        if (pFontProp)
        {
            std::unique_ptr<CODFontProperties> pNewFontProp(new CODFontProperties(*pFontProp));
            pNewFontProp->SetFaceName(_T("Arial"));
            pNewFontProp->SetWeight(FW_BOLD);
            pNewFontProp->SetPointSize(8);
            pTextComp->SetProperty(pNewFontProp.get());
            pNewFontProp.release();
        }

        AppendChild(pTextComp.get());
        pTextComp.release();

        // create the symbol attribute text component
        pTextComp.reset(new CODTextComponent());
        pTextComp->Create(pLabelComp->GetBounds(), NULL);
        pTextComp->SetName(M_AttributeAreaComponentLabel);

        pLineProps.reset(new CODLineProperties());
        pLineProps->SetTransparent(TRUE);
        pTextComp->SetProperty(pLineProps.get());
        pLineProps.release();

        // can't be selected
        pEdit = static_cast<CODEditProperties*>(pTextComp->GetProperty(OD_PROP_EDIT));

        if (pEdit)
        {
            std::unique_ptr<CODEditProperties> pNewEditProps(new CODEditProperties(*pEdit));
            pNewEditProps->SetCanSelect(FALSE);
            pTextComp->SetProperty(pNewEditProps.get());
            pNewEditProps.release();
        }

        // change the fill color
        pFillProps = static_cast<CODFillProperties*>(pTextComp->GetProperty(OD_PROP_FILL));

        if (pFillProps)
        {
            std::unique_ptr<CODFillProperties> pNewFillProps(new CODFillProperties(*pFillProps));
            pNewFillProps->SetColor(RGB(192, 220, 192));
            pTextComp->SetProperty(pNewFillProps.get());
            pNewFillProps.release();
        }

        pTextComp->SetValue(OD_PROP_AUTOSIZE, TRUE);
        pTextComp->SetValue(OD_PROP_WORDBREAK, TRUE);
        pTextComp->SetValue(OD_PROP_MULTILINE, TRUE);
        pTextComp->SetValue(OD_PROP_TRANSPARENT, TRUE);
        pTextComp->SetValue(OD_PROP_HORZ_ALIGNMENT, DT_LEFT);
        pTextComp->SetValue(OD_PROP_VERT_ALIGNMENT, DT_TOP);
        pTextComp->SetTextBox(CRect(0, 0, 100, 40));

        pFontProp = static_cast<CODFontProperties*>(pTextComp->GetProperty(OD_PROP_FONT));

        if (pFontProp)
        {
            std::unique_ptr<CODFontProperties> pNewFontProp(new CODFontProperties(*pFontProp));
            pNewFontProp->SetFaceName(_T("Arial"));
            pNewFontProp->SetWeight(FW_BOLD);
            pNewFontProp->SetPointSize(8);
            pTextComp->SetProperty(pNewFontProp.get());
            pNewFontProp.release();
        }

        AppendChild(pTextComp.get());
        pTextComp.release();
    }
    else
    {
        // no dynamic attributes
        pLabelComp->SetName(M_SymbolNameComponentControlLabel);
        pLabelComp->SetTextBox(CRect(0, 0, 100, 40));

        CODFontProperties* pFontProp = static_cast<CODFontProperties*>(pLabelComp->GetProperty(OD_PROP_FONT));

        if (pFontProp)
        {
            std::unique_ptr<CODFontProperties> pNewFontProps(new CODFontProperties(*pFontProp));
            pNewFontProps->SetFaceName(_T("Arial"));
            pNewFontProps->SetWeight(FW_BOLD);
            pNewFontProps->SetPointSize(8);
            pLabelComp->SetProperty(pNewFontProps.get());
            pNewFontProps.release();
        }

        pLabelComp->SetValue(OD_PROP_AUTOSIZE, TRUE);
        pLabelComp->SetValue(OD_PROP_WORDBREAK, TRUE);
        pLabelComp->SetValue(OD_PROP_MULTILINE, TRUE);
        pLabelComp->SetValue(OD_PROP_HORZ_ALIGNMENT, DT_CENTER);
        pLabelComp->SetValue(OD_PROP_VERT_ALIGNMENT, DT_TOP);

        // Change the fill color
        CODFillProperties* pFillProps = static_cast<CODFillProperties*>(pLabelComp->GetProperty(OD_PROP_FILL));

        if (pFillProps)
        {
            std::unique_ptr<CODFillProperties> pNewFillProps(new CODFillProperties(*pFillProps));
            pNewFillProps->SetColor(RGB(192, 220, 192));
            pLabelComp->SetProperty(pNewFillProps.get());
            pNewFillProps.release();
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::DoDoorProcedureConnection(PSS_DoorSymbolBP*      pSrc,
                                                            PSS_ProcedureSymbolBP* pDst,
                                                            CODModel*              pModel)
{
    PSS_ProcessGraphModelMdlBP* pProcGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pModel);

    if (!pProcGraphModel)
        return true;

    PSS_ProcessGraphModelMdlBP* pSrcChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSrc->GetChildModel());

    if (!pSrcChildModel)
        return true;

    // the door is linked with a model
    CODNodeArray      nodes;
    const std::size_t elementCount = pSrcChildModel->GetBPDoorSymbols(nodes);

    for (std::size_t i = 0; i < elementCount; ++i)
    {
        IODNode*          pINode = nodes.GetAt(i);
        PSS_DoorSymbolBP* pDoor  = static_cast<PSS_DoorSymbolBP*>(pINode);

        if (!pDoor || !pDoor->GetChildModel())
            continue;

        // the door symbol contains another door with a model linked to this model?
        if (pDoor->GetTwinDoorReferenceNumber() == pSrc->GetSymbolReferenceNumber())
        {
            CODEdgeArray      enteringEdges;
            const std::size_t enteringLinkCount = pDoor->GetEdgesEntering_Up(enteringEdges);

            if (enteringLinkCount > 0)
            {
                // get the link
                IODEdge*                     pIEdge       = enteringEdges.GetAt(0);
                PSS_DeliverableLinkSymbolBP* pLinkIndexed =
                        dynamic_cast<PSS_DeliverableLinkSymbolBP*>(static_cast<CODLinkComponent*>(pIEdge));

                if (!pLinkIndexed)
                    return false;

                // define as a reference
                AssignReferenceSymbol(pLinkIndexed);
            }

            // return without error, independently if a link was found or not
            return true;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::DoProcedureDoorConnection(PSS_ProcedureSymbolBP* pSrc,
                                                            PSS_DoorSymbolBP*      pDst,
                                                            CODModel*              pModel)
{
    PSS_ProcessGraphModelMdlBP* pProcGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pModel);

    if (!pProcGraphModel)
        return true;

    PSS_ProcessGraphModelMdlBP* pDstChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDst->GetChildModel());

    if (!pDstChildModel)
        return true;

    // the door is linked with a model
    CODNodeArray      nodes;
    const std::size_t elementCount = pDstChildModel->GetBPDoorSymbols(nodes);

    for (std::size_t i = 0; i < elementCount; ++i)
    {
        IODNode*          pINode = nodes.GetAt(i);
        PSS_DoorSymbolBP* pDoor  = static_cast<PSS_DoorSymbolBP*>(pINode);

        if (!pDoor || !pDoor->GetChildModel())
            continue;

        // do the door symbol contains another door with a model linked to this model?
        if (pDoor->GetTwinDoorReferenceNumber() == pDst->GetSymbolReferenceNumber())
        {
            CODEdgeArray      leavingEdges;
            const std::size_t leavingLinkCount = pDoor->GetEdgesLeaving_Down(leavingEdges);

            if (leavingLinkCount > 0)
            {
                // get the link
                IODEdge*                     pIEdge       = leavingEdges.GetAt(0);
                PSS_DeliverableLinkSymbolBP* pLinkIndexed =
                        dynamic_cast<PSS_DeliverableLinkSymbolBP*>(static_cast<CODLinkComponent*>(pIEdge));

                if (!pLinkIndexed)
                    return false;

                // define as a reference
                AssignReferenceSymbol(pLinkIndexed);
            }

            // return without error, independently if a link was found or not
            return true;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::DoPageProcedureConnection(PSS_PageSymbolBP*      pSrc,
                                                            PSS_ProcedureSymbolBP* pDst,
                                                            CODModel*              pModel)
{
    PSS_ProcessGraphModelMdlBP* pProcGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pModel);

    if (!pProcGraphModel)
        return true;

    PSS_ProcessGraphModelMdlBP* pSrcPageModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSrc->GetPageModel());

    if (!pSrcPageModel)
        return true;

    // the page is linked with a model
    CODNodeArray      nodes;
    const std::size_t elementCount = pSrcPageModel->GetBPPageSymbols(nodes);

    for (std::size_t i = 0; i < elementCount; ++i)
    {
        IODNode*          pINode = nodes.GetAt(i);
        PSS_PageSymbolBP* pPage  = static_cast<PSS_PageSymbolBP*>(pINode);

        if (!pPage || !pPage->GetPageModel())
            continue;

        // the page symbol contains a page with a reference number linked to this model?
        if (pPage->GetTwinPageReferenceNumber() == pSrc->GetSymbolReferenceNumber())
        {
            CODEdgeArray      enteringEdges;
            const std::size_t enteringLinkCount = pPage->GetEdgesEntering_Up(enteringEdges);

            if (enteringLinkCount > 0)
            {
                // get the link
                IODEdge*                     pIEdge       = enteringEdges.GetAt(0);
                PSS_DeliverableLinkSymbolBP* pLinkIndexed =
                        dynamic_cast<PSS_DeliverableLinkSymbolBP*>(static_cast<CODLinkComponent*>(pIEdge));

                if (!pLinkIndexed)
                    return false;

                // define as a reference
                AssignReferenceSymbol(pLinkIndexed);
            }

            // return without error, independently if a link was found or not
            return true;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::DoProcedurePageConnection(PSS_ProcedureSymbolBP* pSrc,
                                                            PSS_PageSymbolBP*      pDst,
                                                            CODModel*              pModel)
{
    PSS_ProcessGraphModelMdlBP* pProcGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pModel);

    if (!pProcGraphModel)
        return true;

    PSS_ProcessGraphModelMdlBP* pDstPageModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDst->GetPageModel());

    if (!pDstPageModel)
        return true;

    // the page is linked with a model
    CODNodeArray      nodes;
    const std::size_t elementCount = pDstPageModel->GetBPPageSymbols(nodes);

    for (std::size_t i = 0; i < elementCount; ++i)
    {
        IODNode*          pINode = nodes.GetAt(i);
        PSS_PageSymbolBP* pPage  = static_cast<PSS_PageSymbolBP*>(pINode);

        if (!pPage || !pPage->GetPageModel())
            continue;

        // the page symbol contains a page with a reference number linked to this model?
        if (pPage->GetTwinPageReferenceNumber() == pDst->GetSymbolReferenceNumber())
        {
            CODEdgeArray      leavingEdges;
            const std::size_t leavingLinkCount = pPage->GetEdgesLeaving_Down(leavingEdges);

            if (leavingLinkCount > 0)
            {
                // get the link
                IODEdge*          pIEdge       = leavingEdges.GetAt(0);
                CODLinkComponent* pLinkIndexed =
                        dynamic_cast<PSS_DeliverableLinkSymbolBP*>(static_cast<CODLinkComponent*>(pIEdge));

                if (!pLinkIndexed)
                    return false;

                // define as a reference
                AssignReferenceSymbol(pLinkIndexed);
            }

            // return without error, independently if a link was found or not
            return true;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_DeliverableLinkSymbolBP::DoProcessProcessConnection(PSS_ProcessSymbolBP* pSrc,
                                                             PSS_ProcessSymbolBP* pDst,
                                                             CODModel*            pModel)
{
    PSS_ProcessGraphModelMdlBP* pProcGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pModel);

    if (!pProcGraphModel)
        return true;

    PSS_ProcessGraphModelMdlBP* pSrcChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSrc->GetChildModel());

    if (!pSrcChildModel)
        return true;

    PSS_ProcessGraphModelMdlBP* pDstChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDst->GetChildModel());

    if (!pDstChildModel)
        return true;

    CODNodeArray nodes;
    std::size_t  elementCount = pDstChildModel->GetBPDoorSymbols(nodes, true);

    // get all door symbols in destination process
    for (std::size_t i = 0; i < elementCount; ++i)
    {
        // for each door symbol, keep only entering up deliverable
        IODNode*          pINode = nodes.GetAt(i);
        PSS_DoorSymbolBP* pDoor  = static_cast<PSS_DoorSymbolBP*>(pINode);

        if (!pDoor || !pDoor->GetChildModel())
            continue;

        PSS_DeliverableLinkSymbolBP* pLinkIndexed = NULL;
        CODEdgeArray                 leavingEdges;
        const std::size_t            leavingLinkCount = pDoor->GetEdgesLeaving_Down(leavingEdges);

        // if entering link, check if it's a deliverable
        if (leavingLinkCount > 0)
        {
            // get the link
            IODEdge* pIEdge = leavingEdges.GetAt(0);
            pLinkIndexed    = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(static_cast<CODLinkComponent*>(pIEdge));
        }

        // if no link or if not a deliverable, remove it from the array, and decrement the index and element counts
        if (!pLinkIndexed)
        {
            nodes.RemoveAt(i);
            --i;
            --elementCount;
        }
    }

    // if still door symbols available
    if (nodes.GetSize() > 0)
    {
        PSS_DoorSymbolBP* pDoorSelected = NULL;
        CODLinkComponent* pLinkSelected = NULL;

        // If more than one symbol are remaining, ask the user to select which one he would like to assign
        if (nodes.GetSize() > 1)
        {
            // filter object classes
            PSS_RuntimeClassSet rtClasses;
            rtClasses.Add(RUNTIME_CLASS(PSS_PageSymbolBP));
            rtClasses.Add(RUNTIME_CLASS(PSS_ProcessSymbolBP));
            rtClasses.Add(RUNTIME_CLASS(PSS_DeliverableLinkSymbolBP));

            PSS_SelectModelSymbolDlg dlg(pDstChildModel,
                                         IDS_SYMBOL_SELECTDELIVERABLE,
                                         RUNTIME_CLASS(PSS_DeliverableLinkSymbolBP),
                                         &rtClasses);

            if (dlg.DoModal() == IDOK)
                pLinkSelected = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(dlg.GetSelectedSymbol());
        }
        else
        {
            // otherwise, select the first door symbol
            IODNode* pINode = nodes.GetAt(0);
            pDoorSelected   = static_cast<PSS_DoorSymbolBP*>(pINode);
        }

        // if no door selected and no link selected, show a warning message and select the first door
        if (!pDoorSelected && !pLinkSelected)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_P2P_FIRSTDELIVERABLE_SELECTED, MB_OK);
            IODNode* pINode = nodes.GetAt(0);
            pDoorSelected   = static_cast<PSS_DoorSymbolBP*>(pINode);
        }

        // if no link selected
        if (!pLinkSelected)
        {
            if (!pDoorSelected || !pDoorSelected->GetChildModel())
                return false;

            CODEdgeArray      leavingEdges;
            const std::size_t linkCount = pDoorSelected->GetEdgesLeaving_Down(leavingEdges);

            if (linkCount > 0)
            {
                // get the link
                IODEdge* pIEdge = leavingEdges.GetAt(0);
                pLinkSelected   = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(static_cast<CODLinkComponent*>(pIEdge));
            }
        }

        if (!pLinkSelected)
            return true;

        // define as a reference
        AssignReferenceSymbol(pLinkSelected);
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::CheckDeliverableStatus()
{
    // notify the owner model about symbol changes
    PSS_ProcessGraphModelMdl* pRootModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

    if (pRootModel && pRootModel->IsInCutOperation())
        return;

    // get the symbols attached to the deliverable
    CODSymbolComponent* pDst = GetFollowingSymbol();
    CODSymbolComponent* pSrc = GetEnteringSymbol();

    // set the right symbol color according to if the symbols are correctly connected or not
    ShowInError(!pSrc || !pDst);
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SavePropertiesToQuantity(const PSS_Properties::IPropertySet& props)
{
    PSS_Properties::IPropertyIterator it(&props);

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_QUANTITY)
        {
            const int itemID = pProp->GetItemID();

            if (itemID == M_Locked_Year_ID      ||
                itemID == M_Locked_January_ID   ||
                itemID == M_Locked_February_ID  ||
                itemID == M_Locked_March_ID     ||
                itemID == M_Locked_April_ID     ||
                itemID == M_Locked_May_ID       ||
                itemID == M_Locked_June_ID      ||
                itemID == M_Locked_July_ID      ||
                itemID == M_Locked_August_ID    ||
                itemID == M_Locked_September_ID ||
                itemID == M_Locked_October_ID   ||
                itemID == M_Locked_November_ID  ||
                itemID == M_Locked_December_ID  ||
                itemID == M_Force_Equalizer_ID)
                m_Quantity.SetValue(itemID, (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo()) ? 1 : 0);
            else
                switch (pProp->GetValueType())
                {
                    case PSS_Property::IE_VT_String:   m_Quantity.SetValue(pProp->GetItemID(),            pProp->GetValueString());  break;
                    case PSS_Property::IE_VT_Double:   m_Quantity.SetValue(pProp->GetItemID(), float(     pProp->GetValueDouble())); break;
                    case PSS_Property::IE_VT_Float:    m_Quantity.SetValue(pProp->GetItemID(),            pProp->GetValueFloat());   break;
                    case PSS_Property::IE_VT_Date:     m_Quantity.SetValue(pProp->GetItemID(), float(DATE(pProp->GetValueDate())));  break;
                    case PSS_Property::IE_VT_TimeSpan:
                    case PSS_Property::IE_VT_Duration: THROW("Unsupported value");
                }
        }

    // calculate all percents, it's necessary to equalize
    m_Quantity.CalculatePercents();
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SetNewNumberAndEqualize(const PSS_Property& prop, const PSS_Properties::IPropertySet& props)
{
    PSS_Properties::IPropertyIterator it(&props);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        // continue until the property to change was found
        if (!pProp || pProp->GetCategoryID() != ZS_BP_PROP_QUANTITY || pProp->GetItemID() != prop.GetItemID())
            continue;

        switch (pProp->GetItemID())
        {
            case M_Number_Year_ID:      m_Quantity.SetAndCalculateQuantitiesBasedOnYear     (prop.GetValueDouble()); return;
            case M_Number_January_ID:   m_Quantity.SetAndCalculateQuantitiesBasedOnJanuary  (prop.GetValueDouble()); return;
            case M_Number_February_ID:  m_Quantity.SetAndCalculateQuantitiesBasedOnFebruary (prop.GetValueDouble()); return;
            case M_Number_March_ID:     m_Quantity.SetAndCalculateQuantitiesBasedOnMarch    (prop.GetValueDouble()); return;
            case M_Number_April_ID:     m_Quantity.SetAndCalculateQuantitiesBasedOnApril    (prop.GetValueDouble()); return;
            case M_Number_May_ID:       m_Quantity.SetAndCalculateQuantitiesBasedOnMay      (prop.GetValueDouble()); return;
            case M_Number_June_ID:      m_Quantity.SetAndCalculateQuantitiesBasedOnJune     (prop.GetValueDouble()); return;
            case M_Number_July_ID:      m_Quantity.SetAndCalculateQuantitiesBasedOnJuly     (prop.GetValueDouble()); return;
            case M_Number_August_ID:    m_Quantity.SetAndCalculateQuantitiesBasedOnAugust   (prop.GetValueDouble()); return;
            case M_Number_September_ID: m_Quantity.SetAndCalculateQuantitiesBasedOnSeptember(prop.GetValueDouble()); return;
            case M_Number_October_ID:   m_Quantity.SetAndCalculateQuantitiesBasedOnOctober  (prop.GetValueDouble()); return;
            case M_Number_November_ID:  m_Quantity.SetAndCalculateQuantitiesBasedOnNovember (prop.GetValueDouble()); return;
            case M_Number_December_ID:  m_Quantity.SetAndCalculateQuantitiesBasedOnDecember (prop.GetValueDouble()); return;
            default:                                                                                                 return;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::SaveEqualizerToProperties(PSS_Properties::IPropertySet& props)
{
    PSS_Properties::IPropertyIterator it(&props);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        if (!pProp || pProp->GetCategoryID() != ZS_BP_PROP_QUANTITY)
            continue;

        switch (pProp->GetItemID())
        {
            case M_Number_Year_ID:      pProp->SetValueDouble(m_Quantity.GetNumberYear());                                                                                   break;
            case M_Number_January_ID:   pProp->SetValueDouble(m_Quantity.GetNumberJanuary());                                                                                break;
            case M_Number_February_ID:  pProp->SetValueDouble(m_Quantity.GetNumberFebruary());                                                                               break;
            case M_Number_March_ID:     pProp->SetValueDouble(m_Quantity.GetNumberMarch());                                                                                  break;
            case M_Number_April_ID:     pProp->SetValueDouble(m_Quantity.GetNumberApril());                                                                                  break;
            case M_Number_May_ID:       pProp->SetValueDouble(m_Quantity.GetNumberMay());                                                                                    break;
            case M_Number_June_ID:      pProp->SetValueDouble(m_Quantity.GetNumberJune());                                                                                   break;
            case M_Number_July_ID:      pProp->SetValueDouble(m_Quantity.GetNumberJuly());                                                                                   break;
            case M_Number_August_ID:    pProp->SetValueDouble(m_Quantity.GetNumberAugust());                                                                                 break;
            case M_Number_September_ID: pProp->SetValueDouble(m_Quantity.GetNumberSeptember());                                                                              break;
            case M_Number_October_ID:   pProp->SetValueDouble(m_Quantity.GetNumberOctober());                                                                                break;
            case M_Number_November_ID:  pProp->SetValueDouble(m_Quantity.GetNumberNovember());                                                                               break;
            case M_Number_December_ID:  pProp->SetValueDouble(m_Quantity.GetNumberDecember());                                                                               break;
            case M_Locked_Year_ID:                                                                                                                                           break;
            case M_Locked_January_ID:   pProp->SetValueString(m_Quantity.GetLockNumberJanuary()   ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_February_ID:  pProp->SetValueString(m_Quantity.GetLockNumberFebruary()  ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_March_ID:     pProp->SetValueString(m_Quantity.GetLockNumberMarch()     ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_April_ID:     pProp->SetValueString(m_Quantity.GetLockNumberApril()     ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_May_ID:       pProp->SetValueString(m_Quantity.GetLockNumberMay()       ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_June_ID:      pProp->SetValueString(m_Quantity.GetLockNumberJune()      ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_July_ID:      pProp->SetValueString(m_Quantity.GetLockNumberJuly()      ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_August_ID:    pProp->SetValueString(m_Quantity.GetLockNumberAugust()    ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_September_ID: pProp->SetValueString(m_Quantity.GetLockNumberSeptember() ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_October_ID:   pProp->SetValueString(m_Quantity.GetLockNumberOctober()   ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_November_ID:  pProp->SetValueString(m_Quantity.GetLockNumberNovember()  ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Locked_December_ID:  pProp->SetValueString(m_Quantity.GetLockNumberDecember()  ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
            case M_Force_Equalizer_ID:  pProp->SetValueString(m_Quantity.GetForceEqualizer()      ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()); break;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_DeliverableLinkSymbolBP::AdjustPoints()
{
    if (m_pILinkShape)
    {
        CODPortComponent*       pSourcePort = GetSourcePort();
        CODPortComponent*       pTargetPort = GetTargetPort();
        CODOrthogonalLinkShape* pLinkShape  = static_cast<CODOrthogonalLinkShape*>(m_pILinkShape);

        if (pLinkShape)
        {
            m_pILinkShape->Dock(pSourcePort, pTargetPort);
            return;
        }

        const int pointCount = pLinkShape->GetPointCount();

        if (pointCount < 2)
            return;

        int            spacing          = 0;
        CODComponent*  pParentLinkShape = pLinkShape->GetParent();
        CODIntProperty propSpacing;

        if (pParentLinkShape)
            spacing = (pParentLinkShape->GetProperty(OD_PROP_LINK_SPACING, propSpacing) ?
                                                     propSpacing.GetValue() : odg_nDefaultLinkSpacing);

        CPoint        ptTail    = pLinkShape->GetVertex(0);
        CPoint        ptHead    = pLinkShape->GetVertex(pointCount - 1);
        CODComponent* pTailComp = NULL;
        CODComponent* pHeadComp = NULL;

        if (pSourcePort)
        {
            ptTail    = pSourcePort->GetLocation();
            pTailComp = pSourcePort->GetOwner();
        }

        if (pTargetPort)
        {
            ptHead    = pTargetPort->GetLocation();
            pHeadComp = pTargetPort->GetOwner();
        }

        pLinkShape->SetVertex(0,              ptTail);
        pLinkShape->SetVertex(pointCount - 1, ptHead);

        const CRect rcLinePadding(odg_rcOrthogonalLinePadding);

        // calculate points to be orthogonal (all 90 degree angles). The direction should be determined for each end point
        CSize szDirPt1(0, 0);
        CSize szDirPt2(0, 0);

        // the default calculation assumes that the line stops at the perimeter of each symbol. In this case, the line
        // direction can be controlled more precisely because it won't cross the symbol. This calculation makes both
        // end points face towards each other to minimize the number of bends in the line
        pLinkShape->CalcEndpointDirections(szDirPt1, szDirPt2);

        if (pTailComp && pHeadComp)
        {
            CRect rcTail = pTailComp->GetBounds();
            CRect rcHead = pHeadComp->GetBounds();

            const int leftInflate   = rcLinePadding.left   / 2;
            const int topInflate    = rcLinePadding.top    / 2;
            const int rightInflate  = rcLinePadding.right  / 2;
            const int bottomInflate = rcLinePadding.bottom / 2;

            rcTail.InflateRect(leftInflate, topInflate, rightInflate, bottomInflate);
            rcHead.InflateRect(leftInflate, topInflate, rightInflate, bottomInflate);

            CRect rcIntersect;
            BOOL  intersect = rcIntersect.IntersectRect(&rcTail, &rcHead);

            if (rcTail == rcHead)
            {
                CSize     szTmp         = szDirPt1;
                const int turnDirection = 1;

                szDirPt1.cx = (szTmp.cy * turnDirection);
                szDirPt1.cy = (szTmp.cx * turnDirection);
            }
            else
            if (intersect)
            {
                CSize szTmp         = szDirPt1;
                int   turnDirection = 1;

                szDirPt1.cx = (szTmp.cy * turnDirection);
                szDirPt1.cy = (szTmp.cx * turnDirection);

                szTmp         = szDirPt2;
                turnDirection = -1;

                szDirPt2.cx = (szTmp.cy * turnDirection);
                szDirPt2.cy = (szTmp.cx * turnDirection);
            }
        }

        // if a port doesn't allow to attach the line on the symbol perimeter, it's possible (even likely) that
        // the line will cross the symbol. Calculate the end point direction to minimize the intersection between
        // the line and the symbol
        if (pSourcePort && pSourcePort->MustAttachAtPerimeter())
        {
            ASSERT_VALID(pTailComp);

            const CRect rcTail = pTailComp->GetBounds();
            CPoint      ptNext = ptTail;

            if (szDirPt1.cx < 0)
                ptNext.x = rcTail.left - 1;

            if (szDirPt1.cx > 0)
                ptNext.x = rcTail.right + 1;

            if (szDirPt1.cy < 0)
                ptNext.y = rcTail.top - 1;

            if (szDirPt1.cy > 0)
                ptNext.y = rcTail.bottom + 1;

            CPoint ptAdjustedTail = pTailComp->GetBaseRgn().GetBoundaryPoint(&ptTail, &ptNext, spacing);
            pLinkShape->SetVertex(0, ptAdjustedTail);
        }
        else
        if (pTailComp)
        {
            szDirPt1                  = CODGlobal::CalcOrthogonalDirection(ptTail, pTailComp->GetBounds());
            const CString srcPortName = pSourcePort->GetName();

            if (srcPortName == M_PortUPComponentLabel)
            {
                szDirPt1.cx =  0;
                szDirPt1.cy = -1;
            }
            else
            if (srcPortName == M_PortDOWNComponentLabel)
            {
                szDirPt1.cx = 0;
                szDirPt1.cy = 1;
            }
            else
            if (srcPortName == M_PortLEFTComponentLabel)
            {
                szDirPt1.cx = -1;
                szDirPt1.cy =  0;
            }
            else
            if (srcPortName == M_PortRIGHTComponentLabel)
            {
                szDirPt1.cx = 1;
                szDirPt1.cy = 0;
            }
            else
                szDirPt1 = CODGlobal::CalcOrthogonalDirection(ptTail, pTailComp->GetBounds());
        }

        if (pTargetPort && pTargetPort->MustAttachAtPerimeter())
        {
            ASSERT_VALID(pHeadComp);

            const CRect rcHead = pHeadComp->GetBounds();
            CPoint      ptPrev = ptHead;

            if (szDirPt2.cx < 0)
                ptPrev.x = rcHead.left - 1;

            if (szDirPt2.cx > 0)
                ptPrev.x = rcHead.right + 1;

            if (szDirPt2.cy < 0)
                ptPrev.y = rcHead.top - 1;

            if (szDirPt2.cy > 0)
                ptPrev.y = rcHead.bottom + 1;

            const CPoint ptAdjustedHead = pHeadComp->GetBaseRgn().GetBoundaryPoint(&ptHead, &ptPrev, spacing);
            pLinkShape->SetVertex(pointCount - 1, ptAdjustedHead);
        }
        else
        if (pHeadComp)
        {
            szDirPt2                     = CODGlobal::CalcOrthogonalDirection(ptHead, pHeadComp->GetBounds());
            const CString targetPortName = pTargetPort->GetName();

            if (targetPortName == M_PortUPComponentLabel)
            {
                szDirPt2.cx =  0;
                szDirPt2.cy = -1;
            }
            else
            if (targetPortName == M_PortDOWNComponentLabel)
            {
                szDirPt2.cx = 0;
                szDirPt2.cy = 1;
            }
            else
            if (targetPortName == M_PortLEFTComponentLabel)
            {
                szDirPt2.cx = -1;
                szDirPt2.cy =  0;
            }
            else
            if (targetPortName == M_PortRIGHTComponentLabel)
            {
                szDirPt2.cx = 1;
                szDirPt2.cy = 0;
            }
            else
                szDirPt2 = CODGlobal::CalcOrthogonalDirection(ptHead, pHeadComp->GetBounds());
        }

        BOOL paddingOk = TRUE;

        if (pointCount > 2)
        {
            CSize szTailSeg = pLinkShape->GetVertex(1)              - pLinkShape->GetVertex(0);
            CSize szHeadSeg = pLinkShape->GetVertex(pointCount - 2) - pLinkShape->GetVertex(pointCount - 1);

            szTailSeg.cx = szTailSeg.cx * szDirPt1.cx;
            szTailSeg.cy = szTailSeg.cy * szDirPt1.cy;

            szHeadSeg.cx = szHeadSeg.cx * szDirPt2.cx;
            szHeadSeg.cy = szHeadSeg.cy * szDirPt2.cy;

            CSize szTailPad(0, 0);

            if (szDirPt1.cx > 0)
                szTailPad.cx = rcLinePadding.right;
            else
            if (szDirPt1.cy < 0)
                szTailPad.cx = rcLinePadding.left;

            if (szDirPt1.cy > 0)
                szTailPad.cy = rcLinePadding.bottom;
            else
            if (szDirPt1.cy < 0)
                szTailPad.cy = rcLinePadding.top;

            CSize szHeadPad(0, 0);

            if (szDirPt2.cx > 0)
                szHeadPad.cx = rcLinePadding.right;
            else
            if (szDirPt2.cy < 0)
                szHeadPad.cx = rcLinePadding.left;

            if (szDirPt2.cy > 0)
                szHeadPad.cy = rcLinePadding.bottom;
            else
            if (szDirPt2.cy < 0)
                szHeadPad.cy = rcLinePadding.top;

            if (szTailSeg.cx < szTailPad.cx)
                paddingOk = FALSE;
            else
            if (szTailSeg.cy < szTailPad.cy)
                paddingOk = FALSE;

            if (szHeadSeg.cx < szHeadPad.cx)
                paddingOk = FALSE;
            else
            if (szHeadSeg.cy < szHeadPad.cy)
                paddingOk = FALSE;
        }

        // calculate the points needed to connect the two end points with a set of orthogonal line segments
        pLinkShape->MakeOrthogonal(szDirPt1, szDirPt2);
    }
    else
        CODLinkComponent::AdjustPoints();
}
//---------------------------------------------------------------------------
CString PSS_DeliverableLinkSymbolBP::GetRuleNameByGUID(PSS_LogicalRulesEntity* pRule, const CString& ruleGUID)
{
    if (!pRule)
        return _T("");

    if (pRule->GetGUID() == ruleGUID)
        return pRule->GetEntityName();

    if (pRule->ContainEntity())
    {
        const int count = pRule->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            PSS_LogicalRulesEntity* pEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pRule->GetEntityAt(i));

            if (!pEntity)
                continue;

            const CString name = GetRuleNameByGUID(pEntity, ruleGUID);

            if (!name.IsEmpty())
                return name;
        }
    }

    return _T("");
}
//---------------------------------------------------------------------------
