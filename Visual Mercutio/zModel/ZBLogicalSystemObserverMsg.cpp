// ZBLogicalSystemObserverMsg.cpp: implementation of the ZBLogicalSystemObserverMsg class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBLogicalSystemObserverMsg.h"

#include "ZBSystemEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_DYNAMIC( ZBLogicalSystemObserverMsg, ZIObserverMsg )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBLogicalSystemObserverMsg::ZBLogicalSystemObserverMsg( UINT			MessageID	/*= 0*/,
													    ZBSystemEntity*	pEntity		/*= NULL*/,
														const CString	RootName	/*= _T( "" )*/  )
	: m_MessageID	( MessageID ),
	  m_pEntity		( pEntity ),
	  m_RootName	( RootName )
{
}

ZBLogicalSystemObserverMsg::~ZBLogicalSystemObserverMsg()
{
}
