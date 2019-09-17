//## begin module%3786DB7B0055.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3786DB7B0055.cm

//## begin module%3786DB7B0055.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%3786DB7B0055.cp

//## Module: BActvt%3786DB7B0055; Package specification
//## Subsystem: ZEvent%378A5F7E02DB
//## Source file: z:\adsoft~1\ZEvent\BActvt.h

#ifndef BActvt_h
#define BActvt_h 1

//## begin module%3786DB7B0055.additionalIncludes preserve=no
//## end module%3786DB7B0055.additionalIncludes

//## begin module%3786DB7B0055.includes preserve=yes

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// Forward declarations
class ZActivity;
class ZProcess;

//## end module%3786DB7B0055.includes

// Mfc
#include "Mfc.h"
//## begin module%3786DB7B0055.declarations preserve=no
//## end module%3786DB7B0055.declarations

//## begin module%3786DB7B0055.additionalDeclarations preserve=yes
#include "zBaseLib\PSS_SmartPtr.h"
#include "zBaseLib\ZBDate.h"
#include "zBaseLib\PSS_MailUserList.h"
#include "Zresourc.h"


enum    ActivityRunMode
{
    SequenceRun, ChooseMode, ParallelMode
};


enum     ActivityVisibilityType
{
    Visible, Invisible, AttributionOfVisibility
};
enum     ActivityTimeOutType
{
    TimeDays, AttributionOfTimeOut
};
// Flags defining the activity type
enum     ActivityType
{
    ActivityTypeInputInformation = 0x0001,
    ActivityTypeAcceptation = 0x0002,
    ActivityTypeAttribution = 0x0004,
    ActivityTypeSendMail = 0x0008,
    ActivityTypeStartProcess = 0x0010,
    ActivityTypeCommandLine = 0x0020,
    ActivityTypeScanning = 0x0040,
    ActivityTypeArchiving = 0x0080
};

enum     ActivityStatus
{
    ActivityStarted, ActivitySent, ActivitySentForAcceptation, ActivityCompleted, ActivityRejected, ActivitySuspended, ActivityAborted, ActivityNotStarted
};


// Activity Type flag
const    char    ActivityTypeInputInformationKey[] = "ActInp";
const    char    ActivityTypeAcceptationKey[] = "ActAcpt";
const    char    ActivityTypeAttributionKey[] = "ActAttr";
const    char    ActivityTypeSendMailKey[] = "ActSndM";
const    char    ActivityTypeStartProcessKey[] = "ActStProc";
const    char    ActivityTypeCommandLineKey[] = "ActCmd";
const    char    ActivityTypeScanningKey[] = "ActScan";
const    char    ActivityTypeArchivingKey[] = "ActArch";


// Activity Status flag
const    char    ActivityStatusProcessStarted[] = "PrcSt";
const    char    ActivityStatusProcessNotStarted[] = "PrcNotSt";
const    char    ActivityStatusProcessInProcess[] = "PrcInProc";
const    char    ActivityStatusProcessPaused[] = "PrcPause";
const    char    ActivityStatusProcessAborted[] = "PrcAbort";
const    char    ActivityStatusProcessCompleted[] = "PrcCmpl";
const    char    ActivityStatusRequestAcceptation[] = "ActRqAcpt";
const    char    ActivityStatusSent[] = "ActSent";
const    char    ActivityStatusAccepted[] = "ActAcpt";
const    char    ActivityStatusRejected[] = "ActRejt";
const    char    ActivityStatusAttribution[] = "ActAttr";
const    char    ActivityStatusCompleted[] = "ActCmpl";
const    char    ActivityStatusNotStarted[] = "ActNotSt";
const    char    ActivityStatusStarted[] = "ActSt";
const    char    ActivityStatusTakeOwnerShip[] = "ActTkOwn";


#ifdef _ZEVENTEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

//## end module%3786DB7B0055.additionalDeclarations


//## Class: ZBaseActivity%3786D911011F
//    This class exposes the interface for activities in
//    general. A process is an activity.
//## Category: ZEvent::Process Classes - Event%378A5FD903A4
//## Subsystem: ZEvent%378A5F7E02DB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3786EC2C0031; { -> }

class AFX_EXT_CLASS ZBaseActivity : public CObject  //## Inherits: <unnamed>%3786DA8902EC
{
    //## begin ZBaseActivity%3786D911011F.initialDeclarations preserve=yes
public:
    // Inherited feature
    typedef CObject inherited;
    DECLARE_SERIAL(ZBaseActivity)
    //## end ZBaseActivity%3786D911011F.initialDeclarations

public:
    //## Constructors (specified)
      //## Operation: ZBaseActivity%931584984
    ZBaseActivity(const CString ActivityName = "", const CString ActivityDescription = "", ActivityStatus ActivityStatus = ActivityNotStarted);

    //## Destructor (generated)
    ~ZBaseActivity();

    const WORD GetActivityType() const;

    //## Other Operations (specified)
      //## Operation: GetParent%932278208
      //    Returns the process that owns the activity.
    ZBaseActivity* GetParent() const;

    ZProcess*         GetParentProcess() const;

    bool             HasActivities() const;

    //## Operation: GetFirstBaseActivity%932314507
    //    Return the first base activity pointer.
    virtual ZBaseActivity* GetFirstBaseActivity() const;

    //## Operation: GetFirstValidActivity%932278209
    //    Return the first activity pointer.
    virtual ZBaseActivity* GetFirstValidActivity() const;

    //## Operation: GetFirstValidBaseActivity%937152021
    //    Return the first activity pointer.
    virtual ZBaseActivity* GetFirstValidBaseActivity() const;

    //## Operation: GetNextBaseActivity%932278202
    //    Return the next activity pointer. If no, return NULL.
    ZBaseActivity* GetNextBaseActivity() const;

    //## Operation: GetPreviousBaseActivity%932278203
    //    Return the previous activity pointer. If no, return NULL.
    ZBaseActivity* GetPreviousBaseActivity() const;

    //## Operation: GetNextValidActivity%932278204
    //    Return the next activity pointer. If no, return NULL.
    ZBaseActivity* GetNextValidActivity() const;

    //## Operation: GetNextValidBaseActivity%937152022
    //    Return the next activity pointer. If no, return NULL.
    ZBaseActivity* GetNextValidBaseActivity() const;

    //## Operation: GetPreviousValidActivity%932278205
    //    Return the previous activity pointer. If no, return NULL.
    ZBaseActivity* GetPreviousValidActivity() const;

    //## Operation: GetPreviousValidBaseActivity%937152023
    //    Return the previous activity pointer. If no, return NULL.
    ZBaseActivity* GetPreviousValidBaseActivity() const;

    //## Operation: GetNextProcess%932278206
    //    Return the next process pointer. If no, return NULL.
    ZProcess* GetNextProcess() const;

    //## Operation: GetPreviousProcess%932278207
    //    Return the previous process pointer. If no, return NULL.
    ZProcess* GetPreviousProcess() const;

    //## Operation: Serialize%931584985
    //    Serialization function required for MFC mecanism.
    virtual void Serialize(CArchive& ar);

    //## Operation: ActivityCreatePersonDelimStr%931584998
    //    Take the activity and build a delimited string
    //    containing the person list.
    virtual CString ActivityCreatePersonDelimStr(PSS_UserManager& UserManager, CString ConnectedUser, CString Delimiter = ";");

    //## Operation: ActivityCreatePersonList%931585003
    //    Take the activity and build the person list for the
    //    email.
    virtual PSS_MailUserList* ActivityCreatePersonList(PSS_UserManager& UserManager, CString ConnectedUser);

    //## Operation: CreatePersonList%931584999
    //    Take the activity and build the person list for the
    //    email.
    virtual PSS_MailUserList* CreatePersonList(ZBaseActivity& Activity, PSS_UserManager& UserManager);

