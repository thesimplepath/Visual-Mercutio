/****************************************************************************
 * ==> PSS_ActivityEventViewerReminderCtrl ---------------------------------*
 ****************************************************************************
 * Description : Provides an event activity viewer reminder control         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityEventViewerReminderCtrl.h"

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
static int g_EventReminderColText[] =
{
    IDS_NOCOLUMNHEADER,
    IDS_COLUMN1_EVENTREMINDER,
    IDS_COLUMN2_EVENTREMINDER, 
    IDS_COLUMN3_EVENTREMINDER,
    IDS_COLUMN4_EVENTREMINDER, 
    IDS_COLUMN5_EVENTREMINDER,
    IDS_COLUMN6_EVENTREMINDER,
    IDS_COLUMN7_EVENTREMINDER
};

static int g_EventReminderColSize[] =
{
    20,  // Priority
    100, // FolderName
    100, // ProcessName
    100, // ActivityName
    80,  // Remaining days
    100, // ActivityDueDate
    100, // ActivityStatus
    1000 // Comments
};
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ActivityEventViewerReminderCtrl, PSS_ListCtrl)
    //{{AFX_MSG_MAP(PSS_ActivityEventViewerReminderCtrl)
    ON_MESSAGE(UM_NEWACTIVITYREMINDEREVENT, OnNewActivityEvent)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ActivityEventViewerReminderCtrl
//---------------------------------------------------------------------------
PSS_ActivityEventViewerReminderCtrl::PSS_ActivityEventViewerReminderCtrl(PSS_ActivityReminderEventManager* pReminderManager) :
    PSS_ListCtrl(),
    m_pReminderManager(pReminderManager),
    m_ColumnsHasBeenBuilt(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ActivityEventViewerReminderCtrl::PSS_ActivityEventViewerReminderCtrl(const PSS_ActivityEventViewerReminderCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityEventViewerReminderCtrl::~PSS_ActivityEventViewerReminderCtrl()
{}
//---------------------------------------------------------------------------
const PSS_ActivityEventViewerReminderCtrl& PSS_ActivityEventViewerReminderCtrl::operator = (const PSS_ActivityEventViewerReminderCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
#ifdef _WIN32
PSS_ActivityReminderEvent& operator >> (PSS_ActivityReminderEvent& activityEvent, PSS_ActivityEventViewerReminderCtrl& eventCtrl)
    {
        const int index      = eventCtrl.GetItemCount();
              int imageIndex = 11;

        if (activityEvent.GetPriority() == g_EventPriorityHigh)
            imageIndex = 10;
        else
        if (activityEvent.GetPriority() == g_EventPriorityLow)
            imageIndex = 9;

        // add the priority
        eventCtrl.InsertItem(LVIF_IMAGE | LVIF_PARAM, index, NULL, 0, 0, imageIndex, LPARAM(&activityEvent));

        // add the folder name
        eventCtrl.SetItem(index, 1, LVIF_TEXT, activityEvent.GetFolderName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process name
        eventCtrl.SetItem(index, 2, LVIF_TEXT, activityEvent.GetProcessName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity name
        eventCtrl.SetItem(index, 3, LVIF_TEXT, activityEvent.GetActivityName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity remaining days
        eventCtrl.SetItem(index, 4, LVIF_TEXT, activityEvent.GetRemainingDaysString(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity due date
        eventCtrl.SetItem(index, 5, LVIF_TEXT, activityEvent.GetFormattedActivityDueDate(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity status
        eventCtrl.SetItem(index, 6, LVIF_TEXT, PSS_Process::GetStatusString(activityEvent.GetActivityStatus()), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the message
        eventCtrl.SetItem(index, 7, LVIF_TEXT, activityEvent.GetMessage(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        return activityEvent;
    }
#endif
//---------------------------------------------------------------------------
void PSS_ActivityEventViewerReminderCtrl::Initialize(PSS_ActivityReminderEventManager* pReminderManager)
{
    m_pReminderManager = pReminderManager;
    Refresh();
}
//---------------------------------------------------------------------------
PSS_ActivityReminderEvent* PSS_ActivityEventViewerReminderCtrl::GetSelectedItem() const
{
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
        return (PSS_ActivityReminderEvent*)GetItemData(GetNextSelectedItem(pPos));

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ActivityEventViewerReminderCtrl::Refresh()
{
    DeleteAllItems();

    // were the columns never built?
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    const int eventCount = m_pReminderManager->GetEventCount();

    for (int i = 0; i < eventCount; ++i)
        ((PSS_ActivityReminderEvent&)*(m_pReminderManager->GetEventAt(i))) >> *this;
}
//---------------------------------------------------------------------------
LRESULT PSS_ActivityEventViewerReminderCtrl::OnNewActivityEvent(WPARAM wParam, LPARAM lParam)
{
    PSS_ActivityReminderEvent* pEvent = (PSS_ActivityReminderEvent*)lParam;

    // were the columns never built?
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    *pEvent >> *this;
    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityEventViewerReminderCtrl::BuildColumns()
{
    // load images
    LoadImageListMasked(IDB_MESSAGEITEM0_ACTEVT, IDB_MESSAGEITEM11_ACTEVT);

    PSS_ListCtrl::SetEnableOver(TRUE);
    PSS_ListCtrl::SetFullRowSelect(TRUE);
    PSS_ListCtrl::EnableSort(TRUE);
    PSS_ListCtrl::BuildColumns(8, g_EventReminderColSize, g_EventReminderColText);

    m_ColumnsHasBeenBuilt = TRUE;

    return TRUE;
}
//---------------------------------------------------------------------------
