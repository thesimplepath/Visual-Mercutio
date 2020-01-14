/****************************************************************************
 * ==> PSS_ModelObserverMsg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a model observer message                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ModelObserverMsg.h"

// processsoft
#include "PSS_ProcessGraphModelDoc.h"
#include "PSS_ProcessGraphPage.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ModelObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_ModelObserverMsg
//---------------------------------------------------------------------------
PSS_ModelObserverMsg::PSS_ModelObserverMsg(IEActionType              actionType,
                                           PSS_ProcessGraphModelDoc* pDoc,
                                           PSS_ProcessGraphModelMdl* pModel,
                                           CODComponent*             pElement) :
    PSS_ObserverMsg(),
    m_pDoc(pDoc),
    m_pModel(pModel),
    m_pPage(NULL),
    m_pElement(pElement),
    m_pElementSet(NULL),
    m_ActionType(actionType)
{}
//---------------------------------------------------------------------------
PSS_ModelObserverMsg::PSS_ModelObserverMsg(IEActionType          actionType,
                                       PSS_ProcessGraphModelDoc* pDoc,
                                       PSS_ProcessGraphModelMdl* pModel,
                                       CODComponentSet*          pElementSet) :
    PSS_ObserverMsg(),
    m_pDoc(pDoc),
    m_pModel(pModel),
    m_pPage(NULL),
    m_pElement(NULL),
    m_pElementSet(pElementSet),
    m_ActionType(actionType)
{}
//---------------------------------------------------------------------------
PSS_ModelObserverMsg::PSS_ModelObserverMsg(IEActionType          actionType,
                                       PSS_ProcessGraphModelDoc* pDoc,
                                       PSS_ProcessGraphModelMdl* pModel,
                                       PSS_ProcessGraphPage*     pPage) :
    PSS_ObserverMsg(),
    m_pDoc(pDoc),
    m_pModel(pModel),
    m_pPage(pPage),
    m_pElement(NULL),
    m_pElementSet(NULL),
    m_ActionType(actionType)
{}
//---------------------------------------------------------------------------
PSS_ModelObserverMsg::~PSS_ModelObserverMsg()
{}
//---------------------------------------------------------------------------
