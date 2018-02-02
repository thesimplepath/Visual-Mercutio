/////////////////////////////////////////////////////////////////////////////
//@doc ZUCheckSesterceConsistency
//@module ZUCheckSesterceConsistency.cpp | Implementation of the <c ZUCheckSesterceConsistency> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 06/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUCheckSesterceConsistency.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "zModelBP\ZBBPDoorSymbol.h"
#include "zModelBP\ZBBPPageSymbol.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zModel\ZUODSymbolManipulator.h"

// Include files for log
#include "zBaseLib\ZILog.h"
#include "zModel\ZBGenericSymbolErrorLine.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 17 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUCheckSesterceConsistency::ZUCheckSesterceConsistency( ZDProcessGraphModelMdl*	pModel	/*= NULL*/,
														ZILog*					pLog	/*= NULL*/ )
	: m_pModel	( pModel ),
	  m_pLog	( pLog )
{
}

ZUCheckSesterceConsistency::~ZUCheckSesterceConsistency()
{
}

bool ZUCheckSesterceConsistency::CheckModel()
{
	// Initialize internal counters
	m_ErrorCounter		= 0;
	m_WarningCounter	= 0;

	if ( m_pModel )
	{
		m_pModel->AcceptVisitor( *this );
		return true;
	}

	return false;
}

bool ZUCheckSesterceConsistency::Visit( CODComponent& Symbol )
{
	CODComponent* pSymbol = &Symbol;

	if ( ISA( pSymbol, ZBBPProcedureSymbol ) )
	{
		return CheckProcedureSymbol( dynamic_cast<ZBBPProcedureSymbol*>( &Symbol ) );
	}
	else if ( ISA( pSymbol, ZBDeliverableLinkSymbol ) )
	{
		return CheckDeliverableLinkSymbol( dynamic_cast<ZBDeliverableLinkSymbol*>( &Symbol ) );
	}
	else if ( ISA( pSymbol, ZBBPDoorSymbol ) )
	{
		return CheckDoorSymbol( dynamic_cast<ZBBPDoorSymbol*>( &Symbol ) );
	}
	else if ( ISA( pSymbol, ZBBPPageSymbol ) )
	{
		return CheckPageSymbol( dynamic_cast<ZBBPPageSymbol*>( &Symbol ) );
	}
	else if ( ISA( pSymbol, ZBBPProcessSymbol ) )
	{
		return CheckProcessSymbol( dynamic_cast<ZBBPProcessSymbol*>( &Symbol ) );
	}
	else if ( ISA( pSymbol, ZBBPStartSymbol ) )
	{
		return CheckStartSymbol( dynamic_cast<ZBBPStartSymbol*>( &Symbol ) );
	}
	else if ( ISA( pSymbol, ZBBPStopSymbol ) )
	{
		return CheckStopSymbol( dynamic_cast<ZBBPStopSymbol*>( &Symbol ) );
	}
	else if ( ISA( pSymbol, ZBSymbol ) )
	{
		return CheckSymbol( dynamic_cast<ZBSymbol*>( &Symbol ) );
	}
	else if ( ISA( pSymbol, ZBLinkSymbol ) )
	{
		return CheckLink( dynamic_cast<ZBLinkSymbol*>( &Symbol ) );
	}

	// Not a right symbol or not necessary to visit
	return false;
}

bool ZUCheckSesterceConsistency::CheckDoorSymbol( ZBBPDoorSymbol* pSymbol )
{
	ASSERT( pSymbol );
	return true;
}

bool ZUCheckSesterceConsistency::CheckPageSymbol( ZBBPPageSymbol* pSymbol )
{
	ASSERT( pSymbol );
	return true;
}

