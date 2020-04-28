/****************************************************************************
 * ==> PSS_CheckSymbolConsistency ------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to check the symbol consistency       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CheckSymbolConsistency.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_ProcessGraphModelController.h"
#include "zModel\PSS_ODSymbolManipulator.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "PSS_DoorSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "PSS_StopSymbolBP.h"
#include "PSS_DeliverableLinkSymbolBP.h"
#include "PSS_ProcessGraphModelMdlBP.h"
#include "PSS_CheckValidUnit.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_CheckSymbolConsistency
//---------------------------------------------------------------------------
PSS_CheckSymbolConsistency::PSS_CheckSymbolConsistency(PSS_ProcessGraphModelMdl* pModel, PSS_Log* pLog) :
    PSS_BasicSymbolVisitor(),
    m_pModel(pModel),
    m_pLog(pLog),
    m_pIDArray(NULL),
    m_RefIDSize(0),
    m_ErrorCounter(0),
    m_WarningCounter(0),
    m_IsLogging(false)
{}
//---------------------------------------------------------------------------
PSS_CheckSymbolConsistency::~PSS_CheckSymbolConsistency()
{
    // delete the array identifier
    if (m_pIDArray)
        delete[] m_pIDArray;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::CheckSymbol(CODComponent& component, BOOL modelIsClean)
{
    // do log?
    if (m_pLog && m_pLog->InitializeLog())
    {
        // initialize the counters
        m_ErrorCounter   = 0;
        m_WarningCounter = 0;

        m_pLog->ClearLog();
        CString message;
        message.Format(IDS_ZS_START, m_pModel->GetModelName());
        PSS_GenericSymbolErrorLine e(message);
        m_pLog->AddLine(e);

        // add a message if the model was cleaned
        if (modelIsClean)
        {
            message.Format(IDS_ZS_DELETE_CORRUPED_SYMBOLS, m_pModel->GetModelName());
            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }
    }

    // preform a deep check before lauching the calculation of the model
    PSS_CheckValidUnit check(m_pModel);
    check.SetLog(m_pLog);
    check.Navigate();

    // assign the error and warning counters
    m_ErrorCounter   += check.GetErrorCounter();
    m_WarningCounter += check.GetWarningCounter();

    // delete the previous array identifier, if exists
    if (m_pIDArray)
        delete[] m_pIDArray;

    // allocate and reset the identifier array
    m_RefIDSize = 10000;
    m_pIDArray  = new int[m_RefIDSize];
    std::memset(m_pIDArray, 0, m_RefIDSize * sizeof(int));

    CODComponent*             pComponent    = &component;
    PSS_Symbol*               pSymbol       =                      dynamic_cast<PSS_Symbol*>(pComponent);
    PSS_LinkSymbol*           pLinkSymbol   = pSymbol     ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComponent);
    PSS_ProcessGraphModelMdl* pProcGraphMdl = pLinkSymbol ? NULL : dynamic_cast<PSS_ProcessGraphModelMdl*>(pComponent);

    if (pSymbol)
        pSymbol->AcceptVisitor(*this);
    else
    if (pLinkSymbol)
        pLinkSymbol->AcceptVisitor(*this);
    else
    if (pProcGraphMdl)
        pProcGraphMdl->AcceptVisitor(*this);

    // do log?
    if (m_pLog)
    {
        CString message;

        if (m_ErrorCounter > 0 || m_WarningCounter > 0)
            message.Format(IDS_ZS_STOP2, m_ErrorCounter, m_WarningCounter);
        else
            message.LoadString(IDS_ZS_STOP);

        PSS_GenericSymbolErrorLine e(message);
        m_pLog->AddLine(e);
    }

    // delete the identifier array
    if (m_pIDArray)
    {
        delete[] m_pIDArray;
        m_pIDArray = NULL;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::Visit(CODComponent& component)
{
    CODComponent*                pComponent   = &component;
    PSS_ProcedureSymbolBP*       pProcedure   =                       dynamic_cast<PSS_ProcedureSymbolBP*>(pComponent);
    PSS_DeliverableLinkSymbolBP* pDeliverable = pProcedure   ? NULL : dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pComponent);
    PSS_DoorSymbolBP*            pDoor        = pDeliverable ? NULL : dynamic_cast<PSS_DoorSymbolBP*>(pComponent);
    PSS_PageSymbolBP*            pPage        = pDoor        ? NULL : dynamic_cast<PSS_PageSymbolBP*>(pComponent);
    PSS_ProcessSymbolBP*         pProcess     = pPage        ? NULL : dynamic_cast<PSS_ProcessSymbolBP*>(pComponent);
    PSS_StartSymbolBP*           pStart       = pProcess     ? NULL : dynamic_cast<PSS_StartSymbolBP*>(pComponent);
    PSS_StopSymbolBP*            pStop        = pStart       ? NULL : dynamic_cast<PSS_StopSymbolBP*>(pComponent);
    PSS_Symbol*                  pSymbol      = pStop        ? NULL : dynamic_cast<PSS_Symbol*>(pComponent);
    PSS_LinkSymbol*              pLinkSymbol  = pSymbol      ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComponent);


    if (pProcedure)
        return CheckProcedureSymbol(pProcedure);
    else
    if (pDeliverable)
        return CheckDeliverableLinkSymbol(pDeliverable);
    else
    if (pDoor)
        return CheckDoorSymbol(pDoor);
    else
    if (pPage)
        return CheckPageSymbol(pPage);
    else
    if (pProcess)
        return CheckProcessSymbol(pProcess);
    else
    if (pStart)
        return CheckStartSymbol(pStart);
    else
    if (pStop)
        return CheckStopSymbol(pStop);
    else
    if (pSymbol)
        return CheckSymbol(pSymbol);
    else
    if (pLinkSymbol)
        return CheckLink(pLinkSymbol);

    // not a symbol or not needed to be visited
    return false;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::CheckDoorSymbol(PSS_DoorSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // check unique reference number
    CheckUniqueRef(pSymbol);

    // check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // get the following nodes
    CODNodeArray      followingNodes;
    const std::size_t followingSymbolCount = pSymbol->GetFollowingSymbols(followingNodes);

    // get the entering nodes
    CODNodeArray      enteringNodes;
    const std::size_t enteringSymbolCount = pSymbol->GetEnteringSymbols(enteringNodes);

    if (followingSymbolCount > 1)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_DOOR_INC_OUT_1,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    if (enteringSymbolCount > 1)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_DOOR_INC_IN_1,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    if (followingSymbolCount < 1 && enteringSymbolCount < 1)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_DOOR_INC_IN_2,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    if (!pSymbol->GetTwinDoorSymbol())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_DOOR_INC_IN_3,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::CheckPageSymbol(PSS_PageSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // check unique reference number
    CheckUniqueRef(pSymbol);

    // check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // get the following nodes
    CODNodeArray      followingNodes;
    const std::size_t followingSymbolCount = pSymbol->GetFollowingSymbols(followingNodes);

    // Retreiving entering nodes
    CODNodeArray      enteringNodes;
    const std::size_t enteringSymbolCount = pSymbol->GetEnteringSymbols(enteringNodes);

    if (followingSymbolCount > 1)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PAGE_INC_OUT_1,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    if (enteringSymbolCount > 1)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PAGE_INC_IN_1,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    if (followingSymbolCount < 1 && enteringSymbolCount < 1)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PAGE_INC_IN_2,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    if (!pSymbol->GetTwinPageSymbol())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PAGE_INC_IN_3,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::CheckProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // check unique reference number
    CheckUniqueRef(pSymbol);

    // check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // get the up nodes
    CODNodeArray upNodes;
    std::size_t  upSymbolCount = pSymbol->GetFollowingSymbols_Up(upNodes);

    // impossible to have following symbols connected from the top side
    if (upSymbolCount > 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_1,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // get the left nodes
    CODNodeArray      leftNodes;
    const std::size_t followingLeftSymbolCount = pSymbol->GetFollowingSymbols_Left(leftNodes);

    if (followingLeftSymbolCount > 0)
    {
        if (PSS_ODSymbolManipulator::HasSymbolsISA(leftNodes, RUNTIME_CLASS(PSS_ProcessSymbolBP)))
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_3,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath(),
                                             -1,
                                             1);
                m_pLog->AddLine(e);
            }

            // increment the error counter
            ++m_ErrorCounter;
        }
    }

    // check the entering left symbols
    const std::size_t enteringLeftSymbolCount = pSymbol->GetEnteringSymbols_Left(leftNodes);

    if (enteringLeftSymbolCount > 0)
    {
        if (PSS_ODSymbolManipulator::HasSymbolsISA(leftNodes, RUNTIME_CLASS(PSS_ProcessSymbolBP)))
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_3,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath(),
                                            -1,
                                             1);
                m_pLog->AddLine(e);
            }

            // increment the error counter
            ++m_ErrorCounter;
        }
    }

    // check if the leaving count matches with the entering left symbol count
    if (followingLeftSymbolCount != enteringLeftSymbolCount)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_2,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }

    // get the right nodes
    CODNodeArray      rightNodes;
    const std::size_t followingRightSymbolCount = pSymbol->GetFollowingSymbols_Right(rightNodes);

    if (followingRightSymbolCount > 0)
    {
        if (PSS_ODSymbolManipulator::HasSymbolsISA(rightNodes, RUNTIME_CLASS(PSS_ProcessSymbolBP)))
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_3,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath(),
                                            -1,
                                             1);
                m_pLog->AddLine(e);
            }

            // increment the error counter
            ++m_ErrorCounter;
        }
    }

    // check entering symbol
    const std::size_t enteringRightSymbolCount = pSymbol->GetEnteringSymbols_Right(rightNodes);

    if (enteringRightSymbolCount > 0)
    {
        if (PSS_ODSymbolManipulator::HasSymbolsISA(rightNodes, RUNTIME_CLASS(PSS_ProcessSymbolBP)))
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_3,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath(),
                                            -1,
                                             1);
                m_pLog->AddLine(e);
            }

            // increment the error counter
            ++m_ErrorCounter;
        }
    }

    // check if leaving count matches with the entering rigth symbol count
    if (followingRightSymbolCount != enteringRightSymbolCount)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_7,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }

    // get the entering up nodes
    upSymbolCount = pSymbol->GetEnteringSymbols_Up(upNodes);

    // check if a process is attached to it
    if (upSymbolCount > 0 && PSS_ODSymbolManipulator::HasSymbolsISA(upNodes, RUNTIME_CLASS(PSS_ProcessSymbolBP)))
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_3,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // check if at least one following symbol is defined
    if (upSymbolCount <= 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_6,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }
    else
    {
        // check if some deliverables are defined in a combination and are not still connected to the procedure
        CString enteringUpDeliverables;
        pSymbol->GetEnteringUpDeliverable(enteringUpDeliverables);

        const int combCounter = pSymbol->GetCombinationCount();

        for (int i = 0; i < combCounter; ++i)
        {
            // check if the master exists in the list of deliverables
            PSS_Tokenizer masterToken(enteringUpDeliverables);
            const CString master = pSymbol->GetCombinationMaster(i);

            if (!master.IsEmpty() && !masterToken.TokenExist(master))
            {
                // if not, error
                if (m_pLog)
                {
                    CString str;
                    str.Format(IDS_EL_PROCEDURE_INC_9, (const char*)master, pSymbol->GetCombinationName(i));
                    PSS_GenericSymbolErrorLine e(str, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 1);
                    m_pLog->AddLine(e);
                }

                // increment the error counter
                ++m_ErrorCounter;
            }

            PSS_Tokenizer delivToken;
            CString       delivComb = delivToken.GetFirstToken(pSymbol->GetCombinationDeliverables(i));

            // iterate through all combination's deliverables and check that all deliverables are attached
            while (!delivComb.IsEmpty())
            {
                // check if the combination's deliverable exists in the entering deliverables
                if (!masterToken.TokenExist(delivComb))
                {
                    // if not, error
                    if (m_pLog)
                    {
                        CString str;
                        str.Format(IDS_EL_PROCEDURE_INC_10,
                                 (const char*)delivComb,
                                 pSymbol->GetCombinationName(i));

                        PSS_GenericSymbolErrorLine e(str, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 1);
                        m_pLog->AddLine(e);
                    }

                    // increment the error counter
                    ++m_ErrorCounter;
                }

                // next deliverable
                delivComb = delivToken.GetNextToken();
            }
        }
    }

    // get the down nodes
    CODNodeArray      downNodes;
    const std::size_t downSymbolCount = pSymbol->GetFollowingSymbols_Down(downNodes);

    // check if a process is attached to it
    if (downSymbolCount > 0 && PSS_ODSymbolManipulator::HasSymbolsISA(downNodes, RUNTIME_CLASS(PSS_ProcessSymbolBP)))
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_3,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // check if at least one following symbol is defined
    if (downSymbolCount <= 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_5,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // get the entering down links
    CODEdgeArray      downEdges;
    const std::size_t downLinkCount = pSymbol->GetEdgesEntering_Down(downEdges);

    // check if any entering link from the down side. Impossible !!!!
    if (downLinkCount > 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_4,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // check the sum of workload out percentage greater or equal to 100%
    CODEdgeArray      leavingDownEdges;
    const std::size_t leavingDownLinkCount = pSymbol->GetEdgesLeaving_Down(leavingDownEdges);

    if (leavingDownLinkCount > 0)
    {
        float value = 0.0f;

        for (std::size_t i = 0; i < leavingDownLinkCount; ++i)
        {
            IODEdge*                     pIEdge = leavingDownEdges.GetAt(i);
            PSS_DeliverableLinkSymbolBP* pLink  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

            // check if a link symbol
            if (!pLink)
                continue;

            // check if it's a local symbol
            if (!pLink->IsLocal())
            {
                // get the local symbol
                PSS_DeliverableLinkSymbolBP* pLocalLink = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pLink->GetLocalSymbol());

                if (pLocalLink)
                    pLink = pLocalLink;
                else
                {
                    // log the error
                    if (m_pLog)
                    {
                        PSS_GenericSymbolErrorLine e(IDS_AL_DELIVERABLE_INC_6,
                                                     pLink->GetSymbolName(),
                                                     pLink->GetAbsolutePath(),
                                                    -1,
                                                     1);
                        m_pLog->AddLine(e);
                    }

                    // increment the error counter
                    ++m_ErrorCounter;
                }
            }

            // add the deliverable cost value
            value += pLink->GetOutWorkloadPercent();
        }

        if (value < 1.0f)
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_8,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());
                m_pLog->AddLine(e);
            }

            // increment the warning counter
            ++m_WarningCounter;
        }
    }

    CStringArray rulesList;
    pSymbol->CheckRulesSync(rulesList);

    // check if the rules contained in the symbol are synchronized with the referential
    if (!rulesList.IsEmpty())
    {
        const std::size_t ruleCount = rulesList.GetCount();

        for (std::size_t i = 0; i < ruleCount; ++i)
        {
            if (m_pLog)
            {
                CString ruleWarning;
                ruleWarning.LoadString(IDS_RULE_IS_NOT_SYNC);
                ruleWarning += _T(" ") + rulesList.GetAt(i);

                PSS_GenericSymbolErrorLine e(ruleWarning,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());
                m_pLog->AddLine(e);
            }

            // increment the warning counter
            ++m_WarningCounter;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::CheckProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // check the unique reference number
    CheckUniqueRef(pSymbol);

    // check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // get the up nodes
    CODNodeArray      upNodes;
    const std::size_t upSymbolCount = pSymbol->GetFollowingSymbols_Up(upNodes);

    // impossible to have following symbols connected from the top side
    if (upSymbolCount > 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCESS_INC_1,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // get the left nodes
    CODNodeArray      leftNodes;
    const std::size_t leftSymbolCount = pSymbol->GetFollowingSymbols_Left(leftNodes);

    // impossible to have following symbols connected from the left side
    if (leftSymbolCount > 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCESS_INC_2,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // get the right nodes
    CODNodeArray      rightNodes;
    const std::size_t rightSymbolCount = pSymbol->GetFollowingSymbols_Right(rightNodes);

    // check if a process is attached to it
    if (rightSymbolCount > 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCESS_INC_3,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // get the down nodes
    CODNodeArray      downNodes;
    const std::size_t downSymbolCount = pSymbol->GetFollowingSymbols_Down(downNodes);

    // check if a process is attached to it
    if (downSymbolCount > 0 && PSS_ODSymbolManipulator::HasSymbolsISA(downNodes, RUNTIME_CLASS(PSS_ProcedureSymbolBP)))
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCESS_INC_4,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);

            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    CStringArray rulesList;
    pSymbol->CheckRulesSync(rulesList);

    // check if the rules are synchronized with the referential
    if (!rulesList.IsEmpty())
    {
        const std::size_t ruleCount = rulesList.GetCount();

        for (std::size_t i = 0; i < ruleCount; ++i)
        {
            if (m_pLog)
            {
                CString ruleWarning;
                ruleWarning.LoadString(IDS_RULE_IS_NOT_SYNC);
                ruleWarning += _T(" ") + rulesList.GetAt(i);

                PSS_GenericSymbolErrorLine e(ruleWarning,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());
                m_pLog->AddLine(e);
            }

            // increment the warning counter
            ++m_WarningCounter;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::CheckStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // check unique reference number
    CheckUniqueRef(pSymbol);

    // check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // get the following nodes
    CODNodeArray      followingNodes;
    const std::size_t followingSymbolCount = pSymbol->GetFollowingSymbols(followingNodes);

    // get the entering nodes
    CODNodeArray      enteringNodes;
    const std::size_t enteringSymbolCount = pSymbol->GetEnteringSymbols(enteringNodes);

    // cannot have entering symbol on start
    if (enteringSymbolCount > 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_START_INC_1,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // cannot have more than one following symbol
    if (followingSymbolCount > 1)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_START_INC_2,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // need at least one following symbol
    if (followingSymbolCount < 1)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_START_INC_3,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    CStringArray rulesList;
    pSymbol->CheckRulesSync(rulesList);

    // check if the rules are synchronized with the referential
    if (!rulesList.IsEmpty())
    {
        const std::size_t ruleCount = rulesList.GetCount();

        for (std::size_t i = 0; i < ruleCount; ++i)
        {
            if (m_pLog)
            {
                CString ruleWarning;
                ruleWarning.LoadString(IDS_RULE_IS_NOT_SYNC);
                ruleWarning += _T(" ") + rulesList.GetAt(i);

                PSS_GenericSymbolErrorLine e(ruleWarning,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());
                m_pLog->AddLine(e);
            }

            // increment the warning counter
            ++m_WarningCounter;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::CheckStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // check the unique reference number
    CheckUniqueRef(pSymbol);

    // check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // get the following nodes
    CODNodeArray      followingNodes;
    const std::size_t followingSymbolCount = pSymbol->GetFollowingSymbols(followingNodes);

    // get the entering nodes
    CODNodeArray      enteringNodes;
    const std::size_t enteringSymbolCount = pSymbol->GetEnteringSymbols(enteringNodes);

    // cannot have following symbol on stop
    if (followingSymbolCount > 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_STOP_INC_1,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // cannot have more than one entering symbol
    if (enteringSymbolCount > 1)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_STOP_INC_2,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // need at least one entering symbol
    if (enteringSymbolCount < 1)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_STOP_INC_3,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    CStringArray rulesList;
    pSymbol->CheckRulesSync(rulesList);

    // check if the rules are synchronized with the referential
    if (!rulesList.IsEmpty())
    {
        const std::size_t ruleCount = rulesList.GetCount();

        for (std::size_t i = 0; i < ruleCount; ++i)
        {
            if (m_pLog)
            {
                CString ruleWarning;
                ruleWarning.LoadString(IDS_RULE_IS_NOT_SYNC);
                ruleWarning += _T(" ") + rulesList.GetAt(i);

                PSS_GenericSymbolErrorLine e(ruleWarning,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());
                m_pLog->AddLine(e);
            }

            // increment the warning counter
            ++m_WarningCounter;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::CheckDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // check unique reference number
    CheckUniqueRef(pSymbol);

    // check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // check if the link is connected to an entering symbol
    if (!pSymbol->GetEnteringSymbol())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_DELIVERABLE_INC_1,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         0);
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }

    // check if the link is connected to a following symbol
    if (!pSymbol->GetFollowingSymbol())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_DELIVERABLE_INC_2,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         0);
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;
    }

    // check if it's a referenced symbol
    if (!pSymbol->IsLocal())
    {
        // get the local symbol
        PSS_DeliverableLinkSymbolBP* pLocalSymbol = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pSymbol->GetLocalSymbol());

        if (!pLocalSymbol)
        {
            // log the error
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_EL_DELIVERABLE_INC_3,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath(),
                                            -1,
                                             1);
                m_pLog->AddLine(e);
            }

            // increment the error counter
            ++m_ErrorCounter;
        }
    }

    CStringArray rulesList;
    pSymbol->CheckRulesSync(rulesList);

    // check if the rules are synchronized with the referential
    if (!rulesList.IsEmpty())
    {
        const std::size_t ruleCount = rulesList.GetCount();

        for (std::size_t i = 0; i < ruleCount; ++i)
        {
            if (m_pLog)
            {
                CString ruleWarning;
                ruleWarning.LoadString(IDS_RULE_IS_NOT_SYNC);
                ruleWarning += _T(" ") + rulesList.GetAt(i);

                PSS_GenericSymbolErrorLine e(ruleWarning,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());

                m_pLog->AddLine(e);
            }

            // increment the warning counter
            ++m_WarningCounter;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::CheckSymbol(PSS_Symbol* pSymbol)
{
    ASSERT(pSymbol);

    // check unique reference number
    CheckUniqueRef(pSymbol);

    // check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::CheckLink(PSS_LinkSymbol* pLink)
{
    ASSERT(pLink);

    // check unique reference number
    CheckUniqueRef(pLink);

    // check for special characters in the name
    CheckInvalidCharInSymbolName(pLink, pLink->GetAbsolutePath());

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::CheckInvalidCharInSymbolName(PSS_BasicSymbol* pSymbol, const CString& path)
{
    ASSERT(pSymbol);

    const char* pStr = (const char*)pSymbol->GetSymbolName();

    for (; *pStr; ++pStr)
        if (*pStr == '\t' || *pStr == '\r' || *pStr == '\n')
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_EL_SYMBOL_INC_2, pSymbol->GetSymbolName(), path, -1, 1);
                m_pLog->AddLine(e);
            }

            // increment the error counter
            ++m_ErrorCounter;
            break;
        }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::CheckUniqueRef(PSS_BasicSymbol* pSymbol)
{
    ASSERT(pSymbol);

    TRACE1("Ref %s\n", (const char*)pSymbol->GetSymbolName());

    // if the ref already exists, allocate a new one
    if (RefExist(pSymbol->GetSymbolReferenceNumber()))
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_SYMBOL_INC_1,
                                         pSymbol->GetSymbolName(),
                                         _T(""),
                                        -1,
                                         0);
            m_pLog->AddLine(e);
        }

        // increment the warning counter
        ++m_WarningCounter;

        // set the next available reference number
        pSymbol->SetSymbolReferenceNumber(m_pModel->GetNextAvailableReferenceNumber());
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::RefExist(int ref)
{
    // the -1 code shouldn't be processed
    if (ref == -1)
        return false;

    int index = 0;

    for (int i = 0; i < m_RefIDSize && m_pIDArray[i] != 0; ++i)
    {
        index = i;

        if (m_pIDArray[i] == ref)
            return true;
    }

    // check the array size before inserting the element
    if (index < m_RefIDSize)
        // add it for the next time
        m_pIDArray[index] = ref;

    return false;
}
//---------------------------------------------------------------------------
