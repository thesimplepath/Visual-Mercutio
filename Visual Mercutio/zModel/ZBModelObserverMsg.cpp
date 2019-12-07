// ZBModelObserverMsg.cpp: implementation of the ZBModelObserverMsg class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBModelObserverMsg.h"
#include "PSS_ProcessGraphModelDoc.h"
#include "ZDProcessGraphPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

IMPLEMENT_DYNAMIC(ZBModelObserverMsg, PSS_ObserverMsg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBModelObserverMsg::ZBModelObserverMsg(MessageActionType        ActionType    /*= NoAction*/,
                                       PSS_ProcessGraphModelDoc*    pDoc        /*= NULL*/,
                                       PSS_ProcessGraphModelMdl*    pModel        /*= NULL*/,
                                       CODComponent*            pElement    /*= NULL*/) :
    PSS_ObserverMsg(),
    m_ActionType(ActionType),
    m_pDoc(pDoc),
    m_pModel(pModel),
    m_pElement(pElement),
    m_pPage(NULL),
    m_pElementSet(NULL)
{}

ZBModelObserverMsg::ZBModelObserverMsg(MessageActionType        ActionType,
                                       PSS_ProcessGraphModelDoc*    pDoc,
                                       PSS_ProcessGraphModelMdl*    pModel,
                                       CODComponentSet*        pElementSet) :
    PSS_ObserverMsg(),
    m_ActionType(ActionType),
    m_pDoc(pDoc),
    m_pModel(pModel),
    m_pElementSet(pElementSet),
    m_pPage(NULL),
    m_pElement(NULL)
{}

ZBModelObserverMsg::ZBModelObserverMsg(MessageActionType        ActionType,
                                       PSS_ProcessGraphModelDoc*    pDoc,
                                       PSS_ProcessGraphModelMdl*    pModel,
                                       ZDProcessGraphPage*        pPage) :
    PSS_ObserverMsg(),
    m_ActionType(ActionType),
    m_pDoc(pDoc),
    m_pModel(pModel),
    m_pPage(pPage),
    m_pElementSet(NULL),
    m_pElement(NULL)
{}

ZBModelObserverMsg::~ZBModelObserverMsg()
{}
