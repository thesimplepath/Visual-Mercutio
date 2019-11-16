// Source file: SrvEvtManager.cpp

#include <StdAfx.h>

#include "SrvEvtManager.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZBServerEventManager 


ZBServerEventManager::ZBServerEventManager()
{}

ZBServerEventManager::~ZBServerEventManager()
{}

ZBEventServer* ZBServerEventManager::AddEvent(COleDateTime Time, CString fileName, EventResult EventResultValue)
{
    ZBEventServer* pEvent = new ZBEventServer(Time, fileName, EventResultValue);

    if (!PSS_EventManager::AddEvent(pEvent))
    {
        delete pEvent;
        pEvent = NULL;
    }

    return pEvent;
}
