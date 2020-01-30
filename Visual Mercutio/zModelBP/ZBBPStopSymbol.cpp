// ZBBPStopSymbol.cpp: implementation of the ZBBPStopSymbol class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "zBaseSym\zBaseSymRes.h"
#include "ZBBPStopSymbol.h"

// JMR-MODIF - Le 26 mai 2005 - D�finition de _ZMODELEXPORT, pour �viter une erreur interne du compilateur.
#define _ZMODELEXPORT
    #include "zModel\PSS_BasicProperties.h"
#undef _ZMODELEXPORT

// JMR-MODIF - Le 29 juillet 2007 - Ajout de l'en-t�te ZAGlobal.h
#include "zBaseLib\PSS_Global.h"

#include "PSS_UnitPropertiesBP_Beta1.h"
#include "zModel\PSS_UserGroupEntity.h"

// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"

// Global for model
#include "zModel\PSS_ModelGlobal.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_SelectUserGroupDlg.h"
#include "zBaseLib\PSS_MsgBox.h"

#include "PSS_ProcessGraphModelControllerBP.h"

#include "PSS_ProcessGraphModelMdlBP.h"

#include "ZVRiskOptionsDlg.h"

// Resources
#include "zModelBPRes.h"
#include "zModel\zModelRes.h"
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 6 octobre 2005 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBBPStopSymbol, PSS_Symbol, g_DefVersion)

// JMR-MODIF - Le 18 d�cembre 2006 - Ajout de la nouvelle variable statique gRulesMenu.
static CMenu gRulesMenu;
// JMR-MODIF - Le 10 juin 2007 - Ajout de la nouvelle variable statique gRiskMenu
static CMenu gRiskMenu;

// JMR-MODIF - Le 18 d�cembre 2006 - Ajout de la constante _MaxRulesSize.
const size_t _MaxRulesSize = 20;
// JMR-MODIF - Le 3 juin 2007 - Ajout de la constante _MaxRisksSize.
const size_t _MaxRisksSize = 20;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBBPStopSymbol::ZBBPStopSymbol(const CString Name /*= ""*/)
{
    PSS_Symbol::SetSymbolName(Name);

    // Change what to show first
    m_ShowNameArea = true;
    m_ShowDescriptionArea = false;
    m_ShowAttributeArea = true;

    // JMR-MODIF - Le 29 juillet 2007 - Ajout de l'appel � CreateSymbolProperties.
    CreateSymbolProperties();
}

ZBBPStopSymbol::~ZBBPStopSymbol()
{}

ZBBPStopSymbol::ZBBPStopSymbol(const ZBBPStopSymbol& src)
{
    *this = src;
}

ZBBPStopSymbol& ZBBPStopSymbol::operator=(const ZBBPStopSymbol& src)
{
    // Call the base class assignement operator
    PSS_Symbol::operator=((const PSS_Symbol&)src);

    m_UnitProp = src.m_UnitProp;

    // JMR-MODIF - Le 18 d�cembre 2006 - Ajout du code de copie pour les r�gles
    m_Rules = src.m_Rules;

    // JMR-MODIF - Le 29 juillet 2007 - Ajout du code de copie pour les risques
    m_Risks = src.m_Risks;

    return *this;
}

CODComponent* ZBBPStopSymbol::Dup() const
{
    return (new ZBBPStopSymbol(*this));
}

void ZBBPStopSymbol::CopySymbolDefinitionFrom(CODSymbolComponent& src)
{
    // Class the base class method
    PSS_Symbol::CopySymbolDefinitionFrom(src);

    if (ISA((&src), ZBBPStopSymbol))
    {
        m_UnitProp = ((ZBBPStopSymbol&)src).m_UnitProp;

        // JMR-MODIF - Le 18 d�cembre 2006 - Ajout de la copie de la variable m_Rules.
        m_Rules = ((ZBBPStopSymbol&)src).m_Rules;

        // JMR-MODIF - Le 29 juillet 2007 - Ajout du code de copie pour les risques
        m_Risks = ((ZBBPStopSymbol&)src).m_Risks;
    }
}

