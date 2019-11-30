// ZBBPProcessSymbol.cpp: implementation of the ZBBPProcessSymbol class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "zBaseSym\zBaseSymRes.h"
#include "ZBBPProcessSymbol.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"

// JMR-MODIF - Le 26 mai 2005 - Définition de _ZMODELEXPORT, pour éviter une erreur interne du compilateur.
#define _ZMODELEXPORT
#include "zModel\ZBBasicProp.h"
#undef _ZMODELEXPORT

#include "ZBBPProcessProp.h"
#include "ZBBPSimPropProcess.h"
#include "zModel\ZBDocObserverMsg.h"

// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"

// Global for model
#include "zModel\ZAModelGlobal.h"

// JMR-MODIF - Le 25 janvier 2006 - Ajout des en-têtes pour la gestion des prestations.
#include "zModel\ZBPrestationsEntity.h"

// JMR-MODIF - Le 6 février 2006 - Ajout des en-têtes pour la gestion des livraisons.
#include "ZBBPDeliveriesProp.h"

// JMR-MODIF - Le 9 février 2006 - Ajout de l'en-tête pour l'intégration des livrables.
#include "ZBDeliverableLinkSymbol.h"

// JMR-MODIF - Le 9 janvier 2006 - Ajout de l'en-tête pour la prise en charge des Tokens.
#include "zBaseLib\PSS_Tokenizer.h"

// JMR-MODIF - Le 13 février 2006 - Ajout de la déclaration pour les boîtes de dialogue des livraisons.
#include "ZVAddRemoveDeliveryDeliverablesDlg.h"
#include "ZVChooseMainDeliverable.h"

// JMR-MODIF - Le 15 février 2006 - Ajout de l'en-tête pour la prise en charge des modèles de pages.
#include "zModel\ZDProcessGraphPage.h"

// JMR-MODIF - Le 25 décembre 2006 - Ajout de l'en-tête ProcGraphModelCtlrBP.h
#include "ProcGraphModelCtlrBP.h"

// JMR-MODIF - Le 13 juin 2007 - Ajout de l'en-tête ZVRiskOptionsDlg.h
#include "ZVRiskOptionsDlg.h"

// Resources
#include "zModel\zModelRes.h"
#include "zModelBPRes.h"
#include "PSS_ModelResIDs.h"

#include "zBaseLib\PSS_Global.h"

#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 26 septembre 2005 - Ajout des décorations unicode _T( ), suppression du code inutile (en commentaires).

// JMR-MODIF - Le 6 février 2006 - Ajout de la déclaration des variables statiques et globales.
static CMenu    gDeliveriesMenu;
static CMenu    gPrestationsMenu;
// JMR-MODIF - Le 18 décembre 2006 - Ajout de la nouvelle variable statique gRulesMenu.
static CMenu    gRulesMenu;
// JMR-MODIF - Le 10 juin 2007 - Ajout de la nouvelle variable statique gRiskMenu
static CMenu    gRiskMenu;

const size_t    _MaxDeliveryListSize = 20;
// JMR-MODIF - Le 18 décembre 2006 - Ajout de la constante _MaxRulesSize.
const size_t    _MaxRulesSize = 20;
// JMR-MODIF - Le 3 juin 2007 - Ajout de la constante _MaxRisksSize.
const size_t    _MaxRisksSize = 20;

IMPLEMENT_SERIAL(ZBBPProcessSymbol, ZBSymbol, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBBPProcessSymbol::ZBBPProcessSymbol(const CString Name /*= ""*/)
    : m_DisplayPreview(false),
    // JMR-MODIF - Le 6 février 2006 - Initialise m_Deliveries, m_AttribuedDeliverables et m_IsUserModified.
    m_Deliveries(this),
    m_IsUserModified(false)
{
    ZBSymbol::SetSymbolName(Name);
    CreateSymbolProperties();
}

ZBBPProcessSymbol::~ZBBPProcessSymbol()
{
    // JMR-MODIF - Le 31 janvier 2006 - Ajout du code de destruction pour les prestations.
    m_PrestProperties.RemoveAll();

    // JMR-MODIF - Le 7 février 2006 - Ajout du test pour déterminer si l'objet est une copie d'un autre objet.
    // Si c'est le cas, il ne faut pas essayer de détruire le modèle, qui est déjà détruit dans l'objet principal.
    if (IsCopy() == FALSE)
    {
        // JMR-MODIF - Le 28 septembre 2005 - Nettoyage des memory leaks, ajout du code de nettoyage de l'objet.
        if (m_pModel != NULL)
        {
            delete m_pModel;
            m_pModel = NULL;
        }
    }
}

ZBBPProcessSymbol::ZBBPProcessSymbol(const ZBBPProcessSymbol& src)
{
    *this = src;
}

ZBBPProcessSymbol& ZBBPProcessSymbol::operator=(const ZBBPProcessSymbol& src)
{
    // Call the base class assignement operator
    ZBSymbol::operator=((const ZBSymbol&)src);

    // JMR-MODIF - Le 6 février 2006 - Copie la variable m_PrestProperties.
    m_PrestProperties = src.m_PrestProperties;

    // JMR-MODIF - Le 6 février 2006 - Copie la variable m_Deliveries.
    m_Deliveries = src.m_Deliveries;

    // JMR-MODIF - Le 18 décembre 2006 - Ajout du code de copie pour les règles
    m_Rules = src.m_Rules;

    // JMR-MODIF - Le 29 juillet 2007 - Ajout du code de copie pour les risques
    m_Risks = src.m_Risks;

    return *this;
}

CODComponent* ZBBPProcessSymbol::Dup() const
{
    return (new ZBBPProcessSymbol(*this));
}

bool ZBBPProcessSymbol::OnFillDefaultAttributes(ZBPropertyAttributes* pAttributes)
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
    }

    return ZBSymbol::OnFillDefaultAttributes(pAttributes);
}

bool ZBBPProcessSymbol::OnChangeAttributes(ZBPropertyAttributes* pAttributes)
{
    return ZBSymbol::OnChangeAttributes(pAttributes);
}

CString ZBBPProcessSymbol::GetAttributeString(ZBPropertyAttributes* pAttributes) const
{
    return ZBSymbol::GetAttributeString(pAttributes);
}

bool ZBBPProcessSymbol::CreateSymbolProperties()
{
    if (!ZBSymbol::CreateSymbolProperties())
    {
        return false;
    }

    ZBBPProcessProperties propProcess;
    AddProperty(propProcess);

    // JMR-MODIF - Le 6 février 2006 - Ajoute au moins un catalogue de propriétés dans les livraisons.
    m_Deliveries.CreateInitialProperties();

    // JMR-MODIF - Le 3 juin 2007 - Ajoute au moins un catalogue de propriétés dans les risques.
    m_Risks.CreateInitialProperties();

    return true;
}

// JMR-MODIF - Le 20 février 2006 - Obtention des noms de toutes les prestations contenues dans ce processus.
PSS_Tokenizer ZBBPProcessSymbol::GetPrestationsList()
{
    PSS_Tokenizer aToken(_T(""));

    POSITION    myPos = m_PrestProperties.GetHeadPosition();
    int            i = 0;

    while (myPos != NULL)
    {
        ZBBPPrestationNode* myCurNode = m_PrestProperties.GetAt(myPos);

        if (myCurNode != NULL)
        {
            aToken.AddToken(myCurNode->GetPrestationName());
        }

        myPos = m_PrestProperties.GetNextPosition();
    }

    return aToken;
}

// Drag and drop methods
bool ZBBPProcessSymbol::AcceptDropItem(CObject* pObj, const CPoint& pt)
{
    // JMR-MODIF - Le 21 avril 2006 - Si le symbole n'est pas local, interdit l'opération de glisser-coller.
    if (!IsLocal())
    {
        return false;
    }

    // JMR-MODIF - Le 25 janvier 2006 - Teste s'il s'agit d'une entité de type prestation.
    if (pObj && ISA(pObj, ZBPrestationsEntity))
    {
        return true;
    }

    // JMR-MODIF - Le 18 décembre 2006 - Détermine si l'objet reçu est un objet de type règle.
    if (pObj && ISA(pObj, ZBLogicalRulesEntity))
    {
        return true;
    }

    // Call the base class
    return ZBSymbol::AcceptDropItem(pObj, pt);
}

