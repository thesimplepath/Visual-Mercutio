/****************************************************************************
 * ==> PSS_PropertyItemObserverMsg -----------------------------------------*
 ****************************************************************************
 * Description : Provides a property item observer message                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PropertyItemObserverMsg.h"

// processsoft
#include "PSS_Property.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_PropertyItemObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_PropertyItemObserverMsg
//---------------------------------------------------------------------------
PSS_PropertyItemObserverMsg::PSS_PropertyItemObserverMsg(PSS_Property* pProp) :
    PSS_ObserverMsg(),
    m_pProperty(pProp)
{}
//---------------------------------------------------------------------------
PSS_PropertyItemObserverMsg::~PSS_PropertyItemObserverMsg()
{}
//---------------------------------------------------------------------------
