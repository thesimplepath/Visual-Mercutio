// ZDGridReportDoc.cpp : implementation of the ZDGridReportDocument class

#include "stdafx.h"

// RS-MODIF 14.12.04
#include "ZBaseLib\ZAGlobal.h"

#include "ZDGridReportDoc.h"
#include "ZVGridView.h"

#include "ZBGenericGridReportGenerator.h"

#include "zBaseLib\MsgBox.h"

#include "zReportRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

static ZBGenericGridReportGenerator* g_pGenerator = NULL;

/////////////////////////////////////////////////////////////////////////////
// ZDGridReportDocument

GXIMPLEMENT_DYNCREATE( ZDGridReportDocument, ZDGridDocument )

BEGIN_MESSAGE_MAP( ZDGridReportDocument, ZDGridDocument )
	//{{AFX_MSG_MAP(ZDGridReportDocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZDGridReportDocument construction/destruction

ZDGridReportDocument::ZDGridReportDocument()
	: m_pGenerator				( NULL ),
	  m_ViewRequireDataRefresh	( false )
{
	// RS-MODIF 14.12.04 bug error closing doc
	//ZAGlobal::SetpReportDocumentTemplate(NULL);
	//m_pGenerator = NULL;
}

ZDGridReportDocument::~ZDGridReportDocument()
{
	if ( m_pGenerator )
	{
		delete m_pGenerator;
		m_pGenerator = NULL;
	}

	// RS-MODIF 14.12.04 try to kill the doc
	/*CMultiDocTemplate* test = ZAGlobal::GetpReportDocumentTemplate();
	if (test != NULL)
	{
		ZAGlobal::SetpReportDocumentTemplate(NULL);
	}*/
	
	//if(m_pReportDocTemplate != NULL)
	//{
		//m_pReportDocTemplate->CloseAllDocuments(TRUE);
		//delete m_pReportDocTemplate;
	//}
}

bool ZDGridReportDocument::SetNewReportGridGenerator( ZBGenericGridReportGenerator* pGenerator )
{
	if ( GetPrimaryDocument() == this )
	{
		if ( pGenerator )
		{
			if ( m_pGenerator )
			{
				delete m_pGenerator;
			}

			m_pGenerator = pGenerator;

			// After the assignement of the new generator,
			// The frame title may has changed.
			UpdateFrameTitle();

			// And now, Initialize the grid with the right information
			return InitializeGrid();
		}
	}

	return ( GetPrimaryDocument() &&
			 ISA( GetPrimaryDocument(), ZDGridReportDocument ) ) ?
				dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->SetNewReportGridGenerator( pGenerator ) : false;
}

bool ZDGridReportDocument::InitializeGenerator()
{
	if ( GetPrimaryDocument() == this )
	{
		return ( m_pGenerator != NULL ) ? m_pGenerator->Initialize() : false;
	}

	// Call the function from the primary document
	return ( GetPrimaryDocument() &&
			 ISA( GetPrimaryDocument(), ZDGridReportDocument ) ) ?
				dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->InitializeGenerator() : false;
}

bool ZDGridReportDocument::InitializeGrid()
{
	if ( !InitializeGenerator() )
	{
		return false;
	}

	// At least one tab is required
	if ( GetGeneratorTabCount() == 0 )
	{
		return false;
	}

	// First, check if necessary to remove tabs
	// Don't remove all tabs, just the difference if positive
	if ( GetGeneratorTabCount() < GetGridTabCount() )
	{
		int Diff = GetGridTabCount() - GetGeneratorTabCount();

		for ( ; Diff > 0; --Diff )
		{
			DeleteGridTab();
		}
	}

	// Now, for each tab, fill the grid param
	size_t ExistingGridTabCount = GetGridTabCount();

	// Now if necessary, create additional tabs
	size_t CompleteTabCount = GetGeneratorTabCount();

	for ( size_t i = ExistingGridTabCount; i < CompleteTabCount; ++i )
	{
		// By inserting new tab, a new view is created and 
		// the OnInitialUpdate function is called,
		// which fill the grid by calling FillGrid for the right 
		// index view
		InsertNewGridTab();
	}

	// Now change the tab name
	for ( size_t j = 0; j < CompleteTabCount; ++j )
	{
		SetTabName( GetGeneratorTabName( j ), j );
	}

	// Request to fill all tabs
	for ( size_t k = 0; k < CompleteTabCount; ++k )
	{
		// Get the adequate grid param pointer
		CGXGridCore* pGridCore = GetTabGridCore( k );

		if ( !pGridCore )
		{
			continue;
		}

		// Lock any drawing
		BOOL bOld = pGridCore->LockUpdate();

		// disable undo mechanism for the following commands
		pGridCore->GetParam()->EnableUndo( FALSE );
		
		// Call the call-back function
		OnPreDataFilled( k );

		// Request to fill the grid parameter
		FillGrid( *pGridCore, k );

		// Call the call-back function
		OnPostDataFilled( k );

		// reenable undo mechanism
		pGridCore->GetParam()->EnableUndo( TRUE );

		// Unlock drawing
		pGridCore->LockUpdate( bOld );

		// Just to be sure that everything is redrawn
		pGridCore->Redraw();
	}

	// Set the modified flag to true
	SetModifiedFlag();

	return true;
}

