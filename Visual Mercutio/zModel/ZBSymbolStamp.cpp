// ZBSymbolStamp.cpp: implementation of the ZBSymbolStamp class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBSymbolStamp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

IMPLEMENT_SERIAL(ZBSymbolStamp, CObject, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBSymbolStamp::ZBSymbolStamp()
    : m_SymbolVersion(1)
{
}

ZBSymbolStamp::ZBSymbolStamp( const ZBSymbolStamp &right )
{
    *this = right;
}

ZBSymbolStamp::~ZBSymbolStamp()
{
}

const ZBSymbolStamp& ZBSymbolStamp::operator=( const ZBSymbolStamp &right )
{
    m_InternalFileVersion    = right.m_InternalFileVersion;
    m_Name                    = right.m_Name;
    m_Description            = right.m_Description;
    m_ClassName                = right.m_ClassName;
    m_Category                = right.m_Category;
    m_SymbolVersion            = right.m_SymbolVersion;
    m_Author                = right.m_Author;
    m_CreationDate            = right.m_CreationDate;
    m_ModificationDate        = right.m_ModificationDate;

    return *this;
}

CArchive& operator >> ( CArchive& ar, ZBSymbolStamp& Stamp )
{
    ar >> Stamp.m_InternalFileVersion;
    ar >> Stamp.m_Name;
    ar >> Stamp.m_Description;
    ar >> Stamp.m_ClassName;
    ar >> Stamp.m_Category;
    ar >> Stamp.m_SymbolVersion;
    ar >> Stamp.m_Author;
    ar >> Stamp.m_CreationDate;
    ar >> Stamp.m_ModificationDate;

    return ar;
}

CArchive& operator << ( CArchive& ar, const ZBSymbolStamp& Stamp )
{
    ar << Stamp.m_InternalFileVersion;
    ar << Stamp.m_Name;
    ar << Stamp.m_Description;
    ar << Stamp.m_ClassName;
    ar << Stamp.m_Category;
    ar << Stamp.m_SymbolVersion;
    ar << Stamp.m_Author;
    ar << Stamp.m_CreationDate;
    ar << Stamp.m_ModificationDate;

    return ar;
}

ZBSymbolStamp* ZBSymbolStamp::Clone()
{
    ZBSymbolStamp* pNewStamp = new ZBSymbolStamp( *this );
    return pNewStamp;
}

BOOL ZBSymbolStamp::ReadFromFile( CString fileName)
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
        loadArchive >> *this;
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

BOOL ZBSymbolStamp::WriteToFile( CString fileName)
{
    ZBSymbolStamp        DummyStamp;

    // First, read bytes coming from the file.
    BOOL                RetValue = FALSE;
    UINT                EffectiveSize = 0;
    CFile                file;
    CFileException        fe;

    if ( !file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe ) )
    {
        return FALSE;
    }

    // File is now open, read the status
    CFileStatus rStatus;

    if ( !file.GetStatus( rStatus ) )
    {
        return FALSE;
    }

    // Create the archive
    CArchive loadArchive( &file, CArchive::load | CArchive::bNoFlushOnDelete );

    loadArchive.m_pDocument = NULL;
    loadArchive.m_bForceFlat = FALSE;

    TRY
    {
        loadArchive >> DummyStamp;
    }
    CATCH( CArchiveException, e )
    {
        loadArchive.Close();
        file.Close();
        return FALSE;
    }
    END_CATCH

    // Now, read the rest of the information
    void* pFileBuffer;

    // Allocate a new buffer with the file size
    pFileBuffer = malloc( (size_t)rStatus.m_size );

    if ( pFileBuffer == 0 )
    {
        return FALSE;
    }

    // Clear the buffer
    memset( pFileBuffer, 0, (size_t)rStatus.m_size );

    TRY
    {
        // Now read the information
        EffectiveSize = loadArchive.Read( pFileBuffer, (UINT)rStatus.m_size );
    }
    CATCH( CFileException, e )
    {
        if ( pFileBuffer )
        {
            delete pFileBuffer;
        }

        // Close the file and the archive
        loadArchive.Close();
        file.Close();

        return FALSE;
    }
    END_CATCH

    // Close the file and the archive
    loadArchive.Close();
    file.Close();

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
        saveArchive << *this;
    }
    CATCH( CArchiveException, e )
    {
        saveArchive.Close();
        file.Close();
        return FALSE;
    }
    END_CATCH

    TRY
    {
        // Now save the information
        saveArchive.Write( pFileBuffer, EffectiveSize );
    }
    CATCH( CFileException, e )
    {
        if ( pFileBuffer )
        {
            delete pFileBuffer;
        }

        // Close the file and the archive
        saveArchive.Close();
        file.Close();

        return FALSE;
    }
    END_CATCH

    saveArchive.Flush();

    // Close the file and the archive
    saveArchive.Close();
    file.Close();

    // Free the buffer
    if ( pFileBuffer )
    {
        delete pFileBuffer;
    }

    return TRUE;
    //## end ZBSymbolStamp::WriteToFile%939754019.body
}

DWORD ZBSymbolStamp::IncrementPublishVersionOfFile( const CString fileName)
{
    // If unable to read file, return error
    if ( !ReadFromFile(fileName) )
    {
        return -1;
    }

    // And now, write the new version to the file.
    ++m_SymbolVersion;

    // If unable to write file, return error
    if ( !WriteToFile(fileName) )
    {
        return -1;
    }

    return m_SymbolVersion;
}

DWORD ZBSymbolStamp::DecrementPublishVersionOfFile( const CString fileName)
{
    // If unable to read file, return error
    if ( !ReadFromFile(fileName) )
    {
        return -1;
    }

    // And now, write the new version to the file.
    --m_SymbolVersion;

    // If unable to write file, return error
    if ( !WriteToFile(fileName) )
    {
        return -1;
    }

    return m_SymbolVersion;
}

BOOL ZBSymbolStamp::SetPublishVersionOfFile( const CString fileName, DWORD Version )
{
    // If unable to read file, return error
    if ( !ReadFromFile(fileName) )
    {
        return FALSE;
    }

    // And now, write the new version to the file.
    m_SymbolVersion = Version;

    // If unable to write file, return error
    if ( !WriteToFile(fileName) )
    {
        return FALSE;
    }

    return m_SymbolVersion;
}

DWORD ZBSymbolStamp::GetPublishVersionOfFile( const CString fileName)
{
    // If reading the file is ok, return the publish version
    if ( ReadFromFile(fileName) )
    {
        return m_SymbolVersion;
    }

    // Otherwise, return -1;
    return -1;
}

void ZBSymbolStamp::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        ar << *this;
    }
    else
    {
        ar >> *this;
    }
}
