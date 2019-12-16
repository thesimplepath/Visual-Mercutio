// **************************************************************************************************************
// *                                             Classe ZUCalculateRisks                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 21 juillet 2007 - Ajout de la classe ZUCalculateRisks.                                        *
// **************************************************************************************************************
// * Cette classe permet de calculer le niveau des risques dans le modèle.                                        *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZUCalculateRisks.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_ProcessGraphModelController.h"
#include "zModel\ZUODSymbolManipulator.h"
#include "zModel\ZBGenericSymbolErrorLine.h"
#include "ZBBPDoorSymbol.h"
#include "ZBBPPageSymbol.h"
#include "ZBBPProcedureSymbol.h"
#include "ZBBPProcessSymbol.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"
#include "ZBDeliverableLinkSymbol.h"
#include "ProcGraphModelMdlBP.h"
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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUCalculateRisks::ZUCalculateRisks(int                        OrangeSeverity,
                                   int                        RedSeverity,
                                   float                    OrangeUE,
                                   float                    RedUE,
                                   float                    OrangePOA,
                                   float                    RedPOA,
                                   BOOL                    OrangeAction,
                                   BOOL                    OrangeNoAction,
                                   BOOL                    RedAction,
                                   BOOL                    RedNoAction,
                                   BOOL                    DefaultColors,
                                   PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                   PSS_Log*                    pLog    /*= NULL*/)
    : m_OrangeSeverity(OrangeSeverity),
    m_RedSeverity(RedSeverity),
    m_OrangeUE(OrangeUE),
    m_RedUE(RedUE),
    m_OrangePOA(OrangePOA),
    m_RedPOA(RedPOA),
    m_OrangeAction(OrangeAction),
    m_OrangeNoAction(OrangeNoAction),
    m_RedAction(RedAction),
    m_RedNoAction(RedNoAction),
    m_DefaultColors(DefaultColors),
    m_pModel(pModel),
    m_pLog(pLog)
{}

ZUCalculateRisks::~ZUCalculateRisks()
{}

bool ZUCalculateRisks::Calculate(CODComponent& Symbol)
{
    // If log required
    if (m_pLog && m_pLog->InitializeLog())
    {
        // Initialize counters
        m_OrangeCounter = 0;
        m_RedCounter = 0;

        m_pLog->ClearLog();

        CString Message = _T("");
        Message.LoadString(IDS_RISK_CALCULATE_START);

        ZBGenericSymbolErrorLine e(Message);
        m_pLog->AddLine(e);
    }

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
        CString Message = _T("");

        if (m_OrangeCounter > 0 || m_RedCounter > 0)
        {
            Message.Format(IDS_RISK_CALCULATE_END_INFOS, m_OrangeCounter, m_RedCounter);
        }
        else
        {
            Message.LoadString(IDS_RISK_CALCULATE_END);
        }

        ZBGenericSymbolErrorLine e(Message);
        m_pLog->AddLine(e);
    }

    PSS_Application::Instance()->GetMainForm()->DoRefreshProperties();

    return true;
}

bool ZUCalculateRisks::Visit(CODComponent& Symbol)
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

bool ZUCalculateRisks::CheckDoorSymbol(ZBBPDoorSymbol* pSymbol)
{
    ASSERT(pSymbol);
    return true;
}

bool ZUCalculateRisks::CheckPageSymbol(ZBBPPageSymbol* pSymbol)
{
    ASSERT(pSymbol);
    return true;
}

