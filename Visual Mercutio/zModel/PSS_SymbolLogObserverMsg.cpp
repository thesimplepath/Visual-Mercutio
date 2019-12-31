/****************************************************************************
 * ==> PSS_SymbolLogObserverMsg --------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol log observer message                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SymbolLogObserverMsg.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_SymbolLogObserverMsg, PSS_ObserverMsg)
//---------------------------------------------------------------------------
// PSS_SymbolLogObserverMsg
//---------------------------------------------------------------------------
PSS_SymbolLogObserverMsg::PSS_SymbolLogObserverMsg() :
    PSS_ObserverMsg()
{}
//---------------------------------------------------------------------------
PSS_SymbolLogObserverMsg::PSS_SymbolLogObserverMsg(const PSS_GenericSymbolErrorLine& errorLine) :
    PSS_ObserverMsg(),
    m_ErrorLine(errorLine)
{}
//---------------------------------------------------------------------------
PSS_SymbolLogObserverMsg::~PSS_SymbolLogObserverMsg()
{}
//---------------------------------------------------------------------------
