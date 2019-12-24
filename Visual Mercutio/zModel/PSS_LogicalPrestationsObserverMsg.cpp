/****************************************************************************
 * ==> PSS_LogicalPrestationsObserverMsg -----------------------------------*
 ****************************************************************************
 * Description : Provides a logical prestation observer message             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LogicalPrestationsObserverMsg.h"

// processsoft
#include "ZBPrestationsEntity.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_LogicalPrestationsObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_LogicalPrestationsObserverMsg
//---------------------------------------------------------------------------
PSS_LogicalPrestationsObserverMsg::PSS_LogicalPrestationsObserverMsg(UINT                 messageID,
                                                                     ZBPrestationsEntity* pEntity,
                                                                     const CString&       rootName) :
    PSS_ObserverMsg(),
    m_pEntity(pEntity),
    m_RootName(rootName),
    m_MessageID(messageID)
{}
//---------------------------------------------------------------------------
PSS_LogicalPrestationsObserverMsg::~PSS_LogicalPrestationsObserverMsg()
{}
//---------------------------------------------------------------------------
