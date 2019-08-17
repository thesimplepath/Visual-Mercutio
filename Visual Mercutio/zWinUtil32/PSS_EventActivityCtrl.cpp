/****************************************************************************
 * ==> PSS_EventActivityCtrl -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an event activity control                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_EventActivityCtrl.h"

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
BEGIN_MESSAGE_MAP(PSS_EventActivityCtrl, ZIListCtrl)
    //{{AFX_MSG_MAP(PSS_EventActivityCtrl)
    ON_MESSAGE(UM_NEWACTIVITYEVENT, OnNewActivityEvent)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_EventActivityCtrl
//---------------------------------------------------------------------------
PSS_EventActivityCtrl::PSS_EventActivityCtrl(ZBEventManager* pEventManager) :
    m_pEventManager(pEventManager),
    m_ColumnsHasBeenBuilt(FALSE)
{}
//---------------------------------------------------------------------------
PSS_EventActivityCtrl::PSS_EventActivityCtrl(const PSS_EventActivityCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_EventActivityCtrl::~PSS_EventActivityCtrl()
{}
//---------------------------------------------------------------------------
const PSS_EventActivityCtrl& PSS_EventActivityCtrl::operator = (const PSS_EventActivityCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
#ifdef _WIN32
    ZBEventActivity& operator >> (ZBEventActivity& left, PSS_EventActivityCtrl& listCtrl)
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
        listCtrl.InsertItem( LVIF_IMAGE | LVIF_PARAM, index, NULL, 0, 0, imageIndex, (LPARAM)&left);

        // add the activity name
        listCtrl.SetItem(index, 1, LVIF_TEXT, left.GetActivityName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the action text
        listCtrl.SetItem(index, 2, LVIF_TEXT, ZProcess::GetStatusString(left.GetActivityStatus()), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the folder name
        listCtrl.SetItem(index, 3, LVIF_TEXT, left.GetFolderName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the process name
        listCtrl.SetItem(index, 4, LVIF_TEXT, left.GetProcessName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the sender name
        listCtrl.SetItem(index, 5, LVIF_TEXT, left.GetSender(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the comments
        listCtrl.SetItem(index, 6, LVIF_TEXT, left.GetComments(), 0, LVIF_TEXT, LVIF_TEXT, 0);
        return left;
    }
#endif
//---------------------------------------------------------------------------
void PSS_EventActivityCtrl::Initialize(ZBEventManager* pEventManager)
{
    m_pEventManager = pEventManager;

    Refresh();
}
//---------------------------------------------------------------------------
ZBEventActivity* PSS_EventActivityCtrl::GetSelectedItem() const
{
    POSITION pPos = GetFirstSelectedItemPosition();

    if (pPos)
        return (ZBEventActivity*)GetItemData(GetNextSelectedItem(pPos));

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_EventActivityCtrl::Refresh()
{
    DeleteAllItems();

    // were the columns never built?
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    const int eventCount = m_pEventManager->GetEventCount();

    for (int i = 0; i < eventCount; ++i)
        ((ZBEventActivity&)*(m_pEventManager->GetEventAt(i))) >> *this;
}
//---------------------------------------------------------------------------
LRESULT PSS_EventActivityCtrl::OnNewActivityEvent(WPARAM wParam, LPARAM lParam)
{
    ZBEventActivity* pEvent = (ZBEventActivity*)lParam;

    // were the columns never built?
    if (!ColumnsHasBeenBuilt())
        BuildColumns();

    *pEvent >> *this;
    return 1;
}
//---------------------------------------------------------------------------
BOOL PSS_EventActivityCtrl::BuildColumns()
{
    // load images
    LoadImageListMasked(IDB_MESSAGEITEM0_ACTEVT, IDB_MESSAGEITEM13_ACTEVT);

    ZIListCtrl::SetEnableOver(TRUE);
    ZIListCtrl::SetFullRowSelect(TRUE);
    ZIListCtrl::EnableSort(TRUE);
    ZIListCtrl::BuildColumns(7, g_ReduceEventActivityColSize, g_ReduceEventActivityColText);

    m_ColumnsHasBeenBuilt = TRUE;

    return TRUE;
}
//---------------------------------------------------------------------------