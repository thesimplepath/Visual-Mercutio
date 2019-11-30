// ZBBPStartSymbol.cpp: implementation of the ZBBPStartSymbol class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBBPStartSymbol.h"

// JMR-MODIF - Le 26 mai 2005 - Définition de _ZMODELEXPORT, pour éviter une erreur interne du compilateur.
#define _ZMODELEXPORT
#include "zModel\ZBBasicProp.h"
#undef _ZMODELEXPORT

#include "ZBBPUnitProp.h"

// Global for model
#include "zModel\ZAModelGlobal.h"

// JMR-MODIF - Le 29 juillet 2007 - Ajout de l'en-tête ZAGlobal.h
#include "zBaseLib\PSS_Global.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\ZVSelectUserGroupDlg.h"
#include "zBaseLib\PSS_MsgBox.h"

// JMR-MODIF - Le 25 décembre 2006 - Ajout de l'en-tête ProcGraphModelCtlrBP.h
#include "ProcGraphModelCtlrBP.h"

// JMR-MODIF - Le 25 décembre 2006 - Ajout de l'en-tête ProcGraphModelMdlBP.h
#include "ProcGraphModelMdlBP.h"

// JMR-MODIF - Le 13 juin 2007 - Ajout de l'en-tête ZVRiskOptionsDlg.h
#include "ZVRiskOptionsDlg.h"

// Resources
#include "zModelBPRes.h"
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(ZBBPStartSymbol, ZBSymbol, g_DefVersion)

// JMR-MODIF - Le 18 décembre 2006 - Ajout de la nouvelle variable statique gRulesMenu.
static CMenu gRulesMenu;
// JMR-MODIF - Le 10 juin 2007 - Ajout de la nouvelle variable statique gRiskMenu
static CMenu gRiskMenu;

// JMR-MODIF - Le 18 décembre 2006 - Ajout de la constante _MaxRulesSize.
const size_t _MaxRulesSize = 20;
// JMR-MODIF - Le 3 juin 2007 - Ajout de la constante _MaxRisksSize.
const size_t _MaxRisksSize = 20;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBBPStartSymbol::ZBBPStartSymbol(const CString Name /*= ""*/)
{
    ZBSymbol::SetSymbolName(Name);

    // Change what to show first
    m_DisplayNameArea = true;
    m_DisplayDescriptionArea = false;
    m_DisplayAttributeArea = true;

    // JMR-MODIF - Le 29 juillet 2007 - Ajout de l'appel à CreateSymbolProperties.
    CreateSymbolProperties();
}

ZBBPStartSymbol::~ZBBPStartSymbol()
{}

ZBBPStartSymbol::ZBBPStartSymbol(const ZBBPStartSymbol& src)
{
    *this = src;
}

ZBBPStartSymbol& ZBBPStartSymbol::operator=(const ZBBPStartSymbol& src)
{
    // Call the base class assignement operator
    ZBSymbol::operator=((const ZBSymbol&)src);

    m_UnitProp = src.m_UnitProp;

    // JMR-MODIF - Le 18 décembre 2006 - Ajout du code de copie pour les règles
    m_Rules = src.m_Rules;

    // JMR-MODIF - Le 29 juillet 2007 - Ajout du code de copie pour les risques
    m_Risks = src.m_Risks;

    return *this;
}

CODComponent* ZBBPStartSymbol::Dup() const
{
    return (new ZBBPStartSymbol(*this));
}

void ZBBPStartSymbol::CopySymbolDefinitionFrom(CODSymbolComponent& src)
{
    // Class the base class method
    ZBSymbol::CopySymbolDefinitionFrom(src);

    if (ISA((&src), ZBBPStartSymbol))
    {
        m_UnitProp = ((ZBBPStartSymbol&)src).m_UnitProp;

        // JMR-MODIF - Le 18 décembre 2006 - Ajout de la copie de la variable m_Rules.
        m_Rules = ((ZBBPStartSymbol&)src).m_Rules;

        // JMR-MODIF - Le 29 juillet 2007 - Ajout du code de copie pour les risques
        m_Risks = ((ZBBPStartSymbol&)src).m_Risks;
    }
}

