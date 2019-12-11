// ProcGraphModelMdlBP.cpp : implementation of the ZDProcessGraphModelMdlBP class

#include "stdafx.h"
#include "ProcGraphModelMdlBP.h"

#include "ProcGraphModelCtlrBP.h"
#include "zModel\PSS_ProcessGraphModelViewport.h"

#include "zBaseLib\PSS_BaseDocument.h"

#include "ZBBPPageSymbol.h"
#include "ZBBPDoorSymbol.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"
#include "ZBBPProcedureSymbol.h"
#include "ZBBPProcessSymbol.h"
#include "ZBDeliverableLinkSymbol.h"
#include "zModel\ZDProcessGraphPage.h"

#include "ZBInputAttributes.h"
#include "ZBDistributionAttributes.h"

#include "zModel\ZBUserEntity.h"

#include "zBaseLib\PSS_GUID.h"

#include "ZUCheckSymbolConsistency.h"

// Include files for log
#include "zBaseLib\PSS_Log.h"
#include "zModel\ZBGenericSymbolErrorLine.h"

#include "zBaseLib\PSS_MessageDlg.h"

#include "zModel\zModelRes.h"
#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 27 septembre 2005 - Ajout de la décoration unicode _T( )

/////////////////////////////////////////////////////////////////////////////
// ZDProcessGraphModelMdlBP

IMPLEMENT_SERIAL(ZDProcessGraphModelMdlBP, PSS_ProcessGraphModelMdl, g_DefVersion)

ZDProcessGraphModelMdlBP::ZDProcessGraphModelMdlBP(const CString                Name    /*= ""*/,
                                                   ZDProcessGraphModelMdlBP*    pParent    /*= NULL*/)
    : PSS_ProcessGraphModelMdl(Name, pParent),
    m_InputAttributes(NULL),
    m_pDistributionAttributes(NULL)
{
    // Set the right notation
    m_Notation = E_MN_Beryl;
}

ZDProcessGraphModelMdlBP::~ZDProcessGraphModelMdlBP()
{
    if (m_InputAttributes)
    {
        delete m_InputAttributes;
        m_InputAttributes = NULL;
    }

    if (m_pDistributionAttributes)
    {
        delete m_pDistributionAttributes;
        m_pDistributionAttributes = NULL;
    }
}

PSS_ProcessGraphModelController* ZDProcessGraphModelMdlBP::CreateController(PSS_ProcessGraphModelViewport* pVp)
{
    return new ZDProcessGraphModelControllerBP(pVp);
}

void ZDProcessGraphModelMdlBP::SetDefaultWkfProperty(bool RedefineOnExisting /*= false*/)
{}

void ZDProcessGraphModelMdlBP::DeleteAllActivitiesLinkedToWorkflow()
{}

size_t ZDProcessGraphModelMdlBP::GetBPPageSymbols(CODNodeArray& Nodes, bool Deep /*= false*/)
{
    return GetSymbolsISA(Nodes, RUNTIME_CLASS(ZBBPPageSymbol), Deep);
}

size_t ZDProcessGraphModelMdlBP::GetBPDoorSymbols(CODNodeArray& Nodes, bool Deep /*= false*/)
{
    return GetSymbolsISA(Nodes, RUNTIME_CLASS(ZBBPDoorSymbol), Deep);
}

size_t ZDProcessGraphModelMdlBP::GetBPStartSymbols(CODNodeArray& Nodes, bool Deep /*= false*/)
{
    return GetSymbolsISA(Nodes, RUNTIME_CLASS(ZBBPStartSymbol), Deep);
}

size_t ZDProcessGraphModelMdlBP::GetBPStopSymbols(CODNodeArray& Nodes, bool Deep /*= false*/)
{
    return GetSymbolsISA(Nodes, RUNTIME_CLASS(ZBBPStopSymbol), Deep);
}

