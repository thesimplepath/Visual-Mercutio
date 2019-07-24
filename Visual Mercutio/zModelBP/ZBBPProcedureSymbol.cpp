// ZBBPProcedureSymbol.cpp: implementation of the ZBBPProcedureSymbol class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "zBaseSym\zBaseSymRes.h"
#include "ZBBPProcedureSymbol.h"
#include "ZBDeliverableLinkSymbol.h"

// JMR-MODIF - Le 26 mai 2005 - Définition de _ZMODELEXPORT, pour éviter une erreur interne du compilateur.
#define _ZMODELEXPORT
#include "zModel\ZBBasicProp.h"
#undef _ZMODELEXPORT

#include "ZBBPRuleListProp.h"
#include "ZBBPTaskListProp.h"
#include "ZBBPDecisionListProp.h"
#include "ZBBPCostPropProcedure.h"
#include "ZBBPUnitProp.h"
#include "ZBBPCombinationProp.h"
#include "ZBBPSimPropProcedure.h"

#include "ZVAddRemoveCombinationDeliverableDlg.h"
#include "ZVChooseMasterDeliverable.h"

// Global for zBaseLib
#include "zBaseLib\ZBTokenizer.h"
#include "zBaseLib\ZAGlobal.h"
#include "zBaseLib\ZBToolbarObserverMsg.h"
#include "zBaseLib\MsgBox.h"
#include "zBaseLib\Draw.h"

// Global for model
#include "zModel\ZAModelGlobal.h"
#include "zModel\ZBUserGroupEntity.h"
#include "zModel\ProcGraphModelDoc.h"
#include "zModel\ZVSelectUserGroupDlg.h"
#include "zModel\ZUODSymbolManipulator.h"

// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"
#include "zProperty\ZBPropertyObserverMsg.h"

// JMR-MODIF - Le 25 décembre 2006 - Ajout de l'en-tête ProcGraphModelCtlrBP.h
#include "ProcGraphModelCtlrBP.h"

// JMR-MODIF - Le 13 juin 2007 - Ajout de l'en-tête ZVRiskOptionsDlg.h
#include "ZVRiskOptionsDlg.h"

// Resources
#include "zModelBPRes.h"
#include "zRMdlBP.h"
#include "zModel\zModelRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 6 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Static variables
static CMenu gCombinationMenu;
// JMR-MODIF - Le 28 novembre 2006 - Ajout de la nouvelle variable statique gRulesMenu.
static CMenu gRulesMenu;
// JMR-MODIF - Le 10 juin 2007 - Ajout de la nouvelle variable statique gRiskMenu
static CMenu gRiskMenu;

const size_t _MaxRuleListSize            = 20;
const size_t _MaxTaskListSize            = 20;
const size_t _MaxDecisionListSize        = 20;
const size_t _MaxCombinationListSize    = 20;
// JMR-MODIF - Le 22 novembre 2006 - Ajout de la constante _MaxRulesSize.
const size_t _MaxRulesSize                = 20;
// JMR-MODIF - Le 3 juin 2007 - Ajout de la constante _MaxRisksSize.
const size_t _MaxRisksSize                = 20;

IMPLEMENT_SERIAL(ZBBPProcedureSymbol, ZBSymbol, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBBPProcedureSymbol::ZBBPProcedureSymbol( const CString Name /*= ""*/ )
    : m_Combinations( this )
{
    m_DisplayAttributeArea = true;

    ZBSymbol::SetSymbolName( Name );

    CreateSymbolProperties();
}

ZBBPProcedureSymbol::~ZBBPProcedureSymbol()
{
}

ZBBPProcedureSymbol::ZBBPProcedureSymbol( const ZBBPProcedureSymbol& src )
{
    *this = src;
}

ZBBPProcedureSymbol& ZBBPProcedureSymbol::operator=( const ZBBPProcedureSymbol& src )
{
    // Call the base class assignement operator
    ZBSymbol::operator=( (const ZBSymbol&)src );

    m_Combinations    = src.m_Combinations;

    // JMR-MODIF - Le 26 novembre 2006 - Ajout du code de copie pour les règles
    m_Rules            = src.m_Rules;

    // JMR-MODIF - Le 29 juillet 2007 - Ajout du code de copie pour les risques
    m_Risks        = src.m_Risks;

    return *this;
}

CODComponent* ZBBPProcedureSymbol::Dup() const
{
    return ( new ZBBPProcedureSymbol( *this ) );
}

bool ZBBPProcedureSymbol::AcceptExtApp() const
{
    // RS-MODIF 17.11.04 ExtApp should appear in Conceptor
/*    CODModel * pModel = const_cast<ZBBPProcedureSymbol*>( this )->GetRootModel();

    if ( pModel && ISA( pModel, ZDProcessGraphModelMdl ) &&
         dynamic_cast<ZDProcessGraphModelMdl*>( pModel )->GetUseWorkflow() )
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

    if ( pModel && ISA( pModel, ZDProcessGraphModelMdl ) &&
         dynamic_cast<ZDProcessGraphModelMdl*>( pModel )->GetUseWorkflow() )
    {
        return true;
    }

    return false;
*/
    return true;
}

bool ZBBPProcedureSymbol::OnFillDefaultAttributes( ZBPropertyAttributes* pAttributes )
{
    if ( !pAttributes )
    {
        return false;
    }

    // If global attributes have been defined, then copy them
    if ( ZAModelGlobal::GetGlobalPropertyAttributes( GetObjectTypeID() ).GetAttributeCount() > 0 )
    {
        *pAttributes = ZAModelGlobal::GetGlobalPropertyAttributes( GetObjectTypeID() );
    }
    else
    {
        // Add the reference number
        pAttributes->AddAttribute( ZS_BP_PROP_BASIC, Z_SYMBOL_NUMBER );

        // Add the unit name
        pAttributes->AddAttribute( ZS_BP_PROP_UNIT, Z_UNIT_NAME );

        // No item labels
        pAttributes->SetDisplayTitleText( false );
    }

    return ZBSymbol::OnFillDefaultAttributes( pAttributes );
}

bool ZBBPProcedureSymbol::OnChangeAttributes( ZBPropertyAttributes* pAttributes )
{
    return ZBSymbol::OnChangeAttributes( pAttributes );
}

CString ZBBPProcedureSymbol::GetAttributeString( ZBPropertyAttributes* pAttributes ) const
{
    return ZBSymbol::GetAttributeString( pAttributes );
}

CString ZBBPProcedureSymbol::GetRuleList() const
{
    ZBBPRuleListProperties* pProps = (ZBBPRuleListProperties*)GetProperty( ZS_BP_PROP_RULELIST );

    if ( !pProps )
    {
        return _T( "" );
    }

    return pProps->GetRuleList();
}

void ZBBPProcedureSymbol::SetRuleList( const CString Value )
{
    ZBBPRuleListProperties* pProps = (ZBBPRuleListProperties*)GetProperty( ZS_BP_PROP_RULELIST );

    if ( pProps )
    {
        ZBBPRuleListProperties Props(*pProps);
        Props.SetRuleList( Value );
        SetProperty( &Props );
    }
}

bool ZBBPProcedureSymbol::RuleExist( const CString Value )
{
    ZBTokenizer token( GetRuleList() );    // Initialize the token with the task list
                                        // and with the default ; as separator

    return ( token.TokenExist( Value ) == TRUE ) ? true : false;
}

void ZBBPProcedureSymbol::AddRule( const CString Value )
{
    ZBTokenizer token( GetRuleList() );    // Initialize the token with the task list
                                        // and with the default ; as separator

    // If the new task has been added correctly,
    // then set the new task list
    if ( token.AddUniqueToken( Value ) )
    {
        // Add the value to the history
        CString Key;
        Key.LoadString( IDS_ZS_BP_PROP_RULELST_TITLE );
        ZAGlobal::GetHistoricValueManager().AddHistoryValue( Key, Value );

        // Set the new task string 
        SetRuleList( token.GetString() );
    }
}

void ZBBPProcedureSymbol::RemoveRule( const CString Value )
{
    ZBTokenizer token( GetRuleList() );    // Initialize the token with the task list
                                        // and with the default ; as separator

    // If the new task has been removed correctly,
    // then set the new task list
    if ( token.RemoveToken( Value ) )
    {
        SetRuleList( token.GetString() );
    }
}

CString ZBBPProcedureSymbol::GetRuleAt( size_t Index )
{
    ZBTokenizer token( GetRuleList() );    // Initialize the token with the task list
                                        // and with the default ; as separator
    CString Value;

    // Retreive the specific indexed token
    if ( token.GetTokenAt( Index, Value ) )
    {
        return Value;
    }

    return _T( "" );
}

size_t ZBBPProcedureSymbol::GetRuleCount() const
{
    ZBTokenizer token( GetRuleList() );    // Initialize the token with the task list
                                        // and with the default ; as separator

    return token.GetTokenCount();
}

CString ZBBPProcedureSymbol::GetTaskList() const
{
    ZBBPTaskListProperties* pProps = (ZBBPTaskListProperties*)GetProperty( ZS_BP_PROP_TASKLIST );

    if ( !pProps )
    {
        return _T( "" );
    }

    return pProps->GetTaskList();
}

void ZBBPProcedureSymbol::SetTaskList( const CString Value )
{
    ZBBPTaskListProperties* pProps = (ZBBPTaskListProperties*)GetProperty( ZS_BP_PROP_TASKLIST );

    if ( pProps )
    {
        ZBBPTaskListProperties Props( *pProps );
        Props.SetTaskList( Value );
        SetProperty( &Props );
    }
}

bool ZBBPProcedureSymbol::TaskExist( const CString Value )
{
    ZBTokenizer token( GetTaskList() );    // Initialize the token with the task list
                                        // and with the default ; as separator

    return ( token.TokenExist( Value ) == TRUE ) ? true : false;
}

void ZBBPProcedureSymbol::AddTask( const CString Value )
{
    ZBTokenizer token( GetTaskList() );    // Initialize the token with the task list
                                        // and with the default ; as separator

    // If the new task has been added correctly,
    // then set the new task list
    if ( token.AddUniqueToken( Value ) )
    {
        // Add the value to the history
        CString Key;
        Key.LoadString( IDS_ZS_BP_PROP_PROCEDURE_TSKLST_TITLE );
        ZAGlobal::GetHistoricValueManager().AddHistoryValue( Key, Value );

        // Set the new task string 
        SetTaskList( token.GetString() );
    }
}

void ZBBPProcedureSymbol::RemoveTask( const CString Value )
{
    ZBTokenizer token( GetTaskList() );    // Initialize the token with the task list
                                        // and with the default ; as separator

    // If the new task has been removed correctly,
    // then set the new task list
    if ( token.RemoveToken( Value ) )
    {
        SetTaskList( token.GetString() );
    }
}

CString ZBBPProcedureSymbol::GetTaskAt( size_t Index )
{
    ZBTokenizer token( GetTaskList() );    // Initialize the token with the task list
                                        // and with the default ; as separator

    CString Value;

    // Retreive the specific indexed token
    if ( token.GetTokenAt( Index, Value ) )
    {
        return Value;
    }

    return _T( "" );
}

size_t ZBBPProcedureSymbol::GetTaskCount() const
{
    ZBTokenizer token( GetTaskList() );    // Initialize the token with the task list
                                        // and with the default ; as separator

    return token.GetTokenCount();
}

CString ZBBPProcedureSymbol::GetDecisionList() const
{
    ZBBPDecisionListProperties* pProps = (ZBBPDecisionListProperties*)GetProperty( ZS_BP_PROP_DECISIONLIST );

    if ( !pProps )
    {
        return _T( "" );
    }

    return pProps->GetDecisionList();
}

void ZBBPProcedureSymbol::SetDecisionList( const CString Value )
{
    ZBBPDecisionListProperties* pProps = (ZBBPDecisionListProperties*)GetProperty( ZS_BP_PROP_DECISIONLIST );

    if ( pProps )
    {
        ZBBPDecisionListProperties Props( *pProps );
        Props.SetDecisionList( Value );
        SetProperty( &Props );
    }
}

bool ZBBPProcedureSymbol::DecisionExist( const CString Value )
{
    ZBTokenizer token( GetDecisionList() );    // Initialize the token with the decision list
                                            // and with the default ; as separator

    return ( token.TokenExist( Value ) == TRUE ) ? true : false;
}

void ZBBPProcedureSymbol::AddDecision( const CString Value )
{
    ZBTokenizer token( GetDecisionList() );    // Initialize the token with the decision list
                                            // and with the default ; as separator

    // If the new decision has been added correctly,
    // then set the new decision list
    if ( token.AddUniqueToken( Value ) )
    {
        // Add the value to the history
        CString Key;
        Key.LoadString( IDS_ZS_BP_PROP_PROCEDURE_DECLST_TITLE );
        ZAGlobal::GetHistoricValueManager().AddHistoryValue( Key, Value );

        // Set the new decision string 
        SetDecisionList( token.GetString() );
    }
}

void ZBBPProcedureSymbol::RemoveDecision( const CString Value )
{
    ZBTokenizer token( GetDecisionList() );    // Initialize the token with the decision list
                                            // and with the default ; as separator

    // If the new decision has been removed correctly,
    // then set the new decision list
    if ( token.RemoveToken( Value ) )
    {
        SetDecisionList( token.GetString() );
    }
}

CString ZBBPProcedureSymbol::GetDecisionAt( size_t Index )
{
    ZBTokenizer token( GetDecisionList() );    // Initialize the token with the decision list
                                            // and with the default ; as separator

    CString Value;

    // Retreive the specific indexed token
    if ( token.GetTokenAt( Index, Value ) )
    {
        return Value;
    }

    return _T( "" );
}

size_t ZBBPProcedureSymbol::GetDecisionCount() const
{
    ZBTokenizer token( GetDecisionList() );    // Initialize the token with the decision list
                                            // and with the default ; as separator

    return token.GetTokenCount();
}

// JMR-MODIF - Le 25 décembre 2006 - Permet de rechercher le nom original d'une règle en fonction de son GUID.
CString ZBBPProcedureSymbol::GetRuleNameByGUID( ZBLogicalRulesEntity* p_Rule, CString RuleGUID )
{
    if ( p_Rule == NULL )
    {
        return _T( "" );
    }

    if ( p_Rule->GetGUID() == RuleGUID )
    {
        return p_Rule->GetEntityName();
    }

    if ( p_Rule->ContainEntity() )
    {
        int Count = p_Rule->GetEntityCount();

        for ( int i = 0; i < Count; ++i )
        {
            ZBRulesEntity* pEntity = p_Rule->GetEntityAt( i );

            if ( !pEntity )
            {
                continue;
            }

            if ( ISA( pEntity, ZBLogicalRulesEntity ) )
            {
                CString m_Name = GetRuleNameByGUID( dynamic_cast<ZBLogicalRulesEntity*>( pEntity ), RuleGUID );

                if ( !m_Name.IsEmpty() )
                {
                    return m_Name;
                }
            }
        }
    }

    return _T( "" );
}

void ZBBPProcedureSymbol::OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg )
{
    // Call the base class method
    ZBSymbol::OnUpdate( pSubject, pMsg );
}

