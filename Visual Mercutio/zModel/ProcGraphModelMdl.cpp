// ProcGraphModelMdl.cpp : implementation of the ZDProcessGraphModelMdl class

#include "stdafx.h"

#include "ProcGraphModelMdl.h"
#include "ProcGraphModelCtlr.h"
#include "ProcGraphModelDoc.h"
#include "ProcGraphModelVp.h"

#include "ZDProcessGraphPage.h"

#include "ZBSymbol.h"
#include "ZBLinkSymbol.h"

#include "ZBLanguageProp.h"
#include "ZBBasicModelProp.h"
#include "zModelRes.h"
#include "zBaseLib\ZBTokenizer.h"

#include "ZUODSymbolManipulator.h"

#include "ZBSymbolObserverMsg.h"
#include "ZBDocObserverMsg.h"

#include "zBaseLib\PSS_MsgBox.h"

// Include files for log
#include "zBaseLib\ZILog.h"
#include "zModel\ZBGenericSymbolErrorLine.h"
#include "zModel\ZBSearchSymbolLogLine.h"

#include "zRBProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 26 septembre 2005 - Ajout de la décoration unicode _T( ), nettoyage du code non utilisé.

/////////////////////////////////////////////////////////////////////////////
// constant definition
const size_t                RecursionMaxLoop = 5000;

/////////////////////////////////////////////////////////////////////////////
// static variables
bool                        ZDProcessGraphModelMdl::m_IsInRecursion = false;
int                            ZDProcessGraphModelMdl::m_RecursionCounter = 0;
size_t                        ZDProcessGraphModelMdl::m_FindCounter = 0;
CODComponentSet                ZDProcessGraphModelMdl::m_FindSet;

CArray<ZDProcessGraphModelMdl::ZBComponentRef*, ZDProcessGraphModelMdl::ZBComponentRef*> ZDProcessGraphModelMdl::m_SymbolParsed;

// Main user group variable
ZBUserGroupEntity*            ZDProcessGraphModelMdl::m_pMainUserGroup = NULL;

// Main logical system
ZBLogicalSystemEntity*        ZDProcessGraphModelMdl::m_pMainLogicalSystem = NULL;

// JMR-MODIF - Le 26 janvier 2006 - Ajout de la déclaration externe de la variables statique des prestations.
ZBLogicalPrestationsEntity*    ZDProcessGraphModelMdl::m_pMainLogicalPrestations = NULL;

// JMR-MODIF - Le 19 novembre 2006 - Ajout de la déclaration externe de la variables statique des règles.
ZBLogicalRulesEntity*        ZDProcessGraphModelMdl::m_pMainLogicalRules = NULL;

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphModelMdl

IMPLEMENT_SERIAL(ZDProcessGraphModelMdl, CODModel, g_DefVersion)

ZDProcessGraphModelMdl::ZDProcessGraphModelMdl(const CString            Name    /*= ""*/,
                                               ZDProcessGraphModelMdl*    pParent    /*= NULL*/)
    : m_hMetaFile(NULL),
    m_pParent(pParent),
    m_Notation(E_MN_Unknown),
    m_pPageSet(NULL),
    m_pCtlr(NULL),
    m_MainUserGroupIsValid(false),
    m_MainLogicalSystemIsValid(false),
    // JMR-MODIF - Le 26 janvier 2006 - Ajout de l'initialisation de la variable m_MainLogicalPrestationsIsValid.
    m_MainLogicalPrestationsIsValid(false),
    // JMR-MODIF - Le 19 novembre 2006 - Ajout de l'initialisation de la variable m_MainLogicalRulesIsValid.
    m_MainLogicalRulesIsValid(false),
    m_IsInCutOperation(false),
    bIsLogo(FALSE),
    // JMR-MODIF - Le 2 juillet 2006 - Aojut de l'initialisation de la variable m_NextAvailableRefNbr.
    m_NextAvailableRefNbr(1)
{
    CreateSymbolProperties();

    // Sets the model name
    SetModelName(Name);

    // Sets the can select flag to true
    SetCanSelect(TRUE);

    // Set the parent name
    if (m_pParent)
    {
        m_ParentName = m_pParent->GetModelName();
    }

    CalculateAbsolutePath();

    // JMR-MODIF - Le 5 août 2005 - Ajout du code d'initialisation des variables m_BkGndFilename et bBkGndFlag.
    m_BkGndFilename = _T("");
    bBkGndFlag = FALSE;
}

ZDProcessGraphModelMdl::~ZDProcessGraphModelMdl()
{
    DeleteAllPages();

    if (m_hMetaFile)
    {
        ::DeleteEnhMetaFile(m_hMetaFile);
        m_hMetaFile = NULL;
    }

    if (m_pPageSet)
    {
        delete m_pPageSet;
        m_pPageSet = NULL;
    }

    // JMR-MODIF - Le 3 octobre 2005 - Supprime les liens sur les observers. Ceux-ci sont déjà détruits ailleurs.
    m_observers.resize(0);
}

/////////////////////////////////////////////////////////////////////////
// Fonctions de nettoyage

// JMR-MODIF - Le 3 octobre 2005 - Cette fonction permet de supprimer les observers de la hiérarchie de modèles.
void ZDProcessGraphModelMdl::DetachAllObserversInHierarchy(ZIProcessGraphModelViewport*    m_pViewport,
                                                           ZDProcessGraphModelDoc*            m_pDocument)
{
    // Recherche tous les composants du modèle.
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // Si un sous-modèle est défini, pas un modèle référencé, et qui a une page définie, déplace le pointeur
        // sur le sous-modèle de façon récursive.
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef() &&
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->HasPageSet())
        {
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->
                                                      GetChildModel())->DetachAllObserversInHierarchy(m_pViewport, m_pDocument);
        }
    }

    // Passe à travers toutes les pages existantes.
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Ne pas effectuer de modifications sur le même modèle.
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->DetachAllObserversInHierarchy(m_pViewport, m_pDocument);
            }
        }
    }

    // Nettoie les liens sur les observeurs du modèle.
    RemoveObserver(m_pViewport);
    DetachObserver(m_pDocument);

    // Réinitialise le drapeau de modification.
    SetModifiedFlag(FALSE);
}

// JMR-MODIF - Le 26 septembre 2005 - Cette fonction permet le nettoyage du système de modèles.
void ZDProcessGraphModelMdl::DeleteModelSet()
{
    // Recherche tous les composants du modèle.
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // Si un sous-modèle est défini, pas un modèle référencé, et qui a une page définie, déplace le pointeur
        // sur le sous-modèle de façon récursive.
        if (pComp                                        &&
            ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef() &&
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->HasPageSet())
        {
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->DeleteModelSet();
        }
    }

    // Passe à travers toutes les pages existantes.
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Ne pas effectuer de modifications sur le même modèle.
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->DeleteModelSet();
            }
        }
    }

    // Détruit les objets enfants du modèle.
    RemoveAllChildren();

    // Nettoie les commandes dans le modèle de transaction.
    MvcTransactionModel *transactionModel = GetTransactionModel();

    if (transactionModel != NULL)
    {
        transactionModel->Reset();
        transactionModel = NULL;
    }

    // Nettoie l'image de fond du modèle.
    if (m_pBkgndComponent != NULL)
    {
        delete m_pBkgndComponent;
        m_pBkgndComponent = NULL;
    }

    // Détruit toutes les pages ouvertes dans le modèle.
    if (m_pPageSet)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            if (pPage->GetpModel() != this)
            {
                delete pPage->GetpModel();
                pPage->SetpModel(NULL);
            }

            delete pPage;
        }

        // Then, remove all elements
        m_pPageSet->RemoveAll();

        delete m_pPageSet;
        m_pPageSet = NULL;
    }

    // Réinitialise le drapeau de modification.
    SetModifiedFlag(FALSE);
}

/////////////////////////////////////////////////////////////////////////
// Fonctions d'implémentation.

CDocument* ZDProcessGraphModelMdl::GetDocument() const
{
    if (m_pCtlr)
    {
        return dynamic_cast<ZDProcessGraphModelController*>(m_pCtlr)->GetDocument();
    }

    return NULL;
}

const CDocument* ZDProcessGraphModelMdl::GetDocumentConst() const
{
    if (m_pCtlr)
    {
        return dynamic_cast<ZDProcessGraphModelController*>(m_pCtlr)->GetDocumentConstPtr();
    }

    return NULL;
}

bool ZDProcessGraphModelMdl::GetCheckConsistency() const
{
    ASSERT(const_cast<ZDProcessGraphModelMdl*>(this)->GetRoot());

    const CDocument* pDoc = const_cast<ZDProcessGraphModelMdl*>(this)->GetRoot()->GetDocumentConst();

    if (pDoc && ISA(pDoc, ZDProcessGraphModelDoc))
    {
        return dynamic_cast<const ZDProcessGraphModelDoc*>(pDoc)->GetCheckConsistency();
    }

    return false;
}

void ZDProcessGraphModelMdl::SetCheckConsistency(bool value)
{
    ASSERT(GetRoot());

    CDocument* pDoc = GetRoot()->GetDocument();

    if (pDoc && ISA(pDoc, ZDProcessGraphModelDoc))
    {
        dynamic_cast<ZDProcessGraphModelDoc*>(pDoc)->SetCheckConsistency(value);
    }
}

bool ZDProcessGraphModelMdl::GetIntegrateCostSimulation() const
{
    ASSERT(const_cast<ZDProcessGraphModelMdl*>(this)->GetRoot());

    const CDocument* pDoc = const_cast<ZDProcessGraphModelMdl*>(this)->GetRoot()->GetDocumentConst();

    if (pDoc && ISA(pDoc, ZDProcessGraphModelDoc))
    {
        return dynamic_cast<const ZDProcessGraphModelDoc*>(pDoc)->GetIntegrateCostSimulation();
    }

    return false;
}

void ZDProcessGraphModelMdl::SetIntegrateCostSimulation(bool value)
{
    ASSERT(GetRoot());

    CDocument* pDoc = GetRoot()->GetDocument();

    if (pDoc && ISA(pDoc, ZDProcessGraphModelDoc))
    {
        dynamic_cast<ZDProcessGraphModelDoc*>(pDoc)->SetIntegrateCostSimulation(value);
    }
}

bool ZDProcessGraphModelMdl::GetUseWorkflow() const
{
    ASSERT(const_cast<ZDProcessGraphModelMdl*>(this)->GetRoot());

    const CDocument* pDoc = const_cast<ZDProcessGraphModelMdl*>(this)->GetRoot()->GetDocumentConst();

    if (pDoc && ISA(pDoc, ZDProcessGraphModelDoc))
    {
        return dynamic_cast<const ZDProcessGraphModelDoc*>(pDoc)->GetUseWorkflow();
    }

    return false;
}

void ZDProcessGraphModelMdl::SetUseWorkflow(bool value)
{
    ASSERT(GetRoot());

    CDocument* pDoc = GetRoot()->GetDocument();

    if (pDoc && ISA(pDoc, ZDProcessGraphModelDoc))
    {
        dynamic_cast<ZDProcessGraphModelDoc*>(pDoc)->SetUseWorkflow(value);
    }
}

bool ZDProcessGraphModelMdl::GetShowPageBorder() const
{
    ASSERT(const_cast<ZDProcessGraphModelMdl*>(this)->GetRoot());

    const CDocument* pDoc = const_cast<ZDProcessGraphModelMdl*>(this)->GetRoot()->GetDocumentConst();

    if (pDoc && ISA(pDoc, ZDProcessGraphModelDoc))
    {
        return dynamic_cast<const ZDProcessGraphModelDoc*>(pDoc)->GetShowPageBorder();
    }

    return false;
}

void ZDProcessGraphModelMdl::SetShowPageBorder(bool value)
{
    ASSERT(GetRoot());

    CDocument* pDoc = GetRoot()->GetDocument();

    if (pDoc && ISA(pDoc, ZDProcessGraphModelDoc))
    {
        dynamic_cast<ZDProcessGraphModelDoc*>(pDoc)->SetShowPageBorder(value);
    }
}

