// **************************************************************************************************************
// *                                           Classe ZBBPRiskProperties                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 20 mai 2007 - Ajout de la classe ZBBPRiskProperties.                                        *
// **************************************************************************************************************
// * Cette classe représente une propriété de type risque.                                                        *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZBBPRiskProp.h"

// Resources
#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace sfl;

IMPLEMENT_SERIAL(ZBBPRiskProperties, CObject, g_DefVersion)

// Constructeur par défaut de la classe ZBBPRiskProperties.
ZBBPRiskProperties::ZBBPRiskProperties()
{
    m_RiskName            = _T( "" );
    m_RiskDesc            = _T( "" );
    m_RiskType            = _T( "" );
    m_RiskImpact        = 0;
    m_RiskProbability    = 0;
    m_RiskSeverity        = 0;
    m_RiskUE            = 0.0f;
    m_RiskPOA            = 0.0f;
    m_RiskAction        = false;
}

// Constructeur par copie de la classe ZBBPRiskProperties.
ZBBPRiskProperties::ZBBPRiskProperties( const ZBBPRiskProperties& propRisk )
{
    m_RiskName            = propRisk.GetRiskName();
    m_RiskDesc            = propRisk.GetRiskDesc();
    m_RiskType            = propRisk.GetRiskType();
    m_RiskImpact        = propRisk.GetRiskImpact();
    m_RiskProbability    = propRisk.GetRiskProbability();
    m_RiskSeverity        = propRisk.GetRiskSeverity();
    m_RiskUE            = propRisk.GetRiskUE();
    m_RiskPOA            = propRisk.GetRiskPOA();
    m_RiskAction        = propRisk.GetRiskAction();
}

// Destructeur de la classe ZBBPRiskProperties.
ZBBPRiskProperties::~ZBBPRiskProperties()
{
}

// Surcharge de l'opérateur = pour la classe ZBBPRiskProperties.
ZBBPRiskProperties& ZBBPRiskProperties::operator=( const ZBBPRiskProperties& propRisk )
{
    SetRiskName            ( propRisk.GetRiskName() );
    SetRiskDesc            ( propRisk.GetRiskDesc() );
    SetRiskType            ( propRisk.GetRiskType() );
    SetRiskImpact        ( propRisk.GetRiskImpact() );
    SetRiskProbability    ( propRisk.GetRiskProbability() );
    SetRiskSeverity        ( propRisk.GetRiskSeverity() );
    SetRiskUE            ( propRisk.GetRiskUE() );
    SetRiskPOA            ( propRisk.GetRiskPOA() );
    SetRiskAction        ( propRisk.GetRiskAction() );

    return *this;
}

// Surcharge de l'opérateur == pour la classe ZBBPRiskProperties.
BOOL ZBBPRiskProperties::operator==( const ZBBPRiskProperties propRisk ) const
{
    return ( GetRiskName()            == propRisk.GetRiskName()            &&
             GetRiskDesc()            == propRisk.GetRiskDesc()            &&
             GetRiskType()            == propRisk.GetRiskType()            &&
             GetRiskImpact()        == propRisk.GetRiskImpact()            &&
             GetRiskProbability()    == propRisk.GetRiskProbability()    &&
             GetRiskSeverity()        == propRisk.GetRiskSeverity()        &&
             GetRiskUE()            == propRisk.GetRiskUE()                &&
             GetRiskPOA()            == propRisk.GetRiskPOA()            &&
             GetRiskAction()        == propRisk.GetRiskAction() );
}

// Cette fonction permet de fusionner deux objets ZBBPRiskProperties, en spécifiant les données partagées.
void ZBBPRiskProperties::Merge( ZBBPRiskProperties* pProperty, DWORD dwChangeFlags )
{
    if ( pProperty )
    {
        if ( dwChangeFlags & Z_CHANGE_RISK_NAME )
        {
            m_RiskName = pProperty->GetRiskName();
        }

        if ( dwChangeFlags & Z_CHANGE_RISK_DESC )
        {
            m_RiskDesc = pProperty->GetRiskDesc();
        }

        if ( dwChangeFlags & Z_CHANGE_RISK_TYPE )
        {
            m_RiskType = pProperty->GetRiskType();
        }

        if ( dwChangeFlags & Z_CHANGE_RISK_IMPACT )
        {
            m_RiskImpact = pProperty->GetRiskImpact();
        }

        if ( dwChangeFlags & Z_CHANGE_RISK_PROBABILITY )
        {
            m_RiskProbability = pProperty->GetRiskProbability();
        }

        if ( dwChangeFlags & Z_CHANGE_RISK_SEVERITY )
        {
            m_RiskSeverity = pProperty->GetRiskSeverity();
        }

        if ( dwChangeFlags & Z_CHANGE_RISK_UE )
        {
            m_RiskUE = pProperty->GetRiskUE();
        }

        if ( dwChangeFlags & Z_CHANGE_RISK_POA )
        {
            m_RiskPOA = pProperty->GetRiskPOA();
        }

        if ( dwChangeFlags & Z_CHANGE_RISK_ACTION )
        {
            m_RiskAction = pProperty->GetRiskAction();
        }
    }
}

