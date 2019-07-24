/************************************************************************************************************
 *                                                    Classe ZFile                                            *
 ************************************************************************************************************
 * Cette classe fournit les outils concernant les opérations de base sur les fichiers, tels que le test de    *
 * l'existence d'un fichier, etc...                                                                            *
 ************************************************************************************************************/

//## begin module%36754E560054.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36754E560054.cm

//## begin module%36754E560054.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%36754E560054.cp

//## Module: File%36754E560054; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\File.cpp

//## begin module%36754E560054.additionalIncludes preserve=no
//## end module%36754E560054.additionalIncludes

//## begin module%36754E560054.includes preserve=yes
#include <StdAfx.h>
#include  <io.h>
//## end module%36754E560054.includes

// File
#include "File.h"
//## begin module%36754E560054.declarations preserve=no
//## end module%36754E560054.declarations

//## begin module%36754E560054.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 24 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZFile, CObject, g_DefVersion)
//## end module%36754E560054.additionalDeclarations

// Class ZFile
ZFile::ZFile()
    //## begin ZFile::ZFile%.hasinit preserve=no
    //## end ZFile::ZFile%.hasinit
    //## begin ZFile::ZFile%.initialization preserve=yes
    : m_AttachementType( InsertedFile )
    //## end ZFile::ZFile%.initialization
{
    //## begin ZFile::ZFile%.body preserve=yes
    //## end ZFile::ZFile%.body
}

ZFile::ZFile( const ZFile &right )
    //## begin ZFile::ZFile%copy.hasinit preserve=no
    //## end ZFile::ZFile%copy.hasinit
    //## begin ZFile::ZFile%copy.initialization preserve=yes
    //## end ZFile::ZFile%copy.initialization
{
    //## begin ZFile::ZFile%copy.body preserve=yes
    *this = right;
    //## end ZFile::ZFile%copy.body
}

ZFile::ZFile( CString FileName, AttachementType Attachement )
    //## begin ZFile::ZFile%933795303.hasinit preserve=no
    //## end ZFile::ZFile%933795303.hasinit
    //## begin ZFile::ZFile%933795303.initialization preserve=yes
    : m_AttachementType( Attachement ), m_FileName( FileName )
    //## end ZFile::ZFile%933795303.initialization
{
    //## begin ZFile::ZFile%933795303.body preserve=yes
    // If file:// defined, remove it
    if ( m_FileName.Left( 7 ).CompareNoCase( _T( "file://" ) ) == 0 )
    {
        m_FileName = m_FileName.Right( m_FileName.GetLength() - 7 );
    }

    _splitpath( m_FileName, m_szDrive, m_szDir, m_szFname, m_szExt );
    //## end ZFile::ZFile%933795303.body
}

ZFile::~ZFile()
{
    //## begin ZFile::~ZFile%.body preserve=yes
    //## end ZFile::~ZFile%.body
}

const ZFile & ZFile::operator=( const ZFile &right )
{
    //## begin ZFile::operator=%.body preserve=yes
    m_FileName            = right.m_FileName;
    m_AttachementType    = right.m_AttachementType;

    return *this;
    //## end ZFile::operator=%.body
}

int ZFile::operator==( const ZFile &right ) const
{
    //## begin ZFile::operator==%.body preserve=yes
    return m_FileName == right.m_FileName;
    //## end ZFile::operator==%.body
}

int ZFile::operator!=( const ZFile &right ) const
{
    //## begin ZFile::operator!=%.body preserve=yes
    return m_FileName != right.m_FileName;
    //## end ZFile::operator!=%.body
}

CArchive& operator>>( CArchive& ar, ZFile& File )
{
    //## begin ZFile::operator >>%933795312.body preserve=yes
    ar >> File.m_FileName;

    WORD wValue;
    ar >> wValue;
    File.m_AttachementType = (AttachementType)wValue;

    // Build completely all file components
    File.ReBuild();

    return ar;
    //## end ZFile::operator >>%933795312.body
}

CArchive& operator<<( CArchive& ar, ZFile& File )
{
    //## begin ZFile::operator <<%933795313.body preserve=yes
    ar << File.m_FileName;
    ar << (WORD)File.m_AttachementType;

    return ar;
    //## end ZFile::operator <<%933795313.body
}

//## Other Operations (implementation)
void ZFile::ReBuild()
{
    //## begin ZFile::ReBuild%940749602.body preserve=yes
    _splitpath( m_FileName, m_szDrive, m_szDir, m_szFname, m_szExt );
    CString s( m_szDir );

    // If \\ at the end of path, remove it
    // JMR-MODIF - Le 18 avril 2006 - Teste si la chaîne est vide avant de tenter d'extraire un caractère.
    while ( !s.IsEmpty() && s.GetAt( s.GetLength() - 1 ) == '\\' )
    {
        s = s.Left( s.GetLength() - 1 );
    }

    // Rebuild the filename
    m_FileName  = m_szDrive;
    m_FileName += s;
    m_FileName += _T( "\\" );
    m_FileName += m_szFname;
    m_FileName += m_szExt;
    //## end ZFile::ReBuild%940749602.body
}

