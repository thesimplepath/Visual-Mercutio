/****************************************************************************
 * ==> PSS_ProcedureSymbolBP -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a procedure symbol for banking process            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "ZBBPProcedureSymbol.h"

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
#include "zProperty\ZBPropertyAttributes.h"
#include "zProperty\ZBPropertyObserverMsg.h"
#include "ZBDeliverableLinkSymbol.h"
#include "ZBBPRuleListProp.h"
#include "ZBBPTaskListProp.h"
#include "PSS_DecisionListPropertiesBP.h"
#include "PSS_CostPropertiesProcedureBP_Beta1.h"
#include "PSS_UnitPropertiesBP_Beta1.h"
#include "PSS_CombinationPropertiesBP.h"
#include "ZBBPSimPropProcedure.h"
#include "ZVAddRemoveCombinationDeliverableDlg.h"
#include "ZVChooseMasterDeliverable.h"
#include "PSS_ProcessGraphModelControllerBP.h"
#include "ZVRiskOptionsDlg.h"

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
const std::size_t _MaxRuleListSize        = 20;
const std::size_t _MaxTaskListSize        = 20;
const std::size_t _MaxDecisionListSize    = 20;
const std::size_t _MaxCombinationListSize = 20;
const std::size_t _MaxRulesSize           = 20;
const std::size_t _MaxRisksSize           = 20;
//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
static CMenu gCombinationMenu;
static CMenu gRulesMenu;
static CMenu gRiskMenu;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(ZBBPProcedureSymbol, PSS_Symbol, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ProcedureSymbolBP
//---------------------------------------------------------------------------
ZBBPProcedureSymbol::ZBBPProcedureSymbol(const CString Name /*= ""*/)
    : m_Combinations(this)
{
    m_ShowAttributeArea = true;

    PSS_Symbol::SetSymbolName(Name);

    CreateSymbolProperties();
}

ZBBPProcedureSymbol::~ZBBPProcedureSymbol()
{}

ZBBPProcedureSymbol::ZBBPProcedureSymbol(const ZBBPProcedureSymbol& src)
{
    *this = src;
}

ZBBPProcedureSymbol& ZBBPProcedureSymbol::operator=(const ZBBPProcedureSymbol& src)
{
    // Call the base class assignement operator
    PSS_Symbol::operator=((const PSS_Symbol&)src);

    m_Combinations = src.m_Combinations;

    // JMR-MODIF - Le 26 novembre 2006 - Ajout du code de copie pour les règles
    m_Rules = src.m_Rules;

    // JMR-MODIF - Le 29 juillet 2007 - Ajout du code de copie pour les risques
    m_Risks = src.m_Risks;

    return *this;
}

CODComponent* ZBBPProcedureSymbol::Dup() const
{
    return (new ZBBPProcedureSymbol(*this));
}

bool ZBBPProcedureSymbol::AcceptExtApp() const
{
    // RS-MODIF 17.11.04 ExtApp should appear in Conceptor
/*    CODModel * pModel = const_cast<ZBBPProcedureSymbol*>( this )->GetRootModel();

    if ( pModel && ISA( pModel, PSS_ProcessGraphModelMdl ) &&
         dynamic_cast<PSS_ProcessGraphModelMdl*>( pModel )->GetUseWorkflow() )
    {
        return true;
    }

    return false;
*/
    return true;
}

bool ZBBPProcedureSymbol::AcceptExtFile() const
{
    // RS-MODIF 17.11.04 ExtFile should appear in Conceptor
/*    CODModel * pModel = const_cast<ZBBPProcedureSymbol*>( this )->GetRootModel();

    if ( pModel && ISA( pModel, PSS_ProcessGraphModelMdl ) &&
         dynamic_cast<PSS_ProcessGraphModelMdl*>( pModel )->GetUseWorkflow() )
    {
        return true;
    }

    return false;
*/
    return true;
}

bool ZBBPProcedureSymbol::OnFillDefaultAttributes(ZBPropertyAttributes* pAttributes)
{
    if (!pAttributes)
    {
        return false;
    }

    // If global attributes have been defined, then copy them
    if (PSS_ModelGlobal::GetGlobalPropertyAttributes(GetObjectTypeID()).GetAttributeCount() > 0)
    {
        *pAttributes = PSS_ModelGlobal::GetGlobalPropertyAttributes(GetObjectTypeID());
    }
    else
    {
        // Add the reference number
        pAttributes->AddAttribute(ZS_BP_PROP_BASIC, M_Symbol_Number_ID);

        // Add the unit name
        pAttributes->AddAttribute(ZS_BP_PROP_UNIT, Z_UNIT_NAME);

        // No item labels
        pAttributes->SetDisplayTitleText(false);
    }

    return PSS_Symbol::OnFillDefaultAttributes(pAttributes);
}

bool ZBBPProcedureSymbol::OnChangeAttributes(ZBPropertyAttributes* pAttributes)
{
    return PSS_Symbol::OnChangeAttributes(pAttributes);
}

CString ZBBPProcedureSymbol::GetAttributeString(ZBPropertyAttributes* pAttributes) const
{
    return PSS_Symbol::GetAttributeString(pAttributes);
}

CString ZBBPProcedureSymbol::GetRuleList() const
{
    ZBBPRuleListProperties* pProps = (ZBBPRuleListProperties*)GetProperty(ZS_BP_PROP_RULELIST);

    if (!pProps)
    {
        return _T("");
    }

    return pProps->GetRuleList();
}

void ZBBPProcedureSymbol::SetRuleList(const CString Value)
{
    ZBBPRuleListProperties* pProps = (ZBBPRuleListProperties*)GetProperty(ZS_BP_PROP_RULELIST);

    if (pProps)
    {
        ZBBPRuleListProperties Props(*pProps);
        Props.SetRuleList(Value);
        SetProperty(&Props);
    }
}

bool ZBBPProcedureSymbol::RuleExist(const CString Value)
{
    PSS_Tokenizer token(GetRuleList());    // Initialize the token with the task list
                                        // and with the default ; as separator

    return (token.TokenExist(Value) == TRUE) ? true : false;
}

void ZBBPProcedureSymbol::AddRule(const CString Value)
{
    PSS_Tokenizer token(GetRuleList());    // Initialize the token with the task list
                                        // and with the default ; as separator

    // If the new task has been added correctly,
    // then set the new task list
    if (token.AddUniqueToken(Value))
    {
        // Add the value to the history
        CString Key;
        Key.LoadString(IDS_ZS_BP_PROP_RULELST_TITLE);
        PSS_Global::GetHistoricValueManager().AddHistoryValue(Key, Value);

        // Set the new task string 
        SetRuleList(token.GetString());
    }
}

void ZBBPProcedureSymbol::RemoveRule(const CString Value)
{
    PSS_Tokenizer token(GetRuleList());    // Initialize the token with the task list
                                        // and with the default ; as separator

    // If the new task has been removed correctly,
    // then set the new task list
    if (token.RemoveToken(Value))
    {
        SetRuleList(token.GetString());
    }
}

CString ZBBPProcedureSymbol::GetRuleAt(size_t Index)
{
    PSS_Tokenizer token(GetRuleList());    // Initialize the token with the task list
                                        // and with the default ; as separator
    CString Value;

    // Retrieve the specific indexed token
    if (token.GetTokenAt(Index, Value))
    {
        return Value;
    }

    return _T("");
}

size_t ZBBPProcedureSymbol::GetRuleCount() const
{
    PSS_Tokenizer token(GetRuleList());    // Initialize the token with the task list
                                        // and with the default ; as separator

    return token.GetTokenCount();
}

CString ZBBPProcedureSymbol::GetTaskList() const
{
    ZBBPTaskListProperties* pProps = (ZBBPTaskListProperties*)GetProperty(ZS_BP_PROP_TASKLIST);

    if (!pProps)
    {
        return _T("");
    }

    return pProps->GetTaskList();
}

void ZBBPProcedureSymbol::SetTaskList(const CString Value)
{
    ZBBPTaskListProperties* pProps = (ZBBPTaskListProperties*)GetProperty(ZS_BP_PROP_TASKLIST);

    if (pProps)
    {
        ZBBPTaskListProperties Props(*pProps);
        Props.SetTaskList(Value);
        SetProperty(&Props);
    }
}

bool ZBBPProcedureSymbol::TaskExist(const CString Value)
{
    PSS_Tokenizer token(GetTaskList());    // Initialize the token with the task list
                                        // and with the default ; as separator

    return (token.TokenExist(Value) == TRUE) ? true : false;
}

void ZBBPProcedureSymbol::AddTask(const CString Value)
{
    PSS_Tokenizer token(GetTaskList());    // Initialize the token with the task list
                                        // and with the default ; as separator

    // If the new task has been added correctly,
    // then set the new task list
    if (token.AddUniqueToken(Value))
    {
        // Add the value to the history
        CString Key;
        Key.LoadString(IDS_ZS_BP_PROP_PROCEDURE_TSKLST_TITLE);
        PSS_Global::GetHistoricValueManager().AddHistoryValue(Key, Value);

        // Set the new task string 
        SetTaskList(token.GetString());
    }
}

void ZBBPProcedureSymbol::RemoveTask(const CString Value)
{
    PSS_Tokenizer token(GetTaskList());    // Initialize the token with the task list
                                        // and with the default ; as separator

    // If the new task has been removed correctly,
    // then set the new task list
    if (token.RemoveToken(Value))
    {
        SetTaskList(token.GetString());
    }
}

CString ZBBPProcedureSymbol::GetTaskAt(size_t Index)
{
    PSS_Tokenizer token(GetTaskList());    // Initialize the token with the task list
                                        // and with the default ; as separator

    CString Value;

    // Retrieve the specific indexed token
    if (token.GetTokenAt(Index, Value))
    {
        return Value;
    }

    return _T("");
}

size_t ZBBPProcedureSymbol::GetTaskCount() const
{
    PSS_Tokenizer token(GetTaskList());    // Initialize the token with the task list
                                        // and with the default ; as separator

    return token.GetTokenCount();
}

CString ZBBPProcedureSymbol::GetDecisionList() const
{
    PSS_DecisionListPropertiesBP* pProps = (PSS_DecisionListPropertiesBP*)GetProperty(ZS_BP_PROP_DECISIONLIST);

    if (!pProps)
    {
        return _T("");
    }

    return pProps->GetDecisionList();
}

void ZBBPProcedureSymbol::SetDecisionList(const CString Value)
{
    PSS_DecisionListPropertiesBP* pProps = (PSS_DecisionListPropertiesBP*)GetProperty(ZS_BP_PROP_DECISIONLIST);

    if (pProps)
    {
        PSS_DecisionListPropertiesBP props(*pProps);
        props.SetDecisionList(Value);
        SetProperty(&props);
    }
}

bool ZBBPProcedureSymbol::DecisionExist(const CString Value)
{
    PSS_Tokenizer token(GetDecisionList());    // Initialize the token with the decision list
                                            // and with the default ; as separator

    return (token.TokenExist(Value) == TRUE) ? true : false;
}

void ZBBPProcedureSymbol::AddDecision(const CString Value)
{
    PSS_Tokenizer token(GetDecisionList());    // Initialize the token with the decision list
                                            // and with the default ; as separator

    // If the new decision has been added correctly,
    // then set the new decision list
    if (token.AddUniqueToken(Value))
    {
        // Add the value to the history
        CString Key;
        Key.LoadString(IDS_ZS_BP_PROP_PROCEDURE_DECLST_TITLE);
        PSS_Global::GetHistoricValueManager().AddHistoryValue(Key, Value);

        // Set the new decision string 
        SetDecisionList(token.GetString());
    }
}

void ZBBPProcedureSymbol::RemoveDecision(const CString Value)
{
    PSS_Tokenizer token(GetDecisionList());    // Initialize the token with the decision list
                                            // and with the default ; as separator

    // If the new decision has been removed correctly,
    // then set the new decision list
    if (token.RemoveToken(Value))
    {
        SetDecisionList(token.GetString());
    }
}

CString ZBBPProcedureSymbol::GetDecisionAt(size_t Index)
{
    PSS_Tokenizer token(GetDecisionList());    // Initialize the token with the decision list
                                            // and with the default ; as separator

    CString Value;

    // Retrieve the specific indexed token
    if (token.GetTokenAt(Index, Value))
    {
        return Value;
    }

    return _T("");
}

size_t ZBBPProcedureSymbol::GetDecisionCount() const
{
    PSS_Tokenizer token(GetDecisionList());    // Initialize the token with the decision list
                                            // and with the default ; as separator

    return token.GetTokenCount();
}

// JMR-MODIF - Le 25 décembre 2006 - Permet de rechercher le nom original d'une règle en fonction de son GUID.
CString ZBBPProcedureSymbol::GetRuleNameByGUID(PSS_LogicalRulesEntity* p_Rule, CString RuleGUID)
{
    if (p_Rule == NULL)
    {
        return _T("");
    }

    if (p_Rule->GetGUID() == RuleGUID)
    {
        return p_Rule->GetEntityName();
    }

    if (p_Rule->ContainEntity())
    {
        int Count = p_Rule->GetEntityCount();

        for (int i = 0; i < Count; ++i)
        {
            PSS_RulesEntity* pEntity = p_Rule->GetEntityAt(i);

            if (!pEntity)
            {
                continue;
            }

            if (ISA(pEntity, PSS_LogicalRulesEntity))
            {
                CString m_Name = GetRuleNameByGUID(dynamic_cast<PSS_LogicalRulesEntity*>(pEntity), RuleGUID);

                if (!m_Name.IsEmpty())
                {
                    return m_Name;
                }
            }
        }
    }

    return _T("");
}

