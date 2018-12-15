//## begin module.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module.cm

//## begin module.cp preserve=no
//## end module.cp

//## Module: Security; Package body
//## Subsystem: Security Modules
//## Source file: d:\adsoft~1\zsecurit\security.cpp


//## begin module.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module.additionalIncludes

//## begin module.includes preserve=yes
#include "Eval.h"
#include "stopprt.h"
//## end module.includes

// Security
#include "security.h"

//## begin module.declarations preserve=no
//## end module.declarations

//## begin module.additionalDeclarations preserve=yes
#include "ShellApi.h"

#include "zBaseLib\ZBRegisterSetup.h"


int    ZASecurity::GetCurrentVersion()
{ 
    return iCurrentVersion; 
}
//## end module.additionalDeclarations


// Class ZASecurity 





ZASecurity::ZASecurity()
{
  //## begin ZASecurity::ZASecurity%.body preserve=yes
    SetbError( FALSE );
  //## end ZASecurity::ZASecurity%.body
}

ZASecurity::ZASecurity(const CString&  sFileName, const CString ApplicationRegistryKey /*= ""*/, const CString ApplicationPID /*= ""*/)
  //## begin ZASecurity::ZASecurity%812250694.hasinit preserve=no
  //## end ZASecurity::ZASecurity%812250694.hasinit
  //## begin ZASecurity::ZASecurity%812250694.initialization preserve=yes
: m_sFilename(sFileName),
  m_sKey(ApplicationRegistryKey),
  m_sPID(ApplicationPID)
  //## end ZASecurity::ZASecurity%812250694.initialization
{
  //## begin ZASecurity::ZASecurity%812250694.body preserve=yes
    SetbError( FALSE );
  //## end ZASecurity::ZASecurity%812250694.body
}


ZASecurity::~ZASecurity()
{
  //## begin ZASecurity::~ZASecurity%.body preserve=yes
  //## end ZASecurity::~ZASecurity%.body
}



//## Other Operations (implementation)
BOOL ZASecurity::Create()
{
  //## begin ZASecurity::Create%811976842.body preserve=yes
      // Create the security file

    // Create the first area
    int    i;
    for( i = 0; i < 20; ++i )
        m_SecurityEntityTable[i].GenerateRandomEntity();

    // Save the initial date
    m_SecurityEntityTable[iPosDateStart].GenerateDate( CTime::GetCurrentTime() );
    // Save the last used date
    m_SecurityEntityTable[iPosDateLast].GenerateDate( CTime::GetCurrentTime() );
    
    // Save the initial counter
    m_SecurityEntityTable[iPosCounterStart].GenerateCounter( 0 );
    // Save the last counter
    m_SecurityEntityTable[iPosCounterLast].GenerateCounter( 0 );
    // Write the version
    m_SecurityEntityTable[iPosVersion].GenerateVersion( iCurrentVersion );
/*
#ifdef _WIN32

    HKEY hkStdFileEditing;
    // Create the registery entry if it does not exist
    if (RegOpenKey(    HKEY_CURRENT_USER,
                       "SOFTWARE\\PlanFin\\System",
                    &hkStdFileEditing) != ERROR_SUCCESS) 
    {
        if (RegCreateKey(     HKEY_CURRENT_USER,             
                            "SOFTWARE\\PlanFin\\System",                 // system string
                            &hkStdFileEditing) != ERROR_SUCCESS)   
            return FALSE;

        RegSetValue(    hkStdFileEditing,              // handle of key
                        sStartDate,                  // Name of subkey
                        REG_SZ,                     // required
                                                    // The start date
                        (const char*)m_SecurityEntityTable[iPosDateStart].GetsEntity(),
                        40);                        // text string size
        
        RegSetValue(    hkStdFileEditing,              // handle of key
                        sLastDate,                  // Name of subkey
                        REG_SZ,                     // required
                                                    // The last date
                        (const char*)m_SecurityEntityTable[iPosDateLast].GetsEntity(),
                        40);                        // text string size

        RegSetValue(    hkStdFileEditing,              // handle of key
                        sLastCounter,                  // Name of subkey
                        REG_SZ,                     // required
                                                    // The counter
                        (const char*)m_SecurityEntityTable[iPosCounterLast].GetsEntity(),
                        40);                        // text string size

        RegCloseKey(hkStdFileEditing);     // closes key and subkeys

    }
#endif // _WIN32
*/
    WriteEntityTable();
      return !GetbError();
  //## end ZASecurity::Create%811976842.body
}

