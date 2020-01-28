// ZUCheckSymbolConsistency.cpp: implementation of the ZUCheckSymbolConsistency class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUCheckSymbolConsistency.h"

#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"

#include "ZBBPDoorSymbol.h"
#include "ZBBPPageSymbol.h"
#include "ZBBPProcedureSymbol.h"
#include "ZBBPProcessSymbol.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"
#include "ZBDeliverableLinkSymbol.h"

#include "PSS_ProcessGraphModelMdlBP.h"

#include "zModel\PSS_ProcessGraphModelController.h"

#include "ZUCheckValidUnit.h"

#include "zModel\PSS_ODSymbolManipulator.h"

// Include files for log
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"

#include "zBaseLib\PSS_Tokenizer.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 20 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUCheckSymbolConsistency::ZUCheckSymbolConsistency(PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                   PSS_Log*                    pLog    /*= NULL*/)
    : m_pModel(pModel),
    m_pLog(pLog),
    m_IsLogging(false),
    m_pIDArray(NULL),
    m_RefIDSize(0)
{}

ZUCheckSymbolConsistency::~ZUCheckSymbolConsistency()
{}

// JMR-MODIF - Le 5 novembre 2006 - Ajout du paramètre ModelIsClean.
bool ZUCheckSymbolConsistency::CheckSymbol(CODComponent& Symbol, BOOL ModelIsClean)
{
    // If log required
    if (m_pLog && m_pLog->InitializeLog())
    {
        // Initialize counters
        m_ErrorCounter = 0;
        m_WarningCounter = 0;

        m_pLog->ClearLog();
        CString message;
        message.Format(IDS_ZS_START, m_pModel->GetModelName());
        PSS_GenericSymbolErrorLine e(message);
        m_pLog->AddLine(e);

        // ********************************************************************************************
        // JMR-MODIF - Le 5 novembre 2006 - Ajoute un message d'information si le modèle a été nettoyé.
        if (ModelIsClean == TRUE)
        {
            message.Format(IDS_ZS_DELETE_CORRUPED_SYMBOLS, m_pModel->GetModelName());
            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }
        // ********************************************************************************************
    }

    // Do an deep check before lauching the calculation of the model
    ZUCheckValidUnit Check(m_pModel);
    Check.SetLog(m_pLog);
    Check.Navigate();

    // Assigns the error counter and the warning counter
    m_ErrorCounter += Check.GetErrorCounter();
    m_WarningCounter += Check.GetWarningCounter();

    // Allocate and reset the array of ids
    m_RefIDSize = 10000;
    m_pIDArray = new int[m_RefIDSize];

    memset(m_pIDArray, 0, m_RefIDSize * sizeof(int));

    CODComponent* pSymbol = &Symbol;

    if (ISA(pSymbol, PSS_Symbol))
    {
        dynamic_cast<PSS_Symbol&>(Symbol).AcceptVisitor(*this);
    }
    else if (ISA(pSymbol, PSS_LinkSymbol))
    {
        dynamic_cast<PSS_LinkSymbol&>(Symbol).AcceptVisitor(*this);
    }
    else if (ISA(pSymbol, PSS_ProcessGraphModelMdl))
    {
        dynamic_cast<PSS_ProcessGraphModelMdl&>(Symbol).AcceptVisitor(*this);
    }

    // If log required
    if (m_pLog)
    {
        CString message;

        if (m_ErrorCounter > 0 || m_WarningCounter > 0)
        {
            message.Format(IDS_ZS_STOP2, m_ErrorCounter, m_WarningCounter);
        }
        else
        {
            message.LoadString(IDS_ZS_STOP);
        }

        PSS_GenericSymbolErrorLine e(message);
        m_pLog->AddLine(e);
    }

    // Delete the array of IDs
    if (m_pIDArray)
    {
        delete[] m_pIDArray;
        m_pIDArray = NULL;
    }

    return true;
}

