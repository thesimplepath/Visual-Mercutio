/****************************************************************************
 * ==> PSS_SoapPublishModelDefinition --------------------------------------*
 ****************************************************************************
 * Description : Publish the model definition to Messenger through a SOAP   *
 *               protocol, and check the publication validity               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SoapPublishModelDefinition.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_ODSymbolManipulator.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "zProperty\PSS_DynamicPropertiesManager.h"
#include "zSOAP\PSS_SoapData_Settings.h"
#include "PSS_ProcessGraphModelMdlBP.h"
#include "PSS_PublishMessengerModelInformation.h"
#include "PSS_DoorSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "PSS_StopSymbolBP.h"
#include "PSS_DeliverableLinkSymbolBP.h"
#include "PSS_InputAttributes.h"
#include "PSS_DistributionAttributes.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_SoapPublishModelDefinition
//---------------------------------------------------------------------------
PSS_SoapPublishModelDefinition::PSS_SoapPublishModelDefinition(PSS_PublishMessengerModelInformation* pInfo,
                                                               PSS_ProcessGraphModelMdl*             pModel,
                                                               void*                                 pClass) :
    PSS_ProcessNavigation(pModel, pClass),
    m_pInfo(pInfo),
    m_pDoc(NULL),
    m_CounterRow(0)
{
    m_PubMdl.AddAlias(m_pInfo->m_MessengerAlias);
}
//---------------------------------------------------------------------------
PSS_SoapPublishModelDefinition::~PSS_SoapPublishModelDefinition()
{}
//---------------------------------------------------------------------------
int PSS_SoapPublishModelDefinition::GetParentSymbolReference(PSS_Symbol*               pSymbol,
                                                             int                       parentID,
                                                             PSS_ProcessGraphModelMdl* pParentModel)
{
    if (!pSymbol)
        return 0;

    // no parent model, start from root
    if (!pParentModel)
        pParentModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetOwnerModel())->GetRoot();

    // parent model still not found?
    if (!pParentModel)
        return 0;

    // get page set from model controller
    PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pSet = pParentModel->GetPageSet();

    if (!pSet)
        return 0;

    PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(pSet);

    // iterate through model controller children pages
    for (PSS_ProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
    {
        // get page model
        PSS_ProcessGraphModelMdlBP* pPageModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pPage->GetModel());

        if (!pPageModel)
            continue;

        // get model symbols
        CODComponentSet* pCompSet = pPageModel->GetComponents();

        if (!pCompSet)
            continue;

        const SEC_INT compSetCount = pCompSet->GetSize();

        // iterate through model symbols
        for (SEC_INT i = 0; i < compSetCount; ++i)
        {
            // get component set
            CODComponent* pComponent = pCompSet->GetAt(i);

            // get process symbol
            PSS_ProcessSymbolBP* pCompProcSym = dynamic_cast<PSS_ProcessSymbolBP*>(pComponent);

            // found it?
            if (pCompProcSym)
            {
                // get process child model
                PSS_ProcessGraphModelMdlBP* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pCompProcSym->GetModel());

                // search a matching symbol in the process model children
                const int result = GetParentSymbolReference(pSymbol,
                                                            pCompProcSym->GetSymbolReferenceNumber(),
                                                            pChildModel);

                // check if a result was found, return it if yes
                if (result)
                    return result;
            }

            // get symbol
            PSS_Symbol* pCompSym = dynamic_cast<PSS_Symbol*>(pComponent);

            // if the found component symbol is identical to the given one, return the parent ID
            if (pCompSym && pCompSym->GetSymbolReferenceNumber() == pSymbol->GetSymbolReferenceNumber())
                return parentID;
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnStart()
{
    if (!m_pClass)
        return false;

    // get the document and Messenger address to publish to
    PSS_PublishMessengerModelInformation* pInfo = static_cast<PSS_PublishMessengerModelInformation*>(m_pClass);
    m_pDoc                                      = pInfo->m_pDoc;
    m_MessengerAddress                          = pInfo->m_MessengerAddress;

    // copy the publication address from source info
    PSS_SoapData_Settings::m_Url = (const char*)m_MessengerAddress;

    // reset the counter for rows
    m_CounterRow = 0;

    if (!m_pDoc)
        return false;

    // publish the model definition
    m_PubMdl.SetModel(PSS_SoapData_Model(PSS_String16(m_pModel->GetModelName()),
                                         PSS_String16(m_pDoc->GetGUID()),
                                         PSS_String16(pInfo->m_BeginDate),
                                         PSS_String16(pInfo->m_EndDate)));

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnFinish()
{
    if (!m_pDoc)
        return false;

    PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pDoc->GetModel());

    if (!pModel)
        return false;

    PSS_InputAttributeManager* pInputAttrManager = pModel->GetInputAttributes();

    // publish the input attributes
    if (pInputAttrManager)
    {
        PSS_InputAttributeManager::IInputAttributeIterator it(&pInputAttrManager->GetInputAttributeSet());

        // iterate through attributes to publish
        for (PSS_InputAttribute* pInputAttrib = it.GetFirst(); pInputAttrib; pInputAttrib = it.GetNext())
        {
            // build the attribute key (to find it in attributes array)
            const short left  = pInputAttrib->GetCategoryID() & 0x0000FFFF;
            const short right = pInputAttrib->GetItemID()     & 0x0000FFFF;
            const int   key   = (left << 16) | right;

            // log the newly added attribute content
            if (m_pLog && m_pLog->IsInDebugMode())
            {
                CString message;
                message.Format(IDS_AL_PUBLISHINPUTATTRIBUTE,
                                pInputAttrib->GetSymbolRef(),
                                key,
                                (const char*)pInputAttrib->GetDefaultValue());
                PSS_GenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            // publish the attribute
            m_PubMdl.Add(PSS_SoapData_Input(pInputAttrib->GetSymbolRef(),
                                            key,
                                            PSS_String16(pInputAttrib->GetDefaultValue()),
                                            pInputAttrib->GetFlag(),
                                           -1));
        }
    }

    // publish the distribution attributes
    if (pModel && pModel->HasDistributionAttributes())
    {
        PSS_DistributionAttributeManager* pDistribManager = pModel->GetDistributionAttributes();

        if (pDistribManager)
        {
            PSS_DistributionAttributeManager::IDistributionAttributeIterator itAttrib (&pDistribManager->GetDistributionAttributeSet());

            // iterate through distribution attributes
            for (PSS_DistributionAttribute* pAttrib = itAttrib.GetFirst(); pAttrib; pAttrib = itAttrib.GetNext())
            {
                PSS_DistributionAttribute::IDistributionRulesForRoleIterator itRole(&pAttrib->GetDistributionRulesForRoleSet());

                // iterate through roles
                for (PSS_DistributionRulesForRole* pRole = itRole.GetFirst(); pRole; pRole = itRole.GetNext())
                {
                    PSS_DistributionRuleManager::IDistributionRuleIterator itRule(&pRole->GetDistributionRuleset());

                    // iterate through rules
                    for (PSS_DistributionRule* pDistribRule = itRule.GetFirst(); pDistribRule; pDistribRule = itRule.GetNext())
                    {
                        // build the attribute key (to find it in attributes array)
                        const short left  = pAttrib->GetCategoryID() & 0x0000FFFF;
                        const short right = pAttrib->GetItemID()     & 0x0000FFFF;
                        const int   key   = (left << 16) | right;

                        // log the newly added attribute role content
                        if (m_pLog && m_pLog->IsInDebugMode())
                        {
                            CString message;
                            message.Format(IDS_AL_PUBLISHDISTRIBATTRIBUTE,
                                           (const char*)pRole->GetRoleGUID(),
                                           key,
                                           pDistribRule->GetOperator(),
                                           (const char*)pDistribRule->GetValue());
                            PSS_GenericSymbolErrorLine e(message);
                            m_pLog->AddLine(e);
                        }

                        // publish the attribute role
                        m_PubMdl.Add(PSS_SoapData_Distribution(PSS_String16(pRole->GetRoleGUID()),
                                                               key,
                                                               pDistribRule->GetOperator(),
                                                               PSS_String16(pDistribRule->GetValue())));

                        // log the newly added attribute content
                        if (m_pLog && m_pLog->IsInDebugMode())
                        {
                            CString message;
                            message.Format(IDS_AL_PUBLISHDISTRIBATTRIBUTEMAP,
                                           pAttrib->GetSymbolRef(),
                                           key,
                                           (const char*)pDistribRule->GetValue(),
                                           pDistribRule->GetLogicalOperator());
                            PSS_GenericSymbolErrorLine e(message);
                            m_pLog->AddLine(e);
                        }

                        // publish the attribute
                        m_PubMdl.Add(PSS_SoapData_DistributionMap(pAttrib->GetSymbolRef(),
                                                                  key,
                                                                  PSS_String16(pDistribRule->GetValue()),
                                                                  pDistribRule->GetLogicalOperator()));
                    }
                }
            }
        }
    }
 
    // send published attributes to the soap server
    return m_PubMdl.Send();
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnDoorSymbol(PSS_DoorSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnPageSymbol(PSS_PageSymbolBP* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    if (!pSymbol)
        return false;

    // publish the symbol
    m_PubMdl.Add(PSS_SoapData_Process(pSymbol->GetSymbolReferenceNumber(),
                                      PSS_String16(pSymbol->GetUnitGUID()),
                                      2,
                                      pSymbol->GetUnitDoubleValidationType(),
                                      GetParentSymbolReference(pSymbol)));

    PSS_Properties::IPropertySet propSet;

    // get the property set from object
    pSymbol->FillProperties(propSet, true, true);

    // publish the symbol attributes
    Publish(pSymbol->GetSymbolReferenceNumber(), propSet);

    PSS_Properties::IPropertyIterator it(&propSet);

    // delete all now published attributes
    for (PSS_Property*  pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    if (!pSymbol)
        return false;

    // publish the process
    m_PubMdl.Add(PSS_SoapData_Process(pSymbol->GetSymbolReferenceNumber(),
                                      _T(""),
                                      4,
                                      0,
                                      0));

    PSS_Properties::IPropertySet propSet;

    // get the process attributes
    pSymbol->FillProperties(propSet, true, true);

    // publish the process attributes
    Publish(pSymbol->GetSymbolReferenceNumber(), propSet);

    PSS_Properties::IPropertyIterator it(&propSet);

    // delete all now published attributes
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    if (!pSymbol)
        return false;

    // publish the start symbol
    m_PubMdl.Add(PSS_SoapData_Process(pSymbol->GetSymbolReferenceNumber(),
                                      PSS_String16(pSymbol->GetUnitGUID()),
                                      0,
                                      0,
                                      GetParentSymbolReference(pSymbol)));

    PSS_Properties::IPropertySet propSet;

    // get the start symbol attributes
    pSymbol->FillProperties(propSet, true, true);

    // publish the start symbol attributes
    Publish(pSymbol->GetSymbolReferenceNumber(), propSet);

    PSS_Properties::IPropertyIterator it(&propSet);

    // delete all now published attributes
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext() )
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    if (!pSymbol)
        return false;

    // publish the stop symbol
    m_PubMdl.Add(PSS_SoapData_Process(pSymbol->GetSymbolReferenceNumber(),
                                      PSS_String16(pSymbol->GetUnitGUID()),
                                      1,
                                      0,
                                      GetParentSymbolReference(pSymbol)));

    PSS_Properties::IPropertySet propSet;

    // get the end symbol attributes
    pSymbol->FillProperties(propSet, true, true);

    // publish the end symbol attributes
    Publish(pSymbol->GetSymbolReferenceNumber(), propSet);

    PSS_Properties::IPropertyIterator it(&propSet);

    // delete all now published attributes
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
{
    if (!pSymbol)
        return false;

    CODSymbolComponent* pSrc = pSymbol->GetEnteringSymbol();
    CODSymbolComponent* pDst = pSymbol->GetFollowingSymbol();

    // get the source symbol as a door or a page
    PSS_DoorSymbolBP* pSrcDoor = dynamic_cast<PSS_DoorSymbolBP*>(pSrc);
    PSS_PageSymbolBP* pSrcPage = dynamic_cast<PSS_PageSymbolBP*>(pSrc);

    // replace the source symbol by the symbol after the page or the door
    if (pSrcDoor)
    {
        // if the deliverable is a reference, skip it
        if (!pSymbol->IsLocal())
            return true;

        PSS_DoorSymbolBP* pTwinDoor = pSrcDoor->GetTwinDoorSymbol();

        if (!pTwinDoor)
            return true;

        CODNodeArray followingNodes;
        pTwinDoor->GetEnteringSymbols_Up(followingNodes);

        const std::size_t followingSymbolCount =
                PSS_ODSymbolManipulator::KeepOnlySymbolsISA(followingNodes, RUNTIME_CLASS(PSS_Symbol));

        if (!followingSymbolCount)
            return true;

        ASSERT(followingNodes.GetSize() > 0);
        IODNode* pINode = followingNodes.GetAt(0);
        pSrc = static_cast<CODSymbolComponent*>(pINode);
    }
    else
    if (pSrcPage)
    {
        // if the deliverable is a reference, skip it
        if (!pSymbol->IsLocal())
            return true;

        PSS_PageSymbolBP* pTwinPage = pSrcPage->GetTwinPageSymbol();

        if (!pTwinPage)
            return true;

        CODNodeArray followingNodes;
        pTwinPage->GetEnteringSymbols_Up(followingNodes);

        std::size_t followingSymbolCount =
                PSS_ODSymbolManipulator::KeepOnlySymbolsISA(followingNodes, RUNTIME_CLASS(PSS_Symbol));

        if (!followingSymbolCount)
            return true;

        ASSERT(followingNodes.GetSize() > 0);
        IODNode* pINode = followingNodes.GetAt(0);
        pSrc = static_cast<CODSymbolComponent*>(pINode);
    }

    // get the destination symbol as a door or a page
    PSS_DoorSymbolBP* pDstDoor = dynamic_cast<PSS_DoorSymbolBP*>(pDst);
    PSS_PageSymbolBP* pDstPage = dynamic_cast<PSS_PageSymbolBP*>(pDst);

    // Now replace the destination symbol by the symbol after the page or the door
    if (pDstDoor)
    {
        // if the deliverable is a reference, skip it
        if (!pSymbol->IsLocal())
            return true;

        PSS_DoorSymbolBP* pTwinDoor = pDstDoor->GetTwinDoorSymbol();

        if (!pTwinDoor)
            return true;

        CODNodeArray followingNodes;
        pTwinDoor->GetFollowingSymbols_Down(followingNodes);

        std::size_t followingSymbolCount =
                PSS_ODSymbolManipulator::KeepOnlySymbolsISA(followingNodes, RUNTIME_CLASS(PSS_Symbol));

        if (!followingSymbolCount)
            return true;

        ASSERT(followingNodes.GetSize() > 0);
        IODNode* pINode = followingNodes.GetAt(0);
        pDst = static_cast<CODSymbolComponent*>(pINode);
    }
    else
    if (pDstPage)
    {
        // if the deliverable is a reference, skip it
        if (!pSymbol->IsLocal())
            return true;

        PSS_PageSymbolBP* pTwinPage = pDstPage->GetTwinPageSymbol();

        if (!pTwinPage)
            return true;

        CODNodeArray followingNodes;
        pTwinPage->GetFollowingSymbols_Down(followingNodes);

        const std::size_t followingSymbolCount =
                PSS_ODSymbolManipulator::KeepOnlySymbolsISA(followingNodes, RUNTIME_CLASS(PSS_Symbol));

        if (!followingSymbolCount)
            return true;

        ASSERT(followingNodes.GetSize() > 0);
        IODNode* pINode = followingNodes.GetAt(0);
        pDst = static_cast<CODSymbolComponent*>(pINode);
    }

    bool lateral          = false;
    int  lateralDirection = 0;

    PSS_Symbol* pSrcSymbol = dynamic_cast<PSS_Symbol*>(pSrc);
    ASSERT(pSrcSymbol);

    // get right edges
    CODEdgeArray      leavingRightEdges;
    const std::size_t leavingRightLinkCount = pSrcSymbol->GetEdgesLeaving_Right(leavingRightEdges);

    // iterate through edges and find right one
    for (std::size_t edgeIndex = 0; edgeIndex < leavingRightLinkCount; ++edgeIndex)
    {
        // get next edge
        IODEdge*                     pIEdge = leavingRightEdges.GetAt(edgeIndex);
        PSS_DeliverableLinkSymbolBP* pLink  = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

        if (!pLink)
            continue;

        // found a right edge?
        if (pLink->GetSymbolName() == pSymbol->GetSymbolName())
        {
            lateral          = true;
            lateralDirection = 1;
            break;
        }
    }

    CODEdgeArray      leavingLeftEdges;
    const std::size_t leavingLeftLinkCount = pSrcSymbol->GetEdgesLeaving_Left(leavingLeftEdges);

    // should search for left edge?
    if (leavingLeftLinkCount  && !lateral)
        // iterate through edges and find left one
        for (std::size_t edgeIndex = 0; edgeIndex < leavingLeftLinkCount; ++edgeIndex)
        {
            IODEdge*                     pIEdge = leavingLeftEdges.GetAt(edgeIndex);
            PSS_DeliverableLinkSymbolBP* pLink  = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

            if (!pLink)
                continue;

            // found a left edge?
            if (pLink->GetSymbolName() == pSymbol->GetSymbolName())
            {
                lateral          = true;
                lateralDirection = 3;    
                break;
            }
        }

    PSS_Symbol* pDstSymbol = dynamic_cast<PSS_Symbol*>(pDst);

    // publish the deliverable link symbol
    m_PubMdl.Add(PSS_SoapData_Deliverable(pSymbol->GetSymbolReferenceNumber(),
                                          pSrcSymbol ? pSrcSymbol->GetSymbolReferenceNumber() : -1,
                                          pDstSymbol ? pDstSymbol->GetSymbolReferenceNumber() : -1,
                                          PSS_String16(pSymbol->GetSymbolName()),
                                          lateral ? 1 : 0,
                                          lateralDirection,
                                          pSymbol->GetUnitDoubleValidationType()));

    PSS_Properties::IPropertySet propSet;

    // get the deliverable link symbol attributes
    pSymbol->FillProperties(propSet, true, true);

    // publish the deliverable link symbol attributes
    Publish(pSymbol->GetSymbolReferenceNumber(), propSet);

    PSS_Properties::IPropertyIterator it(&propSet);

    // delete all now published attributes
    for (PSS_Property*  pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
void PSS_SoapPublishModelDefinition::Publish(int ref, const PSS_Properties::IPropertySet& propSet)
{
    PSS_Properties::IPropertyIterator it(&propSet);

    // publish all properties
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        Publish(ref, pProp);
}
//---------------------------------------------------------------------------
void PSS_SoapPublishModelDefinition::Publish(int ref, PSS_Property* pProp)
{
    if (!pProp)
        return;

    // build the property key (to find it in properties array)
    const short left  = pProp->GetCategoryID() & 0x0000FFFF;
    const short right = pProp->GetItemID()     & 0x0000FFFF;
    const int   key   = (left << 16) | right;

    CString s;

    // search for the property value type
    switch (pProp->GetValueType())
    {
        case PSS_Property::IE_VT_Double:   s.Format(_T("%g"), pProp->GetValueDouble());                  break;
        case PSS_Property::IE_VT_Float:    s.Format(_T("%f"), pProp->GetValueFloat());                   break;
        case PSS_Property::IE_VT_Date:     s = pProp->GetValueDate().GetStandardFormattedDate();         break;
        case PSS_Property::IE_VT_TimeSpan: s = pProp->GetValueTimeSpan().GetStandardFormattedTimeSpan(); break;
        case PSS_Property::IE_VT_Duration: s.Format(_T("%f"), double(pProp->GetValueDuration()));        break;
        default:                           s = pProp->GetValueString();                                  break;
    }

    // log property content
    if (m_pLog && m_pLog->IsInDebugMode())
    {
        CString message;
        message.Format(IDS_AL_PUBLISHSYMBOLATTRIBUTE,
                       ref,
                       key,
                       (const char*)s,
                       pProp->IsDynamic() ? 0 : 1);
        PSS_GenericSymbolErrorLine e(message);
        m_pLog->AddLine(e);
    }

    // publish property
    m_PubMdl.Add(PSS_SoapData_SymbolAttributes(ref,                          // object ref ID (either a proc or deliv)
                                               m_CounterRow,                 // row number
                                               key,                          // ref on attribute definition table
                                               PSS_String16(s),              // value
                                               pProp->IsDynamic() ? 0 : 1));
    ++m_CounterRow;
}
//---------------------------------------------------------------------------
