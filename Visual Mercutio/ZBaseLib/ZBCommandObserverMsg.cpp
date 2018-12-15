// ZBCommandObserverMsg.cpp: implementation of the ZBCommandObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBCommandObserverMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( ZBCommandObserverMsg, ZIObserverMsg )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBCommandObserverMsg::ZBCommandObserverMsg( int CommandID /*= 0*/ )
    : m_CommandID( CommandID )
{
}

ZBCommandObserverMsg::~ZBCommandObserverMsg()
{
}
