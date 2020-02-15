/////////////////////////////////////////////////////////////////////////////
//@doc ZUCheckSesterceConsistency
//@module ZUCheckSesterceConsistency.cpp | Implementation of the <c ZUCheckSesterceConsistency> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 06/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUCheckSesterceConsistency.h"

#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModelBP\PSS_DoorSymbolBP.h"
#include "zModelBP\PSS_PageSymbolBP.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zModelBP\PSS_StartSymbolBP.h"
#include "zModelBP\PSS_StopSymbolBP.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zModel\PSS_ODSymbolManipulator.h"

// Include files for log
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 17 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUCheckSesterceConsistency::ZUCheckSesterceConsistency(PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                       PSS_Log*                    pLog    /*= NULL*/)
    : m_pModel(pModel),
    m_pLog(pLog)
{}

ZUCheckSesterceConsistency::~ZUCheckSesterceConsistency()
{}

bool ZUCheckSesterceConsistency::CheckModel()
{
    // Initialize internal counters
    m_ErrorCounter = 0;
    m_WarningCounter = 0;

    if (m_pModel)
    {
        m_pModel->AcceptVisitor(*this);
        return true;
    }

    return false;
}

bool ZUCheckSesterceConsistency::Visit(CODComponent& Symbol)
{
    CODComponent* pSymbol = &Symbol;

    if (ISA(pSymbol, PSS_ProcedureSymbolBP))
    {
        return CheckProcedureSymbol(dynamic_cast<PSS_ProcedureSymbolBP*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBDeliverableLinkSymbol))
    {
        return CheckDeliverableLinkSymbol(dynamic_cast<ZBDeliverableLinkSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_DoorSymbolBP))
    {
        return CheckDoorSymbol(dynamic_cast<PSS_DoorSymbolBP*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_PageSymbolBP))
    {
        return CheckPageSymbol(dynamic_cast<PSS_PageSymbolBP*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_ProcessSymbolBP))
    {
        return CheckProcessSymbol(dynamic_cast<PSS_ProcessSymbolBP*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_StartSymbolBP))
    {
        return CheckStartSymbol(dynamic_cast<PSS_StartSymbolBP*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_StopSymbolBP))
    {
        return CheckStopSymbol(dynamic_cast<PSS_StopSymbolBP*>(&Symbol));
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

bool ZUCheckSesterceConsistency::CheckDoorSymbol(PSS_DoorSymbolBP* pSymbol)
{
    ASSERT(pSymbol);
    return true;
}

bool ZUCheckSesterceConsistency::CheckPageSymbol(PSS_PageSymbolBP* pSymbol)
{
    ASSERT(pSymbol);
    return true;
}

bool ZUCheckSesterceConsistency::CheckProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // Test if it is a local symbol
    if (!pSymbol->IsLocal())
    {
        // Locate the local symbol
        CODComponent* pComp = pSymbol->GetLocalSymbol();

        if (pComp && ISA(pComp, PSS_ProcedureSymbolBP))
        {
            pSymbol = dynamic_cast<PSS_ProcedureSymbolBP*>(pComp);
        }
    }

    // Check if unit defined for procedure
    if (pSymbol->GetUnitName().IsEmpty())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_10,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());

            m_pLog->AddLine(e);
        }

        // Increment warning counter
        ++m_WarningCounter;
    }
    else
    {
        if (pSymbol->GetUnitCost() == 0)
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_11,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());

                m_pLog->AddLine(e);
            }

            // Increment warning counter
            ++m_WarningCounter;
        }
    }

    // Check the multiplier
    if (pSymbol->GetMultiplier() == 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_12,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());

            m_pLog->AddLine(e);
        }

        // Increment warning counter
        ++m_WarningCounter;
    }

    /* Not in beta 2, the maximum percentage is not used anymore
    // Now check the sum of the combination percentage
    if (pSymbol->CalculateSumOfCombinations() != 1)
    {
        if ( m_pLog )
        {
            ZBGenericSymbolErrorLine e( IDS_AL_PROCEDURE_INC_13,
                                        pSymbol->GetSymbolName(),
                                        pSymbol->GetAbsolutePath() );

            m_pLog->AddLine( e );
        }

        // Increment warning counter
        ++m_WarningCounter;
    }
    */

    // Now check if a master has been defined for each combination
    int Count = pSymbol->GetCombinationCount();

    for (int i = 0; i < Count; ++i)
    {
        if (pSymbol->GetCombinationMaster(i).IsEmpty())
        {
            if (m_pLog)
            {
                CString s;
                s.Format(IDS_AL_PROCEDURE_INC_14, pSymbol->GetCombinationName(i));
                PSS_GenericSymbolErrorLine e(s, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 1);
                m_pLog->AddLine(e);
            }

            // Increment error counter
            ++m_ErrorCounter;
        }
    }

    return true;
}

