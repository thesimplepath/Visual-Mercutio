/****************************************************************************
 * ==> PSS_Process ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a process                                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessH
#define PSS_ProcessH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_Process
    //#define PSS_Process ZProcess
#endif

// processsoft
#include "PSS_Activity.h"
#include "PSS_ProcessIterator.h"
#include "PSS_BaseActivity.h"

#ifdef _ZEVENTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Process : public PSS_BaseActivity
{
    DECLARE_SERIAL(PSS_Process)

    public:
        typedef PSS_BaseActivity inherited;

        enum IEStatus
        {
            IE_PS_Started,
            IE_PS_InProcess,
            IE_PS_Completed,
            IE_PS_Aborted,
            IE_PS_NotStarted,
            IE_PS_Suspend
        };

        /**
        * Constructor
        *@param processStatus - process status
        *@param connectedUser - connected user
        */
        PSS_Process(IEStatus processStatus = IE_PS_NotStarted, const CString& connectedUser = "");

        virtual ~PSS_Process();

        /**
        * Adds a new authorized user
        *@param userName - user name
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL AddAuthUser(const CString& userName);

        /**
        * Gets the authorized user count
        *@return the authorized user count
        */
        virtual inline std::size_t GetAuthUserCount() const;

        /**
        * Gets the authorized user name at index
        *@param index - index
        *@return the authorized user name at index, empty string if not found or on error
        */
        virtual inline CString GetAuthUserAt(int index);

        /**
        * Removes all the authorized users
        */
        virtual inline void RemoveAllAuthUsers();

        /**
        * Fills the authorization user list from an activity
        *@param activity - the activity
        *@param userManager - user manager
        */
        virtual void FillAuthUser(PSS_BaseActivity& activity, const PSS_UserManager& userManager);

        /**
        * Fills the authorization user list from resources
        *@param resources - resources
        */
        virtual void FillAuthUser(const PSS_ActivityResources& resources);

        /**
        * Fills the authorization user list from a delimiter string of users
        *@param userDelimiter - delimited string containing users
        */
        virtual void FillAuthUser(const CString& userDelimiter);

        /**
        * Fills the string array with activity name
        *@param[out] activityArray - activity array to populate with result
        *@param activityType - activity type
        *@param excludedActivity - excluded activity
        *@param stopWhenFound - if TRUE, the fill will stop when found
        *@param attributedActivityOnly - if TRUE, only the attributed activities will be considered
        *@return the activity count
        */
        virtual std::size_t GetActivityNameArray(CStringArray&  activityArray,
                                                 WORD           activityType           = 0,
                                                 const CString& excludedActivity       = "",
                                                 BOOL           stopWhenFound          = TRUE,
                                                 BOOL           attributedActivityOnly = FALSE);

        /**
        * Checks if a specific template name exists
        *@param templateName - the template name
        *@return TRUE if a specific template name exists, otherwise FALS
        */
        virtual BOOL TemplateExist(const CString& templateName);

        /**
        * Build the person email list
        *@param activity - the activity
        *@param userManager - the user manager
        *@return the user email list, NULL on error
        */
        virtual PSS_MailUserList* CreatePersonList(PSS_BaseActivity& activity, const PSS_UserManager& userManager);

        /**
        * Build the person email list
        *@param index - the activity index
        *@param userManager - the user manager
        *@return the user email list, NULL on error
        */
        virtual PSS_MailUserList* CreatePersonList(int index, const PSS_UserManager& userManager);

        /**
        * Fills a person array
        *@param activity - the activity
        *@param userManager - the user manager
        *@param[out] userArray - the user array to populate
        *@return the user email list, NULL on error
        */
        virtual BOOL FillPersonArray(PSS_BaseActivity& activity, const PSS_UserManager& userManager, CStringArray& userArray);

        /**
        * Fills a person array
        *@param index - the activity index
        *@param userManager - the user manager
        *@param[out] userArray - the user array to populate
        *@return the user email list, NULL on error
        */
        virtual BOOL FillPersonArray(int index, const PSS_UserManager& userManager, CStringArray& userArray);

        /**
        * Build a delimited string containing the person list
        *@param activity - activity from which the list will be get
        *@param userManager - user manager
        *@param delimiter - delimiter to use to tokenize the source string
        *@return the person list delimited string
        */
        virtual CString CreatePersonDelimStr(PSS_BaseActivity&       activity,
                                             const PSS_UserManager&  userManager,
                                             const CString&          delimiter = ";");

        /**
        * Build a delimited string containing the person list
        *@param index - the activity index from which the list will be get
        *@param userManager - user manager
        *@param delimiter - delimiter to use to tokenize the source string
        *@return the person list delimited string
        */
        virtual CString CreatePersonDelimStr(int index, const PSS_UserManager& userManager, const CString& delimiter = ";");

        /**
        * For a specific activity, finds its attributed activities
        *@param name - the activity name to search
        *@return the attributed activities array, NULL if not found or on error
        */
        virtual CObArray* GetAttributedActivities(const CString& name);

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
        virtual WORD GetDurationDays();

        /**
        * Gets the activity status key string
        *@param pActivity - the activity
        *@return the activity status key string
        */
        virtual CString GetStatusKeyString(PSS_BaseActivity* pActivity = NULL);

        /**
        * Sets the activity status based on a key string
        *@param key - the key string
        */
        virtual void SetStatusFromKeyString(const CString& key);

        /**
        * Sets the visibility of an activity or process
        *@param value - the visibility status
        */
        virtual void SetVisibility(const EThreeState value);

        /**
        * Gets the activity status string
        *@return the activity status string
        */
        virtual CString GetActivityStatusString() const;

        /**
        * Gets the main process
        *@return the main process
        */
        virtual PSS_Process* GetMainProcess();

        /**
        * Gets the process status
        *@return the process status
        */
        virtual inline const IEStatus GetProcessStatus() const;

        /**
        * Sets the process status
        *@param value - the process status
        */
        virtual inline void SetProcessStatus(IEStatus value);

        /**
        * Gets the list of authorized users allowed to modify the process. It is a function of the activity
        *@return the list of authorized users allowed to modify the process
        */
        virtual inline CStringArray& GetAuthorizedUser();

        /**
        * Gets if the mail may be also used as workflow support
        *@return TRUE if the mail may be also used as workflow support, otherwise FALSE
        */
        virtual inline const BOOL GetUseMail() const;

        /**
        * Sets if the mail may be also used as workflow support
        *@param value - if TRUE, the mail may be also used as workflow support
        */
        virtual inline void SetUseMail(BOOL value);

        /**
        * Gets if the process can be automatically started without human intervention
        *@return TRUE if the process can be automatically started without human intervention, otherwise FALSE
        */
        virtual inline const BOOL GetAutoStart() const;

        /**
        * Gets if the process can be automatically started without human intervention
        *@param value - if TRUE, the process can be automatically started without human intervention
        */
        virtual inline void SetAutoStart(BOOL value);

        /**
        * Gets if the process do not must use the internal messagerie
        *@return TRUE if the process do not must use the internal messagerie, otherwise FALSE
        */
        virtual inline const BOOL GetDoNotUseInternalMessage() const;

        /**
        * Sets if the process do not must use the internal messagerie
        *@param value - if TRUE, the process do not must use the internal messagerie
        */
        virtual inline void SetDoNotUseInternalMessage(BOOL value);

        /**
        * Sets the default property
        */
        virtual void SetDefaultProperty();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CObArray*    m_pAttributedActivitiesArray;
        IEStatus     m_ProcessStatus;
        CStringArray m_AuthorizedUser;
        BOOL         m_UseMail;
        BOOL         m_AutoStart;
        BOOL         m_DoNotUseInternalMessage;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Process(const PSS_Process& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Process& operator = (const PSS_Process& other);
};

