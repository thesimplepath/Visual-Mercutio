/****************************************************************************
 * ==> PSS_SoapPublishLogicalSystem ----------------------------------------*
 ****************************************************************************
 * Description : Publish the logical system to Messenger through a SOAP     *
 *               protocol, and check the publication validity               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SoapPublishLogicalSystem.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zModel\ZBLogicalSystemEntity.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
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
// PSS_SoapPublishLogicalSystem
//---------------------------------------------------------------------------
PSS_SoapPublishLogicalSystem::PSS_SoapPublishLogicalSystem(ZBPublishMessengerModelInformation* pInfo, PSS_Log* pLog) :
    m_pInfo(pInfo),
    m_pLog(pLog)
{}
//---------------------------------------------------------------------------
PSS_SoapPublishLogicalSystem::~PSS_SoapPublishLogicalSystem()
{}
//---------------------------------------------------------------------------
bool PSS_SoapPublishLogicalSystem::Publish()
{
    if (m_pInfo && m_pInfo->m_pDoc && m_pInfo->m_pDoc->GetMainLogicalSystem())
    {
        // copy the publication address from source info
        PSS_SoapData_Settings::m_Url = (const char*)m_pInfo->m_MessengerAddress;

        // publish the logical system
        PublishLogicalSystem(m_pInfo->m_pDoc->GetMainLogicalSystem());

        // send the data to Messenger
        return m_PubSys.Send();
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_SoapPublishLogicalSystem::PublishLogicalSystem(ZBLogicalSystemEntity* pSystem)
{
    if (!pSystem)
        return;

    // log the debug info
    if (m_pLog && m_pLog->IsInDebugMode())
    {
        CString message;
        message.Format(IDS_AL_PUBLISHLOGICALSYSTEM, (const char*)pSystem->GetEntityName());
        ZBGenericSymbolErrorLine e(message);
        m_pLog->AddLine(e);
    }

    // publish the logical system and its alias
    m_PubSys.Add(PSS_SoapData_System(PSS_String16(pSystem->GetGUID()),
                                     PSS_String16(pSystem->GetParent() ? pSystem->GetParent()->GetGUID() : _T("")),
                                     PSS_String16(pSystem->GetEntityName()),
                                     PSS_String16(_T("")), // command in fact does not exist yet
                                     PSS_String16(_T("")), // parameters in fact does not exist yet
                                     PSS_String16(_T("")), // directory in fact does not exist yet
                                     0,                    // priority doesn't exist yet
                                     0));                  // Windows mode doesn't exist yet
    m_PubSys.AddAlias(m_pInfo->m_MessengerAlias);

    // log the debug info
    #ifdef _DEBUG
        CString s;
        s.Format(_T(" System = %s\n"), (const char*)pSystem->GetEntityName());
        TRACE(s);
    #endif

    // system contains entity?
    if (pSystem->ContainEntity())
    {
        const int count = pSystem->GetEntityCount();

        // iterate through entities to publish
        for (int i = 0; i < count; ++i)
        {
            // get next entity
            ZBSystemEntity* pEntity = pSystem->GetEntityAt(i);

            if (!pEntity)
                continue;

            ZBLogicalSystemEntity* pLogicalSystemEntity = dynamic_cast<ZBLogicalSystemEntity*>(pEntity);

            // is entity belonging to logical system?
            if (pLogicalSystemEntity)
                // publish it
                PublishLogicalSystem(pLogicalSystemEntity);
        }
    }
}
//---------------------------------------------------------------------------