size_t ZDProcessGraphModelMdlBP::GetBPProcedureSymbols(CODNodeArray& Nodes, bool Deep /*= false*/)
{
    return GetSymbolsISA(Nodes, RUNTIME_CLASS(ZBBPProcedureSymbol), Deep);
}

size_t ZDProcessGraphModelMdlBP::GetBPProcessSymbols(CODNodeArray& Nodes, bool Deep /*= false*/)
{
    return GetSymbolsISA(Nodes, RUNTIME_CLASS(ZBBPProcessSymbol), Deep);
}

size_t ZDProcessGraphModelMdlBP::GetStartSymbols(CODNodeArray& Nodes, bool Deep /*= false*/)
{
    size_t Counter = GetBPStartSymbols(Nodes, Deep);

    // If we found start symbol on the model, return
    if (Counter > 0)
    {
        return Counter;
    }

    // Otherwise, we need to locate the right processes which contains start symbol
    return GetStartSymbolInStartProcess(Nodes, Deep);
}

size_t ZDProcessGraphModelMdlBP::GetStartSymbolInStartProcess(CODNodeArray& Nodes, bool Deep /*= false*/)
{
    CODNodeArray ProcessNodes;
    size_t Counter = GetBPProcessSymbols(ProcessNodes);

    // If no process, return 0;
    if (Counter == 0)
    {
        return 0;
    }

    // Otherwise, run through the node array and for each process which have no
    // entering up links
    CODNodeArray RetainProcessNodes;

    for (std::size_t nNodeIdx = 0; nNodeIdx < Counter; ++nNodeIdx)
    {
        IODNode* pINode = ProcessNodes.GetAt(nNodeIdx);
        ZBBPProcessSymbol* pProcess = static_cast<ZBBPProcessSymbol*>(pINode);

        if (!pProcess)
        {
            continue;
        }

        // Check if only leaving down edges
        CODEdgeArray Edges;
        size_t EnteringUpLinkCount = pProcess->GetEdgesEntering_Up(Edges);

        // Check if only leaving down and no entering up links
        if (EnteringUpLinkCount == 0)
        {
            RetainProcessNodes.Add(pProcess);
        }
    }

    if (RetainProcessNodes.GetSize() > 0)
    {
        // Now, for each process, retreive start symbol
        // The first time, we don't go deeper
        // if at the end of the search we don't found any start symbol,
        // Then recursively call the GetStartSymbols function
        for (std::size_t nNodeIdx = 0; nNodeIdx < std::size_t(RetainProcessNodes.GetSize()); ++nNodeIdx)
        {
            IODNode*           pINode = RetainProcessNodes.GetAt(nNodeIdx);
            ZBBPProcessSymbol* pProcess = static_cast<ZBBPProcessSymbol*>(pINode);

            if (!pProcess)
                continue;

            CODModel* pSubModel = pProcess->GetChildModel();

            if (pSubModel && ISA(pSubModel, ZDProcessGraphModelMdlBP))
            {
                // Then retreive start symbols
                dynamic_cast<ZDProcessGraphModelMdlBP*>(pSubModel)->GetBPStartSymbols(Nodes);
            }
        }

        // now, check the size of the Nodes Array
        if (Nodes.GetSize() > 0)
            return Nodes.GetSize();

        // Otherwise, redo the loop but call GetStartSymbols function instead
        for (std::size_t nNodeIdx = 0; nNodeIdx < std::size_t(RetainProcessNodes.GetSize()); ++nNodeIdx)
        {
            IODNode* pINode = RetainProcessNodes.GetAt(nNodeIdx);
            ZBBPProcessSymbol* pProcess = static_cast<ZBBPProcessSymbol*>(pINode);

            if (!pProcess)
            {
                continue;
            }

            CODModel* pSubModel = pProcess->GetChildModel();

            if (pSubModel && ISA(pSubModel, ZDProcessGraphModelMdlBP))
            {
                // Then retreive start symbols
                dynamic_cast<ZDProcessGraphModelMdlBP*>(pSubModel)->GetStartSymbols(Nodes, Deep);
            }
        }

        // If found or not found, return the array size
        return Nodes.GetSize();
    }

    // No start found
    return 0;
}