    //## Operation: CreatePersonList%931585000
    //    Take the activity and build the person list for the
    //    email.
    virtual PSS_MailUserList* CreatePersonList(int Index, PSS_UserManager& UserManager);

    //## Operation: CreatePersonDelimStr%931585001
    //    Take the activity and build a delimited string
    //    containing the person list.
    virtual CString CreatePersonDelimStr(ZBaseActivity& Activity, PSS_UserManager& UserManager, CString Delimiter = ";");

    //## Operation: CreatePersonDelimStr%931585002
    //    Take the activity and build a delimited string
    //    containing the person list.
    virtual CString CreatePersonDelimStr(int Index, PSS_UserManager& UserManager, CString Delimiter = ";");

    //## Operation: FillPersonArray%931585012
    //    Take the activity and fill a person array.
    virtual BOOL FillPersonArray(ZBaseActivity& Activity, PSS_UserManager& UserManager, CStringArray& UserArray);

    //## Operation: FillPersonArray%931585013
    //    Take the activity and fill a person array.
    virtual BOOL FillPersonArray(int Index, PSS_UserManager& UserManager, CStringArray& UserArray);

    //    Take the activity and fill a person array.
    virtual BOOL ActivityFillPersonArray(PSS_UserManager& UserManager, CStringArray& UserArray, CString ConnectedUser);

    virtual BOOL ActivityAddUsers(CString DelimiterString);

    virtual BOOL PrincipalResourceActivityAddUsers(CString DelimiterString);

    virtual BOOL BackupResourceActivityAddUsers(CString DelimiterString);


    virtual BOOL PrincipalResourceActivityFillPersonArray(PSS_UserManager& UserManager, CStringArray& UserArray, CString ConnectedUser);
    virtual PSS_MailUserList* PrincipalResourceActivityCreatePersonList(PSS_UserManager& UserManager, CString ConnectedUser);
    virtual CString PrincipalResourceActivityCreatePersonDelimStr(PSS_UserManager& UserManager, CString ConnectedUser, CString Delimiter = ";");

    virtual BOOL BackupResourceActivityFillPersonArray(PSS_UserManager& UserManager, CStringArray& UserArray, CString ConnectedUser);
    virtual PSS_MailUserList* BackupResourceActivityCreatePersonList(PSS_UserManager& UserManager, CString ConnectedUser);
    virtual CString BackupResourceActivityCreatePersonDelimStr(PSS_UserManager& UserManager, CString ConnectedUser, CString Delimiter = ";");


    //## Operation: CalculateForecastedEndDate%931585004
    //    This function calculates the forecasted end date by
    //    taking all activities.
    virtual void CalculateForecastedEndDate();

    //## Operation: CalculateForecastedStartDate%931585005
    //    This function calculates the forecasted start date by
    //    taking all activities.
    virtual void CalculateForecastedStartDate();

    //## Operation: GetDurationDays%931585008
    virtual WORD GetDurationDays();

    //## Operation: SetDurationDays%931585009
    virtual void SetDurationDays(WORD value);

    //## Operation: GetStatusKeyString%931585015
    //    Return the Activity Status string.
    virtual CString GetStatusKeyString(ZBaseActivity* pActivity = NULL);

    //## Operation: SetStatusFromKeyString%943181050
    //    Set the Activity Status based on a keystring.
    virtual void SetStatusFromKeyString(const CString KeyString);

    //## Operation: GetStatusString%931585018
    static CString GetStatusString(const CString KeyString);

    //## Operation: AddUser%931585020
    //    Add a new user.
    virtual void AddUser(const CString UserName);

    //## Operation: RemoveUser%931585021
    //    Remove a specific user.
    virtual BOOL RemoveUser(const CString& UserName);

    //## Operation: UserExist%931585022
    //    Search if a specific user exists.
    virtual BOOL UserExist(const CString& UserName);

    //## Operation: GetUserCount%931585023
    //    Return the number of users.
    virtual size_t GetUserCount();

    //## Operation: RemoveAllUsers%931585024
    //    Remove all users.
    virtual void RemoveAllUsers();

    //## Operation: GetUserAt%931585025
    //    Returns the user at the index position.
    virtual CString GetUserAt(int Index);

    //## Operation: AddBackupUser%931585026
    //    Add a new user.
    virtual void AddBackupUser(const CString UserName);

    //## Operation: RemoveBackupUser%931585027
    //    Remove a specific user.
    virtual BOOL RemoveBackupUser(const CString& UserName);

    //## Operation: BackupUserExist%931585028
    //    Search if a specific user exists.
    virtual BOOL BackupUserExist(const CString& UserName);

    //## Operation: GetBackupUserCount%931585029
    //    Return the number of users.
    virtual size_t GetBackupUserCount();

    //## Operation: RemoveAllBackupUsers%931585030
    //    Remove all users.
    virtual void RemoveAllBackupUsers();

    //## Operation: GetBackupUserAt%931585031
    //    Returns the user at the index position.
    virtual CString GetBackupUserAt(int Index);

    //## Operation: GetAttributedByActivity%931585032
    virtual CString GetAttributedByActivity() const;

    //## Operation: SetAttributedByActivity%931585033
    virtual void SetAttributedByActivity(const CString value = "");

    //## Operation: FillActivityInformationWhenStart%931613230
    //    When the task starts, fill necessary information.
    void FillActivityInformationWhenStart();

    //## Operation: FillActivityInformationWhenEnd%931613231
    //    When the task ends, fill necessary information.
    void FillActivityInformationWhenEnd();

    //## Operation: FillActivityInformationWhenRefused%931613232
    //    When the task is refused, fill necessary information.
    void FillActivityInformationWhenRefused();

    //## Operation: FillActivityInformationWhenSentForAccept%931613233
    //    When the task is sent for acceptation, fill necessary
    //    information.
    void FillActivityInformationWhenSentForAccept();

    //## Operation: FillActivityInformationWhenSent%931613244
    void FillActivityInformationWhenSent();

    //## Operation: ActivityIsShared%931613245
    //    Return TRUE if the activity is shared by several users.
    virtual BOOL ActivityIsShared();

    //## Operation: MustSwitchToBackupResourceActivity%931613249
    //    If it is time to switch to backup resource and if backup
    //    resources have been defined, return TRUE.
    virtual BOOL MustSwitchToBackupResourceActivity();

    //## Operation: MustRemindEndActivity%931613250
    //    If it is time to remind for end activity, return TRUE.
    virtual BOOL MustRemindEndActivity();

    //## Operation: ActivityIsAttribution%931613263
    //    Returns TRUE if it is an attribution activity.
    virtual BOOL ActivityIsAttribution();

    //## Operation: ActivityIsAcceptation%931613264
    //    Returns TRUE if it is an acceptation activity.
    virtual BOOL ActivityIsAcceptation();

    //## Operation: ActivityIsInput%931613265
    //    Returns TRUE if it is an input information activity.
    virtual BOOL ActivityIsInput();

    //## Operation: ActivityIsSendMail%931613266
    //    Returns TRUE if it is a send mail activity.
    virtual BOOL ActivityIsSendMail();

    //## Operation: ActivityIsStartProcess%931613267
    //    Returns TRUE if it is a start process activity.
    virtual BOOL ActivityIsStartProcess();

    //## Operation: ActivityIsCommandLine%931613268
    //    Returns TRUE if it is a command line activity.
    virtual BOOL ActivityIsCommandLine();

    //## Operation: ActivityIsScanning%940156895
    //    Returns TRUE if it is a scanning process activity.
    virtual BOOL ActivityIsScanning();

    //## Operation: ActivityIsArchiving%940156896
    //    Returns TRUE if it is an archiving process activity.
    virtual BOOL ActivityIsArchiving();

    //## Operation: GetActivityStatusString%931711481
    virtual CString GetActivityStatusString();

    //## Operation: AssignNextActivityPtr%932406382
    //    Assigns the next base activity pointer.
    void AssignNextActivityPtr(ZBaseActivity* Ptr);

