/****************************************************************************
 * ==> PSS_ActivityEventCtrl -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an event activity control                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityEventCtrl.h"

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
BEGIN_MESSAGE_MAP(PSS_ActivityEventCtrl, PSS_ListCtrl)
    //{{AFX_MSG_MAP(PSS_ActivityEventCtrl)
    ON_MESSAGE(UM_NEWACTIVITYEVENT, OnNewActivityEvent)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ActivityEventCtrl
//---------------------------------------------------------------------------
PSS_ActivityEventCtrl::PSS_ActivityEventCtrl(ZBEventManager* pEventManager) :
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
PSS_ActivityEvent& operator >> (PSS_ActivityEvent& left, PSS_ActivityEventCtrl& listCtrl)
    {
        const int index      = listCtrl.GetItemCount();
              int imageIndex = 13;

        if (left.GetActivityEventType() != PSS_ActivityEvent::IE_AT_Message)
            if (left.GetActivityStatus() == g_ActivityStatusProcessPaused)
                imageIndex = 12;
            else
            if (left.GetActivityStatus() == g_ActivityStatusProcessAborted)
                imageIndex = 4;
            else
            if (left.GetActivityStatus() == g_ActivityStatusProcessCompleted)
                imageIndex = 5;
            else
            if (left.GetActivityStatus() == g_ActivityStatusRequestAcceptation)
                imageIndex = 8;
            else
            if (left.GetActivityStatus() == g_ActivityStatusAccepted)
                imageIndex = 7;
            else
            if (left.GetActivityStatus() == g_ActivityStatusRejected)
                imageIndex = 6;
            else
            if (left.GetActivityStatus() == g_ActivityStatusAttribution)
                imageIndex = 3;
            else
            if (left.GetActivityStatus() == g_ActivityStatusSent)
                imageIndex = 0;
            else
            if (left.GetActivityStatus() == g_ActivityStatusAttribution)
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
void PSS_ActivityEventCtrl::Initialize(ZBEventManager* pEventManager)
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
