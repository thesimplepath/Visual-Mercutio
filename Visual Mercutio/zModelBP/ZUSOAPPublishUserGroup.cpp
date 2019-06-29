// ZUSOAPPublishUserGroup.cpp: implementation of the ZUSOAPPublishUserGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUSOAPPublishUserGroup.h"

#include "ZBPublishMessengerModelInformation.h"
#include "zSOAP\PSS_SoapData_Settings.h"

#include "zModel\ProcGraphModelDoc.h"
#include "zModel\ZBUserGroupEntity.h"
#include "zModel\ZBUserRoleEntity.h"

// Include files for log
#include "zBaseLib\ZILog.h"
#include "zModel\ZBGenericSymbolErrorLine.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 24 janvier 2006 - Ajout des décorations unicode _T(), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUSOAPPublishUserGroup::ZUSOAPPublishUserGroup( ZBPublishMessengerModelInformation* pInfo, ZILog* pLog /*= NULL*/ )
    : m_pInfo    ( pInfo ),
      m_pLog    ( pLog )
{
}

ZUSOAPPublishUserGroup::~ZUSOAPPublishUserGroup()
{
}

bool ZUSOAPPublishUserGroup::Publish()
{
    if ( m_pInfo &&
         m_pInfo->m_pDoc &&
         m_pInfo->m_pDoc->GetMainUserGroup() )
    {
        // Sets the correct address
        PSS_SoapData_Settings::m_Url = (const char*)m_pInfo->m_MessengerAddress;

        // Process all user groups
        _PublishUserGroup( m_pInfo->m_pDoc->GetMainUserGroup() );

        return m_PubWorkgroup.Send();
    }

    return false;
}

void ZUSOAPPublishUserGroup::_PublishUserGroup( ZBUserGroupEntity* pGroup )
{
    if ( !pGroup )
    {
        return;
    }

    if ( m_pLog && m_pLog->IsInDebugMode() )
    {
        CString message;
        message.Format( IDS_AL_PUBLISHUSERGROUP, (const char*)pGroup->GetEntityName() );
        ZBGenericSymbolErrorLine e( message );
        m_pLog->AddLine( e );
    }

    // JMR-MODIF - Le 6 décembre 2006 - Conversion de float à string pour le coût journalier.
    CString DayCost;
    DayCost.Format( _T( "%.2f" ), pGroup->GetEntityCost() );

    m_PubWorkgroup.Add(PSS_SoapData_Workgroup(PSS_String16(pGroup->GetGUID()),                                             // workgroup GUID
                                              PSS_String16(pGroup->GetParent() ? pGroup->GetParent()->GetGUID() : _T("")), // parent GUID
                                              PSS_String16(pGroup->GetEntityName()),                                       // workgroup name
                                              PSS_String16(pGroup->GetEntityDescription()),                                // mission
                                              PSS_String16(DayCost)));                                                     // day cost
    m_PubWorkgroup.AddAlias(m_pInfo->m_MessengerAlias);

#ifdef _DEBUG
    CString s;
    s.Format( _T( " Group = %s\n" ), (const char*)pGroup->GetEntityName() );
    TRACE( s );
#endif

    if ( pGroup->ContainEntity() )
    {
        int Count = pGroup->GetEntityCount();

        for ( int i = 0; i < Count; ++i )
        {
            ZBUserEntity* pEntity = pGroup->GetEntityAt( i );

            if ( !pEntity )
                continue;

            if ( ISA( pEntity, ZBUserGroupEntity ) )
                _PublishUserGroup( dynamic_cast<ZBUserGroupEntity*>( pEntity ) );

            // JMR-MODIF - Le 24 janvier 2006 - Suppression de l'appel à la routine de publication des rôles.
            /*
            if ( ISA( pEntity, ZBUserRoleEntity ) )
                 _PublishUserRole( dynamic_cast<ZBUserRoleEntity*>( pEntity ) );
            */
        }
    }
}

// JMR-MODIF - Le 24 janvier 2006 - Suppression de la routine d'affichage des rôles. Les rôles sont appelée équipes
// dans l'arbre des groupes.
/*
void ZUSOAPPublishUserGroup::_PublishUserRole( ZBUserRoleEntity* pRole )
{
    if ( !pRole )
        return;

    if ( m_pLog && m_pLog->IsInDebugMode() )
    {
        CString message;
        message.Format( IDS_AL_PUBLISHROLE, (const char*)pRole->GetEntityName() );
        ZBGenericSymbolErrorLine e( message );
        m_pLog->AddLine( e );
    }

    m_pw.addWorkgroup(pworkgroup( String16( pRole->GetGUID() ),                                                                // Role GUID
                                  String16( ( pRole->GetParent() != NULL ) ? pRole->GetParent()->GetGUID() : _T( "" ) ),    // Parent GUID
                                  String16( pRole->GetEntityName() ) ) );                                                    // Role name
#ifdef _DEBUG
    CString s;
    s.Format( _T( " Group = %s\n" ), (const char*)pRole->GetEntityName() );
    TRACE( s );
#endif
}
*/