bool ZBBPProcessSymbol::DropItem(CObject* pObj, const CPoint& pt)
{
    // **********************************************************************************************************
    // JMR-MODIF - Le 25 janvier 2006 - Effectue la modification des données pour les entités de type prestation.
    if (pObj && ISA(pObj, ZBLogicalPrestationsEntity))
    {
        // D'abord, teste si l'entité est valide.
        CODModel * pModel = GetRootModel();

        if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
            !dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->MainLogicalPrestationsIsValid())
        {
            // L'entité n'est pas valide.
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDROP_PRESTATIONSNOTINLINE, MB_OK);
            return false;
        }

        ZBLogicalPrestationsEntity* pPrestations = dynamic_cast<ZBLogicalPrestationsEntity*>(pObj);

        ZBBPPrestationNode* m_Prestation = new ZBBPPrestationNode();

        m_Prestation->SetPrestationName(pPrestations->GetEntityName());
        m_Prestation->SetPrestationGUID(pPrestations->GetGUID());

        m_PrestProperties.AddPrestation(m_Prestation);

        // Set flag for modification
        SetModifiedFlag(TRUE);

        // Refresh the attribute area and redraw the symbol
        RefreshAttributeTextArea(true);

        return true;
    }
    // **********************************************************************************************************

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

void ZBBPProcessSymbol::CopySymbolDefinitionFrom(CODSymbolComponent& src)
{
    // Class the base class method
    ZBSymbol::CopySymbolDefinitionFrom(src);

    if (ISA((&src), ZBBPProcessSymbol))
    {
        m_DisplayPreview = ((ZBBPProcessSymbol&)src).m_DisplayPreview;
        m_CommentRect = ((ZBBPProcessSymbol&)src).m_CommentRect;
        m_SimProperties = ((ZBBPProcessSymbol&)src).m_SimProperties;

        // JMR-MODIF - Le 6 février 2006 - Copie aussi les propriétés des prestations.
        m_PrestProperties = ((ZBBPProcessSymbol&)src).m_PrestProperties;

        // JMR-MODIF - Le 6 février 2006 - Copie aussi les propriétés de livraisons.
        m_Deliveries = dynamic_cast<ZBBPProcessSymbol&>(src).m_Deliveries;
        m_Deliveries.SetParent(this);

        // JMR-MODIF - Le 18 décembre 2006 - Ajout de la copie de la variable m_Rules.
        m_Rules = ((ZBBPProcessSymbol&)src).m_Rules;

        // JMR-MODIF - Le 29 juillet 2007 - Ajout du code de copie pour les risques
        m_Risks = ((ZBBPProcessSymbol&)src).m_Risks;
    }
}

BOOL ZBBPProcessSymbol::SetSymbolName(const CString value)
{
    // Change the model name first
    if (m_pModel && ISA(m_pModel, ZDProcessGraphModelMdl))
    {
        dynamic_cast<ZDProcessGraphModelMdl*>(m_pModel)->SetModelName(value);
    }

    // Then, the symbol name
    BOOL bResult = ZBSymbol::SetSymbolName(value);

    return bResult;
}

BOOL ZBBPProcessSymbol::Create(const CString Name /*= ""*/)
{
    m_IsInCreationProcess = true;

    BOOL RetValue = ZBSymbol::Create(IDR_BP_PROCESS,
                                     AfxFindResourceHandle(MAKEINTRESOURCE(IDR_PROCESS_SYM), _T("Symbol")),
                                     Name);

    if (!CreateSymbolProperties())
    {
        RetValue = FALSE;
    }

    m_IsInCreationProcess = false;

    return RetValue;
}

bool ZBBPProcessSymbol::OnPostCreation(CODModel* pModel /*= NULL*/, CODController* pCtrl /*= NULL*/)
{
    if (!ZBSymbol::OnPostCreation(pModel, pCtrl))
    {
        return false;
    }

    if (pModel && ISA(pModel, ZDProcessGraphModelMdlBP))
    {
        ZDProcessGraphModelMdlBP* pRootModel =
            reinterpret_cast<ZDProcessGraphModelMdlBP*>(reinterpret_cast<ZDProcessGraphModelMdlBP*>(pModel)->GetRoot());

        if (!pRootModel)
        {
            return false;
        }

        CreateEmptyChildModel(reinterpret_cast<ZDProcessGraphModelMdlBP*>(pModel));

        // If a new model is defined, create the first page
        if (m_pModel && !reinterpret_cast<ZDProcessGraphModelMdl*>(m_pModel)->HasPageSet())
        {
            pRootModel->CreateNewPage(reinterpret_cast<ZDProcessGraphModelMdl*>(m_pModel),
                                      _T(""),
                                      reinterpret_cast<ZDProcessGraphModelMdl*>(m_pModel));
        }

        return true;
    }

    return false;
}

// JMR-MODIF - Le 10 février 2006 - Ajout de la fonction de traitement des entrées boutons pour les propriétés.
bool ZBBPProcessSymbol::ProcessExtendedInput(ZBProperty&        Property,
                                             CString&            value,
                                             ZBPropertySet&    Properties,
                                             bool&                Refresh)
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

    if (Property.GetCategoryID() >= ZS_BP_PROP_DELIVERIES &&
        Property.GetCategoryID() <= ZS_BP_PROP_DELIVERIES + GetDeliveriesCount())
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_DELIVERIES;

        switch (Property.GetItemID() - (i * _MaxDeliveryListSize))
        {
            case Z_DELIVERY_DELIVERABLES:
            {
                CString m_AvailableList = GetAvailableDeliverables(Properties);

                // Ouvre la boîte de dialogue ajout/suppression des livrables.
                ZVAddRemoveDeliveryDeliverablesDlg m_Dlg(m_AvailableList, value);

                if (m_Dlg.DoModal() == IDOK)
                {
                    value = m_Dlg.GetDeliverables();
                    m_IsUserModified = true;

                    return true;
                }

                break;
            }

            case Z_DELIVERY_MAIN:
            {
                CString m_MainList = GetPossibleListOfMainDeliverables(Properties, Property.GetCategoryID());

                // Ouvre la boîte de dialogue de définition du livrable maître.
                ZVChooseMainDeliverable m_Dlg(m_MainList, value);

                if (m_Dlg.DoModal() == IDOK)
                {
                    value = m_Dlg.GetMain();
                    return true;
                }

                break;
            }

            default:
            {
                break;
            }
        }
    }

    return ZBSymbol::ProcessExtendedInput(Property, value, Properties, Refresh);
}

