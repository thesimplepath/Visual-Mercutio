// **************************************************************************************************************
// *                                               Classe ZBProcRisk                                            *
// **************************************************************************************************************
// * JMR-MODIF - Le 3 juin 2007 - Ajout de la classe ZBProcRisk.                                                *
// **************************************************************************************************************
// * Cette classe est un gestionnaire pour l'ensemble des propriétés de type risques.                            *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZBProcRisk.h"

#include "PSS_RiskPropertiesBP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// constant definition
const int LastDeliveryIDProperties = ZS_BP_PROP_RISK + 39;

IMPLEMENT_SERIAL(ZBProcRisk, CObject, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Constructeur par défaut de la classe ZBProcRisk.
ZBProcRisk::ZBProcRisk( CODSymbolComponent* pParent /*= NULL*/ )
    : m_pParent( pParent )
{
}

// Constructeur par copie de la classe ZBProcRisk.
ZBProcRisk::ZBProcRisk( const ZBProcRisk& src )
{
    *this = src;
}

// Destructeur de la classe ZBProcRisk.
ZBProcRisk::~ZBProcRisk()
{
    RemoveAllRisks();
}

// Surcharge de l'opérateur = pour la classe ZBProcRisk.
ZBProcRisk& ZBProcRisk::operator=( const ZBProcRisk& src )
{
    // Copy the members.
    ZBBPRiskPropertiesIterator i( &const_cast<ZBProcRisk&>( src ).GetRiskSet() );

    for (PSS_RiskPropertiesBP* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        AddRisk( pProp->Dup() );
    }

    m_pParent = src.m_pParent;

    return *this;
}

// Cette fonction permet d'effectuer un duplicata de l'objet instancié.
ZBProcRisk* ZBProcRisk::Dup() const
{
    return ( new ZBProcRisk( *this ) );
}

// Cette fonction permet l'attribution du composant parent.
void ZBProcRisk::SetParent( CODSymbolComponent* pParent )
{
    m_pParent = pParent;
}

// Cette fonction permet la création d'une propriété par défaut.
bool ZBProcRisk::CreateInitialProperties()
{
    if ( GetRiskCount() > 0 )
    {
        return true;
    }

    PSS_RiskPropertiesBP* pProps = new PSS_RiskPropertiesBP();

    if ( AddRisk( pProps ) >= 0 )
    {
        return true;
    }

    return false;
}

// Cette fonction permet l'ajout d'une nouvelle propriété vide, de type risque, dans la liste.
int ZBProcRisk::AddNewRisk()
{
    PSS_RiskPropertiesBP* pProps = new PSS_RiskPropertiesBP();

    return AddRisk( pProps );
}

// Cette fonction permet l'ajout d'une propriété de type risque dans la liste.
int ZBProcRisk::AddRisk(PSS_RiskPropertiesBP* pProperty )
{
    if ( pProperty )
    {
        // If no risk name specified, set it by default
        if ( pProperty->GetRiskName().IsEmpty() )
        {
            pProperty->SetRiskName( GetNextRiskValidName() );
        }

        m_Set.Add( pProperty );

        // Returns the index
        return GetRiskCount() - 1;
    }

    return -1;
}

// Cette fonction permet la suppression d'une propriété dans la liste.
bool ZBProcRisk::DeleteRisk( size_t Index )
{
    if ( Index < GetRiskCount() )
    {
        PSS_RiskPropertiesBP* pProperty = GetProperty( Index );

        if ( pProperty )
        {
            m_Set.RemoveAt( Index );
            delete pProperty;
            return true;
        }
    }

    return false;
}

// Cette fonction permet la suppression d'une propriété dans la liste.
bool ZBProcRisk::DeleteRisk(PSS_RiskPropertiesBP* pProperty )
{
    ZBBPRiskPropertiesIterator i( &m_Set );

    for (PSS_RiskPropertiesBP* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProperty == pProp )
        {
            i.Remove();
            delete pProp;
            return true;
        }
    }

    return false;
}

// Cette fonction permet la suppression de toutes les propriétés dans la liste.
void ZBProcRisk::RemoveAllRisks()
{
    ZBBPRiskPropertiesIterator i( &m_Set );

    for (PSS_RiskPropertiesBP* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    // Then, remove all elements
    m_Set.RemoveAll();
}

// Permet de savoir si le nom du risque est déjà utilisé par une propriété.
bool ZBProcRisk::RiskNameExist( const CString Name ) const
{
    // Run through the set and build the string
    ZBBPRiskPropertiesIterator i( &m_Set );

    for (PSS_RiskPropertiesBP* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->GetRiskName() == Name )
        {
            return true;
        }
    }

    return false;
}

// Obtient le prochain nom valide pour un risque.
CString ZBProcRisk::GetNextRiskValidName() const
{
    CString str;
    int i = 1;

    do
    {
        str.Format( _T( "Risque %d" ), i++ );
    }
    while ( RiskNameExist( str ) == true );

    return str;
}

// Obtient le nom du risque.
CString ZBProcRisk::GetRiskName( size_t Index ) const
{
    if ( Index < GetRiskCount() )
    {
        return m_Set.GetAt( Index )->GetRiskName();
    }

    return _T( "" );
}

// Inscrit le nom du risque.
void ZBProcRisk::SetRiskName( size_t Index, CString Value )
{
    if ( Index < GetRiskCount() )
    {
        m_Set.GetAt( Index )->SetRiskName( Value );
    }
}