ZDProcessGraphModelController* ZDProcessGraphModelMdl::CreateController(ZIProcessGraphModelViewport* pVp)
{
    return new ZDProcessGraphModelController(pVp);
}

ZDProcessGraphModelMdl* ZDProcessGraphModelMdl::GetRoot()
{
    if (m_pParent)
    {
        return m_pParent->GetRoot();
    }

    return this;
}

const CString ZDProcessGraphModelMdl::GetModelName()
{
    ZBBasicModelProperties* pBasicProps = (ZBBasicModelProperties*)GetProperty(ZS_BP_PROP_MODEL_BASIC);

    if (!pBasicProps)
    {
        return _T("");
    }

    return pBasicProps->GetModelName();
}

void ZDProcessGraphModelMdl::SetModelName(const CString value)
{
    ZBBasicModelProperties BasicProps;
    ZBBasicModelProperties* pCurBasicProps = (ZBBasicModelProperties*)GetProperty(ZS_BP_PROP_MODEL_BASIC);

    if (pCurBasicProps != NULL)
    {
        BasicProps = *pCurBasicProps;
        BasicProps.SetModelName(value);
        SetProperty(&BasicProps);

        // Build the message
        ZBDocObserverMsg DocMsg(ZBDocObserverMsg::ChangedElement, NULL, this);
        AfxGetMainWnd()->SendMessageToDescendants(UM_ELEMENTMODIFIEDDOCUMENTMODEL, 0, (LPARAM)&DocMsg);
    }

    // Recalculate all references
    RecalculateParentPtr();
    ReCalculateAbsolutePath();
}

const CString ZDProcessGraphModelMdl::GetDescription()
{
    ZBBasicModelProperties* pBasicProps = (ZBBasicModelProperties*)GetProperty(ZS_BP_PROP_MODEL_BASIC);

    if (!pBasicProps)
    {
        return _T("");
    }

    return pBasicProps->GetModelDescription();
}

void ZDProcessGraphModelMdl::SetDescription(const CString& value)
{
    ZBBasicModelProperties BasicProps;
    ZBBasicModelProperties* pCurBasicProps = (ZBBasicModelProperties*)GetProperty(ZS_BP_PROP_MODEL_BASIC);

    if (pCurBasicProps != NULL)
    {
        BasicProps = *pCurBasicProps;
        BasicProps.SetModelDescription(value);
        SetProperty(&BasicProps);
    }
}

const ELanguage ZDProcessGraphModelMdl::GetLanguage()
{
    ZBLanguageProp* pProps = (ZBLanguageProp*)GetProperty(ZS_BP_PROP_LANGUAGE);

    // not exists? Create it
    if (!pProps)
    {
        CreateSymbolProperties();
        pProps = (ZBLanguageProp*)GetProperty(ZS_BP_PROP_LANGUAGE);
    }

    // still not exists? Return unknown as error
    if (!pProps)
        return E_LN_Unknown;

    return pProps->GetLanguage();
}

void ZDProcessGraphModelMdl::SetLanguage(ELanguage value)
{
    ZBLanguageProp Props;
    ZBLanguageProp* pProps = (ZBLanguageProp*)GetProperty(ZS_BP_PROP_LANGUAGE);

    if (!pProps)
    {
        CreateSymbolProperties();
        pProps = (ZBLanguageProp*)GetProperty(ZS_BP_PROP_LANGUAGE);
    }
    else
    {
        Props = *pProps;
        Props.SetLanguage(value);
        SetProperty(&Props);
    }
}

CString ZDProcessGraphModelMdl::RetreiveUnitGUID(const CString Name, bool& Error) const
{
    if (m_pMainUserGroup)
    {
        ZBUserEntitySet* pSet = m_pMainUserGroup->FindGroup(Name, true);

        if (pSet && pSet->GetSize() > 0)
        {
            Error = false;
            return pSet->GetAt(0)->GetGUID();
        }
    }

    Error = true;
    return _T("");
}

CString ZDProcessGraphModelMdl::RetreiveUnitName(const CString GUID, bool& Error) const
{
    if (m_pMainUserGroup)
    {
        ZBUserEntity* pEntity = m_pMainUserGroup->FindGroupByGUID(GUID, true);

        if (pEntity)
        {
            Error = false;
            return pEntity->GetEntityName();
        }
    }

    Error = true;
    return _T("");
}

CString ZDProcessGraphModelMdl::RetreiveUnitDescription(const CString GUID, bool& Error) const
{
    if (m_pMainUserGroup)
    {
        ZBUserEntity* pEntity = m_pMainUserGroup->FindGroupByGUID(GUID, true);

        if (pEntity)
        {
            Error = false;
            return pEntity->GetEntityDescription();
        }
    }

    Error = true;
    return _T("");
}

float ZDProcessGraphModelMdl::RetreiveUnitCost(const CString GUID, bool& Error) const
{
    if (m_pMainUserGroup)
    {
        ZBUserEntity* pEntity = m_pMainUserGroup->FindGroupByGUID(GUID, true);

        if (pEntity)
        {
            Error = false;
            return pEntity->GetEntityCost();
        }
    }

    Error = true;
    return 0;
}

CString ZDProcessGraphModelMdl::RetreiveLogicalSystemGUID(const CString Name, bool& Error) const
{
    if (m_pMainLogicalSystem)
    {
        ZBSystemEntitySet* pSet = m_pMainLogicalSystem->FindSystem(Name, true);

        if (pSet && pSet->GetSize() > 0)
        {
            Error = false;
            return pSet->GetAt(0)->GetGUID();
        }
    }

    Error = true;
    return _T("");
}

CString ZDProcessGraphModelMdl::RetreiveLogicalSystemName(const CString GUID, bool& Error) const
{
    if (m_pMainLogicalSystem)
    {
        ZBSystemEntity* pEntity = m_pMainLogicalSystem->FindSystemByGUID(GUID, true);

        if (pEntity)
        {
            Error = false;
            return pEntity->GetEntityName();
        }
    }

    Error = true;
    return _T("");
}

CString ZDProcessGraphModelMdl::RetreiveLogicalSystemDescription(const CString GUID, bool& Error) const
{
    if (m_pMainLogicalSystem)
    {
        ZBSystemEntity* pEntity = m_pMainLogicalSystem->FindSystemByGUID(GUID, true);

        if (pEntity)
        {
            Error = false;
            return pEntity->GetEntityDescription();
        }
    }

    Error = true;
    return _T("");
}

// JMR-MODIF - Le 27 février 2006 - Ajout de la méthode pour la mise à jour du nom des prestations.
CString ZDProcessGraphModelMdl::RetreivePrestationName(const CString GUID, bool& Error) const
{
    if (m_pMainLogicalPrestations)
    {
        ZBLogicalPrestationsEntity* pPrestation =
            dynamic_cast<ZBLogicalPrestationsEntity*>(m_pMainLogicalPrestations->FindPrestationByGUID(GUID, true));

        if (pPrestation)
        {
            Error = false;
            return pPrestation->GetEntityName();
        }
    }

    Error = true;
    return _T("");
}

// JMR-MODIF - Le 19 novembre 2006 - Ajout de la méthode pour la mise à jour du nom des règles.
CString ZDProcessGraphModelMdl::RetreiveRuleName(const CString GUID, bool& Error) const
{
    if (m_pMainLogicalRules)
    {
        ZBLogicalRulesEntity* pRule =
            dynamic_cast<ZBLogicalRulesEntity*>(m_pMainLogicalRules->FindRuleByGUID(GUID, true));

        if (pRule)
        {
            Error = false;
            return pRule->GetEntityName();
        }
    }

    Error = true;
    return _T("");
}

bool ZDProcessGraphModelMdl::CreateSymbolProperties()
{
    ZBBasicModelProperties propBasic;
    AddProperty(propBasic);

    ZBLanguageProp propLanguage;
    AddProperty(propLanguage);

    return true;
}

bool ZDProcessGraphModelMdl::FillProperties(ZBPropertySet&    PropSet,
                                            bool            NumericValue    /*= false*/,
                                            bool            GroupValue        /*= false*/)
{
    // Just retreive the language
    ZBLanguageProp* pProps = (ZBLanguageProp*)GetProperty(ZS_BP_PROP_LANGUAGE);

    // If doesn't exist, create the property
    if (!pProps)
    {
        CreateSymbolProperties();

        // Retreive it again
        pProps = (ZBLanguageProp*)GetProperty(ZS_BP_PROP_LANGUAGE);

        // if problem, return error
        if (!pProps)
        {
            return false;
        }
    }

    ZBBasicModelProperties* pBasicProps = (ZBBasicModelProperties*)GetProperty(ZS_BP_PROP_MODEL_BASIC);

    if (!pBasicProps)
    {
        return false;
    }

    ZBProperty* pNameProp = new ZBProperty(IDS_ZS_BP_PROP_MODEL_BASIC_TITLE,
                                           ZS_BP_PROP_MODEL_BASIC,
                                           IDS_Z_MODEL_NAME_NAME,
                                           Z_MODEL_NAME,
                                           IDS_Z_MODEL_NAME_DESC,
                                           pBasicProps->GetModelName(),
                                           ZBProperty::PT_EDIT_STRING_READONLY);
    PropSet.Add(pNameProp);

    ZBProperty* pDescProp = new ZBProperty(IDS_ZS_BP_PROP_MODEL_BASIC_TITLE,
                                           ZS_BP_PROP_MODEL_BASIC,
                                           IDS_Z_MODEL_DESCRIPTION_NAME,
                                           Z_MODEL_DESCRIPTION,
                                           IDS_Z_MODEL_DESCRIPTION_DESC,
                                           pBasicProps->GetModelDescription());
    PropSet.Add(pDescProp);

    return true;
}

bool ZDProcessGraphModelMdl::SaveProperties(ZBPropertySet& PropSet)
{
    ZBBasicModelProperties* pBasicProps = (ZBBasicModelProperties*)GetProperty(ZS_BP_PROP_MODEL_BASIC);

    if (!pBasicProps)
    {
        return false;
    }

    // Now run through the list of data and fill the property set
    ZBPropertyIterator i(&PropSet);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        // If has not changed, continue
        if (pProp->GetHasChanged() == false)
        {
            continue;
        }

        if (pProp->GetCategoryID() == ZS_BP_PROP_MODEL_BASIC)
        {
            switch (pProp->GetItemID())
            {
                case Z_MODEL_NAME:
                {
                    SetModelName(pProp->GetValueString());
                    break;
                }

                case Z_MODEL_DESCRIPTION:
                {
                    SetDescription(pProp->GetValueString());
                    break;
                }
            }
        }
    }

    return true;
}

bool ZDProcessGraphModelMdl::FillProperty(ZBProperty& Property)
{
    ZBBasicModelProperties* pBasicProps = (ZBBasicModelProperties*)GetProperty(ZS_BP_PROP_MODEL_BASIC);

    if (!pBasicProps)
    {
        return false;
    }

    if (Property.GetCategoryID() == ZS_BP_PROP_MODEL_BASIC)
    {
        switch (Property.GetItemID())
        {
            case Z_MODEL_NAME:
            {
                Property.SetValueString(pBasicProps->GetModelName());
                break;
            }

            case Z_MODEL_DESCRIPTION:
            {
                Property.SetValueString(pBasicProps->GetModelDescription());
                break;
            }
        }
    }

    return true;
}

bool ZDProcessGraphModelMdl::SaveProperty(ZBProperty& Property)
{
    ZBBasicModelProperties* pBasicProps = (ZBBasicModelProperties*)GetProperty(ZS_BP_PROP_MODEL_BASIC);

    if (!pBasicProps)
    {
        return false;
    }

    if (Property.GetCategoryID() == ZS_BP_PROP_MODEL_BASIC)
    {
        switch (Property.GetItemID())
        {
            case Z_MODEL_NAME:
            {
                SetModelName(Property.GetValueString());
                break;
            }

            case Z_MODEL_DESCRIPTION:
            {
                SetDescription(Property.GetValueString());
                break;
            }
        }
    }

    return true;
}

