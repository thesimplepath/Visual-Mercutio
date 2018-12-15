// Source file: ActEvtReminderC.cpp

#include <StdAfx.h>

// ActEvtC
#include "ActEvtReminderC.h"
#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif

#include "zEvent\ZProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int _gEventReminderColText[] = { IDS_NOCOLUMNHEADER,
                                        IDS_COLUMN1_EVENTREMINDER, IDS_COLUMN2_EVENTREMINDER, 
                                        IDS_COLUMN3_EVENTREMINDER, IDS_COLUMN4_EVENTREMINDER, 
                                        IDS_COLUMN5_EVENTREMINDER, IDS_COLUMN6_EVENTREMINDER,
                                        IDS_COLUMN7_EVENTREMINDER };
static int _gEventReminderColSize[] = { 20,        // Priority
                                        100,     // FolderName
                                        100,    // ProcessName
                                        100,     // ActivityName
                                        80,     // Remaining days
                                        100,     // ActivityDueDate
                                        100,    // ActivityStatus
                                        1000 };    // Comments


BEGIN_MESSAGE_MAP(ZCEventActivityViewerReminder, ZIListCtrl)
    //{{AFX_MSG_MAP(ZCEventActivityViewerReminder)
    ON_MESSAGE(UM_NEWACTIVITYREMINDEREVENT, OnNewActivityEvent)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCEventActivityViewerReminder 


ZCEventActivityViewerReminder::ZCEventActivityViewerReminder (ZBActivityEventReminderManager* pReminderManager)
      : m_pReminderManager(pReminderManager), m_ColumnsHasBeenBuilt(FALSE)
{
}


ZCEventActivityViewerReminder::~ZCEventActivityViewerReminder()
{
}



void ZCEventActivityViewerReminder::Initialize (ZBActivityEventReminderManager* pReminderManager)
{
    m_pReminderManager = pReminderManager;
    ZCEventActivityViewerReminder::Refresh();
}

void ZCEventActivityViewerReminder::Refresh ()
{
    DeleteAllItems();
    // If the columns were never built
    if (!ColumnsHasBeenBuilt())
        BuildColumns();
    for (int i = 0; i < m_pReminderManager->GetEventCount(); ++i)
        ((ZBEventActivityReminder&)*(m_pReminderManager->GetEventAt(i))) >> *this;
}

ZBEventActivityReminder*    ZCEventActivityViewerReminder::GetSelectedItem() const
{
    int    Index;
    POSITION pos = GetFirstSelectedItemPosition();
    if (pos != NULL)     
    {
        Index = GetNextSelectedItem( pos );
        return (ZBEventActivityReminder*)GetItemData( Index );
    }
    return NULL;
}

BOOL    ZCEventActivityViewerReminder::BuildColumns()
{
    // Load images
    LoadImageListMasked( IDB_MESSAGEITEM0_ACTEVT, IDB_MESSAGEITEM11_ACTEVT );
    ZIListCtrl::SetEnableOver( TRUE );
    ZIListCtrl::SetFullRowSelect( TRUE );
    ZIListCtrl::EnableSort( TRUE );


    ZIListCtrl::BuildColumns(8, _gEventReminderColSize, _gEventReminderColText);
    m_ColumnsHasBeenBuilt = TRUE;
    return TRUE;
}

ZBEventActivityReminder&    operator>>( ZBEventActivityReminder& left, ZCEventActivityViewerReminder& listCtrl )
{
    int    Index = listCtrl.GetItemCount();
    int    ImageIndex = 11;
    if (left.GetPriority() == EventPriorityHigh)
        ImageIndex = 10;
    else
        if (left.GetPriority() == EventPriorityLow)
            ImageIndex = 9;
    // Add the priority
    listCtrl.InsertItem( LVIF_IMAGE | LVIF_PARAM, Index, 
                         NULL,
                         0, 0, ImageIndex, (LPARAM)&left);
    // Add the folder name
    listCtrl.SetItem( Index, 1, LVIF_TEXT,
                      left.GetFolderName(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the process name
    listCtrl.SetItem( Index, 2, LVIF_TEXT,
                      left.GetProcessName(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the activity name
    listCtrl.SetItem( Index, 3, LVIF_TEXT,
                      left.GetActivityName(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the activity remaining days
    listCtrl.SetItem( Index, 4, LVIF_TEXT,
                      left.GetRemainingDaysString(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the activity due date
    listCtrl.SetItem( Index, 5, LVIF_TEXT,
                      left.GetFormatedActivityDueDate(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the activity status
    listCtrl.SetItem( Index, 6, LVIF_TEXT,
                      ZProcess::GetStatusString( left.GetActivityStatus() ),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the message
    listCtrl.SetItem( Index, 7, LVIF_TEXT,
                      left.GetMessage(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    return left;
}

LRESULT ZCEventActivityViewerReminder::OnNewActivityEvent( WPARAM wParam, LPARAM lParam ) 
{
    ZBEventActivityReminder*    pEvent = (ZBEventActivityReminder*)lParam;

    // If the columns were never built
    if (!ColumnsHasBeenBuilt())
        BuildColumns();
    *pEvent >> *this;
    return 0;
}