// Obtient la description du risque.
CString ZBProcRisk::GetRiskDesc( size_t Index ) const
{
    if ( Index < GetRiskCount() )
    {
        return m_Set.GetAt( Index )->GetRiskDesc();
    }

    return _T( "" );
}

// Inscrit la description du risque.
void ZBProcRisk::SetRiskDesc( size_t Index, CString Value )
{
    if ( Index < GetRiskCount() )
    {
        m_Set.GetAt( Index )->SetRiskDesc( Value );
    }
}

// Obtient le type du risque.
CString ZBProcRisk::GetRiskType( size_t Index ) const
{
    if ( Index < GetRiskCount() )
    {
        return m_Set.GetAt( Index )->GetRiskType();
    }

    return _T( "" );
}

// Inscrit le type du risque.
void ZBProcRisk::SetRiskType( size_t Index, CString Value )
{
    if ( Index < GetRiskCount() )
    {
        m_Set.GetAt( Index )->SetRiskType( Value );
    }
}

// Obtient l'impact du risque.
int ZBProcRisk::GetRiskImpact( size_t Index ) const
{
    if ( Index < GetRiskCount() )
    {
        return m_Set.GetAt( Index )->GetRiskImpact();
    }

    return 0;
}

// Inscrit l'impact du risque.
void ZBProcRisk::SetRiskImpact( size_t Index, int Value )
{
    if ( Index < GetRiskCount() )
    {
        m_Set.GetAt( Index )->SetRiskImpact( Value );
    }
}

// Obtient la probabilité du risque.
int ZBProcRisk::GetRiskProbability( size_t Index ) const
{
    if ( Index < GetRiskCount() )
    {
        return m_Set.GetAt( Index )->GetRiskProbability();
    }

    return 0;
}

// Inscrit la probabilité du risque.
void ZBProcRisk::SetRiskProbability( size_t Index, int Value )
{
    if ( Index < GetRiskCount() )
    {
        m_Set.GetAt( Index )->SetRiskProbability( Value );
    }
}

// Obtient la sévérité du risque.
int ZBProcRisk::GetRiskSeverity( size_t Index ) const
{
    if ( Index < GetRiskCount() )
    {
        return m_Set.GetAt( Index )->GetRiskSeverity();
    }

    return 0;
}

// Inscrit la sévérité du risque.
void ZBProcRisk::SetRiskSeverity( size_t Index, int Value )
{
    if ( Index < GetRiskCount() )
    {
        m_Set.GetAt( Index )->SetRiskSeverity( Value );
    }
}

// Obtient l'estimation unitaire du risque.
float ZBProcRisk::GetRiskUE( size_t Index ) const
{
    if ( Index < GetRiskCount() )
    {
        return m_Set.GetAt( Index )->GetRiskUE();
    }

    return 0.0f;
}

// Inscrit l'estimation unitaire du risque.
void ZBProcRisk::SetRiskUE( size_t Index, float Value )
{
    if ( Index < GetRiskCount() )
    {
        m_Set.GetAt( Index )->SetRiskUE( Value );
    }
}

// Obtient la perte operationnelle annuelle du risque.
float ZBProcRisk::GetRiskPOA( size_t Index ) const
{
    if ( Index < GetRiskCount() )
    {
        return m_Set.GetAt( Index )->GetRiskPOA();
    }

    return 0.0f;
}

// Inscrit la perte operationnelle annuelle du risque.
void ZBProcRisk::SetRiskPOA( size_t Index, float Value )
{
    if ( Index < GetRiskCount() )
    {
        m_Set.GetAt( Index )->SetRiskPOA( Value );
    }
}

// Obtient l'action du risque.
bool ZBProcRisk::GetRiskAction( size_t Index ) const
{
    if ( Index < GetRiskCount() )
    {
        return m_Set.GetAt( Index )->GetRiskAction();
    }

    return false;
}

// Inscrit l'action du risque.
void ZBProcRisk::SetRiskAction( size_t Index, bool Value )
{
    if ( Index < GetRiskCount() )
    {
        m_Set.GetAt( Index )->SetRiskAction( Value );
    }
}

// Fonction de sérialisation de l'objet.
void ZBProcRisk::Serialize( CArchive& ar )
{
    // Only if the object is serialize from and to a document
    if ( ar.m_pDocument )
    {
        if ( ar.IsStoring() )
        {
            TRACE( _T( "ZBProcRisk::Serialize : Start Save\n" ) );
    
            // Serialize the size of the set
            ar << (int)m_Set.GetSize();

            ZBBPRiskPropertiesIterator i( &m_Set );

            for (PSS_RiskPropertiesBP* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
            {
                ar << pProp;
            }

            TRACE( _T( "ZBProcRisk::Serialize : End Save\n" ) );
        }
        else
        {
            TRACE( _T( "ZBProcRisk::Serialize : Start Read\n" ) );

            RemoveAllRisks();

            // Read the size of the set
            int Count;
            ar >> Count;

            PSS_RiskPropertiesBP* pProp;

            for ( int i = 0; i < (int)Count; ++i )
            {
                ar >> pProp;
                AddRisk( pProp );
            }
        
            TRACE( _T( "ZBProcRisk::Serialize : End Read\n" ) );
        }
    }
}
