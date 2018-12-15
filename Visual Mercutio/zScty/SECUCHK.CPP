//## begin module.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module.cm

//## begin module.cp preserve=no
//## end module.cp

//## Module: SecuChk; Package body
//## Subsystem: Security Modules
//## Source file: d:\adsoft~1\zsecurit\secuchk.cpp


//## begin module.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module.additionalIncludes

//## begin module.includes preserve=yes
//## end module.includes

// SecuChk
#include "secuchk.h"

#include "zBaseLib\File.h"

#include "zBaseLib\ZBRegisterSetup.h"
// ZBKeyFile
#include "ZBKeyFile.h"

#include "zRes32\zRes.h"

//## begin module.declarations preserve=no
//## end module.declarations

//## begin module.additionalDeclarations preserve=yes
#ifdef _WIN32
#include <io.h>
#endif // _WIN32
//## end module.additionalDeclarations


// Class ZASecurityCheck 






ZASecurityCheck::ZASecurityCheck()
{
  //## begin ZASecurityCheck::ZASecurityCheck%.body preserve=yes
  //## end ZASecurityCheck::ZASecurityCheck%.body
}

ZASecurityCheck::ZASecurityCheck(const CString&  sFilename, 
                                 int iDaysMax, int iCounterMax, int iCounterMin, 
                                 const CString ApplicationRegistryKey /*= ""*/, const CString ApplicationPID /*= ""*/)
  //## begin ZASecurityCheck::ZASecurityCheck%812506910.hasinit preserve=no
  //## end ZASecurityCheck::ZASecurityCheck%812506910.hasinit
  //## begin ZASecurityCheck::ZASecurityCheck%812506910.initialization preserve=yes
: ZASecurity(sFilename, ApplicationRegistryKey, ApplicationPID), 
  m_iDaysMax(iDaysMax), m_iCounterMax(iCounterMax), m_iCounterMin(iCounterMin)
  //## end ZASecurityCheck::ZASecurityCheck%812506910.initialization
{
  //## begin ZASecurityCheck::ZASecurityCheck%812506910.body preserve=yes
  //## end ZASecurityCheck::ZASecurityCheck%812506910.body
}


ZASecurityCheck::~ZASecurityCheck()
{
  //## begin ZASecurityCheck::~ZASecurityCheck%.body preserve=yes
  //## end ZASecurityCheck::~ZASecurityCheck%.body
}



//## Other Operations (implementation)
BOOL ZASecurityCheck::Check()
{
    // First, check if the product has been register
    CString PID;
    ZBRegisterSetup Registry;
    if (Registry.GetRegValue( m_sKey, m_sPID, PID ))
    {
        if (!PID.IsEmpty())
        {
            // Check if the PID exists

            // Check if the key file exists
            CString strWndDir;
            GetWindowsDirectory(strWndDir.GetBuffer(MAX_PATH), MAX_PATH);
            strWndDir.ReleaseBuffer();

            strWndDir += _T("\\winkeys.key");
            if (ZFile::Exist( strWndDir ))
            {
                // Check the password
                ZBKeyFile File( strWndDir );
                if (!File.IsKeyValid( PID ))
                {
                    CString sText, sCaption;

                    sText.LoadString( IDS_PASSWORDFAILED3 );
                    sCaption.LoadString( IDS_PASSWORDCAPTION );
                    MessageBox( ::GetDesktopWindow(), sText, sCaption, MB_ICONSTOP );

                    return FALSE;
                }
                else
                    return TRUE;
            }
        }
    }

        // Now set the product code to the registry

      // If the counter is greater directly 
      // it is failed
      if (GetCounterSpan() > m_iCounterMax || GetbError())
          return FALSE;
    if (GetTimeSpan().GetDays() > m_iDaysMax || GetbError())
    {
        // If the user didn't reach the minimun
        // the user can countinue to use the program
        if (GetCounterSpan() < m_iCounterMin && !GetbError())
            return TRUE;
          return FALSE;
    }
    return TRUE;
  //## end ZASecurityCheck::Check%812506911.body
}

