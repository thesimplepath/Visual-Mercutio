/****************************************************************************
 * ==> PSS_ActivityAttributionInputDialog ----------------------------------*
 ****************************************************************************
 * Description : Provides an activity attribution input dialog box          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_ActivityAttributionInputDialog.h"

// processsoft
#include "zBaseLib\MsgBox.h"
#include "zBaseLib\InpVal.h"
#include "LstUser.h"
#include "ActIAttr.h"
#include "ActBAttr.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ActivityAttributionInputDialog
//---------------------------------------------------------------------------
PSS_ActivityAttributionInputDialog::PSS_ActivityAttributionInputDialog(ZUUserManager& userManager,
                                                                       ZUMail&        mail,
                                                                       ZActivity*     pActivity,
                                                                       BOOL           lastActivity,
                                                                       BOOL           userAttribution,
                                                                       BOOL           backupUserAttribution,
                                                                       BOOL           timeAttribution,
                                                                       BOOL           visibilityAttribution,
                                                                       CWnd*          pParent) :
    m_UserManager(userManager),
    m_Mail(mail),
    m_pActivity(pActivity),
    m_LastActivity(lastActivity),
    m_UserAttribution(userAttribution),
    m_BackupUserAttribution(backupUserAttribution),
    m_TimeAttribution(timeAttribution),
    m_VisibilityAttribution(visibilityAttribution)
{
    ASSERT(m_pActivity);
}
//---------------------------------------------------------------------------
int PSS_ActivityAttributionInputDialog::DoModal()
{
    if (m_UserAttribution || m_TimeAttribution || m_VisibilityAttribution)
        if (!ProcessBaseValue())
            return IDCANCEL;

    // if backup attribution and activity stills visible or undefined
    if (m_BackupUserAttribution && m_pActivity->GetIsVisible() != E_TS_False)
        if (!ProcessBackupUser())
            return IDCANCEL;

    return IDOK;
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityAttributionInputDialog::ProcessBackupUser()
{
    ZIActivityAttributionBackupInput activityAttributionBackupInput(m_UserManager,
                                                                    m_Mail,
                                                                    m_pActivity,
                                                                    m_LastActivity);

    return (activityAttributionBackupInput.DoModal() != IDCANCEL);
}
//---------------------------------------------------------------------------
BOOL PSS_ActivityAttributionInputDialog::ProcessBaseValue()
{
    ZIActivityAttributionValueInput ActivityAttributionInput(m_UserManager,
                                                             m_Mail,
                                                             m_pActivity,
                                                             m_LastActivity && !m_BackupUserAttribution,
                                                             m_UserAttribution,
                                                             m_TimeAttribution,
                                                             m_VisibilityAttribution);

    return (ActivityAttributionInput.DoModal() != IDCANCEL);
}
//---------------------------------------------------------------------------
