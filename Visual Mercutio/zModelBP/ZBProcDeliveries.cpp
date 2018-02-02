// **************************************************************************************************************
// *										Classe ZBProcDeliveries												*
// **************************************************************************************************************
// * JMR-MODIF - Le 6 février 2006 - Ajout de la classe ZBProcDeliveries.										*
// **************************************************************************************************************
// * Cette classe est un gestionnaire pour l'ensemble des propriétés de type livraisons.						*
// **************************************************************************************************************

#include "stdafx.h"
#include "ZBProcDeliveries.h"

#include "ZBBPDeliveriesProp.h"

#include "zBaseLib\ZBTokenizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// constant definition
const int LastDeliveryIDProperties = ZS_BP_PROP_DELIVERIES + 39;

IMPLEMENT_SERIAL( ZBProcDeliveries, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Constructeur par défaut de la classe ZBProcDeliveries.
ZBProcDeliveries::ZBProcDeliveries( CODSymbolComponent* pParent /*= NULL*/ )
	: m_pParent( pParent )
{
}

// Constructeur par copie de la classe ZBProcDeliveries.
ZBProcDeliveries::ZBProcDeliveries( const ZBProcDeliveries& src )
{
	*this = src;
}

// Destructeur de la classe ZBProcDeliveries.
ZBProcDeliveries::~ZBProcDeliveries()
{
	RemoveAllDeliveries();
}

// Surcharge de l'opérateur = pour la classe ZBProcDeliveries.
ZBProcDeliveries& ZBProcDeliveries::operator=( const ZBProcDeliveries& src )
{
	// Copy the members.
	ZBBPDeliveriesPropertiesIterator i( &const_cast<ZBProcDeliveries&>( src ).GetDeliverySet() );

	for ( ZBBPDeliveriesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
	{
		AddDelivery( pProp->Dup() );
	}

	m_pParent = src.m_pParent;

	return *this;
}

// Cette fonction permet d'effectuer un duplicata de l'objet instancié.
ZBProcDeliveries* ZBProcDeliveries::Dup() const
{
	return ( new ZBProcDeliveries( *this ) );
}

// Cette fonction permet l'attribution du composant parent.
void ZBProcDeliveries::SetParent( CODSymbolComponent* pParent )
{
	m_pParent = pParent;
}

// Cette fonction permet la création d'une propriété par défaut.
bool ZBProcDeliveries::CreateInitialProperties()
{
	if ( GetDeliveriesCount() > 0 )
	{
		return true;
	}

	ZBBPDeliveriesProperties* pProps = new ZBBPDeliveriesProperties;

	if ( AddDelivery( pProps ) >= 0 )
	{
		return true;
	}

	return false;
}

// Cette fonction permet l'ajout d'une nouvelle propriété vide, de type livraison, dans la liste.
int ZBProcDeliveries::AddNewDelivery()
{
	ZBBPDeliveriesProperties* pProps = new ZBBPDeliveriesProperties;

	return AddDelivery( pProps );
}

// Cette fonction permet l'ajout d'une propriété de type livraison dans la liste.
int ZBProcDeliveries::AddDelivery( ZBBPDeliveriesProperties* pProperty )
{
	if ( pProperty )
	{
		// If no delivery name specified, set it by default
		if ( pProperty->GetDeliveryName().IsEmpty() )
		{
			pProperty->SetDeliveryName( GetNextDeliveryValidName() );
		}

		m_Set.Add( pProperty );

		// Returns the index
		return GetDeliveriesCount() - 1;
	}

	return -1;
}

// Cette fonction permet la suppression d'une propriété dans la liste.
bool ZBProcDeliveries::DeleteDelivery( size_t Index )
{
	if ( Index < GetDeliveriesCount() )
	{
		ZBBPDeliveriesProperties* pProperty = GetProperty( Index );

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
bool ZBProcDeliveries::DeleteDelivery( ZBBPDeliveriesProperties* pProperty )
{
	ZBBPDeliveriesPropertiesIterator i( &m_Set );

	for ( ZBBPDeliveriesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
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
void ZBProcDeliveries::RemoveAllDeliveries()
{
	ZBBPDeliveriesPropertiesIterator i( &m_Set );

	for ( ZBBPDeliveriesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
	{
		delete pProp;
	}

	// Then, remove all elements
	m_Set.RemoveAll();
}

// Obtient le nom de la livraison.
CString ZBProcDeliveries::GetDeliveryName( size_t Index ) const
{
	if ( Index < GetDeliveriesCount() )
	{
		return m_Set.GetAt( Index )->GetDeliveryName();
	}

	return _T( "" );
}

// Inscrit le nom de la livraison.
void ZBProcDeliveries::SetDeliveryName( size_t Index, CString Value )
{
	if ( Index < GetDeliveriesCount() )
	{
		m_Set.GetAt( Index )->SetDeliveryName( Value );
	}
}

// Obtient la liste des livrables associés à cette livraison
CString ZBProcDeliveries::GetDeliveryDeliverables( size_t Index ) const
{
	if ( Index < GetDeliveriesCount() )
	{
		return m_Set.GetAt( Index )->GetDeliveryDeliverables();
	}

	return _T( "" );
}

// Inscrit la liste des livrables associés à cette livraison
void ZBProcDeliveries::SetDeliveryDeliverables( size_t Index, CString Value )
{
	if ( Index < GetDeliveriesCount() )
	{
		m_Set.GetAt( Index )->SetDeliveryDeliverables( Value );
	}
}

// Cette fonction permet l'ajout d'un livrable à la liste des livrables de la propriété demandée.
bool ZBProcDeliveries::AddDeliveryDeliverable( size_t Index, CString Value )
{
	CString Deliverables = GetDeliveryDeliverables( Index );

	ZBTokenizer token;	// Initialize the token with ; as separator

	CString str = token.GetFirstToken( Deliverables );
	bool Found = false;
	
	// Run through all tokens
	while ( !str.IsEmpty() )
	{
		// If we found the same deliverable,
		// then sets the Found flag to true
		if ( str == Value )
		{
			Found = true;
			break;
		}

		// Get the next token
		str = token.GetNextToken();
	}

	// If not found, add it
	if ( Found == false )
	{
		token.InitializeString( Deliverables );
		token.AddToken( Value );

		// Set the new deliverable complete string
		SetDeliveryDeliverables( Index, token.GetString() );
	}

	return true;
}

// Cette fonction permet la suppression d'un livrable dans la liste des livrables de la propriété demandée.
bool ZBProcDeliveries::RemoveDeliveryDeliverable( size_t Index, CString Value )
{
	CString Deliverables = GetDeliveryDeliverables( Index );

	ZBTokenizer srcToken;	// Initialize the source token with ; as separator
	ZBTokenizer dstToken;	// Initialize the destination token with ; as separator

	CString str = srcToken.GetFirstToken( Deliverables );
	bool Found = false;

	// Run through all tokens
	while ( !str.IsEmpty() )
	{
		// If we found the same deliverable,
		// then sets the Found flag to true
		// and skip it
		if ( str == Value )
		{
			Found = true;
		}
		else
		{
			// If not the same, can be added to the destination token
			dstToken.AddToken( str );
		}

		// Get the next token
		str = srcToken.GetNextToken();
	}

	// If we found it, sets the new string
	if ( Found == true )
	{
		// Set the new deliverable complete string
		SetDeliveryDeliverables( Index, dstToken.GetString() );
		return true;
	}

	return false;
}

// Cette fonction permet la suppression de la liste des livrables de la propriété demandée.
bool ZBProcDeliveries::RemoveAllDeliveryDeliverable( size_t Index )
{
	SetDeliveryDeliverables( Index, _T( "" ) );
	return true;
}

// Obtient la quantité de la livraison.
float ZBProcDeliveries::GetDeliveryQuantity( size_t Index ) const
{
	if ( Index < GetDeliveriesCount() )
	{
		return m_Set.GetAt( Index )->GetDeliveryQuantity();
	}

	return 0.0f;
}

// Inscrit la quantité de la livraison.
void ZBProcDeliveries::SetDeliveryQuantity( size_t Index, const float value )
{
	if ( Index < GetDeliveriesCount() )
	{
		m_Set.GetAt( Index )->SetDeliveryQuantity( value );
	}
}

// Obtient le pourcentage de la livraison.
float ZBProcDeliveries::GetDeliveryPercentage( size_t Index ) const
{
	if ( Index < GetDeliveriesCount() )
	{
		return m_Set.GetAt( Index )->GetDeliveryPercentage();
	}

	return 0.0f;
}

// Inscrit le pourcentage de la livraison.
void ZBProcDeliveries::SetDeliveryPercentage( size_t Index, const float value )
{
	if ( Index < GetDeliveriesCount() )
	{
		m_Set.GetAt( Index )->SetDeliveryPercentage( value );
	}
}

// Obtient le nom du livrable principal de la livraison.
CString ZBProcDeliveries::GetDeliveryMain( size_t Index ) const
{
	if ( Index < GetDeliveriesCount() )
	{
		return m_Set.GetAt( Index )->GetDeliveryMain();
	}

	return _T( "" );
}

// Inscrit le nom du livrable principal de la livraison.
void ZBProcDeliveries::SetDeliveryMain( size_t Index, CString Value )
{
	if ( Index < GetDeliveriesCount() )
	{
		m_Set.GetAt(Index)->SetDeliveryMain( Value );
	}
}

// Permet de savoir si le nom de la livraison spécifié existe dans la liste des livraisons.
bool ZBProcDeliveries::DeliveryNameExist( const CString Name ) const
{
	// Run through the set and build the string
	ZBBPDeliveriesPropertiesIterator i( &m_Set );

	for ( ZBBPDeliveriesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
	{
		if ( pProp->GetDeliveryName() == Name )
		{
			return true;
		}
	}

	return false;
}

// Obtient le prochain nom valide pour une livraison.
CString ZBProcDeliveries::GetNextDeliveryValidName() const
{
	CString str;
	int i = 1;

	do
	{
		str.Format( _T( "Livr %d" ), i++ );
	}
	while ( DeliveryNameExist( str ) == true );

	return str;
}

// Obtient la liste des livrables disponibles.
CString ZBProcDeliveries::GetAvailableDeliverables( const CString AllDeliverables ) const
{
	// First, retreive the allocated deliverables
	CString AllocatedDeliverables = GetAllocatedDeliverables();

	// Now run through all deliverables and check wich one is available
	ZBTokenizer srcToken;	// Initialize the source token with ; as separator
	ZBTokenizer dstToken;	// Initialize the destination token with ; as separator

	CString str = srcToken.GetFirstToken( AllDeliverables );

	// Run through all tokens
	while ( !str.IsEmpty() )
	{
		// If the token is not in the allocated deliverable string
		// add it to the destination token string
		if ( !IsDeliverableInString( AllocatedDeliverables, str ) )
		{
			dstToken.AddToken( str );
		}

		// Get the next token
		str = srcToken.GetNextToken();
	}

	// Return the available deliverables string
	return dstToken.GetString();
}

// Obtient la liste des livrables déjà alloués.
CString ZBProcDeliveries::GetAllocatedDeliverables() const
{
	ZBTokenizer token;	// Initialize the token with ; as separator

	// Run through the set and build the string
	ZBBPDeliveriesPropertiesIterator i( &m_Set );

	for ( ZBBPDeliveriesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
	{
		// Add the deliverables
		token.AddToken( pProp->GetDeliveryDeliverables() );
	}

	// Return the constructed string
	return token.GetString();
}

// Cette fonction permet de savoir si un livrable existe dans la liste des livrables de la livraison souhaitée.
bool ZBProcDeliveries::IsDeliverableInString( const CString Deliverables, const CString Value ) const
{
	ZBTokenizer token;	// Initialize the token with ; as separator

	CString str = token.GetFirstToken( Deliverables );

	// Run through all tokens
	while ( !str.IsEmpty() )
	{
		// If we found the same deliverable,
		// then return true
		if ( str == Value )
		{
			return true;
		}

		// Get the next token
		str = token.GetNextToken();
	}

	return false;
}

// Cette fonction permet de retrouver la propriété contenant le livrable souhaité.
ZBBPDeliveriesProperties* ZBProcDeliveries::LocateDeliveryOfDeliverable( const CString DeliverableName ) const
{
	int Index = LocateDeliveryIndexOfDeliverable( DeliverableName );

	if ( Index == -1 )
	{
		return NULL;
	}

	return GetProperty( Index );
}

// Cette fonction permet de retrouver l'index de la propriété contenant le livrable souhaité.
int ZBProcDeliveries::LocateDeliveryIndexOfDeliverable( const CString DeliverableName ) const
{
	// Run through the set of deliverables and check if found
	ZBBPDeliveriesPropertiesIterator i( &m_Set );
	int Index = 0;

	for ( ZBBPDeliveriesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext(), ++Index )
	{
		if ( IsDeliverableInString( pProp->GetDeliveryDeliverables(), DeliverableName ) )
		{
			return Index;
		}
	}

	return -1;
}

// Cette fonction permet de retrouver la propriété contenant le livrable principal souhaité.
ZBBPDeliveriesProperties* ZBProcDeliveries::LocateDeliveryOfMain( const CString Main ) const
{
	int Index = LocateDeliveryIndexOfMain( Main );

	if ( Index == -1 )
	{
		return NULL;
	}

	return GetProperty( Index );
}

// Cette fonction permet de retrouver l'index de la propriété contenant le livrable principal souhaité.
int ZBProcDeliveries::LocateDeliveryIndexOfMain( const CString Main ) const
{
	// Run through the set of deliverables and check if found
	ZBBPDeliveriesPropertiesIterator i( &m_Set );
	int Index = 0;

	for ( ZBBPDeliveriesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext(), ++Index )
	{
		if ( !pProp->GetDeliveryMain().IsEmpty() && pProp->GetDeliveryMain() == Main )
		{
			return Index;
		}
	}

	return -1;
}

// Cette fonction permet de remplaçer un livrable par un autre.
bool ZBProcDeliveries::ReplaceDeliverable( const CString OldDeliverableName, const CString NewDeliverableName )
{
	int Index		= LocateDeliveryIndexOfDeliverable( OldDeliverableName );
	bool RetValue	= false;

	if ( Index != -1 )
	{
		// First, remove the old deliverable
		if ( !RemoveDeliveryDeliverable( Index, OldDeliverableName ) )
		{
			return false;
		}
	
		// Then add the new name and return the status
		RetValue = AddDeliveryDeliverable( Index, NewDeliverableName );
	}

	ZBBPDeliveriesProperties* pDelivery = LocateDeliveryOfMain( OldDeliverableName );

	if ( pDelivery )
	{
		// Sets the new deliverable name
		pDelivery->SetDeliveryMain( NewDeliverableName );
		RetValue = true;
	}

	// Not found or not done
	return RetValue;
}

// Cette fonction permet de supprimer l'occurence d'un livrable dans toutes les livraisons.
bool ZBProcDeliveries::DeleteDeliverableFromAllDeliveries( const CString DeliverableName )
{
	int Index		= LocateDeliveryIndexOfDeliverable( DeliverableName );
	bool RetValue	= false;

	if ( Index != -1 )
	{
		// First, remove the old deliverable
		if ( !RemoveDeliveryDeliverable( Index, DeliverableName ) )
		{
			return false;
		}
	}

	ZBBPDeliveriesProperties* pDelivery = LocateDeliveryOfMain( DeliverableName );

	if ( pDelivery )
	{
		// Sets the new deliverable name
		pDelivery->SetDeliveryMain( _T( "" ) );
		RetValue = true;
	}

	// Not found or not done
	return RetValue;
}

// Fonction de sérialisation de l'objet.
void ZBProcDeliveries::Serialize( CArchive& ar )
{
	// Only if the object is serialize from and to a document
	if ( ar.m_pDocument )
	{
		if ( ar.IsStoring() )
		{
			TRACE( _T( "ZBProcDeliveries::Serialize : Start Save\n" ) );
	
			// Serialize the size of the set
			ar << (int)m_Set.GetSize();

			ZBBPDeliveriesPropertiesIterator i( &m_Set );

			for ( ZBBPDeliveriesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
			{
				ar << pProp;
			}

			TRACE( _T( "ZBProcDeliveries::Serialize : End Save\n" ) );
		}
		else
		{
			TRACE( _T( "ZBProcDeliveries::Serialize : Start Read\n" ) );

			RemoveAllDeliveries();

			// Read the size of the set
			int Count;
			ar >> Count;

			ZBBPDeliveriesProperties* pProp;

			for ( int i = 0; i < (int)Count; ++i )
			{
				ar >> pProp;
				AddDelivery( pProp );
			}
		
			TRACE( _T( "ZBProcDeliveries::Serialize : End Read\n" ) );
		}
	}
}
