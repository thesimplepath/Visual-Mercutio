/****************************************************************************
 * ==> PSS_MenuObserverMsg -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a menu observer message                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_MenuObserverMsg.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_MenuObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_MenuObserverMsg
//---------------------------------------------------------------------------
PSS_MenuObserverMsg::PSS_MenuObserverMsg(int commandID) :
    PSS_ObserverMsg(),
    m_CommandID(commandID)
{}
//---------------------------------------------------------------------------
PSS_MenuObserverMsg::~PSS_MenuObserverMsg()
{}
//---------------------------------------------------------------------------
