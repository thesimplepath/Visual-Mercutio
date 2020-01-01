/****************************************************************************
 * ==> PSS_UnitObserverMsg -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an unit observer message                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UnitObserverMsg.h"

// processsoft
#include "PSS_Symbol.h"
#include "PSS_Unit.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_UnitObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_UnitObserverMsg
//---------------------------------------------------------------------------
PSS_UnitObserverMsg::PSS_UnitObserverMsg(IEActionType     actionType,
                                         PSS_UnitManager* pUnitManager,
                                         PSS_Unit*        pUnit,
                                         PSS_Symbol*      pElement) :
    PSS_ObserverMsg(),
    m_pUnitManager(pUnitManager),
    m_pUnit(pUnit),
    m_pElement(pElement),
    m_ActionType(actionType)
{}
//---------------------------------------------------------------------------
PSS_UnitObserverMsg::~PSS_UnitObserverMsg()
{}
//---------------------------------------------------------------------------
