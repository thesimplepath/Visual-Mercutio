/****************************************************************************
 * ==> PSS_UserGroupObserverMsg --------------------------------------------*
 ****************************************************************************
 * Description : Provides an user group observer message                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UserGroupObserverMsg.h"

// processsoft
#include "PSS_UserEntity.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_UserGroupObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_UserGroupObserverMsg
//---------------------------------------------------------------------------
PSS_UserGroupObserverMsg::PSS_UserGroupObserverMsg(UINT messageID, PSS_UserEntity* pEntity, const CString& rootName) :
    PSS_ObserverMsg(),
    m_pEntity(pEntity),
    m_RootName(rootName),
    m_MessageID(messageID)
{}
//---------------------------------------------------------------------------
PSS_UserGroupObserverMsg::~PSS_UserGroupObserverMsg()
{}
//---------------------------------------------------------------------------
