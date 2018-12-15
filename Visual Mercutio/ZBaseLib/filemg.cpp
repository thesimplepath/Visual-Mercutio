//## begin module%36754E690034.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36754E690034.cm

//## begin module%36754E690034.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%36754E690034.cp

//## Module: FileMg%36754E690034; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FileMg.cpp

//## begin module%36754E690034.additionalIncludes preserve=no
//## end module%36754E690034.additionalIncludes

//## begin module%36754E690034.includes preserve=yes
#include <StdAfx.h>
//## end module%36754E690034.includes

// FileMg
#include "FileMg.h"
//## begin module%36754E690034.declarations preserve=no
//## end module%36754E690034.declarations

//## begin module%36754E690034.additionalDeclarations preserve=yes
#include <dos.h>
#include <direct.h>
#include "ZDirectory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 27 juin 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZFileManager, CObject, def_Version )

//## end module%36754E690034.additionalDeclarations

// Class ZFileManager

ZFileManager::ZFileManager()
    //## begin ZFileManager::ZFileManager%.hasinit preserve=no
    //## end ZFileManager::ZFileManager%.hasinit
    //## begin ZFileManager::ZFileManager%.initialization preserve=yes
    //## end ZFileManager::ZFileManager%.initialization
{
    //## begin ZFileManager::ZFileManager%.body preserve=yes
    //## end ZFileManager::ZFileManager%.body
}

ZFileManager::~ZFileManager()
{
    //## begin ZFileManager::~ZFileManager%.body preserve=yes
    RemoveAllFiles();
    //## end ZFileManager::~ZFileManager%.body
}

void ZFileManager::AddFile( CString FileName, AttachementType Attachement )
{
    //## begin ZFileManager::AddFile%938959776.body preserve=yes
    ZFile* pFile = new ZFile( FileName, Attachement );
    AddFile( pFile );
    //## end ZFileManager::AddFile%938959776.body
}

BOOL ZFileManager::RemoveFile( int Index )
{
    //## begin ZFileManager::RemoveFile%938959777.body preserve=yes
    if ( Index < (int)GetCount() )
    {
        delete GetAt( Index );
        m_FileArray.RemoveAt( Index );

        return TRUE;
    }

    return FALSE;
    //## end ZFileManager::RemoveFile%938959777.body
}

BOOL ZFileManager::RemoveFile( ZFile* File )
{
    //## begin ZFileManager::RemoveFile%938959778.body preserve=yes
    for ( size_t i = 0; i < GetCount(); ++i )
    {
        if ( GetAt( i ) == File )
        {
            delete GetAt( i );
            m_FileArray.RemoveAt( i );

            return TRUE;
        }
    }

    return FALSE;
    //## end ZFileManager::RemoveFile%938959778.body
}

BOOL ZFileManager::RemoveFile( const CString& FileName )
{
    //## begin ZFileManager::RemoveFile%938959779.body preserve=yes
    for ( size_t i = 0; i < GetCount(); ++i )
    {
        if ( GetAt( i )->GetCompleteFileName() == FileName )
        {
            delete GetAt( i );
            m_FileArray.RemoveAt( i );

            return TRUE;
        }
    }

    return FALSE;
    //## end ZFileManager::RemoveFile%938959779.body
}

ZFile* ZFileManager::FindFile( const CString& FileName )
{
    //## begin ZFileManager::FindFile%938959780.body preserve=yes
    for ( size_t i = 0; i < GetCount(); ++i )
    {
        if ( GetAt( i )->GetCompleteFileName() == FileName )
        {
            return GetAt( i );
        }
    }

    return NULL;
    //## end ZFileManager::FindFile%938959780.body
}

ZFile* ZFileManager::FindFile( ZFile* File )
{
    //## begin ZFileManager::FindFile%938959781.body preserve=yes
    for ( size_t i = 0; i < GetCount(); ++i )
    {
        if ( GetAt( i ) == File )
        {
            return GetAt( i );
        }
    }

    return NULL;
    //## end ZFileManager::FindFile%938959781.body
}

CString ZFileManager::GetTemporaryFileName( char drive, CString prefix )
{
    //## begin ZFileManager::GetTemporaryFileName%938959782.body preserve=yes
    char szBuf[300];

#ifndef _WIN32
    if ( drive == 0 )
    {
        drive = ::GetTempDrive( 0 );
    }

    // If no prefix defined, sets it to predefined
    if ( prefix.IsEmpty() )
    {
        prefix = _T( "PLF" );
    }

    ::GetTempFileName( drive, prefix, 0, szBuf );
#else
    char szTempPath[200];

    if ( drive == 0 )
    {
        GetTempPath( sizeof( szTempPath ), szTempPath );
    }

    // If no prefix defined, sets it to predefined
    if ( prefix.IsEmpty() )
    {
        prefix = _T( "PLF" );
    }

    ::GetTempFileName( szTempPath, prefix, 0, szBuf );
#endif

    return szBuf;
    //## end ZFileManager::GetTemporaryFileName%938959782.body
}

