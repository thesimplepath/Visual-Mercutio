// ******************************************************************************************************************
// *                                   Classe ZDLogicalRulesDocument                                                *
// ******************************************************************************************************************
// * JMR-MODIF - Le 15 novembre 2006 - Ajout de la classe ZDLogicalRulesDocument.                                    *
// ******************************************************************************************************************
// * Cette classe représente le document utilisé pour gérer le groupe des règles.                                    *
// ******************************************************************************************************************

#include "stdafx.h"
#include "ZDLogicalRulesDocument.h"

#include "zBaseLib\PSS_GUID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(ZDLogicalRulesDocument, PSS_BaseDocument)

BEGIN_MESSAGE_MAP(ZDLogicalRulesDocument, PSS_BaseDocument)
    //{{AFX_MSG_MAP(ZDRulesDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZDLogicalRulesDocument::ZDLogicalRulesDocument()
    : m_IsLoaded( false )
{
    m_GUID = PSS_GUID::CreateNewGUID();
}

ZDLogicalRulesDocument::~ZDLogicalRulesDocument()
{
}

BOOL ZDLogicalRulesDocument::OnNewDocument()
{
    ASSERT( FALSE );
    return FALSE;
}

bool ZDLogicalRulesDocument::ReadFromFile( const CString fileName)
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

bool ZDLogicalRulesDocument::SaveToFile( const CString fileName)
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
// ZDRulesDocument diagnostics

#ifdef _DEBUG
void ZDLogicalRulesDocument::AssertValid() const
{
    ZDBaseDocument::AssertValid();
}

void ZDLogicalRulesDocument::Dump( CDumpContext& dc ) const
{
    ZDBaseDocument::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDRulesDocument serialization

void ZDLogicalRulesDocument::Serialize( CArchive& ar )
{
    // Serialize stamp and base information.
    PSS_BaseDocument::Serialize(ar);

    // Serialize the environement
    m_RulesEnvironment.Serialize( ar );

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
