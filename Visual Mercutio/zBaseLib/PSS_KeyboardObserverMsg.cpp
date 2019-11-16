/****************************************************************************
 * ==> PSS_KeyboardObserverMsg ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a keyboard observer message                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_KeyboardObserverMsg.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_KeyboardObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_KeyboardObserverMsg
//---------------------------------------------------------------------------
PSS_KeyboardObserverMsg::PSS_KeyboardObserverMsg(UINT messageID, UINT key) :
    PSS_ObserverMsg(),
    m_MessageID(messageID),
    m_Key(key)
{}
//---------------------------------------------------------------------------
PSS_KeyboardObserverMsg::~PSS_KeyboardObserverMsg()
{}
//---------------------------------------------------------------------------
