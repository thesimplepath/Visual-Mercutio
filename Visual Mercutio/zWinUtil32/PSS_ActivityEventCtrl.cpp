/****************************************************************************
 * ==> PSS_ActivityEventCtrl -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an event activity control                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityEventCtrl.h"

// processsoft
#include "zEvent\PSS_Process.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
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
static int g_ReduceEventActivityColText[] =
{
    IDS_NOCOLUMNHEADER,
    IDS_COLUMN5_EVENTACTIVITY,
    IDS_COLUMN12_EVENTACTIVITY,
    IDS_COLUMN1_EVENTACTIVITY,
    IDS_COLUMN2_EVENTACTIVITY,
    IDS_COLUMN8_EVENTACTIVITY,
    IDS_COLUMN13_EVENTACTIVITY
};

static int g_ReduceEventActivityColSize[] =
{
    20,  // The icon type
    100, // ActivityName
    150, // The action text
    100, // FolderName
    100, // ProcessName
    100, // Sender
    1000 // Comments
};
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ActivityEventCtrl, PSS_ListCtrl)
    //{{AFX_MSG_MAP(PSS_ActivityEventCtrl)
    ON_MESSAGE(UM_NEWACTIVITYEVENT, OnNewActivityEvent)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ActivityEventCtrl
//---------------------------------------------------------------------------
PSS_ActivityEventCtrl::PSS_ActivityEventCtrl(PSS_EventManager* pEventManager) :
    PSS_ListCtrl(),
    m_pEventManager(pEventManager),
    m_ColumnsHasBeenBuilt(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ActivityEventCtrl::PSS_ActivityEventCtrl(const PSS_ActivityEventCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityEventCtrl::~PSS_ActivityEventCtrl()
{}
//---------------------------------------------------------------------------
const PSS_ActivityEventCtrl& PSS_ActivityEventCtrl::operator = (const PSS_ActivityEventCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
#ifdef _WIN32
PSS_ActivityEvent& operator >> (PSS_ActivityEvent& activityEvent, PSS_ActivityEventCtrl& eventCtrl)
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
        eventCtrl.InsertItem( LVIF_IMAGE | LVIF_PARAM, index, NULL, 0, 0, imageIndex, LPARAM(&activityEvent));

        // add the activity name
        eventCtrl.SetItem(index, 1, LVIF_TEXT, activityEvent.GetActivityName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the action text
        eventCtrl.SetItem(index, 2, LVIF_TEXT, PSS_Process::GetStatusString(activityEvent.GetActivityStatus()), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the folder name
        eventCtrl.SetItem(index, 3, LVIF_TEXT, activityEvent.GetFolderName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process name
        eventCtrl.SetItem(index, 4, LVIF_TEXT, activityEvent.GetProcessName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the sender name
        eventCtrl.SetItem(index, 5, LVIF_TEXT, activityEvent.GetSender(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the comments
        eventCtrl.SetItem(index, 6, LVIF_TEXT, activityEvent.GetComments(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        return activityEvent;
    }
#endif
//---------------------------------------------------------------------------
void PSS_ActivityEventCtrl::Initialize(PSS_EventManager* pEventManager)
{
    m_pEventManager = pEventManager;

    Refresh();
}
//---------------------------------------------------------------------------
PSS_ActivityEvent* PSS_ActivityEventCtrl::GetSelectedItem() const
{
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
        return (PSS_ActivityEvent*)GetItemData(GetNextSelectedItem(pPos));

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventCtrl::Refresh()
{
    DeleteAllItems();

    // were the columns never built?
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    const int eventCount = m_pEventManager->GetEventCount();

    for (int i = 0; i < eventCount; ++i)
        ((PSS_ActivityEvent&)*(m_pEventManager->GetEventAt(i))) >> *this;
}
//---------------------------------------------------------------------------
LRESULT PSS_ActivityEventCtrl::OnNewActivityEvent(WPARAM wParam, LPARAM lParam)
{
    PSS_ActivityEvent* pEvent = (PSS_ActivityEvent*)lParam;

    // were the columns never built?
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    *pEvent >> *this;
    return 1;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityEventCtrl::BuildColumns()
{
    // load images
    LoadImageListMasked(IDB_MESSAGEITEM0_ACTEVT, IDB_MESSAGEITEM13_ACTEVT);

    PSS_ListCtrl::SetEnableOver(TRUE);
    PSS_ListCtrl::SetFullRowSelect(TRUE);
    PSS_ListCtrl::EnableSort(TRUE);
    PSS_ListCtrl::BuildColumns(7, g_ReduceEventActivityColSize, g_ReduceEventActivityColText);

    m_ColumnsHasBeenBuilt = TRUE;

    return TRUE;
}
//---------------------------------------------------------------------------
