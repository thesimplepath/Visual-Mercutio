// **************************************************************************************************************
// *										Classe ZBBPRulesProp												*
// **************************************************************************************************************
// * JMR-MODIF - Le 20 novembre 2006 - Ajout de la classe ZBBPRulesProp.										*
// **************************************************************************************************************
// * Cette classe représente une propriété de type règle.														*
// **************************************************************************************************************

#include "stdafx.h"
#include "ZBBPRulesProp.h"

#include "zBaseLib\ZBTokenizer.h"

#include "zBaseLib\BaseDoc.h"

// Resources
#include "zModelBPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace sfl;

IMPLEMENT_SERIAL( ZBBPRulesProperties, CObject, def_Version )

// Constructeur par défaut de la classe ZBBPRulesProperties.
ZBBPRulesProperties::ZBBPRulesProperties()
{
	m_RuleName			= _T( "" );
	m_RuleDescription	= _T( "" );
	m_RuleGUID			= _T( "" );
}

// Constructeur par copie de la classe ZBBPRulesProperties.
ZBBPRulesProperties::ZBBPRulesProperties( const ZBBPRulesProperties& propProcess )
{
	m_RuleName			= propProcess.GetRuleName();
	m_RuleDescription	= propProcess.GetRuleDescription();
	m_RuleGUID			= propProcess.GetRuleGUID();
}

// Destructeur de la classe ZBBPRulesProperties.
ZBBPRulesProperties::~ZBBPRulesProperties()
{
	m_RuleName.Empty();
	m_RuleDescription.Empty();
	m_RuleGUID.Empty();
}

// Surcharge de l'opérateur = pour la classe ZBBPRulesProperties.
ZBBPRulesProperties& ZBBPRulesProperties::operator=( const ZBBPRulesProperties& propProcess )
{
	SetRuleName			( propProcess.GetRuleName() );
	SetRuleDescription	( propProcess.GetRuleDescription() );
	SetRuleGUID			( propProcess.GetRuleGUID() );

	return *this;
}

// Surcharge de l'opérateur == pour la classe ZBBPRulesProperties.
BOOL ZBBPRulesProperties::operator==( const ZBBPRulesProperties propProcess ) const
{
	return ( GetRuleName()			== propProcess.GetRuleName()			&&
			 GetRuleDescription()	== propProcess.GetRuleDescription()		&&
			 GetRuleGUID()			== propProcess.GetRuleGUID() );
}

// Cette fonction permet de fusionner deux objets ZBBPRulesProperties, en spécifiant les données partagées.
void ZBBPRulesProperties::Merge( ZBBPRulesProperties* pProperty, DWORD dwChangeFlags )
{
	if ( pProperty )
	{
		if ( dwChangeFlags & Z_CHANGE_RULE_NAME )
		{
			m_RuleName = pProperty->GetRuleName();
		}

		if ( dwChangeFlags & Z_CHANGE_RULE_DESCRIPTION )
		{
			m_RuleDescription = pProperty->GetRuleDescription();
		}

		if ( dwChangeFlags & Z_CHANGE_RULE_GUID )
		{
			m_RuleGUID = pProperty->GetRuleGUID();
		}
	}
}

// Cette fonction permet de déterminer si deux objets ZBBPRulesProperties sont égaux.
BOOL ZBBPRulesProperties::IsEqual( ZBBPRulesProperties* pProp )
{
	if ( pProp )
	{
		return ( *this == *pProp );
	}

	return FALSE;
}

// Inscrit le nom de la règle.
void ZBBPRulesProperties::SetRuleName( LPCTSTR lpszValue )
{
	if ( lpszValue != NULL )
	{
		m_RuleName = lpszValue;
	}
	else
	{
		TRACE0( _T( "Z -> Invalid Rule name pointer!\n" ) );
		ASSERT( FALSE );
	}
}

// Fonction interne pour l'inscription du nom de la règle.
void ZBBPRulesProperties::SetRuleNameEx( const CString value )
{
	SetRuleName( value );
}

// Inscrit la description de la règle.
void ZBBPRulesProperties::SetRuleDescription( LPCTSTR lpszValue )
{
	if ( lpszValue != NULL )
	{
		m_RuleDescription = lpszValue;
	}
	else
	{
		TRACE0( _T( "Z -> Invalid Rule Description list pointer!\n" ) );
		ASSERT( FALSE );
	}
}

// Fonction interne pour l'inscription de la description de la règle.
void ZBBPRulesProperties::SetRuleDescriptionEx( const CString value )
{
	SetRuleDescription( value );
}

// Inscrit la description de la règle.
void ZBBPRulesProperties::SetRuleGUID( LPCTSTR lpszValue )
{
	if ( lpszValue != NULL )
	{
		m_RuleGUID = lpszValue;
	}
	else
	{
		TRACE0( _T( "Z -> Invalid Rule GUID list pointer!\n" ) );
		ASSERT( FALSE );
	}
}

