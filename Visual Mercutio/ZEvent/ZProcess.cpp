//## begin module%3675498E00B8.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3675498E00B8.cm

//## begin module%3675498E00B8.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%3675498E00B8.cp

//## Module: ZProcess%3675498E00B8; Package body
//## Subsystem: ZEvent%378A5F7E02DB
//## Source file: z:\adsoft~1\ZEvent\ZProcess.cpp

//## begin module%3675498E00B8.additionalIncludes preserve=no
//## end module%3675498E00B8.additionalIncludes

//## begin module%3675498E00B8.includes preserve=yes
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

IMPLEMENT_SERIAL(ZProcess, ZBaseActivity, g_DefVersion)

ZProcess::ZProcess (ProcessStatus ProcessStatus, CString ConnectedUser)
  //## begin ZProcess::ZProcess%915870188.hasinit preserve=no
  //## end ZProcess::ZProcess%915870188.hasinit
  //## begin ZProcess::ZProcess%915870188.initialization preserve=yes
  : ZBaseActivity(),
    m_UseMail(FALSE),
    m_AutoStart(FALSE),
    m_ProcessStatus(ProcessStatus),  
    m_pAttributedActivitiesArray(NULL),
    m_DoNotUseInternalMessage(FALSE)
  //## end ZProcess::ZProcess%915870188.initialization
{
  //## begin ZProcess::ZProcess%915870188.body preserve=yes
    SetDurationDays( 0 );
    SetConnectedUser( ConnectedUser );
  //## end ZProcess::ZProcess%915870188.body
}


ZProcess::~ZProcess()
{
  //## begin ZProcess::~ZProcess%.body preserve=yes
    if (m_pAttributedActivitiesArray)
        delete m_pAttributedActivitiesArray;
    m_pAttributedActivitiesArray = NULL;
  //## end ZProcess::~ZProcess%.body
}



void ZProcess::Serialize (CArchive& ar)
{
  //## begin ZProcess::Serialize%913664905.body preserve=yes
    ZBaseActivity::Serialize( ar );

    CString    CurrentActivityName;
    CurrentActivityName.Empty();

    if (ar.IsStoring())
    {
          ar << (WORD)m_ProcessStatus;
        ar << (WORD)m_UseMail;
        ar << (WORD)m_AutoStart;
        ar << (WORD)m_DoNotUseInternalMessage;
    }
    else
    {
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 17)
        {
            ar >> CurrentActivityName;
        }

        WORD    wValue;
        ar >> wValue;
          m_ProcessStatus = (ProcessStatus)wValue;
          
        ar >> wValue;
        m_UseMail = (BOOL)wValue;

        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 17)
        {
            ar >> wValue;
            m_RunMode = (ActivityRunMode)wValue;
        }
        ar >> wValue;
        m_AutoStart = (BOOL)wValue;

        ar >> wValue;
        m_DoNotUseInternalMessage = (BOOL)wValue;
    }
    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 17)
    {
        m_ActivityArray.Serialize( ar );
    }
    m_AuthorizedUser.Serialize( ar );

    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 17)
    {
        m_ChoiceActivityArray.Serialize( ar );
        // Once the activity array is serialized, and in reading mode
        // Assign the current activity pointer
        if (!ar.IsStoring() && !CurrentActivityName.IsEmpty())
            m_pCurrentActivity = FindBaseActivity( CurrentActivityName );
    }
  //## end ZProcess::Serialize%913664905.body
}



void ZProcess::FillAuthUser (ZBaseActivity& Activity, PSS_UserManager& UserManager)
{
  //## begin ZProcess::FillAuthUser%915992439.body preserve=yes
      // First remove all users
    m_AuthorizedUser.RemoveAll();
    // Fill the authorized user list
    Activity.ActivityFillPersonArray( UserManager, m_AuthorizedUser, GetConnectedUser() );
  //## end ZProcess::FillAuthUser%915992439.body
}

void ZProcess::FillAuthUser (ZBResources& Resources)
{
  //## begin ZProcess::FillAuthUser%940840074.body preserve=yes
      // First remove all users
    m_AuthorizedUser.RemoveAll();
    // Fill the authorized user list with the backup resources
    for (size_t i = 0; i < Resources.GetUserCount(); ++i)
        m_AuthorizedUser.Add( Resources.GetUserAt(i) );
  //## end ZProcess::FillAuthUser%940840074.body
}