bool ZUCheckSymbolConsistency::Visit(CODComponent& Symbol)
{
    CODComponent* pSymbol = &Symbol;

    if (ISA(pSymbol, ZBBPProcedureSymbol))
    {
        return CheckProcedureSymbol(dynamic_cast<ZBBPProcedureSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBDeliverableLinkSymbol))
    {
        return CheckDeliverableLinkSymbol(dynamic_cast<ZBDeliverableLinkSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPDoorSymbol))
    {
        return CheckDoorSymbol(dynamic_cast<ZBBPDoorSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPPageSymbol))
    {
        return CheckPageSymbol(dynamic_cast<ZBBPPageSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPProcessSymbol))
    {
        return CheckProcessSymbol(dynamic_cast<ZBBPProcessSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPStartSymbol))
    {
        return CheckStartSymbol(dynamic_cast<ZBBPStartSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPStopSymbol))
    {
        return CheckStopSymbol(dynamic_cast<ZBBPStopSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_Symbol))
    {
        return CheckSymbol(dynamic_cast<PSS_Symbol*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_LinkSymbol))
    {
        return CheckLink(dynamic_cast<PSS_LinkSymbol*>(&Symbol));
    }

    // Not a right symbol or not necessary to visit
    return false;
}

bool ZUCheckSymbolConsistency::CheckDoorSymbol(ZBBPDoorSymbol* pSymbol)
{
    ASSERT(pSymbol);

    // First, check unique reference number
    CheckUniqueRef(pSymbol);

    // Check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // Retreiving following nodes
    CODNodeArray FollowingNodes;
    size_t FollowingSymbolCount = pSymbol->GetFollowingSymbols(FollowingNodes);

    // Retreiving entering nodes
    CODNodeArray EnteringNodes;
    size_t EnteringSymbolCount = pSymbol->GetEnteringSymbols(EnteringNodes);

    if (FollowingSymbolCount > 1)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    if (EnteringSymbolCount > 1)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    if (FollowingSymbolCount < 1 && EnteringSymbolCount < 1)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    if (pSymbol->GetTwinDoorSymbol() == NULL)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    return true;
}

bool ZUCheckSymbolConsistency::CheckPageSymbol(ZBBPPageSymbol* pSymbol)
{
    ASSERT(pSymbol);

    // First, check unique reference number
    CheckUniqueRef(pSymbol);

    // Check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // Retreiving following nodes
    CODNodeArray FollowingNodes;
    size_t FollowingSymbolCount = pSymbol->GetFollowingSymbols(FollowingNodes);

    // Retreiving entering nodes
    CODNodeArray EnteringNodes;
    size_t EnteringSymbolCount = pSymbol->GetEnteringSymbols(EnteringNodes);

    if (FollowingSymbolCount > 1)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    if (EnteringSymbolCount > 1)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    if (FollowingSymbolCount < 1 && EnteringSymbolCount < 1)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    if (pSymbol->GetTwinPageSymbol() == NULL)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    return true;
}

