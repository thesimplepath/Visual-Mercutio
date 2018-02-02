// **************************************************************************************************************
// *								  Classe ZUBuildGenericSymbolNewName										*
// **************************************************************************************************************
// * JMR-MODIF - Le 4 avril 2006 - Création de la classe ZUBuildGenericSymbolNewName.							*
// **************************************************************************************************************
// * Cette classe permet la création d'un nom valide et unique pour les symboles génériques.					*
// **************************************************************************************************************

#include "stdafx.h"
#include "ZUBuildGenericSymbolNewName.h"

#include "ProcGraphModelMdl.h"

#include "ZBSymbol.h"
#include "ZBLinkSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUBuildGenericSymbolNewName::ZUBuildGenericSymbolNewName( const CString BaseName /*= ""*/ )
	: m_BaseName( BaseName )
{
}

ZUBuildGenericSymbolNewName::~ZUBuildGenericSymbolNewName()
{
}

CString ZUBuildGenericSymbolNewName::GetNextAvailableSymbolName( CODModel& Model )
{
	for ( int p = 1; p < 10000000; ++p )
	{
		if ( m_BaseName.IsEmpty() )
		{
			m_GenericSymbolName.Format( _T( "Generic%d" ), p );
		}
		else
		{
			m_GenericSymbolName.Format( _T( "%s%d" ), (const char*)m_BaseName, p );
		}

		m_Found = false;

		// Try the name
		_GetNextAvailableSymbolName( Model );

		// If did found the same symbol name, return it
		if ( m_Found == false )
		{
			return m_GenericSymbolName;
		}
	}

	// If no page available, return empty string
	return _T( "" );
}

void ZUBuildGenericSymbolNewName::_GetNextAvailableSymbolName( CODModel& Model )
{
	CODModel* pModel = &Model;

	if ( ISA( pModel, ZDProcessGraphModelMdl ) )
	{
		dynamic_cast<ZDProcessGraphModelMdl&>( Model ).AcceptVisitor( *this );
	}
}

bool ZUBuildGenericSymbolNewName::Visit( CODComponent& Symbol )
{
	CODComponent* pSymbol = &Symbol;

	if ( ISA( pSymbol, ZBSymbol ) && dynamic_cast<ZBSymbol*>( &Symbol )->GetSymbolName() == m_GenericSymbolName )
	{
		m_Found = true;
	}
	else if ( ISA( pSymbol, ZBLinkSymbol ) &&
			  dynamic_cast<ZBLinkSymbol*>( &Symbol )->GetSymbolName() == m_GenericSymbolName )
	{
		m_Found = true;
	}

	return false;
}