void ZBBPProcedureSymbol::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    // Call the base class method
    PSS_Symbol::OnUpdate(pSubject, pMsg);
}

void ZBBPProcedureSymbol::OnConnect(CODConnection* pConnection)
{
    PSS_Symbol::OnConnect(pConnection);

    CheckInitialCombination();
}

void ZBBPProcedureSymbol::OnDisconnect(CODConnection* pConnection)
{
    PSS_Symbol::OnDisconnect(pConnection);

    CheckInitialCombination();
}

void ZBBPProcedureSymbol::OnLinkDisconnect(CODLinkComponent* pLink)
{
    if (pLink && ISA(pLink, PSS_LinkSymbol))
    {
        DeleteDeliverableFromAllCombinations(dynamic_cast<PSS_LinkSymbol*>(pLink)->GetSymbolName());
    }
}

BOOL ZBBPProcedureSymbol::OnConnectionMove(CODConnection* pConnection)
{
    return PSS_Symbol::OnConnectionMove(pConnection);
}

void ZBBPProcedureSymbol::CheckInitialCombination()
{
    // Now check if only one combination.
    // If it is the case, then set all deliverables to the combination
    if (GetCombinationCount() == 1)
    {
        // Get all deliverables
        CString EnteringDeliverables;
        GetEnteringUpDeliverable(EnteringDeliverables);

        // And set it
        SetCombinationDeliverables(0, EnteringDeliverables);

        // If no entering deliverables, then remove the master
        if (EnteringDeliverables.IsEmpty())
        {
            SetCombinationMaster(0, EnteringDeliverables);
        }
        else
        {
            // If there is only one deliverable
            // then sets automatically the master
            PSS_Tokenizer token(EnteringDeliverables);

            if (token.GetTokenCount() == 1)
            {
                CString Value;

                // Retrieve the specific indexed token
                if (token.GetTokenAt(0, Value))
                {
                    SetCombinationMaster(0, Value);
                }
            }
        }

        SetCombinationActivationPerc(0, GetMaxActivationPerc(GetCombinationMaster(0)));
    }
}

void ZBBPProcedureSymbol::OnSymbolNameChanged(CODComponent& Comp, const CString OldName)
{
    // Check if the old symbol name was used somewhere in this procedure

    CODComponent* pComp = &Comp;

    // Check the deliverable for combinations
    if (ISA(pComp, PSS_LinkSymbol))
    {
        ReplaceDeliverable(OldName, dynamic_cast<PSS_LinkSymbol*>(pComp)->GetSymbolName());
    }
}

// JMR-MODIF - Le 10 juin 2007 - Ajout de la fonction OnAddNewRisk.
void ZBBPProcedureSymbol::OnAddNewRisk(ZBProperty&        Property,
                                       CString&        value,
                                       ZBPropertySet&    Properties,
                                       bool&            Refresh)
{
    // Add a new risk
    if (AddNewRisk() >= 0)
    {
        // Sets the refresh flag to true
        Refresh = true;
        SetModifiedFlag(TRUE);
    }
}

// JMR-MODIF - Le 10 juin 2007 - Ajout de la fonction OnDelCurrentRisk.
void ZBBPProcedureSymbol::OnDelCurrentRisk(ZBProperty&        Property,
                                           CString&        value,
                                           ZBPropertySet&    Properties,
                                           bool&            Refresh)
{
    int Count = GetRiskCount();

    if (Count <= 1)
    {
        // Cannot delete all risks
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOTDELETE_ALLRISKS, MB_OK);
        return;
    }

    // Otherwise, delete the current selected risk
    int Index = Property.GetCategoryID() - ZS_BP_PROP_RISK;

    if (DeleteRisk(Index))
    {
        // Sets the refresh flag to true
        Refresh = true;
        SetModifiedFlag(TRUE);
    }
}

void ZBBPProcedureSymbol::OnAddNewCombination(ZBProperty&        Property,
                                              CString&            value,
                                              ZBPropertySet&    Properties,
                                              bool&            Refresh)
{
    // Add a new combination
    if (AddNewCombination() >= 0)
    {
        // Sets the refresh flag to true
        Refresh = true;
        SetModifiedFlag(TRUE);
    }
}

void ZBBPProcedureSymbol::OnDelCurrentCombination(ZBProperty&        Property,
                                                  CString&            value,
                                                  ZBPropertySet&    Properties,
                                                  bool&            Refresh)
{
    int Count = GetCombinationCount();

    if (Count <= 1)
    {
        // Cannot delete all combinations
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOTDELETE_ALLCOMBINATIONS, MB_OK);
        return;
    }

    // Otherwise, delete the current selected combination
    int Index = Property.GetCategoryID() - ZS_BP_PROP_COMBINATION;

    if (DeleteCombination(Index))
    {
        // Sets the refresh flag to true
        Refresh = true;
        SetModifiedFlag(TRUE);
    }
}

void ZBBPProcedureSymbol::OnAddDeliverableCombination(ZBProperty&        Property,
                                                      CString&            value,
                                                      ZBPropertySet&    Properties,
                                                      bool&            Refresh)
{}

void ZBBPProcedureSymbol::OnDelDeliverableCombination(ZBProperty&        Property,
                                                      CString&            value,
                                                      ZBPropertySet&    Properties,
                                                      bool&            Refresh)
{}

bool ZBBPProcedureSymbol::CreateSymbolProperties()
{
    if (!PSS_Symbol::CreateSymbolProperties())
    {
        return false;
    }

    ZBBPRuleListProperties propRules;
    AddProperty(propRules);

    ZBBPTaskListProperties propTasks;
    AddProperty(propTasks);

    PSS_DecisionListPropertiesBP propDecisions;
    AddProperty(propDecisions);

    PSS_CostPropertiesProcedureBP_Beta1 propCost;
    AddProperty(propCost);

    PSS_UnitPropertiesBP_Beta1 propUnit;
    AddProperty(propUnit);

    // Creates at least one combination property
    m_Combinations.CreateInitialProperties();

    // Fill the array of unit double validation type
    m_UnitDoubleValidationTypeArray.RemoveAll();
    GetUnitDoubleValidationTypeStringArray(m_UnitDoubleValidationTypeArray);

    // JMR-MODIF - Le 3 juin 2007 - Ajoute au moins un catalogue de propriétés dans les risques.
    m_Risks.CreateInitialProperties();

    return true;
}

// JMR-MODIF - Le 26 avril 2007 - Cette fonction permet de déterminer si une règle donnée a été attribuée à cet objet.
BOOL ZBBPProcedureSymbol::ContainsRule(CString RuleName)
{
    for (int i = 0; i < m_Rules.GetRulesCount(); i++)
    {
        if (m_Rules.GetRuleName(i) == RuleName)
        {
            return TRUE;
        }
    }

    return FALSE;
}

