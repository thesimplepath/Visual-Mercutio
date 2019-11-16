/****************************************************************************
 * ==> PSS_ToolbarObserverMsg ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a toolbar observer message                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ToolbarObserverMsg.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ToolbarObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_ToolbarObserverMsg
//---------------------------------------------------------------------------
PSS_ToolbarObserverMsg::PSS_ToolbarObserverMsg(UINT messageID) :
    PSS_ObserverMsg(),
    m_MessageID(messageID)
{}
//---------------------------------------------------------------------------
PSS_ToolbarObserverMsg::~PSS_ToolbarObserverMsg()
{}
//---------------------------------------------------------------------------
