/****************************************************************************
 * ==> PSS_LogicalSystemObserverMsg ----------------------------------------*
 ****************************************************************************
 * Description : Provides a logical system observer message                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LogicalSystemObserverMsg.h"

// processsoft
#include "ZBSystemEntity.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_LogicalSystemObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_LogicalSystemObserverMsg
//---------------------------------------------------------------------------
PSS_LogicalSystemObserverMsg::PSS_LogicalSystemObserverMsg(UINT            messageID,
                                                           ZBSystemEntity* pEntity,
                                                           const CString&  rootName) :
    PSS_ObserverMsg(),
    m_pEntity(pEntity),
    m_RootName(rootName),
    m_MessageID(messageID)
{}
//---------------------------------------------------------------------------
PSS_LogicalSystemObserverMsg::~PSS_LogicalSystemObserverMsg()
{}
//---------------------------------------------------------------------------
