/****************************************************************************
 * ==> PSS_Event -----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic event                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_Event.h"

// processsoft
#include "ZEvtRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_Event, CObject)
//---------------------------------------------------------------------------
// PSS_Event
//---------------------------------------------------------------------------
PSS_Event::PSS_Event() :
    CObject(),
    m_EventID(g_Evt_Undefined)
{}
//---------------------------------------------------------------------------
PSS_Event::PSS_Event(const COleDateTime& timeStamp, int eventID, const CString& userQueue) :
    CObject(),
    m_TimeStamp(timeStamp),
    m_UserQueue(userQueue),
    m_EventID(eventID)
{}
//---------------------------------------------------------------------------
PSS_Event::PSS_Event(const PSS_Event& other) :
    CObject(),
    m_EventID(g_Evt_Undefined)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_Event::~PSS_Event()
{}
//---------------------------------------------------------------------------
const PSS_Event& PSS_Event::operator = (const PSS_Event& other)
{
    m_TimeStamp = other.m_TimeStamp;
    m_UserQueue = other.m_UserQueue;
    m_EventID   = other.m_EventID;

    return *this;
}
//---------------------------------------------------------------------------
PSS_Event& operator >> (PSS_Event& left, PSS_ListCtrl& listCtrl)
{
    const int index = listCtrl.GetItemCount();

    // add the event date
    listCtrl.InsertItem(index, left.GetFormattedTimeStamp());

    // add the event type
    listCtrl.SetItem(index, 1, LVIF_TEXT, left.GetEventIDStr(), 0, LVIF_TEXT, LVIF_TEXT, 0);

    return left;
}
//---------------------------------------------------------------------------
CString PSS_Event::GetEventIDStr() const
{
    UINT id;

    switch (GetEventID())
    {
        case g_Evt_Server: id = IDS_EVENTSERVER;    break;
        default:           id = IDS_EVENTUNDEFINED; break;
    }

    CString text;
    text.LoadString(id);

    return text;
}
//---------------------------------------------------------------------------
BOOL PSS_Event::ParseDateTime(COleDateTime& dateTime, const CString& value)
{
    // date to parse are formatted as follow: 01.01.1999 - 23:10:30
    CString dateToParse = value;
    char*   pNext       = dateToParse.GetBuffer(30);

    // insert an end of line char after the day, month, year, hour and minute
    *(pNext + 2)  = 0x00;
    *(pNext + 5)  = 0x00;
    *(pNext + 10) = 0x00;
    *(pNext + 15) = 0x00;
    *(pNext + 18) = 0x00;

    // get the day
    const int day = std::atoi(pNext);

    // move to month and get it
    pNext           += 3;
    const int month  = std::atoi(pNext);

    // move to year and get it
    pNext          += 3;
    const int year  = std::atoi(pNext);

    // move to hour and get it
    pNext          += 7;
    const int hour  = std::atoi(pNext);

    // move to minute and get it
    pNext         += 3;
    const int min  = std::atoi(pNext);

    // move to second and get it
    pNext         += 3;
    const int sec  = std::atoi(pNext);

    // release the buffer
    dateToParse.ReleaseBuffer();

    // set the date and time
    return (dateTime.SetDateTime(year, month, day, hour, min, sec) == COleDateTime::valid);
}
//---------------------------------------------------------------------------