// JMR-MODIF - Le 9 octobre 2007 - Cette fonction retourne les règles qui ne sont plus synchronisées avec le référentiel.
void ZBBPProcedureSymbol::CheckRulesSync(CStringArray& RulesList)
{
    CODModel * pModel = GetRootModel();

    if (pModel == NULL)
    {
        return;
    }

    if (m_Rules.GetRulesCount() > 0)
    {
        PSS_LogicalRulesEntity* p_MainRule = NULL;

        if (GetOwnerModel() != NULL && ISA(GetOwnerModel(), PSS_ProcessGraphModelMdlBP))
        {
            PSS_ProcessGraphModelMdlBP* p_Model = reinterpret_cast<PSS_ProcessGraphModelMdlBP*>(GetOwnerModel());

            p_MainRule = p_Model->GetMainLogicalRules();
        }
        else
        {
            return;
        }

        for (int i = 0; i < m_Rules.GetRulesCount(); i++)
        {
            CString m_SafeName = GetRuleNameByGUID(p_MainRule, m_Rules.GetRuleGUID(i));

            if (m_SafeName.IsEmpty())
            {
                RulesList.Add(m_Rules.GetRuleName(i));
            }
        }
    }
}
//---------------------------------------------------------------------------
bool ZBBPProcedureSymbol::FillProperties(ZBPropertySet& propSet, bool numericValue, bool groupValue)
{
    CODModel * pModel = GetRootModel();

    // if no file, add new one
    if (!GetExtFileCount())
        AddNewExtFile();

    // if no application, add new one
    if (!GetExtAppCount())
        AddNewExtApp();

    // FIXME translate comment!
    // les propriétés "Nom", "Description" et "Référence" du groupe "General" sont affichées par la classe de base.
    // C'est aussi ici que les propriétés pour les liens et fichiers externes sont ajoutées.
    if (!PSS_Symbol::FillProperties(propSet, numericValue, groupValue))
        return false;

    // only local symbol have access to properties
    if (!IsLocal())
        return true;

    // initialize the Currency symbol with the user local currency symbol defined in the Control Panel
    CString currencySymbol = PSS_Global::GetLocaleCurrency();

    // FIXME translate comment
    // JMR-MODIF - Le 30 juillet 2007 - Mets à jour le symbole monétaire en fonction de la sélection utilisateur.
    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl))
    {
        CDocument* pDoc = dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetDocument();

        if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc))
            // retreive the model's currency symbol
            currencySymbol = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetCurrencySymbol();
    }

    int     count;
    CString finalPropName;
    CString propTitle;
    CString propName;
    CString propDesc;
    bool    groupEnabled = true;

    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
        !dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->MainUserGroupIsValid())
        groupEnabled = false;

    // FIXME translate comments
    // ************************************************************************************************************
    // JMR-MODIF - Le 22 novembre 2006 - Nouvelle architecture des règles.

    // if the menu is not loaded, load it
    if (!gRulesMenu.GetSafeHmenu())
        gRulesMenu.LoadMenu(IDR_RULES_MENU);

    if (m_Rules.GetRulesCount() > 0)
    {
        CString ruleSectionTitle = _T("");
        CString ruleName = _T("");
        CString ruleDesc = _T("");

        ruleSectionTitle.LoadString(IDS_Z_RULES_TITLE);
        ruleDesc.LoadString(IDS_Z_RULES_DESC);

        PSS_LogicalRulesEntity* pMainRule = NULL;

        if (GetOwnerModel() && ISA(GetOwnerModel(), PSS_ProcessGraphModelMdlBP))
        {
            PSS_ProcessGraphModelMdlBP* pOwnerModel = reinterpret_cast<PSS_ProcessGraphModelMdlBP*>(GetOwnerModel());

            if (pOwnerModel && pOwnerModel->GetController() && ISA(pOwnerModel->GetController(), PSS_ProcessGraphModelControllerBP))
            {
                PSS_ProcessGraphModelControllerBP* pController =
                    reinterpret_cast<PSS_ProcessGraphModelControllerBP*>(pOwnerModel->GetController());

                if (pController && ISA(pController->GetDocument(), PSS_ProcessGraphModelDoc))
                {
                    PSS_ProcessGraphModelDoc* pDocument =
                        reinterpret_cast<PSS_ProcessGraphModelDoc*>(pController->GetDocument());

                    if (pDocument && pDocument->GetMainLogicalRules())
                        pMainRule = pDocument->GetMainLogicalRules();
                }
            }
        }

        for (int i = 0; i < m_Rules.GetRulesCount(); ++i)
        {
            // FIXME translate comments
            // Le contrôle des règles ne peut être appliqué que si le modèle est en phase avec le système des règles.
            if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
                dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->MainLogicalRulesIsValid())
            {
                CString safeName = GetRuleNameByGUID(pMainRule, m_Rules.GetRuleGUID(i));

                // ********************************************************************************************
                // JMR-MODIF - Le 8 octobre 2007 - Rééctriture de la routine suite à un bug de perte de règles.
                // Avant, le test supprimait une règle qui n'était plus synchronisée au référentiel, maintenant
                // seul le nom de la règle est contrôlé et renommé, à condition qu'il soit synchronisé avec le
                // référentiel.
                /*
                if ( m_SafeName.IsEmpty() )
                {
                    m_Rules.DeleteRule( i );
                }
                else if ( m_SafeName != m_Rules.GetRuleName( i ) )
                {
                    m_Rules.SetRuleName( i, m_SafeName );
                }
                */

                if (!safeName.IsEmpty() && safeName != m_Rules.GetRuleName(i))
                    m_Rules.SetRuleName(i, safeName);
                // ********************************************************************************************
            }

            ruleName.Format(IDS_Z_RULES_NAME, i + 1);

            // FIXME translate comments
            // Propriété "Règle x" du groupe "Règles"
            ZBProperty* pRule = new ZBProperty(ruleSectionTitle,
                                               ZS_BP_PROP_RULES,
                                               ruleName,
                                               Z_RULE_NAME + (i * _MaxRulesSize),
                                               ruleDesc,
                                               m_Rules.GetRuleName(i),
                                               ZBProperty::PT_EDIT_MENU,
                                               true,
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                               NULL,
                                               &gRulesMenu);

            pRule->EnableDragNDrop();
            propSet.Add(pRule);
        }
    }
    // ************************************************************************************************************

    // FIXME translate comments
    // ************************************************************************************************************
    // JMR-MODIF - Le 22 novembre 2006 - ATTENTION : L'ancienne architecture de règles ci-dessous a maintenant
    // changé, et est désignée sous le terme de contrôle, car celle-ci était devenue obsolète après la nouvelle
    // implémentation du système de règles datant de novembre 2006. Mais les deux architectures étant trop
    // différentes l'une de l'autre, il a fallu faire cohabiter les deux pour des raisons de compatibilité avec les
    // anciens fichiers. Cependant, les textes concernant l'ancienne architecture ont été corrigés, et les termes
    // "règles" ont été remplacés par les termes "Contrôles" dans les ressources de textes. Toutefois, les autres
    // corrections étaient trop importantes pour être appliquées au code, ce qui provoque une ambiguité dans le nom
    // des classes et des ressources. Si une nouvelle modification doit être approtée à l'architecture des contrôles
    // il faut donc le faire avec la plus grande prudence.

    // add rules
    ZBBPRuleListProperties* pRulesProps;

    if ((pRulesProps = (ZBBPRuleListProperties*)GetProperty(ZS_BP_PROP_RULELIST)) == NULL)
    {
        // try to add it
        ZBBPRuleListProperties propRules;
        AddProperty(propRules);

        // retreive it
        pRulesProps = (ZBBPRuleListProperties*)GetProperty(ZS_BP_PROP_RULELIST);

        if (!pRulesProps)
            return false;
    }

    // run through all tasks properties, add one to the counter to have always one empty task
    count = GetRuleCount() + 1;
    propTitle.LoadString(IDS_ZS_BP_PROP_RULELST_TITLE);
    CStringArray* pArrayOfValues = PSS_Global::GetHistoricValueManager().GetFieldHistory(propTitle);

    propName.LoadString(IDS_Z_RULE_LIST_NAME);
    propDesc.LoadString(IDS_Z_RULE_LIST_DESC);

    int index = 0;

    for (int i = 0; i < count; ++i)
    {
        index = i;

        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // FIXME translate comments
        // Propriété "Contrôle x" du groupe "Contrôles"
        ZBProperty* pRuleList = new ZBProperty(propTitle,
                                               ZS_BP_PROP_RULELIST,
                                               finalPropName,
                                               Z_RULE_LIST + (i * _MaxRuleListSize),
                                               propDesc,
                                               GetRuleAt(i),
                                               ZBProperty::PT_EDIT_INTELI,
                                               true, // Enable
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                               pArrayOfValues);

        pRuleList->EnableDragNDrop();
        propSet.Add(pRuleList);
    }

    // now continue to add empty tasks till the maximum size
    for (int i = index; i < _MaxRuleListSize; ++i)
    {
        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // Propriété "Contrôle x" du groupe "Contrôles", mais celles-ci sont vides et ne sont pas affichées.
        ZBProperty* pRuleList = new ZBProperty(propTitle,
                                               ZS_BP_PROP_RULELIST,
                                               finalPropName,
                                               Z_RULE_LIST + (i * _MaxRuleListSize),
                                               propDesc,
                                               _T(""),
                                               ZBProperty::PT_EDIT_INTELI,
                                               false, // Disable
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                               pArrayOfValues);

        pRuleList->EnableDragNDrop();
        propSet.Add(pRuleList);
    }
    // ************************************************************************************************************

    // ***********************************************************************************************************
    // JMR-MODIF - Le 3 juin 2007 - Ajout des propriétés liées aux risques.

    // FIXME translate comments
    // Obtient le menu des risques si celui-ci n'est pas encore présent.
    if (!gRiskMenu.GetSafeHmenu())
        gRiskMenu.LoadMenu(IDR_RISK_MENU);

    CString finalRiskName = _T("");
    CString finalRiskTitle = _T("");
    CString riskTitle = _T("");
    CString riskName = _T("");
    CString riskDesc = _T("");

    riskTitle.LoadString(IDS_ZS_BP_PROP_RISK_TITLE);

    for (int i = 0; i < GetRiskCount(); ++i)
    {
        finalRiskTitle.Format(_T("%s (%d)"), riskTitle, i + 1);

        riskName.LoadString(IDS_Z_RISK_NAME_NAME);
        riskDesc.LoadString(IDS_Z_RISK_NAME_DESC);

        // FIXME translate comments
        // Propriété "Titre Risque" du groupe "Risque (x)"
        ZBProperty* pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                                           riskName,
                                           (groupValue ? M_Risk_Name_ID : (M_Risk_Name_ID + (i * _MaxRisksSize))),
                                           riskDesc,
                                           GetRiskName(i),
                                           ZBProperty::PT_EDIT_MENU,
                                           true,
                                           PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                           NULL,
                                           &gRiskMenu);

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_DESC_NAME);
        riskDesc.LoadString(IDS_Z_RISK_DESC_DESC);

        // FIXME translate comments
        // Propriété "Description" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? M_Risk_Desc_ID : (M_Risk_Desc_ID + (i * _MaxRisksSize))),
                               riskDesc,
                               GetRiskDesc(i),
                               ZBProperty::PT_EDIT_EXTENDED);

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_TYPE_NAME);
        riskDesc.LoadString(IDS_Z_RISK_TYPE_DESC);

        CString sNoRiskType = _T("");
        sNoRiskType.LoadString(IDS_NO_RISK_TYPE);

        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? M_Risk_Type_ID : (M_Risk_Type_ID + (i * _MaxRisksSize))),
                               riskDesc,
                               GetRiskType(i).IsEmpty() ? sNoRiskType : GetRiskType(i),
                               ZBProperty::PT_EDIT_EXTENDED_READONLY);

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_IMPACT_NAME);
        riskDesc.LoadString(IDS_Z_RISK_IMPACT_DESC);

        // FIXME translate comments
        // Propriété "Impact" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? M_Risk_Impact_ID : (M_Risk_Impact_ID + (i * _MaxRisksSize))),
                               riskDesc,
                               PSS_Application::Instance()->GetMainForm()->GetRiskImpactContainer()->GetElementAt(GetRiskImpact(i)),
                               ZBProperty::PT_EDIT_EXTENDED_READONLY);

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_PROBABILITY_NAME);
        riskDesc.LoadString(IDS_Z_RISK_PROBABILITY_DESC);

        // FIXME translate comments
        // Propriété "Probabilité" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? M_Risk_Probability_ID : (M_Risk_Probability_ID + (i * _MaxRisksSize))),
                               riskDesc,
                               PSS_Application::Instance()->GetMainForm()->GetRiskProbabilityContainer()->GetElementAt(GetRiskProbability(i)),
                               ZBProperty::PT_EDIT_EXTENDED_READONLY);

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_SEVERITY_NAME);
        riskDesc.LoadString(IDS_Z_RISK_SEVERITY_DESC);

        // FIXME translate comments
        // Propriété "Sévérité" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? M_Risk_Severity_ID : (M_Risk_Severity_ID + (i * _MaxRisksSize))),
                               riskDesc,
                               double(GetRiskSeverity(i)),
                               ZBProperty::PT_EDIT_NUMBER_READONLY);

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_UE_NAME);
        riskDesc.LoadString(IDS_Z_RISK_UE_DESC);

        // FIXME translate comments
        // Propriété "Est. unit." du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? M_Risk_UE_ID : (M_Risk_UE_ID + (i * _MaxRisksSize))),
                               riskDesc,
                               GetRiskUE(i),
                               ZBProperty::PT_EDIT_NUMBER,
                               true,
                               PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol));

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_POA_NAME);
        riskDesc.LoadString(IDS_Z_RISK_POA_DESC);

        // FIXME translate comments
        // Propriété "POA" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? M_Risk_POA_ID : (M_Risk_POA_ID + (i * _MaxRisksSize))),
                               riskDesc,
                               GetRiskPOA(i),
                               ZBProperty::PT_EDIT_NUMBER,
                               true,
                               PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol));

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_ACTION_NAME);
        riskDesc.LoadString(IDS_Z_RISK_ACTION_DESC);

        // FIXME translate comments
        // Propriété "Action" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
            (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? M_Risk_Action_ID : (M_Risk_Action_ID + (i * _MaxRisksSize))),
                               riskDesc,
                               (GetRiskAction(i) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo()),
                               ZBProperty::PT_COMBO_STRING_READONLY,
                               TRUE,
                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                               PSS_Global::GetArrayYesNo());

        propSet.Add(pRisk);
    }
    // ***********************************************************************************************************

    // add tasks
    ZBBPTaskListProperties* pTasksProps = (ZBBPTaskListProperties*)GetProperty(ZS_BP_PROP_TASKLIST);

    if (!pTasksProps)
        return false;

    // run through all tasks properties, add one to the counter to have always one empty task
    count = GetTaskCount() + 1;
    propTitle.LoadString(IDS_ZS_BP_PROP_PROCEDURE_TSKLST_TITLE);
    pArrayOfValues = PSS_Global::GetHistoricValueManager().GetFieldHistory(propTitle);

    propName.LoadString(IDS_Z_TASK_LIST_NAME);
    propDesc.LoadString(IDS_Z_TASK_LIST_DESC);

    index = 0;

    for (int i = 0; i < count; ++i)
    {
        index = i;

        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // FIXME translate comments
        // Propriété "Tâche x" du groupe "Tâches"
        ZBProperty* pTaskList = new ZBProperty(propTitle,
                                               ZS_BP_PROP_TASKLIST,
                                               finalPropName,
                                               Z_TASK_LIST + (i * _MaxTaskListSize),
                                               propDesc,
                                               GetTaskAt(i),
                                               ZBProperty::PT_EDIT_INTELI,
                                               true, // Enable
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                               pArrayOfValues);

        pTaskList->EnableDragNDrop();
        propSet.Add(pTaskList);
    }

    // now continue to add empty tasks till the maximum size
    for (int i = index; i < _MaxTaskListSize; ++i)
    {
        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // FIXME translate comments
        // Propriété "Tâche x" du groupe "Tâches"
        ZBProperty* pTaskList = new ZBProperty(propTitle,
                                               ZS_BP_PROP_TASKLIST,
                                               finalPropName,
                                               Z_TASK_LIST + (i * _MaxTaskListSize),
                                               propDesc,
                                               _T(""),
                                               ZBProperty::PT_EDIT_INTELI,
                                               false, // Disable
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                               pArrayOfValues);

        pTaskList->EnableDragNDrop();
        propSet.Add(pTaskList);
    }

    // add decisions
    PSS_DecisionListPropertiesBP* pDecisionsProps = (PSS_DecisionListPropertiesBP*)GetProperty(ZS_BP_PROP_DECISIONLIST);

    if (!pDecisionsProps)
        return false;

    // run through all tasks properties, add one to the counter to have always one empty decision
    count = GetDecisionCount() + 1;
    propTitle.LoadString(IDS_ZS_BP_PROP_PROCEDURE_DECLST_TITLE);
    pArrayOfValues = PSS_Global::GetHistoricValueManager().GetFieldHistory(propTitle);

    propName.LoadString(IDS_Z_DECISION_LIST_NAME);
    propDesc.LoadString(IDS_Z_DECISION_LIST_DESC);

    index = 0;

    for (int i = 0; i < count; ++i)
    {
        index = i;

        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // FIXME translate comments
        // Propriété "Décision x" du groupe "Décisions"
        ZBProperty* pDecList = new ZBProperty(propTitle,
                                              ZS_BP_PROP_DECISIONLIST,
                                              finalPropName,
                                              M_Decision_List_ID + (i * _MaxDecisionListSize),
                                              propDesc,
                                              GetDecisionAt(i),
                                              ZBProperty::PT_EDIT_INTELI,
                                              true, // Enable
                                              PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                              pArrayOfValues);

        pDecList->EnableDragNDrop();
        propSet.Add(pDecList);
    }

    // now continue to add empty decisions till the maximum size
    for (int i = index; i < _MaxDecisionListSize; ++i)
    {
        finalPropName.Format(_T("%s %d"), propName, i + 1);

        // Propriété "Décision x" du groupe "Décisions"
        ZBProperty* pDecList = new ZBProperty(propTitle,
                                              ZS_BP_PROP_DECISIONLIST,
                                              finalPropName,
                                              M_Decision_List_ID + (i * _MaxDecisionListSize),
                                              propDesc,
                                              _T(""),
                                              ZBProperty::PT_EDIT_INTELI,
                                              false, // Disable
                                              PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                              pArrayOfValues);

        pDecList->EnableDragNDrop();
        propSet.Add(pDecList);
    }

    int hourPerDay = -1;
    int dayPerWeek = -1;
    int dayPerMonth = -1;
    int dayPerYear = -1;

    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl))
    {
        CDocument* pDoc = dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetDocument();

        if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc))
        {
            // FIXME translate comments
            // JMR-MODIF - Le 30 juillet 2007 - Cette opération est effectuée une fois pour toutes au début de la fonction.
            // Retrieve the model's currency symbol
            //CurrencySymbol = dynamic_cast<PSS_ProcessGraphModelDoc*>( pDoc )->GetCurrencySymbol();

            // retreive the standard time definition
            hourPerDay = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetHourPerDay();
            dayPerWeek = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetDayPerWeek();
            dayPerMonth = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetDayPerMonth();
            dayPerYear = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetDayPerYear();
        }
    }

    // RS-MODIF 17.11.04 error has to be defined here
    bool error;

    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
        dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())
    {
        // FIXME translate comments
        // Propriété "Multiplicateur" du groupe "Procédure"
        ZBProperty* pMultiplier = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                                 ZS_BP_PROP_PROCEDURE_COST,
                                                 IDS_Z_COST_MULTIPLIER_NAME,
                                                 M_Cost_Proc_Multiplier_ID,
                                                 IDS_Z_COST_MULTIPLIER_DESC,
                                                 GetMultiplier(),
                                                 ZBProperty::PT_EDIT_NUMBER,
                                                 true,
                                                 PSS_StringFormat(PSS_StringFormat::IE_FT_Accounting, true, -1));

        propSet.Add(pMultiplier);

        ZBProperty* pTime;

        if (numericValue)
            // FIXME translate comments
            // Propriété "Temps standard" du groupe "Procédure"
            pTime = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                   ZS_BP_PROP_PROCEDURE_COST,
                                   IDS_Z_COST_PROCESSING_TIME_NAME,
                                   M_Cost_Proc_Processing_Time_ID,
                                   IDS_Z_COST_PROCESSING_TIME_DESC,
                                   GetProcessingTime(),
                                   ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "Temps standard" du groupe "Procédure"
            pTime = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                   ZS_BP_PROP_PROCEDURE_COST,
                                   IDS_Z_COST_PROCESSING_TIME_NAME,
                                   M_Cost_Proc_Processing_Time_ID,
                                   IDS_Z_COST_PROCESSING_TIME_DESC,
                                   PSS_Duration(GetProcessingTime(),
                                                hourPerDay,
                                                dayPerWeek,
                                                dayPerMonth,
                                                dayPerYear),
                                   ZBProperty::PT_EDIT_DURATION,
                                   true,
                                   PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));

        propSet.Add(pTime);

        // FIXME translate comments
        // Propriété "Coût unitaire" du groupe "Procédure"
        ZBProperty* pPrice = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                            ZS_BP_PROP_PROCEDURE_COST,
                                            IDS_Z_COST_UNITARY_COST_NAME,
                                            M_Cost_Proc_Unitary_Cost_ID,
                                            IDS_Z_COST_UNITARY_COST_DESC,
                                            GetUnitaryCost(),
                                            ZBProperty::PT_EDIT_NUMBER,
                                            true,
                                            PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol));

        propSet.Add(pPrice);

        ZBProperty* pProcessingDuration;

        if (numericValue)
            // FIXME translate comments
            // Propriété "Durée moyenne (pondérée)" du groupe "Procédure"
            pProcessingDuration = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                                 ZS_BP_PROP_PROCEDURE_COST,
                                                 IDS_Z_COST_PROCESSING_DURATION_NAME,
                                                 M_Cost_Proc_Processing_Duration_ID,
                                                 IDS_Z_COST_PROCESSING_DURATION_DESC,
                                                 GetProcessingDuration(),
                                                 ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "Durée moyenne (pondérée)" du groupe "Procédure"
            pProcessingDuration = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                                 ZS_BP_PROP_PROCEDURE_COST,
                                                 IDS_Z_COST_PROCESSING_DURATION_NAME,
                                                 M_Cost_Proc_Processing_Duration_ID,
                                                 IDS_Z_COST_PROCESSING_DURATION_DESC,
                                                 PSS_Duration(GetProcessingDuration(),
                                                              hourPerDay,
                                                              dayPerWeek,
                                                              dayPerMonth,
                                                              dayPerYear),
                                                 ZBProperty::PT_EDIT_DURATION_READONLY,
                                                 true,
                                                 PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));

        propSet.Add(pProcessingDuration);

        ZBProperty* pProcessingDurationMax;

        if (numericValue)
            // FIXME translate comments
            // Propriété "Durée moyenne (maximum)" du groupe "Procédure"
            pProcessingDurationMax = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                                    ZS_BP_PROP_PROCEDURE_COST,
                                                    IDS_Z_COST_PROCESSING_DURATIONMAX_NAME,
                                                    M_Cost_Proc_Processing_Duration_Max_ID,
                                                    IDS_Z_COST_PROCESSING_DURATIONMAX_DESC,
                                                    GetProcessingDurationMax(),
                                                    ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "Durée moyenne (maximum)" du groupe "Procédure"
            pProcessingDurationMax = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                                    ZS_BP_PROP_PROCEDURE_COST,
                                                    IDS_Z_COST_PROCESSING_DURATIONMAX_NAME,
                                                    M_Cost_Proc_Processing_Duration_Max_ID,
                                                    IDS_Z_COST_PROCESSING_DURATIONMAX_DESC,
                                                    PSS_Duration(GetProcessingDurationMax(),
                                                                 hourPerDay,
                                                                 dayPerWeek,
                                                                 dayPerMonth,
                                                                 dayPerYear),
                                                    ZBProperty::PT_EDIT_DURATION_READONLY,
                                                    true,
                                                    PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));

        propSet.Add(pProcessingDurationMax);

        const float unitCost = RetrieveUnitCost(GetUnitGUID(), error);

        // FIXME translate comments
        // Propriété "Coût" du groupe "Unité de traitement"
        ZBProperty* pUnitCost = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                               ZS_BP_PROP_UNIT,
                                               IDS_Z_UNIT_COST_NAME,
                                               Z_UNIT_COST,
                                               IDS_Z_UNIT_COST_DESC,
                                               unitCost,
                                               ZBProperty::PT_EDIT_NUMBER_READONLY,
                                               true,
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol));

        propSet.Add(pUnitCost);

        ZBProperty* pUnitDoubleValid;

        if (numericValue)
            // FIXME translate comments
            // Propriété "Double validation" du groupe "Unité de traitement"
            pUnitDoubleValid = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                              ZS_BP_PROP_UNIT,
                                              IDS_Z_UNIT_DOUBLE_VALIDATION_NAME,
                                              Z_UNIT_DOUBLE_VALIDATION,
                                              IDS_Z_UNIT_DOUBLE_VALIDATION_DESC,
                                              double(GetUnitDoubleValidationType()),
                                              ZBProperty::PT_EDIT_NUMBER,
                                              false, // Disabled
                                              PSS_StringFormat(PSS_StringFormat::IE_FT_General));
        else
            // FIXME translate comments
            // Propriété "Double validation" du groupe "Unité de traitement"
            pUnitDoubleValid = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                              ZS_BP_PROP_UNIT,
                                              IDS_Z_UNIT_DOUBLE_VALIDATION_NAME,
                                              Z_UNIT_DOUBLE_VALIDATION,
                                              IDS_Z_UNIT_DOUBLE_VALIDATION_DESC,
                                              GetUnitDoubleValidationTypeString(GetUnitDoubleValidationType()),
                                              ZBProperty::PT_COMBO_STRING_READONLY,
                                              false, // Disabled
                                              PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                              &m_UnitDoubleValidationTypeArray);

        propSet.Add(pUnitDoubleValid);
    }

    // FIXME translate comments
    // RS-MODIF 17.11.04, Unit GUID and Name should appear in Conceptor
    // Propriété "Guid" du groupe "Unité de traitement"
    ZBProperty* pUnitGUID = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                           ZS_BP_PROP_UNIT,
                                           IDS_Z_UNIT_GUID_NAME,
                                           Z_UNIT_GUID,
                                           IDS_Z_UNIT_GUID_DESC,
                                           GetUnitGUID(),
                                           ZBProperty::PT_EDIT_EXTENDED_READONLY,
                                           false); // not enable, used for saving the unit GUID

    propSet.Add(pUnitGUID);

    const CString unitName = RetrieveUnitName(GetUnitGUID(), error);

    // Propriété "Unité" du groupe "Unité de traitement"
    ZBProperty* pUnitName = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                           ZS_BP_PROP_UNIT,
                                           IDS_Z_UNIT_NAME_NAME,
                                           Z_UNIT_NAME,
                                           IDS_Z_UNIT_NAME_DESC,
                                           unitName,
                                           (groupEnabled ? ZBProperty::PT_EDIT_EXTENDED_READONLY : ZBProperty::PT_EDIT_STRING_READONLY));
    propSet.Add(pUnitName);

    // if the menu is not loaded, load it
    if (!gCombinationMenu.GetSafeHmenu())
        gCombinationMenu.LoadMenu(IDR_COMBINATION_MENU);

    // FIXME translate comments
    // RS-MODIF 17.11.04 should appear only in Messenger
    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
        dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())
    {
        // run through all combination properties
        CString finalPropTitle;
        count = GetCombinationCount();
        propTitle.LoadString(IDS_ZS_BP_PROP_COMBINATION_TITLE);

        // necessary to check if the initial combination is correct
        CheckInitialCombination();

        index = 0;

        for (int i = 0; i < count; ++i)
        {
            index = i;

            finalPropTitle.Format(_T("%s (%d)"), propTitle, i + 1);

            propName.LoadString(IDS_Z_COMBINATION_NAME_NAME);
            propDesc.LoadString(IDS_Z_COMBINATION_NAME_DESC);

            // FIXME translate comments
            // Propriété "Titre comb." du groupe "Combinaisons x"
            ZBProperty* pCombination = new ZBProperty(finalPropTitle,
                (groupValue ? ZS_BP_PROP_COMBINATION : (ZS_BP_PROP_COMBINATION + i)),
                                                      propName,
                                                      (groupValue ? M_Combination_Name_ID : (M_Combination_Name_ID + (i * _MaxCombinationListSize))),
                                                      propDesc,
                                                      GetCombinationName(i),
                                                      ZBProperty::PT_EDIT_MENU,
                                                      true,
                                                      PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                                      NULL,
                                                      &gCombinationMenu);

            propSet.Add(pCombination);

            propName.LoadString(IDS_Z_COMBINATION_DELIVERABLES_NAME);
            propDesc.LoadString(IDS_Z_COMBINATION_DELIVERABLES_DESC);

            // FIXME translate comments
            // Propriété "Livrables" du groupe "Combinaisons x"
            pCombination = new ZBProperty(finalPropTitle,
                (groupValue ? ZS_BP_PROP_COMBINATION : (ZS_BP_PROP_COMBINATION + i)),
                                          propName,
                                          (groupValue ? M_Combination_Deliverables_ID : (M_Combination_Deliverables_ID + (i * _MaxCombinationListSize))),
                                          propDesc,
                                          GetCombinationDeliverables(i),
                                          ZBProperty::PT_EDIT_EXTENDED_READONLY);

            propSet.Add(pCombination);

            propName.LoadString(IDS_Z_COMBINATION_ACTIVATION_PERC_NAME);
            propDesc.LoadString(IDS_Z_COMBINATION_ACTIVATION_PERC_DESC);

            const float maxPercent = GetMaxActivationPerc(GetCombinationMaster(i));

            // FIXME translate comments
            // Propriété "Pourcentage" du groupe "Combinaisons x"
            pCombination = new ZBProperty(finalPropTitle,
                (groupValue ? ZS_BP_PROP_COMBINATION : (ZS_BP_PROP_COMBINATION + i)),
                                          propName,
                                          (groupValue ? M_Combination_Activation_Perc_ID : (M_Combination_Activation_Perc_ID + (i * _MaxCombinationListSize))),
                                          propDesc,
                                          maxPercent,
                                          ZBProperty::PT_EDIT_NUMBER_READONLY,
                                          true,
                                          PSS_StringFormat(PSS_StringFormat::IE_FT_Percentage));

            propSet.Add(pCombination);

            propName.LoadString(IDS_Z_COMBINATION_MASTER_NAME);
            propDesc.LoadString(IDS_Z_COMBINATION_MASTER_DESC);

            // FIXME translate comments
            // Propriété "Maître" du groupe "Combinaisons x"
            pCombination = new ZBProperty(finalPropTitle,
                (groupValue ? ZS_BP_PROP_COMBINATION : (ZS_BP_PROP_COMBINATION + i)),
                                          propName,
                                          (groupValue ? M_Combination_Master_ID : (M_Combination_Master_ID + (i * _MaxCombinationListSize))),
                                          propDesc,
                                          GetCombinationMaster(i),
                                          ZBProperty::PT_EDIT_EXTENDED_READONLY);

            propSet.Add(pCombination);
        }
    }

    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
        dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())
    {
        const double dValue = double(CalculateProcedureActivation());

        // FIXME translate comments
        // Propriété "Activation" du groupe "Calculs et prévisions"
        ZBProperty* pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                              ZS_BP_PROP_SIM_PROCEDURE,
                                              IDS_Z_SIM_PROCEDURE_ACTIVATION_NAME,
                                              Z_SIM_PROCEDURE_ACTIVATION,
                                              IDS_Z_SIM_PROCEDURE_ACTIVATION_DESC,
                                              dValue,
                                              ZBProperty::PT_EDIT_NUMBER_READONLY,
                                              true,
                                              PSS_StringFormat(PSS_StringFormat::IE_FT_Accounting, true, 0));

        propSet.Add(pSimProp);

        // FIXME translate comments
        // Propriété "Coût HMO" du groupe "Calculs et prévisions"
        pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                  ZS_BP_PROP_SIM_PROCEDURE,
                                  IDS_Z_SIM_PROCEDURE_COST_NAME,
                                  Z_SIM_PROCEDURE_COST,
                                  IDS_Z_SIM_PROCEDURE_COST_DESC,
                                  double(GetProcedureCost()),
                                  ZBProperty::PT_EDIT_NUMBER_READONLY,
                                  true,
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol));

        propSet.Add(pSimProp);

        if (numericValue)
            // FIXME translate comments
            // Propriété "Charge" du groupe "Calculs et prévisions"
            pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                      ZS_BP_PROP_SIM_PROCEDURE,
                                      IDS_Z_SIM_PROCEDURE_WORKLOAD_FORECAST_NAME,
                                      Z_SIM_PROCEDURE_WORKLOAD_FORECAST,
                                      IDS_Z_SIM_PROCEDURE_WORKLOAD_FORECAST_DESC,
                                      double(GetProcedureWorkloadForecast()),
                                      ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "Charge" du groupe "Calculs et prévisions"
            pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                      ZS_BP_PROP_SIM_PROCEDURE,
                                      IDS_Z_SIM_PROCEDURE_WORKLOAD_FORECAST_NAME,
                                      Z_SIM_PROCEDURE_WORKLOAD_FORECAST,
                                      IDS_Z_SIM_PROCEDURE_WORKLOAD_FORECAST_DESC,
                                      PSS_Duration(double(GetProcedureWorkloadForecast()),
                                                   hourPerDay,
                                                   dayPerWeek,
                                                   dayPerMonth,
                                                   dayPerYear),
                                      ZBProperty::PT_EDIT_DURATION_READONLY,
                                      true,
                                      PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));

        propSet.Add(pSimProp);

        // FIXME translate comments
        // Propriété "Coût" du groupe "Calculs et prévisions"
        pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                  ZS_BP_PROP_SIM_PROCEDURE,
                                  IDS_Z_SIM_PROCEDURE_COST_FORECAST_NAME,
                                  Z_SIM_PROCEDURE_COST_FORECAST,
                                  IDS_Z_SIM_PROCEDURE_COST_FORECAST_DESC,
                                  double(GetProcedureCostForecast()),
                                  ZBProperty::PT_EDIT_NUMBER_READONLY,
                                  true,
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol));

        propSet.Add(pSimProp);

        if (numericValue)
            // FIXME translate comments
            // Propriété "Charge / activation" du groupe "Calculs et prévisions"
            pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                      ZS_BP_PROP_SIM_PROCEDURE,
                                      IDS_Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV_NAME,
                                      Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV,
                                      IDS_Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV_DESC,
                                      double(GetProcedureWorkloadPerActivity()),
                                      ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "Charge / activation" du groupe "Calculs et prévisions"
            pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                      ZS_BP_PROP_SIM_PROCEDURE,
                                      IDS_Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV_NAME,
                                      Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV,
                                      IDS_Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV_DESC,
                                      PSS_Duration(double(GetProcedureWorkloadPerActivity()),
                                                   hourPerDay,
                                                   dayPerWeek,
                                                   dayPerMonth,
                                                   dayPerYear),
                                      ZBProperty::PT_EDIT_DURATION_READONLY,
                                      true,
                                      PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));

        propSet.Add(pSimProp);

        // FIXME translate comments
        // Propriété "Coût / activation" du groupe "Calculs et prévisions"
        pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCEDURE,
                                  ZS_BP_PROP_SIM_PROCEDURE,
                                  IDS_Z_SIM_PROCEDURE_COST_P_ACTIV_NAME,
                                  Z_SIM_PROCEDURE_COST_P_ACTIV,
                                  IDS_Z_SIM_PROCEDURE_COST_P_ACTIV_DESC,
                                  GetProcedureCostPerActivity(),
                                  ZBProperty::PT_EDIT_NUMBER_READONLY,
                                  true,
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, currencySymbol));

        propSet.Add(pSimProp);
    }

    return true;
}
//---------------------------------------------------------------------------
bool ZBBPProcedureSymbol::SaveProperties(ZBPropertySet& PropSet)
{
    if (!PSS_Symbol::SaveProperties(PropSet))
    {
        return false;
    }

    // Only local symbol have access to properties
    if (!IsLocal())
    {
        return true;
    }

    ZBProperty* pProp;

    // Save the rules
    ZBBPRuleListProperties* pRulesProps = (ZBBPRuleListProperties*)GetProperty(ZS_BP_PROP_RULELIST);

    if (!pRulesProps)
    {
        return false;
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator f(&PropSet);

    // Empty the task list
    SetRuleList(_T(""));

    for (pProp = f.GetFirst(); pProp; pProp = f.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_RULELIST)
        {
            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    // If not empty, add this new task
                    if (!pProp->GetValueString().IsEmpty())
                    {
                        AddRule(pProp->GetValueString());
                    }

                    break;
                }
            }
        }
    }

    // *************************************************************************************************************
    // JMR-MODIF - Le 11 juillet 2007 - Ajout du code pour la mise à jour des valeurs des risques.

    ZBPropertyIterator h(&PropSet);

    for (pProp = h.GetFirst(); pProp; pProp = h.GetNext())
    {
        if (pProp->GetCategoryID() >= ZS_BP_PROP_RISK &&
            pProp->GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount())
        {
            int i = pProp->GetCategoryID() - ZS_BP_PROP_RISK;

            if (pProp->GetItemID() == M_Risk_Name_ID + (i * _MaxRisksSize))
            {
                SetRiskName(i, pProp->GetValueString());
            }

            if (pProp->GetItemID() == M_Risk_Desc_ID + (i * _MaxRisksSize))
            {
                SetRiskDesc(i, pProp->GetValueString());
            }

            if (pProp->GetItemID() == M_Risk_UE_ID + (i * _MaxRisksSize))
            {
                SetRiskUE(i, pProp->GetValueFloat());
            }

            if (pProp->GetItemID() == M_Risk_POA_ID + (i * _MaxRisksSize))
            {
                SetRiskPOA(i, pProp->GetValueFloat());
            }

            if (pProp->GetItemID() == M_Risk_Action_ID + (i * _MaxRisksSize))
            {
                SetRiskAction(i, (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo() ? 1 : 0));
            }
        }
    }
    // *************************************************************************************************************

    // Save the tasks
    ZBBPTaskListProperties* pTasksProps = (ZBBPTaskListProperties*)GetProperty(ZS_BP_PROP_TASKLIST);

    if (!pTasksProps)
    {
        return false;
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator i(&PropSet);

    // Empty the task list
    SetTaskList(_T(""));

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_TASKLIST)
        {
            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    // If not empty, add this new task
                    if (!pProp->GetValueString().IsEmpty())
                    {
                        AddTask(pProp->GetValueString());
                    }

                    break;
                }
            }
        }
    }

    // Because using the AddTask function, not necessary to SetProperty
    // Save the decisions
    PSS_DecisionListPropertiesBP* pDecisionsProps = (PSS_DecisionListPropertiesBP*)GetProperty(ZS_BP_PROP_DECISIONLIST);

    if (!pDecisionsProps)
    {
        return false;
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator p(&PropSet);

    // Empty the decision list
    SetDecisionList(_T(""));

    for (pProp = p.GetFirst(); pProp; pProp = p.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_DECISIONLIST)
        {
            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    // If not empty, add this new decision
                    if (!pProp->GetValueString().IsEmpty())
                    {
                        AddDecision(pProp->GetValueString());
                    }

                    break;
                }
            }
        }
    }

    // Because using the AddDecision function, not necessary to SetProperty
    // Now run through the list of data and fill the property set
    ZBPropertyIterator j(&PropSet);

    for (pProp = j.GetFirst(); pProp; pProp = j.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_PROCEDURE_COST)
        {
            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    m_CostProcedureProp.SetValue(pProp->GetItemID(), pProp->GetValueString());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    m_CostProcedureProp.SetValue(pProp->GetItemID(),
                                                 static_cast<float>(pProp->GetValueDouble()));
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    m_CostProcedureProp.SetValue(pProp->GetItemID(), pProp->GetValueFloat());
                    break;

                }
                case ZBProperty::PT_DATE:
                {
                    m_CostProcedureProp.SetValue(pProp->GetItemID(),
                                                 static_cast<float>((DATE)pProp->GetValueDate()));
                    break;
                }

                case ZBProperty::PT_TIMESPAN:
                {
                    m_CostProcedureProp.SetValue(pProp->GetItemID(),
                        (double)pProp->GetValueTimeSpan());
                    break;
                }

                case ZBProperty::PT_DURATION:
                {
                    m_CostProcedureProp.SetValue(pProp->GetItemID(),
                        (double)pProp->GetValueDuration());
                    break;
                }
            }
        }
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator k(&PropSet);

    for (pProp = k.GetFirst(); pProp; pProp = k.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT)
        {
            // Check if a flag
            if (pProp->GetItemID() == Z_UNIT_DOUBLE_VALIDATION)
            {
                m_UnitProp.SetValue(pProp->GetItemID(),
                                    ConvertUnitDoubleValidationString2Type(pProp->GetValueString()));
            }
            else
            {
                switch (pProp->GetPTValueType())
                {
                    case ZBProperty::PT_DOUBLE:
                    {
                        m_UnitProp.SetValue(pProp->GetItemID(), static_cast<float>(pProp->GetValueDouble()));
                        break;
                    }

                    case ZBProperty::PT_FLOAT:
                    {
                        m_UnitProp.SetValue(pProp->GetItemID(), pProp->GetValueFloat());
                        break;
                    }

                    case ZBProperty::PT_STRING:
                    {
                        m_UnitProp.SetValue(pProp->GetItemID(), pProp->GetValueString());
                        break;
                    }
                }
            }
        }
    }

    // Now run through the list of data and fill the property set of combination
    ZBPropertyIterator l(&PropSet);

    for (pProp = l.GetFirst(); pProp; pProp = l.GetNext())
    {
        if (pProp->GetCategoryID() >= ZS_BP_PROP_COMBINATION &&
            pProp->GetCategoryID() <= ZS_BP_PROP_COMBINATION + GetCombinationCount())
        {
            int i = pProp->GetCategoryID() - ZS_BP_PROP_COMBINATION;
            PSS_CombinationPropertiesBP* pCombProps = GetCombinationProperty(i);

            if (!pCombProps)
            {
                return false;
            }

            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    pCombProps->SetValue(pProp->GetItemID() - (i * _MaxCombinationListSize),
                                         pProp->GetValueString());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    pCombProps->SetValue(pProp->GetItemID() - (i * _MaxCombinationListSize),
                                         static_cast<float>(pProp->GetValueDouble()));
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    pCombProps->SetValue(pProp->GetItemID() - (i * _MaxCombinationListSize),
                                         pProp->GetValueFloat());
                    break;
                }

                case ZBProperty::PT_DATE:
                {
                    pCombProps->SetValue(pProp->GetItemID() - (i * _MaxCombinationListSize),
                                         static_cast<float>((DATE)pProp->GetValueDate()));
                    break;
                }

                case ZBProperty::PT_TIMESPAN:
                {
                    ASSERT(FALSE);
                    break;
                }

                case ZBProperty::PT_DURATION:
                {
                    ASSERT(FALSE);
                    break;
                }
            }
        }
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator m(&PropSet);

    for (pProp = m.GetFirst(); pProp; pProp = m.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_SIM_PROCEDURE)
        {
            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    m_SimulationProperties.SetValue(pProp->GetItemID(), pProp->GetValueString());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    m_SimulationProperties.SetValue(pProp->GetItemID(), pProp->GetValueDouble());
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    m_SimulationProperties.SetValue(pProp->GetItemID(), pProp->GetValueFloat());
                    break;
                }

                case ZBProperty::PT_DATE:
                {
                    m_SimulationProperties.SetValue(pProp->GetItemID(),
                                                    static_cast<float>((DATE)pProp->GetValueDate()));
                    break;
                }

                case ZBProperty::PT_TIMESPAN:
                {
                    m_SimulationProperties.SetValue(pProp->GetItemID(), (double)pProp->GetValueTimeSpan());
                    break;
                }

                case ZBProperty::PT_DURATION:
                {
                    m_SimulationProperties.SetValue(pProp->GetItemID(), (double)pProp->GetValueDuration());
                    break;
                }
            }
        }
    }

    RefreshAttributeTextArea(true);

    return true;
}