bool ZUCheckSesterceConsistency::CheckProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // ************************************************************************************************************
    // JMR-MODIF - Le 17 mars 2006 - Ajout du code de contrôle des livraisons.

    int Count = pSymbol->GetDeliveriesCount();

    for (int i = 0; i < Count; ++i)
    {
        if (pSymbol->GetDeliveryMain(i).IsEmpty())
        {
            if (m_pLog)
            {
                CString s;
                s.Format(IDS_AL_PROCESS_INC_1, pSymbol->GetDeliveryName(i));
                PSS_GenericSymbolErrorLine e(s, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 1);
                m_pLog->AddLine(e);
            }

            // Increment error counter
            ++m_ErrorCounter;
        }
    }
    // ************************************************************************************************************

    return true;
}

bool ZUCheckSesterceConsistency::CheckStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // Check if unit defined for procedure
    if (pSymbol->GetUnitName().IsEmpty())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_START_INC_10,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());

            m_pLog->AddLine(e);
        }

        // Increment warning counter
        ++m_WarningCounter;
    }
    else
    {
        if (pSymbol->GetUnitCost() == 0)
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_AL_START_INC_11,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());

                m_pLog->AddLine(e);
            }

            // Increment warning counter
            ++m_WarningCounter;
        }
    }

    return true;
}

bool ZUCheckSesterceConsistency::CheckStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    // Check if unit defined for procedure
    if (pSymbol->GetUnitName().IsEmpty())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_STOP_INC_10,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());

            m_pLog->AddLine(e);
        }

        // Increment warning counter
        ++m_WarningCounter;
    }
    else
    {
        if (pSymbol->GetUnitCost() == 0)
        {
            if (m_pLog)
            {
                PSS_GenericSymbolErrorLine e(IDS_AL_STOP_INC_11,
                                             pSymbol->GetSymbolName(),
                                             pSymbol->GetAbsolutePath());

                m_pLog->AddLine(e);
            }

            // Increment warning counter
            ++m_WarningCounter;
        }
    }

    return true;
}

bool ZUCheckSesterceConsistency::CheckDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol)
{
    ASSERT(pSymbol);

    // Test if it is a local symbol
    if (!pSymbol->IsLocal())
    {
        // Locate the local symbol
        CODComponent* pComp = pSymbol->GetLocalSymbol();

        if (pComp && ISA(pComp, ZBDeliverableLinkSymbol))
        {
            pSymbol = dynamic_cast<ZBDeliverableLinkSymbol*>(pComp);
        }
    }

    // Check the quantity
    if (pSymbol->GetQuantityYear() <= 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_DELIVERABLE_INC_1,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());

            m_pLog->AddLine(e);
        }

        // Increment warning counter
        ++m_WarningCounter;
    }

    /* Not in beta 2, the maximum percentage is not used anymore
    // Check the percentage in
    if (pSymbol->GetInWorkloadPercent() <= 0)
    {
        if ( m_pLog )
        {
            ZBGenericSymbolErrorLine e( IDS_AL_DELIVERABLE_INC_2,
                                        pSymbol->GetSymbolName(),
                                        pSymbol->GetAbsolutePath() );

            m_pLog->AddLine( e );
        }

        // Increment warning counter
        ++m_WarningCounter;
    }

    if ( pSymbol->GetInWorkloadPercent() > 1 )
    {
        if ( m_pLog )
        {
            ZBGenericSymbolErrorLine e( IDS_AL_DELIVERABLE_INC_3,
                                        pSymbol->GetSymbolName(),
                                        pSymbol->GetAbsolutePath() );

            m_pLog->AddLine( e );
        }

        // Increment warning counter
        ++m_WarningCounter;
    }
    */

    // Check the percentage out
    if (pSymbol->GetOutWorkloadPercent() <= 0)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_DELIVERABLE_INC_4,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());

            m_pLog->AddLine(e);
        }

        // Increment warning counter
        ++m_WarningCounter;
    }

    if (pSymbol->GetOutWorkloadPercent() > 1)
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_DELIVERABLE_INC_5,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath());

            m_pLog->AddLine(e);
        }

        // Increment warning counter
        ++m_WarningCounter;
    }

    return true;
}

bool ZUCheckSesterceConsistency::CheckSymbol(PSS_Symbol* pSymbol)
{
    ASSERT(pSymbol);
    return true;
}

bool ZUCheckSesterceConsistency::CheckLink(PSS_LinkSymbol* pLink)
{
    ASSERT(pLink);
    return true;
}
