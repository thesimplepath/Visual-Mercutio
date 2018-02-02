//## begin module%3786DB6B0323.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3786DB6B0323.cm

//## begin module%3786DB6B0323.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%3786DB6B0323.cp

//## Module: BActvt%3786DB6B0323; Package body
//## Subsystem: ZEvent%378A5F7E02DB
//## Source file: z:\adsoft~1\ZEvent\BActvt.cpp

//## begin module%3786DB6B0323.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%3786DB6B0323.additionalIncludes

//## begin module%3786DB6B0323.includes preserve=yes
//## end module%3786DB6B0323.includes

// BActvt
#include "BActvt.h"

//## begin module%3786DB6B0323.declarations preserve=no
//## end module%3786DB6B0323.declarations

//## begin module%3786DB6B0323.additionalDeclarations preserve=yes
#include "zRes32\ZRes.h"

#include "ZProcess.h"
#include "Activity.h"
#include "zBaseLib\BaseDoc.h"
//## end module%3786DB6B0323.additionalDeclarations

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 30 mars 2006 - Ajout des décorations unicode _T( ), nettoyage de code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZBaseActivity, CObject, def_Version )

// Class ZBaseActivity

ZBaseActivity::ZBaseActivity( const CString		ActivityName,
							  const CString		ActivityDescription,
							  ActivityStatus	ActivityStatus )
	  //## begin ZBaseActivity::ZBaseActivity%931584984.hasinit preserve=no
	: m_IsVisible				( UndefinedState ),
	  m_DurationDays			( 2 ),
	  m_VisibilityType			( Visible ),
	  m_pNextActivity			( NULL ),
	  m_pPreviousActivity		( NULL ),
	  m_IntranetActivity		( TRUE ),
	  //## end ZBaseActivity::ZBaseActivity%931584984.hasinit
	  //## begin ZBaseActivity::ZBaseActivity%931584984.initialization preserve=yes
	  m_Name					( ActivityName ),
	  m_Description				( ActivityDescription ),
	  m_ActivityStatus			( ActivityStatus ),
	  m_TimeType				( TimeDays ),
	  m_DaysForBackupResources	( 1 ),
	  m_UseBackupResources		( FALSE ),
	  m_RemindDays				( 1 ),
	  m_IsInBackupProcess		( FALSE ),
	  m_pParent					( NULL ),
	  m_pCurrentActivity		( NULL ),
	  m_RunMode					( SequenceRun ),
	  m_ActivityType			( 0 )
	  //## end ZBaseActivity::ZBaseActivity%931584984.initialization
{
	//## begin ZBaseActivity::ZBaseActivity%931584984.body preserve=yes
	//## end ZBaseActivity::ZBaseActivity%931584984.body
}

ZBaseActivity::~ZBaseActivity()
{
	//## begin ZBaseActivity::~ZBaseActivity%.body preserve=yes
	RemoveAllActivities();
	//## end ZBaseActivity::~ZBaseActivity%.body
}

//## Other Operations (implementation)
ZBaseActivity* ZBaseActivity::GetParent() const
{
	//## begin ZBaseActivity::GetParent%932278208.body preserve=yes
	return m_pParent;
	//## end ZBaseActivity::GetParent%932278208.body
}

ZProcess* ZBaseActivity::GetParentProcess() const
{
	//## begin ZBaseActivity::GetParent%932278208.body preserve=yes
	if ( m_pParent )
	{
		if ( ISA( m_pParent, ZProcess ) )
		{
			return (ZProcess*)m_pParent;
		}

		return m_pParent->GetParentProcess();
	}

	return NULL;
	//## end ZBaseActivity::GetParent%932278208.body
}

ZBaseActivity* ZBaseActivity::GetFirstBaseActivity() const
{
	//## begin ZBaseActivity::GetFirstBaseActivity%932314507.body preserve=yes
	return GetActivityAt( 0 );
	//## end ZBaseActivity::GetFirstBaseActivity%932314507.body
}

ZBaseActivity* ZBaseActivity::GetFirstValidActivity() const
{
	//## begin ZBaseActivity::GetFirstValidActivity%932278209.body preserve=yes
	ZBaseActivity* pFirstActivity = GetActivityAt( 0 );

	if ( !pFirstActivity )
	{
		return NULL;
	}

	if ( pFirstActivity->IsKindOf( RUNTIME_CLASS( ZActivity ) ) ||
		 ( pFirstActivity->HasActivities() && pFirstActivity->GetRunMode() == ChooseMode ) )
	{
		if ( pFirstActivity->IsConsiderAsVisible() != FalseState )
		{
			return pFirstActivity;
		}
	}

	return pFirstActivity->GetNextValidActivity();
	//## end ZBaseActivity::GetFirstValidActivity%932278209.body
}

ZBaseActivity* ZBaseActivity::GetFirstValidBaseActivity() const
{
	//## begin ZBaseActivity::GetFirstValidBaseActivity%937152021.body preserve=yes
	ZBaseActivity* pFirstActivity = GetActivityAt( 0 );

	if ( !pFirstActivity )
	{
		return NULL;
	}

	if ( pFirstActivity->IsConsiderAsVisible() != FalseState )
	{
		return pFirstActivity;
	}

	return pFirstActivity->GetNextValidActivity();
	//## end ZBaseActivity::GetFirstValidBaseActivity%937152021.body
}

ZBaseActivity* ZBaseActivity::GetNextValidActivity() const
{
	//## begin ZBaseActivity::GetNextValidActivity%932278204.body preserve=yes
	if ( GetNextBaseActivity() )
	{
		// If the next activity is a valid activity, return it
		// otherwise, delegate the next search to him
		if ( GetNextBaseActivity()->IsKindOf( RUNTIME_CLASS( ZActivity ) ) ||
			 ( GetNextBaseActivity()->HasActivities() && GetNextBaseActivity()->GetRunMode() == ChooseMode ) )
		{
			if ( GetNextBaseActivity()->IsConsiderAsVisible() != FalseState )
			{
				return GetNextBaseActivity();
			}
		}

		return GetNextBaseActivity()->GetNextValidActivity();
	}

	return NULL;
	//## end ZBaseActivity::GetNextValidActivity%932278204.body
}