bool ZBBPProcedureSymbol::SaveProperty(ZBProperty& Property)
{
    if (!PSS_Symbol::SaveProperty(Property))
    {
        return false;
    }

    // Only local symbol have access to properties
    if (!IsLocal())
    {
        return true;
    }

    // ************************************************************************************************
    // JMR-MODIF - Le 17 juillet 2007 - Mise à jour des valeurs des propriétés des risques.

    if (Property.GetCategoryID() >= ZS_BP_PROP_RISK &&
        Property.GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_RISK;

        if (Property.GetItemID() == M_Risk_Name_ID + (i * _MaxRisksSize))
        {
            SetRiskName(i, Property.GetValueString());
        }

        if (Property.GetItemID() == M_Risk_Desc_ID + (i * _MaxRisksSize))
        {
            SetRiskDesc(i, Property.GetValueString());
        }

        if (Property.GetItemID() == M_Risk_UE_ID + (i * _MaxRisksSize))
        {
            SetRiskUE(i, Property.GetValueFloat());
        }

        if (Property.GetItemID() == M_Risk_POA_ID + (i * _MaxRisksSize))
        {
            SetRiskPOA(i, Property.GetValueFloat());
        }

        if (Property.GetItemID() == M_Risk_Action_ID + (i * _MaxRisksSize))
        {
            SetRiskAction(i, (Property.GetValueString() == PSS_Global::GetYesFromArrayYesNo() ? 1 : 0));
        }
    }
    // ************************************************************************************************

    // JMR-MODIF - Le 9 mai 2007 - Contrôle si l'utilisateur a tenté de renommer une règle.
    // Si c'est le cas, réetablit le nom d'origine.
    if (Property.GetCategoryID() == ZS_BP_PROP_RULES)
    {
        int Index = (Property.GetItemID() - Z_RULE_NAME) / _MaxRulesSize;

        if (m_Rules.GetRuleName(Index) != Property.GetValueString())
        {
            Property.SetValueString(m_Rules.GetRuleName(Index));
        }
    }

    if (Property.GetCategoryID() >= ZS_BP_PROP_COMBINATION &&
        Property.GetCategoryID() <= ZS_BP_PROP_COMBINATION + GetCombinationCount())
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_COMBINATION;

        switch (Property.GetItemID() - (i * _MaxCombinationListSize))
        {
            case M_Combination_Name_ID:
            {
                SetCombinationName(Property.GetCategoryID() - ZS_BP_PROP_COMBINATION,
                                   Property.GetValueString());
                break;
            }

            case M_Combination_Deliverables_ID:
            {
                SetCombinationDeliverables(Property.GetCategoryID() - ZS_BP_PROP_COMBINATION,
                                           Property.GetValueString());
                break;
            }

            case M_Combination_Activation_Perc_ID:
            {
                SetCombinationActivationPerc(Property.GetCategoryID() - ZS_BP_PROP_COMBINATION,
                                             Property.GetValueFloat());
                break;
            }

            case M_Combination_Master_ID:
            {
                SetCombinationMaster(Property.GetCategoryID() - ZS_BP_PROP_COMBINATION,
                                     Property.GetValueString());
                break;
            }
        }
    }

    if (Property.GetCategoryID() == ZS_BP_PROP_RULELIST)
    {
        // If not empty, add this new rule
        if (!Property.GetValueString().IsEmpty())
        {
            AddRule(Property.GetValueString());
        }
    }

    if (Property.GetCategoryID() == ZS_BP_PROP_TASKLIST)
    {
        // If not empty, add this new task
        if (!Property.GetValueString().IsEmpty())
        {
            AddTask(Property.GetValueString());
        }
    }

    if (Property.GetCategoryID() == ZS_BP_PROP_DECISIONLIST)
    {
        // If not empty, add this new task
        if (!Property.GetValueString().IsEmpty())
        {
            AddDecision(Property.GetValueString());
        }
    }

    // Set the modified flag to true,
    // Do nothing more, the values will be saved by the save properties method
    SetModifiedFlag();

    return true;
}

