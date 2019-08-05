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
    * Loads the options
    *@return TRUE on success, otherwise FALSE
    */
    virtual BOOL LoadOption();

    /**
    * Saves the options
    *@param registeredInformation - if true, registered information will also be saved
    *@return TRUE on success, otherwise FALSE
    */
    virtual BOOL SaveOption(bool registeredInformation = false);

    /**
    * Saves the registered information
    *@return TRUE on success, otherwise FALSE
    */
    virtual BOOL SaveRegisteredInformation();

    /**
    * Creates the options
    *@param iniFile - initialization file
    *@param appDir - application directory
    *@return TRUE on success, otherwise FALSE
    */
    virtual BOOL Create(const CString& iniFile = _T(""), const CString& appDir = _T(""));

    /**
    * Sets the ini file
    *@param fileName - ini file name
    */
    virtual void SetIniFile(const CString& fileName);

    /**
    * Gets the show animation option state
    *@return the show animation option state
    */
    virtual const BOOL GetAnimationShow() const;

    /**
    * Sets the show animation option state
    *@param value - the show animation option state
    */
    virtual void SetAnimationShow(BOOL value);

    /**
    * Gets the create on startup option state
    *@return the create on startup option state
    */
    virtual const BOOL GetCreateOnStartup() const;

    /**
    * Sets the create on startup option state
    *@param value - the create on startup option state
    */
    virtual void SetCreateOnStartup(BOOL value);

    /**
    * Gets the save screen pos option state
    *@return the save screen pos option state
    */
    virtual const BOOL GetScreenPos() const;

    /**
    * Sets the save screen pos option state
    *@param value - the save screen pos option state
    */
    virtual void SetScreenPos(BOOL value);

    /**
    * Gets the print line option state
    *@return the print line option state
    */
    virtual const BOOL GetPrintLine() const;

    /**
    * Sets the print line option state
    *@param value - the print line option state
    */
    virtual void SetPrintLine(BOOL value);

    virtual const BOOL GetAutoCalculate() const;
    virtual void SetAutoCalculate(BOOL value);

    virtual const BOOL GetOpenLastLoadedFile() const;
    virtual void SetOpenLastLoadedFile(BOOL value);

    // Flag to show or not calculated fields
    virtual const BOOL GetCalculateFieldShow() const;
    virtual void SetCalculateFieldShow(BOOL value);

    // To specifiy if hidden fields must be shown.
    virtual const BOOL GetShowHiddenField() const;
    virtual void SetShowHiddenField(BOOL value);

    // Flag representing the option for showing the bound rect
    // of objects.
    virtual const BOOL GetShowBoundsRect() const;
    virtual void SetShowBoundsRect(BOOL value);

    // Defines if the application must go automatically on the
    // next edit after Enter.
    virtual const BOOL GetGoNextEdit() const;
    virtual void SetGoNextEdit(BOOL value);

    // Defines the export filename.
    virtual const CString GetExportFileName() const;
    virtual void SetExportFileName(CString value);

    // The schema name used during importation.
    virtual const CString GetExportSchemaName() const;
    virtual void SetExportSchemaName(CString value);

    // The propagation mode used during importation.
    virtual const int GetExportPropagationMode() const;
    virtual void SetExportPropagationMode(int value);

    // For the import, process empty when zero for numbers.
    virtual const BOOL GetEmptyWhenZero() const;
    virtual void SetEmptyWhenZero(BOOL value);

    // Defines if automatic field creation is required.
    virtual const BOOL GetAutomaticFieldNameCreation() const;
    virtual void SetAutomaticFieldNameCreation(BOOL value);

    virtual const BOOL GetMaximizeFormOnOpen() const;
    virtual void SetMaximizeFormOnOpen(BOOL value);

    virtual const BOOL GetShowWelcomeScreen() const;
    virtual void SetShowWelcomeScreen(BOOL value);

    // Keep a trace of the last load file.
    virtual const CString GetsLastLoadedFile() const;
    virtual void SetsLastLoadedFile(CString value);

    virtual const CString GetServerIniFile() const;
    virtual void SetServerIniFile(const CString& value);

    // JMR-MODIF - Le 8 juillet 2007 - Ajout des fonctions GetRiskTypeFile et SetRiskTypeFile.
    virtual const CString GetRiskTypeFile() const;
    virtual void SetRiskTypeFile(CString value);

    // JMR-MODIF - Le 11 juillet 2007 - Ajout des fonctions GetRiskImpactFile et SetRiskImpactFile.
    virtual const CString GetRiskImpactFile() const;
    virtual void SetRiskImpactFile(CString value);

    // JMR-MODIF - Le 11 juillet 2007 - Ajout des fonctions GetRiskProbabilityFile et SetRiskProbabilityFile.
    virtual const CString GetRiskProbabilityFile() const;
    virtual void SetRiskProbabilityFile(CString value);

    // JMR-MODIF - Le 15 avril 2007 - Cette fonction permet de définir si le programme est utilisé pour la première fois.
    virtual inline BOOL GetFirstUse()
    {
        return m_FirstUse;
    }

    virtual const BOOL GetForceNetworkConnection() const;
    virtual void SetForceNetworkConnection(BOOL value);

    virtual const BOOL GetDontShowToolTip() const;
    virtual void SetDontShowToolTip(BOOL value);

    virtual const BOOL GetDontShowTaskList() const;
    virtual void SetDontShowTaskList(BOOL value);

    virtual inline CString GetRegisteredUserName() const
    {
        return m_RegisteredUserName;
    };

    virtual inline void SetRegisteredUserName(CString value)
    {
        m_RegisteredUserName = value;
    };

    virtual inline CString GetRegisteredCompanyName() const
    {
        return m_RegisteredCompanyName;
    };

    virtual inline void SetRegisteredCompanyName(CString value)
    {
        m_RegisteredCompanyName = value;
    };

    virtual inline CString GetRegisteredProductKey() const
    {
        return m_RegisteredProductKey;
    };

    virtual inline void SetRegisteredProductKey(CString value)
    {
        m_RegisteredProductKey = value;
    };

