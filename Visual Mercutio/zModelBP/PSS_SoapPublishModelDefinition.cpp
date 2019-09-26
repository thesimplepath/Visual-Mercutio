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
#include "zModel\ProcGraphModelDoc.h"
#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "zModel\ZUODSymbolManipulator.h"
#include "zProperty\ZBDynamicPropertiesManager.h"
#include "zSOAP\PSS_SoapData_Settings.h"
#include "ProcGraphModelMdlBP.h"
#include "ZBPublishMessengerModelInformation.h"
#include "ZBBPDoorSymbol.h"
#include "ZBBPPageSymbol.h"
#include "ZBBPProcedureSymbol.h"
#include "ZBBPProcessSymbol.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"
#include "ZBDeliverableLinkSymbol.h"
#include "ZBInputAttributes.h"
#include "ZBDistributionAttributes.h"
#include "zBaseLib\ZILog.h"
#include "zModel\ZBGenericSymbolErrorLine.h"

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
PSS_SoapPublishModelDefinition::PSS_SoapPublishModelDefinition(ZBPublishMessengerModelInformation* pInfo,
                                                               ZDProcessGraphModelMdl*             pModel,
                                                               void*                               pClass) :
    ZUProcessNavigation(pModel, pClass),
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
int PSS_SoapPublishModelDefinition::GetParentSymbolReference(ZBSymbol*               pSymbol,
                                                             int                     ParentID,
                                                             ZDProcessGraphModelMdl* pParentModel)
{
    if (!pSymbol)
        return 0;

    // no parent model, start from root
    if (!pParentModel)
        pParentModel = dynamic_cast<ZDProcessGraphModelMdl*>(pSymbol->GetOwnerModel())->GetRoot();

    // parent model still not found?
    if (!pParentModel)
        return 0;

    // get page set from model controller
    ZBProcessGraphPageSet* pSet = pParentModel->GetPageSet();

    if (!pSet)
        return 0;

    ZBProcessGraphPageIterator it(pSet);

    // iterate through model controller children pages
    for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
    {
        // get page model
        ZDProcessGraphModelMdlBP* pPageModel = dynamic_cast<ZDProcessGraphModelMdlBP*>(pPage->GetpModel());

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
            ZBBPProcessSymbol* pCompProcSym = dynamic_cast<ZBBPProcessSymbol*>(pComponent);

            // found it?
            if (pCompProcSym)
            {
                // get process child model
                ZDProcessGraphModelMdlBP* pChildModel = dynamic_cast<ZDProcessGraphModelMdlBP*>(pCompProcSym->GetpModel());

                // search a matching symbol in the process model children
                const int result = GetParentSymbolReference(pSymbol,
                                                            pCompProcSym->GetSymbolReferenceNumber(),
                                                            pChildModel);

                // check if a result was found, return it if yes
                if (result)
                    return result;
            }

            // get symbol
            ZBSymbol* pCompSym = dynamic_cast<ZBSymbol*>(pComponent);

            // if the found component symbol is identical to the given one, return the parent ID
            if (pCompSym && pCompSym->GetSymbolReferenceNumber() == pSymbol->GetSymbolReferenceNumber())
                return ParentID;
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
    ZBPublishMessengerModelInformation* pInfo = static_cast<ZBPublishMessengerModelInformation*>(m_pClass);
    m_pDoc                                    = pInfo->m_pDoc;
    m_MessengerAddress                        = pInfo->m_MessengerAddress;

    // copy the publication address from source info
    PSS_SoapData_Settings::m_Url = (const char*)m_MessengerAddress;

    // reset the counter for rows
    m_CounterRow = 0;

    if (!m_pDoc)
        return false;

    // publish the model definition
    m_PubMdl.SetModel(PSS_SoapData_Model(PSS_String16(m_pModel->GetModelName()), // model name
                                         PSS_String16(m_pDoc->GetGUID()),        // model ref GUID
                                         PSS_String16(pInfo->m_BeginDate),       // start date
                                         PSS_String16(pInfo->m_EndDate)));       // end date

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnFinish()
{
    if (!m_pDoc)
        return false;

    ZDProcessGraphModelMdlBP* pModel = dynamic_cast<ZDProcessGraphModelMdlBP*>(m_pDoc->GetModel());

    if (!pModel)
        return false;

    ZBInputAttributeManager* pInputAttrManager = pModel->GetInputAttributes();

    // publish the input attributes
    if (pInputAttrManager)
    {
        ZBInputAttributeIterator it(&pInputAttrManager->GetInputAttributeSet());

        // iterate through attributes to publish
        for (ZBInputAttribute* pInputAttrib = it.GetFirst(); pInputAttrib; pInputAttrib = it.GetNext())
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
                ZBGenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            // publish the attribute
            m_PubMdl.Add(PSS_SoapData_Input(pInputAttrib->GetSymbolRef(),                  //  object ID (proc or deliv) or -1 for global
                                            key,                                           //  attrib def ID
                                            PSS_String16(pInputAttrib->GetDefaultValue()), //  default value
                                            pInputAttrib->GetFlag(),                       //  flag
                                           -1));                                           // -1 (reserved for future use)
        }
    }

    // publish the distribution attributes
    if (pModel && pModel->HasDistributionAttributes())
    {
        ZBDistributionAttributeManager* pDistribManager = pModel->GetDistributionAttributes();

        if (pDistribManager)
        {
            ZBDistributionAttributeIterator itAttrib(&pDistribManager->GetDistributionAttributeSet());

            // iterate through distribution attributes
            for (ZBDistributionAttribute* pAttrib = itAttrib.GetFirst(); pAttrib; pAttrib = itAttrib.GetNext())
            {
                ZBDistributionRulesForRoleIterator itRole(&pAttrib->GetDistributionRulesForRoleSet());

                // iterate through roles
                for (ZBDistributionRulesForRole* pRole = itRole.GetFirst(); pRole; pRole = itRole.GetNext())
                {
                    ZBDistributionRuleIterator itRule(&pRole->GetDistributionRuleSet());

                    // iterate through rules
                    for (ZBDistributionRule* pDistribRule = itRule.GetFirst(); pDistribRule; pDistribRule = itRule.GetNext())
                    {
                        // build the attribute key (to find it in attributes array)
                        const short left    = pAttrib->GetCategoryID() & 0x0000FFFF;
                        const short right   = pAttrib->GetItemID()     & 0x0000FFFF;
                        const int   key     = (left << 16) | right;

                        // log the newly added attribute role content
                        if (m_pLog && m_pLog->IsInDebugMode())
                        {
                            CString message;
                            message.Format(IDS_AL_PUBLISHDISTRIBATTRIBUTE,
                                           (const char*)pRole->GetRoleGUID(),
                                           key,
                                           pDistribRule->GetOperator(),
                                           (const char*)pDistribRule->GetValue());
                            ZBGenericSymbolErrorLine e(message);
                            m_pLog->AddLine(e);
                        }

                        // publish the attribute role
                        m_PubMdl.Add(PSS_SoapData_Distribution(PSS_String16(pRole->GetRoleGUID()),       // wkGrpClsID
                                                               key,                                      // attrib def ID
                                                               pDistribRule->GetOperator(),              // operator ID
                                                               PSS_String16(pDistribRule->GetValue()))); // data

                        // log the newly added attribute content
                        if (m_pLog && m_pLog->IsInDebugMode())
                        {
                            CString message;
                            message.Format(IDS_AL_PUBLISHDISTRIBATTRIBUTEMAP,
                                           pAttrib->GetSymbolRef(),
                                           key,
                                           (const char*)pDistribRule->GetValue(),
                                           pDistribRule->GetLogicalOperator());
                            ZBGenericSymbolErrorLine e(message);
                            m_pLog->AddLine(e);
                        }

                        // publish the attribute
                        m_PubMdl.Add(PSS_SoapData_DistributionMap(pAttrib->GetSymbolRef(),                // object ID
                                                                  key,                                    // attrib def ID
                                                                  PSS_String16(pDistribRule->GetValue()), // data
                                                                  pDistribRule->GetLogicalOperator()));   // logical operator (0 = AND, 1 = OR)
                    }
                }
            }
        }
    }
 
    // send published attributes to the soap server
    return m_PubMdl.Send();
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnDoorSymbol(ZBBPDoorSymbol* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnPageSymbol(ZBBPPageSymbol* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnProcedureSymbol(ZBBPProcedureSymbol* pSymbol)
{
    if (!pSymbol)
        return false;

    // publish the symbol
    m_PubMdl.Add(PSS_SoapData_Process(pSymbol->GetSymbolReferenceNumber(),    // object ID (unique between proc/deliv)
                                      PSS_String16(pSymbol->GetUnitGUID()),   // workgroup clsID
                                      2,                                      // 2 = procedure symbol
                                      pSymbol->GetUnitDoubleValidationType(), // double sign
                                      GetParentSymbolReference(pSymbol)));    // parent process

    ZBPropertySet propSet;

    // get the property set from object
    pSymbol->FillProperties(propSet, true, true);

    // publish the symbol attributes
    Publish(pSymbol->GetSymbolReferenceNumber(), propSet);

    ZBPropertyIterator it(&propSet);

    // delete all now published attributes
    for (ZBProperty*  pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnProcessSymbol(ZBBPProcessSymbol* pSymbol)
{
    if (!pSymbol)
        return false;

    // publish the process
    m_PubMdl.Add(PSS_SoapData_Process(pSymbol->GetSymbolReferenceNumber(), // object ID (Unique between proc/deliv)
                                      _T(""),                              // no published GUID for processes
                                      4,                                   // 4 = process symbol
                                      0,                                   // double sign
                                      0));                                 // parent process

    ZBPropertySet propSet;

    // get the process attributes
    pSymbol->FillProperties(propSet, true, true);

    // publish the process attributes
    Publish(pSymbol->GetSymbolReferenceNumber(), propSet);

    ZBPropertyIterator it(&propSet);

    // delete all now published attributes
    for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnStartSymbol(ZBBPStartSymbol* pSymbol)
{
    if (!pSymbol)
        return false;

    // publish the start symbol
    m_PubMdl.Add(PSS_SoapData_Process(pSymbol->GetSymbolReferenceNumber(),  // object ID (unique between proc/deliv)
                                      PSS_String16(pSymbol->GetUnitGUID()), // workgroup ClsID
                                      0,                                    // 0 = start symbol
                                      0,                                    // double sign
                                      GetParentSymbolReference(pSymbol)));  // parent process

    ZBPropertySet propSet;

    // get the start symbol attributes
    pSymbol->FillProperties(propSet, true, true);

    // publish the start symbol attributes
    Publish(pSymbol->GetSymbolReferenceNumber(), propSet);

    ZBPropertyIterator it(&propSet);

    // delete all now published attributes
    for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext() )
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnStopSymbol(ZBBPStopSymbol* pSymbol)
{
    if (!pSymbol)
        return false;

    // publish the stop symbol
    m_PubMdl.Add(PSS_SoapData_Process(pSymbol->GetSymbolReferenceNumber(),  // object ID (unique between proc/deliv)
                                      PSS_String16(pSymbol->GetUnitGUID()), // workgroup clsID
                                      1,                                    // 1 = stop symbol
                                      0,                                    // double sign
                                      GetParentSymbolReference(pSymbol)));  // parent process

    ZBPropertySet propSet;

    // get the end symbol attributes
    pSymbol->FillProperties(propSet, true, true);

    // publish the end symbol attributes
    Publish(pSymbol->GetSymbolReferenceNumber(), propSet);

    ZBPropertyIterator it(&propSet);

    // delete all now published attributes
    for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelDefinition::OnDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol)
{
    if (!pSymbol)
        return false;

    CODSymbolComponent* pSrc = pSymbol->GetEnteringSymbol();
    CODSymbolComponent* pDst = pSymbol->GetFollowingSymbol();

    // get the source symbol as a door or a page
    ZBBPDoorSymbol* pSrcDoor = dynamic_cast<ZBBPDoorSymbol*>(pSrc);
    ZBBPPageSymbol* pSrcPage = dynamic_cast<ZBBPPageSymbol*>(pSrc);

    // replace the source symbol by the symbol after the page or the door
    if (pSrcDoor)
    {
        // if the deliverable is a reference, skip it
        if (!pSymbol->IsLocal())
            return true;

        ZBBPDoorSymbol* pTwinDoor = pSrcDoor->GetTwinDoorSymbol();

        if (!pTwinDoor)
            return true;

        CODNodeArray followingNodes;
        pTwinDoor->GetEnteringSymbols_Up(followingNodes);

        const std::size_t followingSymbolCount =
                ZUODSymbolManipulator::KeepOnlySymbolsISA(followingNodes, RUNTIME_CLASS(ZBSymbol));

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

        ZBBPPageSymbol* pTwinPage = pSrcPage->GetTwinPageSymbol();

        if (!pTwinPage)
            return true;

        CODNodeArray followingNodes;
        pTwinPage->GetEnteringSymbols_Up(followingNodes);

        std::size_t followingSymbolCount =
                ZUODSymbolManipulator::KeepOnlySymbolsISA(followingNodes, RUNTIME_CLASS(ZBSymbol));

        if (!followingSymbolCount)
            return true;

        ASSERT(followingNodes.GetSize() > 0);
        IODNode* pINode = followingNodes.GetAt(0);
        pSrc = static_cast<CODSymbolComponent*>(pINode);
    }

    // get the destination symbol as a door or a page
    ZBBPDoorSymbol* pDstDoor = dynamic_cast<ZBBPDoorSymbol*>(pDst);
    ZBBPPageSymbol* pDstPage = dynamic_cast<ZBBPPageSymbol*>(pDst);

    // Now replace the destination symbol by the symbol after the page or the door
    if (pDstDoor)
    {
        // if the deliverable is a reference, skip it
        if (!pSymbol->IsLocal())
            return true;

        ZBBPDoorSymbol* pTwinDoor = pDstDoor->GetTwinDoorSymbol();

        if (!pTwinDoor)
            return true;

        CODNodeArray followingNodes;
        pTwinDoor->GetFollowingSymbols_Down(followingNodes);

        std::size_t followingSymbolCount =
                ZUODSymbolManipulator::KeepOnlySymbolsISA(followingNodes, RUNTIME_CLASS(ZBSymbol));

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

        ZBBPPageSymbol* pTwinPage = pDstPage->GetTwinPageSymbol();

        if (!pTwinPage)
            return true;

        CODNodeArray followingNodes;
        pTwinPage->GetFollowingSymbols_Down(followingNodes);

        const std::size_t followingSymbolCount =
            ZUODSymbolManipulator::KeepOnlySymbolsISA(followingNodes, RUNTIME_CLASS(ZBSymbol));

        if (!followingSymbolCount)
            return true;

        ASSERT(followingNodes.GetSize() > 0);
        IODNode* pINode = followingNodes.GetAt(0);
        pDst = static_cast<CODSymbolComponent*>(pINode);
    }

    bool lateral          = false;
    int  lateralDirection = 0;

    ZBSymbol* pSrcSymbol = dynamic_cast<ZBSymbol*>(pSrc);
    ASSERT(pSrcSymbol);

    // get right edges
    CODEdgeArray      leavingRightEdges;
    const std::size_t leavingRightLinkCount = pSrcSymbol->GetEdgesLeaving_Right(leavingRightEdges);

    // iterate through edges and find right one
    for (std::size_t edgeIndex = 0; edgeIndex < leavingRightLinkCount; ++edgeIndex)
    {
        // get next edge
        IODEdge*                 pIEdge = leavingRightEdges.GetAt(edgeIndex);
        ZBDeliverableLinkSymbol* pLink  = dynamic_cast<ZBDeliverableLinkSymbol*>(pIEdge);

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
            IODEdge*                 pIEdge = leavingLeftEdges.GetAt(edgeIndex);
            ZBDeliverableLinkSymbol* pLink  = dynamic_cast<ZBDeliverableLinkSymbol*>(pIEdge);

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

    // publish the deliverable link symbol
    m_PubMdl.Add(PSS_SoapData_Deliverable(pSymbol->GetSymbolReferenceNumber(),                       // object ID (unique between proc/deliv)
                                          dynamic_cast<ZBSymbol*>(pSrc)->GetSymbolReferenceNumber(), // src proc
                                          dynamic_cast<ZBSymbol*>(pDst)->GetSymbolReferenceNumber(), // trg proc
                                          PSS_String16(pSymbol->GetSymbolName()),                    // deliv name
                                          lateral ? 1 : 0,                                           // lateral direction: 0 = normal, 1 = lateral starts here
                                          lateralDirection,                                          // 0 = top, 1 = right, 2 = bottom, 3 = left
                                          pSymbol->GetUnitDoubleValidationType()));                  // double sign

    ZBPropertySet propSet;

    // get the deliverable link symbol attributes
    pSymbol->FillProperties(propSet, true, true);

    // publish the deliverable link symbol attributes
    Publish(pSymbol->GetSymbolReferenceNumber(), propSet);

    ZBPropertyIterator it(&propSet);

    // delete all now published attributes
    for (ZBProperty*  pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    return true;
}
//---------------------------------------------------------------------------
void PSS_SoapPublishModelDefinition::Publish(int ref, const ZBPropertySet& propSet)
{
    ZBPropertyIterator it(&propSet);

    // publish all properties
    for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        Publish(ref, pProp);
}
//---------------------------------------------------------------------------
void PSS_SoapPublishModelDefinition::Publish(int ref, ZBProperty* pProp)
{
    if (!pProp)
        return;

    // build the property key (to find it in properties array)
    const short left  = pProp->GetCategoryID() & 0x0000FFFF;
    const short right = pProp->GetItemID()     & 0x0000FFFF;
    const int   key   = (left << 16) | right;

    CString s;

    // search for the property value type
    switch (pProp->GetPTValueType())
    {
        case ZBProperty::PT_DOUBLE:   s.Format(_T("%g"), pProp->GetValueDouble());                 break;
        case ZBProperty::PT_FLOAT:    s.Format(_T("%f"), pProp->GetValueFloat());                  break;
        case ZBProperty::PT_DATE:     s = pProp->GetValueDate().GetStandardFormattedDate();         break;
        case ZBProperty::PT_TIMESPAN: s = pProp->GetValueTimeSpan().GetStandardFormattedTimeSpan(); break;
        case ZBProperty::PT_DURATION: s.Format(_T("%f"), double(pProp->GetValueDuration()));       break;
        default:                      s = pProp->GetValueString();                                 break;
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
        ZBGenericSymbolErrorLine e(message);
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
