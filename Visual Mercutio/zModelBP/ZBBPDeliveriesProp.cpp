// **************************************************************************************************************
// *                                  Classe ZBBPDeliveriesProperties                                            *
// **************************************************************************************************************
// * JMR-MODIF - Le 6 février 2006 - Ajout de la classe ZBBPDeliveriesProperties.                                *
// **************************************************************************************************************
// * Cette classe représente une propriété de type livraison.                                                    *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZBBPDeliveriesProp.h"

#include "zBaseLib\ZBTokenizer.h"

#include "zBaseLib\PSS_BaseDocument.h"

// Resources
#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 6 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)
using namespace sfl;

IMPLEMENT_SERIAL(ZBBPDeliveriesProperties, CObject, g_DefVersion)

// Constructeur par défaut de la classe ZBBPDeliveriesProperties.
ZBBPDeliveriesProperties::ZBBPDeliveriesProperties()
{
    m_DeliveryName            = _T( "" );
    m_DeliveryDeliverables    = _T( "" );
    m_DeliveryQuantity        = 0.0f;
    m_DeliveryPercentage    = 0.0f;
    m_DeliveryMain            = _T( "" );
}

// Constructeur par copie de la classe ZBBPDeliveriesProperties.
ZBBPDeliveriesProperties::ZBBPDeliveriesProperties( const ZBBPDeliveriesProperties& propProcess )
{
    m_DeliveryName            = propProcess.GetDeliveryName();
    m_DeliveryDeliverables    = propProcess.GetDeliveryDeliverables();
    m_DeliveryQuantity        = propProcess.GetDeliveryQuantity();
    m_DeliveryPercentage    = propProcess.GetDeliveryPercentage();
    m_DeliveryMain            = propProcess.GetDeliveryMain();
}

// Destructeur de la classe ZBBPDeliveriesProperties.
ZBBPDeliveriesProperties::~ZBBPDeliveriesProperties()
{
}

// Surcharge de l'opérateur = pour la classe ZBBPDeliveriesProperties.
ZBBPDeliveriesProperties& ZBBPDeliveriesProperties::operator=( const ZBBPDeliveriesProperties& propProcess )
{
    SetDeliveryName            ( propProcess.GetDeliveryName() );
    SetDeliveryDeliverables    ( propProcess.GetDeliveryDeliverables() );
    SetDeliveryQuantity        ( propProcess.GetDeliveryQuantity() );
    SetDeliveryPercentage    ( propProcess.GetDeliveryPercentage() );
    SetDeliveryMain            ( propProcess.GetDeliveryMain() );

    return *this;
}

// Surcharge de l'opérateur == pour la classe ZBBPDeliveriesProperties.
BOOL ZBBPDeliveriesProperties::operator==( const ZBBPDeliveriesProperties propProcess ) const
{
    return ( GetDeliveryName()            == propProcess.GetDeliveryName()            &&
             GetDeliveryDeliverables()    == propProcess.GetDeliveryDeliverables()    &&
             GetDeliveryQuantity()        == propProcess.GetDeliveryQuantity()        &&
             GetDeliveryPercentage()    == propProcess.GetDeliveryPercentage()        &&
             GetDeliveryMain()            == propProcess.GetDeliveryMain() );
}

// Cette fonction permet de fusionner deux objets ZBBPDeliveriesProperties, en spécifiant les données partagées.
void ZBBPDeliveriesProperties::Merge( ZBBPDeliveriesProperties* pProperty, DWORD dwChangeFlags )
{
    if ( pProperty )
    {
        if ( dwChangeFlags & Z_CHANGE_DELIVERY_NAME )
        {
            m_DeliveryName = pProperty->GetDeliveryName();
        }

        if ( dwChangeFlags & Z_CHANGE_DELIVERY_DELIVERABLES )
        {
            m_DeliveryDeliverables = pProperty->GetDeliveryDeliverables();
        }

        if ( dwChangeFlags & Z_CHANGE_DELIVERY_QUANTITY )
        {
            m_DeliveryQuantity = pProperty->GetDeliveryQuantity();
        }

        if ( dwChangeFlags & Z_CHANGE_DELIVERY_PRECENTAGE )
        {
            m_DeliveryPercentage = pProperty->GetDeliveryPercentage();
        }

        if ( dwChangeFlags & Z_CHANGE_DELIVERY_MAIN )
        {
            m_DeliveryMain = pProperty->GetDeliveryMain();
        }
    }
}

