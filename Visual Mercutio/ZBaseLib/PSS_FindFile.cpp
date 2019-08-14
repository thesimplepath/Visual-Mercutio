/****************************************************************************
 * ==> PSS_FindFile --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a helper to find files                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FindFile.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
int PSS_FindFile::m_Level = 0;
//---------------------------------------------------------------------------
// PSS_FindFile
//---------------------------------------------------------------------------
PSS_FindFile::PSS_FindFile(CStringArray& fileArray) :
    m_FoundFiles(fileArray),
    m_TranslateMessage(FALSE)
{}
//---------------------------------------------------------------------------
int PSS_FindFile::CopyFoundFileArray(CStringArray& fileArray)
{
    fileArray.RemoveAll();

    const std::size_t fileCount = m_FoundFiles.GetSize();

    for (std::size_t i = 0; i < fileCount; ++i)
        fileArray.Add(m_FoundFiles.GetAt(i));

    return fileArray.GetSize();
}
//---------------------------------------------------------------------------
int PSS_FindFile::FindFile(const CString& fileName, const CString& defaultDir)
{
    // assign the file name to search
    m_FileNameToSearch = fileName;

    // find a good hard drive
    CString  file;
    CString  defDir = defaultDir;

    m_FoundFiles.RemoveAll();

    // keep the current drive
    const unsigned oldDrive = ::_getdrive();

    // is file in one specific directory?
    if (!defDir.IsEmpty())
    {
        char drive   [_MAX_DRIVE];
        char dir     [_MAX_DIR];
        char fnBuffer[_MAX_FNAME];
        char ext     [_MAX_EXT];
        ::_splitpath(defDir, drive, dir, fnBuffer, ext);

        // change drive
        ::_chdrive(*drive - 'A' + 1);

        if (defDir.GetAt(defDir.GetLength() - 1) == '\\')
            defDir = defDir.Left(defDir.GetLength() - 1);

        if (!::chdir(defDir))
            FindFileInCurrentDir();
    }
    else
    {
        // search on every available drives
        char driveLetter[5];

        for (int i = 0; i < 26; ++i)
        {
            std::sprintf(driveLetter, "%c:", 'A' + i);

            if (::GetDriveType(driveLetter) == DRIVE_FIXED)
                FindFileInDrive(fileName, i);
        }
    }

    // restore the previous drive
    ::_chdrive(oldDrive);

    return m_FoundFiles.GetSize();
}
//---------------------------------------------------------------------------
int PSS_FindFile::ProcessMainSubDir()
{
    ++m_Level;

    // check the level to avoid stack overflow
    if (m_Level < 300)
    {
        CStringArray dirArray;
        int          size = GetMainSubDir(dirArray);

        for (int i = 0; i < size; ++i)
        {
            FindFileInCurrentDir();

            if (::chdir(dirArray[i]))
                continue;

            ProcessMainSubDir();
        }
    }

    --m_Level;
    return 0;
}
//---------------------------------------------------------------------------
int PSS_FindFile::GetMainSubDir(CStringArray& dirArray)
{
    if (!::_getcwd(m_FullPath.GetBufferSetLength(1024), 1024))
    {
        m_FullPath.ReleaseBuffer();
        return 0;
    }

    m_FullPath.ReleaseBuffer();
    dirArray.RemoveAll();

    struct ::_finddata_t fileInfo;
    long                 hFile;

    // search for a subdir. If found, change to it and call SearchDir() recursively
    if ((hFile = ::_findfirst("*.*", &fileInfo)) != -1L)
        do
        {
            MSG msg;

            if (::PeekMessage(&msg, HWND(NULL), 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            if ((fileInfo.attrib & 0x10) != 0x00)
                if (std::strcmp(fileInfo.name, ".") && std::strcmp(fileInfo.name, ".."))
                {
                    // do the full path function
                    if (m_FullPath.GetAt(m_FullPath.GetLength() - 1) == '\\')
                        m_FoundFileName = m_FullPath + fileInfo.name;
                    else
                        m_FoundFileName = m_FullPath + "\\" + fileInfo.name;

                    dirArray.Add(m_FoundFileName);
                }
        }
        while (!::_findnext(hFile, &fileInfo));

    return dirArray.GetSize();
}
//---------------------------------------------------------------------------
int PSS_FindFile::FindFileInDrive(const CString& fileName, int drive)
{
    // initialize the buffer that will contain the result
    m_FoundFileName = "";

    CString driveStr;
    char*   pBuffer = NULL;

    try
    {
        pBuffer  = new char[18];
        driveStr = ::itoa(drive, pBuffer, 10);
    }
    catch (...)
    {
        if (pBuffer)
            delete[] pBuffer;

        throw;
    }

    if (pBuffer)
        delete[] pBuffer;

    CString dir  = driveStr + 'A';
    dir         += ":\\";

    // change drive
    ::_chdrive(drive + 1);

    if (::chdir(dir))
        return 0;

    m_Level = 0;
    ProcessMainSubDir();

    return m_FoundFiles.GetSize();
}
//---------------------------------------------------------------------------
void PSS_FindFile::FindFileInCurrentDir()
{
    struct ::_finddata_t fileInfo;
    long                 hFile;

    // find the first file in the current directory
    if ((hFile = ::_findfirst(m_FileNameToSearch, &fileInfo)) != -1L)
    {
        ::_fullpath(m_FoundFileName.GetBufferSetLength(128), fileInfo.name, 128);
        m_FoundFileName.ReleaseBuffer();
        m_FoundFiles.Add(m_FoundFileName);

        // search for additional files
        while (!::_findnext(hFile, &fileInfo))
            if (!(fileInfo.attrib & _A_SUBDIR))
                if (std::strcmp(fileInfo.name, ".") && std::strcmp(fileInfo.name, ".."))
                {
                    ::_fullpath(m_FoundFileName.GetBufferSetLength(128), fileInfo.name, 128);
                    m_FoundFileName.ReleaseBuffer();
                    m_FoundFiles.Add(m_FoundFileName);
                }
    }
}
//---------------------------------------------------------------------------
BOOL PSS_FindFile::FirstSubDir(struct _finddata_t* pFileInfo)
{
    long hFile;

    // search for a subdir. If found, change to it and call SearchDir() recursively
    if ((hFile = ::_findfirst("*.*", pFileInfo)) != -1L)
        do
        {
            if ((pFileInfo->attrib & 0x10) != 0x00)
                if (std::strcmp(pFileInfo->name, ".") && std::strcmp(pFileInfo->name, ".."))
                {
                    ::_fullpath(m_FoundFileName.GetBufferSetLength(512), pFileInfo->name, 512);
                    m_FoundFileName.ReleaseBuffer();
                    VERIFY(!::chdir(pFileInfo->name));
                    return TRUE;
                }
        }
        while (!::_findnext(hFile, pFileInfo));

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_FindFile::NextSubDir(long hFile, struct ::_finddata_t* pFileInfo)
{
    if (!::_findnext(hFile, pFileInfo))
        do
        {
            if ((pFileInfo->attrib & 0x10) != 0x00)
                if (std::strcmp(pFileInfo->name, ".") && std::strcmp(pFileInfo->name, ".."))
                {
                    ::_fullpath(m_FoundFileName.GetBufferSetLength(128), pFileInfo->name, 128);
                    m_FoundFileName.ReleaseBuffer();
                    VERIFY(!::chdir(pFileInfo->name));
                    return TRUE;
                }
        }
        while (!_findnext(hFile, pFileInfo));

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_FindFile::FindFileInSubDir()
{
    struct ::_finddata_t fileInfo;
    long                 hFile;

    // search for a subdir. If found, change to it and call SearchDir() recursively
    if ((hFile = _findfirst("*.*", &fileInfo)) != -1L)
    {
        if ((fileInfo.attrib & 0x10) != 0x00)
            if (std::strcmp(fileInfo.name, ".") && std::strcmp(fileInfo.name, ".."))
                TRY
                {
                    chdir(fileInfo.name);
                    FindFileInCurrentDir();
                    chdir("..");
                }
                CATCH (CMemoryException, e)
                {
                    return FALSE;
                }
                END_CATCH

        // search for additional sub-directories
        while (!::_findnext(hFile, &fileInfo))
            if ((fileInfo.attrib & 0x10) != 0x00)
                if (std::strcmp(fileInfo.name, ".") && std::strcmp(fileInfo.name, ".."))
                    TRY
                    {
                        chdir(fileInfo.name);
                        FindFileInCurrentDir();
                        chdir("..");
                    }
                    CATCH (CMemoryException, e)
                    {
                        return FALSE;
                    }
                    END_CATCH
    }

    return FALSE;
}
//---------------------------------------------------------------------------
