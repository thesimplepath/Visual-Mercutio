// ZDUserEntityDocument.cpp : implementation file

#include "stdafx.h"
#include "ZDUserEntityDocument.h"

#include "zBaseLib\ZUGUID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 20 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZDUserEntityDocument

IMPLEMENT_DYNCREATE( ZDUserEntityDocument, ZDBaseDocument )

BEGIN_MESSAGE_MAP( ZDUserEntityDocument, ZDBaseDocument )
	//{{AFX_MSG_MAP(ZDUserEntityDocument)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZDUserEntityDocument::ZDUserEntityDocument()
	: m_IsLoaded	( false ),
	  m_Beta1Format	( false )
{
	m_GUID = ZUGUID::CreateNewGUID();
}

ZDUserEntityDocument::~ZDUserEntityDocument()
{
}

BOOL ZDUserEntityDocument::OnNewDocument()
{
	ASSERT( FALSE );
	return FALSE;
}

bool ZDUserEntityDocument::ReadFromFile( const CString Filename )
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
		// If we fail to load the file, then try to
		// load the Beta 1 format
		m_Beta1Format = true;
	}
	END_CATCH

	loadArchive.Close();
	file.Close();

	if ( m_Beta1Format )
	{
		if ( !file.Open( Filename, CFile::modeRead | CFile::shareDenyWrite, &fe ) )
		{
			return FALSE;
		}

		CArchive loadArchiveBeta1( &file, CArchive::load | CArchive::bNoFlushOnDelete );

		loadArchiveBeta1.m_pDocument	= this;
		loadArchiveBeta1.m_bForceFlat	= FALSE;

		TRY
		{
			Serialize( loadArchiveBeta1 );
			RetValue = TRUE;
		}
		CATCH( CArchiveException, e )
		{
			RetValue = FALSE;
		}
		END_CATCH

		// Close all files
		loadArchiveBeta1.Close();
		file.Close();
	}

	// If everything is ok, set the pathname.
	if ( RetValue )
	{
		SetPathName( Filename, FALSE );
	}

	// Set IsLoaded member
	m_IsLoaded = ( RetValue ) ? true : false;

	return RetValue;
}

bool ZDUserEntityDocument::SaveToFile( const CString Filename )
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
// ZDUserEntityDocument diagnostics

#ifdef _DEBUG
void ZDUserEntityDocument::AssertValid() const
{
	ZDBaseDocument::AssertValid();
}

void ZDUserEntityDocument::Dump( CDumpContext& dc ) const
{
	ZDBaseDocument::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDUserEntityDocument serialization

void ZDUserEntityDocument::Serialize( CArchive& ar )
{
	// If we don't have a beta 1 format and we are reading the file
	if ( ( ar.IsLoading() && !IsBeta1Format() ) || ar.IsStoring() )
	{
		// Serialize stamp and base information.
		ZDBaseDocument::Serialize( ar );
	}

	// Serialize the environement
	m_UserGroupEnvironment.Serialize( ar );

	// If some other information to serialize do it below
	if ( ar.IsStoring() )
	{
		ar << m_GUID;
	}
	else if ( !IsBeta1Format() )
	{
		ar >> m_GUID;
	}
}