bool ZDProcessGraphModelMdl::CheckPropertyValue(ZBProperty& Property, CString& value, ZBPropertySet& Properties)
{
    if (Property.GetCategoryID() == ZS_BP_PROP_MODEL_BASIC &&
        Property.GetItemID() == Z_MODEL_NAME)
    {
        ZDProcessGraphModelMdl* pRoot = GetRoot();

        // If this is the root model,
        // notify the user that to rename the root model
        // it must save the model under another name
        if (value != GetModelName())
        {
            if (pRoot == this)
            {
                PSS_MsgBox mBox;
                mBox.Show(IDS_CANNOTRENAME_ROOTMODEL_USE_SA, MB_OK);
                value = GetModelName();

                return false;
            }

            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTRENAME_MODEL_REN_DS, MB_OK);
            value = GetModelName();
        }
    }

    return true;
}

bool ZDProcessGraphModelMdl::ProcessExtendedInput(ZBProperty&        Property,
                                                  CString&            value,
                                                  ZBPropertySet&    Properties,
                                                  bool&            Refresh)
{
    return true;
}

ZIProcessGraphModelViewport* ZDProcessGraphModelMdl::CreateViewport(ZIProcessGraphModelView* pView)
{
    // Create the basic viewport
    // Return the new created instance of basic Viewport
    return new MvcScrollWrapper_T<ZIProcessGraphModelViewport>;
}

/////////////////////////////////////////////////////////////////////////
// Page management functions

ZDProcessGraphPage* ZDProcessGraphModelMdl::GetRootMainModelPage()
{
    return (GetMainPageSet() != NULL && GetMainPageSet()->GetSize() > 0) ? GetMainPageSet()->GetAt(0) : NULL;
}

void ZDProcessGraphModelMdl::SetRootMainModelPage(ZDProcessGraphPage* pPage)
{
    ZBProcessGraphPageSet* pSet = GetMainPageSet();

    if (pSet)
    {
        if (pSet->GetSize() > 0)
        {
            pSet->SetAt(0, pPage);
        }
        else
        {
            pSet->Add(pPage);
        }
    }
}

ZDProcessGraphPage* ZDProcessGraphModelMdl::GetMainModelPage()
{
    return (GetPageSet() != NULL && GetPageSet()->GetSize() > 0) ? GetPageSet()->GetAt(0) : NULL;
}

void ZDProcessGraphModelMdl::SetMainModelPage(ZDProcessGraphPage* pPage)
{
    ZBProcessGraphPageSet* pSet = GetPageSet();

    if (pSet)
    {
        if (pSet->GetSize() > 0)
        {
            pSet->SetAt(0, pPage);
        }
        else
        {
            pSet->Add(pPage);
        }
    }
}

ZBProcessGraphPageSet* ZDProcessGraphModelMdl::GetMainPageSet()
{
    ZDProcessGraphModelMdl* pRootModel = GetRoot();
    return (pRootModel != NULL) ? pRootModel->GetPageSet() : NULL;
}

ZBProcessGraphPageSet* ZDProcessGraphModelMdl::AllocateMainPageSet()
{
    ZDProcessGraphModelMdl* pRootModel = GetRoot();
    return (pRootModel != NULL) ? pRootModel->AllocatePageSet() : NULL;
}

ZBProcessGraphPageSet* ZDProcessGraphModelMdl::AllocatePageSet()
{
    m_pPageSet = new ZBProcessGraphPageSet;
    return m_pPageSet;
}

ZDProcessGraphPage* ZDProcessGraphModelMdl::CreateNewPage(ZDProcessGraphModelMdl*    pModel,
                                                          CString                    PageName    /*= ""*/,
                                                          ZDProcessGraphModelMdl*    pInModel    /*= NULL*/)
{
    // JMR-MODIF - Le 5 août 2005 - Mise à jour du flag pour les nouvelles pages.
    bBkGndFlag = TRUE;

    ZBProcessGraphPageSet* pSet = NULL;

    // If a target model is specified
    if (pInModel)
    {
        // If no page set already allocated
        if (!(pSet = pInModel->GetPageSet()))
        {
            if (!(pSet = pInModel->AllocatePageSet()))
            {
                return NULL;
            }
        }
    }
    else
    {
        if (!(pSet = GetMainPageSet()))
        {
            if (!(pSet = AllocateMainPageSet()))
            {
                return NULL;
            }
        }
    }

    if (PageName.IsEmpty())
    {
        PageName = GetRoot()->GetValidNextPageName();
    }

    ZDProcessGraphPage* pNewPage = new ZDProcessGraphPage(PageName, pModel);
    pSet->Add(pNewPage);

    return pNewPage;
}

bool ZDProcessGraphModelMdl::DeletePage(const CString PageName, bool DeleteModel /*= false*/)
{
    // Process the model components
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If sub model defined,
        // not a model referenced,
        // and has a page set defined
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef() &&
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->HasPageSet())
        {
            // Recursively, call the same method
            if (reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->DeletePage(PageName, DeleteModel))
            {
                return true;
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            TRACE(_T("Page checked for delete : "));
            TRACE(pPage->GetPageName());
            TRACE(_T("\n"));

            // If we found the right page
            if (pPage->GetPageName() == PageName)
            {
                // Remove the current element
                if (DeleteModel && pPage->GetpModel())
                {
                    delete pPage->GetpModel();
                    pPage->SetpModel(NULL);
                }

                delete pPage;

                // Remove it from the table
                i.Remove();

                return true;
            }

            if (pPage->GetpModel() != this)
            {
                if (pPage->GetpModel()->DeletePage(PageName, DeleteModel))
                {
                    return true;
                }
            }
        }
    }

    // Not found
    return false;
}

bool ZDProcessGraphModelMdl::DeleteAllPages()
{
    // Process the model components
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent*    pComp = pSet->GetAt(i);

        // If sub model defined,
        // not a model referenced,
        // and has a page set defined
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef() &&
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->HasPageSet())
        {
            // recursively, call the same method
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->DeleteAllPages();
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the same model
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->DeleteAllPages();
            }
        }
    }

    // Once all elements from the model have been processed,
    // Delete the model page set
    DeleteAllPageInSet();

    return true;
}

bool ZDProcessGraphModelMdl::DeleteAllPageInSet()
{
    if (!m_pPageSet)
    {
        return true;
    }

    ZBProcessGraphPageIterator i(m_pPageSet);

    for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
    {
        delete pPage;
    }

    // Then, remove all elements
    m_pPageSet->RemoveAll();
    return true;
}

ZDProcessGraphPage* ZDProcessGraphModelMdl::FindPage(const CString PageName)
{
    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // If we found the right page
            if (pPage->GetPageName() == PageName)
            {
                return pPage;
            }

            // Do not process the same model
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                ZDProcessGraphPage* pPage2 = pPage->GetpModel()->FindPage(PageName);

                if (pPage2)
                {
                    return pPage2;
                }
            }
        }
    }

    // Process the model components
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If sub model defined,
        // not a model referenced,
        // and has a page set defined
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef() &&
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->HasPageSet())
        {
            // recursively, call the same method
            ZDProcessGraphPage* pPage = reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->FindPage(PageName);

            if (pPage)
            {
                return pPage;
            }
        }
    }

    // Not found
    return NULL;
}

ZDProcessGraphPage* ZDProcessGraphModelMdl::FindModelPage(const CString ModelName, bool InSubModel /*= false*/)
{
    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            if (pPage->GetpModel() && pPage->GetpModel()->GetModelName() == ModelName)
            {
                return pPage;
            }
            else
            {
                // If required to search in submodel,
                // try to locate the model
                if (InSubModel && SubModelExist(ModelName, true))
                {
                    return pPage;
                }
            }
        }
    }

    // Process the model components
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If sub model defined,
        // not a model referenced,
        // and has a page set defined
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef() &&
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->HasPageSet())
        {
            // Recursively, call the same method
            ZDProcessGraphPage* pPage =
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->FindModelPage(ModelName, InSubModel);

            if (pPage)
            {
                return pPage;
            }
        }
    }

    // Not found
    return NULL;
}

ZDProcessGraphPage* ZDProcessGraphModelMdl::FindModelPage(ZDProcessGraphModelMdl*    pModel,
                                                          bool                        InSubModel /*= false*/)
{
    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            if (pPage->GetpModel() == pModel)
            {
                return pPage;
            }

            // Do not check for itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                ZDProcessGraphPage* pSubPage = pPage->GetpModel()->FindModelPage(pModel, InSubModel);

                if (pSubPage)
                {
                    return pSubPage;
                }
            }
        }
    }

    // Process the model components
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If sub model defined,
        // not a model referenced,
        // and has a page set defined
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef() &&
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->HasPageSet())
        {
            // Recursively, call the same method
            ZDProcessGraphPage* pPage =
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->FindModelPage(pModel, InSubModel);

            if (pPage)
            {
                return pPage;
            }
        }
    }

    // Not found
    return NULL;
}

ZDProcessGraphModelMdl* ZDProcessGraphModelMdl::GetOwnerPageModel(ZDProcessGraphPage* pLookForPage)
{
    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            if (pPage && pPage == pLookForPage)
            {
                return this;
            }
        }
    }

    // Process the model components
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);
        // If sub model defined,
        // not a model referenced,
        // and has a page set defined
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef() &&
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->HasPageSet())
        {
            // recursively, call the same method
            ZDProcessGraphModelMdl* pModel =
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->GetOwnerPageModel(pLookForPage);

            if (pModel)
            {
                return pModel;
            }
        }
    }

    // not found
    return NULL;
}

bool ZDProcessGraphModelMdl::PageExist(const CString PageName)
{
    return (FindPage(PageName) != NULL) ? true : false;
}

CString ZDProcessGraphModelMdl::GetValidNextPageName()
{
    CStringArray* pArray = GetExistingPageNameArray();

    if (pArray && pArray->GetSize() > 0)
    {
    #ifdef _DEBUG
        for (int j = 0; j < pArray->GetSize(); ++j)
        {
            TRACE(_T("Existing page:\n"));
            TRACE1(_T("%s\n"), (const char*)pArray->GetAt(j));
        }
    #endif

        CString PageStr;

        for (int p = 1; p < 10000000; ++p)
        {
            PageStr.Format(_T("Page %d"), p);

            bool Found = false;

            for (int i = 0; i < pArray->GetSize(); ++i)
            {
                if (pArray->GetAt(i) == PageStr)
                {
                    Found = true;
                    break;
                }
            }

            // If not found, ok
            if (!Found)
            {
                return PageStr;
            }
        }
    }
    else
    {
        // Returns the first page number
        return _T("Page 1");
    }

    // If no page available, return empty string
    return _T("");
}

CStringArray* ZDProcessGraphModelMdl::GetExistingPageNameArray()
{
    static CStringArray InternalArrayOfPages;

    InternalArrayOfPages.RemoveAll();

    _GetExistingPageNameArray(InternalArrayOfPages);

    return &InternalArrayOfPages;
}

void ZDProcessGraphModelMdl::_GetExistingPageNameArray(CStringArray& PageArray)
{
    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // If a page exists
            if (pPage)
            {
                PageArray.Add(pPage->GetPageName());
            }

            // Do not check for itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->_GetExistingPageNameArray(PageArray);
            }
        }
    }

    // Process the model components
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If sub model defined,
        // not a model referenced,
        // and has a page set defined
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef() &&
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->HasPageSet())
        {
            // recursively, call the same method
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->_GetExistingPageNameArray(PageArray);
        }
    }
}

/////////////////////////////////////////////////////////////////////////
// Unique Symbol Name methods

