/****************************************************************************
 * ==> PSS_ApplicationOption -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic application option management system      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ApplicationOption.h"

 //---------------------------------------------------------------------------
 // PSS_ApplicationOption
 //---------------------------------------------------------------------------
PSS_ApplicationOption::PSS_ApplicationOption(const CString& iniFile, const CString& appDir) :
    CObject(),
    m_ExportSchemaName(g_OriginalSchema),
    m_ExportPropagationMode(g_LocatePageOnly),
    m_OpenLastLoadedFile(FALSE),
    m_GoNextEdit(FALSE),
    m_EmptyWhenZero(FALSE),
    m_AutomaticFieldNameCreation(FALSE),
    m_MaximizeFormOnOpen(FALSE),
    m_ShowWelcomeScreen(FALSE),
    m_ForceNetworkConnection(FALSE),
    m_DontShowToolTip(FALSE),
    m_DontShowTaskList(FALSE),
    m_AnimationShow(FALSE),
    m_CreateOnStartup(FALSE),
    m_ScreenPos(FALSE),
    m_PrintLine(FALSE),
    m_AutoCalculate(FALSE),
    m_CalculateFieldShow(FALSE),
    m_ShowHiddenField(FALSE),
    m_ShowBoundsRect(FALSE),
    m_FirstUse(FALSE)
{
    Create(iniFile, appDir);
}
//---------------------------------------------------------------------------
PSS_ApplicationOption::PSS_ApplicationOption(const PSS_ApplicationOption& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ApplicationOption::~PSS_ApplicationOption()
{}
//---------------------------------------------------------------------------
const PSS_ApplicationOption& PSS_ApplicationOption::operator = (const PSS_ApplicationOption& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_ApplicationOption::Create(const CString& iniFile, const CString& appDir)
{
    m_AppDir = appDir;

    m_SystemOption.Create(iniFile, ApplicationConfigSectionName);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ApplicationOption::LoadOption()
{
    // read options
    m_FirstUse                   = m_SystemOption.ReadOption(szIniFirstUse,                   1);
    m_MaximizeFormOnOpen         = m_SystemOption.ReadOption(szIniMaximizeFormOnOpenEntry,    0);
    m_ShowWelcomeScreen          = m_SystemOption.ReadOption(szIniShowWelcomeScreenEntry,     1);
    m_OpenLastLoadedFile         = m_SystemOption.ReadOption(szIniOpenLastLoadedFile,         0);
    m_LastLoadedFileName         = m_SystemOption.ReadOption(szIniLastLoadedFile,             _T(""));
    m_GoNextEdit                 = m_SystemOption.ReadOption(szIniGoNext,                     1);
    m_ExportFileName             = m_SystemOption.ReadOption(szIniExportFile,                 _T("Export.txt"));
    m_ExportSchemaName           = m_SystemOption.ReadOption(szIniExportSchema,               g_OriginalSchema);
    m_ExportPropagationMode      = m_SystemOption.ReadOption(szIniExportPropagationMode,      g_LocateForwardPage);
    m_EmptyWhenZero              = m_SystemOption.ReadOption(szIniExportEmptyWhenZero,        1);
    m_AutomaticFieldNameCreation = m_SystemOption.ReadOption(szIniAutomaticFieldNameCreation, 0);
    m_AnimationShow              = m_SystemOption.ReadOption(szIniAnimationShow,              1);
    m_CreateOnStartup            = m_SystemOption.ReadOption(szIniCreateOnStartupEntry,       1);
    m_ScreenPos                  = m_SystemOption.ReadOption(szIniSaveScreenPosEntry,         1);
    m_PrintLine                  = m_SystemOption.ReadOption(szIniPrintLineEntry,             1);
    m_AutoCalculate              = m_SystemOption.ReadOption(szIniAutoCalculate,              1);
    m_CalculateFieldShow         = m_SystemOption.ReadOption(szIniShowCalculatedField,        1);
    m_ShowHiddenField            = m_SystemOption.ReadOption(szIniShowHiddenField,            0);
    m_ShowBoundsRect             = m_SystemOption.ReadOption(szIniShowBoundsRect,             0);
    m_ServerIniFileName          = m_SystemOption.ReadOption(szGlobalIniFileEntry,            m_AppDir + g_LocalRefDirectory + g_LocalIniFileName);
    m_RiskTypeFileName           = m_SystemOption.ReadOption(szRiskTypeFileEntry,             m_AppDir + g_RiskDirectory + g_RiskTypeFileName);
    m_RiskImpactFileName         = m_SystemOption.ReadOption(szRiskImpactFileEntry,           m_AppDir + g_RiskDirectory + g_RiskImpactFileName);
    m_RiskProbabilityFileName    = m_SystemOption.ReadOption(szRiskProbabilityFileEntry,      m_AppDir + g_RiskDirectory + g_RiskProbabilityFileName);
    m_ForceNetworkConnection     = m_SystemOption.ReadOption(szIniForceNetworkConnection,     1);
    m_DontShowToolTip            = m_SystemOption.ReadOption(szIniDontShowToolTip,            1);
    m_DontShowTaskList           = m_SystemOption.ReadOption(szIniDontShowTaskList,           0);
    m_RegisteredUserName         = m_SystemOption.ReadOption(szIniUserNameEntry,              _T(""));
    m_RegisteredCompanyName      = m_SystemOption.ReadOption(szIniSocietyNameEntry,           _T(""));
    m_RegisteredProductKey       = m_SystemOption.ReadOption(szIniKeyProductEntry,            _T(""));

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ApplicationOption::SaveOption(bool registeredInfo)
{
    // remove the first use flag
    m_FirstUse = FALSE;

    m_SystemOption.WriteOption(szIniFirstUse,                   m_FirstUse);
    m_SystemOption.WriteOption(szIniMaximizeFormOnOpenEntry,    m_MaximizeFormOnOpen);
    m_SystemOption.WriteOption(szIniShowWelcomeScreenEntry,     m_ShowWelcomeScreen);
    m_SystemOption.WriteOption(szIniOpenLastLoadedFile,         m_OpenLastLoadedFile);
    m_SystemOption.WriteOption(szIniLastLoadedFile,             m_LastLoadedFileName);
    m_SystemOption.WriteOption(szIniGoNext,                     m_GoNextEdit);
    m_SystemOption.WriteOption(szIniExportFile,                 m_ExportFileName);
    m_SystemOption.WriteOption(szIniExportSchema,               m_ExportSchemaName);
    m_SystemOption.WriteOption(szIniExportPropagationMode,      m_ExportPropagationMode);
    m_SystemOption.WriteOption(szIniExportEmptyWhenZero,        m_EmptyWhenZero);
    m_SystemOption.WriteOption(szIniAutomaticFieldNameCreation, m_AutomaticFieldNameCreation);
    m_SystemOption.WriteOption(szIniAnimationShow,              m_AnimationShow);
    m_SystemOption.WriteOption(szIniCreateOnStartupEntry,       m_CreateOnStartup);
    m_SystemOption.WriteOption(szIniSaveScreenPosEntry,         m_ScreenPos);
    m_SystemOption.WriteOption(szIniPrintLineEntry,             m_PrintLine);
    m_SystemOption.WriteOption(szIniAutoCalculate,              m_AutoCalculate);
    m_SystemOption.WriteOption(szIniShowCalculatedField,        m_CalculateFieldShow);
    m_SystemOption.WriteOption(szIniShowHiddenField,            m_ShowHiddenField);
    m_SystemOption.WriteOption(szIniShowBoundsRect,             m_ShowBoundsRect);
    m_SystemOption.WriteOption(szGlobalIniFileEntry,            m_ServerIniFileName);
    m_SystemOption.WriteOption(szRiskTypeFileEntry,             m_RiskTypeFileName);
    m_SystemOption.WriteOption(szRiskImpactFileEntry,           m_RiskImpactFileName);
    m_SystemOption.WriteOption(szRiskProbabilityFileEntry,      m_RiskProbabilityFileName);
    m_SystemOption.WriteOption(szIniForceNetworkConnection,     m_ForceNetworkConnection);
    m_SystemOption.WriteOption(szIniDontShowToolTip,            m_DontShowToolTip);
    m_SystemOption.WriteOption(szIniDontShowTaskList,           m_DontShowTaskList);

    if (registeredInfo)
        SaveRegisteredInfo();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ApplicationOption::SaveRegisteredInfo()
{
    m_SystemOption.ReadOption(szIniUserNameEntry,    m_RegisteredUserName);
    m_SystemOption.ReadOption(szIniSocietyNameEntry, m_RegisteredCompanyName);
    m_SystemOption.ReadOption(szIniKeyProductEntry,  m_RegisteredProductKey);

    return TRUE;
}
//---------------------------------------------------------------------------
