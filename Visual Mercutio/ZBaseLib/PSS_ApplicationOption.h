/****************************************************************************
 * ==> PSS_ApplicationOption -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic application option management system      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/
 
#ifndef PSS_ApplicationOptionH
#define PSS_ApplicationOptionH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZUSystemOption.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Basic application option management system
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ApplicationOption : public CObject
{
    public:
        /**
        * Constructor
        *@param iniFile - initialization file
        *@param appDir - application directory
        */
        PSS_ApplicationOption(const CString& iniFile = _T(""), const CString& appDir = _T(""));

        virtual ~PSS_ApplicationOption();

        /**
        * Creates the options
        *@param iniFile - initialization file
        *@param appDir - application directory
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const CString& iniFile = _T(""), const CString& appDir = _T(""));

        /**
        * Loads the options
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadOption();

        /**
        * Saves the options
        *@param registeredInfo - if true, registered information will also be saved
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveOption(bool registeredInfo = false);

        /**
        * Saves the registered information
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveRegisteredInfo();

        /**
        * Sets the ini file
        *@param fileName - ini file name
        */
        virtual inline void SetIniFile(const CString& fileName);

        /**
        * Gets the show animation option state
        *@return the show animation option state
        */
        virtual inline const BOOL GetShowAnimation() const;

        /**
        * Sets the show animation option state
        *@param value - the show animation option state
        */
        virtual inline void SetShowAnimation(BOOL value);

        /**
        * Gets the create on startup option state
        *@return the create on startup option state
        */
        virtual inline const BOOL GetCreateOnStartup() const;

        /**
        * Sets the create on startup option state
        *@param value - the create on startup option state
        */
        virtual inline void SetCreateOnStartup(BOOL value);

        /**
        * Gets the save screen pos option state
        *@return the save screen pos option state
        */
        virtual inline const BOOL GetScreenPos() const;

        /**
        * Sets the save screen pos option state
        *@param value - the save screen pos option state
        */
        virtual inline void SetScreenPos(BOOL value);

        /**
        * Gets the print line option state
        *@return the print line option state
        */
        virtual inline const BOOL GetPrintLine() const;

        /**
        * Sets the print line option state
        *@param value - the print line option state
        */
        virtual inline void SetPrintLine(BOOL value);

        /**
        * Gets the auto-calculate option state
        *@return the auto-calculate option state
        */
        virtual inline const BOOL GetAutoCalculate() const;

        /**
        * Sets the auto-calculate option state
        *@param value - the auto-calculate option state
        */
        virtual inline void SetAutoCalculate(BOOL value);

        /**
        * Gets the open last loaded file option state
        *@return the open last loaded file option state
        */
        virtual inline const BOOL GetOpenLastLoadedFile() const;

        /**
        * Sets the open last loaded file option state
        *@param value - the open last loaded file option state
        */
        virtual inline void SetOpenLastLoadedFile(BOOL value);

        /**
        * Gets the show calculate field option state
        *@return the show calculate field option state
        */
        virtual inline const BOOL GetShowCalculateField() const;

        /**
        * Sets the show calculate field option state
        *@param value - the show calculate field option state
        */
        virtual inline void SetShowCalculateField(BOOL value);

        /**
        * Gets the show hidden fields option state
        *@return the show hidden fields option state
        */
        virtual inline const BOOL GetShowHiddenField() const;

        /**
        * Sets the show hidden field option state
        *@param value - the show hidden field option state
        */
        virtual inline void SetShowHiddenField(BOOL value);

        /**
        * Gets the show object bounds rect option state
        *@return the show object bounds rect option state
        */
        virtual inline const BOOL GetShowBoundsRect() const;

        /**
        * Sets the show object bounds rect option state
        *@param value - the show object bounds rect option state
        */
        virtual inline void SetShowBoundsRect(BOOL value);

        /**
        * Gets the app must go automatically on the next edit after enter option state
        *@return the app must go automatically on the next edit after enter option state
        */
        virtual inline const BOOL GetGoNextEdit() const;

        /**
        * Sets the app must go automatically on the next edit after enter option state
        *@param value - the app must go automatically on the next edit after enter option state
        */
        virtual inline void SetGoNextEdit(BOOL value);

        /**
        * Gets the export file name
        *@return the export file name
        */
        virtual inline const CString GetExportFileName() const;

        /**
        * Sets the export file name
        *@param value - the export file name
        */
        virtual inline void SetExportFileName(const CString& value);

        /**
        * Gets the schema name to export
        *@return the schema name to export
        */
        virtual inline const CString GetExportSchemaName() const;

        /**
        * Sets the schema name to export
        *@param value - the schema name to export
        */
        virtual inline void SetExportSchemaName(const CString& value);

        /**
        * Gets the propagation mode (used during importation) option state
        *@return the propagation mode (used during importation) option state
        */
        virtual inline const int GetExportPropagationMode() const;

        /**
        * Sets the propagation mode (used during importation) option state
        *@param value - the propagation mode (used during importation) option state
        */
        virtual inline void SetExportPropagationMode(int value);

        /**
        * Gets the process empty when zero for numbers on import option state
        *@return the process empty when zero for numbers on import option state
        */
        virtual inline const BOOL GetEmptyWhenZero() const;

        /**
        * Sets the process empty when zero for numbers on import option state
        *@param value - the process empty when zero for numbers on import option state
        */
        virtual inline void SetEmptyWhenZero(BOOL value);

        /**
        * Gets the requires automatic field creation option state
        *@return the requires automatic field creation option state
        */
        virtual inline const BOOL GetAutomaticFieldNameCreation() const;

        /**
        * Sets the requires automatic field creation option state
        *@param value - the requires automatic field creation option state
        */
        virtual inline void SetAutomaticFieldNameCreation(BOOL value);

        /**
        * Gets the maximize form on open option state
        *@return the maximize form on open option state
        */
        virtual inline const BOOL GetMaximizeFormOnOpen() const;

        /**
        * Sets the maximize form on open option state
        *@param value - the maximize form on open option state
        */
        virtual inline void SetMaximizeFormOnOpen(BOOL value);

        /**
        * Gets the show welcome screen option state
        *@return the show welcome screen option state
        */
        virtual inline const BOOL GetShowWelcomeScreen() const;

        /**
        * Sets the show welcome screen option state
        *@param value - the show welcome screen option state
        */
        virtual inline void SetShowWelcomeScreen(BOOL value);

        /**
        * Gets the trace of the last loaded file name should be kept option state
        *@return the trace of the last loaded file should be kept option state
        */
        virtual inline const CString GetLastLoadedFileName() const;

        /**
        * Sets the trace of the last loaded file name should be kept option state
        *@param value - the trace of the last loaded file should be kept option state
        */
        virtual inline void SetLastLoadedFileName(const CString& value);

        /**
        * Gets the server ini file name
        *@return the server ini file name
        */
        virtual inline const CString GetServerIniFileName() const;

        /**
        * Sets the server ini file name
        *@param value - the server ini file name
        */
        virtual inline void SetServerIniFileName(const CString& value);

        /**
        * Gets the risk type file name
        *@return the risk type file name
        */
        virtual inline const CString GetRiskTypeFileName() const;

        /**
        * Sets the risk type file name
        *@param value - the risk type file name
        */
        virtual inline void SetRiskTypeFileName(const CString& value);

        /**
        * Gets the risk impact file name
        *@return the risk impact file name
        */
        virtual inline const CString GetRiskImpactFileName() const;

        /**
        * Sets the risk impact file name
        *@param value - the risk impact file name
        */
        virtual inline void SetRiskImpactFileName(const CString& value);

        /**
        * Gets the risk probability file name
        *@return the risk probability file name
        */
        virtual inline const CString GetRiskProbabilityFileName() const;

        /**
        * Sets the risk probability file name
        *@param value - the risk probability file name
        */
        virtual inline void SetRiskProbabilityFileName(const CString& value);

        /**
        * Gets the first use option state
        *@return the first use option state
        */
        virtual inline BOOL GetFirstUse();

        /**
        * Gets the force network connection option state
        *@return the force network connection option state
        */
        virtual inline const BOOL GetForceNetworkConnection() const;

        /**
        * Sets the force network connection option state
        *@param value - the force network connection option state
        */
        virtual inline void SetForceNetworkConnection(BOOL value);

        /**
        * Gets the don't show tooltip option state
        *@return the don't show tooltip option state
        */
        virtual inline const BOOL GetDontShowToolTip() const;

        /**
        * Sets the don't show tooltip option state
        *@param value - the don't show tooltip option state
        */
        virtual inline void SetDontShowToolTip(BOOL value);

        /**
        * Gets the don't show task list option state
        *@return the don't show task list option state
        */
        virtual inline const BOOL GetDontShowTaskList() const;

        /**
        * Sets the don't show task list option state
        *@param value - the don't show task list option state
        */
        virtual inline void SetDontShowTaskList(BOOL value);

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
        virtual inline CString GetRegisteredCompanyName() const;

        /**
        * Sets the registered company name
        *@param value - the registered company name
        */
        virtual inline void SetRegisteredCompanyName(const CString& value);

        /**
        * Gets the registered product key
        *@return the registered product key
        */
        virtual inline CString GetRegisteredProductKey() const;

        /**
        * Sets the registered product key
        *@param value - the registered product key
        */
        virtual inline void SetRegisteredProductKey(const CString& value);

    protected:
        ZUSystemOption m_SystemOption;
        CString        m_ExportFileName;
        CString        m_ExportSchemaName;
        CString        m_LastLoadedFileName;
        CString        m_ServerIniFileName;
        CString        m_RegisteredUserName;
        CString        m_RegisteredCompanyName;
        CString        m_RegisteredProductKey;
        CString        m_RiskTypeFileName;
        CString        m_RiskImpactFileName;
        CString        m_RiskProbabilityFileName;
        CString        m_AppDir;
        int            m_ExportPropagationMode;
        BOOL           m_OpenLastLoadedFile;
        BOOL           m_GoNextEdit;
        BOOL           m_EmptyWhenZero;
        BOOL           m_AutomaticFieldNameCreation;
        BOOL           m_MaximizeFormOnOpen;
        BOOL           m_ShowWelcomeScreen;
        BOOL           m_ForceNetworkConnection;
        BOOL           m_DontShowToolTip;
        BOOL           m_DontShowTaskList;
        BOOL           m_AnimationShow;
        BOOL           m_CreateOnStartup;
        BOOL           m_ScreenPos;
        BOOL           m_PrintLine;
        BOOL           m_AutoCalculate;
        BOOL           m_CalculateFieldShow;
        BOOL           m_ShowHiddenField;
        BOOL           m_ShowBoundsRect;
        BOOL           m_FirstUse;

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ApplicationOption(const PSS_ApplicationOption& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ApplicationOption& operator = (const PSS_ApplicationOption& other);
};