UINT ZDProcessGraphModelMdlBP::GetSymbolImageIDRes() const
{
    return IDB_IL_BP_SYMBOLS;
}

void ZDProcessGraphModelMdlBP::OnPostOpenDocument(long DocumentVersion)
{
    if (DocumentVersion < 19)
    {
        // Migrate all old properties to new properties
        MigrateProperties();

        // Check Unit GUID
        // This function is called for compatibility reason
        // only for migrating beta 1 file to Beta 2
        MigrateUnitGUID();

        // show a warning message
        PSS_MessageDlg message;
        message.ShowMessage(IDS_FILEBETA1_CONVERTED, IDS_FILEBETA1_CONVERTED_TITLE);

        // Sets the modified flag to true for the document
        SetModifiedFlag(TRUE);
    }

    if (DocumentVersion < 20)
    {
        // Convert deliverables
        ConvertDeliverables();

        // show a warning message
        PSS_MessageDlg message;
        message.ShowMessage(IDS_FILEBETA2_CONVERTED, IDS_FILEBETA2_CONVERTED_TITLE);

        // Sets the modified flag to true for the document
        SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelMdlBP::MigrateProperties()
{
    CODComponentSet* pSet = GetComponents();
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent*    pComp = pSet->GetAt(i);

        // If has child model
        if (pComp && ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() && !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // and recalculate its model also
            reinterpret_cast<ZDProcessGraphModelMdlBP*>(((ZBSymbol*)pComp)->GetChildModel())->MigrateProperties();
        }
    }

    // Process the page set if there is one
    if (m_pPageSet != NULL)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not recalculate page reference of itself
            if (pPage->GetModel() && pPage->GetModel() != this)
            {
                reinterpret_cast<ZDProcessGraphModelMdlBP*>(pPage->GetModel())->MigrateProperties();
            }
        }
    }
}

void ZDProcessGraphModelMdlBP::MigrateUnitGUID()
{
    CODComponentSet* pSet = GetComponents();
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent*    pComp = pSet->GetAt(i);

        // If a start symbol or a stop symbol or a procedure symbol
        if (pComp && ISA(pComp, ZBBPStartSymbol) &&
            !dynamic_cast<ZBBPStartSymbol*>(pComp)->GetUnitName().IsEmpty())
        {
            if (!PSS_GUID::GUIDIsValid(dynamic_cast<ZBBPStartSymbol*>(pComp)->GetUnitGUID()))
            {
                bool bError;
                dynamic_cast<ZBBPStartSymbol*>(pComp)->SetUnitGUID(dynamic_cast<ZBSymbol*>(pComp)->RetrieveUnitGUID(dynamic_cast<ZBBPStartSymbol*>(pComp)->GetUnitName(), bError));
            }
        }
        else if (pComp && ISA(pComp, ZBBPStopSymbol) &&
                 !dynamic_cast<ZBBPStopSymbol*>(pComp)->GetUnitName().IsEmpty())
        {
            if (!PSS_GUID::GUIDIsValid(dynamic_cast<ZBBPStopSymbol*>(pComp)->GetUnitGUID()))
            {
                bool bError;
                dynamic_cast<ZBBPStopSymbol*>(pComp)->SetUnitGUID(dynamic_cast<ZBSymbol*>(pComp)->RetrieveUnitGUID(dynamic_cast<ZBBPStopSymbol*>(pComp)->GetUnitName(), bError));
            }
        }
        else if (pComp && ISA(pComp, ZBBPProcedureSymbol) &&
                 !dynamic_cast<ZBBPProcedureSymbol*>(pComp)->GetUnitName().IsEmpty())
        {
            if (!PSS_GUID::GUIDIsValid(dynamic_cast<ZBBPProcedureSymbol*>(pComp)->GetUnitGUID()))
            {
                bool bError;
                dynamic_cast<ZBBPProcedureSymbol*>(pComp)->SetUnitGUID(dynamic_cast<ZBSymbol*>(pComp)->RetrieveUnitGUID(dynamic_cast<ZBBPProcedureSymbol*>(pComp)->GetUnitName(), bError));
            }
        }

        // If has child model
        if (pComp && ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() && !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // and recalculate its model also
            reinterpret_cast<ZDProcessGraphModelMdlBP*>(((ZBSymbol*)pComp)->GetChildModel())->MigrateUnitGUID();
        }
    }

    // Process the page set if there is one
    if (m_pPageSet != NULL)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not recalculate page reference of itself
            if (pPage->GetModel() && pPage->GetModel() != this)
            {
                reinterpret_cast<ZDProcessGraphModelMdlBP*>(pPage->GetModel())->MigrateUnitGUID();
            }
        }
    }
}