    //## Operation: AssignPreviousActivityPtr%932406383
    //    Assigns the previous base activity pointer.
    void AssignPreviousActivityPtr(ZBaseActivity* Ptr);

    //## Operation: IsUserAttributionDone%934825328
    //    Returns TRUE if the user attribution has been done for
    //    this activity.
    BOOL IsUserAttributionDone();

    //## Operation: IsTimeAttributionDone%934825329
    //    Returns TRUE if the time attribution has been done for
    //    this activity.
    BOOL IsTimeAttributionDone();

    //## Operation: IsVisibilityAttributionDone%935005730
    //    Returns TRUE if the visibility attribution has been done
    //    for this activity.
    BOOL IsVisibilityAttributionDone();

    //## Operation: IsAttributedActivity%934825330
    //    Returns true if the activity is an attributed activity.
    virtual BOOL IsAttributedActivity() const;

    //## Operation: IsInBackupProcess%934825331
    BOOL IsInBackupProcess() const;

    //## Operation: SetIsInBackupProcess%934825332
    void SetIsInBackupProcess(BOOL value = TRUE);

    //## Operation: GetUserType%934825333
    ActivityUserType GetUserType() const;

    //## Operation: SetUserType%934825334
    void SetUserType(ActivityUserType value);

    //## Operation: GetBackupUserType%934825335
    ActivityUserType GetBackupUserType() const;

    //## Operation: SetBackupUserType%934825336
    void SetBackupUserType(ActivityUserType value);

    //## Operation: GetCurrentResources%934825337
    //    Returns the current resources. It depends if the
    //    activity has been entered in backup process.
    ZBResources& GetCurrentResources();

    //## Operation: IsConsiderAsVisible%935005731
    //    Return TRUE if the activity is considered as visible.
    //    Attributed activity are considered as visible until they
    //    has been selected as invisible.
    EThreeState IsConsiderAsVisible() const;

    //## Operation: SetVisibility%935776835
    //    Set the visibility of an activity or process.
    virtual void SetVisibility(const EThreeState value);

    //## Operation: SetParent%936211873
    void SetParent(ZBaseActivity* pParent);

    //## Operation: GetMainProcess%945000546
    //    Return the main process.
    virtual ZProcess* GetMainProcess();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: IsVisible%37B5237800C0
      //    The real visibility type.
    const EThreeState& GetIsVisible() const;

    //## Attribute: StartDate%3786D98F02C5
    //    Contains the start date.
    const PSS_Date GetStartDate() const;
    void SetStartDate(PSS_Date value);

    //## Attribute: EndDate%3786D99402C2
    //    Contains the end date.
    const PSS_Date GetEndDate() const;
    void SetEndDate(PSS_Date value);

    //## Attribute: ForecastedEndDate%3786D99903AF
    //    Contains the end calculated forecasted date. This date
    //    is initialized once the process starts.
    const PSS_Date GetForecastedEndDate() const;
    void SetForecastedEndDate(PSS_Date value);

    //## Attribute: ForecastedStartDate%3786ECE40361
    //    Contains the start calculated forecasted date. This date
    //    is initialized once the process starts.
    const PSS_Date GetForecastedStartDate() const;
    void SetForecastedStartDate(PSS_Date value);

    //## Attribute: LastUpdateDate%3786D9A000AC
    //    Contains the last update date.
    const PSS_Date GetLastUpdateDate() const;
    void SetLastUpdateDate(PSS_Date value);

    //## Attribute: Name%3786D9C7031F
    //    The process name.
    const CString& GetName() const;
    void SetName(const CString& value);

    //## Attribute: Description%3786D9CB03CF
    //    The process description.
    const CString& GetDescription() const;
    void SetDescription(const CString& value);

    //## Attribute: Comment%37DBD25B0368
    //    The activity comment. Used when reject, stopped or pause
    //    an activity.
    const CString& GetComment() const;
    void SetComment(const CString& value);

    //## Attribute: Initiator%3786D9FD036D
    const CString& GetInitiator() const;
    void SetInitiator(const CString& value);

    //## Attribute: ActivityStatus%3786DA0902CA
    //    The activity status.
    const ActivityStatus GetActivityStatus() const;
    void SetActivityStatus(ActivityStatus value);

    //## Attribute: VisibilityType%3786DA2F0026
    //    Gives the possibility to disable an activity at runtime.
    const ActivityVisibilityType GetVisibilityType() const;
    void SetVisibilityType(ActivityVisibilityType value);

    //## Attribute: ConnectedUser%37874A290258
    //    Contains the connected user.
    const CString GetConnectedUser() const;
    void SetConnectedUser(CString value);

    //## Attribute: DaysForBackupResources%37B850C9019F
    //    Defines the number of day for which the activity is
    //    assigned to backup resources.
    const size_t GetDaysForBackupResources() const;
    void SetDaysForBackupResources(size_t value);

    //## Attribute: UseBackupResources%37B850F403A9
    //    Defines if the system should use backup resources.
    const BOOL GetUseBackupResources() const;
    void SetUseBackupResources(BOOL value);

    //## Attribute: RemindDays%37B851120013
    //    Defines the number of days for reminding the user.
    const size_t GetRemindDays() const;
    void SetRemindDays(size_t value);

    //## Attribute: IntranetActivity%37B8512703D5
    //    Defines if this activity is executed in the Intranet. If
    //    no, the activity is subject to go outside and therefore,
    //    this activity is not sent over the Intranet through the
    //    message queuing.
    const BOOL GetIntranetActivity() const;
    void SetIntranetActivity(BOOL value);

    //## Attribute: TimeType%37B8521D02F2
    //    Defines the time type.
    const ActivityTimeOutType GetTimeType() const;
    void SetTimeType(ActivityTimeOutType value);

    // Additional Public Declarations
      //## begin ZBaseActivity%3786D911011F.public preserve=yes
    virtual void    SetDefaultProperty();

    //    Contains the choosen activities. It is used when the
    //    process in not choose activity mode.
    CStringArray& GetChoiceActivityArray();

    //    return true if one or more activities have been choose.
    //    Only available when the RunMode is equal to ChoiceRun.
    BOOL IsChoiceActivityDone() const;

    //## Operation: ChoiceActivityRemoveAll%934700761
    //    Remove all activities from the choice activity array.
    BOOL ChoiceActivityRemoveAll();

    //## Operation: ChoiceActivityAdd%934700762
    //    Add an activity to the choice activity array.
    BOOL ChoiceActivityAdd(const CString ActivityName);


    //    Set the visibility of all childs of a process.
    void SetChildVisibility(const EThreeState value);

    //## Operation: MoveActivityDown%935832843
    //    return true if the activity has been correctly moved.
    BOOL MoveActivityDown(const CString ActivityName);

    //## Operation: MoveActivityUp%935832844
    //    return true if the activity has been correctly moved.
    BOOL MoveActivityUp(const CString ActivityName);

    //## Operation: CanActivityMoveDown%935832845
    //    return true if the activity can be moved down.
    BOOL CanActivityMoveDown(const CString ActivityName);

    //## Operation: CanActivityMoveUp%935832846
    //    return true if the activity can be moved up.
    BOOL CanActivityMoveUp(const CString ActivityName);

    //    Set the current activity to a valid activity.
    void SetCurrentActivity(const CString ActivityName);

    //## Operation: SetCurrentActivity%931815525
    //    Set the current activity to a valid activity.
    void SetCurrentActivity(ZBaseActivity* pActivity);

    //## Operation: SetCurrentActivityToNext%931677640
    //    Increment the current activity to the next valid
    //    activity.
    ZBaseActivity* SetCurrentActivityToNext();

    //## Operation: SetCurrentActivityToPrevious%931677641
    //    Decrement the current activity to the previous valid
    //    activity.
    ZBaseActivity* SetCurrentActivityToPrevious();

    //## Operation: GetCurrentActivity%929033126
    ZBaseActivity* GetCurrentActivity() const;

