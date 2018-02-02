// ZUSynthesisNavigation.cpp: implementation of the ZUSynthesisNavigation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUSynthesisNavigation.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ZDProcessGraphPage.h"

#include "zModelBP\ZBBPDoorSymbol.h"
#include "zModelBP\ZBBPPageSymbol.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zReport\ZBOStreamGrid.h"

#include "zModelBP\zModelBPRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 7 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUSynthesisNavigation::ZUSynthesisNavigation( ZDProcessGraphModelMdl*	pModel		/*= NULL*/,
											  void*						pClass		/*= NULL*/,
											  ZDProcessGraphModelMdl*	pRootModel	/*= NULL*/,
											  const CString				domainName	/*= ""*/,
											  const CString				unitName	/*= ""*/ )
	: ZUProcessNavigation	( pModel, pClass ),
	  m_pRootModel			( pRootModel ),
	  m_DomainName			( domainName ),
	  m_UnitName			( unitName )
{
}

ZUSynthesisNavigation::~ZUSynthesisNavigation()
{
}

// Cette fonction est appelée lorsque la navigation démarre.
bool ZUSynthesisNavigation::OnStart()
{
	// Start by casting the stream class
	m_postream = static_cast<ZBOStreamGrid*>( m_pClass );
	
	m_BlueStyle.SetTextColor( defCOLOR_BLACK )
							 .SetInterior( RGB( 0, 128, 255 ) );

	return ( m_postream ) ? true : false;
}

// Cette fonction est appelée lorsque la navigation se termine.
bool ZUSynthesisNavigation::OnFinish()
{
	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPProcedureSymbol dans le modèle.
bool ZUSynthesisNavigation::OnProcedureSymbol( ZBBPProcedureSymbol* pSymbol )
{
	int top;
	int left;

	// Check the number of row
	ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
	m_postream->GetCurSel( left, top );

	// If not enough, add 30 rows
	if ( ( top + 30 ) > (int)RowCount )
	{
		m_postream->GetGridCore()->SetRowCount( RowCount + 30 );
	}

	CGXStyle WrapStyle;
	WrapStyle.SetWrapText( TRUE );

	// Only for the specific unit
	// Check if for the same unit
	bool Error;

	CString UnitName = pSymbol->RetreiveUnitName( pSymbol->GetUnitGUID(), Error );

	if ( m_UnitName == UnitName )
	{
		// Add the symbol line
		*m_postream << m_DomainName;
		*m_postream << m_BlueStyle;
		*m_postream << _T( "\t" );

		*m_postream << m_CurrentProcessName;
		*m_postream << m_BlueStyle;
		*m_postream << WrapStyle;
		*m_postream << _T( "\t" );

		*m_postream << pSymbol->GetSymbolName();
		*m_postream << WrapStyle;
		*m_postream << _T( "\n" );
	}

	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBBPProcessSymbol dans le modèle.
bool ZUSynthesisNavigation::OnProcessSymbol( ZBBPProcessSymbol* pSymbol )
{
	m_CurrentProcessName = pSymbol->GetSymbolName();

	ZDProcessGraphModelMdl* pOwnerModel = (ZDProcessGraphModelMdl*)pSymbol->GetOwnerModel();

	if ( pOwnerModel )
	{
		ZDProcessGraphPage* pPage = m_pRootModel->FindModelPage( pOwnerModel, true );

		if ( pPage )
		{
			m_DomainName = pPage->GetPageName();
		}
		else
		{
			m_DomainName.LoadString( IDS_SYNTHESYS_NOT_FOUND );
		}
	}

	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBSymbol dans le modèle.
bool ZUSynthesisNavigation::OnSymbol( ZBSymbol* pSymbol )
{
	return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type ZBLinkSymbol dans le modèle.
bool ZUSynthesisNavigation::OnLink( ZBLinkSymbol* pLink )
{
	return true;
}