void ZDProcessGraphModelMdlBP::NotifyDeletePage(ZDProcessGraphPage* pPage)
{
    CODComponentSet* pSet = GetComponents();
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // If a page symbol
        if (pComp && ISA(pComp, ZBBPPageSymbol))
        {
            if (dynamic_cast<ZBBPPageSymbol*>(pComp)->GetPage() == pPage)
            {
                dynamic_cast<ZBBPPageSymbol*>(pComp)->RemoveTwinPageSymbol();
                dynamic_cast<ZBBPPageSymbol*>(pComp)->SetPageModel(NULL);
            }
        }

        // If has child model
        if (pComp && ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() && !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // and recalculate its model also
            reinterpret_cast<ZDProcessGraphModelMdlBP*>(((ZBSymbol*)pComp)->GetChildModel())->NotifyDeletePage(pPage);
        }
    }

    // Process the page set if there is one
    if (m_pPageSet != NULL)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not recalculate page reference of itself
            if (pPage->GetModel() && pPage->GetModel() != this)
            {
                reinterpret_cast<ZDProcessGraphModelMdlBP*>(pPage->GetModel())->NotifyDeletePage(pPage);
            }
        }
    }
}

void ZDProcessGraphModelMdlBP::ConvertDeliverables()
{
    CODComponentSet* pSet = GetComponents();
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent*    pComp = pSet->GetAt(i);

        // If a deliverable symbol
        if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
        {
            // Sets the new colors
            CODLabelComponent* pLabelComp;

            for (int j = 0; j < dynamic_cast<CODSymbolComponent*>(pComp)->GetNumLabels(); ++j)
            {
                pLabelComp = dynamic_cast<CODSymbolComponent*>(pComp)->GetLabel(j);

                if (pLabelComp)
                {
                    break;
                }
            }

            if (!pLabelComp)
            {
                continue;
            }

            CODFontProperties* pFontProp = (CODFontProperties*)pLabelComp->GetProperty(OD_PROP_FONT);
            CODFontProperties FontProp(*pFontProp);
            FontProp.SetFaceName(_T("Arial"));
            FontProp.SetWeight(FW_BOLD);
            FontProp.SetPointSize(8);
            pLabelComp->SetProperty(&FontProp);

            pLabelComp->SetValue(OD_PROP_AUTOSIZE, TRUE);
            pLabelComp->SetValue(OD_PROP_WORDBREAK, TRUE);
            pLabelComp->SetValue(OD_PROP_MULTILINE, TRUE);
            pLabelComp->SetValue(OD_PROP_HORZ_ALIGNMENT, DT_CENTER);
            pLabelComp->SetValue(OD_PROP_VERT_ALIGNMENT, DT_TOP);

            // Change the fill color
            CODFillProperties* pFillProps = dynamic_cast<CODFillProperties*>(pLabelComp->GetProperty(OD_PROP_FILL));
            CODFillProperties FillProps1(*pFillProps);
            FillProps1.SetColor(RGB(192, 220, 192));
            pLabelComp->SetProperty(&FillProps1);
        }

        // If has child model
        if (pComp && ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() && !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // and recalculate its model also
            reinterpret_cast<ZDProcessGraphModelMdlBP*>(((ZBSymbol*)pComp)->GetChildModel())->ConvertDeliverables();
        }
    }

    // Process the page set if there is one
    if (m_pPageSet != NULL)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not recalculate page reference of itself
            if (pPage->GetModel() && pPage->GetModel() != this)
            {
                reinterpret_cast<ZDProcessGraphModelMdlBP*>(pPage->GetModel())->ConvertDeliverables();
            }
        }
    }
}

