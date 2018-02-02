// ZVGridChildFrm.cpp : implementation of the ZVGridChildFrame class

#include "stdafx.h"

#include "ZDGridDoc.h"
#include "ZVGridView.h"
#include "ZVGridChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVGridChildFrame

IMPLEMENT_DYNCREATE( ZVGridChildFrame, CGXWChildFrame )

BEGIN_MESSAGE_MAP( ZVGridChildFrame, CGXWChildFrame )
	//{{AFX_MSG_MAP(ZVGridChildFrame)
	ON_UPDATE_COMMAND_UI( ID_INSERTSKSHEET, CGXWChildFrame::CanInsertWorkSheet )
	ON_UPDATE_COMMAND_UI( ID_DELETEWKSHEET, CGXWChildFrame::CanDeleteWorkSheet )
	ON_COMMAND(ID_DELETEWKSHEET, OnDeletewksheet)
	ON_COMMAND(ID_INSERTSKSHEET, OnInsertsksheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVGridChildFrame construction/destruction

ZVGridChildFrame::ZVGridChildFrame()
{
	SetDocRuntimeClass( RUNTIME_CLASS( ZDGridDocument ) );
	SetViewRuntimeClass( RUNTIME_CLASS( ZVGridView ) );

	// Initialize the number of tabs to 1. Not 3 as the default
	SetNumberOfTabs( 1 );
}

ZVGridChildFrame::~ZVGridChildFrame()
{
}

BOOL ZVGridChildFrame::PreCreateWindow( CREATESTRUCT& cs )
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CGXWChildFrame::PreCreateWindow( cs );
}

/////////////////////////////////////////////////////////////////////////////
// ZVGridChildFrame diagnostics

#ifdef _DEBUG
void ZVGridChildFrame::AssertValid() const
{
	CGXWChildFrame::AssertValid();
}

void ZVGridChildFrame::Dump( CDumpContext& dc ) const
{
	CGXWChildFrame::Dump( dc );
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZVGridChildFrame message handlers

void ZVGridChildFrame::OnDeletewksheet()
{
	DeleteWorkSheetHandler();
}

void ZVGridChildFrame::OnInsertsksheet()
{
	InsertWorkSheetHandler();
}