bool ZBBPProcedureSymbol::CheckPropertyValue(ZBProperty& Property, CString& value, ZBPropertySet& Properties)
{
    return PSS_Symbol::CheckPropertyValue(Property, value, Properties);
}

bool ZBBPProcedureSymbol::ProcessExtendedInput(ZBProperty&        Property,
                                               CString&        value,
                                               ZBPropertySet&    Properties,
                                               bool&            Refresh)
{
    // ****************************************************************************************************
    // JMR-MODIF - Le 13 juin 2007 - Ajout de la prise en charge des risques.

    if (Property.GetCategoryID() >= ZS_BP_PROP_RISK &&
        Property.GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        int            i = Property.GetCategoryID() - ZS_BP_PROP_RISK;
        CODModel*    pModel = GetRootModel();
        CString        CurrencySymbol = PSS_Global::GetLocaleCurrency();

        if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl))
        {
            CDocument* pDoc = dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetDocument();

            if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc))
            {
                // Retrieve the model's currency symbol
                CurrencySymbol = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetCurrencySymbol();
            }
        }

        CString s_NoRiskType = _T("");
        s_NoRiskType.LoadString(IDS_NO_RISK_TYPE);

        ZVRiskOptionsDlg m_RiskOptions(GetRiskName(i),
                                       GetRiskDesc(i),
                                       (GetRiskType(i).IsEmpty()) ? s_NoRiskType : GetRiskType(i),
                                       GetRiskImpact(i),
                                       GetRiskProbability(i),
                                       GetRiskUE(i),
                                       GetRiskPOA(i),
                                       GetRiskAction(i),
                                       CurrencySymbol);

        if (m_RiskOptions.DoModal() == IDOK)
        {
            SetRiskName(i, m_RiskOptions.GetRiskTitle());
            SetRiskDesc(i, m_RiskOptions.GetRiskDescription());
            SetRiskType(i, m_RiskOptions.GetRiskType());
            SetRiskImpact(i, m_RiskOptions.GetRiskImpact());
            SetRiskProbability(i, m_RiskOptions.GetRiskProbability());
            SetRiskSeverity(i, m_RiskOptions.GetRiskSeverity());
            SetRiskUE(i, m_RiskOptions.GetRiskUE());
            SetRiskPOA(i, m_RiskOptions.GetRiskPOA());
            SetRiskAction(i, m_RiskOptions.GetRiskAction());

            SetModifiedFlag(TRUE);

            Refresh = true;

            return true;
        }
    }
    // ****************************************************************************************************

    CODModel * pModel = GetOwnerModel();

    if (Property.GetCategoryID() == ZS_BP_PROP_UNIT && Property.GetItemID() == Z_UNIT_NAME)
    {
        if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl))
        {
            PSS_SelectUserGroupDlg dlg(IDS_SELECTAGROUP_T,
                                       dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetMainUserGroup(),
                                       true,    // Allow group selection
                                       false); // Doesn't allow role selection

            if (dlg.DoModal() == IDOK)
            {
                PSS_UserEntity* pUserEntity = dlg.GetSelectedUserEntity();

                if (pUserEntity)
                {
                    value = pUserEntity->GetEntityName();

                    // And change the unit GUID of the disable property
                    ZBPropertyIterator i(&Properties);
                    ZBProperty* pProp;

                    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
                    {
                        if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == Z_UNIT_GUID)
                        {
                            pProp->SetValueString(pUserEntity->GetGUID());
                            break;
                        }
                    }

                    return true;
                }
            }
        }
    }
    else if (Property.GetCategoryID() >= ZS_BP_PROP_COMBINATION &&
             Property.GetCategoryID() <= ZS_BP_PROP_COMBINATION + GetCombinationCount())
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_COMBINATION;

        switch (Property.GetItemID() - (i * _MaxCombinationListSize))
        {
            case M_Combination_Deliverables_ID:
            {
                // Get the deliverables
                CString EnteringDeliverables;
                GetEnteringUpDeliverable(EnteringDeliverables);
                CString AvailableDeliverables = GetAvailableDeliverables(EnteringDeliverables);

                // Call the dialog
                ZVAddRemoveCombinationDeliverableDlg dlg(AvailableDeliverables, value);

                if (dlg.DoModal() == IDOK)
                {
                    value = dlg.GetDeliverables();
                    return true;
                }

                break;
            }

            case M_Combination_Master_ID:
            {
                ZVChooseMasterDeliverable dlg(GetCombinationDeliverables(i), value);

                if (dlg.DoModal() == IDOK)
                {
                    value = dlg.GetMaster();
                    return true;
                }

                break;
            }
        }
    }

    return PSS_Symbol::ProcessExtendedInput(Property, value, Properties, Refresh);
}

