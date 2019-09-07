// ZBEvent.cpp: implementation of the ZBEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBEvent.h"
// Include resource header file
#include "ZEvtRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( ZBEvent, CObject )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


ZBEvent::ZBEvent()
: m_EventID(EVT_UNDEFINED)
{

}

ZBEvent::ZBEvent( COleDateTime Time, int EventID, CString UserQueue )
: m_TimeStamp(Time), m_EventID(EventID), m_UserQueue(UserQueue)
{
}

ZBEvent::~ZBEvent()
{

}



ZBEvent::ZBEvent(const ZBEvent &right)
{
    *this = right;
}

const ZBEvent & ZBEvent::operator=(const ZBEvent &right)
{
    m_TimeStamp = right.m_TimeStamp;
    m_EventID = right.m_EventID;
    m_UserQueue = right.m_UserQueue;
    return *this;
}

CString        ZBEvent::GetEventIDStr() const
{
    CString    Text;
    UINT    nID;
    switch (GetEventID())
    {
        case EVT_SERVER:
        {
            nID = IDS_EVENTSERVER;
            break;
        }
        case EVT_UNDEFINED:
        default:
        {
            nID = IDS_EVENTUNDEFINED;
            break;
        }
    }
    Text.LoadString( nID );
    return Text;
}

BOOL    ZBEvent::ParseDateTime(COleDateTime& Date, CString& value)
{
    char*    pNext = value.GetBuffer(30);
    int        Year = 0;
    int        Month = 0;
    int        Day = 0;
    int        Hour = 0;
    int        Min = 0;
    int        Sec = 0;

    // 01.01.1999 - 23:10:30
    // After day
    *(pNext+2) = 0x00;
    // After month
    *(pNext+5) = 0x00;
    // After year
    *(pNext+10) = 0x00;
    // After hour
    *(pNext+15) = 0x00;
    // After min
    *(pNext+18) = 0x00;

    // Extract day
    Day = atoi( pNext );
    // go to month and extract it
    pNext += 3;
    Month = atoi( pNext );
    // go to year and extract it
    pNext += 3;
    Year = atoi( pNext );
    // go to hour and extract it
    pNext += 7;
    Hour = atoi( pNext );
    // go to minute and extract it
    pNext += 3;
    Min = atoi( pNext );
    // go to second and extract it
    pNext += 3;
    Sec = atoi( pNext );
    // Release the buffer
    value.ReleaseBuffer();
    // Sets the date time
    return (Date.SetDateTime( Year, Month, Day, Hour, Min, Sec ) == 0) ? TRUE: FALSE;
}

ZBEvent&    operator>>( ZBEvent& left, ZIListCtrl& listCtrl )
{
    int    Index = listCtrl.GetItemCount();
    // Add the event Date
    listCtrl.InsertItem( Index, left.GetFormattedTimeStamp() );
    // Add the event type
    listCtrl.SetItem( Index, 1, LVIF_TEXT,
                      left.GetEventIDStr(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );

    return left;
}

