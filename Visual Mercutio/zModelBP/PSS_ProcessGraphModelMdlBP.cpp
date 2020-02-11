/****************************************************************************
 * ==> PSS_ProcessGraphModelMdlBP ------------------------------------------*
 ****************************************************************************
 * Description : Provides a process graphic model for banking process       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessGraphModelMdlBP.h"

// processsoft
#include "zBaseLib\PSS_GUID.h"
#include "zBaseLib\PSS_BaseDocument.h"
#include "zBaseLib\PSS_Log.h"
#include "zBaseLib\PSS_MessageDlg.h"
#include "zModel\PSS_ProcessGraphPage.h"
#include "zModel\PSS_ProcessGraphModelViewport.h"
#include "zModel\PSS_UserEntity.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "PSS_ProcessGraphModelControllerBP.h"
#include "PSS_DoorSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "ZBDeliverableLinkSymbol.h"
#include "ZBInputAttributes.h"
#include "ZBDistributionAttributes.h"
#include "ZUCheckSymbolConsistency.h"

// resources
#include "zModel\zModelRes.h"
#include "zModelBPRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ProcessGraphModelMdlBP, PSS_ProcessGraphModelMdl, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ProcessGraphModelMdlBP
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdlBP::PSS_ProcessGraphModelMdlBP(const CString& name, PSS_ProcessGraphModelMdlBP* pParent) :
    PSS_ProcessGraphModelMdl(name, pParent),
    m_pInputAttributes(NULL),
    m_pDistributionAttributes(NULL)
{
    // set the default notation
    m_Notation = E_MN_Beryl;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdlBP::~PSS_ProcessGraphModelMdlBP()
{
    if (m_pInputAttributes)
        delete m_pInputAttributes;

    if (m_pDistributionAttributes)
        delete m_pDistributionAttributes;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelController* PSS_ProcessGraphModelMdlBP::CreateController(PSS_ProcessGraphModelViewport* pVp)
{
    return new PSS_ProcessGraphModelControllerBP(pVp);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::SetDefaultWkfProperty(bool redefineOnExisting)
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::DeleteAllActivitiesLinkedToWorkflow()
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::RecalculateSymbolReferences()
{
    RecalculatePageReference();
    RecalculateDoorReference();
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdlBP::GetBPPageSymbols(CODNodeArray& nodes, bool deep)
{
    return GetSymbolsISA(nodes, RUNTIME_CLASS(PSS_PageSymbolBP), deep);
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdlBP::GetBPDoorSymbols(CODNodeArray& nodes, bool deep)
{
    return GetSymbolsISA(nodes, RUNTIME_CLASS(PSS_DoorSymbolBP), deep);
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdlBP::GetStartSymbols(CODNodeArray& nodes, bool deep)
{
    const std::size_t counter = GetBPStartSymbols(nodes, deep);

    // start symbol was found on the model?
    if (counter > 0)
        return counter;

    // otherwise, locate the right processes which contains start symbol
    return GetStartSymbolInStartProcess(nodes, deep);
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdlBP::GetBPStartSymbols(CODNodeArray& nodes, bool deep)
{
    return GetSymbolsISA(nodes, RUNTIME_CLASS(ZBBPStartSymbol), deep);
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdlBP::GetBPStopSymbols(CODNodeArray& nodes, bool deep)
{
    return GetSymbolsISA(nodes, RUNTIME_CLASS(ZBBPStopSymbol), deep);
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdlBP::GetBPProcedureSymbols(CODNodeArray& nodes, bool deep)
{
    return GetSymbolsISA(nodes, RUNTIME_CLASS(PSS_ProcedureSymbolBP), deep);
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdlBP::GetBPProcessSymbols(CODNodeArray& nodes, bool deep)
{
    return GetSymbolsISA(nodes, RUNTIME_CLASS(PSS_ProcessSymbolBP), deep);
}
//---------------------------------------------------------------------------
UINT PSS_ProcessGraphModelMdlBP::GetSymbolImageIDRes() const
{
    return IDB_IL_BP_SYMBOLS;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdlBP::CheckModelWorkflow(PSS_Log* pLog, BOOL modelIsClean)
{
    // reset the recursion counter
    m_RecursionCounter = 0;
    m_IsInRecursion    = false;

    ZUCheckSymbolConsistency symbolConsistency(this, pLog);
    symbolConsistency.CheckSymbol(*this, modelIsClean);

    // reset the array
    RemoveAllSymbolInParsedArray();

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelMdlBP::GenerateModelWorkflow(PSS_Log* pLog, PSS_ProcessGraphModelDoc* pDoc)
{
    // todo -cFeature -oJean: implement that
    ASSERT(FALSE);
    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::ReassignUnit(PSS_Log* pLog)
{
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();
    CODComponentSet*          pSet       = GetComponents();
    const int                 setSize    = pSet ? pSet->GetSize() : 0;
    bool                      error;

    for (int i = 0; i < setSize; ++i)
    {
        CODComponent* pComp   = pSet->GetAt(i);
        PSS_Symbol*   pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

        if (!pSymbol)
            continue;

        ZBBPStartSymbol*       pStartSymbol     =                       dynamic_cast<ZBBPStartSymbol*>(pComp);
        ZBBPStopSymbol*        pStopSymbol      = pStartSymbol ? NULL : dynamic_cast<ZBBPStopSymbol*>(pComp);
        PSS_ProcedureSymbolBP* pProcedureSymbol = pStopSymbol  ? NULL : dynamic_cast<PSS_ProcedureSymbolBP*>(pComp);

        // if a start symbol, a stop symbol, or a procedure symbol
        if (pStartSymbol                          &&
           !pStartSymbol->GetUnitGUID().IsEmpty() &&
           (pStartSymbol->GetUnitName().IsEmpty() || pStartSymbol->GetUnitCost() <= 0))
        {
            if (pStartSymbol->GetUnitName().IsEmpty())
                pStartSymbol->SetUnitName(pStartSymbol->RetrieveUnitName(pStartSymbol->GetUnitGUID(), error));

            if (pStartSymbol->GetUnitCost() <= 0)
                pStartSymbol->SetUnitCost(pStartSymbol->RetrieveUnitCost(pStartSymbol->GetUnitGUID(), error));

            if (pLog)
            {
                CString message;
                message.Format(IDS_AL_UNITREASSIGNED, pStartSymbol->GetSymbolName());
                PSS_GenericSymbolErrorLine e(message);
                pLog->AddLine(e);
            }
        }
        else
        if (pStopSymbol                          &&
           !pStopSymbol->GetUnitGUID().IsEmpty() &&
           (pStopSymbol->GetUnitName().IsEmpty() || pStopSymbol->GetUnitCost() <= 0))
        {
            if (pStopSymbol->GetUnitName().IsEmpty())
                pStopSymbol->SetUnitName(pStopSymbol->RetrieveUnitName(pStopSymbol->GetUnitGUID(), error));

            if (pStopSymbol->GetUnitCost() <= 0)
                pStopSymbol->SetUnitCost(pStopSymbol->RetrieveUnitCost(pStopSymbol->GetUnitGUID(), error));

            if (pLog)
            {
                CString message;
                message.Format(IDS_AL_UNITREASSIGNED, pStopSymbol->GetSymbolName());
                PSS_GenericSymbolErrorLine e(message);
                pLog->AddLine(e);
            }
        }
        else
        if (pProcedureSymbol                          &&
           !pProcedureSymbol->GetUnitGUID().IsEmpty() &&
           (pProcedureSymbol->GetUnitName().IsEmpty() || pProcedureSymbol->GetUnitCost() <= 0))
        {
            if (pProcedureSymbol->GetUnitName().IsEmpty())
                pProcedureSymbol->SetUnitName(pProcedureSymbol->RetrieveUnitName(pProcedureSymbol->GetUnitGUID(), error));

            if (pProcedureSymbol->GetUnitCost() <= 0)
                pProcedureSymbol->SetUnitCost(pProcedureSymbol->RetrieveUnitCost(pProcedureSymbol->GetUnitGUID(), error));

            if (pLog)
            {
                CString message;
                message.Format(IDS_AL_UNITREASSIGNED, pProcedureSymbol->GetSymbolName());
                PSS_GenericSymbolErrorLine e(message);
                pLog->AddLine(e);
            }
        }

        // if has child model
        if (pSymbol->GetChildModel() && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdlBP* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSymbol->GetChildModel());

            // also recalculate its model
            if (pChildModel)
                pChildModel->ReassignUnit(pLog);
        }
    }

    // process the page set if there is one
    if (m_pPageSet)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(m_pPageSet);

        for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

            // don't recalculate page reference of itself
            if (pModel && pModel != this)
                pModel->ReassignUnit(pLog);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::ReassignSystem(PSS_Log* pLog)
{
    // todo -cFeature -oJean: not required for system for now. If a problem was found, do implement the same mecanism as for units
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::NotifyDeletePage(PSS_ProcessGraphPage* pPage)
{
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();
    CODComponentSet*          pSet       = GetComponents();
    const int                 setSize    = pSet ? pSet->GetSize() : 0;

    for (int i = 0; i < setSize; ++i)
    {
        CODComponent* pComp   = pSet->GetAt(i);
        PSS_Symbol*   pSymbol = dynamic_cast<PSS_Symbol*>(pComp);
        
        if (!pSymbol)
            continue;

        PSS_PageSymbolBP* pPageSymbol = dynamic_cast<PSS_PageSymbolBP*>(pComp);

        // if a page symbol
        if (pPageSymbol && pPageSymbol->GetPage() == pPage)
        {
            pPageSymbol->RemoveTwinPageSymbol();
            pPageSymbol->SetPageModel(NULL);
        }

        // if has child model
        if (pSymbol->GetChildModel() && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSymbol->GetChildModel());

            // also recalculate its model
            if (pModel)
                pModel->NotifyDeletePage(pPage);
        }
    }

    // process the page set if there is one
    if (m_pPageSet)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(m_pPageSet);

        for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

            // don't recalculate page reference of itself
            if (pModel && pModel != this)
                pModel->NotifyDeletePage(pPage);
        }
    }
}
//---------------------------------------------------------------------------
ZBInputAttributeManager* PSS_ProcessGraphModelMdlBP::AllocateInputAttributes(bool deleteExisting)
{
    if (GetRoot() == this)
    {
        if (m_pInputAttributes && deleteExisting)
        {
            delete m_pInputAttributes;
            m_pInputAttributes = NULL;
        }

        m_pInputAttributes = new ZBInputAttributeManager();

        return m_pInputAttributes;
    }

    PSS_ProcessGraphModelMdlBP* pRoot = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(GetRoot());

    if (pRoot)
        return pRoot->AllocateInputAttributes(deleteExisting);

    return NULL;
}
//---------------------------------------------------------------------------
ZBDistributionAttributeManager* PSS_ProcessGraphModelMdlBP::AllocateDistributionAttributes(bool deleteExisting)
{
    if (GetRoot() == this)
    {
        if (m_pDistributionAttributes && deleteExisting)
        {
            delete m_pDistributionAttributes;
            m_pDistributionAttributes = NULL;
        }

        m_pDistributionAttributes = new ZBDistributionAttributeManager;

        return m_pDistributionAttributes;
    }

    PSS_ProcessGraphModelMdlBP* pRoot = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(GetRoot());

    if (pRoot)
        return pRoot->AllocateDistributionAttributes(deleteExisting);

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::Serialize(CArchive& ar)
{
    PSS_ProcessGraphModelMdl::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE(_T("PSS_ProcessGraphModelMdlBP::Serialize : Start Save\n"));

        // serialize the input attributes only for the root model
        if (GetRoot() == this)
        {
            ar << int(1);
            ar << m_pInputAttributes;
            ar << m_pDistributionAttributes;
        }
        else
            ar << int(0);

        TRACE(_T("PSS_ProcessGraphModelMdlBP::Serialize : End Save\n"));
    }
    else
    {
        TRACE(_T("PSS_ProcessGraphModelMdlBP::Serialize : Start Read\n"));

        PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

        // Serialize the input attributes
        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 21)
        {
            int value;
            ar >> value;

            if (value == 1)
            {
                ar >> (CObject*&)m_pInputAttributes;
                ar >> (CObject*&)m_pDistributionAttributes;
            }
        }

        TRACE(_T("PSS_ProcessGraphModelMdlBP::Serialize : End Read\n"));
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::OnPostOpenDocument(long version)
{
    if (version < 19)
    {
        // migrate all old properties to new one
        MigrateProperties();

        // check unit GUID. This function is called for compatibility reason, only for migrating beta 1 file to beta 2
        MigrateUnitGUID();

        // show a warning message
        PSS_MessageDlg message;
        message.ShowMessage(IDS_FILEBETA1_CONVERTED, IDS_FILEBETA1_CONVERTED_TITLE);

        // set the document as modified
        SetModifiedFlag(TRUE);
    }

    if (version < 20)
    {
        // convert deliverables
        ConvertDeliverables();

        // show a warning message
        PSS_MessageDlg message;
        message.ShowMessage(IDS_FILEBETA2_CONVERTED, IDS_FILEBETA2_CONVERTED_TITLE);

        // set the document as modified
        SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::RecalculatePageReference()
{
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();
    CODComponentSet*          pSet       = GetComponents();
    const int                 setSize    = pSet ? pSet->GetSize() : 0;

    for (int i = 0; i < setSize; ++i)
    {
        CODComponent* pComp   = pSet->GetAt(i);
        PSS_Symbol*   pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

        if (!pSymbol)
            continue;

        PSS_PageSymbolBP* pPageSymbol = dynamic_cast<PSS_PageSymbolBP*>(pComp);

        // if a page symbol
        if (pPageSymbol)
            // recalculate the page reference
            pPageSymbol->RecalculateTwinPageReference(pRootModel);

        // If has child model
        if (pSymbol->GetChildModel() && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSymbol->GetChildModel());

            // also recalculate its model
            if (pModel)
                pModel->RecalculatePageReference();
        }
    }

    // process the page set if there is one
    if (m_pPageSet)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(m_pPageSet);

        for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

            // don't recalculate page reference of itself
            if (pModel && pModel != this)
                pModel->RecalculatePageReference();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::RecalculateDoorReference()
{
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();
    CODComponentSet*          pSet       = GetComponents();
    const int                 setSize    = pSet ? pSet->GetSize() : 0;

    for (int i = 0; i < setSize; ++i)
    {
        CODComponent* pComp   = pSet->GetAt(i);
        PSS_Symbol*   pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

        if (!pSymbol)
            continue;

        PSS_DoorSymbolBP* pDoorSymbol = dynamic_cast<PSS_DoorSymbolBP*>(pComp);

        // if a page symbol
        if (pDoorSymbol)
            // recalculate the door reference
            pDoorSymbol->RecalculateTwinDoorReference(pRootModel);

        // if contains a child model
        if (pSymbol->GetChildModel() && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSymbol->GetChildModel());

            // also recalculate its model
            if (pModel)
                pModel->RecalculateDoorReference();
        }
    }

    // process the page set if there is one
    if (m_pPageSet)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(m_pPageSet);

        for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

            // don't recalculate page reference of itself
            if (pModel && pModel != this)
                pModel->RecalculateDoorReference();
        }
    }
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcessGraphModelMdlBP::GetStartSymbolInStartProcess(CODNodeArray& nodes, bool deep)
{
    CODNodeArray      processNodes;
    const std::size_t counter = GetBPProcessSymbols(processNodes);

    // no process?
    if (!counter)
        return 0;

    CODNodeArray retainedProcessNodes;

    // iterate through the node array and for each process which have no entering up links
    for (std::size_t nodeIndex = 0; nodeIndex < counter; ++nodeIndex)
    {
        IODNode*             pINode   = processNodes.GetAt(nodeIndex);
        PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pINode);

        if (!pProcess)
            continue;

        // check if only leaving down edges
        CODEdgeArray edges;
        const std::size_t enteringUpLinkCount = pProcess->GetEdgesEntering_Up(edges);

        // check if only leaving down and no entering up links
        if (!enteringUpLinkCount)
            retainedProcessNodes.Add(pProcess);
    }

    const std::size_t retainedCount = retainedProcessNodes.GetSize();

    if (retainedCount > 0)
    {
        // for each process, get the start symbol. The first time, don't go deeper. If the search end is reached and
        // no start symbol was found, recursively call the GetStartSymbols() function
        for (std::size_t nodeIndex = 0; nodeIndex < retainedCount; ++nodeIndex)
        {
            IODNode*             pINode   = retainedProcessNodes.GetAt(nodeIndex);
            PSS_ProcessSymbolBP* pProcess = static_cast<PSS_ProcessSymbolBP*>(pINode);

            if (!pProcess)
                continue;

            PSS_ProcessGraphModelMdlBP* pSubModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcess->GetChildModel());

            // get the start symbols
            if (pSubModel)
                pSubModel->GetBPStartSymbols(nodes);
        }

        const int nodeSize = nodes.GetSize();

        // check the nodes array size
        if (nodeSize > 0)
            return nodeSize;

        // iterate through the retained processes again, but this time call GetStartSymbols() function instead
        for (std::size_t nodeIndex = 0; nodeIndex < retainedCount; ++nodeIndex)
        {
            IODNode*             pINode   = retainedProcessNodes.GetAt(nodeIndex);
            PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pINode);

            if (!pProcess)
                continue;

            PSS_ProcessGraphModelMdlBP* pSubModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pProcess->GetChildModel());

            // get the start symbols
            if (pSubModel)
                pSubModel->GetStartSymbols(nodes, deep);
        }

        return nodes.GetSize();
    }

    // No start found
    return 0;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::MigrateProperties()
{
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();
    CODComponentSet*          pSet       = GetComponents();
    const int                 setSize    = pSet ? pSet->GetSize() : 0;

    for (int i = 0; i < setSize; ++i)
    {
        CODComponent* pComp   = pSet->GetAt(i);
        PSS_Symbol*   pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

        if (!pSymbol)
            continue;

        // if contains a child model
        if (pSymbol->GetChildModel() && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSymbol->GetChildModel());

            // also recalculate its model
            if (pModel)
                pModel->MigrateProperties();
        }
    }

    // process the page set if there is one
    if (m_pPageSet)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(m_pPageSet);

        for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

            // don't recalculate page reference of itself
            if (pModel && pModel != this)
                pModel->MigrateProperties();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::MigrateUnitGUID()
{
    CODComponentSet*          pSet       = GetComponents();
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();
    const int                 setSize    = pSet ? pSet->GetSize() : 0;

    for (int i = 0; i < setSize; ++i)
    {
        CODComponent* pComp   = pSet->GetAt(i);
        PSS_Symbol*   pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

        if (!pSymbol)
            continue;

        ZBBPStartSymbol*       pStartSymbol     =                       dynamic_cast<ZBBPStartSymbol*>(pComp);
        ZBBPStopSymbol*        pStopSymbol      = pStartSymbol ? NULL : dynamic_cast<ZBBPStopSymbol*>(pComp);
        PSS_ProcedureSymbolBP* pProcedureSymbol = pStopSymbol  ? NULL : dynamic_cast<PSS_ProcedureSymbolBP*>(pComp);
        bool                   error;

        // if a start symbol, a stop symbol, or a procedure symbol
        if (pStartSymbol && !pStartSymbol->GetUnitName().IsEmpty())
        {
            if (!PSS_GUID::GUIDIsValid(pStartSymbol->GetUnitGUID()))
                pStartSymbol->SetUnitGUID(pStartSymbol->RetrieveUnitGUID(pStartSymbol->GetUnitName(), error));
        }
        else
        if (pStopSymbol && !pStopSymbol->GetUnitName().IsEmpty())
        {
            if (!PSS_GUID::GUIDIsValid(pStopSymbol->GetUnitGUID()))
                pStopSymbol->SetUnitGUID(pStopSymbol->RetrieveUnitGUID(pStopSymbol->GetUnitName(), error));
        }
        else
        if (pProcedureSymbol && !pProcedureSymbol->GetUnitName().IsEmpty())
            if (!PSS_GUID::GUIDIsValid(pProcedureSymbol->GetUnitGUID()))
                pProcedureSymbol->SetUnitGUID(pProcedureSymbol->RetrieveUnitGUID(pProcedureSymbol->GetUnitName(), error));

        // if contains a child model
        if (pSymbol->GetChildModel() && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSymbol->GetChildModel());

            // also recalculate its model
            if (pModel)
                pModel->MigrateUnitGUID();
        }
    }

    // process the page set if there is one
    if (m_pPageSet)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(m_pPageSet);

        for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

            // don't recalculate page reference of itself
            if (pModel && pModel != this)
                pModel->MigrateUnitGUID();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelMdlBP::ConvertDeliverables()
{
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();
    CODComponentSet*          pSet       = GetComponents();
    const int                 setSize    = pSet ? pSet->GetSize() : 0;

    for (int i = 0; i < setSize; ++i)
    {
        CODComponent* pComp   = pSet->GetAt(i);
        PSS_Symbol*   pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

        if (!pSymbol)
            continue;

        ZBDeliverableLinkSymbol* pDeliverableSymbol = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);

        // If a deliverable symbol
        if (pDeliverableSymbol)
        {
            const int          labelCount = pDeliverableSymbol->GetNumLabels();
            CODLabelComponent* pLabelComp;

            // set the new colors
            for (int j = 0; j < labelCount; ++j)
            {
                pLabelComp = pDeliverableSymbol->GetLabel(j);

                if (pLabelComp)
                    break;
            }

            if (!pLabelComp)
                continue;

            CODFontProperties* pFontProp = (CODFontProperties*)pLabelComp->GetProperty(OD_PROP_FONT);

            if (pFontProp)
            {
                std::unique_ptr<CODFontProperties> pNewFontProp(new CODFontProperties(*pFontProp));
                pNewFontProp->SetFaceName(_T("Arial"));
                pNewFontProp->SetWeight(FW_BOLD);
                pNewFontProp->SetPointSize(8);
                pLabelComp->SetProperty(pNewFontProp.get());
                pNewFontProp.release();

                pLabelComp->SetValue(OD_PROP_AUTOSIZE,       TRUE);
                pLabelComp->SetValue(OD_PROP_WORDBREAK,      TRUE);
                pLabelComp->SetValue(OD_PROP_MULTILINE,      TRUE);
                pLabelComp->SetValue(OD_PROP_HORZ_ALIGNMENT, DT_CENTER);
                pLabelComp->SetValue(OD_PROP_VERT_ALIGNMENT, DT_TOP);

                // change the fill color
                CODFillProperties* pFillProps = dynamic_cast<CODFillProperties*>(pLabelComp->GetProperty(OD_PROP_FILL));

                if (pFillProps)
                {
                    std::unique_ptr<CODFillProperties> pNewFillProps(new CODFillProperties(*pFillProps));
                    pNewFillProps->SetColor(RGB(192, 220, 192));
                    pLabelComp->SetProperty(pNewFillProps.get());
                    pNewFillProps.release();
                }
            }
        }

        // if has child model
        if (pSymbol->GetChildModel() && !pSymbol->IsChildModelRef())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSymbol->GetChildModel());

            // also recalculate its model
            if (pModel)
                pModel->ConvertDeliverables();
        }
    }

    // process the page set if there is one
    if (m_pPageSet)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(m_pPageSet);

        for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
        {
            PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

            // don't recalculate page reference of itself
            if (pModel && pModel != this)
                pModel->ConvertDeliverables();
        }
    }
}
//---------------------------------------------------------------------------
