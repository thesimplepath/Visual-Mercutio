/****************************************************************************
 * ==> PSS_Process ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a process                                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "ZProcess.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "zBaseLib\PSS_BaseDocument.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_MessageDlg.h"
#include "PSS_ActivityEvent.h"

// resources
#include "zRes32\ZRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_Process, PSS_BaseActivity, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_Process
//---------------------------------------------------------------------------
PSS_Process::PSS_Process(IEStatus processStatus, const CString& ConnectedUser) :
    PSS_BaseActivity(),
    m_pAttributedActivitiesArray(NULL),
    m_ProcessStatus(processStatus),
    m_UseMail(FALSE),
    m_AutoStart(FALSE),
    m_DoNotUseInternalMessage(FALSE)
{
    SetDurationDays(0);
    SetConnectedUser(ConnectedUser);
}
//---------------------------------------------------------------------------
PSS_Process::PSS_Process(const PSS_Process& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Process::~PSS_Process()
{
    if (m_pAttributedActivitiesArray)
        delete m_pAttributedActivitiesArray;
}
//---------------------------------------------------------------------------
const PSS_Process& PSS_Process::operator = (const PSS_Process& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_Process::FillAuthUser(PSS_BaseActivity& activity, const PSS_UserManager& userManager)
{
    // remove all users
    m_AuthorizedUser.RemoveAll();

    // fill the authorized user list
    activity.ActivityFillPersonArray(userManager, m_AuthorizedUser, GetConnectedUser());
}
//---------------------------------------------------------------------------
void PSS_Process::FillAuthUser(const PSS_ActivityResources& resources)
{
    // remove all users
    m_AuthorizedUser.RemoveAll();

    const std::size_t userCount = resources.GetUserCount();

    // fill the authorized user list with the backup resources
    for (std::size_t i = 0; i < userCount; ++i)
        m_AuthorizedUser.Add(resources.GetUserAt(i));
}
//---------------------------------------------------------------------------
void PSS_Process::FillAuthUser(const CString& userDelimiter)
{
    // remove all users
    m_AuthorizedUser.RemoveAll();

    // parse the user delimiter string
    PSS_Tokenizer tokenizer(';');
    CString       token = tokenizer.GetFirstToken(userDelimiter);

    while (!token.IsEmpty())
    {
        m_AuthorizedUser.Add(token);
        token = tokenizer.GetNextToken();
    }
}
//---------------------------------------------------------------------------
std::size_t PSS_Process::GetActivityNameArray(CStringArray&  activityArray,
                                              WORD           activityType,
                                              const CString& excludedActivity,
                                              BOOL           stopWhenFound,
                                              BOOL           attributedActivityOnly)
{
    activityArray.RemoveAll();

    const std::size_t activityCount = GetActivityCount();
          std::size_t count         = 0;

    for (std::size_t i = 0; i < activityCount; ++i)
    {
        PSS_Activity* pActivity = dynamic_cast<PSS_Activity*>(GetActivityAt(i));

        if (pActivity)
            if (excludedActivity != pActivity->GetName())
            {
                if (!activityType || activityType & pActivity->GetActivityType())
                    if (attributedActivityOnly || pActivity->IsAttributedActivity())
                    {
                        activityArray.Add(pActivity->GetName());
                        ++count;
                    }
            }
            else
            if (stopWhenFound)
                return count;
    }

    return count;
}
//---------------------------------------------------------------------------
BOOL PSS_Process::TemplateExist(const CString& templateName)
{
    const std::size_t activityCount = GetActivityCount();

    for (std::size_t i = 0; i < activityCount; ++i)
    {
        PSS_Activity* pActivity = dynamic_cast<PSS_Activity*>(GetActivityAt(i));

        if (pActivity && pActivity->TemplateExist(templateName))
            return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
PSS_MailUserList* PSS_Process::CreatePersonList(PSS_BaseActivity& activity, const PSS_UserManager& userManager)
{
    return activity.ActivityCreatePersonList(userManager, GetConnectedUser());
}
//---------------------------------------------------------------------------
PSS_MailUserList* PSS_Process::CreatePersonList(int index, const PSS_UserManager& userManager)
{
    PSS_BaseActivity* pActivity = GetActivityAt(index);

    if (pActivity)
        return CreatePersonList(*pActivity, userManager);

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_Process::FillPersonArray(PSS_BaseActivity& activity, const PSS_UserManager& userManager, CStringArray& userArray)
{
    return activity.ActivityFillPersonArray(userManager, userArray, m_ConnectedUser);
}
//---------------------------------------------------------------------------
BOOL PSS_Process::FillPersonArray(int index, const PSS_UserManager& userManager, CStringArray& userArray)
{
    PSS_BaseActivity* pActivity = GetActivityAt(index);

    if (pActivity)
        return FillPersonArray(*pActivity, userManager, userArray);

    return FALSE;
}
//---------------------------------------------------------------------------
CString PSS_Process::CreatePersonDelimStr(PSS_BaseActivity& activity, const PSS_UserManager& userManager, const CString& delimiter)
{
    return activity.ActivityCreatePersonDelimStr(userManager, m_ConnectedUser, delimiter);
}
//---------------------------------------------------------------------------
CString PSS_Process::CreatePersonDelimStr(int index, const PSS_UserManager& userManager, const CString& delimiter)
{
    PSS_Activity* pActivity = dynamic_cast<PSS_Activity*>(GetActivityAt(index));

    if (pActivity)
        return CreatePersonDelimStr(*pActivity, userManager, delimiter);

    return "";
}
//---------------------------------------------------------------------------
CObArray* PSS_Process::GetAttributedActivities(const CString& name)
{
    // if old array, delete it
    if (m_pAttributedActivitiesArray)
        delete m_pAttributedActivitiesArray;

    m_pAttributedActivitiesArray = NULL;

    // create a new one
    m_pAttributedActivitiesArray = new CObArray;

    const std::size_t activityCount = GetActivityCount();

    for (std::size_t i = 0; i < activityCount; ++i)
    {
        PSS_Activity* pActivity = dynamic_cast<PSS_Activity*>(GetActivityAt(i));

        if (pActivity && pActivity->GetAttributedByActivity() == name)
            m_pAttributedActivitiesArray->Add(GetActivityAt(i));
    }

    // if nothing found, delete it
    if (m_pAttributedActivitiesArray->GetSize() <= 0)
    {
        if (m_pAttributedActivitiesArray)
            delete m_pAttributedActivitiesArray;

        m_pAttributedActivitiesArray = NULL;
    }

    return m_pAttributedActivitiesArray;
}
//---------------------------------------------------------------------------
void PSS_Process::CalculateForecastedStartDate()
{}
//---------------------------------------------------------------------------
void PSS_Process::CalculateForecastedEndDate()
{
    // set the forecasted end date by adding the duration to the start date
    SetForecastedEndDate(GetStartDate() + COleDateTimeSpan(GetDurationDays()));
}
//---------------------------------------------------------------------------
WORD PSS_Process::GetDurationDays()
{
    int                 duration = 0;
    PSS_ProcessIterator iterator(this);

    // add all days
    for (PSS_BaseActivity* pRunner = iterator.StartIterator(iterator.GetFirstValidActivity()); pRunner; pRunner = iterator.GetNextValidActivity())
        duration += pRunner->GetDurationDays();

    return duration;
}
//---------------------------------------------------------------------------
CString PSS_Process::GetStatusKeyString(PSS_BaseActivity* pActivity)
{
    // if in parallel mode, check the number of resources
    if (GetRunMode() == PSS_BaseActivity::IE_RM_Select)
        return PSS_BaseActivity::GetStatusKeyString(pActivity);

    // check the activity
    if (pActivity)
    {
        switch (GetProcessStatus())
        {
            case IE_PS_Completed:  return g_ActivityStatusProcessCompleted;
            case IE_PS_Aborted:    return g_ActivityStatusProcessAborted;
            case IE_PS_Suspend:    return g_ActivityStatusProcessPaused;
            case IE_PS_NotStarted: return g_ActivityStatusProcessNotStarted;
        }

        return pActivity->GetStatusKeyString(pActivity);
    }

    // check the current activity
    switch (GetProcessStatus())
    {
        case IE_PS_Completed:  return g_ActivityStatusProcessCompleted;
        case IE_PS_Aborted:    return g_ActivityStatusProcessAborted;
        case IE_PS_Suspend:    return g_ActivityStatusProcessPaused;
        case IE_PS_InProcess:  return g_ActivityStatusProcessInProcess;
        case IE_PS_Started:    return g_ActivityStatusProcessStarted;
        case IE_PS_NotStarted: return g_ActivityStatusProcessNotStarted;
    }

    pActivity = GetCurrentActivity();

    // nothing to do
    if (!pActivity)
        return "";

    return pActivity->GetStatusKeyString(pActivity);
}
//---------------------------------------------------------------------------
void PSS_Process::SetStatusFromKeyString(const CString& key)
{
    if (key == g_ActivityStatusProcessCompleted)
        SetProcessStatus(IE_PS_Completed);
    else
    if (key == g_ActivityStatusProcessAborted)
        SetProcessStatus(IE_PS_Aborted);
    else
    if (key == g_ActivityStatusProcessPaused)
        SetProcessStatus(IE_PS_Suspend);
    else
    if (key == g_ActivityStatusProcessInProcess)
        SetProcessStatus(IE_PS_InProcess);
    else
    if (key == g_ActivityStatusProcessStarted)
        SetProcessStatus(IE_PS_Started);
    else
    if (key == g_ActivityStatusProcessNotStarted)
        SetProcessStatus(IE_PS_NotStarted);
    else
        PSS_BaseActivity::SetStatusFromKeyString(key);
}
//---------------------------------------------------------------------------
void PSS_Process::SetVisibility(const EThreeState value)
{
    // set the value for the process itself
    PSS_BaseActivity::SetVisibility(value);

    // set the same visibility for its children
    SetChildVisibility(value);
}
//---------------------------------------------------------------------------
CString PSS_Process::GetActivityStatusString() const
{
    // if in parallel mode, check the number of resources
    if (GetRunMode() == IE_RM_Select)
        return PSS_BaseActivity::GetActivityStatusString();

    CString status;

    // check the current activity
    switch (GetProcessStatus())
    {
        case IE_PS_Started:    status.LoadString(IDS_PROCESS_STARTED);    break;
        case IE_PS_InProcess:  status.LoadString(IDS_PROCESS_INPROCESS);  break;
        case IE_PS_Completed:  status.LoadString(IDS_PROCESS_COMPLETED);  break;
        case IE_PS_Aborted:    status.LoadString(IDS_PROCESS_ABORTED);    break;
        case IE_PS_NotStarted: status.LoadString(IDS_PROCESS_NOTSTARTED); break;
        case IE_PS_Suspend:    status.LoadString(IDS_PROCESS_SUSPENDED);  break;
        default:               status.LoadString(IDS_PROCESS_UNKNOWNSTATE);
    }

    return status;
}
//---------------------------------------------------------------------------
PSS_Process* PSS_Process::GetMainProcess()
{
    if (!GetParent())
        return this;

    return GetParent()->GetMainProcess();
}
//---------------------------------------------------------------------------
void PSS_Process::SetDefaultProperty()
{
    // call the base class function
    PSS_BaseActivity::SetDefaultProperty();

    RemoveAllAuthUsers();

    m_UseMail                 = FALSE;
    m_AutoStart               = FALSE;
    m_DoNotUseInternalMessage = FALSE;

}
//---------------------------------------------------------------------------
void PSS_Process::Serialize(CArchive& ar)
{
    PSS_BaseActivity::Serialize(ar);

    CString currentActivityName;
    currentActivityName.Empty();

    PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

    if (ar.IsStoring())
    {
        ar << WORD(m_ProcessStatus);
        ar << WORD(m_UseMail);
        ar << WORD(m_AutoStart);
        ar << WORD(m_DoNotUseInternalMessage);
    }
    else
    {
        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() < 17)
            ar >> currentActivityName;

        WORD wValue;
        ar >> wValue;
        m_ProcessStatus = IEStatus(wValue);

        ar >> wValue;
        m_UseMail = BOOL(wValue);

        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() < 17)
        {
            ar >> wValue;
            m_RunMode = IERunMode(wValue);
        }

        ar >> wValue;
        m_AutoStart = BOOL(wValue);

        ar >> wValue;
        m_DoNotUseInternalMessage = BOOL(wValue);
    }

    if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() < 17)
        m_ActivityArray.Serialize(ar);

    m_AuthorizedUser.Serialize(ar);

    if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() < 17)
    {
        m_SelectedActivityArray.Serialize(ar);

        // once the activity array is serialized, and in reading mode, assign the current activity
        if (!ar.IsStoring() && !currentActivityName.IsEmpty())
            m_pCurrentActivity = FindBaseActivity(currentActivityName);
    }
}
//---------------------------------------------------------------------------
