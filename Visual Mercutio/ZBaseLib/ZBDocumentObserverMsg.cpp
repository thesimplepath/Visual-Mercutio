// ZBDocumentObserverMsg.cpp: implementation of the ZBDocumentObserverMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBDocumentObserverMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( ZBDocumentObserverMsg, ZIObserverMsg )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBDocumentObserverMsg::ZBDocumentObserverMsg( UINT MessageID /*= 0*/, CDocument* pDoc /*= NULL*/ )
	: m_MessageID	( MessageID ), 
	  m_pDoc		( pDoc ),
	  m_pView		( NULL )
{
}

ZBDocumentObserverMsg::ZBDocumentObserverMsg( UINT MessageID, CView* pView )
	: m_MessageID	( MessageID ),
	  m_pView		( pView ),
	  m_pDoc		( NULL )
{
}

ZBDocumentObserverMsg::ZBDocumentObserverMsg( UINT MessageID, CDocument* pDoc, CView* pView )
	: m_MessageID	( MessageID ), 
	  m_pDoc		( pDoc ),
	  m_pView		( pView )
{
}

ZBDocumentObserverMsg::~ZBDocumentObserverMsg()
{
}
