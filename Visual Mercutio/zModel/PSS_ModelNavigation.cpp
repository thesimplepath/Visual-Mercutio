/****************************************************************************
 * ==> PSS_ModelNavigation -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic model navigator                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ModelNavigation.h"

// processsoft
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"

// resources
#include "zModelRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ModelNavigation
//---------------------------------------------------------------------------
PSS_ModelNavigation::PSS_ModelNavigation(PSS_ProcessGraphModelMdl* pModel, void* pClass) :
    PSS_BasicSymbolVisitor(),
    m_pModel(pModel),
    m_pLog(NULL),
    m_pClass(pClass)
{}
//---------------------------------------------------------------------------
PSS_ModelNavigation::~PSS_ModelNavigation()
{}
//---------------------------------------------------------------------------
bool PSS_ModelNavigation::Navigate(PSS_ProcessGraphModelMdl* pModel, void* pClass)
{
    m_pModel = pModel;
    m_pClass = pClass;

    return Navigate();
}
//---------------------------------------------------------------------------
bool PSS_ModelNavigation::Navigate(PSS_ProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;

    return Navigate();
}
//---------------------------------------------------------------------------
bool PSS_ModelNavigation::Navigate()
{
    // no model, nothing to do
    if (!m_pModel)
        return false;

    // start the navigation
    if (!OnStart())
        return false;

    // process the model
    m_pModel->AcceptVisitor(*this);

    // end the navigation
    return OnFinish();
}
//---------------------------------------------------------------------------
bool PSS_ModelNavigation::Visit(CODComponent& symbol)
{
    CODComponent*   pComp       = &symbol;
    PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
    PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

    if (pSymbol)
        return OnSymbol(pSymbol);
    else
    if (pLinkSymbol)
        return OnLink(pLinkSymbol);

    // not a valid symbol or no need to visit
    return false;
}
//---------------------------------------------------------------------------
bool PSS_ModelNavigation::OnStart()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelNavigation::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelNavigation::OnSymbol(PSS_Symbol* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelNavigation::OnLink(PSS_LinkSymbol* pLink)
{
    return true;
}
//---------------------------------------------------------------------------