ZBaseActivity* ZBaseActivity::GetNextValidBaseActivity() const
{
	//## begin ZBaseActivity::GetNextValidBaseActivity%937152022.body preserve=yes
	if ( GetNextBaseActivity() )
	{
		// If the next activity is a valid activity, return it
		// otherwise, delegate the next search to him
		if ( GetNextBaseActivity()->IsConsiderAsVisible() != FalseState )
		{
			return GetNextBaseActivity();
		}

		return GetNextBaseActivity()->GetNextValidBaseActivity();
	}

	return NULL;
	//## end ZBaseActivity::GetNextValidBaseActivity%937152022.body
}

ZBaseActivity* ZBaseActivity::GetPreviousValidActivity() const
{
	//## begin ZBaseActivity::GetPreviousValidActivity%932278205.body preserve=yes
	if ( GetPreviousBaseActivity() )
	{
		// If the previous activity is a valid activity, return it
		// otherwise, delegate the next search to him
		if ( GetPreviousBaseActivity()->IsKindOf( RUNTIME_CLASS( ZActivity ) ) ||
			 ( GetPreviousBaseActivity()->HasActivities() && GetPreviousBaseActivity()->GetRunMode() == ChooseMode ) )
		{
			if ( GetPreviousBaseActivity()->IsConsiderAsVisible() != FalseState )
			{
				return GetPreviousBaseActivity();
			}
		}

		return GetPreviousBaseActivity()->GetPreviousValidActivity();
	}

	return NULL;
	//## end ZBaseActivity::GetPreviousValidActivity%932278205.body
}

ZBaseActivity* ZBaseActivity::GetPreviousValidBaseActivity() const
{
	//## begin ZBaseActivity::GetPreviousValidBaseActivity%937152023.body preserve=yes
	if ( GetPreviousBaseActivity() )
	{
		// If the previous activity is a valid activity, return it
		// otherwise, delegate the next search to him
		if ( GetPreviousBaseActivity()->IsConsiderAsVisible() != FalseState )
		{
			return GetPreviousBaseActivity();
		}

		return GetPreviousBaseActivity()->GetPreviousValidBaseActivity();
	}

	return NULL;
	//## end ZBaseActivity::GetPreviousValidBaseActivity%937152023.body
}

ZProcess* ZBaseActivity::GetNextProcess() const
{
	//## begin ZBaseActivity::GetNextProcess%932278206.body preserve=yes
	if ( GetNextBaseActivity() )
	{
		// If the next activity is a process, return it
		// otherwise, delegate the next search to him
		if ( GetNextBaseActivity()->IsKindOf( RUNTIME_CLASS( ZProcess ) ) )
		{
			return (ZProcess*)GetNextBaseActivity();
		}

		return GetNextBaseActivity()->GetNextProcess();
	}

	return NULL;
	//## end ZBaseActivity::GetNextProcess%932278206.body
}

ZProcess* ZBaseActivity::GetPreviousProcess() const
{
	//## begin ZBaseActivity::GetPreviousProcess%932278207.body preserve=yes
	if ( GetPreviousBaseActivity() )
	{
		// If the next activity is a process, return it
		// otherwise, delegate the next search to him
		if ( GetPreviousBaseActivity()->IsKindOf( RUNTIME_CLASS( ZProcess ) ) )
		{
			return (ZProcess*)GetPreviousBaseActivity();
		}

		return GetPreviousBaseActivity()->GetPreviousProcess();
	}

	return NULL;
	//## end ZBaseActivity::GetPreviousProcess%932278207.body
}

void ZBaseActivity::CalculateForecastedEndDate()
{
	//## begin ZBaseActivity::CalculateForecastedEndDate%931585004.body preserve=yes
	//## end ZBaseActivity::CalculateForecastedEndDate%931585004.body
}

void ZBaseActivity::CalculateForecastedStartDate()
{
	//## begin ZBaseActivity::CalculateForecastedStartDate%931585005.body preserve=yes
	//## end ZBaseActivity::CalculateForecastedStartDate%931585005.body
}

WORD ZBaseActivity::GetDurationDays()
{
	//## begin ZBaseActivity::GetDurationDays%931585008.body preserve=yes
	return m_DurationDays;
	//## end ZBaseActivity::GetDurationDays%931585008.body
}

void ZBaseActivity::SetDurationDays( WORD value )
{
	//## begin ZBaseActivity::SetDurationDays%931585009.body preserve=yes
	m_DurationDays = value;
	//## end ZBaseActivity::SetDurationDays%931585009.body
}

BOOL ZBaseActivity::FillPersonArray( ZBaseActivity&	Activity,
									 ZUUserManager&	UserManager,
									 CStringArray&	UserArray )
{
	//## begin ZBaseActivity::FillPersonArray%931585012.body preserve=yes
	return TRUE;
	//## end ZBaseActivity::FillPersonArray%931585012.body
}

BOOL ZBaseActivity::FillPersonArray( int			Index,
									 ZUUserManager&	UserManager,
									 CStringArray&	UserArray)
{
	//## begin ZBaseActivity::FillPersonArray%931585013.body preserve=yes
	return TRUE;
	//## end ZBaseActivity::FillPersonArray%931585013.body
}

BOOL ZBaseActivity::ActivityFillPersonArray( ZUUserManager&	UserManager,
											 CStringArray&	UserArray,
											 CString		ConnectedUser)
{
	//## begin ZBaseActivity::ActivityFillPersonArray%931585014.body preserve=yes
	return GetCurrentResources().FillPersonArray( GetMainProcess(), UserManager, UserArray, ConnectedUser );
	//## end ZBaseActivity::ActivityFillPersonArray%931585014.body
}

BOOL ZBaseActivity::PrincipalResourceActivityFillPersonArray( ZUUserManager&	UserManager,
															  CStringArray&		UserArray,
															  CString			ConnectedUser)
{
	return m_PrincipalResources.FillPersonArray( GetMainProcess(), UserManager, UserArray, ConnectedUser );
}

BOOL ZBaseActivity::BackupResourceActivityFillPersonArray( ZUUserManager&	UserManager,
														   CStringArray&	UserArray,
														   CString			ConnectedUser )
{
	return m_BackupResources.FillPersonArray( GetMainProcess(), UserManager, UserArray, ConnectedUser );
}

BOOL ZBaseActivity::ActivityAddUsers( CString DelimiterString )
{
	// Set the user mode
	SetUserType( Users );
	return GetCurrentResources().AddUsers( DelimiterString );
}

BOOL ZBaseActivity::PrincipalResourceActivityAddUsers( CString DelimiterString )
{
	return m_PrincipalResources.AddUsers( DelimiterString );
}

BOOL ZBaseActivity::BackupResourceActivityAddUsers( CString DelimiterString )
{
	return m_BackupResources.AddUsers( DelimiterString );
}