void ZBBPProcedureSymbol::OnConnect(CODConnection* pConnection)
{
    ZBSymbol::OnConnect( pConnection );

    CheckInitialCombination();
}

void ZBBPProcedureSymbol::OnDisconnect( CODConnection* pConnection )
{
    ZBSymbol::OnDisconnect( pConnection );

    CheckInitialCombination();
}

void ZBBPProcedureSymbol::OnLinkDisconnect( CODLinkComponent* pLink )
{
    if ( pLink && ISA( pLink, ZBLinkSymbol ) )
    {
        DeleteDeliverableFromAllCombinations( dynamic_cast<ZBLinkSymbol*>( pLink )->GetSymbolName() );
    }
}

BOOL ZBBPProcedureSymbol::OnConnectionMove( CODConnection* pConnection )
{
    return ZBSymbol::OnConnectionMove( pConnection );
}

void ZBBPProcedureSymbol::CheckInitialCombination()
{
    // Now check if only one combination.
    // If it is the case, then set all deliverables to the combination
    if ( GetCombinationCount() == 1 )
    {
        // Get all deliverables
        CString EnteringDeliverables;
        GetEnteringUpDeliverable( EnteringDeliverables );

        // And set it
        SetCombinationDeliverables( 0, EnteringDeliverables );

        // If no entering deliverables, then remove the master
        if ( EnteringDeliverables.IsEmpty() )
        {
            SetCombinationMaster( 0, EnteringDeliverables );
        }
        else
        {
            // If there is only one deliverable
            // then sets automatically the master
            ZBTokenizer token( EnteringDeliverables );

            if ( token.GetTokenCount() == 1 )
            {
                CString Value;

                // Retreive the specific indexed token
                if ( token.GetTokenAt( 0, Value ) )
                {
                    SetCombinationMaster( 0, Value );
                }
            }
        }

        SetCombinationActivationPerc( 0, GetMaxActivationPerc( GetCombinationMaster( 0 ) ) );
    }
}

void ZBBPProcedureSymbol::OnSymbolNameChanged( CODComponent& Comp, const CString OldName )
{
    // Check if the old symbol name was used somewhere in this procedure

    CODComponent* pComp = &Comp;

    // Check the deliverable for combinations
    if ( ISA( pComp, ZBLinkSymbol ) )
    {
        ReplaceDeliverable( OldName, dynamic_cast<ZBLinkSymbol*>( pComp )->GetSymbolName() );
    }
}

// JMR-MODIF - Le 10 juin 2007 - Ajout de la fonction OnAddNewRisk.
void ZBBPProcedureSymbol::OnAddNewRisk( ZBProperty&        Property,
                                        CString&        value,
                                        ZBPropertySet&    Properties,
                                        bool&            Refresh )
{
    // Add a new risk
    if ( AddNewRisk() >= 0 )
    {
        // Sets the refresh flag to true
        Refresh = true;
        SetModifiedFlag( TRUE );
    }
}

// JMR-MODIF - Le 10 juin 2007 - Ajout de la fonction OnDelCurrentRisk.
void ZBBPProcedureSymbol::OnDelCurrentRisk( ZBProperty&        Property,
                                            CString&        value,
                                            ZBPropertySet&    Properties,
                                            bool&            Refresh )
{
    int Count = GetRiskCount();

    if ( Count <= 1 )
    {
        // Cannot delete all risks
        MsgBox mbox;
        mbox.DisplayMsgBox( IDS_CANNOTDELETE_ALLRISKS, MB_OK );
        return;
    }

    // Otherwise, delete the current selected risk
    int Index = Property.GetCategoryID() - ZS_BP_PROP_RISK;

    if ( DeleteRisk( Index ) )
    {
        // Sets the refresh flag to true
        Refresh = true;
        SetModifiedFlag( TRUE );
    }
}

void ZBBPProcedureSymbol::OnAddNewCombination( ZBProperty&        Property,
                                               CString&            value,
                                               ZBPropertySet&    Properties,
                                               bool&            Refresh )
{
    // Add a new combination
    if ( AddNewCombination() >= 0 )
    {
        // Sets the refresh flag to true
        Refresh = true;
        SetModifiedFlag( TRUE );
    }
}

void ZBBPProcedureSymbol::OnDelCurrentCombination( ZBProperty&        Property,
                                                   CString&            value,
                                                   ZBPropertySet&    Properties,
                                                   bool&            Refresh )
{
    int Count = GetCombinationCount();

    if ( Count <= 1 )
    {
        // Cannot delete all combinations
        MsgBox mbox;
        mbox.DisplayMsgBox( IDS_CANNOTDELETE_ALLCOMBINATIONS, MB_OK );
        return;
    }

    // Otherwise, delete the current selected combination
    int Index = Property.GetCategoryID() - ZS_BP_PROP_COMBINATION;

    if ( DeleteCombination( Index ) )
    {
        // Sets the refresh flag to true
        Refresh = true;
        SetModifiedFlag( TRUE );
    }
}

void ZBBPProcedureSymbol::OnAddDeliverableCombination( ZBProperty&        Property,
                                                       CString&            value,
                                                       ZBPropertySet&    Properties,
                                                       bool&            Refresh )
{
}

void ZBBPProcedureSymbol::OnDelDeliverableCombination( ZBProperty&        Property,
                                                       CString&            value,
                                                       ZBPropertySet&    Properties,
                                                       bool&            Refresh )
{
}

bool ZBBPProcedureSymbol::CreateSymbolProperties()
{
    if ( !ZBSymbol::CreateSymbolProperties() )
    {
        return false;
    }

    ZBBPRuleListProperties propRules;
    AddProperty( propRules );

    ZBBPTaskListProperties propTasks;
    AddProperty( propTasks );

    ZBBPDecisionListProperties propDecisions;
    AddProperty( propDecisions );

    ZBBPCostPropertiesProcedure propCost;
    AddProperty( propCost );

    ZBBPUnitProperties propUnit;
    AddProperty( propUnit );

    // Creates at least one combination property
    m_Combinations.CreateInitialProperties();

    // Fill the array of unit double validation type
    m_UnitDoubleValidationTypeArray.RemoveAll();
    GetUnitDoubleValidationTypeStringArray( m_UnitDoubleValidationTypeArray );

    // JMR-MODIF - Le 3 juin 2007 - Ajoute au moins un catalogue de propriétés dans les risques.
    m_Risks.CreateInitialProperties();

    return true;
}

// JMR-MODIF - Le 26 avril 2007 - Cette fonction permet de déterminer si une règle donnée a été attribuée à cet objet.
BOOL ZBBPProcedureSymbol::ContainsRule( CString RuleName )
{
    for ( int i = 0; i < m_Rules.GetRulesCount(); i++ )
    {
        if ( m_Rules.GetRuleName( i ) == RuleName )
        {
            return TRUE;
        }
    }

    return FALSE;
}

