/****************************************************************************
 * ==> PSS_ProcessGraphModelMdl --------------------------------------------*
 ****************************************************************************
 * Description : Provides a process graphic model                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessGraphModelMdl.h"

// processoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_Log.h"
#include "zModel\ZBGenericSymbolErrorLine.h"
#include "zModel\ZBSearchSymbolLogLine.h"
#include "PSS_ProcessGraphModelController.h"
#include "PSS_ProcessGraphModelDoc.h"
#include "PSS_ProcessGraphModelViewport.h"
#include "ZDProcessGraphPage.h"
#include "ZBSymbol.h"
#include "PSS_LinkSymbol.h"
#include "ZBLanguageProp.h"
#include "PSS_BasicModelProperties.h"
#include "ZUODSymbolManipulator.h"
#include "ZBSymbolObserverMsg.h"
#include "ZBDocObserverMsg.h"

// resources
#include "zModelRes.h"
#include "PSS_ResIDs.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const std::size_t g_RecursionMaxLoop = 5000;
//---------------------------------------------------------------------------
// PSS_ProcessGraphModelMdl::IComponentRef
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl::IComponentRef::IComponentRef(ZBSymbol* pSymbol) :
    m_pSymbol(pSymbol),
    m_Ref(1)
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::IComponentRef::AddRef()
{
    ++m_Ref;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::IComponentRef::RemoveRef()
{
    if (m_Ref)
        --m_Ref;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::IComponentRef::GetRef() const
{
    return m_Ref;
}
//---------------------------------------------------------------------------
ZBSymbol* PSS_ProcessGraphModelMdl::IComponentRef::GetSymbol() const
{
    return m_pSymbol;
}
//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
ZBUserGroupEntity*                                                                         PSS_ProcessGraphModelMdl::m_pMainUserGroup          = NULL;
ZBLogicalSystemEntity*                                                                     PSS_ProcessGraphModelMdl::m_pMainLogicalSystem      = NULL;
ZBLogicalPrestationsEntity*                                                                PSS_ProcessGraphModelMdl::m_pMainLogicalPrestations = NULL;
ZBLogicalRulesEntity*                                                                      PSS_ProcessGraphModelMdl::m_pMainLogicalRules       = NULL;
CArray<PSS_ProcessGraphModelMdl::IComponentRef*, PSS_ProcessGraphModelMdl::IComponentRef*> PSS_ProcessGraphModelMdl::m_SymbolParsed;
CODComponentSet                                                                            PSS_ProcessGraphModelMdl::m_FindSet;
int                                                                                        PSS_ProcessGraphModelMdl::m_RecursionCounter        = 0;
bool                                                                                       PSS_ProcessGraphModelMdl::m_IsInRecursion           = false;
std::size_t                                                                                PSS_ProcessGraphModelMdl::m_FindCounter             = 0;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ProcessGraphModelMdl, CODModel, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ProcessGraphModelMdl
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl::PSS_ProcessGraphModelMdl(const CString& name, PSS_ProcessGraphModelMdl* pParent) :
    CODModel(),
    m_pCtlr(NULL),
    m_pPageSet(NULL),
    m_Notation(E_MN_Unknown),
    m_MainUserGroupIsValid(false),
    m_MainLogicalSystemIsValid(false),
    m_MainLogicalPrestationsIsValid(false),
    m_MainLogicalRulesIsValid(false),
    m_IsInCutOperation(false),
    m_pParent(pParent),
    m_hMetaFile(NULL),
    m_NextAvailableRefNb(1),
    m_BgFlag(FALSE),
    m_IsLogo(FALSE)
{
    CreateSymbolProperties();

    // set the model name
    SetModelName(name);

    // set the can select flag to true
    SetCanSelect(TRUE);

    // set the parent name
    if (m_pParent)
        m_ParentName = m_pParent->GetModelName();

    CalculateAbsolutePath();
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl::~PSS_ProcessGraphModelMdl()
{
    // NOTE use a fully qualified name here to avoid to call a pure virtual frunction during the destruction
    PSS_ProcessGraphModelMdl::DeleteAllPages();

    if (m_hMetaFile)
        ::DeleteEnhMetaFile(m_hMetaFile);

    if (m_pPageSet)
        delete m_pPageSet;

    // release all observers, don't delete them, they were already deleted sooner
    m_observers.resize(0);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::DeleteModelSet()
{
    // get all model components
    CODComponentSet* pSet = GetComponents();

    if (pSet)
    {
        const int componentCount = pSet->GetSize();

        // iterate through all model components and delete each of them
        for (int i = 0; i < componentCount; ++i)
        {
            // get the next symbol
            ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

            // if a sub-model is defined, and not a referenced model, and if it contains a page,
            // iterate through the sub-models in a recursive way
            if (pSymbol && !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                if (pChildModel && pChildModel->HasPageSet())
                    pChildModel->DeleteModelSet();
            }
        }
    }

    // iterate through all existing pages
    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pPage->GetModel());

            // don't modify this model
            if (pModel && pModel != this)
                pModel->DeleteModelSet();
        }
    }

    // delete the model children
    RemoveAllChildren();

    // cleanup the commands in the model transaction
    MvcTransactionModel* pTransactionModel = GetTransactionModel();

    if (pTransactionModel)
    {
        pTransactionModel->Reset();
        pTransactionModel = NULL;
    }

    // cleanup the background image
    if (m_pBkgndComponent)
    {
        delete m_pBkgndComponent;
        m_pBkgndComponent = NULL;
    }

    // delete all the model opened pages
    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pModel = pPage->GetModel();

            if (pModel != this)
            {
                delete pModel;
                pPage->SetModel(NULL);
            }

            delete pPage;
        }

        // remove all elements
        m_pPageSet->RemoveAll();

        delete m_pPageSet;
        m_pPageSet = NULL;
    }

    // reset the modification falg
    SetModifiedFlag(FALSE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::DetachAllObserversInHierarchy(PSS_ProcessGraphModelViewport* pViewport,
                                                             PSS_ProcessGraphModelDoc*      pDocument)
{
    // get all the model components
    CODComponentSet* pSet = GetComponents();

    if (pSet)
    {
        const int componentCount = pSet->GetSize();

        // iterate through all model components and delete each of them
        for (int i = 0; i < componentCount; ++i)
        {
            // get the next symbol
            ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

            // if a sub-model is defined, and not a referenced model, and if it contains a page,
            // iterate through the sub-models in a recursive way
            if (pSymbol && !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                if (pChildModel && pChildModel->HasPageSet())
                    pChildModel->DetachAllObserversInHierarchy(pViewport, pDocument);
            }
        }
    }

    // iterate through the existing pages
    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pModel = pPage->GetModel();

            // don't modify this model
            if (pModel && pModel != this)
                pModel->DetachAllObserversInHierarchy(pViewport, pDocument);
        }
    }

    // cleanup the model observers
    RemoveObserver(pViewport);
    DetachObserver(pDocument);

    // reset the modification falg
    SetModifiedFlag(FALSE);
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelController* PSS_ProcessGraphModelMdl::CreateController(PSS_ProcessGraphModelViewport* pVp)
{
    return new PSS_ProcessGraphModelController(pVp);
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport* PSS_ProcessGraphModelMdl::CreateViewport(PSS_ProcessGraphModelView* pView)
{
    // create a basic viewport
    return new MvcScrollWrapper_T<PSS_ProcessGraphModelViewport>();
}
//---------------------------------------------------------------------------
CDocument* PSS_ProcessGraphModelMdl::GetDocument()
{
    PSS_ProcessGraphModelController* pCtrl = dynamic_cast<PSS_ProcessGraphModelController*>(m_pCtlr);

    if (pCtrl)
        return pCtrl->GetDocument();

    return NULL;
}
//---------------------------------------------------------------------------
const CDocument* PSS_ProcessGraphModelMdl::GetDocument() const
{
    PSS_ProcessGraphModelController* pCtrl = dynamic_cast<PSS_ProcessGraphModelController*>(m_pCtlr);

    if (pCtrl)
        return pCtrl->GetDocument();

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::GetCheckConsistency() const
{
    PSS_ProcessGraphModelMdl* pRoot = const_cast<PSS_ProcessGraphModelMdl*>(this)->GetRoot();
    ASSERT(pRoot);

    const PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pRoot->GetDocument());

    if (pDoc)
        return pDoc->GetCheckConsistency();

    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetCheckConsistency(bool value)
{
    PSS_ProcessGraphModelMdl* pRoot = GetRoot();
    ASSERT(pRoot);

    PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pRoot->GetDocument());

    if (pDoc)
        pDoc->SetCheckConsistency(value);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::GetIntegrateCostSimulation() const
{
    const PSS_ProcessGraphModelMdl* pRoot = const_cast<PSS_ProcessGraphModelMdl*>(this)->GetRoot();
    ASSERT(pRoot);

    const PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<const PSS_ProcessGraphModelDoc*>(pRoot->GetDocument());

    if (pDoc)
        return pDoc->GetIntegrateCostSimulation();

    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetIntegrateCostSimulation(bool value)
{
    PSS_ProcessGraphModelMdl* pRoot = GetRoot();
    ASSERT(pRoot);

    PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pRoot->GetDocument());

    if (pDoc)
        pDoc->SetIntegrateCostSimulation(value);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::GetUseWorkflow() const
{
    const PSS_ProcessGraphModelMdl* pRoot = const_cast<PSS_ProcessGraphModelMdl*>(this)->GetRoot();
    ASSERT(pRoot);

    const PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<const PSS_ProcessGraphModelDoc*>(pRoot->GetDocument());

    if (pDoc)
        return pDoc->GetUseWorkflow();

    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetUseWorkflow(bool value)
{
    PSS_ProcessGraphModelMdl* pRoot = GetRoot();
    ASSERT(pRoot);

    PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pRoot->GetDocument());

    if (pDoc)
        pDoc->SetUseWorkflow(value);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::GetShowPageBorder() const
{
    const PSS_ProcessGraphModelMdl* pRoot = const_cast<PSS_ProcessGraphModelMdl*>(this)->GetRoot();
    ASSERT(pRoot);

    const PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<const PSS_ProcessGraphModelDoc*>(pRoot->GetDocument());

    if (pDoc)
        return pDoc->GetShowPageBorder();

    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetShowPageBorder(bool value)
{
    PSS_ProcessGraphModelMdl* pRoot = GetRoot();
    ASSERT(pRoot);

    PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pRoot->GetDocument());

    if (pDoc)
        pDoc->SetShowPageBorder(value);
}
//---------------------------------------------------------------------------
const ELanguage PSS_ProcessGraphModelMdl::GetLanguage()
{
    ZBLanguageProp* pProps = static_cast<ZBLanguageProp*>(GetProperty(ZS_BP_PROP_LANGUAGE));

    // not exists? Create it
    if (!pProps)
    {
        CreateSymbolProperties();
        pProps = static_cast<ZBLanguageProp*>(GetProperty(ZS_BP_PROP_LANGUAGE));
    }

    // still not exists? Return unknown as error
    if (!pProps)
        return E_LN_Unknown;

    return pProps->GetLanguage();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetLanguage(ELanguage value)
{
    ZBLanguageProp* pProps = static_cast<ZBLanguageProp*>(GetProperty(ZS_BP_PROP_LANGUAGE));

    if (!pProps)
    {
        CreateSymbolProperties();
        pProps = static_cast<ZBLanguageProp*>(GetProperty(ZS_BP_PROP_LANGUAGE));
    }
    else
    {
        ZBLanguageProp props = *pProps;
        props.SetLanguage(value);
        SetProperty(&props);
    }
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelMdl::RetrieveUnitGUID(const CString& name, bool& error) const
{
    error = false;

    if (m_pMainUserGroup)
    {
        ZBUserEntitySet* pSet = m_pMainUserGroup->FindGroup(name, true);

        if (pSet && pSet->GetSize() > 0)
            return pSet->GetAt(0)->GetGUID();
    }

    error = true;
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelMdl::RetrieveUnitName(const CString& guid, bool& error) const
{
    error = false;

    if (m_pMainUserGroup)
    {
        ZBUserEntity* pEntity = m_pMainUserGroup->FindGroupByGUID(guid, true);

        if (pEntity)
            return pEntity->GetEntityName();
    }

    error = true;
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelMdl::RetrieveUnitDescription(const CString& guid, bool& error) const
{
    error = false;

    if (m_pMainUserGroup)
    {
        ZBUserEntity* pEntity = m_pMainUserGroup->FindGroupByGUID(guid, true);

        if (pEntity)
            return pEntity->GetEntityDescription();
    }

    error = true;
    return _T("");
}
//---------------------------------------------------------------------------
float PSS_ProcessGraphModelMdl::RetrieveUnitCost(const CString& guid, bool& error) const
{
    error = false;

    if (m_pMainUserGroup)
    {
        ZBUserEntity* pEntity = m_pMainUserGroup->FindGroupByGUID(guid, true);

        if (pEntity)
            return pEntity->GetEntityCost();
    }

    error = true;
    return 0;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::ReassignUnit(PSS_Log* pLog)
{}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelMdl::RetrieveLogicalSystemGUID(const CString& name, bool& error) const
{
    error = false;

    if (m_pMainLogicalSystem)
    {
        ZBSystemEntitySet* pSet = m_pMainLogicalSystem->FindSystem(name, true);

        if (pSet && pSet->GetSize() > 0)
            return pSet->GetAt(0)->GetGUID();
    }

    error = true;
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelMdl::RetrieveLogicalSystemName(const CString& guid, bool& error) const
{
    error = false;

    if (m_pMainLogicalSystem)
    {
        ZBSystemEntity* pEntity = m_pMainLogicalSystem->FindSystemByGUID(guid, true);

        if (pEntity)
            return pEntity->GetEntityName();
    }

    error = true;
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelMdl::RetrieveLogicalSystemDescription(const CString& guid, bool& error) const
{
    error = false;

    if (m_pMainLogicalSystem)
    {
        ZBSystemEntity* pEntity = m_pMainLogicalSystem->FindSystemByGUID(guid, true);

        if (pEntity)
            return pEntity->GetEntityDescription();
    }

    error = true;
    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::ReassignSystem(PSS_Log* pLog)
{}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelMdl::RetrievePrestationName(const CString& guid, bool& error) const
{
    error = false;

    if (m_pMainLogicalPrestations)
    {
        ZBLogicalPrestationsEntity* pPrestation =
                dynamic_cast<ZBLogicalPrestationsEntity*>(m_pMainLogicalPrestations->FindPrestationByGUID(guid, true));

        if (pPrestation)
            return pPrestation->GetEntityName();
    }

    error = true;
    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::ReassignPrestations(PSS_Log* pLog)
{}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelMdl::RetrieveRuleName(const CString guid, bool& error) const
{
    error = false;

    if (m_pMainLogicalRules)
    {
        ZBLogicalRulesEntity* pRule =
                dynamic_cast<ZBLogicalRulesEntity*>(m_pMainLogicalRules->FindRuleByGUID(guid, true));

        if (pRule)
            return pRule->GetEntityName();
    }

    error = true;
    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::ReassignRules(PSS_Log* pLog)
{}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl::IProcessGraphPageSet* PSS_ProcessGraphModelMdl::GetMainPageSet()
{
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();
    return (pRootModel ? pRootModel->GetPageSet() : NULL);
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl::IProcessGraphPageSet* PSS_ProcessGraphModelMdl::AllocateMainPageSet()
{
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();
    return (pRootModel ? pRootModel->AllocatePageSet() : NULL);
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl::IProcessGraphPageSet* PSS_ProcessGraphModelMdl::AllocatePageSet()
{
    m_pPageSet = new IProcessGraphPageSet;
    return m_pPageSet;
}
//---------------------------------------------------------------------------
ZDProcessGraphPage* PSS_ProcessGraphModelMdl::GetRootMainModelPage()
{
    IProcessGraphPageSet* pPageSet = GetMainPageSet();
    return (pPageSet && pPageSet->GetSize() > 0 ? pPageSet->GetAt(0) : NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetRootMainModelPage(ZDProcessGraphPage* pPage)
{
    IProcessGraphPageSet* pSet = GetMainPageSet();

    if (pSet)
        if (pSet->GetSize() > 0)
            pSet->SetAt(0, pPage);
        else
            pSet->Add(pPage);
}
//---------------------------------------------------------------------------
ZDProcessGraphPage* PSS_ProcessGraphModelMdl::GetMainModelPage()
{
    IProcessGraphPageSet* pPageSet = GetPageSet();
    return (pPageSet && pPageSet->GetSize() > 0 ? pPageSet->GetAt(0) : NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetMainModelPage(ZDProcessGraphPage* pPage)
{
    IProcessGraphPageSet* pSet = GetPageSet();

    if (pSet)
        if (pSet->GetSize() > 0)
            pSet->SetAt(0, pPage);
        else
            pSet->Add(pPage);
}
//---------------------------------------------------------------------------
ZDProcessGraphPage* PSS_ProcessGraphModelMdl::FindModelPage(const CString& modelName, bool inSubModel)
{
    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pModel = pPage->GetModel();

            if (pModel && pModel->GetModelName() == modelName)
                return pPage;
            else
            // if do search in sub-model, locate the model
            if (inSubModel && SubModelExist(modelName, true))
                return pPage;
        }
    }

    // process the model components
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        // if a sub-model exists, and is not a referenced model, and contains a page set
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel && pChildModel->HasPageSet())
            {
                // recursively call the same method
                ZDProcessGraphPage* pPage = pChildModel->FindModelPage(modelName, inSubModel);

                if (pPage)
                    return pPage;
            }
        }
    }

    // not found
    return NULL;
}
//---------------------------------------------------------------------------
ZDProcessGraphPage* PSS_ProcessGraphModelMdl::FindModelPage(PSS_ProcessGraphModelMdl* pModel, bool inSubModel)
{
    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            if (pPageModel == pModel)
                return pPage;

            // do not check for itself
            if (pPageModel && pPageModel != this)
            {
                ZDProcessGraphPage* pSubPage = pPageModel->FindModelPage(pModel, inSubModel);

                if (pSubPage)
                    return pSubPage;
            }
        }
    }

    // process the model components
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        // if sub-model exists, not a referenced model, and contains a page set
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel && pChildModel->HasPageSet())
            {
                // recursively call the same method
                ZDProcessGraphPage* pPage = pChildModel->FindModelPage(pModel, inSubModel);

                if (pPage)
                    return pPage;
            }
        }
    }

    // not found
    return NULL;
}
//---------------------------------------------------------------------------
ZDProcessGraphPage* PSS_ProcessGraphModelMdl::FindPage(const CString& pageName)
{
    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            // if the right page was found
            if (pPage->GetPageName() == pageName)
                return pPage;

            PSS_ProcessGraphModelMdl* pModel = pPage->GetModel();

            // do not process the same model
            if (pModel && pModel != this)
            {
                ZDProcessGraphPage* pChildPage = pModel->FindPage(pageName);

                if (pChildPage)
                    return pChildPage;
            }
        }
    }

    // process the model components
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        // if sub-model exists, not a referenced model, and contains a page set
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pModel && pModel->HasPageSet())
            {
                // recursively call the same method
                ZDProcessGraphPage* pPage = pModel->FindPage(pageName);

                if (pPage)
                    return pPage;
            }
        }
    }

    // not found
    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::PageExist(const CString& pageName)
{
    return FindPage(pageName);
}
//---------------------------------------------------------------------------
ZDProcessGraphPage* PSS_ProcessGraphModelMdl::CreateNewPage(PSS_ProcessGraphModelMdl* pModel,
                                                            const CString&            pageName,
                                                            PSS_ProcessGraphModelMdl* pInModel)
{
    m_BgFlag = TRUE;

    IProcessGraphPageSet* pSet = NULL;

    // if a target model is provided
    if (pInModel)
    {
        // if page set isn't already allocated
        if (!(pSet = pInModel->GetPageSet()))
            if (!(pSet = pInModel->AllocatePageSet()))
                return NULL;
    }
    else
    if (!(pSet = GetMainPageSet()))
        if (!(pSet = AllocateMainPageSet()))
            return NULL;

    CString name = pageName;

    if (name.IsEmpty())
        name = GetRoot()->GetValidNextPageName();

    std::unique_ptr<ZDProcessGraphPage> pNewPage(new ZDProcessGraphPage(name, pModel));
    pSet->Add(pNewPage.get());

    return pNewPage.release();
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelMdl::GetValidNextPageName()
{
    const CStringArray* pArray        = GetExistingPageNameArray();
    const int           pageNameCount = pArray->GetSize();

    if (pArray && pageNameCount > 0)
    {
        #ifdef _DEBUG
            for (int i = 0; i < pageNameCount; ++i)
            {
                TRACE(_T("Existing page:\n"));
                TRACE1(_T("%s\n"), (const char*)pArray->GetAt(i));
            }
        #endif

        CString pageStr;

        for (int i = 1; i < 10000000; ++i)
        {
            pageStr.Format(_T("Page %d"), i);

            bool found = false;

            for (int j = 0; j < pageNameCount; ++j)
                if (pArray->GetAt(j) == pageStr)
                {
                    found = true;
                    break;
                }

            // if not found, ok
            if (!found)
                return pageStr;
        }
    }
    else
        // return the first page number
        return _T("Page 1");

    // if no page available, return empty string
    return _T("");
}
//---------------------------------------------------------------------------
CStringArray* PSS_ProcessGraphModelMdl::GetExistingPageNameArray()
{
    static CStringArray internalPageArray;

    internalPageArray.RemoveAll();
    GetExistingPageNameArray(internalPageArray);

    return &internalPageArray;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::DeletePage(const CString& pageName, bool deleteModel)
{
    // process the model components
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        // if sub-model exists, not a referenced model, and contains a page set
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pModel && pModel->HasPageSet())
                // recursively call the same method
                if (pModel->DeletePage(pageName, deleteModel))
                    return true;
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            TRACE(_T("Page checked for delete : "));
            TRACE(pPage->GetPageName());
            TRACE(_T("\n"));

            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // if found the right page
            if (pPage->GetPageName() == pageName)
            {
                // delete the page model
                if (deleteModel && pPageModel)
                {
                    delete pPageModel;
                    pPage->SetModel(NULL);
                }

                delete pPage;

                // remove the page from the table
                it.Remove();

                return true;
            }

            // ignore the current model page
            if (pPageModel && pPageModel != this)
                if (pPageModel->DeletePage(pageName, deleteModel))
                    return true;
        }
    }

    // not found
    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::NotifyDeletePage(ZDProcessGraphPage* pPage)
{}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelMdl::GetOwnerPageModel(ZDProcessGraphPage* pLookForPage)
{
    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
            if (pPage && pPage == pLookForPage)
                return this;
    }

    // process the model components
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        // if sub-model exists, not a referenced model, and contains a page set
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pModel && pModel->HasPageSet())
            {
                // recursively call the same method
                PSS_ProcessGraphModelMdl* pChildModel = pModel->GetOwnerPageModel(pLookForPage);

                if (pChildModel)
                    return pChildModel;
            }
        }
    }

    // not found
    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::PropagateNewSymbolAttributes(ZBPropertyAttributes* pAttributes, int objectID)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp)
        {
            ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pComp);
            PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

            // Notify the change to elements
            if (pSymbol && pSymbol->GetObjectTypeID() == objectID)
                pSymbol->OnChangeAttributes(pAttributes);
            else
            if (pLinkSymbol && pLinkSymbol->GetObjectTypeID() == objectID)
                pLinkSymbol->OnChangeAttributes(pAttributes);

            // check if has sub-model
            if (pSymbol && !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                // call the model recursively
                if (pChildModel)
                    pChildModel->PropagateNewSymbolAttributes(pAttributes, objectID);
            }
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->PropagateNewSymbolAttributes(pAttributes, objectID);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::RefreshSymbolAttributes(bool redraw)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp)
        {
            ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pComp);
            PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

            // notify the change to elements
            if (pSymbol)
                pSymbol->RefreshAttributeTextArea(redraw);
            else
            if (pLinkSymbol)
                pLinkSymbol->RefreshAttributeTextArea(redraw);

            // check if has sub-model
            if (pSymbol && !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                // call the model recursively
                if (pChildModel)
                    pChildModel->RefreshSymbolAttributes(redraw);
            }
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->RefreshSymbolAttributes(redraw);
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::HasProperties() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::FillProperties(ZBPropertySet& props, bool numericValue, bool groupValue)
{
    // get the language property
    ZBLanguageProp* pProps = static_cast<ZBLanguageProp*>(GetProperty(ZS_BP_PROP_LANGUAGE));

    // if doesn't exist, create the property
    if (!pProps)
    {
        CreateSymbolProperties();

        // get the language prop again
        pProps = static_cast<ZBLanguageProp*>(GetProperty(ZS_BP_PROP_LANGUAGE));

        // on problem, return error
        if (!pProps)
            return false;
    }

    PSS_BasicModelProperties* pBasicProps = static_cast<PSS_BasicModelProperties*>(GetProperty(ZS_BP_PROP_MODEL_BASIC));

    if (!pBasicProps)
        return false;

    std::unique_ptr<ZBProperty> pProp;

    pProp.reset(new ZBProperty(IDS_ZS_BP_PROP_MODEL_BASIC_TITLE,
                               ZS_BP_PROP_MODEL_BASIC,
                               IDS_Z_MODEL_NAME_NAME,
                               M_Model_Name_ID,
                               IDS_Z_MODEL_NAME_DESC,
                               pBasicProps->GetModelName(),
                               ZBProperty::PT_EDIT_STRING_READONLY));
    props.Add(pProp.get());
    pProp.release();

    pProp.reset(new ZBProperty(IDS_ZS_BP_PROP_MODEL_BASIC_TITLE,
                               ZS_BP_PROP_MODEL_BASIC,
                               IDS_Z_MODEL_DESCRIPTION_NAME,
                               M_Model_Description_ID,
                               IDS_Z_MODEL_DESCRIPTION_DESC,
                               pBasicProps->GetModelDescription()));
    props.Add(pProp.get());
    pProp.release();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::SaveProperties(ZBPropertySet& props)
{
    PSS_BasicModelProperties* pBasicProps = static_cast<PSS_BasicModelProperties*>(GetProperty(ZS_BP_PROP_MODEL_BASIC));

    if (!pBasicProps)
        return false;

    ZBPropertyIterator it(&props);

    // iterate through the data list and fill the property set
    for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        // if no changes, continue
        if (!pProp->GetHasChanged())
            continue;

        if (pProp->GetCategoryID() == ZS_BP_PROP_MODEL_BASIC)
            switch (pProp->GetItemID())
            {
                case M_Model_Name_ID:        SetModelName  (pProp->GetValueString()); break;
                case M_Model_Description_ID: SetDescription(pProp->GetValueString()); break;
            }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::FillProperty(ZBProperty& prop)
{
    PSS_BasicModelProperties* pBasicProps = static_cast<PSS_BasicModelProperties*>(GetProperty(ZS_BP_PROP_MODEL_BASIC));

    if (!pBasicProps)
        return false;

    if (prop.GetCategoryID() == ZS_BP_PROP_MODEL_BASIC)
        switch (prop.GetItemID())
        {
            case M_Model_Name_ID:        prop.SetValueString(pBasicProps->GetModelName());        break;
            case M_Model_Description_ID: prop.SetValueString(pBasicProps->GetModelDescription()); break;
        }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::SaveProperty(ZBProperty& prop)
{
    PSS_BasicModelProperties* pBasicProps = static_cast<PSS_BasicModelProperties*>(GetProperty(ZS_BP_PROP_MODEL_BASIC));

    if (!pBasicProps)
        return false;

    if (prop.GetCategoryID() == ZS_BP_PROP_MODEL_BASIC)
        switch (prop.GetItemID())
        {
            case M_Model_Name_ID:        SetModelName  (prop.GetValueString()); break;
            case M_Model_Description_ID: SetDescription(prop.GetValueString()); break;
        }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::CheckPropertyValue(ZBProperty& prop, CString& value, ZBPropertySet& props)
{
    if (prop.GetCategoryID() == ZS_BP_PROP_MODEL_BASIC && prop.GetItemID() == M_Model_Name_ID)
    {
        PSS_ProcessGraphModelMdl* pRoot = GetRoot();

        // if is the root model, notify the user to rename it, because the model should be saved
        // under another name
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
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::ProcessExtendedInput(ZBProperty&    prop,
                                                    CString&       value,
                                                    ZBPropertySet& props,
                                                    bool&          refresh)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::ProcessMenuCommand(int            menuCmdID,
                                                  ZBProperty&    prop,
                                                  CString&       value,
                                                  ZBPropertySet& props,
                                                  bool&          refresh)
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::CreateSymbolProperties()
{
    PSS_BasicModelProperties basicProps;
    AddProperty(basicProps);

    ZBLanguageProp languageProps;
    AddProperty(languageProps);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::IsPropertiesReadOnly() const
{
    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::ClearPath()
{
    PSS_ObjectPath::ClearPath();

    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
            continue;

        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pComp);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pSymbol)
            pSymbol->ClearPath();
        else
        if (pLinkSymbol)
            pLinkSymbol->ClearPath();

        // if the process has a child model, process it
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel)
                pChildModel->ClearPath();
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->ClearPath();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::CalculateAbsolutePath()
{
    // if no path defined
    if (GetAbsolutePath().IsEmpty())
    {
        // set the path
        if (GetParent())
            SetAbsolutePath(GetParent()->GetAbsolutePath());

        AddMemberToPath(GetModelName());
    }

    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
            continue;

        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pComp);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pSymbol)
            pSymbol->CalculateAbsolutePath();
        else
        if (pLinkSymbol)
            pLinkSymbol->CalculateAbsolutePath();

        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            // if the process has a child model, process it
            if (pChildModel)
                pChildModel->CalculateAbsolutePath();
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->CalculateAbsolutePath();
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::SymbolNameAlreadyAllocated(const CString& symbolName)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
            continue;

        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pComp);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        // if the same reference number was found, return true
        if (pSymbol && pSymbol->GetSymbolName() == symbolName)
            return true;
        else
        if (pLinkSymbol && pLinkSymbol->GetSymbolName() == symbolName)
            return true;

        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            // if the process has a child model, process it
            if (pChildModel)
                if (pChildModel->SymbolNameAlreadyAllocated(symbolName))
                    return true;
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                if (pPageModel->SymbolNameAlreadyAllocated(symbolName))
                    return true;
        }
    }

    // no reference number found
    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::ReferenceNumberAlreadyAllocated(int refNumber)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
            continue;

        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pComp);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        // if the same reference number was found, return true
        if (pSymbol && pSymbol->GetSymbolReferenceNumber() == refNumber)
            return true;
        else
        if (pLinkSymbol && pLinkSymbol->GetSymbolReferenceNumber() == refNumber)
            return true;

        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            // if the process has a child model, process it
            if (pChildModel)
                if (pChildModel->ReferenceNumberAlreadyAllocated(refNumber))
                    return true;
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                if (pPageModel->ReferenceNumberAlreadyAllocated(refNumber))
                    return true;
        }
    }

    // no reference number found
    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::ReferenceNumberAlreadyAllocated(const CString& refNumber)
{
    return ReferenceNumberAlreadyAllocated(std::atoi(refNumber));
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelMdl::GetNextAvailableReferenceNumberStr()
{
    CString str;
    str.Format(_T("%d"), GetNextAvailableReferenceNumber());
    return str;
}
//---------------------------------------------------------------------------
int PSS_ProcessGraphModelMdl::GetNextAvailableReferenceNumber(PSS_ProcessGraphModelMdl* pRootModel)
{
    const int currentRefMax = GetNextAvailableRefNb(pRootModel);

    if (currentRefMax > m_NextAvailableRefNb)
        m_NextAvailableRefNb = currentRefMax;

    return ++m_NextAvailableRefNb;
}
//---------------------------------------------------------------------------
CStringArray* PSS_ProcessGraphModelMdl::GetExistingReferenceNumberArray()
{
    static CStringArray internalRefNumberArray;
    internalRefNumberArray.RemoveAll();
    GetExistingReferenceNumberArray(internalRefNumberArray);
    return &internalRefNumberArray;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::AcceptVisitor(PSS_BasicSymbolVisitor& visitor)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
            continue;

        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pComp);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pSymbol)
            pSymbol->AcceptVisitor(visitor);
        else
        if (pLinkSymbol)
            pLinkSymbol->AcceptVisitor(visitor);

        // if sub-model is defined, visit it
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel)
                pChildModel->AcceptVisitor(visitor);
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->AcceptVisitor(visitor);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::GetStartSymbols(CODNodeArray& nodes, bool deep)
{
    // don't know if start symbols exists, the class that will implement this method knows that
    return 0;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::GenerateModelWorkflow(PSS_Log* pLog, PSS_ProcessGraphModelDoc* pDoc)
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::CheckModelWorkflow(PSS_Log* pLog, BOOL modelIsClean)
{
    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetDefaultWkfProperty(bool redefineOnExisting)
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::DeleteAllActivitiesLinkedToWorkflow()
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::RecalculateParent()
{
    CalculateAbsolutePath();

    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            // if the process contains a child model, assign it
            if (pChildModel)
            {
                pChildModel->SetParent(this);
                pChildModel->RecalculateParent();
            }
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
            {
                pPageModel->SetParent(this);
                pPageModel->RecalculateParent();
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::RecalculateChildModel()
{
    PSS_ProcessGraphModelMdl* pRootModel     = GetRoot();
    CODComponentSet*          pSet           = GetComponents();
    const int                 componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        if (pSymbol)
        {
            if (pSymbol->IsChildModelRef() &&
               !pSymbol->GetChildModel() &&
               !pSymbol->GetChildModelPathName().IsEmpty())
                pSymbol->SetChildModel(pRootModel->FindModelFromPath(pSymbol->GetChildModelPathName(), true));

            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            // recalculate its model
            if (pChildModel && !pSymbol->IsChildModelRef())
                pChildModel->RecalculateChildModel();
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->RecalculateChildModel();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::RecalculateReference()
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pSet->GetAt(i));
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSet->GetAt(i));

        // check if the symbol is a reference
        if (pSymbol && pSymbol->IsReferenced())
        {
            PSS_ProcessGraphModelMdl* pRoot = GetRoot();
            ASSERT(pRoot);

            CODComponentSet* pSet = pRoot->FindSymbolByRefNumber(std::atoi(pSymbol->GetReferenceName()), true);

            if (pSet && pSet->GetSize() > 0)
            {
                ZBSymbol* pSetSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(0));

                if (pSetSymbol)
                    pSymbol->AssignReferenceSymbol(pSetSymbol);
            }
        }
        else
        if (pLinkSymbol && pLinkSymbol->IsReferenced())
        {
            PSS_ProcessGraphModelMdl* pRoot = GetRoot();
            ASSERT(pRoot);

            CODComponentSet* pSet = pRoot->FindSymbolByRefNumber(std::atoi(pLinkSymbol->GetReferenceName()), true);

            if (pSet && pSet->GetSize() > 0)
            {
                PSS_LinkSymbol* pSetSymbol = dynamic_cast<PSS_LinkSymbol*>(pSet->GetAt(0));

                if (pSetSymbol)
                    pLinkSymbol->AssignReferenceSymbol(pSetSymbol);
            }
        }

        // recalculate the reference on the child model
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel)
                pChildModel->RecalculateReference();
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->RecalculateReference();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::RecalculateSymbolReferences()
{}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelMdl::GetSymbolModel(ZBSymbol* pSymbolToFind)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        if (!pSymbol)
            continue;

        // if the symbol was found, return its model
        if (pSymbol == pSymbolToFind)
            return this;

        // find in sub-model, if exists
        if (!pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel)
            {
                PSS_ProcessGraphModelMdl* pMdl = pChildModel->GetSymbolModel(pSymbolToFind);

                if (pMdl)
                    return pMdl;
            }
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the same model
            if (pPageModel && pPageModel != this)
            {
                PSS_ProcessGraphModelMdl* pMdl = pPageModel->GetSymbolModel(pSymbolToFind);

                if (pMdl)
                    return pMdl;
            }
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelMdl::GetLinkSymbolModel(PSS_LinkSymbol* pSymbolToFind)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
            continue;

        // if the symbol was found, return its model
        if (pComp == pSymbolToFind && ISA(pComp, PSS_LinkSymbol))
            return this;

        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        // find in sub-model, if exists
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel)
            {
                PSS_ProcessGraphModelMdl* pMdl = pChildModel->GetLinkSymbolModel(pSymbolToFind);

                if (pMdl)
                    return pMdl;
            }
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the same model
            if (pPageModel && pPageModel != this)
            {
                PSS_ProcessGraphModelMdl* pMdl = pPageModel->GetLinkSymbolModel(pSymbolToFind);

                if (pMdl)
                    return pMdl;
            }
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelMdl::GetRoot()
{
    if (m_pParent)
        return m_pParent->GetRoot();

    return this;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetParent(PSS_ProcessGraphModelMdl* pModel)
{
    m_pParent = pModel;

    // get the new parent name
    if (m_pParent)
        m_ParentName = m_pParent->GetModelName();
    else
        m_ParentName.Empty();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetBackgroundComponent(CODComponent& bgComp, bool toAll, bool stretchToModel)
{
    if (!toAll)
        SetBackgroundComponentToModel(bgComp, stretchToModel);
    else
    {
        PSS_ProcessGraphModelMdl* pRoot = GetRoot();

        // do apply to all components, call the function from the root if not already on it
        if (pRoot && this != pRoot)
            pRoot->SetBackgroundComponentToAll(bgComp, stretchToModel);
        else
            SetBackgroundComponentToAll(bgComp, stretchToModel);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::ClearBackgroundComponent(bool toAll)
{
    if (!toAll)
        ClearBackgroundComponentToModel();
    else
    {
        PSS_ProcessGraphModelMdl* pRoot = GetRoot();

        // do apply to all components, call the function from the root if not already on it
        if (pRoot && this != pRoot)
            pRoot->ClearBackgroundComponentToAll();
        else
            ClearBackgroundComponentToAll();
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::RedrawComponent(CODComponent& comp)
{
    UpdateComponent(&comp, OD_UPDATE_ALL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::RedrawComponentSet(CODComponentSet& compSet)
{
    UpdateComponents(&compSet, OD_UPDATE_ALL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SelectAllComponents()
{
    PSS_ProcessGraphModelController* pController = dynamic_cast<PSS_ProcessGraphModelController*>(GetController());

    if (pController)
        pController->SelectAllComponents();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::UnselectAllComponents()
{
    PSS_ProcessGraphModelController* pController = dynamic_cast<PSS_ProcessGraphModelController*>(GetController());

    if (pController)
        pController->UnselectAllComponents();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SelectComponent(CODComponent& comp)
{
    PSS_ProcessGraphModelController* pController = dynamic_cast<PSS_ProcessGraphModelController*>(GetController());

    if (pController)
        pController->SelectComponent(comp);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SelectComponentSet(CODComponentSet& compSet)
{
    PSS_ProcessGraphModelController* pController = dynamic_cast<PSS_ProcessGraphModelController*>(GetController());

    if (pController)
        pController->SelectComponentSet(compSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::UnselectComponent(CODComponent& comp)
{
    PSS_ProcessGraphModelController* pController = dynamic_cast<PSS_ProcessGraphModelController*>(GetController());

    if (pController)
        pController->UnselectComponent(comp);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::UnselectComponentSet(CODComponentSet& compSet)
{
    PSS_ProcessGraphModelController* pController = dynamic_cast<PSS_ProcessGraphModelController*>(GetController());

    if (pController)
        pController->UnselectComponentSet(compSet);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::IsComponentSelected(CODComponent& comp)
{
    PSS_ProcessGraphModelController* pController = dynamic_cast<PSS_ProcessGraphModelController*>(GetController());

    return (pController ? pController->IsComponentSelected(comp) : false);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::DeleteComponent(CODComponent* pComp)
{
    PSS_ProcessGraphModelController* pController = dynamic_cast<PSS_ProcessGraphModelController*>(GetController());

    if (pController)
        pController->DeleteComponent(pComp);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::DeleteComponents(CODComponentSet* pCompSet)
{
    PSS_ProcessGraphModelController* pController = dynamic_cast<PSS_ProcessGraphModelController*>(GetController());

    if (pController)
        pController->DeleteComponents(pCompSet);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::SymbolExistInModel(CODComponent* pCompToFind, bool inSubModel)
{
    CODComponentSet* pSet = FindSymbol(pCompToFind, inSubModel);
    return (pSet && pSet->GetSize() > 0);
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ProcessGraphModelMdl::FindSymbol(CODComponent* pCompToFind, bool inSubModel)
{
    m_FindSet.RemoveAll();
    FindSymbolPvt(pCompToFind, inSubModel);

    return &m_FindSet;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ProcessGraphModelMdl::FindSymbol(CODModel* pModel, bool inSubModel, bool onlyLocal)
{
    m_FindSet.RemoveAll();
    FindSymbolPvt(pModel, inSubModel, onlyLocal);

    return &m_FindSet;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ProcessGraphModelMdl::FindSymbol(const CString& name,
                                                      const CString& path,
                                                      bool           inSubModel,
                                                      bool           caseSensitive,
                                                      bool           onlyLocal)
{
    m_FindSet.RemoveAll();
    FindSymbolPvt(name, path, inSubModel, caseSensitive, onlyLocal);
    return &m_FindSet;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ProcessGraphModelMdl::FindSymbolFromPath(const CString& path,
                                                              bool           inSubModel,
                                                              bool           caseSensitive,
                                                              bool           onlyLocal)
{
    m_FindSet.RemoveAll();
    FindSymbolFromPathPvt(path, inSubModel, caseSensitive, onlyLocal);
    return &m_FindSet;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ProcessGraphModelMdl::FindSymbolByRefNumber(int refNumber, bool inSubModel)
{
    m_FindSet.RemoveAll();
    FindSymbolByRefNumberPvt(refNumber, inSubModel);
    return &m_FindSet;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ProcessGraphModelMdl::FindSymbolPartialName(const CString& name,
                                                                 bool           inSubModel,
                                                                 bool           caseSensitive,
                                                                 bool           onlyLocal)
{
    m_FindSet.RemoveAll();
    FindSymbolPartialNamePvt(name, inSubModel, caseSensitive, onlyLocal);
    return &m_FindSet;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::Find(const CString&        argument,
                                           PSS_Log*              pLog,
                                           ZBPropertyAttributes* pPropAttributes,
                                           bool                  inSubModel,
                                           bool                  caseSensitive,
                                           bool                  partialSearch)
{
    m_FindCounter = 0;

    // if log
    if (pLog)
    {
        pLog->ClearLog();
        CString message;
        message.Format(IDS_AL_START_FINDMATCH, argument, GetModelName());
        ZBGenericSymbolErrorLine error(message);
        pLog->AddLine(error);
    }

    FindPvt(argument, pLog, pPropAttributes, inSubModel, caseSensitive, partialSearch);

    // If log
    if (pLog)
    {
        CString message;
        message.Format(IDS_AL_STOP_FINDMATCH, m_FindCounter);
        ZBGenericSymbolErrorLine error(message);
        pLog->AddLine(error);
    }

    return m_FindCounter;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelMdl::FindModel(const CString&            name,
                                                              bool                      caseSensitive,
                                                              PSS_ProcessGraphModelMdl* pRootModel)
{
    // empty name?
    if (name.IsEmpty())
        return NULL;

    // if the root model is empty, the the search should be performed on the whole document
    if (!pRootModel)
        // get the document model controller instead
        pRootModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRoot());

    if (pRootModel)
    {
        // get the page set from the model controller
        IProcessGraphPageSet* pSet = pRootModel->GetPageSet();

        if (pSet)
        {
            IProcessGraphPageIterator it(pSet);

            // iterate through the children pages contained in the model controller
            for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
            {
                // get the current page model controller
                PSS_ProcessGraphModelMdl* pCurModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pPage->GetModel());

                if (pCurModel)
                {
                    // get the symbol set from the model controller
                    CODComponentSet* pCompSet = pCurModel->GetComponents();

                    if (pCompSet)
                    {
                        const int componentSize = pCompSet->GetSize();

                        // iterate through the symbols contained in the model contoller
                        for (int i = 0; i < componentSize; ++i)
                        {
                            ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pCompSet->GetAt(i));

                            // check if the component is valid and if it's a kind of symbol
                            if (pSymbol)
                                // check if the symbol contains a model controller
                                if (pSymbol->GetChildModel() && !pSymbol->IsChildModelRef())
                                {
                                    // get the model controller from the symbol
                                    PSS_ProcessGraphModelMdl* pChildModel =
                                            dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                                    // check if the symbol was found
                                    if ((caseSensitive && pSymbol->GetSymbolName() == name) ||
                                       (!caseSensitive && !name.CompareNoCase(pSymbol->GetSymbolName())))
                                        return pChildModel;

                                    // recursive call the FindModel() function, until all the child model pages
                                    // were processed, or the model was found
                                    PSS_ProcessGraphModelMdl* pModel = FindModel(name, caseSensitive, pChildModel);

                                    // if the model was not found, it may be contained in another set,
                                    // so continue to search
                                    if (pModel)
                                        return pModel;
                                }
                        }
                    }
                }
            }
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelMdl::FindModelFromPath(const CString& path, bool caseSensitive)
{
    return FindModelFromPathPvt(path, caseSensitive);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::SubModelExist(CODModel* pModel)
{
    if (pModel == this)
        return true;

    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        // search in sub-model, if exists
        if (pSymbol &&  !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel)
                return pChildModel->SubModelExist(pModel);
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::SubModelExist(const CString& modelName, bool caseSensitive)
{
    const CString curModelName = GetModelName();

    // is the same name?
    if ((caseSensitive && modelName == curModelName) || (!caseSensitive && !modelName.CompareNoCase(curModelName)))
        return true;

    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        // Find in sub-model if there is
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel)
                return pChildModel->SubModelExist(modelName, caseSensitive);
        }
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::DrawMetaFile(CDC* pDC, const CRect& rect)
{
    if (m_hMetaFile)
        pDC->PlayMetaFile(m_hMetaFile, &rect);
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelMdl::RecalculateAllLinks()
{
    return FALSE;
}
//---------------------------------------------------------------------------
const CString PSS_ProcessGraphModelMdl::GetModelName() const
{
    PSS_BasicModelProperties* pBasicProps = static_cast<PSS_BasicModelProperties*>(GetProperty(ZS_BP_PROP_MODEL_BASIC));

    if (!pBasicProps)
        return _T("");

    return pBasicProps->GetModelName();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetModelName(const CString& value)
{
    PSS_BasicModelProperties  basicProps;
    PSS_BasicModelProperties* pCurBasicProps = static_cast<PSS_BasicModelProperties*>(GetProperty(ZS_BP_PROP_MODEL_BASIC));

    if (pCurBasicProps != NULL)
    {
        basicProps = *pCurBasicProps;
        basicProps.SetModelName(value);
        SetProperty(&basicProps);

        CWnd* pMainWnd = AfxGetMainWnd();
        ASSERT(pMainWnd);

        // build the message
        ZBDocObserverMsg docMsg(ZBDocObserverMsg::ChangedElement, NULL, this);
        pMainWnd->SendMessageToDescendants(UM_ELEMENTMODIFIEDDOCUMENTMODEL, 0, (LPARAM)&docMsg);
    }

    // recalculate all references
    RecalculateParent();
    RecalculateAbsolutePath();
}
//---------------------------------------------------------------------------
const CString PSS_ProcessGraphModelMdl::GetDescription() const
{
    PSS_BasicModelProperties* pBasicProps = static_cast<PSS_BasicModelProperties*>(GetProperty(ZS_BP_PROP_MODEL_BASIC));

    if (!pBasicProps)
        return _T("");

    return pBasicProps->GetModelDescription();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetDescription(const CString& value)
{
    PSS_BasicModelProperties  basicProps;
    PSS_BasicModelProperties* pCurBasicProps = static_cast<PSS_BasicModelProperties*>(GetProperty(ZS_BP_PROP_MODEL_BASIC));

    if (pCurBasicProps)
    {
        basicProps = *pCurBasicProps;
        basicProps.SetModelDescription(value);
        SetProperty(&basicProps);
    }
}
//---------------------------------------------------------------------------
CString PSS_ProcessGraphModelMdl::GetBkGndFileName() const
{
    return m_BgFileName;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetBkGndFileName(const CString& fileName)
{
    m_BgFileName = fileName;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelMdl::IsLogo()
{
    return m_IsLogo;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetIsLogo(BOOL isLogo)
{
    m_IsLogo = isLogo;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelMdl::IsBkGndMustBeRestored() const
{
    return m_BgFlag;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::ResetBkGndMustBeRestored()
{
    m_BgFlag = FALSE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::Serialize(CArchive& ar)
{
    PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

    if (pDocument->GetDocumentStamp().GetInternalVersion() >= 22)
    {
        if (ar.IsStoring())
        {
            ar << m_BgFileName;

            if (pDocument->GetDocumentStamp().GetInternalVersion() >= 23)
                ar << int(m_IsLogo);

            // clear the background
            ClearBackgroundComponent(true);
        }
        else
        {
            ar >> m_BgFileName;

            if (pDocument->GetDocumentStamp().GetInternalVersion() >= 23)
            {
                int value;
                ar >> value;
                m_IsLogo = BOOL(value);
            }
        }
    }

    CODModel::Serialize(ar);

    // set the background reset flag
    m_BgFlag = TRUE;

    if (ar.IsStoring())
    {
        ar << m_ParentName;
        ar << m_ObjectPath;
        ar << DWORD(m_Notation);

        if (pDocument->GetDocumentStamp().GetInternalVersion() >= 25)
            ar << m_NextAvailableRefNb;
    }
    else
    {
        ar >> m_ParentName;
        ar >> m_ObjectPath;

        DWORD dwValue;
        ar >> dwValue;
        m_Notation = EModelNotation(dwValue);

        if (pDocument->GetDocumentStamp().GetInternalVersion() >= 25)
            ar >> m_NextAvailableRefNb;
    }

    // the page set
    SerializePageSet(ar);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::PostRead(CArchive& ar)
{
    // recalculate the parent model
    RecalculateParent();

    // recalculate the children models
    RecalculateChildModel();

    // recalculate the symbol reference
    RecalculateReference();

    // recalculate all the symbol references
    RecalculateSymbolReferences();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::PostWrite(CArchive& ar)
{}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessGraphModelMdl::AssertValid() const
    {
        CODModel::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessGraphModelMdl::Dump(CDumpContext& dc) const
    {
        CODModel::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::OnPostOpenDocument(long documentVersion)
{}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::OnPrePropertyChanged(const CString& newValue, ZBProperty& prop, ZBPropertySet& props)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::OnPostPropertyChanged(ZBProperty& prop, ZBPropertySet& props, bool& refresh)
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::OnDropInternalPropertyItem(ZBProperty&    srcProp,
                                                          ZBProperty&    dstProp,
                                                          bool           top2Down,
                                                          ZBPropertySet& props)
{
    return true;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::OnSymbolNameChanged(CODComponent& comp, const CString& oldName)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pSet->GetAt(i));
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSet->GetAt(i));

        if (pSymbol)
            pSymbol->OnSymbolNameChanged(comp, oldName);
        else
        if (pLinkSymbol)
            pLinkSymbol->OnSymbolNameChanged(comp, oldName);

        // find in sub-model, if exists
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel)
                pChildModel->OnSymbolNameChanged(comp, oldName);
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                // call the methods for all pages
                pPageModel->OnSymbolNameChanged(comp, oldName);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::OnPageNameChanged(ZDProcessGraphPage* pPage, const CString& oldName)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pSet->GetAt(i));
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSet->GetAt(i));

        if (pSymbol)
            pSymbol->OnPageNameChanged(pPage, oldName);
        else
        if (pLinkSymbol)
            pLinkSymbol->OnPageNameChanged(pPage, oldName);

        // find in sub-model, if exists
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel)
                pChildModel->OnPageNameChanged(pPage, oldName);
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pGraphPage = it.GetFirst(); pGraphPage; pGraphPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                // call the methods for all pages
                pPageModel->OnPageNameChanged(pPage, oldName);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::OnUserEntityChanged(ZBUserEntity* pUserEntity, const CString& oldName)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pSet->GetAt(i));
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSet->GetAt(i));

        if (pSymbol)
            pSymbol->OnUserEntityChanged(pUserEntity, oldName);
        else
        if (pLinkSymbol)
            pLinkSymbol->OnUserEntityChanged(pUserEntity, oldName);

        // notify the sub-model, if exists
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel)
                pChildModel->OnUserEntityChanged(pUserEntity, oldName);
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                // call the method for all pages
                pPageModel->OnUserEntityChanged(pUserEntity, oldName);
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::DeleteAllPages()
{
    // process the model components
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        // if the sub model exists, not a referenced model, and contains a page set
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            // delete all pages in sub-model
            if (pChildModel && pChildModel->HasPageSet())
                pChildModel->DeleteAllPages();
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->DeleteAllPages();
        }
    }

    // once all elements from the model have been processed, delete the model page set
    DeleteAllPageInSet();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdl::DeleteAllPageInSet()
{
    if (!m_pPageSet)
        return true;

    IProcessGraphPageIterator it(m_pPageSet);

    for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        delete pPage;

    // remove all elements
    m_pPageSet->RemoveAll();
    return true;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SerializePageSet(CArchive& ar)
{
    if (ar.IsStoring())
    {
        if (!m_pPageSet)
            ar << int(0);
        else
        {
            CString                   emptyString;
            PSS_ProcessGraphModelMdl* pRootModel = GetRoot();
            PSS_ProcessGraphModelMdl* pNULLModel = NULL;
            IProcessGraphPageIterator it(m_pPageSet);

            // serialize the item count
            ar << m_pPageSet->GetSize();

            for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
            {
                ar << pPage->GetPageName();

                PSS_ProcessGraphModelMdl* pModel = pPage->GetModel();

                // do not serialize the root model, already serialized by the document
                if (pModel)
                {
                    ar << pModel->GetAbsolutePath();

                    if (pModel != this)
                        ar << pModel;
                    else
                        ar << pNULLModel;
                }
                else
                    ar << emptyString;
            }
        }
    }
    else
    {
        DeleteAllPageInSet();

        int count;
        ar >> count;

        if (count > 0)
        {
            PSS_ProcessGraphModelMdl* pRootModel  = GetRoot();
            PSS_ProcessGraphModelMdl* pModelFound = NULL;

            if (pRootModel)
            {
                if (!m_pPageSet)
                    AllocatePageSet();

                CString pageName;
                CString modelName;

                for (int i = 0; i < count; ++i)
                {
                    ar >> pageName;
                    ar >> modelName;

                    if (!modelName.IsEmpty())
                    {
                        ar >> pModelFound;

                        if (!pModelFound)
                            pModelFound = pRootModel->FindModelFromPath(modelName, true);

                        if (pModelFound)
                        {
                            std::unique_ptr<ZDProcessGraphPage> pPage(new ZDProcessGraphPage(pageName, pModelFound));
                            m_pPageSet->Add(pPage.get());
                            pPage.release();
                        }
                    }
                }
            }
        }
        else
            m_pPageSet = NULL;
    }
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::GetEnteringSymbols(ZBSymbol* pComp, CODNodeArray& nodes)
{
    if (pComp)
        return pComp->GetEnteringSymbols(nodes);

    return 0;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::GetFollowingSymbols(ZBSymbol* pComp, CODNodeArray& nodes)
{
    if (pComp)
        return pComp->GetFollowingSymbols(nodes);

    return 0;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::GetEdgesEntering(ZBSymbol* pComp, CODEdgeArray& edges)
{
    if (pComp)
        return pComp->GetEdgesEntering(edges);

    return 0;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::GetEdgesLeaving(ZBSymbol* pComp, CODEdgeArray& edges)
{
    if (pComp)
        return pComp->GetEdgesLeaving(edges);

    return 0;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::GetEnteringSymbolsISA(ZBSymbol*            pComp,
                                                            CODNodeArray&        nodes,
                                                            const CRuntimeClass* pClass)
{
    if (!pComp)
        return 0;

    pComp->GetEnteringSymbols(nodes);

    return KeepOnlySymbolsISA(nodes, pClass);
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::GetFollowingSymbolsISA(ZBSymbol*            pComp,
                                                             CODNodeArray&        nodes,
                                                             const CRuntimeClass* pClass)
{
    if (!pComp)
        return 0;

    pComp->GetFollowingSymbols(nodes);

    return KeepOnlySymbolsISA(nodes, pClass);
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::GetEdgesEnteringISA(ZBSymbol*            pComp,
                                                          CODEdgeArray&        edges,
                                                          const CRuntimeClass* pClass)
{
    if (!pComp)
        return 0;

    pComp->GetEdgesEntering(edges);

    return KeepOnlyLinksISA(edges, pClass);
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::GetEdgesLeavingISA(ZBSymbol*            pComp,
                                                         CODEdgeArray&        edges,
                                                         const CRuntimeClass* pClass)
{
    if (!pComp)
        return 0;

    pComp->GetEdgesLeaving(edges);

    return KeepOnlyLinksISA(edges, pClass);
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::KeepOnlySymbolsISA(CODNodeArray& nodes, const CRuntimeClass* pClass)
{
    return ZUODSymbolManipulator::KeepOnlySymbolsISA(nodes, pClass);
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::KeepOnlyLinksISA(CODEdgeArray& edges, const CRuntimeClass* pClass)
{
    return ZUODSymbolManipulator::KeepOnlyLinksISA(edges, pClass);
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::CountActivities(ZBSymbol* pSymbol, const CODNodeArray& nodes)
{
    std::size_t counter   = 0;
    const int   nodeCount = nodes.GetSize();

    for (int i = 0; i < nodeCount; ++i)
    {
        IODNode*            pNode = nodes.GetAt(i);
        CODSymbolComponent* pComp = static_cast<CODSymbolComponent*>(pNode);

        if (!pComp)
            continue;

        if (pComp == pSymbol)
            ++counter;
    }

    return counter;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::CountLinks(CODLinkComponent* pLink, const CODEdgeArray& edges)
{
    std::size_t counter   = 0;
    const int   edgeCount = edges.GetSize();

    for (int i = 0; i < edgeCount; ++i)
    {
        IODEdge*          pEdge = edges.GetAt(i);
        CODLinkComponent* pComp = static_cast<CODLinkComponent*>(pEdge);

        if (!pComp)
            continue;

        if (pComp == pLink)
            ++counter;
    }

    return counter;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::GetSymbolsISA(CODNodeArray&        nodes,
                                                    const CRuntimeClass* pClass,
                                                    bool                 deep)
{
    CODComponentSet* pSet = GetComponents();

    if (!pSet)
        return 0;

    const int componentCount = pSet->GetSize();

    // iterate through all elements
    for (int i = 0; i < componentCount; ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (pComp && pComp->IsKindOf(pClass))
            nodes.Add(guid_cast<IODNode*>(pComp));

        // if need to go deeper
        if (deep)
        {
            ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pComp);

            if (pSymbol && !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                // iterate through its children models
                if (pChildModel)
                    pChildModel->GetSymbolsISA(nodes, pClass, deep);
            }
        }
    }

    // if need to go through pages also
    if (deep && m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages, if exists
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // do not process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->GetSymbolsISA(nodes, pClass, deep);
        }
    }

    return nodes.GetSize();
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ProcessGraphModelMdl::FindSymbolPvt(CODComponent* pCompToFind, bool inSubModel)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // if is a symbol and the contains the same name
        if (pComp == pCompToFind)
            m_FindSet.Add(pComp);

        if (inSubModel)
        {
            ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pComp);

            // search in sub-model, if exists
            if (pSymbol && !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                if (pChildModel)
                    pChildModel->FindSymbolPvt(pCompToFind, inSubModel);
            }
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->FindSymbolPvt(pCompToFind, inSubModel);
        }
    }

    return &m_FindSet;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ProcessGraphModelMdl::FindSymbolPvt(CODModel* pModel, bool inSubModel, bool onlyLocal)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        // check on symbols only, because there are no child model on deliverables
        if (pSymbol)
        {
            CODModel* pChildModel = pSymbol->GetChildModel();

            if ((!onlyLocal || pSymbol->IsLocal()) && pChildModel && pChildModel == pModel)
                m_FindSet.Add(pSymbol);
        }

        if (inSubModel)
        {
            // search in sub-model, if exists
            if (pSymbol && !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                if (pChildModel)
                    pChildModel->FindSymbolPvt(pModel, inSubModel, onlyLocal);
            }
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->FindSymbolPvt(pModel, inSubModel, onlyLocal);
        }
    }

    return &m_FindSet;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ProcessGraphModelMdl::FindSymbolPvt(const CString& name,
                                                         const CString& path,
                                                         bool           inSubModel,
                                                         bool           caseSensitive,
                                                         bool           onlyLocal)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pSet->GetAt(i));
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSet->GetAt(i));

        // if is a symbol or a link symbol
        if (pSymbol)
        {
            // if the symbol names match
            if ((caseSensitive && pSymbol->GetSymbolName() == name) || 
               (!caseSensitive && !name.CompareNoCase(pSymbol->GetSymbolName())))
                // if no path required or the path is equal, and if only local and is local, add the element to the set
                if ((path.IsEmpty() || (!path.IsEmpty() && pSymbol->GetAbsolutePath() == path)) &&
                    (!onlyLocal     || pSymbol->IsLocal()))
                    m_FindSet.Add(pSymbol);
        }
        else
        if (pLinkSymbol)
            // if the symbol names match
            if ((caseSensitive && pLinkSymbol->GetSymbolName() == name) ||
               (!caseSensitive && !name.CompareNoCase(pLinkSymbol->GetSymbolName())))
                // if no path required or the path is equal, and if only local and is local, add the element to the set
                if ((path.IsEmpty() || (!path.IsEmpty() && pLinkSymbol->GetAbsolutePath() == path)) &&
                    (!onlyLocal     || pLinkSymbol->IsLocal()))
                    m_FindSet.Add(pLinkSymbol);

        // find in sub-model, if exists
        if (inSubModel)
            if (pSymbol && !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                if (pChildModel)
                    pChildModel->FindSymbolPvt(name, path, inSubModel, caseSensitive, onlyLocal);
            }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->FindSymbolPvt(name, path, inSubModel, caseSensitive, onlyLocal);
        }
    }

    return &m_FindSet;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ProcessGraphModelMdl::FindSymbolFromPathPvt(const CString& path,
                                                                 bool           inSubModel,
                                                                 bool           caseSensitive,
                                                                 bool           onlyLocal)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pSet->GetAt(i));
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSet->GetAt(i));

        // if is a symbol or a link symbol
        if (pSymbol)
        {
            // if the symbol paths match
            if (((caseSensitive && pSymbol->GetAbsolutePath() == path)               ||
                (!caseSensitive && !path.CompareNoCase(pSymbol->GetAbsolutePath()))) &&
                (!onlyLocal     || pSymbol->IsLocal()))
                m_FindSet.Add(pSymbol);
        }
        else
        if (pLinkSymbol)
        {
            // if the symbol paths match
            if (((caseSensitive && pLinkSymbol->GetAbsolutePath() == path) ||
                (!caseSensitive && !path.CompareNoCase(pLinkSymbol->GetAbsolutePath()))) &&
                (!onlyLocal     || pLinkSymbol->IsLocal()))
                m_FindSet.Add(pLinkSymbol);
        }

        if (inSubModel)
            // search in sub-model, if exists
            if (pSymbol && !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                if (pChildModel)
                    pChildModel->FindSymbolFromPathPvt(path, inSubModel, caseSensitive, onlyLocal);
            }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->FindSymbolFromPathPvt(path, inSubModel, caseSensitive, onlyLocal);
        }
    }

    return &m_FindSet;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ProcessGraphModelMdl::FindSymbolByRefNumberPvt(int refNumber, bool inSubModel)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pSet->GetAt(i));
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSet->GetAt(i));

        // if is a symbol or a link symbol
        if (pSymbol)
        {
            // if the symbol reference number match
            if (pSymbol->GetSymbolReferenceNumber() == refNumber)
                m_FindSet.Add(pSymbol);
        }
        else
        if (pLinkSymbol)
            // if the symbol reference number match
            if (pLinkSymbol->GetSymbolReferenceNumber() == refNumber)
                m_FindSet.Add(pLinkSymbol);

        if (inSubModel)
            // search in sub-model, if exists
            if (pSymbol && !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                if (pChildModel)
                    pChildModel->FindSymbolByRefNumberPvt(refNumber, inSubModel);
            }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->FindSymbolByRefNumberPvt(refNumber, inSubModel);
        }
    }

    return &m_FindSet;
}
//---------------------------------------------------------------------------
CODComponentSet* PSS_ProcessGraphModelMdl::FindSymbolPartialNamePvt(const CString& name,
                                                                    bool           inSubModel,
                                                                    bool           caseSensitive,
                                                                    bool           onlyLocal)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pSet->GetAt(i));
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSet->GetAt(i));

        // if is a symbol or a link symbol
        if (pSymbol)
        {
            // if no path required or the path is equal, and if only local and is local,
            // add the element to the set
            if (!onlyLocal || pSymbol->IsLocal())
                // do search case sensitive names?
                if (!caseSensitive)
                {
                    // transform the names to lower case
                    CString symName = pSymbol->GetSymbolName();
                    symName.MakeLower();

                    CString nameToFind = name;
                    nameToFind.MakeLower();

                    if (symName.Find(nameToFind) != -1)
                        m_FindSet.Add(pSymbol);
                }
                else
                if (pSymbol->GetSymbolName().Find(name) != -1)
                    m_FindSet.Add(pSymbol);
        }
        else
        if (pLinkSymbol)
            // if no path required or the path is equal, and if only local and is local,
            // add the element to the set
            if (!onlyLocal || pLinkSymbol->IsLocal())
                // do search case sensitive names?
                if (!caseSensitive)
                {
                    // transform the names to lower case
                    CString symName = pLinkSymbol->GetSymbolName();
                    symName.MakeLower();

                    CString nameToFind = name;
                    nameToFind.MakeLower();

                    if (symName.Find(nameToFind) != -1)
                        m_FindSet.Add(pLinkSymbol);
                }
                else
                if (pLinkSymbol->GetSymbolName().Find(name) != -1)
                    m_FindSet.Add(pLinkSymbol);

        if (inSubModel)
            // search in sub-model, if exists
            if (pSymbol && !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                if (pChildModel)
                    pChildModel->FindSymbolPartialNamePvt(name, inSubModel, caseSensitive, onlyLocal);
            }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->FindSymbolPartialNamePvt(name, inSubModel, caseSensitive, onlyLocal);
        }
    }

    return &m_FindSet;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::FindPvt(const CString&        argument,
                                       PSS_Log*              pLog,
                                       ZBPropertyAttributes* pPropAttributes,
                                       bool                  inSubModel,
                                       bool                  caseSensitive,
                                       bool                  partialSearch)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pSet->GetAt(i));
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSet->GetAt(i));

        // if is a symbol or a link symbol
        if (pSymbol)
        {
            // if the symbol matches with the search arguments
            if (pSymbol->Match(argument, pPropAttributes, caseSensitive, partialSearch))
            {
                // add to the log
                if (pLog)
                {
                    ZBSearchSymbolLogLine line(pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath());
                    pLog->AddLine(line);
                }

                ++m_FindCounter;
            }
        }
        else
        if (pLinkSymbol)
        {
            // if the symbol matches with the search arguments
            if (pLinkSymbol->Match(argument, pPropAttributes, caseSensitive, partialSearch))
            {
                // add to the log
                if (pLog)
                {
                    ZBSearchSymbolLogLine line(pLinkSymbol->GetSymbolName(), pLinkSymbol->GetAbsolutePath());
                    pLog->AddLine(line);
                }

                ++m_FindCounter;
            }
        }

        if (inSubModel)
            // search in sub-model, if exists
            if (pSymbol &&  !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                if (pChildModel)
                    pChildModel->FindPvt(argument, pLog, pPropAttributes, inSubModel, caseSensitive, partialSearch);
            }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->FindPvt(argument, pLog, pPropAttributes, inSubModel, caseSensitive, partialSearch);
        }
    }
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelMdl::FindModelFromPathPvt(const CString& path, bool caseSensitive)
{
    if (((caseSensitive && GetAbsolutePath() == path) || (!caseSensitive && !path.CompareNoCase(GetAbsolutePath()))))
        return this;

    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        // find in sub-model, if exists
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel)
            {
                PSS_ProcessGraphModelMdl* pModel = pChildModel->FindModelFromPathPvt(path, caseSensitive);

                if (pModel)
                    return pModel;
            }
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the page model owned by itself
            if (pPageModel && pPageModel != this)
            {
                PSS_ProcessGraphModelMdl* pModel = pPageModel->FindModelFromPathPvt(path, caseSensitive);

                if (pModel)
                    return pModel;
            }
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetBackgroundComponentToModel(CODComponent& bgComp, bool stretchToModel)
{
    CODComponent* pBgComp = bgComp.Dup();

    if (!pBgComp)
        return;

    if (stretchToModel)
    {
        // get the diagram bounding rect
        const CRect rect = GetBounds();

        // stretch the image   
        pBgComp->MoveTo(rect);
    }

    SetBkgndComponent(pBgComp);
    SetModifiedFlag(FALSE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::SetBackgroundComponentToAll(CODComponent& bgComp, bool stretchToModel)
{
    // set the model background
    SetBackgroundComponentToModel(bgComp, stretchToModel);

    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            // call the model recursively
            if (pChildModel)
                pChildModel->SetBackgroundComponentToAll(bgComp, stretchToModel);
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->SetBackgroundComponentToAll(bgComp, stretchToModel);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::ClearBackgroundComponentToModel()
{
    CODComponent* pBgComp = GetBkgndComponent();

    if (pBgComp)
        SetBkgndComponent(NULL);

    SetModifiedFlag(FALSE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::ClearBackgroundComponentToAll()
{
    // clear the previous background
    ClearBackgroundComponentToModel();

    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            // call the model recursively
            if (pChildModel)
                pChildModel->ClearBackgroundComponentToAll();
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->ClearBackgroundComponentToAll();
        }
    }
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdl::AddSymbolInParsedArray(ZBSymbol* pComp)
{
    IComponentRef* pRef = FindSymbolInParsedArray(pComp);

    if (pRef)
    {
        pRef->AddRef();
        return pRef->GetRef();
    }

    std::unique_ptr<IComponentRef> pNewRef(new IComponentRef(pComp));
    m_SymbolParsed.Add(pNewRef.get());
    pNewRef.release();

    return 1;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl::IComponentRef* PSS_ProcessGraphModelMdl::FindSymbolInParsedArray(ZBSymbol* pComp)
{
    std::size_t symbolCount = m_SymbolParsed.GetSize();

    for (register std::size_t index = 0; index < symbolCount; ++index)
    {
        PSS_ProcessGraphModelMdl::IComponentRef* pCurRef = m_SymbolParsed.GetAt(index);

        if (pCurRef->GetSymbol() == pComp)
            return pCurRef;
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::RemoveAllSymbolInParsedArray()
{
    std::size_t symbolCount = m_SymbolParsed.GetSize();

    for (register std::size_t index = 0; index < symbolCount; ++index)
    {

        PSS_ProcessGraphModelMdl::IComponentRef* pCurRef = m_SymbolParsed.GetAt(index);

        if (pCurRef)
            delete pCurRef;
    }

    m_SymbolParsed.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::GetExistingPageNameArray(CStringArray& pageArray)
{
    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            // if a page exists
            if (pPage)
                pageArray.Add(pPage->GetPageName());

            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->GetExistingPageNameArray(pageArray);
        }
    }

    // process the model components
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pSet->GetAt(i));

        // if a sub-model exists, not a referenced model, and contains a page set
        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            if (pChildModel && pChildModel->HasPageSet())
                pChildModel->GetExistingPageNameArray(pageArray);
        }
    }
}
//---------------------------------------------------------------------------
int PSS_ProcessGraphModelMdl::GetNextAvailableRefNb(PSS_ProcessGraphModelMdl* pRootModel)
{
    int result = 1;

    // if no root model defined, the search should be processed on all the document
    if (!pRootModel)
        // get the document model controller
        pRootModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(GetRoot());

    if (!pRootModel)
        return result;

    // get the model controller page set
    IProcessGraphPageSet* pSet = pRootModel->GetPageSet();

    if (!pSet)
        return result;

    IProcessGraphPageIterator it(pSet);

    // iterate through the model controller children pages
    for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
    {
        // get the model controller current page
        PSS_ProcessGraphModelMdl* pCurModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pPage->GetModel());

        if (!pCurModel)
            continue;

        // get the model controller symbol set
        CODComponentSet* pCompSet = pCurModel->GetComponents();

        if (!pCompSet)
            continue;

        const int componentCount = pCompSet->GetSize();

        // iterate through model controller symbols
        for (int i = 0; i < componentCount; ++i)
        {
            ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pCompSet->GetAt(i));
            PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pCompSet->GetAt(i));

            // is a symbol?
            if (pSymbol && !pSymbol->IsChildModelRef())
            {
                PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

                // if thge symbol contains children, continue the search on it
                if (pChildModel)
                {
                    const int childResult = GetNextAvailableRefNb(pChildModel);

                    if (childResult > result)
                        result = childResult;
                }

                // check and update the result
                if (pSymbol->GetSymbolReferenceNumber() >= result)
                {
                    result = pSymbol->GetSymbolReferenceNumber();
                    ++result;
                }
            }

            // is a link symbol?
            if (pLinkSymbol)
                // check and update the result
                if (pLinkSymbol->GetSymbolReferenceNumber() >= result)
                {
                    result = pLinkSymbol->GetSymbolReferenceNumber();
                    ++result;
                }
        }
    }

    return result;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdl::GetExistingReferenceNumberArray(CStringArray& refNbArray)
{
    CODComponentSet* pSet           = GetComponents();
    const int        componentCount = pSet->GetSize();

    for (int i = 0; i < componentCount; ++i)
    {
        ZBSymbol*       pSymbol     =                  dynamic_cast<ZBSymbol*>(pSet->GetAt(i));
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pSet->GetAt(i));

        // add the reference number to the array
        if (pSymbol)
            refNbArray.Add(pSymbol->GetSymbolReferenceNumberStr());
        else
        if (pLinkSymbol)
            refNbArray.Add(pLinkSymbol->GetSymbolReferenceNumberStr());

        if (pSymbol && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

            // if the process contains a child model, process it
            if (pChildModel)
                pChildModel->GetExistingReferenceNumberArray(refNbArray);
        }
    }

    if (m_pPageSet)
    {
        IProcessGraphPageIterator it(m_pPageSet);

        // iterate through all pages
        for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

            // don't process the page model owned by itself
            if (pPageModel && pPageModel != this)
                pPageModel->GetExistingReferenceNumberArray(refNbArray);
        }
    }
}
//---------------------------------------------------------------------------
