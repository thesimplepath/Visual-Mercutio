/****************************************************************************
 * ==> PSS_MainApp ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the basic main application interface              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MainAppH
#define PSS_MainAppH

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

// uncomment this line to enable special security checks
//#define CHECK_INFO

// processsoft
#include "zBaseLib\PSS_PlanFinObsoleteObjects.h"
#include "zBaseLib\PSS_Document.h"
#include "zBaseLib\PSS_DocTemplateEx.h"
#include "zBaseLib\PSS_ProcessModelDocTmpl.h"
#include "zBaseLib\PSS_SingleInstanceApplication.h"
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Server.h"
#include "zBaseLib\PSS_FontManager.h"
#include "zBaseLib\PSS_StyleManager.h"
#include "zBaseLib\PSS_TemplateManager.h"
#include "zBaseLib\PSS_ApplicationOption.h"
#include "zBaseLib\PSS_FieldRepository.h"
#include "zBaseLib\PSS_GlobalFieldDocument.h"
#include "zBaseLib\PSS_Global.h"
#ifdef CHECK_INFO
    #include "zBaseLib\PSS_CryptedFileApplicationTypeInfo.h"
#endif
#include "zEvent\PSS_ActivityLog.h"
#include "PSS_TemplateDocument.h"
#include "PSS_ModifyView.h"
#include "PSS_ExternalBoxFunctions.h"
#include "PSS_MainFrame.h"
#include "planfin.hdf"

// windows
#include <CTYPE.H>
#include <locale.h>

#ifndef _WIN32
    extern "C" extern void WINAPI InitZResDLL();
    extern "C" extern void WINAPI InitZWinUtilDLL();

    // three external functions to enable 3d controls
    #ifdef __cplusplus
        extern "C"
        {
            #endif
                int FAR PASCAL Ctl3dRegister(HANDLE);
                int FAR PASCAL Ctl3dAutoSubclass(HANDLE);
                int FAR PASCAL Ctl3dUnregister(HANDLE);
            #ifdef __cplusplus
        }
    #endif
#endif

// scope symbols in stingray foundation library
using namespace sfl;

/**
* Basic main application interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_MainApp : public PSS_SingleInstanceApplication,
                    public PSS_Subject,
                    public PSS_TemplateDocument<PSS_TemplateFunctionNoopAccessor>
{
    DECLARE_DYNAMIC(PSS_MainApp)

    public:
        typedef PSS_SingleInstanceApplication inherited;

        PSS_MainApp();
        virtual ~PSS_MainApp();

        /**
        * Initializes the application instance
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitInstance();

        /**
        * Exits the application instance
        *@return the modal result
        */
        virtual int ExitInstance();

        /**
        * Exits the application
        *@return TRUE if the application is allowed to exit, otherwise FALSE
        */
        virtual BOOL ExitApp();

        /**
        * Gets the main window
        *@return the main window
        */
        virtual inline PSS_MainFrame* GetMainWindow();

        /**
        * Selects the server
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SelectServer();

        /**
        * Gets the server
        *@return the server
        */
        virtual inline const PSS_CltServer& GetServer() const;
        virtual inline       PSS_CltServer& GetServer();

        /**
        * Gets the server ini file
        *@return the server ini file
        */
        virtual inline CString GetServerIniFile() const;

        /**
        * Sets the server ini file
        *@param value - the server ini file
        */
        virtual inline void SetServerIniFile(const CString& value);

        /**
        * Gets the file directory
        *@return the file directory
        */
        virtual inline CString GetFileDirectory() const;

        /**
        * Sets the file directory
        *@param value - the file directory
        */
        virtual inline void SetFileDirectory(const CString& value);

        /**
        * Gets the application name
        *@return the application name
        */
        virtual inline CString GetApplicationName() const;

        /**
        * Gets the application directory
        *@return the application directory
        */
        virtual CString GetApplicationDir() const;

        /**
        * Gets the application type
        *@return the application type
        */
        virtual PSS_Global::IEApplicationType GetApplicationType() const = 0;

        /**
        * Gets the application registry key
        *@return the application registry key
        */
        virtual inline CString GetApplicationRegistryKey() const;

        /**
        * Gets the application registry key for the product ID
        *@return the application registry key for the product ID
        */
        virtual inline CString GetApplicationRegistryProductEntryKey() const;

        /**
        * Gets the registered user name
        *@return the registered user name
        */
        virtual inline CString GetRegisteredUserName() const;

        /**
        * Sets the registered user name
        *@param value - the registered user name
        */
        virtual inline void SetRegisteredUserName(const CString& value);

        /**
        * Gets the registered company name
        *@return the registered company name
        */
        virtual inline CString GetRegisteredCompanyName();

        /**
        * Sets the registered company name
        *@param value - the registered company name
        */
        virtual inline void SetRegisteredCompanyName(const CString& value);

        /**
        * Gets the registered product key
        *@return the registered product key
        */
        virtual inline CString GetRegisteredProductKey();

        /**
        * Sets the registered product key
        *@param value - the registered product key
        */
        virtual inline void SetRegisteredProductKey(const CString& value);

        /**
        * Gets the application options
        *@return the application options
        */
        virtual inline const PSS_ApplicationOption& GetApplicationOptions() const;
        virtual inline       PSS_ApplicationOption& GetApplicationOptions();

        /**
        * Loads the application options
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadApplicationOptions() = 0;

        /**
        * Saves the application options
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveApplicationOptions() = 0;

        /**
        * Checks if the user needs to be authenticated
        *@return TRUE if the system needs to authenticate the user before starting the application, otherwise FALSE
        */
        virtual BOOL UserAuthenticationRequired() const = 0;

        /**
        * Opens the field repository in read-only mode
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OpenFieldRepositoryReadOnly() const = 0;

        /**
        * Checks if the user file should be loaded
        *@return TRUE if the user file should be loaded, otherwise FALSE
        */
        virtual BOOL LoadUserFile() const = 0;

        /**
        * Opens a document from a file
        *@param pFileName - the document file name
        *@return the opened document, NULL on error
        *@note This function may also be called from the DDE
        */
        virtual CDocument* OpenDocumentFile(LPCTSTR pFileName);

        /**
        * Checks if the document is already open
        *@return TRUE if the document is already open, otherwise FALSE
        */
        virtual BOOL IsDocumentOpen(const CString& fileName);

        /**
        * Saves all modified document without prompting for save, except for new document without names
        *@return true on success, otherwise false
        */
        virtual bool SaveAllModifiedNoPrompt();

        /**
        * Builds the template name
        *@param[out] name - the template name on function ends
        *@param stamp - the stamp
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL BuildTemplateName(CString& name, PSS_Stamp& stamp);

        /**
        * Gets the template directory
        *@return the template directory
        */
        virtual inline CString GetTemplateDirectory() const;

        /**
        * Sets the template directory
        *@return the template directory
        */
        virtual inline void SetTemplateDirectory(const CString& value);

        /**
        * Notifies that the directory name has changed
        */
        virtual void TemplateDirectoryHasChanged();

        /**
        * Gets the normal template name
        *@return the normal template name
        */
        virtual inline CString GetNormalTemplate() const;

        /**
        * Gets the process template directory
        *@return the process template directory
        */
        virtual inline CString GetProcessTemplateDirectory() const;

        /**
        * Sets the process template directory
        *@param value - the process template directory
        */
        virtual inline void SetProcessTemplateDirectory(const CString& value);

        /**
        * Notifies that the process template directory has changed
        */
        virtual void ProcessTemplateDirectoryHasChanged();

        /**
        * Gets the normal process template name
        *@return the normal process template name
        */
        virtual inline CString GetNormalProcessTemplate() const;

        /**
        * Gets the model template directory
        *@return the model template directory
        */
        virtual inline CString GetModelTemplateDirectory() const;

        /**
        * Sets the model template directory
        *@param value - the model template directory
        */
        virtual inline void SetModelTemplateDirectory(const CString& value);

        /**
        * Notifies that the model template directory has changed
        */
        virtual void ModelTemplateDirectoryHasChanged();

        /**
        * Gets the model template name
        *@return the model template name
        */
        virtual inline CString GetNormalModelTemplate() const;

        /**
        * Gets the model unit directory
        *@return the model unit directory
        */
        virtual inline CString GetModelUnitDirectory() const;

        /**
        * Sets the model unit directory
        *@param value - the model unit directory
        */
        virtual inline void SetModelUnitDirectory(const CString& value);

        /**
        * Gets the root directory
        *@return the root directory
        */
        virtual inline CString GetRootDirectory() const;

        /**
        * Sets the root directory
        *@param value - the root directory
        */
        virtual inline void SetRootDirectory(const CString& value);

        /**
        * Gets the system directory
        *@return the system directory
        */
        virtual inline CString GetSystemDirectory() const;

        /**
        * Gets the event directory
        *@return the event directory
        */
        virtual inline CString GetEventDirectory() const;

        /**
        * Gets the interface directory
        *@return the interface directory
        */
        virtual inline CString GetInterfaceDirectory() const;

        /**
        * Gets the logs directory
        *@return the logs directory
        */
        virtual inline CString GetLogDirectory() const;

        /**
        * Gets the user directory
        *@return the user directory
        */
        virtual inline CString GetUserDirectory() const;

        /**
        * Gets the user definition file
        *@return the user definition file
        */
        virtual inline CString GetUserDefinitionFile() const;

        /**
        * Gets the global field name repository
        *@return the global field name repository
        */
        virtual inline CString GetGlobalFieldNameRepository() const;

        /**
        * Sets the global field name repository
        *@param value - the global field name repository
        */
        virtual inline void SetGlobalFieldNameRepository(const CString& value);

        /**
        * Gets the log file name
        *@return the log file name
        */
        virtual inline CString GetLogFile() const;

        /**
        * Gets the log database file name
        *@return the log database file name
        */
        virtual inline CString GetLogDatabaseFile() const;

        /**
        * Gets if the log text file should be used
        *@return TRUE if the log text file should be used, otherwise FALSE
        */
        virtual inline BOOL GetUseLogTextFile() const;

        /**
        * Sets if the log text file should be used
        *@param value - if TRUE, the log text file should be used
        */
        virtual inline void SetUseLogTextFile(BOOL value);

        /**
        * Gets if the log database file should be used
        *@return TRUE if the log database file should be used, otherwise FALSE
        */
        virtual inline BOOL GetUseLogDatabaseFile() const;

        /**
        * Sets if the log database file should be used
        *@param value - if TRUE, the log database file should be used
        */
        virtual inline void SetUseLogDatabaseFile(BOOL value);

        /**
        * Gets if the folder name should be used as a file
        *@return TRUE if the folder name should be used as a file, otherwise FALSE
        */
        virtual inline const BOOL GetUseFolderNameAsFile() const;

        /**
        * Sets if the folder name should be used as a file
        *@param value - if TRUE, the folder name should be used as a file
        */
        virtual inline void SetUseFolderNameAsFile(BOOL value);

        /**
        * Gets if the user file should be stored by the user
        *@return TRUE if the user file should be stored by the user, otherwise FALSE
        */
        virtual inline const BOOL GetStoreUserFileByUser() const;

        /**
        * Sets if the user file should be stored by the user
        *@param value - if TRUE, the user file should be stored by the user
        */
        virtual inline void SetStoreUserFileByUser(BOOL value);

        /**
        * Checks if the welcome screen should be shown
        *@return TRUE if the welcome screen should be shown, otherwise FALSE
        */
        virtual inline BOOL ShowWelcomeScreen() const;

        /**
        * Sets if the welcome screen should be shown
        *@param value - if TRUE, the welcome screen should be shown
        */
        virtual inline void SetShowWelcomeScreen(const BOOL value);

        /**
        * Checks if the form should be maximized on open
        *@return TRUE if the form should be maximized on open, otherwise FALSE
        */
        virtual inline BOOL MaximizeFormOnOpen() const;

        /**
        * Checks if the auto-calculation mode is enabled
        *@return TRUE if the auto-calculation mode is enabled, otherwise FALSE
        */
        virtual inline BOOL IsAutoCalculate() const;

        /**
        * Moves the focus to the next edit which may receive it
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL GoNextEdit() const;

        /**
        * Gets if the calculated fields should be shown
        *@return TRUE if the calculated fields should be shown, otherwise FALSE
        */
        virtual inline BOOL ShowCalculateField() const;

        /**
        * Gets if the hidden fields should be shown
        *@return TRUE if the hidden fields should be shown, otherwise FALSE
        */
        virtual inline BOOL ShowHiddenField() const;

        /**
        * Gets if the bounding rects should be shown
        *@return TRUE if the bounding rects should be shown, otherwise FALSE
        */
        virtual inline BOOL ShowBoundsRect() const;

        /**
        * Gets if the animations should be shown
        *@return TRUE if the animations should be shown, otherwise FALSE
        */
        virtual inline BOOL ShowAnimation() const;

        /**
        * Gets if the create form dialog should be shown on startup
        *@return TRUE if the create form dialog should be shown on startup, otherwise FALSE
        */
        virtual inline BOOL ShowCreateFormsOnStartup() const;

        /**
        * Checks if the last loaded file should be opened
        *@return TRUE if the last loaded file should be opened, otherwise FALSE
        */
        virtual inline BOOL MustOpenLastLoadedFile() const;

        /**
        * Gets the last loaded file name
        *@return the last loaded file name
        */
        virtual inline const CString GetLastLoadedFileName() const;

        /**
        * Sets the last loaded file name
        *@param value - the last loaded file name
        */
        virtual inline void SetLastLoadedFileName(const CString& value);

        /**
        * Gets if the automatic field name creation option is enabled
        *@return TRUE if the automatic field name creation option is enabled, otherwise FALSE
        */
        virtual inline BOOL AutomaticFieldNameCreation() const;

        /**
        * Gets the export schema name
        *@return the export schema name
        */
        virtual inline const CString GetExportSchemaName() const;

        /**
        * Gets the export propagation mode
        *@return the export propagation mode
        */
        virtual inline const int GetExportPropagationMode() const;

        /**
        * Checks if the fields become empty when their content is equal to 0
        *@return TRUE if the fields become empty when their content is equal to 0, otherwise FALSE
        */
        virtual inline BOOL GetEmptyWhenZero() const;

        /**
        * Checks if the network connection should be forced
        *@return TRUE if the network connection should be forced, otherwise FALSE
        */
        virtual inline BOOL ForceNetworkConnection() const;

        /**
        * Sets if the network connection should be forced
        *@param value - if TRUE, the network connection should be forced
        */
        virtual inline void SetForceNetworkConnection(const BOOL value);

        /**
        * Checks if the tooltip shouldn't be shown
        *@return TRUE if the tooltip shouldn't be shown, otherwise FALSE
        */
        virtual inline BOOL DontShowToolTip();

        /**
        * Sets if the tooltip shouldn't be shown
        *@param value - if TRUE, the tooltip shouldn't be shown
        */
        virtual inline void SetDontShowToolTip(const BOOL value);

        /**
        * Checks if the task list shouldn't be shown
        *@return TRUE if the task list shouldn't be shown, otherwise FALSE
        */
        virtual inline BOOL DontShowTaskList() const;

        /**
        * Sets if the task list shouldn't be shown
        *@param value - if TRUE, the task list shouldn't be shown
        */
        virtual inline void SetDontShowTaskList(const BOOL value);

        /**
        * Refreshes the current schema
        */
        virtual inline void RefreshCurrentSchema();

        /**
        * Processes the message filter
        *@param code - the message code
        *@param pMsg - the message
        */
        virtual BOOL ProcessMessageFilter(int code, LPMSG pMsg);

        /**
        * Checks if the design should be saved
        *@return TRUE if the design should be saved, otherwise FALSE
        */
        virtual inline BOOL ShouldSaveDesign() const;

        /**
        * Checks if the line should be printed
        *@return TRUE if the line should be printed, otherwise FALSE
        */
        virtual inline BOOL ShouldPrintLine() const;

        /**
        * Gets the active document
        *@return the active document
        */
        virtual inline PSS_Document* GetActiveDocument();

        /**
        * Gets the active base document
        *@return the active base document
        */
        virtual inline PSS_BaseDocument* GetActiveBaseDocument();

        /**
        * Gets the active base CDocument
        *@return the active base CDocument
        */
        virtual inline CDocument* GetActiveCDocument();

        /**
        * Gets the current document style manager
        *@return the current document style manager
        */
        virtual inline PSS_StyleManager& GetStyleManager();

        /**
        * Gets the current document font manager
        *@return the current document font manager
        */
        virtual inline PSS_FontManager& GetFontManager();

        /**
        * Draws a sample text
        *@param pDC - the device context to draw to
        *@param value - the value to show
        *@param rect - the rectangle surrounding the value to show
        *@param hFont - the font handle to use to draw the value
        *@param hStyle - the style handle to use to draw the value
        */
        virtual void DrawSampleText(CDC*              pDC,
                                    const CString&    value,
                                    const CRect&      rect,
                                    PSS_Font::Handle  hFont  = g_NoFontDefined,
                                    PSS_Style::Handle hStyle = g_NoStyleDefined);

        /**
        * Shows a sample text
        *@param pDC - the device context to draw to
        *@param value - the value to show
        *@param rect - the rectangle surrounding the value to show
        *@param pFont - the font to use to draw the value
        *@param pStyle - the style to use to draw the value
        */
        virtual void DrawSampleText(CDC*           pDC,
                                    const CString& value,
                                    const CRect&   rect,
                                    PSS_Font*      pFont  = NULL,
                                    PSS_Style*     pStyle = NULL);

        /**
        * Checks if the cursor capture is still valid
        *@param point - the cursor position
        *@param pView - the view to check against
        *@return TRUE if the cursor capture is still valid, otherwise FALSE
        */
        virtual BOOL IsCapturedCursorValid(const CPoint& point, PSS_View* pView);

        /**
        * Gets the field repository
        *@return the field repository
        */
        virtual inline PSS_FieldRepository* GetFieldRepository();

        /**
        * Gets the current document
        *@return the current document
        */
        virtual inline PSS_Document* GetCurrentDocument() const;

        /**
        * Sets the current document
        *@param pDoc - the current document
        */
        virtual inline void SetCurrentDocument(PSS_Document* pDoc);

        /**
        * Gets the opened document list
        *@param docList - the document list to populate
        */
        virtual void GetDocumentList(CObList& docList) const;

        /**
        * Gets the opened document file name array
        *@param fileArray - the file name array to populate
        */
        virtual void GetDocumentArrayName(CStringArray& fileArray);

        /**
        * Checks if the documents should be open in read-only mode
        *@return TRUE if the documents should be open in read-only mode, otherwise FALSE
        */
        virtual BOOL ReadOnlyDocuments() const = 0;

        /**
        * Gets if the application is working locally
        *@return TRUE if the application is working locally, otherwise FALSE
        */
        virtual BOOL IsWorkingLocaly() const = 0;

        /**
        * Gets the activity log
        *@return the activity log
        */
        virtual inline PSS_ActivityLog& GetActivityLog();

        /**
        * Calls the Windows help
        *@param data - the help data
        *@param cmd - the help command
        */
        virtual void WinHelp(DWORD data, UINT cmd = HELP_CONTEXT);

        /**
        * Shows the warning on command
        */
        virtual void ShowWarningOnCommand();

        /**
        * Gets the status bar
        *@return the status bar
        *@throw Runtime error exception on error
        */
        virtual inline PSS_StatusBar& GetStatusBar();

        /**
        * Sets the visual tool object
        *@param className - the class name
        *@return the visual tool object
        */
        virtual void SetVisualToolObject(const CString& className) = 0;

        /**
        * Called when a command message is received
        *@param id - the message identifier
        *@param code - the message code
        *@param pExtra - the extra custom data
        *@param pHandlerInfo - the handler info
        *@return TRUE if the message was processed
        */
        virtual BOOL OnCmdMsg(UINT id, int code, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

        /**
        * Called when the windows initialization file name is changed
        */
        virtual void OnChangeWinIniFileName();

        /**
        * Gets the application directory
        *@return the application directory
        */
        #ifdef CHECK_INFO
            virtual inline PSS_CryptedFileApplicationTypeInfo::IEApplicationInfoType GetApplicationInfoType() const;
        #endif

        /**
        * Gets the product key file info
        *@return the product key file info
        */
        #ifdef CHECK_INFO
            virtual inline CString GetProductKeyFileInfo() const;
        #endif

    protected:
        typedef PSS_TemplateDocument<PSS_TemplateFunctionNoopAccessor> IClassInfo;

        PSS_Document*         m_pCurrentDocument;
        PSS_PlanFinObject*    m_pOldSelectedObj;
        PSS_ApplicationOption m_ApplicationOptions;
        PSS_FieldRepository*  m_pFieldRepository;
        CString               m_HelpFile;
        DWORD                 m_NumHelpIDs;
        UINT                  m_SplashID;
        UINT                  m_AboutID;
        UINT                  m_SupportID;

        /**
        * Initializes the application
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitApp();

        /**
        * Called after the application initialization
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PostInitApp();

        /**
        * Releases the application
        */
        virtual void Release();

        /**
        * Opens a server session
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OpenServerSession();

        /**
        * Registers an additional template
        *@param resID - the template resource identifier
        */
        virtual void RegisterAdditionalTemplate(UINT resID);

        /**
        * Registers the additional Shell extension files and icon facility
        *@param compat - TRUE for print and drag/drop to printer
        */
        virtual void RegisterAdditionalTemplateShellFileTypes(BOOL compat = FALSE);

        /**
        * Registers the standard Shell extension files and icon facility
        *@param compat - TRUE for print and drag/drop to printer
        */
        virtual void RegisterShellFileTypes(BOOL compat = FALSE);

        /**
        * Enables the shell open
        *@note This is a bug correction for short executable file name
        */
        virtual void EnableShellOpen();

        /**
        * Loads all the users and initialize the connected user
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadAllUsers();

        /**
        * Called when file name should be prompted
        *@param fileName - the file name to prompt
        *@param initialDir - the inital directory
        *@param titleID - the title resource identifier
        *@param flags - the flags
        *@param openFileDialog - if TRUE, the file dialog will be opened
        *@param pTemplate - the template, if NULL all document templates will be considered
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DoPromptFileName(const CString& fileName,
                                      const CString& initialDir,
                                      UINT           titleID,
                                      DWORD          flags,
                                      BOOL           openFileDialog,
                                      CDocTemplate*  pTemplate);

        /**
        * Appends the filter suffix
        *@param[in, out] filter - the filter to append, the appened filer on function end
        *@param ofn - the open file name
        *@param pTemplate - the template
        *@param pDefaultExt - the default extension
        */
        virtual void AppendFilterSuffix(CString& filter, OPENFILENAME& ofn, CDocTemplate* pTemplate, CString* pDefaultExt);

        /**
        * Called when a server was selected
        */
        virtual void OnServerChanged();

        /**
        * Called when a server was opened
        */
        virtual void OnServerHasBeenOpened();

        /**
        * Called when an additional template not covered by CDocTemplate was registered
        *@return true if the tamplate is allowed to be registered, otherwise false
        */
        virtual bool OnRegisterAdditionalTemplate();

        /**
        * Called when an additional template file is opened
        *@param pFileName - the template file name
        *@return the matching document
        */
        virtual CDocument* OnOpenAdditionalTemplateFile(LPCSTR pFileName);

        /**
        * Called when an additional template file is saved
        *@param pFileName - the template file name
        */
        virtual void OnSaveAdditionalTemplateFile(LPCSTR pFileName);

        /**
        * Called after a document was opened
        *@param pDoc - the opened document
        *@param fileName - the document file name
        */
        virtual void OnAfterOpenDocument(CDocument* pDoc, const CString& fileName);

        /**
        * Called after a document was saved
        *@param pDoc - the saved document
        */
        virtual void OnAfterSaveDocument(CDocument* pDoc);

        /**
        * Called when the help file name should be built
        *@return the built help file name
        */
        virtual CString OnBuildHelpFileName();

        /// Generated message map functions
        //{{AFX_MSG(PSS_MainApp)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_CltServer   m_Server;
        PSS_ActivityLog m_ActivityLog;

        #ifdef CHECK_INFO
            PSS_CryptedFileApplicationTypeInfo::IEApplicationInfoType m_ApplicationInfoType;
            CString                                                   m_ProductKeyFileInfo;
        #endif

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_MainApp(const PSS_MainApp& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_MainApp& operator = (const PSS_MainApp& other);

        /**
        * Loads the global field repository
        *@return TRUE on success, otherwise FALSE
        */
        BOOL LoadGlobalFieldRepository();

        /**
        * Loads the application info type
        */
        #ifdef CHECK_INFO
            void LoadApplicationInfoType();
        #endif
};

//---------------------------------------------------------------------------
// PSS_MainApp
//---------------------------------------------------------------------------
PSS_MainFrame* PSS_MainApp::GetMainWindow()
{
    return dynamic_cast<PSS_MainFrame*>(m_pMainWnd);
}
//---------------------------------------------------------------------------
const PSS_CltServer& PSS_MainApp::GetServer() const
{
    return m_Server;
}
//---------------------------------------------------------------------------
PSS_CltServer& PSS_MainApp::GetServer()
{
    return m_Server;
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetServerIniFile() const
{
    return GetApplicationOptions().GetServerIniFileName();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetServerIniFile(const CString& value)
{
    GetApplicationOptions().SetServerIniFileName(value);
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetFileDirectory() const
{
    return GetServer().GetFileDirectory();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetFileDirectory(const CString& value)
{
    GetServer().SetFileDirectory(value);
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetApplicationName() const
{
    return(_T("Plan Financier"));
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetApplicationRegistryKey() const
{
    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetApplicationRegistryProductEntryKey() const
{
    return _T("PID");
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetRegisteredUserName() const
{
    return GetApplicationOptions().GetRegisteredUserName();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetRegisteredUserName(const CString& value)
{
    GetApplicationOptions().SetRegisteredUserName(value);
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetRegisteredCompanyName()
{
    return GetApplicationOptions().GetRegisteredCompanyName();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetRegisteredCompanyName(const CString& value)
{
    GetApplicationOptions().SetRegisteredCompanyName(value);
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetRegisteredProductKey()
{
    return GetApplicationOptions().GetRegisteredProductKey();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetRegisteredProductKey(const CString& value)
{
    GetApplicationOptions().SetRegisteredProductKey(value);
}
//---------------------------------------------------------------------------
const PSS_ApplicationOption& PSS_MainApp::GetApplicationOptions() const
{
    return m_ApplicationOptions;
}
//---------------------------------------------------------------------------
PSS_ApplicationOption& PSS_MainApp::GetApplicationOptions()
{
    return m_ApplicationOptions;
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetTemplateDirectory() const
{
    return GetServer().GetTemplateDirectory();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetTemplateDirectory(const CString& value)
{
    GetServer().SetTemplateDirectory(value);
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetNormalTemplate() const
{
    return GetServer().GetNormalTemplate();
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetProcessTemplateDirectory() const
{
    return GetServer().GetProcessTemplateDirectory();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetProcessTemplateDirectory(const CString& value)
{
    GetServer().SetProcessTemplateDirectory(value);
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetNormalProcessTemplate() const
{
    return GetServer().GetNormalProcessTemplate();
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetModelTemplateDirectory() const
{
    return GetServer().GetModelTemplateDirectory();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetModelTemplateDirectory(const CString& value)
{
    GetServer().SetModelTemplateDirectory(value);
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetNormalModelTemplate() const
{
    return GetServer().GetNormalModelTemplate();
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetModelUnitDirectory() const
{
    return GetServer().GetModelUnitDirectory();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetModelUnitDirectory(const CString& value)
{
    GetServer().SetModelUnitDirectory(value);
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetRootDirectory() const
{
    return GetServer().GetRootPath();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetRootDirectory(const CString& value)
{
    GetServer().SetRootPath(value);
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetSystemDirectory() const
{
    return GetServer().GetSystemDirectory();
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetEventDirectory() const
{
    return GetServer().GetEventDirectory();
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetInterfaceDirectory() const
{
    return GetServer().GetInterfaceDirectory();
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetLogDirectory() const
{
    return GetServer().GetLogDirectory();
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetUserDirectory() const
{
    return GetServer().GetUserDirectory();
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetUserDefinitionFile() const
{
    return GetServer().GetUserDefinitionFile();
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetGlobalFieldNameRepository() const
{
    return GetServer().GetGlobalFieldNameRepository();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetGlobalFieldNameRepository(const CString& value)
{
    GetServer().SetGlobalFieldNameRepository(value);
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetLogFile() const
{
    return GetServer().GetLogFile();
}
//---------------------------------------------------------------------------
CString PSS_MainApp::GetLogDatabaseFile() const
{
    return GetServer().GetLogDatabaseFile();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::GetUseLogTextFile() const
{
    return GetServer().GetUseLogTextFile();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetUseLogTextFile(BOOL value)
{
    GetServer().SetUseLogTextFile(value);
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::GetUseLogDatabaseFile() const
{
    return GetServer().GetUseLogDatabaseFile();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetUseLogDatabaseFile(BOOL value)
{
    GetServer().SetUseLogDatabaseFile(value);
}
//---------------------------------------------------------------------------
const BOOL PSS_MainApp::GetUseFolderNameAsFile() const
{
    return GetServer().GetUseFolderNameAsFile();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetUseFolderNameAsFile(BOOL value)
{
    GetServer().SetUseFolderNameAsFile(value);
}
//---------------------------------------------------------------------------
const BOOL PSS_MainApp::GetStoreUserFileByUser() const
{
    return GetServer().GetStoreUserFileByUser();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetStoreUserFileByUser(BOOL value)
{
    GetServer().SetStoreUserFileByUser(value);
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::ShowWelcomeScreen() const
{
    return GetApplicationOptions().GetShowWelcomeScreen();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetShowWelcomeScreen(const BOOL value)
{
    GetApplicationOptions().SetShowWelcomeScreen(value);
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::MaximizeFormOnOpen() const
{
    return GetApplicationOptions().GetMaximizeFormOnOpen();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::IsAutoCalculate() const
{
    return GetApplicationOptions().GetAutoCalculate();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::GoNextEdit() const
{
    return GetApplicationOptions().GetGoNextEdit();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::ShowCalculateField() const
{
    return GetApplicationOptions().GetShowCalculateField();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::ShowHiddenField() const
{
    return GetApplicationOptions().GetShowHiddenField();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::ShowBoundsRect() const
{
    return GetApplicationOptions().GetShowBoundsRect();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::ShowAnimation() const
{
    return GetApplicationOptions().GetShowAnimation();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::ShowCreateFormsOnStartup() const
{
    return GetApplicationOptions().GetCreateOnStartup();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::MustOpenLastLoadedFile() const
{
    return GetApplicationOptions().GetOpenLastLoadedFile();
}
//---------------------------------------------------------------------------
const CString PSS_MainApp::GetLastLoadedFileName() const
{
    return GetApplicationOptions().GetLastLoadedFileName();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetLastLoadedFileName(const CString& value)
{
    GetApplicationOptions().SetLastLoadedFileName(value);
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::AutomaticFieldNameCreation() const
{
    return GetApplicationOptions().GetAutomaticFieldNameCreation();
}
//---------------------------------------------------------------------------
const CString PSS_MainApp::GetExportSchemaName() const
{
    return GetApplicationOptions().GetExportSchemaName();
}
//---------------------------------------------------------------------------
const int PSS_MainApp::GetExportPropagationMode() const
{
    return GetApplicationOptions().GetExportPropagationMode();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::GetEmptyWhenZero() const
{
    return GetApplicationOptions().GetEmptyWhenZero();
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::ForceNetworkConnection() const
{
    return GetApplicationOptions().GetForceNetworkConnection();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetForceNetworkConnection(const BOOL value)
{
    GetApplicationOptions().SetForceNetworkConnection(value);
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::DontShowToolTip()
{
    return GetApplicationOptions().GetDontShowToolTip();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetDontShowToolTip(const BOOL value)
{
    GetApplicationOptions().SetDontShowToolTip(value);
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::DontShowTaskList() const
{
    return GetApplicationOptions().GetDontShowTaskList();
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetDontShowTaskList(const BOOL value)
{
    GetApplicationOptions().SetDontShowTaskList(value);
}
//---------------------------------------------------------------------------
void PSS_MainApp::RefreshCurrentSchema()
{}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::ShouldSaveDesign() const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_MainApp::ShouldPrintLine() const
{
    return m_ApplicationOptions.GetPrintLine();
}
//---------------------------------------------------------------------------
PSS_Document* PSS_MainApp::GetActiveDocument()
{
    CFrameWnd* pWnd = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

    if (!pWnd)
        return NULL;

    CFrameWnd* pActiveFrame = pWnd->GetActiveFrame();

    if (!pActiveFrame)
        return NULL;

    return dynamic_cast<PSS_Document*>(pActiveFrame->GetActiveDocument());
}
//---------------------------------------------------------------------------
PSS_BaseDocument* PSS_MainApp::GetActiveBaseDocument()
{
    CFrameWnd* pWnd = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

    if (!pWnd)
        return NULL;

    CFrameWnd* pActiveFrame = pWnd->GetActiveFrame();

    if (!pActiveFrame)
        return NULL;

    return dynamic_cast<PSS_BaseDocument*>(pActiveFrame->GetActiveDocument());
}
//---------------------------------------------------------------------------
CDocument* PSS_MainApp::GetActiveCDocument()
{
    CFrameWnd* pWnd = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

    if (!pWnd)
        return NULL;

    CFrameWnd* pActiveFrame = pWnd->GetActiveFrame();

    if (!pActiveFrame)
        return NULL;

    return pActiveFrame->GetActiveDocument();
}
//---------------------------------------------------------------------------
PSS_StyleManager& PSS_MainApp::GetStyleManager()
{
    PSS_Document* pDoc = GetActiveDocument();

    // must have a current document
    if (!pDoc)
        throw std::runtime_error("Active document is missing");

    return pDoc->GetStyleManager();
}
//---------------------------------------------------------------------------
inline PSS_FontManager& PSS_MainApp::GetFontManager()
{
    PSS_Document* pDoc = GetActiveDocument();

    // must have a current document
    if (!pDoc)
        throw std::runtime_error("Active document is missing");

    return pDoc->GetFontManager();
}
//---------------------------------------------------------------------------
PSS_FieldRepository* PSS_MainApp::GetFieldRepository()
{
    if (m_pFieldRepository)
        return (m_pFieldRepository->IsValid() ? m_pFieldRepository : NULL);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_Document* PSS_MainApp::GetCurrentDocument() const
{
    return m_pCurrentDocument;
}
//---------------------------------------------------------------------------
void PSS_MainApp::SetCurrentDocument(PSS_Document* pDoc)
{
    m_pCurrentDocument = pDoc;
}
//---------------------------------------------------------------------------
PSS_ActivityLog& PSS_MainApp::GetActivityLog()
{
    return m_ActivityLog;
}
//---------------------------------------------------------------------------
PSS_StatusBar& PSS_MainApp::GetStatusBar()
{
    PSS_MainFrame* pMainFrame = dynamic_cast<PSS_MainFrame*>(::AfxGetMainWnd());

    if (!pMainFrame)
        throw std::runtime_error("Main frame was not found");

    return pMainFrame->GetStatusBar();
}
//---------------------------------------------------------------------------
#ifdef CHECK_INFO
    PSS_CryptedFileApplicationTypeInfo::IEApplicationInfoType PSS_MainApp::GetApplicationInfoType() const
    {
        return m_ApplicationInfoType;
    }
#endif
//---------------------------------------------------------------------------
#ifdef CHECK_INFO
    CString PSS_MainApp::GetProductKeyFileInfo() const
    {
        return m_ProductKeyFileInfo;
    }
#endif
//---------------------------------------------------------------------------

#endif