bool ZBBPProcedureSymbol::ProcessMenuCommand(int                MenuCommand,
                                             ZBProperty&        Property,
                                             CString&            value,
                                             ZBPropertySet&    Properties,
                                             bool&                Refresh)
{
    // ************************************************************************************************************
    // JMR-MODIF - Le 10 juin - Ajout du code pour traitement du menu des risques.

    if (Property.GetCategoryID() >= ZS_BP_PROP_RISK &&
        Property.GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        switch (MenuCommand)
        {
            case ID_ADD_NEWRISK:
            {
                OnAddNewRisk(Property, value, Properties, Refresh);
                break;
            }

            case ID_DEL_CURRENTRISK:
            {
                OnDelCurrentRisk(Property, value, Properties, Refresh);
                break;
            }

            default:
            {
                break;
            }
        }

        return true;
    }
    // ************************************************************************************************************

    if (Property.GetCategoryID() >= ZS_BP_PROP_COMBINATION &&
        Property.GetCategoryID() <= ZS_BP_PROP_COMBINATION + GetCombinationCount())
    {
        switch (MenuCommand)
        {
            case ID_ADD_NEWCOMBINATION:
            {
                OnAddNewCombination(Property, value, Properties, Refresh);
                break;
            }

            case ID_DEL_CURRENTCOMBINATION:
            {
                OnDelCurrentCombination(Property, value, Properties, Refresh);
                break;
            }

            case ID_ADD_DELIVERABLE_COMBINATION:
            {
                OnAddDeliverableCombination(Property, value, Properties, Refresh);
                break;
            }

            case ID_DEL_DELIVERABLE_COMBINATION:
            {
                OnDelDeliverableCombination(Property, value, Properties, Refresh);
                break;
            }

            default:
            {
                break;
            }
        }

        return true;
    }

    // ************************************************************************************************************
    // JMR-MODIF - Le 28 novembre 2006 - Ajout du code pour traitement de la fonction supprimer du menu des règles.

    if (Property.GetCategoryID() == ZS_BP_PROP_RULES)
    {
        switch (MenuCommand)
        {
            case ID_DEL_CURRENTRULE:
            {
                int Index = (Property.GetItemID() - Z_RULE_NAME) / _MaxRulesSize;

                m_Rules.DeleteRule(Index);

                // JMR-MODIF - Le 8 mai 2007 - Demande le rafraîchissement après exécution de l'opération.
                Refresh = true;

                break;
            }

            default:
            {
                break;
            }
        }
    }
    // ************************************************************************************************************

    return PSS_Symbol::ProcessMenuCommand(MenuCommand, Property, value, Properties, Refresh);
}