CString ZBaseActivity::ActivityCreatePersonDelimStr( ZUUserManager&	UserManager,
													 CString		ConnectedUser,
													 CString		Delimiter )
{
	//## begin ZBaseActivity::ActivityCreatePersonDelimStr%931584998.body preserve=yes
	return GetCurrentResources().CreatePersonDelimStr( GetMainProcess(), UserManager, ConnectedUser, Delimiter );
	//## end ZBaseActivity::ActivityCreatePersonDelimStr%931584998.body
}

ZUMailUserList* ZBaseActivity::ActivityCreatePersonList( ZUUserManager& UserManager, CString ConnectedUser )
{
	//## begin ZBaseActivity::ActivityCreatePersonList%931585003.body preserve=yes
	return GetCurrentResources().CreatePersonList( GetMainProcess(), UserManager, ConnectedUser );
	//## end ZBaseActivity::ActivityCreatePersonList%931585003.body
}

ZUMailUserList* ZBaseActivity::CreatePersonList( ZBaseActivity& Activity, ZUUserManager& UserManager )
{
	//## begin ZBaseActivity::CreatePersonList%931584999.body preserve=yes
	return NULL;
	//## end ZBaseActivity::CreatePersonList%931584999.body
}

ZUMailUserList* ZBaseActivity::CreatePersonList( int Index, ZUUserManager& UserManager )
{
	//## begin ZBaseActivity::CreatePersonList%931585000.body preserve=yes
	return NULL;
	//## end ZBaseActivity::CreatePersonList%931585000.body
}

CString ZBaseActivity::CreatePersonDelimStr( ZBaseActivity&	Activity,
											 ZUUserManager&	UserManager,
											 CString		Delimiter )
{
	//## begin ZBaseActivity::CreatePersonDelimStr%931585001.body preserve=yes
	return _T( "" );
	//## end ZBaseActivity::CreatePersonDelimStr%931585001.body
}

CString ZBaseActivity::CreatePersonDelimStr( int			Index,
											 ZUUserManager&	UserManager,
											 CString		Delimiter )
{
	//## begin ZBaseActivity::CreatePersonDelimStr%931585002.body preserve=yes
	return _T( "" );
	//## end ZBaseActivity::CreatePersonDelimStr%931585002.body
}

ZUMailUserList* ZBaseActivity::PrincipalResourceActivityCreatePersonList( ZUUserManager&	UserManager,
																		  CString			ConnectedUser )
{
	return m_PrincipalResources.CreatePersonList( GetMainProcess(), UserManager, ConnectedUser );
}

CString ZBaseActivity::PrincipalResourceActivityCreatePersonDelimStr( ZUUserManager&	UserManager,
																	  CString			ConnectedUser,
																	  CString			Delimiter )
{
	return m_PrincipalResources.CreatePersonDelimStr( GetMainProcess(), UserManager, ConnectedUser, Delimiter );
}

ZUMailUserList* ZBaseActivity::BackupResourceActivityCreatePersonList( ZUUserManager&	UserManager,
																	   CString			ConnectedUser )
{
	return m_BackupResources.CreatePersonList( GetMainProcess(), UserManager, ConnectedUser );
}

CString ZBaseActivity::BackupResourceActivityCreatePersonDelimStr( ZUUserManager&	UserManager,
																   CString			ConnectedUser,
																   CString			Delimiter )
{
	return m_BackupResources.CreatePersonDelimStr( GetMainProcess(), UserManager, ConnectedUser, Delimiter );
}

CString ZBaseActivity::GetStatusKeyString( ZBaseActivity* pActivity )
{
	//## begin ZBaseActivity::GetStatusKeyString%931585015.body preserve=yes
	if ( ActivityIsAttribution() && GetActivityStatus() != ActivitySentForAcceptation )
	{
		return ActivityStatusAttribution;
	}

	switch ( GetActivityStatus() )
	{
		case ActivityCompleted:
		{
			return ActivityStatusCompleted;
		}

		case ActivityRejected:
		{
			return ActivityStatusRejected;
		}

		case ActivitySent:
		{
			return ActivityStatusSent;
		}

		case ActivitySentForAcceptation:
		{
			return ActivityStatusRequestAcceptation;
		}

		case ActivityNotStarted:
		{
			return ActivityStatusNotStarted;
		}

		case ActivitySuspended:
		{
			return ActivityStatusProcessPaused;
		}

		case ActivityAborted:
		{
			return ActivityStatusProcessAborted;
		}

		case ActivityStarted:
		{
			return ActivityStatusStarted;
		}
	}

	return _T( "" );
	//## end ZBaseActivity::GetStatusKeyString%931585015.body
}

void ZBaseActivity::SetStatusFromKeyString( const CString KeyString )
{
	//## begin ZBaseActivity::SetStatusFromKeyString%943181050.body preserve=yes
	if ( KeyString == ActivityStatusCompleted )
	{
		SetActivityStatus( ActivityCompleted );
	}
	else if ( KeyString == ActivityStatusRejected )
	{
		SetActivityStatus( ActivityRejected );
	}
	else if ( KeyString == ActivityStatusSent )
	{
		SetActivityStatus( ActivitySent );
	}
	else if ( KeyString == ActivityStatusRequestAcceptation )
	{
		SetActivityStatus( ActivitySentForAcceptation );
	}
	else if ( KeyString == ActivityStatusNotStarted )
	{
		SetActivityStatus( ActivityNotStarted );
	}
	else if ( KeyString == ActivityStatusProcessPaused )
	{
		SetActivityStatus( ActivitySuspended );
	}
	else if ( KeyString == ActivityStatusProcessAborted )
	{
		SetActivityStatus( ActivityAborted );
	}
	else if ( KeyString == ActivityStatusStarted )
	{
		SetActivityStatus( ActivityStarted );
	}
	//## end ZBaseActivity::SetStatusFromKeyString%943181050.body
}

