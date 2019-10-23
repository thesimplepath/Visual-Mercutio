/****************************************************************************
 * ==> PSS_EventActivityViewerReminderCtrl ---------------------------------*
 ****************************************************************************
 * Description : Provides an event activity viewer reminder control         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_EventActivityViewerReminderCtrl.h"

// processsoft
#include "zEvent\ZProcess.h"

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
BEGIN_MESSAGE_MAP(PSS_EventActivityViewerReminderCtrl, PSS_ListCtrl)
    //{{AFX_MSG_MAP(PSS_EventActivityViewerReminderCtrl)
    ON_MESSAGE(UM_NEWACTIVITYREMINDEREVENT, OnNewActivityEvent)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_EventActivityViewerReminderCtrl
//---------------------------------------------------------------------------
PSS_EventActivityViewerReminderCtrl::PSS_EventActivityViewerReminderCtrl(ZBActivityEventReminderManager* pReminderManager) :
    PSS_ListCtrl(),
    m_pReminderManager(pReminderManager),
    m_ColumnsHasBeenBuilt(FALSE)
{}
//---------------------------------------------------------------------------
PSS_EventActivityViewerReminderCtrl::PSS_EventActivityViewerReminderCtrl(const PSS_EventActivityViewerReminderCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_EventActivityViewerReminderCtrl::~PSS_EventActivityViewerReminderCtrl()
{}
//---------------------------------------------------------------------------
const PSS_EventActivityViewerReminderCtrl& PSS_EventActivityViewerReminderCtrl::operator = (const PSS_EventActivityViewerReminderCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
#ifdef _WIN32
    ZBEventActivityReminder& operator>>(ZBEventActivityReminder& left, PSS_EventActivityViewerReminderCtrl& listCtrl)
    {
        const int index      = listCtrl.GetItemCount();
              int imageIndex = 11;

        if (left.GetPriority() == EventPriorityHigh)
            imageIndex = 10;
        else
        if (left.GetPriority() == EventPriorityLow)
            imageIndex = 9;

        // add the priority
        listCtrl.InsertItem(LVIF_IMAGE | LVIF_PARAM, index, NULL, 0, 0, imageIndex, (LPARAM)&left);

        // add the folder name
        listCtrl.SetItem(index, 1, LVIF_TEXT, left.GetFolderName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process name
        listCtrl.SetItem(index, 2, LVIF_TEXT, left.GetProcessName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity name
        listCtrl.SetItem(index, 3, LVIF_TEXT, left.GetActivityName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity remaining days
        listCtrl.SetItem(index, 4, LVIF_TEXT, left.GetRemainingDaysString(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity due date
        listCtrl.SetItem(index, 5, LVIF_TEXT, left.GetFormattedActivityDueDate(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity status
        listCtrl.SetItem(index, 6, LVIF_TEXT, ZProcess::GetStatusString(left.GetActivityStatus()), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the message
        listCtrl.SetItem(index, 7, LVIF_TEXT, left.GetMessage(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        return left;
    }
#endif
//---------------------------------------------------------------------------
void PSS_EventActivityViewerReminderCtrl::Initialize(ZBActivityEventReminderManager* pReminderManager)
{
    m_pReminderManager = pReminderManager;
    Refresh();
}
//---------------------------------------------------------------------------
ZBEventActivityReminder* PSS_EventActivityViewerReminderCtrl::GetSelectedItem() const
{
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
        return (ZBEventActivityReminder*)GetItemData(GetNextSelectedItem(pPos));

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_EventActivityViewerReminderCtrl::Refresh()
{
    DeleteAllItems();

    // were the columns never built?
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    const int eventCount = m_pReminderManager->GetEventCount();

    for (int i = 0; i < eventCount; ++i)
        ((ZBEventActivityReminder&)*(m_pReminderManager->GetEventAt(i))) >> *this;
}
//---------------------------------------------------------------------------
LRESULT PSS_EventActivityViewerReminderCtrl::OnNewActivityEvent(WPARAM wParam, LPARAM lParam)
{
    ZBEventActivityReminder* pEvent = (ZBEventActivityReminder*)lParam;

    // were the columns never built?
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    *pEvent >> *this;
    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_EventActivityViewerReminderCtrl::BuildColumns()
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