BOOL ZASecurity::WriteEntityTable()
{
/*
    HANDLE hFile = CreateFile( (const char*)GetSecurityFilename(),
                                GENERIC_WRITE, FILE_SHARE_READ,
                                NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
      {
          SetbError( TRUE );
          return;
      }
*/
    if (!m_SecurityFile.Open( (const char*)GetSecurityFilename(),    
                                CFile::modeCreate | 
                                CFile::modeWrite |
                                CFile::shareExclusive ))
      {
          SetbError( TRUE );
          return !GetbError();
      }
    TRY
    {
        for( int i = 0; i < 20; ++i )
            m_SecurityFile.WriteString( m_SecurityEntityTable[i].GetsEntity() + "\n" );
    }
    CATCH( CFileException, e )
    {
          SetbError( TRUE );
    }
    END_CATCH

    TRY
    {
          m_SecurityFile.Close();
    }
    CATCH( CFileException, e )
    {
          SetbError( TRUE );
    }
    END_CATCH
/*
    // Set a default date to hide the file modifications
    HANDLE hFile = CreateFile(
        (const char*)GetSecurityFilename(),    // pointer to name of the file 
        GENERIC_WRITE,        // access (read-write) mode 
        FILE_SHARE_WRITE,    // share mode 
        NULL,    // pointer to security descriptor 
        OPEN_EXISTING,    // how to create 
        FILE_ATTRIBUTE_HIDDEN,    // file attributes 
        NULL     // handle to file with attributes to copy  
        );
    FILETIME    FileTime;
    DosDateTimeToFileTime( 0x12c1, 0x5000, &FileTime );    // 10:00  6-1-89
    SetFileTime(    static_cast<HANDLE>( hFile ), 
                    &FileTime,        // time the file was created
                    &FileTime,        // time the file was last accessed
                    &FileTime );    // time the file was last written
    CloseHandle( hFile );
    SetFileAttributes( (const char*)GetSecurityFilename(), FILE_ATTRIBUTE_HIDDEN );
*/
      return !GetbError();
}

BOOL ZASecurity::SetLastUseDate(CTime tmDate)
{
    if (!LoadSecurityTable())
        return FALSE;
    // Save the last used date
    m_SecurityEntityTable[iPosDateLast].GenerateDate( tmDate );
    return WriteEntityTable();

/*
#ifdef _WIN32
    // Open the registery entry
    HKEY hkStdFileEditing;
    if (RegOpenKey(    HKEY_CURRENT_USER,
                       "SOFTWARE\\PlanFin\\System",
                    &hkStdFileEditing) == ERROR_SUCCESS) 
    {
        RegSetValue(    hkStdFileEditing,              // handle of key
                        sLastDate,                  // Name of subkey
                        REG_SZ,                     // required
                                                    // The last date
                        (const char*)m_SecurityEntityTable[iPosDateLast].GetsEntity(),
                        40);                        // text string size

        RegCloseKey(hkStdFileEditing);     // closes key and subkeys
    }
    else
          SetbError( TRUE );
#endif // _WIN32      
*/        
      return !GetbError();
  //## end ZASecurity::SetLastUseDate%812250691.body
}

BOOL ZASecurity::SetLastUseCounter(int iCounter)
{
  //## begin ZASecurity::SetLastUseCounter%812250692.body preserve=yes
    if (!LoadSecurityTable())
        return FALSE;
    // Save the last counter
    m_SecurityEntityTable[iPosCounterLast].GenerateCounter( iCounter );
    return WriteEntityTable();

/*
#ifdef _WIN32
    // Open the registery entry
    HKEY hkStdFileEditing;
    if (RegOpenKey(    HKEY_CURRENT_USER,
                       "SOFTWARE\\PlanFin\\System",
                    &hkStdFileEditing) == ERROR_SUCCESS) 
    {
        RegSetValue(    hkStdFileEditing,              // handle of key
                        sLastCounter,                  // Name of subkey
                        REG_SZ,                     // required
                                                    // The counter
                        (const char*)m_SecurityEntityTable[iPosCounterLast].GetsEntity(),
                        40);                        // text string size

        RegCloseKey(hkStdFileEditing);     // closes key and subkeys
    }
    else
          SetbError( TRUE );
#endif // _WIN32          
*/
      return !GetbError();
  //## end ZASecurity::SetLastUseCounter%812250692.body
}

