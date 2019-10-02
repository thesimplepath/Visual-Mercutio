/****************************************************************************
 * ==> PSS_WorkspaceObserverMsg --------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace observer message                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceObserverMsg.h"

 // processsoft
#include "PSS_WorkspaceEntity.h"
#include "PSS_WorkspaceEnv.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_WorkspaceObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_WorkspaceObserverMsg
//---------------------------------------------------------------------------
PSS_WorkspaceObserverMsg::PSS_WorkspaceObserverMsg(UINT messageID, PSS_WorkspaceEnv* pEnv) :
    PSS_ObserverMsg(),
    m_pEntity(NULL),
    m_pEnv(pEnv),
    m_MessageID(messageID)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceObserverMsg::PSS_WorkspaceObserverMsg(UINT messageID, PSS_WorkspaceEnv* pEnv, PSS_WorkspaceEntity* pEntity) :
    PSS_ObserverMsg(),
    m_pEntity(pEntity),
    m_pEnv(pEnv),
    m_MessageID(messageID)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceObserverMsg::PSS_WorkspaceObserverMsg(UINT messageID, PSS_WorkspaceEntity* pEntity) :
    PSS_ObserverMsg(),
    m_pEntity(pEntity),
    m_pEnv(NULL),
    m_MessageID(messageID)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceObserverMsg::~PSS_WorkspaceObserverMsg()
{}
//---------------------------------------------------------------------------