const CString ZASecurityCheck::FindOldVersion(const CString&  sExeFilename)
{
  //## begin ZASecurityCheck::FindOldVersion%812562131.body preserve=yes
    // Find a good hard drive
    CString        sFile;
    unsigned     uOldDrive;

#ifdef _WIN32
    CString    sDriveType;
    // Keep the current drive    
    uOldDrive = _getdrive();
    for( int iDrive=0 ; iDrive < 26 ; iDrive++ )
    {
        // JMR-MODIF - Le 18 mai 2005 - Conversion explicite d'un nombre en chaîne de caractères
        // exigée par la nouvelle classe CString.
        char* myBuffer = new char[18];
        CString sIDrive = itoa(iDrive, myBuffer, 10);
        delete[] myBuffer;

        sDriveType = sIDrive + 'A';
        sDriveType += ":\\";

        if( GetDriveType( sDriveType ) == DRIVE_FIXED )
        {                  
            sFile = FindFile( sExeFilename, iDrive );
            if (!sFile.IsEmpty())
            {
                // Restore the previous drive
                   _chdrive( uOldDrive );
                return sFile;
            }
        }
    }
    // Restore the previous drive
      _chdrive( uOldDrive );
#else
    // Keep the current drive    
    _dos_getdrive( &uOldDrive );
    for( int iDrive=0 ; iDrive < 26 ; iDrive++ )
        if( GetDriveType( iDrive ) == DRIVE_FIXED )
        {                  
            sFile = FindFile( sExeFilename, iDrive );
            if (!sFile.IsEmpty())
            {
                // Restore the previous drive
                   _dos_setdrive( uOldDrive, &uNumberOfDrives );
                return sFile;
            }
        }
    // Restore the previous drive
      _dos_setdrive( uOldDrive, &uNumberOfDrives );
#endif // _WIN32

    return "";
  //## end ZASecurityCheck::FindOldVersion%812562131.body
}

const CString&  ZASecurityCheck::FindFile(const CString&  sFilename, int iDrive)
{
  //## begin ZASecurityCheck::FindFile%812564853.body preserve=yes
    // Initialize the buffer that will
    // contain the result
    m_sFoundedFilename = "";

    // Assign the filename to search    
    m_sFilenameToSearch = sFilename;
    // JMR-MODIF - Le 18 mai 2005 - Conversion explicite d'un nombre en chaîne de caractères
    // exigée par la nouvelle classe CString.
    char* myBuffer = new char[18];
    CString sIDrive = itoa(iDrive, myBuffer, 10);
    delete[] myBuffer;
    CString        sDir = sIDrive + 'A';
    sDir += ":\\";

#ifndef _WIN32
    // Change drive
       unsigned     uNumberOfDrives;
       _dos_setdrive( iDrive+1, &uNumberOfDrives );
#endif // _WIN32

#ifdef _WIN32
    SetCurrentDirectory( sDir );
#else
    chdir( sDir );
#endif // _WIN32

    FindFileInCurrentDir();
    return m_sFoundedFilename;
  //## end ZASecurityCheck::FindFile%812564853.body
}