    //## Operation: GetNextValidActivityFromCurrent%932278231
    //    Retreive from the current activity, the next valid
    //    activity.
    ZBaseActivity* GetNextValidActivityFromCurrent();

    //## Operation: GetPreviousValidActivityFromCurrent%932278232
    //    Get from the current activity, the previous valid
    //    activity.
    ZBaseActivity* GetPreviousValidActivityFromCurrent();

    //## Operation: GetNextBaseActivityFromCurrent%932278233
    //    Retreive from the current activity, the next base
    //    activity.
    ZBaseActivity* GetNextBaseActivityFromCurrent();

    //## Operation: GetPreviousBaseActivityFromCurrent%932278234
    //    Get from the current activity, the previous base
    //    activity.
    ZBaseActivity* GetPreviousBaseActivityFromCurrent();

    //## Operation: RemoveActivityAt%935832848
    //    Remove an activity from the array
    BOOL RemoveActivityAt(size_t Index);

    //## Operation: InsertActivityAt%935832849
    //    Add a new activity at a specific position.
    BOOL InsertActivityAt(ZBaseActivity* pActivity, size_t Index);

    //## Operation: AddActivity%913664906
    //    Add a new activity. At the end.
    BOOL AddActivity(ZBaseActivity* Activity);

    //## Operation: AddActivityAfter%913664907
    //    Add a new activity after a specific activity  name.
    BOOL AddActivityAfter(ZBaseActivity* Activity, const CString& ActivityName);

    //## Operation: DeleteActivity%913664908
    //    Delete an activity.
    BOOL DeleteActivity(ZBaseActivity* Activity);

    //## Operation: DeleteActivity%913885071
    //    Delete an activity.
    BOOL DeleteActivity(const CString& ActivityName);

    //## Operation: FindBaseActivity%934700763
    //    Finds a base activity. Returns the pointer to the
    //    activity.
    ZBaseActivity* FindBaseActivity(const CString& ActivityName);

    //## Operation: FindActivity%913664909
    //    Finds an activity. Returns the pointer to the activity.
    ZActivity* FindActivity(const CString& ActivityName);

    //## Operation: AddProcess%932406384
    //    Add a new process. At the end.
    BOOL AddProcess(ZProcess* Process);

    //## Operation: AddProcessAfter%932406385
    //    Add a new process after a specific activity  name.
    BOOL AddProcessAfter(ZProcess* Process, const CString& ActivityName);

    //## Operation: DeleteProcess%932406386
    //    Delete a process.
    BOOL DeleteProcess(ZProcess* Process);

    //## Operation: DeleteProcess%932406387
    //    Delete a process.
    BOOL DeleteProcess(const CString& ProcessName);

    //## Operation: FindProcess%932406388
    //    Finds a process. Returns the pointer to the process.
    ZProcess* FindProcess(const CString& ProcessName);

    //## Operation: RemoveAllActivities%913664910
    void RemoveAllActivities(bool bDeleteActivityPtr = true);

    //## Operation: GetActivityCount%913885069
    //    Return the number of activities.
    size_t GetActivityCount() const;

    //## Operation: GetActivityAt%913885070
    //    Returns the activity at the index position.
    ZBaseActivity* GetActivityAt(int Index) const;

    //## Operation: GetActivityIndex%916175122
    //    Finds an activity. Returns the index of the activity.
    //    Returns -1 if not found.
    int GetActivityIndex(const CString& ActivityName) const;

    //## Operation: SetActivityAt%916175123
    //    Set the activity at the index position.
    BOOL SetActivityAt(int Index, ZBaseActivity* pActivity);

    //## Operation: IsLastActivity%929033123
    //    Return True if it is the last activity.
    BOOL IsLastActivity();

    //## Operation: RecalculateAllLinks%932406379
    //    Recalculates all links for the process
    BOOL RecalculateAllLinks();

    //    Defines the way activities are executed.
    const ActivityRunMode GetRunMode() const;
    void SetRunMode(ActivityRunMode value);

    //## end ZBaseActivity%3786D911011F.public


protected:
    // Data Members for Class Attributes
      //    Recalculates all links for the process.
    ZBaseActivity* RecalculateProcessAllLinks(ZBaseActivity* pParent = NULL, ZBaseActivity* pNextOfParent = NULL);


    // Contains activities
    CObArray m_ActivityArray;
    // The run mode of the base activity
    // When an activity has a link to several activities,
    // the run mode is set to parallel
    ActivityRunMode m_RunMode;

    // Contains the current activity pointer.
    ZBaseActivity* m_pCurrentActivity;

    CStringArray m_ChoiceActivityArray;

    WORD m_ActivityType;

    //## begin ZBaseActivity::StartDate%3786D98F02C5.attr preserve=no  public: ZBDate {U} 
    PSS_Date m_StartDate;
    //## end ZBaseActivity::StartDate%3786D98F02C5.attr

    //## begin ZBaseActivity::EndDate%3786D99402C2.attr preserve=no  public: ZBDate {U} 
    PSS_Date m_EndDate;
    //## end ZBaseActivity::EndDate%3786D99402C2.attr

    //## begin ZBaseActivity::ForecastedEndDate%3786D99903AF.attr preserve=no  public: ZBDate {U} 
    PSS_Date m_ForecastedEndDate;
    //## end ZBaseActivity::ForecastedEndDate%3786D99903AF.attr

    //## begin ZBaseActivity::ForecastedStartDate%3786ECE40361.attr preserve=no  public: ZBDate {U} 
    PSS_Date m_ForecastedStartDate;
    //## end ZBaseActivity::ForecastedStartDate%3786ECE40361.attr

    //## begin ZBaseActivity::LastUpdateDate%3786D9A000AC.attr preserve=no  public: ZBDate {U} 
    PSS_Date m_LastUpdateDate;
    //## end ZBaseActivity::LastUpdateDate%3786D9A000AC.attr

    //## Attribute: DurationDays%3786D9B500DF
    //    Defines the number of days within the process should be
    //    done.
    //## begin ZBaseActivity::DurationDays%3786D9B500DF.attr preserve=no  public: WORD {U} 2
    WORD m_DurationDays;
    //## end ZBaseActivity::DurationDays%3786D9B500DF.attr

    //## begin ZBaseActivity::Name%3786D9C7031F.attr preserve=no  public: CString {U} 
    CString m_Name;
    //## end ZBaseActivity::Name%3786D9C7031F.attr

    //## begin ZBaseActivity::Description%3786D9CB03CF.attr preserve=no  public: CString {U} 
    CString m_Description;
    //## end ZBaseActivity::Description%3786D9CB03CF.attr

    //## begin ZBaseActivity::Comment%37DBD25B0368.attr preserve=no  public: CString {U} 
    CString m_Comment;
    //## end ZBaseActivity::Comment%37DBD25B0368.attr

    //## begin ZBaseActivity::Initiator%3786D9FD036D.attr preserve=no  public: CString {U} 
    CString m_Initiator;
    //## end ZBaseActivity::Initiator%3786D9FD036D.attr

    //## begin ZBaseActivity::ActivityStatus%3786DA0902CA.attr preserve=no  public: ActivityStatus {U} 
    ActivityStatus m_ActivityStatus;
    //## end ZBaseActivity::ActivityStatus%3786DA0902CA.attr

    //## begin ZBaseActivity::VisibilityType%3786DA2F0026.attr preserve=no  public: ActivityVisibilityType {U} Visible
    ActivityVisibilityType m_VisibilityType;
    //## end ZBaseActivity::VisibilityType%3786DA2F0026.attr

    //## begin ZBaseActivity::ConnectedUser%37874A290258.attr preserve=no  public: CString {U} 
    CString m_ConnectedUser;
    //## end ZBaseActivity::ConnectedUser%37874A290258.attr

