// ZBPropertyObserverMsg.cpp: implementation of the ZBPropertyObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBPropertyObserverMsg.h"
#include "ZIProperties.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(ZBPropertyObserverMsg, ZIObserverMsg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBPropertyObserverMsg::ZBPropertyObserverMsg(ZIProperties* pProperties /*= NULL*/)
: m_pProperties(pProperties)
{

}


ZBPropertyObserverMsg::~ZBPropertyObserverMsg()
{

}