CString ZFileManager::GetTemporaryFileName( CString path, CString prefix, CString ext )
{
    //## begin ZFileManager::GetTemporaryFileName%938959783.body preserve=yes
    // If no path, call the other GetTemporary filename
    if ( path.IsEmpty() )
    {
        return GetTemporaryFileName ( 0, prefix );
    }

    // If no prefix defined, sets it to predefined
    if ( prefix.IsEmpty() )
    {
        prefix = _T( "PLF" );
    }

    // If the extension is empty use the standard extension
    if ( ext.IsEmpty() )
    {
        ext = _T( "TMP" );
    }

#ifndef _WIN32
    // Take the drive from the path
    unsigned drive = toupper( path[0] ) - 'A' + 1;
    unsigned olddrive;
    unsigned number_of_drives;

    // Save the current drive
    _dos_getdrive( &olddrive );

    // Change to the specified drive
    _dos_setdrive( drive, &number_of_drives );

    // Change to the specified path
    _chdir( path );
#else
    char szCurrentDir[300];

    GetCurrentDirectory( sizeof( szCurrentDir ), szCurrentDir );
    path = ZDirectory::NormalizeDirectory( path );
    SetCurrentDirectory( path );
#endif

    // Search the next file
    char File[300];
    BOOL DoNotExist = FALSE;

#ifndef _WIN32
    struct _find_t    c_file;
    int                width = 8 - prefix.GetLength();

    if ( width > 0 )
    {
        for ( register double Index = 0; DoNotExist == FALSE && Index < 999999; ++Index )
        {
            if ( !ext.IsEmpty() && ext[0] == '.' )
            {
                sprintf( File,
                         _T( "%s%0*.0f%s" ),
                         (const char*)prefix,
                         width,
                         Index,
                         (const char*)ext );
            }
            else
            {
                sprintf( File,
                         _T( "%s%0*.0f.%s" ),
                         (const char*)prefix,
                         width,
                         Index,
                         (const char*)ext );
            }

            // find the first equivalent file in the specified directory
            if ( _dos_findfirst( File, _A_NORMAL, &c_file ) != 0 )
            {
                DoNotExist = TRUE;
            }
        }
    }

    // Restore initial drive
    _dos_setdrive( olddrive, &number_of_drives );
#else
    WIN32_FIND_DATA    c_file;
    int                width = 20 - prefix.GetLength();

    if ( width > 0 )
    {
        for ( register double Index = 0; DoNotExist == FALSE && Index < 999999; ++Index )
        {
            if ( !ext.IsEmpty() && ext[0] == '.' )
            {
                sprintf( File,
                         _T( "%s\\%s%0*.0f%s" ),
                         (const char*)path,
                         (const char*)prefix,
                         width,
                         Index,
                         (const char*)ext );
            }
            else
            {
                sprintf( File,
                         _T( "%s\\%s%0*.0f.%s" ),
                         (const char*)path,
                         (const char*)prefix,
                         width,
                         Index,
                         (const char*)ext );
            }

            // Find the first equivalent file in the specified directory
            if ( FindFirstFile( File, &c_file ) == INVALID_HANDLE_VALUE )
            {
                DoNotExist = TRUE;
            }
        }
    }

    // Restore initial directory
    SetCurrentDirectory( szCurrentDir );
#endif

    if ( DoNotExist )
    {
        return File;
    }

    return _T( "" );
    //## end ZFileManager::GetTemporaryFileName%938959783.body
}

CString ZFileManager::GetTemporaryPath()
{
    //## begin ZFileManager::GetTemporaryPath%938959784.body preserve=yes
    char szTempPath[200];

    GetTempPath( sizeof( szTempPath ), szTempPath );

    return szTempPath;
    //## end ZFileManager::GetTemporaryPath%938959784.body
}

// Additional Declarations

//## begin ZFileManager%37A8A55202C9.declarations preserve=yes
//## end ZFileManager%37A8A55202C9.declarations

//## Other Operations (implementation)
void ZFileManager::Serialize( CArchive& ar )
{
    //## begin ZFileManager::Serialize%938959775.body preserve=yes
    m_FileArray.Serialize( ar );
    //## end ZFileManager::Serialize%938959775.body
}

//## begin module%36754E690034.epilog preserve=yes
//## end module%36754E690034.epilog

// Detached code regions:
// WARNING: this code will be lost if code is regenerated.

#if 0
//## begin ZFileManager::Serialize%913659117.body preserve=no
//## end ZFileManager::Serialize%913659117.body

//## begin ZFileManager::AddFile%913659118.body preserve=no
//## end ZFileManager::AddFile%913659118.body

//## begin ZFileManager::RemoveFile%913659123.body preserve=no
//## end ZFileManager::RemoveFile%913659123.body

//## begin ZFileManager::RemoveFile%913659124.body preserve=no
//## end ZFileManager::RemoveFile%913659124.body

//## begin ZFileManager::RemoveFile%913659125.body preserve=no
//## end ZFileManager::RemoveFile%913659125.body

//## begin ZFileManager::FindFile%913659126.body preserve=no
//## end ZFileManager::FindFile%913659126.body

//## begin ZFileManager::FindFile%913659127.body preserve=no
//## end ZFileManager::FindFile%913659127.body

//## begin ZFileManager::GetTemporaryFileName%915901876.body preserve=no
//## end ZFileManager::GetTemporaryFileName%915901876.body

//## begin ZFileManager::GetTemporaryFileName%915901877.body preserve=no
//## end ZFileManager::GetTemporaryFileName%915901877.body
#endif