    //## Attribute: pNextActivity%37916B5B008B
    //    The pointer to the next activity. If no next activity,
    //    NULL.
    //## begin ZBaseActivity::pNextActivity%37916B5B008B.attr preserve=no  protected: ZBaseActivity* {U} NULL
    ZBaseActivity* m_pNextActivity;
    //## end ZBaseActivity::pNextActivity%37916B5B008B.attr

    //## Attribute: pPreviousActivity%37916BAF01C3
    //    The pointer to the previous activity. If no previous
    //    activity, NULL.
    //## begin ZBaseActivity::pPreviousActivity%37916BAF01C3.attr preserve=no  protected: ZBaseActivity* {U} NULL
    ZBaseActivity* m_pPreviousActivity;
    //## end ZBaseActivity::pPreviousActivity%37916BAF01C3.attr

    //## Attribute: PrincipalResources%37B850D6000D
    //    Contains the principal resource object.
    //## begin ZBaseActivity::PrincipalResources%37B850D6000D.attr preserve=no  public: ZBResources {U} 
    ZBResources m_PrincipalResources;
    //## end ZBaseActivity::PrincipalResources%37B850D6000D.attr

    //## Attribute: BackupResources%37B850DF01F1
    //    Contains the backup resource object.
    //## begin ZBaseActivity::BackupResources%37B850DF01F1.attr preserve=no  public: ZBResources {U} 
    ZBResources m_BackupResources;
    //## end ZBaseActivity::BackupResources%37B850DF01F1.attr

    //## Attribute: pParent%37CD751202C9
    //    Points to the parent process
    //## begin ZBaseActivity::pParent%37CD751202C9.attr preserve=no  protected: ZProcess* {U} 
    ZBaseActivity* m_pParent;
    //## end ZBaseActivity::pParent%37CD751202C9.attr

  // Additional Protected Declarations
    //## begin ZBaseActivity%3786D911011F.protected preserve=yes
    //## end ZBaseActivity%3786D911011F.protected

private:
    // Data Members for Class Attributes

      //## begin ZBaseActivity::IsVisible%37B5237800C0.attr preserve=no  public: ThreeState {U} UndefinedState
    EThreeState m_IsVisible;
    //## end ZBaseActivity::IsVisible%37B5237800C0.attr

    //## begin ZBaseActivity::DaysForBackupResources%37B850C9019F.attr preserve=no  public: size_t {U} 
    size_t m_DaysForBackupResources;
    //## end ZBaseActivity::DaysForBackupResources%37B850C9019F.attr

    //## begin ZBaseActivity::UseBackupResources%37B850F403A9.attr preserve=no  public: BOOL {U} 
    BOOL m_UseBackupResources;
    //## end ZBaseActivity::UseBackupResources%37B850F403A9.attr

    //## Attribute: IsInBackupProcess%37B850FC03E7
    //    Defines if the process is currently in backup process.
    //## begin ZBaseActivity::IsInBackupProcess%37B850FC03E7.attr preserve=no  public: BOOL {U} 
    BOOL m_IsInBackupProcess;
    //## end ZBaseActivity::IsInBackupProcess%37B850FC03E7.attr

    //## begin ZBaseActivity::RemindDays%37B851120013.attr preserve=no  public: size_t {U} 
    size_t m_RemindDays;
    //## end ZBaseActivity::RemindDays%37B851120013.attr

    //## begin ZBaseActivity::IntranetActivity%37B8512703D5.attr preserve=no  public: BOOL {U} TRUE
    BOOL m_IntranetActivity;
    //## end ZBaseActivity::IntranetActivity%37B8512703D5.attr

    //## begin ZBaseActivity::TimeType%37B8521D02F2.attr preserve=no  public: ActivityTimeOutType {U} 
    ActivityTimeOutType m_TimeType;
    //## end ZBaseActivity::TimeType%37B8521D02F2.attr

  // Additional Private Declarations
    //## begin ZBaseActivity%3786D911011F.private preserve=yes
    //## end ZBaseActivity%3786D911011F.private

private:  //## implementation
    // Copy constructor.
    ZBaseActivity(const ZBaseActivity& src);
    // Assignment operator.
    ZBaseActivity& operator=(const ZBaseActivity& src);

};

//## begin ZBaseActivity%3786D911011F.postscript preserve=yes
//#undef  AFX_DATA
//#define AFX_DATA
//## end ZBaseActivity%3786D911011F.postscript

// Class ZBaseActivity 


inline const WORD ZBaseActivity::GetActivityType() const
{
    return m_ActivityType;
}



inline size_t ZBaseActivity::GetActivityCount() const
{
    //## begin ZProcess::GetActivityCount%913885069.body preserve=yes
    return m_ActivityArray.GetSize();
    //## end ZProcess::GetActivityCount%913885069.body
}

inline ZBaseActivity* ZBaseActivity::GetActivityAt(int Index) const
{
    //## begin ZProcess::GetActivityAt%913885070.body preserve=yes
    if (Index < (int)GetActivityCount())
        return (ZBaseActivity*)m_ActivityArray.GetAt(Index);
    return NULL;
    //## end ZProcess::GetActivityAt%913885070.body
}

inline ZBaseActivity* ZBaseActivity::GetCurrentActivity() const
{
    //## begin ZProcess::GetCurrentActivity%929033126.body preserve=yes
    return m_pCurrentActivity;
    //## end ZProcess::GetCurrentActivity%929033126.body
}

inline BOOL ZBaseActivity::IsLastActivity()
{
    //## begin ZProcess::IsLastActivity%929033123.body preserve=yes
    return (m_pCurrentActivity && m_pCurrentActivity->GetNextValidBaseActivity()) ? FALSE : TRUE;
    //## end ZProcess::IsLastActivity%929033123.body
}

inline BOOL ZBaseActivity::IsChoiceActivityDone() const
{
    //## begin ZProcess::IsChoiceActivityDone%934700760.body preserve=yes
    if (m_RunMode == SequenceRun)
        return FALSE;
    return m_ChoiceActivityArray.GetSize() > 0;
    //## end ZProcess::IsChoiceActivityDone%934700760.body
}

inline BOOL ZBaseActivity::ChoiceActivityRemoveAll()
{
    //## begin ZProcess::ChoiceActivityRemoveAll%934700761.body preserve=yes
    m_ChoiceActivityArray.RemoveAll();
    return m_ChoiceActivityArray.GetSize() == 0;
    //## end ZProcess::ChoiceActivityRemoveAll%934700761.body
}

inline CStringArray& ZBaseActivity::GetChoiceActivityArray()
{
    //## begin ZProcess::GetChoiceActivityArray%37B51FAB03B0.get preserve=no
    return m_ChoiceActivityArray;
    //## end ZProcess::GetChoiceActivityArray%37B51FAB03B0.get
}


//## Other Operations (inline)
inline ZBaseActivity* ZBaseActivity::GetNextBaseActivity() const
{
    //## begin ZBaseActivity::GetNextBaseActivity%932278202.body preserve=yes
    return m_pNextActivity;
    //## end ZBaseActivity::GetNextBaseActivity%932278202.body
}

inline ZBaseActivity* ZBaseActivity::GetPreviousBaseActivity() const
{
    //## begin ZBaseActivity::GetPreviousBaseActivity%932278203.body preserve=yes
    return m_pPreviousActivity;
    //## end ZBaseActivity::GetPreviousBaseActivity%932278203.body
}

inline void ZBaseActivity::AddUser(const CString UserName)
{
    //## begin ZBaseActivity::AddUser%931585020.body preserve=yes
    m_PrincipalResources.AddUser(UserName);
    //## end ZBaseActivity::AddUser%931585020.body
}

inline BOOL ZBaseActivity::RemoveUser(const CString& UserName)
{
    //## begin ZBaseActivity::RemoveUser%931585021.body preserve=yes
    return m_PrincipalResources.RemoveUser(UserName);
    //## end ZBaseActivity::RemoveUser%931585021.body
}

