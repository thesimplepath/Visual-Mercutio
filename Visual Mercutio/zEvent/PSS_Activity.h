/****************************************************************************
 * ==> PSS_Activity --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityH
#define PSS_ActivityH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_Activity
    #define PSS_Activity ZActivity
#endif

// processsoft
#include "zBaseLib\PSS_FileManager.h"
#include "zBaseLib\PSS_MailMessage.h"
#include "zBaseLib\PSS_CommandLine.h"
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

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const char g_RejectActivityToPrevious[] = "/P";
//---------------------------------------------------------------------------

/**
* Activity
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Activity : public PSS_BaseActivity
{
    DECLARE_SERIAL(PSS_Activity)

    public:
        typedef PSS_BaseActivity inherited;

        /**
        * Constructor
        *@param activityName - activity name
        *@param activityDescription - activity description
        *@param activityType - activity type
        *@param activityStatus - activity status
        */
        PSS_Activity(const CString& activityName        = "",
                     const CString& activityDescription = "",
                     int            activityType        = (int)IEType::IE_AT_InputInformation,
                     IEStatus       activityStatus      = IEStatus::IE_AS_NotStarted);

        virtual ~PSS_Activity();

        /**
        * Adds a new template
        *@param templateName - template name
        */
        virtual void AddTemplate(const CString& templateName);

        /**
        * Removes an existing template
        *@param templateName - template name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveTemplate(const CString& TemplateName);

        /**
        * Removes all the existing templates
        */
        virtual inline void RemoveAllTemplates();

        /**
        * Gets the template count
        *@return the template count
        */
        virtual inline std::size_t GetTemplateCount() const;

        /**
        * Gets the template at the index position
        *@param index - index
        *@return the template name, empty string if not found or on error
        */
        virtual inline CString GetTemplateAt(int index) const;

        /**
        * Checks if a template exists
        *@param templateName - template name to search for
        *@return TRUE if the template exists, otherwise FALSE
        */
        virtual BOOL TemplateExist(const CString& templateName) const;

        /**
        * Builds the template list to a string
        *@param separatorChar - separator char to use
        *@return the built template list as a string
        */
        virtual CString BuildTemplateListString(const char separatorChar = ';') const;

        /**
        * Gets the default activity string
        *@return the default activity string
        */
        virtual CString GetDefaultString() const;

        /**
        * Sets the attribution status
        *@param value - if TRUE, the attribution status will be added to the activity, otherwise removed
        */
        virtual inline void SetActivityAsAttribution(BOOL value = TRUE);

        /**
        * Sets the acceptation status
        *@param value - if TRUE, the acceptation status will be added to the activity, otherwise removed
        */
        virtual inline void SetActivityAsAcceptation(BOOL value = TRUE);

        /**
        * Sets the input status
        *@param value - if TRUE, the input status will be added to the activity, otherwise removed
        */
        virtual inline void SetActivityAsInput(BOOL value = TRUE);

        /**
        * Sets the send mail status
        *@param value - if TRUE, the send mail status will be added to the activity, otherwise removed
        */
        virtual inline void SetActivityAsSendMail(BOOL value = TRUE);

        /**
        * Sets the start process status
        *@param value - if TRUE, the start process status will be added to the activity, otherwise removed
        */
        virtual inline void SetActivityAsStartProcess(BOOL value = TRUE);

        /**
        * Sets the command line status
        *@param value - if TRUE, the command line status will be added to the activity, otherwise removed
        */
        virtual inline void SetActivityAsCommandLine(BOOL value = TRUE);

        /**
        * Sets the scanning status
        *@param value - if TRUE, the scanning status will be added to the activity, otherwise removed
        */
        virtual inline void SetActivityAsScanning(BOOL value = TRUE);

        /**
        * Sets the archiving status
        *@param value - if TRUE, the archiving status will be added to the activity, otherwise removed
        */
        virtual inline void SetActivityAsArchiving(BOOL value = TRUE);

        /**
        * Fills a person array
        *@param userManager - user manager
        *@param[out] userArray - user array to populate with results
        *@param connectedUser - connected user
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ActivityFillPersonArray(const PSS_UserManager& userManager,
                                             CStringArray&          userArray,
                                             const CString&         connectedUser);

        /**
        * Builds an user email list
        *@param userManager - user manager
        *@param connectedUser - connected user
        *@return the user email list, NULL on error
        */
        virtual PSS_MailUserList* ActivityCreatePersonList(const PSS_UserManager& userManager, const CString& connectedUser);

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
        * Checks if the activity contains the attributed state
        *@return TRUE if the activity contains the attributed state, otherwise FALSE
        */
        virtual inline BOOL IsAttributedActivity() const;

        /**
        * Deletes the sent email
        */
        virtual void DeleteEmailToSend();

        /**
        * Deletes the command line
        */
        virtual void DeleteCommandLine();

        /**
        * Calculates the forecast start date by taking all activities
        */
        virtual void CalculateForecastedStartDate();

        /**
        * Calculates the forecast end date by taking all activities
        */
        virtual void CalculateForecastedEndDate();

        /**
        * Gets the attributed by activity
        *@return the attributed by activity
        */
        virtual inline CString GetAttributedByActivity() const;

        /**
        * Sets the attributed by activity
        *@param value - the attributed by activity
        */
        virtual inline void SetAttributedByActivity(const CString& value = "");

        /**
        * Adds a form file name
        *@param fileName - the file name
        *@param attachment - attachment type
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddFormFile(const CString& fileName, PSS_File::IEAttachmentType attachment = PSS_File::IEAttachmentType::IE_AT_InsertedFile);

        /**
        * Adds form file names
        *@param fileNameArray - file name array
        *@param attachment - attachment type
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddFormFiles(const CStringArray& fileNameArray, PSS_File::IEAttachmentType attachement = PSS_File::IEAttachmentType::IE_AT_InsertedFile);

        /**
        * Removes all form file names
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveAllFormFiles();

        /**
        * Adds a process file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddProcFile(const CString& FileName, PSS_File::IEAttachmentType Attachement = PSS_File::IEAttachmentType::IE_AT_InsertedFile);

        /**
        * Adds process file names
        *@param fileNameArray - file name array
        *@param attachment - attachment type
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AddProcFiles(const CStringArray& FileNameArray, PSS_File::IEAttachmentType Attachement = PSS_File::IEAttachmentType::IE_AT_InsertedFile);

        /**
        * Removes all process file names
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveAllProcFiles();

        /**
        * Gets the form file count
        *@return the form file count
        */
        virtual std::size_t GetFormFileCount() const;

        /**
        * Gets the process file count
        *@return the process file count
        */
        virtual std::size_t GetProcFileCount() const;

        /**
        * Gets the form file at the specified index
        *@param index - index
        *@return the form file, NULL if not found or on error
        */
        virtual PSS_File* GetFormFileAt(std::size_t index);

        /**
        * Gets the process file at the specified index
        *@param index - index
        *@return the process file, NULL if not found or on error
        */
        virtual PSS_File* GetProcFileAt(std::size_t index);

        /**
        * Gets the rejected to activity
        *@return the rejected activity
        *@note By default the activity is rejected to the sender
        */
        virtual inline const CString GetRejectedToActivity() const;

        /**
        * Sets the rejected to activity
        *@return the rejected activity
        *@note By default the activity is rejected to the sender
        */
        virtual inline void SetRejectedToActivity(const CString& value);

        /**
        * Gets the mail message
        *@return the mail message, NULL if no mail message or on error
        */
        virtual inline PSS_MailMessage* GetMailMessage();

        /**
        * Sets the mail message
        *@param pMailMsg - the mail message
        */
        virtual inline void SetMailMessage(PSS_MailMessage* pMailMsg);

        /**
        * Gets the command line
        *@return the command line, NULL if no command line or on error
        */
        virtual inline PSS_CommandLine* GetCommandLine();

        /**
        * Sets the command line
        *@param pCmdLine - the command line
        */
        virtual inline void SetCommandLine(PSS_CommandLine* pCmdLine);

        /**
        * Gets the start process array
        *@return the start process array
        */
        virtual inline CStringArray& GetProcessToStartArray();

        /**
        * Gets the form file status while the the activity starts
        *@return required form file state
        */
        virtual inline const EThreeState GetRequireFormFile() const;

        /**
        * Sets the form file status while the the activity starts
        *@param value - the form file state
        */
        virtual inline void SetRequireFormFile(EThreeState value);

        /**
        * Gets the process file status while the the activity starts
        *@return required process file state
        */
        virtual inline const EThreeState GetRequireProcFile() const;

        /**
        * Sets the process file status while the the activity starts
        *@param value - the process file state
        */
        virtual inline void SetRequireProcFile(EThreeState value);

        /**
        * Gets the optional form names
        *@return the optional form names
        */
        virtual inline CStringArray& GetBaseFormNames();

        /**
        * Gets the optional process names
        *@return the optional process names
        */
        virtual inline CStringArray& GetBaseProcNames();

        /**
        * Gets the form attachement type
        *@return the form attachement type
        */
        virtual inline const PSS_File::IEAttachmentType GetFormAttachmentType() const;

        /**
        * Sets the form attachement type
        *@param value - the form attachement type
        */
        virtual inline void SetFormAttachmentType(PSS_File::IEAttachmentType value);

        /**
        * Gets the process attachement type
        *@return the process attachement type
        */
        virtual inline const PSS_File::IEAttachmentType GetProcessAttachmentType() const;

        /**
        * Sets the process attachement type
        *@param value - the process attachement type
        */
        virtual inline void SetProcessAttachmentType(PSS_File::IEAttachmentType value);

        /**
        * Gets if the pre-conditions were completed
        *@return TRUE if the pre-conditions were already completed, otherwise FALSE
        */
        virtual inline const BOOL GetPreConditionsDone() const;

        /**
        * Sets if the pre-conditions were completed
        *@param value - if TRUE, the pre-conditions were already completed
        */
        virtual inline void SetPreConditionsDone(BOOL value);

        /**
        * Gets if the post-conditions were completed
        *@return TRUE if the post-conditions were already completed, otherwise FALSE
        */
        virtual inline const BOOL GetPostConditionsDone() const;

        /**
        * Sets if the post-conditions were completed
        *@param value - if TRUE, the post-conditions were already completed
        */
        virtual inline void SetPostConditionsDone(BOOL value);

        /**
        * Gets if, for pre-conditions, the form import must be set as read-only
        *@return TRUE if the form import must be set as read-only, otherwise FALSE
        */
        virtual inline const BOOL GetPreFormReadOnly() const;

        /**
        * Sets if, for pre-conditions, the form import must be set as read-only
        *@param value - if TRUE, the form import must be set as read-only, otherwise FALSE
        */
        virtual inline void SetPreFormReadOnly(BOOL value);

        /**
        * Gets if, for pre-conditions, the process import must be set as read-only
        *@return TRUE if the process import must be set as read-only, otherwise FALSE
        */
        virtual inline const BOOL GetPreProcReadOnly() const;

        /**
        * Sets if, for pre-conditions, the process import must be set as read-only
        *@param value - if TRUE, the process import must be set as read-only, otherwise FALSE
        */
        virtual inline void SetPreProcReadOnly(BOOL value);

        /**
        * Sets the default property
        */
        virtual void SetDefaultProperty();

        /**
        * Gets the activity type key string
        *@return the activity type key string
        */
        virtual CString GetActivityTypeKeyString() const;

        /**
        * Gets the activity type key string
        *@param key - the activity type key string
        *@return the activity type key string
        */
        virtual void SetActivityTypeFromKeyString(const CString& key);

        /**
        * Deletes the process to start
        */
        virtual void DeleteProcessToStart();

        /**
        * Deletes based on form file
        */
        virtual void DeleteBaseOnFormFile();

        /**
        * Deletes based on process file
        */
        virtual void DeleteBaseOnProcFile();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    protected:
        CStringArray m_ProcessToStartArray;
        CStringArray m_BaseFormNames;
        CStringArray m_BaseProcNames;

    private:
        PSS_MailMessage*           m_pMailMessage;
        PSS_CommandLine*           m_pCommandLine;
        PSS_FileManager*           m_pBaseOnFormFile;
        PSS_FileManager*           m_pBaseOnProcFile;
        PSS_File::IEAttachmentType m_FormAttachmentType;
        PSS_File::IEAttachmentType m_ProcessAttachmentType;
        EThreeState                m_RequireFormFile;
        EThreeState                m_RequireProcFile;
        CStringArray               m_TemplateArray;
        CString                    m_RejectedToActivity;
        CString                    m_AttributedByActivity;
        BOOL                       m_PreConditionsDone;
        BOOL                       m_PostConditionsDone;
        BOOL                       m_PreFormReadOnly;
        BOOL                       m_PreProcReadOnly;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Activity(const PSS_Activity& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Activity& operator = (const PSS_Activity& other);
};

