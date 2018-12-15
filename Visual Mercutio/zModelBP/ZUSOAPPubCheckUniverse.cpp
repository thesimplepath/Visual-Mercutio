// **************************************************************************************************************
// *                                   Classe ZUSOAPPubCheckUniverse                                            *
// **************************************************************************************************************
// * JMR-MODIF - Le 21 juin 2006 - Création de la classe ZUSOAPPubCheckUniverse.                                *
// **************************************************************************************************************
// * Cette classe prend en charge le test des référentiels, et permet de déterminer si la publication est        *
// * valide.                                                                                                    *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZUSOAPPubCheckUniverse.h"

#include "zSOAP\pPublishSettings.h"
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

ZUSOAPPubCheckUniverse::ZUSOAPPubCheckUniverse( ZBPublishMessengerModelInformation*    pInfo,
                                                ZILog*                                pLog    /*= NULL*/ )
    : m_pInfo    ( pInfo ),
      m_pLog    ( pLog )
{
}

ZUSOAPPubCheckUniverse::~ZUSOAPPubCheckUniverse()
{
}

// Cette fonction permet de publier les GUID des réferentiels, et de tester la validité de ceux-ci.
bool ZUSOAPPubCheckUniverse::IsValid()
{
    if ( m_pInfo && m_pInfo->m_pDoc && m_pInfo->m_pDoc->GetMainLogicalSystem() )
    {
        // Sets the correct address
        pPublishSettings::url = (const char*)m_pInfo->m_MessengerAddress;

        m_cu.reset();

        m_cu.addUniverse( puniverse( String16( m_pInfo->m_pDoc->GetSystemDefGUID() ),
                                     String16( m_pInfo->m_pDoc->GetPrestationsDefGUID() ),
                                     String16( m_pInfo->m_pDoc->GetUserDefGUID() ) ) );

        m_cu.addAlias( m_pInfo->m_MessengerAlias );

#ifdef _DEBUG
        CString s;
        s.Format( _T( " System def GUID = %s\n" ), (const char*)m_pInfo->m_pDoc->GetSystemDefGUID() );
        TRACE( s );

        s.Format( _T( " Prestations def GUID = %s\n" ), (const char*)m_pInfo->m_pDoc->GetPrestationsDefGUID() );
        TRACE( s );

        s.Format( _T( " Workgroup def GUID = %s\n" ), (const char*)m_pInfo->m_pDoc->GetUserDefGUID() );
        TRACE( s );
#endif

        return m_cu.check();
    }

    return false;
}
