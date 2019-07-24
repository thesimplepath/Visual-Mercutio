/////////////////////////////////////////////////////////////////////////////
//@doc ZAApplicationOption
//@module AppOpt.cpp | Implementation of the <c ZAApplicationOption> class.
// 
// zForms<tm>
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software, Inc. 
// All rights reserved.
// Contact:
// mailto:dominique.aigroz@adsoft-form.com
// http://www.adsoft-form.com

#include <StdAfx.h>

// AppOpt
#include "AppOpt.h"

// JMR-MODIF - Le 21 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Class ZAApplicationOption

// JMR-MODIF - Le 15 avril 2007 - Ajouté la variable AppDir, qui représente le répertoire d'installation du programme.
ZAApplicationOption::ZAApplicationOption( CString IniFile, CString AppDir )
    : m_ExportSchemaName(g_OriginalSchema),
      m_ExportPropagationMode(g_LocatePageOnly)
{
    // JMR-MODIF - Le 15 avril 2007 - Ajouté l'initialisation de la variable m_AppDir.
    m_AppDir = AppDir;

    Create( IniFile );
}

ZAApplicationOption::~ZAApplicationOption()
{
}

// JMR-MODIF - Le 15 avril 2007 - Ajouté la variable AppDir, qui représente le répertoire d'installation du programme.
BOOL ZAApplicationOption::Create( CString IniFile, CString AppDir )
{
    // JMR-MODIF - Le 15 avril 2007 - Ajouté l'initialisation de la variable m_AppDir.
    m_AppDir = AppDir;

    m_SystemOption.Create( IniFile, ApplicationConfigSectionName );

    return TRUE;
}

