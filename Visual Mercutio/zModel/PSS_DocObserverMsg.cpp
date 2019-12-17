/****************************************************************************
 * ==> PSS_DocObserverMsg --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a document observer message                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DocObserverMsg.h"

// processsoft
#include "PSS_Symbol.h"
#include "PSS_ProcessGraphModelDoc.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_DocObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_DocObserverMsg
//---------------------------------------------------------------------------
PSS_DocObserverMsg::PSS_DocObserverMsg(IEActionType              actionType,
                                       PSS_ProcessGraphModelDoc* pDoc,
                                       PSS_ProcessGraphModelMdl* pModel,
                                       CODSymbolComponent*       pElement) :
    PSS_ObserverMsg(),
    m_ActionType(actionType),
    m_pDoc(pDoc),
    m_pModel(pModel),
    m_pElement(pElement)
{}
//---------------------------------------------------------------------------
PSS_DocObserverMsg::~PSS_DocObserverMsg()
{}
//---------------------------------------------------------------------------