BOOL ZBBPStopSymbol::Create(const CString Name /*= ""*/)
{
    m_IsInCreationProcess = true;

    BOOL RetValue = PSS_Symbol::Create(IDR_BP_STOP,
                                     AfxFindResourceHandle(MAKEINTRESOURCE(IDR_UML_END_SYM), _T("Symbol")),
                                     Name);

    if (!CreateSymbolProperties())
    {
        RetValue = FALSE;
    }

    m_IsInCreationProcess = false;

    return RetValue;
}

bool ZBBPStopSymbol::OnFillDefaultAttributes(ZBPropertyAttributes* pAttributes)
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

bool ZBBPStopSymbol::OnChangeAttributes(ZBPropertyAttributes* pAttributes)
{
    return PSS_Symbol::OnChangeAttributes(pAttributes);
}

CString ZBBPStopSymbol::GetAttributeString(ZBPropertyAttributes* pAttributes) const
{
    return PSS_Symbol::GetAttributeString(pAttributes);
}

// Drag and drop methods
bool ZBBPStopSymbol::AcceptDropItem(CObject* pObj, const CPoint& pt)
{
    // JMR-MODIF - Le 18 d�cembre 2006 - Si le symbole n'est pas local, interdit l'op�ration de glisser-coller.
    if (!IsLocal())
    {
        return false;
    }

    // If a user entity
    if (pObj && ISA(pObj, PSS_UserGroupEntity))
    {
        return true;
    }

    // JMR-MODIF - Le 18 d�cembre 2006 - D�termine si l'objet re�u est un objet de type r�gle.
    if (pObj && ISA(pObj, PSS_LogicalRulesEntity))
    {
        return true;
    }

    // Otherwise, call the base class
    return PSS_Symbol::AcceptDropItem(pObj, pt);
}