CString ZASecurity::GetSecurityFilename() const
{
  //## begin ZASecurity::GetSecurityFilename%812250693.body preserve=yes
      char    szWinDir[100];
      GetWindowsDirectory(szWinDir, sizeof( szWinDir ) );
      CString    sCompleteFilename( szWinDir );
      sCompleteFilename += "\\" + m_sFilename;
      return sCompleteFilename;
  //## end ZASecurity::GetSecurityFilename%812250693.body
}

BOOL ZASecurity::LoadSecurityTable()
{
    SetbError( FALSE );
    // Open the file
      if (!m_SecurityFile.Open( (const char*)GetSecurityFilename(), 
                                CFile::modeRead | 
                                CFile::shareDenyWrite ))
      {
          SetbError( TRUE );
          return !m_bError;
      }

/*
    WORD    date;
    WORD    time;
    HANDLE hFile = CreateFile(
        (const char*)GetSecurityFilename(),    // pointer to name of the file 
        GENERIC_WRITE,        // access (read-write) mode 
        FILE_SHARE_WRITE,    // share mode 
        NULL,    // pointer to security descriptor 
        OPEN_EXISTING,    // how to create 
        FILE_ATTRIBUTE_HIDDEN,    // file attributes 
        NULL     // handle to file with attributes to copy  
        );
    FILETIME    FileTime, DummyTime;
    GetFileTime(hFile,            // identifies the file 
                &FileTime,        // address of creation time 
                &DummyTime,        // address of last access time  
                &DummyTime );     // address of last write time 
    CloseHandle( hFile );
    FileTimeToDosDateTime(    &FileTime,    // pointer to 64-bit file time 
                            &date, // pointer to variable for MS-DOS date  
                            &time );     // pointer to variable for MS-DOS time  
    // Test if the filename has the same
    // date and time
    if (date != 0x12c1 && time != 0x5000)
    {
        // If not the user has changed manually the filename
          SetbError( TRUE );
          return;
      }
*/
    for (int i = 0; i < 20; ++i)
    {
        CString s;
        TRY
        {
            m_SecurityFile.ReadString( s );
        }
        CATCH( CFileException, e )
        {
              SetbError( TRUE );
            break;
        }
        END_CATCH
        m_SecurityEntityTable[i].SetsEntity( s ); 
    }

    TRY
    {
          m_SecurityFile.Close();
    }
    CATCH( CFileException, e )
    {
          SetbError( TRUE );
    }
    END_CATCH
    
    return !m_bError;
}

int ZASecurity::GetCounterSpan()
{
  //## begin ZASecurity::GetCounterSpan%812506908.body preserve=yes
    if (!LoadSecurityTable())
        return -1;

/*
    // Test if the counter is the same
    // in the file and in the registery
    // Open the registery entry
    char szBuff[80];
    LONG cb;
       cb = sizeof(szBuff);
    HKEY hkStdFileEditing;
    if (RegOpenKey(    HKEY_CURRENT_USER,
                       "SOFTWARE\\PlanFin\\System",
                    &hkStdFileEditing) == ERROR_SUCCESS) 
    {
        // Check the counter
        if (RegQueryValue(    hkStdFileEditing,
                            sLastCounter,                  // Name of subkey
                            szBuff,
                            &cb) != ERROR_SUCCESS ||
            strcmp( szBuff, (const char*)m_SecurityEntityTable[iPosCounterLast].GetsEntity()) != 0)
        {
              SetbError( TRUE );
              return 0;
          }
        RegCloseKey(hkStdFileEditing);     // closes key and subkeys
    }
    else
    {
          SetbError( TRUE );
          return 0;
      }
*/    
    // Get the initial counter
    int            iStart = m_SecurityEntityTable[iPosCounterStart].GetCounter();
    // Get the last counter
    int            iLast = m_SecurityEntityTable[iPosCounterLast].GetCounter();
    return iLast - iStart;
}

