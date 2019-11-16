// ZBEventServer.cpp: implementation of the ZBEventServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBEventServer.h"
// Include resource header file
#include "ZEvtRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBEventServer::ZBEventServer()
: PSS_Event(), m_EventResult(EventNF)
{

}

ZBEventServer::ZBEventServer( COleDateTime Time, CString fileName, EventResult EventResultValue )
: PSS_Event(Time, g_Evt_Server), m_FileName(fileName), m_EventResult(EventResultValue)
{
}

ZBEventServer::~ZBEventServer()
{

}



ZBEventServer::ZBEventServer(const ZBEventServer &right)
{
    *this = right;
}

const ZBEventServer & ZBEventServer::operator=(const ZBEventServer &right)
{
    PSS_Event::operator=( right );
    m_FileName = right.m_FileName;
    m_EventResult = right.m_EventResult;
    return *this;
}


CString        ZBEventServer::GetEventResultStr() const
{
    CString    Text;
    UINT    nID;
    switch (GetEventResult())
    {
        case EventImported:
        {
            nID = IDS_EVENTIMPORTED;
            break;
        }
        case EventRejected:
        {
            nID = IDS_EVENTREJECTED;
            break;
        }
        case EventLogAdded:
        {
            nID = IDS_EVENTLOGADDED;
            break;
        }
        case EventLogProblem:
        {
            nID = IDS_EVENTLOGPROBLEM;
            break;
        }
        case EventNF:
        default:
        {
            nID = IDS_EVENTUNDEFINED;
            break;
        }
    }
    Text.LoadString( nID );
    return Text;
}

