/////////////////////////////////////////////////////////////////////////////
//@doc ZBKeyFile
//@module ZBKeyFile.cpp | Implementation of the <c ZBKeyFile> class.
// 
// zADS<tm>
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software, Inc. 
// All rights reserved.
// Contact:
// mailto:devzone@adsoft-form.com
// http://www.adsoft-form.com
// 
// 
// <nl>Created: 03/2001
// 
/////////////////////////////////////////////////////////////////////////////
#include <StdAfx.h>

// ZBKeyFile
#include "ZBKeyFile.h"


// Class ZBKeyFile 





ZBKeyFile::ZBKeyFile()
: m_Count(1000)
{
}

ZBKeyFile::ZBKeyFile(const CString& sFileName)
: m_sFilename(sFileName), 
  m_Count(0)
{
}

ZBKeyFile::ZBKeyFile(const CString& sFileName, const CString& sClearFileName, int Count)
: m_sFilename(sFileName), 
  m_sClearFilename(sClearFileName), 
  m_Count(Count)
{
}


ZBKeyFile::~ZBKeyFile()
{
}



BOOL ZBKeyFile::GenerateFile()
{
    // Create the first area
    int    i;
    for( i = 0; i < m_Count; ++i )
        m_KeyEntityTable[i].GenerateRandomEntity();

    if (!WriteEntityTable( GetClearFilename() ))
        return FALSE;

    for( i = 0; i < m_Count; ++i )
        m_KeyEntityTable[i].CriptEntity();

    return WriteEntityTable( GetFilename() );
}


BOOL ZBKeyFile::IsKeyValid( const CString Key )
{

    if (!LoadSecurityTable( GetFilename() ))
        return FALSE;

    for (int i = 0; i < m_Count; ++i)
    {
        m_KeyEntityTable[i].CriptEntity();
        if (m_KeyEntityTable[i].GetsEntity() == Key)
            return TRUE;
    }
    return FALSE;

}

BOOL ZBKeyFile::WriteEntityTable( CString Filename )
{
    if (!m_SecurityFile.Open( Filename,    
                              CFile::modeCreate | 
                              CFile::modeWrite |
                              CFile::shareExclusive ))
      {
        return FALSE;
      }

    BOOL Error = FALSE;

    TRY
    {
        for( int i = 0; i < m_Count; ++i )
            m_SecurityFile.WriteString( m_KeyEntityTable[i].GetsEntity() + "\n" );
    }
    CATCH( CFileException, e )
    {
        Error = TRUE;
    }
    END_CATCH

    TRY
    {
          m_SecurityFile.Close();
    }
    CATCH( CFileException, e )
    {
        Error = TRUE;
    }
    END_CATCH
      return !Error;
}

BOOL ZBKeyFile::LoadSecurityTable( CString Filename )
{
    // Open the file
      if (!m_SecurityFile.Open( Filename, 
                              CFile::modeRead | 
                              CFile::shareDenyWrite ))
      {
          return FALSE;
      }

    BOOL Error = FALSE;
    BOOL End = FALSE;
    m_Count = 0;
    int MaxElement = sizeof( m_KeyEntityTable ) / sizeof(ZBKeyEntity) ;
    while (End == FALSE)
    {
        CString s;
        TRY
        {
            if (!m_SecurityFile.ReadString( s ))
                End = TRUE;
        }
        CATCH( CFileException, e )
        {
              Error = TRUE;
            break;
        }
        END_CATCH
        if (m_Count < MaxElement)
            m_KeyEntityTable[m_Count].SetsEntity( s ); 
        ++m_Count;
    }

    TRY
    {
          m_SecurityFile.Close();
    }
    CATCH( CFileException, e )
    {
        Error = TRUE;
    }
    END_CATCH
    
    return !Error;
}


// Class ZBKeyEntity 


ZBKeyEntity::ZBKeyEntity()
{
}


ZBKeyEntity::~ZBKeyEntity()
{
  srand( (unsigned)time( NULL ) );
  GenerateRandomEntity();
}



void ZBKeyEntity::CriptEntity()
{
      char*    cpKey = m_sEntity.GetBuffer(60);
      
      for( ; *cpKey; ++cpKey )
          *cpKey ^= 100;
      m_sEntity.ReleaseBuffer();
}

CString ZBKeyEntity::GenerateRandomEntity()
{
      char    szBuf[60];
      sprintf( szBuf, "%04d-%04d-%04d-%04d-%04d", rand(), rand(), rand(), rand(), rand() );
      m_sEntity = szBuf;
      return m_sEntity;
}

bool ZBKeyEntity::IsEqual( ZBKeyEntity& Entity )
{
    return false;
}





