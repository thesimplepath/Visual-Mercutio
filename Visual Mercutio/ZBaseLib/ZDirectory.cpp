// ZDirectory.cpp: implementation of the ZDirectory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZDirectory.h"
#include "File.h"
#include "findfile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZDirectory::ZDirectory()
{

}

ZDirectory::~ZDirectory()
{

}


CString ZDirectory::NormalizeDirectory( const CString Directory, bool CheckFullPath /*= false*/ )
{
    if (!Directory.IsEmpty())
    {
        CString s(Directory);
        // If \\ at the end of path, remove it
        while (s.GetAt( s.GetLength()-1 ) == '\\')
            s = s.Left( s.GetLength()-1 );
        if (CheckFullPath)
        {
            int Index;
            while( (Index=s.Find( _T("\\\\"))) != -1)
            {
                CString sRight = s.Right( s.GetLength() - Index - 1 );
                s = s.Left( Index ) + sRight;
            }
        }
        return s;
    }
    return Directory;
}


CString    ZDirectory::GetUpperDirectory( const CString Directory )
{
    CString    Normalized = ZDirectory::NormalizeDirectory( Directory );
    int    Position;
    // Locate the previous backslash
    if ((Position=Normalized.ReverseFind( '\\' )) == -1)
        return "";
    return Normalized.Left( Position );
}

CString    ZDirectory::GetShortDirectoryName( const CString Directory )
{
    CString    Normalized = ZDirectory::NormalizeDirectory( Directory );
    int    Position;
    // Locate the previous backslash
    if ((Position=Normalized.ReverseFind( '\\' )) == -1)
        return "";
    return Normalized.Right( Normalized.GetLength() - 1 - Position );
}


BOOL ZDirectory::DeleteFile( const CString File )
{
    return ::DeleteFile( File );
}

int    ZDirectory::FindFile( const CString Filter, CStringArray& FileArray )
{
    CFileFind finder;
    BOOL bWorking = finder.FindFile( Filter );
    // If no file found, return TRUE
    if (!bWorking)
        return FileArray.GetSize();
    // Run through files
    while (bWorking)   
    {
        bWorking = finder.FindNextFile();
        if (finder.IsDots())
            continue;
        if (finder.IsDirectory())
            continue;
        FileArray.Add( finder.GetFilePath() );
    }
    return FileArray.GetSize();
}


int        ZDirectory::FindFile( const CString Filter, const CString Directory, CStringArray& FileArray, bool IncludeSubDir /*= false*/ )
{
    ZUFindFile    Find( FileArray );

    int    FoundFile = Find.FindFile( Filter, Directory );
    return FoundFile;

}

BOOL ZDirectory::CreateDirectory( const CString Directory )
{
    if (ZDirectory::Exist( Directory ))
        return FALSE;

    return ::CreateDirectory( Directory, NULL );
}

BOOL ZDirectory::DeleteDirectory( const CString Directory, BOOL IncludeContents /*= FALSE*/, BOOL IncludeSubDirectory /*= FALSE*/ )
{
    static BOOL Error = FALSE;

    if (IncludeContents)
    {
        if (!ZDirectory::DeleteFileFromDirectory( Directory ))
            return FALSE;
    }
    if (IncludeSubDirectory)
    {
        BOOL Error = FALSE;

        CString    Filter = ZDirectory::NormalizeDirectory( Directory ) + "\\*.*";

        CFileFind finder;
        BOOL bWorking = finder.FindFile( Filter );
        // If no file found, return TRUE
        if (!bWorking)
            return TRUE;
        // Run through files
        while (bWorking)   
        {
            bWorking = finder.FindNextFile();
            if (finder.IsDots())
                continue;
            if (!finder.IsDirectory())
                continue;
            if (!ZDirectory::DeleteDirectory( Directory + "\\" + finder.GetFileName(), IncludeContents, IncludeSubDirectory ))
                return FALSE;
        }
    }
    return RemoveDirectory( ZDirectory::NormalizeDirectory(Directory) );
}

