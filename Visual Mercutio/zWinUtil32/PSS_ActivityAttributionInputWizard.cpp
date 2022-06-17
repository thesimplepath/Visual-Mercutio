/****************************************************************************
 * ==> PSS_ActivityAttributionInputWizard ----------------------------------*
 ****************************************************************************
 * Description : Provides an activity attribution input wizard              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_ActivityAttributionInputWizard.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_InputValue.h"
#include "PSS_ActivityAttributionInputBackupDialog.h"
#include "PSS_ActivityAttributionInputValueDialog.h"
#include "PSS_UserListDialog.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ActivityAttributionInputWizard
//---------------------------------------------------------------------------
PSS_ActivityAttributionInputWizard::PSS_ActivityAttributionInputWizard(PSS_UserManager& userManager,
                                                                       PSS_Mail&        mail,
                                                                       PSS_Activity*    pActivity,
                                                                       BOOL             lastActivity,
                                                                       BOOL             userAttribution,
                                                                       BOOL             backupUserAttribution,
                                                                       BOOL             timeAttribution,
                                                                       BOOL             visibilityAttribution,
                                                                       CWnd*            pParent) :
    m_UserManager(userManager),
    m_Mail(mail),
    m_pActivity(pActivity),
    m_LastActivity(lastActivity),
    m_UserAttribution(userAttribution),
    m_BackupUserAttribution(backupUserAttribution),
    m_TimeAttribution(timeAttribution),
    m_VisibilityAttribution(visibilityAttribution)
{
    PSS_Assert(m_pActivity);
}
//---------------------------------------------------------------------------
int PSS_ActivityAttributionInputWizard::Execute()
{
    if (m_UserAttribution || m_TimeAttribution || m_VisibilityAttribution)
        if (!ProcessBaseValue())
            return IDCANCEL;

    // if backup attribution and activity stills visible or undefined
    if (m_BackupUserAttribution && m_pActivity->GetIsVisible() != EThreeState::E_TS_False)
        if (!ProcessBackupUser())
            return IDCANCEL;

    return IDOK;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityAttributionInputWizard::ProcessBackupUser()
{
    PSS_ActivityAttributionInputBackupDialog activityAttributionBackupInput(m_UserManager,
                                                                            m_Mail,
                                                                            m_pActivity,
                                                                            m_LastActivity);

    return (activityAttributionBackupInput.DoModal() != IDCANCEL);
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityAttributionInputWizard::ProcessBaseValue()
{
    PSS_ActivityAttributionInputValueDialog ActivityAttributionInput(m_UserManager,
                                                                     m_Mail,
                                                                     m_pActivity,
                                                                     m_LastActivity && !m_BackupUserAttribution,
                                                                     m_UserAttribution,
                                                                     m_TimeAttribution,
                                                                     m_VisibilityAttribution);

    return (ActivityAttributionInput.DoModal() != IDCANCEL);
}
//---------------------------------------------------------------------------
