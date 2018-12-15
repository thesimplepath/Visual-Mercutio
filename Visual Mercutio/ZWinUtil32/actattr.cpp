// actattr.cpp : implementation file
//

#include "stdafx.h"
#include "ActAttr.h"
#include "LstUser.h"
#include "ActIAttr.h"
#include "ActBAttr.h"

#include "zBaseLib\MsgBox.h"
#include "zBaseLib\InpVal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIActivityAttributionInput


ZIActivityAttributionInput::ZIActivityAttributionInput(ZUUserManager& UserManager, ZUMail& Mail, ZActivity* pActivity, BOOL LastActivity, BOOL UserAttribution, BOOL BackupUserAttribution, BOOL TimeAttribution, BOOL VisibilityAttribution, CWnd* pParent)
    :     m_UserManager(UserManager), m_Mail(Mail), m_pActivity(pActivity),
        m_LastActivity(LastActivity),
        m_UserAttribution(UserAttribution),
        m_BackupUserAttribution(BackupUserAttribution),
        m_TimeAttribution(TimeAttribution),
        m_VisibilityAttribution(VisibilityAttribution)
        
{
    ASSERT( m_pActivity );
}



BOOL ZIActivityAttributionInput::ProcessBaseValue()
{
    ZIActivityAttributionValueInput    ActivityAttributionInput( m_UserManager, 
                                                                m_Mail, 
                                                                m_pActivity,
                                                                m_LastActivity && !m_BackupUserAttribution,
                                                                m_UserAttribution,
                                                                m_TimeAttribution,
                                                                m_VisibilityAttribution );
    if (ActivityAttributionInput.DoModal() == IDCANCEL)
        return FALSE;
    return TRUE;
}

BOOL ZIActivityAttributionInput::ProcessBackupUser()
{
    ZIActivityAttributionBackupInput    ActivityAttributionBackupInput(    m_UserManager, 
                                                                        m_Mail, 
                                                                        m_pActivity, 
                                                                        m_LastActivity);
    if (ActivityAttributionBackupInput.DoModal() == IDCANCEL)
        return FALSE;
    return TRUE;
}


int ZIActivityAttributionInput::DoModal()
{
    if (m_UserAttribution || m_TimeAttribution || m_VisibilityAttribution)
    {
        if (!ProcessBaseValue())
            return IDCANCEL;
    }
    // If backup attribution and activity stills visible or undefined
    if (m_BackupUserAttribution && m_pActivity->GetIsVisible() != FalseState)
    {
        if (!ProcessBackupUser())
            return IDCANCEL;
    }
    return IDOK;
}