void ZProcess::FillAuthUser (CString UserDelimiter)
{
      // First remove all users
    m_AuthorizedUser.RemoveAll();
    // Parse the user delimiter string
    PSS_Tokenizer    Tokenizer( ';' );
    CString    Token = Tokenizer.GetFirstToken( UserDelimiter );
    while (!Token.IsEmpty())
    {
        m_AuthorizedUser.Add( Token );
        Token = Tokenizer.GetNextToken();
    }

}

size_t ZProcess::GetActivityNameArray (CStringArray& ActivityArray, WORD ActivityType, CString ExcludedActivity, BOOL StopWhenFound, BOOL AttributedActivityOnly)
{
  //## begin ZProcess::GetActivityNameArray%916072770.body preserve=yes
      ActivityArray.RemoveAll();
    size_t        Count = 0;
      for (size_t i = 0; i < GetActivityCount(); ++i)
    {
        ZBaseActivity*    pActivity = GetActivityAt( i );
        if (pActivity && pActivity->IsKindOf(RUNTIME_CLASS(ZActivity)))
        {
            if (ExcludedActivity != pActivity->GetName())
            {
                if (ActivityType == 0 || ActivityType & ((ZActivity*)pActivity)->GetActivityType())
                {
                    if (!AttributedActivityOnly || (AttributedActivityOnly && ((ZActivity*)pActivity)->IsAttributedActivity()))
                    {
                        ActivityArray.Add( pActivity->GetName() );
                        ++Count;
                    }
                }
            }
            else
                // If requested to stop when activity is found 
                if (StopWhenFound)
                    return Count;
        }
    }
      return Count;
  //## end ZProcess::GetActivityNameArray%916072770.body
}

BOOL ZProcess::TemplateExist (const CString& TemplateName)
{
  //## begin ZProcess::TemplateExist%916261170.body preserve=yes
      for (size_t i = 0; i < GetActivityCount(); ++i)
    {
        if (GetActivityAt(i)->IsKindOf(RUNTIME_CLASS(ZActivity)))
        {
              if (((ZActivity*)GetActivityAt(i))->TemplateExist( TemplateName ))
                  return TRUE;
        }
    }
      return FALSE;
  //## end ZProcess::TemplateExist%916261170.body
}

PSS_MailUserList* ZProcess::CreatePersonList (ZBaseActivity& Activity, PSS_UserManager& UserManager)
{
  //## begin ZProcess::CreatePersonList%927439016.body preserve=yes
    return Activity.ActivityCreatePersonList( UserManager, GetConnectedUser() );
  //## end ZProcess::CreatePersonList%927439016.body
}

PSS_MailUserList* ZProcess::CreatePersonList (int Index, PSS_UserManager& UserManager)
{
  //## begin ZProcess::CreatePersonList%927439017.body preserve=yes
    ZBaseActivity*    pActivity = GetActivityAt( Index );
    if (pActivity)
        return CreatePersonList( *pActivity, UserManager );
    return NULL;
  //## end ZProcess::CreatePersonList%927439017.body
}

BOOL ZProcess::FillPersonArray (ZBaseActivity& Activity, PSS_UserManager& UserManager, CStringArray& UserArray)
{
  //## begin ZProcess::FillPersonArray%927439018.body preserve=yes
    return Activity.ActivityFillPersonArray( UserManager, UserArray, m_ConnectedUser );
  //## end ZProcess::FillPersonArray%927439018.body
}

BOOL ZProcess::FillPersonArray (int Index, PSS_UserManager& UserManager, CStringArray& UserArray)
{
  //## begin ZProcess::FillPersonArray%927439019.body preserve=yes
    ZBaseActivity*    pActivity = GetActivityAt( Index );
    if (pActivity)
        return FillPersonArray( *pActivity, UserManager, UserArray );
    return FALSE;
  //## end ZProcess::FillPersonArray%927439019.body
}