// JMR-MODIF - Le 9 octobre 2007 - Cette fonction retourne les règles qui ne sont plus synchronisées avec le référentiel.
void ZBBPProcedureSymbol::CheckRulesSync( CStringArray& RulesList )
{
    CODModel * pModel = GetRootModel();

    if ( pModel == NULL )
    {
        return;
    }

    if ( m_Rules.GetRulesCount() > 0 )
    {
        ZBLogicalRulesEntity* p_MainRule = NULL;

        if ( GetOwnerModel() != NULL && ISA( GetOwnerModel(), ZDProcessGraphModelMdlBP ) )
        {
            ZDProcessGraphModelMdlBP* p_Model = reinterpret_cast<ZDProcessGraphModelMdlBP*>( GetOwnerModel() );

            p_MainRule = p_Model->GetMainLogicalRules();
        }
        else
        {
            return;
        }

        for ( int i = 0; i < m_Rules.GetRulesCount(); i++ )
        {
            CString m_SafeName = GetRuleNameByGUID( p_MainRule, m_Rules.GetRuleGUID( i ) );

            if ( m_SafeName.IsEmpty() )
            {
                RulesList.Add( m_Rules.GetRuleName( i ) );
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
    if (!ZBSymbol::FillProperties(propSet, numericValue, groupValue))
        return false;

    // only local symbol have access to properties
    if (!IsLocal())
        return true;

    // initialize the Currency symbol with the user local currency symbol defined in the Control Panel
    CString currencySymbol = ZAGlobal::GetLocaleCurrency();

    // FIXME translate comment
    // JMR-MODIF - Le 30 juillet 2007 - Mets à jour le symbole monétaire en fonction de la sélection utilisateur.
    if (pModel && ISA(pModel, ZDProcessGraphModelMdl))
    {
        CDocument* pDoc = dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetDocument();

        if (pDoc && ISA(pDoc, ZDProcessGraphModelDoc))
            // retreive the model's currency symbol
            currencySymbol = dynamic_cast<ZDProcessGraphModelDoc*>(pDoc)->GetCurrencySymbol();
    }

    int     count;
    CString finalPropName;
    CString propTitle;
    CString propName;
    CString propDesc;
    bool    groupEnabled = true;

    if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
            !dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->MainUserGroupIsValid())
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
        CString ruleName         = _T("");
        CString ruleDesc         = _T("");

        ruleSectionTitle.LoadString(IDS_Z_RULES_TITLE);
        ruleDesc.LoadString(IDS_Z_RULES_DESC);

        ZBLogicalRulesEntity* pMainRule = NULL;

        if (GetOwnerModel() && ISA(GetOwnerModel(), ZDProcessGraphModelMdlBP))
        {
            ZDProcessGraphModelMdlBP* pOwnerModel = reinterpret_cast<ZDProcessGraphModelMdlBP*>(GetOwnerModel());

            if (pOwnerModel && pOwnerModel->GetController() && ISA(pOwnerModel->GetController(), ZDProcessGraphModelControllerBP))
            {
                ZDProcessGraphModelControllerBP* pController =
                        reinterpret_cast<ZDProcessGraphModelControllerBP*>(pOwnerModel->GetController());

                if (pController && ISA(pController->GetDocument(), ZDProcessGraphModelDoc))
                {
                    ZDProcessGraphModelDoc* pDocument =
                            reinterpret_cast<ZDProcessGraphModelDoc*>(pController->GetDocument());

                    if (pDocument && pDocument->GetMainLogicalRules())
                        pMainRule = pDocument->GetMainLogicalRules();
                }
            }
        }

        for (int i = 0; i < m_Rules.GetRulesCount(); ++i)
        {
            // FIXME translate comments
            // Le contrôle des règles ne peut être appliqué que si le modèle est en phase avec le système des règles.
            if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
                    dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->MainLogicalRulesIsValid())
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
                                               m_Rules.GetRuleName( i ),
                                               ZBProperty::PT_EDIT_MENU,
                                               true,
                                               ZBStringFormat(ZBStringFormat::General),
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

    if ((pRulesProps = (ZBBPRuleListProperties*)GetProperty( ZS_BP_PROP_RULELIST)) == NULL)
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
    CStringArray* pArrayOfValues = ZAGlobal::GetHistoricValueManager().GetFieldHistory(propTitle);

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
                                               ZBStringFormat(ZBStringFormat::General),
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
                                               ZBStringFormat(ZBStringFormat::General),
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

    CString finalRiskName  = _T("");
    CString finalRiskTitle = _T("");
    CString riskTitle      = _T("");
    CString riskName       = _T("");
    CString riskDesc       = _T("");

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
                                           (groupValue? Z_RISK_NAME : (Z_RISK_NAME + (i * _MaxRisksSize))),
                                           riskDesc,
                                           GetRiskName(i),
                                           ZBProperty::PT_EDIT_MENU,
                                           true,
                                           ZBStringFormat(ZBStringFormat::General),
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
                               (groupValue ? Z_RISK_DESC : (Z_RISK_DESC + (i * _MaxRisksSize))),
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
                               (groupValue ? Z_RISK_TYPE : (Z_RISK_TYPE + (i * _MaxRisksSize))),
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
                               (groupValue ? Z_RISK_IMPACT : (Z_RISK_IMPACT + (i * _MaxRisksSize))),
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
                               (groupValue ? Z_RISK_PROBABILITY : (Z_RISK_PROBABILITY + (i * _MaxRisksSize))),
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
                               (groupValue ? Z_RISK_SEVERITY : (Z_RISK_SEVERITY + (i * _MaxRisksSize))),
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
                               (groupValue ? Z_RISK_UE : (Z_RISK_UE + (i * _MaxRisksSize))),
                               riskDesc,
                               GetRiskUE(i),
                               ZBProperty::PT_EDIT_NUMBER,
                               true,
                               ZBStringFormat(ZBStringFormat::Currency, true, 2, currencySymbol));

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_POA_NAME);
        riskDesc.LoadString(IDS_Z_RISK_POA_DESC);

        // FIXME translate comments
        // Propriété "POA" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
                               (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? Z_RISK_POA : (Z_RISK_POA + (i * _MaxRisksSize))),
                               riskDesc,
                               GetRiskPOA(i),
                               ZBProperty::PT_EDIT_NUMBER,
                               true,
                               ZBStringFormat(ZBStringFormat::Currency, true, 2, currencySymbol));

        propSet.Add(pRisk);

        riskName.LoadString(IDS_Z_RISK_ACTION_NAME);
        riskDesc.LoadString(IDS_Z_RISK_ACTION_DESC);

        // FIXME translate comments
        // Propriété "Action" du groupe "Risque (x)"
        pRisk = new ZBProperty(finalRiskTitle,
                               (groupValue ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i)),
                               riskName,
                               (groupValue ? Z_RISK_ACTION : (Z_RISK_ACTION + (i * _MaxRisksSize))),
                               riskDesc,
                               (GetRiskAction(i) ? ZAGlobal::GetYesFromArrayYesNo() : ZAGlobal::GetNoFromArrayYesNo()),
                               ZBProperty::PT_COMBO_STRING_READONLY,
                               TRUE,
                               ZBStringFormat(ZBStringFormat::General),
                               ZAGlobal::GetArrayYesNo());

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
    pArrayOfValues = ZAGlobal::GetHistoricValueManager().GetFieldHistory(propTitle);

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
                                               ZBStringFormat(ZBStringFormat::General),
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
                                               ZBStringFormat(ZBStringFormat::General),
                                               pArrayOfValues);

        pTaskList->EnableDragNDrop();
        propSet.Add(pTaskList);
    }

    // add decisions
    ZBBPDecisionListProperties* pDecisionsProps = (ZBBPDecisionListProperties*)GetProperty(ZS_BP_PROP_DECISIONLIST);

    if (!pDecisionsProps)
        return false;

    // run through all tasks properties, add one to the counter to have always one empty decision
    count = GetDecisionCount() + 1;
    propTitle.LoadString(IDS_ZS_BP_PROP_PROCEDURE_DECLST_TITLE);
    pArrayOfValues = ZAGlobal::GetHistoricValueManager().GetFieldHistory(propTitle);

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
                                              Z_DECISION_LIST + (i * _MaxDecisionListSize),
                                              propDesc,
                                              GetDecisionAt(i),
                                              ZBProperty::PT_EDIT_INTELI,
                                              true, // Enable
                                              ZBStringFormat(ZBStringFormat::General),
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
                                              Z_DECISION_LIST + (i * _MaxDecisionListSize),
                                              propDesc,
                                              _T(""),
                                              ZBProperty::PT_EDIT_INTELI,
                                              false, // Disable
                                              ZBStringFormat(ZBStringFormat::General),
                                              pArrayOfValues);

        pDecList->EnableDragNDrop();
        propSet.Add(pDecList);
    }

    int hourPerDay  = -1;
    int dayPerWeek  = -1;
    int dayPerMonth = -1;
    int dayPerYear  = -1;

    if (pModel && ISA(pModel, ZDProcessGraphModelMdl))
    {
        CDocument* pDoc = dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetDocument();

        if (pDoc && ISA(pDoc, ZDProcessGraphModelDoc))
        {
            // FIXME translate comments
            // JMR-MODIF - Le 30 juillet 2007 - Cette opération est effectuée une fois pour toutes au début de la fonction.
            // Retreive the model's currency symbol
            //CurrencySymbol = dynamic_cast<ZDProcessGraphModelDoc*>( pDoc )->GetCurrencySymbol();

            // retreive the standard time definition
            hourPerDay  = dynamic_cast<ZDProcessGraphModelDoc*>(pDoc)->GetHourPerDay();
            dayPerWeek  = dynamic_cast<ZDProcessGraphModelDoc*>(pDoc)->GetDayPerWeek();
            dayPerMonth = dynamic_cast<ZDProcessGraphModelDoc*>(pDoc)->GetDayPerMonth();
            dayPerYear  = dynamic_cast<ZDProcessGraphModelDoc*>(pDoc)->GetDayPerYear();
        }
    }

    // RS-MODIF 17.11.04 error has to be defined here
    bool error;
        
    if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
            dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())
    {
        // FIXME translate comments
        // Propriété "Multiplicateur" du groupe "Procédure"
        ZBProperty* pMultiplier = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                                 ZS_BP_PROP_PROCEDURE_COST,
                                                 IDS_Z_COST_MULTIPLIER_NAME,
                                                 Z_COST_MULTIPLIER,
                                                 IDS_Z_COST_MULTIPLIER_DESC,
                                                 GetMultiplier(),
                                                 ZBProperty::PT_EDIT_NUMBER,
                                                 true,
                                                 ZBStringFormat(ZBStringFormat::Accounting, true, -1));

        propSet.Add(pMultiplier);

        ZBProperty* pTime;

        if (numericValue)
            // FIXME translate comments
            // Propriété "Temps standard" du groupe "Procédure"
            pTime = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                   ZS_BP_PROP_PROCEDURE_COST,
                                   IDS_Z_COST_PROCESSING_TIME_NAME,
                                   Z_COST_PROCESSING_TIME,
                                   IDS_Z_COST_PROCESSING_TIME_DESC,
                                   GetProcessingTime(),
                                   ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "Temps standard" du groupe "Procédure"
            pTime = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                   ZS_BP_PROP_PROCEDURE_COST,
                                   IDS_Z_COST_PROCESSING_TIME_NAME,
                                   Z_COST_PROCESSING_TIME,
                                   IDS_Z_COST_PROCESSING_TIME_DESC,
                                   ZBDuration(GetProcessingTime(),
                                              hourPerDay,
                                              dayPerWeek,
                                              dayPerMonth,
                                              dayPerYear),
                                   ZBProperty::PT_EDIT_DURATION,
                                   true,
                                   ZBStringFormat(ZBStringFormat::Duration7));

        propSet.Add(pTime);

        // FIXME translate comments
        // Propriété "Coût unitaire" du groupe "Procédure"
        ZBProperty* pPrice = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                            ZS_BP_PROP_PROCEDURE_COST,
                                            IDS_Z_COST_UNITARY_COST_NAME,
                                            Z_COST_UNITARY_COST,
                                            IDS_Z_COST_UNITARY_COST_DESC,
                                            GetUnitaryCost(),
                                            ZBProperty::PT_EDIT_NUMBER,
                                            true,
                                            ZBStringFormat(ZBStringFormat::Currency, true, 2, currencySymbol));

        propSet.Add(pPrice);

        ZBProperty* pProcessingDuration;

        if (numericValue)
            // FIXME translate comments
            // Propriété "Durée moyenne (pondérée)" du groupe "Procédure"
            pProcessingDuration = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                                 ZS_BP_PROP_PROCEDURE_COST,
                                                 IDS_Z_COST_PROCESSING_DURATION_NAME,
                                                 Z_COST_PROCESSING_DURATION,
                                                 IDS_Z_COST_PROCESSING_DURATION_DESC,
                                                 GetProcessingDuration(),
                                                 ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "Durée moyenne (pondérée)" du groupe "Procédure"
            pProcessingDuration = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                                 ZS_BP_PROP_PROCEDURE_COST,
                                                 IDS_Z_COST_PROCESSING_DURATION_NAME,
                                                 Z_COST_PROCESSING_DURATION,
                                                 IDS_Z_COST_PROCESSING_DURATION_DESC,
                                                 ZBDuration(GetProcessingDuration(),
                                                            hourPerDay,
                                                            dayPerWeek,
                                                            dayPerMonth,
                                                            dayPerYear),
                                                 ZBProperty::PT_EDIT_DURATION_READONLY,
                                                 true,
                                                 ZBStringFormat(ZBStringFormat::Duration7));

        propSet.Add(pProcessingDuration);

        ZBProperty* pProcessingDurationMax;

        if (numericValue)
            // FIXME translate comments
            // Propriété "Durée moyenne (maximum)" du groupe "Procédure"
            pProcessingDurationMax = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                                    ZS_BP_PROP_PROCEDURE_COST,
                                                    IDS_Z_COST_PROCESSING_DURATIONMAX_NAME,
                                                    Z_COST_PROCESSING_DURATIONMAX,
                                                    IDS_Z_COST_PROCESSING_DURATIONMAX_DESC,
                                                    GetProcessingDurationMax(),
                                                    ZBProperty::PT_EDIT_NUMBER);
        else
            // FIXME translate comments
            // Propriété "Durée moyenne (maximum)" du groupe "Procédure"
            pProcessingDurationMax = new ZBProperty(IDS_ZS_BP_PROP_PROCEDURE_TITLE,
                                                    ZS_BP_PROP_PROCEDURE_COST,
                                                    IDS_Z_COST_PROCESSING_DURATIONMAX_NAME,
                                                    Z_COST_PROCESSING_DURATIONMAX,
                                                    IDS_Z_COST_PROCESSING_DURATIONMAX_DESC,
                                                    ZBDuration(GetProcessingDurationMax(),
                                                               hourPerDay,
                                                               dayPerWeek,
                                                               dayPerMonth,
                                                               dayPerYear),
                                                    ZBProperty::PT_EDIT_DURATION_READONLY,
                                                    true,
                                                    ZBStringFormat(ZBStringFormat::Duration7));

        propSet.Add(pProcessingDurationMax);

        const float unitCost = RetreiveUnitCost(GetUnitGUID(), error);

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
                                               ZBStringFormat(ZBStringFormat::Currency, true, 2, currencySymbol));

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
                                              ZBStringFormat(ZBStringFormat::General));
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
                                              ZBStringFormat(ZBStringFormat::General),
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

    const CString unitName = RetreiveUnitName(GetUnitGUID(), error);

    // Propriété "Unité" du groupe "Unité de traitement"
    ZBProperty* pUnitName = new ZBProperty( IDS_ZS_BP_PROP_UNIT_TITLE,
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
    if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
            dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())
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
                                                      (groupValue? ZS_BP_PROP_COMBINATION : (ZS_BP_PROP_COMBINATION + i)),
                                                      propName,
                                                      (groupValue ? Z_COMBINATION_NAME : (Z_COMBINATION_NAME + (i * _MaxCombinationListSize))),
                                                      propDesc,
                                                      GetCombinationName(i),
                                                      ZBProperty::PT_EDIT_MENU,
                                                      true,
                                                      ZBStringFormat(ZBStringFormat::General),
                                                      NULL,
                                                      &gCombinationMenu);

            propSet.Add(pCombination);

            propName.LoadString(IDS_Z_COMBINATION_DELIVERABLES_NAME);
            propDesc.LoadString(IDS_Z_COMBINATION_DELIVERABLES_DESC);

            // FIXME translate comments
            // Propriété "Livrables" du groupe "Combinaisons x"
            pCombination = new ZBProperty(finalPropTitle,
                                          (groupValue? ZS_BP_PROP_COMBINATION : (ZS_BP_PROP_COMBINATION + i)),
                                          propName,
                                          (groupValue? Z_COMBINATION_DELIVERABLES : (Z_COMBINATION_DELIVERABLES + (i * _MaxCombinationListSize))),
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
                                          (groupValue? ZS_BP_PROP_COMBINATION : (ZS_BP_PROP_COMBINATION + i)),
                                          propName,
                                          (groupValue? Z_COMBINATION_ACTIVATION_PERC : (Z_COMBINATION_ACTIVATION_PERC + (i * _MaxCombinationListSize))),
                                          propDesc,
                                          maxPercent,
                                          ZBProperty::PT_EDIT_NUMBER_READONLY,
                                          true,
                                          ZBStringFormat(ZBStringFormat::Percentage));

            propSet.Add(pCombination);

            propName.LoadString(IDS_Z_COMBINATION_MASTER_NAME);
            propDesc.LoadString(IDS_Z_COMBINATION_MASTER_DESC);

            // FIXME translate comments
            // Propriété "Maître" du groupe "Combinaisons x"
            pCombination = new ZBProperty(finalPropTitle,
                                          (groupValue ? ZS_BP_PROP_COMBINATION : (ZS_BP_PROP_COMBINATION + i)),
                                          propName,
                                          (groupValue ? Z_COMBINATION_MASTER : (Z_COMBINATION_MASTER + (i * _MaxCombinationListSize))),
                                          propDesc,
                                          GetCombinationMaster(i),
                                          ZBProperty::PT_EDIT_EXTENDED_READONLY);

            propSet.Add(pCombination);
        }
    }

    if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
            dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())
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
                                              ZBStringFormat(ZBStringFormat::Accounting, true, 0));

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
                                  ZBStringFormat( ZBStringFormat::Currency, true, 2, currencySymbol));

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
                                      ZBDuration(double(GetProcedureWorkloadForecast()),
                                                 hourPerDay,
                                                 dayPerWeek,
                                                 dayPerMonth,
                                                 dayPerYear),
                                      ZBProperty::PT_EDIT_DURATION_READONLY,
                                      true,
                                      ZBStringFormat(ZBStringFormat::Duration7));

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
                                  ZBStringFormat(ZBStringFormat::Currency, true, 2, currencySymbol));

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
                                      ZBDuration(double(GetProcedureWorkloadPerActivity()),
                                                 hourPerDay,
                                                 dayPerWeek,
                                                 dayPerMonth,
                                                 dayPerYear),
                                      ZBProperty::PT_EDIT_DURATION_READONLY,
                                      true,
                                      ZBStringFormat(ZBStringFormat::Duration7));

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
                                  ZBStringFormat(ZBStringFormat::Currency, true, 2, currencySymbol));

        propSet.Add(pSimProp);
    }

    return true;
}
//---------------------------------------------------------------------------
bool ZBBPProcedureSymbol::SaveProperties( ZBPropertySet& PropSet )
{
    if ( !ZBSymbol::SaveProperties( PropSet ) )
    {
        return false;
    }

    // Only local symbol have access to properties
    if ( !IsLocal() )
    {
        return true;
    }

    ZBProperty* pProp;

    // Save the rules
    ZBBPRuleListProperties* pRulesProps = (ZBBPRuleListProperties*)GetProperty( ZS_BP_PROP_RULELIST );

    if ( !pRulesProps )
    {
        return false;
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator f( &PropSet );

    // Empty the task list
    SetRuleList( _T( "" ) );

    for ( pProp = f.GetFirst(); pProp; pProp = f.GetNext() )
    {
        if ( pProp->GetCategoryID() == ZS_BP_PROP_RULELIST )
        {
            switch ( pProp->GetPTValueType() )
            {
                case ZBProperty::PT_STRING:
                {
                    // If not empty, add this new task
                    if ( !pProp->GetValueString().IsEmpty() )
                    {
                        AddRule( pProp->GetValueString() );
                    }

                    break;
                }
            }
        }
    }

    // *************************************************************************************************************
    // JMR-MODIF - Le 11 juillet 2007 - Ajout du code pour la mise à jour des valeurs des risques.

    ZBPropertyIterator h( &PropSet );

    for ( pProp = h.GetFirst(); pProp; pProp = h.GetNext() )
    {
        if ( pProp->GetCategoryID() >= ZS_BP_PROP_RISK &&
             pProp->GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount() )
        {
            int i = pProp->GetCategoryID() - ZS_BP_PROP_RISK;

            if ( pProp->GetItemID() == Z_RISK_NAME + ( i * _MaxRisksSize ) )
            {
                SetRiskName( i, pProp->GetValueString() );
            }

            if ( pProp->GetItemID() == Z_RISK_DESC + ( i * _MaxRisksSize ) )
            {
                SetRiskDesc( i, pProp->GetValueString() );
            }

            if ( pProp->GetItemID() == Z_RISK_UE + ( i * _MaxRisksSize ) )
            {
                SetRiskUE( i, pProp->GetValueFloat() );
            }

            if ( pProp->GetItemID() == Z_RISK_POA + ( i * _MaxRisksSize ) )
            {
                SetRiskPOA( i, pProp->GetValueFloat() );
            }

            if ( pProp->GetItemID() == Z_RISK_ACTION + ( i * _MaxRisksSize ) )
            {
                SetRiskAction( i, ( pProp->GetValueString() == ZAGlobal::GetYesFromArrayYesNo() ? 1 : 0 ) );
            }
        }
    }
    // *************************************************************************************************************

    // Save the tasks
    ZBBPTaskListProperties* pTasksProps = (ZBBPTaskListProperties*)GetProperty( ZS_BP_PROP_TASKLIST );

    if ( !pTasksProps )
    {
        return false;
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator i( &PropSet );

    // Empty the task list
    SetTaskList( _T( "" ) );

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->GetCategoryID() == ZS_BP_PROP_TASKLIST )
        {
            switch ( pProp->GetPTValueType() )
            {
                case ZBProperty::PT_STRING:
                {
                    // If not empty, add this new task
                    if ( !pProp->GetValueString().IsEmpty() )
                    {
                        AddTask( pProp->GetValueString() );
                    }

                    break;
                }
            }
        }
    }

    // Because using the AddTask function, not necessary to SetProperty
    // Save the decisions
    ZBBPDecisionListProperties* pDecisionsProps = (ZBBPDecisionListProperties*)GetProperty( ZS_BP_PROP_DECISIONLIST );

    if ( !pDecisionsProps )
    {
        return false;
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator p( &PropSet );

    // Empty the decision list
    SetDecisionList( _T( "" ) );

    for ( pProp = p.GetFirst(); pProp; pProp = p.GetNext() )
    {
        if ( pProp->GetCategoryID() == ZS_BP_PROP_DECISIONLIST )
        {
            switch ( pProp->GetPTValueType() )
            {
                case ZBProperty::PT_STRING:
                {
                    // If not empty, add this new decision
                    if ( !pProp->GetValueString().IsEmpty() )
                    {
                        AddDecision( pProp->GetValueString() );
                    }

                    break;
                }
            }
        }
    }

    // Because using the AddDecision function, not necessary to SetProperty
    // Now run through the list of data and fill the property set
    ZBPropertyIterator j( &PropSet );

    for ( pProp = j.GetFirst(); pProp; pProp = j.GetNext() )
    {
        if ( pProp->GetCategoryID() == ZS_BP_PROP_PROCEDURE_COST )
        {
            switch ( pProp->GetPTValueType() )
            {
                case ZBProperty::PT_STRING:
                {
                    m_CostProcedureProp.SetValue( pProp->GetItemID(), pProp->GetValueString() );
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    m_CostProcedureProp.SetValue( pProp->GetItemID(),
                                                  static_cast<float>( pProp->GetValueDouble() ) );
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    m_CostProcedureProp.SetValue( pProp->GetItemID(), pProp->GetValueFloat() );
                    break;

                }
                case ZBProperty::PT_DATE:
                {
                    m_CostProcedureProp.SetValue( pProp->GetItemID(),
                                                  static_cast<float>( (DATE)pProp->GetValueDate() ) );
                    break;
                }

                case ZBProperty::PT_TIMESPAN:
                {
                    m_CostProcedureProp.SetValue( pProp->GetItemID(),
                                                  (double)pProp->GetValueTimeSpan() );
                    break;
                }

                case ZBProperty::PT_DURATION:
                {
                    m_CostProcedureProp.SetValue( pProp->GetItemID(),
                                                  (double)pProp->GetValueDuration() );
                    break;
                }
            }
        }
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator k( &PropSet );

    for ( pProp = k.GetFirst(); pProp; pProp = k.GetNext() )
    {
        if ( pProp->GetCategoryID() == ZS_BP_PROP_UNIT )
        {
            // Check if a flag
            if ( pProp->GetItemID() == Z_UNIT_DOUBLE_VALIDATION )
            {
                m_UnitProp.SetValue( pProp->GetItemID(),
                                     ConvertUnitDoubleValidationString2Type( pProp->GetValueString() ) );
            }
            else
            {
                switch ( pProp->GetPTValueType() )
                {
                    case ZBProperty::PT_DOUBLE:
                    {
                        m_UnitProp.SetValue( pProp->GetItemID(), static_cast<float>( pProp->GetValueDouble() ) );
                        break;
                    }

                    case ZBProperty::PT_FLOAT:
                    {
                        m_UnitProp.SetValue( pProp->GetItemID(), pProp->GetValueFloat() );
                        break;
                    }

                    case ZBProperty::PT_STRING:
                    {
                        m_UnitProp.SetValue( pProp->GetItemID(), pProp->GetValueString() );
                        break;
                    }
                }
            }
        }
    }

    // Now run through the list of data and fill the property set of combination
    ZBPropertyIterator l( &PropSet );

    for ( pProp = l.GetFirst(); pProp; pProp = l.GetNext() )
    {
        if ( pProp->GetCategoryID() >= ZS_BP_PROP_COMBINATION &&
             pProp->GetCategoryID() <= ZS_BP_PROP_COMBINATION + GetCombinationCount() )
        {
            int i = pProp->GetCategoryID() - ZS_BP_PROP_COMBINATION;
            ZBBPCombinationProperties* pCombProps = GetCombinationProperty( i );

            if ( !pCombProps )
            {
                return false;
            }

            switch ( pProp->GetPTValueType() )
            {
                case ZBProperty::PT_STRING:
                {
                    pCombProps->SetValue( pProp->GetItemID() - ( i * _MaxCombinationListSize ),
                                          pProp->GetValueString() );
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    pCombProps->SetValue( pProp->GetItemID() - ( i * _MaxCombinationListSize ),
                                          static_cast<float>( pProp->GetValueDouble() ) );
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    pCombProps->SetValue( pProp->GetItemID() - ( i * _MaxCombinationListSize ),
                                          pProp->GetValueFloat() );
                    break;
                }

                case ZBProperty::PT_DATE:
                {
                    pCombProps->SetValue( pProp->GetItemID() - ( i * _MaxCombinationListSize ),
                                          static_cast<float>((DATE)pProp->GetValueDate()) );
                    break;
                }

                case ZBProperty::PT_TIMESPAN:
                {
                    ASSERT( FALSE );
                    break;
                }

                case ZBProperty::PT_DURATION:
                {
                    ASSERT( FALSE );
                    break;
                }
            }
        }
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator m( &PropSet );

    for ( pProp = m.GetFirst(); pProp; pProp = m.GetNext() )
    {
        if ( pProp->GetCategoryID() == ZS_BP_PROP_SIM_PROCEDURE )
        {
            switch ( pProp->GetPTValueType() )
            {
                case ZBProperty::PT_STRING:
                {
                    m_SimulationProperties.SetValue( pProp->GetItemID(), pProp->GetValueString() );
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    m_SimulationProperties.SetValue( pProp->GetItemID(), pProp->GetValueDouble() );
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    m_SimulationProperties.SetValue( pProp->GetItemID(), pProp->GetValueFloat() );
                    break;
                }

                case ZBProperty::PT_DATE:
                {
                    m_SimulationProperties.SetValue( pProp->GetItemID(),
                                                     static_cast<float>( (DATE)pProp->GetValueDate() ) );
                    break;
                }

                case ZBProperty::PT_TIMESPAN:
                {
                    m_SimulationProperties.SetValue( pProp->GetItemID(), (double)pProp->GetValueTimeSpan() );
                    break;
                }

                case ZBProperty::PT_DURATION:
                {
                    m_SimulationProperties.SetValue( pProp->GetItemID(), (double)pProp->GetValueDuration() );
                    break;
                }
            }
        }
    }

    RefreshAttributeAreaText( true );

    return true;
}

bool ZBBPProcedureSymbol::SaveProperty( ZBProperty& Property )
{
    if ( !ZBSymbol::SaveProperty( Property ) )
    {
        return false;
    }

    // Only local symbol have access to properties
    if ( !IsLocal() )
    {
        return true;
    }

    // ************************************************************************************************
    // JMR-MODIF - Le 17 juillet 2007 - Mise à jour des valeurs des propriétés des risques.

    if ( Property.GetCategoryID() >= ZS_BP_PROP_RISK &&
         Property.GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount() )
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_RISK;

        if ( Property.GetItemID() == Z_RISK_NAME + ( i * _MaxRisksSize ) )
        {
            SetRiskName( i, Property.GetValueString() );
        }

        if ( Property.GetItemID() == Z_RISK_DESC + ( i * _MaxRisksSize ) )
        {
            SetRiskDesc( i, Property.GetValueString() );
        }

        if ( Property.GetItemID() == Z_RISK_UE + ( i * _MaxRisksSize ) )
        {
            SetRiskUE( i, Property.GetValueFloat() );
        }

        if ( Property.GetItemID() == Z_RISK_POA + ( i * _MaxRisksSize ) )
        {
            SetRiskPOA( i, Property.GetValueFloat() );
        }

        if ( Property.GetItemID() == Z_RISK_ACTION + ( i * _MaxRisksSize ) )
        {
            SetRiskAction( i, ( Property.GetValueString() == ZAGlobal::GetYesFromArrayYesNo() ? 1 : 0 ) );
        }
    }
    // ************************************************************************************************

    // JMR-MODIF - Le 9 mai 2007 - Contrôle si l'utilisateur a tenté de renommer une règle.
    // Si c'est le cas, réetablit le nom d'origine.
    if ( Property.GetCategoryID() == ZS_BP_PROP_RULES )
    {
        int Index = ( Property.GetItemID() - Z_RULE_NAME ) / _MaxRulesSize;

        if ( m_Rules.GetRuleName( Index ) != Property.GetValueString() )
        {
            Property.SetValueString( m_Rules.GetRuleName( Index ) );
        }
    }

    if ( Property.GetCategoryID() >= ZS_BP_PROP_COMBINATION &&
         Property.GetCategoryID() <= ZS_BP_PROP_COMBINATION + GetCombinationCount() )
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_COMBINATION;

        switch( Property.GetItemID() - ( i * _MaxCombinationListSize ) )
        {
            case Z_COMBINATION_NAME:
            {
                SetCombinationName( Property.GetCategoryID() - ZS_BP_PROP_COMBINATION,
                                    Property.GetValueString() );
                break;
            }

            case Z_COMBINATION_DELIVERABLES:
            {
                SetCombinationDeliverables( Property.GetCategoryID() - ZS_BP_PROP_COMBINATION,
                                            Property.GetValueString() );
                break;
            }

            case Z_COMBINATION_ACTIVATION_PERC:
            {
                SetCombinationActivationPerc( Property.GetCategoryID() - ZS_BP_PROP_COMBINATION,
                                              Property.GetValueFloat() );
                break;
            }

            case Z_COMBINATION_MASTER:
            {
                SetCombinationMaster( Property.GetCategoryID() - ZS_BP_PROP_COMBINATION,
                                      Property.GetValueString() );
                break;
            }
        }
    }

    if ( Property.GetCategoryID() == ZS_BP_PROP_RULELIST )
    {
        // If not empty, add this new rule
        if ( !Property.GetValueString().IsEmpty() )
        {
            AddRule( Property.GetValueString() );
        }
    }

    if ( Property.GetCategoryID() == ZS_BP_PROP_TASKLIST )
    {
        // If not empty, add this new task
        if ( !Property.GetValueString().IsEmpty() )
        {
            AddTask( Property.GetValueString() );
        }
    }

    if ( Property.GetCategoryID() == ZS_BP_PROP_DECISIONLIST )
    {
        // If not empty, add this new task
        if ( !Property.GetValueString().IsEmpty() )
        {
            AddDecision( Property.GetValueString() );
        }
    }

    // Set the modified flag to true,
    // Do nothing more, the values will be saved by the save properties method
    SetModifiedFlag();

    return true;
}

bool ZBBPProcedureSymbol::CheckPropertyValue( ZBProperty& Property, CString& value, ZBPropertySet& Properties )
{
    return ZBSymbol::CheckPropertyValue( Property, value, Properties );
}

bool ZBBPProcedureSymbol::ProcessExtendedInput( ZBProperty&        Property,
                                                CString&        value,
                                                ZBPropertySet&    Properties,
                                                bool&            Refresh )
{
    // ****************************************************************************************************
    // JMR-MODIF - Le 13 juin 2007 - Ajout de la prise en charge des risques.

    if ( Property.GetCategoryID() >= ZS_BP_PROP_RISK &&
         Property.GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount() )
    {
        int            i                = Property.GetCategoryID() - ZS_BP_PROP_RISK;
        CODModel*    pModel            = GetRootModel();
        CString        CurrencySymbol    = ZAGlobal::GetLocaleCurrency();

        if ( pModel && ISA( pModel, ZDProcessGraphModelMdl ) )
        {
            CDocument* pDoc = dynamic_cast<ZDProcessGraphModelMdl*>( pModel )->GetDocument();

            if ( pDoc && ISA( pDoc, ZDProcessGraphModelDoc ) )
            {
                // Retreive the model's currency symbol
                CurrencySymbol = dynamic_cast<ZDProcessGraphModelDoc*>( pDoc )->GetCurrencySymbol();
            }
        }

        CString s_NoRiskType = _T( "" );
        s_NoRiskType.LoadString( IDS_NO_RISK_TYPE );

        ZVRiskOptionsDlg m_RiskOptions( GetRiskName( i ),
                                        GetRiskDesc( i ),
                                        ( GetRiskType( i ).IsEmpty() ) ? s_NoRiskType : GetRiskType( i ),
                                        GetRiskImpact( i ),
                                        GetRiskProbability( i ),
                                        GetRiskUE( i ),
                                        GetRiskPOA( i ),
                                        GetRiskAction( i ),
                                        CurrencySymbol );

        if ( m_RiskOptions.DoModal() == IDOK )
        {
            SetRiskName( i, m_RiskOptions.GetRiskTitle() );
            SetRiskDesc( i, m_RiskOptions.GetRiskDescription() );
            SetRiskType( i, m_RiskOptions.GetRiskType() );
            SetRiskImpact( i, m_RiskOptions.GetRiskImpact() );
            SetRiskProbability( i, m_RiskOptions.GetRiskProbability() );
            SetRiskSeverity( i, m_RiskOptions.GetRiskSeverity() );
            SetRiskUE( i, m_RiskOptions.GetRiskUE() );
            SetRiskPOA( i, m_RiskOptions.GetRiskPOA() );
            SetRiskAction( i, m_RiskOptions.GetRiskAction() );

            SetModifiedFlag( TRUE );

            Refresh = true;

            return true;
        }
    }
    // ****************************************************************************************************

    CODModel * pModel = GetOwnerModel();

    if ( Property.GetCategoryID() == ZS_BP_PROP_UNIT && Property.GetItemID() == Z_UNIT_NAME )
    {
        if ( pModel && ISA( pModel, ZDProcessGraphModelMdl ) )
        {
            ZVSelectUserGroupDlg dlg( IDS_SELECTAGROUP_T,
                                      dynamic_cast<ZDProcessGraphModelMdl*>( pModel )->GetMainUserGroup(),
                                      true,    // Allow group selection
                                      false ); // Doesn't allow role selection

            if ( dlg.DoModal() == IDOK )
            {
                ZBUserEntity* pUserEntity = dlg.GetSelectedUserEntity();

                if ( pUserEntity )
                {
                    value = pUserEntity->GetEntityName();

                    // And change the unit GUID of the disable property
                    ZBPropertyIterator i( &Properties );
                    ZBProperty* pProp;

                    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
                    {
                        if ( pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == Z_UNIT_GUID )
                        {
                            pProp->SetValueString( pUserEntity->GetGUID() );
                            break;
                        }
                    }

                    return true;
                }
            }
        }
    }
    else if ( Property.GetCategoryID() >= ZS_BP_PROP_COMBINATION &&
              Property.GetCategoryID() <= ZS_BP_PROP_COMBINATION + GetCombinationCount() )
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_COMBINATION;

        switch( Property.GetItemID() - ( i * _MaxCombinationListSize ) )
        {
            case Z_COMBINATION_DELIVERABLES:
            {
                // Get the deliverables
                CString EnteringDeliverables;
                GetEnteringUpDeliverable( EnteringDeliverables );
                CString AvailableDeliverables = GetAvailableDeliverables( EnteringDeliverables );

                // Call the dialog
                ZVAddRemoveCombinationDeliverableDlg dlg( AvailableDeliverables, value );

                if ( dlg.DoModal() == IDOK )
                {
                    value = dlg.GetDeliverables();
                    return true;
                }

                break;
            }

            case Z_COMBINATION_MASTER:
            {
                ZVChooseMasterDeliverable dlg( GetCombinationDeliverables( i ), value );

                if ( dlg.DoModal() == IDOK )
                {
                    value = dlg.GetMaster();
                    return true;
                }

                break;
            }
        }
    }

    return ZBSymbol::ProcessExtendedInput( Property, value, Properties, Refresh );
}