bool ZDProcessGraphModelMdl::SymbolNameAlreadyAllocated(const CString SymbolName)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
        {
            continue;
        }

        // If we found the same reference number, return true
        if (ISA(pComp, ZBSymbol) && reinterpret_cast<ZBSymbol*>(pComp)->GetSymbolName() == SymbolName)
        {
            return true;
        }
        // If we found the same reference number, return true
        else if (ISA(pComp, ZBLinkSymbol) &&
                 reinterpret_cast<ZBLinkSymbol*>(pComp)->GetSymbolName() == SymbolName)
        {
            return true;
        }

        if (ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() && !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // If the process has a child model,
            // process the child model
            if (reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->SymbolNameAlreadyAllocated(SymbolName))
            {
                return true;
            }

            // Otherwise, continue to check
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not check if allocated for itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                if (pPage->GetpModel()->SymbolNameAlreadyAllocated(SymbolName))
                {
                    return true;
                }

                // Otherwise, continue to check
            }
        }
    }

    // No reference number found
    return false;
}

/////////////////////////////////////////////////////////////////////////
// Unique Reference number methods

bool ZDProcessGraphModelMdl::ReferenceNumberAlreadyAllocated(const CString ReferenceNumberStr)
{
    return ReferenceNumberAlreadyAllocated(atoi(ReferenceNumberStr));
}

bool ZDProcessGraphModelMdl::ReferenceNumberAlreadyAllocated(int ReferenceNumber)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
        {
            continue;
        }

        // If we found the same reference number, return true
        if (ISA(pComp, ZBSymbol) &&
            reinterpret_cast<ZBSymbol*>(pComp)->GetSymbolReferenceNumber() == ReferenceNumber)
        {
            return true;
        }
        // If we found the same reference number, return true
        else if (ISA(pComp, ZBLinkSymbol) &&
                 reinterpret_cast<ZBLinkSymbol*>(pComp)->GetSymbolReferenceNumber() == ReferenceNumber)
        {
            return true;
        }

        if (ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // If the process has a child model,
            // process the child model
            if (reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->ReferenceNumberAlreadyAllocated(ReferenceNumber))
            {
                return true;
            }

            // Otherwise, continue to check
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not check if allocated for itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                if (pPage->GetpModel()->ReferenceNumberAlreadyAllocated(ReferenceNumber))
                {
                    return true;
                }
            }
        }
    }

    // No reference number found
    return false;
}

CString ZDProcessGraphModelMdl::GetNextAvailableReferenceNumberStr()
{
    CString Str;

    Str.Format(_T("%d"), GetNextAvailableReferenceNumber());

    return Str;
}

// JMR-MODIF - Le 22 mai 2006 - Ajout du paramètre m_RootModel.
int ZDProcessGraphModelMdl::GetNextAvailableReferenceNumber(ZDProcessGraphModelMdl* m_RootModel)
{
    // JMR-MODIF - Le 22 mai 2006 - Suppression de l'ancien code de la fonction GetNextAvailableReferenceNumber.
    // Ancien code conservé ci-dessous.
/*
    for ( int RefNumber = 1; RefNumber < 100000; ++RefNumber )
    {
        // If we found the ref number, try next number
        if ( !_GetNextAvailableReferenceNumber( RefNumber ) )
        {
            return RefNumber;
        }
    }

    // If no reference number, return -1
    return -1;
*/

// **********************************************************************************************************
// JMR-MODIF - Le 2 juillet 2006 - Nouveau code pour la fonction GetNextAvailableReferenceNumber.

    int CurrentRefMax = _GetNextAvailableReferenceNumber(m_RootModel);

    if (CurrentRefMax > m_NextAvailableRefNbr)
    {
        m_NextAvailableRefNbr = CurrentRefMax;
    }

    return m_NextAvailableRefNbr++;
    // **********************************************************************************************************
}

// JMR-MODIF - Le 2 juillet 2006 - Ajout de la nouvelle fonction _GetNextAvailableReferenceNumber.
int ZDProcessGraphModelMdl::_GetNextAvailableReferenceNumber(ZDProcessGraphModelMdl* m_RootModel)
{
    int Result = 1;

    // Si le modèle d'entrée est vide, cela veut dire que l'on veut une recherche sur tout le document.
    if (m_RootModel == NULL)
    {
        // Obtient le contrôleur de modèles du document.
        m_RootModel = dynamic_cast<ZDProcessGraphModelMdl*>(GetRoot());
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
                ZDProcessGraphModelMdl* m_CurModel = dynamic_cast<ZDProcessGraphModelMdl*>(pPage->GetpModel());

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

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'un symbole.
                            if (pComponent && ISA(pComponent, ZBSymbol))
                            {
                                // Si le symbole possède des enfants, effectue la recherche sur les modèles enfants.
                                if (((ZBSymbol*)pComponent)->GetChildModel() &&
                                    !((ZBSymbol*)pComponent)->IsChildModelRef())
                                {
                                    CODModel* pChildMdl =
                                        dynamic_cast<ZBSymbol*>(pComponent)->GetChildModel();

                                    int ChildResult =
                                        _GetNextAvailableReferenceNumber(dynamic_cast<ZDProcessGraphModelMdl*>(pChildMdl));

                                    if (ChildResult > Result)
                                    {
                                        Result = ChildResult;
                                    }
                                }

                                // Contrôle et mets à jour le résultat.
                                if (dynamic_cast<ZBSymbol*>(pComponent)->GetSymbolReferenceNumber() >= Result)
                                {
                                    Result = dynamic_cast<ZBSymbol*>(pComponent)->GetSymbolReferenceNumber();
                                    Result++;
                                }
                            }

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'un symbole de lien.
                            if (pComponent && ISA(pComponent, ZBLinkSymbol))
                            {
                                // Contrôle et mets à jour le résultat.
                                if (dynamic_cast<ZBLinkSymbol*>(pComponent)->GetSymbolReferenceNumber() >= Result)
                                {
                                    Result = dynamic_cast<ZBLinkSymbol*>(pComponent)->GetSymbolReferenceNumber();
                                    Result++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return Result;
}

/*
// JMR-MODIF - Le 22 mai 2006 - Nouvelle fonction GetNextAvailableReferenceNumber rend cette fonction obsolète.
bool ZDProcessGraphModelMdl::_GetNextAvailableReferenceNumber( int& ReferenceNumber )
{
    CODComponentSet* pSet = GetComponents();

    for ( int i = 0; i < pSet->GetSize(); ++i )
    {
        CODComponent* pComp = pSet->GetAt( i );

        if ( !pComp )
        {
            continue;
        }

        // If we found the same reference number, return true
        if ( ISA( pComp, ZBSymbol ) &&
             reinterpret_cast<ZBSymbol*>( pComp )->GetSymbolReferenceNumber() == ReferenceNumber )
        {
            return true;
        }
        // If we found the same reference number, return true
        else if ( ISA( pComp, ZBLinkSymbol ) &&
                  reinterpret_cast<ZBLinkSymbol*>( pComp )->GetSymbolReferenceNumber() == ReferenceNumber )
        {
            return true;
        }

        if ( ISA( pComp, ZBSymbol )                    &&
             ( (ZBSymbol*)pComp )->GetChildModel()    &&
             !( (ZBSymbol*)pComp )->IsChildModelRef() )
        {
            // If the process has a child model,
            // process the child model
            if ( reinterpret_cast<ZDProcessGraphModelMdl*>( ( (ZBSymbol*)pComp )->GetChildModel() )->_GetNextAvailableReferenceNumber( ReferenceNumber ) )
            {
                return true;
            }
        }
    }

    // Run through all pages if there are
    if ( m_pPageSet != NULL )
    {
        ZBProcessGraphPageIterator i( m_pPageSet );

        for ( ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext() )
        {
            // Do not clear the path of itself
            if ( pPage->GetpModel() && pPage->GetpModel() != this )
            {
                if ( pPage->GetpModel()->_GetNextAvailableReferenceNumber( ReferenceNumber ) )
                {
                    return true;
                }
            }
        }
    }

    // No reference number found
    return false;
}
*/

CStringArray* ZDProcessGraphModelMdl::GetExistingReferenceNumberArray()
{
    static CStringArray InternalArrayOfReferenceNumbers;
    InternalArrayOfReferenceNumbers.RemoveAll();

    _GetExistingReferenceNumberArray(InternalArrayOfReferenceNumbers);

    return &InternalArrayOfReferenceNumbers;
}

void ZDProcessGraphModelMdl::_GetExistingReferenceNumberArray(CStringArray& ReferenceNumberArray)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
        {
            continue;
        }

        // Add the reference number to the array
        if (ISA(pComp, ZBSymbol))
        {
            ReferenceNumberArray.Add(reinterpret_cast<ZBSymbol*>(pComp)->GetSymbolReferenceNumberStr());
        }
        // Add the reference number to the array
        else if (ISA(pComp, ZBLinkSymbol))
        {
            ReferenceNumberArray.Add(reinterpret_cast<ZBLinkSymbol*>(pComp)->GetSymbolReferenceNumberStr());
        }

        if (ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // If the process has a child model,
            // process the child model
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->_GetExistingReferenceNumberArray(ReferenceNumberArray);
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not clear the path of itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->_GetExistingReferenceNumberArray(ReferenceNumberArray);
            }
        }
    }
}

bool ZDProcessGraphModelMdl::AcceptVisitor(ZIBasicSymbolVisitor& Visitor)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp)
        {
            if (ISA(pComp, ZBSymbol))
            {
                reinterpret_cast<ZBSymbol*>(pComp)->AcceptVisitor(Visitor);
            }
            else if (ISA(pComp, ZBLinkSymbol))
            {
                reinterpret_cast<ZBLinkSymbol*>(pComp)->AcceptVisitor(Visitor);
            }

            // If sub model defined
            if (ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
                !((ZBSymbol*)pComp)->IsChildModelRef())
            {
                // and recalculate its model also
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->AcceptVisitor(Visitor);
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do process itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->AcceptVisitor(Visitor);
            }
        }
    }

    return true;
}

BOOL ZDProcessGraphModelMdl::RecalculateAllLinks()
{
    return FALSE;
}

ZDProcessGraphModelMdl* ZDProcessGraphModelMdl::GetSymbolModel(ZBSymbol* pSymbolToFind)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp && ISA(pComp, ZBSymbol) && pComp == pSymbolToFind)
        {
            // If the symbol has been identified,
            // return the model
            return this;
        }

        // Find in sub-model if there is
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            ZDProcessGraphModelMdl* pMdl =
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->GetSymbolModel(pSymbolToFind);

            if (pMdl)
            {
                return pMdl;
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the same model
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                ZDProcessGraphModelMdl* pMdl = pPage->GetpModel()->GetSymbolModel(pSymbolToFind);

                if (pMdl)
                {
                    return pMdl;
                }
            }
        }
    }

    return NULL;
}

ZDProcessGraphModelMdl* ZDProcessGraphModelMdl::GetLinkSymbolModel(ZBLinkSymbol* pSymbolToFind)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp && ISA(pComp, ZBLinkSymbol) && pComp == pSymbolToFind)
        {
            // If the symbol has been identified,
            // return the model
            return this;
        }

        // Find in sub-model if there is
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            ZDProcessGraphModelMdl* pMdl =
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->GetLinkSymbolModel(pSymbolToFind);

            if (pMdl)
            {
                return pMdl;
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the same model
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                ZDProcessGraphModelMdl* pMdl = pPage->GetpModel()->GetLinkSymbolModel(pSymbolToFind);

                if (pMdl)
                {
                    return pMdl;
                }
            }
        }
    }

    return NULL;
}

// JMR-MODIF - Le 5 août 2005 - Ajout de la fonction SetBkGndFilename.
void ZDProcessGraphModelMdl::SetBkGndFilename(CString Filename)
{
    m_BkGndFilename = Filename;
}

// JMR-MODIF - Le 5 août 2005 - Ajout de la fonction GetBkGndFilename.
CString ZDProcessGraphModelMdl::GetBkGndFilename()
{
    return m_BkGndFilename;
}

void ZDProcessGraphModelMdl::SetBackgroundComponent(CODComponent&    BkgndComponent,
                                                    bool            ToAll            /*= true*/,
                                                    bool            StretchToModel    /*= false*/)
{
    if (!ToAll)
    {
        SetBackgroundComponentToModel(BkgndComponent, StretchToModel);
    }
    else
    {
        // To all is required, if we are not at the root, call the function from the root
        if (this != GetRoot())
        {
            GetRoot()->_SetBackgroundComponentToAll(BkgndComponent, StretchToModel);
        }
        else
        {
            _SetBackgroundComponentToAll(BkgndComponent, StretchToModel);
        }
    }
}