// Cette fonction permet de déterminer si deux objets ZBBPDeliveriesProperties sont égaux.
BOOL ZBBPDeliveriesProperties::IsEqual( ZBBPDeliveriesProperties* pProp )
{
    if ( pProp )
    {
        return ( *this == *pProp );
    }

    return FALSE;
}

// Cette fonction permet de déterminer si un livrable donné se trouve dans la liste des livrables de la livraison.
bool ZBBPDeliveriesProperties::IsDeliverableInDelivery( LPCTSTR lpszValue )
{
    ZBTokenizer token;    // Initialize the token with ; as separator

    CString str = token.GetFirstToken( lpszValue );
    
    // Run through all tokens
    while ( !str.IsEmpty() )
    {
        // If we found the same deliverable,
        // then sets the Found flag to true
        if ( str == lpszValue )
        {
            return true;
        }

        // Get the next token
        str = token.GetNextToken();
    }

    return false;
}

// Inscrit le nom de la livraison.
void ZBBPDeliveriesProperties::SetDeliveryName( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_DeliveryName = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Delivery name pointer!\n" ) );
        ASSERT( FALSE );
    }
}

// Fonction interne pour l'inscription du nom de la livraison.
void ZBBPDeliveriesProperties::SetDeliveryNameEx( const CString value )
{
    SetDeliveryName( value );
}

// Inscrit la liste des livrables de la livraison.
void ZBBPDeliveriesProperties::SetDeliveryDeliverables( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_DeliveryDeliverables = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Delivery Deliverables list pointer!\n" ) );
        ASSERT( FALSE );
    }
}

// Fonction interne pour l'inscription de la liste des livrables de la livraison.
void ZBBPDeliveriesProperties::SetDeliveryDeliverablesEx( const CString value )
{
    SetDeliveryDeliverables( value );
}

// Inscrit le nom du livrable principal de la livraison.
void ZBBPDeliveriesProperties::SetDeliveryMain( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_DeliveryMain = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Delivery main name pointer!\n" ) );
        ASSERT( FALSE );
    }
}

// Fonction interne pour l'inscription du nom du livrable principal de la livraison.
void ZBBPDeliveriesProperties::SetDeliveryMainEx( const CString value )
{
    SetDeliveryMain( value );
}

// Obtient une valeur de type CString, en spécifiant son ID.
BOOL ZBBPDeliveriesProperties::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_DELIVERY_NAME:
        {
            strValue = m_DeliveryName;
            break;
        }

        case Z_DELIVERY_DELIVERABLES:
        {
            strValue = m_DeliveryDeliverables;
            break;
        }

        case Z_DELIVERY_MAIN:
        {
            strValue = m_DeliveryMain;
            break;
        }

        default:
        {
            ASSERT( FALSE );
            return FALSE;
        }
    }

    return TRUE;
}