bool ZUCheckSymbolConsistency::CheckProcedureSymbol(ZBBPProcedureSymbol* pSymbol)
{
    ASSERT(pSymbol);

    // First, check unique reference number
    CheckUniqueRef(pSymbol);

    // Check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // Retreiving up nodes
    CODNodeArray UpNodes;
    size_t UpSymbolCount = pSymbol->GetFollowingSymbols_Up(UpNodes);

    // Impossible to have following symbols connected from the top side
    if (UpSymbolCount > 0)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Retreiving left nodes
    CODNodeArray LeftNodes;
    size_t FollowingLeftSymbolCount = pSymbol->GetFollowingSymbols_Left(LeftNodes);

    if (FollowingLeftSymbolCount > 0)
    {
        if (PSS_ODSymbolManipulator::HasSymbolsISA(LeftNodes, RUNTIME_CLASS(ZBBPProcessSymbol)))
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

            // Increment error counter
            ++m_ErrorCounter;
        }
    }

    // Check entering symbol
    size_t EnteringLeftSymbolCount = pSymbol->GetEnteringSymbols_Left(LeftNodes);

    if (EnteringLeftSymbolCount > 0)
    {
        if (PSS_ODSymbolManipulator::HasSymbolsISA(LeftNodes, RUNTIME_CLASS(ZBBPProcessSymbol)))
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

            // Increment error counter
            ++m_ErrorCounter;
        }
    }

    // Check if we have the same count of leaving and entering left symbols 
    if (FollowingLeftSymbolCount != EnteringLeftSymbolCount)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_2,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());

            m_pLog->AddLine(e);
        }

        // Increment warning counter
        ++m_WarningCounter;
    }

    // Retreiving right nodes
    CODNodeArray RightNodes;
    size_t FollowingRightSymbolCount = pSymbol->GetFollowingSymbols_Right(RightNodes);

    if (FollowingRightSymbolCount > 0)
    {
        if (PSS_ODSymbolManipulator::HasSymbolsISA(RightNodes, RUNTIME_CLASS(ZBBPProcessSymbol)))
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

            // Increment error counter
            ++m_ErrorCounter;
        }
    }

    // Check entering symbol
    size_t EnteringRightSymbolCount = pSymbol->GetEnteringSymbols_Right(RightNodes);

    if (EnteringRightSymbolCount > 0)
    {
        if (PSS_ODSymbolManipulator::HasSymbolsISA(RightNodes, RUNTIME_CLASS(ZBBPProcessSymbol)))
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

            // Increment error counter
            ++m_ErrorCounter;
        }
    }

    // Check if we have the same count of leaving and entering rigth symbols 
    if (FollowingRightSymbolCount != EnteringRightSymbolCount)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_7,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());

            m_pLog->AddLine(e);
        }

        // Increment warning counter
        ++m_WarningCounter;
    }

    // Retreiving entering up nodes
    UpSymbolCount = pSymbol->GetEnteringSymbols_Up(UpNodes);

    // Check if a process is attached to it
    if (UpSymbolCount > 0 && PSS_ODSymbolManipulator::HasSymbolsISA(UpNodes, RUNTIME_CLASS(ZBBPProcessSymbol)))
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Check if at least one following symbol defined
    if (UpSymbolCount <= 0)
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

        // Increment error counter
        ++m_ErrorCounter;
    }
    else
    {
        // Now check if some deliverables are defined in a combination and are not still connected to the procedure
        CString EnteringUpDeliverables;
        pSymbol->GetEnteringUpDeliverable(EnteringUpDeliverables);

        int CombCounter = pSymbol->GetCombinationCount();

        for (int i = 0; i < CombCounter; ++i)
        {
            // Check if the master exists in the list of deliverables
            PSS_Tokenizer token(EnteringUpDeliverables);
            CString Master = pSymbol->GetCombinationMaster(i);

            if (!Master.IsEmpty() && !token.TokenExist(Master))
            {
                // If not, error
                if (m_pLog)
                {
                    CString s;
                    s.Format(IDS_EL_PROCEDURE_INC_9, (const char*)Master, pSymbol->GetCombinationName(i));
                    PSS_GenericSymbolErrorLine e(s, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 1);
                    m_pLog->AddLine(e);
                }

                // Increment error counter
                ++m_ErrorCounter;
            }

            // Now, run through all combination's deliverables
            // and check that all deliverables are attached
            PSS_Tokenizer token2;
            CString DelivComb = token2.GetFirstToken(pSymbol->GetCombinationDeliverables(i));

            while (!DelivComb.IsEmpty())
            {
                // Check if the combination's deliverable exists in the list of entering deliverables
                if (!token.TokenExist(DelivComb))
                {
                    // If not, error
                    if (m_pLog)
                    {
                        CString s;
                        s.Format(IDS_EL_PROCEDURE_INC_10,
                            (const char*)DelivComb,
                                 pSymbol->GetCombinationName(i));

                        PSS_GenericSymbolErrorLine e(s, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 1);
                        m_pLog->AddLine(e);
                    }

                    // Increment error counter
                    ++m_ErrorCounter;
                }

                // Next deliverable
                DelivComb = token2.GetNextToken();
            }
        }
    }

    // Retreiving down nodes
    CODNodeArray DownNodes;
    size_t DownSymbolCount = pSymbol->GetFollowingSymbols_Down(DownNodes);

    // Check if a process is attached to it
    if (DownSymbolCount > 0 &&
        PSS_ODSymbolManipulator::HasSymbolsISA(DownNodes, RUNTIME_CLASS(ZBBPProcessSymbol)))
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Check if at least one following symbol defined
    if (DownSymbolCount <= 0)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Retreiving entering down links
    CODEdgeArray DownEdges;
    size_t DownLinkCount = pSymbol->GetEdgesEntering_Down(DownEdges);

    // Check if any entering link from the down side. Impossible !!!!
    if (DownLinkCount > 0)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Check the sum of workload out percentage greater or equal to 100%
    CODEdgeArray LeavingDownEdges;
    size_t LeavingDownLinkCount = pSymbol->GetEdgesLeaving_Down(LeavingDownEdges);

    if (LeavingDownLinkCount > 0)
    {
        float Value = 0;

        for (size_t nEdgeIdx = 0; nEdgeIdx < LeavingDownLinkCount; ++nEdgeIdx)
        {
            IODEdge* pIEdge = LeavingDownEdges.GetAt(nEdgeIdx);

            // check if a link symbol
            if (!static_cast<CODLinkComponent*>(pIEdge) ||
                !ISA(static_cast<CODLinkComponent*>(pIEdge), ZBDeliverableLinkSymbol))
            {
                continue;
            }

            ZBDeliverableLinkSymbol* pLink = static_cast<ZBDeliverableLinkSymbol*>(pIEdge);

            if (!pLink)
            {
                continue;
            }

            // Test if it is a local symbol
            if (!pLink->IsLocal())
            {
                // Locate the local symbol
                CODComponent* pComp = pLink->GetLocalSymbol();

                if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
                {
                    pLink = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
                }
                else
                {
                    // Log the error
                    if (m_pLog)
                    {
                        PSS_GenericSymbolErrorLine e(IDS_AL_DELIVERABLE_INC_6,
                                                     pLink->GetSymbolName(),
                                                     pLink->GetAbsolutePath(),
                                                     -1,
                                                     1);

                        m_pLog->AddLine(e);
                    }

                    // Increment error counter
                    ++m_ErrorCounter;
                }
            }

            // Now add the deliverable cost value
            Value += pLink->GetOutWorkloadPercent();
        }

        if (Value < 1)
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_EL_PROCEDURE_INC_8,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());

                m_pLog->AddLine(e);
            }

            // Increment warning counter
            ++m_WarningCounter;
        }
    }

    // *************************************************************************************************
    // JMR-MODIF - Le 10 octobre 2007 - Teste si les règles contenues dans le symbole sont synchronisées
    // avec le référentiel.

    CStringArray RulesList;

    pSymbol->CheckRulesSync(RulesList);

    if (RulesList.IsEmpty() == FALSE)
    {
        for (int i = 0; i < RulesList.GetCount(); i++)
        {
            if (m_pLog)
            {
                CString s_RuleWarning = _T("");
                s_RuleWarning.LoadString(IDS_RULE_IS_NOT_SYNC);
                s_RuleWarning += _T(" ") + RulesList.GetAt(i);

                PSS_GenericSymbolErrorLine e(s_RuleWarning,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());

                m_pLog->AddLine(e);
            }

            // Increment warning counter
            ++m_WarningCounter;
        }
    }
    // *************************************************************************************************

    return true;
}