void ZDProcessGraphModelMdl::_SetBackgroundComponentToAll(CODComponent&    BkgndComponent,
                                                          bool                StretchToModel    /*= false*/)
{
    // Sets the background to this model
    SetBackgroundComponentToModel(BkgndComponent, StretchToModel);

    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // call the model recursively
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->_SetBackgroundComponentToAll(BkgndComponent, StretchToModel);
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the page pointing on itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                // The parent of all pages is itself
                pPage->GetpModel()->_SetBackgroundComponentToAll(BkgndComponent, StretchToModel);
            }
        }
    }
}

void ZDProcessGraphModelMdl::SetBackgroundComponentToModel(CODComponent&    BkgndComponent,
                                                           bool            StretchToModel    /*= false*/)
{
    CODComponent* pBkgndComponent = BkgndComponent.Dup();

    if (StretchToModel && pBkgndComponent)
    {
        // Determine the diagram's bounding CRect
        CRect rect = GetBounds();

        // This will stretch the image   
        pBkgndComponent->MoveTo(rect);
    }

    if (pBkgndComponent)
    {
        SetBkgndComponent(pBkgndComponent);
        SetModifiedFlag(FALSE);
    }
}

void ZDProcessGraphModelMdl::ClearBackgroundComponent(bool ToAll /*= true*/)
{
    if (!ToAll)
    {
        ClearBackgroundComponentToModel();
    }
    else
    {
        // To all is required, if we are not at the root, call the function from the root
        if (this != GetRoot())
        {
            GetRoot()->_ClearBackgroundComponentToAll();
        }
        else
        {
            _ClearBackgroundComponentToAll();
        }
    }
}

void ZDProcessGraphModelMdl::_ClearBackgroundComponentToAll()
{
    // Sets the background to this model
    ClearBackgroundComponentToModel();

    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // call the model recursively
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->_ClearBackgroundComponentToAll();
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the page pointing on itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                // The parent of all pages is itself
                pPage->GetpModel()->_ClearBackgroundComponentToAll();
            }
        }
    }
}

void ZDProcessGraphModelMdl::ClearBackgroundComponentToModel()
{
    CODComponent* pBkgndComponent = GetBkgndComponent();

    if (pBkgndComponent)
    {
        SetBkgndComponent(NULL);
    }

    SetModifiedFlag(FALSE);
}

void ZDProcessGraphModelMdl::PropagateNewSymbolAttributes(ZBPropertyAttributes* pAttributes, int ObjectID)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp)
        {
            // Notify the change to elements
            if (ISA(pComp, ZBSymbol) && dynamic_cast<ZBSymbol*>(pComp)->GetObjectTypeID() == ObjectID)
            {
                dynamic_cast<ZBSymbol*>(pComp)->OnChangeAttributes(pAttributes);
            }
            else if (ISA(pComp, ZBLinkSymbol) &&
                     dynamic_cast<ZBLinkSymbol*>(pComp)->GetObjectTypeID() == ObjectID)
            {
                reinterpret_cast<ZBLinkSymbol*>(pComp)->OnChangeAttributes(pAttributes);
            }

            // Check if has sub-model
            if (ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
                !((ZBSymbol*)pComp)->IsChildModelRef())
            {
                // call the model recursively
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->PropagateNewSymbolAttributes(pAttributes, ObjectID);
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the page pointing on itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                // The parent of all pages is itself
                pPage->GetpModel()->PropagateNewSymbolAttributes(pAttributes, ObjectID);
            }
        }
    }
}

void ZDProcessGraphModelMdl::RefreshSymbolAttributes(bool Redraw /*= false*/)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp)
        {
            // Notify the change to elements
            if (ISA(pComp, ZBSymbol))
            {
                reinterpret_cast<ZBSymbol*>(pComp)->RefreshAttributeAreaText(Redraw);
            }
            else if (ISA(pComp, ZBLinkSymbol))
            {
                reinterpret_cast<ZBLinkSymbol*>(pComp)->RefreshAttributeAreaText(Redraw);
            }

            // Check if has sub-model
            if (ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
                !((ZBSymbol*)pComp)->IsChildModelRef())
            {
                // call the model recursively
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->RefreshSymbolAttributes(Redraw);
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the page pointing on itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                // The parent of all pages is itself
                pPage->GetpModel()->RefreshSymbolAttributes(Redraw);
            }
        }
    }
}

void ZDProcessGraphModelMdl::ReDrawComponent(CODComponent& Comp)
{
    UpdateComponent(&Comp, OD_UPDATE_ALL);
}

void ZDProcessGraphModelMdl::ReDrawComponentSet(CODComponentSet& Set)
{
    UpdateComponents(&Set, OD_UPDATE_ALL);
}

void ZDProcessGraphModelMdl::SelectAllComponents()
{
    if (GetController())
    {
        dynamic_cast<ZDProcessGraphModelController*>(GetController())->SelectAllComponents();
    }
}

void ZDProcessGraphModelMdl::UnselectAllComponents()
{
    if (GetController())
    {
        dynamic_cast<ZDProcessGraphModelController*>(GetController())->UnselectAllComponents();
    }
}

void ZDProcessGraphModelMdl::SelectComponent(CODComponent& Comp)
{
    if (GetController())
    {
        dynamic_cast<ZDProcessGraphModelController*>(GetController())->SelectComponent(Comp);
    }
}

void ZDProcessGraphModelMdl::SelectComponentSet(CODComponentSet& Set)
{
    if (GetController())
    {
        dynamic_cast<ZDProcessGraphModelController*>(GetController())->SelectComponentSet(Set);
    }
}

void ZDProcessGraphModelMdl::UnselectComponent(CODComponent& Comp)
{
    if (GetController())
    {
        dynamic_cast<ZDProcessGraphModelController*>(GetController())->UnselectComponent(Comp);
    }
}

void ZDProcessGraphModelMdl::UnselectComponentSet(CODComponentSet& Set)
{
    if (GetController())
    {
        dynamic_cast<ZDProcessGraphModelController*>(GetController())->UnselectComponentSet(Set);
    }
}

bool ZDProcessGraphModelMdl::IsComponentSelected(CODComponent& Comp)
{
    return (GetController()) ? dynamic_cast<ZDProcessGraphModelController*>(GetController())->IsComponentSelected(Comp) :
        false;
}

void ZDProcessGraphModelMdl::DeleteComponents(CODComponentSet* pCompSet)
{
    if (GetController())
    {
        dynamic_cast<ZDProcessGraphModelController*>(GetController())->DeleteComponents(pCompSet);
    }
}

void ZDProcessGraphModelMdl::DeleteComponent(CODComponent* pComp)
{
    if (GetController())
    {
        dynamic_cast<ZDProcessGraphModelController*>(GetController())->DeleteComponent(pComp);
    }
}

bool ZDProcessGraphModelMdl::SymbolExistInModel(CODComponent* pCompToFind, bool InSubModel /*= true*/)
{
    CODComponentSet* pSet = FindSymbol(pCompToFind, InSubModel);
    return (pSet && pSet->GetSize() > 0) ? true : false;
}

CODComponentSet* ZDProcessGraphModelMdl::FindSymbol(CODComponent* pCompToFind, bool InSubModel /*= true*/)
{
    m_FindSet.RemoveAll();
    _FindSymbol(pCompToFind, InSubModel);

    return &m_FindSet;
}

CODComponentSet* ZDProcessGraphModelMdl::FindSymbol(const CString    Name,
                                                    const CString    Path            /*= ""*/,
                                                    bool            InSubModel        /*= true*/,
                                                    bool            CaseSensitive    /*= false*/,
                                                    bool            OnlyLocal        /*= false*/)
{
    m_FindSet.RemoveAll();
    _FindSymbol(Name, Path, InSubModel, CaseSensitive, OnlyLocal);

    return &m_FindSet;
}

CODComponentSet* ZDProcessGraphModelMdl::FindSymbol(CODModel*    pModel,
                                                    bool        InSubModel    /*= true*/,
                                                    bool        OnlyLocal    /*= false*/)
{
    m_FindSet.RemoveAll();
    _FindSymbol(pModel, InSubModel, OnlyLocal);

    return &m_FindSet;
}

CODComponentSet* ZDProcessGraphModelMdl::FindSymbolFromPath(const CString    Path,
                                                            bool            InSubModel        /*= true*/,
                                                            bool            CaseSensitive    /*=false*/,
                                                            bool            OnlyLocal        /*= false*/)
{
    m_FindSet.RemoveAll();
    _FindSymbolFromPath(Path, InSubModel, CaseSensitive, OnlyLocal);

    return &m_FindSet;
}

CODComponentSet* ZDProcessGraphModelMdl::FindSymbolByRefNumber(int RefNumber, bool InSubModel /*= true*/)
{
    m_FindSet.RemoveAll();
    _FindSymbolByRefNumber(RefNumber, InSubModel);

    return &m_FindSet;
}

ZDProcessGraphModelMdl* ZDProcessGraphModelMdl::FindModelFromPath(const CString Path, bool CaseSensitive /*= false*/)
{
    return _FindModelFromPath(Path, CaseSensitive);
}

// JMR-MODIF - Le 28 mars 2006 - Ajouté paramètre m_RootModel dans la fonction.
ZDProcessGraphModelMdl* ZDProcessGraphModelMdl::FindModel(const CString            Name,
                                                          bool                        CaseSensitive    /*= false*/,
                                                          ZDProcessGraphModelMdl*    m_RootModel        /*= NULL*/)
{
    // Si le nom est vide, retourne NULL.
    if (Name.IsEmpty())
    {
        return NULL;
    }

    // Si le modèle d'entrée est vide, cela veut dire que l'on veut une recherche sur tout le document.
    if (m_RootModel == NULL)
    {
        // Obtient le contrôleur de modèles du document.
        m_RootModel = dynamic_cast<ZDProcessGraphModelMdl*>(this->GetRoot());
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
                ZDProcessGraphModelMdl* m_CurModel = dynamic_cast<ZDProcessGraphModelMdl*>(pPage->GetpModel());

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

                            // Contrôle que le composant soit valide, et identifie s'il s'agit d'un symbole.
                            if (pComponent && ISA(pComponent, ZBSymbol))
                            {
                                // Convertit le symbole.
                                ZBSymbol* m_Symbol = dynamic_cast<ZBSymbol*>(pComponent);

                                // Contrôle que le symbole contienne un contrôleur de modèles.
                                if (m_Symbol                    &&
                                    m_Symbol->GetChildModel() &&
                                    !m_Symbol->IsChildModelRef())
                                {
                                    // Obtient le contrôleur de modèle du symbole.
                                    ZDProcessGraphModelMdl* m_ChildModel =
                                        dynamic_cast<ZDProcessGraphModelMdl*>(m_Symbol->GetChildModel());

                                    // Teste s'il s'agit du symbole recherché.
                                    if ((CaseSensitive && m_Symbol->GetSymbolName() == Name) ||
                                        (!CaseSensitive && Name.CompareNoCase(m_Symbol->GetSymbolName()) == 0))
                                    {
                                        return m_ChildModel;
                                    }
                                    else
                                    {
                                        // Appel récursif à FindModel, jusqu'à ce que toutes les pages des modèles
                                        // enfants aient été visitées, ou que le modèle désiré ait été trouvé.
                                        ZDProcessGraphModelMdl* Result = FindModel(Name,
                                                                                   CaseSensitive,
                                                                                   m_ChildModel);

                                        // Le modèle n'est peut-être pas dans cet ensemble de pages si le résultat
                                        // vaut NULL. Alors, il faut continuer à chercher.
                                        if (Result != NULL)
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
        }
    }

    return NULL;

    // JMR-MODIF - Le 28 mars 2006 - Réecritue de la fonction. Ancienne implémentation conservée ci-dessous.
//    return _FindModel( Name, CaseSensitive );
}

CODComponentSet* ZDProcessGraphModelMdl::FindSymbolPartialName(const CString    Name,
                                                               bool            InSubModel        /*= true*/,
                                                               bool            CaseSensitive    /*=false*/,
                                                               bool            OnlyLocal        /*= false*/)
{
    m_FindSet.RemoveAll();
    _FindSymbolPartialName(Name, InSubModel, CaseSensitive, OnlyLocal);

    return &m_FindSet;
}

size_t ZDProcessGraphModelMdl::Find(const CString            What,
                                    ZILog*                    pLog,
                                    ZBPropertyAttributes*    pPropAttributes    /*= NULL*/,
                                    bool                    InSubModel        /*= true*/,
                                    bool                    CaseSensitive    /*=false*/,
                                    bool                    PartialSearch    /*= false*/)
{
    m_FindCounter = 0;

    // If log
    if (pLog)
    {
        pLog->ClearLog();
        CString message;
        message.Format(IDS_AL_START_FINDMATCH, What, GetModelName());
        ZBGenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    _Find(What, pLog, pPropAttributes, InSubModel, CaseSensitive, PartialSearch);

    // If log
    if (pLog)
    {
        CString message;
        message.Format(IDS_AL_STOP_FINDMATCH, m_FindCounter);
        ZBGenericSymbolErrorLine e(message);
        pLog->AddLine(e);
    }

    return m_FindCounter;
}

bool ZDProcessGraphModelMdl::SubModelExist(CODModel* pModel)
{
    if (this == pModel)
    {
        return true;
    }

    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // Find in sub-model if there is
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            return reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->SubModelExist(pModel);
        }
    }

    return false;
}

bool ZDProcessGraphModelMdl::SubModelExist(const CString ModelName, bool CaseSensitive /*= false*/)
{
    // If a symbol and the same name
    if ((CaseSensitive && GetModelName() == ModelName) ||
        (!CaseSensitive && ModelName.CompareNoCase(GetModelName()) == 0))
    {
        return true;
    }

    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // Find in sub-model if there is
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            return reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->SubModelExist(ModelName, CaseSensitive);
        }
    }

    return false;
}

