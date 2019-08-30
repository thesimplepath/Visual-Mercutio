/****************************************************************************
 * ==> PSS_TemplateManager -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a template manager                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_TemplateManager.h"

// mfc
#ifndef _WIN32
    #include <ver.h>
#else
    #include <WinVer.h>
#endif

// windows
#include <direct.h> 
#include <dos.h>

//---------------------------------------------------------------------------
// PSS_TemplateManager
//---------------------------------------------------------------------------
PSS_TemplateManager::PSS_TemplateManager()
{}
//---------------------------------------------------------------------------
PSS_TemplateManager::PSS_TemplateManager(const CString& rootDirectory, const CString& fileExtension)
{
    Create(rootDirectory, fileExtension);
}
//---------------------------------------------------------------------------
PSS_TemplateManager::PSS_TemplateManager(const PSS_TemplateManager& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_TemplateManager::~PSS_TemplateManager()
{
    FreeList();
}
//---------------------------------------------------------------------------
const PSS_TemplateManager& PSS_TemplateManager::operator = (const PSS_TemplateManager& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_TemplateManager::Create(const CString& rootDirectory, const CString& fileExtension)
{
    // assign the root directory
    m_RootDirectory = rootDirectory;

    // assign the extension type
    m_FileExtension = fileExtension;

    return Scan();
}
//---------------------------------------------------------------------------
BOOL PSS_TemplateManager::Scan()
{
    // free the template dir list
    m_TemplateDirList.RemoveAll();

    // free the list
    FreeList();

    #ifndef _WIN32
        // scan the root directory, and its sub-directories
        char     drive   [_MAX_DRIVE];
        char     dir     [_MAX_DIR];
        char     fileName[_MAX_FNAME];
        char     ext     [_MAX_EXT];
        unsigned oldDrive;
        unsigned numberOfDrives;

        // keep the current drive    
        ::_dos_getdrive(&oldDrive);

        // search the files from the current directory
        ::_splitpath(m_RootDirectory, drive, dir, fileName, ext);
        ::_dos_setdrive(((unsigned)*drive) - 'A' + 1, &numberOfDrives);
        ::chdir(m_RootDirectory);
    #else
        char currentDir[300];
        GetCurrentDirectory(sizeof(currentDir), currentDir);
        SetCurrentDirectory(m_RootDirectory);
    #endif

    // create a page for the root directory
    CString rootTitle(GetRootCaption());

    // add the title to the template dir list
    m_TemplateDirList.Add(rootTitle);

    // add the template dir
    std::unique_ptr<PSS_TemplateDir> pDir(new PSS_TemplateDir(m_RootDirectory, rootTitle, m_FileExtension));
    m_TemplateList.Add(pDir.get());
    pDir.release();

    #ifndef _WIN32
        struct find_t fileInfo;

        // search for subdirectories
        if (!::_dos_findfirst("*.*", _A_SUBDIR, &fileInfo))
            do
            {
                if ((fileInfo.attrib & 0x10) != 0x00)
                    if ((std::strcmp(fileInfo.name, ".")  != 0) && (std::strcmp(fileInfo.name, "..") != 0))
                    {
                        // add the title to the template dir list
                        m_TemplateDirList.Add(fileInfo.name);

                        // add the TemplateDir
                        std::unique_ptr< PSS_TemplateDir> pSubDir(new PSS_TemplateDir(m_RootDirectory + "\\" + fileInfo.name,
                                                                                      fileInfo.name,
                                                                                      m_FileExtension));
                        m_TemplateList.Add(pSubDir.get());
                        pSubDir.release();
                    }
            }
            while (!::_dos_findnext(&fileInfo));

        // restore the previous drive
        ::_dos_setdrive(oldDrive, &numberOfDrives);
    #else
        WIN32_FIND_DATA fileInfo;
        HANDLE          hFile;

        // search for sub-directories
        if ((hFile = ::FindFirstFile("*.*", &fileInfo)) != INVALID_HANDLE_VALUE)
            do
            {
                if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    if ((std::strcmp(fileInfo.cFileName, ".") != 0) && (std::strcmp(fileInfo.cFileName, "..") != 0))
                    {
                        // add the title to the template dir list
                        m_TemplateDirList.Add(fileInfo.cFileName);

                        // add the TemplateDir
                        std::unique_ptr<PSS_TemplateDir> pSubDir(new PSS_TemplateDir(m_RootDirectory + "\\" + fileInfo.cFileName,
                                                                                     fileInfo.cFileName,
                                                                                     m_FileExtension));
                        m_TemplateList.Add(pSubDir.get());
                        pSubDir.release();
                    }
            }
            while (::FindNextFile(hFile, &fileInfo));

        // restore initial directory
        SetCurrentDirectory(currentDir);
    #endif

    return m_TemplateList.GetSize() > 0;
}
//---------------------------------------------------------------------------
PSS_TemplateDir* PSS_TemplateManager::FindTemplateDir(const CString& templateDir)
{
    const int templateCount = m_TemplateList.GetSize();

    // itherate through the list and find the right templatedir
    for (int i = 0; i < templateCount; ++i)
    {
        PSS_TemplateDir* pDir = static_cast<PSS_TemplateDir*>(m_TemplateList[i]);

        if (pDir && !pDir->GetTitle().CompareNoCase(templateDir))
            return pDir;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_TemplateFile* PSS_TemplateManager::FindTemplate(const CString& templateName)
{
    // iterate through the list and find the right template name
    PSS_TemplateFile* pTmplFile;

    const int templateCount = m_TemplateList.GetSize();

    for (int i = 0; i < templateCount; ++i)
        if ((pTmplFile = ((PSS_TemplateDir*)(m_TemplateList[i]))->FindTitle(templateName)) != NULL)
            return pTmplFile;

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_TemplateManager::GetRootCaption()
{
    CString rootTitle;
    rootTitle.LoadString(IDS_ROOTTEMPLATETITLE);

    return rootTitle;
}
//---------------------------------------------------------------------------
BOOL PSS_TemplateManager::MoveTemplateFile(const CString& fileName,
                                           const CString& sourceTemplateDir,
                                           const CString& destinationTemplateDir)
{
    // search the source template
    PSS_TemplateDir* pSource = FindTemplateDir(sourceTemplateDir);

    if (!pSource)
        return FALSE;

    // search the file in the source template
    PSS_TemplateFile* pFile = pSource->FindFile(fileName);

    if (!pFile)
        return FALSE;

    // search the destination template
    PSS_TemplateDir* pDestination = FindTemplateDir(destinationTemplateDir);

    if (!pDestination)
        return FALSE;

    // call the basic function
    return MoveTemplateFile(*pFile, *pSource, *pDestination);
}
//---------------------------------------------------------------------------
BOOL PSS_TemplateManager::MoveTemplateFile(PSS_TemplateFile& file,
                                           PSS_TemplateDir&  sourceTemplateDir,
                                           PSS_TemplateDir&  destinationTemplateDir)
{
    // extract the file name
    char drive   [_MAX_DRIVE];
    char dir     [_MAX_DIR];
    char fnBuffer[_MAX_FNAME];
    char ext     [_MAX_EXT];
    ::_splitpath((const char*)file.GetFileName(), drive, dir, fnBuffer, ext);

    CString fileName;
    fileName  = fnBuffer;
    fileName += ext;

    // buffer is in an array for further use with VerFindFile
    char temp       [_MAX_PATH];
    char previousVer[_MAX_PATH];
    UINT previousVerLen = sizeof(previousVer);
    UINT len            = sizeof(temp);

    #ifndef _WIN32
        ::VerFindFile(VFFF_ISSHAREDFILE,
                      (const char*)fileName,
                      (const char*)sourceTemplateDir.GetDirectory(),
                      (const char*)sourceTemplateDir.GetDirectory(),
                      temp,
                      &len,
                      previousVer,
                      &previousVerLen);
    #else
        ::VerFindFile(VFFF_ISSHAREDFILE,
                      const_cast<char*>(static_cast<const char*>(fileName)),
                      const_cast<char*>(static_cast<const char*>(sourceTemplateDir.GetDirectory())),
                      const_cast<char*>(static_cast<const char*>(sourceTemplateDir.GetDirectory())),
                      temp,
                      &len,
                      previousVer,
                      &previousVerLen);
    #endif

    #ifndef _WIN32
        const DWORD result = ::VerInstallFile(VIFF_FORCEINSTALL,
                                              (const char*)fileName,
                                              (const char*)fileName,
                                              (const char*)sourceTemplateDir.GetDirectory(),
                                              (const char*)destinationTemplateDir.GetDirectory(),
                                              previousVer,
                                              temp,
                                              &len);
    #else
        const DWORD result = ::VerInstallFile(VIFF_FORCEINSTALL,
                                              const_cast<char*>(static_cast<const char*>(fileName)),
                                              const_cast<char*>(static_cast<const char*>(fileName)),
                                              const_cast<char*>(static_cast<const char*>(sourceTemplateDir.GetDirectory())),
                                              const_cast<char*>(static_cast<const char*>(destinationTemplateDir.GetDirectory())),
                                              previousVer,
                                              temp,
                                              &len);
    #endif

    switch (result)
    {
        case VIF_FILEINUSE:
        case VIF_TEMPFILE:
        case VIF_CANNOTREADSRC:
        case VIF_CANNOTCREATE:
            return FALSE;
    }

    // once the file is moved, delete it
    CFile::Remove(file.GetFileName());

    // refresh the whole list
    return Scan();
}
//---------------------------------------------------------------------------
void PSS_TemplateManager::FreeList()
{
    const int templateCount = m_TemplateList.GetSize();

    // delete all allocated file objects
    for (int i = 0; i < templateCount; ++i)
        delete m_TemplateList[i];

    m_TemplateList.RemoveAll();
}
//---------------------------------------------------------------------------
