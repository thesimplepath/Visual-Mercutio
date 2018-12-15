// ZBMenuObserverMsg.cpp: implementation of the ZBMenuObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBMenuObserverMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( ZBMenuObserverMsg, ZIObserverMsg )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBMenuObserverMsg::ZBMenuObserverMsg( int CommandID /*= 0*/ )
    : m_CommandID( CommandID )
{
}

ZBMenuObserverMsg::~ZBMenuObserverMsg()
{
}