void ZDProcessGraphModelMdl::_Find(const CString            What,
                                   ZILog*                    pLog,
                                   ZBPropertyAttributes*    pPropAttributes    /*= NULL*/,
                                   bool                    InSubModel        /*= true*/,
                                   bool                    CaseSensitive    /*=false*/,
                                   bool                    PartialSearch    /*= false*/)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If a symbol and the same name
        if (pComp && ISA(pComp, ZBSymbol))
        {
            if (((ZBSymbol*)pComp)->Match(What, pPropAttributes, CaseSensitive, PartialSearch))
            {
                // Add to the log
                if (pLog)
                {
                    ZBSearchSymbolLogLine e(((ZBSymbol*)pComp)->GetSymbolName(), ((ZBSymbol*)pComp)->GetAbsolutePath());
                    pLog->AddLine(e);
                }

                ++m_FindCounter;
            }
        }
        // If a link symbol and the same name
        else if (pComp && ISA(pComp, ZBLinkSymbol))
        {
            if (((ZBLinkSymbol*)pComp)->Match(What, pPropAttributes, CaseSensitive, PartialSearch))
            {
                // Add to the log
                if (pLog)
                {
                    ZBSearchSymbolLogLine e(((ZBLinkSymbol*)pComp)->GetSymbolName(), ((ZBLinkSymbol*)pComp)->GetAbsolutePath());
                    pLog->AddLine(e);
                }

                ++m_FindCounter;
            }
        }

        if (InSubModel)
        {
            // Find in sub-model if there is
            if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
                !((ZBSymbol*)pComp)->IsChildModelRef())
            {
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->_Find(What, pLog, pPropAttributes, InSubModel, CaseSensitive, PartialSearch);
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the same model
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->_Find(What, pLog, pPropAttributes, InSubModel, CaseSensitive, PartialSearch);
            }
        }
    }
}

CODComponentSet* ZDProcessGraphModelMdl::_FindSymbol(CODComponent* pCompToFind, bool InSubModel /*= true*/)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If a symbol and the same name
        if (pComp == pCompToFind)
        {
            m_FindSet.Add(pComp);
        }

        if (InSubModel)
        {
            // Find in sub-model if there is
            if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
                !((ZBSymbol*)pComp)->IsChildModelRef())
            {
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->_FindSymbol(pCompToFind, InSubModel);
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the same model
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->_FindSymbol(pCompToFind, InSubModel);
            }
        }
    }

    return &m_FindSet;
}

CODComponentSet* ZDProcessGraphModelMdl::_FindSymbol(const CString    Name,
                                                     const CString    Path            /*= ""*/,
                                                     bool            InSubModel        /*= true*/,
                                                     bool            CaseSensitive    /*=false*/,
                                                     bool            OnlyLocal        /*= false*/)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If a symbol and the same name
        if (pComp && ISA(pComp, ZBSymbol))
        {
            if ((CaseSensitive && ((ZBSymbol*)pComp)->GetSymbolName() == Name) ||
                (!CaseSensitive && Name.CompareNoCase(((ZBSymbol*)pComp)->GetSymbolName()) == 0))
            {
                // If no path required or the path is equal
                // and if only local and islocal
                // add the element to the set
                if ((Path.IsEmpty() || (!Path.IsEmpty() && ((ZBSymbol*)pComp)->GetAbsolutePath() == Path)) &&
                    (OnlyLocal == false || (OnlyLocal && ((ZBSymbol*)pComp)->IsLocal())))
                {
                    m_FindSet.Add(pComp);
                }
            }
        }
        // If a link symbol and the same name
        else if (pComp && ISA(pComp, ZBLinkSymbol))
        {
            if ((CaseSensitive && ((ZBLinkSymbol*)pComp)->GetSymbolName() == Name) ||
                (!CaseSensitive && Name.CompareNoCase(((ZBLinkSymbol*)pComp)->GetSymbolName()) == 0))
            {
                // If no path required or the path is equal
                // and if only local and islocal
                // add the element to the set
                if ((Path.IsEmpty() || (!Path.IsEmpty() && ((ZBLinkSymbol*)pComp)->GetAbsolutePath() == Path)) &&
                    (OnlyLocal == false || (OnlyLocal && ((ZBLinkSymbol*)pComp)->IsLocal())))
                {
                    m_FindSet.Add(pComp);
                }
            }
        }

        if (InSubModel)
        {
            // Find in sub-model if there is
            if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
                !((ZBSymbol*)pComp)->IsChildModelRef())
            {
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->_FindSymbol(Name, Path, InSubModel, CaseSensitive, OnlyLocal);
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the same model
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->_FindSymbol(Name, Path, InSubModel, CaseSensitive, OnlyLocal);
            }
        }
    }

    return &m_FindSet;
}

CODComponentSet* ZDProcessGraphModelMdl::_FindSymbol(CODModel*    pModel,
                                                     bool        InSubModel    /*= true*/,
                                                     bool        OnlyLocal    /*= false*/)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // Test only for a symbol, because not child model on a deliverable
        // If a symbol and the same name
        if (pComp && ISA(pComp, ZBSymbol))
        {
            if (pComp && ISA(pComp, ZBSymbol) &&
                (OnlyLocal == false || (OnlyLocal && ((ZBSymbol*)pComp)->IsLocal())) &&
                ((ZBSymbol*)pComp)->GetChildModel() && ((ZBSymbol*)pComp)->GetChildModel() == pModel)
            {
                m_FindSet.Add(pComp);
            }
        }

        if (InSubModel)
        {
            // Find in sub-model if there is
            if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
                !((ZBSymbol*)pComp)->IsChildModelRef())
            {
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->_FindSymbol(pModel, InSubModel, OnlyLocal);
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the same model
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->_FindSymbol(pModel, InSubModel, OnlyLocal);
            }
        }
    }

    return &m_FindSet;
}

CODComponentSet* ZDProcessGraphModelMdl::_FindSymbolFromPath(const CString    Path,
                                                             bool            InSubModel        /*= true*/,
                                                             bool            CaseSensitive    /*=false*/,
                                                             bool            OnlyLocal        /*= false*/)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If a symbol and the same name
        if (pComp && ISA(pComp, ZBSymbol))
        {
            if (((CaseSensitive && ((ZBSymbol*)pComp)->GetAbsolutePath() == Path) ||
                (!CaseSensitive && Path.CompareNoCase(((ZBSymbol*)pComp)->GetAbsolutePath()) == 0)) &&
                 (OnlyLocal == false || (OnlyLocal && ((ZBSymbol*)pComp)->IsLocal())))
            {
                m_FindSet.Add(pComp);
            }
        }
        // If a link symbol and the same name
        else if (pComp && ISA(pComp, ZBLinkSymbol))
        {
            if (((CaseSensitive && ((ZBLinkSymbol*)pComp)->GetAbsolutePath() == Path) ||
                (!CaseSensitive && Path.CompareNoCase(((ZBLinkSymbol*)pComp)->GetAbsolutePath()) == 0)) &&
                 (OnlyLocal == false || (OnlyLocal && ((ZBLinkSymbol*)pComp)->IsLocal())))
            {
                m_FindSet.Add(pComp);
            }
        }

        if (InSubModel)
        {
            // Find in sub-model if there is
            if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
                !((ZBSymbol*)pComp)->IsChildModelRef())
            {
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->_FindSymbolFromPath(Path, InSubModel, CaseSensitive, OnlyLocal);
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the same model
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->_FindSymbolFromPath(Path, InSubModel, CaseSensitive, OnlyLocal);
            }
        }
    }

    return &m_FindSet;
}

CODComponentSet* ZDProcessGraphModelMdl::_FindSymbolByRefNumber(int RefNumber, bool InSubModel /*= true*/)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If a symbol and the same name
        if (pComp && ISA(pComp, ZBSymbol))
        {
            if (((ZBSymbol*)pComp)->GetSymbolReferenceNumber() == RefNumber)
            {
                m_FindSet.Add(pComp);
            }
        }
        // If a link symbol and the same name
        else if (pComp && ISA(pComp, ZBLinkSymbol))
        {
            if (((ZBLinkSymbol*)pComp)->GetSymbolReferenceNumber() == RefNumber)
            {
                m_FindSet.Add(pComp);
            }
        }

        if (InSubModel)
        {
            // Find in sub-model if there is
            if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
                !((ZBSymbol*)pComp)->IsChildModelRef())
            {
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->_FindSymbolByRefNumber(RefNumber, InSubModel);
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the same model
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->_FindSymbolByRefNumber(RefNumber, InSubModel);
            }
        }
    }

    return &m_FindSet;
}

CODComponentSet* ZDProcessGraphModelMdl::_FindSymbolPartialName(const CString    Name,
                                                                bool            InSubModel        /*= true*/,
                                                                bool            CaseSensitive    /*=false*/,
                                                                bool            OnlyLocal        /*= false*/)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If a symbol and the same name
        if (pComp && ISA(pComp, ZBSymbol))
        {
            // For non case sensitive search, transform the string to lowercase
            CString SymbName = ((ZBSymbol*)pComp)->GetSymbolName();
            SymbName.MakeLower();
            CString NameToFind = Name;
            NameToFind.MakeLower();

            // In case sensitive, use Find function
            if ((CaseSensitive && ((ZBSymbol*)pComp)->GetSymbolName().Find(Name) != -1) ||
                (!CaseSensitive && SymbName.Find(NameToFind) != -1))
            {
                // If no path required or the path is equal
                // and if only local and islocal
                // add the element to the set
                if (OnlyLocal == false || (OnlyLocal && ((ZBSymbol*)pComp)->IsLocal()))
                {
                    m_FindSet.Add(pComp);
                }
            }
        }
        // If a link symbol and the same name
        else if (pComp && ISA(pComp, ZBLinkSymbol))
        {
            // For non case sensitive search, transform the string to lowercase
            CString SymbName = ((ZBLinkSymbol*)pComp)->GetSymbolName();
            SymbName.MakeLower();

            CString NameToFind = Name;
            NameToFind.MakeLower();

            if ((CaseSensitive && ((ZBLinkSymbol*)pComp)->GetSymbolName().Find(Name) != -1) ||
                (!CaseSensitive && SymbName.Find(NameToFind) != -1))
            {
                // If no path required or the path is equal
                // and if only local and islocal
                // add the element to the set
                if (OnlyLocal == false || (OnlyLocal && ((ZBLinkSymbol*)pComp)->IsLocal()))
                {
                    m_FindSet.Add(pComp);
                }
            }
        }

        if (InSubModel)
        {
            // Find in sub-model if there is
            if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
                !((ZBSymbol*)pComp)->IsChildModelRef())
            {
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->_FindSymbolPartialName(Name, InSubModel, CaseSensitive, OnlyLocal);
            }
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the same model
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->_FindSymbolPartialName(Name, InSubModel, CaseSensitive, OnlyLocal);
            }
        }
    }

    return &m_FindSet;
}