bool ZUCheckSymbolConsistency::CheckProcessSymbol(ZBBPProcessSymbol* pSymbol)
{
    ASSERT(pSymbol);

    // First, check unique reference number
    CheckUniqueRef(pSymbol);

    // Check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // Retreiving up nodes
    CODNodeArray UpNodes;
    size_t UpSymbolCount = pSymbol->GetFollowingSymbols_Up(UpNodes);

    // Impossible to have following symbols connected from the top side
    if (UpSymbolCount > 0)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Retreiving left nodes
    CODNodeArray LeftNodes;
    size_t LeftSymbolCount = pSymbol->GetFollowingSymbols_Left(LeftNodes);

    // Impossible to have following symbols connected from the left side
    if (LeftSymbolCount > 0)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Retreiving right nodes
    CODNodeArray RightNodes;
    size_t RightSymbolCount = pSymbol->GetFollowingSymbols_Right(RightNodes);

    // Check if a process is attached to it
    if (RightSymbolCount > 0)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Retreiving down nodes
    CODNodeArray DownNodes;
    size_t DownSymbolCount = pSymbol->GetFollowingSymbols_Down(DownNodes);

    // Check if a process is attached to it
    if (DownSymbolCount > 0 &&
        PSS_ODSymbolManipulator::HasSymbolsISA(DownNodes, RUNTIME_CLASS(ZBBPProcedureSymbol)))
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // *************************************************************************************************
    // JMR-MODIF - Le 10 octobre 2007 - Teste si les règles contenues dans le symbole sont synchronisées
    // avec le référentiel.

    CStringArray RulesList;

    pSymbol->CheckRulesSync(RulesList);

    if (RulesList.IsEmpty() == FALSE)
    {
        for (int i = 0; i < RulesList.GetCount(); i++)
        {
            if (m_pLog)
            {
                CString s_RuleWarning = _T("");
                s_RuleWarning.LoadString(IDS_RULE_IS_NOT_SYNC);
                s_RuleWarning += _T(" ") + RulesList.GetAt(i);

                PSS_GenericSymbolErrorLine e(s_RuleWarning,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());

                m_pLog->AddLine(e);
            }

            // Increment warning counter
            ++m_WarningCounter;
        }
    }
    // *************************************************************************************************

    return true;
}

