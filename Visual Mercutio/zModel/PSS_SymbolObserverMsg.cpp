/****************************************************************************
 * ==> PSS_SymbolObserverMsg -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol observer message                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SymbolObserverMsg.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_SymbolObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_SymbolObserverMsg
//---------------------------------------------------------------------------
PSS_SymbolObserverMsg::PSS_SymbolObserverMsg(IEActionType actionType, CODComponent* pElement) :
    PSS_ObserverMsg(),
    m_pElement(pElement),
    m_ActionType(actionType),
    m_SymbolRef(-1)
{}
//---------------------------------------------------------------------------
PSS_SymbolObserverMsg::PSS_SymbolObserverMsg(int symbolRef, IEActionType actionType) :
    PSS_ObserverMsg(),
    m_pElement(NULL),
    m_ActionType(actionType),
    m_SymbolRef(symbolRef)
{}
//---------------------------------------------------------------------------
PSS_SymbolObserverMsg::~PSS_SymbolObserverMsg()
{}
//---------------------------------------------------------------------------