CTimeSpan ZASecurity::GetTimeSpan()
{
  //## begin ZASecurity::GetTimeSpan%812506909.body preserve=yes
    if (!LoadSecurityTable())
        return CTimeSpan( 25000 );

/*
    // Test if the counter is the same
    // in the file and in the registery
    // Open the registery entry
    char szBuff[80];
    LONG cb;
       cb = sizeof(szBuff);
    HKEY hkStdFileEditing;
    if (RegOpenKey(    HKEY_CURRENT_USER,
                       "SOFTWARE\\PlanFin\\System",
                    &hkStdFileEditing) == ERROR_SUCCESS) 
    {
          // Check the last date
        if (RegQueryValue(    hkStdFileEditing,
                            sLastDate,                  // Name of subkey
                            szBuff,
                            &cb) != ERROR_SUCCESS ||
             strcmp( szBuff, (const char*)m_SecurityEntityTable[iPosDateLast].GetsEntity()) != 0)
        {
              SetbError( TRUE );
              return 0;
          }
          // Check the start date
        if (RegQueryValue(    hkStdFileEditing,
                            sStartDate,                  // Name of subkey
                            szBuff,
                            &cb) != ERROR_SUCCESS ||
            strcmp( szBuff, (const char*)m_SecurityEntityTable[iPosDateStart].GetsEntity()) != 0)
        {
              SetbError( TRUE );
              return 0;
          }

        RegCloseKey(hkStdFileEditing);     // closes key and subkeys
    }
    else
    {
          SetbError( TRUE );
          return 0;
      }
*/
    // Get the initial date
    CTime    tmStart = m_SecurityEntityTable[iPosDateStart].GetDate();
    // Get the last date
    CTime    tmLast = m_SecurityEntityTable[iPosDateLast].GetDate();
    // Check if the start date and the last date is coherent
    if (tmLast < tmStart)
        return CTimeSpan( 1000000, 0, 0, 0 );    // Return 1 million of days ellapsed
    return tmLast - tmStart;
  //## end ZASecurity::GetTimeSpan%812506909.body
}

BOOL ZASecurity::IncrementCounter()
{
  //## begin ZASecurity::IncrementCounter%812682976.body preserve=yes
    if (!LoadSecurityTable())
        return FALSE;
    // Get the last counter
    int            iLast = m_SecurityEntityTable[iPosCounterLast].GetCounter();
    // Save the incremented counter
    m_SecurityEntityTable[iPosCounterLast].GenerateCounter( iLast + 1 );
    return WriteEntityTable();
  //## end ZASecurity::IncrementCounter%812682976.body
}

int ZASecurity::GetVersion()
{
  //## begin ZASecurity::GetVersion%854929698.body preserve=yes
    if (!LoadSecurityTable())
        return -1;
    // Get the last counter
    int            iVersion = m_SecurityEntityTable[iPosVersion].GetVersion();
    if (GetbError())
        return -1;
      return iVersion;
  //## end ZASecurity::GetVersion%854929698.body
}

void ZASecurity::DisplayWarning()
{
  //## begin ZASecurity::DisplayWarning%854929699.body preserve=yes
      ZIEvalWarning    EvalWarning;
      EvalWarning.DoModal();
  //## end ZASecurity::DisplayWarning%854929699.body
}

void ZASecurity::DisplayStopWnd()
{
  //## begin ZASecurity::DisplayStopWnd%855119248.body preserve=yes
      ZIStopPrint    StopPrint;
      if (StopPrint.DoModal() == IDCHANGE)
    {
        // Now set the product code to the registry
        ZBRegisterSetup Registry;
        Registry.CreateEntry( m_sKey, m_sPID, StopPrint.GetCode() );
    }

  //## end ZASecurity::DisplayStopWnd%855119248.body
}

BOOL ZASecurity::SetVersion(int iVersion)
{
  //## begin ZASecurity::SetVersion%855298594.body preserve=yes
    if (!LoadSecurityTable())
        return FALSE;
    // Write the version
    m_SecurityEntityTable[iPosVersion].GenerateVersion( iVersion );
    return WriteEntityTable();
  //## end ZASecurity::SetVersion%855298594.body
}


// Additional Declarations
//## begin ZASecurity.declarations preserve=yes
//## end ZASecurity.declarations


// Class ZASecurityEntity 


ZASecurityEntity::ZASecurityEntity()
{
}

ZASecurityEntity::ZASecurityEntity( const CString s )
: m_sEntity(s)
{
}

ZASecurityEntity::~ZASecurityEntity()
{
  //## begin ZASecurityEntity::~ZASecurityEntity%.body preserve=yes
  srand( (unsigned)time( NULL ) );
  GenerateRandomEntity();
  //## end ZASecurityEntity::~ZASecurityEntity%.body
}



//## Other Operations (implementation)
void ZASecurityEntity::CriptEntity()
{
  //## begin ZASecurityEntity::CriptEntity%811984124.body preserve=yes
      char*    cpKey = m_sEntity.GetBuffer(30);
      
      for( ; *cpKey; ++cpKey )
          *cpKey ^= 140;
      m_sEntity.ReleaseBuffer();
  //## end ZASecurityEntity::CriptEntity%811984124.body
}

