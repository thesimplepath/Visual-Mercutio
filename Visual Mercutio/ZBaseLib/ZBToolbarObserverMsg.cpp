// ZBToolbarObserverMsg.cpp: implementation of the ZBToolbarObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBToolbarObserverMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( ZBToolbarObserverMsg, ZIObserverMsg )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBToolbarObserverMsg::ZBToolbarObserverMsg( UINT MessageID /*= 0*/ )
	: m_MessageID( MessageID )
{
}

ZBToolbarObserverMsg::~ZBToolbarObserverMsg()
{
}
