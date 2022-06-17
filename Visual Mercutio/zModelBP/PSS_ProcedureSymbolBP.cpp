/****************************************************************************
 * ==> PSS_ProcedureSymbolBP -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a procedure symbol for banking process            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcedureSymbolBP.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_DrawFunctions.h"
#include "zBaseSym\zBaseSymRes.h"
#include "zModel\PSS_ModelGlobal.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_SelectUserGroupDlg.h"
#include "zModel\PSS_ODSymbolManipulator.h"
#define _ZMODELEXPORT
    #include "zModel\PSS_BasicProperties.h"
#undef _ZMODELEXPORT
#include "zProperty\PSS_PropertyAttributes.h"
#include "zProperty\PSS_PropertyObserverMsg.h"
#include "PSS_DeliverableLinkSymbolBP.h"
#include "PSS_RuleListPropertiesBP.h"
#include "PSS_TaskListPropertiesBP.h"
#include "PSS_DecisionListPropertiesBP.h"
#include "PSS_CostPropertiesProcedureBP_Beta1.h"
#include "PSS_UnitPropertiesBP_Beta1.h"
#include "PSS_CombinationPropertiesBP.h"
#include "PSS_SimPropertiesProcedureBP.h"
#include "PSS_AddRemoveCombinationDeliverableDlg.h"
#include "PSS_SelectMasterDeliverableDlg.h"
#include "PSS_ProcessGraphModelControllerBP.h"
#include "PSS_RiskOptionsDlg.h"

// resources
#include "zModelBPRes.h"
#include "PSS_ModelResIDs.h"
#include "zModel\zModelRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const std::size_t g_MaxRuleListSize        = 20;
const std::size_t g_MaxTaskListSize        = 20;
const std::size_t g_MaxDecisionListSize    = 20;
const std::size_t g_MaxCombinationListSize = 20;
const std::size_t g_MaxRulesSize           = 20;
const std::size_t g_MaxRisksSize           = 20;
//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
static CMenu g_CombinationMenu;
static CMenu g_RulesMenu;
static CMenu g_RiskMenu;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ProcedureSymbolBP, PSS_Symbol, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ProcedureSymbolBP
//---------------------------------------------------------------------------
PSS_ProcedureSymbolBP::PSS_ProcedureSymbolBP(const CString& name) :
    PSS_Symbol(),
    m_Combinations(this)
{
    ShowAttributeArea(true);

    PSS_Symbol::SetSymbolName(name);

    CreateSymbolProperties();
}
//---------------------------------------------------------------------------
PSS_ProcedureSymbolBP::PSS_ProcedureSymbolBP(const PSS_ProcedureSymbolBP& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ProcedureSymbolBP::~PSS_ProcedureSymbolBP()
{}
//---------------------------------------------------------------------------
PSS_ProcedureSymbolBP& PSS_ProcedureSymbolBP::operator = (const PSS_ProcedureSymbolBP& other)
{
    PSS_Symbol::operator = ((const PSS_Symbol&)other);

    m_Combinations = other.m_Combinations;
    m_Rules        = other.m_Rules;
    m_Risks        = other.m_Risks;

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcedureSymbolBP::Create(const CString& name)
{
    BOOL result = FALSE;

    try
    {
        m_IsInCreationProcess = true;
        result                = PSS_Symbol::Create(IDR_BP_PROCEDURE,
                                                   ::AfxFindResourceHandle(MAKEINTRESOURCE(IDR_PACKAGE_SYM),
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
CODComponent* PSS_ProcedureSymbolBP::Dup() const
{
    return new PSS_ProcedureSymbolBP(*this);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::CopySymbolDefinitionFrom(const CODSymbolComponent& src)
{
    PSS_Symbol::CopySymbolDefinitionFrom(src);

    const PSS_ProcedureSymbolBP* pProcedure = dynamic_cast<const PSS_ProcedureSymbolBP*>(&src);

    if (pProcedure)
    {
        m_Combinations         = pProcedure->m_Combinations;
        m_Combinations.SetParent(this);
        m_SimulationProperties = pProcedure->m_SimulationProperties;
        m_UnitProp             = pProcedure->m_UnitProp;
        m_CostProcedureProp    = pProcedure->m_CostProcedureProp;
        m_Rules                = pProcedure->m_Rules;
        m_Risks                = pProcedure->m_Risks;
        m_CommentRect          = pProcedure->m_CommentRect;

        // fill the unit double validation type array
        m_UnitDoubleValidationTypeArray.RemoveAll();
        GetUnitDoubleValidationTypeStringArray(m_UnitDoubleValidationTypeArray);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ProcedureSymbolBP::SetSymbolName(const CString& value)
{
    return PSS_Symbol::SetSymbolName(value);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    // don't allow the drop if the symbol isn't local
    if (!IsLocal())
        return false;

    // is an user entity?
    if (pObj && ISA(pObj, PSS_UserGroupEntity))
        return true;

    // is a rule?
    if (pObj && ISA(pObj, PSS_LogicalRulesEntity))
        return true;

    return PSS_Symbol::AcceptDropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::DropItem(CObject* pObj, const CPoint& point)
{
    PSS_UserGroupEntity* pUserGroupEntity = dynamic_cast<PSS_UserGroupEntity*>(pObj);

    if (pUserGroupEntity)
    {
        PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

        // is the user group valid?
        if (pModel && !pModel->MainUserGroupIsValid())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_USERGROUPNOTINLINE, MB_OK);
            return false;
        }

        SetUnitGUID(pUserGroupEntity->GetGUID());
        SetUnitName(pUserGroupEntity->GetEntityName());

        // change the unit cost
        SetUnitCost(pUserGroupEntity->GetEntityCost());

        // set flag for modification
        SetModifiedFlag(TRUE);

        // refresh the attribute area and redraw the symbol
        RefreshAttributeTextArea(true);
        return true;
    }

    PSS_LogicalRulesEntity* pLogicalRulesEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pObj);

    if (pLogicalRulesEntity)
    {
        PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

        // is the rule valid?
        if (pModel && !pModel->MainLogicalRulesIsValid())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_RULENOTINLINE, MB_OK);
            return false;
        }

        std::unique_ptr<PSS_RulesPropertiesBP> pRuleProps(new PSS_RulesPropertiesBP());
        pRuleProps->SetRuleName(pLogicalRulesEntity->GetEntityName());
        pRuleProps->SetRuleDescription(pLogicalRulesEntity->GetEntityDescription());
        pRuleProps->SetRuleGUID(pLogicalRulesEntity->GetGUID());
        m_Rules.AddRule(pRuleProps.get());
        pRuleProps.release();

        // set the procedure symbol as modified
        SetModifiedFlag(TRUE);

        // refresh the attribute area and redraw the symbol
        RefreshAttributeTextArea(true);
        return true;
    }

    return PSS_Symbol::DropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::AcceptExtApp() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::AcceptExtFile() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::CreateSymbolProperties()
{
    if (!PSS_Symbol::CreateSymbolProperties())
        return false;

    PSS_RuleListPropertiesBP propRules;
    AddProperty(propRules);

    PSS_TaskListPropertiesBP propTasks;
    AddProperty(propTasks);

    PSS_DecisionListPropertiesBP propDecisions;
    AddProperty(propDecisions);

    PSS_CostPropertiesProcedureBP_Beta1 propCost;
    AddProperty(propCost);

    PSS_UnitPropertiesBP_Beta1 propUnit;
    AddProperty(propUnit);

    // create at least one combination property
    m_Combinations.CreateInitialProperties();

    // fill the unit double validation type array
    m_UnitDoubleValidationTypeArray.RemoveAll();
    GetUnitDoubleValidationTypeStringArray(m_UnitDoubleValidationTypeArray);

    // create at least one risk property
    m_Risks.CreateInitialProperties();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::FillProperties(PSS_Properties::IPropertySet& propSet, bool numericValues, bool groupValues)
{
    // if no file, add a new one
    if (!GetExtFileCount())
        AddNewExtFile();

    // if no application, add a new one
    if (!GetExtAppCount())
        AddNewExtApp();

    // the "Name", "Description" and "Reference" properties of the "General" group can be found in the base class.
    // The "External Files" and "External Apps" properties are also available from there
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

        // get the main rule
        if (pOwnerModel)
        {
            PSS_ProcessGraphModelControllerBP* pModelCtrl =
                    dynamic_cast<PSS_ProcessGraphModelControllerBP*>(pOwnerModel->GetController());

            if (pModelCtrl)
            {
                PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pModelCtrl->GetDocument());

                if (pDoc)
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
    int     count = GetRuleCount() + 1;

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
                                         PSS_Property::IEType::IE_T_EditIntelli,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_General),
                                         pValueArray));
        else
            // the "Control X" of the "Controls" group, but it is empty and not shown
            pProp.reset(new PSS_Property(propTitle,
                                         ZS_BP_PROP_RULELIST,
                                         finalPropName,
                                         M_Rule_List_ID + (i * g_MaxRuleListSize),
                                         propDesc,
                                         _T(""),
                                         PSS_Property::IEType::IE_T_EditIntelli,
                                         false,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_General),
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

        CString finalRiskName;

        // the "Risk title" property of the "Risk (x)" group
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

        CString sNoRiskType = _T("");
        sNoRiskType.LoadString(IDS_NO_RISK_TYPE);

        // the "Type" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Type_ID : (M_Risk_Type_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     GetRiskType(i).IsEmpty() ? sNoRiskType : GetRiskType(i),
                                     PSS_Property::IEType::IE_T_EditExtendedReadOnly));

        propSet.Add(pProp.get());
        pProp.release();

        riskName.LoadString(IDS_Z_RISK_IMPACT_NAME);
        riskDesc.LoadString(IDS_Z_RISK_IMPACT_DESC);

        PSS_Application* pApplication = PSS_Application::Instance();
        PSS_MainForm*    pMainForm    = NULL;
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
                                     PSS_Property::IEType::IE_T_EditExtendedReadOnly));

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

    // add tasks
    PSS_TaskListPropertiesBP* pTasksProps = static_cast<PSS_TaskListPropertiesBP*>(GetProperty(ZS_BP_PROP_TASKLIST));

    if (!pTasksProps)
        return false;

    count       = GetTaskCount() + 1;
    propTitle.LoadString(IDS_ZS_BP_PROP_PROCEDURE_TSKLST_TITLE);
    pValueArray = PSS_Global::GetHistoricValueManager().GetFieldHistory(propTitle);

    propName.LoadString(IDS_Z_TASK_LIST_NAME);
    propDesc.LoadString(IDS_Z_TASK_LIST_DESC);

    // iterate through all task properties, and define at least one task
    for (int i = 0; i < g_MaxTaskListSize; ++i)
    {
        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // add task, if count is reached continue to add empty task until reaching the maximum size
        if (i < count)
            // the "Task x" property of the "Tasks" group
            pProp.reset(new PSS_Property(propTitle,
                                         ZS_BP_PROP_TASKLIST,
                                         finalPropName,
                                         M_Task_List_ID + (i * g_MaxTaskListSize),
                                         propDesc,
                                         GetTaskAt(i),
                                         PSS_Property::IEType::IE_T_EditIntelli,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_General),
                                         pValueArray));
        else
            // the "Task x" property of the "Tasks" group, but empty and not shown
            pProp.reset(new PSS_Property(propTitle,
                                         ZS_BP_PROP_TASKLIST,
                                         finalPropName,
                                         M_Task_List_ID + (i * g_MaxTaskListSize),
                                         propDesc,
                                         _T(""),
                                         PSS_Property::IEType::IE_T_EditIntelli,
                                         false,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_General),
                                         pValueArray));

        pProp->EnableDragNDrop();
        propSet.Add(pProp.get());
        pProp.release();
    }

    // get the decisions
    PSS_DecisionListPropertiesBP* pDecisionsProps =
            static_cast<PSS_DecisionListPropertiesBP*>(GetProperty(ZS_BP_PROP_DECISIONLIST));

    if (!pDecisionsProps)
        return false;

    count       = GetDecisionCount() + 1;
    propTitle.LoadString(IDS_ZS_BP_PROP_PROCEDURE_DECLST_TITLE);
    pValueArray = PSS_Global::GetHistoricValueManager().GetFieldHistory(propTitle);

    propName.LoadString(IDS_Z_DECISION_LIST_NAME);
    propDesc.LoadString(IDS_Z_DECISION_LIST_DESC);

    // iterate through all decision properties, and define at least one decision
    for (int i = 0; i < g_MaxDecisionListSize; ++i)
    {
        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // add decision, if count is reached continue to add empty decision until reaching the maximum size
        if (i < count)
            // the "Decision x" property of the "Decisions" group
            pProp.reset(new PSS_Property(propTitle,
                                         ZS_BP_PROP_DECISIONLIST,
                                         finalPropName,
                                         M_Decision_List_ID + (i * g_MaxDecisionListSize),
                                         propDesc,
                                         GetDecisionAt(i),
                                         PSS_Property::IEType::IE_T_EditIntelli,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_General),
                                         pValueArray));
        else
            // the "Decision x" property of the "Decisions" group, but it is empty and not shown
            pProp.reset(new PSS_Property(propTitle,
                                         ZS_BP_PROP_DECISIONLIST,
                                         finalPropName,
                                         M_Decision_List_ID + (i * g_MaxDecisionListSize),
                                         propDesc,
                                         _T(""),
                                         PSS_Property::IEType::IE_T_EditIntelli,
                                         false,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_General),
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

    bool error;

    // do add the procedure and processing unit properties?
    if (pProcessGraphModel && pProcessGraphModel->GetIntegrateCostSimulation())
    {
        // the "Multiplier" property of the "Procedure" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                     ZS_BP_PROP_PROCEDURE_COST,
                                     IDS_Z_COST_MULTIPLIER_NAME,
                                     M_Cost_Proc_Multiplier_ID,
                                     IDS_Z_COST_MULTIPLIER_DESC,
                                     GetMultiplier(),
                                     PSS_Property::IEType::IE_T_EditNumber,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Accounting, true, -1)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Standard time" property of the "Procedure" group
        if (numericValues)
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                         ZS_BP_PROP_PROCEDURE_COST,
                                         IDS_Z_COST_PROCESSING_TIME_NAME,
                                         M_Cost_Proc_Processing_Time_ID,
                                         IDS_Z_COST_PROCESSING_TIME_DESC,
                                         GetProcessingTime(),
                                         PSS_Property::IEType::IE_T_EditNumber));
        else
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                         ZS_BP_PROP_PROCEDURE_COST,
                                         IDS_Z_COST_PROCESSING_TIME_NAME,
                                         M_Cost_Proc_Processing_Time_ID,
                                         IDS_Z_COST_PROCESSING_TIME_DESC,
                                         PSS_Duration(GetProcessingTime(),
                                                      hourPerDay,
                                                      dayPerWeek,
                                                      dayPerMonth,
                                                      dayPerYear),
                                         PSS_Property::IEType::IE_T_EditDuration,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Unitary cost" property of the "Procedure" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                     ZS_BP_PROP_PROCEDURE_COST,
                                     IDS_Z_COST_UNITARY_COST_NAME,
                                     M_Cost_Proc_Unitary_Cost_ID,
                                     IDS_Z_COST_UNITARY_COST_DESC,
                                     GetUnitaryCost(),
                                     PSS_Property::IEType::IE_T_EditNumber,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Currency,
                                                      true,
                                                      2,
                                                      currencySymbol)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Average duration (weighted)" property of the "Procedure" group
        if (numericValues)
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                         ZS_BP_PROP_PROCEDURE_COST,
                                         IDS_Z_COST_PROCESSING_DURATION_NAME,
                                         M_Cost_Proc_Processing_Duration_ID,
                                         IDS_Z_COST_PROCESSING_DURATION_DESC,
                                         GetProcessingDuration(),
                                         PSS_Property::IEType::IE_T_EditNumber));
        else
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                         ZS_BP_PROP_PROCEDURE_COST,
                                         IDS_Z_COST_PROCESSING_DURATION_NAME,
                                         M_Cost_Proc_Processing_Duration_ID,
                                         IDS_Z_COST_PROCESSING_DURATION_DESC,
                                         PSS_Duration(GetProcessingDuration(),
                                                      hourPerDay,
                                                      dayPerWeek,
                                                      dayPerMonth,
                                                      dayPerYear),
                                         PSS_Property::IEType::IE_T_EditDurationReadOnly,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Average duration (max)" property of the "Procedure" group
        if (numericValues)
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                         ZS_BP_PROP_PROCEDURE_COST,
                                         IDS_Z_COST_PROCESSING_DURATIONMAX_NAME,
                                         M_Cost_Proc_Processing_Duration_Max_ID,
                                         IDS_Z_COST_PROCESSING_DURATIONMAX_DESC,
                                         GetProcessingDurationMax(),
                                         PSS_Property::IEType::IE_T_EditNumber));
        else
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                         ZS_BP_PROP_PROCEDURE_COST,
                                         IDS_Z_COST_PROCESSING_DURATIONMAX_NAME,
                                         M_Cost_Proc_Processing_Duration_Max_ID,
                                         IDS_Z_COST_PROCESSING_DURATIONMAX_DESC,
                                         PSS_Duration(GetProcessingDurationMax(),
                                                      hourPerDay,
                                                      dayPerWeek,
                                                      dayPerMonth,
                                                      dayPerYear),
                                         PSS_Property::IEType::IE_T_EditDurationReadOnly,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();

        // get the unit cost
        const float unitCost = RetrieveUnitCost(GetUnitGUID(), error);

        // the "Cost" property of the "Processing unit" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_UNIT_TITLE,
                                     ZS_BP_PROP_UNIT,
                                     IDS_Z_UNIT_COST_NAME,
                                     M_Unit_Cost_ID,
                                     IDS_Z_UNIT_COST_DESC,
                                     unitCost,
                                     PSS_Property::IEType::IE_T_EditNumberReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Currency,
                                                      true,
                                                      2,
                                                      currencySymbol)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Double validation" property of the "Processing unit" group
        if (numericValues)
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_UNIT_TITLE,
                                         ZS_BP_PROP_UNIT,
                                         IDS_Z_UNIT_DOUBLE_VALIDATION_NAME,
                                         M_Unit_Double_Validation_ID,
                                         IDS_Z_UNIT_DOUBLE_VALIDATION_DESC,
                                         double(GetUnitDoubleValidationType()),
                                         PSS_Property::IEType::IE_T_EditNumber,
                                         false,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_General)));
        else
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_UNIT_TITLE,
                                         ZS_BP_PROP_UNIT,
                                         IDS_Z_UNIT_DOUBLE_VALIDATION_NAME,
                                         M_Unit_Double_Validation_ID,
                                         IDS_Z_UNIT_DOUBLE_VALIDATION_DESC,
                                         GetUnitDoubleValidationTypeString(GetUnitDoubleValidationType()),
                                         PSS_Property::IEType::IE_T_ComboStringReadOnly,
                                         false,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_General),
                                         &m_UnitDoubleValidationTypeArray));

        propSet.Add(pProp.get());
        pProp.release();
    }

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

    // get the unit name
    const CString unitName = RetrieveUnitName(GetUnitGUID(), error);

    // the "Unit" property of the "Processing unit" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_UNIT_TITLE,
                                 ZS_BP_PROP_UNIT,
                                 IDS_Z_UNIT_NAME_NAME,
                                 M_Unit_Name_ID,
                                 IDS_Z_UNIT_NAME_DESC,
                                 unitName,
                                 groupEnabled ? PSS_Property::IEType::IE_T_EditExtendedReadOnly : PSS_Property::IEType::IE_T_EditStringReadOnly));

    propSet.Add(pProp.get());
    pProp.release();

    // if the combination menu is not loaded, load it
    if (!g_CombinationMenu.GetSafeHmenu())
        g_CombinationMenu.LoadMenu(IDR_COMBINATION_MENU);

    // the combination properties should appear only in Messenger
    if (pProcessGraphModel && pProcessGraphModel->GetIntegrateCostSimulation())
    {
        CString finalPropTitle;
        count = GetCombinationCount();
        propTitle.LoadString(IDS_ZS_BP_PROP_COMBINATION_TITLE);

        // necessary to check if the initial combination is correct
        CheckInitialCombination();

        // iterate through all combination properties
        for (int i = 0; i < count; ++i)
        {
            finalPropTitle.Format(_T("%s (%d)"), propTitle, i + 1);

            propName.LoadString(IDS_Z_COMBINATION_NAME_NAME);
            propDesc.LoadString(IDS_Z_COMBINATION_NAME_DESC);

            // the "Combination title" property of the "Combination x" group
            pProp.reset(new PSS_Property(finalPropTitle,
                                         groupValues ? ZS_BP_PROP_COMBINATION : (ZS_BP_PROP_COMBINATION + i),
                                         propName,
                                         groupValues ? M_Combination_Name_ID : (M_Combination_Name_ID + (i * g_MaxCombinationListSize)),
                                         propDesc,
                                         GetCombinationName(i),
                                         PSS_Property::IEType::IE_T_EditMenu,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_General),
                                         NULL,
                                         &g_CombinationMenu));

            propSet.Add(pProp.get());
            pProp.release();

            propName.LoadString(IDS_Z_COMBINATION_DELIVERABLES_NAME);
            propDesc.LoadString(IDS_Z_COMBINATION_DELIVERABLES_DESC);

            // the "Deliverables" property of the "Combination x" group
            pProp.reset(new PSS_Property(finalPropTitle,
                                         groupValues ? ZS_BP_PROP_COMBINATION : (ZS_BP_PROP_COMBINATION + i),
                                         propName,
                                         groupValues ? M_Combination_Deliverables_ID : (M_Combination_Deliverables_ID + (i * g_MaxCombinationListSize)),
                                         propDesc,
                                         GetCombinationDeliverables(i),
                                         PSS_Property::IEType::IE_T_EditExtendedReadOnly));

            propSet.Add(pProp.get());
            pProp.release();

            propName.LoadString(IDS_Z_COMBINATION_ACTIVATION_PERC_NAME);
            propDesc.LoadString(IDS_Z_COMBINATION_ACTIVATION_PERC_DESC);

            // get the percentage
            const float maxPercent = GetMaxActivationPerc(GetCombinationMaster(i));

            // the "Percentage" property of the "Combination x" group
            pProp.reset(new PSS_Property(finalPropTitle,
                                         groupValues ? ZS_BP_PROP_COMBINATION : (ZS_BP_PROP_COMBINATION + i),
                                         propName,
                                         groupValues ? M_Combination_Activation_Perc_ID : (M_Combination_Activation_Perc_ID + (i * g_MaxCombinationListSize)),
                                         propDesc,
                                         maxPercent,
                                         PSS_Property::IEType::IE_T_EditNumberReadOnly,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Percentage)));

            propSet.Add(pProp.get());
            pProp.release();

            propName.LoadString(IDS_Z_COMBINATION_MASTER_NAME);
            propDesc.LoadString(IDS_Z_COMBINATION_MASTER_DESC);

            // the "Master" property of the "Combination x" group
            pProp.reset(new PSS_Property(finalPropTitle,
                                         groupValues ? ZS_BP_PROP_COMBINATION : (ZS_BP_PROP_COMBINATION + i),
                                         propName,
                                         groupValues ? M_Combination_Master_ID : (M_Combination_Master_ID + (i * g_MaxCombinationListSize)),
                                         propDesc,
                                         GetCombinationMaster(i),
                                         PSS_Property::IEType::IE_T_EditExtendedReadOnly));

            propSet.Add(pProp.get());
            pProp.release();
        }
    }

    if (pProcessGraphModel && pProcessGraphModel->GetIntegrateCostSimulation())
    {
        // get the procedure activation value
        const double value = double(CalculateProcedureActivation());

        // the "Activation" property of the "Calculations and forecasts" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                     ZS_BP_PROP_SIM_PROCEDURE,
                                     IDS_Z_SIM_PROCEDURE_ACTIVATION_NAME,
                                     M_Sim_Procedure_Activation_ID,
                                     IDS_Z_SIM_PROCEDURE_ACTIVATION_DESC,
                                     value,
                                     PSS_Property::IEType::IE_T_EditNumberReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Accounting, true, 0)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "HMO cost" property of the "Calculations and forecasts" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                     ZS_BP_PROP_SIM_PROCEDURE,
                                     IDS_Z_SIM_PROCEDURE_COST_NAME,
                                     M_Sim_Procedure_Cost_ID,
                                     IDS_Z_SIM_PROCEDURE_COST_DESC,
                                     double(GetProcedureCost()),
                                     PSS_Property::IEType::IE_T_EditNumberReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Currency, true, 2, currencySymbol)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Charge" property of the "Calculations and forecasts" group
        if (numericValues)
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                         ZS_BP_PROP_SIM_PROCEDURE,
                                         IDS_Z_SIM_PROCEDURE_WORKLOAD_FORECAST_NAME,
                                         M_Sim_Procedure_Workload_Forecast_ID,
                                         IDS_Z_SIM_PROCEDURE_WORKLOAD_FORECAST_DESC,
                                         double(GetProcedureWorkloadForecast()),
                                         PSS_Property::IEType::IE_T_EditNumber));
        else
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                         ZS_BP_PROP_SIM_PROCEDURE,
                                         IDS_Z_SIM_PROCEDURE_WORKLOAD_FORECAST_NAME,
                                         M_Sim_Procedure_Workload_Forecast_ID,
                                         IDS_Z_SIM_PROCEDURE_WORKLOAD_FORECAST_DESC,
                                         PSS_Duration(double(GetProcedureWorkloadForecast()),
                                                             hourPerDay,
                                                             dayPerWeek,
                                                             dayPerMonth,
                                                             dayPerYear),
                                         PSS_Property::IEType::IE_T_EditDurationReadOnly,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Cost" property of the "Calculations and forecasts" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                     ZS_BP_PROP_SIM_PROCEDURE,
                                     IDS_Z_SIM_PROCEDURE_COST_FORECAST_NAME,
                                     M_Sim_Procedure_Cost_Forecast_ID,
                                     IDS_Z_SIM_PROCEDURE_COST_FORECAST_DESC,
                                     double(GetProcedureCostForecast()),
                                     PSS_Property::IEType::IE_T_EditNumberReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Currency, true, 2, currencySymbol)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Charge / activation" property of the "Calculations and forecasts" group
        if (numericValues)
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                         ZS_BP_PROP_SIM_PROCEDURE,
                                         IDS_Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV_NAME,
                                         M_Sim_Procedure_Workload_Per_Activ_ID,
                                         IDS_Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV_DESC,
                                         double(GetProcedureWorkloadPerActivity()),
                                         PSS_Property::IEType::IE_T_EditNumber));
        else
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                         ZS_BP_PROP_SIM_PROCEDURE,
                                         IDS_Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV_NAME,
                                         M_Sim_Procedure_Workload_Per_Activ_ID,
                                         IDS_Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV_DESC,
                                         PSS_Duration(double(GetProcedureWorkloadPerActivity()),
                                                      hourPerDay,
                                                      dayPerWeek,
                                                      dayPerMonth,
                                                      dayPerYear),
                                         PSS_Property::IEType::IE_T_EditDurationReadOnly,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Cost / activation" property of the "Calculations and forecasts" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                     ZS_BP_PROP_SIM_PROCEDURE,
                                     IDS_Z_SIM_PROCEDURE_COST_P_ACTIV_NAME,
                                     M_Sim_Procedure_Cost_Per_Activ_ID,
                                     IDS_Z_SIM_PROCEDURE_COST_P_ACTIV_DESC,
                                     GetProcedureCostPerActivity(),
                                     PSS_Property::IEType::IE_T_EditNumberReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IEFormatType::IE_FT_Currency, true, 2, currencySymbol)));

        propSet.Add(pProp.get());
        pProp.release();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::SaveProperties(PSS_Properties::IPropertySet& propSet)
{
    if (!PSS_Symbol::SaveProperties(propSet))
        return false;

    // only local symbol may access to properties
    if (!IsLocal())
        return true;

    // save the rules
    PSS_RuleListPropertiesBP* pRulesProps = static_cast<PSS_RuleListPropertiesBP*>(GetProperty(ZS_BP_PROP_RULELIST));

    if (!pRulesProps)
        return false;

    PSS_Properties::IPropertyIterator it(&propSet);

    // empty the task list
    SetRuleList(_T(""));

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_RULELIST)
            switch (pProp->GetValueType())
            {
                case PSS_Property::IEValueType::IE_VT_String:
                    // if not empty, add this new task
                    if (!pProp->GetValueString().IsEmpty())
                        AddRule(pProp->GetValueString());

                    break;
            }

    // save the tasks
    PSS_TaskListPropertiesBP* pTasksProps = static_cast<PSS_TaskListPropertiesBP*>(GetProperty(ZS_BP_PROP_TASKLIST));

    if (!pTasksProps)
        return false;

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

    // empty the task list
    SetTaskList(_T(""));

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_TASKLIST)
            switch (pProp->GetValueType())
            {
                case PSS_Property::IEValueType::IE_VT_String:
                    // if not empty, add this new task
                    if (!pProp->GetValueString().IsEmpty())
                        AddTask(pProp->GetValueString());

                    break;
            }

    // save the decisions. Because the AddTask() function is called, it's not necessary to call SetProperty()
    PSS_DecisionListPropertiesBP* pDecisionsProps =
            static_cast<PSS_DecisionListPropertiesBP*>(GetProperty(ZS_BP_PROP_DECISIONLIST));

    if (!pDecisionsProps)
        return false;

    // empty the decision list
    SetDecisionList(_T(""));

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_DECISIONLIST)
            switch (pProp->GetValueType())
            {
                case PSS_Property::IEValueType::IE_VT_String:
                    // if not empty, add this new decision
                    if (!pProp->GetValueString().IsEmpty())
                        AddDecision(pProp->GetValueString());

                    break;
            }

    // iterate through the data list and fill the property set. Because the AddDecision() function is called,
    // it's not necessary to call SetProperty()
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_PROCEDURE_COST)
        {
            const int itemID = pProp->GetItemID();

            switch (pProp->GetValueType())
            {
                case PSS_Property::IEValueType::IE_VT_String:   m_CostProcedureProp.SetValue(itemID,            pProp->GetValueString());    break;
                case PSS_Property::IEValueType::IE_VT_Double:   m_CostProcedureProp.SetValue(itemID, float(     pProp->GetValueDouble()));   break;
                case PSS_Property::IEValueType::IE_VT_Float:    m_CostProcedureProp.SetValue(itemID,            pProp->GetValueFloat());     break;
                case PSS_Property::IEValueType::IE_VT_Date:     m_CostProcedureProp.SetValue(itemID, float(DATE(pProp->GetValueDate())));    break;
                case PSS_Property::IEValueType::IE_VT_TimeSpan: m_CostProcedureProp.SetValue(itemID, double(    pProp->GetValueTimeSpan())); break;
                case PSS_Property::IEValueType::IE_VT_Duration: m_CostProcedureProp.SetValue(itemID, double(    pProp->GetValueDuration())); break;
            }
        }

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT)
            if (pProp->GetItemID() == M_Unit_Double_Validation_ID)
                m_UnitProp.SetValue(pProp->GetItemID(),
                                    ConvertUnitDoubleValidationString2Type(pProp->GetValueString()));
            else
            {
                const int itemID = pProp->GetItemID();

                switch (pProp->GetValueType())
                {
                    case PSS_Property::IEValueType::IE_VT_Double: m_UnitProp.SetValue(itemID, float(pProp->GetValueDouble())); break;
                    case PSS_Property::IEValueType::IE_VT_Float:  m_UnitProp.SetValue(itemID,       pProp->GetValueFloat());   break;
                    case PSS_Property::IEValueType::IE_VT_String: m_UnitProp.SetValue(itemID,       pProp->GetValueString());  break;
                }
            }

    // iterate through the data list and fill the property set of combination
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        const int categoryID = pProp->GetCategoryID();

        if (categoryID >= ZS_BP_PROP_COMBINATION && categoryID <= ZS_BP_PROP_COMBINATION + GetCombinationCount())
        {
            const int                    i          = categoryID - ZS_BP_PROP_COMBINATION;
            PSS_CombinationPropertiesBP* pCombProps = GetCombinationProperty(i);

            if (!pCombProps)
                return false;

            const int itemID = pProp->GetItemID();

            switch (pProp->GetValueType())
            {
                case PSS_Property::IEValueType::IE_VT_String:   pCombProps->SetValue(itemID - (i * g_MaxCombinationListSize),            pProp->GetValueString());  break;
                case PSS_Property::IEValueType::IE_VT_Double:   pCombProps->SetValue(itemID - (i * g_MaxCombinationListSize), float(     pProp->GetValueDouble())); break;
                case PSS_Property::IEValueType::IE_VT_Float:    pCombProps->SetValue(itemID - (i * g_MaxCombinationListSize),            pProp->GetValueFloat());   break;
                case PSS_Property::IEValueType::IE_VT_Date:     pCombProps->SetValue(itemID - (i * g_MaxCombinationListSize), float(DATE(pProp->GetValueDate())));  break;
                case PSS_Property::IEValueType::IE_VT_TimeSpan:
                case PSS_Property::IEValueType::IE_VT_Duration: THROW("Unsupported value");
            }
        }
    }

    // iterate through the data list and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_SIM_PROCEDURE)
        {
            const int itemID = pProp->GetItemID();

            switch (pProp->GetValueType())
            {
                case PSS_Property::IEValueType::IE_VT_String:   m_SimulationProperties.SetValue(itemID,            pProp->GetValueString());    break;
                case PSS_Property::IEValueType::IE_VT_Double:   m_SimulationProperties.SetValue(itemID,            pProp->GetValueDouble());    break;
                case PSS_Property::IEValueType::IE_VT_Float:    m_SimulationProperties.SetValue(itemID,            pProp->GetValueFloat());     break;
                case PSS_Property::IEValueType::IE_VT_Date:     m_SimulationProperties.SetValue(itemID, float(DATE(pProp->GetValueDate())));    break;
                case PSS_Property::IEValueType::IE_VT_TimeSpan: m_SimulationProperties.SetValue(itemID, double(    pProp->GetValueTimeSpan())); break;
                case PSS_Property::IEValueType::IE_VT_Duration: m_SimulationProperties.SetValue(itemID, double(    pProp->GetValueDuration())); break;
            }
        }

    RefreshAttributeTextArea(true);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::SaveProperty(PSS_Property& prop)
{
    if (!PSS_Symbol::SaveProperty(prop))
        return false;

    // only local symbol may access to properties
    if (!IsLocal())
        return true;

    const int categoryID = prop.GetCategoryID();

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

    if (categoryID >= ZS_BP_PROP_COMBINATION && categoryID <= ZS_BP_PROP_COMBINATION + GetCombinationCount())
    {
        const int i = categoryID - ZS_BP_PROP_COMBINATION;

        switch (prop.GetItemID() - (i * g_MaxCombinationListSize))
        {
            case M_Combination_Name_ID:            SetCombinationName          (prop.GetCategoryID() - ZS_BP_PROP_COMBINATION, prop.GetValueString()); break;
            case M_Combination_Deliverables_ID:    SetCombinationDeliverables  (prop.GetCategoryID() - ZS_BP_PROP_COMBINATION, prop.GetValueString()); break;
            case M_Combination_Activation_Perc_ID: SetCombinationActivationPerc(prop.GetCategoryID() - ZS_BP_PROP_COMBINATION, prop.GetValueFloat());  break;
            case M_Combination_Master_ID:          SetCombinationMaster        (prop.GetCategoryID() - ZS_BP_PROP_COMBINATION, prop.GetValueString()); break;
        }
    }

    if (categoryID == ZS_BP_PROP_RULELIST)
        // if not empty, add this new rule
        if (!prop.GetValueString().IsEmpty())
            AddRule(prop.GetValueString());

    if (categoryID == ZS_BP_PROP_TASKLIST)
        // if not empty, add this new task
        if (!prop.GetValueString().IsEmpty())
            AddTask(prop.GetValueString());

    if (categoryID == ZS_BP_PROP_DECISIONLIST)
        // if not empty, add this new task
        if (!prop.GetValueString().IsEmpty())
            AddDecision(prop.GetValueString());

    // set the symbol as modified. Do nothing else, the values will be saved by the save properties method
    SetModifiedFlag();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::CheckPropertyValue(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props)
{
    return PSS_Symbol::CheckPropertyValue(prop, value, props);
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetRuleNameByGUID(PSS_LogicalRulesEntity* pRule, const CString& ruleGUID) const
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
bool PSS_ProcedureSymbolBP::ProcessExtendedInput(PSS_Property&                 prop,
                                                 CString&                      value,
                                                 PSS_Properties::IPropertySet& props,
                                                 bool&                         refresh)
{
    const int categoryID = prop.GetCategoryID();

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

                    // change the disabled property unit GUID
                    PSS_Properties::IPropertyIterator it(&props);

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
    if (categoryID >= ZS_BP_PROP_COMBINATION && categoryID <= ZS_BP_PROP_COMBINATION + GetCombinationCount())
    {
        const int i = categoryID - ZS_BP_PROP_COMBINATION;

        switch (prop.GetItemID() - (i * g_MaxCombinationListSize))
        {
            case M_Combination_Deliverables_ID:
            {
                // get the deliverables
                CString enteringDeliverables;
                GetEnteringUpDeliverable(enteringDeliverables);
                CString availableDeliverables = GetAvailableDeliverables(enteringDeliverables);

                // show the dialog
                PSS_AddRemoveCombinationDeliverableDlg dlg(availableDeliverables, value);

                if (dlg.DoModal() == IDOK)
                {
                    value = dlg.GetDeliverables();
                    return true;
                }

                break;
            }

            case M_Combination_Master_ID:
            {
                PSS_SelectMasterDeliverableDlg dlg(GetCombinationDeliverables(i), value);

                if (dlg.DoModal() == IDOK)
                {
                    value = dlg.GetMaster();
                    return true;
                }

                break;
            }
        }
    }

    return PSS_Symbol::ProcessExtendedInput(prop, value, props, refresh);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::ProcessMenuCommand(int                           menuCmdID,
                                               PSS_Property&                 prop,
                                               CString&                      value,
                                               PSS_Properties::IPropertySet& props,
                                               bool&                         refresh)
{
    const int categoryID = prop.GetCategoryID();

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

    if (categoryID >= ZS_BP_PROP_COMBINATION && categoryID <= ZS_BP_PROP_COMBINATION + GetCombinationCount())
    {
        switch (menuCmdID)
        {
            case ID_ADD_NEWCOMBINATION:          OnAddNewCombination        (prop, value, props, refresh); break;
            case ID_DEL_CURRENTCOMBINATION:      OnDelCurrentCombination    (prop, value, props, refresh); break;
            case ID_ADD_DELIVERABLE_COMBINATION: OnAddDeliverableCombination(prop, value, props, refresh); break;
            case ID_DEL_DELIVERABLE_COMBINATION: OnDelDeliverableCombination(prop, value, props, refresh); break;
            default:                                                                                       break;
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

    return PSS_Symbol::ProcessMenuCommand(menuCmdID, prop, value, props, refresh);
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetAttributeString(PSS_PropertyAttributes* pAttributes) const
{
    return PSS_Symbol::GetAttributeString(pAttributes);
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetEnteringUpDeliverable(CString& deliverables)
{
    int          counter = 0;
    CODEdgeArray edges;

    // keep only deliverable symbols
    if (GetEnteringUpDeliverable(edges) > 0)
    {
        // initialize the token with ; as separator
        PSS_Tokenizer token;
        const int     edgeCount = edges.GetSize();

        for (int i = 0; i < edgeCount; ++i)
        {
            IODEdge*                     pIEdge = edges.GetAt(i);
            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

            if (pComp)
            {
                token.AddToken(pComp->GetSymbolName());
                ++counter;
            }
        }

        // assign the resulting string
        deliverables = token.GetString();
    }

    return counter;
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetEnteringUpDeliverable(CODEdgeArray& edges)
{
    // get all procedure entering up edges
    GetEdgesEntering_Up(edges);

    CODComponentSet* pSet = GetReferenceSymbols();
    CODComponentSet  internalSet;

    // get all edges from referenced procedures and local symbol if a referenced symbol is defined
    if (!IsLocal())
    {
        if (!pSet)
            pSet = &internalSet;

        CODComponent* pLocalSymbol = GetLocalSymbol();

        if (pLocalSymbol)
            pSet->Add(pLocalSymbol);
    }

    if (pSet)
    {
        const int setCount = pSet->GetSize();

        for (int i = 0; i < setCount; ++i)
        {
            PSS_ProcedureSymbolBP* pComp = dynamic_cast<PSS_ProcedureSymbolBP*>(pSet->GetAt(i));

            if (pComp)
            {
                CODEdgeArray additionalEdges;
                pComp->GetEdgesEntering_Up(additionalEdges);

                const int edgeCount = additionalEdges.GetSize();

                // copy additional edges to the main edges
                for (int j = 0; j < edgeCount; ++j)
                    // get the link
                    edges.AddEdge(additionalEdges.GetAt(j));
            }
        }
    }

    // keep only deliverable symbols
    return int(PSS_ODSymbolManipulator::KeepOnlyLinksISA(edges, RUNTIME_CLASS(PSS_DeliverableLinkSymbolBP)));
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetLeavingDownDeliverable(CString& deliverables)
{
    int          counter = 0;
    CODEdgeArray edges;

    if (GetLeavingDownDeliverable(edges) > 0)
    {
        // initialize the token with ; as separator
        PSS_Tokenizer token;
        const int     edgeCount = edges.GetSize();

        for (int i = 0; i < edgeCount; ++i)
        {
            IODEdge*                     pIEdge = edges.GetAt(i);
            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

            if (pComp)
            {
                token.AddToken(pComp->GetSymbolName());
                ++counter;
            }
        }

        // assign the resulting string
        deliverables = token.GetString();
    }

    return counter;
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetLeavingDownDeliverable(CODEdgeArray& edges)
{
    // get all leaving down edges
    GetEdgesLeaving_Down(edges);

    CODComponentSet* pSet = GetReferenceSymbols();
    CODComponentSet  internalSet;

    // get all edges from referenced procedures and local symbol if a referenced symbol is defined
    if (!IsLocal())
    {
        if (!pSet)
            pSet = &internalSet;

        CODComponent* pLocalSymbol = GetLocalSymbol();

        if (pLocalSymbol)
            pSet->Add(pLocalSymbol);
    }

    if (pSet)
    {
        const int setCount = pSet->GetSize();

        for (int i = 0; i < setCount; ++i)
        {
            PSS_ProcedureSymbolBP* pComp = dynamic_cast<PSS_ProcedureSymbolBP*>(pSet->GetAt(i));

            if (pComp)
            {
                CODEdgeArray additionalEdges;
                pComp->GetEdgesLeaving_Down(additionalEdges);

                const int edgeCount = additionalEdges.GetSize();

                // copy additional edges to the main edges
                for (int j = 0; j < edgeCount; ++j)
                    // get the link
                    edges.AddEdge(additionalEdges.GetAt(j));
            }
        }
    }

    // keep only deliverable symbols
    return int(PSS_ODSymbolManipulator::KeepOnlyLinksISA(edges, RUNTIME_CLASS(PSS_DeliverableLinkSymbolBP)));
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetLeavingLeftDeliverable(CString& deliverables)
{
    int          counter = 0;
    CODEdgeArray edges;

    if (GetLeavingLeftDeliverable(edges) > 0)
    {
        // initialize the token with ; as separator
        PSS_Tokenizer token;
        const int     edgeCount = edges.GetSize();

        for (int i = 0; i < edgeCount; ++i)
        {
            IODEdge*                     pIEdge = edges.GetAt(i);
            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

            if (pComp)
            {
                token.AddToken(pComp->GetSymbolName());
                ++counter;
            }
        }

        // assign the resulting string
        deliverables = token.GetString();
    }

    return counter;
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetLeavingLeftDeliverable(CODEdgeArray& edges)
{
    // get all leaving left edges
    GetEdgesLeaving_Left(edges);

    CODComponentSet* pSet = GetReferenceSymbols();
    CODComponentSet  internalSet;

    // get all edges from referenced procedures and local symbol if a referenced symbol is defined
    if (!IsLocal())
    {
        if (!pSet)
            pSet = &internalSet;

        CODComponent* pLocalSymbol = GetLocalSymbol();

        if (pLocalSymbol)
            pSet->Add(pLocalSymbol);
    }

    if (pSet)
    {
        const int setCount = pSet->GetSize();

        for (int i = 0; i < setCount; ++i)
        {
            PSS_ProcedureSymbolBP* pComp = dynamic_cast<PSS_ProcedureSymbolBP*>(pSet->GetAt(i));

            if (pComp)
            {
                CODEdgeArray additionalEdges;
                pComp->GetEdgesLeaving_Left(additionalEdges);

                const int edgeCount = additionalEdges.GetSize();

                // copy additional edges to the main edges
                for (int j = 0; j < edgeCount; ++j)
                    // get the link
                    edges.AddEdge(additionalEdges.GetAt(j));
            }
        }
    }

    // keep only deliverable symbols
    return (int)PSS_ODSymbolManipulator::KeepOnlyLinksISA(edges, RUNTIME_CLASS(PSS_DeliverableLinkSymbolBP));
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetLeavingRightDeliverable(CString& deliverables)
{
    int          counter = 0;
    CODEdgeArray edges;

    if (GetLeavingRightDeliverable(edges) > 0)
    {
        // initialize the token with ; as separator
        PSS_Tokenizer token;
        const int     edgeCount = edges.GetSize();

        for (int i = 0; i < edgeCount; ++i)
        {
            IODEdge*                     pIEdge = edges.GetAt(i);
            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

            if (pComp)
            {
                token.AddToken(pComp->GetSymbolName());
                ++counter;
            }
        }

        // assign the resulting string
        deliverables = token.GetString();
    }

    return counter;
}
//---------------------------------------------------------------------------
int PSS_ProcedureSymbolBP::GetLeavingRightDeliverable(CODEdgeArray& edges)
{
    // get all leaving right edges
    GetEdgesLeaving_Right(edges);

    // get all edges from referenced procedures and local symbol if a referenced symbol is defined
    CODComponentSet* pSet = GetReferenceSymbols();
    CODComponentSet  internalSet;

    if (!IsLocal())
    {
        if (!pSet)
            pSet = &internalSet;

        CODComponent* pLocalSymbol = GetLocalSymbol();

        if (pLocalSymbol)
            pSet->Add(pLocalSymbol);
    }

    if (pSet)
    {
        const int setCount = pSet->GetSize();

        for (int i = 0; i < setCount; ++i)
        {
            PSS_ProcedureSymbolBP* pComp = dynamic_cast<PSS_ProcedureSymbolBP*>(pSet->GetAt(i));

            if (pComp)
            {
                CODEdgeArray additionalEdges;
                pComp->GetEdgesLeaving_Right(additionalEdges);

                const int edgeCount = additionalEdges.GetSize();

                // copy additional edges to the main edges
                for (int j = 0; j < edgeCount; ++j)
                    // get the link
                    edges.AddEdge(additionalEdges.GetAt(j));
            }
        }
    }

    // keep only deliverable symbols
    return (int)PSS_ODSymbolManipulator::KeepOnlyLinksISA(edges, RUNTIME_CLASS(PSS_DeliverableLinkSymbolBP));
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP PSS_ProcedureSymbolBP::CalculateProcedureActivation()
{
    // get all entering deliverables
    CODEdgeArray edges;

    // get all entering up edges
    if (!GetEnteringUpDeliverable(edges))
        return 0;

    PSS_AnnualNumberPropertiesBP ProcedureActivation(0);

    // for each deliverables, calculate the max procedure activation
    for (int i = 0; i < edges.GetSize(); ++i)
    {
        IODEdge*                     pIEdge       = edges.GetAt(i);
        PSS_DeliverableLinkSymbolBP* pDeliverable = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

        if (!pDeliverable)
            continue;

        // check if it's a local symbol
        if (!pDeliverable->IsLocal())
        {
            // get the local symbol
            pDeliverable = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pDeliverable->GetLocalSymbol());

            if (!pDeliverable)
                return false;
        }

        const int count = GetCombinationCount();

        // iterate through combination and check if this deliverable is defined as a master. If yes,
        // add it to the procedure activation
        for (int j = 0; j < count; ++j)
        {
            TRACE1("Master   = %s\n", GetCombinationMaster(j));
            TRACE1("Livrable = %s\n", pDeliverable->GetSymbolName());

            // found a master?
            if (!GetCombinationMaster(j).IsEmpty() && GetCombinationMaster(j) == pDeliverable->GetSymbolName())
                ProcedureActivation += pDeliverable->GetQuantity();
        }
    }

    return ProcedureActivation;
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetRuleList() const
{
    PSS_RuleListPropertiesBP* pProps = static_cast<PSS_RuleListPropertiesBP*>(GetProperty(ZS_BP_PROP_RULELIST));

    if (!pProps)
        return _T("");

    return pProps->GetRuleList();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetRuleList(const CString& value)
{
    PSS_RuleListPropertiesBP* pProps = static_cast<PSS_RuleListPropertiesBP*>(GetProperty(ZS_BP_PROP_RULELIST));

    if (pProps)
    {
        PSS_RuleListPropertiesBP props(*pProps);
        props.SetRuleList(value);
        SetProperty(&props);
    }
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::RuleExist(const CString& value)
{
    // initialize the token with the rule list and with the default ; as separator
    PSS_Tokenizer token(GetRuleList());

    return token.TokenExist(value);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::AddRule(const CString& value)
{
    // initialize the token with the rule list and with the default ; as separator
    PSS_Tokenizer token(GetRuleList());

    // if the new rule was added successfully, update the rule list
    if (token.AddUniqueToken(value))
    {
        // add the value to the history
        CString key;
        key.LoadString(IDS_ZS_BP_PROP_RULELST_TITLE);
        PSS_Global::GetHistoricValueManager().AddHistoryValue(key, value);

        // set the new rule string
        SetRuleList(token.GetString());
    }
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::RemoveRule(const CString& value)
{
    // initialize the token with the rule list and with the default ; as separator
    PSS_Tokenizer token(GetRuleList());

    // if the rule was removed successfully, update the rule list
    if (token.RemoveToken(value))
        SetRuleList(token.GetString());
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetRuleAt(std::size_t index)
{
    // initialize the token with the rule list and with the default ; as separator
    PSS_Tokenizer token(GetRuleList());
    CString       value;

    // get the token at index
    if (token.GetTokenAt(index, value))
        return value;

    return _T("");
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcedureSymbolBP::GetRuleCount() const
{
    // initialize the token with the rule list and with the default ; as separator
    PSS_Tokenizer token(GetRuleList());

    return token.GetTokenCount();
}
//---------------------------------------------------------------------------
BOOL PSS_ProcedureSymbolBP::ContainsRule(const CString& ruleName) const
{
    const int ruleCount = m_Rules.GetRulesCount();

    for (int i = 0; i < ruleCount; ++i)
        if (m_Rules.GetRuleName(i) == ruleName)
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetRuleGUID(std::size_t index) const
{
    if (index < m_Rules.GetRulesCount())
        return m_Rules.GetRuleGUID(index);

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetTaskList() const
{
    PSS_TaskListPropertiesBP* pProps = static_cast<PSS_TaskListPropertiesBP*>(GetProperty(ZS_BP_PROP_TASKLIST));

    if (!pProps)
        return _T("");

    return pProps->GetTaskList();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetTaskList(const CString& value)
{
    PSS_TaskListPropertiesBP* pProps = static_cast<PSS_TaskListPropertiesBP*>(GetProperty(ZS_BP_PROP_TASKLIST));

    if (pProps)
    {
        PSS_TaskListPropertiesBP props(*pProps);
        props.SetTaskList(value);
        SetProperty(&props);
    }
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::TaskExist(const CString& value)
{
    // initialize the token with the task list and with the default ; as separator
    PSS_Tokenizer token(GetTaskList());

    return token.TokenExist(value);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::AddTask(const CString& value)
{
    // initialize the token with the task list and with the default ; as separator
    PSS_Tokenizer token(GetTaskList());

    // if the new task was added successfully, update the task list
    if (token.AddUniqueToken(value))
    {
        // add the value to the history
        CString key;
        key.LoadString(IDS_ZS_BP_PROP_PROCEDURE_TSKLST_TITLE);
        PSS_Global::GetHistoricValueManager().AddHistoryValue(key, value);

        // set the new task string
        SetTaskList(token.GetString());
    }
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::RemoveTask(const CString& value)
{
    // initialize the token with the task list and with the default ; as separator
    PSS_Tokenizer token(GetTaskList());

    // if the new task was removed successfully, update the task list
    if (token.RemoveToken(value))
        SetTaskList(token.GetString());
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetTaskAt(std::size_t index)
{
    // Initialize the token with the task list and with the default ; as separator
    PSS_Tokenizer token(GetTaskList());

    CString value;

    // get the token at index
    if (token.GetTokenAt(index, value))
        return value;

    return _T("");
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcedureSymbolBP::GetTaskCount() const
{
    // initialize the token with the task list and with the default ; as separator
    PSS_Tokenizer token(GetTaskList());

    return token.GetTokenCount();
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetDecisionList() const
{
    PSS_DecisionListPropertiesBP* pProps = static_cast<PSS_DecisionListPropertiesBP*>(GetProperty(ZS_BP_PROP_DECISIONLIST));

    if (!pProps)
        return _T("");

    return pProps->GetDecisionList();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::SetDecisionList(const CString& value)
{
    PSS_DecisionListPropertiesBP* pProps = static_cast<PSS_DecisionListPropertiesBP*>(GetProperty(ZS_BP_PROP_DECISIONLIST));

    if (pProps)
    {
        PSS_DecisionListPropertiesBP props(*pProps);
        props.SetDecisionList(value);
        SetProperty(&props);
    }
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::DecisionExist(const CString& value)
{
    // initialize the token with the decision list and with the default ; as separator
    PSS_Tokenizer token(GetDecisionList());

    return token.TokenExist(value);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::AddDecision(const CString& value)
{
    // initialize the token with the decision list and with the default ; as separator
    PSS_Tokenizer token(GetDecisionList());

    // if the new decision was added successfully, update the decision list
    if (token.AddUniqueToken(value))
    {
        // add the value to the history
        CString key;
        key.LoadString(IDS_ZS_BP_PROP_PROCEDURE_DECLST_TITLE);
        PSS_Global::GetHistoricValueManager().AddHistoryValue(key, value);

        // set the new decision string
        SetDecisionList(token.GetString());
    }
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::RemoveDecision(const CString& value)
{
    // initialize the token with the decision list and with the default ; as separator
    PSS_Tokenizer token(GetDecisionList());

    // if the new decision was removed successfully, update the decision list
    if (token.RemoveToken(value))
        SetDecisionList(token.GetString());
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetDecisionAt(std::size_t index)
{
    // initialize the token with the decision list and with the default ; as separator
    PSS_Tokenizer token(GetDecisionList());

    CString value;

    // get the decision at index
    if (token.GetTokenAt(index, value))
        return value;

    return _T("");
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcedureSymbolBP::GetDecisionCount() const
{
    // initialize the token with the decision list and with the default ; as separator
    PSS_Tokenizer token(GetDecisionList());

    return token.GetTokenCount();
}
//---------------------------------------------------------------------------
CString PSS_ProcedureSymbolBP::GetRiskType(std::size_t index) const
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
void PSS_ProcedureSymbolBP::Serialize(CArchive& ar)
{
    PSS_Symbol::Serialize(ar);

    // only if the object is serialized from or to a document
    if (ar.m_pDocument)
    {
        // serialize the combinations
        m_Combinations.Serialize(ar);

        m_SimulationProperties.Serialize(ar);

        PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

        // serialize the risks
        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 27)
            m_Risks.Serialize(ar);

        // serialize the rules
        if (ar.IsStoring())
            m_Rules.Serialize(ar);
        else
        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 26)
            m_Rules.Serialize(ar);

        if (ar.IsStoring() || (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 19))
        {
            m_UnitProp.Serialize(ar);
            m_CostProcedureProp.Serialize(ar);
        }
        else
        {
            TRACE("PSS_ProcedureSymbolBP::Serialize - Start read\n");

            // transfer the properties to new format
            PSS_CostPropertiesProcedureBP_Beta1* pCostProps =
                    static_cast<PSS_CostPropertiesProcedureBP_Beta1*>(GetProperty(ZS_BP_PROP_PROCEDURE_COST));

            if (pCostProps)
            {
                SetMultiplier(pCostProps->GetMultiplier());
                SetProcessingTime(pCostProps->GetProcessingTime());
                SetUnitaryCost(pCostProps->GetUnitaryCost());
            }

            PSS_UnitPropertiesBP_Beta1* pUnitProps = static_cast<PSS_UnitPropertiesBP_Beta1*>(GetProperty(ZS_BP_PROP_UNIT));

            if (pUnitProps)
            {
                SetUnitName(pUnitProps->GetUnitName());
                SetUnitCost(pUnitProps->GetUnitCost());
            }

            // set the master if only one deliverable was found for the combination
            const int count = GetCombinationCount();

            for (int i = 0; i < count; ++i)
            {
                const CString deliverables = GetCombinationDeliverables(i);

                // if no separator, only one deliverable, so set this deliverable as the master one
                if (deliverables.Find(';') == -1)
                    SetCombinationMaster(i, deliverables);
            }

            TRACE("PSS_ProcedureSymbolBP::Serialize - End read\n");
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::OnSymbolNameChanged(CODComponent& comp, const CString& oldName)
{
    PSS_LinkSymbol* pSymbol = dynamic_cast<PSS_LinkSymbol*>(&comp);

    if (pSymbol)
        ReplaceDeliverable(oldName, pSymbol->GetSymbolName());
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::OnPostPropertyChanged(PSS_Property& prop, PSS_Properties::IPropertySet& props, bool& refresh)
{
    // only local symbol may access to properties
    if (!IsLocal())
        return false;

    bool result = false;

    if (prop.GetCategoryID() >= ZS_BP_PROP_COMBINATION &&
        prop.GetCategoryID() <= ZS_BP_PROP_COMBINATION + GetCombinationCount())
    {
        const int i = prop.GetCategoryID() - ZS_BP_PROP_COMBINATION;

        switch (prop.GetItemID() - (i * g_MaxCombinationListSize))
        {
            case M_Combination_Deliverables_ID:
            {
                const float maxPercent =
                        GetMaxActivationPerc(GetCombinationMaster(prop.GetCategoryID() - ZS_BP_PROP_COMBINATION));

                PSS_Properties::IPropertyIterator it(&props);
                bool                              found = false;

                // set the value to the property
                for (PSS_Property* pProp = it.GetFirst(); pProp && !found; pProp = it.GetNext())
                {
                    if (!pProp || ((pProp->GetCategoryID() - ZS_BP_PROP_COMBINATION) != i))
                        continue;

                    if (pProp->GetItemID() - (i * g_MaxCombinationListSize) == M_Combination_Activation_Perc_ID)
                    {
                        pProp->SetValueFloat(maxPercent);
                        found = true;
                    }
                }

                // change the return value if found
                if (found)
                    result = true;

                break;
            }

            default:
                break;
        }
    }
    else
    if (prop.GetCategoryID() == ZS_BP_PROP_UNIT && prop.GetItemID() == M_Unit_Name_ID)
    {
        PSS_Properties::IPropertyIterator it(&props);
        CString                           guid;

        // iterate through the properties and change the unit cost to the property value
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
                    bool  error;
                    float unitCost = RetrieveUnitCost(guid, error);

                    if (!error)
                    {
                        pProp->SetValueFloat(unitCost);
                        result = true;
                    }

                    break;
                }
    }
    else
    if (prop.GetCategoryID() == ZS_BP_PROP_RULELIST)
    {
        // change the return value to reload the properties. Need to reload since the rule list has an empty rule.
        // If the user fills it, need to enable a new empty one. And if the user remove one rule, need also to
        // disable one from the property list
        PSS_Properties::IPropertyIterator it(&props);
        std::size_t                       counterEnableEmpty = 0;

        // iterate through the properties and change their enabled flag. To change it, need to check if it is a new
        // property that need to be enabled or not, then need to ensure that only an empty property is enable
        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            if (pProp->GetCategoryID() == ZS_BP_PROP_RULELIST)
            {
                // if the string is not empty, set its enabled flag to true
                if (!pProp->GetValueString().IsEmpty())
                    pProp->SetEnabled(true);

                // if the string is empty, check if its enabled flag is set and add it to the counter.
                // Enable or disable it according to if the counter is equal or not to 1
                if (pProp->GetValueString().IsEmpty())
                {
                    if (pProp->GetEnabled())
                        ++counterEnableEmpty;
                    else
                    // if not at least one empty element
                    if (counterEnableEmpty < 1)
                    {
                        pProp->SetEnabled(true);
                        ++counterEnableEmpty;
                    }

                    // if the counter is greater than 1, need to disable the empty element
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
    if (prop.GetCategoryID() == ZS_BP_PROP_TASKLIST)
    {
        // change the return value to reload the properties. Need to reload since the rule list has an empty task.
        // If the user fills it, need to enable a new empty one. And if the user remove one task, need also to
        // disable one from the property list
        PSS_Properties::IPropertyIterator it(&props);
        std::size_t                       counterEnableEmpty = 0;

        // iterate through the properties and change their enabled flag. To change it, need to check if it is a new
        // property that need to be enabled or not, then need to ensure that only an empty property is enable
        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            if (pProp->GetCategoryID() == ZS_BP_PROP_TASKLIST)
            {
                // if the string is not empty, set the enabled flag to true
                if (!pProp->GetValueString().IsEmpty())
                    pProp->SetEnabled(true);

                // if the string is empty, check if its enabled flag is set and add it to the counter.
                // Enable or disable it according to if the counter is equal or not to 1
                if (pProp->GetValueString().IsEmpty())
                {
                    if (pProp->GetEnabled())
                        ++counterEnableEmpty;
                    else
                    // if not at least one empty element
                    if (counterEnableEmpty < 1)
                    {
                        pProp->SetEnabled(true);
                        ++counterEnableEmpty;
                    }

                    // if the counter is greater than 1, need to disable the empty element
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
    if (prop.GetCategoryID() == ZS_BP_PROP_DECISIONLIST)
    {
        // change the return value to reload the properties. Need to reload since the decision list has an empty decision.
        // If the user fills it, need to enable a new empty one. And if the user remove one decision, need also to
        // disable one from the property list
        PSS_Properties::IPropertyIterator it(&props);
        std::size_t                       counterEnableEmpty = 0;

        // iterate through the properties and change their enabled flag. To change it, need to check if it is a new
        // property that need to be enabled or not, then need to ensure that only an empty property is enable
        for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            if (pProp->GetCategoryID() == ZS_BP_PROP_DECISIONLIST)
            {
                // if the string is not empty, set its enabled flag to true
                if (!pProp->GetValueString().IsEmpty())
                    pProp->SetEnabled(true);

                // if the string is empty, check if its enabled flag is set and add it to the counter.
                // Enable or disable it according to if the counter is equal or not to 1
                if (pProp->GetValueString().IsEmpty())
                {
                    if (pProp->GetEnabled() == true)
                        ++counterEnableEmpty;
                    else
                    // if not at least one empty element
                    if (counterEnableEmpty < 1)
                    {
                        pProp->SetEnabled(true);
                        ++counterEnableEmpty;
                    }

                    // if the counter is greater than 1, need to disable the empty element
                    if (counterEnableEmpty > 1)
                    {
                        --counterEnableEmpty;
                        pProp->SetEnabled(false);
                    }
                }
            }

        result = true;
    }

    if (!result)
        return PSS_Symbol::OnPostPropertyChanged(prop, props, refresh);

    return result;
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::OnDropInternalPropertyItem(PSS_Property&                 srcProperty,
                                                       PSS_Property&                 dstProperty,
                                                       bool                          top2Down,
                                                       PSS_Properties::IPropertySet& props)
{
    bool result = ::SwapInternalPropertyItem(srcProperty, dstProperty, top2Down, props, ZS_BP_PROP_TASKLIST);

    if (result)
        return true;

    result = ::SwapInternalPropertyItem(srcProperty, dstProperty, top2Down, props, ZS_BP_PROP_RULELIST);

    if (result)
        return true;

    result = ::SwapInternalPropertyItem(srcProperty, dstProperty, top2Down, props, ZS_BP_PROP_RULES);

    if (result)
    {
        const int srcIndex = (srcProperty.GetItemID() - M_Rule_Name_ID) / g_MaxRulesSize;
        const int dstIndex = (dstProperty.GetItemID() - M_Rule_Name_ID) / g_MaxRulesSize;

        const CString srcRuleName = m_Rules.GetRuleName(srcIndex);
        const CString srcRuleDesc = m_Rules.GetRuleDescription(srcIndex);
        const CString srcRuleGUID = m_Rules.GetRuleGUID(srcIndex);

        const CString dstRuleName = m_Rules.GetRuleName(dstIndex);
        const CString dstRuleDesc = m_Rules.GetRuleDescription(dstIndex);
        const CString dstRuleGUID = m_Rules.GetRuleGUID(dstIndex);

        m_Rules.SetRuleName(srcIndex, dstRuleName);
        m_Rules.SetRuleDescription(srcIndex, dstRuleDesc);
        m_Rules.SetRuleGUID(srcIndex, dstRuleGUID);

        m_Rules.SetRuleName(dstIndex, srcRuleName);
        m_Rules.SetRuleDescription(dstIndex, srcRuleDesc);
        m_Rules.SetRuleGUID(dstIndex, srcRuleGUID);

        return true;
    }

    // otherwise, do it for decisions
    return ::SwapInternalPropertyItem(srcProperty, dstProperty, top2Down, props, ZS_BP_PROP_DECISIONLIST);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::OnFillDefaultAttributes(PSS_PropertyAttributes* pAttributes)
{
    if (!pAttributes)
        return false;

    PSS_PropertyAttributes& attributes = PSS_ModelGlobal::GetGlobalPropertyAttributes(GetObjectTypeID());

    // if global attributes were defined, copy them
    if (attributes.GetAttributeCount() > 0)
        *pAttributes = attributes;
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
bool PSS_ProcedureSymbolBP::OnChangeAttributes(PSS_PropertyAttributes* pAttributes)
{
    return PSS_Symbol::OnChangeAttributes(pAttributes);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::OnConnect(CODConnection* pConnection)
{
    PSS_Symbol::OnConnect(pConnection);

    CheckInitialCombination();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::OnDisconnect(CODConnection* pConnection)
{
    PSS_Symbol::OnDisconnect(pConnection);

    CheckInitialCombination();
}
//---------------------------------------------------------------------------
BOOL PSS_ProcedureSymbolBP::OnConnectionMove(CODConnection* pConnection)
{
    return PSS_Symbol::OnConnectionMove(pConnection);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::OnLinkDisconnect(CODLinkComponent* pLink)
{
    PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pLink);

    if (pLinkSymbol)
        DeleteDeliverableFromAllCombinations(pLinkSymbol->GetSymbolName());
}
//---------------------------------------------------------------------------
BOOL PSS_ProcedureSymbolBP::OnDoubleClick()
{
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_Symbol::OnUpdate(pSubject, pMsg);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::OnDraw(CDC* pDC)
{
    PSS_Symbol::OnDraw(pDC);
}
//---------------------------------------------------------------------------
bool PSS_ProcedureSymbolBP::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    toolTipText.Format(IDS_FS_BPPROCEDURE_TOOLTIP,
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
void PSS_ProcedureSymbolBP::AdjustElementPosition()
{
    PSS_Symbol::AdjustElementPosition();
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::CheckInitialCombination()
{
    // check if only one combination. If it's the case, set all deliverables to the combination
    if (GetCombinationCount() == 1)
    {
        // get all deliverables
        CString enteringDeliverables;
        GetEnteringUpDeliverable(enteringDeliverables);

        // set it
        SetCombinationDeliverables(0, enteringDeliverables);

        // if no entering deliverables, remove the master
        if (enteringDeliverables.IsEmpty())
            SetCombinationMaster(0, enteringDeliverables);
        else
        {
            // if there is only one deliverable, it's the master
            PSS_Tokenizer token(enteringDeliverables);

            if (token.GetTokenCount() == 1)
            {
                CString value;

                // get the token at index
                if (token.GetTokenAt(0, value))
                    SetCombinationMaster(0, value);
            }
        }

        SetCombinationActivationPerc(0, GetMaxActivationPerc(GetCombinationMaster(0)));
    }
}
//---------------------------------------------------------------------------
float PSS_ProcedureSymbolBP::GetMaxActivationPerc(const CString& master)
{
    if (master.IsEmpty())
        return 0.0f;

    double       sum            = 0;
    double       masterQuantity = 0;
    CODEdgeArray edges;

    // get all procedures entering up edges
    if (GetEnteringUpDeliverable(edges) > 0)
    {
        const int edgeCount = edges.GetSize();

        for (int i = 0; i < edgeCount; ++i)
        {
            IODEdge*                     pIEdge = edges.GetAt(i);
            PSS_DeliverableLinkSymbolBP* pComp = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

            // check if it's a local symbol
            if (!pComp->IsLocal())
                // get the local symbol
                pComp = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pComp->GetLocalSymbol());

            if (pComp)
            {
                // check if the component is the master
                if (pComp->GetSymbolName() == master)
                    masterQuantity = (double)pComp->GetQuantity();

                // iterate through combinations and check if the component is the combination master,
                // add its quantity to the sum
                const int combinationCount = GetCombinationCount();

                for (int i = 0; i < combinationCount; ++i)
                    if (pComp->GetSymbolName() == GetCombinationMaster(i))
                        sum += (double)pComp->GetQuantity();
            }
        }
    }

    if (!sum)
        return 0.0f;

    return float(masterQuantity / sum);
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::OnAddNewCombination(PSS_Property&                 prop,
                                                CString&                      value,
                                                PSS_Properties::IPropertySet& props,
                                                bool&                         refresh)
{
    // add a new combination
    if (AddNewCombination() >= 0)
    {
        // set the refresh flag to true
        refresh = true;
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::OnDelCurrentCombination(PSS_Property&                 prop,
                                                    CString&                      value,
                                                    PSS_Properties::IPropertySet& props,
                                                    bool&                         refresh)
{
    const int count = GetCombinationCount();

    if (count <= 1)
    {
        // cannot delete all combinations
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOTDELETE_ALLCOMBINATIONS, MB_OK);
        return;
    }

    // otherwise, delete the currently selected combination
    const int index = prop.GetCategoryID() - ZS_BP_PROP_COMBINATION;

    if (DeleteCombination(index))
    {
        // set the refresh flag to true
        refresh = true;
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::OnAddDeliverableCombination(PSS_Property&                 prop,
                                                        CString&                      value,
                                                        PSS_Properties::IPropertySet& props,
                                                        bool&                         refresh)
{}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::OnDelDeliverableCombination(PSS_Property&                 prop,
                                                        CString&                      value,
                                                        PSS_Properties::IPropertySet& props,
                                                        bool&                         refresh)
{}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::OnAddNewRisk(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props, bool& refresh)
{
    // sdd a new risk
    if (AddNewRisk() >= 0)
    {
        // set the refresh flag to true
        refresh = true;
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcedureSymbolBP::OnDelCurrentRisk(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props, bool& refresh)
{
    const int count = GetRiskCount();

    if (count <= 1)
    {
        // cannot delete all risks
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOTDELETE_ALLRISKS, MB_OK);
        return;
    }

    // otherwise, delete the currently selected risk
    const int index = prop.GetCategoryID() - ZS_BP_PROP_RISK;

    if (DeleteRisk(index))
    {
        // set the refresh flag to true
        refresh = true;
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
