// ZBSymbolObserverMsg.cpp: implementation of the ZBSymbolObserverMsg class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBSymbolObserverMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

IMPLEMENT_DYNAMIC( ZBSymbolObserverMsg, ZIObserverMsg )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBSymbolObserverMsg::ZBSymbolObserverMsg( MessageActionType    ActionType    /*= NoAction*/,
                                          CODComponent*        pElement    /*= NULL*/)
    : m_pElement    ( pElement ),
      m_ActionType    ( ActionType ),
      m_SymbolRef    ( -1 )
{
}

ZBSymbolObserverMsg::ZBSymbolObserverMsg( int SymbolRef, MessageActionType ActionType /*= NoAction*/ )
    : m_pElement    ( NULL ),
      m_ActionType    ( ActionType ),
      m_SymbolRef    ( SymbolRef )
{
}

ZBSymbolObserverMsg::~ZBSymbolObserverMsg()
{
}