// JMR-MODIF - Le 10 février 2006 - Ajout de la fonction de traitement des entrées menus pour les propriétés.
bool ZBBPProcessSymbol::ProcessMenuCommand(int                MenuCommand,
                                           ZBProperty&        Property,
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

    // ************************************************************************************************************
    // JMR-MODIF - Le 20 mars 2006 - Ajout de la prise en charge du menu des prestations.

    if (Property.GetCategoryID() == ZS_BP_PROP_PRESTATIONS && Property.GetItemID() == Z_PRESTATION_NAME)
    {
        switch (MenuCommand)
        {
            case ID_DEL_CURRENTPRESTATION:
            {
                OnDelCurrentPrestation(Property, value, Properties, Refresh);
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

    // ************************************************************************************************************
    // JMR-MODIF - Le 6 février 2006 - Ajout du code pour traitement du menu des livraisons.

    if (Property.GetCategoryID() >= ZS_BP_PROP_DELIVERIES &&
        Property.GetCategoryID() <= ZS_BP_PROP_DELIVERIES + GetDeliveriesCount())
    {
        switch (MenuCommand)
        {
            case ID_ADD_NEWDELIVERY:
            {
                OnAddNewDelivery(Property, value, Properties, Refresh);
                break;
            }

            case ID_DEL_CURRENTDELIVERY:
            {
                OnDelCurrentDelivery(Property, value, Properties, Refresh);
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

    // ************************************************************************************************************
    // JMR-MODIF - Le 18 décembre 2006 - Ajout du code pour traitement de la fonction supprimer du menu des règles.

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

    return ZBSymbol::ProcessMenuCommand(MenuCommand, Property, value, Properties, Refresh);
}

// JMR-MODIF - Le 18 décembre 2006 - Cette fonction est appelée lorsque l'utilisateur a tenté de déplaçer une propriété.
bool ZBBPProcessSymbol::OnDropInternalPropertyItem(ZBProperty&        SrcProperty,
                                                   ZBProperty&        DstProperty,
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

// JMR-MODIF - Le 10 juin 2007 - Ajout de la fonction OnAddNewRisk.
void ZBBPProcessSymbol::OnAddNewRisk(ZBProperty&        Property,
                                     CString&            value,
                                     ZBPropertySet&    Properties,
                                     bool&                Refresh)
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
void ZBBPProcessSymbol::OnDelCurrentRisk(ZBProperty&        Property,
                                         CString&            value,
                                         ZBPropertySet&    Properties,
                                         bool&                Refresh)
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

// JMR-MODIF - Le 20 mars 2006 - Ajout de la fonction OnDelCurrentPrestation.
void ZBBPProcessSymbol::OnDelCurrentPrestation(ZBProperty&        Property,
                                               CString&        value,
                                               ZBPropertySet&    Properties,
                                               bool&            Refresh)
{
    POSITION    myPos = m_PrestProperties.GetHeadPosition();
    int            i = 0;

    while (myPos != NULL)
    {
        ZBBPPrestationNode* myCurNode = m_PrestProperties.GetAt(myPos);

        switch (Property.GetPTValueType())
        {
            case ZBProperty::PT_STRING:
            {
                if (Property.GetValueString() == myCurNode->GetPrestationName())
                {
                    m_PrestProperties.RemovePrestation(myPos);

                    // Sets the refresh flag to true
                    Refresh = true;
                    SetModifiedFlag(TRUE);

                    return;
                }

                break;
            }

            default:
            {
                break;
            }
        }

        myPos = m_PrestProperties.GetNextPosition();
    }
}

// JMR-MODIF - Le 15 février 2006 - Ajout de la fonction OnAddNewDelivery.
void ZBBPProcessSymbol::OnAddNewDelivery(ZBProperty&        Property,
                                         CString&            value,
                                         ZBPropertySet&    Properties,
                                         bool&                Refresh)
{
    // Add a new delivery
    if (AddNewDelivery() >= 0)
    {
        // Sets the refresh flag to true
        Refresh = true;
        SetModifiedFlag(TRUE);
    }
}

// JMR-MODIF - Le 15 février 2006 - Ajout de la fonction OnDelCurrentDelivery.
void ZBBPProcessSymbol::OnDelCurrentDelivery(ZBProperty&        Property,
                                             CString&            value,
                                             ZBPropertySet&    Properties,
                                             bool&                Refresh)
{
    int Count = GetDeliveriesCount();

    if (Count <= 1)
    {
        // Cannot delete all deliveries
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOTDELETE_ALLDELIVERIES, MB_OK);
        return;
    }

    // Otherwise, delete the current selected delivery
    int Index = Property.GetCategoryID() - ZS_BP_PROP_DELIVERIES;

    if (DeleteDelivery(Index))
    {
        // Sets the refresh flag to true
        Refresh = true;
        SetModifiedFlag(TRUE);
    }
}

// JMR-MODIF - Le 27 mars 2006 - Cette fonction est appelée lorsque le nom d'un livrable a changé.
void ZBBPProcessSymbol::OnDeliverableNameChange(CString OldName, CString NewName)
{
    for (int i = 0; i < GetDeliveriesCount(); i++)
    {
        PSS_Tokenizer m_OldDeliverablesList(GetDeliveryDeliverables(i));
        PSS_Tokenizer m_NewDeliverablesList(_T(""));

        for (size_t j = 0; j < m_OldDeliverablesList.GetTokenCount(); j++)
        {
            CString m_CurName = _T("");

            m_OldDeliverablesList.GetTokenAt(j, m_CurName);

            if (m_CurName == OldName)
            {
                m_NewDeliverablesList.AddToken(NewName);

                if (GetDeliveryMain(i) == OldName)
                {
                    SetDeliveryMain(i, NewName);
                }
            }
            else
            {
                m_NewDeliverablesList.AddToken(m_CurName);
            }
        }

        SetDeliveryDeliverables(i, m_NewDeliverablesList.GetString());
    }
}

// JMR-MODIF - Le 10 février 2006 - Ajout de la fonction permettant l'obtention de la quantité du livrable principal.
float ZBBPProcessSymbol::FindQuantity(const CString Main, ZDProcessGraphModelMdlBP* m_RootModel /* = NULL */)
{
    // Si le nom est vide, retourne 0.
    if (Main.IsEmpty())
    {
        return 0.0f;
    }

    // Si le modèle d'entrée est vide, cela veut dire que l'on veut une recherche sur tout le document.
    if (m_RootModel == NULL)
    {
        // Obtient le contrôleur de modèles du document.
        m_RootModel = dynamic_cast<ZDProcessGraphModelMdlBP*>(GetRootModel());
    }

    if (m_RootModel != NULL)
    {
        // Obtient l'ensemble des pages contenues dans le contrôleur de modèles.
        ZBProcessGraphPageSet* pSet = m_RootModel->GetPageSet();

        if (pSet != NULL)
        {
            ZBProcessGraphPageIterator i(pSet);

            // On passe en revue toutes les pages enfants contenues dans le contrôleur de modèles.
            for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
            {
                // Obtient le contrôleur de modèle de la page courante.
                ZDProcessGraphModelMdlBP* m_CurModel = dynamic_cast<ZDProcessGraphModelMdlBP*>(pPage->GetModel());

                if (m_CurModel != NULL)
                {
                    // Obtient l'ensemble des symboles contenus dans le contrôleur de modèles.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    if (pCompSet != NULL)
                    {
                        // On passe en revue toutes les symboles contenus dans le contrôleur de modèles.
                        for (int j = 0; j < pCompSet->GetSize(); ++j)
                        {
                            CODComponent* pComponent = pCompSet->GetAt(j);

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'un livrable.
                            if (pComponent && ISA(pComponent, ZBDeliverableLinkSymbol))
                            {
                                // Contrôle si le nom du livrable est identique à celui recherché, et si ce n'est
                                // pas une copie.
                                if (dynamic_cast<ZBDeliverableLinkSymbol*>(pComponent)->GetSymbolName() == Main &&
                                    dynamic_cast<ZBDeliverableLinkSymbol*>(pComponent)->IsLocal() == true)
                                {
                                    // Obtient et retourne la quantité du livrable principal.
                                    return (float)(dynamic_cast<ZBDeliverableLinkSymbol*>(pComponent)->GetQuantity());
                                }
                            }

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'un processus.
                            if (pComponent && ISA(pComponent, ZBBPProcessSymbol))
                            {
                                float Result = 0.0f;

                                // Convertit le symbole.
                                ZBBPProcessSymbol* m_Process = dynamic_cast<ZBBPProcessSymbol*>(pComponent);

                                // Obtient le contrôleur de modèle du processus.
                                ZDProcessGraphModelMdlBP* m_ChildModel =
                                    dynamic_cast<ZDProcessGraphModelMdlBP*>(m_Process->GetModel());

                                // Appel récursif à FindQuantity, jusqu'à ce que toutes les pages des processus
                                // enfants aient été visitées, ou que le livrable original ait été trouvé.
                                Result = FindQuantity(Main, m_ChildModel);

                                // L'original n'est peut-être pas dans cet ensemble de pages si le résultat vaut 0.
                                // Alors, il faut continuer à chercher.
                                if (Result != 0.0f)
                                {
                                    return Result;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0.0f;
}

// JMR-MODIF - Le 9 février 2006 - Ajout de la fonction d'obtention des livrables dans les pages dépendantes.
int ZBBPProcessSymbol::GetDeliverablesInChildPages(CString& DeliverablesList)
{
    int            Counter = 0;
    PSS_Tokenizer    Token;

    // Obtient le contrôleur de modèles du processus.
    ZDProcessGraphModelMdlBP* m_RootChldModel = dynamic_cast<ZDProcessGraphModelMdlBP*>(m_pModel);

    if (m_RootChldModel != NULL)
    {
        // Obtient l'ensemble des pages contenues dans le contrôleur de modèles.
        ZBProcessGraphPageSet* pSet = m_RootChldModel->GetPageSet();

        if (pSet != NULL)
        {
            ZBProcessGraphPageIterator i(pSet);

            // On passe en revue toutes les pages enfants contenues dans le contrôleur de modèles.
            for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
            {
                // Obtient le contrôleur de modèle de la page courante.
                ZDProcessGraphModelMdlBP* m_CurModel = dynamic_cast<ZDProcessGraphModelMdlBP*>(pPage->GetModel());

                if (m_CurModel != NULL)
                {
                    // Obtient l'ensemble des symboles contenus dans la page.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    // On passe en revue chacun des symboles de la page.
                    for (int j = 0; j < pCompSet->GetSize(); ++j)
                    {
                        CODComponent* pComponent = pCompSet->GetAt(j);

                        // Si le symbole courant est valide, et si c'est un livrable, alors on le prend en compte.
                        if (pComponent && ISA(pComponent, ZBDeliverableLinkSymbol))
                        {
                            BOOL IsTokenAlreadyExist = FALSE;
                            CString m_Name = dynamic_cast<ZBDeliverableLinkSymbol*>(pComponent)->GetSymbolName();

                            // Passe en revue tous les noms inscrit, et vérifie que le nouveau nom n'existe pas
                            // déjà dans la liste.
                            for (int k = 0; k < Token.GetTokenCount(); k++)
                            {
                                CString m_Src = _T("");
                                Token.GetTokenAt(k, m_Src);

                                if (m_Src == m_Name)
                                {
                                    IsTokenAlreadyExist = TRUE;
                                }
                            }

                            // Si le nouveau nom n'existe pas, on l'inscrit dans la liste.
                            if (IsTokenAlreadyExist == FALSE)
                            {
                                Token.AddToken(m_Name);
                                Counter++;
                            }

                            IsTokenAlreadyExist = FALSE;
                        }
                    }
                }
            }
        }
    }

    DeliverablesList = Token.GetString();

    return Counter;
}

// JMR-MODIF - Le 16 février 2006 - Ajout de la fonction permettant de récupérer la liste des livrables principaux.
CString ZBBPProcessSymbol::GetPossibleListOfMainDeliverables(ZBPropertySet& PropSet, int nCatID)
{
    ZBPropertyIterator i(&PropSet);

    for (ZBProperty* pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (pProp->GetCategoryID() == nCatID)
        {
            int j = pProp->GetCategoryID() - ZS_BP_PROP_DELIVERIES;

            if ((pProp->GetItemID() - (j * _MaxDeliveryListSize)) == Z_DELIVERY_DELIVERABLES)
            {
                switch (pProp->GetPTValueType())
                {
                    case ZBProperty::PT_STRING:
                    {
                        return pProp->GetValueString();
                    }

                    default:
                    {
                        return _T("");
                    }
                }
            }
        }
    }

    return _T("");
}

// JMR-MODIF - Le 16 février 2006 - Ajout de la fonction permettant de récupérer la liste des livrables disponibles.
CString ZBBPProcessSymbol::GetAvailableDeliverables(ZBPropertySet& PropSet)
{
    CString DeliverableList = _T("");
    CString AttribuedDeliverables = _T("");

    GetDeliverablesInChildPages(DeliverableList);

    ZBPropertyIterator i(&PropSet);

    // Construit la liste contenant tous les livrables déjà attribués.
    for (ZBProperty* pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (pProp->GetCategoryID() >= ZS_BP_PROP_DELIVERIES &&
            pProp->GetCategoryID() <= ZS_BP_PROP_DELIVERIES + GetDeliveriesCount())
        {
            int j = pProp->GetCategoryID() - ZS_BP_PROP_DELIVERIES;

            if ((pProp->GetItemID() - (j * _MaxDeliveryListSize)) == Z_DELIVERY_DELIVERABLES)
            {
                switch (pProp->GetPTValueType())
                {
                    case ZBProperty::PT_STRING:
                    {
                        CString m_List = pProp->GetValueString();

                        if (!m_List.IsEmpty())
                        {
                            AttribuedDeliverables += m_List + _T(";");
                        }

                        break;
                    }

                    default:
                    {
                        break;
                    }
                }
            }
        }
    }

    PSS_Tokenizer srcToken(DeliverableList);
    PSS_Tokenizer cmpToken(AttribuedDeliverables);
    PSS_Tokenizer rstToken(_T(""));

    // Compare la liste des livrables déjà attribués avec la liste de tous les livrables contenus dans
    // les pages enfants du processus. Ceux qui ne figurent pas dans la liste des livrables attribués
    // sont ajoutés à la liste des livrables disponibles.
    for (size_t j = 0; j < srcToken.GetTokenCount(); j++)
    {
        BOOL bIsAttribued = FALSE;

        CString m_Src = _T("");
        srcToken.GetTokenAt(j, m_Src);

        for (size_t k = 0; k < cmpToken.GetTokenCount(); k++)
        {
            CString m_Cmp = _T("");
            cmpToken.GetTokenAt(k, m_Cmp);

            if (m_Src == m_Cmp)
            {
                bIsAttribued = TRUE;
            }
        }

        if (bIsAttribued != TRUE)
        {
            rstToken.AddToken(m_Src);
        }

        bIsAttribued = FALSE;
    }

    return rstToken.GetString();
}

// JMR-MODIF - Le 27 mars 2006 - Ajout de la fonction pour le contrôle de la valeur de la liste des livrables.
CString ZBBPProcessSymbol::CheckDeliverables(int Index)
{
    CString m_DeliveryList = GetDeliveryDeliverables(Index);
    CString m_ChildPageList = _T("");

    GetDeliverablesInChildPages(m_ChildPageList);

    PSS_Tokenizer m_DeliverablesListFromDelivery(m_DeliveryList);
    PSS_Tokenizer m_DeliverablesListFromChildPages(m_ChildPageList);
    PSS_Tokenizer m_DeliverablesList(_T(""));

    for (size_t i = 0; i < m_DeliverablesListFromDelivery.GetTokenCount(); i++)
    {
        CString m_CurVal = _T("");

        m_DeliverablesListFromDelivery.GetTokenAt(i, m_CurVal);

        for (size_t j = 0; j < m_DeliverablesListFromChildPages.GetTokenCount(); j++)
        {
            CString m_TstVal = _T("");

            m_DeliverablesListFromChildPages.GetTokenAt(j, m_TstVal);

            if (m_CurVal == m_TstVal && !m_DeliverablesList.TokenExist(m_CurVal))
            {
                m_DeliverablesList.AddToken(m_CurVal);
            }
        }
    }

    return m_DeliverablesList.GetString();
}

// JMR-MODIF - Le 16 février 2006 - Ajout de la fonction pour le contrôle de la valeur du livrable principal.
CString ZBBPProcessSymbol::CheckMainDeliverable(int Index)
{
    CString m_Main = GetDeliveryDeliverables(Index);

    // Si la liste des livrables de la livraison est vide, on vide le champ du livrable principal.
    if (m_Main.IsEmpty())
    {
        return _T("");
    }

    CString Result = _T("");
    PSS_Tokenizer cmpToken(m_Main);

    // Compare si le livrable principal se trouve toujours dans la liste des livrables de la livraison.
    // Retourne une nouvelle valeur pour le champ "Principal" si le livrable principal précédemment sélectionné
    // ne se trouve plus dans la liste des livrables attribués à la livraison.
    for (size_t i = 0; i < cmpToken.GetTokenCount(); i++)
    {
        CString m_Cmp = _T("");
        cmpToken.GetTokenAt(i, m_Cmp);

        if (m_Cmp == GetDeliveryMain(Index))
        {
            return GetDeliveryMain(Index);
        }
    }

    /**************************************************************************************************************
    // JMR-MODIF - Le 20 mars 2006 - On n'attribue plus le premier livrable disponible dans la liste si le livrable
    // principal précédemment sélectionné ne s'y trouve plus. On vide seulement la valeur du champ "Principal.
    cmpToken.GetTokenAt( 0, Result );

    return Result;
    **************************************************************************************************************/

    // JMR-MODIF - Le 20 mars 2006 - Le livrable principal doit être effacé s'il ne se trouve plus dans la liste.
    return _T("");
}

// JMR-MODIF - Le 16 février 2006 - Ajout de la fonction pour la mise à jour des valeurs des livraisons.
void ZBBPProcessSymbol::UpdateValuesForThisDeliveryProperty(size_t Index)
{
    /****************************************************************************************************
    // JMR-MODIF - Le 8 mars 2006 - Suppression du code d'auto-remplissage des données. Dorénavant,
    // c'est l'utilisateur, et lui seul, qui remplira les données. La gestion automatique est désactivée.

    // Contrôle qu'une livraison ait bien été crée.
    if ( Index == 0 )
    {
        CString    DeliverablesList    = _T( "" );
        int        NbDeliverables        = 0;

        // Obtient tous les livrables disponibles dans les pages enfants, à partir de ce processus.
        GetDeliverablesInChildPages( DeliverablesList );

        // Tant que l'utilisateur n'a pas commencé à manipuler les valeurs des livraisons,
        // on laisse le programme attribuer et mettre à jour automatiquement ces valeurs.
        if ( m_IsUserModified == false )
        {
            SetDeliveryDeliverables( Index, DeliverablesList );

            if ( DeliverablesList.IsEmpty() )
            {
                SetDeliveryMain ( Index, DeliverablesList );
                SetDeliveryQuantity        ( Index, 0.0f );
                SetDeliveryPercentage    ( Index, 0.0f );
                return;
            }
            else
            {
                ZBTokenizer Token( DeliverablesList );

                if ( Token.GetTokenCount() > 0 && GetDeliveryMain( Index ).IsEmpty() == TRUE )
                {
                    CString Value;

                    // Retreive the specific indexed token
                    if ( Token.GetTokenAt( Index, Value ) )
                    {
                        SetDeliveryMain( Index, Value );
                    }
                }
            }
        }
    }
    ****************************************************************************************************/

    // Mets à jour les valeurs des champs pour chaque index de propriété des livraisons.
    SetDeliveryDeliverables(Index, CheckDeliverables(Index));
    SetDeliveryMain(Index, CheckMainDeliverable(Index));
    SetDeliveryQuantity(Index, FindQuantity(GetDeliveryMain(Index)));
    SetDeliveryPercentage(Index, CalculateDeliveryPercentage(GetDeliveryQuantity(Index)));
}

// JMR-MODIF - Le 25 décembre 2006 - Permet de rechercher le nom original d'une règle en fonction de son GUID.
CString ZBBPProcessSymbol::GetRuleNameByGUID(ZBLogicalRulesEntity* p_Rule, CString RuleGUID)
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

bool ZBBPProcessSymbol::CreateWorkflowActivity(bool DefaultProp /*= true*/)
{
    return true;
}

bool ZBBPProcessSymbol::SetDefaultPropertyToWorkflowActivity()
{
    return true;
}

// JMR-MODIF - Le 26 avril 2007 - Cette fonction permet de déterminer si une règle donnée a été attribuée à cet objet.
BOOL ZBBPProcessSymbol::ContainsRule(CString RuleName)
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
void ZBBPProcessSymbol::CheckRulesSync(CStringArray& RulesList)
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

bool ZBBPProcessSymbol::FillProperties(ZBPropertySet&    PropSet,
                                       bool            NumericValue    /*= false*/,
                                       bool            GroupValue        /*= false*/)
{
    // Les propriétés "Nom", "Description" et "Référence" du groupe "General" sont affichées par la classe de base.
    if (!ZBSymbol::FillProperties(PropSet, NumericValue, GroupValue))
    {
        return false;
    }

    // Only local symbol have access to properties
    if (!IsLocal())
    {
        return true;
    }

    int            i = 0;
    CODModel*    pModel = GetRootModel();

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

        for (i = 0; i < m_Rules.GetRulesCount(); i++)
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

    for (i = 0; i < GetRiskCount(); ++i)
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

    // JMR-MODIF - Le 17 février 2006 - Calcule la somme des livraisons.
    float m_SumOfDeliveries = CalculateSumOfDeliveries();

    int HourPerDay = -1;
    int DayPerWeek = -1;
    int DayPerMonth = -1;
    int DayPerYear = -1;

    if (pModel && ISA(pModel, ZDProcessGraphModelMdl))
    {
        CDocument* pDoc = dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetDocument();

        if (pDoc && ISA(pDoc, PSS_ProcessGraphModelDoc))
        {
            // JMR-MODIF - Le 30 juillet 2007 - Cette opération est effectuée une fois pour toutes au début de la fonction.
            // Retreive the model's currency symbol
            //CurrencySymbol = dynamic_cast<PSS_ProcessGraphModelDoc*>( pDoc )->GetCurrencySymbol();

            // Retreive the standard time definition
            HourPerDay = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetHourPerDay();
            DayPerWeek = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetDayPerWeek();
            DayPerMonth = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetDayPerMonth();
            DayPerYear = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDoc)->GetDayPerYear();
        }
    }

    ZBBPProcessProperties* pProcessProps = (ZBBPProcessProperties*)GetProperty(ZS_BP_PROP_PROCESS);

    if (!pProcessProps)
    {
        return false;
    }

    // Propriété "Cas de gestion" du groupe "Processus"
    ZBProperty* pMngCase = new ZBProperty(IDS_ZS_BP_PROP_PROCESS_TITLE,
                                          ZS_BP_PROP_PROCESS,
                                          IDS_Z_MANAGEMENT_CASE_NAME,
                                          Z_MANAGEMENT_CASE,
                                          IDS_Z_MANAGEMENT_CASE_DESC,
                                          pProcessProps->GetManagementCase());

    PropSet.Add(pMngCase);

    // ***********************************************************************************************************
    // JMR-MODIF - Le 27 janvier 2006 - Ajout des propriétés liées aux prestations.

    // JMR-MODIF - Le 20 mars 2006 - Obtient le menu des prestations si celui-ci n'est pas encore présent.
    if (gPrestationsMenu.GetSafeHmenu() == NULL)
    {
        gPrestationsMenu.LoadMenu(IDR_PRESTATIONS_MENU);
    }

    POSITION myPos = m_PrestProperties.GetHeadPosition();

    while (myPos != NULL)
    {
        ZBBPPrestationNode* myCurNode = m_PrestProperties.GetAt(myPos);

        CString myPropTitle;
        CString myPropSubTitle;
        CString myPropTitleNbr;
        CString myPropDesc;
        bool Error = false;

        myCurNode->SetPrestationName(RetreivePrestationName(myCurNode->GetPrestationGUID(), Error));

        myPropTitle.LoadString(IDS_Z_PRESTATIONS_TITLE);
        myPropTitleNbr.Format(_T(" %i"), ++i);
        myPropTitle += myPropTitleNbr;

        myPropSubTitle.LoadString(IDS_Z_PRESTATION_NAME_TITLE);
        myPropDesc.LoadString(IDS_Z_PRESTATION_NAME_DESC);

        // JMR-MODIF - Le 20 mars 2006 - Propriété "Nom" du groupe "Prestation x"
        ZBProperty* pPrestations = new ZBProperty(myPropTitle,
                                                  ZS_BP_PROP_PRESTATIONS,
                                                  myPropSubTitle,
                                                  Z_PRESTATION_NAME,
                                                  myPropDesc,
                                                  myCurNode->GetPrestationName(),
                                                  ZBProperty::PT_EDIT_MENU,
                                                  true,
                                                  PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                                  NULL,
                                                  &gPrestationsMenu);

        PropSet.Add(pPrestations);

        float PercentageActivity = 0.0f;
        myCurNode->GetValue(Z_PRESTATION_PERCENTAGE, PercentageActivity);

        myPropSubTitle.LoadString(IDS_Z_PRESTATION_PERCENTAGE_TITLE);
        myPropDesc.LoadString(IDS_Z_PRESTATION_PERCENTAGE_DESC);

        // JMR-MODIF - Le 20 mars 2006 - Propriété "Pourcentage" du groupe "Prestation x"
        pPrestations = new ZBProperty(myPropTitle,
                                      ZS_BP_PROP_PRESTATIONS,
                                      myPropSubTitle,
                                      Z_PRESTATION_PERCENTAGE,
                                      myPropDesc,
                                      PercentageActivity,
                                      ZBProperty::PT_EDIT_NUMBER,
                                      true,
                                      PSS_StringFormat(PSS_StringFormat::IE_FT_Percentage));

        PropSet.Add(pPrestations);

        // JMR-MODIF - Le 14 mars 2006 - La(les) prestation(s) suivante(s) est(sont) dépendante(s) de Sesterce.
        if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
            dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())
        {
            myPropSubTitle.LoadString(IDS_Z_PRESTPROCESS_TITLE);
            myPropDesc.LoadString(IDS_Z_PRESTPROCESS_DESC);

            float myPropPrestProcessValue = m_SumOfDeliveries * PercentageActivity;

            // Propriété "Prest. du proces." du groupe "Prestation x"
            pPrestations = new ZBProperty(myPropTitle,
                                          ZS_BP_PROP_PRESTATIONS,
                                          myPropSubTitle,
                                          Z_PRESTATION_PRESTPROCESS,
                                          myPropDesc,
                                          myPropPrestProcessValue,
                                          ZBProperty::PT_EDIT_NUMBER_READONLY,
                                          true,
                                          PSS_StringFormat(PSS_StringFormat::IE_FT_Accounting, false, 0));

            PropSet.Add(pPrestations);
        }

        //        myPropSubTitle.LoadString( IDS_Z_PRESTID_TITLE );
        //        myPropDesc.LoadString( IDS_Z_PRESTID_DESC );

                // JMR-MODIF - Le 19 juin 2006 - Propriété "Identifiant" du groupe "Prestation x"
        pPrestations = new ZBProperty(myPropTitle,
                                      ZS_BP_PROP_PRESTATIONS,
                                      "Identifiant",//myPropSubTitle,
                                      Z_PRESTATION_IDENTIFIER,
                                      "Identifiant de la prestation",//myPropDesc,
                                      myCurNode->GetPrestationGUID(),
                                      ZBProperty::PT_EDIT_STRING_READONLY,
                                      false);

        PropSet.Add(pPrestations);

        myPos = m_PrestProperties.GetNextPosition();
    }
    // ***********************************************************************************************************

    // JMR-MODIF - Le 14 mars 2006 - La(les) prestation(s) suivante(s) est(sont) dépendante(s) de Sesterce.
    if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
        dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())
    {
        ZBProperty* pSimProp;

        if (NumericValue)
        {
            // Propriété "Charge" du groupe "Calculs et prévisions"
            pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCESS,
                                      ZS_BP_PROP_SIM_PROCESS,
                                      IDS_Z_SIM_PROCESS_WORKLOAD_FORECAST_NAME,
                                      Z_SIM_PROCESS_WORKLOAD_FORECAST,
                                      IDS_Z_SIM_PROCESS_WORKLOAD_FORECAST_DESC,
                                      (double)GetProcessWorkloadForecast(),
                                      ZBProperty::PT_EDIT_NUMBER);
        }
        else
        {
            // Propriété "Charge" du groupe "Calculs et prévisions"
            pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCESS,
                                      ZS_BP_PROP_SIM_PROCESS,
                                      IDS_Z_SIM_PROCESS_WORKLOAD_FORECAST_NAME,
                                      Z_SIM_PROCESS_WORKLOAD_FORECAST,
                                      IDS_Z_SIM_PROCESS_WORKLOAD_FORECAST_DESC,
                                      PSS_Duration((double)GetProcessWorkloadForecast(),
                                                 HourPerDay, DayPerWeek, DayPerMonth, DayPerYear),
                                      ZBProperty::PT_EDIT_DURATION_READONLY,
                                      true,
                                      PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));
        }

        PropSet.Add(pSimProp);

        // Propriété "Coût" du groupe "Calculs et prévisions"
        pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCESS,
                                  ZS_BP_PROP_SIM_PROCESS,
                                  IDS_Z_SIM_PROCESS_COST_FORECAST_NAME,
                                  Z_SIM_PROCESS_COST_FORECAST,
                                  IDS_Z_SIM_PROCESS_COST_FORECAST_DESC,
                                  (double)GetProcessCostForecast(),
                                  ZBProperty::PT_EDIT_NUMBER_READONLY,
                                  true,
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, CurrencySymbol));

        PropSet.Add(pSimProp);

        // JMR-MODIF - Le 14 mars 2006 - Ajout propriété "Coût HMO" du groupe "Calculs et prévisions"
        pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCESS,
                                  ZS_BP_PROP_SIM_PROCESS,
                                  IDS_Z_SIM_PROCESS_COST_NAME,
                                  Z_SIM_PROCESS_COST_HMO,
                                  IDS_Z_SIM_PROCESS_COST_DESC,
                                  (double)GetProcessCost(),
                                  ZBProperty::PT_EDIT_NUMBER_READONLY,
                                  true,
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_Currency, true, 2, CurrencySymbol));

        PropSet.Add(pSimProp);

        // JMR-MODIF - Le 21 février 2006 - Ajout propriété "Somme livraisons" du groupe "Calculs et prévisions"
        pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCESS,
                                  ZS_BP_PROP_SIM_PROCESS,
                                  IDS_Z_SIM_PROCESS_SUM_DELIVERIES_NAME,
                                  Z_SIM_PROCESS_SUM_DELIVERIES,
                                  IDS_Z_SIM_PROCESS_SUM_DELIVERIES_DESC,
                                  m_SumOfDeliveries,
                                  ZBProperty::PT_EDIT_NUMBER_READONLY,
                                  true,
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_Accounting, false, 0));

        PropSet.Add(pSimProp);

        float m_WorkloadByDeliveries = 0.0f;
        float m_CostByDeliveries = 0.0f;

        if (m_SumOfDeliveries != 0.0f)
        {
            m_WorkloadByDeliveries = (float)GetProcessWorkloadForecast() / m_SumOfDeliveries;
            m_CostByDeliveries = (float)GetProcessCostForecast() / m_SumOfDeliveries;
        }

        // JMR-MODIF - Le 27 février 2006 - Ajout propriété "Charge / livraison" du groupe "Calculs et prévisions"
        pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCESS,
                                  ZS_BP_PROP_SIM_PROCESS,
                                  IDS_Z_SIM_PROCESS_WORKLOAD_BY_DELIVERIES,
                                  Z_SIM_PROCESS_WORKLOAD_BY_DELIVERIES,
                                  IDS_Z_SIM_PROCESS_WORKLOAD_BY_DELIVERIES_DESC,
                                  // JMR-MODIF - Le 19 juin 2006 - Changé affichage de la valeur numérique.
//                                   m_WorkloadByDeliveries,
//                                   ZBProperty::PT_EDIT_NUMBER_READONLY );
PSS_Duration((double)m_WorkloadByDeliveries,
           HourPerDay,
           DayPerWeek,
           DayPerMonth,
           DayPerYear),
                                  ZBProperty::PT_EDIT_DURATION_READONLY,
                                  true,
                                  PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7));

        PropSet.Add(pSimProp);

        // JMR-MODIF - Le 27 février 2006 - Ajout propriété "Coût / livraison" du groupe "Calculs et prévisions"
        pSimProp = new ZBProperty(IDS_ZS_BP_PROP_SIM_PROCESS,
                                  ZS_BP_PROP_SIM_PROCESS,
                                  IDS_Z_SIM_PROCESS_COST_BY_DELIVERIES,
                                  Z_SIM_PROCESS_COST_BY_DELIVERIES,
                                  IDS_Z_SIM_PROCESS_COST_BY_DELIVERIES_DESC,
                                  m_CostByDeliveries,
                                  ZBProperty::PT_EDIT_NUMBER_READONLY);

        PropSet.Add(pSimProp);
    }

    // ***********************************************************************************************************
    // JMR-MODIF - Le 6 février 2006 - Ajout des propriétés liées aux livraisons.

    // Obtient le menu des livraisons si celui-ci n'est pas encore présent.
    if (gDeliveriesMenu.GetSafeHmenu() == NULL)
    {
        gDeliveriesMenu.LoadMenu(IDR_DELIVERIES_MENU);
    }

    CString FinalPropName;
    CString FinalPropTitle;
    CString PropTitle;
    CString PropName;
    CString PropDesc;

    PropTitle.LoadString(IDS_ZS_BP_PROP_DELIVERY_TITLE);

    for (i = 0; i < GetDeliveriesCount(); ++i)
    {
        // Contrôle et mets à jour la livraison initiale.
        UpdateValuesForThisDeliveryProperty(i);

        FinalPropTitle.Format(_T("%s (%d)"), PropTitle, i + 1);

        PropName.LoadString(IDS_Z_DELIVERY_NAME_NAME);
        PropDesc.LoadString(IDS_Z_DELIVERY_NAME_DESC);

        // Propriété "Titre livraison" du groupe "Livraisons (x)"
        ZBProperty* pDelivery = new ZBProperty(FinalPropTitle,
            (GroupValue == true) ? ZS_BP_PROP_DELIVERIES : (ZS_BP_PROP_DELIVERIES + i),
                                               PropName,
                                               (GroupValue == true) ? Z_DELIVERY_NAME : (Z_DELIVERY_NAME + (i * _MaxDeliveryListSize)),
                                               PropDesc,
                                               GetDeliveryName(i),
                                               ZBProperty::PT_EDIT_MENU,
                                               true,
                                               PSS_StringFormat(PSS_StringFormat::IE_FT_General),
                                               NULL,
                                               &gDeliveriesMenu);

        PropSet.Add(pDelivery);

        PropName.LoadString(IDS_Z_DELIVERY_DELIVERABLES_NAME);
        PropDesc.LoadString(IDS_Z_DELIVERY_DELIVERABLES_DESC);

        // Propriété "Livrables" du groupe "Livraisons (x)"
        pDelivery = new ZBProperty(FinalPropTitle,
            (GroupValue == true) ? ZS_BP_PROP_DELIVERIES : (ZS_BP_PROP_DELIVERIES + i),
                                   PropName,
                                   (GroupValue == true) ? Z_DELIVERY_DELIVERABLES : (Z_DELIVERY_DELIVERABLES + (i * _MaxDeliveryListSize)),
                                   PropDesc,
                                   GetDeliveryDeliverables(i),
                                   ZBProperty::PT_EDIT_EXTENDED_READONLY);

        PropSet.Add(pDelivery);

        // JMR-MODIF - Le 14 mars 2006 - La(les) prestation(s) suivante(s) est(sont) dépendante(s) de Sesterce.
        if (pModel && ISA(pModel, ZDProcessGraphModelMdl) &&
            dynamic_cast<ZDProcessGraphModelMdl*>(pModel)->GetIntegrateCostSimulation())
        {
            PropName.LoadString(IDS_Z_DELIVERY_QUANTITY_NAME);
            PropDesc.LoadString(IDS_Z_DELIVERY_QUANTITY_DESC);
            float Quantity = FindQuantity(GetDeliveryMain(i));

            // Propriété "Quantité" du groupe "Livraisons (x)"
            pDelivery = new ZBProperty(FinalPropTitle,
                (GroupValue == true) ? ZS_BP_PROP_DELIVERIES : (ZS_BP_PROP_DELIVERIES + i),
                                       PropName,
                                       (GroupValue == true) ? Z_DELIVERY_QUANTITY : (Z_DELIVERY_QUANTITY + (i * _MaxDeliveryListSize)),
                                       PropDesc,
                                       Quantity,
                                       ZBProperty::PT_EDIT_NUMBER_READONLY,
                                       true,
                                       PSS_StringFormat(PSS_StringFormat::IE_FT_Accounting, false, 0));

            PropSet.Add(pDelivery);

            PropName.LoadString(IDS_Z_DELIVERY_PERCENTAGE_NAME);
            PropDesc.LoadString(IDS_Z_DELIVERY_PERCENTAGE_DESC);
            float Percentage = GetDeliveryPercentage(i);

            // Propriété "Pourcentage" du groupe "Livraisons (x)"
            pDelivery = new ZBProperty(FinalPropTitle,
                (GroupValue == true) ? ZS_BP_PROP_DELIVERIES : (ZS_BP_PROP_DELIVERIES + i),
                                       PropName,
                                       (GroupValue == true) ? Z_DELIVERY_PERCENTAGE : (Z_DELIVERY_PERCENTAGE + (i * _MaxDeliveryListSize)),
                                       PropDesc,
                                       Percentage,
                                       ZBProperty::PT_EDIT_NUMBER_READONLY,
                                       true,
                                       PSS_StringFormat(PSS_StringFormat::IE_FT_Percentage));

            PropSet.Add(pDelivery);
        }

        PropName.LoadString(IDS_Z_DELIVERY_MAIN_NAME);
        PropDesc.LoadString(IDS_Z_DELIVERY_MAIN_DESC);

        // Propriété "Principal" du groupe "Livraisons (x)"
        pDelivery = new ZBProperty(FinalPropTitle,
            (GroupValue == true) ? ZS_BP_PROP_DELIVERIES : (ZS_BP_PROP_DELIVERIES + i),
                                   PropName,
                                   (GroupValue == true) ? Z_DELIVERY_MAIN : (Z_DELIVERY_MAIN + (i * _MaxDeliveryListSize)),
                                   PropDesc,
                                   GetDeliveryMain(i),
                                   ZBProperty::PT_EDIT_EXTENDED_READONLY);

        PropSet.Add(pDelivery);
    }
    // ***********************************************************************************************************

    return true;
}

