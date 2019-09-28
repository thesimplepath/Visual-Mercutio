// ZBWorkspaceObserverMsg.cpp: implementation of the ZBWorkspaceObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBWorkspaceObserverMsg.h"

// processsoft
#include "PSS_WorkspaceEntity.h"
#include "PSS_WorkspaceEnv.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(ZBWorkspaceObserverMsg, PSS_ObserverMsg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBWorkspaceObserverMsg::ZBWorkspaceObserverMsg(UINT MessageID, PSS_WorkspaceEnv* pEnv) :
    PSS_ObserverMsg(),
    m_MessageID(MessageID),
    m_pEnv(pEnv),
    m_pEntity(NULL)
{}

ZBWorkspaceObserverMsg::ZBWorkspaceObserverMsg(UINT MessageID, PSS_WorkspaceEnv* pEnv, PSS_WorkspaceEntity* pEntity) :
    PSS_ObserverMsg(),
    m_MessageID(MessageID),
    m_pEnv(pEnv),
    m_pEntity(pEntity)
{}

ZBWorkspaceObserverMsg::ZBWorkspaceObserverMsg(UINT MessageID, PSS_WorkspaceEntity* pEntity) :
    PSS_ObserverMsg(),
    m_MessageID(MessageID),
    m_pEnv(NULL),
    m_pEntity(pEntity)
{}

ZBWorkspaceObserverMsg::~ZBWorkspaceObserverMsg()
{}