bool ZUCheckSymbolConsistency::CheckStartSymbol(ZBBPStartSymbol* pSymbol)
{
    ASSERT(pSymbol);

    // First, check unique reference number
    CheckUniqueRef(pSymbol);

    // Check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // Retreiving following nodes
    CODNodeArray FollowingNodes;
    size_t FollowingSymbolCount = pSymbol->GetFollowingSymbols(FollowingNodes);

    // Retreiving entering nodes
    CODNodeArray EnteringNodes;
    size_t EnteringSymbolCount = pSymbol->GetEnteringSymbols(EnteringNodes);

    // Cannot have entering symbol on start
    if (EnteringSymbolCount > 0)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Cannot have more than one following symbol 
    if (FollowingSymbolCount > 1)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Need at least one following symbol
    if (FollowingSymbolCount < 1)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // *************************************************************************************************
    // JMR-MODIF - Le 10 octobre 2007 - Teste si les règles contenues dans le symbole sont synchronisées
    // avec le référentiel.

    CStringArray RulesList;

    pSymbol->CheckRulesSync(RulesList);

    if (RulesList.IsEmpty() == FALSE)
    {
        for (int i = 0; i < RulesList.GetCount(); i++)
        {
            if (m_pLog)
            {
                CString s_RuleWarning = _T("");
                s_RuleWarning.LoadString(IDS_RULE_IS_NOT_SYNC);
                s_RuleWarning += _T(" ") + RulesList.GetAt(i);

                PSS_GenericSymbolErrorLine e(s_RuleWarning,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());

                m_pLog->AddLine(e);
            }

            // Increment warning counter
            ++m_WarningCounter;
        }
    }
    // *************************************************************************************************

    return true;
}

bool ZUCheckSymbolConsistency::CheckStopSymbol(ZBBPStopSymbol* pSymbol)
{
    ASSERT(pSymbol);

    // First, check unique reference number
    CheckUniqueRef(pSymbol);

    // Check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // Retreiving following nodes
    CODNodeArray FollowingNodes;
    size_t FollowingSymbolCount = pSymbol->GetFollowingSymbols(FollowingNodes);

    // Retreiving entering nodes
    CODNodeArray EnteringNodes;
    size_t EnteringSymbolCount = pSymbol->GetEnteringSymbols(EnteringNodes);

    // Cannot have following symbol on stop
    if (FollowingSymbolCount > 0)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Cannot have more than one entering symbol 
    if (EnteringSymbolCount > 1)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Need at least one entering symbol
    if (EnteringSymbolCount < 1)
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

        // Increment error counter
        ++m_ErrorCounter;
    }

    // *************************************************************************************************
    // JMR-MODIF - Le 10 octobre 2007 - Teste si les règles contenues dans le symbole sont synchronisées
    // avec le référentiel.

    CStringArray RulesList;

    pSymbol->CheckRulesSync(RulesList);

    if (RulesList.IsEmpty() == FALSE)
    {
        for (int i = 0; i < RulesList.GetCount(); i++)
        {
            if (m_pLog)
            {
                CString s_RuleWarning = _T("");
                s_RuleWarning.LoadString(IDS_RULE_IS_NOT_SYNC);
                s_RuleWarning += _T(" ") + RulesList.GetAt(i);

                PSS_GenericSymbolErrorLine e(s_RuleWarning,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());

                m_pLog->AddLine(e);
            }

            // Increment warning counter
            ++m_WarningCounter;
        }
    }
    // *************************************************************************************************

    return true;
}

