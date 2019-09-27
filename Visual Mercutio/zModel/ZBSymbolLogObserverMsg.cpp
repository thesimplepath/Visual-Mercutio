// ZBSymbolLogObserverMsg.cpp: implementation of the ZBSymbolLogObserverMsg class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBSymbolLogObserverMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

IMPLEMENT_DYNAMIC(ZBSymbolLogObserverMsg, PSS_ObserverMsg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBSymbolLogObserverMsg::ZBSymbolLogObserverMsg() :
    PSS_ObserverMsg()
{}

ZBSymbolLogObserverMsg::ZBSymbolLogObserverMsg(ZBGenericSymbolErrorLine ErrorLine) :
    PSS_ObserverMsg(),
    m_ErrorLine(ErrorLine)
{}

ZBSymbolLogObserverMsg::~ZBSymbolLogObserverMsg()
{}
