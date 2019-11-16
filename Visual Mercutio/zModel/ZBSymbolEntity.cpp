// ZBSymbolEntity.cpp: implementation of the ZBSymbolEntity class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBSymbolEntity.h"

#include "ZBSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

IMPLEMENT_SERIAL(ZBSymbolEntity, CObject, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBSymbolEntity::ZBSymbolEntity()
{
}

ZBSymbolEntity::ZBSymbolEntity( const ZBSymbolEntity &right )
{
    *this = right;
}

ZBSymbolEntity::~ZBSymbolEntity()
{
}

const ZBSymbolEntity& ZBSymbolEntity::operator=( const ZBSymbolEntity &right )
{
    m_SymbolStamp = right.m_SymbolStamp;

    m_Image.CopyImage( const_cast<SECJpeg*>( &( right.m_Image ) ) );
    m_pSymbol = dynamic_cast<ZBSymbol*>( right.m_pSymbol->Dup() );

    return *this;
}

ZBSymbolEntity* ZBSymbolEntity::Clone()
{
    ZBSymbolEntity* pNewObject = new ZBSymbolEntity( *this );
    return pNewObject;
}

BOOL ZBSymbolEntity::ReadFromFile( CString fileName)
{
    BOOL            RetValue = TRUE;
    CFile            file;
    CFileException    fe;

    if ( !file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe ) )
    {
        return FALSE;
    }

    // Create the archive
    CArchive loadArchive( &file, CArchive::load | CArchive::bNoFlushOnDelete );

    loadArchive.m_pDocument = NULL;
    loadArchive.m_bForceFlat = FALSE;

    TRY
    {
        Serialize( loadArchive );
    }
    CATCH( CArchiveException, e )
    {
        loadArchive.Close();
        file.Close();
        return FALSE;
    }
    END_CATCH

    // Now close the archive
    loadArchive.Close();
    file.Close();

    return RetValue;
}

BOOL ZBSymbolEntity::WriteToFile( CString fileName)
{
    CFile            file;
    CFileException    fe;

    // Now write the new stamp
    if ( !file.Open(fileName, CFile::modeWrite | CFile::shareDenyWrite, &fe ) )
    {
        return FALSE;
    }

    // Create the save archive
    CArchive saveArchive( &file, CArchive::store | CArchive::bNoFlushOnDelete );

    saveArchive.m_pDocument = NULL;
    saveArchive.m_bForceFlat = FALSE;

    TRY
    {
        Serialize( saveArchive );
    }
    CATCH( CArchiveException, e )
    {
        saveArchive.Close();
        file.Close();
        return FALSE;
    }
    END_CATCH

    saveArchive.Flush();

    // Close the file and the archive
    saveArchive.Close();
    file.Close();

    return TRUE;
}

void ZBSymbolEntity::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        ar << m_SymbolStamp;
        ar << m_pSymbol;
    }
    else
    {
        ar >> m_SymbolStamp;
        ar >> m_pSymbol;
    }

    m_Image.Serialize( ar );
}
