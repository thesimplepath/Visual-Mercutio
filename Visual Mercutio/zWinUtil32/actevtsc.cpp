// Source file: ActEvtSC.cpp

#include <StdAfx.h>
#include "ActEvtSC.h"

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

static int _gReduceEventActivityColText[] = {    IDS_NOCOLUMNHEADER, 
                                                IDS_COLUMN5_EVENTACTIVITY, 
                                                IDS_COLUMN12_EVENTACTIVITY,
                                                IDS_COLUMN1_EVENTACTIVITY, 
                                                IDS_COLUMN2_EVENTACTIVITY, 
                                                IDS_COLUMN8_EVENTACTIVITY, 
                                                IDS_COLUMN13_EVENTACTIVITY };
static int _gReduceEventActivityColSize[] ={20,        // The icon type
                                            100,     // ActivityName
                                            150,    // The action text
                                            100,    // FolderName
                                            100,     // ProcessName
                                            100,     // Sender    
                                            1000 };    // Comments


BEGIN_MESSAGE_MAP(ZCEventActivity, ZIListCtrl)
    //{{AFX_MSG_MAP(ZCEventActivity)
    ON_MESSAGE(UM_NEWACTIVITYEVENT, OnNewActivityEvent)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCEventActivity 


ZCEventActivity::ZCEventActivity (ZBEventManager* pEventManager)
      : m_pEventManager(pEventManager), m_ColumnsHasBeenBuilt(FALSE)
{
}


ZCEventActivity::~ZCEventActivity()
{
}



void ZCEventActivity::Initialize (ZBEventManager* pEventManager)
{
    m_pEventManager = pEventManager;
    ZCEventActivity::Refresh();
}

void ZCEventActivity::Refresh ()
{
    DeleteAllItems();
    // If the columns were never built
    if (!ColumnsHasBeenBuilt())
        BuildColumns();
    for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
        ((ZBEventActivity&)*(m_pEventManager->GetEventAt(i))) >> *this;
}

ZBEventActivity*    ZCEventActivity::GetSelectedItem() const
{
    int    Index;
    POSITION pos = GetFirstSelectedItemPosition();
    if (pos != NULL)     
    {
        Index = GetNextSelectedItem( pos );
        return (ZBEventActivity*)GetItemData( Index );
    }
    return NULL;
}

BOOL    ZCEventActivity::BuildColumns()
{
    // Load images
    LoadImageListMasked( IDB_MESSAGEITEM0_ACTEVT, IDB_MESSAGEITEM13_ACTEVT );
    ZIListCtrl::SetEnableOver( TRUE );
    ZIListCtrl::SetFullRowSelect( TRUE );
    ZIListCtrl::EnableSort( TRUE );

    ZIListCtrl::BuildColumns(7, _gReduceEventActivityColSize, _gReduceEventActivityColText);
    m_ColumnsHasBeenBuilt = TRUE;
    return TRUE;
}

ZBEventActivity&    operator>>( ZBEventActivity& left, ZCEventActivity& listCtrl )
{
    int    Index = listCtrl.GetItemCount();
    int    ImageIndex = 13;
    if (left.GetActivityEventType() != MessageActivity)
    {
        if (left.GetActivityStatus() == ActivityStatusProcessPaused)
            ImageIndex = 12;
        else
        if (left.GetActivityStatus() == ActivityStatusProcessAborted)
            ImageIndex = 4;
        else
        if (left.GetActivityStatus() == ActivityStatusProcessCompleted)
            ImageIndex = 5;
        else
        if (left.GetActivityStatus() == ActivityStatusRequestAcceptation)
            ImageIndex = 8;
        else
        if (left.GetActivityStatus() == ActivityStatusAccepted)
            ImageIndex = 7;
        else
        if (left.GetActivityStatus() == ActivityStatusRejected)
            ImageIndex = 6;
        else
        if (left.GetActivityStatus() == ActivityStatusAttribution)
            ImageIndex = 3;
        else
        if (left.GetActivityStatus() == ActivityStatusSent)
            ImageIndex = 0;
        else
        if (left.GetActivityStatus() == ActivityStatusAttribution)
            ImageIndex = 7;
        else
            ImageIndex = 11;
    }
    // Add the action icon
    listCtrl.InsertItem( LVIF_IMAGE | LVIF_PARAM, Index, 
                         NULL,
                         0, 0, 
                         ImageIndex, 
                         (LPARAM)&left);
    // Add the activity name
    listCtrl.SetItem( Index, 1, LVIF_TEXT,
                      left.GetActivityName(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the action text
    listCtrl.SetItem( Index, 2, LVIF_TEXT,
                      ZProcess::GetStatusString( left.GetActivityStatus() ),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the folder name
    listCtrl.SetItem( Index, 3, LVIF_TEXT,
                      left.GetFolderName(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the process name
    listCtrl.SetItem( Index, 4, LVIF_TEXT,
                      left.GetProcessName(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the sender name
    listCtrl.SetItem( Index, 5, LVIF_TEXT,
                      left.GetSender(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the comments
    listCtrl.SetItem( Index, 6, LVIF_TEXT,
                      left.GetComments(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    return left;
}

LRESULT ZCEventActivity::OnNewActivityEvent( WPARAM wParam, LPARAM lParam ) 
{
    ZBEventActivity*    pEvent = (ZBEventActivity*)lParam;

    // If the columns were never built
    if (!ColumnsHasBeenBuilt())
        BuildColumns();
    *pEvent >> *this;
    return 1;
}