//---------------------------------------------------------------------------
// PSS_Activity
//---------------------------------------------------------------------------
void PSS_Activity::RemoveAllTemplates()
{
    m_TemplateArray.RemoveAll();
}
//---------------------------------------------------------------------------
std::size_t PSS_Activity::GetTemplateCount() const
{
    return m_TemplateArray.GetSize();
}
//---------------------------------------------------------------------------
CString PSS_Activity::GetTemplateAt(int index) const
{
    return m_TemplateArray.GetAt(index);
}
//---------------------------------------------------------------------------
void PSS_Activity::SetActivityAsAttribution(BOOL value)
{
    if (value)
        m_ActivityType |= (DWORD)IEType::IE_AT_Attribution;
    else
        m_ActivityType &= ~(DWORD)IEType::IE_AT_Attribution;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetActivityAsAcceptation(BOOL value)
{
    if (value)
        m_ActivityType |= (DWORD)IEType::IE_AT_Acceptation;
    else
        m_ActivityType &= ~(DWORD)IEType::IE_AT_Acceptation;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetActivityAsInput(BOOL value)
{
    if (value)
        m_ActivityType |= (DWORD)IEType::IE_AT_InputInformation;
    else
        m_ActivityType &= ~(DWORD)IEType::IE_AT_InputInformation;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetActivityAsSendMail(BOOL value)
{
    if (value)
        m_ActivityType |= (DWORD)IEType::IE_AT_SendMail;
    else
        m_ActivityType &= ~(DWORD)IEType::IE_AT_SendMail;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetActivityAsStartProcess(BOOL value)
{
    if (value)
        m_ActivityType |= (DWORD)IEType::IE_AT_StartProcess;
    else
        m_ActivityType &= ~(DWORD)IEType::IE_AT_StartProcess;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetActivityAsCommandLine(BOOL value)
{
    if (value)
        m_ActivityType |= (DWORD)IEType::IE_AT_CommandLine;
    else
        m_ActivityType &= ~(DWORD)IEType::IE_AT_CommandLine;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetActivityAsScanning(BOOL value)
{
    if (value)
        m_ActivityType |= (DWORD)IEType::IE_AT_Scanning;
    else
        m_ActivityType &= ~(DWORD)IEType::IE_AT_Scanning;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetActivityAsArchiving(BOOL value)
{
    if (value)
        m_ActivityType |= (DWORD)IEType::IE_AT_Archiving;
    else
        m_ActivityType &= ~(DWORD)IEType::IE_AT_Archiving;
}
//---------------------------------------------------------------------------
BOOL PSS_Activity::IsAttributedActivity() const
{
    return (GetVisibilityType()             == IEVisibilityType::IE_VT_AttributionOfVisibility             ||
            m_MainResources.GetUserType()   == PSS_ActivityResources::IEUserType::IE_UT_AttributionOfUsers ||
            m_BackupResources.GetUserType() == PSS_ActivityResources::IEUserType::IE_UT_AttributionOfUsers ||
            GetTimeType()                   == IETimeoutType::IE_TT_AttributionOfTimeout);
}
//---------------------------------------------------------------------------
CString PSS_Activity::GetAttributedByActivity() const
{
    return m_AttributedByActivity;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetAttributedByActivity(const CString& value)
{
    m_AttributedByActivity = value;
}
//---------------------------------------------------------------------------
const CString PSS_Activity::GetRejectedToActivity() const
{
    return m_RejectedToActivity;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetRejectedToActivity(const CString& value)
{
    m_RejectedToActivity = value;
}
//---------------------------------------------------------------------------
PSS_MailMessage* PSS_Activity::GetMailMessage()
{
    return m_pMailMessage;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetMailMessage(PSS_MailMessage* pMailMsg)
{
    m_pMailMessage = pMailMsg;
}
//---------------------------------------------------------------------------
PSS_CommandLine* PSS_Activity::GetCommandLine()
{
    return m_pCommandLine;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetCommandLine(PSS_CommandLine* value)
{
    m_pCommandLine = value;
}
//---------------------------------------------------------------------------
CStringArray& PSS_Activity::GetProcessToStartArray()
{
    return m_ProcessToStartArray;
}
//---------------------------------------------------------------------------
const EThreeState PSS_Activity::GetRequireFormFile() const
{
    return m_RequireFormFile;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetRequireFormFile(EThreeState value)
{
    m_RequireFormFile = value;
}
//---------------------------------------------------------------------------
const EThreeState PSS_Activity::GetRequireProcFile() const
{
    return m_RequireProcFile;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetRequireProcFile(EThreeState value)
{
    m_RequireProcFile = value;
}
//---------------------------------------------------------------------------
CStringArray& PSS_Activity::GetBaseFormNames()
{
    return m_BaseFormNames;
}
//---------------------------------------------------------------------------
CStringArray& PSS_Activity::GetBaseProcNames()
{
    return m_BaseProcNames;
}
//---------------------------------------------------------------------------
const PSS_File::IEAttachmentType PSS_Activity::GetFormAttachmentType() const
{
    return m_FormAttachmentType;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetFormAttachmentType(PSS_File::IEAttachmentType value)
{
    m_FormAttachmentType = value;
}
//---------------------------------------------------------------------------
const PSS_File::IEAttachmentType PSS_Activity::GetProcessAttachmentType() const
{
    return m_ProcessAttachmentType;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetProcessAttachmentType(PSS_File::IEAttachmentType value)
{
    m_ProcessAttachmentType = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_Activity::GetPreConditionsDone() const
{
    return m_PreConditionsDone;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetPreConditionsDone(BOOL value)
{
    m_PreConditionsDone = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_Activity::GetPostConditionsDone() const
{
    return m_PostConditionsDone;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetPostConditionsDone(BOOL value)
{
    m_PostConditionsDone = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_Activity::GetPreFormReadOnly() const
{
    return m_PreFormReadOnly;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetPreFormReadOnly(BOOL value)
{
    m_PreFormReadOnly = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_Activity::GetPreProcReadOnly() const
{
    return m_PreProcReadOnly;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetPreProcReadOnly(BOOL value)
{
    m_PreProcReadOnly = value;
}
//---------------------------------------------------------------------------

#endif