bool ZUCalculateRisks::CheckProcedureSymbol(ZBBPProcedureSymbol* pSymbol)
{
    ASSERT(pSymbol);

    CString    s_RiskLevel = _T("");
    CString    s_Message = _T("");
    int        i_Level = 0;

    for (int i = 0; i < pSymbol->GetRiskCount(); i++)
    {
        // Niveau orange:
        // Contrôle que les cases "Action en cours" et "Pas d'action en cours" correspondent aux demandes de l'utilisateur.
        if ((m_OrangeAction != FALSE || m_OrangeNoAction != FALSE) &&
            ((m_OrangeAction == (BOOL)pSymbol->GetRiskAction(i)) ||
            (m_OrangeNoAction == (BOOL)!pSymbol->GetRiskAction(i)) ||
             (m_OrangeAction == TRUE && m_OrangeNoAction == TRUE)))
        {
            // Contrôle les niveaux des paramètres entrés par l'utilisateur par rapport aux niveaux des risques.
            if ((pSymbol->GetRiskSeverity(i) >= m_OrangeSeverity) &&
                (pSymbol->GetRiskUE(i) >= m_OrangeUE) &&
                (pSymbol->GetRiskPOA(i) >= m_OrangePOA))
            {
                i_Level = 1;
            }
        }

        // Niveau rouge:
        // Contrôle que les cases "Action en cours" et "Pas d'action en cours" correspondent aux demandes de l'utilisateur.
        if ((m_RedAction != FALSE || m_RedNoAction != FALSE) &&
            ((m_RedAction == (BOOL)pSymbol->GetRiskAction(i)) ||
            (m_RedNoAction == (BOOL)!pSymbol->GetRiskAction(i)) ||
             (m_RedAction == TRUE && m_RedNoAction == TRUE)))
        {
            // Contrôle les niveaux des paramètres entrés par l'utilisateur par rapport aux niveaux des risques.
            if ((pSymbol->GetRiskSeverity(i) >= m_RedSeverity) &&
                (pSymbol->GetRiskUE(i) >= m_RedUE) &&
                (pSymbol->GetRiskPOA(i) >= m_RedPOA))
            {
                i_Level = 2;
                break;
            }
        }
    }

    switch (i_Level)
    {
        // Niveau de risque orange.
        case 1:
        {
            if (m_DefaultColors == FALSE)
            {
                pSymbol->UpdateGraphicFromRisk(RGB(255, 150, 0), TRUE);
            }
            else
            {
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            }

            s_RiskLevel.LoadString(IDS_Z_RISK_SERIOUS_LEVEL);
            pSymbol->SetRiskLevel(s_RiskLevel);

            s_Message.Format(IDS_Z_RISK_SERIOUS_MESSAGE, pSymbol->GetSymbolName());

            break;
        }

        // Niveau de risque rouge.
        case 2:
        {
            if (m_DefaultColors == FALSE)
            {
                pSymbol->UpdateGraphicFromRisk(RGB(255, 0, 0), TRUE);
            }
            else
            {
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            }

            s_RiskLevel.LoadString(IDS_Z_RISK_SEVERE_LEVEL);
            pSymbol->SetRiskLevel(s_RiskLevel);

            s_Message.Format(IDS_Z_RISK_SEVERE_MESSAGE, pSymbol->GetSymbolName());

            break;
        }

        // Niveau de risque normal.
        default:
        {
            s_RiskLevel.LoadString(IDS_Z_RISK_NORMAL_LEVEL);

            pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            pSymbol->SetRiskLevel(s_RiskLevel);

            break;
        }
    }

    if (s_Message.IsEmpty() == false)
    {
        if (m_pLog)
        {
            ZBGenericSymbolErrorLine e(s_Message,
                                       pSymbol->GetSymbolName(),
                                       pSymbol->GetAbsolutePath(),
                                       -1,
                                       0);

            m_pLog->AddLine(e);
        }
    }

    return true;
}