BOOL ZAApplicationOption::LoadOption()
{
    // JMR-MODIF - Le 15 avril 2007 - Lecture du paramètre désignant si le programme est utilisé pour la première fois.
    m_bFirstUse = m_SystemOption.ReadOption( szIniFirstUse, 1 );

    // Retreive the maximize form on open flag
    m_MaximizeFormOnOpen = m_SystemOption.ReadOption( szIniMaximizeFormOnOpenEntry, 0 );

    // Retreive the show welcome screen flag
    m_ShowWelcomeScreen = m_SystemOption.ReadOption( szIniShowWelcomeScreenEntry, 1 );

    // Retreive the flag for open the last load file
    m_bOpenLastLoadedFile = m_SystemOption.ReadOption( szIniOpenLastLoadedFile, 0 );

    // Retreive the filename of the last loaded file
    m_sLastLoadedFile = m_SystemOption.ReadOption( szIniLastLoadedFile, _T( "" ) );

    // Retreive the Go Next flag 
    m_GoNextEdit = m_SystemOption.ReadOption( szIniGoNext, 1 );

    // Retreive the export filename
    m_ExportFilename = m_SystemOption.ReadOption( szIniExportFile, _T( "Export.txt" ) );

    // Retreive the export schema name
    m_ExportSchemaName = m_SystemOption.ReadOption( szIniExportSchema, g_OriginalSchema );

    // Retreive the propagation mode
    m_ExportPropagationMode = m_SystemOption.ReadOption(szIniExportPropagationMode, g_LocateForwardPage);

    // Retreive the empty when zero for numbers
    m_EmptyWhenZero = m_SystemOption.ReadOption( szIniExportEmptyWhenZero, 1 );

    // Retreive the automatic field creation
    m_AutomaticFieldNameCreation = m_SystemOption.ReadOption( szIniAutomaticFieldNameCreation, 0 );

    // Retreive the animation flag
    m_bAnimationShow = m_SystemOption.ReadOption( szIniAnimationShow, 1 );

    // Retreive the flag for creation of a new planfin on startup
    m_bCreateOnStartup = m_SystemOption.ReadOption( szIniCreateOnStartupEntry, 1 );

    // Retreive the screen position flag
    m_bScreenPos = m_SystemOption.ReadOption( szIniSaveScreenPosEntry, 1 );

    // Retreive the print line flag
    m_bPrintLine = m_SystemOption.ReadOption( szIniPrintLineEntry, 1 );

    // Retreive the auto calculate flag
    m_bAutoCalculate = m_SystemOption.ReadOption( szIniAutoCalculate, 1 );

    // Retreive the calculated field show flag
    m_bCalculateFieldShow = m_SystemOption.ReadOption( szIniShowCalculatedField, 1 );

    // Retreive the Hidden field show flag
    m_bShowHiddenField = m_SystemOption.ReadOption( szIniShowHiddenField, 0 );

    // Retreive the Show Bounds Rect flag
    m_bShowBoundsRect = m_SystemOption.ReadOption( szIniShowBoundsRect, 0 );

    // Retreive the server ini filename
    // JMR-MODIF - Le 15 avril 2007 - Par défaut, fait pointer le serveur sur le référenciel fourni lors de l'installation.
//    m_ServerIniFile = m_SystemOption.ReadOption( szGlobalIniFileEntry, _T( "" ) );
    m_ServerIniFile = m_SystemOption.ReadOption( szGlobalIniFileEntry,
                                                 m_AppDir + g_LocalRefDirectory + g_LocalIniFileName );

    // JMR-MODIF - Le 8 juillet 2007 - Ajout de l'initialisation de la variable m_RiskTypeFile.
    m_RiskTypeFile = m_SystemOption.ReadOption( szRiskTypeFileEntry,
                                                m_AppDir + g_RiskDirectory + g_RiskTypeFileName );

    // JMR-MODIF - Le 11 juillet 2007 - Ajout de l'initialisation de la variable m_RiskImpactFile.
    m_RiskImpactFile = m_SystemOption.ReadOption( szRiskImpactFileEntry,
                                                  m_AppDir + g_RiskDirectory + g_RiskImpactFileName );

    // JMR-MODIF - Le 11 juillet 2007 - Ajout de l'initialisation de la variable m_RiskProbabilityFile.
    m_RiskProbabilityFile = m_SystemOption.ReadOption( szRiskProbabilityFileEntry,
                                                       m_AppDir + g_RiskDirectory + g_RiskProbabilityFileName );

    // Retreive the force network connection flag
    m_ForceNetworkConnection = m_SystemOption.ReadOption( szIniForceNetworkConnection, 1 );

    // Retreive the don't show tooltip on startup
    m_DontShowToolTip = m_SystemOption.ReadOption( szIniDontShowToolTip, 1 );

    // Retreive the don't show task list on when a file is open
    m_DontShowTaskList = m_SystemOption.ReadOption( szIniDontShowTaskList, 0 );

    // Retreive registered information
    m_RegisteredUserName    = m_SystemOption.ReadOption( szIniUserNameEntry,    _T( "" ) );
    m_RegisteredCompanyName = m_SystemOption.ReadOption( szIniSocietyNameEntry, _T( "" ) );
    m_RegisteredProductKey    = m_SystemOption.ReadOption( szIniKeyProductEntry,    _T( "" ) );

    return TRUE;
}