void ZDProcessGraphModelMdlBP::ReassignUnit(PSS_Log* pLog /*= NULL*/)
{
    CODComponentSet* pSet = GetComponents();
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();
    bool bError;

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent*    pComp = pSet->GetAt(i);

        // If a start symbol or a stop symbol or a procedure symbol
        if (pComp && ISA(pComp, ZBBPStartSymbol) &&
            !dynamic_cast<ZBBPStartSymbol*>(pComp)->GetUnitGUID().IsEmpty() &&
            (dynamic_cast<ZBBPStartSymbol*>(pComp)->GetUnitName().IsEmpty() ||
             dynamic_cast<ZBBPStartSymbol*>(pComp)->GetUnitCost() <= 0))
        {
            if (dynamic_cast<ZBBPStartSymbol*>(pComp)->GetUnitName().IsEmpty())
            {
                dynamic_cast<ZBBPStartSymbol*>(pComp)->SetUnitName(dynamic_cast<ZBSymbol*>(pComp)->RetrieveUnitName(dynamic_cast<ZBBPStartSymbol*>(pComp)->GetUnitGUID(), bError));
            }

            if (dynamic_cast<ZBBPStartSymbol*>(pComp)->GetUnitCost() <= 0)
            {
                dynamic_cast<ZBBPStartSymbol*>(pComp)->SetUnitCost(dynamic_cast<ZBSymbol*>(pComp)->RetrieveUnitCost(dynamic_cast<ZBBPStartSymbol*>(pComp)->GetUnitGUID(), bError));
            }

            if (pLog)
            {
                CString message;
                message.Format(IDS_AL_UNITREASSIGNED, dynamic_cast<ZBBPStartSymbol*>(pComp)->GetSymbolName());
                ZBGenericSymbolErrorLine e(message);
                pLog->AddLine(e);
            }
        }
        else if (pComp && ISA(pComp, ZBBPStopSymbol) &&
                 !dynamic_cast<ZBBPStopSymbol*>(pComp)->GetUnitGUID().IsEmpty() &&
                 (dynamic_cast<ZBBPStopSymbol*>(pComp)->GetUnitName().IsEmpty() ||
                  dynamic_cast<ZBBPStopSymbol*>(pComp)->GetUnitCost() <= 0))
        {
            if (dynamic_cast<ZBBPStopSymbol*>(pComp)->GetUnitName().IsEmpty())
            {
                dynamic_cast<ZBBPStopSymbol*>(pComp)->SetUnitName(dynamic_cast<ZBSymbol*>(pComp)->RetrieveUnitName(dynamic_cast<ZBBPStopSymbol*>(pComp)->GetUnitGUID(), bError));
            }

            if (dynamic_cast<ZBBPStopSymbol*>(pComp)->GetUnitCost() <= 0)
            {
                dynamic_cast<ZBBPStopSymbol*>(pComp)->SetUnitCost(dynamic_cast<ZBSymbol*>(pComp)->RetrieveUnitCost(dynamic_cast<ZBBPStopSymbol*>(pComp)->GetUnitGUID(), bError));
            }

            if (pLog)
            {
                CString message;
                message.Format(IDS_AL_UNITREASSIGNED, dynamic_cast<ZBBPStopSymbol*>(pComp)->GetSymbolName());
                ZBGenericSymbolErrorLine e(message);
                pLog->AddLine(e);
            }
        }
        else if (pComp && ISA(pComp, ZBBPProcedureSymbol) &&
                 !dynamic_cast<ZBBPProcedureSymbol*>(pComp)->GetUnitGUID().IsEmpty() &&
                 (dynamic_cast<ZBBPProcedureSymbol*>(pComp)->GetUnitName().IsEmpty() ||
                  dynamic_cast<ZBBPProcedureSymbol*>(pComp)->GetUnitCost() <= 0))
        {
            if (dynamic_cast<ZBBPProcedureSymbol*>(pComp)->GetUnitName().IsEmpty())
            {
                dynamic_cast<ZBBPProcedureSymbol*>(pComp)->SetUnitName(dynamic_cast<ZBSymbol*>(pComp)->RetrieveUnitName(dynamic_cast<ZBBPProcedureSymbol*>(pComp)->GetUnitGUID(), bError));
            }

            if (dynamic_cast<ZBBPProcedureSymbol*>(pComp)->GetUnitCost() <= 0)
            {
                dynamic_cast<ZBBPProcedureSymbol*>(pComp)->SetUnitCost(dynamic_cast<ZBSymbol*>(pComp)->RetrieveUnitCost(dynamic_cast<ZBBPProcedureSymbol*>(pComp)->GetUnitGUID(), bError));
            }

            if (pLog)
            {
                CString message;
                message.Format(IDS_AL_UNITREASSIGNED, dynamic_cast<ZBBPProcedureSymbol*>(pComp)->GetSymbolName());
                ZBGenericSymbolErrorLine e(message);
                pLog->AddLine(e);
            }
        }

        // If has child model
        if (pComp && ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() && !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // and recalculate its model also
            reinterpret_cast<ZDProcessGraphModelMdlBP*>(((ZBSymbol*)pComp)->GetChildModel())->ReassignUnit(pLog);
        }
    }

    // Process the page set if there is one
    if (m_pPageSet != NULL)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not recalculate page reference of itself
            if (pPage->GetModel() && pPage->GetModel() != this)
            {
                reinterpret_cast<ZDProcessGraphModelMdlBP*>(pPage->GetModel())->ReassignUnit(pLog);
            }
        }
    }
}

