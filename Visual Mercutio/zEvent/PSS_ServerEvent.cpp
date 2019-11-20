/****************************************************************************
 * ==> PSS_ServerEvent -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a server event                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ServerEvent.h"

// resources
#include "ZEvtRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ServerEvent
//---------------------------------------------------------------------------
PSS_ServerEvent::PSS_ServerEvent() :
    PSS_Event(),
    m_EventResult(IE_ER_NF)
{}
//---------------------------------------------------------------------------
PSS_ServerEvent::PSS_ServerEvent(const COleDateTime& time, const CString& fileName, IEResult eventResultValue) :
    PSS_Event(time, g_Evt_Server),
    m_EventResult(eventResultValue),
    m_FileName(fileName)
{}
//---------------------------------------------------------------------------
PSS_ServerEvent::PSS_ServerEvent(const PSS_ServerEvent& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ServerEvent::~PSS_ServerEvent()
{}
//---------------------------------------------------------------------------
const PSS_ServerEvent& PSS_ServerEvent::operator = (const PSS_ServerEvent& other)
{
    PSS_Event::operator=(other);

    m_EventResult = other.m_EventResult;
    m_FileName    = other.m_FileName;

    return *this;
}
//---------------------------------------------------------------------------
CString PSS_ServerEvent::GetEventResultStr() const
{
    UINT id;

    switch (GetEventResult())
    {
        case IE_ER_Imported:   id = IDS_EVENTIMPORTED;   break;
        case IE_ER_Rejected:   id = IDS_EVENTREJECTED;   break;
        case IE_ER_LogAdded:   id = IDS_EVENTLOGADDED;   break;
        case IE_ER_LogProblem: id = IDS_EVENTLOGPROBLEM; break;
        default:               id = IDS_EVENTUNDEFINED;  break;
    }

    CString text;
    text.LoadString(id);

    return text;
}
//---------------------------------------------------------------------------
