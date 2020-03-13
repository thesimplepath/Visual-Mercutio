/****************************************************************************
 * ==> PSS_PropertyObserverMsg ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a property observer message                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PropertyObserverMsg.h"

// processsoft
#include "PSS_Properties.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_PropertyObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_PropertyObserverMsg
//---------------------------------------------------------------------------
PSS_PropertyObserverMsg::PSS_PropertyObserverMsg(PSS_Properties* pProps) :
    PSS_ObserverMsg(),
    m_pProperties(pProps)
{}
//---------------------------------------------------------------------------
PSS_PropertyObserverMsg::~PSS_PropertyObserverMsg()
{}
//---------------------------------------------------------------------------