bool ZDGridReportDocument::SetAllTabNameToGrid()
{
	size_t CompleteTabCount = GetGeneratorTabCount();

	// Request to fill all tabs
	for ( size_t i = 0; i < CompleteTabCount; ++i )
	{
		// First, sets the correct tab name
		SetTabName( GetGeneratorTabName( i ), i );
	}

	return true;
}

size_t ZDGridReportDocument::GetGeneratorTabCount() const
{
	if ( GetPrimaryDocument() == const_cast<ZDGridReportDocument*>( this ) )
	{
		return ( m_pGenerator != NULL ) ? m_pGenerator->GetGeneratorTabCount() : 0;
	}

	// Call the function from the primary document
	return ( GetPrimaryDocument() &&
			 ISA( GetPrimaryDocument(), ZDGridReportDocument ) ) ?
				dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->GetGeneratorTabCount() : 0;
}

const CString ZDGridReportDocument::GetGeneratorTabName( size_t Index )
{
	if ( GetPrimaryDocument() == this )
	{
		return ( m_pGenerator != NULL ) ? m_pGenerator->GetGeneratorTabName( Index ) : _T( "" );
	}

	// Call the function from the primary document
	return ( GetPrimaryDocument() &&
			 ISA( GetPrimaryDocument(), ZDGridReportDocument ) ) ?
				dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->GetGeneratorTabName( Index ) : _T( "" );
}

bool ZDGridReportDocument::FillGrid( CGXGridCore& GridCore, size_t Index )
{
	if ( GetPrimaryDocument() == this )
	{
		return ( m_pGenerator != NULL ) ? m_pGenerator->FillGrid( GridCore, Index ) : true;
	}

	// Call the function from the primary document
	return ( GetPrimaryDocument() &&
			 ISA( GetPrimaryDocument(), ZDGridReportDocument ) ) ?
				dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->FillGrid( GridCore, Index ) : true;
}

void ZDGridReportDocument::SetReportTypeID( int TypeID )
{
	if ( GetPrimaryDocument() == this )
	{
		if ( m_pGenerator != NULL )
		{
			m_pGenerator->SetReportTypeID( TypeID );
		}
	}

	// Call the function from the primary document
	if ( GetPrimaryDocument() && ISA( GetPrimaryDocument(), ZDGridReportDocument ) )
	{
		dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->SetReportTypeID( TypeID );
	}
}

int  ZDGridReportDocument::GetReportTypeID() const
{
	if ( GetPrimaryDocument() == const_cast<ZDGridReportDocument*>( this ) )
	{
		return ( m_pGenerator != NULL ) ? m_pGenerator->GetReportTypeID() : -1;
	}

	// Call the function from the primary document
	return ( GetPrimaryDocument() &&
			 ISA( GetPrimaryDocument(), ZDGridReportDocument ) ) ?
				dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->GetReportTypeID() : -1;
}

const CString ZDGridReportDocument::GetReportTitle() const
{
	if ( GetPrimaryDocument() == const_cast<ZDGridReportDocument*>( this ) )
	{
		return ( m_pGenerator != NULL ) ? m_pGenerator->GetReportTitle() : _T( "" );
	}

	// Call the function from the primary document
	return ( GetPrimaryDocument() &&
			 ISA( GetPrimaryDocument(), ZDGridReportDocument ) ) ?
				dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->GetReportTitle() : _T( "" );
}

bool ZDGridReportDocument::IsReportDataExternal() const
{
	if ( GetPrimaryDocument() == const_cast<ZDGridReportDocument*>( this ) )
	{
		return ( m_pGenerator != NULL ) ? m_pGenerator->IsReportDataExternal() : false;
	}

	// Call the function from the primary document
	return ( GetPrimaryDocument() &&
			 ISA( GetPrimaryDocument(), ZDGridReportDocument ) ) ?
				dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->IsReportDataExternal() : false;
}

bool ZDGridReportDocument::ReportDataMustBeReloaded() const
{
	if ( GetPrimaryDocument() == const_cast<ZDGridReportDocument*>( this ) )
	{
		return ( m_pGenerator != NULL ) ? m_pGenerator->ReportDataMustBeReloaded() : false;
	}

	// Call the function from the primary document
	return ( GetPrimaryDocument() &&
			 ISA( GetPrimaryDocument(), ZDGridReportDocument ) ) ?
				dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->ReportDataMustBeReloaded() : false;
}

bool ZDGridReportDocument::UseAutomaticReload() const
{
	if ( GetPrimaryDocument() == const_cast<ZDGridReportDocument*>( this ) )
	{
		return ( m_pGenerator != NULL ) ? m_pGenerator->UseAutomaticReload() : false;
	}

	// Call the function from the primary document
	return ( GetPrimaryDocument() &&
			 ISA( GetPrimaryDocument(), ZDGridReportDocument ) ) ?
				dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->UseAutomaticReload() : false;
}