protected:
    ZUSystemOption m_SystemOption;
    CString        m_ExportFileName;
    CString        m_ExportSchemaName;
    CString        m_LastLoadedFile;
    CString        m_ServerIniFile;
    CString        m_RegisteredUserName;
    CString        m_RegisteredCompanyName;
    CString        m_RegisteredProductKey;
    CString        m_RiskTypeFile;
    CString        m_RiskImpactFile;
    CString        m_RiskProbabilityFile;
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

inline void ZAApplicationOption::SetIniFile( const CString& File )
{
    m_SystemOption.SetIniFile( File );
}

inline const BOOL ZAApplicationOption::GetbAnimationShow() const
{
    return m_bAnimationShow;
}

inline void ZAApplicationOption::SetbAnimationShow( BOOL value )
{
    m_bAnimationShow = value;
}

inline const BOOL ZAApplicationOption::GetbCreateOnStartup() const
{
    return m_bCreateOnStartup;
}

inline void ZAApplicationOption::SetbCreateOnStartup( BOOL value )
{
    m_bCreateOnStartup = value;
}

inline const BOOL ZAApplicationOption::GetbScreenPos() const
{
    return m_bScreenPos;
}

inline void ZAApplicationOption::SetbScreenPos( BOOL value )
{
    m_bScreenPos = value;
}

inline const BOOL ZAApplicationOption::GetbPrintLine() const
{
    return m_bPrintLine;
}

inline void ZAApplicationOption::SetbPrintLine( BOOL value )
{
    m_bPrintLine = value;
}

inline const BOOL ZAApplicationOption::GetbAutoCalculate() const
{
    return m_bAutoCalculate;
}

inline void ZAApplicationOption::SetbAutoCalculate( BOOL value )
{
    m_bAutoCalculate = value;
}

inline const BOOL ZAApplicationOption::GetbOpenLastLoadedFile() const
{
    return m_bOpenLastLoadedFile;
}

inline void ZAApplicationOption::SetbOpenLastLoadedFile( BOOL value )
{
    m_bOpenLastLoadedFile = value;
}

inline const BOOL ZAApplicationOption::GetbCalculateFieldShow() const
{
    return m_bCalculateFieldShow;
}

inline void ZAApplicationOption::SetbCalculateFieldShow( BOOL value )
{
    m_bCalculateFieldShow = value;
}

inline const BOOL ZAApplicationOption::GetbShowHiddenField() const
{
    return m_bShowHiddenField;
}

inline void ZAApplicationOption::SetbShowHiddenField( BOOL value )
{
    m_bShowHiddenField = value;
}

inline const BOOL ZAApplicationOption::GetbShowBoundsRect() const
{
    return m_bShowBoundsRect;
}

inline void ZAApplicationOption::SetbShowBoundsRect( BOOL value )
{
    m_bShowBoundsRect = value;
}

inline const BOOL ZAApplicationOption::GetGoNextEdit() const
{
    return m_GoNextEdit;
}

inline void ZAApplicationOption::SetGoNextEdit( BOOL value )
{
    m_GoNextEdit = value;
}

