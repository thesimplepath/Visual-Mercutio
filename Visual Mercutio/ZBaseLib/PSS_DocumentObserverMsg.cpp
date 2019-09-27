/****************************************************************************
 * ==> PSS_DocumentObserverMsg ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a message for the document observer               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DocumentObserverMsg.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_DocumentObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_DocumentObserverMsg
//---------------------------------------------------------------------------
PSS_DocumentObserverMsg::PSS_DocumentObserverMsg(UINT messageID, CDocument* pDoc) :
    PSS_ObserverMsg(),
    m_MessageID(messageID),
    m_pDoc(pDoc),
    m_pView(NULL)
{}
//---------------------------------------------------------------------------
PSS_DocumentObserverMsg::PSS_DocumentObserverMsg(UINT messageID, CView* pView) :
    PSS_ObserverMsg(),
    m_MessageID(messageID),
    m_pView(pView),
    m_pDoc(NULL)
{}
//---------------------------------------------------------------------------
PSS_DocumentObserverMsg::PSS_DocumentObserverMsg(UINT messageID, CDocument* pDoc, CView* pView) :
    PSS_ObserverMsg(),
    m_MessageID(messageID),
    m_pDoc(pDoc),
    m_pView(pView)
{}
//---------------------------------------------------------------------------
PSS_DocumentObserverMsg::~PSS_DocumentObserverMsg()
{}
//---------------------------------------------------------------------------