CString ZASecurityEntity::GenerateRandomEntity()
{
  //## begin ZASecurityEntity::GenerateRandomEntity%811984121.body preserve=yes
      char    szBuf[20];
      sprintf( szBuf, "%04d%04d%04d", rand(), rand(), rand() );
      m_sEntity = szBuf;
      CriptEntity();
      return m_sEntity;
  //## end ZASecurityEntity::GenerateRandomEntity%811984121.body
}

CString ZASecurityEntity::GenerateDate(CTime tmDate)
{
  //## begin ZASecurityEntity::GenerateDate%812250686.body preserve=yes
      char    szBuf[20];
      sprintf( szBuf, "%04.04d", rand() );
      // bug with the format length
      // then cut artificially
      szBuf[4] = 0x00;
      m_sEntity = szBuf;
  
    sprintf( szBuf, "%04d%02d%02d", tmDate.GetYear(), 
                                      tmDate.GetMonth(),
                                      tmDate.GetDay());
      m_sEntity += szBuf;
//tmDate.Format("%Y%m%d");
      CriptEntity();
      return m_sEntity;
  //## end ZASecurityEntity::GenerateDate%812250686.body
}

CString ZASecurityEntity::GenerateCounter(int iCounter)
{
  //## begin ZASecurityEntity::GenerateCounter%812250687.body preserve=yes
      char    szBuf[20];
      sprintf( szBuf, "%04.04d", rand() );
      // bug with the format length
      // then cut artificially
      szBuf[4] = 0x00;
      m_sEntity = szBuf;
  
      // Add the counter
      sprintf( szBuf, "%04.04d", iCounter );
      szBuf[4] = 0x00;
      m_sEntity += szBuf;

      sprintf( szBuf, "%04.04d", rand() );
      szBuf[4] = 0x00;
      m_sEntity += szBuf;
      CriptEntity();
      return m_sEntity;
  //## end ZASecurityEntity::GenerateCounter%812250687.body
}

int ZASecurityEntity::GetCounter()
{
  //## begin ZASecurityEntity::GetCounter%812250688.body preserve=yes
      // Decript the entity
      CriptEntity();
      CString        sTemp = m_sEntity.Right(8);
      // Extract the string number
      CString        sNum( sTemp, 4 );
      return atoi( sNum );
  //## end ZASecurityEntity::GetCounter%812250688.body
}

CTime ZASecurityEntity::GetDate()
{
  //## begin ZASecurityEntity::GetDate%812250689.body preserve=yes
      // Decript the entity
      CriptEntity();
      // Extract the day
      CString        sDay = m_sEntity.Right(2);
      // Extract the year
      CString        sTemp = m_sEntity.Right(8);
      CString        sYear( sTemp, 4 );
      // Extract the month
      sTemp = m_sEntity.Right(4);
      CString        sMonth( sTemp, 2 );
      return CTime( atoi( sYear ), atoi( sMonth ), atoi( sDay ), 0, 0, 0 );
  //## end ZASecurityEntity::GetDate%812250689.body
}

int ZASecurityEntity::GetVersion()
{
  //## begin ZASecurityEntity::GetVersion%855298592.body preserve=yes
      // Decript the entity
      CriptEntity();
      CString        sTemp = m_sEntity.Right(8);
      CString        sCheck = m_sEntity.Right(4);
      if (sCheck != sCheckString)
          return 0;
      // Extract the string number
      CString        sNum( sTemp, 4 );
      return atoi( sNum );
  //## end ZASecurityEntity::GetVersion%855298592.body
}

CString ZASecurityEntity::GenerateVersion(int iVersion)
{
  //## begin ZASecurityEntity::GenerateVersion%855298593.body preserve=yes
      char    szBuf[20];
      sprintf( szBuf, "%04.04d", rand() );
      // bug with the format length
      // then cut artificially
      szBuf[4] = 0x00;
      m_sEntity = szBuf;
  
      // Add the version
      sprintf( szBuf, "%04.04d", iVersion );
      szBuf[4] = 0x00;
      m_sEntity += szBuf;

    // Add a stamp to differentiate new version
      m_sEntity += sCheckString;
      CriptEntity();
      return m_sEntity;
  //## end ZASecurityEntity::GenerateVersion%855298593.body
}


// Additional Declarations
//## begin ZASecurityEntity.declarations preserve=yes
//## end ZASecurityEntity.declarations