// Cette fonction permet de déterminer si deux objets ZBBPRiskProperties sont égaux.
BOOL ZBBPRiskProperties::IsEqual( ZBBPRiskProperties* pProp )
{
    if ( pProp )
    {
        return ( *this == *pProp );
    }

    return FALSE;
}

// Inscrit le nom du risque.
void ZBBPRiskProperties::SetRiskName( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_RiskName = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Risk name pointer!\n" ) );
        ASSERT( FALSE );
    }
}

// Fonction interne pour l'inscription du nom du risque.
void ZBBPRiskProperties::SetRiskNameEx( const CString value )
{
    SetRiskName( value );
}

// Inscrit la description du risque.
void ZBBPRiskProperties::SetRiskDesc( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_RiskDesc = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Risk Description pointer!\n" ) );
        ASSERT( FALSE );
    }
}

// Fonction interne pour l'inscription de la description du risque.
void ZBBPRiskProperties::SetRiskDescEx( const CString value )
{
    SetRiskDesc( value );
}

// Inscrit le type du risque.
void ZBBPRiskProperties::SetRiskType( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_RiskType = lpszValue;
    }
    else
    {
        TRACE0( _T( "Z -> Invalid Risk Type pointer!\n" ) );
        ASSERT( FALSE );
    }
}

// Fonction interne pour l'inscription du type du risque.
void ZBBPRiskProperties::SetRiskTypeEx( const CString value )
{
    SetRiskType( value );
}