inline BOOL ZBaseActivity::UserExist(const CString& UserName)
{
    //## begin ZBaseActivity::UserExist%931585022.body preserve=yes
    return m_PrincipalResources.UserExist(UserName);
    //## end ZBaseActivity::UserExist%931585022.body
}

inline size_t ZBaseActivity::GetUserCount()
{
    //## begin ZBaseActivity::GetUserCount%931585023.body preserve=yes
    return m_PrincipalResources.GetUserCount();
    //## end ZBaseActivity::GetUserCount%931585023.body
}

inline void ZBaseActivity::RemoveAllUsers()
{
    //## begin ZBaseActivity::RemoveAllUsers%931585024.body preserve=yes
    m_PrincipalResources.RemoveAllUsers();
    //## end ZBaseActivity::RemoveAllUsers%931585024.body
}

inline CString ZBaseActivity::GetUserAt(int Index)
{
    //## begin ZBaseActivity::GetUserAt%931585025.body preserve=yes
    if (Index < (int)GetUserCount())
        return m_PrincipalResources.GetUserAt(Index);
    return "";
    //## end ZBaseActivity::GetUserAt%931585025.body
}

inline void ZBaseActivity::AddBackupUser(const CString UserName)
{
    //## begin ZBaseActivity::AddBackupUser%931585026.body preserve=yes
    m_BackupResources.AddUser(UserName);
    //## end ZBaseActivity::AddBackupUser%931585026.body
}

inline BOOL ZBaseActivity::RemoveBackupUser(const CString& UserName)
{
    //## begin ZBaseActivity::RemoveBackupUser%931585027.body preserve=yes
    return m_BackupResources.RemoveUser(UserName);
    //## end ZBaseActivity::RemoveBackupUser%931585027.body
}

inline BOOL ZBaseActivity::BackupUserExist(const CString& UserName)
{
    //## begin ZBaseActivity::BackupUserExist%931585028.body preserve=yes
    return m_BackupResources.UserExist(UserName);
    //## end ZBaseActivity::BackupUserExist%931585028.body
}

inline size_t ZBaseActivity::GetBackupUserCount()
{
    //## begin ZBaseActivity::GetBackupUserCount%931585029.body preserve=yes
    return m_BackupResources.GetUserCount();
    //## end ZBaseActivity::GetBackupUserCount%931585029.body
}

inline void ZBaseActivity::RemoveAllBackupUsers()
{
    //## begin ZBaseActivity::RemoveAllBackupUsers%931585030.body preserve=yes
    m_BackupResources.RemoveAllUsers();
    //## end ZBaseActivity::RemoveAllBackupUsers%931585030.body
}

inline CString ZBaseActivity::GetBackupUserAt(int Index)
{
    //## begin ZBaseActivity::GetBackupUserAt%931585031.body preserve=yes
    if (Index < (int)GetBackupUserCount())
        return m_BackupResources.GetUserAt(Index);
    return "";
    //## end ZBaseActivity::GetBackupUserAt%931585031.body
}

inline CString ZBaseActivity::GetAttributedByActivity() const
{
    //## begin ZBaseActivity::GetAttributedByActivity%931585032.body preserve=yes
    return "";
    //## end ZBaseActivity::GetAttributedByActivity%931585032.body
}

inline void ZBaseActivity::SetAttributedByActivity(const CString value)
{
    //## begin ZBaseActivity::SetAttributedByActivity%931585033.body preserve=yes
    //## end ZBaseActivity::SetAttributedByActivity%931585033.body
}

inline BOOL ZBaseActivity::ActivityIsAttribution()
{
    //## begin ZBaseActivity::ActivityIsAttribution%931613263.body preserve=yes
      // If no activites or If it is parallel mode
    if (!HasActivities() || (HasActivities() && GetRunMode() == ChooseMode))
        return ((m_ActivityType & ActivityTypeAttribution) > 0) ? TRUE : FALSE;
    // Else, check the current activity
    if (!GetCurrentActivity())
        return FALSE;
    return GetCurrentActivity()->ActivityIsAttribution();
    //## end ZBaseActivity::ActivityIsAttribution%931613263.body
}

inline BOOL ZBaseActivity::ActivityIsAcceptation()
{
    //## begin ZBaseActivity::ActivityIsAcceptation%931613264.body preserve=yes
      // If no activites or If it is parallel mode
    if (!HasActivities() || (HasActivities() && GetRunMode() == ChooseMode))
        return ((m_ActivityType & ActivityTypeAcceptation) > 0) ? TRUE : FALSE;
    if (!GetCurrentActivity())
        return FALSE;
    return GetCurrentActivity()->ActivityIsAcceptation();
    //## end ZBaseActivity::ActivityIsAcceptation%931613264.body
}

inline BOOL ZBaseActivity::ActivityIsInput()
{
    //## begin ZBaseActivity::ActivityIsInput%931613265.body preserve=yes
      // If no activites or If it is parallel mode
    if (!HasActivities() || (HasActivities() && GetRunMode() == ChooseMode))
        return ((m_ActivityType & ActivityTypeInputInformation) > 0) ? TRUE : FALSE;
    if (!GetCurrentActivity())
        return FALSE;
    return GetCurrentActivity()->ActivityIsInput();
    //## end ZBaseActivity::ActivityIsInput%931613265.body
}

inline BOOL ZBaseActivity::ActivityIsSendMail()
{
    //## begin ZBaseActivity::ActivityIsSendMail%931613266.body preserve=yes
      // If no activites or If it is parallel mode
    if (!HasActivities() || (HasActivities() && GetRunMode() == ChooseMode))
        return ((m_ActivityType & ActivityTypeSendMail) > 0) ? TRUE : FALSE;
    if (!GetCurrentActivity())
        return FALSE;
    return GetCurrentActivity()->ActivityIsSendMail();
    //## end ZBaseActivity::ActivityIsSendMail%931613266.body
}

inline BOOL ZBaseActivity::ActivityIsStartProcess()
{
    //## begin ZBaseActivity::ActivityIsStartProcess%931613267.body preserve=yes
      // If no activites or If it is parallel mode
    if (!HasActivities() || (HasActivities() && GetRunMode() == ChooseMode))
        return ((m_ActivityType & ActivityTypeStartProcess) > 0) ? TRUE : FALSE;
    if (!GetCurrentActivity())
        return FALSE;
    return GetCurrentActivity()->ActivityIsStartProcess();
    //## end ZBaseActivity::ActivityIsStartProcess%931613267.body
}

inline BOOL ZBaseActivity::ActivityIsCommandLine()
{
    //## begin ZBaseActivity::ActivityIsCommandLine%931613268.body preserve=yes
      // If no activites or If it is parallel mode
    if (!HasActivities() || (HasActivities() && GetRunMode() == ChooseMode))
        return ((m_ActivityType & ActivityTypeCommandLine) > 0) ? TRUE : FALSE;
    if (!GetCurrentActivity())
        return FALSE;
    return GetCurrentActivity()->ActivityIsCommandLine();
    //## end ZBaseActivity::ActivityIsCommandLine%931613268.body
}

inline BOOL ZBaseActivity::ActivityIsScanning()
{
    //## begin ZBaseActivity::ActivityIsScanning%940156895.body preserve=yes
      // If no activites or If it is parallel mode
    if (!HasActivities() || (HasActivities() && GetRunMode() == ChooseMode))
        return ((m_ActivityType & ActivityTypeScanning) > 0) ? TRUE : FALSE;
    if (!GetCurrentActivity())
        return FALSE;
    return GetCurrentActivity()->ActivityIsScanning();
    //## end ZBaseActivity::ActivityIsScanning%940156895.body
}

inline BOOL ZBaseActivity::ActivityIsArchiving()
{
    //## begin ZBaseActivity::ActivityIsArchiving%940156896.body preserve=yes
      // If no activites or If it is parallel mode
    if (!HasActivities() || (HasActivities() && GetRunMode() == ChooseMode))
        return ((m_ActivityType & ActivityTypeArchiving) > 0) ? TRUE : FALSE;
    if (!GetCurrentActivity())
        return FALSE;
    return GetCurrentActivity()->ActivityIsArchiving();
    //## end ZBaseActivity::ActivityIsArchiving%940156896.body
}