bool ZBBPStopSymbol::DropItem(CObject* pObj, const CPoint& pt)
{
    if (pObj && ISA(pObj, PSS_UserGroupEntity))
    {
        // First, check if the user group is valid
        CODModel * pModel = GetRootModel();

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

    // **********************************************************************************************************
    // JMR-MODIF - Le 18 d�cembre 2006 - Ajout du code pour le traitement des objets de type r�gles.
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
    // **********************************************************************************************************

    return PSS_Symbol::DropItem(pObj, pt);
}

// JMR-MODIF - Le 25 d�cembre 2006 - Permet de rechercher le nom original d'une r�gle en fonction de son GUID.
CString ZBBPStopSymbol::GetRuleNameByGUID(PSS_LogicalRulesEntity* p_Rule, CString RuleGUID)
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

BOOL ZBBPStopSymbol::OnDoubleClick()
{
    return FALSE;
}

bool ZBBPStopSymbol::CreateSymbolProperties()
{
    if (!PSS_Symbol::CreateSymbolProperties())
    {
        return false;
    }

    PSS_UnitPropertiesBP_Beta1 propUnit;
    AddProperty(propUnit);

    // JMR-MODIF - Le 3 juin 2007 - Ajoute au moins un catalogue de propri�t�s dans les risques.
    m_Risks.CreateInitialProperties();

    return true;
}

// JMR-MODIF - Le 26 avril 2007 - Cette fonction permet de d�terminer si une r�gle donn�e a �t� attribu�e � cet objet.
BOOL ZBBPStopSymbol::ContainsRule(CString RuleName)
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

// JMR-MODIF - Le 9 octobre 2007 - Cette fonction retourne les r�gles qui ne sont plus synchronis�es avec le r�f�rentiel.
void ZBBPStopSymbol::CheckRulesSync(CStringArray& RulesList)
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

bool ZBBPStopSymbol::FillProperties(ZBPropertySet& PropSet, bool NumericValue /*= false*/, bool GroupValue /*= false*/)
{
    if (!PSS_Symbol::FillProperties(PropSet, NumericValue, GroupValue))
    {
        return false;
    }

    // JMR-MODIF - Le 29 juillet 2007 - Ajout du test de symbole local.
    // Only local symbol have access to properties
    if (!IsLocal())
    {
        return true;
    }

    // JMR-MODIF - Le 25 d�cembre 2006 - Ajout du mod�le.
    CODModel* pModel = GetRootModel();

    // Initialize the Currency symbol with the user local currency symbol
    // defined in the Control Panel
    CString CurrencySymbol = PSS_Global::GetLocaleCurrency();

    // JMR-MODIF - Le 30 juillet 2007 - Mets � jour le symbole mon�taire en fonction de la s�lection utilisateur.
    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl))
    {
        CDocument* pDoc = dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetDocument();

        if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc))
        {
            // Retrieve the model's currency symbol
            CurrencySymbol = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetCurrencySymbol();
        }
    }

    // ************************************************************************************************************
    // JMR-MODIF - Le 18 d�cembre 2006 - Nouvelle architecture des r�gles.

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

        PSS_LogicalRulesEntity* p_MainRule = NULL;

        if (GetOwnerModel() != NULL && ISA(GetOwnerModel(), PSS_ProcessGraphModelMdlBP))
        {
            PSS_ProcessGraphModelMdlBP* p_Model = reinterpret_cast<PSS_ProcessGraphModelMdlBP*>(GetOwnerModel());

            if (p_Model != NULL &&
                p_Model->GetController() != NULL &&
                ISA(p_Model->GetController(), PSS_ProcessGraphModelControllerBP))
            {
                PSS_ProcessGraphModelControllerBP* p_Controller =
                    reinterpret_cast<PSS_ProcessGraphModelControllerBP*>(p_Model->GetController());

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
            // Le contr�le des r�gles ne peut �tre appliqu� que si le mod�le est en phase avec le syst�me des r�gles.
            if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
                dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->MainLogicalRulesIsValid())
            {
                CString m_SafeName = GetRuleNameByGUID(p_MainRule, m_Rules.GetRuleGUID(i));

                // ********************************************************************************************
                // JMR-MODIF - Le 8 octobre 2007 - R��ctriture de la routine suite � un bug de perte de r�gles.
                // Avant, le test supprimait une r�gle qui n'�tait plus synchronis�e au r�f�rentiel, maintenant
                // seul le nom de la r�gle est contr�l� et renomm�, � condition qu'il soit synchronis� avec le
                // r�f�rentiel.
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

            // Propri�t� "R�gle x" du groupe "R�gles"
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
    // JMR-MODIF - Le 3 juin 2007 - Ajout des propri�t�s li�es aux risques.

    // Obtient le menu des risques si celui-ci n'est pas encore pr�sent.
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

        // Propri�t� "Titre Risque" du groupe "Risque (x)"
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

        // Propri�t� "Description" du groupe "Risque (x)"
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

        // Propri�t� "Impact" du groupe "Risque (x)"
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

        // Propri�t� "Probabilit�" du groupe "Risque (x)"
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

        // Propri�t� "S�v�rit�" du groupe "Risque (x)"
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

        // Propri�t� "Est. unit." du groupe "Risque (x)"
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

        // Propri�t� "POA" du groupe "Risque (x)"
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

        // Propri�t� "Action" du groupe "Risque (x)"
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
    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
        !dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->MainUserGroupIsValid())
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

    CString UnitName = RetrieveUnitName(GetUnitGUID(), Error);
    ZBProperty* pUnitName = new ZBProperty(IDS_ZS_BP_PROP_UNIT_TITLE,
                                           ZS_BP_PROP_UNIT,
                                           IDS_Z_UNIT_NAME_NAME,
                                           Z_UNIT_NAME,
                                           IDS_Z_UNIT_NAME_DESC,
                                           UnitName,
                                           (GroupEnabled) ? ZBProperty::PT_EDIT_EXTENDED_READONLY : ZBProperty::PT_EDIT_STRING_READONLY);

    PropSet.Add(pUnitName);

    // RS-MODIF 17.11.04 UnitCost should only appear in Sesterces
    if (pModel && ISA(pModel, PSS_ProcessGraphModelMdl) &&
        dynamic_cast<PSS_ProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())

    {
        float UnitCost = RetrieveUnitCost(GetUnitGUID(), Error);
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

bool ZBBPStopSymbol::SaveProperties(ZBPropertySet& PropSet)
{
    if (!PSS_Symbol::SaveProperties(PropSet))
    {
        return false;
    }

    ZBProperty* pProp;

    // *************************************************************************************************************
    // JMR-MODIF - Le 11 juillet 2007 - Ajout du code pour la mise � jour des valeurs des risques.

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

bool ZBBPStopSymbol::SaveProperty(ZBProperty& Property)
{
    if (!PSS_Symbol::SaveProperty(Property))
    {
        return false;
    }

    // JMR-MODIF - Le 9 mai 2007 - Seuls les symboles locaux ont acc�s aux propri�t�s.
    if (!IsLocal())
    {
        return true;
    }

    // ************************************************************************************************
    // JMR-MODIF - Le 17 juillet 2007 - Mise � jour des valeurs des propri�t�s des risques.

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

    // JMR-MODIF - Le 9 mai 2007 - Contr�le si l'utilisateur a tent� de renommer une r�gle.
    // Si c'est le cas, r�etablit le nom d'origine.
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

bool ZBBPStopSymbol::CheckPropertyValue(ZBProperty& Property, CString& value, ZBPropertySet& Properties)
{
    return PSS_Symbol::CheckPropertyValue(Property, value, Properties);
}

bool ZBBPStopSymbol::ProcessExtendedInput(ZBProperty& Property, CString& value, ZBPropertySet& Properties, bool& Refresh)
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
                                       true,        // Allow group selection
                                       false);    // Doesn't allow role selection

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

    return PSS_Symbol::ProcessExtendedInput(Property, value, Properties, Refresh);
}

// JMR-MODIF - Le 18 d�cembre 2006 - Ajout de la fonction ProcessMenuCommand.
bool ZBBPStopSymbol::ProcessMenuCommand(int            MenuCommand,
                                        ZBProperty&    Property,
                                        CString&        value,
                                        ZBPropertySet&    Properties,
                                        bool&            Refresh)
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

                // JMR-MODIF - Le 8 mai 2007 - Demande le rafra�chissement apr�s ex�cution de l'op�ration.
                Refresh = true;

                break;
            }

            default:
            {
                break;
            }
        }
    }

    return PSS_Symbol::ProcessMenuCommand(MenuCommand, Property, value, Properties, Refresh);
}