void ZDProcessGraphModelMdlBP::ReassignSystem(PSS_Log* pLog /*= NULL*/)
{
    // Not necessary for system now. If we found a problem
    // we will implement the same mecanism as for units
}

void ZDProcessGraphModelMdlBP::RecalculateSymbolReferences()
{
    RecalculatePageReference();
    RecalculateDoorReference();
}

void ZDProcessGraphModelMdlBP::RecalculatePageReference()
{
    CODComponentSet* pSet = GetComponents();
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent*    pComp = pSet->GetAt(i);

        // If a page symbol
        if (pComp && ISA(pComp, ZBBPPageSymbol))
        {
            // Call the symbol function used to recalculate the page reference
            reinterpret_cast<ZBBPPageSymbol*>(pComp)->RecalculateTwinPageReference(pRootModel);
        }

        // If has child model
        if (pComp && ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() && !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // and recalculate its model also
            reinterpret_cast<ZDProcessGraphModelMdlBP*>(((ZBSymbol*)pComp)->GetChildModel())->RecalculatePageReference();
        }
    }

    // Process the page set if there is one
    if (m_pPageSet != NULL)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not recalculate page reference of itself
            if (pPage->GetModel() && pPage->GetModel() != this)
            {
                reinterpret_cast<ZDProcessGraphModelMdlBP*>(pPage->GetModel())->RecalculatePageReference();
            }
        }
    }
}

