// ZUProcessNavigation.cpp: implementation of the ZUProcessNavigation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUProcessNavigation.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "zModelBP\ZBBPDoorSymbol.h"
#include "zModelBP\ZBBPPageSymbol.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 28 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUProcessNavigation::ZUProcessNavigation( ZDProcessGraphModelMdl* pModel /*= NULL*/, void* pClass /*= NULL*/ )
	: m_pModel	( pModel ),
	  m_pClass	( pClass )
{
}

ZUProcessNavigation::~ZUProcessNavigation()
{
}

bool ZUProcessNavigation::Navigate( ZDProcessGraphModelMdl* pModel, void* pClass )
{
	m_pModel = pModel;
	m_pClass = pClass;
	return ZUProcessNavigation::Navigate();
}

bool ZUProcessNavigation::Navigate( ZDProcessGraphModelMdl* pModel )
{
	m_pModel = pModel;
	return ZUProcessNavigation::Navigate();
}

bool ZUProcessNavigation::Navigate()
{
	if ( m_pModel )
	{
		// Initialize counters
		m_ErrorCounter		= 0;
		m_WarningCounter	= 0;

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

bool ZUProcessNavigation::Visit( CODComponent& Symbol )
{
	CODComponent* pSymbol = &Symbol;

	if ( ISA ( pSymbol, ZBBPProcedureSymbol ) )
	{
		return OnProcedureSymbol( dynamic_cast<ZBBPProcedureSymbol*>( &Symbol ) );
	}
	else if ( ISA ( pSymbol, ZBDeliverableLinkSymbol ) )
	{
		return OnDeliverableLinkSymbol( dynamic_cast<ZBDeliverableLinkSymbol*>( &Symbol ) );
	}
	else if ( ISA ( pSymbol, ZBBPDoorSymbol ) )
	{
		return OnDoorSymbol( dynamic_cast<ZBBPDoorSymbol*>( &Symbol ) );
	}
	else if ( ISA ( pSymbol, ZBBPPageSymbol ) )
	{
		return OnPageSymbol( dynamic_cast<ZBBPPageSymbol*>( &Symbol ) );
	}
	else if ( ISA ( pSymbol, ZBBPProcessSymbol ) )
	{
		return OnProcessSymbol( dynamic_cast<ZBBPProcessSymbol*>( &Symbol ) );
	}
	else if ( ISA ( pSymbol, ZBBPStartSymbol ) )
	{
		return OnStartSymbol( dynamic_cast<ZBBPStartSymbol*>( &Symbol ) );
	}
	else if ( ISA ( pSymbol, ZBBPStopSymbol ) )
	{
		return OnStopSymbol( dynamic_cast<ZBBPStopSymbol*>( &Symbol ) );
	}
	else if ( ISA ( pSymbol, ZBSymbol ) )
	{
		return OnSymbol( dynamic_cast<ZBSymbol*>( &Symbol ) );
	}
	else if ( ISA ( pSymbol, ZBLinkSymbol ) )
	{
		return OnLink( dynamic_cast<ZBLinkSymbol*>( &Symbol ) );
	}

	// Not a right symbol or not necessary to visit
	return false;
}