CString ZBaseActivity::GetStatusString( const CString KeyString )
{
	//## begin ZBaseActivity::GetStatusString%931585018.body preserve=yes
	UINT nID;

	if ( KeyString == ActivityStatusProcessCompleted )
	{
		nID = IDS_STATUSPROC_COMPLETED;
	}
	else if ( KeyString == ActivityStatusAttribution )
	{
		nID = IDS_STATUSACT_ATTRIBUTION;
	}
	else if ( KeyString == ActivityStatusCompleted )
	{
		nID = IDS_STATUSACT_COMPLETED;
	}
	else if ( KeyString == ActivityStatusRejected )
	{
		nID = IDS_STATUSACT_REJECTED;
	}
	else if ( KeyString == ActivityStatusSent )
	{
		nID = IDS_STATUSACT_SENT;
	}
	else if ( KeyString == ActivityStatusRequestAcceptation )
	{
		nID = IDS_STATUSACT_SENTFORACPT;
	}
	else if ( KeyString == ActivityStatusNotStarted )
	{
		nID = IDS_STATUSACT_NOTSTARTED;
	}
	else if ( KeyString == ActivityStatusProcessPaused )
	{
		nID = IDS_STATUSPROC_SUSPENDED;
	}
	else if ( KeyString == ActivityStatusProcessAborted )
	{
		nID = IDS_STATUSPROC_ABORTED;
	}
	else
	{
		nID = IDS_STATUSACT_UNKNOWN;
	}

	CString Text;
	Text.LoadString( nID );

	return Text;
	//## end ZBaseActivity::GetStatusString%931585018.body
}

void ZBaseActivity::FillActivityInformationWhenStart()
{
	//## begin ZBaseActivity::FillActivityInformationWhenStart%931613230.body preserve=yes
	SetInitiator( GetConnectedUser() );
	SetStartDate( ZBDate::GetToday() );

	// Set the forecasted start date to be able 
	// to calculate the forecasted end date
	SetForecastedStartDate( ZBDate::GetToday() );

	// Calculate the forecasted end date
	CalculateForecastedEndDate();
	SetActivityStatus( ActivityStarted );
	//## end ZBaseActivity::FillActivityInformationWhenStart%931613230.body
}

void ZBaseActivity::FillActivityInformationWhenEnd()
{
	//## begin ZBaseActivity::FillActivityInformationWhenEnd%931613231.body preserve=yes
	SetEndDate( ZBDate::GetToday() );
	SetActivityStatus( ActivityCompleted );
	//## end ZBaseActivity::FillActivityInformationWhenEnd%931613231.body
}

void ZBaseActivity::FillActivityInformationWhenRefused()
{
	//## begin ZBaseActivity::FillActivityInformationWhenRefused%931613232.body preserve=yes
	SetLastUpdateDate( ZBDate::GetToday() );
	SetActivityStatus( ActivityRejected );
	//## end ZBaseActivity::FillActivityInformationWhenRefused%931613232.body
}

void ZBaseActivity::FillActivityInformationWhenSentForAccept()
{
	//## begin ZBaseActivity::FillActivityInformationWhenSentForAccept%931613233.body preserve=yes
	if ( GetActivityStatus() == ActivityNotStarted )
	{
		SetForecastedStartDate( ZBDate::GetToday() );

		// Calculate the forecasted end date
		CalculateForecastedEndDate();
	}

	SetLastUpdateDate( ZBDate::GetToday() );
	SetActivityStatus( ActivitySentForAcceptation );
	//## end ZBaseActivity::FillActivityInformationWhenSentForAccept%931613233.body
}

void ZBaseActivity::FillActivityInformationWhenSent()
{
	//## begin ZBaseActivity::FillActivityInformationWhenSent%931613244.body preserve=yes
	if ( GetActivityStatus() == ActivityNotStarted )
	{
		SetForecastedStartDate( ZBDate::GetToday() );

		// Calculate the forecasted end date
		CalculateForecastedEndDate();
	}

	SetLastUpdateDate( ZBDate::GetToday() );
	SetActivityStatus( ActivitySent );
	//## end ZBaseActivity::FillActivityInformationWhenSent%931613244.body
}

BOOL ZBaseActivity::ActivityIsShared()
{
	//## begin ZBaseActivity::ActivityIsShared%931613245.body preserve=yes
	// If no activites or If it is parallel mode, check the number of resources
	if ( !HasActivities() || ( HasActivities() && GetRunMode() == ChooseMode ) )
	{
		return GetCurrentResources().GetUserCount() > 1;
	}

	// If has activities, check the current activity
	if ( !GetCurrentActivity() )
	{
		return FALSE;
	}

	return GetCurrentActivity()->ActivityIsShared();
	//## end ZBaseActivity::ActivityIsShared%931613245.body
}

BOOL ZBaseActivity::MustSwitchToBackupResourceActivity()
{
	//## begin ZBaseActivity::MustSwitchToBackupResourceActivity%931613249.body preserve=yes
	// If it is parallel mode, check the number of resources
	if ( !HasActivities() || ( HasActivities() && GetRunMode() == ChooseMode ) )
	{
		if ( GetUseBackupResources() && GetForecastedEndDate() > 0 )
		{
			return ( COleDateTime::GetCurrentTime() >= ( GetForecastedEndDate() + COleDateTimeSpan( GetDaysForBackupResources() ) ) ) ? TRUE : FALSE;
		}

		return FALSE;
	}

	// Else, check the current activity
	if ( !GetCurrentActivity() )
	{
		return FALSE;
	}

	return GetCurrentActivity()->MustSwitchToBackupResourceActivity();
	//## end ZBaseActivity::MustSwitchToBackupResourceActivity%931613249.body
}

BOOL ZBaseActivity::MustRemindEndActivity()
{
	//## begin ZBaseActivity::MustRemindEndActivity%931613250.body preserve=yes
	// If it is parallel mode, check the number of resources
	if ( !HasActivities() || ( HasActivities() && GetRunMode() == ChooseMode ) )
	{
		if ( GetForecastedEndDate() > 0 )
		{
			return ( COleDateTime::GetCurrentTime() >= ( GetForecastedEndDate() - COleDateTimeSpan( GetRemindDays() ) ) ) ? TRUE : FALSE;
		}

		return FALSE;
	}

	// Else, check the current activity
	if ( !GetCurrentActivity() )
	{
		return FALSE;
	}

	return GetCurrentActivity()->MustRemindEndActivity();
	//## end ZBaseActivity::MustRemindEndActivity%931613250.body
}