// JMR-MODIF - Le 10 juin 2007 - Ajout de la fonction OnAddNewRisk.
void ZBBPStopSymbol::OnAddNewRisk(ZBProperty&        Property,
                                  CString&            value,
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
void ZBBPStopSymbol::OnDelCurrentRisk(ZBProperty&        Property,
                                      CString&            value,
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

bool ZBBPStopSymbol::OnPostPropertyChanged(ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh)
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

    if (RetValue == false)
    {
        return PSS_Symbol::OnPostPropertyChanged(Property, Properties, Refresh);
    }

    return RetValue;
}

// JMR-MODIF - Le 18 d�cembre 2006 - Cette fonction est appel�e lorsque l'utilisateur a tent� de d�pla�er une propri�t�.
bool ZBBPStopSymbol::OnDropInternalPropertyItem(ZBProperty&    SrcProperty,
                                                ZBProperty&    DstProperty,
                                                bool            Top2Down,
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

bool ZBBPStopSymbol::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    toolTipText.Format(IDS_FS_BPSTOP_TOOLTIP,
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

void ZBBPStopSymbol::Serialize(CArchive& ar)
{
    // Serialize the canvas model.
    PSS_Symbol::Serialize(ar);

    // Only if the object is serialize from and to a document
    if (ar.m_pDocument)
    {
        // JMR-MODIF - Le 10 juin 2007 - Ajout du code pour la s�rialisation des risques.
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
            PSS_UnitPropertiesBP_Beta1* pUnitProps = (PSS_UnitPropertiesBP_Beta1*)GetProperty(ZS_BP_PROP_UNIT);

            if (pUnitProps)
            {
                SetUnitName(pUnitProps->GetUnitName());
                SetUnitCost(pUnitProps->GetUnitCost());
            }
        }

        // JMR-MODIF - Le 18 d�cembre 2006 - Ajout du syst�me de r�gles.
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
