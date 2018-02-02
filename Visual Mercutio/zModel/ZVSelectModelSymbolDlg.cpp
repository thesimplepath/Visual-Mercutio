// ZVSelectModelSymbolDlg.cpp : implementation file

#include "stdafx.h"
#include "ZVSelectModelSymbolDlg.h"

#include "ProcGraphModelMdl.h"
#include "ZDProcessGraphPage.h"
#include "ZBModelSet.h"

#include "ZBSymbol.h"
#include "ZBLinkSymbol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 6 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVSelectModelSymbolDlg dialog

BEGIN_MESSAGE_MAP( ZVSelectModelSymbolDlg, ZIDialog )
	//{{AFX_MSG_MAP(ZVSelectModelSymbolDlg)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(TVN_SELCHANGED, IDC_SYMBOLTREE, OnSelchangedSymboltree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVSelectModelSymbolDlg::ZVSelectModelSymbolDlg( ZDProcessGraphModelMdl*	pModel,
												const CString			Title			/*= ""*/,
												int						SelectableItem	/*= Selectable_All*/,
												ZBRuntimeClassSet*		pSet			/*= NULL*/,
												CWnd*					pParent			/*=NULL*/ )
	: ZIDialog			( ZVSelectModelSymbolDlg::IDD, TRUE, pParent ),
	  m_pModel			( pModel ),
	  m_pSelectedModel	( NULL ),
	  m_pSelectedSymbol	( NULL ),
	  m_pSelectedPage	( NULL ),
	  m_pSelectableClass( NULL ),
	  m_Title			( Title ),
	  m_SelectableItem	( SelectableItem ),
	  m_pSet			( pSet )
{
	//{{AFX_DATA_INIT(ZVSelectModelSymbolDlg)
	m_SymbolPath = _T("");
	m_SymbolName = _T("");
	//}}AFX_DATA_INIT
}

ZVSelectModelSymbolDlg::ZVSelectModelSymbolDlg( ZDProcessGraphModelMdl*	pModel,
												const CString			Title,
												CRuntimeClass*			pSelectableClass,
												ZBRuntimeClassSet*		pSet				/*= NULL*/,
												CWnd*					pParent				/*=NULL*/ )
	: ZIDialog			( ZVSelectModelSymbolDlg::IDD, TRUE, pParent ),
	  m_pModel			( pModel ),
	  m_pSelectedModel	( NULL ),
	  m_pSelectedSymbol	( NULL ),
	  m_pSelectedPage	( NULL ),
	  m_Title			( Title ),
	  m_pSelectableClass( pSelectableClass ),
	  m_SelectableItem	( 0 ),
	  m_pSet			( pSet )
{
	//{{AFX_DATA_INIT(ZVSelectSymbolFromGraphModel)
	m_SymbolPath = _T("");
	m_SymbolName = _T("");
	//}}AFX_DATA_INIT
}

ZVSelectModelSymbolDlg::ZVSelectModelSymbolDlg( ZDProcessGraphModelMdl*	pModel,
												UINT					nIDResTitle,
												int						SelectableItem	/*= Selectable_All*/,
												ZBRuntimeClassSet*		pSet			/*= NULL*/,
												CWnd*					pParent			/*=NULL*/ )
	: ZIDialog				( ZVSelectModelSymbolDlg::IDD, TRUE, pParent ),
	  m_pModel				( pModel ),
	  m_pSelectedModel		( NULL ),
	  m_pSelectedSymbol		( NULL ),
	  m_pSelectableClass	( NULL ),
	  m_pSelectedPage		( NULL ),
	  m_SelectableItem		( SelectableItem ),
	  m_pSet				( pSet )
{
	//{{AFX_DATA_INIT(ZVSelectModelSymbolDlg)
	m_SymbolPath = _T("");
	m_SymbolName = _T("");
	//}}AFX_DATA_INIT
	m_Title.LoadString( nIDResTitle );
}