bool ZBBPProcedureSymbol::ProcessMenuCommand( int                MenuCommand,
                                              ZBProperty&        Property,
                                              CString&            value,
                                              ZBPropertySet&    Properties,
                                              bool&                Refresh )
{
    // ************************************************************************************************************
    // JMR-MODIF - Le 10 juin - Ajout du code pour traitement du menu des risques.

    if ( Property.GetCategoryID() >= ZS_BP_PROP_RISK &&
         Property.GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount() )
    {
        switch( MenuCommand )
        {
            case ID_ADD_NEWRISK:
            {
                OnAddNewRisk( Property, value, Properties, Refresh );
                break;
            }

            case ID_DEL_CURRENTRISK:
            {
                OnDelCurrentRisk( Property, value, Properties, Refresh );
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

    if ( Property.GetCategoryID() >= ZS_BP_PROP_COMBINATION &&
         Property.GetCategoryID() <= ZS_BP_PROP_COMBINATION + GetCombinationCount() )
    {
        switch( MenuCommand )
        {
            case ID_ADD_NEWCOMBINATION:
            {
                OnAddNewCombination( Property, value, Properties, Refresh );
                break;
            }

            case ID_DEL_CURRENTCOMBINATION:
            {
                OnDelCurrentCombination( Property, value, Properties, Refresh );
                break;
            }

            case ID_ADD_DELIVERABLE_COMBINATION:
            {
                OnAddDeliverableCombination( Property, value, Properties, Refresh );
                break;
            }

            case ID_DEL_DELIVERABLE_COMBINATION:
            {
                OnDelDeliverableCombination( Property, value, Properties, Refresh );
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

    if ( Property.GetCategoryID() == ZS_BP_PROP_RULES )
    {
        switch( MenuCommand )
        {
            case ID_DEL_CURRENTRULE:
            {
                int Index = ( Property.GetItemID() - Z_RULE_NAME ) / _MaxRulesSize;

                m_Rules.DeleteRule( Index );

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

    return ZBSymbol::ProcessMenuCommand( MenuCommand, Property, value, Properties, Refresh );
}

bool ZBBPProcedureSymbol::OnPostPropertyChanged( ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh )
{
    // Only local symbol have access to properties
    if ( !IsLocal() )
    {
        return false;
    }

    bool RetValue = false;

    if ( Property.GetCategoryID() >= ZS_BP_PROP_COMBINATION &&
         Property.GetCategoryID() <= ZS_BP_PROP_COMBINATION + GetCombinationCount() )
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_COMBINATION;

        switch( Property.GetItemID() - ( i * _MaxCombinationListSize ) )
        {
            case Z_COMBINATION_DELIVERABLES:
            {
                float MaxPercent =
                    GetMaxActivationPerc( GetCombinationMaster( Property.GetCategoryID() - ZS_BP_PROP_COMBINATION ) );

                // Now sets the right value to the right property
                ZBPropertyIterator s( &Properties );
                ZBProperty* pProp;
                bool bFound = false;

                for ( pProp = s.GetFirst(); pProp && bFound == false; pProp = s.GetNext() )
                {
                    if ( !pProp || ( ( pProp->GetCategoryID() - ZS_BP_PROP_COMBINATION ) != i ) )
                    {
                        continue;
                    }

                    if ( pProp->GetItemID() - ( i * _MaxCombinationListSize) == Z_COMBINATION_ACTIVATION_PERC )
                    {
                        pProp->SetValueFloat( MaxPercent );
                        bFound = true;
                    }
                }

                // Change the return value if we found
                if ( bFound )
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
    else if ( Property.GetCategoryID() == ZS_BP_PROP_UNIT &&
              Property.GetItemID() == Z_UNIT_NAME )
    {
        // Run trough the set of properties and changed the unit cost
        // to the value of the property
        ZBPropertyIterator i( &Properties );
        ZBProperty* pProp;
        CString GUID;

        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
        {
            if ( pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == Z_UNIT_GUID )
            {
                GUID = pProp->GetValueString();
                break;
            }
        }

        if ( !GUID.IsEmpty() )
        {
            for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
            {
                if ( pProp->GetCategoryID() == ZS_BP_PROP_UNIT && pProp->GetItemID() == Z_UNIT_COST )
                {
                    bool Error;
                    float UnitCost = RetreiveUnitCost( GUID, Error );

                    if ( Error == false )
                    {
                        // If the previous value is different
                        pProp->SetValueFloat( UnitCost );

                        // Change the return value
                        RetValue = true;
                    }

                    break;
                }
            }
        }
    }
    else if ( Property.GetCategoryID() == ZS_BP_PROP_RULELIST )
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
        ZBPropertyIterator i( &Properties );
        ZBProperty* pProp;
        size_t        CounterEnableEmpty = 0;

        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
        {
            if ( pProp->GetCategoryID() == ZS_BP_PROP_RULELIST )
            {
                // If the string is not empty, first, sets the enable flag to true
                if ( !pProp->GetValueString().IsEmpty() )
                {
                    pProp->SetEnable( true );
                }

                // If the string is empty
                // Check if he has the enable flag and add it to the counter
                // If the counter is not equal to 1, then enable or disable it
                if ( pProp->GetValueString().IsEmpty() )
                {
                    if ( pProp->GetEnable() == true )
                    {
                        ++CounterEnableEmpty;
                    }
                    else
                    {
                        // If not at least one empty element
                        if ( CounterEnableEmpty < 1 )
                        {
                            pProp->SetEnable( true );
                            ++CounterEnableEmpty;
                        }
                    }

                    // Now if the counter is greather than 1, then you need to disable the empty element
                    if ( CounterEnableEmpty > 1 )
                    {
                        --CounterEnableEmpty;
                        pProp->SetEnable( false );
                    }
                }
            }
        }

        RetValue = true;
    }
    else if ( Property.GetCategoryID() == ZS_BP_PROP_TASKLIST )
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
        ZBPropertyIterator i( &Properties );
        ZBProperty* pProp;
        size_t        CounterEnableEmpty = 0;

        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
        {
            if ( pProp->GetCategoryID() == ZS_BP_PROP_TASKLIST )
            {
                // If the string is not empty, first, sets the enable flag to true
                if ( !pProp->GetValueString().IsEmpty() )
                {
                    pProp->SetEnable( true );
                }

                // If the string is empty
                // Check if he has the enable flag and add it to the counter
                // If the counter is not equal to 1, then enable or disable it
                if ( pProp->GetValueString().IsEmpty() )
                {
                    if ( pProp->GetEnable() == true )
                    {
                        ++CounterEnableEmpty;
                    }
                    else
                    {
                        // If not at least one empty element
                        if ( CounterEnableEmpty < 1 )
                        {
                            pProp->SetEnable( true );
                            ++CounterEnableEmpty;
                        }
                    }

                    // Now if the counter is greather than 1, then you need to disable the empty element
                    if ( CounterEnableEmpty > 1 )
                    {
                        --CounterEnableEmpty;
                        pProp->SetEnable( false );
                    }
                }
            }
        }

        RetValue = true;
    }
    else if ( Property.GetCategoryID() == ZS_BP_PROP_DECISIONLIST )
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
        ZBPropertyIterator i( &Properties );
        ZBProperty* pProp;
        size_t        CounterEnableEmpty = 0;

        for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
        {
            if ( pProp->GetCategoryID() == ZS_BP_PROP_DECISIONLIST )
            {
                // If the string is not empty, first, sets the enable flag to true
                if ( !pProp->GetValueString().IsEmpty() )
                {
                    pProp->SetEnable( true );
                }

                // If the string is empty
                // Check if he has the enable flag and add it to the counter
                // If the counter is not equal to 1, then enable or disable it
                if ( pProp->GetValueString().IsEmpty() )
                {
                    if ( pProp->GetEnable() == true )
                    {
                        ++CounterEnableEmpty;
                    }
                    else
                    {
                        // If not at least one empty element
                        if ( CounterEnableEmpty < 1 )
                        {
                            pProp->SetEnable( true );
                            ++CounterEnableEmpty;
                        }
                    }

                    // Now if the counter is greather than 1, then you need to disable the empty element
                    if ( CounterEnableEmpty > 1 )
                    {
                        --CounterEnableEmpty;
                        pProp->SetEnable( false );
                    }
                }
            }
        }

        RetValue = true;
    }

    if ( RetValue == false )
    {
        return ZBSymbol::OnPostPropertyChanged( Property, Properties, Refresh );
    }

    return RetValue;
}

bool ZBBPProcedureSymbol::OnDropInternalPropertyItem( ZBProperty&        SrcProperty,
                                                      ZBProperty&        DstProperty,
                                                      bool                Top2Down,
                                                      ZBPropertySet&    Properties )
{
    // Call the utility function for swaping two property items
    bool RetValue = ::SwapInternalPropertyItem( SrcProperty,
                                                DstProperty,
                                                Top2Down,
                                                Properties,
                                                ZS_BP_PROP_TASKLIST );

    // If done, return
    if ( RetValue )
    {
        return true;
    }

    RetValue = ::SwapInternalPropertyItem( SrcProperty,
                                           DstProperty,
                                           Top2Down,
                                           Properties,
                                           ZS_BP_PROP_RULELIST );

    // If done, return
    if ( RetValue )
    {
        return true;
    }

    // ********************************************************************************************
    // JMR-MODIF - Le 10 décembre 2006 - Ajout du code pour permettre le glisser-coller des règles.

    RetValue = ::SwapInternalPropertyItem( SrcProperty,
                                           DstProperty,
                                           Top2Down,
                                           Properties,
                                           ZS_BP_PROP_RULES );

    // If done, return
    if ( RetValue )
    {
        int SrcIndex = ( SrcProperty.GetItemID() - Z_RULE_NAME ) / _MaxRulesSize;
        int DstIndex = ( DstProperty.GetItemID() - Z_RULE_NAME ) / _MaxRulesSize;

        CString SrcRuleName = m_Rules.GetRuleName( SrcIndex );
        CString SrcRuleDesc = m_Rules.GetRuleDescription( SrcIndex );
        CString SrcRuleGUID = m_Rules.GetRuleGUID( SrcIndex );

        CString DstRuleName = m_Rules.GetRuleName( DstIndex );
        CString DstRuleDesc = m_Rules.GetRuleDescription( DstIndex );
        CString DstRuleGUID = m_Rules.GetRuleGUID( DstIndex );

        m_Rules.SetRuleName( SrcIndex, DstRuleName );
        m_Rules.SetRuleDescription( SrcIndex, DstRuleDesc );
        m_Rules.SetRuleGUID( SrcIndex, DstRuleGUID );

        m_Rules.SetRuleName( DstIndex, SrcRuleName );
        m_Rules.SetRuleDescription( DstIndex, SrcRuleDesc );
        m_Rules.SetRuleGUID( DstIndex, SrcRuleGUID );

        return true;
    }
    // ********************************************************************************************

    // Otherwise, try to do it for Decisions
    return ::SwapInternalPropertyItem( SrcProperty, DstProperty, Top2Down, Properties, ZS_BP_PROP_DECISIONLIST );
}

float ZBBPProcedureSymbol::GetMaxActivationPerc( const CString Master )
{
    if ( Master.IsEmpty() )
    {
        return 0;
    }

    double Sum = 0;
    double MasterQuantity = 0;

    CODEdgeArray Edges;

    // Retreive all entering Up edges of the procedure
    if ( GetEnteringUpDeliverable( Edges ) > 0 )
    {
        for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
        {
            IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

            // Test if it is a local symbol
            if ( !pComp->IsLocal() )
            {
                // Locate the local symbol
                CODComponent* pLocalComp = pComp->GetLocalSymbol();

                if ( pLocalComp && ISA( pLocalComp, ZBDeliverableLinkSymbol ) )
                {
                    pComp = dynamic_cast<ZBDeliverableLinkSymbol*>( pLocalComp );
                }
                else
                {
                    pComp = NULL;
                }
            }

            if ( pComp )
            {
                // Check if the component is the requested master
                if ( pComp->GetSymbolName() == Master )
                {
                    MasterQuantity = (double)pComp->GetQuantity();
                }

                // Now, run through combination
                // and check if the component is a master of the combination
                // add its quantity to the sum
                int CombinationCount = GetCombinationCount();

                for ( int i = 0; i < CombinationCount; ++i )
                {
                    if ( pComp->GetSymbolName() == GetCombinationMaster( i ) )
                    {
                        Sum += (double)pComp->GetQuantity();
                    }
                }
            }
        }
    }

    return (float)( MasterQuantity / Sum );
}

// To calculate the procedure activation,
// we need to run through all combination and to take the maximum
// of each deliverable multiply by the percent of its combination
ZBBPAnnualNumberProperties ZBBPProcedureSymbol::CalculateProcedureActivation()
{
    // First, we need to get all entering deliverables
    CODEdgeArray Edges;

    // Retreive all entering Up edges
    if ( GetEnteringUpDeliverable( Edges ) == 0 )
    {
        return 0;
    }

    // Now for each deliverables, we will calculate the max procedure activation
    ZBBPAnnualNumberProperties ProcedureActivation( 0 );

    for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
    {
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);
        ZBDeliverableLinkSymbol* pDeliverable = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

        if ( !pDeliverable )
        {
            continue;
        }

        // Test if it is a local symbol
        if ( !pDeliverable->IsLocal() )
        {
            // Locate the local symbol
            CODComponent* pComp = pDeliverable->GetLocalSymbol();

            if ( pComp && ISA( pComp, ZBDeliverableLinkSymbol ) )
            {
                pDeliverable = dynamic_cast<ZBDeliverableLinkSymbol*>( pComp );
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

        for ( int i = 0; i < Count; ++i )
        {
            TRACE1(    _T( "Master = %s" ), GetCombinationMaster( i ) );
            TRACE1(    _T( "   Livrable = %s\n" ), pDeliverable->GetSymbolName() );

            // If we have a master
            if ( !GetCombinationMaster( i ).IsEmpty() && GetCombinationMaster(i) == pDeliverable->GetSymbolName() )
            {
                ProcedureActivation += pDeliverable->GetQuantity();
            }
        }
    }

    return ProcedureActivation;
}

int ZBBPProcedureSymbol::GetEnteringUpDeliverable( CString& EnteringDeliverables )
{
    int Counter = 0;
    CODEdgeArray Edges;

    // Keep only deliverable symbols
    if ( GetEnteringUpDeliverable( Edges ) > 0 )
    {
        ZBTokenizer token;    // Initialize the token with ; as separator
        
        for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
        {
            IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

            if ( pComp )
            {
                token.AddToken( pComp->GetSymbolName() );
                ++Counter;
            }
        }

        // Assign the return string
        EnteringDeliverables = token.GetString();
    }

    return Counter;
}

int     ZBBPProcedureSymbol::GetEnteringUpDeliverable( CODEdgeArray& Edges )
{
    // Retreive all entering Up edges of the procedure
    GetEdgesEntering_Up( Edges );

    // And also from all referenced procedures
    // and local symbol if we have a referenced symbol
    CODComponentSet* pSet;
    CODComponentSet  InternalSet;

    if ( IsLocal() )
    {
        pSet = GetReferenceSymbols();
    }
    else
    {
        pSet = GetReferenceSymbols();

        if ( !pSet )
        {
            pSet = &InternalSet;
        }

        CODComponent* pLocalSymbol = GetLocalSymbol();

        if ( pLocalSymbol )
        {
            pSet->Add( pLocalSymbol );
        }
    }

    if ( pSet && pSet->GetSize() > 0 )
    {
        for ( int i = 0; i < pSet->GetSize(); ++i ) 
        {
            CODComponent* pComp = pSet->GetAt( i );

            if ( pComp && ISA( pComp, ZBBPProcedureSymbol ) )
            {
                CODEdgeArray AdditionalEdges;
                reinterpret_cast<ZBBPProcedureSymbol*>( pComp )->GetEdgesEntering_Up( AdditionalEdges );

                // Copy additional edges to the principal edges
                for ( int nEdgeIdx = 0; nEdgeIdx < AdditionalEdges.GetSize(); ++nEdgeIdx )
                {
                    // Get the link 
                    Edges.AddEdge( AdditionalEdges.GetAt( nEdgeIdx ) );
                }
            }
        }
    }

    // Keep only deliverable symbols
    return (int)ZUODSymbolManipulator::KeepOnlyLinksISA( Edges, RUNTIME_CLASS( ZBDeliverableLinkSymbol ) );
}

int ZBBPProcedureSymbol::GetLeavingDownDeliverable( CString& LeavingDeliverables )
{
    int Counter = 0;
    CODEdgeArray Edges;

    if ( GetLeavingDownDeliverable( Edges ) > 0 )
    {
        ZBTokenizer token;    // Initialize the token with ; as separator
        
        for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
        {
            IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

            if ( pComp )
            {
                token.AddToken( pComp->GetSymbolName() );
                ++Counter;
            }
        }

        // Assign the return string
        LeavingDeliverables = token.GetString();
    }

    return Counter;
}

int ZBBPProcedureSymbol::GetLeavingDownDeliverable( CODEdgeArray& Edges )
{
    // Retreive all leaving down edges
    GetEdgesLeaving_Down( Edges );

    // And also from all referenced procedures
    // and local symbol if we have a referenced symbol
    CODComponentSet* pSet;
    CODComponentSet  InternalSet;

    if ( IsLocal() )
    {
        pSet = GetReferenceSymbols();
    }
    else
    {
        pSet = GetReferenceSymbols();

        if ( !pSet )
        {
            pSet = &InternalSet;
        }

        CODComponent* pLocalSymbol = GetLocalSymbol();

        if ( pLocalSymbol )
        {
            pSet->Add( pLocalSymbol );
        }
    }

    if ( pSet && pSet->GetSize() > 0 )
    {
        for ( int i = 0; i < pSet->GetSize(); ++i )
        {
            CODComponent* pComp = pSet->GetAt( i );

            if ( pComp && ISA( pComp, ZBBPProcedureSymbol ) )
            {
                CODEdgeArray AdditionalEdges;
                reinterpret_cast<ZBBPProcedureSymbol*>( pComp )->GetEdgesLeaving_Down( AdditionalEdges );

                // Copy additional edges to the principal edges
                for ( int nEdgeIdx = 0; nEdgeIdx < AdditionalEdges.GetSize(); ++nEdgeIdx )
                {
                    // Get the link 
                    Edges.AddEdge( AdditionalEdges.GetAt(nEdgeIdx) );
                }
            }
        }
    }

    // Keep only deliverable symbols
    return (int)ZUODSymbolManipulator::KeepOnlyLinksISA( Edges, RUNTIME_CLASS( ZBDeliverableLinkSymbol ) );
}

int     ZBBPProcedureSymbol::GetLeavingRightDeliverable( CString& LeavingDeliverables )
{
    int Counter = 0;
    CODEdgeArray Edges;

    if ( GetLeavingRightDeliverable( Edges ) > 0 )
    {
        ZBTokenizer token;    // Initialize the token with ; as separator
        
        for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
        {
            IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

            if ( pComp )
            {
                token.AddToken( pComp->GetSymbolName() );
                ++Counter;
            }
        }

        // Assign the return string
        LeavingDeliverables = token.GetString();
    }

    return Counter;
}

int     ZBBPProcedureSymbol::GetLeavingRightDeliverable( CODEdgeArray& Edges )
{
    // Retreive all leaving right edges
    GetEdgesLeaving_Right( Edges );

    // And also from all referenced procedures
    // and local symbol if we have a referenced symbol
    CODComponentSet* pSet;
    CODComponentSet  InternalSet;

    if ( IsLocal() )
    {
        pSet = GetReferenceSymbols();
    }
    else
    {
        pSet = GetReferenceSymbols();

        if ( !pSet )
        {
            pSet = &InternalSet;
        }

        CODComponent* pLocalSymbol = GetLocalSymbol();

        if ( pLocalSymbol )
        {
            pSet->Add( pLocalSymbol );
        }
    }

    if ( pSet && pSet->GetSize() > 0 )
    {
        for ( int i = 0; i < pSet->GetSize(); ++i )
        {
            CODComponent* pComp = pSet->GetAt( i );

            if ( pComp && ISA( pComp, ZBBPProcedureSymbol ) )
            {
                CODEdgeArray AdditionalEdges;
                reinterpret_cast<ZBBPProcedureSymbol*>( pComp )->GetEdgesLeaving_Right( AdditionalEdges );

                // Copy additional edges to the principal edges
                for ( int nEdgeIdx = 0; nEdgeIdx < AdditionalEdges.GetSize(); ++nEdgeIdx )
                {
                    // Get the link 
                    Edges.AddEdge( AdditionalEdges.GetAt( nEdgeIdx ) );
                }
            }
        }
    }

    // Keep only deliverable symbols
    return (int)ZUODSymbolManipulator::KeepOnlyLinksISA( Edges, RUNTIME_CLASS(ZBDeliverableLinkSymbol ) );
}

int     ZBBPProcedureSymbol::GetLeavingLeftDeliverable( CString& LeavingDeliverables )
{
    int Counter = 0;
    CODEdgeArray Edges;

    if ( GetLeavingLeftDeliverable( Edges ) > 0 )
    {
        ZBTokenizer token;    // Initialize the token with ; as separator
        
        for ( int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx )
        {
            IODEdge* pIEdge = Edges.GetAt( nEdgeIdx );
            ZBDeliverableLinkSymbol* pComp = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

            if ( pComp )
            {
                token.AddToken( pComp->GetSymbolName() );
                ++Counter;
            }
        }

        // Assign the return string
        LeavingDeliverables = token.GetString();
    }

    return Counter;
}

int     ZBBPProcedureSymbol::GetLeavingLeftDeliverable( CODEdgeArray& Edges )
{
    // Retreive all leaving left edges
    GetEdgesLeaving_Left( Edges );

    // And also from all referenced procedures
    // and local symbol if we have a referenced symbol
    CODComponentSet* pSet;
    CODComponentSet  InternalSet;

    if ( IsLocal() )
    {
        pSet = GetReferenceSymbols();
    }
    else
    {
        pSet = GetReferenceSymbols();

        if ( !pSet )
        {
            pSet = &InternalSet;
        }

        CODComponent* pLocalSymbol = GetLocalSymbol();

        if ( pLocalSymbol )
        {
            pSet->Add( pLocalSymbol );
        }
    }

    if ( pSet && pSet->GetSize() > 0 )
    {
        for ( int i = 0; i < pSet->GetSize(); ++i )
        {
            CODComponent* pComp = pSet->GetAt( i );

            if ( pComp && ISA( pComp, ZBBPProcedureSymbol ) )
            {
                CODEdgeArray AdditionalEdges;
                reinterpret_cast<ZBBPProcedureSymbol*>( pComp )->GetEdgesLeaving_Left( AdditionalEdges );

                // Copy additional edges to the principal edges
                for ( int nEdgeIdx = 0; nEdgeIdx < AdditionalEdges.GetSize(); ++nEdgeIdx )
                {
                    // Get the link 
                    Edges.AddEdge( AdditionalEdges.GetAt( nEdgeIdx ) );
                }
            }
        }
    }

    // Keep only deliverable symbols
    return (int)ZUODSymbolManipulator::KeepOnlyLinksISA( Edges, RUNTIME_CLASS( ZBDeliverableLinkSymbol ) );
}

BOOL ZBBPProcedureSymbol::SetSymbolName( const CString value )
{
    BOOL bResult = ZBSymbol::SetSymbolName( value );
    return bResult;
}

// Drag and drop methods
bool ZBBPProcedureSymbol::AcceptDropItem( CObject* pObj, CPoint pt )
{
    // JMR-MODIF - Le 18 décembre 2006 - Si le symbole n'est pas local, interdit l'opération de glisser-coller.
    if ( !IsLocal() )
    {
        return false;
    }

    // If a user entity
    if ( pObj && ISA( pObj, ZBUserGroupEntity ) )
    {
        return true;
    }

    // JMR-MODIF - Le 19 novembre 2006 - Détermine si l'objet reçu est un objet de type règle.
    if ( pObj && ISA( pObj, ZBLogicalRulesEntity ) )
    {
        return true;
    }

    return ZBSymbol::AcceptDropItem( pObj, pt );
}

bool ZBBPProcedureSymbol::DropItem( CObject* pObj, CPoint pt )
{
    if ( pObj && ISA( pObj, ZBUserGroupEntity ) )
    {
        // First, check if the user group is valid
        CODModel* pModel = GetRootModel();

        if ( pModel && ISA( pModel, ZDProcessGraphModelMdl ) &&
             !dynamic_cast<ZDProcessGraphModelMdl*>( pModel )->MainUserGroupIsValid() )
        {
            // Cannot delete all combinations
            MsgBox mbox;
            mbox.DisplayMsgBox( IDS_CANNOTDROP_USERGROUPNOTINLINE, MB_OK );
            return false;
        }

        ZBUserGroupEntity* pGroup = dynamic_cast<ZBUserGroupEntity*>( pObj );
        SetUnitGUID( pGroup->GetGUID() );
        SetUnitName( pGroup->GetEntityName() );

        // Change the unit cost
        SetUnitCost( pGroup->GetEntityCost() );

        // Set flag for modification
        SetModifiedFlag( TRUE );

        // Refresh the attribute area and redraw the symbol
        RefreshAttributeAreaText( true );
        return true;
    }

    // *********************************************************************************************
    // JMR-MODIF - Le 20 novembre 2006 - Ajout du code pour le traitement des objets de type règles.
    if ( pObj && ISA( pObj, ZBLogicalRulesEntity ) )
    {
        // First, check if the rule is valid
        CODModel* pModel = GetRootModel();

        if ( pModel && ISA( pModel, ZDProcessGraphModelMdl ) &&
             !dynamic_cast<ZDProcessGraphModelMdl*>( pModel )->MainLogicalRulesIsValid() )
        {
            // Cannot delete all rules
            MsgBox mbox;
            mbox.DisplayMsgBox( IDS_CANNOTDROP_RULENOTINLINE, MB_OK );
            return false;
        }

        ZBLogicalRulesEntity* pRule = dynamic_cast<ZBLogicalRulesEntity*>( pObj );

        ZBBPRulesProperties* m_NewRule = new ZBBPRulesProperties();

        m_NewRule->SetRuleName( pRule->GetEntityName() );
        m_NewRule->SetRuleDescription( pRule->GetEntityDescription() );
        m_NewRule->SetRuleGUID( pRule->GetGUID() );

        m_Rules.AddRule( m_NewRule );

        // Set flag for modification
        SetModifiedFlag( TRUE );

        // Refresh the attribute area and redraw the symbol
        RefreshAttributeAreaText( true );
        return true;
    }
    // *********************************************************************************************

    // Otherwise, call the base class
    return ZBSymbol::DropItem( pObj, pt );
}

void ZBBPProcedureSymbol::CopySymbolDefinitionFrom( CODSymbolComponent& src )
{
    // Class the base class method
    ZBSymbol::CopySymbolDefinitionFrom( src );

    if ( ISA( ( &src ), ZBBPProcedureSymbol ) )
    {
        m_CommentRect    = dynamic_cast<ZBBPProcedureSymbol&>( src ).m_CommentRect;
        m_Combinations    = dynamic_cast<ZBBPProcedureSymbol&>( src ).m_Combinations;
        m_Combinations.SetParent( this );

        m_SimulationProperties    = dynamic_cast<ZBBPProcedureSymbol&>( src ).m_SimulationProperties;
        m_UnitProp                = dynamic_cast<ZBBPProcedureSymbol&>( src ).m_UnitProp;
        m_CostProcedureProp        = dynamic_cast<ZBBPProcedureSymbol&>( src ).m_CostProcedureProp;

        // JMR-MODIF - Le 26 novembre 2006 - Ajout du code de copie pour les règles.
        m_Rules                    = dynamic_cast<ZBBPProcedureSymbol&>( src ).m_Rules;

        // JMR-MODIF - Le 29 juillet 2007 - Ajout du code de copie pour les risques
        m_Risks                    = dynamic_cast<ZBBPProcedureSymbol&>( src ).m_Risks;

        // Fill the array of unit double validation type
        m_UnitDoubleValidationTypeArray.RemoveAll();
        GetUnitDoubleValidationTypeStringArray( m_UnitDoubleValidationTypeArray );
    }
}

BOOL ZBBPProcedureSymbol::Create( const CString Name /*= ""*/ )
{
    m_IsInCreationProcess = true;

    BOOL RetValue = ZBSymbol::Create( IDR_BP_PROCEDURE,
                                      AfxFindResourceHandle( MAKEINTRESOURCE( IDR_PACKAGE_SYM ), _T( "Symbol" ) ),
                                      Name );

    if ( !CreateSymbolProperties() )
    {
        RetValue = FALSE;
    }

    m_IsInCreationProcess = false;

    return RetValue;
}

void ZBBPProcedureSymbol::AdjustElementPosition()
{
    ZBSymbol::AdjustElementPosition();
}

void ZBBPProcedureSymbol::OnDraw( CDC* pDC )
{
    ZBSymbol::OnDraw( pDC );
}

BOOL ZBBPProcedureSymbol::OnDoubleClick()
{
    return FALSE;
}

bool ZBBPProcedureSymbol::OnToolTip( CString& ToolTipText, CPoint point, ToolTipMode ToolTip /*= NormalToolTip*/ )
{
    ToolTipText.Format( IDS_FS_BPPROCEDURE_TOOLTIP,
                        (const char*)GetSymbolName(),
                        (const char*)GetSymbolComment(),
                        (const char*)GetSymbolReferenceNumberStr() );

    if ( ToolTip == ZBSymbol::DesignToolTip )
    {
        // From now do nothing,
        // need to implement the result of the control checking
        // TODO
    }

    return true;
}

void ZBBPProcedureSymbol::Serialize( CArchive& ar )
{
    // Serialize the canvas model.
    ZBSymbol::Serialize( ar );

    // Only if the object is serialize from and to a document
    if ( ar.m_pDocument )
    {
        // Serialize the combinations
        m_Combinations.Serialize( ar );

        m_SimulationProperties.Serialize( ar );

        // JMR-MODIF - Le 10 juin 2007 - Ajout du code pour la sérialisation des risques.
        if ( dynamic_cast<ZDBaseDocument*>( ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 27 )
        {
            m_Risks.Serialize( ar );
        }

        // ******************************************************************************************************
        // JMR-MODIF - Le 26 novembre 2006 - Ajout de la sérialisation des règles.
        if ( ar.IsStoring() )
        {
            m_Rules.Serialize( ar );
        }
        else
        {
            if ( ( (ZDBaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 26 )
            {
                m_Rules.Serialize( ar );
            }
        }
        // ******************************************************************************************************

        if ( ar.IsStoring() ||
             dynamic_cast<ZDBaseDocument*>( ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 19 )
        {
            m_UnitProp.Serialize( ar );
            m_CostProcedureProp.Serialize( ar );
        }
        else
        {
            TRACE( _T( "ZBBPProcedureSymbol::Serialize : Start Read\n" ) );

            // Transfert the properties to new format
            ZBBPCostPropertiesProcedure* pCostProps =
                (ZBBPCostPropertiesProcedure*)GetProperty( ZS_BP_PROP_PROCEDURE_COST );

            if ( pCostProps )
            {
                SetMultiplier( pCostProps->GetMultiplier() );
                SetProcessingTime( pCostProps->GetProcessingTime() );
                SetUnitaryCost( pCostProps->GetUnitaryCost() );
            }

            ZBBPUnitProperties* pUnitProps = (ZBBPUnitProperties*)GetProperty( ZS_BP_PROP_UNIT );

            if ( pUnitProps )
            {
                SetUnitName( pUnitProps->GetUnitName() );
                SetUnitCost( pUnitProps->GetUnitCost() );
            }

            // Sets the master if only one deliverable for the combination
            int Count = GetCombinationCount();

            for ( int i = 0; i < Count; ++i )
            {
                CString Deliverables = GetCombinationDeliverables( i );

                // If no separator, then only one deliverable
                // Then sets the master to this deliverable
                if ( Deliverables.Find( ';' ) == -1 )
                {
                    SetCombinationMaster( i, Deliverables );
                }
            }

            // JMR-MODIF - Le 6 octobre 2005 - Ajout du traçage de fin.
            TRACE( _T( "ZBBPProcedureSymbol::Serialize : End Read\n" ) );
        }
    }
}
