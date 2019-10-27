/****************************************************************************
 * ==> PSS_Global ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a global application helper                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GlobalH
#define PSS_GlobalH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Network.h"
#include "PSS_TemplateManager.h"
#include "ZUMail.h"
#include "PSS_DocTemplateEx.h"
#include "PSS_HistoricValueManager.h"

// class name mapping
#ifndef PSS_Document
    #define PSS_Document ZDDocument
#endif

// forward class declarations
class PSS_Document;
class PSS_ProcessModelDocTmpl;
class PSS_Server;

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

using namespace sfl;

/**
* Global application helper
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Global
{
    public:
        /**
        * Application type
        */
        enum IEApplicationType
        {
            IE_AT_Undef,
            IE_AT_Reader,
            IE_AT_Writer,
            IE_AT_Publisher,
            IE_AT_Process,
            IE_AT_Designer,
            IE_AT_Analyser,
            IE_AT_Watcher
        };

        /**
        * Reference insertion type
        */
        enum IEReferenceInsertionType
        {
            IE_RI_External = 0,
            IE_RI_Internal = 1
        };

        /**
        * Reference activation type
        */
        enum IEReferenceActivationType
        {
            IE_RA_InAndAfterSymbol  = 0,
            IE_RA_InSymbol          = 1,
            IE_RA_InAndBeforeSymbol = 2,
            IE_RA_Always            = 3
        };

        typedef CCArray_T<CStringArray*, CStringArray*> IFullMonthSet;
        typedef CCArray_T<CStringArray*, CStringArray*> IShortMonthSet;
        typedef CCArray_T<CStringArray*, CStringArray*> IDaySet;

        PSS_Global();
        virtual ~PSS_Global();

        /**
        * Initializes the class
        *@param pServer - server
        *@param appType - application type
        *@param isFormDesigner - if TRUE, application is a form designer
        *@param showAnimation - if TRUE, animation should be shown
        *@param maximizeFormOnOpen - if TRUE, form will be maximized on open
        *@param fileDirectory - file directory
        *@param eventDirectory - event directory
        */
        static void Initialize(PSS_Server*       pServer,
                               IEApplicationType appType,
                               BOOL              isFormDesigner,
                               BOOL              showAnimation,
                               BOOL              maximizeFormOnOpen,
                               const CString&    fileDirectory,
                               const CString&    eventDirectory);

        /**
        * Initializes the network
        *@return true on success, otherwise false
        */
        static const bool InitializeNetwork();

        /**
        * Releases the global resources
        */
        static void Release();

        /**
        * Gets the server
        *@return the server
        */
        static inline PSS_Server* GetServer();

        /**
        * Reads historic value methods from file
        *@param fileName - file name
        *@return true on success, otherwise false
        */
        static bool ReadFromFileHistoricValue(const CString& fileName);

        /**
        * Saves historic value methods to file
        *@param fileName - file name
        *@return true on success, otherwise false
        */
        static bool SaveToFileHistoricValue(const CString& fileName);

        /**
        * Gets the historic value manager
        *@return the historic value manager
        */
        static inline PSS_HistoricValueManager& GetHistoricValueManager();

        /**
        * Gets if the application is in initialization process
        *@return TRUE if the application is in initialization process, otherwise FALSE
        */
        static inline const BOOL IsDuringInitialization();

        /**
        * Starts the initialization process
        */
        static inline void StartInitialization();

        /**
        * Ends the initialization process
        */
        static inline void EndInitialization();

        /**
        * Gets the application type
        *@return the application type
        */
        static inline IEApplicationType GetType();

        /**
        * Sets the application type
        *@param value - the application type
        */
        static inline void SetType(IEApplicationType value);

        /**
        * Gets the current document for serialization
        *@return the current document for serialization
        */
        static inline PSS_Document* GetCurrentDocumentForSerialization();

        /**
        * Sets the current document for serialization
        *@param value - the current document for serialization
        */
        static inline void SetCurrentDocumentForSerialization(PSS_Document* value);

        /**
        * Opens the file in silent mode
        *@return TRUE on success, otherwise FALSE
        */
        static inline BOOL OpenFileInSilentMode();

        /**
        * Sets the file as opened in silent mode
        *@return TRUE on success, otherwise FALSE
        */
        static inline void SetOpenFileInSilentMode(BOOL value = TRUE);

        /**
        * Checks if form is a form designer
        *@return TRUE if form is a form designer, otherwise FALSE
        */
        static inline BOOL IsFormDesigner();

        /**
        * Sets form as a form designer
        *@param value - if TRUE, form will be a form designer
        */
        static inline void SetIsFormDesigner(BOOL value);

        /**
        * Checks if animations are shown
        *@return TRUE if animations are shown, otherwise FALSE
        */
        static inline BOOL ShowAnimation();

        /**
        * Sets if animations should be shown
        *@param value - if TRUE, animation should be shown
        */
        static inline void SetShowAnimation(BOOL value);

        /**
        * Gets if form should be maximized on open
        *@return TRUE if form should be maximized on open, otherwise FALSE
        */
        static inline BOOL MaximizeFormOnOpen();

        /**
        * Selects the form file
        *@param initialDir - initial directory
        *@return the form file
        */
        static CString SelectFormFile(const CString& initialDir = _T(""));

        /**
        * Gets the application directory
        *@return the application directory
        */
        static inline CString GetApplicationDirectory();

        /**
        * Sets the application directory
        *@param value - the application directory
        */
        static inline void SetApplicationDirectory(const CString& value);

        /**
        * Sets the server file directory
        */
        static void SetToFileDirectory();

        /**
        * Gets the file directory
        *@return the file directory
        */
        static inline CString GetFileDirectory();

        /**
        * Sets the file directory
        *@param value - the file directory
        */
        static inline void SetFileDirectory(const CString& value);

        /**
        * Gets the event directory
        *@return the event directory
        */
        static inline CString GetEventDirectory();

        /**
        * Sets the event directory
        *@param value - the event directory
        */
        static inline void SetEventDirectory(const CString value);

        /**
        * Gets the file extension
        *@return the file extension
        */
        static inline CString GetFileExtension();

        /**
        * Gets the process file extension
        *@return the process file extension
        */
        static inline CString GetProcessFileExtension();

        /**
        * Gets the model file extension
        *@return the model file extension
        */
        static inline CString GetModelFileExtension();

        /**
        * Gets the template manager
        *@return the template manager
        */
        static inline PSS_TemplateManager& GetTemplateManager();

        /**
        * Gets the process template manager
        *@return the process template manager
        */
        static inline PSS_TemplateManager& GetProcessTemplateManager();

        /**
        * Gets the model template manager
        *@return the model template manager
        */
        static inline PSS_TemplateManager& GetModelTemplateManager();

        /**
        * Gets the multi-document template
        *@return the multi-document template
        */
        static inline PSS_DocTemplateEx* GetDocTemplate();

        /**
        * Sets the multi-document template
        *@param pDoc - the multi-document template
        */
        static inline void SetDocTemplate(PSS_DocTemplateEx* pDoc);

        /**
        * Gets the process multi-document template
        *@return the process multi-document template
        */
        static inline PSS_DocTemplateEx* GetProcessDocTemplate();

        /**
        * Sets the process multi-document template
        *@param pDoc - the process multi-document template
        */
        static inline void SetProcessDocTemplate(PSS_DocTemplateEx* pDoc);

        /**
        * Gets the process model multi-document template
        *@return the process model multi-document template
        */
        static inline PSS_ProcessModelDocTmpl* GetProcessModelDocumentTemplate();

        /**
        * Sets the process model multi-document template
        *@param pDoc - the process model multi-document template
        */
        static inline void SetProcessModelDocumentTemplate(PSS_ProcessModelDocTmpl* pDoc);

        /**
        * Gets the report multi-document template
        *@return the report multi-document template
        */
        static inline CMultiDocTemplate* GetReportDocumentTemplate();

        /**
        * Sets the report multi-document template
        *@param pDoc - the report multi-document template
        */
        static inline void SetReportDocumentTemplate(CMultiDocTemplate* pDoc);

        /**
        * Gets the network
        *@return the network
        */
        static inline PSS_Network& GetNetWork();

        /**
        * Gets the e-mail
        *@return the e-mail
        */
        static inline ZUMail& GetMail();

        /**
        * Gets the user manager
        *@return the user manager
        */
        static inline PSS_UserManager& GetUserManager();

        /**
        * Gets the responsible user name key
        *@return the responsible user name key
        */
        static inline const CString& GetResponsibleUserNameKeyString();

        /**
        * Gets the requested user name key
        *@return the requested user name key
        */
        static inline const CString& GetRequestedUserNameKeyString();

        /**
        * Gets the connected user name
        *@return the connected user name
        */
        static const CString GetConnectedUserName();

        /**
        * Gets the connected user
        *@return the connected user
        */
        static inline const ZUser* GetConnectedUser();

        /**
        * Gets the modal dialog window
        *@return the modal dialog window
        */
        static inline CWnd* GetModalDialogCWnd();

        /**
        * Sets the modal dialog window
        *@param pWnd - the modal dialog window
        */
        static inline void SetModalDialogCWnd(CWnd* pWnd);

        /**
        * Clears the modal dialog window
        */
        static inline void ClearModalDialogCWnd();

        /**
        * Gets the array yes/no strings
        *@return the array yes/no strings
        */
        static inline CStringArray* GetArrayYesNo();

        /**
        * Gets the yes string from the array yes/no strings
        *@return the yes string from the array yes/no strings
        */
        static inline CString GetYesFromArrayYesNo();

        /**
        * Gets the no string from the array yes/no strings
        *@return the no string from the array yes/no strings
        */
        static inline CString GetNoFromArrayYesNo();

        /**
        * Gets the Windows mode array string
        *@return the Windows mode array string
        */
        static inline CStringArray* GetArrayWindowMode();

        /**
        * Gets the Windows mode string
        *@param mode - Windows mode
        *@return the Windows mode string
        */
        static CString GetWindowModeString(int mode);

        /**
        * Gets the Windows mode
        *@param mode - Windows mode string
        *@return the Windows mode
        */
        static int GetWindowMode(const CString& mode);

        /**
        * Gets the job priority array
        *@return the job priority array
        */
        static inline CStringArray* GetArrayJobPriority();

        /**
        * Gets the job priority string
        *@param priority - job priority
        *@return the job priority string
        */
        static CString GetJobPriorityString(int priority);

        /**
        * Gets the job priority
        *@param priority - job priority string
        *@return the job priority
        */
        static int GetJobPriority(const CString& priority);

        /**
        * Gets the array insertion type
        *@return the array insertion type
        */
        static inline CStringArray* GetArrayInsertionType();

        /**
        * Gets the insertion type string
        *@param type - insertion type
        *@return the insertion type string
        */
        static CString GetInsertionTypeString(int type);

        /**
        * Gets the insertion type
        *@param type - insertion type string
        *@return the insertion type
        */
        static int GetInsertionType(const CString& type);

        /**
        * Gets the activation type array
        *@return the activation type array
        */
        static inline CStringArray* GetArrayActivationType();

        /**
        * Gets the activation type string
        *@param type - activation type
        *@return the activation type string
        */
        static CString GetActivationTypeString(int type);

        /**
        * Gets the activation type
        *@param type - activation type string
        *@return the activation type
        */
        static int GetActivationType(const CString& type);

        /**
        * Gets the primary language identifier from LCID
        *@param lcid - lcid
        *@return the primary language identifier
        */
        static inline WORD GetPrimaryLanguageIDFromLCID(LCID lcid);

        /**
        * Gets the sub-language identifier from LCID
        *@param lcid - lcid
        *@return the sub-language identifier
        */
        static inline WORD GetSubLanguageIDFromLCID(LCID lcid);

        /**
        * Gets the sort language identifier from LCID
        *@param lcid - lcid
        *@return the sort language identifier
        */
        static inline WORD GetSortLanguageIDFromLCID(LCID lcid);

        /**
        * Makes the LCID from a language ID
        *@param primaryLID - primary language identifier
        *@param subID - sub-language identifier
        *@param sortID - sort identifier
        *@return the newly created LCID, 0 on error
        */
        static inline LCID MakeLCIDFromLanguageID(WORD primaryLID,
                                                  WORD subLID = SUBLANG_DEFAULT,
                                                  WORD sortID = SORT_DEFAULT);

        /**
        * Gets a language identifier from a LCID
        *@param lcid - lcid to get from
        *@param[out] primaryLID - primary language identifier
        *@param[out] subID - sub-language identifier
        *@param[out] sortID - sort identifier
        */
        static inline void GetLanguageIDsFromLCID(LCID lcid, WORD& primaryLID, WORD& subLID, WORD& sortID);

        /**
        * Gets the full month string
        *@param monthIndex - month index
        *@param lcid - lcid
        *@return the full month string
        */
        static const CString GetFullMonth(std::size_t monthIndex, LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the full month string
        *@param monthIndex - month index
        *@param primaryLID - primary language identifier
        *@return the full month string
        */
        static const CString GetFullMonth(std::size_t monthIndex, WORD primaryLID);

        /**
        * Gets the short month string
        *@param monthIndex - month index
        *@param lcid - lcid
        *@return the short month string
        */
        static const CString GetShortMonth(std::size_t monthIndex, LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the short month string
        *@param monthIndex - month index
        *@param primaryLID - primary language identifier
        *@return the short month string
        */
        static const CString GetShortMonth(std::size_t monthIndex, WORD primaryLID);

        /**
        * Gets the full day string
        *@param dayIndex - day index
        *@param lcid - lcid
        *@return the full day string
        */
        static const CString GetFullDay(std::size_t dayIndex, LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the full day string
        *@param dayIndex - day index
        *@param primaryLID - primary language identifier
        *@return the full day string
        */
        static const CString GetFullDay(std::size_t dayIndex, WORD primaryLID);

        /**
        * Gets the short day string
        *@param dayIndex - day index
        *@param lcid - lcid
        *@return the short day string
        */
        static const CString GetShortDay(std::size_t dayIndex, LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the short day string
        *@param dayIndex - day index
        *@param primaryLID - primary language identifier
        *@return the short day string
        */
        static const CString GetShortDay(std::size_t dayIndex, WORD primaryLID);

        /**
        * Gets the month prefix
        *@param lcid - lcid
        *@return the month prefix
        */
        static const CString GetMonthPrefix(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the month prefix
        *@param primaryLID - primary language identifier
        *@return the month prefix
        */
        static const CString GetMonthPrefix(WORD primaryLID);

        /**
        * Gets the month short prefix
        *@param lcid - lcid
        *@return the month short prefix
        */
        static const CString GetMonthShortPrefix(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the month short prefix
        *@param primaryLID - primary language identifier
        *@return the month short prefix
        */
        static const CString GetMonthShortPrefix(WORD primaryLID);

        /**
        * Gets the week prefix
        *@param lcid - lcid
        *@return the week prefix
        */
        static const CString GetWeekPrefix(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the week prefix
        *@param primaryLID - primary language identifier
        *@return the week prefix
        */
        static const CString GetWeekPrefix(WORD primaryLID);

        /**
        * Gets the week short prefix
        *@param lcid - lcid
        *@return the week short prefix
        */
        static const CString GetWeekShortPrefix(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the week short prefix
        *@param primaryLID - primary language identifier
        *@return the week short prefix
        */
        static const CString GetWeekShortPrefix(WORD primaryLID);

        /**
        * Gets the day prefix
        *@param lcid - lcid
        *@return the day prefix
        */
        static const CString GetDayPrefix(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the day prefix
        *@param primaryLID - primary language identifier
        *@return the day prefix
        */
        static const CString GetDayPrefix(WORD primaryLID);

        /**
        * Gets the day short prefix
        *@param lcid - lcid
        *@return the day short prefix
        */
        static const CString GetDayShortPrefix(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the day short prefix
        *@param primaryLID - primary language identifier
        *@return the day short prefix
        */
        static const CString GetDayShortPrefix(WORD primaryLID);

        /**
        * Gets the hour prefix
        *@param lcid - lcid
        *@return the hour prefix
        */
        static const CString GetHourPrefix(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the hour prefix
        *@param primaryLID - primary language identifier
        *@return the hour prefix
        */
        static const CString GetHourPrefix(WORD primaryLID);

        /**
        * Gets the hour short prefix
        *@param lcid - lcid
        *@return the hour short prefix
        */
        static const CString GetHourShortPrefix(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the hour short prefix
        *@param primaryLID - primary language identifier
        *@return the hour short prefix
        */
        static const CString GetHourShortPrefix(WORD primaryLID);

        /**
        * Gets the locale currency
        *@param lcid - lcid
        *@return the locale currency
        */
        static const CString GetLocaleCurrency(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the date separator
        *@param lcid - lcid
        *@return the date separator
        */
        static const CString GetDateSeparator(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the time separator
        *@param lcid - lcid
        *@return the time separator
        */
        static const CString GetTimeSeparator(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the decimal separator
        *@param lcid - lcid
        *@return the decimal separator
        */
        static const CString GetDecimalSeparator(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Gets the thousand separator
        *@param lcid - lcid
        *@return the thousand separator
        */
        static const CString GetThousandSeparator(LCID lcid = LOCALE_USER_DEFAULT);

        /**
        * Fills a string array from a raw string content. The source string is delimited by ; separators
        *@param str - source string to parse
        *@param[out] strArray - string array to fill with source string content
        */
        static void FillArray(const CString& str, CStringArray& strArray);

    private:
        static CWnd*                    m_pModalDialogCWnd;
        static PSS_Document*            m_pCurrentDocumentForSerialization;
        static PSS_DocTemplateEx*       m_pDocTemplate;
        static PSS_DocTemplateEx*       m_pProcessDocTemplate;
        static CMultiDocTemplate*       m_pReportDocTemplate;
        static PSS_ProcessModelDocTmpl* m_pProcessModelDocumentTemplate;
        static ZUser*                   m_ConnectedUser;
        static PSS_Server*              m_pServer;
        static PSS_HistoricValueManager m_HistoricValueManager;
        static PSS_TemplateManager      m_TemplateManager;
        static PSS_TemplateManager      m_ProcessTemplateManager;
        static PSS_TemplateManager      m_ModelTemplateManager;
        static PSS_UserManager          m_UserManager;
        static PSS_Network              m_NetWork;
        static ZUMail                   m_Mail;
        static IFullMonthSet            m_FullMonthSet;
        static IShortMonthSet           m_ShortMonthSet;
        static IDaySet                  m_DaySet;
        static IEApplicationType        m_AppType;
        static CStringArray             m_ArrayYesNo;
        static CStringArray             m_WindowMode;
        static CStringArray             m_PriorityJob;
        static CStringArray             m_InsertionTypeArray;
        static CStringArray             m_ActivationTypeArray;
        static CStringArray             m_MonthPrefixArray;
        static CStringArray             m_MonthShortPrefixArray;
        static CStringArray             m_WeekPrefixArray;
        static CStringArray             m_WeekShortPrefixArray;
        static CStringArray             m_DayPrefixArray;
        static CStringArray             m_DayShortPrefixArray;
        static CStringArray             m_HourPrefixArray;
        static CStringArray             m_HourShortPrefixArray;
        static CString                  m_FileDirectory;
        static CString                  m_EventDirectory;
        static CString                  m_ApplicationDirectory;
        static CString                  m_ResponsibleUserNameKeyString;
        static CString                  m_RequestedUserNameKeyString;
        static BOOL                     m_OpenFileInSilentMode;
        static BOOL                     m_IsFormDesigner;
        static BOOL                     m_ShowAnimation;
        static BOOL                     m_MaximizeFormOnOpen;
        static BOOL                     m_DuringInitialization;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Global(const PSS_Global& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Global& operator = (const PSS_Global& other);

        /**
        * Gets the language table index
        *@param lcid - language identifier
        *@return the language table index
        */
        static std::size_t GetLanguageTableIndex(LCID lcid);

        /**
        * Gets the language table index
        *@param primaryLID - primary language identifier
        *@return the language table index
        */
        static std::size_t GetLanguageTableIndex(WORD primaryLID);

        /**
        * Loads the date array
        */
        static void LoadDateArray();

        /**
        * Loads the prefix array
        */
        static void LoadPrefixArrays();
};

//---------------------------------------------------------------------------
// PSS_Global
//---------------------------------------------------------------------------
PSS_Server* PSS_Global::GetServer()
{
    return m_pServer;
}
//---------------------------------------------------------------------------
PSS_HistoricValueManager& PSS_Global::GetHistoricValueManager()
{
    return m_HistoricValueManager;
}
//---------------------------------------------------------------------------
const BOOL PSS_Global::IsDuringInitialization()
{
    return m_DuringInitialization;
}
//---------------------------------------------------------------------------
void PSS_Global::StartInitialization()
{
    m_DuringInitialization = TRUE;
}
//---------------------------------------------------------------------------
void PSS_Global::EndInitialization()
{
    m_DuringInitialization = FALSE;
}
//---------------------------------------------------------------------------
PSS_Global::IEApplicationType PSS_Global::GetType()
{
    return m_AppType;
}
//---------------------------------------------------------------------------
void PSS_Global::SetType(IEApplicationType value)
{
    m_AppType = value;
}
//---------------------------------------------------------------------------
PSS_Document* PSS_Global::GetCurrentDocumentForSerialization()
{
    return m_pCurrentDocumentForSerialization;
}
//---------------------------------------------------------------------------
void PSS_Global::SetCurrentDocumentForSerialization(PSS_Document* value)
{
    m_pCurrentDocumentForSerialization = value;
}
//---------------------------------------------------------------------------
BOOL PSS_Global::OpenFileInSilentMode()
{
    return m_OpenFileInSilentMode;
}
//---------------------------------------------------------------------------
void PSS_Global::SetOpenFileInSilentMode(BOOL value)
{
    m_OpenFileInSilentMode = value;
}
//---------------------------------------------------------------------------
BOOL PSS_Global::IsFormDesigner()
{
    return m_IsFormDesigner;
}
//---------------------------------------------------------------------------
void PSS_Global::SetIsFormDesigner(BOOL value)
{
    m_IsFormDesigner = value;
}
//---------------------------------------------------------------------------
BOOL PSS_Global::ShowAnimation()
{
    return m_ShowAnimation;
}
//---------------------------------------------------------------------------
void PSS_Global::SetShowAnimation(BOOL value)
{
    m_ShowAnimation = value;
}
//---------------------------------------------------------------------------
BOOL PSS_Global::MaximizeFormOnOpen()
{
    return m_MaximizeFormOnOpen;
}
//---------------------------------------------------------------------------
CString PSS_Global::GetApplicationDirectory()
{
    return m_ApplicationDirectory;
}
//---------------------------------------------------------------------------
void PSS_Global::SetApplicationDirectory(const CString& value)
{
    m_ApplicationDirectory = value;
}
//---------------------------------------------------------------------------
CString PSS_Global::GetFileDirectory()
{
    return m_FileDirectory;
}
//---------------------------------------------------------------------------
void PSS_Global::SetFileDirectory(const CString& value)
{
    m_FileDirectory = value;
}
//---------------------------------------------------------------------------
CString PSS_Global::GetEventDirectory()
{
    return m_EventDirectory;
}
//---------------------------------------------------------------------------
void PSS_Global::SetEventDirectory(const CString value)
{
    m_EventDirectory = value;
}
//---------------------------------------------------------------------------
CString PSS_Global::GetFileExtension()
{
    return g_FormExtensionNoDot;
}
//---------------------------------------------------------------------------
CString PSS_Global::GetProcessFileExtension()
{
    return g_ProcessExtensionNoDot;
}
//---------------------------------------------------------------------------
CString PSS_Global::GetModelFileExtension()
{
    return g_ModelExtensionNoDot;
}
//---------------------------------------------------------------------------
PSS_TemplateManager& PSS_Global::GetTemplateManager()
{
    return m_TemplateManager;
}
//---------------------------------------------------------------------------
PSS_TemplateManager& PSS_Global::GetProcessTemplateManager()
{
    return m_ProcessTemplateManager;
}
//---------------------------------------------------------------------------
PSS_TemplateManager& PSS_Global::GetModelTemplateManager()
{
    return m_ModelTemplateManager;
}
//---------------------------------------------------------------------------
PSS_DocTemplateEx* PSS_Global::GetDocTemplate()
{
    return m_pDocTemplate;
}
//---------------------------------------------------------------------------
void PSS_Global::SetDocTemplate(PSS_DocTemplateEx* pDoc)
{
    m_pDocTemplate = pDoc;
}
//---------------------------------------------------------------------------
PSS_DocTemplateEx* PSS_Global::GetProcessDocTemplate()
{
    return m_pProcessDocTemplate;
}
//---------------------------------------------------------------------------
void PSS_Global::SetProcessDocTemplate(PSS_DocTemplateEx* pDoc)
{
    m_pProcessDocTemplate = pDoc;
}
//---------------------------------------------------------------------------
PSS_ProcessModelDocTmpl* PSS_Global::GetProcessModelDocumentTemplate()
{
    return m_pProcessModelDocumentTemplate;
}
//---------------------------------------------------------------------------
void PSS_Global::SetProcessModelDocumentTemplate(PSS_ProcessModelDocTmpl* value)
{
    m_pProcessModelDocumentTemplate = value;
}
//---------------------------------------------------------------------------
CMultiDocTemplate* PSS_Global::GetReportDocumentTemplate()
{
    return m_pReportDocTemplate;
}
//---------------------------------------------------------------------------
void PSS_Global::SetReportDocumentTemplate(CMultiDocTemplate* value)
{
    m_pReportDocTemplate = value;
}
//---------------------------------------------------------------------------
PSS_Network& PSS_Global::GetNetWork()
{
    return m_NetWork;
}
//---------------------------------------------------------------------------
ZUMail& PSS_Global::GetMail()
{
    return m_Mail;
}
//---------------------------------------------------------------------------
PSS_UserManager& PSS_Global::GetUserManager()
{
    return m_UserManager;
}
//---------------------------------------------------------------------------
const CString& PSS_Global::GetResponsibleUserNameKeyString()
{
    return m_ResponsibleUserNameKeyString;
}
//---------------------------------------------------------------------------
const CString& PSS_Global::GetRequestedUserNameKeyString()
{
    return m_RequestedUserNameKeyString;
}
//---------------------------------------------------------------------------
const ZUser* PSS_Global::GetConnectedUser()
{
    return m_ConnectedUser;
}
//---------------------------------------------------------------------------
CWnd* PSS_Global::GetModalDialogCWnd()
{
    return m_pModalDialogCWnd;
}
//---------------------------------------------------------------------------
void PSS_Global::SetModalDialogCWnd(CWnd* pWnd)
{
    m_pModalDialogCWnd = pWnd;
}
//---------------------------------------------------------------------------
void PSS_Global::ClearModalDialogCWnd()
{
    m_pModalDialogCWnd = NULL;
}
//---------------------------------------------------------------------------
CStringArray* PSS_Global::GetArrayYesNo()
{
    return &m_ArrayYesNo;
}
//---------------------------------------------------------------------------
CString PSS_Global::GetYesFromArrayYesNo()
{
    ASSERT(m_ArrayYesNo.GetSize() >= 2);
    return m_ArrayYesNo.GetAt(1);
}
//---------------------------------------------------------------------------
CString PSS_Global::GetNoFromArrayYesNo()
{
    ASSERT(m_ArrayYesNo.GetSize() >= 2);
    return m_ArrayYesNo.GetAt(0);
}
//---------------------------------------------------------------------------
CStringArray* PSS_Global::GetArrayWindowMode()
{
    return &m_WindowMode;
}
//---------------------------------------------------------------------------
CStringArray* PSS_Global::GetArrayJobPriority()
{
    return &m_PriorityJob;
}
//---------------------------------------------------------------------------
CStringArray* PSS_Global::GetArrayInsertionType()
{
    return &m_InsertionTypeArray;
}
//---------------------------------------------------------------------------
CStringArray* PSS_Global::GetArrayActivationType()
{
    return &m_ActivationTypeArray;
}
//---------------------------------------------------------------------------
WORD PSS_Global::GetPrimaryLanguageIDFromLCID(LCID lcid)
{
    // get the lang id 
    const WORD langID = LANGIDFROMLCID(lcid);

    // return the primary language id
    return PRIMARYLANGID(langID);
}
//---------------------------------------------------------------------------
WORD PSS_Global::GetSubLanguageIDFromLCID(LCID lcid)
{
    // get the lang id 
    const WORD langID = LANGIDFROMLCID(lcid);

    // return the sub language id
    return SUBLANGID(langID);
}
//---------------------------------------------------------------------------
WORD PSS_Global::GetSortLanguageIDFromLCID(LCID lcid)
{
    // get the sort id
    return SORTIDFROMLCID(lcid);
}
//---------------------------------------------------------------------------
LCID PSS_Global::MakeLCIDFromLanguageID(WORD primaryLID, WORD subLID, WORD sortID)
{
    const WORD langID = MAKELANGID(primaryLID, subLID);
    return MAKELCID(langID, sortID);
}
//---------------------------------------------------------------------------
void PSS_Global::GetLanguageIDsFromLCID(LCID lcid, WORD& primaryLID, WORD& subLID, WORD& sortID)
{
    // get the lang id
    const WORD langID = LANGIDFROMLCID(lcid);

    // get the identifiers
    sortID     = SORTIDFROMLCID(lcid);
    primaryLID = PRIMARYLANGID(langID);
    subLID     = SUBLANGID(langID);
}
//---------------------------------------------------------------------------

#endif
