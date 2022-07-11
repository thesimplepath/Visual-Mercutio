/****************************************************************************
 * ==> PSS_TemplateDir -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template directory                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_TemplateDir.h"

// windows
#include <direct.h>
#include <dos.h>

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_TemplateDir, CObject)
//---------------------------------------------------------------------------
// PSS_TemplateDir
//---------------------------------------------------------------------------
PSS_TemplateDir::PSS_TemplateDir() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_TemplateDir::PSS_TemplateDir(const CString& directory, const CString& title, const CString& fileExtension) :
    CObject(),
    m_FileExtension(fileExtension)
{
    Create(directory, title);
}
//---------------------------------------------------------------------------
PSS_TemplateDir::PSS_TemplateDir(const PSS_TemplateDir& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_TemplateDir::~PSS_TemplateDir()
{
    FreeList();
}
//---------------------------------------------------------------------------
const PSS_TemplateDir& PSS_TemplateDir::operator = (const PSS_TemplateDir& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_TemplateFile* PSS_TemplateDir::FindFile(const CString& fileName)
{
    const int dirListCount = m_DirectoryList.GetSize();

    // iterate through the list and tries to locate the specified file name
    for (int i = 0; i < dirListCount; ++i)
    {
        PSS_TemplateFile* pFile = static_cast<PSS_TemplateFile*>(m_DirectoryList[i]);

        if (pFile && !pFile->GetFileName().CompareNoCase(fileName))
            return pFile;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_TemplateFile* PSS_TemplateDir::FindTitle(const CString& title)
{
    const int dirListCount = m_DirectoryList.GetSize();

    // iterate through the list and tries to locate the specified file name
    for (int i = 0; i < dirListCount; ++i)
    {
        PSS_TemplateFile* pFile = static_cast<PSS_TemplateFile*>(m_DirectoryList[i]);

        if (pFile && !pFile->GetStamp().GetTitle().CompareNoCase(title))
            return pFile;
    }

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_TemplateDir::Create(const CString& directory, const CString& title)
{
    // free the file list
    m_TemplateFileList.RemoveAll();

    // save the directory and the title
    m_Directory = directory;
    m_Title     = title;

    // free the list
    FreeList();

    #ifndef _WIN32
        // scan the directory
        char     drive   [_MAX_DRIVE];
        char     dir     [_MAX_DIR];
        char     fileName[_MAX_FNAME];
        char     ext     [_MAX_EXT];
        unsigned oldDrive;
        unsigned numberOfDrives;

        // keep the current drive
        ::_dos_getdrive(&oldDrive);

        // extract and set the new drive
        ::_splitpath(directory, drive, dir, fileName, ext);
        ::_dos_setdrive(((unsigned)*drive) - 'A' + 1, &numberOfDrives);
        ::chdir(directory);
    #else
        char currentDir[300];
        GetCurrentDirectory(sizeof(currentDir), currentDir);
        SetCurrentDirectory(directory);
    #endif

    // search files from the current directory
    CString files = "*." + m_FileExtension;
    CString completeFile;

    #ifndef _WIN32
        struct find_t fileInfo;

        // search for files
        if (!::_dos_findfirst(files, _A_NORMAL | _A_RDONLY | _A_HIDDEN, &fileInfo))
            do
            {
                // build the complete file
                completeFile = directory + "\\" + fileInfo.name;

                std::unique_ptr<PSS_TemplateFile> pFile(new PSS_TemplateFile(completeFile));

                if (!pFile->IsPersistent())
                    continue;

                // add the file name to the file list
                m_TemplateFileList.Add(pFile->GetTitle());

                // add the file object to the array
                m_DirectoryList.Add(pFile.get());

                pFile.release();
            }
            while (!::_dos_findnext(&fileInfo));

        // restore the previous drive
        ::_dos_setdrive(oldDrive, &numberOfDrives);
    #else
        WIN32_FIND_DATA fileInfo;
        HANDLE          hFile;

        // search for files
        if ((hFile = ::FindFirstFile(files, &fileInfo)) != INVALID_HANDLE_VALUE)
            do
            {
                if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_NORMAL   ||
                    fileInfo.dwFileAttributes & FILE_ATTRIBUTE_READONLY ||
                    fileInfo.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN   ||
                    fileInfo.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
                {
                    // build the complete file
                    completeFile = directory + "\\" + fileInfo.cFileName;

                    std::unique_ptr<PSS_TemplateFile> pFile(new PSS_TemplateFile(completeFile));

                    if (!pFile->IsPersistent())
                        continue;

                    // add the file name to the file list
                    m_TemplateFileList.Add(pFile->GetTitle());

                    // add the file object to the array
                    m_DirectoryList.Add(pFile.get());

                    pFile.release();
                }
            }
            while (FindNextFile(hFile, &fileInfo) != 0);

        // restore initial directory
        SetCurrentDirectory(currentDir);
    #endif

    return m_DirectoryList.GetSize() > 0;
}
//---------------------------------------------------------------------------
void PSS_TemplateDir::FreeList()
{
    const int dirListCount = m_DirectoryList.GetSize();

    // free all file objects allocated
    for (int i = 0; i < dirListCount; ++i)
        delete m_DirectoryList[i];

    m_DirectoryList.RemoveAll();
}
//---------------------------------------------------------------------------
