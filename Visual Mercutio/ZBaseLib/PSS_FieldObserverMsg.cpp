/****************************************************************************
 * ==> PSS_FieldObserverMsg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a message for the field observer                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FieldObserverMsg.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_FieldObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_FieldObserverMsg
//---------------------------------------------------------------------------
PSS_FieldObserverMsg::PSS_FieldObserverMsg(UINT messageID, PSS_PlanFinObject* pObject) :
    PSS_ObserverMsg(),
    m_MessageID(messageID),
    m_pObject(pObject)
{}
//---------------------------------------------------------------------------
PSS_FieldObserverMsg::~PSS_FieldObserverMsg()
{}
//---------------------------------------------------------------------------