bool ZUCalculateRisks::CheckProcessSymbol(ZBBPProcessSymbol* pSymbol)
{
    ASSERT(pSymbol);

    CString    s_RiskLevel = _T("");
    CString    s_Message = _T("");
    int        i_Level = 0;

    for (int i = 0; i < pSymbol->GetRiskCount(); i++)
    {
        // Niveau orange:
        // Contrôle que les cases "Action en cours" et "Pas d'action en cours" correspondent aux demandes de l'utilisateur.
        if ((m_OrangeAction != FALSE || m_OrangeNoAction != FALSE) &&
            ((m_OrangeAction == (BOOL)pSymbol->GetRiskAction(i)) ||
            (m_OrangeNoAction == (BOOL)!pSymbol->GetRiskAction(i)) ||
             (m_OrangeAction == TRUE && m_OrangeNoAction == TRUE)))
        {
            // Contrôle les niveaux des paramètres entrés par l'utilisateur par rapport aux niveaux des risques.
            if ((pSymbol->GetRiskSeverity(i) >= m_OrangeSeverity) &&
                (pSymbol->GetRiskUE(i) >= m_OrangeUE) &&
                (pSymbol->GetRiskPOA(i) >= m_OrangePOA))
            {
                i_Level = 1;
            }
        }

        // Niveau rouge:
        // Contrôle que les cases "Action en cours" et "Pas d'action en cours" correspondent aux demandes de l'utilisateur.
        if ((m_RedAction != FALSE || m_RedNoAction != FALSE) &&
            ((m_RedAction == (BOOL)pSymbol->GetRiskAction(i)) ||
            (m_RedNoAction == (BOOL)!pSymbol->GetRiskAction(i)) ||
             (m_RedAction == TRUE && m_RedNoAction == TRUE)))
        {
            // Contrôle les niveaux des paramètres entrés par l'utilisateur par rapport aux niveaux des risques.
            if ((pSymbol->GetRiskSeverity(i) >= m_RedSeverity) &&
                (pSymbol->GetRiskUE(i) >= m_RedUE) &&
                (pSymbol->GetRiskPOA(i) >= m_RedPOA))
            {
                i_Level = 2;
                break;
            }
        }
    }

    switch (i_Level)
    {
        // Niveau de risque orange.
        case 1:
        {
            if (m_DefaultColors == FALSE)
            {
                pSymbol->UpdateGraphicFromRisk(RGB(255, 150, 0), TRUE);
            }
            else
            {
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            }

            s_RiskLevel.LoadString(IDS_Z_RISK_SERIOUS_LEVEL);
            pSymbol->SetRiskLevel(s_RiskLevel);

            s_Message.Format(IDS_Z_RISK_SERIOUS_MESSAGE, pSymbol->GetSymbolName());

            break;
        }

        // Niveau de risque rouge.
        case 2:
        {
            if (m_DefaultColors == FALSE)
            {
                pSymbol->UpdateGraphicFromRisk(RGB(255, 0, 0), TRUE);
            }
            else
            {
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            }

            s_RiskLevel.LoadString(IDS_Z_RISK_SEVERE_LEVEL);
            pSymbol->SetRiskLevel(s_RiskLevel);

            s_Message.Format(IDS_Z_RISK_SEVERE_MESSAGE, pSymbol->GetSymbolName());

            break;
        }

        // Niveau de risque normal.
        default:
        {
            s_RiskLevel.LoadString(IDS_Z_RISK_NORMAL_LEVEL);

            pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            pSymbol->SetRiskLevel(s_RiskLevel);

            break;
        }
    }

    if (s_Message.IsEmpty() == false)
    {
        if (m_pLog)
        {
            ZBGenericSymbolErrorLine e(s_Message,
                                       pSymbol->GetSymbolName(),
                                       pSymbol->GetAbsolutePath(),
                                       -1,
                                       0);

            m_pLog->AddLine(e);
        }
    }

    return true;
}

