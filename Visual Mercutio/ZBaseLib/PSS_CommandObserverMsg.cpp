/****************************************************************************
 * ==> PSS_CommandObserverMsg ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a message for the command observer                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CommandObserverMsg.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_CommandObserverMsg, ZIObserverMsg)
//---------------------------------------------------------------------------
// PSS_CommandObserverMsg
//---------------------------------------------------------------------------
PSS_CommandObserverMsg::PSS_CommandObserverMsg(int commandID) :
    m_CommandID(commandID)
{}
//---------------------------------------------------------------------------
PSS_CommandObserverMsg::~PSS_CommandObserverMsg()
{}
//---------------------------------------------------------------------------
