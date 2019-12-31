// ZBUnitObserverMsg.cpp: implementation of the ZBUnitObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBUnitObserverMsg.h"
#include "PSS_Symbol.h"
#include "PSS_Unit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(ZBUnitObserverMsg, PSS_ObserverMsg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBUnitObserverMsg::ZBUnitObserverMsg(MessageActionType ActionType /*= NoAction*/,
                                     ZBUnitManager* pUnitManager /*= NULL*/,
                                     PSS_Unit* pUnit /*= NULL*/,
                                     PSS_Symbol* pElement /*= NULL*/) :
    PSS_ObserverMsg(),
    m_ActionType(ActionType),
    m_pUnitManager(pUnitManager),
    m_pUnit(pUnit),
    m_pElement(pElement)
{}

ZBUnitObserverMsg::~ZBUnitObserverMsg()
{}