bool ZUCalculateRisks::CheckStartSymbol(ZBBPStartSymbol* pSymbol)
{
    ASSERT(pSymbol);

    CString    s_RiskLevel = _T("");
    CString    s_Message = _T("");
    int        i_Level = 0;

    for (int i = 0; i < pSymbol->GetRiskCount(); i++)
    {
        // Niveau orange:
        // Contrôle que les cases "Action en cours" et "Pas d'action en cours" correspondent aux demandes de l'utilisateur.
        if ((m_OrangeAction != FALSE || m_OrangeNoAction != FALSE) &&
            ((m_OrangeAction == (BOOL)pSymbol->GetRiskAction(i)) ||
            (m_OrangeNoAction == (BOOL)!pSymbol->GetRiskAction(i)) ||
             (m_OrangeAction == TRUE && m_OrangeNoAction == TRUE)))
        {
            // Contrôle les niveaux des paramètres entrés par l'utilisateur par rapport aux niveaux des risques.
            if ((pSymbol->GetRiskSeverity(i) >= m_OrangeSeverity) &&
                (pSymbol->GetRiskUE(i) >= m_OrangeUE) &&
                (pSymbol->GetRiskPOA(i) >= m_OrangePOA))
            {
                i_Level = 1;
            }
        }

        // Niveau rouge:
        // Contrôle que les cases "Action en cours" et "Pas d'action en cours" correspondent aux demandes de l'utilisateur.
        if ((m_RedAction != FALSE || m_RedNoAction != FALSE) &&
            ((m_RedAction == (BOOL)pSymbol->GetRiskAction(i)) ||
            (m_RedNoAction == (BOOL)!pSymbol->GetRiskAction(i)) ||
             (m_RedAction == TRUE && m_RedNoAction == TRUE)))
        {
            // Contrôle les niveaux des paramètres entrés par l'utilisateur par rapport aux niveaux des risques.
            if ((pSymbol->GetRiskSeverity(i) >= m_RedSeverity) &&
                (pSymbol->GetRiskUE(i) >= m_RedUE) &&
                (pSymbol->GetRiskPOA(i) >= m_RedPOA))
            {
                i_Level = 2;
                break;
            }
        }
    }

    switch (i_Level)
    {
        // Niveau de risque orange.
        case 1:
        {
            if (m_DefaultColors == FALSE)
            {
                pSymbol->UpdateGraphicFromRisk(RGB(255, 150, 0), TRUE);
            }
            else
            {
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            }

            s_RiskLevel.LoadString(IDS_Z_RISK_SERIOUS_LEVEL);
            pSymbol->SetRiskLevel(s_RiskLevel);

            s_Message.Format(IDS_Z_RISK_SERIOUS_MESSAGE, pSymbol->GetSymbolName());

            break;
        }

        // Niveau de risque rouge.
        case 2:
        {
            if (m_DefaultColors == FALSE)
            {
                pSymbol->UpdateGraphicFromRisk(RGB(255, 0, 0), TRUE);
            }
            else
            {
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            }

            s_RiskLevel.LoadString(IDS_Z_RISK_SEVERE_LEVEL);
            pSymbol->SetRiskLevel(s_RiskLevel);

            s_Message.Format(IDS_Z_RISK_SEVERE_MESSAGE, pSymbol->GetSymbolName());

            break;
        }

        // Niveau de risque normal.
        default:
        {
            s_RiskLevel.LoadString(IDS_Z_RISK_NORMAL_LEVEL);

            pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            pSymbol->SetRiskLevel(s_RiskLevel);

            break;
        }
    }

    if (s_Message.IsEmpty() == false)
    {
        if (m_pLog)
        {
            ZBGenericSymbolErrorLine e(s_Message,
                                       pSymbol->GetSymbolName(),
                                       pSymbol->GetAbsolutePath(),
                                       -1,
                                       0);

            m_pLog->AddLine(e);
        }
    }

    return true;
}