bool ZUCheckSesterceConsistency::CheckProcedureSymbol( ZBBPProcedureSymbol* pSymbol )
{
	ASSERT( pSymbol );

	// Test if it is a local symbol
	if ( !pSymbol->IsLocal() )
	{
		// Locate the local symbol
		CODComponent* pComp = pSymbol->GetLocalSymbol();

		if ( pComp && ISA( pComp, ZBBPProcedureSymbol ) )
		{
			pSymbol = dynamic_cast<ZBBPProcedureSymbol*>( pComp );
		}
	}

	// Check if unit defined for procedure
	if ( pSymbol->GetUnitName().IsEmpty() )
	{
		if ( m_pLog )
		{
			ZBGenericSymbolErrorLine e( IDS_AL_PROCEDURE_INC_10,
										pSymbol->GetSymbolName(),
										pSymbol->GetAbsolutePath() );

			m_pLog->AddLine( e );
		}

		// Increment warning counter
		++m_WarningCounter;
	}
	else
	{
		if ( pSymbol->GetUnitCost() == 0 )
		{
			if ( m_pLog )
			{
				ZBGenericSymbolErrorLine e( IDS_AL_PROCEDURE_INC_11,
											pSymbol->GetSymbolName(),
											pSymbol->GetAbsolutePath() );

				m_pLog->AddLine( e );
			}

			// Increment warning counter
			++m_WarningCounter;
		}
	}

	// Check the multiplier
	if ( pSymbol->GetMultiplier() == 0 )
	{
		if ( m_pLog )
		{
			ZBGenericSymbolErrorLine e( IDS_AL_PROCEDURE_INC_12,
										pSymbol->GetSymbolName(),
										pSymbol->GetAbsolutePath() );

			m_pLog->AddLine( e );
		}

		// Increment warning counter
		++m_WarningCounter;
	}

	/* Not in beta 2, the maximum percentage is not used anymore
	// Now check the sum of the combination percentage
	if (pSymbol->CalculateSumOfCombinations() != 1)
	{
		if ( m_pLog )
		{
			ZBGenericSymbolErrorLine e( IDS_AL_PROCEDURE_INC_13,
										pSymbol->GetSymbolName(),
										pSymbol->GetAbsolutePath() );

			m_pLog->AddLine( e );
		}

		// Increment warning counter
		++m_WarningCounter;
	}
	*/

	// Now check if a master has been defined for each combination
	int Count = pSymbol->GetCombinationCount();

	for ( int i = 0; i < Count; ++i )
	{
		if ( pSymbol->GetCombinationMaster( i ).IsEmpty() )
		{
			if ( m_pLog )
			{
				CString s;
				s.Format( IDS_AL_PROCEDURE_INC_14, pSymbol->GetCombinationName( i ) );
				ZBGenericSymbolErrorLine e( s, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 1 );
				m_pLog->AddLine( e );
			}

			// Increment error counter
			++m_ErrorCounter;
		}
	}

	return true;
}

bool ZUCheckSesterceConsistency::CheckProcessSymbol( ZBBPProcessSymbol* pSymbol )
{
	ASSERT( pSymbol );

	// ************************************************************************************************************
	// JMR-MODIF - Le 17 mars 2006 - Ajout du code de contrôle des livraisons.

	int Count = pSymbol->GetDeliveriesCount();

	for ( int i = 0; i < Count; ++i )
	{
		if ( pSymbol->GetDeliveryMain( i ).IsEmpty() )
		{
			if ( m_pLog )
			{
				CString s;
				s.Format( IDS_AL_PROCESS_INC_1, pSymbol->GetDeliveryName( i ) );
				ZBGenericSymbolErrorLine e( s, pSymbol->GetSymbolName(), pSymbol->GetAbsolutePath(), -1, 1 );
				m_pLog->AddLine( e );
			}

			// Increment error counter
			++m_ErrorCounter;
		}
	}
	// ************************************************************************************************************

	return true;
}

bool ZUCheckSesterceConsistency::CheckStartSymbol( ZBBPStartSymbol* pSymbol )
{
	ASSERT( pSymbol );

	// Check if unit defined for procedure
	if ( pSymbol->GetUnitName().IsEmpty() )
	{
		if ( m_pLog )
		{
			ZBGenericSymbolErrorLine e( IDS_AL_START_INC_10,
										pSymbol->GetSymbolName(),
										pSymbol->GetAbsolutePath() );

			m_pLog->AddLine( e );
		}

		// Increment warning counter
		++m_WarningCounter;
	}
	else
	{
		if ( pSymbol->GetUnitCost() == 0 )
		{
			if ( m_pLog )
			{
				ZBGenericSymbolErrorLine e( IDS_AL_START_INC_11,
											pSymbol->GetSymbolName(),
											pSymbol->GetAbsolutePath() );

				m_pLog->AddLine( e );
			}

			// Increment warning counter
			++m_WarningCounter;
		}
	}

	return true;
}