BOOL ZBBPStartSymbol::Create(const CString Name /*= _T( "" )*/)
{
    m_IsInCreationProcess = true;

    BOOL RetValue = ZBSymbol::Create(IDR_BP_START,
                                     AfxFindResourceHandle(MAKEINTRESOURCE(IDR_UML_START_SYM), _T("Symbol")),
                                     Name);

    if (!CreateSymbolProperties())
    {
        RetValue = FALSE;
    }

    m_IsInCreationProcess = false;

    return RetValue;
}

bool ZBBPStartSymbol::OnFillDefaultAttributes(ZBPropertyAttributes* pAttributes)
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
        pAttributes->AddAttribute(ZS_BP_PROP_BASIC, Z_SYMBOL_NUMBER);

        // Add the unit name
        pAttributes->AddAttribute(ZS_BP_PROP_UNIT, Z_UNIT_NAME);

        // No item labels
        pAttributes->SetDisplayTitleText(false);
    }

    return ZBSymbol::OnFillDefaultAttributes(pAttributes);
}

bool ZBBPStartSymbol::OnChangeAttributes(ZBPropertyAttributes* pAttributes)
{
    return ZBSymbol::OnChangeAttributes(pAttributes);
}

CString ZBBPStartSymbol::GetAttributeString(ZBPropertyAttributes* pAttributes) const
{
    return ZBSymbol::GetAttributeString(pAttributes);
}

// Drag and drop methods
bool ZBBPStartSymbol::AcceptDropItem(CObject* pObj, const CPoint& pt)
{
    // JMR-MODIF - Le 18 décembre 2006 - Si le symbole n'est pas local, interdit l'opération de glisser-coller.
    if (!IsLocal())
    {
        return false;
    }

    // If a user entity
    if (pObj && ISA(pObj, ZBUserGroupEntity))
    {
        return true;
    }

    // JMR-MODIF - Le 18 décembre 2006 - Détermine si l'objet reçu est un objet de type règle.
    if (pObj && ISA(pObj, ZBLogicalRulesEntity))
    {
        return true;
    }

    // Otherwise, call the base class
    return ZBSymbol::AcceptDropItem(pObj, pt);
}

bool ZBBPStartSymbol::DropItem(CObject* pObj, const CPoint& pt)
{
    if (pObj && ISA(pObj, ZBUserGroupEntity))
    {
        // First, check if the user group is valid
        CODModel * pModel = GetRootModel();

        if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
            !dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->MainUserGroupIsValid())
        {
            // Cannot delete all combinations
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_USERGROUPNOTINLINE, MB_OK);
            return false;
        }

        ZBUserGroupEntity* pGroup = dynamic_cast<ZBUserGroupEntity*>(pObj);
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

    // **********************************************************************************************************
    // JMR-MODIF - Le 18 décembre 2006 - Ajout du code pour le traitement des objets de type règles.
    if (pObj && ISA(pObj, ZBLogicalRulesEntity))
    {
        // First, check if the rule is valid
        CODModel* pModel = GetRootModel();

        if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
            !dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->MainLogicalRulesIsValid())
        {
            // Cannot delete all rules
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_RULENOTINLINE, MB_OK);
            return false;
        }

        ZBLogicalRulesEntity* pRule = dynamic_cast<ZBLogicalRulesEntity*>(pObj);

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
    // **********************************************************************************************************

    return ZBSymbol::DropItem(pObj, pt);
}

