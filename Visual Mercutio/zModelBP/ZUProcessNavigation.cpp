// ZUProcessNavigation.cpp: implementation of the ZUProcessNavigation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUProcessNavigation.h"

#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModelBP\PSS_DoorSymbolBP.h"
#include "zModelBP\PSS_PageSymbolBP.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 28 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUProcessNavigation::ZUProcessNavigation(PSS_ProcessGraphModelMdl* pModel /*= NULL*/, void* pClass /*= NULL*/)
    : m_pModel(pModel),
    m_pClass(pClass)
{}

ZUProcessNavigation::~ZUProcessNavigation()
{}

bool ZUProcessNavigation::Navigate(PSS_ProcessGraphModelMdl* pModel, void* pClass)
{
    m_pModel = pModel;
    m_pClass = pClass;
    return ZUProcessNavigation::Navigate();
}

bool ZUProcessNavigation::Navigate(PSS_ProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;
    return ZUProcessNavigation::Navigate();
}

bool ZUProcessNavigation::Navigate()
{
    if (m_pModel)
    {
        // Initialize counters
        m_ErrorCounter = 0;
        m_WarningCounter = 0;

        // Call the OnStart method
        if (!OnStart())
        {
            return false;
        }

        // Process the model
        m_pModel->AcceptVisitor(*this);

        // Call the OnFinish method and returns its retval.
        return OnFinish();
    }

    return false;
}

bool ZUProcessNavigation::Visit(CODComponent& Symbol)
{
    CODComponent* pSymbol = &Symbol;

    if (ISA(pSymbol, ZBBPProcedureSymbol))
    {
        return OnProcedureSymbol(dynamic_cast<ZBBPProcedureSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBDeliverableLinkSymbol))
    {
        return OnDeliverableLinkSymbol(dynamic_cast<ZBDeliverableLinkSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_DoorSymbolBP))
    {
        return OnDoorSymbol(dynamic_cast<PSS_DoorSymbolBP*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_PageSymbolBP))
    {
        return OnPageSymbol(dynamic_cast<PSS_PageSymbolBP*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPProcessSymbol))
    {
        return OnProcessSymbol(dynamic_cast<ZBBPProcessSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPStartSymbol))
    {
        return OnStartSymbol(dynamic_cast<ZBBPStartSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, ZBBPStopSymbol))
    {
        return OnStopSymbol(dynamic_cast<ZBBPStopSymbol*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_Symbol))
    {
        return OnSymbol(dynamic_cast<PSS_Symbol*>(&Symbol));
    }
    else if (ISA(pSymbol, PSS_LinkSymbol))
    {
        return OnLink(dynamic_cast<PSS_LinkSymbol*>(&Symbol));
    }

    // Not a right symbol or not necessary to visit
    return false;
}