BOOL ZDirectory::Exist( const CString Directory )
{
    CString    CurrentDirectory = ZDirectory::GetCurrentDirectory();

    BOOL    RetValue = ::SetCurrentDirectory( ZDirectory::NormalizeDirectory(Directory) );

    ::SetCurrentDirectory( CurrentDirectory );
    return RetValue;
}

BOOL ZDirectory::ChangeCurrentDirectory( const CString Directory )
{
    return ::SetCurrentDirectory( Directory );
}

CString ZDirectory::GetCurrentDirectory()
{
    char    szPath[MAX_PATH];

    if (::GetCurrentDirectory(MAX_PATH-1, szPath) == 0)
        return "";

    return szPath;
}



BOOL ZDirectory::DeleteFileFromDirectory(  const CString Directory )
{
    BOOL Error = FALSE;

    CString    Filter = ZDirectory::NormalizeDirectory( Directory ) + "\\*.*";

    CFileFind finder;
    BOOL bWorking = finder.FindFile( Filter );
    // If no file found, return TRUE
    if (!bWorking)
        return TRUE;
    // Run through files
    while (bWorking)   
    {
        bWorking = finder.FindNextFile();
        if (finder.IsDots())
            continue;
        if (finder.IsDirectory())
            continue;
        if (!DeleteFile( Directory + "\\" + finder.GetFileName() ))
            Error = TRUE;
    }

    return !Error;        
}



BOOL    ZDirectory::CopyFileFromToDirectory( const CString SrcDirectory, const CString DstDirectory, const CString Filename, BOOL Overwrite /*=TRUE*/ )
{
    if (!ZDirectory::Exist( SrcDirectory ))
        return FALSE;
    if (!ZDirectory::Exist( DstDirectory ))
        return FALSE;
    // Check existance source file
    CString    Source = ZDirectory::NormalizeDirectory( SrcDirectory ) + "\\";
    Source += Filename;
    ZFile    File( Source );
    if (!File.Exist())
        return FALSE;
    // Build destination file
    CString    Destination = ZDirectory::NormalizeDirectory( DstDirectory ) + "\\";
    Destination += Filename;

    return ::CopyFile( Source, Destination, !Overwrite );
}


BOOL    ZDirectory::CopyFile( const CString SrcFile, const CString DstFile, BOOL Overwrite /*=TRUE*/ )
{
    ZFile    File( SrcFile );
    if (!File.Exist())
        return FALSE;
    return ::CopyFile( SrcFile, DstFile, !Overwrite );
}

BOOL    ZDirectory::CopyAllFileFromToDirectory( const CString SrcDirectory, const CString DstDirectory, BOOL Overwrite /*=TRUE*/, BOOL IncludeSubDirectory /*= FALSE*/, BOOL CreateDir /*=FALSE*/ )
{
    if (!ZDirectory::Exist( SrcDirectory ))
        return FALSE;
    if (!ZDirectory::Exist( DstDirectory ))
    {
        if (!CreateDir)
            return FALSE;
        ZDirectory::CreateDirectory( DstDirectory );
    }

    BOOL    Error = FALSE;
    CString    Destination;
    CString    Source;
    CString    Filter = ZDirectory::NormalizeDirectory( SrcDirectory ) + "\\*.*";

    CFileFind finder;
    BOOL bWorking = finder.FindFile( Filter );
    // If no file found, return TRUE
    if (!bWorking)
        return TRUE;
    // Run through files
    while (bWorking)   
    {
        bWorking = finder.FindNextFile();
        if (finder.IsDots())
            continue;
        if (finder.IsDirectory())
        {
            // If do include sub-directory
            if (IncludeSubDirectory)
            {
                // Build the source directory
                Source = ZDirectory::NormalizeDirectory( SrcDirectory ) + "\\";
                Source += finder.GetFileName();
                // Build destination directory
                Destination = ZDirectory::NormalizeDirectory( DstDirectory ) + "\\";
                Destination += finder.GetFileName();
                if (!ZDirectory::CopyAllFileFromToDirectory( Source, Destination, Overwrite, IncludeSubDirectory, CreateDir ))
                    Error = TRUE;
            }
            continue;
        }
        // Build the source
        Source = ZDirectory::NormalizeDirectory( SrcDirectory ) + "\\";
        Source += finder.GetFileName();
        // Build destination file
        Destination = ZDirectory::NormalizeDirectory( DstDirectory ) + "\\";
        Destination += finder.GetFileName();

        if (!CopyFile( Source, Destination, Overwrite ))
            Error = TRUE;
    }

    return !Error;        
}


