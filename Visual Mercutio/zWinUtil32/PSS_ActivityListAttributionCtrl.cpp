/****************************************************************************
 * ==> PSS_ActivityListAttributionCtrl -------------------------------------*
 ****************************************************************************
 * Description : Provides an activity list attribution control              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityListAttributionCtrl.h"

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

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
#ifdef _WIN32
    static int g_ActivityAttrColText[] =
    {
        IDS_COLUMN1_ACTIVITY,
        IDS_COLUMN2_ACTIVITY
    };

    static int g_ActivityAttrColSize[] =
    {
        80,
        165
    };
#endif
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
#ifdef _WIN32
    BEGIN_MESSAGE_MAP(PSS_ActivityListAttributionCtrl, CListCtrl)
#else
    BEGIN_MESSAGE_MAP(PSS_ActivityListAttributionCtrl, CListBox)
#endif
    //{{AFX_MSG_MAP(PSS_ActivityListAttributionCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ActivityListAttributionCtrl
//---------------------------------------------------------------------------
PSS_ActivityListAttributionCtrl::PSS_ActivityListAttributionCtrl(ZProcess*      pProcess,
                                                                 int            activityType,
                                                                 const CString& excludedActivity,
                                                                 BOOL           stopOnFound,
                                                                 BOOL           attributedActivityOnly) :
    #ifdef _WIN32
        // 32 bit version
        ZIListCtrl(),
    #else
        // 16 bit version
        CListBox(),
    #endif
    m_pProcess(pProcess),
    m_ActivityType(activityType),
    m_ExcludedActivity(excludedActivity),
    m_StopOnFound(stopOnFound),
    m_AttributedActivityOnly(attributedActivityOnly)
{}
//---------------------------------------------------------------------------
PSS_ActivityListAttributionCtrl::PSS_ActivityListAttributionCtrl(const PSS_ActivityListAttributionCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityListAttributionCtrl::~PSS_ActivityListAttributionCtrl()
{}
//---------------------------------------------------------------------------
const PSS_ActivityListAttributionCtrl& PSS_ActivityListAttributionCtrl::operator = (const PSS_ActivityListAttributionCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_ActivityListAttributionCtrl::Initialize (ZProcess*      pProcess,
                                                 int            activityType,
                                                 const CString& excludedActivity,
                                                 BOOL           stopOnFound,
                                                 BOOL           attributedActivityOnly)
{
    m_pProcess               = pProcess;
    m_ActivityType           = activityType;
    m_ExcludedActivity       = excludedActivity;
    m_StopOnFound            = stopOnFound;
    m_AttributedActivityOnly = attributedActivityOnly;

    return Refresh();
}
//---------------------------------------------------------------------------
CString PSS_ActivityListAttributionCtrl::GetSelectedActivity()
{
    // 16 bit version
    #ifndef _WIN32
        const int index = GetCurSel();

        if (index != CB_ERR)
        {
            CString text;
            GetLBText(index, text);
            return text;
        }
    #endif

    // 32 bit version
    #ifdef _WIN32
        POSITION pPos = GetFirstSelectedItemPosition();

        if (pPos)
            return GetItemText(GetNextSelectedItem(pPos), 0);
    #endif

    return "";
}
//---------------------------------------------------------------------------
int PSS_ActivityListAttributionCtrl::GetSelectedActivities(CStringArray& activitiesArray)
{
    activitiesArray.RemoveAll();

    // 16 bit version
    #ifndef _WIN32
        const int count = GetSelCount();

        if (count > 0)
        {
            // get the list of selection IDs.
            int* pItems = new int[count];
            GetSelItems(count, pItems);

            for (int i = 0; i < count; ++i)
            {
                CString text;
                GetLBText(pItems[i], text);
                Array.Add(text);
            }

            // done with the item list
            delete pItems;
        }
    #endif

    // 32 bit version
    #ifdef _WIN32
        const int      count = GetSelectedCount();
              POSITION pPos  = GetFirstSelectedItemPosition();

        while (pPos)
            activitiesArray.Add(GetItemText(GetNextSelectedItem(pPos), 0));
    #endif

    return count;
}
//---------------------------------------------------------------------------
int PSS_ActivityListAttributionCtrl::Refresh()
{
    #ifdef _WIN32
        BuildColumns(2, g_ActivityAttrColText, g_ActivityAttrColSize);
        DeleteAllItems();
    #endif

    CStringArray activityArray;

    #ifndef _WIN32
        ResetContent();
    #endif

    const int count = m_pProcess->GetActivityNameArray(activityArray,
                                                       m_ActivityType,
                                                       m_ExcludedActivity,
                                                       m_StopOnFound,
                                                       m_AttributedActivityOnly);

    for (register std::size_t index = 0; index < std::size_t(count); ++index)
    #ifndef _WIN32
            AddString(ActivityArray[index]);
    #endif
    #ifdef _WIN32
        {
            InsertItem(index, activityArray[index]);

            ZBaseActivity* pActivity = m_pProcess->FindActivity(activityArray[index]);

            SetItem(index, 1, LVIF_TEXT, pActivity ? pActivity->GetAttributedByActivity() : "", 0, LVIF_TEXT, LVIF_TEXT, 0);
        }
    #endif

    return count;
}
//---------------------------------------------------------------------------