bool ZUCheckSesterceConsistency::CheckStopSymbol( ZBBPStopSymbol* pSymbol )
{
	ASSERT( pSymbol );

	// Check if unit defined for procedure
	if ( pSymbol->GetUnitName().IsEmpty() )
	{
		if ( m_pLog )
		{
			ZBGenericSymbolErrorLine e( IDS_AL_STOP_INC_10,
										pSymbol->GetSymbolName(),
										pSymbol->GetAbsolutePath() );

			m_pLog->AddLine( e );
		}

		// Increment warning counter
		++m_WarningCounter;
	}
	else
	{
		if ( pSymbol->GetUnitCost() == 0 )
		{
			if ( m_pLog )
			{
				ZBGenericSymbolErrorLine e( IDS_AL_STOP_INC_11,
											pSymbol->GetSymbolName(),
											pSymbol->GetAbsolutePath() );

				m_pLog->AddLine( e );
			}

			// Increment warning counter
			++m_WarningCounter;
		}
	}

	return true;
}

bool ZUCheckSesterceConsistency::CheckDeliverableLinkSymbol( ZBDeliverableLinkSymbol* pSymbol )
{
	ASSERT( pSymbol );

	// Test if it is a local symbol
	if ( !pSymbol->IsLocal() )
	{
		// Locate the local symbol
		CODComponent* pComp = pSymbol->GetLocalSymbol();

		if ( pComp && ISA( pComp, ZBDeliverableLinkSymbol ) )
		{
			pSymbol = dynamic_cast<ZBDeliverableLinkSymbol*>( pComp );
		}
	}

	// Check the quantity
	if ( pSymbol->GetQuantityYear() <= 0 )
	{
		if ( m_pLog )
		{
			ZBGenericSymbolErrorLine e( IDS_AL_DELIVERABLE_INC_1,
										pSymbol->GetSymbolName(),
										pSymbol->GetAbsolutePath() );

			m_pLog->AddLine( e );
		}

		// Increment warning counter
		++m_WarningCounter;
	}

	/* Not in beta 2, the maximum percentage is not used anymore
	// Check the percentage in
	if (pSymbol->GetInWorkloadPercent() <= 0)
	{
		if ( m_pLog )
		{
			ZBGenericSymbolErrorLine e( IDS_AL_DELIVERABLE_INC_2,
										pSymbol->GetSymbolName(),
										pSymbol->GetAbsolutePath() );

			m_pLog->AddLine( e );
		}

		// Increment warning counter
		++m_WarningCounter;
	}

	if ( pSymbol->GetInWorkloadPercent() > 1 )
	{
		if ( m_pLog )
		{
			ZBGenericSymbolErrorLine e( IDS_AL_DELIVERABLE_INC_3,
										pSymbol->GetSymbolName(),
										pSymbol->GetAbsolutePath() );

			m_pLog->AddLine( e );
		}

		// Increment warning counter
		++m_WarningCounter;
	}
	*/

	// Check the percentage out
	if ( pSymbol->GetOutWorkloadPercent() <= 0 )
	{
		if ( m_pLog )
		{
			ZBGenericSymbolErrorLine e( IDS_AL_DELIVERABLE_INC_4,
										pSymbol->GetSymbolName(),
										pSymbol->GetAbsolutePath() );

			m_pLog->AddLine( e );
		}

		// Increment warning counter
		++m_WarningCounter;
	}

	if ( pSymbol->GetOutWorkloadPercent() > 1 )
	{
		if ( m_pLog )
		{
			ZBGenericSymbolErrorLine e( IDS_AL_DELIVERABLE_INC_5,
										pSymbol->GetSymbolName(),
										pSymbol->GetAbsolutePath() );

			m_pLog->AddLine( e );
		}

		// Increment warning counter
		++m_WarningCounter;
	}

	return true;
}

bool ZUCheckSesterceConsistency::CheckSymbol( ZBSymbol* pSymbol )
{
	ASSERT( pSymbol );
	return true;
}

bool ZUCheckSesterceConsistency::CheckLink( ZBLinkSymbol* pLink )
{
	ASSERT( pLink );
	return true;
}
