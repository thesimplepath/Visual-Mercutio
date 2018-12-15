// ZBUserGroupObserverMsg.cpp: implementation of the ZBUserGroupObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBUserGroupObserverMsg.h"

#include "ZBUserEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_DYNAMIC( ZBUserGroupObserverMsg, ZIObserverMsg )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBUserGroupObserverMsg::ZBUserGroupObserverMsg( UINT            MessageID    /*= 0*/,
                                                ZBUserEntity*    pEntity        /*= NULL*/,
                                                const CString    RootName    /*= _T( "" )*/  )
    : m_MessageID    ( MessageID ), 
      m_pEntity        ( pEntity ),
      m_RootName    ( RootName )
{
}

ZBUserGroupObserverMsg::~ZBUserGroupObserverMsg()
{
}
