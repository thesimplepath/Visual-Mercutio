//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//    Source file: ActLstTk.cpp

#include <StdAfx.h>
#include "ActLstTk.h"

// processsoft
#include "zEvent\ProcIter.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

#ifdef _WIN32
BEGIN_MESSAGE_MAP(ZCActivityTaskList, CListCtrl)
#endif
#ifndef _WIN32
BEGIN_MESSAGE_MAP(ZCActivityTaskList, CListBox)
#endif
    //{{AFX_MSG_MAP(ZCActivityTaskList)
    ON_MESSAGE(UM_ACTIVITYLISTCHANGE, OnActivityListChange)
    ON_MESSAGE(UM_SELECTACTIVITYINTASKLIST, OnSelectActivityInTaskList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

#ifdef _WIN32
static int _gTaskActivityColText[] = {    IDS_NOCOLUMNHEADER, 
                                        IDS_COLUMN1_TASKACTIVITY, IDS_COLUMN2_TASKACTIVITY, 
                                        IDS_COLUMN3_TASKACTIVITY, IDS_COLUMN4_TASKACTIVITY,
                                        IDS_COLUMN5_TASKACTIVITY, IDS_COLUMN6_TASKACTIVITY};
static int _gTaskActivityColSize[] = {    20, 
                                        100, 
                                        120, 
                                        80, 
                                        120, 
                                        120, 
                                        100 };
#endif

ZCActivityTaskList::ZCActivityTaskList (ZProcess* pProcess)
:    m_pProcess(pProcess), m_HasBuiltColumns(FALSE)
{
}


ZCActivityTaskList::~ZCActivityTaskList()
{
}



int ZCActivityTaskList::Initialize (ZProcess* pProcess)
{
    m_pProcess = pProcess;
    return ZCActivityTaskList::Refresh();
}

#ifdef _WIN32
void ZCActivityTaskList::BuildColumns()
{
    // Load images
    LoadImageListMasked( IDB_MESSAGEITEM0_ACTEVT, IDB_MESSAGEITEM16_ACTEVT );
    ZIListCtrl::SetEnableOver( TRUE );
    ZIListCtrl::SetFullRowSelect( TRUE );

    ZIListCtrl::BuildColumns(7, _gTaskActivityColSize, _gTaskActivityColText );
    m_HasBuiltColumns = TRUE;
}
#endif

int ZCActivityTaskList::Refresh()
{
    if (!m_pProcess)
        return 0;
#ifdef _WIN32
    if (!HasBuiltColumns())
        BuildColumns();
    DeleteAllItems();
#endif

#ifndef _WIN32
    ResetContent();
#endif
    ZProcessIterator    Iterator( m_pProcess );
      for (ZBaseActivity* pRunner = Iterator.StartIterator(Iterator.GetFirstValidActivity()); pRunner; pRunner = Iterator.GetNextValidActivity())
    {
        if (m_pProcess->GetCurrentActivity() && m_pProcess->GetCurrentActivity()->GetName() == pRunner->GetName())
            InsertActivity( *pRunner, true );
        else
            InsertActivity( *pRunner, false );
    }

    return m_pProcess->GetActivityCount();
}

CString    ZCActivityTaskList::GetSelectedActivity()
{
#ifndef _WIN32    // In 16bit
    int    Index = GetCurSel();
    if (Index != CB_ERR)
    {
        CString    Text;
        GetLBText( Index, Text );
        return Text;
    }
#endif

#ifdef _WIN32    // In 32bit
    int    Index;
    POSITION pos = GetFirstSelectedItemPosition();
    if (pos != NULL)     
    {
        Index = GetNextSelectedItem( pos );
        return GetItemText( Index, 0 );
    }
#endif

    return "";
}


int    ZCActivityTaskList::GetSelectedActivities( CStringArray Array )
{
    Array.RemoveAll();
    int    Count = 0;

#ifndef _WIN32    // In 16bit
    Count = GetSelCount();
    if (Count > 0)
    {
        // Get the list of selection IDs.
        int* pItems = new int [Count];
        GetSelItems( Count, pItems );
        for (int i = 0; i < Count; ++i) 
        {
            CString    Text;
            GetLBText( pItems[i], Text );
            Array.Add( Text );
        }
        // Done with the item list.
        delete pItems;
    }
#endif
    
#ifdef _WIN32    // In 32bit
    Count = GetSelectedCount();
    POSITION pos = GetFirstSelectedItemPosition();
    while (pos)
    {
        int nItem = GetNextSelectedItem(pos);
        Array.Add( GetItemText( nItem, 0 ) );
    }
#endif

    return Count;
}


void    ZCActivityTaskList::ClearAllSelection()
{
    int iItem = -1;

    // as long as GetNextItem found an item...
    while (GetItemCount() > 0 && (iItem = GetNextItem(iItem, LVNI_ALL)) > -1 )
    {
        SetItemState(iItem,
                     0,              // nState
                     LVIS_SELECTED); // nMask
    }
}
void        ZCActivityTaskList::SelectActivity (size_t ActivityIndex, BOOL ShouldClearAllSelection)
{
    if (ShouldClearAllSelection)
        ClearAllSelection();
    SetItemState( ActivityIndex,
                  LVIS_SELECTED,  // nState
                  LVIS_SELECTED); 
}
void        ZCActivityTaskList::SelectActivity (const CString ActivityName, BOOL ShouldClearAllSelection)
{
    if (ShouldClearAllSelection)
        ClearAllSelection();
    // Find the activity
    for (register size_t Index = 0; Index < (size_t)m_pProcess->GetActivityCount(); ++Index)
        if (m_pProcess->GetActivityAt(Index)->GetName() == ActivityName)
        {
            SetItemState( Index,
                          LVIS_SELECTED,  // nState
                          LVIS_SELECTED); 
            return;
        }
}

void    ZCActivityTaskList::InsertActivity( ZBaseActivity& Activity, bool IsCurrentActivity )
{
    if (!HasBuiltColumns())
        BuildColumns();
#ifndef _WIN32
          CString    Line = Activity.GetActivityName();
          Line += "  " + Activity.GetStatusString();
          if (!Activity.GetInitiator().IsEmpty())
          {
              Line += " initié par: " + Activity.GetInitiator();
            char    buf[50];
            sprintf( buf, " le: %d.%d.%d", Activity.GetStartDate().GetDay(), Activity.GetStartDate().GetMonth(), Activity.GetStartDate().GetYear());
            Line += buf;
          }
        AddString( Line );
#endif
#ifdef _WIN32
    {
        char    buf[50];
        int    Index = GetItemCount();
        int    ImageIndex = 11;
        if (IsCurrentActivity == true ||
            Activity.GetActivityStatus() == ActivityStarted)
            ImageIndex = 14;
        else
        if (Activity.GetActivityStatus() == ActivitySent)
            ImageIndex = 0;
        else
        if (Activity.GetActivityStatus() == ActivitySentForAcceptation)
            ImageIndex = 8;
        else
        if (Activity.GetActivityStatus() == ActivityCompleted)
            ImageIndex = 15;
        else
        if (Activity.GetActivityStatus() == ActivityRejected)
            ImageIndex = 6;
        else
        if (Activity.GetActivityStatus() == ActivitySuspended)
            ImageIndex = 12;
        else
        if (Activity.GetActivityStatus() == ActivityAborted)
            ImageIndex = 4;
        else
        if (Activity.GetActivityStatus() == ActivityNotStarted)
            ImageIndex = 16;
        // Add the action icon
        InsertItem( LVIF_IMAGE | LVIF_PARAM, Index, 
                    NULL,
                    0, 0, 
                    ImageIndex, 
                    (LPARAM)&Activity);
        // Activity name
        // The status
        SetItem( Index, 1, LVIF_TEXT,
                 Activity.GetName(),
                 0, LVIF_TEXT, LVIF_TEXT, 0 );
        // The status
        SetItem( Index, 2, LVIF_TEXT,
                 Activity.GetActivityStatusString(),
                 0, LVIF_TEXT, LVIF_TEXT, 0 );
        // The initiator
        SetItem( Index, 3, LVIF_TEXT,
                 Activity.GetInitiator(),
                 0, LVIF_TEXT, LVIF_TEXT, 0 );

        CString    Text;
        Text = (Activity.GetActivityStatus() == ActivityNotStarted) ? " - " :    ((ZBDate&)(Activity.GetStartDate())).GetStandardFormatedDate();
        // The creation date
        SetItem( Index, 4, LVIF_TEXT,
                 Text,
                 0, LVIF_TEXT, LVIF_TEXT, 0 );

        Text = (Activity.GetActivityStatus() == ActivityNotStarted) ? " - " :    ((ZBDate&)(Activity.GetForecastedEndDate())).GetStandardFormatedDate();
        // The due date
        SetItem(Index, 5, LVIF_TEXT,
                Text,
                0, LVIF_TEXT, LVIF_TEXT, 0 );

        if (Activity.GetActivityStatus() == ActivityNotStarted)
            strcpy( buf, " - " );
        else
        {
            // The remaining days
            ZBDate            DateEnd = Activity.GetForecastedEndDate();
            DateEnd.ClearTime();
            ZBDate            DateToday = ZBDate::GetToday();
            DateToday.ClearTime();
            COleDateTimeSpan    DateTimeSpan( DateEnd - DateToday );
            if (DateTimeSpan.GetStatus() == COleDateTimeSpan::valid)
                sprintf( buf, "%d", (int)DateTimeSpan.GetTotalDays());
            else
                strcpy( buf, "-" );
        }
        SetItem( Index, 6, LVIF_TEXT,
                 buf,
                 0, LVIF_TEXT, LVIF_TEXT, 0 );
    }
#endif
}

LRESULT ZCActivityTaskList::OnActivityListChange( WPARAM wParam, LPARAM lParam )
{
    Refresh();
    return 1;
}


LRESULT ZCActivityTaskList::OnSelectActivityInTaskList( WPARAM wParam, LPARAM lParam )
{
    ZActivity*    pActivity = (ZActivity*)lParam;
    SelectActivity( pActivity->GetName(), TRUE );
    return 1;
}
