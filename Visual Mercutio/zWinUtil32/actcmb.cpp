//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//    Source file: z:\adsoft~1\ZProcess\ActivityCmb.cpp

#include <StdAfx.h>

#include "ActCmb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//BEGIN_MESSAGE_MAP(ZCActivityCombo, CCJListCtrl)
    //{{AFX_MSG_MAP(ZCActivityCombo)
    //}}AFX_MSG_MAP
//END_MESSAGE_MAP()


// Class ZCActivityCombo 


ZCActivityCombo::ZCActivityCombo (ZProcess* pProcess, int ActivityType, CString ExcludedActivity, BOOL StopWhenFound, BOOL AttributedActivityOnly)
:    m_pProcess(pProcess), m_ActivityType(ActivityType), 
    m_ExcludedActivity(ExcludedActivity), m_StopWhenFound(StopWhenFound),
    m_AttributedActivityOnly(AttributedActivityOnly)
{
}


ZCActivityCombo::~ZCActivityCombo()
{
}



int ZCActivityCombo::Initialize (ZProcess* pProcess, int ActivityType, CString ExcludedActivity, BOOL StopWhenFound, BOOL AttributedActivityOnly)
{
    m_pProcess = pProcess;
    m_ActivityType = ActivityType;
    m_ExcludedActivity = ExcludedActivity;
    m_StopWhenFound = StopWhenFound;
    m_AttributedActivityOnly = AttributedActivityOnly;
    return ZCActivityCombo::Refresh();
}

int ZCActivityCombo::Refresh()
{
    CStringArray    ActivityArray;

    ResetContent();
    int    Count = m_pProcess->GetActivityNameArray( ActivityArray, m_ActivityType, m_ExcludedActivity, m_StopWhenFound, m_AttributedActivityOnly );
    for (register size_t Index = 0; Index < (size_t)Count; ++Index)
        AddString( ActivityArray[Index] );
    return Count;
}

CString    ZCActivityCombo::GetSelectedActivity()
{
    int    Index = GetCurSel();
    if (Index != CB_ERR)
    {
        CString    Text;
        GetLBText( Index, Text );
        return Text;
    }
    return "";
}


void    ZCActivityCombo::SelectActivity( const CString ActivityName )
{
    int    Index = FindString( -1, ActivityName );
    if (Index != CB_ERR)
        SetCurSel( Index );
}
