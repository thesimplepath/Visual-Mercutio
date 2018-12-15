// ZDHistoricValueDocument.cpp : implementation file

#include "stdafx.h"
#include "ZDHistoricValueDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 9 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZDHistoricValueDocument

IMPLEMENT_DYNCREATE( ZDHistoricValueDocument, CDocument )

BEGIN_MESSAGE_MAP( ZDHistoricValueDocument, CDocument )
    //{{AFX_MSG_MAP(ZDHistoricValueDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZDHistoricValueDocument::ZDHistoricValueDocument()
    : m_IsLoaded( false )
{
}

BOOL ZDHistoricValueDocument::OnNewDocument()
{
    ASSERT( FALSE );
    return FALSE;
}

ZDHistoricValueDocument::~ZDHistoricValueDocument()
{
}

bool ZDHistoricValueDocument::ReadFromFile( const CString Filename )
{
    bool            RetValue = false;
    CFile            file;
    CFileException    fe;

    if ( !file.Open( Filename, CFile::modeRead | CFile::shareDenyWrite, &fe ) )
    {
        return FALSE;
    }

    CArchive loadArchive( &file, CArchive::load | CArchive::bNoFlushOnDelete );

    loadArchive.m_pDocument        = this;
    loadArchive.m_bForceFlat    = FALSE;

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

bool ZDHistoricValueDocument::SaveToFile( const CString Filename )
{
    bool            RetValue = false;
    CFile            file;
    CFileException    fe;

    if ( !file.Open( Filename, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite, &fe ) )
    {
        return FALSE;
    }

    CArchive saveArchive( &file, CArchive::store | CArchive::bNoFlushOnDelete );

    saveArchive.m_pDocument        = this;
    saveArchive.m_bForceFlat    = FALSE;

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
// ZDHistoricValueDocument diagnostics

#ifdef _DEBUG
void ZDHistoricValueDocument::AssertValid() const
{
    CDocument::AssertValid();
}

void ZDHistoricValueDocument::Dump( CDumpContext& dc ) const
{
    CDocument::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDHistoricValueDocument serialization

void ZDHistoricValueDocument::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        ar << m_HistoricValueManager;
    }
    else
    {
        ar >> m_HistoricValueManager;
    }
}
