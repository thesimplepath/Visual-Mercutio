/****************************************************************************
 * ==> PSS_EventActivityLogCtrl --------------------------------------------*
 ****************************************************************************
 * Description : Provides an event activity logger control                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_EventActivityLogCtrl.h"

// processsoft
#include "zEvent\BActVt.h"
#include "zEvent\ZProcess.h"

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
    200, // ProcessFilename
    200, // ExchangeDataFilename
    200, // Process ExchangeDataFilename
    1000 // Comments
};
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_EventActivityLogCtrl, ZIListCtrl)
    //{{AFX_MSG_MAP(PSS_EventActivityLogCtrl)
    ON_MESSAGE(UM_NEWACTIVITYEVENT, OnNewActivityEvent)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_EventActivityLogCtrl
//---------------------------------------------------------------------------
PSS_EventActivityLogCtrl::PSS_EventActivityLogCtrl(ZBEventManager* pEventManager) :
    ZIListCtrl(),
    m_pEventManager(pEventManager),
    m_ColumnsHasBeenBuilt(FALSE)
{}
//---------------------------------------------------------------------------
PSS_EventActivityLogCtrl::PSS_EventActivityLogCtrl(const PSS_EventActivityLogCtrl& other)
{
    THROW("Copy constructor is prohibited for this class");
}
//---------------------------------------------------------------------------
PSS_EventActivityLogCtrl::~PSS_EventActivityLogCtrl()
{}
//---------------------------------------------------------------------------
const PSS_EventActivityLogCtrl& PSS_EventActivityLogCtrl::operator = (const PSS_EventActivityLogCtrl& other)
{
    THROW("Copy operator is prohibited for this class");
}
//---------------------------------------------------------------------------
#ifdef _WIN32
    ZBEventActivity& operator >> (ZBEventActivity& left, PSS_EventActivityLogCtrl& listCtrl)
    {
        const int index      = listCtrl.GetItemCount();
              int imageIndex = 13;

        if (left.GetActivityEventType() != MessageActivity)
            if (left.GetActivityStatus() == ActivityStatusProcessPaused)
                imageIndex = 12;
            else
            if (left.GetActivityStatus() == ActivityStatusProcessAborted)
                imageIndex = 4;
            else
            if (left.GetActivityStatus() == ActivityStatusProcessCompleted)
                imageIndex = 5;
            else
            if (left.GetActivityStatus() == ActivityStatusRequestAcceptation)
                imageIndex = 8;
            else
            if (left.GetActivityStatus() == ActivityStatusAccepted)
                imageIndex = 7;
            else
            if (left.GetActivityStatus() == ActivityStatusRejected)
                imageIndex = 6;
            else
            if (left.GetActivityStatus() == ActivityStatusAttribution)
                imageIndex = 3;
            else
            if (left.GetActivityStatus() == ActivityStatusSent)
                imageIndex = 0;
            else
            if (left.GetActivityStatus() == ActivityStatusAttribution)
                imageIndex = 7;
            else
                imageIndex = 11;

        // add the action icon
        listCtrl.InsertItem(LVIF_IMAGE | LVIF_PARAM, index, NULL, 0, 0, imageIndex, LPARAM(&left));

        // add the action text
        listCtrl.SetItem(index,
                         1,
                         LVIF_TEXT,
                         ZProcess::GetStatusString(left.GetActivityStatus()),
                         0,
                         LVIF_TEXT,
                         LVIF_TEXT,
                         0);

        // add the Activity Type
        listCtrl.SetItem(index, 2, LVIF_TEXT, left.GetActivityType(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the event Date
        listCtrl.SetItem(index, 3, LVIF_TEXT, left.GetFormatedTimeStamp(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the folder name
        listCtrl.SetItem(index, 4, LVIF_TEXT, left.GetFolderName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process name
        listCtrl.SetItem(index, 5, LVIF_TEXT, left.GetProcessName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process creation date
        listCtrl.SetItem(index, 6, LVIF_TEXT, left.GetFormatedProcessCreationDate(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process due date
        listCtrl.SetItem(index, 7, LVIF_TEXT, left.GetFormatedProcessDueDate(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity name
        listCtrl.SetItem(index, 8, LVIF_TEXT, left.GetActivityName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity creation date
        listCtrl.SetItem(index, 9, LVIF_TEXT, left.GetFormatedActivityCreationDate(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the activity due date
        listCtrl.SetItem(index, 10, LVIF_TEXT, left.GetFormatedActivityDueDate(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the sender name
        listCtrl.SetItem(index, 11, LVIF_TEXT, left.GetSender(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the receiver name
        listCtrl.SetItem(index, 12, LVIF_TEXT, left.GetReceiver(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process filename
        listCtrl.SetItem(index, 13, LVIF_TEXT, left.GetProcessFilename(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the exchange date filename
        listCtrl.SetItem(index, 14, LVIF_TEXT, left.GetExchangeDataFilename(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process exchange date filename
        listCtrl.SetItem(index, 15, LVIF_TEXT, left.GetProcessExchangeDataFilename(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the comments
        listCtrl.SetItem(index, 16, LVIF_TEXT, left.GetComments(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        return left;
    }
#endif
//---------------------------------------------------------------------------
void PSS_EventActivityLogCtrl::Initialize (ZBEventManager* pEventManager)
{
    m_pEventManager = pEventManager;

    Refresh();
}
//---------------------------------------------------------------------------
ZBEventActivity* PSS_EventActivityLogCtrl::GetSelectedItem() const
{
    int      index;
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
    {
        index = GetNextSelectedItem(pPos);
        return (ZBEventActivity*)GetItemData(index);
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_EventActivityLogCtrl::Refresh()
{
    DeleteAllItems();

    // if the columns were never built
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    if (m_pEventManager)
    {
        const int count = m_pEventManager->GetEventCount();

        for (int i = 0; i < count; ++i)
            ((ZBEventActivity&)*(m_pEventManager->GetEventAt(i))) >> *this;
    }
}
//---------------------------------------------------------------------------
LRESULT PSS_EventActivityLogCtrl::OnNewActivityEvent(WPARAM wParam, LPARAM lParam)
{
    ZBEventActivity* pEvent = (ZBEventActivity*)lParam;

    // if the columns were never built
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    *pEvent >> *this;

    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_EventActivityLogCtrl::BuildColumns()
{
    // load images
    LoadImageListMasked(IDB_MESSAGEITEM0_ACTEVT, IDB_MESSAGEITEM13_ACTEVT);

    ZIListCtrl::SetEnableOver(TRUE);
    ZIListCtrl::SetFullRowSelect(TRUE);
    ZIListCtrl::EnableSort(TRUE);
    ZIListCtrl::BuildColumns(17, g_EventActivityColSize, g_EventActivityColText);

    m_ColumnsHasBeenBuilt = TRUE;

    return TRUE;
}
//---------------------------------------------------------------------------