inline void ZBaseActivity::AssignNextActivityPtr(ZBaseActivity* Ptr)
{
    //## begin ZBaseActivity::AssignNextActivityPtr%932406382.body preserve=yes
    m_pNextActivity = Ptr;
    //## end ZBaseActivity::AssignNextActivityPtr%932406382.body
}

inline void ZBaseActivity::AssignPreviousActivityPtr(ZBaseActivity* Ptr)
{
    //## begin ZBaseActivity::AssignPreviousActivityPtr%932406383.body preserve=yes
    m_pPreviousActivity = Ptr;
    //## end ZBaseActivity::AssignPreviousActivityPtr%932406383.body
}

inline BOOL ZBaseActivity::IsUserAttributionDone()
{
    //## begin ZBaseActivity::IsUserAttributionDone%934825328.body preserve=yes
    return GetUserCount() > 0;
    //## end ZBaseActivity::IsUserAttributionDone%934825328.body
}

inline BOOL ZBaseActivity::IsTimeAttributionDone()
{
    //## begin ZBaseActivity::IsTimeAttributionDone%934825329.body preserve=yes
    return GetDurationDays() > 0;
    //## end ZBaseActivity::IsTimeAttributionDone%934825329.body
}

inline BOOL ZBaseActivity::IsVisibilityAttributionDone()
{
    //## begin ZBaseActivity::IsVisibilityAttributionDone%935005730.body preserve=yes
    return GetIsVisible() != E_TS_Undefined;
    //## end ZBaseActivity::IsVisibilityAttributionDone%935005730.body
}

inline BOOL ZBaseActivity::IsAttributedActivity() const
{
    //## begin ZBaseActivity::IsAttributedActivity%934825330.body preserve=yes
    return    m_PrincipalResources.GetUserType() == AttributionOfUsers ||
        m_BackupResources.GetUserType() == AttributionOfUsers ||
        GetTimeType() == AttributionOfTimeOut ||
        GetVisibilityType() == AttributionOfVisibility;
    //## end ZBaseActivity::IsAttributedActivity%934825330.body
}

inline BOOL ZBaseActivity::IsInBackupProcess() const
{
    //## begin ZBaseActivity::IsInBackupProcess%934825331.body preserve=yes
    return m_IsInBackupProcess;
    //## end ZBaseActivity::IsInBackupProcess%934825331.body
}

inline void ZBaseActivity::SetIsInBackupProcess(BOOL value)
{
    //## begin ZBaseActivity::SetIsInBackupProcess%934825332.body preserve=yes
    m_IsInBackupProcess = value;
    //## end ZBaseActivity::SetIsInBackupProcess%934825332.body
}

inline ActivityUserType ZBaseActivity::GetUserType() const
{
    //## begin ZBaseActivity::GetUserType%934825333.body preserve=yes
    return m_PrincipalResources.GetUserType();
    //## end ZBaseActivity::GetUserType%934825333.body
}

inline void ZBaseActivity::SetUserType(ActivityUserType value)
{
    //## begin ZBaseActivity::SetUserType%934825334.body preserve=yes
    m_PrincipalResources.SetUserType(value);
    //## end ZBaseActivity::SetUserType%934825334.body
}

inline ActivityUserType ZBaseActivity::GetBackupUserType() const
{
    //## begin ZBaseActivity::GetBackupUserType%934825335.body preserve=yes
    return m_BackupResources.GetUserType();
    //## end ZBaseActivity::GetBackupUserType%934825335.body
}

inline void ZBaseActivity::SetBackupUserType(ActivityUserType value)
{
    //## begin ZBaseActivity::SetBackupUserType%934825336.body preserve=yes
    m_BackupResources.SetUserType(value);
    //## end ZBaseActivity::SetBackupUserType%934825336.body
}

inline ZBResources& ZBaseActivity::GetCurrentResources()
{
    //## begin ZBaseActivity::GetCurrentResources%934825337.body preserve=yes
    return (IsInBackupProcess()) ? m_BackupResources : m_PrincipalResources;
    //## end ZBaseActivity::GetCurrentResources%934825337.body
}

inline EThreeState ZBaseActivity::IsConsiderAsVisible() const
{
    //## begin ZBaseActivity::IsConsiderAsVisible%935005731.body preserve=yes
    if (GetIsVisible() == E_TS_Undefined)
        return E_TS_Undefined;
    else
        if ((GetVisibilityType() == AttributionOfVisibility && GetIsVisible() == E_TS_True) ||
            GetVisibilityType() == Visible)
            return E_TS_True;
        else
            if ((GetVisibilityType() == AttributionOfVisibility && GetIsVisible() == E_TS_False) ||
                GetVisibilityType() == Invisible)
                return E_TS_False;
    return E_TS_Undefined;
    //## end ZBaseActivity::IsConsiderAsVisible%935005731.body
}

