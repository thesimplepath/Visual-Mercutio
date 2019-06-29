// **************************************************************************************************************
// *                                    Classe ZUSOAPPublishPrestations                                            *
// **************************************************************************************************************
// * JMR-MODIF - Le 30 mars 2006 - Création de la classe ZUSOAPPublishPrestations.                                *
// **************************************************************************************************************
// * Cette classe prend en charge la publication des prestations vers Messenger.                                *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZUSOAPPublishPrestations.h"

// processsoft
#include "zSOAP\PSS_SoapData_Settings.h"
#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUSOAPPublishPrestations::ZUSOAPPublishPrestations( ZBPublishMessengerModelInformation*    pInfo,
                                                    ZILog*                                pLog    /*= NULL*/ )
    : m_pInfo    ( pInfo ),
      m_pLog    ( pLog )
{
}

ZUSOAPPublishPrestations::~ZUSOAPPublishPrestations()
{
}

bool ZUSOAPPublishPrestations::Publish()
{
    if ( m_pInfo && m_pInfo->m_pDoc && m_pInfo->m_pDoc->GetMainLogicalPrestations() )
    {
        // set the correct address
        PSS_SoapData_Settings::m_Url = (const char*)m_pInfo->m_MessengerAddress;

        // Process all prestations
        _PublishPrestations( m_pInfo->m_pDoc->GetMainLogicalPrestations() );

        return m_pp.Send();
    }

    return false;
}

void ZUSOAPPublishPrestations::_PublishPrestations( ZBLogicalPrestationsEntity* p_Prestations )
{
    if ( !p_Prestations )
    {
        return;
    }

    if ( m_pLog && m_pLog->IsInDebugMode() )
    {
        CString message;
        message.Format( IDS_AL_PUBLISHPRESTATION, (const char*)p_Prestations->GetEntityName() );
        ZBGenericSymbolErrorLine e( message );
        m_pLog->AddLine( e );
    }

    m_pp.Set(PSS_SoapData_Prestations(PSS_String16(p_Prestations->GetGUID()),
                                      PSS_String16(p_Prestations->GetParent() ? p_Prestations->GetParent()->GetGUID() : _T("")),
                                      PSS_String16(p_Prestations->GetEntityName())));

    m_pp.AddAlias(m_pInfo->m_MessengerAlias);

#ifdef _DEBUG
    CString s;
    s.Format( _T( " Prestation = %s\n" ), (const char*)p_Prestations->GetEntityName() );
    TRACE( s );
#endif

    if ( p_Prestations->ContainEntity() )
    {
        int Count = p_Prestations->GetEntityCount();

        for ( int i = 0; i < Count; ++i )
        {
            ZBPrestationsEntity* pEntity = p_Prestations->GetEntityAt( i );

            if ( !pEntity )
            {
                continue;
            }

            if ( ISA( pEntity, ZBLogicalPrestationsEntity ) )
            {
                _PublishPrestations( dynamic_cast<ZBLogicalPrestationsEntity*>( pEntity ) );
            }
        }
    }
}
