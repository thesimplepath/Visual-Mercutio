// ZUSOAPPublishLogicalSystem.cpp: implementation of the ZUSOAPPublishLogicalSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUSOAPPublishLogicalSystem.h"

#include "zSOAP\PSS_SoapPublisher_Settings.h"
#include "zModel\ZBLogicalSystemEntity.h"
#include "ZBPublishMessengerModelInformation.h"

#include "zModel\ProcGraphModelDoc.h"

// Include files for log
#include "zBaseLib\ZILog.h"
#include "zModel\ZBGenericSymbolErrorLine.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUSOAPPublishLogicalSystem::ZUSOAPPublishLogicalSystem( ZBPublishMessengerModelInformation*    pInfo,
                                                        ZILog*                                pLog    /*= NULL*/ )
    : m_pInfo    ( pInfo ),
      m_pLog    ( pLog )
{
}

ZUSOAPPublishLogicalSystem::~ZUSOAPPublishLogicalSystem()
{
}

bool ZUSOAPPublishLogicalSystem::Publish()
{
    if ( m_pInfo && m_pInfo->m_pDoc && m_pInfo->m_pDoc->GetMainLogicalSystem() )
    {
        // Sets the correct address
        PSS_SoapPublisher_Settings::m_Url = (const char*)m_pInfo->m_MessengerAddress;

        // Process all logical systems
        _PublishLogicalSystem( m_pInfo->m_pDoc->GetMainLogicalSystem() );

        return m_PubSys.Send();
    }

    return false;
}

void ZUSOAPPublishLogicalSystem::_PublishLogicalSystem( ZBLogicalSystemEntity* pSystem )
{
    if ( !pSystem )
    {
        return;
    }

    if ( m_pLog && m_pLog->IsInDebugMode() )
    {
        CString message;
        message.Format( IDS_AL_PUBLISHLOGICALSYSTEM, (const char*)pSystem->GetEntityName() );
        ZBGenericSymbolErrorLine e( message );
        m_pLog->AddLine( e );
    }

    m_PubSys.Add(PSS_SoapData_System(PSS_String16(pSystem->GetGUID()),
                                     PSS_String16(pSystem->GetParent() ? pSystem->GetParent()->GetGUID() : _T("")),
                                     PSS_String16(pSystem->GetEntityName()),
                                     PSS_String16(_T("")), // command in fact does not exist yet
                                     PSS_String16(_T("")), // parameters in fact does not exist yet
                                     PSS_String16(_T("")), // directory in fact does not exist yet
                                     0,                    // priority doesn't exist yet
                                     0));                  // Windows mode doesn't exist yet
    m_PubSys.AddAlias(m_pInfo->m_MessengerAlias);

#ifdef _DEBUG
    CString s;
    s.Format( _T( " System = %s\n" ), (const char*)pSystem->GetEntityName() );
    TRACE( s );
#endif

    if ( pSystem->ContainEntity() )
    {
        int Count = pSystem->GetEntityCount();

        for ( int i = 0; i < Count; ++i )
        {
            ZBSystemEntity* pEntity = pSystem->GetEntityAt( i );

            if ( !pEntity )
            {
                continue;
            }

            if ( ISA( pEntity, ZBLogicalSystemEntity ) )
            {
                _PublishLogicalSystem( dynamic_cast<ZBLogicalSystemEntity*>( pEntity ) );
            }
        }
    }
}