// JMR-MODIF - Le 25 décembre 2006 - Permet de rechercher le nom original d'une règle en fonction de son GUID.
CString ZBBPStartSymbol::GetRuleNameByGUID(ZBLogicalRulesEntity* p_Rule, CString RuleGUID)
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
            ZBRulesEntity* pEntity = p_Rule->GetEntityAt(i);

            if (!pEntity)
            {
                continue;
            }

            if (ISA(pEntity, ZBLogicalRulesEntity))
            {
                CString m_Name = GetRuleNameByGUID(dynamic_cast<ZBLogicalRulesEntity*>(pEntity), RuleGUID);

                if (!m_Name.IsEmpty())
                {
                    return m_Name;
                }
            }
        }
    }

    return _T("");
}

BOOL ZBBPStartSymbol::OnDoubleClick()
{
    return FALSE;
}

bool ZBBPStartSymbol::CreateSymbolProperties()
{
    if (!ZBSymbol::CreateSymbolProperties())
    {
        return false;
    }

    ZBBPUnitProperties propUnit;
    AddProperty(propUnit);

    // JMR-MODIF - Le 3 juin 2007 - Ajoute au moins un catalogue de propriétés dans les risques.
    m_Risks.CreateInitialProperties();

    return true;
}

// JMR-MODIF - Le 26 avril 2007 - Cette fonction permet de déterminer si une règle donnée a été attribuée à cet objet.
BOOL ZBBPStartSymbol::ContainsRule(CString RuleName)
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
void ZBBPStartSymbol::CheckRulesSync(CStringArray& RulesList)
{
    CODModel * pModel = GetRootModel();

    if (pModel == NULL)
    {
        return;
    }

    if (m_Rules.GetRulesCount() > 0)
    {
        ZBLogicalRulesEntity* p_MainRule = NULL;

        if (GetOwnerModel() != NULL && ISA(GetOwnerModel(), ZDProcessGraphModelMdlBP))
        {
            ZDProcessGraphModelMdlBP* p_Model = reinterpret_cast<ZDProcessGraphModelMdlBP*>(GetOwnerModel());

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

bool ZBBPStartSymbol::FillProperties(ZBPropertySet& PropSet, bool NumericValue /*= false*/, bool GroupValue /*= false*/)
{
    if (!ZBSymbol::FillProperties(PropSet, NumericValue, GroupValue))
    {
        return false;
    }

    // JMR-MODIF - Le 29 juillet 2007 - Ajout du test de symbole local.
    // Only local symbol have access to properties
    if (!IsLocal())
    {
        return true;
    }

    // JMR-MODIF - Le 25 décembre 2006 - Ajout du modèle.
    CODModel* pModel = GetRootModel();

    // Initialize the Currency symbol with the user local currency symbol
    // defined in the Control Panel
    CString CurrencySymbol = PSS_Global::GetLocaleCurrency();

    // JMR-MODIF - Le 30 juillet 2007 - Mets à jour le symbole monétaire en fonction de la sélection utilisateur.
    if (pModel && ISA(pModel, ZDProcessGraphModelMdl))
    {
        CDocument* pDoc = dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetDocument();

        if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc))
        {
            // Retreive the model's currency symbol
            CurrencySymbol = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetCurrencySymbol();
        }
    }

    // ************************************************************************************************************
    // JMR-MODIF - Le 18 décembre 2006 - Nouvelle architecture des règles.

    // If the menu is not loaded, load it
    if (gRulesMenu.GetSafeHmenu() == NULL)
    {
        gRulesMenu.LoadMenu(IDR_RULES_MENU);
    }

    if (m_Rules.GetRulesCount() > 0)
    {
        CString RuleSectionTitle = _T("");
        CString RuleName = _T("");
        CString RuleDesc = _T("");

        RuleSectionTitle.LoadString(IDS_Z_RULES_TITLE);
        RuleDesc.LoadString(IDS_Z_RULES_DESC);

        ZBLogicalRulesEntity* p_MainRule = NULL;

        if (GetOwnerModel() != NULL && ISA(GetOwnerModel(), ZDProcessGraphModelMdlBP))
        {
            ZDProcessGraphModelMdlBP* p_Model = reinterpret_cast<ZDProcessGraphModelMdlBP*>(GetOwnerModel());

            if (p_Model != NULL &&
                p_Model->GetController() != NULL &&
                ISA(p_Model->GetController(), ZDProcessGraphModelControllerBP))
            {
                ZDProcessGraphModelControllerBP* p_Controller =
                    reinterpret_cast<ZDProcessGraphModelControllerBP*>(p_Model->GetController());

                if (p_Controller != NULL && ISA(p_Controller->GetDocument(), PSS_ProcessGraphModelDoc))
                {
                    PSS_ProcessGraphModelDoc* p_Document =
                        reinterpret_cast<PSS_ProcessGraphModelDoc*>(p_Controller->GetDocument());

                    if (p_Document != NULL && p_Document->GetMainLogicalRules() != NULL)
                    {
                        p_MainRule = p_Document->GetMainLogicalRules();
                    }
                }
            }
        }

        for (int i = 0; i < m_Rules.GetRulesCount(); i++)
        {
            // Le contrôle des règles ne peut être appliqué que si le modèle est en phase avec le système des règles.
            if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
                dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->MainLogicalRulesIsValid())
            {
                CString m_SafeName = GetRuleNameByGUID(p_MainRule, m_Rules.GetRuleGUID(i));

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

                if (!m_SafeName.IsEmpty() && m_SafeName != m_Rules.GetRuleName(i))
                {
                    m_Rules.SetRuleName(i, m_SafeName);
                }
                // ********************************************************************************************
            }

            RuleName.Format(IDS_Z_RULES_NAME, i + 1);

            // Propriété "Règle x" du groupe "Règles"
            ZBProperty* pRule = new ZBProperty(RuleSectionTitle,
                                               ZS_BP_PROP_RULES,
                                               RuleName,
                                               Z_RULE_NAME + (i * _MaxRulesSize),
                                               RuleDesc,
                                               m_Rules.GetRuleName(i),
                                               ZBProperty::PT_EDIT_MENU,
                                               true,
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                               NULL,
                                               &gRulesMenu);

            pRule->EnableDragNDrop();
            PropSet.Add(pRule);
        }
    }
    // ************************************************************************************************************

    // ***********************************************************************************************************
    // JMR-MODIF - Le 3 juin 2007 - Ajout des propriétés liées aux risques.

    // Obtient le menu des risques si celui-ci n'est pas encore présent.
    if (gRiskMenu.GetSafeHmenu() == NULL)
    {
        gRiskMenu.LoadMenu(IDR_RISK_MENU);
    }

    CString FinalRiskName = _T("");
    CString FinalRiskTitle = _T("");
    CString RiskTitle = _T("");
    CString RiskName = _T("");
    CString RiskDesc = _T("");

    RiskTitle.LoadString(IDS_ZS_BP_PROP_RISK_TITLE);

    for (int i = 0; i < GetRiskCount(); ++i)
    {
        FinalRiskTitle.Format(_T("%s (%d)"), RiskTitle, i + 1);

        RiskName.LoadString(IDS_Z_RISK_NAME_NAME);
        RiskDesc.LoadString(IDS_Z_RISK_NAME_DESC);

        // Propriété "Titre Risque" du groupe "Risque (x)"
        ZBProperty* pRisk = new ZBProperty(FinalRiskTitle,
            (GroupValue == true) ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                                           RiskName,
                                           (GroupValue == true) ? Z_RISK_NAME : (Z_RISK_NAME + (i * _MaxRisksSize)),
                                           RiskDesc,
                                           GetRiskName(i),
                                           ZBProperty::PT_EDIT_MENU,
                                           true,
                                           PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                           NULL,
                                           &gRiskMenu);

        PropSet.Add(pRisk);

        RiskName.LoadString(IDS_Z_RISK_DESC_NAME);
        RiskDesc.LoadString(IDS_Z_RISK_DESC_DESC);

        // Propriété "Description" du groupe "Risque (x)"
        pRisk = new ZBProperty(FinalRiskTitle,
            (GroupValue == true) ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                               RiskName,
                               (GroupValue == true) ? Z_RISK_DESC : (Z_RISK_DESC + (i * _MaxRisksSize)),
                               RiskDesc,
                               GetRiskDesc(i),
                               ZBProperty::PT_EDIT_EXTENDED);

        PropSet.Add(pRisk);

        RiskName.LoadString(IDS_Z_RISK_TYPE_NAME);
        RiskDesc.LoadString(IDS_Z_RISK_TYPE_DESC);

        CString s_NoRiskType = _T("");
        s_NoRiskType.LoadString(IDS_NO_RISK_TYPE);

        pRisk = new ZBProperty(FinalRiskTitle,
            (GroupValue == true) ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                               RiskName,
                               (GroupValue == true) ? Z_RISK_TYPE : (Z_RISK_TYPE + (i * _MaxRisksSize)),
                               RiskDesc,
                               GetRiskType(i).IsEmpty() ? s_NoRiskType : GetRiskType(i),
                               ZBProperty::PT_EDIT_EXTENDED_READONLY);

        PropSet.Add(pRisk);

        RiskName.LoadString(IDS_Z_RISK_IMPACT_NAME);
        RiskDesc.LoadString(IDS_Z_RISK_IMPACT_DESC);

        // Propriété "Impact" du groupe "Risque (x)"
        pRisk = new ZBProperty(FinalRiskTitle,
            (GroupValue == true) ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                               RiskName,
                               (GroupValue == true) ? Z_RISK_IMPACT : (Z_RISK_IMPACT + (i * _MaxRisksSize)),
                               RiskDesc,
                               PSS_Application::Instance()->GetMainForm()->GetRiskImpactContainer()->GetElementAt(GetRiskImpact(i)),
                               ZBProperty::PT_EDIT_EXTENDED_READONLY);

        PropSet.Add(pRisk);

        RiskName.LoadString(IDS_Z_RISK_PROBABILITY_NAME);
        RiskDesc.LoadString(IDS_Z_RISK_PROBABILITY_DESC);

        // Propriété "Probabilité" du groupe "Risque (x)"
        pRisk = new ZBProperty(FinalRiskTitle,
            (GroupValue == true) ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                               RiskName,
                               (GroupValue == true) ? Z_RISK_PROBABILITY : (Z_RISK_PROBABILITY + (i * _MaxRisksSize)),
                               RiskDesc,
                               PSS_Application::Instance()->GetMainForm()->GetRiskProbabilityContainer()->GetElementAt(GetRiskProbability(i)),
                               ZBProperty::PT_EDIT_EXTENDED_READONLY);

        PropSet.Add(pRisk);

        RiskName.LoadString(IDS_Z_RISK_SEVERITY_NAME);
        RiskDesc.LoadString(IDS_Z_RISK_SEVERITY_DESC);

        // Propriété "Sévérité" du groupe "Risque (x)"
        pRisk = new ZBProperty(FinalRiskTitle,
            (GroupValue == true) ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                               RiskName,
                               (GroupValue == true) ? Z_RISK_SEVERITY : (Z_RISK_SEVERITY + (i * _MaxRisksSize)),
                               RiskDesc,
                               (double)GetRiskSeverity(i),
                               ZBProperty::PT_EDIT_NUMBER_READONLY);

        PropSet.Add(pRisk);

        RiskName.LoadString(IDS_Z_RISK_UE_NAME);
        RiskDesc.LoadString(IDS_Z_RISK_UE_DESC);

        // Propriété "Est. unit." du groupe "Risque (x)"
        pRisk = new ZBProperty(FinalRiskTitle,
            (GroupValue == true) ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                               RiskName,
                               (GroupValue == true) ? Z_RISK_UE : (Z_RISK_UE + (i * _MaxRisksSize)),
                               RiskDesc,
                               GetRiskUE(i),
                               ZBProperty::PT_EDIT_NUMBER,
                               true,
                               PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, CurrencySymbol));

        PropSet.Add(pRisk);

        RiskName.LoadString(IDS_Z_RISK_POA_NAME);
        RiskDesc.LoadString(IDS_Z_RISK_POA_DESC);

        // Propriété "POA" du groupe "Risque (x)"
        pRisk = new ZBProperty(FinalRiskTitle,
            (GroupValue == true) ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                               RiskName,
                               (GroupValue == true) ? Z_RISK_POA : (Z_RISK_POA + (i * _MaxRisksSize)),
                               RiskDesc,
                               GetRiskPOA(i),
                               ZBProperty::PT_EDIT_NUMBER,
                               true,
                               PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, CurrencySymbol));

        PropSet.Add(pRisk);

        RiskName.LoadString(IDS_Z_RISK_ACTION_NAME);
        RiskDesc.LoadString(IDS_Z_RISK_ACTION_DESC);

        // Propriété "Action" du groupe "Risque (x)"
        pRisk = new ZBProperty(FinalRiskTitle,
            (GroupValue == true) ? ZS_BP_PROP_RISK : (ZS_BP_PROP_RISK + i),
                               RiskName,
                               (GroupValue == true) ? Z_RISK_ACTION : (Z_RISK_ACTION + (i * _MaxRisksSize)),
                               RiskDesc,
                               (GetRiskAction(i) == true) ? PSS_Global::GetYesFromArrayYesNo() : PSS_Global::GetNoFromArrayYesNo(),
                               ZBProperty::PT_COMBO_STRING_READONLY,
                               TRUE,
                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                               PSS_Global::GetArrayYesNo());

        PropSet.Add(pRisk);
    }
    // ***********************************************************************************************************

    bool GroupEnabled = true;

    // First, check if the user group is valid
    if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
        !dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->MainUserGroupIsValid())
    {
        GroupEnabled = false;
    }

    ZBProperty* pUnitGUID = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                           ZS_BP_PROP_UNIT,
                                           IDS_Z_UNIT_GUID_NAME,
                                           Z_UNIT_GUID,
                                           IDS_Z_UNIT_GUID_DESC,
                                           GetUnitGUID(),
                                           ZBProperty::PT_EDIT_EXTENDED_READONLY,
                                           false); // Not enable, used for saving the unit GUID

    PropSet.Add(pUnitGUID);

    bool Error;

    CString UnitName = RetreiveUnitName(GetUnitGUID(), Error);
    ZBProperty* pUnitName = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                           ZS_BP_PROP_UNIT,
                                           IDS_Z_UNIT_NAME_NAME,
                                           Z_UNIT_NAME,
                                           IDS_Z_UNIT_NAME_DESC,
                                           UnitName,
                                           (GroupEnabled) ? ZBProperty::PT_EDIT_EXTENDED_READONLY : ZBProperty::PT_EDIT_STRING_READONLY);

    PropSet.Add(pUnitName);

    // RS-MODIF 17.11.04 UnitCost should only appear in Sesterces
    if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
        dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())

    {
        float UnitCost = RetreiveUnitCost(GetUnitGUID(), Error);
        ZBProperty* pUnitCost = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                               ZS_BP_PROP_UNIT,
                                               IDS_Z_UNIT_COST_NAME,
                                               Z_UNIT_COST,
                                               IDS_Z_UNIT_COST_DESC,
                                               UnitCost,
                                               ZBProperty::PT_EDIT_NUMBER_READONLY);

        PropSet.Add(pUnitCost);
    }

    return true;
}

