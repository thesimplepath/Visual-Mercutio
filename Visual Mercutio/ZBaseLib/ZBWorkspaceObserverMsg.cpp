// ZBWorkspaceObserverMsg.cpp: implementation of the ZBWorkspaceObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBWorkspaceObserverMsg.h"

#include "ZBWorkspaceEntity.h"
#include "ZBWorkspaceEnv.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( ZBWorkspaceObserverMsg, ZIObserverMsg )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBWorkspaceObserverMsg::ZBWorkspaceObserverMsg( UINT MessageID /*= 0*/, ZBWorkspaceEnv* pEnv /*= NULL*/ )
	: m_MessageID	( MessageID ),
	  m_pEnv		( pEnv ),
	  m_pEntity		( NULL )
{
}

ZBWorkspaceObserverMsg::ZBWorkspaceObserverMsg( UINT MessageID, ZBWorkspaceEnv* pEnv, ZBWorkspaceEntity* pEntity )
	: m_MessageID	( MessageID ), 
	  m_pEnv		( pEnv ),
	  m_pEntity		( pEntity )
{
}

ZBWorkspaceObserverMsg::ZBWorkspaceObserverMsg( UINT MessageID, ZBWorkspaceEntity* pEntity )
	: m_MessageID	( MessageID ),
	  m_pEnv		( NULL ),
	  m_pEntity		( pEntity )
{
}

ZBWorkspaceObserverMsg::~ZBWorkspaceObserverMsg()
{
}
