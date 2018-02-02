// ZBFieldObserverMsg.cpp: implementation of the ZBFieldObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBFieldObserverMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( ZBFieldObserverMsg, ZIObserverMsg )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBFieldObserverMsg::ZBFieldObserverMsg( UINT MessageID /*= 0*/, PlanFinObject* pObject /*= NULL*/ )
	: m_MessageID	( MessageID ), 
	  m_pObject		( pObject )
{
}


ZBFieldObserverMsg::~ZBFieldObserverMsg()
{
}
