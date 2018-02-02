// ZVInsertModelNewPageDlg.cpp : implementation file

#include "stdafx.h"
#include "ZVInsertModelNewPageDlg.h"

#include "ProcGraphModelMdl.h"
#include "ZDProcessGraphPage.h"
#include "ZBModelSet.h"
#include "ZBSymbol.h"
#include "zBaseLib\MsgBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 3 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVInsertModelNewPageDlg dialog

BEGIN_MESSAGE_MAP( ZVInsertModelNewPageDlg, ZIDialog )
	//{{AFX_MSG_MAP(ZVInsertModelNewPageDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_EXISTINGPROCESS, OnSelchangedSymboltree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVInsertModelNewPageDlg::ZVInsertModelNewPageDlg( ZDProcessGraphModelMdl*	pModel,
												  const CString				NewPageName		/*= ""*/,
												  CStringArray*				pArrayPageName	/*= NULL*/,
												  ZBRuntimeClassSet*		pSet			/*= NULL*/,
												  CWnd*						pParent			/*=NULL*/ )
	: ZIDialog			( ZVInsertModelNewPageDlg::IDD, TRUE, pParent ),
	  m_pModel			( pModel ),
	  m_pArrayPageName	( pArrayPageName ),
	  m_pParentModel	( pModel ),
	  m_pSet			( pSet )
{
	//{{AFX_DATA_INIT(ZVInsertModelNewPageDlg)
	m_PageName = NewPageName;
	//}}AFX_DATA_INIT
}

void ZVInsertModelNewPageDlg::DoDataExchange( CDataExchange* pDX )
{
	ZIDialog::DoDataExchange( pDX );

	//{{AFX_DATA_MAP(ZVInsertModelNewPageDlg)
	DDX_Control(pDX, IDC_EXISTINGPROCESS, m_SymbolTree);
	DDX_Text(pDX, IDC_PAGENAME, m_PageName);
	//}}AFX_DATA_MAP
}

void ZVInsertModelNewPageDlg::CheckControls()
{
	ZDProcessGraphModelMdl* pParentModel = m_SymbolTree.GetSelectedOwnerModel();

	// If a page is selected, then reset the parent model
	if ( m_SymbolTree.GetSelectedPage() )
	{
		pParentModel = NULL;
	}

	if ( pParentModel )
	{
		if ( GetDlgItem( IDOK ) )
		{
			GetDlgItem( IDOK )->EnableWindow( TRUE );
		}
	}
	else
	{
		if ( GetDlgItem( IDOK ) )
		{
			GetDlgItem( IDOK )->EnableWindow( FALSE );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// ZVInsertModelNewPageDlg message handlers

void ZVInsertModelNewPageDlg::OnOK()
{
	UpdateData( TRUE );

	if ( m_PageName.IsEmpty() )
	{
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_NEWMODELPAGE_EMPTY, MB_OK );
		return;
	}

	m_pParentModel = m_SymbolTree.GetSelectedOwnerModel();

	// If a page is selected, then reset the parent model
	if ( m_SymbolTree.GetSelectedPage() )
	{
		m_pParentModel = NULL;
	}

	if ( !m_pParentModel )
	{
		MsgBox mbox;
		mbox.DisplayMsgBox( IDS_NEWMODELPAGE_EMPTY, MB_OK );
		return;
	}

	// Assigns the model pathname
	m_ParentModelFullName = m_pParentModel->GetAbsolutePath();

	// Check existence of new page name
	if ( m_pArrayPageName )
	{
		for ( int i = 0; i < m_pArrayPageName->GetSize(); ++i )
		{
			if ( m_PageName == m_pArrayPageName->GetAt( i ) )
			{
				// Display error message
				MsgBox mbox;
				mbox.DisplayMsgBox( IDS_NEWMODELPAGE_ALREADYEXIST, MB_OK );
				return;
			}
		}
	}

	ZIDialog::OnOK();
}

void ZVInsertModelNewPageDlg::OnSelchangedSymboltree( NMHDR* pNMHDR, LRESULT* pResult )
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	*pResult = 0;

	CheckControls();
}

BOOL ZVInsertModelNewPageDlg::OnInitDialog()
{
	ZIDialog::OnInitDialog();

	if ( m_pModel )
	{
		ZBModelSet DocumentModelSet;
		DocumentModelSet.AddModel( m_pModel );

		m_SymbolTree.Initialize( _T( "Document" ), &DocumentModelSet, IDB_IL_BP_SYMBOLS, m_pSet );
		m_SymbolTree.SelectItemName( m_pModel->GetModelName() );
	}

	CheckControls();

	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}