bool ZBBPStartSymbol::SaveProperties(ZBPropertySet& PropSet)
{
    if (!ZBSymbol::SaveProperties(PropSet))
    {
        return false;
    }

    ZBProperty* pProp;

    // *************************************************************************************************************
    // JMR-MODIF - Le 11 juillet 2007 - Ajout du code pour la mise à jour des valeurs des risques.

    ZBPropertyIterator j(&PropSet);

    for (pProp = j.GetFirst(); pProp; pProp = j.GetNext())
    {
        if (pProp->GetCategoryID() >= ZS_BP_PROP_RISK &&
            pProp->GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount())
        {
            int i = pProp->GetCategoryID() - ZS_BP_PROP_RISK;

            if (pProp->GetItemID() == Z_RISK_NAME + (i * _MaxRisksSize))
            {
                SetRiskName(i, pProp->GetValueString());
            }

            if (pProp->GetItemID() == Z_RISK_DESC + (i * _MaxRisksSize))
            {
                SetRiskDesc(i, pProp->GetValueString());
            }

            if (pProp->GetItemID() == Z_RISK_UE + (i * _MaxRisksSize))
            {
                SetRiskUE(i, pProp->GetValueFloat());
            }

            if (pProp->GetItemID() == Z_RISK_POA + (i * _MaxRisksSize))
            {
                SetRiskPOA(i, pProp->GetValueFloat());
            }

            if (pProp->GetItemID() == Z_RISK_ACTION + (i * _MaxRisksSize))
            {
                SetRiskAction(i, (pProp->GetValueString() == PSS_Global::GetYesFromArrayYesNo() ? 1 : 0));
            }
        }
    }
    // *************************************************************************************************************

    // Now run through the list of data and fill the property set
    ZBPropertyIterator k(&PropSet);

    for (pProp = k.GetFirst(); pProp; pProp = k.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_UNIT)
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

    RefreshAttributeTextArea(true);

    return true;
}

