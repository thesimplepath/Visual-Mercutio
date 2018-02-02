// ZDWorkspaceEnvDocument.cpp : implementation file

#include "stdafx.h"
#include "ZDWorkspaceEnvDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 18 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZDWorkspaceEnvDocument

IMPLEMENT_DYNCREATE( ZDWorkspaceEnvDocument, CDocument )

BEGIN_MESSAGE_MAP( ZDWorkspaceEnvDocument, CDocument )
	//{{AFX_MSG_MAP(ZDWorkspaceEnvDocument)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZDWorkspaceEnvDocument::ZDWorkspaceEnvDocument()
	: m_IsLoaded( false )
{
}

BOOL ZDWorkspaceEnvDocument::OnNewDocument()
{
	ASSERT( FALSE );
	return FALSE;
}

ZDWorkspaceEnvDocument::~ZDWorkspaceEnvDocument()
{
}

bool ZDWorkspaceEnvDocument::ReadFromFile( const CString Filename )
{
	bool			RetValue = false;
	CFile			file;
	CFileException	fe;

	if ( !file.Open( Filename, CFile::modeRead | CFile::shareDenyWrite, &fe ) )
	{
		return FALSE;
	}

	CArchive loadArchive( &file, CArchive::load | CArchive::bNoFlushOnDelete );

	loadArchive.m_pDocument		= this;
	loadArchive.m_bForceFlat	= FALSE;

	TRY
	{
		Serialize( loadArchive );
		RetValue = TRUE;
	}
	CATCH( CArchiveException, e )
	{
		RetValue = FALSE;
	}
	END_CATCH

	loadArchive.Close();
	file.Close();

	// If everything is ok, set the pathname.
	if ( RetValue )
	{
		SetPathName( Filename, FALSE );
	}

	// Set IsLoaded member
	m_IsLoaded = ( RetValue ) ? true : false;
	return RetValue;
}

bool ZDWorkspaceEnvDocument::SaveToFile( const CString Filename )
{
	bool			RetValue = false;
	CFile			file;
	CFileException	fe;

	if ( !file.Open( Filename, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite, &fe ) )
	{
		return FALSE;
	}

	CArchive saveArchive( &file, CArchive::store | CArchive::bNoFlushOnDelete );

	saveArchive.m_pDocument		= this;
	saveArchive.m_bForceFlat	= FALSE;

	TRY
	{
		Serialize( saveArchive );
		RetValue = TRUE;
	}
	CATCH( CArchiveException, e )
	{
		RetValue = FALSE;
	}
	END_CATCH

	saveArchive.Close();
	file.Close();

	// After a save, clear the modified flag
	SetModifiedFlag( FALSE );
	return RetValue;
}

/////////////////////////////////////////////////////////////////////////////
// ZDWorkspaceEnvDocument diagnostics

#ifdef _DEBUG
void ZDWorkspaceEnvDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void ZDWorkspaceEnvDocument::Dump( CDumpContext& dc ) const
{
	CDocument::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDWorkspaceEnvDocument serialization

void ZDWorkspaceEnvDocument::Serialize( CArchive& ar )
{
	// Serialize the environement
	m_WorkspaceEnvironment.Serialize( ar );

	// If some other information to serialize do it below
	if ( ar.IsStoring() )
	{
		// TODO: add storing code here
	}
	else
	{
		// After having read the document structure,
		// check if the project has been moved
	}
}