CString ZProcess::CreatePersonDelimStr (ZBaseActivity& Activity, PSS_UserManager& UserManager, CString Delimiter)
{
  //## begin ZProcess::CreatePersonDelimStr%927439020.body preserve=yes
    return Activity.ActivityCreatePersonDelimStr( UserManager, m_ConnectedUser, Delimiter );
  //## end ZProcess::CreatePersonDelimStr%927439020.body
}

CString ZProcess::CreatePersonDelimStr (int Index, PSS_UserManager& UserManager, CString Delimiter)
{
  //## begin ZProcess::CreatePersonDelimStr%927439021.body preserve=yes
    if (GetActivityAt(Index)->IsKindOf(RUNTIME_CLASS(ZActivity)))
    {
        ZActivity*    pActivity = (ZActivity*)GetActivityAt( Index );
        if (pActivity)
            return CreatePersonDelimStr( *pActivity, UserManager, Delimiter );
    }
    return "";
  //## end ZProcess::CreatePersonDelimStr%927439021.body
}

CObArray* ZProcess::GetAttributedActivities (const CString Name)
{
  //## begin ZProcess::GetAttributedActivities%927535108.body preserve=yes
    // If old array, delete it
    if (m_pAttributedActivitiesArray)
        delete m_pAttributedActivitiesArray;
    m_pAttributedActivitiesArray = NULL;
    // Create a new one
    m_pAttributedActivitiesArray = new CObArray;
      for (size_t i = 0; i < GetActivityCount(); ++i)
        if (GetActivityAt(i)->IsKindOf(RUNTIME_CLASS(ZActivity)))
        {
              if (((ZActivity*)GetActivityAt(i))->GetAttributedByActivity() == Name)
                  m_pAttributedActivitiesArray->Add( GetActivityAt(i) );
        }
    // If nothing found, delete it
    if (m_pAttributedActivitiesArray->GetSize() <= 0)
    {
        if (m_pAttributedActivitiesArray)
            delete m_pAttributedActivitiesArray;
        m_pAttributedActivitiesArray = NULL;
    }
      return m_pAttributedActivitiesArray;
  //## end ZProcess::GetAttributedActivities%927535108.body
}

void ZProcess::CalculateForecastedStartDate ()
{
  //## begin ZProcess::CalculateForecastedStartDate%931585006.body preserve=yes
  //## end ZProcess::CalculateForecastedStartDate%931585006.body
}

void ZProcess::CalculateForecastedEndDate ()
{
  //## begin ZProcess::CalculateForecastedEndDate%929033120.body preserve=yes
    // Sets the forecasted end date 
    // by adding the duration to the start date
    SetForecastedEndDate( GetStartDate() + COleDateTimeSpan(GetDurationDays()) );
  //## end ZProcess::CalculateForecastedEndDate%929033120.body
}

WORD ZProcess::GetDurationDays ()
{
  //## begin ZProcess::GetDurationDays%931585010.body preserve=yes
    // First, add all days
    int    Duration = 0;
    ZProcessIterator    Iterator( this );
      for (ZBaseActivity* pRunner = Iterator.StartIterator(Iterator.GetFirstValidActivity()); pRunner; pRunner = Iterator.GetNextValidActivity())
        Duration += pRunner->GetDurationDays();
    return Duration;
  //## end ZProcess::GetDurationDays%931585010.body
}

CString ZProcess::GetStatusKeyString (ZBaseActivity* pActivity)
{
  //## begin ZProcess::GetStatusKeyString%931585016.body preserve=yes
    // If it is parallel mode, check the number of resources
    if (GetRunMode() == ChooseMode)
        return ZBaseActivity::GetStatusKeyString(pActivity);
    // Else, check the current activity
    if (pActivity)
    {
        switch (GetProcessStatus())
        {
            case ProcessCompleted: return ActivityStatusProcessCompleted;
            case ProcessAborted: return ActivityStatusProcessAborted;
            case ProcessSuspend: return ActivityStatusProcessPaused;
            case ProcessNotStarted: return ActivityStatusProcessNotStarted;
        }
        return pActivity->GetStatusKeyString( pActivity );
    }
    // Else, check the current activity
    switch (GetProcessStatus())
    {
        case ProcessCompleted: return ActivityStatusProcessCompleted;
        case ProcessAborted: return ActivityStatusProcessAborted;
        case ProcessSuspend: return ActivityStatusProcessPaused;
        case ProcessInProcess: return ActivityStatusProcessInProcess;
        case ProcessStarted: return ActivityStatusProcessStarted;
        case ProcessNotStarted: return ActivityStatusProcessNotStarted;
    }

    if (pActivity == NULL)
        pActivity = GetCurrentActivity();
      // Nothing to do
    if (!pActivity)
        return "";
    return pActivity->GetStatusKeyString( pActivity );
  //## end ZProcess::GetStatusKeyString%931585016.body
}