bool ZBBPStartSymbol::SaveProperty(ZBProperty& Property)
{
    if (!ZBSymbol::SaveProperty(Property))
    {
        return false;
    }

    // JMR-MODIF - Le 9 mai 2007 - Seuls les symboles locaux ont accès aux propriétés.
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

        if (Property.GetItemID() == Z_RISK_NAME + (i * _MaxRisksSize))
        {
            SetRiskName(i, Property.GetValueString());
        }

        if (Property.GetItemID() == Z_RISK_DESC + (i * _MaxRisksSize))
        {
            SetRiskDesc(i, Property.GetValueString());
        }

        if (Property.GetItemID() == Z_RISK_UE + (i * _MaxRisksSize))
        {
            SetRiskUE(i, Property.GetValueFloat());
        }

        if (Property.GetItemID() == Z_RISK_POA + (i * _MaxRisksSize))
        {
            SetRiskPOA(i, Property.GetValueFloat());
        }

        if (Property.GetItemID() == Z_RISK_ACTION + (i * _MaxRisksSize))
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

    // Set the modified flag to true,
    // Do nothing more, the values will be saved by the save properties method
    SetModifiedFlag();

    return true;
}

bool ZBBPStartSymbol::CheckPropertyValue(ZBProperty& Property, CString& value, ZBPropertySet& Properties)
{
    return ZBSymbol::CheckPropertyValue(Property, value, Properties);
}