// Fonction interne pour l'inscription de la description de la règle.
void ZBBPRulesProperties::SetRuleGUIDEx( const CString value )
{
	SetRuleGUID( value );
}

// Obtient une valeur de type CString, en spécifiant son ID.
BOOL ZBBPRulesProperties::GetValue( const int nPropId, CString& strValue ) const
{
	switch ( nPropId )
	{
		case Z_RULE_NAME:
		{
			strValue = m_RuleName;
			break;
		}

		case Z_RULE_DESCRIPTION:
		{
			strValue = m_RuleDescription;
			break;
		}

		case Z_RULE_IDENTIFIER:
		{
			strValue = m_RuleGUID;
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
BOOL ZBBPRulesProperties::GetValue( const int nPropId, int& nValue ) const
{
	switch ( nPropId )
	{
		case Z_RULE_NAME:
		case Z_RULE_DESCRIPTION:
		case Z_RULE_IDENTIFIER:
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
BOOL ZBBPRulesProperties::GetValue( const int nPropId, UINT& nValue ) const
{
	switch ( nPropId )
	{
		case Z_RULE_NAME:
		case Z_RULE_DESCRIPTION:
		case Z_RULE_IDENTIFIER:
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
BOOL ZBBPRulesProperties::GetValue( const int nPropId, DWORD& dwValue ) const
{
	switch ( nPropId )
	{
		case Z_RULE_NAME:
		case Z_RULE_DESCRIPTION:
		case Z_RULE_IDENTIFIER:
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
BOOL ZBBPRulesProperties::GetValue( const int nPropId, float& fValue ) const
{
	switch ( nPropId )
	{
		case Z_RULE_NAME:
		case Z_RULE_DESCRIPTION:
		case Z_RULE_IDENTIFIER:
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

// Inscrit une valeur de type LPCTSTR, en spécifiant son ID.
BOOL ZBBPRulesProperties::SetValue( const int nPropId, LPCTSTR lpszValue )
{
	switch ( nPropId )
	{
		case Z_RULE_NAME:
		{
			m_RuleName = lpszValue;
			break;
		}

		case Z_RULE_DESCRIPTION:
		{
			m_RuleDescription = lpszValue;
			break;
		}

		case Z_RULE_IDENTIFIER:
		{
			m_RuleGUID = lpszValue;
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
BOOL ZBBPRulesProperties::SetValue( const int nPropId, const int nValue )
{
	switch ( nPropId )
	{
		case Z_RULE_NAME:
		case Z_RULE_DESCRIPTION:
		case Z_RULE_IDENTIFIER:
		{
			ASSERT( FALSE );
			return FALSE;
			break;
		}

		default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

// Inscrit une valeur de type const UINT, en spécifiant son ID.
BOOL ZBBPRulesProperties::SetValue( const int nPropId, const UINT nValue )
{
	switch ( nPropId )
	{
		case Z_RULE_NAME:
		case Z_RULE_DESCRIPTION:
		case Z_RULE_IDENTIFIER:
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
BOOL ZBBPRulesProperties::SetValue( const int nPropId, const DWORD dwValue )
{
	switch ( nPropId )
	{
		case Z_RULE_NAME:
		case Z_RULE_DESCRIPTION:
		case Z_RULE_IDENTIFIER:
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
BOOL ZBBPRulesProperties::SetValue( const int nPropId, const float fValue )
{
	switch ( nPropId )
	{
		case Z_RULE_NAME:
		case Z_RULE_DESCRIPTION:
		case Z_RULE_IDENTIFIER:
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

/////////////////////////////////////////////////////////////////////////////
// ZBBPRulesProperties diagnostics

#ifdef _DEBUG
void ZBBPRulesProperties::AssertValid() const
{
	CObject::AssertValid();
}

void ZBBPRulesProperties::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );

	dc << _T( "Name = " )			<< m_RuleName			<< _T( "\n" );
	dc << _T( "Description = " )	<< m_RuleDescription	<< _T( "\n" );
	dc << _T( "GUID = " )			<< m_RuleGUID			<< _T( "\n" );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBBPRulesProperties serialization

void ZBBPRulesProperties::Serialize( CArchive& ar )
{
	if ( ar.IsStoring() )
	{
		TRACE( _T( "ZBBPRulesProperties::Serialize : Start Save\n" ) );

		ar << m_RuleName;
		ar << m_RuleDescription;
		ar << m_RuleGUID;

		TRACE( _T( "ZBBPRulesProperties::Serialize : End Save\n" ) );
	}
	else
	{
		TRACE( _T( "ZBBPRulesProperties::Serialize : Start Read\n" ) );

		ar >> m_RuleName;
		ar >> m_RuleDescription;
		ar >> m_RuleGUID;

		TRACE( _T( "ZBBPRulesProperties::Serialize : End Read\n" ) );
	}
}