bool ZBBPProcedureSymbol::OnPostPropertyChanged(ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh)
{
    // Only local symbol have access to properties
    if (!IsLocal())
    {
        return false;
    }

    bool RetValue = false;

    if (Property.GetCategoryID() >= ZS_BP_PROP_COMBINATION &&
        Property.GetCategoryID() <= ZS_BP_PROP_COMBINATION + GetCombinationCount())
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_COMBINATION;

        switch (Property.GetItemID() - (i * _MaxCombinationListSize))
        {
            case M_Combination_Deliverables_ID:
            {
                float MaxPercent =
                    GetMaxActivationPerc(GetCombinationMaster(Property.GetCategoryID() - ZS_BP_PROP_COMBINATION));

                // Now sets the right value to the right property
                ZBPropertyIterator s(&Properties);
                ZBProperty* pProp;
                bool bFound = false;

                for (pProp = s.GetFirst(); pProp && bFound == false; pProp = s.GetNext())
                {
                    if (!pProp || ((pProp->GetCategoryID() - ZS_BP_PROP_COMBINATION) != i))
                    {
                        continue;
                    }

                    if (pProp->GetItemID() - (i * _MaxCombinationListSize) == M_Combination_Activation_Perc_ID)
                    {
                        pProp->SetValueFloat(MaxPercent);
                        bFound = true;
                    }
                }

                // Change the return value if we found
                if (bFound)
                {
                    RetValue = true;
                }

                break;
            }

            default:
            {
                break;
            }
        }
    }
    else if (Property.GetCategoryID() == ZS_BP_PROP_UNIT &&
             Property.GetItemID() == Z_UNIT_NAME)
    {
        // Run trough the set of properties and changed the unit cost
        // to the value of the property
        ZBPropertyIterator i(&Properties);
        ZBProperty* pProp;
        CString GUID;

        for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        {
            if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == Z_UNIT_GUID)
            {
                GUID = pProp->GetValueString();
                break;
            }
        }

        if (!GUID.IsEmpty())
        {
            for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
            {
                if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == Z_UNIT_COST)
                {
                    bool Error;
                    float UnitCost = RetrieveUnitCost(GUID, Error);

                    if (Error == false)
                    {
                        // If the previous value is different
                        pProp->SetValueFloat(UnitCost);

                        // Change the return value
                        RetValue = true;
                    }

                    break;
                }
            }
        }
    }
    else if (Property.GetCategoryID() == ZS_BP_PROP_RULELIST)
    {
        // Change the return value to reload the properties
        // We need to reload since the rulelist has an empty task.
        // If the user fill it, we need to enable a new empty one.
        // And if the user remove one task, we need also to disable one from
        // the property list

        // Run trough the set of properties and changed the enable flag
        // To change the enable flag, we need to check if it is a new
        // property that need to be enabled or not
        // Then we need to insure that only one empty property is enable
        ZBPropertyIterator i(&Properties);
        ZBProperty* pProp;
        size_t        CounterEnableEmpty = 0;

        for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        {
            if (pProp->GetCategoryID() == ZS_BP_PROP_RULELIST)
            {
                // If the string is not empty, first, sets the enable flag to true
                if (!pProp->GetValueString().IsEmpty())
                {
                    pProp->SetEnable(true);
                }

                // If the string is empty
                // Check if he has the enable flag and add it to the counter
                // If the counter is not equal to 1, then enable or disable it
                if (pProp->GetValueString().IsEmpty())
                {
                    if (pProp->GetEnable() == true)
                    {
                        ++CounterEnableEmpty;
                    }
                    else
                    {
                        // If not at least one empty element
                        if (CounterEnableEmpty < 1)
                        {
                            pProp->SetEnable(true);
                            ++CounterEnableEmpty;
                        }
                    }

                    // Now if the counter is greather than 1, then you need to disable the empty element
                    if (CounterEnableEmpty > 1)
                    {
                        --CounterEnableEmpty;
                        pProp->SetEnable(false);
                    }
                }
            }
        }

        RetValue = true;
    }
    else if (Property.GetCategoryID() == ZS_BP_PROP_TASKLIST)
    {
        // Change the return value to reload the properties
        // We need to reload since the tasklist has an empty task.
        // If the user fill it, we need to enable a new empty one.
        // And if the user remove one task, we need also to disable one from
        // the property list

        // Run trough the set of properties and changed the enable flag
        // To change the enable flag, we need to check if it is a new
        // property that need to be enabled or not
        // Then we need to insure that only one empty property is enable
        ZBPropertyIterator i(&Properties);
        ZBProperty* pProp;
        size_t        CounterEnableEmpty = 0;

        for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        {
            if (pProp->GetCategoryID() == ZS_BP_PROP_TASKLIST)
            {
                // If the string is not empty, first, sets the enable flag to true
                if (!pProp->GetValueString().IsEmpty())
                {
                    pProp->SetEnable(true);
                }

                // If the string is empty
                // Check if he has the enable flag and add it to the counter
                // If the counter is not equal to 1, then enable or disable it
                if (pProp->GetValueString().IsEmpty())
                {
                    if (pProp->GetEnable() == true)
                    {
                        ++CounterEnableEmpty;
                    }
                    else
                    {
                        // If not at least one empty element
                        if (CounterEnableEmpty < 1)
                        {
                            pProp->SetEnable(true);
                            ++CounterEnableEmpty;
                        }
                    }

                    // Now if the counter is greather than 1, then you need to disable the empty element
                    if (CounterEnableEmpty > 1)
                    {
                        --CounterEnableEmpty;
                        pProp->SetEnable(false);
                    }
                }
            }
        }

        RetValue = true;
    }
    else if (Property.GetCategoryID() == ZS_BP_PROP_DECISIONLIST)
    {
        // Change the return value to reload the properties
        // We need to reload since the decisionlist has an empty decision.
        // If the user fill it, we need to enable a new empty one.
        // And if the user remove one decision, we need also to disable one from
        // the property list

        // Run trough the set of properties and changed the enable flag
        // To change the enable flag, we need to check if it is a new
        // property that need to be enabled or not
        // Then we need to insure that only one empty property is enable
        ZBPropertyIterator i(&Properties);
        ZBProperty* pProp;
        size_t        CounterEnableEmpty = 0;

        for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
        {
            if (pProp->GetCategoryID() == ZS_BP_PROP_DECISIONLIST)
            {
                // If the string is not empty, first, sets the enable flag to true
                if (!pProp->GetValueString().IsEmpty())
                {
                    pProp->SetEnable(true);
                }

                // If the string is empty
                // Check if he has the enable flag and add it to the counter
                // If the counter is not equal to 1, then enable or disable it
                if (pProp->GetValueString().IsEmpty())
                {
                    if (pProp->GetEnable() == true)
                    {
                        ++CounterEnableEmpty;
                    }
                    else
                    {
                        // If not at least one empty element
                        if (CounterEnableEmpty < 1)
                        {
                            pProp->SetEnable(true);
                            ++CounterEnableEmpty;
                        }
                    }

                    // Now if the counter is greather than 1, then you need to disable the empty element
                    if (CounterEnableEmpty > 1)
                    {
                        --CounterEnableEmpty;
                        pProp->SetEnable(false);
                    }
                }
            }
        }

        RetValue = true;
    }

    if (RetValue == false)
    {
        return PSS_Symbol::OnPostPropertyChanged(Property, Properties, Refresh);
    }

    return RetValue;
}

bool ZBBPProcedureSymbol::OnDropInternalPropertyItem(ZBProperty&        SrcProperty,
                                                     ZBProperty&        DstProperty,
                                                     bool                Top2Down,
                                                     ZBPropertySet&    Properties)
{
    // Call the utility function for swaping two property items
    bool RetValue = ::SwapInternalPropertyItem(SrcProperty,
                                               DstProperty,
                                               Top2Down,
                                               Properties,
                                               ZS_BP_PROP_TASKLIST);

    // If done, return
    if (RetValue)
    {
        return true;
    }

    RetValue = ::SwapInternalPropertyItem(SrcProperty,
                                          DstProperty,
                                          Top2Down,
                                          Properties,
                                          ZS_BP_PROP_RULELIST);

    // If done, return
    if (RetValue)
    {
        return true;
    }

    // ********************************************************************************************
    // JMR-MODIF - Le 10 décembre 2006 - Ajout du code pour permettre le glisser-coller des règles.

    RetValue = ::SwapInternalPropertyItem(SrcProperty,
                                          DstProperty,
                                          Top2Down,
                                          Properties,
                                          ZS_BP_PROP_RULES);

    // If done, return
    if (RetValue)
    {
        int SrcIndex = (SrcProperty.GetItemID() - Z_RULE_NAME) / _MaxRulesSize;
        int DstIndex = (DstProperty.GetItemID() - Z_RULE_NAME) / _MaxRulesSize;

        CString SrcRuleName = m_Rules.GetRuleName(SrcIndex);
        CString SrcRuleDesc = m_Rules.GetRuleDescription(SrcIndex);
        CString SrcRuleGUID = m_Rules.GetRuleGUID(SrcIndex);

        CString DstRuleName = m_Rules.GetRuleName(DstIndex);
        CString DstRuleDesc = m_Rules.GetRuleDescription(DstIndex);
        CString DstRuleGUID = m_Rules.GetRuleGUID(DstIndex);

        m_Rules.SetRuleName(SrcIndex, DstRuleName);
        m_Rules.SetRuleDescription(SrcIndex, DstRuleDesc);
        m_Rules.SetRuleGUID(SrcIndex, DstRuleGUID);

        m_Rules.SetRuleName(DstIndex, SrcRuleName);
        m_Rules.SetRuleDescription(DstIndex, SrcRuleDesc);
        m_Rules.SetRuleGUID(DstIndex, SrcRuleGUID);

        return true;
    }
    // ********************************************************************************************

    // Otherwise, try to do it for Decisions
    return ::SwapInternalPropertyItem(SrcProperty, DstProperty, Top2Down, Properties, ZS_BP_PROP_DECISIONLIST);
}

float ZBBPProcedureSymbol::GetMaxActivationPerc(const CString Master)
{
    if (Master.IsEmpty())
    {
        return 0;
    }

    double Sum = 0;
    double MasterQuantity = 0;

    CODEdgeArray Edges;

    // Retrieve all entering Up edges of the procedure
    if (GetEnteringUpDeliverable(Edges) > 0)
    {
        for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
        {
            IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

            // Test if it is a local symbol
            if (!pComp->IsLocal())
            {
                // Locate the local symbol
                CODComponent* pLocalComp = pComp->GetLocalSymbol();

                if (pLocalComp && ISA(pLocalComp, ZBDeliverableLinkSymbol))
                {
                    pComp = dynamic_cast<ZBDeliverableLinkSymbol*>(pLocalComp);
                }
                else
                {
                    pComp = NULL;
                }
            }

            if (pComp)
            {
                // Check if the component is the requested master
                if (pComp->GetSymbolName() == Master)
                {
                    MasterQuantity = (double)pComp->GetQuantity();
                }

                // Now, run through combination
                // and check if the component is a master of the combination
                // add its quantity to the sum
                int CombinationCount = GetCombinationCount();

                for (int i = 0; i < CombinationCount; ++i)
                {
                    if (pComp->GetSymbolName() == GetCombinationMaster(i))
                    {
                        Sum += (double)pComp->GetQuantity();
                    }
                }
            }
        }
    }

    return (float)(MasterQuantity / Sum);
}

// To calculate the procedure activation,
// we need to run through all combination and to take the maximum
// of each deliverable multiply by the percent of its combination
PSS_AnnualNumberPropertiesBP ZBBPProcedureSymbol::CalculateProcedureActivation()
{
    // First, we need to get all entering deliverables
    CODEdgeArray Edges;

    // Retrieve all entering Up edges
    if (GetEnteringUpDeliverable(Edges) == 0)
    {
        return 0;
    }

    // Now for each deliverables, we will calculate the max procedure activation
    PSS_AnnualNumberPropertiesBP ProcedureActivation(0);

    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        ZBDeliverableLinkSymbol* pDeliverable = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

        if (!pDeliverable)
        {
            continue;
        }

        // Test if it is a local symbol
        if (!pDeliverable->IsLocal())
        {
            // Locate the local symbol
            CODComponent* pComp = pDeliverable->GetLocalSymbol();

            if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
            {
                pDeliverable = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
            }
            else
            {
                // Log the error
                return false;
            }
        }

        // Run through combination and check if this deliverable is defined as a master.
        // If yes, add it to the procedure activation
        int Count = GetCombinationCount();

        for (int i = 0; i < Count; ++i)
        {
            TRACE1(_T("Master = %s"), GetCombinationMaster(i));
            TRACE1(_T("   Livrable = %s\n"), pDeliverable->GetSymbolName());

            // If we have a master
            if (!GetCombinationMaster(i).IsEmpty() && GetCombinationMaster(i) == pDeliverable->GetSymbolName())
            {
                ProcedureActivation += pDeliverable->GetQuantity();
            }
        }
    }

    return ProcedureActivation;
}

int ZBBPProcedureSymbol::GetEnteringUpDeliverable(CString& EnteringDeliverables)
{
    int Counter = 0;
    CODEdgeArray Edges;

    // Keep only deliverable symbols
    if (GetEnteringUpDeliverable(Edges) > 0)
    {
        PSS_Tokenizer token;    // Initialize the token with ; as separator

        for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
        {
            IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

            if (pComp)
            {
                token.AddToken(pComp->GetSymbolName());
                ++Counter;
            }
        }

        // Assign the return string
        EnteringDeliverables = token.GetString();
    }

    return Counter;
}

int     ZBBPProcedureSymbol::GetEnteringUpDeliverable(CODEdgeArray& Edges)
{
    // Retrieve all entering Up edges of the procedure
    GetEdgesEntering_Up(Edges);

    // And also from all referenced procedures
    // and local symbol if we have a referenced symbol
    CODComponentSet* pSet;
    CODComponentSet  InternalSet;

    if (IsLocal())
    {
        pSet = GetReferenceSymbols();
    }
    else
    {
        pSet = GetReferenceSymbols();

        if (!pSet)
        {
            pSet = &InternalSet;
        }

        CODComponent* pLocalSymbol = GetLocalSymbol();

        if (pLocalSymbol)
        {
            pSet->Add(pLocalSymbol);
        }
    }

    if (pSet && pSet->GetSize() > 0)
    {
        for (int i = 0; i < pSet->GetSize(); ++i)
        {
            CODComponent* pComp = pSet->GetAt(i);

            if (pComp && ISA(pComp, ZBBPProcedureSymbol))
            {
                CODEdgeArray AdditionalEdges;
                reinterpret_cast<ZBBPProcedureSymbol*>(pComp)->GetEdgesEntering_Up(AdditionalEdges);

                // Copy additional edges to the principal edges
                for (int nEdgeIdx = 0; nEdgeIdx < AdditionalEdges.GetSize(); ++nEdgeIdx)
                {
                    // Get the link 
                    Edges.AddEdge(AdditionalEdges.GetAt(nEdgeIdx));
                }
            }
        }
    }

    // Keep only deliverable symbols
    return (int)PSS_ODSymbolManipulator::KeepOnlyLinksISA(Edges, RUNTIME_CLASS(ZBDeliverableLinkSymbol));
}

int ZBBPProcedureSymbol::GetLeavingDownDeliverable(CString& LeavingDeliverables)
{
    int Counter = 0;
    CODEdgeArray Edges;

    if (GetLeavingDownDeliverable(Edges) > 0)
    {
        PSS_Tokenizer token;    // Initialize the token with ; as separator

        for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
        {
            IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

            if (pComp)
            {
                token.AddToken(pComp->GetSymbolName());
                ++Counter;
            }
        }

        // Assign the return string
        LeavingDeliverables = token.GetString();
    }

    return Counter;
}

int ZBBPProcedureSymbol::GetLeavingDownDeliverable(CODEdgeArray& Edges)
{
    // Retrieve all leaving down edges
    GetEdgesLeaving_Down(Edges);

    // And also from all referenced procedures
    // and local symbol if we have a referenced symbol
    CODComponentSet* pSet;
    CODComponentSet  InternalSet;

    if (IsLocal())
    {
        pSet = GetReferenceSymbols();
    }
    else
    {
        pSet = GetReferenceSymbols();

        if (!pSet)
        {
            pSet = &InternalSet;
        }

        CODComponent* pLocalSymbol = GetLocalSymbol();

        if (pLocalSymbol)
        {
            pSet->Add(pLocalSymbol);
        }
    }

    if (pSet && pSet->GetSize() > 0)
    {
        for (int i = 0; i < pSet->GetSize(); ++i)
        {
            CODComponent* pComp = pSet->GetAt(i);

            if (pComp && ISA(pComp, ZBBPProcedureSymbol))
            {
                CODEdgeArray AdditionalEdges;
                reinterpret_cast<ZBBPProcedureSymbol*>(pComp)->GetEdgesLeaving_Down(AdditionalEdges);

                // Copy additional edges to the principal edges
                for (int nEdgeIdx = 0; nEdgeIdx < AdditionalEdges.GetSize(); ++nEdgeIdx)
                {
                    // Get the link 
                    Edges.AddEdge(AdditionalEdges.GetAt(nEdgeIdx));
                }
            }
        }
    }

    // Keep only deliverable symbols
    return (int)PSS_ODSymbolManipulator::KeepOnlyLinksISA(Edges, RUNTIME_CLASS(ZBDeliverableLinkSymbol));
}

