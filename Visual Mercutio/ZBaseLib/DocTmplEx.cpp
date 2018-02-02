// DocTmplEx.cpp : implementation file

#include "stdafx.h"
#include "DocTmplEx.h"

// JMR-MODIF - Le 16 octobre 2007 - Ajout de l'en-tête ZBMediator.h
#include "zMediator\ZBMediator.h"

#include <afxadv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 28 mai 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_DYNAMIC( ZDDocTemplateEx, CMultiDocTemplate )

/////////////////////////////////////////////////////////////////////////////
// ZDDocTemplateEx

ZDDocTemplateEx::ZDDocTemplateEx( UINT				nIDResource,
								  CRuntimeClass*	pDocClass,
								  CRuntimeClass*	pFrameClass,
								  CRuntimeClass*	pViewClass,
								  UINT				nMenuId,
								  UINT				nMaxMRU )
	: CMultiDocTemplate( nIDResource, pDocClass, pFrameClass, pViewClass )
{
	m_pRecentFileList	= NULL;
	m_nMenuId			= nMenuId;

	if ( m_nMenuId )
	{
		LoadStdProfileSettings( nMaxMRU );
	}
}

ZDDocTemplateEx::~ZDDocTemplateEx()
{
	CWinApp* pApp = AfxGetApp();

	if ( pApp->m_pCmdInfo == NULL ||
		 pApp->m_pCmdInfo->m_nShellCommand != CCommandLineInfo::AppUnregister )
	{
		if ( !afxContextIsDLL )
		{
			SaveStdProfileSettings();
		}
	}

	// Free recent file list
	if ( m_pRecentFileList != NULL )
	{
		delete m_pRecentFileList;
	}
}

/////////////////////////////////////////////////////////////////////////////
// ZDDocTemplateEx implementation

void ZDDocTemplateEx::AddToRecentFileList( LPCTSTR lpszPathName )
{
	ASSERT_VALID( this );
	ASSERT( lpszPathName != NULL );
	ASSERT( AfxIsValidString( lpszPathName ) );

	if ( m_pRecentFileList != NULL )
	{
		m_pRecentFileList->Add( lpszPathName );
	}
}

void ZDDocTemplateEx::LoadStdProfileSettings( UINT nMaxMRU )
{
	ASSERT_VALID( this );
	ASSERT( m_pRecentFileList == NULL );

	CString FileEntry = _T( "File%d" );
	CString FileSection;

	GetDocString( FileSection, CDocTemplate::docName );

	if ( nMaxMRU != 0 )
	{
		// Create file MRU since nMaxMRU not zero
		m_pRecentFileList = new CRecentFileList( 0, FileSection, FileEntry, nMaxMRU );
		m_pRecentFileList->ReadList();
	}
}

void ZDDocTemplateEx::SaveStdProfileSettings()
{
	ASSERT_VALID( this );

	if ( m_pRecentFileList != NULL )
	{
		m_pRecentFileList->WriteList();
	}
}

void ZDDocTemplateEx::OnUpdateRecentFileMenu( CCmdUI* pCmdUI )
{
	ASSERT_VALID( this );

	// Updating a submenu?
	if ( pCmdUI->m_pSubMenu!=NULL )
	{
		// The following inactivates the submenu when the MRU list is empty
		UINT nEnable = MF_ENABLED;

		if ( ( m_pRecentFileList==NULL )			||
			 ( m_pRecentFileList->GetSize() == 0 )	||
			 (*m_pRecentFileList)[0].IsEmpty() )
		{
			nEnable = ( MF_DISABLED | MF_GRAYED );
		}
		
		pCmdUI->m_pMenu->EnableMenuItem( pCmdUI->m_nIndex, MF_BYPOSITION | nEnable );

		return;
	}

	// No MRU files
	if ( m_pRecentFileList == NULL )
	{
		pCmdUI->Enable( FALSE );
	}
	else
	{
		m_pRecentFileList->UpdateMenu( pCmdUI );
	}
}