bool ZBBPStartSymbol::ProcessExtendedInput(ZBProperty& Property, CString& value, ZBPropertySet& Properties, bool& Refresh)
{
    // ****************************************************************************************************
    // JMR-MODIF - Le 13 juin 2007 - Ajout de la prise en charge des risques.

    if (Property.GetCategoryID() >= ZS_BP_PROP_RISK &&
        Property.GetCategoryID() <= ZS_BP_PROP_RISK + GetRiskCount())
    {
        int            i = Property.GetCategoryID() - ZS_BP_PROP_RISK;
        CODModel*    pModel = GetRootModel();
        CString        CurrencySymbol = PSS_Global::GetLocaleCurrency();

        if (pModel && ISA(pModel, ZDProcessGraphModelMdl))
        {
            CDocument* pDoc = dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetDocument();

            if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc))
            {
                // Retreive the model's currency symbol
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
        if (pModel && ISA(pModel, ZDProcessGraphModelMdl))
        {
            ZVSelectUserGroupDlg dlg(IDS_SELECTAGROUP_T,
                                     dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetMainUserGroup(),
                                     true,        // Allow group selection
                                     false);    // Doesn't allow role selection

            if (dlg.DoModal() == IDOK)
            {
                ZBUserEntity* pUserEntity = dlg.GetSelectedUserEntity();

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

    return ZBSymbol::ProcessExtendedInput(Property, value, Properties, Refresh);
}

// JMR-MODIF - Le 18 décembre 2006 - Ajout de la fonction ProcessMenuCommand.
bool ZBBPStartSymbol::ProcessMenuCommand(int                MenuCommand,
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

    return ZBSymbol::ProcessMenuCommand(MenuCommand, Property, value, Properties, Refresh);
}

// JMR-MODIF - Le 10 juin 2007 - Ajout de la fonction OnAddNewRisk.
void ZBBPStartSymbol::OnAddNewRisk(ZBProperty&        Property,
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
void ZBBPStartSymbol::OnDelCurrentRisk(ZBProperty&        Property,
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

bool ZBBPStartSymbol::OnPostPropertyChanged(ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh)
{
    bool RetValue = false;

    if (Property.GetCategoryID() == ZS_BP_PROP_UNIT && Property.GetItemID() == Z_UNIT_NAME)
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
                    float UnitCost = RetreiveUnitCost(GUID, Error);

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

    if (RetValue == false)
        return ZBSymbol::OnPostPropertyChanged(Property, Properties, Refresh);

    return RetValue;
}

// JMR-MODIF - Le 18 décembre 2006 - Cette fonction est appelée lorsque l'utilisateur a tenté de déplaçer une propriété.
bool ZBBPStartSymbol::OnDropInternalPropertyItem(ZBProperty&        SrcProperty,
                                                 ZBProperty&        DstProperty,
                                                 bool                Top2Down,
                                                 ZBPropertySet&    Properties)
{
    bool RetValue = ::SwapInternalPropertyItem(SrcProperty,
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

    return false;
}

bool ZBBPStartSymbol::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    toolTipText.Format(IDS_FS_BPSTART_TOOLTIP,
        (const char*)GetSymbolName(),
                       (const char*)GetSymbolComment(),
                       (const char*)GetSymbolReferenceNumberStr());

    if (mode == ZBSymbol::IE_TT_Design)
    {
        // From now do nothing,
        // need to implement the result of the control checking
        // TODO
    }

    return true;
}

void ZBBPStartSymbol::Serialize(CArchive& ar)
{
    // Serialize the canvas model.
    ZBSymbol::Serialize(ar);

    // Only if the object is serialize from and to a document
    if (ar.m_pDocument)
    {
        // JMR-MODIF - Le 10 juin 2007 - Ajout du code pour la sérialisation des risques.
        if (dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 27)
        {
            m_Risks.Serialize(ar);
        }

        if (ar.IsStoring() ||
            dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 19)
        {
            m_UnitProp.Serialize(ar);
        }
        else
        {
            // Transfert the properties to new format
            ZBBPUnitProperties* pUnitProps = (ZBBPUnitProperties*)GetProperty(ZS_BP_PROP_UNIT);

            if (pUnitProps)
            {
                SetUnitName(pUnitProps->GetUnitName());
                SetUnitCost(pUnitProps->GetUnitCost());
            }
        }

        // JMR-MODIF - Le 18 décembre 2006 - Ajout du système de règles.
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
    }
}
