//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//    Source file: ActLst.cpp

#include <StdAfx.h>

#include "ActLstAt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _WIN32
BEGIN_MESSAGE_MAP(ZCActivityListAttribution, CListCtrl)
#endif
#ifndef _WIN32
BEGIN_MESSAGE_MAP(ZCActivityListAttribution, CListBox)
#endif
    //{{AFX_MSG_MAP(ZCActivityListAttribution)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCActivityListAttribution 

#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif
#include "zRes32\ZRes.h"

#ifdef _WIN32
static int _gActivityAttrColText[] = { IDS_COLUMN1_ACTIVITY, IDS_COLUMN2_ACTIVITY };
static int _gActivityAttrColSize[] = { 80, 165 };
#endif

ZCActivityListAttribution::ZCActivityListAttribution (ZProcess* pProcess, int ActivityType, CString ExcludedActivity, BOOL StopWhenFound, BOOL AttributedActivityOnly)
:    m_pProcess(pProcess), m_ActivityType(ActivityType), 
    m_ExcludedActivity(ExcludedActivity), m_StopWhenFound(StopWhenFound),
    m_AttributedActivityOnly(AttributedActivityOnly)
{
}


ZCActivityListAttribution::~ZCActivityListAttribution()
{
}



int ZCActivityListAttribution::Initialize (ZProcess* pProcess, int ActivityType, CString ExcludedActivity, BOOL StopWhenFound, BOOL AttributedActivityOnly)
{
    m_pProcess = pProcess;
    m_ActivityType = ActivityType;
    m_ExcludedActivity = ExcludedActivity;
    m_StopWhenFound = StopWhenFound;
    m_AttributedActivityOnly = AttributedActivityOnly;
    return ZCActivityListAttribution::Refresh();
}

int ZCActivityListAttribution::Refresh ()
{
#ifdef _WIN32
    BuildColumns(2, _gActivityAttrColText, _gActivityAttrColSize);
    DeleteAllItems();
#endif

    CStringArray    ActivityArray;

#ifndef _WIN32
    ResetContent();
#endif

    int    Count = m_pProcess->GetActivityNameArray( ActivityArray, m_ActivityType, m_ExcludedActivity, m_StopWhenFound, m_AttributedActivityOnly );
    for (register size_t Index = 0; Index < (size_t)Count; ++Index)
#ifndef _WIN32
        AddString( ActivityArray[Index] );
#endif
#ifdef _WIN32
    {
        InsertItem( Index, ActivityArray[Index] );
        ZBaseActivity*    pActivity = m_pProcess->FindActivity( ActivityArray[Index] );

        SetItem( Index, 1, LVIF_TEXT,
        (pActivity) ? pActivity->GetAttributedByActivity() : "",
                 0, LVIF_TEXT, LVIF_TEXT, 0 );

    }
#endif
    return Count;
}

CString    ZCActivityListAttribution::GetSelectedActivity()
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


int    ZCActivityListAttribution::GetSelectedActivities( CStringArray Array )
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