ZDProcessGraphModelMdl* ZDProcessGraphModelMdl::_FindModelFromPath(const CString Path, bool CaseSensitive /*=false*/)
{
    if (((CaseSensitive && GetAbsolutePath() == Path) ||
        (!CaseSensitive && Path.CompareNoCase(GetAbsolutePath()) == 0)))
    {
        return this;
    }

    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // Find in sub-model if there is
        if (pComp && ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() && !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            ZDProcessGraphModelMdl* pMdl = reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->_FindModelFromPath(Path, CaseSensitive);

            if (pMdl)
            {
                return pMdl;
            }

            // Otherwise, continue
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the same model
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                ZDProcessGraphModelMdl* pMdl = pPage->GetpModel()->_FindModelFromPath(Path, CaseSensitive);

                if (pMdl)
                {
                    return pMdl;
                }

                // Otherwise, continue
            }
        }
    }

    return NULL;
}

// JMR-MODIF - Le 28 mars 2006 - Supperssion de la fonction _FindModel, car directement exécutée dans FindModel.
/*
ZDProcessGraphModelMdl* ZDProcessGraphModelMdl::_FindModel( const CString Name, bool CaseSensitive = false )
{
    if ( ( ( CaseSensitive && GetModelName() == Name ) ||
         (  !CaseSensitive && Name.CompareNoCase( GetModelName() ) == 0 ) ) )
    {
        return this;
    }

    CODComponentSet* pSet = GetComponents();

    for ( int i = 0; i < pSet->GetSize(); ++i )
    {
        CODComponent* pComp = pSet->GetAt( i );

        // Find in sub-model if there is, otherwise continue.
        if ( pComp && ISA( pComp, ZBSymbol )        &&
             ( (ZBSymbol*)pComp )->GetChildModel()    &&
             !( (ZBSymbol*)pComp )->IsChildModelRef() )
        {
            ZDProcessGraphModelMdl* pMdl =
                reinterpret_cast<ZDProcessGraphModelMdl*>( ( (ZBSymbol*)pComp )->GetChildModel() )->_FindModel( Name, CaseSensitive );

            if ( pMdl )
            {
                return pMdl;
            }
        }
    }

    // Run through all pages if there are
    if ( m_pPageSet != NULL )
    {
        ZBProcessGraphPageIterator i( m_pPageSet );

        for ( ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext() )
        {
            // Do not process the same model.
            if ( pPage->GetpModel() && pPage->GetpModel() != this )
            {
                // Check if it's the good model, otherwise continue.
                ZDProcessGraphModelMdl* pMdl = pPage->GetpModel()->_FindModel( Name, CaseSensitive );

                if ( pMdl )
                {
                    return pMdl;
                }
            }
        }
    }

    return NULL;
}
*/

void ZDProcessGraphModelMdl::DrawMetaFile(CDC* pDC, CRect& Rect)
{
    if (m_hMetaFile)
    {
        pDC->PlayMetaFile(m_hMetaFile, &Rect);
    }
}

void ZDProcessGraphModelMdl::SetParent(ZDProcessGraphModelMdl* value)
{
    m_pParent = value;

    // Set the parent name
    if (m_pParent)
    {
        m_ParentName = m_pParent->GetModelName();
    }
}

void ZDProcessGraphModelMdl::ClearPath()
{
    ZIObjectPath::ClearPath();
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
        {
            continue;
        }

        if (ISA(pComp, ZBSymbol))
        {
            reinterpret_cast<ZBSymbol*>(pComp)->ClearPath();
        }
        else if (ISA(pComp, ZBLinkSymbol))
        {
            reinterpret_cast<ZBLinkSymbol*>(pComp)->ClearPath();
        }

        if (ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // If the process has a child model,
            // process the child model
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->ClearPath();
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not clear the path of itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->ClearPath();
            }
        }
    }
}

void ZDProcessGraphModelMdl::CalculateAbsolutePath()
{
    // If no path defined
    if (GetAbsolutePath().IsEmpty())
    {
        // Set the path
        if (GetParent())
        {
            SetAbsolutePath(GetParent()->GetAbsolutePath());
        }

        AddMemberToPath(GetModelName());
    }

    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
        {
            continue;
        }

        if (ISA(pComp, ZBSymbol))
        {
            reinterpret_cast<ZBSymbol*>(pComp)->CalculateAbsolutePath();
        }
        else if (ISA(pComp, ZBLinkSymbol))
        {
            reinterpret_cast<ZBLinkSymbol*>(pComp)->CalculateAbsolutePath();
        }

        if (ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // If the process has a child model,
            // process the child model
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->CalculateAbsolutePath();
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not clear the path of itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->CalculateAbsolutePath();
            }
        }
    }
}

void ZDProcessGraphModelMdl::SetDefaultWkfProperty(bool RedefineOnExisting /*= false*/)
{}

void ZDProcessGraphModelMdl::DeleteAllActivitiesLinkedToWorkflow()
{}

void ZDProcessGraphModelMdl::OnSymbolNameChanged(CODComponent& Comp, const CString OldName)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp && ISA(pComp, ZBSymbol))
        {
            ((ZBSymbol*)pComp)->OnSymbolNameChanged(Comp, OldName);
        }
        else if (pComp && ISA(pComp, ZBLinkSymbol))
        {
            ((ZBLinkSymbol*)pComp)->OnSymbolNameChanged(Comp, OldName);
        }

        // Find in sub-model if there is
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->OnSymbolNameChanged(Comp, OldName);
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the page pointing on itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                // call the methods for all pages
                pPage->GetpModel()->OnSymbolNameChanged(Comp, OldName);
            }
        }
    }
}

void ZDProcessGraphModelMdl::OnPageNameChanged(ZDProcessGraphPage* pPage, const CString OldName)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp && ISA(pComp, ZBSymbol))
        {
            ((ZBSymbol*)pComp)->OnPageNameChanged(pPage, OldName);
        }
        else if (pComp && ISA(pComp, ZBLinkSymbol))
        {
            ((ZBLinkSymbol*)pComp)->OnPageNameChanged(pPage, OldName);
        }

        // Find in sub-model if there is
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->OnPageNameChanged(pPage, OldName);
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pGraphPage = i.GetFirst(); pGraphPage != NULL; pGraphPage = i.GetNext())
        {
            // Do not process the page pointing on itself
            if (pGraphPage->GetpModel() && pGraphPage->GetpModel() != this)
            {
                // call the methods for all pages
                pGraphPage->GetpModel()->OnPageNameChanged(pPage, OldName);
            }
        }
    }
}

void ZDProcessGraphModelMdl::OnUserEntityChanged(ZBUserEntity* pUserEntity, const CString OldName)
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent*    pComp = pSet->GetAt(i);

        if (pComp && ISA(pComp, ZBSymbol))
        {
            ((ZBSymbol*)pComp)->OnUserEntityChanged(pUserEntity, OldName);
        }
        else if (pComp && ISA(pComp, ZBLinkSymbol))
        {
            ((ZBLinkSymbol*)pComp)->OnUserEntityChanged(pUserEntity, OldName);
        }

        // Find in sub-model if there is
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->OnUserEntityChanged(pUserEntity, OldName);
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the page pointing on itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                // call the methods for all pages
                pPage->GetpModel()->OnUserEntityChanged(pUserEntity, OldName);
            }
        }
    }
}

void ZDProcessGraphModelMdl::OnPostOpenDocument(long DocumentVersion)
{
    // Do nothing in the base class
}

void ZDProcessGraphModelMdl::PostWrite(CArchive& ar)
{}

void ZDProcessGraphModelMdl::PostRead(CArchive& ar)
{
    // Recalculate the parent models
    RecalculateParentPtr();

    // Recalculate the child model pointer
    RecalculateChildModelPtr();

    // And reference to symbol
    RecalculateReference();

    // Recalculate all the symbol references
    RecalculateSymbolReferences();
}

void ZDProcessGraphModelMdl::RecalculateReference()
{
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // Check if the symbol is a reference
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->IsReferenced())
        {
            ASSERT(GetRoot());

            CODComponentSet* pSet =
                GetRoot()->FindSymbolByRefNumber(atoi(((ZBSymbol*)pComp)->GetNameOfReference()), true);

            if (pSet && pSet->GetSize() > 0 && pSet->GetAt(0) && ISA(pSet->GetAt(0), ZBSymbol))
            {
                ((ZBSymbol*)pComp)->AssignReferenceSymbol((ZBSymbol*)pSet->GetAt(0));
            }
        }
        else if (pComp && ISA(pComp, ZBLinkSymbol) && ((ZBLinkSymbol*)pComp)->IsReferenced())
        {
            ASSERT(GetRoot());

            CODComponentSet* pSet =
                GetRoot()->FindSymbolByRefNumber(atoi(((ZBLinkSymbol*)pComp)->GetNameOfReference()), true);

            if (pSet && pSet->GetSize() > 0 && pSet->GetAt(0) && ISA(pSet->GetAt(0), ZBLinkSymbol))
            {
                ((ZBLinkSymbol*)pComp)->AssignReferenceSymbol((ZBLinkSymbol*)pSet->GetAt(0));
            }
        }

        // Find in sub-model if there is
        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->RecalculateReference();
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the page pointing on itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                // The parent of all pages is itself
                pPage->GetpModel()->RecalculateReference();
            }
        }
    }
}

void ZDProcessGraphModelMdl::RecalculateParentPtr()
{
    CalculateAbsolutePath();

    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent*    pComp = pSet->GetAt(i);

        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // If the process has a child model,
            // assigns the pointer of this model
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->SetParent(this);

            // and recalculate its model also
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->RecalculateParentPtr();
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not process the page pointing on itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                // The parent of all pages is itself
                pPage->GetpModel()->SetParent(this);
                pPage->GetpModel()->RecalculateParentPtr();
            }
        }
    }
}

void ZDProcessGraphModelMdl::RecalculateChildModelPtr()
{
    ZDProcessGraphModelMdl* pRootModel = GetRoot();
    CODComponentSet* pSet = GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->IsChildModelRef() &&
            !((ZBSymbol*)pComp)->GetChildModel() && !((ZBSymbol*)pComp)->GetChildModelPathName().IsEmpty())
        {
            ((ZBSymbol*)pComp)->SetChildModel(reinterpret_cast<ZDProcessGraphModelMdl*>(pRootModel)->FindModelFromPath(((ZBSymbol*)pComp)->GetChildModelPathName(), true));
        }

        if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
            !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // and recalculate its model also
            reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->RecalculateChildModelPtr();
        }
    }

    // Run through all pages if there are
    if (m_pPageSet != NULL)
    {
        ZBProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not recalculate itself
            if (pPage->GetpModel() && pPage->GetpModel() != this)
            {
                pPage->GetpModel()->RecalculateChildModelPtr();
            }
        }
    }
}

size_t ZDProcessGraphModelMdl::GetFollowingSymbols(ZBSymbol* pComp, CODNodeArray& Nodes)
{
    if (pComp)
    {
        return pComp->GetFollowingSymbols(Nodes);
    }

    return 0;
}

