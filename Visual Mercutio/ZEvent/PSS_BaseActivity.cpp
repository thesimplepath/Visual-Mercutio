/****************************************************************************
 * ==> PSS_BaseActivity ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic activity interface                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_BaseActivity.h"

// processsoft
#include "ZProcess.h"
#include "PSS_Activity.h"
#include "zBaseLib\PSS_BaseDocument.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_BaseActivity, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_BaseActivity
//---------------------------------------------------------------------------
PSS_BaseActivity::PSS_BaseActivity(const CString& name, const CString& description, IEStatus status) :
    CObject(),
    m_ActivityStatus(status),
    m_VisibilityType(IE_VT_Visible),
    m_RunMode(IE_RM_Sequence),
    m_pParent(NULL),
    m_pCurrentActivity(NULL),
    m_pPreviousActivity(NULL),
    m_pNextActivity(NULL),
    m_Name(name),
    m_Description(description),
    m_ActivityType(0),
    m_DurationDays(2),
    m_IsVisible(E_TS_Undefined),
    m_TimeType(IE_TT_TimeDays),
    m_DaysForBackupResources(1),
    m_RemindDays(1),
    m_UseBackupResources(FALSE),
    m_IsInBackupProcess(FALSE),
    m_IntranetActivity(TRUE)
{}
//---------------------------------------------------------------------------
PSS_BaseActivity::PSS_BaseActivity(const PSS_BaseActivity& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_BaseActivity::~PSS_BaseActivity()
{
    RemoveAllActivities();
}
//---------------------------------------------------------------------------
const PSS_BaseActivity& PSS_BaseActivity::operator = (const PSS_BaseActivity& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetParent() const
{
    return m_pParent;
}
//---------------------------------------------------------------------------
ZProcess* PSS_BaseActivity::GetParentProcess() const
{
    if (m_pParent)
    {
        ZProcess* pParentProcess = dynamic_cast<ZProcess*>(m_pParent);

        if (pParentProcess)
            return pParentProcess;

        return m_pParent->GetParentProcess();
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetFirstBaseActivity() const
{
    return GetActivityAt(0);
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetFirstValidActivity() const
{
    PSS_BaseActivity* pFirstActivity = GetActivityAt(0);

    if (!pFirstActivity)
        return NULL;

    if (pFirstActivity->IsKindOf(RUNTIME_CLASS(PSS_Activity)) || 
       (pFirstActivity->HasActivities() && pFirstActivity->GetRunMode() == IE_RM_Select))
        if (pFirstActivity->DoConsiderAsVisible() != E_TS_False)
            return pFirstActivity;

    return pFirstActivity->GetNextValidActivity();
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetFirstValidBaseActivity() const
{
    PSS_BaseActivity* pFirstActivity = GetActivityAt(0);

    if (!pFirstActivity)
        return NULL;

    if (pFirstActivity->DoConsiderAsVisible() != E_TS_False)
        return pFirstActivity;

    return pFirstActivity->GetNextValidActivity();
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetPreviousValidActivity() const
{
    if (GetPreviousBaseActivity())
    {
        // if the previous activity is a valid activity, return it
        if (GetPreviousBaseActivity()->IsKindOf(RUNTIME_CLASS(PSS_Activity)) ||
           (GetPreviousBaseActivity()->HasActivities() && GetPreviousBaseActivity()->GetRunMode() == IE_RM_Select))
            if (GetPreviousBaseActivity()->DoConsiderAsVisible() != E_TS_False)
                return GetPreviousBaseActivity();

        // continue to search in previous base activities
        return GetPreviousBaseActivity()->GetPreviousValidActivity();
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetPreviousValidBaseActivity() const
{
    if (GetPreviousBaseActivity())
    {
        // if the previous activity is a valid activity, return it
        if (GetPreviousBaseActivity()->DoConsiderAsVisible() != E_TS_False)
            return GetPreviousBaseActivity();

        // continue to search in previous base activities
        return GetPreviousBaseActivity()->GetPreviousValidBaseActivity();
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetNextValidActivity() const
{
    if (GetNextBaseActivity())
    {
        // if the next activity is a valid activity, return it
        if (GetNextBaseActivity()->IsKindOf(RUNTIME_CLASS(PSS_Activity)) ||
           (GetNextBaseActivity()->HasActivities() && GetNextBaseActivity()->GetRunMode() == IE_RM_Select))
            if (GetNextBaseActivity()->DoConsiderAsVisible() != E_TS_False)
                return GetNextBaseActivity();

        // continue to search in next base activities
        return GetNextBaseActivity()->GetNextValidActivity();
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetNextValidBaseActivity() const
{
    if (GetNextBaseActivity())
    {
        // if the next activity is a valid activity, return it
        if (GetNextBaseActivity()->DoConsiderAsVisible() != E_TS_False)
            return GetNextBaseActivity();

        // continue to search in next base activities
        return GetNextBaseActivity()->GetNextValidBaseActivity();
    }

    return NULL;
}
//---------------------------------------------------------------------------
ZProcess* PSS_BaseActivity::GetPreviousProcess() const
{
    PSS_BaseActivity* pBaseActivity = GetPreviousBaseActivity();

    if (pBaseActivity)
    {
        ZProcess* pProcess = dynamic_cast<ZProcess*>(pBaseActivity);

        // if the previous activity is a process, return it
        if (pProcess)
            return pProcess;

        // continue to search in previous activities
        return GetPreviousBaseActivity()->GetPreviousProcess();
    }

    return NULL;
}
//---------------------------------------------------------------------------
ZProcess* PSS_BaseActivity::GetNextProcess() const
{
    PSS_BaseActivity* pBaseActivity = GetNextBaseActivity();

    if (pBaseActivity)
    {
        ZProcess* pProcess = dynamic_cast<ZProcess*>(pBaseActivity);

        // if the next activity is a process, return it
        if (pProcess)
            return pProcess;

        // continue to search in next activities
        return GetNextBaseActivity()->GetNextProcess();
    }

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_BaseActivity::ActivityCreatePersonDelimStr(const PSS_UserManager& userManager,
                                                       const CString&         connectedUser,
                                                       const CString&         delimiter)
{
    return GetCurrentResources().CreatePersonDelimStr(GetMainProcess(), userManager, connectedUser, delimiter);
}
//---------------------------------------------------------------------------
PSS_MailUserList* PSS_BaseActivity::ActivityCreatePersonList(const PSS_UserManager& userManager, const CString& connectedUser)
{
    return GetCurrentResources().CreatePersonList(GetMainProcess(), userManager, connectedUser);
}
//---------------------------------------------------------------------------
PSS_MailUserList* PSS_BaseActivity::CreatePersonList(const PSS_BaseActivity& activity, const PSS_UserManager& userManager)
{
    return NULL;
}
//---------------------------------------------------------------------------
PSS_MailUserList* PSS_BaseActivity::CreatePersonList(int index, const PSS_UserManager& userManager)
{
    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_BaseActivity::CreatePersonDelimStr(const PSS_BaseActivity& activity,
                                               const PSS_UserManager&  userManager,
                                               const CString&          delimiter)
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_BaseActivity::CreatePersonDelimStr(int                    index,
                                               const PSS_UserManager& userManager,
                                               const CString&         delimiter)
{
    return _T("");
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::FillPersonArray(const PSS_BaseActivity& activity,
                                       const PSS_UserManager&  userManager,
                                       CStringArray&           userArray)
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::FillPersonArray(int                    index,
                                       const PSS_UserManager& userManager,
                                       CStringArray&          userArray)
{
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::ActivityFillPersonArray(const PSS_UserManager& userManager,
                                               CStringArray&          userArray,
                                               const CString&         connectedUser)
{
    return GetCurrentResources().FillPersonArray(GetMainProcess(), userManager, userArray, connectedUser);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::ActivityAddUsers(const CString& delimiterString)
{
    // set the user mode
    SetUserType(PSS_ActivityResources::IE_UT_Users);
    return GetCurrentResources().AddUsers(delimiterString);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::MainResourceActivityAddUsers(const CString& delimiterString)
{
    return m_MainResources.AddUsers(delimiterString);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::BackupResourceActivityAddUsers(const CString& delimiterString)
{
    return m_BackupResources.AddUsers(delimiterString);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::MainResourceActivityFillPersonArray(const PSS_UserManager& userManager,
                                                           CStringArray&          userArray,
                                                           const CString&         connectedUser)
{
    return m_MainResources.FillPersonArray(GetMainProcess(), userManager, userArray, connectedUser);
}
//---------------------------------------------------------------------------
PSS_MailUserList* PSS_BaseActivity::MainResourceActivityCreatePersonList(const PSS_UserManager& userManager,
                                                                         const CString&         connectedUser)
{
    return m_MainResources.CreatePersonList(GetMainProcess(), userManager, connectedUser);
}
//---------------------------------------------------------------------------
CString PSS_BaseActivity::MainResourceActivityCreatePersonDelimStr(const PSS_UserManager& userManager,
                                                                   const CString&         connectedUser,
                                                                   const CString&         delimiter)
{
    return m_MainResources.CreatePersonDelimStr(GetMainProcess(), userManager, connectedUser, delimiter);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::BackupResourceActivityFillPersonArray(const PSS_UserManager& userManager,
                                                             CStringArray&          userArray,
                                                             const CString&         connectedUser)
{
    return m_BackupResources.FillPersonArray(GetMainProcess(), userManager, userArray, connectedUser);
}
//---------------------------------------------------------------------------
PSS_MailUserList* PSS_BaseActivity::BackupResourceActivityCreatePersonList(const PSS_UserManager& userManager,
                                                                           const CString&         connectedUser)
{
    return m_BackupResources.CreatePersonList(GetMainProcess(), userManager, connectedUser);
}
//---------------------------------------------------------------------------
CString PSS_BaseActivity::BackupResourceActivityCreatePersonDelimStr(const PSS_UserManager& userManager,
                                                                     const CString&         connectedUser,
                                                                     const CString&         delimiter)
{
    return m_BackupResources.CreatePersonDelimStr(GetMainProcess(), userManager, connectedUser, delimiter);
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::CalculateForecastedStartDate()
{}
//---------------------------------------------------------------------------
void PSS_BaseActivity::CalculateForecastedEndDate()
{}
//---------------------------------------------------------------------------
WORD PSS_BaseActivity::GetDurationDays() const
{
    return m_DurationDays;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetDurationDays(WORD value)
{
    m_DurationDays = value;
}
//---------------------------------------------------------------------------
CString PSS_BaseActivity::GetStatusKeyString(PSS_BaseActivity* pActivity)
{
    if (ActivityIsAttribution() && GetActivityStatus() != IE_AS_SentForAcceptation)
        return g_ActivityStatusAttribution;

    switch (GetActivityStatus())
    {
        case IE_AS_Completed:          return g_ActivityStatusCompleted;
        case IE_AS_Rejected:           return g_ActivityStatusRejected;
        case IE_AS_Sent:               return g_ActivityStatusSent;
        case IE_AS_SentForAcceptation: return g_ActivityStatusRequestAcceptation;
        case IE_AS_NotStarted:         return g_ActivityStatusNotStarted;
        case IE_AS_Suspended:          return g_ActivityStatusProcessPaused;
        case IE_AS_Aborted:            return g_ActivityStatusProcessAborted;
        case IE_AS_Started:            return g_ActivityStatusStarted;
    }

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetStatusFromKeyString(const CString& key)
{
    if (key == g_ActivityStatusCompleted)
        SetActivityStatus(IE_AS_Completed);
    else
    if (key == g_ActivityStatusRejected)
        SetActivityStatus(IE_AS_Rejected);
    else
    if (key == g_ActivityStatusSent)
        SetActivityStatus(IE_AS_Sent);
    else
    if (key == g_ActivityStatusRequestAcceptation)
        SetActivityStatus(IE_AS_SentForAcceptation);
    else
    if (key == g_ActivityStatusNotStarted)
        SetActivityStatus(IE_AS_NotStarted);
    else
    if (key == g_ActivityStatusProcessPaused)
        SetActivityStatus(IE_AS_Suspended);
    else
    if (key == g_ActivityStatusProcessAborted)
        SetActivityStatus(IE_AS_Aborted);
    else
    if (key == g_ActivityStatusStarted)
        SetActivityStatus(IE_AS_Started);
}
//---------------------------------------------------------------------------
CString PSS_BaseActivity::GetStatusString(const CString& key)
{
    UINT id;

    if (key == g_ActivityStatusProcessCompleted)
        id = IDS_STATUSPROC_COMPLETED;
    else
    if (key == g_ActivityStatusAttribution)
        id = IDS_STATUSACT_ATTRIBUTION;
    else
    if (key == g_ActivityStatusCompleted)
        id = IDS_STATUSACT_COMPLETED;
    else
    if (key == g_ActivityStatusRejected)
        id = IDS_STATUSACT_REJECTED;
    else
    if (key == g_ActivityStatusSent)
        id = IDS_STATUSACT_SENT;
    else
    if (key == g_ActivityStatusRequestAcceptation)
        id = IDS_STATUSACT_SENTFORACPT;
    else
    if (key == g_ActivityStatusNotStarted)
        id = IDS_STATUSACT_NOTSTARTED;
    else
    if (key == g_ActivityStatusProcessPaused)
        id = IDS_STATUSPROC_SUSPENDED;
    else
    if (key == g_ActivityStatusProcessAborted)
        id = IDS_STATUSPROC_ABORTED;
    else
        id = IDS_STATUSACT_UNKNOWN;

    CString text;
    text.LoadString(id);

    return text;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::FillActivityInformationWhenStart()
{
    SetInitiator(GetConnectedUser());
    SetStartDate(PSS_Date::GetToday());

    // set the forecasted start date to be able to calculate the forecasted end date
    SetForecastedStartDate(PSS_Date::GetToday());

    // calculate the forecasted end date
    CalculateForecastedEndDate();
    SetActivityStatus(IE_AS_Started);
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::FillActivityInformationWhenEnd()
{
    SetEndDate(PSS_Date::GetToday());
    SetActivityStatus(IE_AS_Completed);
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::FillActivityInformationWhenRefused()
{
    SetLastUpdateDate(PSS_Date::GetToday());
    SetActivityStatus(IE_AS_Rejected);
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::FillActivityInformationWhenSentForAccept()
{
    if (GetActivityStatus() == IE_AS_NotStarted)
    {
        SetForecastedStartDate(PSS_Date::GetToday());

        // calculate the forecasted end date
        CalculateForecastedEndDate();
    }

    SetLastUpdateDate(PSS_Date::GetToday());
    SetActivityStatus(IE_AS_SentForAcceptation);
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::FillActivityInformationWhenSent()
{
    if (GetActivityStatus() == IE_AS_NotStarted)
    {
        SetForecastedStartDate(PSS_Date::GetToday());

        // calculate the forecasted end date
        CalculateForecastedEndDate();
    }

    SetLastUpdateDate(PSS_Date::GetToday());
    SetActivityStatus(IE_AS_Sent);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::ActivityIsShared() const
{
    // if no activites or in selection mode, check the number of resources
    if (!HasActivities() || GetRunMode() == IE_RM_Select)
        return (GetCurrentResources().GetUserCount() > 1);

    // if has activities, check the current one
    if (!GetCurrentActivity())
        return FALSE;

    return GetCurrentActivity()->ActivityIsShared();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::MustSwitchToBackupResourceActivity() const
{
    // if no activites or in selection mode, check the number of resources
    if (!HasActivities() || GetRunMode() == IE_RM_Select)
    {
        if (GetUseBackupResources() && GetForecastedEndDate() > 0)
            return (COleDateTime::GetCurrentTime() >= (GetForecastedEndDate() + COleDateTimeSpan(GetDaysForBackupResources())));

        return FALSE;
    }

    // check the current activity
    if (!GetCurrentActivity())
        return FALSE;

    return GetCurrentActivity()->MustSwitchToBackupResourceActivity();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::MustRemindEndActivity() const
{
    // if no activites or in selection mode, check the number of resources
    if (!HasActivities() || GetRunMode() == IE_RM_Select)
    {
        if (GetForecastedEndDate() > 0)
            return (COleDateTime::GetCurrentTime() >= (GetForecastedEndDate() - COleDateTimeSpan(GetRemindDays())));

        return FALSE;
    }

    // check the current activity
    if (!GetCurrentActivity())
        return FALSE;

    return GetCurrentActivity()->MustRemindEndActivity();
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetParent(PSS_BaseActivity* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
ZProcess* PSS_BaseActivity::GetMainProcess()
{
    if (GetParent())
        return GetParent()->GetMainProcess();

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_BaseActivity::GetActivityStatusString() const
{
    CString status;

    switch (GetActivityStatus())
    {
        case IE_AS_Started:            status.LoadString(IDS_ACTIVITY_STARTED);        break;
        case IE_AS_Completed:          status.LoadString(IDS_ACTIVITY_COMPLETED);      break;
        case IE_AS_Rejected:           status.LoadString(IDS_ACTIVITY_REJECTED);       break;
        case IE_AS_Sent:               status.LoadString(IDS_ACTIVITY_NEXTPERSON);     break;
        case IE_AS_SentForAcceptation: status.LoadString(IDS_ACTIVITY_FORACCEPTATION); break;
        case IE_AS_NotStarted:         status.LoadString(IDS_ACTIVITY_NOTSTARTED);     break;
        case IE_AS_Suspended:          status.LoadString(IDS_PROCESS_SUSPENDED);       break;
        case IE_AS_Aborted:            status.LoadString(IDS_PROCESS_ABORTED);         break;
        default:                       status.LoadString(IDS_ACTIVITY_UNKNOWNSTATE);
    }

    return status;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetDefaultProperty()
{
    m_VisibilityType         = IE_VT_Visible;
    m_DurationDays           = 2;
    m_IsVisible              = E_TS_True;
    m_TimeType               = IE_TT_TimeDays;
    m_DaysForBackupResources = 2;
    m_RemindDays             = 1;
    m_UseBackupResources     = FALSE;
    m_IsInBackupProcess      = FALSE;
    m_IntranetActivity       = TRUE;

    m_Initiator.Empty();

    RemoveAllUsers();
    RemoveAllBackupUsers();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::AddActivityToSelection(const CString& activityName)
{
    const int selectedArraySize = GetSelectedActivityArray().GetSize();

    // check if the array doesn't contain the value
    for (int i = 0; i < selectedArraySize; ++i)
        if (activityName == GetSelectedActivityArray().GetAt(i))
            return TRUE;

    return GetSelectedActivityArray().Add(activityName) > -1;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetChildVisibility(const EThreeState value)
{
    const std::size_t activityCount = GetActivityCount();

    // set the value for all activities and sub-process
    for (std::size_t i = 0; i < activityCount; ++i)
        GetActivityAt(i)->SetVisibility(value);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::MoveActivityUp(const CString& activityName)
{
    if (!CanActivityMoveUp(activityName))
        return FALSE;

    PSS_BaseActivity* pActivity = FindBaseActivity(activityName);

    if (pActivity)
    {
        PSS_BaseActivity* pParent = pActivity->GetParent();

        if (pParent)
        {
            const std::size_t activityCount = pParent->GetActivityCount();

            for (std::size_t i = 0; i < activityCount; ++i)
            {
                // activity found?
                if (pParent->GetActivityAt(i) == pActivity)
                {
                    // remove the activity from the array
                    if (!pParent->RemoveActivityAt(i))
                        return FALSE;

                    // insert it after
                    if (!pParent->InsertActivityAt(pActivity, i - 1))
                        return FALSE;

                    // recalculate all links
                    RecalculateAllLinks();
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::MoveActivityDown(const CString& activityName)
{
    if (!CanActivityMoveDown(activityName))
        return FALSE;

    PSS_BaseActivity* pActivity = FindBaseActivity(activityName);

    if (pActivity)
    {
        PSS_BaseActivity* pParent = pActivity->GetParent();

        if (pParent)
        {
            const std::size_t activityCount = pParent->GetActivityCount();

            for (std::size_t i = 0; i < activityCount; ++i)
            {
                // activity found?
                if (pParent->GetActivityAt(i) == pActivity)
                {
                    // remove the activity from the array
                    if (!pParent->RemoveActivityAt(i))
                        return FALSE;

                    // insert it after
                    if (!pParent->InsertActivityAt(pActivity, i + 1))
                        return FALSE;

                    // recalculate all links
                    RecalculateAllLinks();
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::CanActivityMoveUp(const CString& activityName)
{
    PSS_BaseActivity* pActivity      = FindBaseActivity(activityName);
    PSS_BaseActivity* pFirstActivity = GetActivityAt(0);

    if (pActivity)
        // if owns activities, can only move at the same level
        if (pActivity->HasActivities())
        {
            PSS_BaseActivity* pParent = pActivity->GetParent();

            if (pParent)
            {
                const std::size_t activityCount = pParent->GetActivityCount();

                // iterate through parent activities. When activity found, return true if there is one more above
                for (std::size_t i = 0; i < activityCount; ++i)
                    if (pParent->GetActivityAt(i) == pActivity)
                        return i;
            }
        }
        else
            // return true if not the first activity and not the process
            return (pFirstActivity->GetName() != activityName && GetName() != activityName);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::CanActivityMoveDown(const CString& activityName)
{
    PSS_BaseActivity* pActivity = FindBaseActivity(activityName);

    if (pActivity)
    {
        // if owns activities, can only move at the same level
        if (pActivity->HasActivities())
        {
            PSS_BaseActivity* pParent = pActivity->GetParent();

            if (pParent)
            {
                const std::size_t activityCount = pParent->GetActivityCount();

                // iterate through parent activities. When activity found, return true if there is one more below
                for (std::size_t i = 0; i < activityCount; ++i)
                    if (pParent->GetActivityAt(i) == pActivity)
                        return (i < pParent->GetActivityCount() - 1);
            }
        }
        else
        if (pActivity->GetNextBaseActivity())
            return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetCurrentActivity(const CString& activityName)
{
    m_pCurrentActivity = FindActivity(activityName);
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetCurrentActivity(PSS_BaseActivity* pActivity)
{
    m_pCurrentActivity = pActivity;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::SetCurrentActivityToPrevious()
{
    if (m_pCurrentActivity)
        m_pCurrentActivity = m_pCurrentActivity->GetPreviousValidActivity();
    else
        m_pCurrentActivity = GetPreviousValidActivity();

    return m_pCurrentActivity;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::SetCurrentActivityToNext()
{
    if (m_pCurrentActivity)
        m_pCurrentActivity = m_pCurrentActivity->GetNextValidActivity();
    else
        m_pCurrentActivity = GetNextValidActivity();

    return m_pCurrentActivity;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetPreviousValidActivityFromCurrent() const
{
    if (m_pCurrentActivity)
        return m_pCurrentActivity->GetPreviousValidActivity();

    return NULL;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetNextValidActivityFromCurrent() const
{
    if (m_pCurrentActivity)
        return m_pCurrentActivity->GetNextValidActivity();

    return NULL;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetPreviousBaseActivityFromCurrent() const
{
    if (m_pCurrentActivity)
        return m_pCurrentActivity->GetPreviousBaseActivity();

    return NULL;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetNextBaseActivityFromCurrent() const
{
    if (m_pCurrentActivity)
        return m_pCurrentActivity->GetNextBaseActivity();

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::RemoveActivityAt(std::size_t index)
{
    if (index < GetActivityCount())
    {
        m_ActivityArray.RemoveAt(index);
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::InsertActivityAt(PSS_BaseActivity* pActivity, std::size_t index)
{
    if (index >= GetActivityCount())
        m_ActivityArray.Add(pActivity);
    else
        m_ActivityArray.InsertAt(index, pActivity);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::AddActivity(PSS_BaseActivity* pActivity)
{
    if (m_ActivityArray.Add(pActivity) < 0)
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::AddActivityAfter(PSS_BaseActivity* pActivity, const CString& activityName)
{
    const std::size_t activityCount = GetActivityCount();

    for (std::size_t i = 0; i < activityCount; ++i)
        if (GetActivityAt(i)->GetName() == activityName)
        {
            m_ActivityArray.InsertAt(i + 1, pActivity);
            return TRUE;
        }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::DeleteActivity(PSS_BaseActivity* pActivity)
{
    const std::size_t activityCount = GetActivityCount();

    for (std::size_t i = 0; i < activityCount; ++i)
    {
        if (GetActivityAt(i) == pActivity)
        {
            delete GetActivityAt(i);
            m_ActivityArray.RemoveAt(i);

            return TRUE;
        }

        if (GetActivityAt(i)->HasActivities())
            if (GetActivityAt(i)->DeleteActivity(pActivity) == TRUE)
                return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::DeleteActivity(const CString& activityName)
{
    PSS_BaseActivity* pActivity = FindActivity(activityName);

    if (pActivity)
        return DeleteActivity(pActivity);

    return FALSE;
}
//---------------------------------------------------------------------------
PSS_Activity* PSS_BaseActivity::FindActivity(const CString& activityName) const
{
    const std::size_t activityCount = GetActivityCount();

    for (std::size_t i = 0; i < activityCount; ++i)
    {
        PSS_BaseActivity* pActivity = GetActivityAt(i);

        if (!pActivity)
            continue;

        if (pActivity->HasActivities())
        {
            PSS_Activity* pReturnedActivity = pActivity->FindActivity(activityName);

            if (pReturnedActivity)
                return pReturnedActivity;
        }
        else
        if (pActivity->IsKindOf(RUNTIME_CLASS(PSS_Activity)) && pActivity->GetName() == activityName)
            return static_cast<PSS_Activity*>(pActivity);
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::FindBaseActivity(const CString& activityName) const
{
    const std::size_t activityCount = GetActivityCount();

    for (std::size_t i = 0; i < activityCount; ++i)
    {
        PSS_BaseActivity* pActivity = GetActivityAt(i);

        if (!pActivity)
            continue;

        if (pActivity->GetName() == activityName)
            return pActivity;

        if (pActivity->HasActivities())
        {
            PSS_BaseActivity* pReturnedActivity = pActivity->FindBaseActivity(activityName);

            if (pReturnedActivity)
                return pReturnedActivity;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::AddProcess(ZProcess* pProcess)
{
    return AddActivity(pProcess);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::AddProcessAfter(ZProcess* pProcess, const CString& activityName)
{
    return AddActivityAfter(pProcess, activityName);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::DeleteProcess(ZProcess* pProcess)
{
    return DeleteActivity(pProcess);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::DeleteProcess(const CString& processName)
{
    return DeleteActivity(processName);
}
//---------------------------------------------------------------------------
ZProcess* PSS_BaseActivity::FindProcess(const CString& processName) const
{
    ZProcess* pProcess = dynamic_cast<ZProcess*>(FindActivity(processName));

    if (pProcess)
        return pProcess;

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::RemoveAllActivities(bool doDelete)
{
    const std::size_t activityCount = GetActivityCount();

    for (std::size_t i = 0; i < activityCount; ++i)
        if (GetActivityAt(i))
        {
            if (GetActivityAt(i)->HasActivities())
                GetActivityAt(i)->RemoveAllActivities(doDelete);

            if (doDelete)
                delete GetActivityAt(i);
        }

    m_ActivityArray.RemoveAll();
}
//---------------------------------------------------------------------------
int PSS_BaseActivity::GetActivityIndex(const CString& activityName) const
{
    const std::size_t activityCount = GetActivityCount();

    for (std::size_t i = 0; i < activityCount; ++i)
        if (GetActivityAt(i)->GetName() == activityName)
            return int(i);

    return -1;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::SetActivityAt(int index, PSS_BaseActivity* pActivity)
{
    if (index < int(GetActivityCount()))
    {
        m_ActivityArray.SetAt(index, pActivity);
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::RecalculateAllLinks()
{
    RecalculateProcessAllLinks(this);
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::Serialize(CArchive& ar)
{
    PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

    CString currentActivityName;
    currentActivityName.Empty();

    if (ar.IsStoring())
    {
        ar << m_Name;
        ar << m_Description;
        ar << m_Comment;
        ar << m_Initiator;
        ar << WORD(m_ActivityStatus);
        ar << m_DurationDays;
        ar << m_ForecastedStartDate;
        ar << m_ForecastedEndDate;
        ar << m_StartDate;
        ar << m_EndDate;
        ar << m_LastUpdateDate;
        ar << WORD(m_VisibilityType);
        ar << WORD(m_IsVisible);
        ar << WORD(m_TimeType);
        ar << WORD(m_IntranetActivity);
        ar << WORD(m_DaysForBackupResources);
        ar << WORD(m_UseBackupResources);
        ar << WORD(m_IsInBackupProcess);
        ar << WORD(m_RemindDays);
        ar << m_MainResources;
        ar << m_BackupResources;

        // version 17
        if (m_pCurrentActivity)
            ar << m_pCurrentActivity->GetName();
        else
            // serialize empty
            ar << currentActivityName;

        ar << WORD(m_RunMode);
        ar << m_ActivityType;
    }
    else
    {
        ar >> m_Name;
        ar >> m_Description;
        ar >> m_Comment;
        ar >> m_Initiator;

        WORD wValue;
        ar >> wValue;
        m_ActivityStatus = IEStatus(wValue);

        ar >> m_DurationDays;
        ar >> m_ForecastedStartDate;
        ar >> m_ForecastedEndDate;
        ar >> m_StartDate;
        ar >> m_EndDate;
        ar >> m_LastUpdateDate;

        ar >> wValue;
        m_VisibilityType = IEVisibilityType(wValue);

        ar >> wValue;
        m_IsVisible = EThreeState(wValue);

        ar >> wValue;
        m_TimeType = IETimeoutType(wValue);

        ar >> wValue;
        m_IntranetActivity = BOOL(wValue);

        ar >> wValue;
        m_DaysForBackupResources = std::size_t(wValue);

        ar >> wValue;
        m_UseBackupResources = BOOL(wValue);

        ar >> wValue;
        m_IsInBackupProcess = BOOL(wValue);

        ar >> wValue;
        m_RemindDays = std::size_t(wValue);

        ar >> m_MainResources;
        ar >> m_BackupResources;

        // version 17
        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 17)
        {
            ar >> currentActivityName;

            ar >> wValue;
            m_RunMode = IERunMode(wValue);

            ar >> m_ActivityType;
        }
    }

    if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 17)
    {
        m_ActivityArray.Serialize(ar);

        m_SelectedActivityArray.Serialize(ar);

        // once the activity array is serialized, and in reading mode, assign the current activity
        if (!ar.IsStoring() && !currentActivityName.IsEmpty())
            m_pCurrentActivity = FindBaseActivity(currentActivityName);
    }
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::RecalculateProcessAllLinks(PSS_BaseActivity* pParent, PSS_BaseActivity* pNextOfParent)
{
    if (GetActivityCount() > 0)
    {
        // initialize the previous activity of the first one to the parent
        PSS_BaseActivity* pPrevious       = pParent;
        PSS_BaseActivity* pReturnActivity = NULL;
        PSS_BaseActivity* pLastOfChild    = NULL;

        if (GetRunMode() == IE_RM_Sequence || !IsActivitySelectionDone())
        {
            // assigns the next pointer of the process to the first activity
            AssignNextActivity(GetActivityAt(0));

            const std::size_t activityCount = GetActivityCount();

            // iterate through the process activities
            for (std::size_t i = 0; i < activityCount; ++i)
            {
                // assign the parent pointer to the activity
                GetActivityAt(i)->SetParent(this);

                // assigns previous activity
                GetActivityAt(i)->AssignPreviousActivity(pPrevious);

                // if the activity contains children activities, process all of them
                if (GetActivityAt(i)->HasActivities())
                {
                    // call recursively with the parent and the next activity, and save the previous activity
                    pPrevious = GetActivityAt(i)->RecalculateProcessAllLinks(GetActivityAt(i), GetActivityAt(i + 1));

                    // assign the next of the returned activity
                    if (pPrevious)
                        pPrevious->AssignNextActivity(GetActivityAt(i + 1));
                    else
                        // if no activity, set previous as normal previous. Save the previous activity
                        pPrevious = GetActivityAt(i);

                    // if no next activity, therefore, the last activity is the returned activity
                    if (!GetActivityAt(i + 1))
                        pReturnActivity = pPrevious;
                }
                else
                {
                    // assign next, if no, NULL will be assigned
                    GetActivityAt(i)->AssignNextActivity(GetActivityAt(i + 1));

                    // save the previous activity pointer
                    pPrevious = GetActivityAt(i);
                }
            }

            PSS_BaseActivity* pProcess = GetActivityAt(GetActivityCount() - 1);

            // the next activity of the last one points to the next activity of the parent, only if not a process
            // and has no activities
            if (!pProcess->IsKindOf(RUNTIME_CLASS(ZProcess)) && !pProcess->HasActivities())
                GetActivityAt(GetActivityCount() - 1)->AssignNextActivity(pNextOfParent);

            return (pReturnActivity ? pReturnActivity : pProcess);
        }
        else
        {
            // take the selected activity and link it. In the first version, only the first selected activity was selected
            PSS_BaseActivity* pSelectedActivity = FindBaseActivity(GetSelectedActivityArray().GetAt(0));

            // assign the next process activity to the selected activity
            AssignNextActivity(pSelectedActivity);

            // assign the parent to the activity
            pSelectedActivity->SetParent(this);

            // assign previous activiy
            pSelectedActivity->AssignPreviousActivity(pPrevious);

            // if the activity owns activities, process all activities
            if (pSelectedActivity->HasActivities())
            {
                // call recursively with the parent and the next activity and save the previous activity
                pPrevious = pSelectedActivity->RecalculateProcessAllLinks(pSelectedActivity, NULL);

                // if no activity, set previous as normal previous
                if (!pPrevious)
                    // save the previous activity pointer
                    pPrevious = pSelectedActivity;
            }
            else
            {
                // assign next, if no, it will be assigned to NULL
                pSelectedActivity->AssignNextActivity(NULL);

                // save the previous activity
                pPrevious = pSelectedActivity;
            }

            // the next activity of the last one points to the next activity of the parent only if not a process
            if (!pPrevious->IsKindOf(RUNTIME_CLASS(ZProcess)) && !pPrevious->HasActivities())
                pPrevious->AssignNextActivity(pNextOfParent);

            return pPrevious;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
