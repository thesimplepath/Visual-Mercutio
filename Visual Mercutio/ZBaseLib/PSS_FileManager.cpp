/****************************************************************************
 * ==> PSS_FileManager -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file manager, i.e a list of files. Implements   *
 *               methods to copy, move, or delete files                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FileManager.h"

// windows
#include <dos.h>
#include <direct.h>

// processsoft
#include "PSS_Directory.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_FileManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_FileManager
//---------------------------------------------------------------------------
PSS_FileManager::PSS_FileManager() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_FileManager::PSS_FileManager(const PSS_FileManager& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_FileManager::~PSS_FileManager()
{
    RemoveAllFiles();
}
//---------------------------------------------------------------------------
const PSS_FileManager& PSS_FileManager::operator = (const PSS_FileManager& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_FileManager::AddFile(const CString& fileName, PSS_File::IEAttachmentType attachement)
{
    PSS_File* pFile = new PSS_File(fileName, attachement);
    AddFile(pFile);
}
//---------------------------------------------------------------------------
BOOL PSS_FileManager::RemoveFile(int index)
{
    if (index < int(GetCount()))
    {
        delete GetAt(index);
        m_FileArray.RemoveAt(index);

        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_FileManager::RemoveFile(PSS_File* pFile)
{
    const std::size_t fileCount = GetCount();

    for (std::size_t i = 0; i < fileCount; ++i)
        if (GetAt(i) == pFile)
        {
            delete GetAt(i);
            m_FileArray.RemoveAt(i);

            return TRUE;
        }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_FileManager::RemoveFile(const CString& fileName)
{
    const std::size_t fileCount = GetCount();

    for (size_t i = 0; i < fileCount; ++i)
        if (GetAt(i)->GetCompleteFileName() == fileName)
        {
            delete GetAt(i);
            m_FileArray.RemoveAt(i);

            return TRUE;
        }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_FileManager::RemoveAllFiles()
{
    const std::size_t fileCount = GetCount();

    for (std::size_t i = 0; i < fileCount; ++i)
        delete GetAt(i);

    m_FileArray.RemoveAll();
}
//---------------------------------------------------------------------------
PSS_File* PSS_FileManager::FindFile(const CString& fileName)
{
    const std::size_t fileCount = GetCount();

    for (size_t i = 0; i < fileCount; ++i)
        if (GetAt(i)->GetCompleteFileName() == fileName)
            return GetAt(i);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_File* PSS_FileManager::FindFile(PSS_File* pFile)
{
    const std::size_t fileCount = GetCount();

    for (size_t i = 0; i < fileCount; ++i)
        if (GetAt(i) == pFile)
            return GetAt(i);

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_FileManager::GetTemporaryFileName(char drive, const CString& prefix)
{
    char    buffer[300];
    CString filePrefix;

    #ifndef _WIN32
        if (!drive)
            drive = ::GetTempDrive(0);

        // if no prefix defined, set it to a pre-defined value
        if (filePrefix.IsEmpty())
            filePrefix = _T("PLF");
        else
            filePrefix = prefix;

        ::GetTempFileName(drive, filePrefix, 0, buffer);
    #else
        char tempPath[200];

        if (!drive)
            ::GetTempPath(sizeof(tempPath), tempPath);

        // if no prefix defined, set it to a pre-defined value
        if (prefix.IsEmpty())
            filePrefix = _T("PLF");
        else
            filePrefix = prefix;

        ::GetTempFileName(tempPath, filePrefix, 0, buffer);
    #endif

    return buffer;
}
//---------------------------------------------------------------------------
CString PSS_FileManager::GetTemporaryFileName(const CString& path, const CString& prefix, const CString& ext)
{
    // if no path, call the other GetTemporaryFileName() function
    if (path.IsEmpty())
        return GetTemporaryFileName(0, prefix);

    CString filePrefix;

    // if no prefix defined, set it to a pre-defined value
    if (filePrefix.IsEmpty())
        filePrefix = _T("PLF");
    else
        filePrefix = prefix;

    CString fileExt;

    // if the extension is empty, use the standard extension
    if (fileExt.IsEmpty())
        fileExt = _T("TMP");
    else
        fileExt = ext;

    #ifndef _WIN32
        // take the drive from the path
        unsigned drive = ::toupper(path[0]) - 'A' + 1;
        unsigned olddrive;
        unsigned number_of_drives;

        // save the current drive
        ::_dos_getdrive(&olddrive);

        // change to the specified drive
        ::_dos_setdrive(drive, &number_of_drives);

        // change to the specified path
        ::_chdir(path);
    #else
        char currentDir[300];

        ::GetCurrentDirectory(sizeof(currentDir), currentDir);
        const CString filePath = PSS_Directory::NormalizeDirectory(path);
        ::SetCurrentDirectory(filePath);
    #endif

    // search the next file
    char fileName[300];
    BOOL doNotExist = FALSE;

    #ifndef _WIN32
        struct ::_find_t c_file;
        int              width = 8 - filePrefix.GetLength();

        if (width > 0)
            for (register double index = 0; !doNotExist && index < 999999; ++index)
            {
                if (!fileExt.IsEmpty() && fileExt[0] == '.')
                    std::sprintf(fileName,
                                 _T("%s%0*.0f%s"),
                                 (const char*)filePrefix,
                                 width,
                                 index,
                                 (const char*)fileExt);
                else
                    std::sprintf(fileName,
                                 _T("%s%0*.0f.%s"),
                                 (const char*)filePrefix,
                                 width,
                                 index,
                                 (const char*)fileExt);

                // find the first equivalent file in the specified directory
                if (::_dos_findfirst(fileName, _A_NORMAL, &c_file))
                    doNotExist = TRUE;
            }

        // restore initial drive
        ::_dos_setdrive(olddrive, &number_of_drives);
    #else
        ::WIN32_FIND_DATA c_file;
        int               width = 20 - filePrefix.GetLength();

        if (width > 0)
            for (register double index = 0; !doNotExist && index < 999999; ++index)
            {
                if (!fileExt.IsEmpty() && fileExt[0] == '.')
                    std::sprintf(fileName,
                                 _T("%s\\%s%0*.0f%s"),
                                 (const char*)filePath,
                                 (const char*)filePrefix,
                                 width,
                                 index,
                                 (const char*)fileExt);
                else
                    std::sprintf(fileName,
                                 _T("%s\\%s%0*.0f.%s"),
                                 (const char*)filePath,
                                 (const char*)filePrefix,
                                 width,
                                 index,
                                 (const char*)fileExt);

                // find the first equivalent file in the specified directory
                if (::FindFirstFile(fileName, &c_file) == INVALID_HANDLE_VALUE)
                    doNotExist = TRUE;
            }

        // restore initial directory
        ::SetCurrentDirectory(currentDir);
    #endif

    if (doNotExist)
        return fileName;

    return _T("");
}
//---------------------------------------------------------------------------
CString PSS_FileManager::GetTemporaryPath()
{
    char tempPath[200];

    ::GetTempPath(sizeof(tempPath), tempPath);

    return tempPath;
}
//---------------------------------------------------------------------------
void PSS_FileManager::Serialize(CArchive& ar)
{
    m_FileArray.Serialize(ar);
}
//---------------------------------------------------------------------------