void ZFile::SetCompleteFileName( const CString value, AttachementType Attachement )
{
    //## begin ZFile::SetCompleteFileName%933795304.body preserve=yes
    m_AttachementType    = Attachement;
    m_FileName            = value;

    _splitpath( m_FileName, m_szDrive, m_szDir, m_szFname, m_szExt );
    //## end ZFile::SetCompleteFileName%933795304.body
}

CString ZFile::GetCompleteFileName()
{
    //## begin ZFile::GetCompleteFileName%933795305.body preserve=yes
    return m_FileName;
    //## end ZFile::GetCompleteFileName%933795305.body
}

void ZFile::SetFileName( const CString value, AttachementType Attachement )
{
    //## begin ZFile::SetFileName%933795306.body preserve=yes
    m_FileName  = m_szDrive;
    m_FileName += m_szDir;
    m_FileName += value;
    //## end ZFile::SetFileName%933795306.body
}

CString ZFile::GetFileName()
{
    //## begin ZFile::GetFileName%933795307.body preserve=yes
    CString str;
    str.Format( _T( "%s%s" ), m_szFname, m_szExt );

    return str;
    //## end ZFile::GetFileName%933795307.body
}

void ZFile::SetFilePath( const CString value )
{
    //## begin ZFile::SetFilePath%933795308.body preserve=yes
    m_FileName = m_szDrive;
    m_FileName += value;
    m_FileName += m_szFname;
    m_FileName += m_szExt;
    //## end ZFile::SetFilePath%933795308.body
}

CString ZFile::GetFilePath()
{
    //## begin ZFile::GetFilePath%933795309.body preserve=yes
    CString str;
    str.Format( _T( "%s%s" ), m_szDrive, m_szDir );

    return str;
    //## end ZFile::GetFilePath%933795309.body
}

void ZFile::SetFileDrive( const char value )
{
    //## begin ZFile::SetFileDrive%933795310.body preserve=yes
    m_FileName  = value;
    m_FileName += _T( ":" );
    m_FileName += m_szDir;
    m_FileName += m_szFname;
    m_FileName += m_szExt;
    //## end ZFile::SetFileDrive%933795310.body
}

const char ZFile::GetFileDrive()
{
    //## begin ZFile::GetFileDrive%933795311.body preserve=yes
    return m_FileName[0];
    //## end ZFile::GetFileDrive%933795311.body
}

CString ZFile::GetDisplayName()
{
    //## begin ZFile::GetDisplayName%933795315.body preserve=yes
    SHFILEINFO sfi;

    ::SHGetFileInfo( m_FileName, 0, &sfi, sizeof( SHFILEINFO ), SHGFI_DISPLAYNAME );

    return sfi.szDisplayName;
    //## end ZFile::GetDisplayName%933795315.body
}

int ZFile::GetIconIndex()
{
    //## begin ZFile::GetIconIndex%933795316.body preserve=yes
    SHFILEINFO sfi;

    ::SHGetFileInfo( m_FileName, 0, &sfi, sizeof( SHFILEINFO ), SHGFI_SYSICONINDEX | SHGFI_SMALLICON );

    return sfi.iIcon;
    //## end ZFile::GetIconIndex%933795316.body
}

CString ZFile::GetFileTitle()
{
    //## begin ZFile::GetFileTitle%933795317.body preserve=yes
    return m_szFname;
    //## end ZFile::GetFileTitle%933795317.body
}

CString ZFile::GetFileExt()
{
    //## begin ZFile::GetFileExt%933795318.body preserve=yes
    return m_szExt;
    //## end ZFile::GetFileExt%933795318.body
}

CString ZFile::GetDescription()
{
    //## begin ZFile::GetDescription%933795319.body preserve=yes
    SHFILEINFO sfi;

    ::SHGetFileInfo( m_FileName, 0, &sfi, sizeof( SHFILEINFO ), SHGFI_TYPENAME );

    return sfi.szTypeName;
    //## end ZFile::GetDescription%933795319.body
}

BOOL ZFile::Exist()
{
    return ZFile::Exist( GetCompleteFileName() );
}

BOOL ZFile::Exist( CString Filename )
{
    // Check for existence
    if ( ( _access( Filename, 0 ) ) != -1 )
    {
        WIN32_FIND_DATA fd;

        CString    szFindPath    = Filename;
        int        nSlash        = szFindPath.ReverseFind( _T( '\\' ) );
        int        nLength        = szFindPath.GetLength();

        if ( nSlash == nLength - 1 )
        {
            if ( nLength == 3 )
            {
                if ( szFindPath.GetAt( 1 ) == _T( ':' ) )
                {
                    return TRUE;
                }
            }
            else
            {
                szFindPath = szFindPath.Left( nSlash );
            }
        }

        HANDLE hFind = FindFirstFile( szFindPath, &fd );

        if ( hFind != INVALID_HANDLE_VALUE )
        {
            FindClose( hFind );
        }

        return hFind != INVALID_HANDLE_VALUE;
    }

    return FALSE;
}

