/****************************************************************************
 * ==> PSS_CalculateRisks --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a Risk calculator                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CalculateRisks.h"

// processsoft
#include "zMediator\PSS_Application.h"
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
#include "ZUCheckValidUnit.h"
#include "zBaseLib\PSS_Log.h"
#include "zBaseLib\PSS_Tokenizer.h"
#include "zModelBPRes.h"
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_CalculateRisks
//---------------------------------------------------------------------------
PSS_CalculateRisks::PSS_CalculateRisks(int                       orangeSeverity,
                                       int                       redSeverity,
                                       float                     orangeUE,
                                       float                     redUE,
                                       float                     orangePOA,
                                       float                     redPOA,
                                       BOOL                      orangeAction,
                                       BOOL                      orangeNoAction,
                                       BOOL                      redAction,
                                       BOOL                      redNoAction,
                                       BOOL                      defaultColors,
                                       PSS_ProcessGraphModelMdl* pModel,
                                       PSS_Log*                  pLog) :
    PSS_BasicSymbolVisitor(),
    m_pModel(pModel),
    m_pLog(pLog),
    m_OrangeUE(orangeUE),
    m_RedUE(redUE),
    m_OrangePOA(orangePOA),
    m_RedPOA(redPOA),
    m_OrangeCounter(0),
    m_RedCounter(0),
    m_OrangeSeverity(orangeSeverity),
    m_RedSeverity(redSeverity),
    m_OrangeAction(orangeAction),
    m_OrangeNoAction(orangeNoAction),
    m_RedAction(redAction),
    m_RedNoAction(redNoAction),
    m_DefaultColors(defaultColors)
{}
//---------------------------------------------------------------------------
PSS_CalculateRisks::~PSS_CalculateRisks()
{}
//---------------------------------------------------------------------------
bool PSS_CalculateRisks::Calculate(CODComponent& component)
{
    // do log?
    if (m_pLog && m_pLog->InitializeLog())
    {
        // initialize counters
        m_OrangeCounter = 0;
        m_RedCounter    = 0;

        m_pLog->ClearLog();

        CString message = _T("");
        message.LoadString(IDS_RISK_CALCULATE_START);

        PSS_GenericSymbolErrorLine e(message);
        m_pLog->AddLine(e);
    }

    CODComponent*             pComponent         = &component;
    PSS_Symbol*               pSymbol            =                      dynamic_cast<PSS_Symbol*>(pComponent);
    PSS_LinkSymbol*           pLinkSymbol        = pSymbol     ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComponent);
    PSS_ProcessGraphModelMdl* pProcessGraphModel = pLinkSymbol ? NULL : dynamic_cast<PSS_ProcessGraphModelMdl*>(pComponent);

    if (pSymbol)
        pSymbol->AcceptVisitor(*this);
    else
    if (pLinkSymbol)
        pLinkSymbol->AcceptVisitor(*this);
    else
    if (pProcessGraphModel)
        pProcessGraphModel->AcceptVisitor(*this);

    // can log?
    if (m_pLog)
    {
        CString message;

        if (m_OrangeCounter > 0 || m_RedCounter > 0)
            message.Format(IDS_RISK_CALCULATE_END_INFOS, m_OrangeCounter, m_RedCounter);
        else
            message.LoadString(IDS_RISK_CALCULATE_END);

        PSS_GenericSymbolErrorLine e(message);
        m_pLog->AddLine(e);
    }

    PSS_Application::Instance()->GetMainForm()->DoRefreshProperties();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CalculateRisks::Visit(CODComponent& component)
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
    PSS_LinkSymbol*              pLink        = pSymbol      ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComponent);

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
    if (pLink)
        return CheckLink(pLink);

    // not a known symbol or should not be visit
    return false;
}
//---------------------------------------------------------------------------
bool PSS_CalculateRisks::CheckDoorSymbol(PSS_DoorSymbolBP* pSymbol)
{
    ASSERT(pSymbol);
    return true;
}
//---------------------------------------------------------------------------
bool PSS_CalculateRisks::CheckPageSymbol(PSS_PageSymbolBP* pSymbol)
{
    ASSERT(pSymbol);
    return true;
}
//---------------------------------------------------------------------------
bool PSS_CalculateRisks::CheckProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    CString   riskLevel;
    CString   message;
    int       level     = 0;
    const int riskCount = pSymbol->GetRiskCount();

    for (int i = 0; i < riskCount; ++i)
    {
        // orange level, check that the "Running action" and "No running action" checkboxes match the user configuration
        if ((m_OrangeAction   || m_OrangeNoAction)                 &&
           ((m_OrangeAction   == BOOL( pSymbol->GetRiskAction(i))) ||
            (m_OrangeNoAction == BOOL(!pSymbol->GetRiskAction(i))) ||
            (m_OrangeAction   && m_OrangeNoAction)))
            // check the input parameter levels entered by the user in relation to the risk levels
            if ((pSymbol->GetRiskSeverity(i) >= m_OrangeSeverity) &&
                (pSymbol->GetRiskUE(i)       >= m_OrangeUE)       &&
                (pSymbol->GetRiskPOA(i)      >= m_OrangePOA))
                level = 1;

        // red level, check that the "Running action" and "No running action" checkboxes match the user configuration
        if ((m_RedAction   || m_RedNoAction)                    &&
           ((m_RedAction   == BOOL( pSymbol->GetRiskAction(i))) ||
            (m_RedNoAction == BOOL(!pSymbol->GetRiskAction(i))) ||
            (m_RedAction   && m_RedNoAction)))
            // check the input parameter levels entered by the user in relation to the risk levels
            if ((pSymbol->GetRiskSeverity(i) >= m_RedSeverity) &&
                (pSymbol->GetRiskUE(i)       >= m_RedUE)       &&
                (pSymbol->GetRiskPOA(i)      >= m_RedPOA))
            {
                level = 2;
                break;
            }
    }

    switch (level)
    {
        case 1:
            // orange risk level
            if (!m_DefaultColors)
                pSymbol->UpdateGraphicFromRisk(RGB(255, 150, 0), TRUE);
            else
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);

            riskLevel.LoadString(IDS_Z_RISK_SERIOUS_LEVEL);
            pSymbol->SetRiskLevel(riskLevel);

            message.Format(IDS_Z_RISK_SERIOUS_MESSAGE, pSymbol->GetSymbolName());

            break;

        case 2:
            // red risk level
            if (!m_DefaultColors)
                pSymbol->UpdateGraphicFromRisk(RGB(255, 0, 0), TRUE);
            else
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);

            riskLevel.LoadString(IDS_Z_RISK_SEVERE_LEVEL);
            pSymbol->SetRiskLevel(riskLevel);

            message.Format(IDS_Z_RISK_SEVERE_MESSAGE, pSymbol->GetSymbolName());

            break;

        default:
            // normal risk level
            riskLevel.LoadString(IDS_Z_RISK_NORMAL_LEVEL);

            pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            pSymbol->SetRiskLevel(riskLevel);

            break;
    }

    if (!message.IsEmpty())
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(message, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 0);
            m_pLog->AddLine(e);
        }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CalculateRisks::CheckProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    CString   riskLevel;
    CString   message;
    int       level     = 0;
    const int riskCount = pSymbol->GetRiskCount();

    for (int i = 0; i < riskCount; ++i)
    {
        // orange level, check that the "Running action" and "No running action" checkboxes match the user configuration
        if ((m_OrangeAction   || m_OrangeNoAction)                 &&
           ((m_OrangeAction   == BOOL( pSymbol->GetRiskAction(i))) ||
            (m_OrangeNoAction == BOOL(!pSymbol->GetRiskAction(i))) ||
            (m_OrangeAction   && m_OrangeNoAction)))
            // check the input parameter levels entered by the user in relation to the risk levels
            if ((pSymbol->GetRiskSeverity(i) >= m_OrangeSeverity) &&
                (pSymbol->GetRiskUE(i)       >= m_OrangeUE)       &&
                (pSymbol->GetRiskPOA(i)      >= m_OrangePOA))
                level = 1;

        // red level, check that the "Running action" and "No running action" checkboxes match the user configuration
        if ((m_RedAction   || m_RedNoAction)                    &&
            ((m_RedAction  == BOOL( pSymbol->GetRiskAction(i))) ||
            (m_RedNoAction == BOOL(!pSymbol->GetRiskAction(i))) ||
             (m_RedAction  && m_RedNoAction)))
            // check the input parameter levels entered by the user in relation to the risk levels
            if ((pSymbol->GetRiskSeverity(i) >= m_RedSeverity) &&
                (pSymbol->GetRiskUE(i)       >= m_RedUE)       &&
                (pSymbol->GetRiskPOA(i)      >= m_RedPOA))
            {
                level = 2;
                break;
            }
    }

    switch (level)
    {
        case 1:
            // orange risk level
            if (!m_DefaultColors)
                pSymbol->UpdateGraphicFromRisk(RGB(255, 150, 0), TRUE);
            else
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);

            riskLevel.LoadString(IDS_Z_RISK_SERIOUS_LEVEL);
            pSymbol->SetRiskLevel(riskLevel);

            message.Format(IDS_Z_RISK_SERIOUS_MESSAGE, pSymbol->GetSymbolName());

            break;

        case 2:
            // red risk level
            if (!m_DefaultColors)
                pSymbol->UpdateGraphicFromRisk(RGB(255, 0, 0), TRUE);
            else
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);

            riskLevel.LoadString(IDS_Z_RISK_SEVERE_LEVEL);
            pSymbol->SetRiskLevel(riskLevel);

            message.Format(IDS_Z_RISK_SEVERE_MESSAGE, pSymbol->GetSymbolName());

            break;

        default:
            // normal risk level
            riskLevel.LoadString(IDS_Z_RISK_NORMAL_LEVEL);

            pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            pSymbol->SetRiskLevel(riskLevel);

            break;
    }

    if (message.IsEmpty() == false)
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(message, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 0);
            m_pLog->AddLine(e);
        }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CalculateRisks::CheckStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    CString   riskLevel;
    CString   message;
    int       level     = 0;
    const int riskCount = pSymbol->GetRiskCount();

    for (int i = 0; i < riskCount; ++i)
    {
        // orange level, check that the "Running action" and "No running action" checkboxes match the user configuration
        if ((m_OrangeAction   || m_OrangeNoAction)                 &&
           ((m_OrangeAction   == BOOL( pSymbol->GetRiskAction(i))) ||
            (m_OrangeNoAction == BOOL(!pSymbol->GetRiskAction(i))) ||
            (m_OrangeAction   && m_OrangeNoAction)))
            // check the input parameter levels entered by the user in relation to the risk levels
            if ((pSymbol->GetRiskSeverity(i) >= m_OrangeSeverity) &&
                (pSymbol->GetRiskUE(i)       >= m_OrangeUE)       &&
                (pSymbol->GetRiskPOA(i)      >= m_OrangePOA))
                level = 1;

        // red level, check that the "Running action" and "No running action" checkboxes match the user configuration
        if ((m_RedAction   || m_RedNoAction)                    &&
           ((m_RedAction   == BOOL( pSymbol->GetRiskAction(i))) ||
            (m_RedNoAction == BOOL(!pSymbol->GetRiskAction(i))) ||
            (m_RedAction   && m_RedNoAction)))
            // check the input parameter levels entered by the user in relation to the risk levels
            if ((pSymbol->GetRiskSeverity(i) >= m_RedSeverity) &&
                (pSymbol->GetRiskUE(i)       >= m_RedUE)       &&
                (pSymbol->GetRiskPOA(i)      >= m_RedPOA))
            {
                level = 2;
                break;
            }
    }

    switch (level)
    {
        case 1:
            // orange risk level
            if (!m_DefaultColors)
                pSymbol->UpdateGraphicFromRisk(RGB(255, 150, 0), TRUE);
            else
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);

            riskLevel.LoadString(IDS_Z_RISK_SERIOUS_LEVEL);
            pSymbol->SetRiskLevel(riskLevel);

            message.Format(IDS_Z_RISK_SERIOUS_MESSAGE, pSymbol->GetSymbolName());

            break;

        case 2:
            // red risk level
            if (!m_DefaultColors)
                pSymbol->UpdateGraphicFromRisk(RGB(255, 0, 0), TRUE);
            else
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);

            riskLevel.LoadString(IDS_Z_RISK_SEVERE_LEVEL);
            pSymbol->SetRiskLevel(riskLevel);

            message.Format(IDS_Z_RISK_SEVERE_MESSAGE, pSymbol->GetSymbolName());

            break;

        default:
            // normal risk level
            riskLevel.LoadString(IDS_Z_RISK_NORMAL_LEVEL);

            pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            pSymbol->SetRiskLevel(riskLevel);

            break;
    }

    if (!message.IsEmpty())
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(message, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 0);
            m_pLog->AddLine(e);
        }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CalculateRisks::CheckStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    CString   riskLevel;
    CString   message;
    int       level     = 0;
    const int riskCount = pSymbol->GetRiskCount();

    for (int i = 0; i < riskCount; ++i)
    {
        // orange level, check that the "Running action" and "No running action" checkboxes match the user configuration
        if ((m_OrangeAction   || m_OrangeNoAction)                 &&
           ((m_OrangeAction   == BOOL( pSymbol->GetRiskAction(i))) ||
            (m_OrangeNoAction == BOOL(!pSymbol->GetRiskAction(i))) ||
            (m_OrangeAction   && m_OrangeNoAction)))
            // check the input parameter levels entered by the user in relation to the risk levels
            if ((pSymbol->GetRiskSeverity(i) >= m_OrangeSeverity) &&
                (pSymbol->GetRiskUE(i)       >= m_OrangeUE)       &&
                (pSymbol->GetRiskPOA(i)      >= m_OrangePOA))
                level = 1;

        // red level, check that the "Running action" and "No running action" checkboxes match the user configuration
        if ((m_RedAction   || m_RedNoAction)                    &&
           ((m_RedAction   == BOOL( pSymbol->GetRiskAction(i))) ||
            (m_RedNoAction == BOOL(!pSymbol->GetRiskAction(i))) ||
            (m_RedAction   && m_RedNoAction)))
            // check the input parameter levels entered by the user in relation to the risk levels
            if ((pSymbol->GetRiskSeverity(i) >= m_RedSeverity) &&
                (pSymbol->GetRiskUE(i)       >= m_RedUE)       &&
                (pSymbol->GetRiskPOA(i)      >= m_RedPOA))
            {
                level = 2;
                break;
            }
    }

    switch (level)
    {
        case 1:
            // orange risk level
            if (!m_DefaultColors)
                pSymbol->UpdateGraphicFromRisk(RGB(255, 150, 0), TRUE);
            else
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);

            riskLevel.LoadString(IDS_Z_RISK_SERIOUS_LEVEL);
            pSymbol->SetRiskLevel(riskLevel);

            message.Format(IDS_Z_RISK_SERIOUS_MESSAGE, pSymbol->GetSymbolName());

            break;

        case 2:
            // red risk level
            if (!m_DefaultColors)
                pSymbol->UpdateGraphicFromRisk(RGB(255, 0, 0), TRUE);
            else
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);

            riskLevel.LoadString(IDS_Z_RISK_SEVERE_LEVEL);
            pSymbol->SetRiskLevel(riskLevel);

            message.Format(IDS_Z_RISK_SEVERE_MESSAGE, pSymbol->GetSymbolName());

            break;

        default:
            // normal risk level
            riskLevel.LoadString(IDS_Z_RISK_NORMAL_LEVEL);

            pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            pSymbol->SetRiskLevel(riskLevel);

            break;
    }

    if (!message.IsEmpty())
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(message, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 0);
            m_pLog->AddLine(e);
        }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CalculateRisks::CheckDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
{
    ASSERT(pSymbol);

    CString   riskLevel;
    CString   message;
    int       level     = 0;
    const int riskCount = pSymbol->GetRiskCount();

    for (int i = 0; i < riskCount; ++i)
    {
        // orange level, check that the "Running action" and "No running action" checkboxes match the user configuration
        if ((m_OrangeAction   || m_OrangeNoAction)                 &&
            ((m_OrangeAction  == BOOL( pSymbol->GetRiskAction(i))) ||
            (m_OrangeNoAction == BOOL(!pSymbol->GetRiskAction(i))) ||
             (m_OrangeAction  && m_OrangeNoAction)))
            // check the input parameter levels entered by the user in relation to the risk levels
            if ((pSymbol->GetRiskSeverity(i) >= m_OrangeSeverity) &&
                (pSymbol->GetRiskUE(i)       >= m_OrangeUE)       &&
                (pSymbol->GetRiskPOA(i)      >= m_OrangePOA))
                level = 1;

        // red level, check that the "Running action" and "No running action" checkboxes match the user configuration
        if ((m_RedAction   || m_RedNoAction) &&
           ((m_RedAction   == BOOL( pSymbol->GetRiskAction(i))) ||
            (m_RedNoAction == BOOL(!pSymbol->GetRiskAction(i))) ||
            (m_RedAction   && m_RedNoAction)))
            // check the input parameter levels entered by the user in relation to the risk levels
            if ((pSymbol->GetRiskSeverity(i) >= m_RedSeverity) &&
                (pSymbol->GetRiskUE(i)       >= m_RedUE) &&
                (pSymbol->GetRiskPOA(i)      >= m_RedPOA))
            {
                level = 2;
                break;
            }
    }

    switch (level)
    {
        case 1:
            // orange risk level
            if (!m_DefaultColors)
                pSymbol->UpdateGraphicFromRisk(RGB(255, 150, 0), TRUE);
            else
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);

            riskLevel.LoadString(IDS_Z_RISK_SERIOUS_LEVEL);
            pSymbol->SetRiskLevel(riskLevel);

            message.Format(IDS_Z_RISK_SERIOUS_MESSAGE, pSymbol->GetSymbolName());

            break;

        case 2:
            // red risk level
            if (!m_DefaultColors)
                pSymbol->UpdateGraphicFromRisk(RGB(255, 0, 0), TRUE);
            else
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);

            riskLevel.LoadString(IDS_Z_RISK_SEVERE_LEVEL);
            pSymbol->SetRiskLevel(riskLevel);

            message.Format(IDS_Z_RISK_SEVERE_MESSAGE, pSymbol->GetSymbolName());

            break;

        default:
            // normal risk level
            riskLevel.LoadString(IDS_Z_RISK_NORMAL_LEVEL);

            pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            pSymbol->SetRiskLevel(riskLevel);

            break;
    }

    if (!message.IsEmpty())
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(message, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 0);
            m_pLog->AddLine(e);
        }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CalculateRisks::CheckSymbol(PSS_Symbol* pSymbol)
{
    ASSERT(pSymbol);
    return true;
}
//---------------------------------------------------------------------------
bool PSS_CalculateRisks::CheckLink(PSS_LinkSymbol* pLink)
{
    ASSERT(pLink);
    return true;
}
//---------------------------------------------------------------------------