int     ZBBPProcedureSymbol::GetLeavingRightDeliverable(CString& LeavingDeliverables)
{
    int Counter = 0;
    CODEdgeArray Edges;

    if (GetLeavingRightDeliverable(Edges) > 0)
    {
        PSS_Tokenizer token;    // Initialize the token with ; as separator

        for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
        {
            IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

            if (pComp)
            {
                token.AddToken(pComp->GetSymbolName());
                ++Counter;
            }
        }

        // Assign the return string
        LeavingDeliverables = token.GetString();
    }

    return Counter;
}

int     ZBBPProcedureSymbol::GetLeavingRightDeliverable(CODEdgeArray& Edges)
{
    // Retrieve all leaving right edges
    GetEdgesLeaving_Right(Edges);

    // And also from all referenced procedures
    // and local symbol if we have a referenced symbol
    CODComponentSet* pSet;
    CODComponentSet  InternalSet;

    if (IsLocal())
    {
        pSet = GetReferenceSymbols();
    }
    else
    {
        pSet = GetReferenceSymbols();

        if (!pSet)
        {
            pSet = &InternalSet;
        }

        CODComponent* pLocalSymbol = GetLocalSymbol();

        if (pLocalSymbol)
        {
            pSet->Add(pLocalSymbol);
        }
    }

    if (pSet && pSet->GetSize() > 0)
    {
        for (int i = 0; i < pSet->GetSize(); ++i)
        {
            CODComponent* pComp = pSet->GetAt(i);

            if (pComp && ISA(pComp, ZBBPProcedureSymbol))
            {
                CODEdgeArray AdditionalEdges;
                reinterpret_cast<ZBBPProcedureSymbol*>(pComp)->GetEdgesLeaving_Right(AdditionalEdges);

                // Copy additional edges to the principal edges
                for (int nEdgeIdx = 0; nEdgeIdx < AdditionalEdges.GetSize(); ++nEdgeIdx)
                {
                    // Get the link 
                    Edges.AddEdge(AdditionalEdges.GetAt(nEdgeIdx));
                }
            }
        }
    }

    // Keep only deliverable symbols
    return (int)PSS_ODSymbolManipulator::KeepOnlyLinksISA(Edges, RUNTIME_CLASS(ZBDeliverableLinkSymbol));
}

int     ZBBPProcedureSymbol::GetLeavingLeftDeliverable(CString& LeavingDeliverables)
{
    int Counter = 0;
    CODEdgeArray Edges;

    if (GetLeavingLeftDeliverable(Edges) > 0)
    {
        PSS_Tokenizer token;    // Initialize the token with ; as separator

        for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
        {
            IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

            if (pComp)
            {
                token.AddToken(pComp->GetSymbolName());
                ++Counter;
            }
        }

        // Assign the return string
        LeavingDeliverables = token.GetString();
    }

    return Counter;
}

int     ZBBPProcedureSymbol::GetLeavingLeftDeliverable(CODEdgeArray& Edges)
{
    // Retrieve all leaving left edges
    GetEdgesLeaving_Left(Edges);

    // And also from all referenced procedures
    // and local symbol if we have a referenced symbol
    CODComponentSet* pSet;
    CODComponentSet  InternalSet;

    if (IsLocal())
    {
        pSet = GetReferenceSymbols();
    }
    else
    {
        pSet = GetReferenceSymbols();

        if (!pSet)
        {
            pSet = &InternalSet;
        }

        CODComponent* pLocalSymbol = GetLocalSymbol();

        if (pLocalSymbol)
        {
            pSet->Add(pLocalSymbol);
        }
    }

    if (pSet && pSet->GetSize() > 0)
    {
        for (int i = 0; i < pSet->GetSize(); ++i)
        {
            CODComponent* pComp = pSet->GetAt(i);

            if (pComp && ISA(pComp, ZBBPProcedureSymbol))
            {
                CODEdgeArray AdditionalEdges;
                reinterpret_cast<ZBBPProcedureSymbol*>(pComp)->GetEdgesLeaving_Left(AdditionalEdges);

                // Copy additional edges to the principal edges
                for (int nEdgeIdx = 0; nEdgeIdx < AdditionalEdges.GetSize(); ++nEdgeIdx)
                {
                    // Get the link 
                    Edges.AddEdge(AdditionalEdges.GetAt(nEdgeIdx));
                }
            }
        }
    }

    // Keep only deliverable symbols
    return (int)PSS_ODSymbolManipulator::KeepOnlyLinksISA(Edges, RUNTIME_CLASS(ZBDeliverableLinkSymbol));
}

BOOL ZBBPProcedureSymbol::SetSymbolName(const CString value)
{
    BOOL bResult = PSS_Symbol::SetSymbolName(value);
    return bResult;
}

// Drag and drop methods
bool ZBBPProcedureSymbol::AcceptDropItem(CObject* pObj, const CPoint& pt)
{
    // JMR-MODIF - Le 18 décembre 2006 - Si le symbole n'est pas local, interdit l'opération de glisser-coller.
    if (!IsLocal())
    {
        return false;
    }

    // If a user entity
    if (pObj && ISA(pObj, PSS_UserGroupEntity))
    {
        return true;
    }

    // JMR-MODIF - Le 19 novembre 2006 - Détermine si l'objet reçu est un objet de type règle.
    if (pObj && ISA(pObj, PSS_LogicalRulesEntity))
    {
        return true;
    }

    return PSS_Symbol::AcceptDropItem(pObj, pt);
}

bool ZBBPProcedureSymbol::DropItem(CObject* pObj, const CPoint& pt)
{
    if (pObj && ISA(pObj, PSS_UserGroupEntity))
    {
        // First, check if the user group is valid
        CODModel* pModel = GetRootModel();

        if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
            !dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->MainUserGroupIsValid())
        {
            // Cannot delete all combinations
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_USERGROUPNOTINLINE, MB_OK);
            return false;
        }

        PSS_UserGroupEntity* pGroup = dynamic_cast<PSS_UserGroupEntity*>(pObj);
        SetUnitGUID(pGroup->GetGUID());
        SetUnitName(pGroup->GetEntityName());

        // Change the unit cost
        SetUnitCost(pGroup->GetEntityCost());

        // Set flag for modification
        SetModifiedFlag(TRUE);

        // Refresh the attribute area and redraw the symbol
        RefreshAttributeTextArea(true);
        return true;
    }

    // *********************************************************************************************
    // JMR-MODIF - Le 20 novembre 2006 - Ajout du code pour le traitement des objets de type règles.
    if (pObj && ISA(pObj, PSS_LogicalRulesEntity))
    {
        // First, check if the rule is valid
        CODModel* pModel = GetRootModel();

        if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
            !dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->MainLogicalRulesIsValid())
        {
            // Cannot delete all rules
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_RULENOTINLINE, MB_OK);
            return false;
        }

        PSS_LogicalRulesEntity* pRule = dynamic_cast<PSS_LogicalRulesEntity*>(pObj);

        ZBBPRulesProperties* m_NewRule = new ZBBPRulesProperties();

        m_NewRule->SetRuleName(pRule->GetEntityName());
        m_NewRule->SetRuleDescription(pRule->GetEntityDescription());
        m_NewRule->SetRuleGUID(pRule->GetGUID());

        m_Rules.AddRule(m_NewRule);

        // Set flag for modification
        SetModifiedFlag(TRUE);

        // Refresh the attribute area and redraw the symbol
        RefreshAttributeTextArea(true);
        return true;
    }
    // *********************************************************************************************

    // Otherwise, call the base class
    return PSS_Symbol::DropItem(pObj, pt);
}

void ZBBPProcedureSymbol::CopySymbolDefinitionFrom(CODSymbolComponent& src)
{
    // Class the base class method
    PSS_Symbol::CopySymbolDefinitionFrom(src);

    if (ISA((&src), ZBBPProcedureSymbol))
    {
        m_CommentRect = dynamic_cast<ZBBPProcedureSymbol&>(src).m_CommentRect;
        m_Combinations = dynamic_cast<ZBBPProcedureSymbol&>(src).m_Combinations;
        m_Combinations.SetParent(this);

        m_SimulationProperties = dynamic_cast<ZBBPProcedureSymbol&>(src).m_SimulationProperties;
        m_UnitProp = dynamic_cast<ZBBPProcedureSymbol&>(src).m_UnitProp;
        m_CostProcedureProp = dynamic_cast<ZBBPProcedureSymbol&>(src).m_CostProcedureProp;

        // JMR-MODIF - Le 26 novembre 2006 - Ajout du code de copie pour les règles.
        m_Rules = dynamic_cast<ZBBPProcedureSymbol&>(src).m_Rules;

        // JMR-MODIF - Le 29 juillet 2007 - Ajout du code de copie pour les risques
        m_Risks = dynamic_cast<ZBBPProcedureSymbol&>(src).m_Risks;

        // Fill the array of unit double validation type
        m_UnitDoubleValidationTypeArray.RemoveAll();
        GetUnitDoubleValidationTypeStringArray(m_UnitDoubleValidationTypeArray);
    }
}

BOOL ZBBPProcedureSymbol::Create(const CString Name /*= ""*/)
{
    m_IsInCreationProcess = true;

    BOOL RetValue = PSS_Symbol::Create(IDR_BP_PROCEDURE,
                                     AfxFindResourceHandle(MAKEINTRESOURCE(IDR_PACKAGE_SYM), _T("Symbol")),
                                     Name);

    if (!CreateSymbolProperties())
    {
        RetValue = FALSE;
    }

    m_IsInCreationProcess = false;

    return RetValue;
}

void ZBBPProcedureSymbol::AdjustElementPosition()
{
    PSS_Symbol::AdjustElementPosition();
}

void ZBBPProcedureSymbol::OnDraw(CDC* pDC)
{
    PSS_Symbol::OnDraw(pDC);
}

BOOL ZBBPProcedureSymbol::OnDoubleClick()
{
    return FALSE;
}

bool ZBBPProcedureSymbol::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    toolTipText.Format(IDS_FS_BPPROCEDURE_TOOLTIP,
        (const char*)GetSymbolName(),
                       (const char*)GetSymbolComment(),
                       (const char*)GetSymbolReferenceNumberStr());

    if (mode == PSS_Symbol::IE_TT_Design)
    {
        // From now do nothing,
        // need to implement the result of the control checking
        // TODO
    }

    return true;
}

void ZBBPProcedureSymbol::Serialize(CArchive& ar)
{
    // Serialize the canvas model.
    PSS_Symbol::Serialize(ar);

    // Only if the object is serialize from and to a document
    if (ar.m_pDocument)
    {
        // Serialize the combinations
        m_Combinations.Serialize(ar);

        m_SimulationProperties.Serialize(ar);

        // JMR-MODIF - Le 10 juin 2007 - Ajout du code pour la sérialisation des risques.
        if (dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 27)
        {
            m_Risks.Serialize(ar);
        }

        // ******************************************************************************************************
        // JMR-MODIF - Le 26 novembre 2006 - Ajout de la sérialisation des règles.
        if (ar.IsStoring())
        {
            m_Rules.Serialize(ar);
        }
        else
        {
            if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 26)
            {
                m_Rules.Serialize(ar);
            }
        }
        // ******************************************************************************************************

        if (ar.IsStoring() ||
            dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 19)
        {
            m_UnitProp.Serialize(ar);
            m_CostProcedureProp.Serialize(ar);
        }
        else
        {
            TRACE(_T("ZBBPProcedureSymbol::Serialize : Start Read\n"));

            // Transfert the properties to new format
            PSS_CostPropertiesProcedureBP_Beta1* pCostProps =
                (PSS_CostPropertiesProcedureBP_Beta1*)GetProperty(ZS_BP_PROP_PROCEDURE_COST);

            if (pCostProps)
            {
                SetMultiplier(pCostProps->GetMultiplier());
                SetProcessingTime(pCostProps->GetProcessingTime());
                SetUnitaryCost(pCostProps->GetUnitaryCost());
            }

            PSS_UnitPropertiesBP_Beta1* pUnitProps = (PSS_UnitPropertiesBP_Beta1*)GetProperty(ZS_BP_PROP_UNIT);

            if (pUnitProps)
            {
                SetUnitName(pUnitProps->GetUnitName());
                SetUnitCost(pUnitProps->GetUnitCost());
            }

            // Sets the master if only one deliverable for the combination
            int Count = GetCombinationCount();

            for (int i = 0; i < Count; ++i)
            {
                CString Deliverables = GetCombinationDeliverables(i);

                // If no separator, then only one deliverable
                // Then sets the master to this deliverable
                if (Deliverables.Find(';') == -1)
                {
                    SetCombinationMaster(i, Deliverables);
                }
            }

            // JMR-MODIF - Le 6 octobre 2005 - Ajout du traçage de fin.
            TRACE(_T("ZBBPProcedureSymbol::Serialize : End Read\n"));
        }
    }
}