BOOL ZDDocTemplateEx::OnOpenRecentFile( UINT nID )
{
	ASSERT_VALID( this );
	ASSERT( m_pRecentFileList != NULL );

	ASSERT( nID >= m_nMenuId );
	ASSERT( nID < m_nMenuId + (UINT)m_pRecentFileList->GetSize() );

	int nIndex = nID - m_nMenuId;

	ASSERT( ( *m_pRecentFileList )[nIndex].GetLength() != 0 );

	TRACE2( _T( "MRU: open file (%d) '%s'.\n" ),
			( nIndex ) + 1,
			(LPCTSTR)( *m_pRecentFileList )[nIndex] );

	// ***********************************************************************************************
	// JMR-MODIF - Le 16 octobre 2007 - Modification de la routine de chargement des fichiers récents.

	/*if ( OpenDocumentFile( (*m_pRecentFileList)[nIndex] ) == NULL )
	{
		m_pRecentFileList->Remove( nIndex );
	}*/

	LPCTSTR		p_File	= (*m_pRecentFileList)[nIndex];
	CDocument*	p_Doc	= OpenDocumentFile( p_File );

	if ( p_Doc == NULL )
	{
		m_pRecentFileList->Remove( nIndex );
	}
	else
	{
		ZBMediator::Instance()->GetMainApp()->OnAfterOpenDocument( p_Doc, p_File );
	}
	// ***********************************************************************************************

	return TRUE;
}

// This hack is necessary because the menu ID is a member of the class.
// MFC message maps need the IDs to be global.
BOOL ZDDocTemplateEx::OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo )
{
	// Determine the message number and code (packed into nCode)
	UINT	nMsg = 0;
	int		nCod = nCode;

	if ( nCod != CN_UPDATE_COMMAND_UI )
	{
		nMsg = HIWORD( nCod );
		nCod = LOWORD( nCod );
	}

	// For backward compatibility HIWORD(nCode) == 0 is WM_COMMAND
	if ( nMsg == 0 )
	{
		nMsg = WM_COMMAND;
	}

	if ( ( nCod == CN_UPDATE_COMMAND_UI ) && ( nID >= m_nMenuId ) && ( nID <= m_nMenuId + MRU_RANGE ) )
	{
		// Default is ok
		BOOL bResult = TRUE;

		ASSERT( pExtra != NULL );

		CCmdUI* pCmdUI = (CCmdUI*)pExtra;

		// Idle - not set
		ASSERT( !pCmdUI->m_bContinueRouting );

		OnUpdateRecentFileMenu( pCmdUI );

		bResult = !pCmdUI->m_bContinueRouting;

		// Go back to idle
		pCmdUI->m_bContinueRouting = FALSE;

		return bResult;
	}

	if ( ( nMsg == WM_COMMAND ) && ( nCod == CN_COMMAND ) && ( nID >= m_nMenuId ) && ( nID <= m_nMenuId+MRU_RANGE ) )
	{
#ifdef _DEBUG
			if ( afxTraceFlags & traceCmdRouting )
			{
				TRACE2( _T( "SENDING command id 0x%04X to %hs target.\n" ),
						nID,
						GetRuntimeClass()->m_lpszClassName );
			}
#endif //_DEBUG

		return OnOpenRecentFile( nID );
	}

	return CMultiDocTemplate::OnCmdMsg( nID, nCode, pExtra, pHandlerInfo );
}

/////////////////////////////////////////////////////////////////////////////
// ZDDocTemplateEx diagnostics

#ifdef _DEBUG
void ZDDocTemplateEx::Dump( CDumpContext& dc ) const
{
	CMultiDocTemplate::Dump( dc );

	if ( m_pRecentFileList != NULL )
	{
		dc << _T( "\nm_strRecentFiles[] = " );

		int nSize = m_pRecentFileList->GetSize();

		for ( int i = 0; i < nSize; i++ )
		{
			if ( (*m_pRecentFileList)[i].GetLength() != 0 )
			{
				dc << _T( "\n\tFile: " ) << (*m_pRecentFileList)[i];
			}
		}
	}

	dc << _T( "\n" );
}

void ZDDocTemplateEx::AssertValid() const
{
	CMultiDocTemplate::AssertValid();
}
#endif //_DEBUG