// Obtient une valeur de type int, en spécifiant son ID.
BOOL ZBBPDeliveriesProperties::GetValue( const int nPropId, int& nValue ) const
{
    switch ( nPropId )
    {
        case Z_DELIVERY_NAME:
        case Z_DELIVERY_DELIVERABLES:
        case Z_DELIVERY_QUANTITY:
        case Z_DELIVERY_PERCENTAGE:
        case Z_DELIVERY_MAIN:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

// Obtient une valeur de type UINT, en spécifiant son ID.
BOOL ZBBPDeliveriesProperties::GetValue( const int nPropId, UINT& nValue ) const
{
    switch ( nPropId )
    {
        case Z_DELIVERY_NAME:
        case Z_DELIVERY_DELIVERABLES:
        case Z_DELIVERY_QUANTITY:
        case Z_DELIVERY_PERCENTAGE:
        case Z_DELIVERY_MAIN:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

// Obtient une valeur de type DWORD, en spécifiant son ID.
BOOL ZBBPDeliveriesProperties::GetValue( const int nPropId, DWORD& dwValue ) const
{
    switch ( nPropId )
    {
        case Z_DELIVERY_NAME:
        case Z_DELIVERY_DELIVERABLES:
        case Z_DELIVERY_QUANTITY:
        case Z_DELIVERY_PERCENTAGE:
        case Z_DELIVERY_MAIN:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

// Obtient une valeur de type float, en spécifiant son ID.
BOOL ZBBPDeliveriesProperties::GetValue( const int nPropId, float& fValue ) const
{
    switch ( nPropId )
    {
        case Z_DELIVERY_NAME:
        case Z_DELIVERY_DELIVERABLES:
        case Z_DELIVERY_MAIN:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        case Z_DELIVERY_QUANTITY:
        {
            fValue = m_DeliveryQuantity;
            break;
        }

        case Z_DELIVERY_PERCENTAGE:
        {
            fValue = m_DeliveryPercentage;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

// Inscrit une valeur de type LPCTSTR, en spécifiant son ID.
BOOL ZBBPDeliveriesProperties::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_DELIVERY_NAME:
        {
            m_DeliveryName = lpszValue;
            break;
        }

        case Z_DELIVERY_DELIVERABLES:
        {
            m_DeliveryDeliverables = lpszValue;
            break;
        }

        case Z_DELIVERY_MAIN:
        {
            m_DeliveryMain = lpszValue;
            break;
        }

        default:
        {
            ASSERT( FALSE );
            return FALSE;
        }
    }

    return TRUE;
}

// Inscrit une valeur de type const int, en spécifiant son ID.
BOOL ZBBPDeliveriesProperties::SetValue( const int nPropId, const int nValue )
{
    switch ( nPropId )
    {
        case Z_DELIVERY_NAME:
        case Z_DELIVERY_DELIVERABLES:
        case Z_DELIVERY_QUANTITY:
        case Z_DELIVERY_PERCENTAGE:
        case Z_DELIVERY_MAIN:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

// Inscrit une valeur de type const UINT, en spécifiant son ID.
BOOL ZBBPDeliveriesProperties::SetValue( const int nPropId, const UINT nValue )
{
    switch ( nPropId )
    {
        case Z_DELIVERY_NAME:
        case Z_DELIVERY_DELIVERABLES:
        case Z_DELIVERY_QUANTITY:
        case Z_DELIVERY_PERCENTAGE:
        case Z_DELIVERY_MAIN:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

// Inscrit une valeur de type const DWORD, en spécifiant son ID.
BOOL ZBBPDeliveriesProperties::SetValue( const int nPropId, const DWORD dwValue )
{
    switch ( nPropId )
    {
        case Z_DELIVERY_NAME:
        case Z_DELIVERY_DELIVERABLES:
        case Z_DELIVERY_QUANTITY:
        case Z_DELIVERY_PERCENTAGE:
        case Z_DELIVERY_MAIN:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

// Inscrit une valeur de type const float, en spécifiant son ID.
BOOL ZBBPDeliveriesProperties::SetValue( const int nPropId, const float fValue )
{
    switch ( nPropId )
    {
        case Z_DELIVERY_NAME:
        case Z_DELIVERY_DELIVERABLES:
        case Z_DELIVERY_MAIN:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        case Z_DELIVERY_QUANTITY:
        {
            m_DeliveryQuantity = fValue;
            break;
        }

        case Z_DELIVERY_PERCENTAGE:
        {
            m_DeliveryPercentage = fValue;
            break;
        }

        default:
        {
            return FALSE;
        }
    }

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPDeliveriesProperties diagnostics

#ifdef _DEBUG
void ZBBPDeliveriesProperties::AssertValid() const
{
    CObject::AssertValid();
}

void ZBBPDeliveriesProperties::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );

    dc << _T( "Name = " )            << m_DeliveryName            << _T( "\n" );
    dc << _T( "Deliverables = " )    << m_DeliveryDeliverables    << _T( "\n" );
    dc << _T( "Main = " )            << m_DeliveryMain            << _T( "\n" );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBBPDeliveriesProperties serialization

void ZBBPDeliveriesProperties::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        TRACE( _T( "ZBBPDeliveriesProperties::Serialize : Start Save\n" ) );

        ar << m_DeliveryName;
        ar << m_DeliveryDeliverables;
        ar << m_DeliveryQuantity;
        ar << m_DeliveryPercentage;
        ar << m_DeliveryMain;

        TRACE( _T( "ZBBPDeliveriesProperties::Serialize : End Save\n" ) );
    }
    else
    {
        TRACE( _T( "ZBBPDeliveriesProperties::Serialize : Start Read\n" ) );

        ar >> m_DeliveryName;
        ar >> m_DeliveryDeliverables;
        ar >> m_DeliveryQuantity;
        ar >> m_DeliveryPercentage;
        ar >> m_DeliveryMain;

        TRACE( _T( "ZBBPDeliveriesProperties::Serialize : End Read\n" ) );
    }
}
