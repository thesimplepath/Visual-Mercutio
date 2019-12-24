/****************************************************************************
 * ==> PSS_LogicalRulesObserverMsg -----------------------------------------*
 ****************************************************************************
 * Description : Provides a logical rules observer message                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LogicalRulesObserverMsg.h"

// processsoft
#include "ZBRulesEntity.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_LogicalRulesObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_LogicalRulesObserverMsg
//---------------------------------------------------------------------------
PSS_LogicalRulesObserverMsg::PSS_LogicalRulesObserverMsg(UINT           messageID,
                                                         ZBRulesEntity* pEntity,
                                                         const CString& rootName) :
    PSS_ObserverMsg(),
    m_pEntity(pEntity),
    m_RootName(rootName),
    m_MessageID(messageID)
{}
//---------------------------------------------------------------------------
PSS_LogicalRulesObserverMsg::~PSS_LogicalRulesObserverMsg()
{}
//---------------------------------------------------------------------------