BOOL    ZDirectory::MoveFileFromToDirectory( const CString SrcDirectory, const CString DstDirectory, const CString Filename, BOOL Overwrite /*=TRUE*/ )
{
    if (!ZDirectory::Exist( SrcDirectory ))
        return FALSE;
    if (!ZDirectory::Exist( DstDirectory ))
        return FALSE;
    // Check existance source file
    CString    Source = ZDirectory::NormalizeDirectory( SrcDirectory ) + "\\";
    Source += Filename;
    ZFile    File( Source );
    if (!File.Exist())
        return FALSE;
    // Build destination file
    CString    Destination = ZDirectory::NormalizeDirectory( DstDirectory ) + "\\";
    Destination += Filename;
    // Copy file allowed
    DWORD    dwFlags = MOVEFILE_COPY_ALLOWED;
    // If overwrite sets, set flags for it
    if (Overwrite)
        dwFlags |= MOVEFILE_REPLACE_EXISTING;
    return MoveFileEx( Source, Destination, dwFlags );
}

BOOL    ZDirectory::MoveFile( const CString SrcFile, const CString DstFile, BOOL Overwrite /*=TRUE*/ )
{
    ZFile    File( SrcFile );
    if (!File.Exist())
        return FALSE;
    // Copy file allowed
    DWORD    dwFlags = MOVEFILE_COPY_ALLOWED;
    // If overwrite sets, set flags for it
    if (Overwrite)
        dwFlags |= MOVEFILE_REPLACE_EXISTING;
    return MoveFileEx( SrcFile, DstFile, dwFlags );
}

BOOL    ZDirectory::MoveAllFileFromToDirectory( const CString SrcDirectory, const CString DstDirectory, BOOL Overwrite /*=TRUE*/, BOOL IncludeSubDirectory /*= FALSE*/, BOOL CreateDir /*=FALSE*/ )
{
    if (!ZDirectory::Exist( SrcDirectory ))
        return FALSE;
    if (!ZDirectory::Exist( DstDirectory ))
    {
        if (!CreateDir)
            return FALSE;
        ZDirectory::CreateDirectory( DstDirectory );
    }

    BOOL    Error = FALSE;
    CString    Destination;
    CString    Source;
    CString    Filter = ZDirectory::NormalizeDirectory( SrcDirectory ) + "\\*.*";
    // Copy file allowed
    DWORD    dwFlags = MOVEFILE_COPY_ALLOWED;
    // If overwrite sets, set flags for it
    if (Overwrite)
        dwFlags |= MOVEFILE_REPLACE_EXISTING;

    CFileFind finder;
    BOOL bWorking = finder.FindFile( Filter );
    // If no file found, return TRUE
    if (!bWorking)
        return TRUE;
    // Run through files
    while (bWorking)   
    {
        bWorking = finder.FindNextFile();
        if (finder.IsDots())
            continue;
        if (finder.IsDirectory())
        {
            // If do include sub-directory
            if (IncludeSubDirectory)
            {
                // Build the source directory
                Source = ZDirectory::NormalizeDirectory( SrcDirectory ) + "\\";
                Source += finder.GetFileName();
                // Build destination directory
                Destination = ZDirectory::NormalizeDirectory( DstDirectory ) + "\\";
                Destination += finder.GetFileName();
                if (!ZDirectory::MoveAllFileFromToDirectory( Source, Destination, Overwrite, IncludeSubDirectory, CreateDir ))
                    Error = TRUE;
            }
            continue;
        }
        // Build the source
        Source = ZDirectory::NormalizeDirectory( SrcDirectory ) + "\\";
        Source += finder.GetFileName();
        // Build destination file
        Destination = ZDirectory::NormalizeDirectory( DstDirectory ) + "\\";
        Destination += finder.GetFileName();

        if (!MoveFileEx( Source, Destination, dwFlags ))
            Error = TRUE;
    }

    return !Error;        
}