CString ZBaseActivity::GetActivityStatusString()
{
	//## begin ZBaseActivity::GetActivityStatusString%931711481.body preserve=yes
	CString Status;

	switch ( GetActivityStatus() )
	{
		case ActivityStarted:
	{
			Status.LoadString( IDS_ACTIVITY_STARTED );
			break;
		}

		case ActivityCompleted:
		{
			Status.LoadString( IDS_ACTIVITY_COMPLETED );
			break;
		}

		case ActivityRejected:
		{
			Status.LoadString( IDS_ACTIVITY_REJECTED );
			break;
		}

		case ActivitySent:
		{
			Status.LoadString( IDS_ACTIVITY_NEXTPERSON );
			break;
		}

		case ActivitySentForAcceptation:
		{
			Status.LoadString( IDS_ACTIVITY_FORACCEPTATION );
			break;
		}

		case ActivityNotStarted:
		{
			Status.LoadString( IDS_ACTIVITY_NOTSTARTED );
			break;
		}

		case ActivitySuspended:
		{
			Status.LoadString( IDS_PROCESS_SUSPENDED );
			break;
		}

		case ActivityAborted:
		{
			Status.LoadString( IDS_PROCESS_ABORTED );
			break;
		}

		default:
		{
			Status.LoadString( IDS_ACTIVITY_UNKNOWNSTATE );
		}
	}

	return Status;
	//## end ZBaseActivity::GetActivityStatusString%931711481.body
}

void ZBaseActivity::SetParent( ZBaseActivity* pParent )
{
	//## begin ZBaseActivity::SetParent%936211873.body preserve=yes
	m_pParent = pParent;
	//## end ZBaseActivity::SetParent%936211873.body
}

ZProcess* ZBaseActivity::GetMainProcess()
{
	//## begin ZBaseActivity::GetMainProcess%945000546.body preserve=yes
	if ( GetParent() )
	{
		return GetParent()->GetMainProcess();
	}

	return NULL;
	//## end ZBaseActivity::GetMainProcess%945000546.body
}

void ZBaseActivity::SetCurrentActivity( const CString ActivityName )
{
	//## begin ZProcess::SetCurrentActivity%931815523.body preserve=yes
	m_pCurrentActivity = FindActivity( ActivityName );
	//## end ZProcess::SetCurrentActivity%931815523.body
}

void ZBaseActivity::SetCurrentActivity( ZBaseActivity* pActivity )
{
	//## begin ZProcess::SetCurrentActivity%931815525.body preserve=yes
	m_pCurrentActivity = pActivity;
	//## end ZProcess::SetCurrentActivity%931815525.body
}

ZBaseActivity* ZBaseActivity::SetCurrentActivityToNext()
{
	//## begin ZProcess::SetCurrentActivityToNext%931677640.body preserve=yes
	if ( m_pCurrentActivity )
	{
		m_pCurrentActivity = m_pCurrentActivity->GetNextValidActivity();
	}
	else
	{
		m_pCurrentActivity = GetNextValidActivity();
	}

	return m_pCurrentActivity;
	//## end ZProcess::SetCurrentActivityToNext%931677640.body
}

ZBaseActivity* ZBaseActivity::SetCurrentActivityToPrevious()
{
	//## begin ZProcess::SetCurrentActivityToPrevious%931677641.body preserve=yes
	if ( m_pCurrentActivity )
	{
		m_pCurrentActivity = m_pCurrentActivity->GetPreviousValidActivity();
	}
	else
	{
		m_pCurrentActivity = GetPreviousValidActivity();
	}

	return m_pCurrentActivity;
	//## end ZProcess::SetCurrentActivityToPrevious%931677641.body
}

ZBaseActivity* ZBaseActivity::GetNextValidActivityFromCurrent()
{
	//## begin ZProcess::GetNextValidActivityFromCurrent%932278231.body preserve=yes
	if ( m_pCurrentActivity )
	{
		return m_pCurrentActivity->GetNextValidActivity();
	}

	return NULL;
	//## end ZProcess::GetNextValidActivityFromCurrent%932278231.body
}

ZBaseActivity* ZBaseActivity::GetPreviousValidActivityFromCurrent()
{
	//## begin ZProcess::GetPreviousValidActivityFromCurrent%932278232.body preserve=yes
	if ( m_pCurrentActivity )
	{
		return m_pCurrentActivity->GetPreviousValidActivity();
	}

	return NULL;
	//## end ZProcess::GetPreviousValidActivityFromCurrent%932278232.body
}

ZBaseActivity* ZBaseActivity::GetNextBaseActivityFromCurrent()
{
	//## begin ZProcess::GetNextBaseActivityFromCurrent%932278233.body preserve=yes
	if ( m_pCurrentActivity )
	{
		return m_pCurrentActivity->GetNextBaseActivity();
	}

	return NULL;
	//## end ZProcess::GetNextBaseActivityFromCurrent%932278233.body
}

ZBaseActivity* ZBaseActivity::GetPreviousBaseActivityFromCurrent()
{
	//## begin ZProcess::GetPreviousBaseActivityFromCurrent%932278234.body preserve=yes
	if ( m_pCurrentActivity )
	{
		return m_pCurrentActivity->GetPreviousBaseActivity();
	}

	return NULL;
	//## end ZProcess::GetPreviousBaseActivityFromCurrent%932278234.body
}

BOOL ZBaseActivity::RemoveActivityAt( size_t Index )
{
	//## begin ZProcess::RemoveActivityAt%935832848.body preserve=yes
	if ( Index < GetActivityCount() )
	{
		m_ActivityArray.RemoveAt( Index );
		return TRUE;
	}

	return FALSE;
	//## end ZProcess::RemoveActivityAt%935832848.body
}

BOOL ZBaseActivity::InsertActivityAt( ZBaseActivity* pActivity, size_t Index )
{
	//## begin ZProcess::InsertActivityAt%935832849.body preserve=yes
	if ( Index >= GetActivityCount() )
	{
		m_ActivityArray.Add( (CObject*)pActivity );
	}
	else
	{
		m_ActivityArray.InsertAt( Index, (CObject*)pActivity );
	}

	return TRUE;
	//## end ZProcess::InsertActivityAt%935832849.body
}

BOOL ZBaseActivity::AddActivity( ZBaseActivity* Activity )
{
	//## begin ZProcess::AddActivity%913664906.body preserve=yes
	if ( m_ActivityArray.Add( (CObject*)Activity ) < 0 )
	{
		return FALSE;
	}

	return TRUE;
	//## end ZProcess::AddActivity%913664906.body
}

BOOL ZBaseActivity::AddActivityAfter( ZBaseActivity* Activity, const CString& ActivityName )
{
	//## begin ZProcess::AddActivityAfter%913664907.body preserve=yes
	for ( size_t i = 0; i < GetActivityCount(); ++i )
	{
		if ( GetActivityAt( i )->GetName() == ActivityName )
		{
			m_ActivityArray.InsertAt( i + 1, (CObject*)Activity );
			return TRUE;
		}
	}

	return FALSE;
	//## end ZProcess::AddActivityAfter%913664907.body
}

