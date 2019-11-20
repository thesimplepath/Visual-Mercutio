/****************************************************************************
 * ==> PSS_ActivityEventLogCtrl --------------------------------------------*
 ****************************************************************************
 * Description : Provides an event activity logger control                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityEventLogCtrl.h"

// processsoft
#include "zEvent\PSS_BaseActivity.h"
#include "zEvent\PSS_Process.h"

// resources
#ifndef _WIN32
    #include "rWinUtilRes.h"
#endif
#ifdef _WIN32
    #include "zWinUtil32Res.h"
#endif

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static int g_EventActivityColText[] =
{
    IDS_NOCOLUMNHEADER,
    IDS_COLUMN12_EVENTACTIVITY,
    IDS_COLUMN15_EVENTACTIVITY,
    IDS_COLUMN0_EVENTACTIVITY,
    IDS_COLUMN1_EVENTACTIVITY,
    IDS_COLUMN2_EVENTACTIVITY,
    IDS_COLUMN3_EVENTACTIVITY,
    IDS_COLUMN4_EVENTACTIVITY,
    IDS_COLUMN5_EVENTACTIVITY,
    IDS_COLUMN6_EVENTACTIVITY,
    IDS_COLUMN7_EVENTACTIVITY,
    IDS_COLUMN8_EVENTACTIVITY,
    IDS_COLUMN9_EVENTACTIVITY,
    IDS_COLUMN10_EVENTACTIVITY,
    IDS_COLUMN11_EVENTACTIVITY,
    IDS_COLUMN14_EVENTACTIVITY,
    IDS_COLUMN13_EVENTACTIVITY
};

static int g_EventActivityColSize[] =
{
    20,  // The action icon
    130, // The action text
    100, // The activity type
    150, // Time
    100, // FolderName
    100, // ProcessName
    100, // ProcessCreationDate
    100, // ProcessDueDate
    100, // ActivityName
    100, // ActivityCreationDate
    100, // ActivityDueDate
    100, // Sender
    100, // Receiver
    200, // ProcessFileName
    200, // ExchangeDataFileName
    200, // Process ExchangeDataFileName
    1000 // Comments
};
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ActivityEventLogCtrl, PSS_ListCtrl)
    //{{AFX_MSG_MAP(PSS_ActivityEventLogCtrl)
    ON_MESSAGE(UM_NEWACTIVITYEVENT, OnNewActivityEvent)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ActivityEventLogCtrl
//---------------------------------------------------------------------------
PSS_ActivityEventLogCtrl::PSS_ActivityEventLogCtrl(PSS_EventManager* pEventManager) :
    PSS_ListCtrl(),
    m_pEventManager(pEventManager),
    m_ColumnsHasBeenBuilt(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ActivityEventLogCtrl::PSS_ActivityEventLogCtrl(const PSS_ActivityEventLogCtrl& other)
{
    THROW("Copy constructor is prohibited for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityEventLogCtrl::~PSS_ActivityEventLogCtrl()
{}
//---------------------------------------------------------------------------
const PSS_ActivityEventLogCtrl& PSS_ActivityEventLogCtrl::operator = (const PSS_ActivityEventLogCtrl& other)
{
    THROW("Copy operator is prohibited for this class");
}
//---------------------------------------------------------------------------
#ifdef _WIN32
    PSS_ActivityEvent& operator >> (PSS_ActivityEvent& activityEvent, PSS_ActivityEventLogCtrl& eventCtrl)
    {
        const int index      = eventCtrl.GetItemCount();
              int imageIndex = 13;

        if (activityEvent.GetActivityEventType() != PSS_ActivityEvent::IE_AT_Message)
            if (activityEvent.GetActivityStatus() == g_ActivityStatusProcessPaused)
                imageIndex = 12;
            else
            if (activityEvent.GetActivityStatus() == g_ActivityStatusProcessAborted)
                imageIndex = 4;
            else
            if (activityEvent.GetActivityStatus() == g_ActivityStatusProcessCompleted)
                imageIndex = 5;
            else
            if (activityEvent.GetActivityStatus() == g_ActivityStatusRequestAcceptation)
                imageIndex = 8;
            else
            if (activityEvent.GetActivityStatus() == g_ActivityStatusAccepted)
                imageIndex = 7;
            else
            if (activityEvent.GetActivityStatus() == g_ActivityStatusRejected)
                imageIndex = 6;
            else
            if (activityEvent.GetActivityStatus() == g_ActivityStatusAttribution)
                imageIndex = 3;
            else
            if (activityEvent.GetActivityStatus() == g_ActivityStatusSent)
                imageIndex = 0;
            else
            if (activityEvent.GetActivityStatus() == g_ActivityStatusAttribution)
                imageIndex = 7;
            else
                imageIndex = 11;

        // add the action icon
        eventCtrl.InsertItem(LVIF_IMAGE | LVIF_PARAM, index, NULL, 0, 0, imageIndex, LPARAM(&activityEvent));

        // add the action text
        eventCtrl.SetItem(index,
                          1,
                          LVIF_TEXT,
                          PSS_Process::GetStatusString(activityEvent.GetActivityStatus()),
                          0,
                          LVIF_TEXT,
                          LVIF_TEXT,
                          0);

        // add the Activity Type
        eventCtrl.SetItem(index, 2, LVIF_TEXT, activityEvent.GetActivityType(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the event Date
        eventCtrl.SetItem(index, 3, LVIF_TEXT, activityEvent.GetFormattedTimeStamp(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the folder name
        eventCtrl.SetItem(index, 4, LVIF_TEXT, activityEvent.GetFolderName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process name
        eventCtrl.SetItem(index, 5, LVIF_TEXT, activityEvent.GetProcessName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process creation date
        eventCtrl.SetItem(index, 6, LVIF_TEXT, activityEvent.GetFormattedProcessCreationDate(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process due date
        eventCtrl.SetItem(index, 7, LVIF_TEXT, activityEvent.GetFormattedProcessDueDate(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity name
        eventCtrl.SetItem(index, 8, LVIF_TEXT, activityEvent.GetActivityName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity creation date
        eventCtrl.SetItem(index, 9, LVIF_TEXT, activityEvent.GetFormattedActivityCreationDate(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity due date
        eventCtrl.SetItem(index, 10, LVIF_TEXT, activityEvent.GetFormattedActivityDueDate(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the sender name
        eventCtrl.SetItem(index, 11, LVIF_TEXT, activityEvent.GetSender(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the receiver name
        eventCtrl.SetItem(index, 12, LVIF_TEXT, activityEvent.GetReceiver(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process file name
        eventCtrl.SetItem(index, 13, LVIF_TEXT, activityEvent.GetProcessFileName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the exchange date file name
        eventCtrl.SetItem(index, 14, LVIF_TEXT, activityEvent.GetExchangeDataFileName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process exchange date file name
        eventCtrl.SetItem(index, 15, LVIF_TEXT, activityEvent.GetProcessExchangeDataFileName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the comments
        eventCtrl.SetItem(index, 16, LVIF_TEXT, activityEvent.GetComments(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        return activityEvent;
    }
#endif
//---------------------------------------------------------------------------
void PSS_ActivityEventLogCtrl::Initialize(PSS_EventManager* pEventManager)
{
    m_pEventManager = pEventManager;

    Refresh();
}
//---------------------------------------------------------------------------
PSS_ActivityEvent* PSS_ActivityEventLogCtrl::GetSelectedItem() const
{
    int      index;
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
    {
        index = GetNextSelectedItem(pPos);
        return (PSS_ActivityEvent*)GetItemData(index);
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventLogCtrl::Refresh()
{
    DeleteAllItems();

    // if the columns were never built
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    if (m_pEventManager)
    {
        const int count = m_pEventManager->GetEventCount();

        for (int i = 0; i < count; ++i)
            ((PSS_ActivityEvent&)*(m_pEventManager->GetEventAt(i))) >> *this;
    }
}
//---------------------------------------------------------------------------
LRESULT PSS_ActivityEventLogCtrl::OnNewActivityEvent(WPARAM wParam, LPARAM lParam)
{
    PSS_ActivityEvent* pEvent = (PSS_ActivityEvent*)lParam;

    // if the columns were never built
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    *pEvent >> *this;

    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityEventLogCtrl::BuildColumns()
{
    // load images
    LoadImageListMasked(IDB_MESSAGEITEM0_ACTEVT, IDB_MESSAGEITEM13_ACTEVT);

    PSS_ListCtrl::SetEnableOver(TRUE);
    PSS_ListCtrl::SetFullRowSelect(TRUE);
    PSS_ListCtrl::EnableSort(TRUE);
    PSS_ListCtrl::BuildColumns(17, g_EventActivityColSize, g_EventActivityColText);

    m_ColumnsHasBeenBuilt = TRUE;

    return TRUE;
}
//---------------------------------------------------------------------------
