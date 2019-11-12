/****************************************************************************
 * ==> PSS_ActivityTaskListCtrl --------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity task list control                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityTaskListCtrl.h"

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

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
#ifdef _WIN32
    static int g_TaskActivityColText[] =
    {
        IDS_NOCOLUMNHEADER,
        IDS_COLUMN1_TASKACTIVITY,
        IDS_COLUMN2_TASKACTIVITY,
        IDS_COLUMN3_TASKACTIVITY,
        IDS_COLUMN4_TASKACTIVITY,
        IDS_COLUMN5_TASKACTIVITY,
        IDS_COLUMN6_TASKACTIVITY
    };

    static int g_TaskActivityColSize[] =
    {
        20,
        100,
        120,
        80,
        120,
        120,
        100
    };
#endif
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
#ifdef _WIN32
    BEGIN_MESSAGE_MAP(PSS_ActivityTaskListCtrl, PSS_ListCtrl)
#else
    BEGIN_MESSAGE_MAP(PSS_ActivityTaskListCtrl, CListBox)
#endif
    //{{AFX_MSG_MAP(PSS_ActivityTaskListCtrl)
    ON_MESSAGE(UM_ACTIVITYLISTCHANGE, OnActivityListChange)
    ON_MESSAGE(UM_SELECTACTIVITYINTASKLIST, OnSelectActivityInTaskList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ActivityTaskListCtrl
//---------------------------------------------------------------------------
PSS_ActivityTaskListCtrl::PSS_ActivityTaskListCtrl(ZProcess* pProcess) :
    #ifdef _WIN32
        // 32 bit version
        PSS_ListCtrl(),
    #else
        // 16 bit version
        CListBox(),
    #endif
    m_pProcess(pProcess),
    m_HasBuiltColumns(FALSE)
{}
//---------------------------------------------------------------------------
PSS_ActivityTaskListCtrl::PSS_ActivityTaskListCtrl(const PSS_ActivityTaskListCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityTaskListCtrl::~PSS_ActivityTaskListCtrl()
{}
//---------------------------------------------------------------------------
const PSS_ActivityTaskListCtrl& PSS_ActivityTaskListCtrl::operator = (const PSS_ActivityTaskListCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_ActivityTaskListCtrl::Initialize(ZProcess* pProcess)
{
    m_pProcess = pProcess;
    return Refresh();
}
//---------------------------------------------------------------------------
CString PSS_ActivityTaskListCtrl::GetSelectedActivity()
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
int PSS_ActivityTaskListCtrl::GetSelectedActivities(CStringArray& activitiesArray)
{
    activitiesArray.RemoveAll();

    // 16 bit version
    #ifndef _WIN32
        const int count = GetSelCount();

        if (Count > 0)
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
void PSS_ActivityTaskListCtrl::SelectActivity(std::size_t activityIndex, BOOL shouldClearAllSelection)
{
    if (shouldClearAllSelection)
        ClearAllSelection();

    SetItemState(activityIndex, LVIS_SELECTED, LVIS_SELECTED);
}
//---------------------------------------------------------------------------
void PSS_ActivityTaskListCtrl::SelectActivity(const CString& activityName, BOOL shouldClearAllSelection)
{
    if (shouldClearAllSelection)
        ClearAllSelection();

    // find the activity
    for (register std::size_t index = 0; index < std::size_t(m_pProcess->GetActivityCount()); ++index)
        if (m_pProcess->GetActivityAt(index)->GetName() == activityName)
        {
            SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
            return;
        }
}
//---------------------------------------------------------------------------
void PSS_ActivityTaskListCtrl::ClearAllSelection()
{
    int item = -1;

    // as long as GetNextItem found an item...
    while (GetItemCount() > 0 && (item = GetNextItem(item, LVNI_ALL)) > -1)
        SetItemState(item, 0, LVIS_SELECTED);
}
//---------------------------------------------------------------------------
int PSS_ActivityTaskListCtrl::Refresh()
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

    PSS_ProcessIterator it(m_pProcess);

    for (PSS_BaseActivity* pRunner = it.StartIterator(it.GetFirstValidActivity()); pRunner; pRunner = it.GetNextValidActivity())
        if (m_pProcess->GetCurrentActivity() && m_pProcess->GetCurrentActivity()->GetName() == pRunner->GetName())
            InsertActivity(*pRunner, true);
        else
            InsertActivity(*pRunner, false);

    return m_pProcess->GetActivityCount();
}
//---------------------------------------------------------------------------
LRESULT PSS_ActivityTaskListCtrl::OnActivityListChange(WPARAM wParam, LPARAM lParam)
{
    Refresh();
    return 1;
}
//---------------------------------------------------------------------------
LRESULT PSS_ActivityTaskListCtrl::OnSelectActivityInTaskList(WPARAM wParam, LPARAM lParam)
{
    PSS_Activity* pActivity = (PSS_Activity*)lParam;
    SelectActivity(pActivity->GetName(), TRUE);
    return 1;
}
//---------------------------------------------------------------------------
void PSS_ActivityTaskListCtrl::InsertActivity(PSS_BaseActivity& activity, bool isCurrentActivity)
{
    if (!HasBuiltColumns())
        BuildColumns();

    // 16 bit version
    #ifndef _WIN32
        CString line  = activity.GetActivityName();
        line         += "  " + activity.GetStatusString();

        if (!activity.GetInitiator().IsEmpty())
        {
            // todo -cFeature -oJean: Translate texts below
            line += " initié par: " + activity.GetInitiator();

            char buffer[50];
            std::sprintf(buffer,
                         " le: %d.%d.%d",
                         activity.GetStartDate().GetDay(),
                         activity.GetStartDate().GetMonth(),
                         activity.GetStartDate().GetYear());
            line += buffer;
        }

        AddString(line);
    #endif

    // 32 bit version
    #ifdef _WIN32
        const int index = GetItemCount();
              int imageIndex = 11;

        if (isCurrentActivity || activity.GetActivityStatus() == PSS_BaseActivity::IE_AS_Started)
            imageIndex = 14;
        else
        if (activity.GetActivityStatus() == PSS_BaseActivity::IE_AS_Sent)
            imageIndex = 0;
        else
        if (activity.GetActivityStatus() == PSS_BaseActivity::IE_AS_SentForAcceptation)
            imageIndex = 8;
        else
        if (activity.GetActivityStatus() == PSS_BaseActivity::IE_AS_Completed)
            imageIndex = 15;
        else
        if (activity.GetActivityStatus() == PSS_BaseActivity::IE_AS_Rejected)
            imageIndex = 6;
        else
        if (activity.GetActivityStatus() == PSS_BaseActivity::IE_AS_Suspended)
            imageIndex = 12;
        else
        if (activity.GetActivityStatus() == PSS_BaseActivity::IE_AS_Aborted)
            imageIndex = 4;
        else
        if (activity.GetActivityStatus() == PSS_BaseActivity::IE_AS_NotStarted)
            imageIndex = 16;

        // add the action icon
        InsertItem(LVIF_IMAGE | LVIF_PARAM, index, NULL, 0, 0, imageIndex, (LPARAM)&activity);

        // add the activity name
        SetItem(index, 1, LVIF_TEXT, activity.GetName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the status
        SetItem(index, 2, LVIF_TEXT, activity.GetActivityStatusString(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the initiator
        SetItem(index, 3, LVIF_TEXT, activity.GetInitiator(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        CString text;

        // the creation date
        text = (activity.GetActivityStatus() == PSS_BaseActivity::IE_AS_NotStarted ? " - " : ((PSS_Date&)activity.GetStartDate()).GetStandardFormattedDate());
        SetItem(index, 4, LVIF_TEXT, text, 0, LVIF_TEXT, LVIF_TEXT, 0);

        // the due date
        text = (activity.GetActivityStatus() == PSS_BaseActivity::IE_AS_NotStarted ? " - " : ((PSS_Date&)activity.GetForecastedEndDate()).GetStandardFormattedDate());
        SetItem(index, 5, LVIF_TEXT, text, 0, LVIF_TEXT, LVIF_TEXT, 0);

        char buffer[50];

        // the remaining days
        if (activity.GetActivityStatus() == PSS_BaseActivity::IE_AS_NotStarted)
            ::strcpy_s(buffer, ::_tcslen(buffer), " - ");
        else
        {
            PSS_Date dateEnd = activity.GetForecastedEndDate();
            dateEnd.ClearTime();

            PSS_Date dateToday = PSS_Date::GetToday();
            dateToday.ClearTime();

            COleDateTimeSpan dateTimeSpan(dateEnd - dateToday);

            if (dateTimeSpan.GetStatus() == COleDateTimeSpan::valid)
                ::sprintf_s(buffer, ::_tcslen(buffer), "%d", int(dateTimeSpan.GetTotalDays()));
            else
                ::strcpy_s(buffer, ::_tcslen(buffer), "-");
        }

        SetItem(index, 6, LVIF_TEXT, buffer, 0, LVIF_TEXT, LVIF_TEXT, 0);
    #endif
}
//---------------------------------------------------------------------------
#ifdef _WIN32
    void PSS_ActivityTaskListCtrl::BuildColumns()
    {
        // load images
        LoadImageListMasked(IDB_MESSAGEITEM0_ACTEVT, IDB_MESSAGEITEM16_ACTEVT);
        PSS_ListCtrl::SetEnableOver(TRUE);
        PSS_ListCtrl::SetFullRowSelect(TRUE);
        PSS_ListCtrl::BuildColumns(7, g_TaskActivityColSize, g_TaskActivityColText);
        m_HasBuiltColumns = TRUE;
    }
#endif
//---------------------------------------------------------------------------