BOOL ZBaseActivity::DeleteActivity( ZBaseActivity* Activity )
{
	//## begin ZProcess::DeleteActivity%913664908.body preserve=yes
	for ( size_t i = 0; i < GetActivityCount(); ++i )
	{
		if ( GetActivityAt( i ) == Activity )
		{
			delete GetActivityAt( i );
			m_ActivityArray.RemoveAt( i );

			return TRUE;
		}

		if ( GetActivityAt( i )->HasActivities() )
		{
			if ( GetActivityAt( i )->DeleteActivity( Activity ) == TRUE )
			{
				return TRUE;
			}
		}
	}

	return FALSE;
	//## end ZProcess::DeleteActivity%913664908.body
}

BOOL ZBaseActivity::DeleteActivity( const CString& ActivityName )
{
	//## begin ZProcess::DeleteActivity%913885071.body preserve=yes
	ZBaseActivity* pActivity = FindActivity( ActivityName );

	if ( pActivity )
	{
		return DeleteActivity( pActivity );
	}

	return FALSE;
	//## end ZProcess::DeleteActivity%913885071.body
}

ZBaseActivity* ZBaseActivity::FindBaseActivity( const CString& ActivityName )
{
	//## begin ZProcess::FindBaseActivity%934700763.body preserve=yes
	for ( size_t i = 0; i < GetActivityCount(); ++i )
	{
		if ( GetActivityAt( i )->GetName() == ActivityName )
		{
			return GetActivityAt( i );
		}

		if ( GetActivityAt( i )->HasActivities() )
		{
			ZBaseActivity* pReturnedActivity = GetActivityAt( i )->FindBaseActivity( ActivityName );

			if ( pReturnedActivity )
			{
				return pReturnedActivity;
			}
		}
	}

	return NULL;
	//## end ZProcess::FindBaseActivity%934700763.body
}

ZActivity* ZBaseActivity::FindActivity( const CString& ActivityName )
{
	//## begin ZProcess::FindActivity%913664909.body preserve=yes
	for ( size_t i = 0; i < GetActivityCount(); ++i )
	{
		if ( GetActivityAt( i )->HasActivities() )
		{
			ZActivity* pReturnedActivity = GetActivityAt( i )->FindActivity( ActivityName );

			if ( pReturnedActivity )
			{
				return pReturnedActivity;
			}
		}
		else if ( GetActivityAt( i )->IsKindOf( RUNTIME_CLASS( ZActivity ) ) &&
				  GetActivityAt( i )->GetName() == ActivityName )
		{
				return (ZActivity*)GetActivityAt( i );
		}
	}

	return NULL;
	//## end ZProcess::FindActivity%913664909.body
}

BOOL ZBaseActivity::AddProcess( ZProcess* Process )
{
	//## begin ZProcess::AddProcess%932406384.body preserve=yes
	return AddActivity( Process );
	//## end ZProcess::AddProcess%932406384.body
}

BOOL ZBaseActivity::AddProcessAfter( ZProcess* Process, const CString& ActivityName )
{
	//## begin ZProcess::AddProcessAfter%932406385.body preserve=yes
	return AddActivityAfter( Process, ActivityName );
	//## end ZProcess::AddProcessAfter%932406385.body
}

BOOL ZBaseActivity::DeleteProcess( ZProcess* Process )
{
	//## begin ZProcess::DeleteProcess%932406386.body preserve=yes
	return DeleteActivity( Process );
	//## end ZProcess::DeleteProcess%932406386.body
}

BOOL ZBaseActivity::DeleteProcess( const CString& ProcessName )
{
	//## begin ZProcess::DeleteProcess%932406387.body preserve=yes
	return DeleteActivity( ProcessName );
	//## end ZProcess::DeleteProcess%932406387.body
}

ZProcess* ZBaseActivity::FindProcess( const CString& ProcessName )
{
	//## begin ZProcess::FindProcess%932406388.body preserve=yes
	ZBaseActivity* pProcess = FindActivity( ProcessName );

	if ( pProcess && pProcess->IsKindOf( RUNTIME_CLASS( ZProcess ) ) )
	{
		return (ZProcess*)pProcess;
	}

	return NULL;
	//## end ZProcess::FindProcess%932406388.body
}

void ZBaseActivity::RemoveAllActivities ( bool bDeleteActivityPtr /*= true*/ )
{
	//## begin ZProcess::RemoveAllActivities%913664910.body preserve=yes
	for ( size_t i = 0; i < GetActivityCount(); ++i )
	{
		if ( GetActivityAt( i ) )
		{
			if ( GetActivityAt( i )->HasActivities() )
			{
				GetActivityAt( i )->RemoveAllActivities( bDeleteActivityPtr );
			}

			if ( bDeleteActivityPtr )
			{
				delete GetActivityAt( i );
			}
		}
	}

	m_ActivityArray.RemoveAll();
	//## end ZProcess::RemoveAllActivities%913664910.body
}

int ZBaseActivity::GetActivityIndex ( const CString& ActivityName ) const
{
	//## begin ZProcess::GetActivityIndex%916175122.body preserve=yes
	for ( size_t i = 0; i < GetActivityCount(); ++i )
	{
		if ( GetActivityAt( i )->GetName() == ActivityName )
		{
			return (int)i;
		}
	}

	return -1;
	//## end ZProcess::GetActivityIndex%916175122.body
}

BOOL ZBaseActivity::SetActivityAt ( int Index, ZBaseActivity* pActivity )
{
	//## begin ZProcess::SetActivityAt%916175123.body preserve=yes
	if ( Index < (int)GetActivityCount() )
	{
		m_ActivityArray.SetAt( Index, pActivity );
		return TRUE;
	}

	return FALSE;
	//## end ZProcess::SetActivityAt%916175123.body
}

BOOL ZBaseActivity::ChoiceActivityAdd ( const CString ActivityName )
{
	//## begin ZProcess::ChoiceActivityAdd%934700762.body preserve=yes
	// First, check if the array does not contains the value
	for ( int i = 0; i < GetChoiceActivityArray().GetSize(); ++i )
	{
		if ( ActivityName == GetChoiceActivityArray().GetAt( i ) )
		{
			return TRUE;
		}
	}

	return GetChoiceActivityArray().Add( ActivityName ) > -1;
	//## end ZProcess::ChoiceActivityAdd%934700762.body
}

