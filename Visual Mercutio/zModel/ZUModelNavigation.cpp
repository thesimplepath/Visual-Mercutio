// ZUModelNavigation.cpp: implementation of the ZUModelNavigation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUModelNavigation.h"

#include "ProcGraphModelMdl.h"
#include "ZBSymbol.h"
#include "ZBLinkSymbol.h"

#include "zModelRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 2 mars 2006 - Ajout de la décoration unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUModelNavigation::ZUModelNavigation( ZDProcessGraphModelMdl* pModel /*= NULL*/, void* pClass /*= NULL*/ )
	: m_pModel	( pModel ),
	  m_pClass	( pClass )
{
}

ZUModelNavigation::~ZUModelNavigation()
{
}

bool ZUModelNavigation::Navigate( ZDProcessGraphModelMdl* pModel, void* pClass )
{
	m_pModel = pModel;
	m_pClass = pClass;

	return ZUModelNavigation::Navigate();
}

bool ZUModelNavigation::Navigate( ZDProcessGraphModelMdl* pModel )
{
	m_pModel = pModel;
	return ZUModelNavigation::Navigate();
}

bool ZUModelNavigation::Navigate()
{
	if ( m_pModel )
	{
		// Call the OnStart method
		if ( !OnStart() )
		{
			return false;
		}

		// Process the model
		m_pModel->AcceptVisitor( *this );

		// Call the OnFinish method and returns its retval.
		return OnFinish();
	}

	return false;
}

bool ZUModelNavigation::Visit( CODComponent& Symbol )
{
	CODComponent* pSymbol = &Symbol;

	if ( ISA( pSymbol, ZBSymbol ) )
	{
		return OnSymbol( dynamic_cast<ZBSymbol*>( &Symbol ) );
	}
	else if ( ISA( pSymbol, ZBLinkSymbol ) )
	{
		return OnLink( dynamic_cast<ZBLinkSymbol*>( &Symbol ) );
	}

	// Not a right symbol or not necessary to visit
	return false;
}