void ZProcess::SetStatusFromKeyString (const CString KeyString)
{
  //## begin ZProcess::SetStatusFromKeyString%943181049.body preserve=yes
    if (KeyString == ActivityStatusProcessCompleted)
        SetProcessStatus( ProcessCompleted );
    else
    if (KeyString == ActivityStatusProcessAborted)
        SetProcessStatus( ProcessAborted );
    else
    if (KeyString == ActivityStatusProcessPaused)
        SetProcessStatus( ProcessSuspend );
    else
    if (KeyString == ActivityStatusProcessInProcess)
        SetProcessStatus( ProcessInProcess );
    else
    if (KeyString == ActivityStatusProcessStarted)
        SetProcessStatus( ProcessStarted );
    else
    if (KeyString == ActivityStatusProcessNotStarted)
        SetProcessStatus( ProcessNotStarted );
    else
        ZBaseActivity::SetStatusFromKeyString( KeyString );
  //## end ZProcess::SetStatusFromKeyString%943181049.body
}


void ZProcess::SetVisibility (const EThreeState value)
{
  //## begin ZProcess::SetVisibility%935776836.body preserve=yes
    // Sets the value for the process itself
    ZBaseActivity::SetVisibility( value );
    // and finally the same visibility for its childs
    SetChildVisibility( value );
  //## end ZProcess::SetVisibility%935776836.body
}


CString ZProcess::GetActivityStatusString ()
{
  //## begin ZProcess::GetActivityStatusString%935923759.body preserve=yes
    // If it is parallel mode, check the number of resources
    if (GetRunMode() == ChooseMode)
        return ZBaseActivity::GetActivityStatusString();
    // Else, check the current activity
      CString    Status;
    switch (GetProcessStatus())
    {
        case ProcessStarted:
        {
            Status.LoadString( IDS_PROCESS_STARTED );
            break;
        }
        case ProcessInProcess:
        {
            Status.LoadString( IDS_PROCESS_INPROCESS );
            break;
        }
        case ProcessCompleted:
        {
            Status.LoadString( IDS_PROCESS_COMPLETED );
            break;
        }
        case ProcessAborted:
        {
            Status.LoadString( IDS_PROCESS_ABORTED );
            break;
        }
        case ProcessNotStarted:
        {
            Status.LoadString( IDS_PROCESS_NOTSTARTED );
            break;
        }
        case ProcessSuspend:
        {
            Status.LoadString( IDS_PROCESS_SUSPENDED );
            break;
        }
        default:
        {
            Status.LoadString( IDS_PROCESS_UNKNOWNSTATE );
        }
    }
    return Status;
  //## end ZProcess::GetActivityStatusString%935923759.body
}

ZProcess* ZProcess::GetMainProcess ()
{
  //## begin ZProcess::GetMainProcess%945000549.body preserve=yes
    if (GetParent() == NULL)
        return this;
    return GetParent()->GetMainProcess();
  //## end ZProcess::GetMainProcess%945000549.body
}

// Additional Declarations
  //## begin ZProcess%36725B570291.declarations preserve=yes
  //## end ZProcess%36725B570291.declarations

//## begin module%3675498E00B8.epilog preserve=yes
void ZProcess::SetDefaultProperty()
{
    // Call the base class function first
    ZBaseActivity::SetDefaultProperty();

    RemoveAllAuthUsers();
    m_UseMail = FALSE;
    m_AutoStart = FALSE;
    m_DoNotUseInternalMessage = FALSE;

}
//## end module%3675498E00B8.epilog