size_t ZDProcessGraphModelMdl::GetEnteringSymbols(ZBSymbol* pComp, CODNodeArray& Nodes)
{
    if (pComp)
    {
        return pComp->GetEnteringSymbols(Nodes);
    }

    return 0;
}

size_t ZDProcessGraphModelMdl::GetEdgesLeaving(ZBSymbol* pComp, CODEdgeArray& Edges)
{
    if (pComp)
    {
        return pComp->GetEdgesLeaving(Edges);
    }

    return 0;
}

size_t ZDProcessGraphModelMdl::GetEdgesEntering(ZBSymbol* pComp, CODEdgeArray& Edges)
{
    if (pComp)
    {
        return pComp->GetEdgesEntering(Edges);
    }

    return 0;
}

size_t ZDProcessGraphModelMdl::GetFollowingSymbolsISA(ZBSymbol*            pComp,
                                                      CODNodeArray&        Nodes,
                                                      const CRuntimeClass*    pClass)
{
    if (!pComp)
    {
        return 0;
    }

    pComp->GetFollowingSymbols(Nodes);

    return KeepOnlySymbolsISA(Nodes, pClass);
}

size_t ZDProcessGraphModelMdl::GetEnteringSymbolsISA(ZBSymbol*                pComp,
                                                     CODNodeArray&            Nodes,
                                                     const CRuntimeClass*    pClass)
{
    if (!pComp)
    {
        return 0;
    }

    pComp->GetEnteringSymbols(Nodes);

    return KeepOnlySymbolsISA(Nodes, pClass);
}

size_t ZDProcessGraphModelMdl::GetEdgesLeavingISA(ZBSymbol*            pComp,
                                                  CODEdgeArray&        Edges,
                                                  const CRuntimeClass*    pClass)
{
    if (!pComp)
    {
        return 0;
    }

    pComp->GetEdgesLeaving(Edges);

    return KeepOnlyLinksISA(Edges, pClass);
}

size_t ZDProcessGraphModelMdl::GetEdgesEnteringISA(ZBSymbol*                pComp,
                                                   CODEdgeArray&            Edges,
                                                   const CRuntimeClass*    pClass)
{
    if (!pComp)
    {
        return 0;
    }

    pComp->GetEdgesEntering(Edges);

    return KeepOnlyLinksISA(Edges, pClass);
}

size_t ZDProcessGraphModelMdl::GetSymbolsISA(CODNodeArray&            Nodes,
                                             const CRuntimeClass*    pClass,
                                             bool                    Deep    /*= false*/)
{
    CODComponentSet* pSet = GetComponents();

    if (!pSet)
    {
        return 0;
    }

    // Run through all elements
    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp && pComp->IsKindOf(pClass))
        {
            Nodes.Add(guid_cast<IODNode*>(pComp));
        }

        // If need to go deeper
        if (Deep)
        {
            if (pComp && ISA(pComp, ZBSymbol) && ((ZBSymbol*)pComp)->GetChildModel() &&
                !((ZBSymbol*)pComp)->IsChildModelRef())
            {
                // and run through its model also
                reinterpret_cast<ZDProcessGraphModelMdl*>(((ZBSymbol*)pComp)->GetChildModel())->GetSymbolsISA(Nodes, pClass, Deep);
            }
        }
    }

    // And finally if need to go through pages also
    if (Deep)
    {
        // Run through all pages if there are
        if (m_pPageSet != NULL)
        {
            ZBProcessGraphPageIterator i(m_pPageSet);

            for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
            {
                // Do not process the page pointing on itself
                if (pPage->GetpModel() && pPage->GetpModel() != this)
                {
                    // The parent of all pages is itself
                    pPage->GetpModel()->GetSymbolsISA(Nodes, pClass, Deep);
                }
            }
        }
    }

    return Nodes.GetSize();
}

size_t ZDProcessGraphModelMdl::KeepOnlySymbolsISA(CODNodeArray& Nodes, const CRuntimeClass* pClass)
{
    return ZUODSymbolManipulator::KeepOnlySymbolsISA(Nodes, pClass);
}

size_t ZDProcessGraphModelMdl::KeepOnlyLinksISA(CODEdgeArray& Edges, const CRuntimeClass* pClass)
{
    return ZUODSymbolManipulator::KeepOnlyLinksISA(Edges, pClass);
}

size_t ZDProcessGraphModelMdl::FindActivity(ZBSymbol* pCompToFind, CODNodeArray& Nodes)
{
    size_t Counter = 0;

    for (int nNodeIdx = 0; nNodeIdx < Nodes.GetSize(); ++nNodeIdx)
    {
        IODNode* pINode = Nodes.GetAt(nNodeIdx);

        CODSymbolComponent* pComp = static_cast<CODSymbolComponent*>(pINode);

        if (!pComp)
        {
            continue;
        }

        if (pComp == pCompToFind)
        {
            ++Counter;
        }
    }

    return Counter;
}

size_t ZDProcessGraphModelMdl::FindLink(CODLinkComponent* pCompToFind, CODEdgeArray& Edges)
{
    size_t Counter = 0;

    for (int nEdgeIdx = 0; nEdgeIdx < Edges.GetSize(); ++nEdgeIdx)
    {
        IODEdge* pIEdge = Edges.GetAt(nEdgeIdx);

        CODLinkComponent* pComp = static_cast<CODLinkComponent*>(pIEdge);

        if (!pComp)
        {
            continue;
        }

        if (pComp == pCompToFind)
        {
            ++Counter;
        }
    }

    return Counter;
}

void ZDProcessGraphModelMdl::RemoveAllSymbolInParsedArray()
{
    size_t Size = m_SymbolParsed.GetSize();

    for (register size_t Index = 0; Index < Size; ++Index)
    {
        if (m_SymbolParsed.GetAt(Index) != NULL)
        {
            delete m_SymbolParsed.GetAt(Index);
        }
    }

    m_SymbolParsed.RemoveAll();
}

ZDProcessGraphModelMdl::ZBComponentRef* ZDProcessGraphModelMdl::FindSymbolInParsedArray(ZBSymbol* pComp)
{
    size_t Size = m_SymbolParsed.GetSize();

    for (register size_t Index = 0; Index < Size; ++Index)
    {
        if (m_SymbolParsed.GetAt(Index)->m_pSymbol == pComp)
        {
            return m_SymbolParsed.GetAt(Index);
        }
    }

    return NULL;
}

size_t ZDProcessGraphModelMdl::AddSymbolInParsedArray(ZBSymbol* pComp)
{
    ZDProcessGraphModelMdl::ZBComponentRef* pRef = FindSymbolInParsedArray(pComp);

    if (pRef)
    {
        pRef->AddRef();

        return pRef->m_Ref;
    }

    m_SymbolParsed.Add((new ZBComponentRef(pComp)));

    return 1;
}

// JMR-MODIF - Le 5 août 2005 - Retourne l'état du drapeau indiquant si le fond de page doit être restauré.
BOOL ZDProcessGraphModelMdl::IsBkGndMustBeRestored()
{
    return bBkGndFlag;
}

// JMR-MODIF - Le 5 août 2005 - Remet le drapeau de restauration du fond de page à FALSE.
void ZDProcessGraphModelMdl::ResetBkGndMustBeRestored()
{
    bBkGndFlag = FALSE;
}

void ZDProcessGraphModelMdl::SetIsLogo(BOOL IsLogo)
{
    bIsLogo = IsLogo;
}

BOOL ZDProcessGraphModelMdl::IsLogo()
{
    return bIsLogo;
}

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphModelMdl diagnostics

#ifdef _DEBUG
void ZDProcessGraphModelMdl::AssertValid() const
{
    CODModel::AssertValid();
}

void ZDProcessGraphModelMdl::Dump(CDumpContext& dc) const
{
    CODModel::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphModelMdl serialization

void ZDProcessGraphModelMdl::SerializePageSet(CArchive& ar)
{
    if (ar.IsStoring())
    {
        if (m_pPageSet == NULL)
        {
            ar << (int)0;
        }
        else
        {
            CString    EmptyString;
            EmptyString.Empty();
            ZDProcessGraphModelMdl* pRootModel = GetRoot();
            ZDProcessGraphModelMdl* pNULLModel = NULL;

            ZBProcessGraphPageIterator i(m_pPageSet);

            // Serialize the number of element
            ar << m_pPageSet->GetSize();

            for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
            {
                ar << pPage->GetPageName();

                // Do not serialize root model, already serialized by the document
                if (pPage->GetpModel())
                {
                    ar << pPage->GetpModel()->GetAbsolutePath();

                    if (pPage->GetpModel() != this)
                    {
                        ar << pPage->GetpModel();
                    }
                    else
                    {
                        ar << pNULLModel;
                    }
                }
                else
                {
                    ar << EmptyString;
                }
            }
        }
    }
    else
    {
        DeleteAllPageInSet();

        int Count;
        ar >> Count;

        if (Count > 0)
        {
            ZDProcessGraphModelMdl* pRootModel = GetRoot();
            ZDProcessGraphModelMdl* pModelFound = NULL;

            if (pRootModel)
            {
                if (!m_pPageSet)
                {
                    AllocatePageSet();
                }

                CString PageName;
                CString ModelName;

                for (int i = 0; i < Count; ++i)
                {
                    ar >> PageName;
                    ar >> ModelName;

                    if (!ModelName.IsEmpty())
                    {
                        ar >> pModelFound;

                        if (!pModelFound)
                        {
                            pModelFound = pRootModel->FindModelFromPath(ModelName, true);
                        }

                        if (pModelFound)
                        {
                            ZDProcessGraphPage* pPage = new ZDProcessGraphPage(PageName, pModelFound);
                            m_pPageSet->Add(pPage);
                        }
                    }
                }
            }
        }
        else m_pPageSet = NULL;
    }
}

void ZDProcessGraphModelMdl::Serialize(CArchive& ar)
{
    // JMR-MODIF - Le 5 août 2005 - Inscription de la trame de fond sous forme de nom de fichier plutôt que directement.
    if (dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 22)
    {
        if (ar.IsStoring())
        {
            ar << m_BkGndFilename;

            // JMR-MODIF - Le 7 octobre 2005 - Intègre le marquage du logo au document.
            if (dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 23)
            {
                // JMR-MODIF - Le 10 septembre 2007 - Conversion de BOOL en int pour respecter la logique du code.
                ar << (int)bIsLogo;
            }

            // Détrame le modèle.
            ClearBackgroundComponent(true);

            // Enregistre le modèle.
            CODModel::Serialize(ar);
        }
        else
        {
            ar >> m_BkGndFilename;

            // JMR-MODIF - Le 7 octobre 2005 - Récupère le marquage du logo depuis le document.
            if (dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 23)
            {
                // JMR-MODIF - Le 10 septembre 2007 - Conversion de int en BOOL pour respecter la logique du code.
                int Value;
                ar >> Value;
                bIsLogo = (Value == 1) ? TRUE : FALSE;
            }

            // Charge le modèle.
            CODModel::Serialize(ar);
        }

        // Pose le drapeau pour la restauration du tramage.
        bBkGndFlag = TRUE;
    }
    else
    {
        CODModel::Serialize(ar);
    }

    if (ar.IsStoring())
    {
        ar << m_ParentName;
        ar << m_ObjectPath;
        ar << (DWORD)m_Notation;

        // JMR-MODIF - Le 2 juillet 2006 - Sauvegarde de la variable de génération des références internes.
        if (dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 25)
        {
            ar << m_NextAvailableRefNbr;
        }
    }
    else
    {
        ar >> m_ParentName;
        ar >> m_ObjectPath;

        DWORD dwValue;
        ar >> dwValue;

        m_Notation = EModelNotation(dwValue);

        // JMR-MODIF - Le 2 juillet 2006 - Sauvegarde de la variable de génération des références internes.
        if (dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 25)
        {
            ar >> m_NextAvailableRefNbr;
        }
    }

    // The page set
    SerializePageSet(ar);
}
