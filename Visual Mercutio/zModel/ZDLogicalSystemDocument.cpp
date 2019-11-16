// ZDLogicalSystemDocument.cpp : implementation file
//

#include "stdafx.h"
#include "ZDLogicalSystemDocument.h"

#include "zBaseLib\PSS_GUID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 14 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZDLogicalSystemDocument

IMPLEMENT_DYNCREATE(ZDLogicalSystemDocument, PSS_BaseDocument)

BEGIN_MESSAGE_MAP(ZDLogicalSystemDocument, PSS_BaseDocument)
    //{{AFX_MSG_MAP(ZDLogicalSystemDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZDLogicalSystemDocument::ZDLogicalSystemDocument()
    : m_IsLoaded( false )
{
    m_GUID = PSS_GUID::CreateNewGUID();
}

ZDLogicalSystemDocument::~ZDLogicalSystemDocument()
{
}

BOOL ZDLogicalSystemDocument::OnNewDocument()
{
    ASSERT( FALSE );
    return FALSE;
}

bool ZDLogicalSystemDocument::ReadFromFile( const CString fileName)
{
    bool            RetValue = false;
    CFile            file;
    CFileException    fe;

    if ( !file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe ) )
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
        SetPathName(fileName, FALSE );
    }

    // Set IsLoaded member
    m_IsLoaded = ( RetValue ) ? true : false;

    return RetValue;
}

bool ZDLogicalSystemDocument::SaveToFile( const CString fileName)
{
    bool            RetValue = false;
    CFile            file;
    CFileException    fe;

    if ( !file.Open(fileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite, &fe ) )
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
// ZDLogicalSystemDocument diagnostics

#ifdef _DEBUG
void ZDLogicalSystemDocument::AssertValid() const
{
    ZDBaseDocument::AssertValid();
}

void ZDLogicalSystemDocument::Dump( CDumpContext& dc ) const
{
    ZDBaseDocument::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDLogicalSystemDocument serialization

void ZDLogicalSystemDocument::Serialize( CArchive& ar )
{
    // Serialize stamp and base information.
    PSS_BaseDocument::Serialize(ar);

    // Serialize the environement
    m_LogicalSystemEnvironment.Serialize( ar );

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
