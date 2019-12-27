// ZBUserGroupObserverMsg.cpp: implementation of the ZBUserGroupObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBUserGroupObserverMsg.h"

#include "PSS_UserEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_DYNAMIC(ZBUserGroupObserverMsg, PSS_ObserverMsg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBUserGroupObserverMsg::ZBUserGroupObserverMsg(UINT            MessageID    /*= 0*/,
                                               PSS_UserEntity* pEntity        /*= NULL*/,
                                               const CString   RootName    /*= _T( "" )*/) :
    PSS_ObserverMsg(),
    m_MessageID(MessageID),
    m_pEntity(pEntity),
    m_RootName(RootName)
{}

ZBUserGroupObserverMsg::~ZBUserGroupObserverMsg()
{}
