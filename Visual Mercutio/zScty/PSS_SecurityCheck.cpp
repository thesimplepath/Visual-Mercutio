/****************************************************************************
 * ==> PSS_SecurityCheck ---------------------------------------------------*
 ****************************************************************************
 * Description : Manages the security file for product key                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_SecurityCheck.h"

 // std
#ifdef _WIN32
    #include <io.h>
#endif

// processsoft
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\PSS_RegisterSetup.h"
#include "PSS_KeyFile.h"

// resources
#include "zRes32\zRes.h"

//---------------------------------------------------------------------------
// PSS_SecurityCheck
//---------------------------------------------------------------------------
PSS_SecurityCheck::PSS_SecurityCheck() :
    PSS_Security()
{}
//---------------------------------------------------------------------------
PSS_SecurityCheck::PSS_SecurityCheck(const CString& fileName,
                                     int            daysMax,
                                     int            counterMax,
                                     int            counterMin,
                                     const CString& appRegistryKey,
                                     const CString& appPID) :
    PSS_Security(fileName, appRegistryKey, appPID),
    m_DaysMax(daysMax),
    m_CounterMax(counterMax),
    m_CounterMin(counterMin)
{}
//---------------------------------------------------------------------------
PSS_SecurityCheck::~PSS_SecurityCheck()
{}
//---------------------------------------------------------------------------
BOOL PSS_SecurityCheck::Check()
{
    CString           pid;
    PSS_RegisterSetup registry;

    //  check if the product was registered
    if (registry.GetRegValue(HKEY_LOCAL_MACHINE, m_Key, m_PID, pid))
        if (!pid.IsEmpty())
        {
            CString winDir;

            // build key file name
            GetWindowsDirectory(winDir.GetBuffer(MAX_PATH), MAX_PATH);
            winDir.ReleaseBuffer();
            winDir += _T("\\winkeys.key");

            // key file exists?
            if (PSS_File::Exist(winDir))
            {
                PSS_KeyFile file(winDir);

                // check the password
                if (!file.IsKeyValid(pid))
                {
                    CString text, caption;
                    text.LoadString(IDS_PASSWORDFAILED3);
                    caption.LoadString(IDS_PASSWORDCAPTION);

                    // show error message to user
                    MessageBox(::GetDesktopWindow(), text, caption, MB_ICONSTOP);

                    return FALSE;
                }

                return TRUE;
            }
        }

    // set the product code to the registry, fail if the counter is greater
    if (GetCounterSpan() > m_CounterMax || GetError())
        return FALSE;

    // trial days exceeded?
    if (GetTimeSpan().GetDays() > m_DaysMax || GetError())
    {
        // the user can countinue to use the program if the minimun counter wasn't reached
        if (GetCounterSpan() < m_CounterMin && !GetError())
            return TRUE;

        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
const CString PSS_SecurityCheck::FindOldVersion(const CString& exeFileName)
{
    CString  fileName;
    unsigned oldDrive;

    // find a good hard drive
    #ifdef _WIN32
        CString driveType;

        // keep the current drive
        oldDrive = ::_getdrive();

        // iterate through possible drives
        for (int drive = 0; drive < 26; ++drive)
        {
            CString driveLetter;
            char*   pBuffer = NULL;

            // convert drive letter to string
            try
            {
                pBuffer = new char[18];
                
                if (!_itoa_s(drive, pBuffer, _tcslen(pBuffer), 10))
                    driveLetter = pBuffer;
            }
            catch (...)
            {
                if (pBuffer)
                    delete[] pBuffer;

                throw;
            }

            delete[] pBuffer;

            driveType  = driveLetter + 'A';
            driveType += ":\\";

            if (GetDriveType(driveType) == DRIVE_FIXED)
            {
                fileName = FindFile(exeFileName, drive);

                if (!fileName.IsEmpty())
                {
                    // restore the previous drive
                    ::_chdrive(oldDrive);

                    return fileName;
                }
            }
        }

        // Restore the previous drive
        ::_chdrive(oldDrive);
    #else
        unsigned numberOfDrives;

        // keep the current drive
        ::_dos_getdrive(&oldDrive);

        // iterate through possible drives
        for (int drive = 0; drive < 26; ++drive)
            if (GetDriveType(drive) == DRIVE_FIXED)
            {                  
                fileName = FindFile(exeFileName, drive);

                if (!fileName.IsEmpty())
                {
                    // restore the previous drive
                    ::_dos_setdrive(oldDrive, &numberOfDrives);
                    return fileName;
                }
            }

        // restore the previous drive
        ::_dos_setdrive(oldDrive, &numberOfDrives);
    #endif

    return "";
}
//---------------------------------------------------------------------------
BOOL PSS_SecurityCheck::CreateSecurityFile()
{
    return PSS_Security::Create();
}
//---------------------------------------------------------------------------
BOOL PSS_SecurityCheck::Create(const CString& fileName,
                               int            daysMax,
                               int            counterMax,
                               int            counterMin,
                               const CString& appRegistryKey,
                               const CString& appPID)
{
    SetFileName(fileName);

    if (!appRegistryKey.IsEmpty())
        m_Key = appRegistryKey;

    if (!appPID.IsEmpty())
        m_PID = appPID;

    m_DaysMax    = daysMax;
    m_CounterMax = counterMax;
    m_CounterMin = counterMin;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SecurityCheck::CheckRegistry()
{
    #ifdef _WIN32
        HKEY hkStdFileEditing;

        if (RegOpenKey(HKEY_CLASSES_ROOT, "SOFTWARE\\PlanFin\\System", &hkStdFileEditing) == ERROR_SUCCESS)
        {
            // close key and subkeys
            RegCloseKey(hkStdFileEditing);
            return FALSE;
        }
    #endif

    return TRUE;
}
//---------------------------------------------------------------------------
const CString& PSS_SecurityCheck::FindFile(const CString& fileName, int drive)
{
    // initialize the buffer that will contain the result
    m_FoundFileName = "";

    // assign the filename to search
    m_FileNameToSearch = fileName;

    CString driveLetter;
    char*   pBuffer = NULL;

    // convert drive letter to string
    try
    {
        pBuffer = new char[18];

        if (!_itoa_s(drive, pBuffer, _tcslen(pBuffer), 10))
            driveLetter = pBuffer;
    }
    catch (...)
    {
        if (pBuffer)
            delete[] pBuffer;

        throw;
    }

    delete[] pBuffer;

    CString dir  = driveLetter + 'A';
    dir         += ":\\";

    #ifdef _WIN32
        SetCurrentDirectory(dir);
    #else
        // change drive
        unsigned numberOfDrives;
        ::_dos_setdrive(drive + 1, &numberOfDrives);

        ::chdir(dir);
    #endif

    FindFileInCurrentDir();

    return m_FoundFileName;
}
//---------------------------------------------------------------------------
BOOL PSS_SecurityCheck::FindFileInCurrentDir()
{
    #ifdef _WIN32
        struct _finddata_t fileInfo;

        // Find the first file in the current directory.
        if (::_findfirst(m_FileNameToSearch, &fileInfo) == -1L)
        {
            ::_fullpath(m_FoundFileName.GetBufferSetLength(128), fileInfo.name, 128);
            m_FoundFileName.ReleaseBuffer();
            return TRUE;
        }

        long hFile;

        // search for a subdirectory. If found, move to it and call SearchDir recursively
        if ((hFile = ::_findfirst("*.*", &fileInfo)) == -1L)
        {
            if ((fileInfo.attrib & 0x10) != 0x00)
                if ((std::strcmp(fileInfo.name, ".") != 0) && (std::strcmp(fileInfo.name, "..") != 0))
                {
                    ::_chdir (fileInfo.name);
                    FindFileInCurrentDir();
                    ::_chdir ("..");
                }

            // search for additional subdirectories
            while (!::_findnext(hFile, &fileInfo))
                if ((fileInfo.attrib & 0x10) != 0x00)
                    if ((std::strcmp(fileInfo.name, ".") != 0) && (std::strcmp(fileInfo.name, "..") != 0))
                    {
                        ::_chdir(fileInfo.name);
                        FindFileInCurrentDir();
                        ::_chdir("..");
                    }
        }
    #else
        struct find_t fileInfo;

        // find the first file in the current directory.
        if (!::_dos_findfirst(m_FileNameToSearch, _A_NORMAL | _A_RDONLY | _A_HIDDEN, &fileInfo))
        {
            ::_fullpath (m_FoundFileName.GetBufferSetLength(128), fileInfo.name, 128);
            m_FoundFileName.ReleaseBuffer();
            return TRUE;
        }

        // search for a subdirectory. If found, move to it and call SearchDir recursively
        if (!::_dos_findfirst("*.*", _A_SUBDIR, &fileInfo))
        {
            if ((fileInfo.attrib & 0x10) != 0x00)
                if ((std::strcmp(fileInfo.name, ".") != 0) && (std::strcmp(fileInfo.name, "..") != 0))
                {
                    ::chdir(fileInfo.name);
                    FindFileInCurrentDir();
                    ::chdir("..");
                }
 
            // search for additional subdirectories
            while (!::_dos_findnext(&fileInfo))
                if ((fileInfo.attrib & 0x10) != 0x00)
                    if ((std::strcmp(fileInfo.name, ".") != 0) && (std::strcmp(fileInfo.name, "..") != 0))
                    {
                        ::chdir(fileInfo.name);
                        FindFileInCurrentDir();
                        ::chdir("..");
                    }
        }
    #endif

    return FALSE;
}
//---------------------------------------------------------------------------
