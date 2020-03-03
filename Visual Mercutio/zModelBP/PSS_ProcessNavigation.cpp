/****************************************************************************
 * ==> PSS_ProcessNavigation -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to visit the proces symbols           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessNavigation.h"

// processsoft
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "PSS_DoorSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "PSS_StopSymbolBP.h"
#include "PSS_DeliverableLinkSymbolBP.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ProcessNavigation
//---------------------------------------------------------------------------
PSS_ProcessNavigation::PSS_ProcessNavigation(PSS_ProcessGraphModelMdl* pModel, void* pClass) :
    PSS_BasicSymbolVisitor(),
    m_pModel(pModel),
    m_pLog(NULL),
    m_pClass(pClass),
    m_ErrorCounter(0),
    m_WarningCounter(0)
{}
//---------------------------------------------------------------------------
PSS_ProcessNavigation::~PSS_ProcessNavigation()
{}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::Navigate(PSS_ProcessGraphModelMdl* pModel, void* pClass)
{
    m_pModel = pModel;
    m_pClass = pClass;

    return Navigate();
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::Navigate(PSS_ProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;

    return Navigate();
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::Navigate()
{
    if (m_pModel)
    {
        // initialize the counters
        m_ErrorCounter   = 0;
        m_WarningCounter = 0;

        // notify that the navigation started
        if (!OnStart())
            return false;

        // process the model
        m_pModel->AcceptVisitor(*this);

        // notify that the navigation ended
        return OnFinish();
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessNavigation::Visit(CODComponent& component)
{
    CODComponent* pComponent = &component;

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
        return OnProcedureSymbol(pProcedure);
    else
    if (pDeliverable)
        return OnDeliverableLinkSymbol(pDeliverable);
    else
    if (pDoor)
        return OnDoorSymbol(pDoor);
    else
    if (pPage)
        return OnPageSymbol(pPage);
    else
    if (pProcess)
        return OnProcessSymbol(pProcess);
    else
    if (pStart)
        return OnStartSymbol(pStart);
    else
    if (pStop)
        return OnStopSymbol(pStop);
    else
    if (pSymbol)
        return OnSymbol(pSymbol);
    else
    if (pLinkSymbol)
        return OnLink(pLinkSymbol);

    // not a symbol or not needed to be visited
    return false;
}
//---------------------------------------------------------------------------
