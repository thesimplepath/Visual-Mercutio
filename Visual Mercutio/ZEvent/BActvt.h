/****************************************************************************
 * ==> PSS_BaseActivity ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic activity interface                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BaseActivityH
#define PSS_BaseActivityH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_BaseActivity
    #define PSS_BaseActivity ZBaseActivity
#endif

// mfc
#include "Mfc.h"

// processsoft
#include "zBaseLib\PSS_SmartPtr.h"
#include "zBaseLib\PSS_Date.h"
#include "zBaseLib\PSS_MailUserList.h"

// resources
#include "zResourc.h"

// class name mapping
#ifndef PSS_Activity
    #define PSS_Activity ZActivity
#endif

// forward class declarations
class PSS_Activity;
class ZProcess;

#ifdef _ZEVENTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const char g_ActivityTypeInputInformationKey[]  = "ActInp";
const char g_ActivityTypeAcceptationKey[]       = "ActAcpt";
const char g_ActivityTypeAttributionKey[]       = "ActAttr";
const char g_ActivityTypeSendMailKey[]          = "ActSndM";
const char g_ActivityTypeStartProcessKey[]      = "ActStProc";
const char g_ActivityTypeCommandLineKey[]       = "ActCmd";
const char g_ActivityTypeScanningKey[]          = "ActScan";
const char g_ActivityTypeArchivingKey[]         = "ActArch";
const char g_ActivityStatusProcessStarted[]     = "PrcSt";
const char g_ActivityStatusProcessNotStarted[]  = "PrcNotSt";
const char g_ActivityStatusProcessInProcess[]   = "PrcInProc";
const char g_ActivityStatusProcessPaused[]      = "PrcPause";
const char g_ActivityStatusProcessAborted[]     = "PrcAbort";
const char g_ActivityStatusProcessCompleted[]   = "PrcCmpl";
const char g_ActivityStatusRequestAcceptation[] = "ActRqAcpt";
const char g_ActivityStatusSent[]               = "ActSent";
const char g_ActivityStatusAccepted[]           = "ActAcpt";
const char g_ActivityStatusRejected[]           = "ActRejt";
const char g_ActivityStatusAttribution[]        = "ActAttr";
const char g_ActivityStatusCompleted[]          = "ActCmpl";
const char g_ActivityStatusNotStarted[]         = "ActNotSt";
const char g_ActivityStatusStarted[]            = "ActSt";
const char g_ActivityStatusTakeOwnerShip[]      = "ActTkOwn";
//---------------------------------------------------------------------------

/**
* Basic activity interface (e.g a process is a kind of activity)
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BaseActivity : public CObject
{
    DECLARE_SERIAL(PSS_BaseActivity)

    public:
        /**
        * Activity run mode
        */
        enum IERunMode
        {
            IE_RM_Sequence,
            IE_RM_Select,
            IE_RM_Parallel
        };

        /**
        * Activity visibility type
        */
        enum IEVisibilityType
        {
            IE_VT_Visible,
            IE_VT_Invisible,
            IE_VT_AttributionOfVisibility
        };

        /**
        * Activity timeout type
        */
        enum IETimeoutType
        {
            IE_TT_TimeDays,
            IE_TT_AttributionOfTimeout
        };

        /**
        * Activity type
        */
        enum IEType
        {
            IE_AT_InputInformation = 0x0001,
            IE_AT_Acceptation      = 0x0002,
            IE_AT_Attribution      = 0x0004,
            IE_AT_SendMail         = 0x0008,
            IE_AT_StartProcess     = 0x0010,
            IE_AT_CommandLine      = 0x0020,
            IE_AT_Scanning         = 0x0040,
            IE_AT_Archiving        = 0x0080
        };

        /**
        * Activity status
        */
        enum IEStatus
        {
            IE_AS_Started,
            IE_AS_Sent,
            IE_AS_SentForAcceptation,
            IE_AS_Completed,
            IE_AS_Rejected,
            IE_AS_Suspended,
            IE_AS_Aborted,
            IE_AS_NotStarted
        };

        typedef CObject inherited;

        /**
        * Constructor
        *@param name - activity name
        *@param description - activity description
        *@param status - activity status
        */
        PSS_BaseActivity(const CString& name = "", const CString& description = "", IEStatus status = IE_AS_NotStarted);

        virtual ~PSS_BaseActivity();

        /**
        * Gets the activity type
        *@return the activity type
        */
        virtual inline const WORD GetActivityType() const;

        /**
        * Gets the activitie count
        *@return the activitie count
        */
        virtual inline std::size_t GetActivityCount() const;

        /**
        * Gets the current activity
        *@return the current activity
        */
        virtual inline PSS_BaseActivity* GetCurrentActivity() const;

        /**
        * Gets the activity at index
        *@param index - the index
        *@return the activity at index, NULL if not found or on error
        */
        virtual inline PSS_BaseActivity* GetActivityAt(int index) const;

        /**
        * Gets the parent activity
        *@return the parent activity, NULL if no parent or on error
        */
        virtual PSS_BaseActivity* GetParent() const;

        /**
        * Gets the parent process
        *@return the parent process, NULL if no parent or on error
        */
        virtual ZProcess* GetParentProcess() const;

        /**
        * Checks if activities are defined
        *@return true if activities are defined, otherwise false
        */
        virtual inline bool HasActivities() const;

        /**
        * Gets if the activity is the last one
        *@return TRUE if the activity is the last one, otherwise FALSE
        */
        virtual inline BOOL IsLastActivity();

        /**
        * Gets the first base activity
        *@return the first base activity
        */
        virtual PSS_BaseActivity* GetFirstBaseActivity() const;

        /**
        * Gets the first valid activity
        *@return the first valid activity
        */
        virtual PSS_BaseActivity* GetFirstValidActivity() const;

        /**
        * Gets the first valid base activity
        *@return the first valid base activity
        */
        virtual PSS_BaseActivity* GetFirstValidBaseActivity() const;

        /**
        * Gets the previous base activity
        *@return the previous base activity, NULL if not found or on error
        */
        virtual inline PSS_BaseActivity* GetPreviousBaseActivity() const;

        /**
        * Gets the previous valid ity
        *@return the previous valid activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetPreviousValidActivity() const;

        /**
        * Gets the previous valid base activity
        *@return the previous valid base activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetPreviousValidBaseActivity() const;

        /**
        * Gets the next base activity
        *@return the next base activity, NULL if not found or on error
        */
        virtual inline PSS_BaseActivity* GetNextBaseActivity() const;

        /**
        * Gets the next valid activity
        *@return the next valid activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetNextValidActivity() const;

        /**
        * Gets the next valid base activity
        *@return the next valid base activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetNextValidBaseActivity() const;

        /**
        * Gets the previous process
        *@return the previous process, NULL if not found or on error
        */
        virtual ZProcess* GetPreviousProcess() const;

        /**
        * Gets the next process
        *@return the next process, NULL if not found or on error
        */
        virtual ZProcess* GetNextProcess() const;

        /**
        * Builds a delimited string containing the person list
        *@param userManager - user manager
        *@param connectedUser - connected user
        *@param delimiter - delimiter to use to tokenize the source string
        *@return the user email list, NULL on error
        */
        virtual CString ActivityCreatePersonDelimStr(const PSS_UserManager& userManager,
                                                     const CString&         connectedUser,
                                                     const CString&         delimiter = ";");

        /**
        * Builds an user email list
        *@param userManager - user manager
        *@param connectedUser - connected user
        *@return the user email list, NULL on error
        */
        virtual PSS_MailUserList* ActivityCreatePersonList(const PSS_UserManager& userManager, const CString& connectedUser);

        /**
        * Builds a person email list
        *@param activity - activity from which the list will be get
        *@param userManager - user manager
        *@return the person email list, NULL on error
        */
        virtual PSS_MailUserList* CreatePersonList(const PSS_BaseActivity& activity, const PSS_UserManager& userManager);

        /**
        * Builds a person email list
        *@param index - activity index from which the list will be get
        *@param userManager - user manager
        *@return the person email list, NULL on error
        */
        virtual PSS_MailUserList* CreatePersonList(int index, const PSS_UserManager& userManager);

        /**
        * Build a delimited string containing the person list
        *@param activity - activity from which the list will be get
        *@param userManager - user manager
        *@param delimiter - delimiter to use to tokenize the source string
        *@return the person list delimited string
        */
        virtual CString CreatePersonDelimStr(const PSS_BaseActivity& activity,
                                             const PSS_UserManager&  userManager,
                                             const CString&          delimiter = ";");

        /**
        * Build a delimited string containing the person list
        *@param index - activity index from which the list will be get
        *@param userManager - user manager
        *@param delimiter - delimiter to use to tokenize the source string
        *@return the person list delimited string
        */
        virtual CString CreatePersonDelimStr(int index, const PSS_UserManager& userManager, const CString& delimiter = ";");

        /**
        * Fills a person array
        *@param activity - activity from which the array will be get
        *@param userManager - user manager
        *@param[out] userArray - user array to populate with the result
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL FillPersonArray(const PSS_BaseActivity& activity, const PSS_UserManager& userManager, CStringArray& userArray);

        /**
        * Fills a person array
        *@param index - activity index from which the array will be get
        *@param userManager - user manager
        *@param[out] userArray - user array to populate with the result
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL FillPersonArray(int index, const PSS_UserManager& userManager, CStringArray& userArray);

        /**
        * Fills a person array
        *@param userManager - user manager
        *@param[out] userArray - user array to populate with results
        *@param connectedUser - connected user
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ActivityFillPersonArray(const PSS_UserManager& userManager, CStringArray& userArray, const CString& connectedUser);

        /**
        * Add users
        *@param delimitedString - delimited string containing the users to add
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ActivityAddUsers(const CString& delimitedString);

        /**
        * Add users in main resources
        *@param delimitedString - delimited string containing the users to add
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL MainResourceActivityAddUsers(const CString& delimitedString);

        /**
        * Add users in backup resources
        *@param delimitedString - delimited string containing the users to add
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL BackupResourceActivityAddUsers(const CString& delimitedString);

        /**
        * Fills a person array using the main resources
        *@param userManager - user manager
        *@param[out] userArray - user array to populate with results
        *@param connectedUser - connected user
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL MainResourceActivityFillPersonArray(const PSS_UserManager& userManager,
                                                         CStringArray&          userArray,
                                                         const CString&         connectedUser);

        /**
        * Builds an user email list using the main resources
        *@param userManager - user manager
        *@param connectedUser - connected user
        *@return the user email list, NULL on error
        */
        virtual PSS_MailUserList* MainResourceActivityCreatePersonList(const PSS_UserManager& userManager,
                                                                       const CString&         connectedUser);

        /**
        * Build a delimited string containing the person list using the main resources
        *@param activity - activity from which the list will be get
        *@param userManager - user manager
        *@param delimiter - delimiter to use to tokenize the source string
        *@return the person list delimited string
        */
        virtual CString MainResourceActivityCreatePersonDelimStr(const PSS_UserManager& userManager,
                                                                 const CString&         connectedUser,
                                                                 const CString&         delimiter = ";");

        /**
        * Fills a person array using the backup resources
        *@param userManager - user manager
        *@param[out] userArray - user array to populate with results
        *@param connectedUser - connected user
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL BackupResourceActivityFillPersonArray(const PSS_UserManager& userManager,
                                                           CStringArray&          userArray,
                                                           const CString&         connectedUser);

        /**
        * Builds an user email list using the backup resources
        *@param userManager - user manager
        *@param connectedUser - connected user
        *@return the user email list, NULL on error
        */
        virtual PSS_MailUserList* BackupResourceActivityCreatePersonList(const PSS_UserManager& userManager, const CString& connectedUser);

        /**
        * Build a delimited string containing the person list using the backup resources
        *@param activity - activity from which the list will be get
        *@param userManager - user manager
        *@param delimiter - delimiter to use to tokenize the source string
        *@return the person list delimited string
        */
        virtual CString BackupResourceActivityCreatePersonDelimStr(const PSS_UserManager& userManager,
                                                                   const CString&         connectedUser,
                                                                   const CString&         delimiter = ";");

        /**
        * Calculates the forecasted start date by taking all activities
        */
        virtual void CalculateForecastedStartDate();

        /**
        * Calculates the forecasted end date by taking all activities
        */
        virtual void CalculateForecastedEndDate();

        /**
        * Gets the duration days
        *@return the duration days
        */
        virtual WORD GetDurationDays() const;

        /**
        * Sets the duration days
        *@param value - the duration days
        */
        virtual void SetDurationDays(WORD value);

        /**
        * Gets the status key string
        *@return the status key string
        */
        virtual CString GetStatusKeyString(PSS_BaseActivity* pActivity = NULL);

        /**
        * Sets the status key string
        *@param key - the status key string
        */
        virtual void SetStatusFromKeyString(const CString& key);

        /**
        * Gets the status string
        *@param key - the status key string
        *@return the status string
        */
        static CString GetStatusString(const CString& key);

        /**
        * Adds a new user
        *@param userName - the user name
        */
        virtual inline void AddUser(const CString& userName);

        /**
        * Removes a specific user
        *@param userName - the user name
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL RemoveUser(const CString& userName);

        /**
        * Removes all the users
        */
        virtual inline void RemoveAllUsers();

        /**
        * Searches if an user exists
        *@param userName - the user name
        *@return TRUE if the user exists, otherwise FALSE
        */
        virtual inline BOOL UserExist(const CString& userName) const;

        /**
        * Gets the user count
        *@return the user count
        */
        virtual inline std::size_t GetUserCount() const;

        /**
        * Gets the user at index
        *@param index - index
        *@return the user, empty string if not found or on error
        */
        virtual inline CString GetUserAt(int index) const;

        /**
        * Adds a new user to the backup resources
        *@param userName - the user name
        */
        virtual inline void AddBackupUser(const CString& userName);

        /**
        * Removes an user from the backup resources
        *@param userName - the user name
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL RemoveBackupUser(const CString& userName);

        /**
        * Removes all the users from the backup resources
        */
        virtual inline void RemoveAllBackupUsers();

        /**
        * Searches if an user exists in the backup resources
        *@param userName - the user name
        *@return TRUE if the user exists in the backup resources, otherwise FALSE
        */
        virtual inline BOOL BackupUserExist(const CString& userName) const;

        /**
        * Gets the user count in the backup resources
        *@return the user count in the backup resources
        */
        virtual inline std::size_t GetBackupUserCount() const;

        /**
        * Gets the user at index in the backup resources
        *@param index - index
        *@return the user, empty string if not found or on error
        */
        virtual inline CString GetBackupUserAt(int index) const;

        /**
        * Gets attributed by activity
        *@return attributed by activity
        */
        virtual inline CString GetAttributedByActivity() const;

        /**
        * Sets attributed by activity
        *@param value - attributed by activity
        */
        virtual inline void SetAttributedByActivity(const CString& value = "");

        /**
        * Fills the necessary information when the task starts
        */
        void FillActivityInformationWhenStart();

        /**
        * Fills the necessary information when the task ends
        */
        void FillActivityInformationWhenEnd();

        /**
        * Fills the necessary information when the task is refused
        */
        void FillActivityInformationWhenRefused();

        /**
        * Fills the necessary information when the task is sent for acceptation
        */
        void FillActivityInformationWhenSentForAccept();

        /**
        * Fills the necessary information when the task is sent
        */
        void FillActivityInformationWhenSent();

        /**
        * Checks if the activity is shared by several users
        *@return TRUE if the activity is shared by several users, otherwise FALSE
        */
        virtual BOOL ActivityIsShared() const;

        /**
        * Checks if it is time to switch to backup resource and if backup resources have been defined
        *@return TRUE if it is time to switch to backup resource and if backup resources have been defined, otherwise FALSE
        */
        virtual BOOL MustSwitchToBackupResourceActivity() const;

        /**
        * Checks if it is time to remind for end activity
        *@return TRUE if it is time to remind for end activity, otherwise FALSE
        */
        virtual BOOL MustRemindEndActivity() const;

        /**
        * Checks if is an attribution activity
        *@return TRUE if is an attribution activity, otherwise FALSE
        */
        virtual inline BOOL ActivityIsAttribution() const;

        /**
        * Checks if is an acceptation activity
        *@return TRUE if is an acceptation activity, otherwise FALSE
        */
        virtual inline BOOL ActivityIsAcceptation() const;

        /**
        * Checks if is an input information activity
        *@return TRUE if is an input information activity, otherwise FALSE
        */
        virtual inline BOOL ActivityIsInput() const;

        /**
        * Checks if is a send mail activity
        *@return TRUE if is a send mail activity, otherwise FALSE
        */
        virtual inline BOOL ActivityIsSendMail() const;

        /**
        * Checks if is a start process activity
        *@return TRUE if is a start process activity, otherwise FALSE
        */
        virtual inline BOOL ActivityIsStartProcess() const;

        /**
        * Checks if is a command line activity
        *@return TRUE if is a command line activity, otherwise FALSE
        */
        virtual inline BOOL ActivityIsCommandLine() const;

        /**
        * Checks if is a scanning process activity
        *@return TRUE if is a scanning process activity, otherwise FALSE
        */
        virtual inline BOOL ActivityIsScanning() const;

        /**
        * Checks if is an archiving process activity
        *@return TRUE if is an archiving process activity, otherwise FALSE
        */
        virtual inline BOOL ActivityIsArchiving() const;

        /**
        * Assigns the previous base activity
        *@param pActivity - activity
        */
        void inline AssignPreviousActivity(PSS_BaseActivity* pActivity);

        /**
        * Assigns the next base activity
        *@param pActivity - activity
        */
        void inline AssignNextActivity(PSS_BaseActivity* pActivity);

        /**
        * Checks if the user attribution has been done for this activity
        *@return TRUE if the user attribution has been done for this activity, otherwise FALSE
        */
        virtual inline BOOL IsUserAttributionDone() const;

        /**
        * Checks if the time attribution has been done for this activity
        *@return TRUE if the time attribution has been done for this activity, otherwise FALSE
        */
        virtual inline BOOL IsTimeAttributionDone() const;

        /**
        * Checks if the visibility attribution has been done for this activity
        *@return TRUE if the visibility attribution has been done for this activity, otherwise FALSE
        */
        virtual inline BOOL IsVisibilityAttributionDone() const;

        /**
        * Checks if the activity is an attributed activity
        *@return TRUE if the activity is an attributed activity, otherwise FALSE
        */
        virtual inline BOOL IsAttributedActivity() const;

        /**
        * Gets if is in a backup process
        *@return TRUE if is in a backup process, otherwise FALSE
        */
        virtual inline BOOL IsInBackupProcess() const;

        /**
        * Sets if is in a backup process
        *@param value - if TRUE, is in a backup process
        */
        virtual inline void SetIsInBackupProcess(BOOL value = TRUE);

        /**
        * Gets the user type
        *@return the user type
        */
        virtual inline ActivityUserType GetUserType() const;

        /**
        * Sets the user type
        *@param value - the user type
        */
        virtual inline void SetUserType(ActivityUserType value);

        /**
        * Gets the backup user type
        *@return the backup user type
        */
        virtual inline ActivityUserType GetBackupUserType() const;

        /**
        * Sets the backup user type
        *@param value - the backup user type
        */
        virtual inline void SetBackupUserType(ActivityUserType value);

        /**
        * Gets the current resources. It depends if the activity has been entered in backup process
        *@return the current resources
        */
        virtual inline       ZBResources& GetCurrentResources();
        virtual inline const ZBResources& GetCurrentResources() const;

        /**
        * Gets if the activity should be considered as visible
        *@return the visibility state
        *@note Attributed activities are considered as visible until they were set to invisible
        */
        virtual inline EThreeState DoConsiderAsVisible() const;

        /**
        * Sets the activity or process visibility
        *@param value - the visibility state
        */
        virtual inline void SetVisibility(const EThreeState value);

        /**
        * Sets the parent
        *@param pParent - the parent
        */
        void SetParent(PSS_BaseActivity* pParent);

        /**
        * Gets the main process
        *@return the main process
        */
        virtual ZProcess* GetMainProcess();

        /**
        * Gets if activity is visible
        *@return the activity visibility styte
        */
        virtual inline const EThreeState& GetIsVisible() const;

        /**
        * Gets the start date
        *@return the start date
        */
        virtual inline const PSS_Date GetStartDate() const;

        /**
        * Sets the start date
        *@param value - the start date
        */
        virtual inline void SetStartDate(const PSS_Date& value);

        /**
        * Gets the end date
        *@return the end date
        */
        virtual inline const PSS_Date GetEndDate() const;

        /**
        * Sets the end date
        *@param value - the end date
        */
        virtual inline void SetEndDate(const PSS_Date& value);

        /**
        * Gets the start calculated forecasted date. This date is initialized once the process starts
        *@return the start calculated forecasted date
        */
        virtual inline const PSS_Date GetForecastedStartDate() const;

        /**
        * Sets the start calculated forecasted date. This date is initialized once the process starts
        *@param value - the start calculated forecasted date
        */
        virtual inline void SetForecastedStartDate(const PSS_Date& value);

        /**
        * Gets the end calculated forecasted date. This date is initialized once the process starts
        *@return the end calculated forecasted date
        */
        virtual inline const PSS_Date GetForecastedEndDate() const;

        /**
        * Gets the end calculated forecasted date. This date is initialized once the process starts
        *@param value - the end calculated forecasted date
        */
        virtual inline void SetForecastedEndDate(const PSS_Date& value);

        /**
        * Gets the last update date
        *@return the last update date
        */
        virtual inline const PSS_Date GetLastUpdateDate() const;

        /**
        * Sets the last update date
        *@param value - the last update date
        */
        virtual inline void SetLastUpdateDate(const PSS_Date& value);

        /**
        * Gets the process name
        *@return the process name
        */
        virtual inline const CString& GetName() const;

        /**
        * Sets the process name
        *@param value - the process name
        */
        virtual inline void SetName(const CString& value);

        /**
        * Gets the process description
        *@return the process description
        */
        virtual inline const CString& GetDescription() const;

        /**
        * Sets the process description
        *@param value - the process description
        */
        virtual inline void SetDescription(const CString& value);

        /**
        * Gets the activity comment. Used when an activity is rejected, stopped or paused
        *@return the activity comment
        */
        virtual inline const CString& GetComment() const;

        /**
        * Sets the activity comment. Used when an activity is rejected, stopped or paused
        *@param value - the activity comment
        */
        virtual inline void SetComment(const CString& value);

        /**
        * Gets the initiator
        *@return the initiator
        */
        virtual inline const CString& GetInitiator() const;

        /**
        * Sets the initiator
        *@return the initiator
        */
        virtual inline void SetInitiator(const CString& value);

        /**
        * Gets the activity status
        *@return the activity status
        */
        virtual inline const IEStatus GetActivityStatus() const;

        /**
        * Gets the activity status as a string
        *@return the activity status as a string
        */
        virtual CString GetActivityStatusString() const;

        /**
        * Sets the activity status
        *@param value - the activity status
        */
        virtual inline void SetActivityStatus(IEStatus value);

        /**
        * Gets the activity visibility
        *@return the activity visibility
        */
        virtual inline const IEVisibilityType GetVisibilityType() const;

        /**
        * Sets the activity visibility
        *@param value - the activity visibility
        */
        virtual inline void SetVisibilityType(IEVisibilityType value);

        /**
        * Gets the connected user
        *@return the connected user
        */
        virtual inline const CString GetConnectedUser() const;

        /**
        * Sets the connected user
        *@param value - the connected user
        */
        virtual inline void SetConnectedUser(const CString& value);

        /**
        * Gets the number of day for which the activity is assigned to backup resources
        *@return the number of day for which the activity is assigned to backup resources
        */
        virtual inline const std::size_t GetDaysForBackupResources() const;

        /**
        * Sets the number of day for which the activity is assigned to backup resources
        *@param value - the number of day for which the activity is assigned to backup resources
        */
        virtual inline void SetDaysForBackupResources(std::size_t value);

        /**
        * Gets if the system should use backup resources
        *@return TRUE if the system should use backup resources, otherwise FALSE
        */
        virtual inline const BOOL GetUseBackupResources() const;

        /**
        * Sets if the system should use backup resources
        *@param value - if TRUE, the system should use backup resources
        */
        virtual inline void SetUseBackupResources(BOOL value);

        /**
        * Gets the number of days before reminding the user
        *@return the number of days before reminding the user
        */
        virtual inline const std::size_t GetRemindDays() const;

        /**
        * Sets the number of days before reminding the user
        *@param value - the number of days before reminding the user
        */
        virtual inline void SetRemindDays(std::size_t value);

        /**
        * Gets if the activity is executed in the Intranet. If no, the activity is subject to go outside
        * and therefore, this activity is not sent over the Intranet through the message queuing
        *@return TRUE if this activity is executed in the Intranet, otherwise FALSE
        */
        virtual inline const BOOL GetIntranetActivity() const;

        /**
        * Sets if the activity is executed in the Intranet. If no, the activity is subject to go outside
        * and therefore, this activity is not sent over the Intranet through the message queuing
        *@param value - if TRUE, the activity is executed in the Intranet
        */
        virtual inline void SetIntranetActivity(BOOL value);

        /**
        * Gets the time type
        *@return the time type
        */
        virtual inline const IETimeoutType GetTimeType() const;

        /**
        * Sets the time type
        *@param value - the time type
        */
        virtual inline void SetTimeType(IETimeoutType value);

        /**
        * Sets the default property
        */
        virtual void SetDefaultProperty();

        /**
        * Gets the selected activities. Used when the process in not set to select activity mode
        *@return the selected activities
        */
        virtual inline CStringArray& GetSelectedActivityArray();

        /**
        * Gets if one or more activities have been selected. Only available when the RunMode is equal to IE_RM_Select
        *@return TRUE if one or more activities have been selected, otherwise FALSE
        */
        virtual inline BOOL IsActivitySelectionDone() const;

        /**
        * Removes all activities from the selected activity array
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL RemoveAllSelection();

        /**
        * Adds an activity to the selected activity array
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddActivityToSelection(const CString& activityName);

        /**
        * Sets the visibility for all childs of a process
        *@param value - visibility status
        */
        virtual void SetChildVisibility(const EThreeState value);

        /**
        * Moves up an activity
        *@param activityName - activity name
        *@return TRUE if the activity has been correctly moved, otherwise FALSE
        */
        virtual BOOL MoveActivityUp(const CString& activityName);

        /**
        * Moves down an activity
        *@param activityName - activity name
        *@return TRUE if the activity has been correctly moved, otherwise FALSE
        */
        virtual BOOL MoveActivityDown(const CString& activityName);

        /**
        * Checks if the activity can be moved up
        *@param activityName - activity name
        *@return TRUE if the activity can be moved up, otherwise FALSE
        */
        virtual BOOL CanActivityMoveUp(const CString& activityName);

        /**
        * Checks if the activity can be moved down
        *@param activityName - activity name
        *@return TRUE if the activity can be moved down, otherwise FALSE
        */
        virtual BOOL CanActivityMoveDown(const CString& activityName);

        /**
        * Sets the current activity to a valid activity
        *@param activityName - activity name
        */
        virtual void SetCurrentActivity(const CString& activityName);

        /**
        * Sets the current activity to a valid activity
        *@param pActivity - activity
        */
        virtual void SetCurrentActivity(PSS_BaseActivity* pActivity);

        /**
        * Sets the current activity to the previous valid activity
        *@return the activity
        */
        virtual PSS_BaseActivity* SetCurrentActivityToPrevious();

        /**
        * Sets the current activity to the next valid activity
        *@return the activity
        */
        virtual PSS_BaseActivity* SetCurrentActivityToNext();

        /**
        * Gets the previous valid activity from the current one
        *@return the previous valid activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetPreviousValidActivityFromCurrent() const;

        /**
        * Gets the next valid activity from the current one
        *@return the next valid activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetNextValidActivityFromCurrent() const;

        /**
        * Gets the previous base activity from the current one
        *@return the previous valid activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetPreviousBaseActivityFromCurrent() const;

        /**
        * Gets the next base activity from the current one
        *@return the next base activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* GetNextBaseActivityFromCurrent() const;

        /**
        * Removes an activity at index
        *@param index - the index
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveActivityAt(std::size_t index);

        /**
        * Adds a new activity at index
        *@param pActivity - the activity to add
        *@param index - the index
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InsertActivityAt(PSS_BaseActivity* pActivity, std::size_t index);

        /**
        * Adds a new activity on the end
        *@param pActivity - the activity to add
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddActivity(PSS_BaseActivity* pActivity);

        /**
        * Adds a new activity after a specified one
        *@param pActivity - the activity to add
        *@param activityName - activity name after which the new activity should be added
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddActivityAfter(PSS_BaseActivity* pActivity, const CString& activityName);

        /**
        * Deletes an activity
        *@param pActivity - the activity to delete
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteActivity(PSS_BaseActivity* pActivity);

        /**
        * Deletes an activity
        *@param activityName - the activity name to delete
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteActivity(const CString& activityName);

        /**
        * Finds an activity
        *@param activityName - the activity name to find
        *@returns the activity, NULL if not found or on error
        */
        virtual PSS_Activity* FindActivity(const CString& activityName) const;

        /**
        * Finds a base activity
        *@param activityName - the activity name to find
        *@returns the activity, NULL if not found or on error
        */
        virtual PSS_BaseActivity* FindBaseActivity(const CString& activityName) const;

        /**
        * Adds a new process on the end
        *@param pProcess - the process to add
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddProcess(ZProcess* pProcess);

        /**
        * Adds a new process after a specified activity
        *@param pProcess - the process to add
        *@param activityName - activity name after which the new process should be added
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddProcessAfter(ZProcess* pProcess, const CString& activityName);

        /**
        * Deletes a process
        *@param pProcess - the process to delete
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteProcess(ZProcess* pProcess);

        /**
        * Deletes a process
        *@param processName - the process name to delete
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteProcess(const CString& processName);

        /**
        * Finds a process
        *@param processName - the process name to find
        *@returns the process, NULL if not found or on error
        */
        virtual ZProcess* FindProcess(const CString& processName) const;

        /**
        * Removes all the activities
        *@param doDelete - if true, the activities will also be deleted on removed
        */
        virtual void RemoveAllActivities(bool doDelete = true);

        /**
        * Gets the index of an activity
        *@param activityName - the activity name to find
        *@return the activity index, -1 if not found or on error
        */
        virtual int GetActivityIndex(const CString& activityName) const;

        /**
        * Sets the activity at index
        *@param index - the index
        *@param pActivity - the activity to set
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetActivityAt(int index, PSS_BaseActivity* pActivity);

        /**
        * Recalculates all links for the process
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RecalculateAllLinks();

        /**
        * Gets the activity run mode
        *@return the activity run mode
        */
        virtual inline const IERunMode GetRunMode() const;

        /**
        * Sets the activity run mode
        *@param value - the activity run mode
        */
        virtual inline void SetRunMode(IERunMode value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    protected:
        IEStatus          m_ActivityStatus;
        IEVisibilityType  m_VisibilityType;
        IERunMode         m_RunMode;
        ZBResources       m_MainResources;
        ZBResources       m_BackupResources;
        PSS_BaseActivity* m_pParent;
        PSS_BaseActivity* m_pCurrentActivity;
        PSS_BaseActivity* m_pPreviousActivity;
        PSS_BaseActivity* m_pNextActivity;
        CObArray          m_ActivityArray;
        CStringArray      m_SelectedActivityArray;
        CString           m_Name;
        CString           m_Description;
        CString           m_Comment;
        CString           m_Initiator;
        CString           m_ConnectedUser;
        PSS_Date          m_StartDate;
        PSS_Date          m_EndDate;
        PSS_Date          m_ForecastedEndDate;
        PSS_Date          m_ForecastedStartDate;
        PSS_Date          m_LastUpdateDate;
        WORD              m_ActivityType;
        WORD              m_DurationDays;

        /**
        * Recalculates all links for the process
        *@param pParent - parent activity
        *@param pNextofParent - next of parent activity
        *@return the recalculated activity, NULL on error
        */
        PSS_BaseActivity* RecalculateProcessAllLinks(PSS_BaseActivity* pParent = NULL, PSS_BaseActivity* pNextOfParent = NULL);

    private:
        EThreeState   m_IsVisible;
        IETimeoutType m_TimeType;
        std::size_t   m_DaysForBackupResources;
        std::size_t   m_RemindDays;
        BOOL          m_UseBackupResources;
        BOOL          m_IsInBackupProcess;
        BOOL          m_IntranetActivity;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_BaseActivity(const PSS_BaseActivity& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_BaseActivity& operator = (const PSS_BaseActivity& other);
};

//---------------------------------------------------------------------------
// PSS_BaseActivity
//---------------------------------------------------------------------------
const WORD PSS_BaseActivity::GetActivityType() const
{
    return m_ActivityType;
}
//---------------------------------------------------------------------------
std::size_t PSS_BaseActivity::GetActivityCount() const
{
    return m_ActivityArray.GetSize();
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetCurrentActivity() const
{
    return m_pCurrentActivity;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetActivityAt(int index) const
{
    if (index < int(GetActivityCount()))
        return static_cast<PSS_BaseActivity*>(m_ActivityArray.GetAt(index));

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_BaseActivity::HasActivities() const
{
    return (GetActivityCount() > 0);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::IsLastActivity()
{
    return (m_pCurrentActivity && m_pCurrentActivity->GetNextValidBaseActivity()) ? FALSE : TRUE;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetPreviousBaseActivity() const
{
    return m_pPreviousActivity;
}
//---------------------------------------------------------------------------
PSS_BaseActivity* PSS_BaseActivity::GetNextBaseActivity() const
{
    return m_pNextActivity;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::AddUser(const CString& userName)
{
    m_MainResources.AddUser(userName);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::RemoveUser(const CString& userName)
{
    return m_MainResources.RemoveUser(userName);
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::RemoveAllUsers()
{
    m_MainResources.RemoveAllUsers();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::UserExist(const CString& userName) const
{
    return m_MainResources.UserExist(userName);
}
//---------------------------------------------------------------------------
std::size_t PSS_BaseActivity::GetUserCount() const
{
    return m_MainResources.GetUserCount();
}
//---------------------------------------------------------------------------
CString PSS_BaseActivity::GetUserAt(int index) const
{
    if (index < int(GetUserCount()))
        return m_MainResources.GetUserAt(index);

    return "";
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::AddBackupUser(const CString& userName)
{
    m_BackupResources.AddUser(userName);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::RemoveBackupUser(const CString& userName)
{
    return m_BackupResources.RemoveUser(userName);
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::RemoveAllBackupUsers()
{
    m_BackupResources.RemoveAllUsers();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::BackupUserExist(const CString& userName) const
{
    return m_BackupResources.UserExist(userName);
}
//---------------------------------------------------------------------------
std::size_t PSS_BaseActivity::GetBackupUserCount() const
{
    return m_BackupResources.GetUserCount();
}
//---------------------------------------------------------------------------
CString PSS_BaseActivity::GetBackupUserAt(int index) const
{
    if (index < int(GetBackupUserCount()))
        return m_BackupResources.GetUserAt(index);

    return "";
}
//---------------------------------------------------------------------------
CString PSS_BaseActivity::GetAttributedByActivity() const
{
    return "";
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetAttributedByActivity(const CString& value)
{}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::ActivityIsAttribution() const
{
    // if no activites or in selection mode
    if (!HasActivities() || GetRunMode() == IE_RM_Select)
        return (m_ActivityType & IE_AT_Attribution);

    // check the current activity
    if (!GetCurrentActivity())
        return FALSE;

    return GetCurrentActivity()->ActivityIsAttribution();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::ActivityIsAcceptation() const
{
    // if no activites or in selection mode
    if (!HasActivities() || GetRunMode() == IE_RM_Select)
        return (m_ActivityType & IE_AT_Acceptation);

    if (!GetCurrentActivity())
        return FALSE;

    return GetCurrentActivity()->ActivityIsAcceptation();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::ActivityIsInput() const
{
    // if no activites or in selection mode
    if (!HasActivities() || GetRunMode() == IE_RM_Select)
        return (m_ActivityType & IE_AT_InputInformation);

    if (!GetCurrentActivity())
        return FALSE;

    return GetCurrentActivity()->ActivityIsInput();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::ActivityIsSendMail() const
{
    // if no activites or in selection mode
    if (!HasActivities() || GetRunMode() == IE_RM_Select)
        return (m_ActivityType & IE_AT_SendMail);

    if (!GetCurrentActivity())
        return FALSE;

    return GetCurrentActivity()->ActivityIsSendMail();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::ActivityIsStartProcess() const
{
    // if no activites or in selection mode
    if (!HasActivities() || GetRunMode() == IE_RM_Select)
        return (m_ActivityType & IE_AT_StartProcess);

    if (!GetCurrentActivity())
        return FALSE;

    return GetCurrentActivity()->ActivityIsStartProcess();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::ActivityIsCommandLine() const
{
    // if no activites or in selection mode
    if (!HasActivities() || GetRunMode() == IE_RM_Select)
        return (m_ActivityType & IE_AT_CommandLine);

    if (!GetCurrentActivity())
        return FALSE;

    return GetCurrentActivity()->ActivityIsCommandLine();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::ActivityIsScanning() const
{
    // if no activites or in selection mode
    if (!HasActivities() || GetRunMode() == IE_RM_Select)
        return (m_ActivityType & IE_AT_Scanning);

    if (!GetCurrentActivity())
        return FALSE;

    return GetCurrentActivity()->ActivityIsScanning();
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::ActivityIsArchiving() const
{
    // if no activites or in selection mode
    if (!HasActivities() || GetRunMode() == IE_RM_Select)
        return (m_ActivityType & IE_AT_Archiving);

    if (!GetCurrentActivity())
        return FALSE;

    return GetCurrentActivity()->ActivityIsArchiving();
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::AssignPreviousActivity(PSS_BaseActivity* pActivity)
{
    m_pPreviousActivity = pActivity;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::AssignNextActivity(PSS_BaseActivity* pActivity)
{
    m_pNextActivity = pActivity;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::IsUserAttributionDone() const
{
    return (GetUserCount() > 0);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::IsTimeAttributionDone() const
{
    return (GetDurationDays() > 0);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::IsVisibilityAttributionDone() const
{
    return (GetIsVisible() != E_TS_Undefined);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::IsAttributedActivity() const
{
    return (m_MainResources.GetUserType()   == AttributionOfUsers         ||
            m_BackupResources.GetUserType() == AttributionOfUsers         ||
            GetTimeType()                   == IE_TT_AttributionOfTimeout ||
            GetVisibilityType()             == IE_VT_AttributionOfVisibility);
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::IsInBackupProcess() const
{
    return m_IsInBackupProcess;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetIsInBackupProcess(BOOL value)
{
    m_IsInBackupProcess = value;
}
//---------------------------------------------------------------------------
ActivityUserType PSS_BaseActivity::GetUserType() const
{
    return m_MainResources.GetUserType();
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetUserType(ActivityUserType value)
{
    m_MainResources.SetUserType(value);
}
//---------------------------------------------------------------------------
ActivityUserType PSS_BaseActivity::GetBackupUserType() const
{
    return m_BackupResources.GetUserType();
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetBackupUserType(ActivityUserType value)
{
    m_BackupResources.SetUserType(value);
}
//---------------------------------------------------------------------------
ZBResources& PSS_BaseActivity::GetCurrentResources()
{
    return (IsInBackupProcess() ? m_BackupResources : m_MainResources);
}
//---------------------------------------------------------------------------
const ZBResources& PSS_BaseActivity::GetCurrentResources() const
{
    return (IsInBackupProcess() ? m_BackupResources : m_MainResources);
}
//---------------------------------------------------------------------------
EThreeState PSS_BaseActivity::DoConsiderAsVisible() const
{
    if (GetIsVisible() == E_TS_Undefined)
        return E_TS_Undefined;

    if ((GetVisibilityType() == IE_VT_AttributionOfVisibility && GetIsVisible() == E_TS_True) ||
         GetVisibilityType() == IE_VT_Visible)
        return E_TS_True;

    if ((GetVisibilityType() == IE_VT_AttributionOfVisibility && GetIsVisible() == E_TS_False) ||
         GetVisibilityType() == IE_VT_Invisible)
        return E_TS_False;

    return E_TS_Undefined;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetVisibility(const EThreeState value)
{
    m_IsVisible = value;
}
//---------------------------------------------------------------------------
const EThreeState& PSS_BaseActivity::GetIsVisible() const
{
    return m_IsVisible;
}
//---------------------------------------------------------------------------
const PSS_Date PSS_BaseActivity::GetStartDate() const
{
    return m_StartDate;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetStartDate(const PSS_Date& value)
{
    m_StartDate = value;
}
//---------------------------------------------------------------------------
const PSS_Date PSS_BaseActivity::GetEndDate() const
{
    return m_EndDate;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetEndDate(const PSS_Date& value)
{
    m_EndDate = value;
}
//---------------------------------------------------------------------------
const PSS_Date PSS_BaseActivity::GetForecastedStartDate() const
{
    return m_ForecastedStartDate;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetForecastedStartDate(const PSS_Date& value)
{
    m_ForecastedStartDate = value;
}
//---------------------------------------------------------------------------
const PSS_Date PSS_BaseActivity::GetForecastedEndDate() const
{
    return m_ForecastedEndDate;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetForecastedEndDate(const PSS_Date& value)
{
    m_ForecastedEndDate = value;
}
//---------------------------------------------------------------------------
const PSS_Date PSS_BaseActivity::GetLastUpdateDate() const
{
    return m_LastUpdateDate;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetLastUpdateDate(const PSS_Date& value)
{
    m_LastUpdateDate = value;
}
//---------------------------------------------------------------------------
const CString& PSS_BaseActivity::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetName(const CString& value)
{
    m_Name = value;
}
//---------------------------------------------------------------------------
const CString& PSS_BaseActivity::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetDescription(const CString& value)
{
    m_Description = value;
}
//---------------------------------------------------------------------------
const CString& PSS_BaseActivity::GetComment() const
{
    return m_Comment;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetComment(const CString& value)
{
    m_Comment = value;
}
//---------------------------------------------------------------------------
const CString& PSS_BaseActivity::GetInitiator() const
{
    return m_Initiator;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetInitiator(const CString& value)
{
    m_Initiator = value;
}
//---------------------------------------------------------------------------
const PSS_BaseActivity::IEStatus PSS_BaseActivity::GetActivityStatus() const
{
    return m_ActivityStatus;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetActivityStatus(IEStatus value)
{
    m_ActivityStatus = value;
}
//---------------------------------------------------------------------------
const PSS_BaseActivity::IEVisibilityType PSS_BaseActivity::GetVisibilityType() const
{
    return m_VisibilityType;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetVisibilityType(IEVisibilityType value)
{
    m_VisibilityType = value;
}
//---------------------------------------------------------------------------
const CString PSS_BaseActivity::GetConnectedUser() const
{
    return m_ConnectedUser;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetConnectedUser(const CString& value)
{
    m_ConnectedUser = value;
}
//---------------------------------------------------------------------------
const std::size_t PSS_BaseActivity::GetDaysForBackupResources() const
{
    return m_DaysForBackupResources;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetDaysForBackupResources(std::size_t value)
{
    m_DaysForBackupResources = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_BaseActivity::GetUseBackupResources() const
{
    return m_UseBackupResources;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetUseBackupResources(BOOL value)
{
    m_UseBackupResources = value;
}
//---------------------------------------------------------------------------
const std::size_t PSS_BaseActivity::GetRemindDays() const
{
    return m_RemindDays;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetRemindDays(std::size_t value)
{
    m_RemindDays = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_BaseActivity::GetIntranetActivity() const
{
    return m_IntranetActivity;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetIntranetActivity(BOOL value)
{
    m_IntranetActivity = value;
}
//---------------------------------------------------------------------------
const PSS_BaseActivity::IETimeoutType PSS_BaseActivity::GetTimeType() const
{
    return m_TimeType;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetTimeType(IETimeoutType value)
{
    m_TimeType = value;
}
//---------------------------------------------------------------------------
CStringArray& PSS_BaseActivity::GetSelectedActivityArray()
{
    return m_SelectedActivityArray;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::IsActivitySelectionDone() const
{
    if (m_RunMode == IE_RM_Sequence)
        return FALSE;

    return m_SelectedActivityArray.GetSize() > 0;
}
//---------------------------------------------------------------------------
BOOL PSS_BaseActivity::RemoveAllSelection()
{
    m_SelectedActivityArray.RemoveAll();
    return !m_SelectedActivityArray.GetSize();
}
//---------------------------------------------------------------------------
const PSS_BaseActivity::IERunMode PSS_BaseActivity::GetRunMode() const
{
    return m_RunMode;
}
//---------------------------------------------------------------------------
void PSS_BaseActivity::SetRunMode(IERunMode value)
{
    m_RunMode = value;
}
//---------------------------------------------------------------------------

#endif
