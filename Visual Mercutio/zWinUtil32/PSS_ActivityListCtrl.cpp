/****************************************************************************
 * ==> PSS_ActivityListCtrl ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity list control                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ActivityListCtrl.h"

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
    static int g_ActivityColText[] =
    {
        IDS_NOCOLUMNHEADER,
        IDS_COLUMN1_ACTIVITY,
        IDS_COLUMNDESC_ACTIVITY
    };

    static int g_ActivityColSize[] =
    {
        20,
        80,
        265
    };
#endif
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
#ifdef _WIN32
    BEGIN_MESSAGE_MAP(PSS_ActivityListCtrl, PSS_ListCtrl)
#else
    BEGIN_MESSAGE_MAP(PSS_ActivityListCtrl, CListBox)
#endif
    //{{AFX_MSG_MAP(PSS_ActivityListCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ActivityListCtrl
//---------------------------------------------------------------------------
PSS_ActivityListCtrl::PSS_ActivityListCtrl(ZProcess*      pProcess,
                                           int            activityType,
                                           const CString& excludedActivity,
                                           BOOL           stopOnFound,
                                           BOOL           attributedActivityOnly) :
    #ifdef _WIN32
        // 32 bit version
        PSS_ListCtrl(),
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
PSS_ActivityListCtrl::PSS_ActivityListCtrl(const PSS_ActivityListCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ActivityListCtrl::~PSS_ActivityListCtrl()
{}
//---------------------------------------------------------------------------
const PSS_ActivityListCtrl& PSS_ActivityListCtrl::operator = (const PSS_ActivityListCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_ActivityListCtrl::Initialize(ZProcess*     pProcess,
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
    BuildColumns(3, g_ActivityColSize, g_ActivityColText );

    // load images
    LoadImageListMasked(IDB_PROCESSITEM, IDB_PROCESSCHOOSEITEM);
    PSS_ListCtrl::SetEnableOver(TRUE);
    PSS_ListCtrl::SetFullRowSelect(TRUE);

    return Refresh();
}
//---------------------------------------------------------------------------
CString PSS_ActivityListCtrl::GetSelectedActivity()
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
            return GetItemText(GetNextSelectedItem(pPos), 1);
    #endif

    return "";
}
//---------------------------------------------------------------------------
int PSS_ActivityListCtrl::GetSelectedActivities(CStringArray& activitiesArray)
{
    activitiesArray.RemoveAll();

    // 16 bit version
    #ifndef _WIN32
        const int count = GetSelCount();

        if (count > 0)
        {
            // get the list of selection IDs
            int* pItems = new int[count];
            GetSelItems(count, pItems);

            for (int i = 0; i < count; ++i)
            {
                CString text;
                GetLBText(pItems[i], text);
                activitiesArray.Add(text);
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
int PSS_ActivityListCtrl::Refresh ()
{
    #ifdef _WIN32
        DeleteAllItems();
    #endif

    CStringArray activityArray;

    #ifndef _WIN32
        ResetContent();
    #endif

    const std::size_t count = m_pProcess->GetActivityCount();

    for (std::size_t index = 0; index < count; ++index)
    {
        ZBaseActivity* pActivity = m_pProcess->GetActivityAt(index);

        if (!pActivity)
            continue;

        // 16 bit version
        #ifndef _WIN32
            AddString(pActivity->GetName());
        #endif

        // 32 bit version
        #ifdef _WIN32
            int imageIndex;

            if (pActivity->IsKindOf(RUNTIME_CLASS(ZActivity)))
                imageIndex = 1;
            else
            if (pActivity->IsKindOf(RUNTIME_CLASS(ZProcess)))
                imageIndex = (((ZProcess*)pActivity)->GetRunMode() == SequenceRun) ? 0 : 2;

            // add the action icon
            InsertItem(LVIF_IMAGE | LVIF_PARAM, index, NULL, 0, 0, imageIndex, 0);

            SetItem(index, 1, LVIF_TEXT, pActivity->GetName(),        0, LVIF_TEXT, LVIF_TEXT, 0);
            SetItem(index, 2, LVIF_TEXT, pActivity->GetDescription(), 0, LVIF_TEXT, LVIF_TEXT, 0);
        #endif
    }

    return count;
}
//---------------------------------------------------------------------------
