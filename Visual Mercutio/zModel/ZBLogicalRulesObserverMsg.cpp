// ******************************************************************************************************************
// *									  Classe ZBLogicalRulesObserverMsg											*
// ******************************************************************************************************************
// * JMR-MODIF - Le 14 novembre 2006 - Ajout de la classe ZBLogicalRulesObserverMsg.								*
// ******************************************************************************************************************
// * Cette classe est un observateur d'événements pour les classes de gestion des règles.							*
// ******************************************************************************************************************

#include "stdafx.h"
#include "ZBLogicalRulesObserverMsg.h"

#include "ZBRulesEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( ZBLogicalRulesObserverMsg, ZIObserverMsg )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBLogicalRulesObserverMsg::ZBLogicalRulesObserverMsg( UINT				MessageID	/*= 0*/,
													  ZBRulesEntity*	pEntity		/*= NULL*/,
													  const CString		RootName	/*= _T( "" )*/ )
	: m_MessageID	( MessageID ),
	  m_pEntity		( pEntity ),
	  m_RootName	( RootName )
{
}

ZBLogicalRulesObserverMsg::~ZBLogicalRulesObserverMsg()
{
}
