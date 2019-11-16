/****************************************************************************
 * ==> PSS_Directory -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a directory helper                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_Directory.h"

 // processsoft
#include "PSS_File.h"
#include "PSS_FindFile.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_Directory
//---------------------------------------------------------------------------
PSS_Directory::PSS_Directory()
{}
//---------------------------------------------------------------------------
PSS_Directory::~PSS_Directory()
{}
//---------------------------------------------------------------------------
BOOL PSS_Directory::CreateDirectory(const CString& directory)
{
    if (Exist(directory))
        return FALSE;

    return ::CreateDirectory(directory, NULL);
}
//---------------------------------------------------------------------------
BOOL PSS_Directory::DeleteDirectory(const CString& directory, BOOL includeContents, BOOL includeSubDirectory)
{
    if (includeContents)
        if (!DeleteFilesFromDirectory(directory))
            return FALSE;

    if (includeSubDirectory)
    {
        CFileFind finder;
        CString   filter  = NormalizeDirectory(directory) + "\\*.*";
        BOOL      working = finder.FindFile(filter);

        // if no file found, return TRUE
        if (!working)
            return TRUE;

        // iterate through files
        while (working)
        {
            working = finder.FindNextFile();

            if (finder.IsDots())
                continue;

            if (!finder.IsDirectory())
                continue;

            if (!DeleteDirectory(directory + "\\" + finder.GetFileName(), includeContents, includeSubDirectory))
                return FALSE;
        }
    }

    return RemoveDirectory(NormalizeDirectory(directory));
}
//---------------------------------------------------------------------------
BOOL PSS_Directory::DeleteFile(const CString& file)
{
    return ::DeleteFile(file);
}
//---------------------------------------------------------------------------
BOOL PSS_Directory::DeleteFilesFromDirectory(const CString& directory)
{
    BOOL    error  = FALSE;
    CString filter = NormalizeDirectory(directory) + "\\*.*";

    CFileFind finder;
    BOOL      working = finder.FindFile(filter);

    // if no file found, return TRUE
    if (!working)
        return TRUE;

    // iterate through files
    while (working)
    {
        working = finder.FindNextFile();

        if (finder.IsDots())
            continue;

        if (finder.IsDirectory())
            continue;

        if (!DeleteFile(directory + "\\" + finder.GetFileName()))
            error = TRUE;
    }

    return !error;
}
//---------------------------------------------------------------------------
BOOL PSS_Directory::CopyFile(const CString& srcFile, const CString& dstFile, BOOL overwrite)
{
    PSS_File File(srcFile);

    if (!File.Exist())
        return FALSE;

    return ::CopyFile(srcFile, dstFile, !overwrite);
}
//---------------------------------------------------------------------------
BOOL PSS_Directory::MoveFile(const CString& srcFile, const CString& dstFile, BOOL overwrite)
{
    PSS_File File(srcFile);

    if (!File.Exist())
        return FALSE;

    // copy file allowed
    DWORD flags = MOVEFILE_COPY_ALLOWED;

    // if do overwrite, set flag to allow that
    if (overwrite)
        flags |= MOVEFILE_REPLACE_EXISTING;

    return ::MoveFileEx(srcFile, dstFile, flags);
}
//---------------------------------------------------------------------------
BOOL PSS_Directory::CopyFileFromToDirectory(const CString& srcDir, const CString& dstDir, const CString& fileName, BOOL overwrite)
{
    if (!Exist(srcDir))
        return FALSE;

    if (!Exist(dstDir))
        return FALSE;

    // check if source file exists
    const CString source = NormalizeDirectory(srcDir) + "\\" + fileName;

    PSS_File File(source);

    if (!File.Exist())
        return FALSE;

    // build destination file
    const CString destination = NormalizeDirectory(dstDir) + "\\" + fileName;

    return ::CopyFile(source, destination, !overwrite);
}
//---------------------------------------------------------------------------
BOOL PSS_Directory::MoveFileFromToDirectory(const CString& srcDir,
                                            const CString& dstDir,
                                            const CString& fileName,
                                            BOOL           overwrite)
{
    if (!Exist(srcDir))
        return FALSE;

    if (!Exist(dstDir))
        return FALSE;

    // check if source file exists
    const CString source = NormalizeDirectory(srcDir) + "\\" + fileName;

    PSS_File File(source);

    if (!File.Exist())
        return FALSE;

    // build destination file
    const CString destination = NormalizeDirectory(dstDir) + "\\" + fileName;

    // copy file allowed
    DWORD flags = MOVEFILE_COPY_ALLOWED;

    // if do overwrite, set flag to allow that
    if (overwrite)
        flags |= MOVEFILE_REPLACE_EXISTING;

    return ::MoveFileEx(source, destination, flags);
}
//---------------------------------------------------------------------------
BOOL PSS_Directory::CopyAllFilesFromToDirectory(const CString& srcDir,
                                                const CString& dstDir,
                                                BOOL           overwrite,
                                                BOOL           includeSubDirectory,
                                                BOOL           createDir)
{
    if (!Exist(srcDir))
        return FALSE;

    if (!Exist(dstDir))
    {
        if (!createDir)
            return FALSE;

        if (!CreateDirectory(dstDir))
            return FALSE;
    }

    const CString filter = NormalizeDirectory(srcDir) + "\\*.*";

    CFileFind finder;
    BOOL      working = finder.FindFile(filter);

    // if no file found, return TRUE
    if (!working)
        return TRUE;

    BOOL error = FALSE;

    // iterate through files
    while (working)
    {
        working = finder.FindNextFile();

        if (finder.IsDots())
            continue;

        if (finder.IsDirectory())
        {
            // do include sub-directories?
            if (includeSubDirectory)
            {
                // build the source directory
                const CString source = NormalizeDirectory(srcDir) + "\\" + finder.GetFileName();

                // build destination directory
                const CString destination = NormalizeDirectory(dstDir) + "\\" + finder.GetFileName();

                if (!CopyAllFilesFromToDirectory(source, destination, overwrite, includeSubDirectory, createDir))
                    error = TRUE;
            }

            continue;
        }

        // build the source file
        const CString source = NormalizeDirectory(srcDir) + "\\" + finder.GetFileName();

        // build destination file
        const CString destination = NormalizeDirectory(dstDir) + "\\" + finder.GetFileName();

        if (!CopyFile(source, destination, overwrite))
            error = TRUE;
    }

    return !error;
}
//---------------------------------------------------------------------------
BOOL PSS_Directory::MoveAllFilesFromToDirectory(const CString& srcDir,
                                                const CString& dstDir,
                                                BOOL           overwrite,
                                                BOOL           includeSubDirectory,
                                                BOOL           createDir)
{
    if (!Exist(srcDir))
        return FALSE;

    if (!Exist(dstDir))
    {
        if (!createDir)
            return FALSE;

        if (!CreateDirectory(dstDir))
            return FALSE;
    }

    const CString filter = NormalizeDirectory(srcDir) + "\\*.*";

    // copy allowed files
    DWORD flags = MOVEFILE_COPY_ALLOWED;

    // if do overwrite, set flag to allow that
    if (overwrite)
        flags |= MOVEFILE_REPLACE_EXISTING;

    CFileFind finder;
    BOOL      working = finder.FindFile(filter);

    // if no file found, return TRUE
    if (!working)
        return TRUE;

    BOOL error = FALSE;

    // iterate through files
    while (working)
    {
        working = finder.FindNextFile();

        if (finder.IsDots())
            continue;

        if (finder.IsDirectory())
        {
            // do include sub-directories?
            if (includeSubDirectory)
            {
                // build the source directory
                const CString source = NormalizeDirectory(srcDir) + "\\" + finder.GetFileName();

                // build destination directory
                const CString destination = NormalizeDirectory(dstDir) + "\\" + finder.GetFileName();

                if (!MoveAllFilesFromToDirectory(source, destination, overwrite, includeSubDirectory, createDir))
                    error = TRUE;
            }

            continue;
        }

        // build the source
        const CString source = NormalizeDirectory(srcDir) + "\\" + finder.GetFileName();

        // build destination file
        const CString destination = NormalizeDirectory(dstDir) + "\\" + finder.GetFileName();

        if (!::MoveFileEx(source, destination, flags))
            error = TRUE;
    }

    return !error;
}
//---------------------------------------------------------------------------
int PSS_Directory::FindFile(const CString& filters, CStringArray& fileArray)
{
    CFileFind finder;
    BOOL      working = finder.FindFile(filters);

    // if no file found, return TRUE
    if (!working)
        return fileArray.GetSize();

    // iterate through files
    while (working)
    {
        working = finder.FindNextFile();

        if (finder.IsDots())
            continue;

        if (finder.IsDirectory())
            continue;

        fileArray.Add(finder.GetFilePath());
    }

    return fileArray.GetSize();
}
//---------------------------------------------------------------------------
int PSS_Directory::FindFile(const CString& filters, const CString& directory, CStringArray& fileArray, bool includeSubDir)
{
    PSS_FindFile findFile(fileArray);

    return findFile.FindFile(filters, directory);
}
//---------------------------------------------------------------------------
CString PSS_Directory::NormalizeDirectory(const CString& directory, bool checkFullPath)
{
    if (!directory.IsEmpty())
    {
        CString str(directory);

        // remove path end backslash, if exists
        while (str.GetAt(str.GetLength() - 1) == '\\')
            str = str.Left(str.GetLength() - 1);

        if (checkFullPath)
        {
            int index;

            while ((index = str.Find(_T("\\\\"))) != -1)
                str = str.Left(index) + str.Right(str.GetLength() - index - 1);
        }

        return str;
    }

    return directory;
}
//---------------------------------------------------------------------------
CString PSS_Directory::GetUpperDirectory(const CString& directory)
{
    const CString normalized = NormalizeDirectory(directory);
    int           position;

    // locate the previous backslash
    if ((position = normalized.ReverseFind('\\')) == -1)
        return "";

    return normalized.Left(position);
}
//---------------------------------------------------------------------------
CString PSS_Directory::GetShortDirectoryName(const CString& directory)
{
    const CString normalized = NormalizeDirectory(directory);
    int           position;

    // locate the previous backslash
    if ((position = normalized.ReverseFind('\\')) == -1)
        return "";

    return normalized.Right(normalized.GetLength() - 1 - position);
}
//---------------------------------------------------------------------------
BOOL PSS_Directory::Exist(const CString& directory)
{
    const CString currentDirectory = GetCurrentDirectory();
    const BOOL    result           = ::SetCurrentDirectory(NormalizeDirectory(directory));

    ::SetCurrentDirectory(currentDirectory);
    return result;
}
//---------------------------------------------------------------------------
CString PSS_Directory::GetCurrentDirectory()
{
    char path[MAX_PATH];

    if (!::GetCurrentDirectory(MAX_PATH - 1, path))
        return "";

    return path;
}
//---------------------------------------------------------------------------
BOOL PSS_Directory::ChangeCurrentDirectory(const CString& directory)
{
    return ::SetCurrentDirectory(directory);
}
//---------------------------------------------------------------------------