// Obtient une valeur de type CString, en spécifiant son ID.
BOOL ZBBPRiskProperties::GetValue( const int nPropId, CString& strValue ) const
{
    switch ( nPropId )
    {
        case Z_RISK_NAME:
        {
            strValue = m_RiskName;
            break;
        }

        case Z_RISK_DESC:
        {
            strValue = m_RiskDesc;
            break;
        }

        case Z_RISK_TYPE:
        {
            strValue = m_RiskType;
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
BOOL ZBBPRiskProperties::GetValue( const int nPropId, int& nValue ) const
{
    switch ( nPropId )
    {
        case Z_RISK_IMPACT:
        {
            nValue = m_RiskImpact;
            break;
        }

        case Z_RISK_PROBABILITY:
        {
            nValue = m_RiskProbability;
            break;
        }

        case Z_RISK_SEVERITY:
        {
            nValue = m_RiskSeverity;
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

// Obtient une valeur de type UINT, en spécifiant son ID.
BOOL ZBBPRiskProperties::GetValue( const int nPropId, UINT& nValue ) const
{
    switch ( nPropId )
    {
        case Z_RISK_NAME:
        case Z_RISK_DESC:
        case Z_RISK_TYPE:
        case Z_RISK_IMPACT:
        case Z_RISK_PROBABILITY:
        case Z_RISK_SEVERITY:
        case Z_RISK_UE:
        case Z_RISK_POA:
        case Z_RISK_ACTION:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            ASSERT( FALSE );
            return FALSE;
        }
    }

    return TRUE;
}

// Obtient une valeur de type DWORD, en spécifiant son ID.
BOOL ZBBPRiskProperties::GetValue( const int nPropId, DWORD& dwValue ) const
{
    switch ( nPropId )
    {
        case Z_RISK_NAME:
        case Z_RISK_DESC:
        case Z_RISK_TYPE:
        case Z_RISK_IMPACT:
        case Z_RISK_PROBABILITY:
        case Z_RISK_SEVERITY:
        case Z_RISK_UE:
        case Z_RISK_POA:
        case Z_RISK_ACTION:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            ASSERT( FALSE );
            return FALSE;
        }
    }

    return TRUE;
}

// Obtient une valeur de type float, en spécifiant son ID.
BOOL ZBBPRiskProperties::GetValue( const int nPropId, float& fValue ) const
{
    switch ( nPropId )
    {
        case Z_RISK_UE:
        {
            fValue = m_RiskUE;
            break;
        }

        case Z_RISK_POA:
        {
            fValue = m_RiskPOA;
        }

        default:
        {
            ASSERT( FALSE );
            return FALSE;
        }
    }

    return TRUE;
}

// Obtient une valeur de type bool, en spécifiant son ID.
BOOL ZBBPRiskProperties::GetValue( const int nPropId, bool& bValue ) const
{
    switch ( nPropId )
    {
        case Z_RISK_ACTION:
        {
            bValue = m_RiskAction;
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

// Inscrit une valeur de type LPCTSTR, en spécifiant son ID.
BOOL ZBBPRiskProperties::SetValue( const int nPropId, LPCTSTR lpszValue )
{
    switch ( nPropId )
    {
        case Z_RISK_NAME:
        {
            m_RiskName = lpszValue;
            break;
        }

        case Z_RISK_DESC:
        {
            m_RiskDesc = lpszValue;
            break;
        }

        case Z_RISK_TYPE:
        {
            m_RiskType = lpszValue;
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
BOOL ZBBPRiskProperties::SetValue( const int nPropId, const int nValue )
{
    switch ( nPropId )
    {
        case Z_RISK_IMPACT:
        {
            m_RiskImpact = nValue;
            break;
        }

        case Z_RISK_PROBABILITY:
        {
            m_RiskProbability = nValue;
            break;
        }

        case Z_RISK_SEVERITY:
        {
            m_RiskSeverity = nValue;
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

// Inscrit une valeur de type const UINT, en spécifiant son ID.
BOOL ZBBPRiskProperties::SetValue( const int nPropId, const UINT nValue )
{
    switch ( nPropId )
    {
        case Z_RISK_NAME:
        case Z_RISK_DESC:
        case Z_RISK_TYPE:
        case Z_RISK_IMPACT:
        case Z_RISK_PROBABILITY:
        case Z_RISK_SEVERITY:
        case Z_RISK_UE:
        case Z_RISK_POA:
        case Z_RISK_ACTION:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            ASSERT( FALSE );
            return FALSE;
        }
    }

    return TRUE;
}

// Inscrit une valeur de type const DWORD, en spécifiant son ID.
BOOL ZBBPRiskProperties::SetValue( const int nPropId, const DWORD dwValue )
{
    switch ( nPropId )
    {
        case Z_RISK_NAME:
        case Z_RISK_DESC:
        case Z_RISK_TYPE:
        case Z_RISK_IMPACT:
        case Z_RISK_PROBABILITY:
        case Z_RISK_SEVERITY:
        case Z_RISK_UE:
        case Z_RISK_POA:
        case Z_RISK_ACTION:
        {
            ASSERT( FALSE );
            return FALSE;
        }

        default:
        {
            ASSERT( FALSE );
            return FALSE;
        }
    }

    return TRUE;
}

// Inscrit une valeur de type const float, en spécifiant son ID.
BOOL ZBBPRiskProperties::SetValue( const int nPropId, const float fValue )
{
    switch ( nPropId )
    {
        case Z_RISK_UE:
        {
            m_RiskUE = fValue;
            break;
        }

        case Z_RISK_POA:
        {
            m_RiskPOA = fValue;
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

// Inscrit une valeur de type const bool, en spécifiant son ID.
BOOL ZBBPRiskProperties::SetValue( const int nPropId, const bool bValue )
{
    switch ( nPropId )
    {
        case Z_RISK_ACTION:
        {
            m_RiskAction = bValue;
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

/////////////////////////////////////////////////////////////////////////////
// ZBBPRiskProperties diagnostics

#ifdef _DEBUG
void ZBBPRiskProperties::AssertValid() const
{
    CObject::AssertValid();
}

void ZBBPRiskProperties::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );

    dc << _T( "Name = " )    << m_RiskName    << _T( "\n" );
    dc << _T( "Desc = " )    << m_RiskDesc    << _T( "\n" );
    dc << _T( "Type = " )    << m_RiskType    << _T( "\n" );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBBPRiskProperties serialization

void ZBBPRiskProperties::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        TRACE( _T( "ZBBPRiskProperties::Serialize : Start Save\n" ) );

        ar << m_RiskName;
        ar << m_RiskDesc;
        ar << m_RiskType;
        ar << m_RiskImpact;
        ar << m_RiskProbability;
        ar << m_RiskSeverity;
        ar << m_RiskUE;
        ar << m_RiskPOA;
        ar << (WORD)m_RiskAction;

        TRACE( _T( "ZBBPRiskProperties::Serialize : End Save\n" ) );
    }
    else
    {
        TRACE( _T( "ZBBPRiskProperties::Serialize : Start Read\n" ) );

        ar >> m_RiskName;
        ar >> m_RiskDesc;
        ar >> m_RiskType;
        ar >> m_RiskImpact;
        ar >> m_RiskProbability;
        ar >> m_RiskSeverity;
        ar >> m_RiskUE;
        ar >> m_RiskPOA;

        WORD wValue;
        ar >> wValue;
        m_RiskAction = ( ( wValue == 1 ) ? ( true ) : ( false ) );

        TRACE( _T( "ZBBPRiskProperties::Serialize : End Read\n" ) );
    }
}