bool ZUCalculateRisks::CheckStopSymbol(ZBBPStopSymbol* pSymbol)
{
    ASSERT(pSymbol);

    CString    s_RiskLevel = _T("");
    CString    s_Message = _T("");
    int        i_Level = 0;

    for (int i = 0; i < pSymbol->GetRiskCount(); i++)
    {
        // Niveau orange:
        // Contrôle que les cases "Action en cours" et "Pas d'action en cours" correspondent aux demandes de l'utilisateur.
        if ((m_OrangeAction != FALSE || m_OrangeNoAction != FALSE) &&
            ((m_OrangeAction == (BOOL)pSymbol->GetRiskAction(i)) ||
            (m_OrangeNoAction == (BOOL)!pSymbol->GetRiskAction(i)) ||
             (m_OrangeAction == TRUE && m_OrangeNoAction == TRUE)))
        {
            // Contrôle les niveaux des paramètres entrés par l'utilisateur par rapport aux niveaux des risques.
            if ((pSymbol->GetRiskSeverity(i) >= m_OrangeSeverity) &&
                (pSymbol->GetRiskUE(i) >= m_OrangeUE) &&
                (pSymbol->GetRiskPOA(i) >= m_OrangePOA))
            {
                i_Level = 1;
            }
        }

        // Niveau rouge:
        // Contrôle que les cases "Action en cours" et "Pas d'action en cours" correspondent aux demandes de l'utilisateur.
        if ((m_RedAction != FALSE || m_RedNoAction != FALSE) &&
            ((m_RedAction == (BOOL)pSymbol->GetRiskAction(i)) ||
            (m_RedNoAction == (BOOL)!pSymbol->GetRiskAction(i)) ||
             (m_RedAction == TRUE && m_RedNoAction == TRUE)))
        {
            // Contrôle les niveaux des paramètres entrés par l'utilisateur par rapport aux niveaux des risques.
            if ((pSymbol->GetRiskSeverity(i) >= m_RedSeverity) &&
                (pSymbol->GetRiskUE(i) >= m_RedUE) &&
                (pSymbol->GetRiskPOA(i) >= m_RedPOA))
            {
                i_Level = 2;
                break;
            }
        }
    }

    switch (i_Level)
    {
        // Niveau de risque orange.
        case 1:
        {
            if (m_DefaultColors == FALSE)
            {
                pSymbol->UpdateGraphicFromRisk(RGB(255, 150, 0), TRUE);
            }
            else
            {
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            }

            s_RiskLevel.LoadString(IDS_Z_RISK_SERIOUS_LEVEL);
            pSymbol->SetRiskLevel(s_RiskLevel);

            s_Message.Format(IDS_Z_RISK_SERIOUS_MESSAGE, pSymbol->GetSymbolName());

            break;
        }

        // Niveau de risque rouge.
        case 2:
        {
            if (m_DefaultColors == FALSE)
            {
                pSymbol->UpdateGraphicFromRisk(RGB(255, 0, 0), TRUE);
            }
            else
            {
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            }

            s_RiskLevel.LoadString(IDS_Z_RISK_SEVERE_LEVEL);
            pSymbol->SetRiskLevel(s_RiskLevel);

            s_Message.Format(IDS_Z_RISK_SEVERE_MESSAGE, pSymbol->GetSymbolName());

            break;
        }

        // Niveau de risque normal.
        default:
        {
            s_RiskLevel.LoadString(IDS_Z_RISK_NORMAL_LEVEL);

            pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            pSymbol->SetRiskLevel(s_RiskLevel);

            break;
        }
    }

    if (s_Message.IsEmpty() == false)
    {
        if (m_pLog)
        {
            ZBGenericSymbolErrorLine e(s_Message,
                                       pSymbol->GetSymbolName(),
                                       pSymbol->GetAbsolutePath(),
                                       -1,
                                       0);

            m_pLog->AddLine(e);
        }
    }

    return true;
}