BOOL ZASecurityCheck::FindFileInCurrentDir()
{
  //## begin ZASecurityCheck::FindFileInCurrentDir%812564854.body preserve=yes
#ifdef _WIN32
    struct _finddata_t FileInfo; 
    long    lHandle;
     // Find the first file in the current directory.
 
    if (_findfirst (m_sFilenameToSearch, &FileInfo) == -1L ) 
    {
        _fullpath (m_sFoundedFilename.GetBufferSetLength(128), FileInfo.name, 128);
        m_sFoundedFilename.ReleaseBuffer();
        return TRUE;
    }
    // Now search for a subdirectory.  If a subdirectory is
    // found, change to it and call SearchDir recursively.
 
    if ((lHandle=_findfirst ("*.*", &FileInfo)) == -1L ) 
    {
        if ((FileInfo.attrib & 0x10) != 0x00)
            if ((strcmp (FileInfo.name, ".") != 0) &&
                (strcmp (FileInfo.name, "..") != 0)) 
            {
                _chdir (FileInfo.name);
                FindFileInCurrentDir ();
                _chdir ("..");
            }
 
        // Search for additional subdirectories.
 
        while (!_findnext (lHandle, &FileInfo))
            if ((FileInfo.attrib & 0x10) != 0x00)
                if ((strcmp (FileInfo.name, ".") != 0) &&
                    (strcmp (FileInfo.name, "..") != 0)) 
                {
                    _chdir (FileInfo.name);
                    FindFileInCurrentDir ();
                    _chdir ("..");
                }
    }
#else
    struct find_t FileInfo;
     // Find the first file in the current directory.
 
    if (!_dos_findfirst (m_sFilenameToSearch, _A_NORMAL | _A_RDONLY | _A_HIDDEN, &FileInfo)) 
    {
        _fullpath (m_sFoundedFilename.GetBufferSetLength(128), FileInfo.name, 128);
        m_sFoundedFilename.ReleaseBuffer();
        return TRUE;
    }
    // Now search for a subdirectory.  If a subdirectory is
    // found, change to it and call SearchDir recursively.
 
    if (!_dos_findfirst ("*.*", _A_SUBDIR, &FileInfo)) 
    {
        if ((FileInfo.attrib & 0x10) != 0x00)
            if ((strcmp (FileInfo.name, ".") != 0) &&
                (strcmp (FileInfo.name, "..") != 0)) 
            {
                chdir (FileInfo.name);
                FindFileInCurrentDir ();
                chdir ("..");
            }
 
        // Search for additional subdirectories.
 
        while (!_dos_findnext (&FileInfo))
            if ((FileInfo.attrib & 0x10) != 0x00)
                if ((strcmp (FileInfo.name, ".") != 0) &&
                    (strcmp (FileInfo.name, "..") != 0)) 
                {
                    chdir (FileInfo.name);
                    FindFileInCurrentDir ();
                    chdir ("..");
                }
    }
#endif // _WIN32
 
 
    return FALSE;
  //## end ZASecurityCheck::FindFileInCurrentDir%812564854.body
}

BOOL ZASecurityCheck::CreateSecurityFile()
{
  //## begin ZASecurityCheck::CreateSecurityFile%812564855.body preserve=yes
      return ZASecurity::Create();
  //## end ZASecurityCheck::CreateSecurityFile%812564855.body
}

BOOL ZASecurityCheck::Create(const CString&  sFilename, int iDaysMax, int iCounterMax, int iCounterMin,
                             const CString ApplicationRegistryKey /*= ""*/, const CString ApplicationPID /*= ""*/)
{
  //## begin ZASecurityCheck::Create%812682977.body preserve=yes
    SetsFilename( sFilename );
    if (!ApplicationRegistryKey.IsEmpty())
        m_sKey = ApplicationRegistryKey;
    if (!ApplicationPID.IsEmpty())
        m_sPID = ApplicationPID;
    m_iDaysMax = iDaysMax;
    m_iCounterMax = iCounterMax;
    m_iCounterMin = iCounterMin;
    return TRUE;
  //## end ZASecurityCheck::Create%812682977.body
}

BOOL ZASecurityCheck::CheckRegistery()
{
  //## begin ZASecurityCheck::CheckRegistery%854929700.body preserve=yes
#ifdef _WIN32
    HKEY hkStdFileEditing;
    if (RegOpenKey(    HKEY_CLASSES_ROOT,
                       "SOFTWARE\\PlanFin\\System",
                    &hkStdFileEditing) == ERROR_SUCCESS) 
    {
        RegCloseKey(hkStdFileEditing);     // closes key and subkeys
        return FALSE;
    }
#endif // _WIN32
    return TRUE;
  //## end ZASecurityCheck::CheckRegistery%854929700.body
}


// Additional Declarations
//## begin ZASecurityCheck.declarations preserve=yes
//## end ZASecurityCheck.declarations




