/****************************************************************************
 * ==> PSS_SoapPublishUserGroup --------------------------------------------*
 ****************************************************************************
 * Description : Publish the user groups to Messenger through a SOAP        *
 *               protocol, and check the publication validity               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SoapPublishUserGroup.h"

// processsoft
#include "zBaseLib\ZILog.h"
#include "zModel\ProcGraphModelDoc.h"
#include "zModel\ZBUserGroupEntity.h"
#include "zModel\ZBUserRoleEntity.h"
#include "zModel\ZBGenericSymbolErrorLine.h"
#include "zSOAP\PSS_SoapData_Settings.h"
#include "ZBPublishMessengerModelInformation.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_SoapPublishUserGroup
//---------------------------------------------------------------------------
PSS_SoapPublishUserGroup::PSS_SoapPublishUserGroup(ZBPublishMessengerModelInformation* pInfo, ZILog* pLog) :
    m_pInfo(pInfo),
    m_pLog(pLog)
{}
//---------------------------------------------------------------------------
PSS_SoapPublishUserGroup::~PSS_SoapPublishUserGroup()
{}
//---------------------------------------------------------------------------
bool PSS_SoapPublishUserGroup::Publish()
{
    if (!m_pInfo || !m_pInfo->m_pDoc || !m_pInfo->m_pDoc->GetMainUserGroup())
        return false;

    // copy the publication address from source info
    PSS_SoapData_Settings::m_Url = (const char*)m_pInfo->m_MessengerAddress;

    // publish all user groups
    PublishUserGroup(m_pInfo->m_pDoc->GetMainUserGroup());

    return m_PubWorkgroup.Send();
}
//---------------------------------------------------------------------------
void PSS_SoapPublishUserGroup::PublishUserGroup(ZBUserGroupEntity* pGroup)
{
    if (!pGroup)
        return;

    if (m_pLog && m_pLog->IsInDebugMode())
    {
        CString message;
        message.Format(IDS_AL_PUBLISHUSERGROUP, (const char*)pGroup->GetEntityName());
        ZBGenericSymbolErrorLine e(message);
        m_pLog->AddLine(e);
    }

    CString dayCost;
    dayCost.Format(_T("%.2f"), pGroup->GetEntityCost());

    // publish the user groups and their alias
    m_PubWorkgroup.Add(PSS_SoapData_Workgroup(PSS_String16(pGroup->GetGUID()),                                             // workgroup GUID
                                              PSS_String16(pGroup->GetParent() ? pGroup->GetParent()->GetGUID() : _T("")), // parent GUID
                                              PSS_String16(pGroup->GetEntityName()),                                       // workgroup name
                                              PSS_String16(pGroup->GetEntityDescription()),                                // mission
                                              PSS_String16(dayCost)));                                                     // day cost
    m_PubWorkgroup.AddAlias(m_pInfo->m_MessengerAlias);

    #ifdef _DEBUG
        CString s;
        s.Format(_T(" Group = %s\n"), (const char*)pGroup->GetEntityName());
        TRACE(s);
    #endif

    if (pGroup->ContainEntity())
    {
        const int count = pGroup->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            ZBUserEntity* pEntity = pGroup->GetEntityAt(i);

            if (!pEntity)
                continue;

            PublishUserGroup(dynamic_cast<ZBUserGroupEntity*>(pEntity));
        }
    }
}
//---------------------------------------------------------------------------
