// ZBKeyboardObserverMsg.cpp: implementation of the ZBKeyboardObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBKeyboardObserverMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( ZBKeyboardObserverMsg, ZIObserverMsg )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBKeyboardObserverMsg::ZBKeyboardObserverMsg( UINT MessageID /*= 0*/, UINT Key /*= 0*/ )
	: m_MessageID	( MessageID ),
	  m_Key			( Key )
{
}

ZBKeyboardObserverMsg::~ZBKeyboardObserverMsg()
{
}