bool ZUCalculateRisks::CheckDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol)
{
    ASSERT(pSymbol);

    CString    s_RiskLevel = _T("");
    CString    s_Message = _T("");
    int        i_Level = 0;

    for (int i = 0; i < pSymbol->GetRiskCount(); i++)
    {
        // Niveau orange:
        // Contrôle que les cases "Action en cours" et "Pas d'action en cours" correspondent aux demandes de l'utilisateur.
        if ((m_OrangeAction != FALSE || m_OrangeNoAction != FALSE) &&
            ((m_OrangeAction == (BOOL)pSymbol->GetRiskAction(i)) ||
            (m_OrangeNoAction == (BOOL)!pSymbol->GetRiskAction(i)) ||
             (m_OrangeAction == TRUE && m_OrangeNoAction == TRUE)))
        {
            // Contrôle les niveaux des paramètres entrés par l'utilisateur par rapport aux niveaux des risques.
            if ((pSymbol->GetRiskSeverity(i) >= m_OrangeSeverity) &&
                (pSymbol->GetRiskUE(i) >= m_OrangeUE) &&
                (pSymbol->GetRiskPOA(i) >= m_OrangePOA))
            {
                i_Level = 1;
            }
        }

        // Niveau rouge:
        // Contrôle que les cases "Action en cours" et "Pas d'action en cours" correspondent aux demandes de l'utilisateur.
        if ((m_RedAction != FALSE || m_RedNoAction != FALSE) &&
            ((m_RedAction == (BOOL)pSymbol->GetRiskAction(i)) ||
            (m_RedNoAction == (BOOL)!pSymbol->GetRiskAction(i)) ||
             (m_RedAction == TRUE && m_RedNoAction == TRUE)))
        {
            // Contrôle les niveaux des paramètres entrés par l'utilisateur par rapport aux niveaux des risques.
            if ((pSymbol->GetRiskSeverity(i) >= m_RedSeverity) &&
                (pSymbol->GetRiskUE(i) >= m_RedUE) &&
                (pSymbol->GetRiskPOA(i) >= m_RedPOA))
            {
                i_Level = 2;
                break;
            }
        }
    }

    switch (i_Level)
    {
        // Niveau de risque orange.
        case 1:
        {
            if (m_DefaultColors == FALSE)
            {
                pSymbol->UpdateGraphicFromRisk(RGB(255, 150, 0), TRUE);
            }
            else
            {
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            }

            s_RiskLevel.LoadString(IDS_Z_RISK_SERIOUS_LEVEL);
            pSymbol->SetRiskLevel(s_RiskLevel);

            s_Message.Format(IDS_Z_RISK_SERIOUS_MESSAGE, pSymbol->GetSymbolName());

            break;
        }

        // Niveau de risque rouge.
        case 2:
        {
            if (m_DefaultColors == FALSE)
            {
                pSymbol->UpdateGraphicFromRisk(RGB(255, 0, 0), TRUE);
            }
            else
            {
                pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            }

            s_RiskLevel.LoadString(IDS_Z_RISK_SEVERE_LEVEL);
            pSymbol->SetRiskLevel(s_RiskLevel);

            s_Message.Format(IDS_Z_RISK_SEVERE_MESSAGE, pSymbol->GetSymbolName());

            break;
        }

        // Niveau de risque normal.
        default:
        {
            s_RiskLevel.LoadString(IDS_Z_RISK_NORMAL_LEVEL);

            pSymbol->UpdateGraphicFromRisk(RGB(0, 0, 0), FALSE);
            pSymbol->SetRiskLevel(s_RiskLevel);

            break;
        }
    }

    if (s_Message.IsEmpty() == false)
    {
        if (m_pLog)
        {
            ZBGenericSymbolErrorLine e(s_Message,
                                       pSymbol->GetSymbolName(),
                                       pSymbol->GetAbsolutePath(),
                                       -1,
                                       0);

            m_pLog->AddLine(e);
        }
    }

    return true;
}

bool ZUCalculateRisks::CheckSymbol(PSS_Symbol* pSymbol)
{
    ASSERT(pSymbol);
    return true;
}

bool ZUCalculateRisks::CheckLink(PSS_LinkSymbol* pLink)
{
    ASSERT(pLink);
    return true;
}