//---------------------------------------------------------------------------
// PSS_Process
//---------------------------------------------------------------------------
BOOL PSS_Process::AddAuthUser(const CString& userName)
{
    return m_AuthorizedUser.Add(userName) >= 0;
}
//---------------------------------------------------------------------------
std::size_t PSS_Process::GetAuthUserCount() const
{
    return std::size_t(m_AuthorizedUser.GetSize());
}
//---------------------------------------------------------------------------
CString PSS_Process::GetAuthUserAt(int index)
{
    return (CString)m_AuthorizedUser.GetAt(index);
}
//---------------------------------------------------------------------------
void PSS_Process::RemoveAllAuthUsers()
{
    m_AuthorizedUser.RemoveAll();
}
//---------------------------------------------------------------------------
const PSS_Process::IEStatus PSS_Process::GetProcessStatus() const
{
    return m_ProcessStatus;
}
//---------------------------------------------------------------------------
void PSS_Process::SetProcessStatus(IEStatus value)
{
    m_ProcessStatus = value;
}
//---------------------------------------------------------------------------
CStringArray& PSS_Process::GetAuthorizedUser()
{
    return m_AuthorizedUser;
}
//---------------------------------------------------------------------------
const BOOL PSS_Process::GetUseMail() const
{
    return m_UseMail;
}
//---------------------------------------------------------------------------
void PSS_Process::SetUseMail(BOOL value)
{
    m_UseMail = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_Process::GetAutoStart() const
{
    return m_AutoStart;
}
//---------------------------------------------------------------------------
void PSS_Process::SetAutoStart(BOOL value)
{
    m_AutoStart = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_Process::GetDoNotUseInternalMessage() const
{
    return m_DoNotUseInternalMessage;
}
//---------------------------------------------------------------------------
void PSS_Process::SetDoNotUseInternalMessage(BOOL value)
{
    m_DoNotUseInternalMessage = value;
}
//---------------------------------------------------------------------------

#endif