BOOL ZAApplicationOption::SaveOption( bool RegisteredInformation /*= false*/ )
{
    // JMR-MODIF - Le 15 avril 2007 - Inscrit la première instance du programme dans le fichier d'initialisation.
    m_bFirstUse = FALSE;
    m_SystemOption.WriteOption( szIniFirstUse, m_bFirstUse );

    // Save the maximize form on open flag
    m_SystemOption.WriteOption( szIniMaximizeFormOnOpenEntry, m_MaximizeFormOnOpen );

    // Save the show welcome screen flag
    m_SystemOption.WriteOption( szIniShowWelcomeScreenEntry, m_ShowWelcomeScreen );

    // Save the flag for open the last load file
    m_SystemOption.WriteOption( szIniOpenLastLoadedFile, m_bOpenLastLoadedFile );

    // Save the filename of the last loaded file
    m_SystemOption.WriteOption( szIniLastLoadedFile, m_sLastLoadedFile );

    // Save the Go Next flag 
    m_SystemOption.WriteOption( szIniGoNext, m_GoNextEdit );

    // Save the export filename
    m_SystemOption.WriteOption( szIniExportFile, m_ExportFilename );

    // Save the export schema name
    m_SystemOption.WriteOption( szIniExportSchema, m_ExportSchemaName );

    // Save the propagation mode
    m_SystemOption.WriteOption( szIniExportPropagationMode, m_ExportPropagationMode );

    // Save the empty when zero for numbers
    m_SystemOption.WriteOption( szIniExportEmptyWhenZero, m_EmptyWhenZero );

    // Save the automatic field creation
    m_SystemOption.WriteOption( szIniAutomaticFieldNameCreation, m_AutomaticFieldNameCreation );

    // Save the animation flag
    m_SystemOption.WriteOption( szIniAnimationShow, m_bAnimationShow );

    // Save the flag for creation of a new planfin on startup
    m_SystemOption.WriteOption( szIniCreateOnStartupEntry, m_bCreateOnStartup );

    // Save the screen position flag
    m_SystemOption.WriteOption( szIniSaveScreenPosEntry, m_bScreenPos );

    // Save the print line flag
    m_SystemOption.WriteOption( szIniPrintLineEntry, m_bPrintLine );

    // Save the auto calculate flag
    m_SystemOption.WriteOption( szIniAutoCalculate, m_bAutoCalculate );

    // Save the calculated field show flag
    m_SystemOption.WriteOption( szIniShowCalculatedField, m_bCalculateFieldShow );

    // Save the Hidden field show flag
    m_SystemOption.WriteOption( szIniShowHiddenField, m_bShowHiddenField );

    // Save the Show Bounds Rect flag
    m_SystemOption.WriteOption( szIniShowBoundsRect, m_bShowBoundsRect );

    // Save the server ini filename
    m_SystemOption.WriteOption( szGlobalIniFileEntry, m_ServerIniFile );

    // JMR-MODIF - Le 8 juillet 2007 - Ajout de la sauvegarde de la variable m_RiskTypeFile.
    m_SystemOption.WriteOption( szRiskTypeFileEntry, m_RiskTypeFile );

    // JMR-MODIF - Le 11 juillet 2007 - Ajout de la sauvegarde de la variable m_RiskImpactFile.
    m_SystemOption.WriteOption( szRiskImpactFileEntry, m_RiskImpactFile );

    // JMR-MODIF - Le 11 juillet 2007 - Ajout de la sauvegarde de la variable m_RiskProbabilityFile.
    m_SystemOption.WriteOption( szRiskProbabilityFileEntry, m_RiskProbabilityFile );

    // Save the force network connection flag
    m_SystemOption.WriteOption( szIniForceNetworkConnection, m_ForceNetworkConnection );

    // Save the don't show tooltip on startup
    m_SystemOption.WriteOption( szIniDontShowToolTip, m_DontShowToolTip );

    // Save the don't show task list on when a file is open
    m_SystemOption.WriteOption( szIniDontShowTaskList, m_DontShowTaskList );

    if ( RegisteredInformation )
    {
        SaveRegisteredInformation();
    }

    return TRUE;
}

BOOL ZAApplicationOption::SaveRegisteredInformation()
{
    // Save registered information
    m_SystemOption.ReadOption( szIniUserNameEntry,        m_RegisteredUserName );
    m_SystemOption.ReadOption( szIniSocietyNameEntry,    m_RegisteredCompanyName );
    m_SystemOption.ReadOption( szIniKeyProductEntry,    m_RegisteredProductKey );

    return TRUE;
}
