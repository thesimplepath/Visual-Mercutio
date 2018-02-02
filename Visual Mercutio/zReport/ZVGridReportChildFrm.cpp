// ZVGridReportChildFrm.cpp : implementation of the ZVGridReportChildFrame class

#include "stdafx.h"

#include "ZDGridReportDoc.h"
#include "ZVGridReportView.h"
#include "ZVGridReportChildFrm.h"

#include "ZDGridReportDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVGridReportChildFrame

IMPLEMENT_DYNCREATE( ZVGridReportChildFrame, ZVGridChildFrame )

BEGIN_MESSAGE_MAP( ZVGridReportChildFrame, ZVGridChildFrame )
	//{{AFX_MSG_MAP(ZVGridReportChildFrame)
	ON_MESSAGE(WM_GX_INITNEW, OnInitNew)
	ON_MESSAGE(WM_GX_INITFILE, OnInitFromFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVGridReportChildFrame construction/destruction

ZVGridReportChildFrame::ZVGridReportChildFrame()
{
	SetDocRuntimeClass( RUNTIME_CLASS( ZDGridReportDocument ) );
	SetViewRuntimeClass( RUNTIME_CLASS( ZVGridReportView ) );
}

ZVGridReportChildFrame::~ZVGridReportChildFrame()
{
	// RS-MODIF 20.12.04 We need to remove the tab manager when destroying the child frame, because sometimes it remains for no reason
	// and causes the application to crash
	CGXAppAdapter* pAppAdapt = dynamic_cast<CGXAppAdapter*>( AfxGetApp() );
	pAppAdapt->RemoveTabManager( CGXFrameAdapter::GetWindow()->GetRuntimeClass(), m_pContext->m_pCurrentDoc );
}

//////////////////
// Override to change the model title.

void ZVGridReportChildFrame::OnUpdateFrameTitle( BOOL bAddToTitle )
{
	ZVGridChildFrame::OnUpdateFrameTitle( bAddToTitle );
	CDocument* pDoc = GetActiveDocument();

	if ( pDoc && ISA( pDoc, ZDGridReportDocument ) )
	{
		CString WndText = ( (ZDGridReportDocument*)pDoc )->GetReportTitle();

		// Set the right title
		SetWindowText( WndText );
	}
}

/////////////////////////////////////////////////////////////////////////////
// ZVGridReportChildFrame message handlers

// default initialization for the tabs
LRESULT ZVGridReportChildFrame::OnInitNew( WPARAM wParam, LPARAM lParam )
{
	// RS-MODIF 15.12.04 doc bug => the crash occurs in this routine
	// when the pointer m_hWnd from m_pActivePane is wrong
	LRESULT lResult = CGXWChildFrame::OnInitNew( wParam, lParam );

	CGXAppAdapter* pAppAdapt = dynamic_cast<CGXAppAdapter*>( AfxGetApp() );

	ASSERT( pAppAdapt != NULL );

	// We need a valid create context --> END
	ASSERT( m_pContext != NULL );

	// RS-MODIF 15.12.04 doc bug test
	// the call to GetTabManager fails to create a new tab manager depending on an information in m_pContext->m_pCurrentDoc
	// stingray calls a routine where GetMap()->Lookup(dw, pObject) should return FALSE (that is, the object at memory dw should not exist)
	// when the object exist, the crash occurs
	CGXTabWndMgr* pMgr =
		pAppAdapt->GetTabManager( CGXFrameAdapter::GetWindow()->GetRuntimeClass(), m_pContext->m_pCurrentDoc );

	// Call the post initialization handler
	if ( ISA( m_pContext->m_pCurrentDoc, ZDGridReportDocument ) )
	{
		dynamic_cast<ZDGridReportDocument*>( m_pContext->m_pCurrentDoc )->OnPostInitialized( pMgr, pAppAdapt, true );
	}

	return lResult;
}

// When initializing from a file
LRESULT ZVGridReportChildFrame::OnInitFromFile( WPARAM wParam, LPARAM lParam )
{
	LRESULT lResult = CGXWChildFrame::OnInitFromFile( wParam, lParam );

	CGXAppAdapter* pAppAdapt = dynamic_cast<CGXAppAdapter*>( AfxGetApp() );
	ASSERT( pAppAdapt != NULL );

	// We need a valid create context --> END
	ASSERT( m_pContext != NULL );

	CGXTabWndMgr* pMgr =
		pAppAdapt->GetTabManager( CGXFrameAdapter::GetWindow()->GetRuntimeClass(), m_pContext->m_pCurrentDoc );

	// Call the post initialization handler
	if ( ISA( m_pContext->m_pCurrentDoc, ZDGridReportDocument ) )
	{
		dynamic_cast<ZDGridReportDocument*>( m_pContext->m_pCurrentDoc )->OnPostInitialized( pMgr, pAppAdapt, false );
	}

	return lResult;
}

/////////////////////////////////////////////////////////////////////////////
// ZVGridReportChildFrame diagnostics

#ifdef _DEBUG
void ZVGridReportChildFrame::AssertValid() const
{
	ZVGridChildFrame::AssertValid();
}

void ZVGridReportChildFrame::Dump( CDumpContext& dc ) const
{
	ZVGridChildFrame::Dump( dc );
}
#endif //_DEBUG
