// ZUSOAPPublishModelAttributes.cpp: implementation of the ZUSOAPPublishModelAttributes class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUSOAPPublishModelAttributes.h"

// Include files for log
#include "zBaseLib\ZILog.h"

#include "zProperty\ZBDynamicPropertiesManager.h"

#include "zSOAP\pPublishSettings.h"

#include "zModel\ProcGraphModelDoc.h"
#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
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

// JMR-MODIF - Le 21 juin 2006 - Ajout de la variable m_pInfo dans le constructeur.
ZUSOAPPublishModelAttributes::ZUSOAPPublishModelAttributes( ZBPublishMessengerModelInformation*    pInfo,
                                                            ZDProcessGraphModelMdl*                pModel /*= NULL*/,
                                                            void*                                pClass /*= NULL*/ )
    : m_pInfo            ( pInfo ),
      ZUModelNavigation    ( pModel, pClass )
{
}

ZUSOAPPublishModelAttributes::~ZUSOAPPublishModelAttributes()
{
}

bool ZUSOAPPublishModelAttributes::OnStart()
{
    m_MessengerAddress = static_cast<const char*>( m_pClass );

    // Sets the correct address
    pPublishSettings::url = (const char*)m_MessengerAddress;

    // Reset the array of ids
    memset( m_IDArray, 0, sizeof( m_IDArray ) );

    // Nothing more to do
    return true;
}

bool ZUSOAPPublishModelAttributes::OnFinish()
{
    // Now, add the dynamics attributes
    CDocument* pDoc = m_pModel->GetDocument();

    if ( ISA( pDoc, ZDProcessGraphModelDoc ) )
    {
        ZBDynamicPropertiesManager* pDynPropMgr =
            dynamic_cast<ZDProcessGraphModelDoc*>( pDoc )->GetDynamicPropertiesManager();

        if ( pDynPropMgr )
        {
            ZBPropertySet PropSet;
            ZBDynamicPropertiesInfoIterator i( &pDynPropMgr->GetDynamicPropertiesInfoSet() );

            for ( _ZBDynamicPropertyInfo* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
            {
                PropSet.Add( pProp->m_pProperty );
            }

            // Add the attributes to the pPublishAttribDef class
            PublishAttribDef( PropSet );

            // Remove all properties, but don't delete the pointer itself
            PropSet.RemoveAll();
        }
    }

    // Send it to the soap server
    return m_pa.send();
}

bool ZUSOAPPublishModelAttributes::OnSymbol( ZBSymbol* pSymbol )
{
    ZBPropertySet PropSet;

    // Retrieve the property set from object
    pSymbol->FillProperties( PropSet, true, true );

    // Add the attributes to the pPublishAttribDef class
    PublishAttribDef( PropSet );

    // Remove all properties
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    PropSet.RemoveAll();

    return true;
}

bool ZUSOAPPublishModelAttributes::OnLink( ZBLinkSymbol* pLink )
{
    ZBPropertySet PropSet;

    // Retrieve the property set from object
    pLink->FillProperties( PropSet, true, true );

    // Add the attributes to the pPublishAttribDef class
    PublishAttribDef( PropSet );

    // Remove all properties
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    PropSet.RemoveAll();

    return true;
}

void ZUSOAPPublishModelAttributes::PublishAttribDef( ZBPropertySet& PropSet )
{
    // Remove all properties
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        short left    = pProp->GetCategoryID() & 0x0000FFFF;
        short right    = pProp->GetItemID() & 0x0000FFFF;
        int Key        = ( left << 16 ) | right;
        int Type    = 1;

        switch ( pProp->GetPTValueType() )
        {
            case ZBProperty::PT_DOUBLE:
            {
                Type = 2;
                break;
            }

            case ZBProperty::PT_FLOAT:
            {
                Type = 2;
                break;
            }

            case ZBProperty::PT_DATE:
            {
                Type = 3;
                break;
            }

            case ZBProperty::PT_TIMESPAN:
            {
                Type = 3;
                break;
            }

            case ZBProperty::PT_DURATION:
            {
                Type = 3;
                break;
            }

            case ZBProperty::PT_UNKNOWN:
            case ZBProperty::PT_STRING:
            default:
            {
                Type = 1;
                break;
            }
        }

        if ( !KeyExist( Key ) )
        {
            if ( m_pLog && m_pLog->IsInDebugMode() )
            {
                CString message;
                message.Format( IDS_AL_PUBLISHMODELATTRIBUTE,
                                pProp->GetItemID(),
                                (const char*)pProp->GetLabel(),
                                pProp->GetPTValueType() );

                ZBGenericSymbolErrorLine e( message );
                m_pLog->AddLine( e );
            }

            m_pa.addAttribDef( pattribdef( Key,                                // Attrib ID
                                           pProp->GetItemID(),                // Group ID
                                           String16( pProp->GetLabel() ),    // Text
                                           Type,                            // Type (1 = String)
                                           1 ) );                            // 1 = Mandatory (Always set to 1)

            // JMR-MODIF - Le 21 juin 2006 - Ajout de l'alias dans la publication.
            m_pa.addAlias( m_pInfo->m_MessengerAlias );

#ifdef _DEBUG
            CString s;

            s.Format( _T( " Attributes = %s Key =%d SubKey =%d\n" ),
                      (const char*)pProp->GetLabel(),
                      Key,
                      pProp->GetItemID() );

            TRACE( s );
#endif
        }
    }
}
//---------------------------------------------------------------------------
bool ZUSOAPPublishModelAttributes::KeyExist(int key)
{
    int index = 0;

    for (int i = 0; i < sizeof(m_IDArray) && m_IDArray[i] != 0; ++i)
    {
        index = i;

        if (m_IDArray[i] == key)
            return true;
    }

    // dosen't exist, check the array size before inserting the element
    if (index < sizeof(m_IDArray) / sizeof(int))
        // add it for the next time
        m_IDArray[index] = key;

    return false;
}
//---------------------------------------------------------------------------