void ZBaseActivity::SetChildVisibility( const ThreeState value )
{
	//## begin ZProcess::SetChildVisibility%935952019.body preserve=yes
	// Sets the value for all activities and sub-process
	for ( size_t i = 0; i < GetActivityCount(); ++i )
	{
		GetActivityAt( i )->SetVisibility( value );
	}
	//## end ZProcess::SetChildVisibility%935952019.body
}

BOOL ZBaseActivity::MoveActivityDown( const CString ActivityName )
{
	//## begin ZProcess::MoveActivityDown%935832843.body preserve=yes
	if ( !CanActivityMoveDown( ActivityName ) )
	{
		return FALSE;
	}

	ZBaseActivity* pActivity = FindBaseActivity( ActivityName );

	if ( pActivity )
	{
		ZBaseActivity* pParent = pActivity->GetParent();

		if ( pParent )
		{
			for ( size_t i = 0; i < pParent->GetActivityCount(); ++i )
			{
				// When activity found
				if ( pParent->GetActivityAt( i ) == pActivity )
				{
					// Remove the pointer from the activity array
					if ( !pParent->RemoveActivityAt( i ) )
					{
						return FALSE;
					}

					// And insert it after
					if ( !pParent->InsertActivityAt( pActivity, i + 1 ) )
					{
						return FALSE;
					}

					// Then recalculate all links
					RecalculateAllLinks();
					return TRUE;
				}
			}
		}
	}

	return FALSE;
	//## end ZProcess::MoveActivityDown%935832843.body
}

BOOL ZBaseActivity::MoveActivityUp( const CString ActivityName )
{
	//## begin ZProcess::MoveActivityUp%935832844.body preserve=yes
	if ( !CanActivityMoveUp( ActivityName ) )
	{
		return FALSE;
	}

	ZBaseActivity* pActivity = FindBaseActivity( ActivityName );

	if ( pActivity )
	{
		ZBaseActivity* pParent = pActivity->GetParent();

		if ( pParent )
		{
			for ( size_t i = 0; i < pParent->GetActivityCount(); ++i )
			{
				// When activity found
				if ( pParent->GetActivityAt(i) == pActivity )
				{
					// Remove the pointer from the activity array
					if ( !pParent->RemoveActivityAt( i ) )
					{
						return FALSE;
					}

					// And insert it after
					if ( !pParent->InsertActivityAt( pActivity, i - 1 ) )
					{
						return FALSE;
					}

					// Then recalculate all links
					RecalculateAllLinks();
					return TRUE;
				}
			}
		}
	}

	return FALSE;
	//## end ZProcess::MoveActivityUp%935832844.body
}

BOOL ZBaseActivity::CanActivityMoveDown( const CString ActivityName )
{
	//## begin ZProcess::CanActivityMoveDown%935832845.body preserve=yes
	ZBaseActivity* pActivity = FindBaseActivity( ActivityName );

	if ( pActivity )
	{
		// If owns activities, can only move at the same level
		if ( pActivity->HasActivities() )
		{
			ZBaseActivity* pParent = pActivity->GetParent();

			if ( pParent )
			{
				for ( size_t i = 0; i < pParent->GetActivityCount(); ++i )
				{
					// When activity found, return true if there is one more below
					if ( pParent->GetActivityAt( i ) == pActivity )
					{
						return i < pParent->GetActivityCount() - 1;
					}
				}
			}
		}
		else if ( pActivity->GetNextBaseActivity() )
		{
			return TRUE;
		}
	}

	return FALSE;
	//## end ZProcess::CanActivityMoveDown%935832845.body
}

BOOL ZBaseActivity::CanActivityMoveUp( const CString ActivityName )
{
	//## begin ZProcess::CanActivityMoveUp%935832846.body preserve=yes
	ZBaseActivity*	pActivity		= FindBaseActivity( ActivityName );
	ZBaseActivity*	pFirstActivity	= GetActivityAt( 0 );

	if ( pActivity )
	{
		// If owns activities, can only move at the same level
		if ( pActivity->HasActivities() )
		{
			ZBaseActivity* pParent = pActivity->GetParent();

			if ( pParent )
			{
				for ( size_t i = 0; i < pParent->GetActivityCount(); ++i )
				{
					// When activity found, return true if there is one more above
					if ( pParent->GetActivityAt(i) == pActivity )
					{
						return i != 0;
					}
				}
			}
		}
		else
		{
			// return true if not the first activity and not the process
			return pFirstActivity->GetName() != ActivityName && GetName() != ActivityName;
		}
	}

	return FALSE;
	//## end ZProcess::CanActivityMoveUp%935832846.body
}

BOOL ZBaseActivity::RecalculateAllLinks()
{
	//## begin ZProcess::RecalculateAllLinks%932406379.body preserve=yes
	RecalculateProcessAllLinks( this );
	return TRUE;
	//## end ZProcess::RecalculateAllLinks%932406379.body
}

