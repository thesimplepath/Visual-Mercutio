/****************************************************************************
 * ==> PSS_ProcessSymbolBP -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a process symbol for banking process              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessSymbolBP.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseSym\zBaseSymRes.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#define _ZMODELEXPORT
    #include "zModel\PSS_BasicProperties.h"
#undef _ZMODELEXPORT
#include "zModel\PSS_DocObserverMsg.h"
#include "zModel\PSS_ModelGlobal.h"
#include "zModel\PSS_PrestationsEntity.h"
#include "zModel\PSS_ProcessGraphPage.h"
#include "zProperty\PSS_PropertyAttributes.h"
#include "PSS_ProcessPropertiesBP.h"
#include "PSS_SimPropertiesProcessBP.h"
#include "PSS_DeliveriesPropertiesBP.h"
#include "PSS_DeliverableLinkSymbolBP.h"
#include "PSS_AddRemoveDeliveryDeliverablesDlg.h"
#include "PSS_SelectMainDeliverableDlg.h"
#include "PSS_ProcessGraphModelControllerBP.h"
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
static CMenu       g_DeliveriesMenu;
static CMenu       g_PrestationsMenu;
static CMenu       g_RulesMenu;
static CMenu       g_RiskMenu;
const  std::size_t g_MaxDeliveryListSize = 20;
const  std::size_t g_MaxRulesSize        = 20;
const  std::size_t g_MaxRisksSize        = 20;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ProcessSymbolBP, PSS_Symbol, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ProcessSymbolBP
//---------------------------------------------------------------------------
PSS_ProcessSymbolBP::PSS_ProcessSymbolBP(const CString& name) :
    PSS_Symbol(),
    m_Deliveries(this),
    m_IsUserModified(false),
    m_ShowPreview(false)
{
    PSS_Symbol::SetSymbolName(name);
    CreateSymbolProperties();
}
//---------------------------------------------------------------------------
PSS_ProcessSymbolBP::PSS_ProcessSymbolBP(const PSS_ProcessSymbolBP& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ProcessSymbolBP::~PSS_ProcessSymbolBP()
{
    m_PrestProperties.RemoveAll();

    if (m_pModel && !IsCopy())
        delete m_pModel;
}
//---------------------------------------------------------------------------
PSS_ProcessSymbolBP& PSS_ProcessSymbolBP::operator = (const PSS_ProcessSymbolBP& other)
{
    PSS_Symbol::operator = ((const PSS_Symbol&)other);

    m_PrestProperties = other.m_PrestProperties;
    m_Deliveries      = other.m_Deliveries;
    m_Rules           = other.m_Rules;
    m_Risks           = other.m_Risks;

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessSymbolBP::Create(const CString& name)
{
    BOOL result = FALSE;

    try
    {
        m_IsInCreationProcess = true;
        result                = PSS_Symbol::Create(IDR_BP_PROCESS,
                                                   ::AfxFindResourceHandle(MAKEINTRESOURCE(IDR_PROCESS_SYM),
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
BOOL PSS_ProcessSymbolBP::CreateEmptyChildModel(CODModel* pParent)
{
    if (!m_pModel)
        m_pModel = new PSS_ProcessGraphModelMdlBP(GetSymbolName(), dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pParent));
    else
        return FALSE;

    return (m_pModel != NULL);
}
//---------------------------------------------------------------------------
CODComponent* PSS_ProcessSymbolBP::Dup() const
{
    return new PSS_ProcessSymbolBP(*this);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::CopySymbolDefinitionFrom(const CODSymbolComponent& src)
{
    PSS_Symbol::CopySymbolDefinitionFrom(src);

    const PSS_ProcessSymbolBP* pSymbol = dynamic_cast<const PSS_ProcessSymbolBP*>(&src);

    if (pSymbol)
    {
        m_PrestProperties = pSymbol->m_PrestProperties;
        m_SimProperties   = pSymbol->m_SimProperties;
        m_Deliveries      = pSymbol->m_Deliveries;
        m_Deliveries.SetParent(this);
        m_Rules           = pSymbol->m_Rules;
        m_Risks           = pSymbol->m_Risks;
        m_CommentRect     = pSymbol->m_CommentRect;
        m_ShowPreview     = pSymbol->m_ShowPreview;
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessSymbolBP::SetSymbolName(const CString& value)
{
    PSS_ProcessGraphModelMdl* pProcessGraphModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pModel);

    // change the model name
    if (pProcessGraphModel)
        pProcessGraphModel->SetModelName(value);

    // change the symbol name
    return PSS_Symbol::SetSymbolName(value);
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    // don't allow the drop if the symbol isn't local
    if (!IsLocal())
        return false;

    if (pObj)
    {
        // is a kind of prestation?
        if (ISA(pObj, PSS_PrestationsEntity))
            return true;

        // is a kind of rule?
        if (ISA(pObj, PSS_LogicalRulesEntity))
            return true;
    }

    return PSS_Symbol::AcceptDropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::DropItem(CObject* pObj, const CPoint& point)
{
    PSS_LogicalPrestationsEntity* pPrestations = dynamic_cast<PSS_LogicalPrestationsEntity*>(pObj);

    // drop a prestation
    if (pPrestations)
    {
        PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

        // check the prestations validity on the model
        if (pModel && !pModel->MainLogicalPrestationsIsValid())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_PRESTATIONSNOTINLINE, MB_OK);
            return false;
        }

        std::unique_ptr<PSS_Prestation> pNewPrestation(new PSS_Prestation());
        pNewPrestation->SetName(pPrestations->GetEntityName());
        pNewPrestation->SetGUID(pPrestations->GetGUID());
        m_PrestProperties.AddPrestation(pNewPrestation.get());
        pNewPrestation.release();

        // set the symbol as modified
        SetModifiedFlag(TRUE);

        // refresh the attribute area and redraw the symbol
        RefreshAttributeTextArea(true);

        return true;
    }

    PSS_LogicalRulesEntity* pRules = dynamic_cast<PSS_LogicalRulesEntity*>(pObj);

    // drop a rule
    if (pRules)
    {
        PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());

        // check the rules validity on the model
        if (pModel && !pModel->MainLogicalRulesIsValid())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_RULENOTINLINE, MB_OK);
            return false;
        }

        std::unique_ptr<PSS_RulesPropertiesBP> pRule(new PSS_RulesPropertiesBP());

        pRule->SetRuleName(pRules->GetEntityName());
        pRule->SetRuleDescription(pRules->GetEntityDescription());
        pRule->SetRuleGUID(pRules->GetGUID());
        m_Rules.AddRule(pRule.get());
        pRule.release();

        // set the symbol as modified
        SetModifiedFlag(TRUE);

        // refresh the attribute area and redraw the symbol
        RefreshAttributeTextArea(true);

        return true;
    }

    return PSS_Symbol::DropItem(pObj, point);
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::CreateSymbolProperties()
{
    if (!PSS_Symbol::CreateSymbolProperties())
        return false;

    PSS_ProcessPropertiesBP propProcess;
    AddProperty(propProcess);

    m_Deliveries.CreateInitialProperties();
    m_Risks.CreateInitialProperties();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::FillProperties(PSS_Properties::IPropertySet& propSet, bool numericValues, bool groupValues)
{
    // the "Name", "Description" and "Reference" properties of the "General" group can be found in the base class
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

    // if the rules menu is still not loaded, load it
    if (!g_RulesMenu.GetSafeHmenu())
        g_RulesMenu.LoadMenu(IDR_RULES_MENU);

    // fill the rule properties
    if (m_Rules.GetRulesCount() > 0)
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

        const int ruleCount = m_Rules.GetRulesCount();

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
            pProp.release();
        }
    }

    // if the risks menu is still not loaded, load it
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

        CString noRiskType = _T("");
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

        // the "Impact" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Impact_ID : (M_Risk_Impact_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     PSS_Application::Instance()->GetMainForm()->GetRiskImpactContainer()->GetElementAt(GetRiskImpact(i)),
                                     PSS_Property::IE_T_EditExtendedReadOnly));

        propSet.Add(pProp.get());
        pProp.release();

        riskName.LoadString(IDS_Z_RISK_PROBABILITY_NAME);
        riskDesc.LoadString(IDS_Z_RISK_PROBABILITY_DESC);

        // the "Probability" property of the "Risk (x)" group
        pProp.reset(new PSS_Property(finalRiskTitle,
                                     groupValues ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                     riskName,
                                     groupValues ? M_Risk_Probability_ID : (M_Risk_Probability_ID + (i * g_MaxRisksSize)),
                                     riskDesc,
                                     PSS_Application::Instance()->GetMainForm()->GetRiskProbabilityContainer()->GetElementAt(GetRiskProbability(i)),
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

        // the "Unitary estimation" property of the "Risk (x)" group
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

        // the "Annual operating loss" property of the "Risk (x)" group
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

    // get the sum of deliveries
    const float sumOfDeliveries = CalculateSumOfDeliveries();

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

    PSS_ProcessPropertiesBP* pProcessProps = static_cast<PSS_ProcessPropertiesBP*>(GetProperty(ZS_BP_PROP_PROCESS));

    if (!pProcessProps)
        return false;

    // the "Management case" property of the "Process" group
    pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_PROCESS_TITLE,
                                 ZS_BP_PROP_PROCESS,
                                 IDS_Z_MANAGEMENT_CASE_NAME,
                                 M_Management_Case_ID,
                                 IDS_Z_MANAGEMENT_CASE_DESC,
                                 pProcessProps->GetManagementCase()));

    propSet.Add(pProp.get());
    pProp.release();

    // if the prestations menu is still not loaded, load it
    if (!g_PrestationsMenu.GetSafeHmenu())
        g_PrestationsMenu.LoadMenu(IDR_PRESTATIONS_MENU);

    POSITION pPos = m_PrestProperties.GetHeadPosition();
    int      i    = 0;

    while (pPos)
    {
        PSS_Prestation* pCurNode = m_PrestProperties.GetAt(pPos);

        if (pCurNode)
        {
            bool error = false;
            pCurNode->SetName(RetrievePrestationName(pCurNode->GetGUID(), error));

            CString propTitle;
            propTitle.LoadString(IDS_Z_PRESTATIONS_TITLE);

            CString propTitleNbr;
            propTitleNbr.Format(_T(" %i"), ++i);
            propTitle += propTitleNbr;

            CString propSubTitle;
            propSubTitle.LoadString(IDS_Z_PRESTATION_NAME_TITLE);

            CString propDesc;
            propDesc.LoadString(IDS_Z_PRESTATION_NAME_DESC);

            // the "Prestations" property of the "Prestation (x)" group
            pProp.reset(new PSS_Property(propTitle,
                                         ZS_BP_PROP_PRESTATIONS,
                                         propSubTitle,
                                         M_Prestation_Name,
                                         propDesc,
                                         pCurNode->GetName(),
                                         PSS_Property::IE_T_EditMenu,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                         NULL,
                                         &g_PrestationsMenu));

            propSet.Add(pProp.get());
            pProp.release();

            float percentageActivity = 0.0f;
            pCurNode->GetValue(M_Prestation_Percentage, percentageActivity);

            propSubTitle.LoadString(IDS_Z_PRESTATION_PERCENTAGE_TITLE);
            propDesc.LoadString(IDS_Z_PRESTATION_PERCENTAGE_DESC);

            // the "Percentage" property of the "Prestation (x)" group
            pProp.reset(new PSS_Property(propTitle,
                                         ZS_BP_PROP_PRESTATIONS,
                                         propSubTitle,
                                         M_Prestation_Percentage,
                                         propDesc,
                                         percentageActivity,
                                         PSS_Property::IE_T_EditNumber,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_Percentage)));

            propSet.Add(pProp.get());
            pProp.release();

            // the following prestations depends on Sesterce
            if (pProcessGraphModel && pProcessGraphModel->GetIntegrateCostSimulation())
            {
                propSubTitle.LoadString(IDS_Z_PRESTPROCESS_TITLE);
                propDesc.LoadString(IDS_Z_PRESTPROCESS_DESC);

                const float propPrestProcessValue = sumOfDeliveries * percentageActivity;

                // the "Process" property of the "Prestation (x)" group
                pProp.reset(new PSS_Property(propTitle,
                                             ZS_BP_PROP_PRESTATIONS,
                                             propSubTitle,
                                             M_Prestation_Prest_Process,
                                             propDesc,
                                             propPrestProcessValue,
                                             PSS_Property::IE_T_EditNumberReadOnly,
                                             true,
                                             PSS_StringFormat(PSS_StringFormat::IE_FT_Accounting, false, 0)));

                propSet.Add(pProp.get());
                pProp.release();
            }

            // todo -cFeature -oJean: Localize me
            // the "Identifiant" property of the "Prestation (x)" group
            pProp.reset(new PSS_Property(propTitle,
                                         ZS_BP_PROP_PRESTATIONS,
                                         "Identifiant",
                                         M_Prestation_Identifier,
                                         "Identifiant de la prestation",
                                         pCurNode->GetGUID(),
                                         PSS_Property::IE_T_EditStringReadOnly,
                                         false));

            propSet.Add(pProp.get());
            pProp.release();
        }

        pPos = m_PrestProperties.GetNextPosition();
    }

    // the following properties depends on Sesterce
    if (pProcessGraphModel && pProcessGraphModel->GetIntegrateCostSimulation())
    {
        // the "Charge" property of the "Calculations and forecasts" group
        if (numericValues)
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCESS,
                                         ZS_BP_PROP_SIM_PROCESS,
                                         IDS_Z_SIM_PROCESS_WORKLOAD_FORECAST_NAME,
                                         M_Sim_Process_Workload_Forecast_ID,
                                         IDS_Z_SIM_PROCESS_WORKLOAD_FORECAST_DESC,
                                         double(GetProcessWorkloadForecast()),
                                         PSS_Property::IE_T_EditNumber));
        else
            pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCESS,
                                         ZS_BP_PROP_SIM_PROCESS,
                                         IDS_Z_SIM_PROCESS_WORKLOAD_FORECAST_NAME,
                                         M_Sim_Process_Workload_Forecast_ID,
                                         IDS_Z_SIM_PROCESS_WORKLOAD_FORECAST_DESC,
                                         PSS_Duration(double(GetProcessWorkloadForecast()),
                                                      hourPerDay,
                                                      dayPerWeek,
                                                      dayPerMonth,
                                                      dayPerYear),
                                         PSS_Property::IE_T_EditDurationReadOnly,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Cost" property of the "Calculations and forecasts" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCESS,
                                     ZS_BP_PROP_SIM_PROCESS,
                                     IDS_Z_SIM_PROCESS_COST_FORECAST_NAME,
                                     M_Sim_Process_Cost_Forecast_ID,
                                     IDS_Z_SIM_PROCESS_COST_FORECAST_DESC,
                                     double(GetProcessCostForecast()),
                                     PSS_Property::IE_T_EditNumberReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "HMO cost" property of the "Calculations and forecasts" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCESS,
                                     ZS_BP_PROP_SIM_PROCESS,
                                     IDS_Z_SIM_PROCESS_COST_NAME,
                                     M_Sim_Process_Cost_HMO_ID,
                                     IDS_Z_SIM_PROCESS_COST_DESC,
                                     double(GetProcessCostHMO()),
                                     PSS_Property::IE_T_EditNumberReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Sum of deliveries" property of the "Calculations and forecasts" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCESS,
                                     ZS_BP_PROP_SIM_PROCESS,
                                     IDS_Z_SIM_PROCESS_SUM_DELIVERIES_NAME,
                                     M_Sim_Process_Sum_Deliveries_ID,
                                     IDS_Z_SIM_PROCESS_SUM_DELIVERIES_DESC,
                                     sumOfDeliveries,
                                     PSS_Property::IE_T_EditNumberReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_Accounting, false, 0)));

        propSet.Add(pProp.get());
        pProp.release();

        float workloadByDeliveries = 0.0f;
        float costByDeliveries     = 0.0f;

        if (sumOfDeliveries)
        {
            workloadByDeliveries = float(GetProcessWorkloadForecast()) / sumOfDeliveries;
            costByDeliveries     = float(GetProcessCostForecast())     / sumOfDeliveries;
        }

        // the "Charge / delivery" property of the "Calculations and forecasts" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCESS,
                                     ZS_BP_PROP_SIM_PROCESS,
                                     IDS_Z_SIM_PROCESS_WORKLOAD_BY_DELIVERIES,
                                     M_Sim_Process_Workload_By_Deliveries_ID,
                                     IDS_Z_SIM_PROCESS_WORKLOAD_BY_DELIVERIES_DESC,
                                     PSS_Duration(double(workloadByDeliveries),
                                                  hourPerDay,
                                                  dayPerWeek,
                                                  dayPerMonth,
                                                  dayPerYear),
                                     PSS_Property::IE_T_EditDurationReadOnly,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7)));

        propSet.Add(pProp.get());
        pProp.release();

        // the "Cost / delivery" property of the "Calculations and forecasts" group
        pProp.reset(new PSS_Property(IDS_ZS_BP_PROP_SIM_PROCESS,
                                     ZS_BP_PROP_SIM_PROCESS,
                                     IDS_Z_SIM_PROCESS_COST_BY_DELIVERIES,
                                     M_Sim_Process_Cost_By_Deliveries_ID,
                                     IDS_Z_SIM_PROCESS_COST_BY_DELIVERIES_DESC,
                                     costByDeliveries,
                                     PSS_Property::IE_T_EditNumberReadOnly));

        propSet.Add(pProp.get());
        pProp.release();
    }

    // if the deliveries menu is still not loaded, load it
    if (!g_DeliveriesMenu.GetSafeHmenu())
        g_DeliveriesMenu.LoadMenu(IDR_DELIVERIES_MENU);

    CString propTitle;
    propTitle.LoadString(IDS_ZS_BP_PROP_DELIVERY_TITLE);

    CString   propName;
    CString   propDesc;
    const int deliveriesCount = GetDeliveriesCount();

    // iterate through deliveries
    for (int i = 0; i < deliveriesCount; ++i)
    {
        // check and update the initial delivery
        UpdateValuesForThisDeliveryProperty(i);

        CString finalPropTitle;
        finalPropTitle.Format(_T("%s (%d)"), propTitle, i + 1);

        propName.LoadString(IDS_Z_DELIVERY_NAME_NAME);
        propDesc.LoadString(IDS_Z_DELIVERY_NAME_DESC);

        // the "Title" property of the "Deliveries (x)" group
        pProp.reset(new PSS_Property(finalPropTitle,
                                     groupValues ? ZS_BP_PROP_DELIVERIES : (ZS_BP_PROP_DELIVERIES + i),
                                     propName,
                                     groupValues ? M_Delivery_Name_ID : (M_Delivery_Name_ID + (i * g_MaxDeliveryListSize)),
                                     propDesc,
                                     GetDeliveryName(i),
                                     PSS_Property::IE_T_EditMenu,
                                     true,
                                     PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                     NULL,
                                     &g_DeliveriesMenu));

        propSet.Add(pProp.get());
        pProp.release();

        propName.LoadString(IDS_Z_DELIVERY_DELIVERABLES_NAME);
        propDesc.LoadString(IDS_Z_DELIVERY_DELIVERABLES_DESC);

        // the "Delivery" property of the "Deliveries (x)" group
        pProp.reset(new PSS_Property(finalPropTitle,
                                     groupValues ? ZS_BP_PROP_DELIVERIES : (ZS_BP_PROP_DELIVERIES + i),
                                     propName,
                                     groupValues ? M_Delivery_Deliverables_ID : (M_Delivery_Deliverables_ID + (i * g_MaxDeliveryListSize)),
                                     propDesc,
                                     GetDeliveryDeliverables(i),
                                     PSS_Property::IE_T_EditExtendedReadOnly));

        propSet.Add(pProp.get());
        pProp.release();

        // the following properties depends on Sesterce
        if (pProcessGraphModel && pProcessGraphModel->GetIntegrateCostSimulation())
        {
            propName.LoadString(IDS_Z_DELIVERY_QUANTITY_NAME);
            propDesc.LoadString(IDS_Z_DELIVERY_QUANTITY_DESC);

            const float quantity = FindQuantity(GetDeliveryMain(i));

            // the "Quantity" property of the "Deliveries (x)" group
            pProp.reset(new PSS_Property(finalPropTitle,
                                         groupValues ? ZS_BP_PROP_DELIVERIES : (ZS_BP_PROP_DELIVERIES + i),
                                         propName,
                                         groupValues ? M_Delivery_Quantity_ID : (M_Delivery_Quantity_ID + (i * g_MaxDeliveryListSize)),
                                         propDesc,
                                         quantity,
                                         PSS_Property::IE_T_EditNumberReadOnly,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_Accounting, false, 0)));

            propSet.Add(pProp.get());
            pProp.release();

            propName.LoadString(IDS_Z_DELIVERY_PERCENTAGE_NAME);
            propDesc.LoadString(IDS_Z_DELIVERY_PERCENTAGE_DESC);

            const float percentage = GetDeliveryPercentage(i);

            // the "Percentage" property of the "Deliveries (x)" group
            pProp.reset(new PSS_Property(finalPropTitle,
                                         groupValues ? ZS_BP_PROP_DELIVERIES : (ZS_BP_PROP_DELIVERIES + i),
                                         propName,
                                         groupValues ? M_Delivery_Percentage_ID : (M_Delivery_Percentage_ID + (i * g_MaxDeliveryListSize)),
                                         propDesc,
                                         percentage,
                                         PSS_Property::IE_T_EditNumberReadOnly,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_Percentage)));

            propSet.Add(pProp.get());
            pProp.release();
        }

        propName.LoadString(IDS_Z_DELIVERY_MAIN_NAME);
        propDesc.LoadString(IDS_Z_DELIVERY_MAIN_DESC);

        // the "Main" property of the "Deliveries (x)" group
        pProp.reset(new PSS_Property(finalPropTitle,
                                     groupValues ? ZS_BP_PROP_DELIVERIES : (ZS_BP_PROP_DELIVERIES + i),
                                     propName,
                                     groupValues ? M_Delivery_Main_ID : (M_Delivery_Main_ID + (i * g_MaxDeliveryListSize)),
                                     propDesc,
                                     GetDeliveryMain(i),
                                     PSS_Property::IE_T_EditExtendedReadOnly));

        propSet.Add(pProp.get());
        pProp.release();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::SaveProperties(PSS_Properties::IPropertySet& PropSet)
{
    if (!PSS_Symbol::SaveProperties(PropSet))
        return false;

    // Only local symbol may access to properties
    if (!IsLocal())
        return true;

    PSS_ProcessPropertiesBP* pProcessProps = (PSS_ProcessPropertiesBP*)GetProperty(ZS_BP_PROP_PROCESS);

    if (!pProcessProps)
        return false;

    PSS_ProcessPropertiesBP           processProps(*pProcessProps);
    PSS_Properties::IPropertyIterator it(&PropSet);

    // iterate through the processes and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_PROCESS)
            switch (pProp->GetValueType())
            {
                case PSS_Property::IE_VT_String: processProps.SetValue(pProp->GetItemID(), pProp->GetValueString());            break;
                case PSS_Property::IE_VT_Double: processProps.SetValue(pProp->GetItemID(), float(pProp->GetValueDouble()));     break;
                case PSS_Property::IE_VT_Float:  processProps.SetValue(pProp->GetItemID(), pProp->GetValueFloat());             break;
                case PSS_Property::IE_VT_Date:   processProps.SetValue(pProp->GetItemID(), float(DATE(pProp->GetValueDate()))); break;
            }

    // set the new property
    SetProperty(&processProps);

    // iterate through the risks and fill the property set
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

    POSITION pPos = m_PrestProperties.GetHeadPosition();

    // iterate through the prestations and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_PRESTATIONS)
            if (pProp->GetItemID() == M_Prestation_Percentage)
                switch (pProp->GetValueType())
                {
                    case PSS_Property::IE_VT_Float:
                        if (pPos)
                        {
                            PSS_Prestation* pCurNode = m_PrestProperties.GetAt(pPos);

                            if (pCurNode)
                                pCurNode->SetValue(M_Prestation_Percentage, pProp->GetValueFloat());

                            pPos = m_PrestProperties.GetNextPosition();
                        }

                        break;
                }

    // iterate through the simulation processes and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == ZS_BP_PROP_SIM_PROCESS)
            switch (pProp->GetValueType())
            {
                case PSS_Property::IE_VT_String: m_SimProperties.SetValue(pProp->GetItemID(), pProp->GetValueString());            break;
                case PSS_Property::IE_VT_Double: m_SimProperties.SetValue(pProp->GetItemID(), pProp->GetValueDouble());            break;
                case PSS_Property::IE_VT_Float:  m_SimProperties.SetValue(pProp->GetItemID(), pProp->GetValueFloat());             break;
                case PSS_Property::IE_VT_Date:   m_SimProperties.SetValue(pProp->GetItemID(), float(DATE(pProp->GetValueDate()))); break;
            }

    // iterate through the deliveries and fill the property set
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        const int categoryID = pProp->GetCategoryID();

        if (categoryID >= ZS_BP_PROP_DELIVERIES && categoryID <= ZS_BP_PROP_DELIVERIES + GetDeliveriesCount())
        {
            const int                   i               = pProp->GetCategoryID() - ZS_BP_PROP_DELIVERIES;
            PSS_DeliveriesPropertiesBP* pDeliveriesProp = GetDeliveryProperty(i);

            if (!pDeliveriesProp)
                return false;

            switch (pProp->GetValueType())
            {
                case PSS_Property::IE_VT_String:   pDeliveriesProp->SetValue(pProp->GetItemID() - (i * g_MaxDeliveryListSize), pProp->GetValueString());            break;
                case PSS_Property::IE_VT_Double:   pDeliveriesProp->SetValue(pProp->GetItemID() - (i * g_MaxDeliveryListSize), float(pProp->GetValueDouble()));     break;
                case PSS_Property::IE_VT_Float:    pDeliveriesProp->SetValue(pProp->GetItemID() - (i * g_MaxDeliveryListSize), pProp->GetValueFloat());             break;
                case PSS_Property::IE_VT_Date:     pDeliveriesProp->SetValue(pProp->GetItemID() - (i * g_MaxDeliveryListSize), float(DATE(pProp->GetValueDate()))); break;
                case PSS_Property::IE_VT_TimeSpan: ASSERT(FALSE);                                                                                                   break;
                case PSS_Property::IE_VT_Duration: ASSERT(FALSE);                                                                                                   break;
            }
        }
    }

    RefreshAttributeTextArea(true);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::SaveProperty(PSS_Property& prop)
{
    if (!PSS_Symbol::SaveProperty(prop))
        return false;

    // only local symbol may access to properties
    if (!IsLocal())
        return true;

    const int categoryID = prop.GetCategoryID();

    // save the risk property
    if (categoryID >= ZS_BP_PROP_RISK && categoryID <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        const int i = categoryID - ZS_BP_PROP_RISK;

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

    // check if the user tried to rename a rule, if yes revert to previous name
    if (categoryID == ZS_BP_PROP_RULES)
    {
        const int index = (prop.GetItemID() - M_Rule_Name_ID) / g_MaxRulesSize;

        if (m_Rules.GetRuleName(index) != prop.GetValueString())
            prop.SetValueString(m_Rules.GetRuleName(index));
    }

    if (categoryID >= ZS_BP_PROP_DELIVERIES && categoryID <= ZS_BP_PROP_DELIVERIES + GetDeliveriesCount())
    {
        const int i = categoryID - ZS_BP_PROP_DELIVERIES;

        switch (prop.GetItemID() - (i * g_MaxDeliveryListSize))
        {
            case M_Delivery_Name_ID:         SetDeliveryName        (categoryID - ZS_BP_PROP_DELIVERIES, prop.GetValueString()); break;
            case M_Delivery_Deliverables_ID: SetDeliveryDeliverables(categoryID - ZS_BP_PROP_DELIVERIES, prop.GetValueString()); break;
            case M_Delivery_Quantity_ID:     SetDeliveryQuantity    (categoryID - ZS_BP_PROP_DELIVERIES, prop.GetValueFloat());  break;
            case M_Delivery_Main_ID:         SetDeliveryMain        (categoryID - ZS_BP_PROP_DELIVERIES, prop.GetValueString()); break;
        }
    }

    // set the symbol as modified
    SetModifiedFlag();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::ProcessExtendedInput(PSS_Property&                 prop,
                                               CString&                      value,
                                               PSS_Properties::IPropertySet& props,
                                               bool&                         refresh)
{
    const int categoryID = prop.GetCategoryID();

    // process the risks
    if (categoryID >= ZS_BP_PROP_RISK && categoryID <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        int                       i                = categoryID - ZS_BP_PROP_RISK;
        PSS_ProcessGraphModelMdl* pProcessGraphMdl = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRootModel());
        CString                   currencySymbol   = PSS_Global::GetLocaleCurrency();

        // get the model currency symbol
        if (pProcessGraphMdl)
        {
            PSS_ProcessGraphModelDoc* pProcessGraphDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pProcessGraphMdl->GetDocument());

            if (pProcessGraphDoc)
                currencySymbol = pProcessGraphDoc->GetCurrencySymbol();
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

    // process the deliveries
    if (categoryID >= ZS_BP_PROP_DELIVERIES && categoryID <= ZS_BP_PROP_DELIVERIES + GetDeliveriesCount())
    {
        const int i = categoryID - ZS_BP_PROP_DELIVERIES;

        switch (prop.GetItemID() - (i * g_MaxDeliveryListSize))
        {
            case M_Delivery_Deliverables_ID:
            {
                const CString availableList = GetAvailableDeliverables(props);

                // open the add/delete delivery dialog box
                PSS_AddRemoveDeliveryDeliverablesDlg dlg(availableList, value);

                if (dlg.DoModal() == IDOK)
                {
                    value            = dlg.GetDeliverables();
                    m_IsUserModified = true;
                    return true;
                }

                break;
            }

            case M_Delivery_Main_ID:
            {
                const CString mainList = GetPossibleListOfMainDeliverables(props, categoryID);

                // open the set master delivery dialog box
                PSS_SelectMainDeliverableDlg dlg(mainList, value);

                if (dlg.DoModal() == IDOK)
                {
                    value = dlg.GetMain();
                    return true;
                }

                break;
            }

            default:
                break;
        }
    }

    return PSS_Symbol::ProcessExtendedInput(prop, value, props, refresh);
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::ProcessMenuCommand(int                           menuCmdID,
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

    // process the prestations
    if (categoryID == ZS_BP_PROP_PRESTATIONS && prop.GetItemID() == M_Prestation_Name)
    {
        switch (menuCmdID)
        {
            case ID_DEL_CURRENTPRESTATION: OnDelCurrentPrestation(prop, value, props, refresh); break;
            default:                                                                            break;
        }

        return true;
    }

    // process the deliveries
    if (categoryID >= ZS_BP_PROP_DELIVERIES && categoryID <= ZS_BP_PROP_DELIVERIES + GetDeliveriesCount())
    {
        switch (menuCmdID)
        {
            case ID_ADD_NEWDELIVERY:     OnAddNewDelivery    (prop, value, props, refresh); break;
            case ID_DEL_CURRENTDELIVERY: OnDelCurrentDelivery(prop, value, props, refresh); break;
            default:                                                                        break;
        }

        return true;
    }

    // process the rules
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
CString PSS_ProcessSymbolBP::GetAttributeString(PSS_PropertyAttributes* pAttributes) const
{
    return PSS_Symbol::GetAttributeString(pAttributes);
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::CreateWorkflowActivity(bool defaultProp)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::SetDefaultPropertyToWorkflowActivity()
{
    return true;
}
//---------------------------------------------------------------------------
PSS_Tokenizer PSS_ProcessSymbolBP::GetPrestationsList()
{
    PSS_Tokenizer token(_T(""));
    POSITION      pPos = m_PrestProperties.GetHeadPosition();
    int           i    = 0;

    while (pPos)
    {
        PSS_Prestation* pCurNode = m_PrestProperties.GetAt(pPos);

        if (pCurNode)
            token.AddToken(pCurNode->GetName());

        pPos = m_PrestProperties.GetNextPosition();
    }

    return token;
}
//---------------------------------------------------------------------------
CString PSS_ProcessSymbolBP::GetRiskType(std::size_t index) const
{
    int     count    = PSS_Application::Instance()->GetMainForm()->GetRiskTypeContainer()->GetElementCount();
    CString riskType = m_Risks.GetRiskType(index);

    for (int i = 0; i < count; ++i)
        if (riskType == PSS_Application::Instance()->GetMainForm()->GetRiskTypeContainer()->GetElementAt(i))
            return m_Risks.GetRiskType(index);

    return _T("");
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessSymbolBP::ContainsRule(const CString& ruleName) const
{
    const int ruleCount = m_Rules.GetRulesCount();

    for (int i = 0; i < ruleCount; ++i)
        if (m_Rules.GetRuleName(i) == ruleName)
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::CheckRulesSync(CStringArray& rulesList)
{
    CODModel* pModel = GetRootModel();

    if (!pModel)
        return;

    const std::size_t ruleCount = m_Rules.GetRulesCount();

    if (ruleCount > 0)
    {
        PSS_ProcessGraphModelMdlBP* pProcessGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(GetOwnerModel());
        PSS_LogicalRulesEntity*     pMainRule          = NULL;

        if (pProcessGraphModel)
            pMainRule = pProcessGraphModel->GetMainLogicalRules();
        else
            return;

        for (int i = 0; i < int(ruleCount); ++i)
        {
            const CString safeName = GetRuleNameByGUID(pMainRule, m_Rules.GetRuleGUID(i));

            if (safeName.IsEmpty())
                rulesList.Add(m_Rules.GetRuleName(i));
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::Serialize(CArchive& ar)
{
    PSS_Symbol::Serialize(ar);

    // only if the object is serialized from or to a document
    if (ar.m_pDocument)
    {
        PSS_BaseDocument* pDoc = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

        if (pDoc && pDoc->GetDocumentStamp().GetInternalVersion() >= 24)
        {
            m_PrestProperties.Serialize(ar);
            m_Deliveries.Serialize(ar);
        }

        if (pDoc && pDoc->GetDocumentStamp().GetInternalVersion() >= 26)
            m_Rules.Serialize(ar);

        if (pDoc && pDoc->GetDocumentStamp().GetInternalVersion() >= 27)
            m_Risks.Serialize(ar);

        m_SimProperties.Serialize(ar);

        if (ar.IsStoring())
        {
            TRACE(_T("PSS_ProcessSymbolBP::Serialize - Start save\n"));

            ar << WORD(m_ShowPreview);
            ar << WORD(m_IsUserModified);

            TRACE(_T("PSS_ProcessSymbolBP::Serialize - End save\n"));
        }
        else
        {
            TRACE(_T("PSS_ProcessSymbolBP::Serialize - Start read\n"));

            WORD wValue;
            ar >> wValue;
            m_ShowPreview = bool(wValue);

            if (pDoc && pDoc->GetDocumentStamp().GetInternalVersion() >= 24)
            {
                ar >> wValue;
                m_IsUserModified = bool(wValue);
            }

            TRACE(_T("PSS_ProcessSymbolBP::Serialize - End read\n"));
        }

        if (m_pModel)
            m_pModel->SetName(GetSymbolName());
    }
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::OnPostCreation(CODModel* pModel, CODController* pCtrl)
{
    if (!PSS_Symbol::OnPostCreation(pModel, pCtrl))
        return false;

    PSS_ProcessGraphModelMdlBP* pProcessGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pModel);

    if (pProcessGraphModel)
    {
        PSS_ProcessGraphModelMdlBP* pRootModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcessGraphModel->GetRoot());

        if (!pRootModel)
            return false;

        CreateEmptyChildModel(pProcessGraphModel);

        PSS_ProcessGraphModelMdl* pCurMdl = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pModel);

        // if a new model is defined, create the first page
        if (pCurMdl && !pCurMdl->HasPageSet())
            pRootModel->CreateNewPage(pCurMdl, _T(""), pCurMdl);

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::OnPostPropertyChanged(PSS_Property& prop, PSS_Properties::IPropertySet& props, bool& refresh)
{
    // only local symbol may access to the properties
    if (!IsLocal())
        return false;

    const int categoryID = prop.GetCategoryID();
    bool      result     = false;

    if (categoryID >= ZS_BP_PROP_DELIVERIES && categoryID <= ZS_BP_PROP_DELIVERIES + GetDeliveriesCount())
    {
        const int i = categoryID - ZS_BP_PROP_DELIVERIES;

        switch (prop.GetItemID() - (i * g_MaxDeliveryListSize))
        {
            case M_Delivery_Deliverables_ID:
            {
                const float quantity = FindQuantity(GetDeliveryMain(categoryID - ZS_BP_PROP_DELIVERIES));

                PSS_Properties::IPropertyIterator it(&props);
                bool                              found = false;

                // iterate through propertis and search for the quantity
                for (PSS_Property* pProp = it.GetFirst(); pProp && !found; pProp = it.GetNext())
                {
                    if (!pProp || ((pProp->GetCategoryID() - ZS_BP_PROP_DELIVERIES) != i))
                        continue;

                    if (pProp->GetItemID() - (i * g_MaxDeliveryListSize) == M_Delivery_Quantity_ID)
                    {
                        pProp->SetValueFloat(quantity);
                        found = true;
                    }
                }

                if (found)
                    result = true;

                break;
            }

            default:
                break;
        }
    }

    if (!result)
        return PSS_Symbol::OnPostPropertyChanged(prop, props, refresh);

    return result;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::OnDropInternalPropertyItem(PSS_Property&                 srcProperty,
                                                     PSS_Property&                 dstProperty,
                                                     bool                          top2Down,
                                                     PSS_Properties::IPropertySet& props)
{
    if (!::SwapInternalPropertyItem(srcProperty, dstProperty, top2Down, props, ZS_BP_PROP_RULES))
        return false;

    const int srcIndex = (srcProperty.GetItemID() - M_Rule_Name_ID) / g_MaxRulesSize;
    const int dstIndex = (dstProperty.GetItemID() - M_Rule_Name_ID) / g_MaxRulesSize;

    const CString srcRuleName = m_Rules.GetRuleName(srcIndex);
    const CString srcRuleDesc = m_Rules.GetRuleDescription(srcIndex);
    const CString srcRuleGUID = m_Rules.GetRuleGUID(srcIndex);

    const CString dstRuleName = m_Rules.GetRuleName(dstIndex);
    const CString dstRuleDesc = m_Rules.GetRuleDescription(dstIndex);
    const CString dstRuleGUID = m_Rules.GetRuleGUID(dstIndex);

    m_Rules.SetRuleName       (srcIndex, dstRuleName);
    m_Rules.SetRuleDescription(srcIndex, dstRuleDesc);
    m_Rules.SetRuleGUID       (srcIndex, dstRuleGUID);

    m_Rules.SetRuleName       (dstIndex, srcRuleName);
    m_Rules.SetRuleDescription(dstIndex, srcRuleDesc);
    m_Rules.SetRuleGUID       (dstIndex, srcRuleGUID);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::OnFillDefaultAttributes(PSS_PropertyAttributes* pAttributes)
{
    if (!pAttributes)
        return false;

    // if global attributes exist, copy them
    if (PSS_ModelGlobal::GetGlobalPropertyAttributes(GetObjectTypeID()).GetAttributeCount() > 0)
        *pAttributes = PSS_ModelGlobal::GetGlobalPropertyAttributes(GetObjectTypeID());
    else
        // add the reference number
        pAttributes->AddAttribute(ZS_BP_PROP_BASIC, M_Symbol_Number_ID);

    return PSS_Symbol::OnFillDefaultAttributes(pAttributes);
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::OnChangeAttributes(PSS_PropertyAttributes* pAttributes)
{
    return PSS_Symbol::OnChangeAttributes(pAttributes);
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::OnDeliverableNameChange(const CString& oldName, const CString& newName)
{
    const int deliveriesCount = GetDeliveriesCount();

    for (int i = 0; i < deliveriesCount; ++i)
    {
        PSS_Tokenizer oldDeliverablesList(GetDeliveryDeliverables(i));
        PSS_Tokenizer newDeliverablesList(_T(""));

        for (std::size_t j = 0; j < oldDeliverablesList.GetTokenCount(); ++j)
        {
            CString curName;

            oldDeliverablesList.GetTokenAt(j, curName);

            if (curName == oldName)
            {
                newDeliverablesList.AddToken(newName);

                if (GetDeliveryMain(i) == oldName)
                    SetDeliveryMain(i, newName);
            }
            else
                newDeliverablesList.AddToken(curName);
        }

        SetDeliveryDeliverables(i, newDeliverablesList.GetString());
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::OnDelCurrentPrestation(PSS_Property&                 prop,
                                                 CString&                      value,
                                                 PSS_Properties::IPropertySet& props,
                                                 bool&                         refresh)
{
    POSITION pPos = m_PrestProperties.GetHeadPosition();
    int      i    = 0;

    while (pPos)
    {
        PSS_Prestation* pCurNode = m_PrestProperties.GetAt(pPos);

        if (pCurNode)
            switch (prop.GetValueType())
            {
                case PSS_Property::IE_VT_String:
                    if (prop.GetValueString() == pCurNode->GetName())
                    {
                        m_PrestProperties.RemovePrestation(pPos);

                        refresh = true;

                        // set the symbol as modified
                        SetModifiedFlag(TRUE);

                        return;
                    }

                    break;

                default:
                    break;
            }

        pPos = m_PrestProperties.GetNextPosition();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessSymbolBP::OnDoubleClick()
{
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::OnDraw(CDC* pDC)
{
    PSS_Symbol::OnDraw(pDC);
}
//---------------------------------------------------------------------------
bool PSS_ProcessSymbolBP::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    toolTipText.Format(IDS_FS_BPPROCESS_TOOLTIP,
                       (const char*)GetSymbolName(),
                       (const char*)GetSymbolComment(),
                       (const char*)GetSymbolReferenceNumberStr());

    if (mode == PSS_Symbol::IE_TT_Design)
    {
        // todo -cFeature -oJean: need to implement the result of the control checking
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::AdjustElementPosition()
{
    PSS_Symbol::AdjustElementPosition();
}
//---------------------------------------------------------------------------
CString PSS_ProcessSymbolBP::GetPossibleListOfMainDeliverables(const PSS_Properties::IPropertySet& propSet, int catID) const
{
    PSS_Properties::IPropertyIterator it(&propSet);

    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCategoryID() == catID)
        {
            const int index = pProp->GetCategoryID() - ZS_BP_PROP_DELIVERIES;

            if ((pProp->GetItemID() - (index * g_MaxDeliveryListSize)) == M_Delivery_Deliverables_ID)
                switch (pProp->GetValueType())
                {
                    case PSS_Property::IE_VT_String: return pProp->GetValueString();
                    default:                         return _T("");
                }
        }

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_ProcessSymbolBP::GetAvailableDeliverables(const PSS_Properties::IPropertySet& propSet) const
{
    CString deliverableList;
    GetDeliverablesInChildPages(deliverableList);

    PSS_Properties::IPropertyIterator it(&propSet);
    CString                           attribuedDeliverables;

    // build the set containing all the already attributed deliverables
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        const int categoryID = pProp->GetCategoryID();

        if (categoryID >= ZS_BP_PROP_DELIVERIES && categoryID <= ZS_BP_PROP_DELIVERIES + GetDeliveriesCount())
        {
            const int index = pProp->GetCategoryID() - ZS_BP_PROP_DELIVERIES;

            if ((pProp->GetItemID() - (index * g_MaxDeliveryListSize)) == M_Delivery_Deliverables_ID)
                switch (pProp->GetValueType())
                {
                    case PSS_Property::IE_VT_String:
                    {
                        const CString list = pProp->GetValueString();

                        if (!list.IsEmpty())
                            attribuedDeliverables += list + _T(";");

                        break;
                    }

                    default:
                        break;
                }
        }
    }

    PSS_Tokenizer srcToken(deliverableList);
    PSS_Tokenizer cmpToken(attribuedDeliverables);
    PSS_Tokenizer dstToken(_T(""));

    // compare the already attributed deliverables with all the deliverables contained in the children
    // pages. All of those which are not found in the attributed list are added to the available list
    for (std::size_t i = 0; i < srcToken.GetTokenCount(); ++i)
    {
        BOOL isAttribued = FALSE;

        CString src = _T("");
        srcToken.GetTokenAt(i, src);

        for (std::size_t j = 0; j < cmpToken.GetTokenCount(); ++j)
        {
            CString cmp = _T("");
            cmpToken.GetTokenAt(j, cmp);

            if (src == cmp)
                isAttribued = TRUE;
        }

        if (!isAttribued)
            dstToken.AddToken(src);
    }

    return dstToken.GetString();
}
//---------------------------------------------------------------------------
int PSS_ProcessSymbolBP::GetDeliverablesInChildPages(CString& deliverablesList) const
{
    int           counter = 0;
    PSS_Tokenizer token;

    // get the root child process model controller
    PSS_ProcessGraphModelMdlBP* pRootChldModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pModel);

    if (pRootChldModel)
    {
        // get the pages contained in the model controller
        PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pRootChldModel->GetPageSet();

        if (pSet)
        {
            PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(pSet);

            // iterate through children pages contained in the model controller
            for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
            {
                // get the current page model controller
                PSS_ProcessGraphModelMdlBP* pCurModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

                if (pCurModel)
                {
                    // get the page symbols
                    CODComponentSet* pCompSet = pCurModel->GetComponents();

                    // On passe en revue chacun des symboles de la page.
                    for (int i = 0; i < pCompSet->GetSize(); ++i)
                    {
                        PSS_DeliverableLinkSymbolBP* pSymbol = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pCompSet->GetAt(i));

                        // if the symbol is valid, and if it's a deliverable, get it
                        if (pSymbol)
                        {
                            BOOL    tokenAlreadyExist = FALSE;
                            CString name              = pSymbol->GetSymbolName();

                            // iterate through the registered names, and check if the new name is unique
                            for (int j = 0; j < token.GetTokenCount(); ++j)
                            {
                                CString src;
                                token.GetTokenAt(j, src);

                                if (src == name)
                                    tokenAlreadyExist = TRUE;
                            }

                            // if the new name is unique and can be used, add it in the list
                            if (!tokenAlreadyExist)
                            {
                                token.AddToken(name);
                                ++counter;
                            }
                        }
                    }
                }
            }
        }
    }

    deliverablesList = token.GetString();

    return counter;
}
//---------------------------------------------------------------------------
CString PSS_ProcessSymbolBP::CheckMainDeliverable(int index)
{
    const CString main = GetDeliveryDeliverables(index);

    // is the deliverable set empty?
    if (main.IsEmpty())
        return _T("");

    PSS_Tokenizer     cmpToken(main);
    const std::size_t tokenCount   = cmpToken.GetTokenCount();
    const CString     mainDelivery = GetDeliveryMain(index);

    // compare if the main delivery is still in the delivery deliverables list. Return a new "Main" field value
    // if the main deliverable previously selected can no longer be found in the delivery deliverables list
    for (std::size_t i = 0; i < tokenCount; ++i)
    {
        CString cmp;
        cmpToken.GetTokenAt(i, cmp);

        if (cmp == mainDelivery)
            return mainDelivery;
    }

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_ProcessSymbolBP::CheckDeliverables(int index)
{
    const CString deliveryList = GetDeliveryDeliverables(index);

    CString childPageList;
    GetDeliverablesInChildPages(childPageList);

    PSS_Tokenizer deliverablesListFromDelivery(deliveryList);
    PSS_Tokenizer deliverablesListFromChildPages(childPageList);
    PSS_Tokenizer deliverablesList;

    const std::size_t deliverableFromDeliveryCount = deliverablesListFromDelivery.GetTokenCount();

    for (std::size_t i = 0; i < deliverableFromDeliveryCount; ++i)
    {
        CString curVal;
        deliverablesListFromDelivery.GetTokenAt(i, curVal);

        const std::size_t deliverableFromChildPageCount = deliverablesListFromChildPages.GetTokenCount();

        for (std::size_t j = 0; j < deliverableFromChildPageCount; ++j)
        {
            CString checkVal;
            deliverablesListFromChildPages.GetTokenAt(j, checkVal);

            if (curVal == checkVal && !deliverablesList.TokenExist(curVal))
                deliverablesList.AddToken(curVal);
        }
    }

    return deliverablesList.GetString();
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::UpdateValuesForThisDeliveryProperty(std::size_t index)
{
    // update the field values for each deliverables properties index
    SetDeliveryDeliverables(index, CheckDeliverables(index));
    SetDeliveryMain        (index, CheckMainDeliverable(index));
    SetDeliveryQuantity    (index, FindQuantity(GetDeliveryMain(index)));
    SetDeliveryPercentage  (index, CalculateDeliveryPercentage(GetDeliveryQuantity(index)));
}
//---------------------------------------------------------------------------
float PSS_ProcessSymbolBP::FindQuantity(const CString& main, PSS_ProcessGraphModelMdlBP* pRootModel)
{
    // empty name?
    if (main.IsEmpty())
        return 0.0f;

    // if the root model is empty, the search should be performed on the entire document
    if (!pRootModel)
        pRootModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(GetRootModel());

    if (pRootModel)
    {
        // get the pages contained in the model controller
        PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pRootModel->GetPageSet();

        if (pSet)
        {
            PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(pSet);

            // iterate through the children pages contained in the model controller
            for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
            {
                // get the page model controller
                PSS_ProcessGraphModelMdlBP* pCurModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

                if (pCurModel)
                {
                    // get the page symbols
                    CODComponentSet* pCompSet = pCurModel->GetComponents();

                    if (pCompSet)
                    {
                        const int symbolCount = pCompSet->GetSize();

                        // iterate through the page symbols
                        for (int i = 0; i < symbolCount; ++i)
                        {
                            CODComponent*                pComponent  = pCompSet->GetAt(i);
                            PSS_DeliverableLinkSymbolBP* pLinkSymbol = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pComponent);

                            // is a deliverable?
                            if (pLinkSymbol)
                                // Check if the deliverable name matches with the searched one, and if the symbol is local
                                if (pLinkSymbol->GetSymbolName() == main && pLinkSymbol->IsLocal())
                                    // get and return the main deliverable quantity value
                                    return float(pLinkSymbol->GetQuantity());

                            PSS_ProcessSymbolBP* pProcessSymbol = dynamic_cast<PSS_ProcessSymbolBP*>(pComponent);

                            // is a process?
                            if (pProcessSymbol)
                            {
                                float result = 0.0f;

                                // get the process model controller
                                PSS_ProcessGraphModelMdlBP* pChildModel =
                                        dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcessSymbol->GetModel());

                                // call recursively the FindQuantity() function until all the process children pages
                                // were processed, or until the source deliverable was found
                                result = FindQuantity(main, pChildModel);

                                // found the result, break the recursion
                                if (result)
                                    return result;
                            }
                        }
                    }
                }
            }
        }
    }

    return 0.0f;
}
//---------------------------------------------------------------------------
float PSS_ProcessSymbolBP::CalculateSumOfDeliveries()
{
    const int deliveriesCount = GetDeliveriesCount();
    float     sumOfDeliveries = 0.0f;

    for (int i = 0; i < deliveriesCount; ++i)
        sumOfDeliveries += GetDeliveryQuantity(i);

    return sumOfDeliveries;
}
//---------------------------------------------------------------------------
CString PSS_ProcessSymbolBP::GetRuleNameByGUID(PSS_LogicalRulesEntity* pRule, const CString& ruleGUID)
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
            PSS_RulesEntity* pEntity = pRule->GetEntityAt(i);

            if (!pEntity)
                continue;

            PSS_LogicalRulesEntity* pRulesEntity = dynamic_cast<PSS_LogicalRulesEntity*>(pEntity);

            if (pRulesEntity)
            {
                const CString name = GetRuleNameByGUID(pRulesEntity, ruleGUID);

                if (!name.IsEmpty())
                    return name;
            }
        }
    }

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::OnAddNewRisk(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props, bool& refresh)
{
    // add a new risk
    if (AddNewRisk() >= 0)
    {
        refresh = true;

        // set the symbol as modified
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::OnDelCurrentRisk(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props, bool& refresh)
{
    const int count = GetRiskCount();

    // cannot delete all risks?
    if (count <= 1)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOTDELETE_ALLRISKS, MB_OK);
        return;
    }

    // otherwise delete the current selected risk
    const int index = prop.GetCategoryID() - ZS_BP_PROP_RISK;

    if (DeleteRisk(index))
    {
        refresh = true;

        // set the symbol as modified
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::OnAddNewDelivery(PSS_Property& prop, CString& value, PSS_Properties::IPropertySet& props, bool& refresh)
{
    // add a new delivery
    if (AddNewDelivery() >= 0)
    {
        refresh = true;

        // set the symbol as modified
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessSymbolBP::OnDelCurrentDelivery(PSS_Property&                 prop,
                                               CString&                      value,
                                               PSS_Properties::IPropertySet& props,
                                               bool&                         refresh)
{
    const int count = GetDeliveriesCount();

    // cannot delete all deliveries?
    if (count <= 1)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOTDELETE_ALLDELIVERIES, MB_OK);
        return;
    }

    // otherwise delete the current selected delivery
    const int index = prop.GetCategoryID() - ZS_BP_PROP_DELIVERIES;

    if (DeleteDelivery(index))
    {
        refresh = true;

        // set the symbol as modified
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
