// ******************************************************************************************************************
// *                                      Classe ZBLogicalPrestationsObserverMsg                                    *
// ******************************************************************************************************************
// * JMR-MODIF - Le 7 octobre 2005 - Ajout de la classe ZBLogicalPrestationsObserverMsg.                            *
// ******************************************************************************************************************
// * Cette classe est un observateur d'événements pour les classes de gestion des prestations.                        *
// ******************************************************************************************************************

#include "stdafx.h"
#include "ZBLogicalPrestationsObserverMsg.h"

#include "ZBPrestationsEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(ZBLogicalPrestationsObserverMsg, PSS_ObserverMsg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBLogicalPrestationsObserverMsg::ZBLogicalPrestationsObserverMsg(UINT                    MessageID    /*= 0*/,
                                                                 ZBPrestationsEntity*    pEntity        /*= NULL*/,
                                                                 const CString            RootName    /*= _T( "" )*/) :
    PSS_ObserverMsg(),
    m_MessageID(MessageID),
    m_pEntity(pEntity),
    m_RootName(RootName)
{}

ZBLogicalPrestationsObserverMsg::~ZBLogicalPrestationsObserverMsg()
{}
