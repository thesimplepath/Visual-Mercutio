// Source file: MessageC.cpp

#include <StdAfx.h>
#include "MessageC.h"

// resources
#ifndef _WIN32
    #include "ZWinUtilRes.h"
#else
    #include "ZWinUtil32Res.h"
#endif

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

static int _gMessageColText[] = { IDS_COLUMN1_EVENTLOG, IDS_COLUMN2_EVENTLOG, IDS_COLUMN3_EVENTLOG };
static int _gMessageColSize[] = { 160, 300, 300 };


BEGIN_MESSAGE_MAP(ZCEventLog, CListCtrl)
    //{{AFX_MSG_MAP(ZCEventLog)
    ON_MESSAGE(UM_NEWEVENT, OnNewEvent)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCEventLog 


ZCEventLog::ZCEventLog (ZBEventManager* pEventManager)
      : m_pEventManager(pEventManager), m_ColumnsHasBeenBuilt(FALSE)
{
}


ZCEventLog::~ZCEventLog()
{
}



void ZCEventLog::Initialize (ZBEventManager* pEventManager)
{
    m_pEventManager = pEventManager;
    ZCEventLog::Refresh();
}

void ZCEventLog::Refresh ()
{
    DeleteAllItems();
    // If the columns were never built
    if (!ColumnsHasBeenBuilt())
        BuildColumns();
    for (int i = 0; i < m_pEventManager->GetEventCount(); ++i)
        ((ZBEventServer&)*(m_pEventManager->GetEventAt(i))) >> *this;
}


BOOL    ZCEventLog::BuildColumns()
{
    ZIListCtrl::BuildColumns(3, _gMessageColSize, _gMessageColText);
    m_ColumnsHasBeenBuilt = TRUE;
    return TRUE;
}

ZBEventServer&    operator>>( ZBEventServer& left, ZCEventLog& listCtrl )
{
    int    Index = listCtrl.GetItemCount();
    // Add the event Date
    listCtrl.InsertItem( Index, left.GetFormatedTimeStamp() );
    // Add the filename
    listCtrl.SetItem( Index, 1, LVIF_TEXT,
                      left.GetFilename(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the result
    listCtrl.SetItem( Index, 2, LVIF_TEXT,
                      left.GetEventResultStr(),
                      0, LVIF_TEXT, LVIF_TEXT, 0 );
    return left;
}

LRESULT ZCEventLog::OnNewEvent( WPARAM wParam, LPARAM lParam ) 
{
    ZBEventServer*    pEvent = (ZBEventServer*)lParam;

    // If the columns were never built
    if (!ColumnsHasBeenBuilt())
        BuildColumns();
    *pEvent >> *this;
    return 1;
}