void ZDProcessGraphModelMdlBP::RecalculateDoorReference()
{
    CODComponentSet* pSet = GetComponents();
    PSS_ProcessGraphModelMdl* pRootModel = GetRoot();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent*    pComp = pSet->GetAt(i);

        // If a page symbol
        if (pComp && ISA(pComp, ZBBPDoorSymbol))
        {
            // Call the symbol function used to recalculate the page reference
            reinterpret_cast<ZBBPDoorSymbol*>(pComp)->RecalculateTwinDoorReference(pRootModel);
        }

        // If has child model
        if (pComp && ISA(pComp, ZBSymbol) &&
            ((ZBSymbol*)pComp)->GetChildModel() && !((ZBSymbol*)pComp)->IsChildModelRef())
        {
            // and recalculate its model also
            reinterpret_cast<ZDProcessGraphModelMdlBP*>(((ZBSymbol*)pComp)->GetChildModel())->RecalculateDoorReference();
        }
    }

    // Process the page set if there is one
    if (m_pPageSet != NULL)
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator i(m_pPageSet);

        for (ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext())
        {
            // Do not recalculate page reference of itself
            if (pPage->GetModel() && pPage->GetModel() != this)
            {
                reinterpret_cast<ZDProcessGraphModelMdlBP*>(pPage->GetModel())->RecalculateDoorReference();
            }
        }
    }
}

// JMR-MODIF - Le 5 novembre 2006 - Ajout du paramètre ModelIsClean.
bool ZDProcessGraphModelMdlBP::CheckModelWorkflow(PSS_Log* pLog, BOOL ModelIsClean)
{
    // Reset the recursion counter
    m_RecursionCounter = 0;
    m_IsInRecursion = false;

    ZUCheckSymbolConsistency SymbolConsistency(this, pLog);
    SymbolConsistency.CheckSymbol(*this, ModelIsClean);

    // Reset the array of pointer
    RemoveAllSymbolInParsedArray();

    return false;
}

bool ZDProcessGraphModelMdlBP::GenerateModelWorkflow(PSS_Log* pLog, PSS_ProcessGraphModelDoc* pDoc)
{
    ASSERT(FALSE); // TODO : not now implemented
    return false;
}

ZBInputAttributeManager* ZDProcessGraphModelMdlBP::AllocateInputAttributes(bool DeleteExisting /*= false*/)
{
    if (GetRoot() == this)
    {
        if (m_InputAttributes && DeleteExisting)
        {
            delete m_InputAttributes;
            m_InputAttributes = NULL;
        }

        m_InputAttributes = new ZBInputAttributeManager;

        return m_InputAttributes;
    }

    return dynamic_cast<ZDProcessGraphModelMdlBP*>(GetRoot())->AllocateInputAttributes(DeleteExisting);
}

ZBDistributionAttributeManager* ZDProcessGraphModelMdlBP::AllocateDistributionAttributes(bool DeleteExisting /*= false*/)
{
    if (GetRoot() == this)
    {
        if (m_pDistributionAttributes && DeleteExisting)
        {
            delete m_pDistributionAttributes;
            m_pDistributionAttributes = NULL;
        }

        m_pDistributionAttributes = new ZBDistributionAttributeManager;

        return m_pDistributionAttributes;
    }

    return dynamic_cast<ZDProcessGraphModelMdlBP*>(GetRoot())->AllocateDistributionAttributes(DeleteExisting);
}

void ZDProcessGraphModelMdlBP::Serialize(CArchive& ar)
{
    PSS_ProcessGraphModelMdl::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE(_T("ZDProcessGraphModelMdl::Serialize : Start Save\n"));

        // Serialize the input attributes only for the root model
        if (GetRoot() == this)
        {
            ar << (int)1;
            ar << m_InputAttributes;
            ar << m_pDistributionAttributes;
        }
        else
        {
            ar << (int)0;
        }

        TRACE(_T("ZDProcessGraphModelMdl::Serialize : End Save\n"));
    }
    else
    {
        TRACE(_T("ZDProcessGraphModelMdl::Serialize : Start Read\n"));

        // Serialize the input attributes
        if (ar.m_pDocument &&
            dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 21)
        {
            int Value;
            ar >> Value;

            if (Value == 1)
            {
                ar >> (CObject*&)m_InputAttributes;
                ar >> (CObject*&)m_pDistributionAttributes;
            }
        }

        TRACE(_T("ZDProcessGraphModelMdl::Serialize : End Read\n"));
    }
}
