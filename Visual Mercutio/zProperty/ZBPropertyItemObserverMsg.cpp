// ZBPropertyItemObserverMsg.cpp: implementation of the ZBPropertyItemObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBPropertyItemObserverMsg.h"
#include "ZBProperty.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(ZBPropertyItemObserverMsg, PSS_ObserverMsg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBPropertyItemObserverMsg::ZBPropertyItemObserverMsg(ZBProperty* pProperty) :
    PSS_ObserverMsg(),
    m_pProperty(pProperty)
{}

ZBPropertyItemObserverMsg::~ZBPropertyItemObserverMsg()
{}
