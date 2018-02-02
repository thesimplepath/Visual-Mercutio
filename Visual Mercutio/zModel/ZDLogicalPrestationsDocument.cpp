// ******************************************************************************************************************
// *										Classe ZDLogicalPrestationsDocument										*
// ******************************************************************************************************************
// * JMR-MODIF - Le 7 octobre 2005 - Ajout de la classe ZDLogicalPrestationsDocument.								*
// ******************************************************************************************************************
// * Cette classe représente le document utilisé pour gérer le groupe des prestations.								*
// ******************************************************************************************************************

#include "stdafx.h"
#include "ZDLogicalPrestationsDocument.h"

#include "zBaseLib\ZUGUID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( ZDLogicalPrestationsDocument, ZDBaseDocument )

BEGIN_MESSAGE_MAP( ZDLogicalPrestationsDocument, ZDBaseDocument )
	//{{AFX_MSG_MAP(ZDPrestationsDocument)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZDLogicalPrestationsDocument::ZDLogicalPrestationsDocument()
	: m_IsLoaded( false )
{
	m_GUID = ZUGUID::CreateNewGUID();
}

ZDLogicalPrestationsDocument::~ZDLogicalPrestationsDocument()
{
}

BOOL ZDLogicalPrestationsDocument::OnNewDocument()
{
	ASSERT( FALSE );
	return FALSE;
}

bool ZDLogicalPrestationsDocument::ReadFromFile( const CString Filename )
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

bool ZDLogicalPrestationsDocument::SaveToFile( const CString Filename )
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
// ZDPrestationsDocument diagnostics

#ifdef _DEBUG
void ZDLogicalPrestationsDocument::AssertValid() const
{
	ZDBaseDocument::AssertValid();
}

void ZDLogicalPrestationsDocument::Dump( CDumpContext& dc ) const
{
	ZDBaseDocument::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDPrestationsDocument serialization

void ZDLogicalPrestationsDocument::Serialize( CArchive& ar )
{
	// Serialize stamp and base information.
	ZDBaseDocument::Serialize( ar );

	// Serialize the environement
	m_PrestationsEnvironment.Serialize( ar );

	// If some other information to serialize do it below
	if ( ar.IsStoring() )
	{
		ar << m_GUID;
	}
	else
	{
		ar >> m_GUID;
	}
}