inline const CString ZAApplicationOption::GetExportFilename() const
{
    return m_ExportFilename;
}

inline void ZAApplicationOption::SetExportFilename( CString value )
{
    m_ExportFilename = value;
}

inline const CString ZAApplicationOption::GetExportSchemaName() const
{
    return m_ExportSchemaName;
}

inline void ZAApplicationOption::SetExportSchemaName( CString value )
{
    m_ExportSchemaName = value;
}

inline const int ZAApplicationOption::GetExportPropagationMode() const
{
    return m_ExportPropagationMode;
}

inline void ZAApplicationOption::SetExportPropagationMode( int value )
{
    m_ExportPropagationMode = value;
}

inline const BOOL ZAApplicationOption::GetEmptyWhenZero() const
{
    return m_EmptyWhenZero;
}

inline void ZAApplicationOption::SetEmptyWhenZero( BOOL value )
{
    m_EmptyWhenZero = value;
}

inline const BOOL ZAApplicationOption::GetAutomaticFieldNameCreation() const
{
    return m_AutomaticFieldNameCreation;
}

inline void ZAApplicationOption::SetAutomaticFieldNameCreation( BOOL value )
{
    m_AutomaticFieldNameCreation = value;
}

inline const BOOL ZAApplicationOption::GetMaximizeFormOnOpen() const
{
    return m_MaximizeFormOnOpen;
}

inline void ZAApplicationOption::SetMaximizeFormOnOpen( BOOL value )
{
    m_MaximizeFormOnOpen = value;
}

inline const BOOL ZAApplicationOption::GetShowWelcomeScreen() const
{
    return m_ShowWelcomeScreen;
}

inline void ZAApplicationOption::SetShowWelcomeScreen( BOOL value )
{
    m_ShowWelcomeScreen = value;
}

inline const CString ZAApplicationOption::GetsLastLoadedFile() const
{
    return m_sLastLoadedFile;
}

inline void ZAApplicationOption::SetsLastLoadedFile( CString value )
{
    m_sLastLoadedFile = value;
}

inline const CString ZAApplicationOption::GetServerIniFile() const
{
    return m_ServerIniFile;
}

inline void ZAApplicationOption::SetServerIniFile(const CString& value)
{
    m_ServerIniFile = value;
}

// JMR-MODIF - Le 8 juillet 2007 - Cette fonction permet d'obtenir le nom du fichier des types des risques.
inline const CString ZAApplicationOption::GetRiskTypeFile() const
{
    return m_RiskTypeFile;
}

// JMR-MODIF - Le 8 juillet 2007 - Cette fonction permet de définir le nom du fichier des types des risques.
inline void ZAApplicationOption::SetRiskTypeFile( CString value )
{
    m_RiskTypeFile = value;
}

// JMR-MODIF - Le 11 juillet 2007 - Cette fonction permet d'obtenir le nom du fichier des impacts des risques.
inline const CString ZAApplicationOption::GetRiskImpactFile() const
{
    return m_RiskImpactFile;
}

// JMR-MODIF - Le 11 juillet 2007 - Cette fonction permet de définir le nom du fichier des impacts des risques.
inline void ZAApplicationOption::SetRiskImpactFile( CString value )
{
    m_RiskImpactFile = value;
}

// JMR-MODIF - Le 11 juillet 2007 - Cette fonction permet d'obtenir le nom du fichier des probabilités des risques.
inline const CString ZAApplicationOption::GetRiskProbabilityFile() const
{
    return m_RiskProbabilityFile;
}

// JMR-MODIF - Le 11 juillet 2007 - Cette fonction permet de définir le nom du fichier des probabilités des risques.
inline void ZAApplicationOption::SetRiskProbabilityFile( CString value )
{
    m_RiskProbabilityFile = value;
}

inline const BOOL ZAApplicationOption::GetForceNetworkConnection() const
{
    return m_ForceNetworkConnection;
}

inline void ZAApplicationOption::SetForceNetworkConnection( BOOL value )
{
    m_ForceNetworkConnection = value;
}

inline const BOOL ZAApplicationOption::GetDontShowToolTip() const
{
    return m_DontShowToolTip;
}

inline void ZAApplicationOption::SetDontShowToolTip( BOOL value )
{
    m_DontShowToolTip = value;
}

inline const BOOL ZAApplicationOption::GetDontShowTaskList() const
{
    return m_DontShowTaskList;
}

inline void ZAApplicationOption::SetDontShowTaskList( BOOL value )
{
    m_DontShowTaskList = value;
}

#endif