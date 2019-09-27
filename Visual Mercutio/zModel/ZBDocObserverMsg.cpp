// ZBDocObserverMsg.cpp: implementation of the ZBDocObserverMsg class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBDocObserverMsg.h"
#include "ZBSymbol.h"
#include "ProcGraphModelDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 août 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_DYNAMIC(ZBDocObserverMsg, PSS_ObserverMsg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBDocObserverMsg::ZBDocObserverMsg(MessageActionType        ActionType    /*= NoAction*/,
                                   ZDProcessGraphModelDoc*    pDoc        /*= NULL*/,
                                   ZDProcessGraphModelMdl*    pModel        /*= NULL*/,
                                   CODSymbolComponent*        pElement    /*= NULL*/) :
    PSS_ObserverMsg(),
    m_ActionType(ActionType),
    m_pDoc(pDoc),
    m_pModel(pModel),
    m_pElement(pElement)
{}

ZBDocObserverMsg::~ZBDocObserverMsg()
{}