inline void ZBaseActivity::SetVisibility(const EThreeState value)
{
    //## begin ZBaseActivity::SetVisibility%935776835.body preserve=yes
    m_IsVisible = value;
    //## end ZBaseActivity::SetVisibility%935776835.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const EThreeState& ZBaseActivity::GetIsVisible() const
{
    //## begin ZBaseActivity::GetIsVisible%37B5237800C0.get preserve=no
    return m_IsVisible;
    //## end ZBaseActivity::GetIsVisible%37B5237800C0.get
}

inline const PSS_Date ZBaseActivity::GetStartDate() const
{
    //## begin ZBaseActivity::GetStartDate%3786D98F02C5.get preserve=no
    return m_StartDate;
    //## end ZBaseActivity::GetStartDate%3786D98F02C5.get
}

inline void ZBaseActivity::SetStartDate(PSS_Date value)
{
    //## begin ZBaseActivity::SetStartDate%3786D98F02C5.set preserve=no
    m_StartDate = value;
    //## end ZBaseActivity::SetStartDate%3786D98F02C5.set
}

inline const PSS_Date ZBaseActivity::GetEndDate() const
{
    //## begin ZBaseActivity::GetEndDate%3786D99402C2.get preserve=no
    return m_EndDate;
    //## end ZBaseActivity::GetEndDate%3786D99402C2.get
}

inline void ZBaseActivity::SetEndDate(PSS_Date value)
{
    //## begin ZBaseActivity::SetEndDate%3786D99402C2.set preserve=no
    m_EndDate = value;
    //## end ZBaseActivity::SetEndDate%3786D99402C2.set
}

inline const PSS_Date ZBaseActivity::GetForecastedEndDate() const
{
    //## begin ZBaseActivity::GetForecastedEndDate%3786D99903AF.get preserve=no
    return m_ForecastedEndDate;
    //## end ZBaseActivity::GetForecastedEndDate%3786D99903AF.get
}

inline void ZBaseActivity::SetForecastedEndDate(PSS_Date value)
{
    //## begin ZBaseActivity::SetForecastedEndDate%3786D99903AF.set preserve=no
    m_ForecastedEndDate = value;
    //## end ZBaseActivity::SetForecastedEndDate%3786D99903AF.set
}

inline const PSS_Date ZBaseActivity::GetForecastedStartDate() const
{
    //## begin ZBaseActivity::GetForecastedStartDate%3786ECE40361.get preserve=no
    return m_ForecastedStartDate;
    //## end ZBaseActivity::GetForecastedStartDate%3786ECE40361.get
}

inline void ZBaseActivity::SetForecastedStartDate(PSS_Date value)
{
    //## begin ZBaseActivity::SetForecastedStartDate%3786ECE40361.set preserve=no
    m_ForecastedStartDate = value;
    //## end ZBaseActivity::SetForecastedStartDate%3786ECE40361.set
}

inline const PSS_Date ZBaseActivity::GetLastUpdateDate() const
{
    //## begin ZBaseActivity::GetLastUpdateDate%3786D9A000AC.get preserve=no
    return m_LastUpdateDate;
    //## end ZBaseActivity::GetLastUpdateDate%3786D9A000AC.get
}

inline void ZBaseActivity::SetLastUpdateDate(PSS_Date value)
{
    //## begin ZBaseActivity::SetLastUpdateDate%3786D9A000AC.set preserve=no
    m_LastUpdateDate = value;
    //## end ZBaseActivity::SetLastUpdateDate%3786D9A000AC.set
}

inline const CString& ZBaseActivity::GetName() const
{
    //## begin ZBaseActivity::GetName%3786D9C7031F.get preserve=no
    return m_Name;
    //## end ZBaseActivity::GetName%3786D9C7031F.get
}

inline void ZBaseActivity::SetName(const CString& value)
{
    //## begin ZBaseActivity::SetName%3786D9C7031F.set preserve=no
    m_Name = value;
    //## end ZBaseActivity::SetName%3786D9C7031F.set
}

inline const CString& ZBaseActivity::GetDescription() const
{
    //## begin ZBaseActivity::GetDescription%3786D9CB03CF.get preserve=no
    return m_Description;
    //## end ZBaseActivity::GetDescription%3786D9CB03CF.get
}

inline void ZBaseActivity::SetDescription(const CString& value)
{
    //## begin ZBaseActivity::SetDescription%3786D9CB03CF.set preserve=no
    m_Description = value;
    //## end ZBaseActivity::SetDescription%3786D9CB03CF.set
}

inline const CString& ZBaseActivity::GetComment() const
{
    //## begin ZBaseActivity::GetComment%37DBD25B0368.get preserve=no
    return m_Comment;
    //## end ZBaseActivity::GetComment%37DBD25B0368.get
}

inline void ZBaseActivity::SetComment(const CString& value)
{
    //## begin ZBaseActivity::SetComment%37DBD25B0368.set preserve=no
    m_Comment = value;
    //## end ZBaseActivity::SetComment%37DBD25B0368.set
}

inline const CString& ZBaseActivity::GetInitiator() const
{
    //## begin ZBaseActivity::GetInitiator%3786D9FD036D.get preserve=no
    return m_Initiator;
    //## end ZBaseActivity::GetInitiator%3786D9FD036D.get
}

inline void ZBaseActivity::SetInitiator(const CString& value)
{
    //## begin ZBaseActivity::SetInitiator%3786D9FD036D.set preserve=no
    m_Initiator = value;
    //## end ZBaseActivity::SetInitiator%3786D9FD036D.set
}

inline const ActivityStatus ZBaseActivity::GetActivityStatus() const
{
    //## begin ZBaseActivity::GetActivityStatus%3786DA0902CA.get preserve=no
    return m_ActivityStatus;
    //## end ZBaseActivity::GetActivityStatus%3786DA0902CA.get
}

inline void ZBaseActivity::SetActivityStatus(ActivityStatus value)
{
    //## begin ZBaseActivity::SetActivityStatus%3786DA0902CA.set preserve=no
    m_ActivityStatus = value;
    //## end ZBaseActivity::SetActivityStatus%3786DA0902CA.set
}

inline const ActivityVisibilityType ZBaseActivity::GetVisibilityType() const
{
    //## begin ZBaseActivity::GetVisibilityType%3786DA2F0026.get preserve=no
    return m_VisibilityType;
    //## end ZBaseActivity::GetVisibilityType%3786DA2F0026.get
}

inline void ZBaseActivity::SetVisibilityType(ActivityVisibilityType value)
{
    //## begin ZBaseActivity::SetVisibilityType%3786DA2F0026.set preserve=no
    m_VisibilityType = value;
    //## end ZBaseActivity::SetVisibilityType%3786DA2F0026.set
}

inline const CString ZBaseActivity::GetConnectedUser() const
{
    //## begin ZBaseActivity::GetConnectedUser%37874A290258.get preserve=no
    return m_ConnectedUser;
    //## end ZBaseActivity::GetConnectedUser%37874A290258.get
}

inline void ZBaseActivity::SetConnectedUser(CString value)
{
    //## begin ZBaseActivity::SetConnectedUser%37874A290258.set preserve=no
    m_ConnectedUser = value;
    //## end ZBaseActivity::SetConnectedUser%37874A290258.set
}

inline const size_t ZBaseActivity::GetDaysForBackupResources() const
{
    //## begin ZBaseActivity::GetDaysForBackupResources%37B850C9019F.get preserve=no
    return m_DaysForBackupResources;
    //## end ZBaseActivity::GetDaysForBackupResources%37B850C9019F.get
}

inline void ZBaseActivity::SetDaysForBackupResources(size_t value)
{
    //## begin ZBaseActivity::SetDaysForBackupResources%37B850C9019F.set preserve=no
    m_DaysForBackupResources = value;
    //## end ZBaseActivity::SetDaysForBackupResources%37B850C9019F.set
}

inline const BOOL ZBaseActivity::GetUseBackupResources() const
{
    //## begin ZBaseActivity::GetUseBackupResources%37B850F403A9.get preserve=no
    return m_UseBackupResources;
    //## end ZBaseActivity::GetUseBackupResources%37B850F403A9.get
}

inline void ZBaseActivity::SetUseBackupResources(BOOL value)
{
    //## begin ZBaseActivity::SetUseBackupResources%37B850F403A9.set preserve=no
    m_UseBackupResources = value;
    //## end ZBaseActivity::SetUseBackupResources%37B850F403A9.set
}

inline const size_t ZBaseActivity::GetRemindDays() const
{
    //## begin ZBaseActivity::GetRemindDays%37B851120013.get preserve=no
    return m_RemindDays;
    //## end ZBaseActivity::GetRemindDays%37B851120013.get
}

inline void ZBaseActivity::SetRemindDays(size_t value)
{
    //## begin ZBaseActivity::SetRemindDays%37B851120013.set preserve=no
    m_RemindDays = value;
    //## end ZBaseActivity::SetRemindDays%37B851120013.set
}

inline const BOOL ZBaseActivity::GetIntranetActivity() const
{
    //## begin ZBaseActivity::GetIntranetActivity%37B8512703D5.get preserve=no
    return m_IntranetActivity;
    //## end ZBaseActivity::GetIntranetActivity%37B8512703D5.get
}

inline void ZBaseActivity::SetIntranetActivity(BOOL value)
{
    //## begin ZBaseActivity::SetIntranetActivity%37B8512703D5.set preserve=no
    m_IntranetActivity = value;
    //## end ZBaseActivity::SetIntranetActivity%37B8512703D5.set
}

inline const ActivityTimeOutType ZBaseActivity::GetTimeType() const
{
    //## begin ZBaseActivity::GetTimeType%37B8521D02F2.get preserve=no
    return m_TimeType;
    //## end ZBaseActivity::GetTimeType%37B8521D02F2.get
}

inline void ZBaseActivity::SetTimeType(ActivityTimeOutType value)
{
    //## begin ZBaseActivity::SetTimeType%37B8521D02F2.set preserve=no
    m_TimeType = value;
    //## end ZBaseActivity::SetTimeType%37B8521D02F2.set
}

inline const ActivityRunMode ZBaseActivity::GetRunMode() const
{
    //## begin ZProcess::GetRunMode%37A2AA430062.get preserve=no
    return m_RunMode;
    //## end ZProcess::GetRunMode%37A2AA430062.get
}

inline void ZBaseActivity::SetRunMode(ActivityRunMode value)
{
    //## begin ZProcess::SetRunMode%37A2AA430062.set preserve=no
    m_RunMode = value;
    //## end ZProcess::SetRunMode%37A2AA430062.set
}

inline bool    ZBaseActivity::HasActivities() const
{
    return ((GetActivityCount() > 0) ? true : false);
}

#endif
