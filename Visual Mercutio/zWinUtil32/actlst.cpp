//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//    Source file: ActLst.cpp

#include <StdAfx.h>

#include "ActLst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _WIN32
BEGIN_MESSAGE_MAP(ZCActivityList, CListCtrl)
#endif
#ifndef _WIN32
BEGIN_MESSAGE_MAP(ZCActivityList, CListBox)
#endif
    //{{AFX_MSG_MAP(ZCActivityList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCActivityList 

#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif
#include "zRes32\ZRes.h"

#ifdef _WIN32
static int _gActivityColText[] = { IDS_NOCOLUMNHEADER, IDS_COLUMN1_ACTIVITY, IDS_COLUMNDESC_ACTIVITY };
static int _gActivityColSize[] = { 20, 80, 265 };
#endif

ZCActivityList::ZCActivityList (ZProcess* pProcess, int ActivityType, CString ExcludedActivity, BOOL StopWhenFound, BOOL AttributedActivityOnly)
:    m_pProcess(pProcess), m_ActivityType(ActivityType), 
    m_ExcludedActivity(ExcludedActivity), m_StopWhenFound(StopWhenFound),
    m_AttributedActivityOnly(AttributedActivityOnly)
{
}


ZCActivityList::~ZCActivityList()
{
}



int ZCActivityList::Initialize (ZProcess* pProcess, int ActivityType, CString ExcludedActivity, BOOL StopWhenFound, BOOL AttributedActivityOnly)
{
    m_pProcess = pProcess;
    m_ActivityType = ActivityType;
    m_ExcludedActivity = ExcludedActivity;
    m_StopWhenFound = StopWhenFound;
    m_AttributedActivityOnly = AttributedActivityOnly;
    BuildColumns(3, _gActivityColSize, _gActivityColText );
    // Load images
    LoadImageListMasked( IDB_PROCESSITEM, IDB_PROCESSCHOOSEITEM );
    ZIListCtrl::SetEnableOver( TRUE );
    ZIListCtrl::SetFullRowSelect( TRUE );

    return ZCActivityList::Refresh();
}

int ZCActivityList::Refresh ()
{
#ifdef _WIN32
    DeleteAllItems();
#endif

    CStringArray    ActivityArray;

#ifndef _WIN32
    ResetContent();
#endif

    size_t        Count = m_pProcess->GetActivityCount();
      for (size_t Index = 0; Index < Count; ++Index)
    {
        ZBaseActivity*    pActivity = m_pProcess->GetActivityAt( Index );
        if (!pActivity)
            continue;
#ifndef _WIN32
        AddString( pActivity->GetName() );
#endif
#ifdef _WIN32
        int    ImageIndex;
          if (pActivity->IsKindOf(RUNTIME_CLASS(ZActivity)))
        {
            ImageIndex = 1;
        }
        else
              if (pActivity->IsKindOf(RUNTIME_CLASS(ZProcess)))
            {
                if (((ZProcess*)pActivity)->GetRunMode() == SequenceRun)
                    ImageIndex = 0;
                else
                    ImageIndex = 2;
            }
        // Add the action icon
        InsertItem( LVIF_IMAGE | LVIF_PARAM, Index, 
                    NULL,
                    0, 0, 
                    ImageIndex, 
                    0);

        SetItem( Index, 1, LVIF_TEXT,
                 pActivity->GetName(),
                 0, LVIF_TEXT, LVIF_TEXT, 0 );
        SetItem( Index, 2, LVIF_TEXT,
                 pActivity->GetDescription(),
                 0, LVIF_TEXT, LVIF_TEXT, 0 );

#endif
    }

    return Count;
}

CString    ZCActivityList::GetSelectedActivity()
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
        return GetItemText( Index, 1 );
    }
#endif

    return "";
}


int    ZCActivityList::GetSelectedActivities( CStringArray Array )
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
