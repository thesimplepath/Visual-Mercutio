// ZBModelObserverMsg.cpp: implementation of the ZBModelObserverMsg class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBModelObserverMsg.h"
#include "ProcGraphModelDoc.h"
#include "ZDProcessGraphPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

IMPLEMENT_DYNAMIC( ZBModelObserverMsg, ZIObserverMsg )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBModelObserverMsg::ZBModelObserverMsg( MessageActionType		ActionType	/*= NoAction*/,
										ZDProcessGraphModelDoc*	pDoc		/*= NULL*/,
										ZDProcessGraphModelMdl*	pModel		/*= NULL*/,
										CODComponent*			pElement	/*= NULL*/ )
	: m_ActionType	( ActionType ),
	  m_pDoc		( pDoc ),
	  m_pModel		( pModel ),
	  m_pElement	( pElement ),
	  m_pPage		( NULL ),
	  m_pElementSet	( NULL )
{
}

ZBModelObserverMsg::ZBModelObserverMsg( MessageActionType		ActionType,
										ZDProcessGraphModelDoc*	pDoc,
										ZDProcessGraphModelMdl*	pModel,
										CODComponentSet*		pElementSet )
	: m_ActionType	( ActionType ),
	  m_pDoc		( pDoc ),
	  m_pModel		( pModel ),
	  m_pElementSet	( pElementSet ),
	  m_pPage		( NULL ),
	  m_pElement	( NULL )
{
}

ZBModelObserverMsg::ZBModelObserverMsg( MessageActionType		ActionType,
										ZDProcessGraphModelDoc*	pDoc,
										ZDProcessGraphModelMdl*	pModel,
										ZDProcessGraphPage*		pPage )
	: m_ActionType	( ActionType ),
	  m_pDoc		( pDoc ),
	  m_pModel		( pModel ),
	  m_pPage		( pPage ),
	  m_pElementSet	( NULL ),
	  m_pElement	( NULL )
{
}

ZBModelObserverMsg::~ZBModelObserverMsg()
{
}
