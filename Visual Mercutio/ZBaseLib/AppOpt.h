/////////////////////////////////////////////////////////////////////////////
//@doc ZAApplicationOption
//@module AppOpt.h | Interface of the <c ZAApplicationOption> class.
//
// Advanced Dedicated Software Classes
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software,
// All rights reserved.
// Contact:
// mailto:dominique.aigroz@adsoft-form.com
// http://www.adsoft-form.com
//
// This source code is part of the zForms library.
// See these sources for detailed information regarding
// zForms libraries.
//
// Author:       Dom
// <nl>Created:         03/2000
// <nl>Description:  ZAApplicationOption basic application option management

#ifndef AppOpt_h
#define AppOpt_h 1

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// ZUSystemOption
#include "zBaseLib\ZUSystemOption.h"

#ifdef _ZBASELIBEXPORT
//Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 9 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZAApplicationOption : public CObject
{
public:

    ZAApplicationOption( CString IniFile = _T( "" ), CString AppDir = _T( "" ) );
    ~ZAApplicationOption();

    // Loads the options.
    BOOL LoadOption();

    // Saves the options.
    BOOL SaveOption( bool RegisteredInformation = false );
    BOOL SaveRegisteredInformation();

    BOOL Create( CString IniFile = _T( "" ), CString AppDir = _T( "" ) );

    // Sets the ini file.
    void SetIniFile( const CString& File );

    // Options accessors
    const BOOL GetbAnimationShow() const;
    void SetbAnimationShow( BOOL value );

    const BOOL GetbCreateOnStartup() const;
    void SetbCreateOnStartup( BOOL value );

    const BOOL GetbScreenPos() const;
    void SetbScreenPos( BOOL value );

    const BOOL GetbPrintLine() const;
    void SetbPrintLine( BOOL value );

    const BOOL GetbAutoCalculate() const;
    void SetbAutoCalculate( BOOL value );

    const BOOL GetbOpenLastLoadedFile() const;
    void SetbOpenLastLoadedFile( BOOL value );

    // Flag to show or not calculated fields
    const BOOL GetbCalculateFieldShow() const;
    void SetbCalculateFieldShow( BOOL value );

    // To specifiy if hidden fields must be shown.
    const BOOL GetbShowHiddenField() const;
    void SetbShowHiddenField( BOOL value );

    // Flag representing the option for showing the bound rect
    // of objects.
    const BOOL GetbShowBoundsRect() const;
    void SetbShowBoundsRect( BOOL value );

    // Defines if the application must go automatically on the
    // next edit after Enter.
    const BOOL GetGoNextEdit() const;
    void SetGoNextEdit( BOOL value );

    // Defines the export filename.
    const CString GetExportFilename() const;
    void SetExportFilename( CString value );

    // The schema name used during importation.
    const CString GetExportSchemaName() const;
    void SetExportSchemaName( CString value );

    // The propagation mode used during importation.
    const int GetExportPropagationMode() const;
    void SetExportPropagationMode( int value );

    // For the import, process empty when zero for numbers.
    const BOOL GetEmptyWhenZero() const;
    void SetEmptyWhenZero( BOOL value );

    // Defines if automatic field creation is required.
    const BOOL GetAutomaticFieldNameCreation() const;
    void SetAutomaticFieldNameCreation( BOOL value );

    const BOOL GetMaximizeFormOnOpen() const;
    void SetMaximizeFormOnOpen( BOOL value );

    const BOOL GetShowWelcomeScreen() const;
    void SetShowWelcomeScreen( BOOL value );

    // Keep a trace of the last load file.
    const CString GetsLastLoadedFile() const;
    void SetsLastLoadedFile( CString value );

    const CString GetServerIniFile() const;
    void SetServerIniFile( CString value );

    // JMR-MODIF - Le 8 juillet 2007 - Ajout des fonctions GetRiskTypeFile et SetRiskTypeFile.
    const CString GetRiskTypeFile() const;
    void SetRiskTypeFile( CString value );

    // JMR-MODIF - Le 11 juillet 2007 - Ajout des fonctions GetRiskImpactFile et SetRiskImpactFile.
    const CString GetRiskImpactFile() const;
    void SetRiskImpactFile( CString value );

    // JMR-MODIF - Le 11 juillet 2007 - Ajout des fonctions GetRiskProbabilityFile et SetRiskProbabilityFile.
    const CString GetRiskProbabilityFile() const;
    void SetRiskProbabilityFile( CString value );

    // JMR-MODIF - Le 15 avril 2007 - Cette fonction permet de définir si le programme est utilisé pour la première fois.
    BOOL GetFirstUse()
    {
        return m_bFirstUse;
    }

    const BOOL GetForceNetworkConnection() const;
    void SetForceNetworkConnection( BOOL value );

    const BOOL GetDontShowToolTip() const;
    void SetDontShowToolTip( BOOL value );

    const BOOL GetDontShowTaskList() const;
    void SetDontShowTaskList( BOOL value );

    CString GetRegisteredUserName() const
    {
        return m_RegisteredUserName;
    };

    void SetRegisteredUserName( CString value )
    {
        m_RegisteredUserName = value;
    };

    CString GetRegisteredCompanyName() const
    {
        return m_RegisteredCompanyName;
    };

    void SetRegisteredCompanyName( CString value )
    {
        m_RegisteredCompanyName = value;
    };

    CString GetRegisteredProductKey() const
    {
        return m_RegisteredProductKey;
    };

    void SetRegisteredProductKey( CString value )
    {
        m_RegisteredProductKey = value;
    };

private:

    ZAApplicationOption( const ZAApplicationOption &right );
    const ZAApplicationOption & operator=( const ZAApplicationOption &right );

protected:

    // Data Members for Class Attributes
    BOOL            m_bOpenLastLoadedFile;
    BOOL            m_GoNextEdit;
    BOOL            m_EmptyWhenZero;
    BOOL            m_AutomaticFieldNameCreation;
    BOOL            m_MaximizeFormOnOpen;
    BOOL            m_ShowWelcomeScreen;
    BOOL            m_ForceNetworkConnection;
    BOOL            m_DontShowToolTip;
    BOOL            m_DontShowTaskList;
    BOOL            m_bAnimationShow;
    BOOL            m_bCreateOnStartup;
    BOOL            m_bScreenPos;
    BOOL            m_bPrintLine;
    BOOL            m_bAutoCalculate;
    BOOL            m_bCalculateFieldShow;
    BOOL            m_bShowHiddenField;
    BOOL            m_bShowBoundsRect;
    // JMR-MODIF - Le 15 avril 2007 - Ajout de la variable m_bFirstUse
    BOOL            m_bFirstUse;

    CString            m_ExportFilename;
    CString            m_ExportSchemaName;
    CString            m_sLastLoadedFile;
    CString            m_ServerIniFile;
    CString            m_RegisteredUserName;
    CString            m_RegisteredCompanyName;
    CString            m_RegisteredProductKey;
    // JMR-MODIF - Le 8 juillet 2007 - Ajouté la variable m_RiskTypeFile.
    CString            m_RiskTypeFile;
    // JMR-MODIF - Le 11 juillet 2007 - Ajouté la variable m_RiskImpactFile.
    CString            m_RiskImpactFile;
    // JMR-MODIF - Le 11 juillet 2007 - Ajouté la variable m_RiskProbabilityFile.
    CString            m_RiskProbabilityFile;
    // JMR-MODIF - Le 15 avril 2007 - Ajouté la variable m_AppDir;
    CString            m_AppDir;

    int                m_ExportPropagationMode;

    // Object who take care of reading and saving options
    ZUSystemOption    m_SystemOption;
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

inline void ZAApplicationOption::SetServerIniFile( CString value )
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