//---------------------------------------------------------------------------
// PSS_ApplicationOption
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetIniFile(const CString& fileName)
{
    m_SystemOption.SetIniFile(fileName);
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetShowAnimation() const
{
    return m_AnimationShow;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetShowAnimation(BOOL value)
{
    m_AnimationShow = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetCreateOnStartup() const
{
    return m_CreateOnStartup;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetCreateOnStartup(BOOL value)
{
    m_CreateOnStartup = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetScreenPos() const
{
    return m_ScreenPos;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetScreenPos(BOOL value)
{
    m_ScreenPos = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetPrintLine() const
{
    return m_PrintLine;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetPrintLine(BOOL value)
{
    m_PrintLine = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetAutoCalculate() const
{
    return m_AutoCalculate;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetAutoCalculate(BOOL value)
{
    m_AutoCalculate = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetOpenLastLoadedFile() const
{
    return m_OpenLastLoadedFile;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetOpenLastLoadedFile(BOOL value)
{
    m_OpenLastLoadedFile = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetShowCalculateField() const
{
    return m_CalculateFieldShow;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetShowCalculateField(BOOL value)
{
    m_CalculateFieldShow = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetShowHiddenField() const
{
    return m_ShowHiddenField;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetShowHiddenField(BOOL value)
{
    m_ShowHiddenField = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetShowBoundsRect() const
{
    return m_ShowBoundsRect;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetShowBoundsRect(BOOL value)
{
    m_ShowBoundsRect = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetGoNextEdit() const
{
    return m_GoNextEdit;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetGoNextEdit(BOOL value)
{
    m_GoNextEdit = value;
}
//---------------------------------------------------------------------------
const CString PSS_ApplicationOption::GetExportFileName() const
{
    return m_ExportFileName;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetExportFileName(const CString& value)
{
    m_ExportFileName = value;
}
//---------------------------------------------------------------------------
const CString PSS_ApplicationOption::GetExportSchemaName() const
{
    return m_ExportSchemaName;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetExportSchemaName(const CString& value)
{
    m_ExportSchemaName = value;
}
//---------------------------------------------------------------------------
const int PSS_ApplicationOption::GetExportPropagationMode() const
{
    return m_ExportPropagationMode;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetExportPropagationMode(int value)
{
    m_ExportPropagationMode = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetEmptyWhenZero() const
{
    return m_EmptyWhenZero;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetEmptyWhenZero(BOOL value)
{
    m_EmptyWhenZero = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetAutomaticFieldNameCreation() const
{
    return m_AutomaticFieldNameCreation;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetAutomaticFieldNameCreation(BOOL value)
{
    m_AutomaticFieldNameCreation = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetMaximizeFormOnOpen() const
{
    return m_MaximizeFormOnOpen;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetMaximizeFormOnOpen(BOOL value)
{
    m_MaximizeFormOnOpen = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetShowWelcomeScreen() const
{
    return m_ShowWelcomeScreen;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetShowWelcomeScreen(BOOL value)
{
    m_ShowWelcomeScreen = value;
}
//---------------------------------------------------------------------------
const CString PSS_ApplicationOption::GetLastLoadedFileName() const
{
    return m_LastLoadedFileName;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetLastLoadedFileName(const CString& value)
{
    m_LastLoadedFileName = value;
}
//---------------------------------------------------------------------------
const CString PSS_ApplicationOption::GetServerIniFileName() const
{
    return m_ServerIniFileName;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetServerIniFileName(const CString& value)
{
    m_ServerIniFileName = value;
}
//---------------------------------------------------------------------------
const CString PSS_ApplicationOption::GetRiskTypeFileName() const
{
    return m_RiskTypeFileName;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetRiskTypeFileName(const CString& value)
{
    m_RiskTypeFileName = value;
}
//---------------------------------------------------------------------------
const CString PSS_ApplicationOption::GetRiskImpactFileName() const
{
    return m_RiskImpactFileName;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetRiskImpactFileName(const CString& value )
{
    m_RiskImpactFileName = value;
}
//---------------------------------------------------------------------------
const CString PSS_ApplicationOption::GetRiskProbabilityFileName() const
{
    return m_RiskProbabilityFileName;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetRiskProbabilityFileName(const CString& value)
{
    m_RiskProbabilityFileName = value;
}
//---------------------------------------------------------------------------
BOOL PSS_ApplicationOption::GetFirstUse()
{
    return m_FirstUse;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetForceNetworkConnection() const
{
    return m_ForceNetworkConnection;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetForceNetworkConnection(BOOL value)
{
    m_ForceNetworkConnection = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetDontShowToolTip() const
{
    return m_DontShowToolTip;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetDontShowToolTip(BOOL value)
{
    m_DontShowToolTip = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_ApplicationOption::GetDontShowTaskList() const
{
    return m_DontShowTaskList;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetDontShowTaskList(BOOL value)
{
    m_DontShowTaskList = value;
}
//---------------------------------------------------------------------------
CString PSS_ApplicationOption::GetRegisteredUserName() const
{
    return m_RegisteredUserName;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetRegisteredUserName(const CString& value)
{
    m_RegisteredUserName = value;
}
//---------------------------------------------------------------------------
CString PSS_ApplicationOption::GetRegisteredCompanyName() const
{
    return m_RegisteredCompanyName;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetRegisteredCompanyName(const CString& value)
{
    m_RegisteredCompanyName = value;
}
//---------------------------------------------------------------------------
CString PSS_ApplicationOption::GetRegisteredProductKey() const
{
    return m_RegisteredProductKey;
}
//---------------------------------------------------------------------------
void PSS_ApplicationOption::SetRegisteredProductKey(const CString& value)
{
    m_RegisteredProductKey = value;
}
//---------------------------------------------------------------------------

#endif