HANDLE ZFile::GetFileHandle( CString Filename )
{
    HANDLE hFile = CreateFile( Filename,
                               GENERIC_READ,
                               0,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL );

    if ( hFile != INVALID_HANDLE_VALUE )
    {
        return hFile;
    }

    return NULL;
}

BOOL ZFile::IsReadOnly()
{
    //## begin ZFile::IsReadOnly%941091645.body preserve=yes
    CFileStatus rStatus;
    CFile::GetStatus( GetCompleteFileName(), rStatus );

    return rStatus.m_attribute & CFile::readOnly;
    //## end ZFile::IsReadOnly%941091645.body
}

BOOL ZFile::SetReadOnly( BOOL ReadOnly )
{
    //## begin ZFile::SetReadOnly%941091646.body preserve=yes
    // First, read the file status
    CFileStatus rStatus;
    CFile::GetStatus( GetCompleteFileName(), rStatus );

    // If no need to change
    if ( ( ReadOnly == TRUE  && ( ( rStatus.m_attribute & CFile::readOnly ) == 0 ) ) ||
         ( ReadOnly == FALSE && ( ( rStatus.m_attribute & CFile::readOnly ) == 1 ) ) )
    {
        // Otherwise, sets the new file status
        if ( ReadOnly == TRUE )
        {
            rStatus.m_attribute |= CFile::readOnly;
        }
        else
        {
            rStatus.m_attribute &= ~CFile::readOnly;
        }

        TRY
        {
            CFile::SetStatus( GetCompleteFileName(), rStatus );
        }
        CATCH( CFileException, e )
        {
            return FALSE;
        }
        END_CATCH
    }

    return TRUE;
    //## end ZFile::SetReadOnly%941091646.body
}

BOOL ZFile::IsArchive()
{
    //## begin ZFile::IsArchive%941091647.body preserve=yes
    CFileStatus rStatus;
    CFile::GetStatus( GetCompleteFileName(), rStatus );

    return rStatus.m_attribute & CFile::archive;
    //## end ZFile::IsArchive%941091647.body
}

BOOL ZFile::SetArchive( BOOL Archive )
{
    //## begin ZFile::SetArchive%941091648.body preserve=yes
    // First, read the file status
    CFileStatus rStatus;
    CFile::GetStatus( GetCompleteFileName(), rStatus );

    // If no need to change
    if ( ( Archive == TRUE  && ( ( rStatus.m_attribute & CFile::archive ) == 0 ) ) ||
         ( Archive == FALSE && ( ( rStatus.m_attribute & CFile::archive ) == 1 ) ) )
    {
        // Otherwise, sets the new file status
        if ( Archive == TRUE )
        {
            rStatus.m_attribute |= CFile::archive;
        }
        else
        {
            rStatus.m_attribute &= ~CFile::archive;
        }

        TRY
        {
            CFile::SetStatus( GetCompleteFileName(), rStatus );
        }
        CATCH( CFileException, e )
        {
            return FALSE;
        }
        END_CATCH
    }

    return TRUE;
    //## end ZFile::SetArchive%941091648.body
}

BOOL ZFile::GetLastWriteTime( SYSTEMTIME& tm )
{
    return ZFile::GetLastWriteTime( GetCompleteFileName(), tm );
}

BOOL ZFile::GetLastWriteTime( CString Filename, SYSTEMTIME& tm )
{
    FILETIME ftCreate, ftAccess, ftWrite, ftLocal;

    HANDLE hFile = ZFile::GetFileHandle( Filename );

    if ( hFile == NULL )
    {
        return FALSE;
    }

    // Retrieve the file times for the file.
    if ( !GetFileTime( hFile, &ftCreate, &ftAccess, &ftWrite ) )
    {
        return FALSE;
    }

    // Convert the last-write time to local time.
    if ( !FileTimeToLocalFileTime( &ftWrite, &ftLocal ) )
    {
        return FALSE;
    }

    // Convert the local file time from UTC to system time.
    FileTimeToSystemTime( &ftLocal, &tm );

    // Close the file handle before leaving the function
    // otherwise, we have an open handle to a file and the system
    // will not be able to access the file further
    CloseHandle( hFile );

    return TRUE;
}

// Additional Declarations

//## begin ZFile%37A8A5510200.declarations preserve=yes
//## end ZFile%37A8A5510200.declarations

//## begin module%36754E560054.epilog preserve=yes
//## end module%36754E560054.epilog