void ZDGridReportDocument::OnPreDataFilled( size_t Index )
{
	if ( GetPrimaryDocument() == this )
	{
		if ( m_pGenerator != NULL )
		{
			m_pGenerator->OnPreDataFilled( Index );
		}

		return;
	}

	// Call the function from the primary document
	if ( GetPrimaryDocument() && ISA( GetPrimaryDocument(), ZDGridReportDocument ) )
	{
		dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->OnPreDataFilled( Index );
	}
}

void ZDGridReportDocument::OnPostDataFilled( size_t Index )
{
	if ( GetPrimaryDocument() == this )
	{
		if ( m_pGenerator != NULL )
		{
			m_pGenerator->OnPostDataFilled( Index );

			// Change the modified flag
			SetModifiedFlag();
		}

		return;
	}

	// Call the function from the primary document
	if ( GetPrimaryDocument() && ISA( GetPrimaryDocument(), ZDGridReportDocument ) )
	{
		dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->OnPostDataFilled( Index );
	}
}

/////////////////////////////////////////////////////////////////////////////
// ZDGridReportDocument serialization

void ZDGridReportDocument::WorkBookSerialize( CArchive& ar )
{
	ZDGridDocument::WorkBookSerialize( ar );

	if ( ar.IsStoring() )
	{
		ar << m_pGenerator;
	}
	else
	{
		ar >> m_pGenerator;

		// If we have a pointer value and we are not the primary document
		if ( m_pGenerator )
		{
			// Saves the pointer for further assignement
			// We cannot set this pointer through the GetPrimaryDocument, since
			// since he is not yet assigned 
			g_pGenerator = m_pGenerator;

			// Reset the pointer value.
			m_pGenerator = NULL;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// ZDGridReportDocument commands

BOOL ZDGridReportDocument::OnOpenDocument( LPCTSTR pszPathName )
{
	// Reset the Generator pointer
	g_pGenerator = NULL;

	// Set to false. If necessary, will be set to true later
	m_ViewRequireDataRefresh = false;

	if ( !ZDGridDocument::OnOpenDocument( pszPathName ) )
	{
		return FALSE;
	}

	// if we have a valid generator pointer
	// Assigns it to the primary document
	if ( g_pGenerator && GetPrimaryDocument() && ISA( GetPrimaryDocument(), ZDGridReportDocument ) )
	{
		dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() )->AssignGeneratorPtr( g_pGenerator );
		g_pGenerator->SetDocument( dynamic_cast<ZDGridReportDocument*>( GetPrimaryDocument() ) );
	}

	return TRUE;
}

bool ZDGridReportDocument::OnPostInitialized( CGXTabWndMgr* pMgr, CGXAppAdapter* pAppAdapt, bool NewFile )
{
	if ( !NewFile )
	{
		// We do this, since I don't know why objective grid sets the primary document as
		// the last document and not on this document which is the master document after the
		// read. In CreateTabs function, the manager changes the primary document
		// to the last document. This generates a situation where the last document has
		// a primary document pointer to itself and all the others have the primary
		// document pointer set to this document
		ASSERT( pMgr );
		ASSERT( pAppAdapt );

		// Retreive the tab create info pointer array
		CArray<CGXTabCreateInfo*, CGXTabCreateInfo*>* pTabInfoArray = pMgr->GetTabCreateInfoArray();

		// Retreive the size
		int Count = pTabInfoArray->GetSize();

		for ( int i = 0; i < Count; ++i )
		{
			CGXTabCreateInfo* pInfo = pTabInfoArray->GetAt( i );
			ASSERT( pInfo );

			if ( pInfo->GetDocument() )
			{
				pInfo->GetDocument()->SetPrimaryDocument( this );
			}
		}

		if ( IsReportDataExternal() && ReportDataMustBeReloaded() )
		{
			// Set the m_ViewRequireDataRefresh to true. This will force the view to
			// fill the grid again when the OnInitialUpdate will be called
			m_ViewRequireDataRefresh = true;

			// If don't use automatic reload, ask the question before
			if ( !UseAutomaticReload() )
			{
				MsgBox mbox;

				if ( mbox.DisplayMsgBox( IDS_MASTERDATA_CHANGE_RELOAD, MB_YESNO ) == IDNO )
				{
					// Set the m_ViewRequireDataRefresh to false. This will not required the view to
					// fill the grid again when the OnInitialUpdate will be called
					m_ViewRequireDataRefresh = false;
				}
			}

			InitializeGrid();
		}
		else
		{
			// Reload all tab names from the generator
			SetAllTabNameToGrid();
		}

		// Reset the flag
		m_ViewRequireDataRefresh = false;
	}

	// Returns the first document view
	ZVGridView* pView = GetFirstView();

	// Sets the right popup submenu
	if ( pView )
	{
		pView->SetPopupMenu( IDR_GRIDREPORT_SUBMENU );
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
// ZDGridReportDocument diagnostics

#ifdef _DEBUG
void ZDGridReportDocument::AssertValid() const
{
	ZDGridDocument::AssertValid();
}

void ZDGridReportDocument::Dump( CDumpContext& dc ) const
{
	ZDGridDocument::Dump( dc );
}
#endif //_DEBUG