bool ZBBPProcessSymbol::SaveProperties(ZBPropertySet& PropSet)
{
    if (!ZBSymbol::SaveProperties(PropSet))
    {
        return false;
    }

    // Only local symbol have access to properties
    if (!IsLocal())
    {
        return true;
    }

    ZBBPProcessProperties* pProcessProps = (ZBBPProcessProperties*)GetProperty(ZS_BP_PROP_PROCESS);

    if (!pProcessProps)
    {
        return false;
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator i(&PropSet);
    ZBProperty* pProp;
    ZBBPProcessProperties ProcessProps(*pProcessProps);

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_PROCESS)
        {
            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    ProcessProps.SetValue(pProp->GetItemID(), pProp->GetValueString());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    ProcessProps.SetValue(pProp->GetItemID(), static_cast<float>(pProp->GetValueDouble()));
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    ProcessProps.SetValue(pProp->GetItemID(), pProp->GetValueFloat());
                    break;
                }

                case ZBProperty::PT_DATE:
                {
                    ProcessProps.SetValue(pProp->GetItemID(), static_cast<float>((DATE)pProp->GetValueDate()));
                    break;
                }
            }
        }
    }

    // Now sets the new property
    SetProperty(&ProcessProps);

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

    // *************************************************************************************************************
    // JMR-MODIF - Le 1er février 2006 - Ajout du code pour la mise à jour des valeurs des prestations.

    ZBPropertyIterator k(&PropSet);
    POSITION myPos = m_PrestProperties.GetHeadPosition();

    for (pProp = k.GetFirst(); pProp; pProp = k.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_PRESTATIONS)
        {
            if (pProp->GetItemID() == Z_PRESTATION_PERCENTAGE)
            {
                switch (pProp->GetPTValueType())
                {
                    case ZBProperty::PT_FLOAT:
                    {
                        if (myPos != NULL)
                        {
                            ZBBPPrestationNode* myCurNode = m_PrestProperties.GetAt(myPos);
                            myCurNode->SetValue(Z_PRESTATION_PERCENTAGE, pProp->GetValueFloat());
                            myPos = m_PrestProperties.GetNextPosition();
                        }

                        break;
                    }
                }
            }
        }
    }
    // *************************************************************************************************************

    // Now run through the list of data and fill the property set
    ZBPropertyIterator l(&PropSet);

    for (pProp = l.GetFirst(); pProp; pProp = l.GetNext())
    {
        if (pProp->GetCategoryID() == ZS_BP_PROP_SIM_PROCESS)
        {
            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    m_SimProperties.SetValue(pProp->GetItemID(), pProp->GetValueString());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    m_SimProperties.SetValue(pProp->GetItemID(), pProp->GetValueDouble());
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    m_SimProperties.SetValue(pProp->GetItemID(), pProp->GetValueFloat());
                    break;
                }

                case ZBProperty::PT_DATE:
                {
                    m_SimProperties.SetValue(pProp->GetItemID(), static_cast<float>((DATE)pProp->GetValueDate()));
                    break;
                }
            }
        }
    }

    // *************************************************************************************************************
    // JMR-MODIF - Le 15 février 2006 - Ajout du code pour la mise à jour des valeurs des livraisons.

    ZBPropertyIterator m(&PropSet);

    for (pProp = m.GetFirst(); pProp; pProp = m.GetNext())
    {
        if (pProp->GetCategoryID() >= ZS_BP_PROP_DELIVERIES &&
            pProp->GetCategoryID() <= ZS_BP_PROP_DELIVERIES + GetDeliveriesCount())
        {
            int i = pProp->GetCategoryID() - ZS_BP_PROP_DELIVERIES;
            ZBBPDeliveriesProperties* pDelyProp = GetDeliveryProperty(i);

            if (!pDelyProp)
            {
                return false;
            }

            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_STRING:
                {
                    pDelyProp->SetValue(pProp->GetItemID() - (i * _MaxDeliveryListSize),
                                        pProp->GetValueString());
                    break;
                }

                case ZBProperty::PT_DOUBLE:
                {
                    pDelyProp->SetValue(pProp->GetItemID() - (i * _MaxDeliveryListSize),
                                        static_cast<float>(pProp->GetValueDouble()));
                    break;
                }

                case ZBProperty::PT_FLOAT:
                {
                    pDelyProp->SetValue(pProp->GetItemID() - (i * _MaxDeliveryListSize),
                                        pProp->GetValueFloat());
                    break;
                }

                case ZBProperty::PT_DATE:
                {
                    pDelyProp->SetValue(pProp->GetItemID() - (i * _MaxDeliveryListSize),
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
    // *************************************************************************************************************

    RefreshAttributeTextArea(true);

    return true;
}

// JMR-MODIF - Le 15 février 2006 - Ajout de la fonction SaveProperty.
bool ZBBPProcessSymbol::SaveProperty(ZBProperty& Property)
{
    if (!ZBSymbol::SaveProperty(Property))
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

    if (Property.GetCategoryID() >= ZS_BP_PROP_DELIVERIES &&
        Property.GetCategoryID() <= ZS_BP_PROP_DELIVERIES + GetDeliveriesCount())
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_DELIVERIES;

        switch (Property.GetItemID() - (i * _MaxDeliveryListSize))
        {
            case Z_DELIVERY_NAME:
            {
                SetDeliveryName(Property.GetCategoryID() - ZS_BP_PROP_DELIVERIES,
                                Property.GetValueString());
                break;
            }

            case Z_DELIVERY_DELIVERABLES:
            {
                SetDeliveryDeliverables(Property.GetCategoryID() - ZS_BP_PROP_DELIVERIES,
                                        Property.GetValueString());
                break;
            }

            case Z_DELIVERY_QUANTITY:
            {
                SetDeliveryQuantity(Property.GetCategoryID() - ZS_BP_PROP_DELIVERIES,
                                    Property.GetValueFloat());
                break;
            }

            case Z_DELIVERY_MAIN:
            {
                SetDeliveryMain(Property.GetCategoryID() - ZS_BP_PROP_DELIVERIES,
                                Property.GetValueString());
                break;
            }
        }
    }

    // Set the modified flag to true,
    // Do nothing more, the values will be saved by the save properties method
    SetModifiedFlag();

    return true;
}

// JMR-MODIF - Le 15 février 2006 - Ajout de la fonction OnPostPropertyChanged.
bool ZBBPProcessSymbol::OnPostPropertyChanged(ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh)
{
    // Only local symbol have access to properties
    if (!IsLocal())
    {
        return false;
    }

    bool RetValue = false;

    if (Property.GetCategoryID() >= ZS_BP_PROP_DELIVERIES &&
        Property.GetCategoryID() <= ZS_BP_PROP_DELIVERIES + GetDeliveriesCount())
    {
        int i = Property.GetCategoryID() - ZS_BP_PROP_DELIVERIES;

        switch (Property.GetItemID() - (i * _MaxDeliveryListSize))
        {
            case Z_DELIVERY_DELIVERABLES:
            {
                float Quantity = FindQuantity(GetDeliveryMain(Property.GetCategoryID() - ZS_BP_PROP_DELIVERIES));

                // Attribue la bonne valeur à la bonne propriété.
                ZBPropertyIterator s(&Properties);
                ZBProperty* pProp;
                bool bFound = false;

                for (pProp = s.GetFirst(); pProp && bFound == false; pProp = s.GetNext())
                {
                    if (!pProp || ((pProp->GetCategoryID() - ZS_BP_PROP_DELIVERIES) != i))
                    {
                        continue;
                    }

                    if (pProp->GetItemID() - (i * _MaxDeliveryListSize) == Z_DELIVERY_QUANTITY)
                    {
                        pProp->SetValueFloat(Quantity);
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

    if (RetValue == false)
    {
        return ZBSymbol::OnPostPropertyChanged(Property, Properties, Refresh);
    }

    return RetValue;
}

void ZBBPProcessSymbol::OnDraw(CDC* pDC)
{
    ZBSymbol::OnDraw(pDC);
}

void ZBBPProcessSymbol::AdjustElementPosition()
{
    ZBSymbol::AdjustElementPosition();
}

BOOL ZBBPProcessSymbol::CreateEmptyChildModel(CODModel* pParent)
{
    if (!m_pModel)
    {
        m_pModel = new ZDProcessGraphModelMdlBP(GetSymbolName(),
                                                reinterpret_cast<ZDProcessGraphModelMdlBP*>(pParent));
    }
    else return FALSE;

    return m_pModel != NULL;
}

BOOL ZBBPProcessSymbol::OnDoubleClick()
{
    return TRUE;
}

bool ZBBPProcessSymbol::OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode)
{
    toolTipText.Format(IDS_FS_BPPROCESS_TOOLTIP,
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

void ZBBPProcessSymbol::Serialize(CArchive& ar)
{
    // Serialize the canvas model.
    ZBSymbol::Serialize(ar);

    // Only if the object is serialize from and to a document
    if (ar.m_pDocument)
    {
        // JMR-MODIF - Le 1er février 2006 - Ajout du code pour la sérialisation des prestations.
        if (dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 24)
        {
            m_PrestProperties.Serialize(ar);

            // JMR-MODIF - Le 16 février 2006 - Ajout du système de livraisons.
            m_Deliveries.Serialize(ar);
        }

        // JMR-MODIF - Le 18 décembre 2006 - Ajout du code pour la sérialisation des règles.
        if (dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 26)
        {
            m_Rules.Serialize(ar);
        }

        // JMR-MODIF - Le 10 juin 2007 - Ajout du code pour la sérialisation des risques.
        if (dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 27)
        {
            m_Risks.Serialize(ar);
        }

        m_SimProperties.Serialize(ar);

        if (ar.IsStoring())
        {
            TRACE(_T("ZBBPProcessSymbol::Serialize : Start Save\n"));

            ar << (WORD)m_DisplayPreview;

            // JMR-MODIF - Le 16 février 2006 - Ajout de la variable m_IsUserModified dans la sérialisation.
            ar << (WORD)m_IsUserModified;

            TRACE(_T("ZBBPProcessSymbol::Serialize : End Save\n"));
        }
        else
        {
            TRACE(_T("ZBBPProcessSymbol::Serialize : Start Read\n"));

            WORD wValue;
            ar >> wValue;
            m_DisplayPreview = (wValue == 0) ? false : true;

            // JMR-MODIF - Le 16 février 2006 - Ajout de la variable m_IsUserModified dans la sérialisation.
            if (dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 24)
            {
                ar >> wValue;
                m_IsUserModified = (wValue == 0) ? false : true;
            }

            TRACE(_T("ZBBPProcessSymbol::Serialize : End Read\n"));
        }

        if (m_pModel)
        {
            m_pModel->SetName(GetSymbolName());
        }
    }
}