ZVSelectModelSymbolDlg::ZVSelectModelSymbolDlg( ZDProcessGraphModelMdl*	pModel,
												UINT					nIDResTitle,
												CRuntimeClass*			pSelectableClass,
												ZBRuntimeClassSet*		pSet				/*= NULL*/,
												CWnd*					pParent				/*=NULL*/ )
	: ZIDialog			( ZVSelectModelSymbolDlg::IDD, TRUE, pParent ),
	  m_pModel			( pModel ),
	  m_pSelectedModel	( NULL ),
	  m_pSelectedSymbol	( NULL ),
	  m_pSelectedPage	( NULL ),
	  m_pSelectableClass( pSelectableClass ),
	  m_SelectableItem	( 0 ),
	  m_pSet			( pSet )
{
	//{{AFX_DATA_INIT(ZVSelectSymbolFromGraphModel)
	m_SymbolPath = _T("");
	m_SymbolName = _T("");
	//}}AFX_DATA_INIT
	m_Title.LoadString( nIDResTitle );
}

void ZVSelectModelSymbolDlg::DoDataExchange( CDataExchange* pDX )
{
	ZIDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP(ZVSelectModelSymbolDlg)
	DDX_Control(pDX, IDC_SYMBOLTREE, m_SymbolTree);
	DDX_Text(pDX, IDC_SYMBOLPATH, m_SymbolPath);
	DDX_Text(pDX, IDC_SYMBOLNAME, m_SymbolName);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVSelectModelSymbolDlg message handlers

void ZVSelectModelSymbolDlg::OnOK()
{
	// Assign values
	if ( m_SymbolTree.GetSelectedPage() != NULL )
	{
		// If the check must be done by runtime class
		if ( m_pSelectableClass )
		{
			if ( m_SymbolTree.GetSelectedPage() && m_SymbolTree.GetSelectedPage()->IsKindOf( m_pSelectableClass ) )
			{
				m_pSelectedPage		= m_SymbolTree.GetSelectedPage();
				m_pSelectedModel	= NULL;
				m_pSelectedSymbol	= NULL;
			}

			if ( m_pSelectedPage->GetpModel() )
			{
				m_SymbolPath = m_pSelectedPage->GetpModel()->GetAbsolutePath();
				m_SymbolName = m_pSelectedPage->GetpModel()->GetModelName();
			}
			else
			{
				m_SymbolPath = _T( "" );
				m_SymbolName = _T( "" );
			}
		}
		else
		{
			if ( m_SelectableItem & Selectable_GraphPage )
			{
				m_pSelectedPage		= m_SymbolTree.GetSelectedPage();
				m_pSelectedModel	= NULL;
				m_pSelectedSymbol	= NULL;

				if ( m_pSelectedPage->GetpModel() )
				{
					m_SymbolPath = m_pSelectedPage->GetpModel()->GetAbsolutePath();
					m_SymbolName = m_pSelectedPage->GetpModel()->GetModelName();
				}
				else
				{
					m_SymbolPath = _T( "" );
					m_SymbolName = _T( "" );
				}
			}
			else
			{
				// Not possible, should have been checked before
				ASSERT( FALSE );
			}
		}
	}
	else
	{
		m_pSelectedSymbol = m_SymbolTree.GetSelectedSymbol();

		// If the check must be done by runtime class
		if ( m_pSelectableClass )
		{
			if ( m_pSelectedSymbol && m_pSelectedSymbol->IsKindOf( m_pSelectableClass ) )
			{
				if ( m_pSelectedSymbol && ISA( m_pSelectedSymbol, ZBSymbol ) )
				{
					m_SymbolPath = ( (ZBSymbol*)m_pSelectedSymbol )->GetAbsolutePath();
					m_SymbolName = ( (ZBSymbol*)m_pSelectedSymbol )->GetSymbolName();
				}
				else if ( m_pSelectedSymbol && ISA( m_pSelectedSymbol, ZBLinkSymbol ) )
				{
					m_SymbolPath = ( (ZBLinkSymbol*)m_pSelectedSymbol )->GetAbsolutePath();
					m_SymbolName = ( (ZBLinkSymbol*)m_pSelectedSymbol )->GetSymbolName();
				}
				else
				{
					m_SymbolPath = _T( "" );
					m_SymbolName = _T( "" );
				}
			}
			else
			{
				// Not possible, should have been checked before
				ASSERT( FALSE );
			}
		}
		else if ( m_pSelectedSymbol && ISA( m_pSelectedSymbol, ZBSymbol ) )
		{
			if ( m_SelectableItem & Selectable_Symbol )
			{
				m_SymbolPath = ( (ZBSymbol*)m_pSelectedSymbol )->GetAbsolutePath();
				m_SymbolName = ( (ZBSymbol*)m_pSelectedSymbol )->GetSymbolName();
			}
			// And if contains a model
			if ( ( (ZBSymbol*)m_pSelectedSymbol )->GetChildModel() &&
				 ISA( ( (ZBSymbol*)m_pSelectedSymbol )->GetChildModel(), ZDProcessGraphModelMdl ) &&
				 !( (ZBSymbol*)m_pSelectedSymbol )->IsChildModelRef() )
			{
				if ( m_SelectableItem & Selectable_Model )
				{
					// Assign the model pointer
					m_pSelectedModel = ( (ZBSymbol*)m_pSelectedSymbol )->GetChildModel();

					m_SymbolPath =
						dynamic_cast<ZDProcessGraphModelMdl*>( ( (ZBSymbol*)m_pSelectedSymbol )->GetChildModel() )->GetAbsolutePath();

					m_SymbolName =
						dynamic_cast<ZDProcessGraphModelMdl*>( ( (ZBSymbol*)m_pSelectedSymbol )->GetChildModel() )->GetModelName();
				}
			}
		}
		else if ( m_pSelectedSymbol && ISA( m_pSelectedSymbol, ZBLinkSymbol ) )
		{
			if ( m_SelectableItem & Selectable_LinkSymbol )
			{
				m_SymbolPath = ( (ZBLinkSymbol*)m_pSelectedSymbol )->GetAbsolutePath();
				m_SymbolName = ( (ZBLinkSymbol*)m_pSelectedSymbol )->GetSymbolName();
			}
			else
			{
				// Not possible, should have been checked before
				ASSERT( FALSE );
			}
		}
	}

	UpdateData( FALSE );

	ZIDialog::OnOK();
}

void ZVSelectModelSymbolDlg::OnSelchangedSymboltree( NMHDR* pNMHDR, LRESULT* pResult )
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	bool				Enable			= false;
	CODModel*			pSelectedModel;
	CODSymbolComponent* pSelectedSymbol;
	ZDProcessGraphPage* pSelectedPage;

	if ( m_SymbolTree.GetSelectedPage () != NULL )
	{
		pSelectedPage = m_SymbolTree.GetSelectedPage();

		// If the check must be done by runtime class
		if ( m_pSelectableClass )
		{
			if ( pSelectedPage && pSelectedPage->IsKindOf( m_pSelectableClass ) )
			{
				Enable = true;
			}
		}
		else if ( m_SelectableItem & Selectable_GraphPage )
		{
			Enable = true;
		}

		pSelectedModel	= NULL;
		pSelectedSymbol = NULL;

		if ( pSelectedPage->GetpModel() )
		{
			m_SymbolPath = pSelectedPage->GetpModel()->GetAbsolutePath();
			m_SymbolName = pSelectedPage->GetpModel()->GetModelName();
		}
		else
		{
			m_SymbolPath = _T( "" );
			m_SymbolName = _T( "" );
		}
	}
	else
	{
		pSelectedSymbol = m_SymbolTree.GetSelectedSymbol();

		if ( pSelectedSymbol && ISA( pSelectedSymbol, ZBSymbol ) )
		{
			// If the check must be done by runtime class
			if ( m_pSelectableClass )
			{
				if ( pSelectedSymbol && pSelectedSymbol->IsKindOf( m_pSelectableClass ) )
				{
					Enable = true;
				}
			}
			else if ( m_SelectableItem & Selectable_Symbol )
			{
				Enable = true;
			}

			m_SymbolPath = ( (ZBSymbol*)pSelectedSymbol )->GetAbsolutePath();
			m_SymbolName = ( (ZBSymbol*)pSelectedSymbol )->GetSymbolName();

			// And if contains a model
			if ( ( (ZBSymbol*)pSelectedSymbol )->GetChildModel() &&
				 ISA( ( (ZBSymbol*)pSelectedSymbol )->GetChildModel(), ZDProcessGraphModelMdl ) &&
				 !( (ZBSymbol*)pSelectedSymbol )->IsChildModelRef() )
			{
				if ( !m_pSelectableClass && ( m_SelectableItem & Selectable_Model ) )
				{
					Enable = true;
				}

				// Assign the model pointer
				pSelectedModel = ( (ZBSymbol*)pSelectedSymbol )->GetChildModel();

				m_SymbolPath =
					dynamic_cast<ZDProcessGraphModelMdl*>( ( (ZBSymbol*)pSelectedSymbol )->GetChildModel() )->GetAbsolutePath();

				m_SymbolName =
					dynamic_cast<ZDProcessGraphModelMdl*>( ( (ZBSymbol*)pSelectedSymbol )->GetChildModel() )->GetModelName();
			}
		}
		else if ( pSelectedSymbol && ISA( pSelectedSymbol, ZBLinkSymbol ) )
		{
			// If the check must be done by runtime class
			if ( m_pSelectableClass )
			{
				if ( pSelectedSymbol && pSelectedSymbol->IsKindOf( m_pSelectableClass ) )
				{
					Enable = true;
				}
			}
			else if ( m_SelectableItem & Selectable_LinkSymbol )
			{
				Enable = true;
			}

			m_SymbolPath = ( (ZBLinkSymbol*)pSelectedSymbol )->GetAbsolutePath();
			m_SymbolName = ( (ZBLinkSymbol*)pSelectedSymbol )->GetSymbolName();
		}
		else if ( !pSelectedSymbol )
		{
			if ( !m_pSelectableClass &&
				 m_SymbolTree.IsDocumentSelected() &&
				 ( m_SelectableItem & Selectable_Document ) )
			{
				Enable = true;
			}

			if ( !m_pSelectableClass &&
				 m_SymbolTree.IsRootSelected() &&
				 ( m_SelectableItem & Selectable_RootModel ) )
			{
				Enable = true;
			}
		}
	}

	UpdateData( FALSE );

	// Enable or not the ok button
	if ( GetDlgItem( IDOK ) )
	{
		GetDlgItem(IDOK)->EnableWindow( Enable );
	}

	*pResult = 0;
}

void ZVSelectModelSymbolDlg::OnContextMenu( CWnd* pWnd, CPoint point )
{
	if ( m_SymbolTree.HasContextMenu( pWnd, point ) != -1 )
	{
		m_SymbolTree.DisplayContextMenu( pWnd, point );

		// Done
		return;
	}
}

BOOL ZVSelectModelSymbolDlg::OnInitDialog()
{
	ZIDialog::OnInitDialog();

	if ( m_pModel )
	{
		ZBModelSet DocumentModelSet;
		DocumentModelSet.AddModel( m_pModel );
		m_SymbolTree.Initialize( _T( "Document" ), &DocumentModelSet, IDB_IL_BP_SYMBOLS, m_pSet );
	}

	if ( !m_Title.IsEmpty() )
	{
		SetWindowText( m_Title );
	}

	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}