bool ZUCheckSymbolConsistency::CheckDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol)
{
    ASSERT(pSymbol);

    // First, check unique reference number
    CheckUniqueRef(pSymbol);

    // Check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    // Check if the link is connected to entering and following symbols
    if (pSymbol->GetEnteringSymbol() == NULL)
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

        // Increment warning counter
        ++m_WarningCounter;
    }

    if (pSymbol->GetFollowingSymbol() == NULL)
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

        // Increment warning counter
        ++m_WarningCounter;
    }

    // Test if it is a referenced symbol
    if (!pSymbol->IsLocal())
    {
        // Locate the local symbol
        CODComponent* pComp = pSymbol->GetLocalSymbol();

        if (!pComp || !ISA(pComp, ZBDeliverableLinkSymbol))
        {
            // Log the error
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_EL_DELIVERABLE_INC_3,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath(),
                                             -1,
                                             1);

                m_pLog->AddLine(e);
            }

            // Increment error counter
            ++m_ErrorCounter;
        }
    }

    // *************************************************************************************************
    // JMR-MODIF - Le 10 octobre 2007 - Teste si les règles contenues dans le symbole sont synchronisées
    // avec le référentiel.

    CStringArray RulesList;

    pSymbol->CheckRulesSync(RulesList);

    if (RulesList.IsEmpty() == FALSE)
    {
        for (int i = 0; i < RulesList.GetCount(); i++)
        {
            if (m_pLog)
            {
                CString s_RuleWarning = _T("");
                s_RuleWarning.LoadString(IDS_RULE_IS_NOT_SYNC);
                s_RuleWarning += _T(" ") + RulesList.GetAt(i);

                PSS_GenericSymbolErrorLine e(s_RuleWarning,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());

                m_pLog->AddLine(e);
            }

            // Increment warning counter
            ++m_WarningCounter;
        }
    }
    // *************************************************************************************************

    return true;
}

bool ZUCheckSymbolConsistency::CheckSymbol(PSS_Symbol* pSymbol)
{
    ASSERT(pSymbol);

    // First, check unique reference number
    CheckUniqueRef(pSymbol);

    // Check for special characters in the name
    CheckInvalidCharInSymbolName(pSymbol, pSymbol->GetAbsolutePath());

    return true;
}

bool ZUCheckSymbolConsistency::CheckLink(PSS_LinkSymbol* pLink)
{
    ASSERT(pLink);

    // First, check unique reference number
    CheckUniqueRef(pLink);

    // Check for special characters in the name
    CheckInvalidCharInSymbolName(pLink, pLink->GetAbsolutePath());

    return true;
}

// Check for special characters in the name
bool ZUCheckSymbolConsistency::CheckInvalidCharInSymbolName(PSS_BasicSymbol* pSymbol, CString Path)
{
    ASSERT(pSymbol);

    const char* pStr = (const char*)pSymbol->GetSymbolName();

    for (; *pStr; ++pStr)
    {
        if (*pStr == '\t' || *pStr == '\r' || *pStr == '\n')
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_EL_SYMBOL_INC_2, pSymbol->GetSymbolName(), Path, -1, 1);

                m_pLog->AddLine(e);
            }

            // Increment error counter
            ++m_ErrorCounter;
            break;
        }
    }

    return true;
}

bool ZUCheckSymbolConsistency::CheckUniqueRef(PSS_BasicSymbol* pSymbol)
{
    ASSERT(pSymbol);

    TRACE1(_T("Ref %s\n"), (const char*)pSymbol->GetSymbolName());

    // If the ref already exists, allocate a new one
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

        // Increment warning counter
        ++m_WarningCounter;

        // Sets the next available reference number
        pSymbol->SetSymbolReferenceNumber(m_pModel->GetNextAvailableReferenceNumber());
    }

    return true;
}
//---------------------------------------------------------------------------
bool ZUCheckSymbolConsistency::RefExist(int ref)
{
    // FIXME translate comments
    // JMR-MODIF - Le 20 mars 2006 - Le code -1 ne doit pas être pris en charge.
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