ZBaseActivity* ZBaseActivity::RecalculateProcessAllLinks( ZBaseActivity* pParent, ZBaseActivity* pNextOfParent )
{
	//## begin ZProcess::RecalculateProcessAllLinks%932406381.body preserve=yes
	if ( GetActivityCount() > 0 )
	{
		// Initialize the previous pointer of first activity to the parent
		ZBaseActivity*	pPrevious		= pParent;
		ZBaseActivity*	pReturnActivity	= NULL;
		ZBaseActivity*	pLastOfChild	= NULL;

		if ( GetRunMode() == SequenceRun || !IsChoiceActivityDone() )
		{
			// Assigns the next pointer of the process to the first activity
			AssignNextActivityPtr( GetActivityAt( 0 ) );

			// Run through the process' activities
 			for ( size_t i = 0; i < GetActivityCount(); ++i )
			{
				// Assign the parent pointer to the activity
				GetActivityAt( i )->SetParent( this );

				// And assigns previous pointer
				GetActivityAt( i )->AssignPreviousActivityPtr( pPrevious );

				// If the activity has activities, process all activities
				if ( GetActivityAt( i )->HasActivities() )
				{
					// Call recursively with the parent and the next activity
					// and save the previous activity pointer
					pPrevious = GetActivityAt( i )->RecalculateProcessAllLinks( GetActivityAt( i ),
																				GetActivityAt( i + 1 ) );

					// Assign the next of the returned activity
					if ( pPrevious )
					{
						pPrevious->AssignNextActivityPtr( GetActivityAt( i + 1 ) );
					}
					else
					{
						// If no activity, set previous as normal previous
						// Save the previous activity pointer
						pPrevious = GetActivityAt( i );
					}

					// If no next activity, therefore, the last activity is the returned activity
					if ( GetActivityAt( i + 1 ) == NULL )
					{
						pReturnActivity = pPrevious;
					}
				}
				else
				{
					// Assigns next, if no, it assigns NULL pointer
					GetActivityAt( i )->AssignNextActivityPtr( GetActivityAt( i + 1 ) );

					// Save the previous activity pointer
					pPrevious = GetActivityAt( i );
				}
			}

			// The next pointer of the last activity points to the next activity of the parent
			// only if not a process and has no activities
			if ( !GetActivityAt( GetActivityCount() - 1 )->IsKindOf( RUNTIME_CLASS( ZProcess ) ) &&
				 !GetActivityAt( GetActivityCount() - 1 )->HasActivities() )
			{
				GetActivityAt( GetActivityCount() - 1 )->AssignNextActivityPtr( pNextOfParent );
			}

			return ( pReturnActivity ) ? pReturnActivity : GetActivityAt( GetActivityCount() - 1 );
		}
		else
		{
			// Take the choosen activity and link it
			// In the first version, only the first chosen activity is selected
			ZBaseActivity* pChoosenActivity = FindBaseActivity( GetChoiceActivityArray().GetAt( 0 ) );

			// Assigns the next pointer of the process to the chosen activity
			AssignNextActivityPtr( pChoosenActivity );

			// Assign the parent pointer to the activity
			pChoosenActivity->SetParent( this );

			// and assigns previous pointer
			pChoosenActivity->AssignPreviousActivityPtr( pPrevious );

			// If the activity owns activities, process all activities
			if ( pChoosenActivity->HasActivities() )
			{
				// Call recursively with the parent and the next activity
				// and save the previous activity pointer
				pPrevious = pChoosenActivity->RecalculateProcessAllLinks( pChoosenActivity, NULL );

				// If no activity, set previous as normal previous
				if ( !pPrevious )
				{
					// Save the previous activity pointer
					pPrevious = pChoosenActivity;
				}
			}
			else
			{
				// Assigns next, if no, it assigns NULL pointer
				pChoosenActivity->AssignNextActivityPtr( NULL );

				// Save the previous activity pointer
				pPrevious = pChoosenActivity;
			}

			// The next pointer of the last activity points to the next activity of the parent
			// only if not a process
			if ( !pPrevious->IsKindOf( RUNTIME_CLASS( ZProcess ) ) && !pPrevious->HasActivities() )
			{
				pPrevious->AssignNextActivityPtr( pNextOfParent );
			}

			return pPrevious;
		}
	}

	return NULL;
	//## end ZProcess::RecalculateProcessAllLinks%932406381.body
}

void ZBaseActivity::SetDefaultProperty()
{
	m_TimeType					= TimeDays;
	m_DurationDays				= 2;
	m_VisibilityType			= Visible;
	m_IsVisible					= TrueState;
	m_DaysForBackupResources	= 2;
	m_UseBackupResources		= FALSE;
	m_RemindDays				= 1;
	m_IntranetActivity			= TRUE;
	m_IsInBackupProcess			= FALSE;

	m_Initiator.Empty();

	RemoveAllUsers();
	RemoveAllBackupUsers();
}

void ZBaseActivity::Serialize ( CArchive& ar )
{
	//## begin ZBaseActivity::Serialize%931584985.body preserve=yes
	CString CurrentActivityName;
	CurrentActivityName.Empty();

	if ( ar.IsStoring() )
	{
		ar << m_Name;
		ar << m_Description;
		ar << m_Comment;
		ar << m_Initiator;
		ar << (WORD)m_ActivityStatus;
		ar << m_DurationDays;
		ar << m_ForecastedStartDate;
		ar << m_ForecastedEndDate;
		ar << m_StartDate;
		ar << m_EndDate;
		ar << m_LastUpdateDate;
		ar << (WORD)m_VisibilityType;
		ar << (WORD)m_IsVisible;
		ar << (WORD)m_TimeType;
		ar << (WORD)m_IntranetActivity;

		ar << (WORD)m_DaysForBackupResources;
		ar << (WORD)m_UseBackupResources;
		ar << (WORD)m_IsInBackupProcess;
		ar << (WORD)m_RemindDays;

		ar << m_PrincipalResources;
		ar << m_BackupResources;

		// Version 17
		if ( m_pCurrentActivity )
		{
			ar << m_pCurrentActivity->GetName();
		}
		else
		{
			// Serialize empty
			ar << CurrentActivityName;
		}

		ar << (WORD)m_RunMode;
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
		m_ActivityStatus = (ActivityStatus)wValue;

		ar >> m_DurationDays;
		ar >> m_ForecastedStartDate;
		ar >> m_ForecastedEndDate;
		ar >> m_StartDate;
		ar >> m_EndDate;
		ar >> m_LastUpdateDate;

		ar >> wValue;
		m_VisibilityType = (ActivityVisibilityType)wValue;

		ar >> wValue;
		m_IsVisible = (ThreeState)wValue;

		ar >> wValue;
		m_TimeType = (ActivityTimeOutType)wValue;

		ar >> wValue;
		m_IntranetActivity = (BOOL)wValue;

		ar >> wValue;
		m_DaysForBackupResources = (size_t)wValue;

		ar >> wValue;
		m_UseBackupResources = (BOOL)wValue;

		ar >> wValue;
		m_IsInBackupProcess = (BOOL)wValue;

		ar >> wValue;
		m_RemindDays = (size_t)wValue;

		ar >> m_PrincipalResources;
		ar >> m_BackupResources;

		// Version 17
		if ( ( (ZDBaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 17 )
		{
			ar >> CurrentActivityName;

			ar >> wValue;
			m_RunMode = (ActivityRunMode)wValue;

			ar >> m_ActivityType;
		}
	}

	if ( ( (ZDBaseDocument*)ar.m_pDocument )->GetDocumentStamp().GetInternalVersion() >= 17 )
	{
		m_ActivityArray.Serialize( ar );
	}

	if ( ( (ZDBaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 17 )
	{
		m_ChoiceActivityArray.Serialize( ar );

		// Once the activity array is serialized, and in reading mode
		// Assign the current activity pointer
		if ( !ar.IsStoring() && !CurrentActivityName.IsEmpty() )
		{
			m_pCurrentActivity = FindBaseActivity( CurrentActivityName );
		}
	}
	//## end ZBaseActivity::Serialize%931584985.body
}
