//    Advanced Dedicated Software
//    Dominique AIGROZ
// Source file: ZBCriptedLine.cpp



#include "StdAfx.h"

// ZBCriptedLine
#include "ZBCriptedLine.h"



const int    CriptedLineLength = 100;
const int    CriptedNumberOfItem = 25;    // Multiply by 4 must give CriptedLineLength


IMPLEMENT_DYNCREATE( ZBCriptedLine, CObject );

// Class ZBCriptedLine 


ZBCriptedLine::ZBCriptedLine()
{
}


ZBCriptedLine::~ZBCriptedLine()
{
  srand( (unsigned)time( NULL ) );
  GenerateRandomLine();
}


ZBCriptedLine::ZBCriptedLine(const ZBCriptedLine &right)
{
      *this = right;
}

const ZBCriptedLine& ZBCriptedLine::operator=(const ZBCriptedLine &right)
{
      m_sEntity = right.m_sEntity;
      return *this;
}


void ZBCriptedLine::CriptEntity(CString& Line)
{
      char*    cpKey = Line.GetBuffer(Line.GetLength()+1);
      
      for( ; *cpKey; ++cpKey )
          *cpKey ^= 140;
      Line.ReleaseBuffer();
}

CString ZBCriptedLine::GenerateRandomLine(int size)
{
    CString    Line;

    int        Counter = size / 4;
    int        LeftCounter = size - (Counter*4);
      char    szBuf[30];
    for (int i = 0; i < Counter; ++i)
    {
          sprintf( szBuf, "%04.04d", rand() );
        szBuf[4] = 0x00;
          Line += szBuf;
    }
    for (i = 0; i < LeftCounter; ++i)
    {
          sprintf( szBuf, "%1.1d", rand() );
          Line += szBuf[0];
    }
      return Line;
}

CString ZBCriptedLine::GenerateRandomLine()
{
    m_sEntity = GenerateRandomLine(CriptedLineLength);

    // And finally, cript the entity
      CriptEntity(m_sEntity);
      return m_sEntity;
}

CString ZBCriptedLine::GenerateLine(CString value)
{
      char    szBuf[5];
    sprintf( szBuf, "%03d", value.GetLength() );
    m_sEntity = szBuf;
    m_sEntity += value;
    int Len = value.GetLength()+3;
    if (Len < CriptedLineLength)
    {
        // Add random char
        for (int i = Len; i < CriptedLineLength; ++i)
        {
              sprintf( szBuf, "%1.1d", rand() );
              m_sEntity += szBuf[0];
        }
    }
    // And finally, cript the entity
      CriptEntity(m_sEntity);
      return m_sEntity;
}

CString ZBCriptedLine::GenerateLine(CTime& Date)
{
    int LeftSize = (CriptedLineLength - 8) / 2;
    m_sEntity = GenerateRandomLine( LeftSize );

      char    szBuf[20];
    sprintf( szBuf, "%04d%02d%02d", Date.GetYear(), 
                                      Date.GetMonth(),
                                      Date.GetDay());
      m_sEntity += szBuf;

    int RightSize = CriptedLineLength - 8 - LeftSize;
    CString    RightLine = GenerateRandomLine( RightSize );
      m_sEntity += RightLine;

    CriptEntity( m_sEntity );
      return m_sEntity;
}

CString ZBCriptedLine::GenerateLine(ZBDate& Date)
{
    int LeftSize = (CriptedLineLength - 8) / 2;
    m_sEntity = GenerateRandomLine( LeftSize );

      char    szBuf[20];
    sprintf( szBuf, "%04d%02d%02d", Date.GetYear(), 
                                      Date.GetMonth(),
                                      Date.GetDay());
      m_sEntity += szBuf;

    int RightSize = CriptedLineLength - 8 - LeftSize;
    CString    RightLine = GenerateRandomLine( RightSize );
      m_sEntity += RightLine;

    CriptEntity( m_sEntity );
      return m_sEntity;
}

CString ZBCriptedLine::GenerateLine(int value)
{
    int LeftSize = (CriptedLineLength - 10) / 2;
    m_sEntity = GenerateRandomLine( LeftSize );
  
      char    szBuf[30];
      // Add the counter
      sprintf( szBuf, "%10.10d", value );
    szBuf[10] = 0x00;
      m_sEntity += szBuf;

    int RightSize = CriptedLineLength - 10 - LeftSize;
    CString    RightLine = GenerateRandomLine( RightSize );
      m_sEntity += RightLine;

    CriptEntity( m_sEntity );
      return m_sEntity;
}


CString ZBCriptedLine::GetString()
{
      // Decript the entity
      CriptEntity( m_sEntity );
    CString    Length = m_sEntity.Left(3);
    int        Len = atoi( Length );
      CString        sTemp = m_sEntity.Mid(3, Len);
      return sTemp;
}


int ZBCriptedLine::GetInt()
{
      // Decript the entity
      CriptEntity( m_sEntity );

    int LeftSize = (CriptedLineLength - 10) / 2;
    int RightSize = CriptedLineLength - 10 - LeftSize;

      CString        sTemp = m_sEntity.Right(RightSize + 10);
      // Extract the string number
      CString        sNum( sTemp, 10 );
      return atoi( sNum );
}

CTime ZBCriptedLine::GetCTime()
{
      // Decript the entity
      CriptEntity( m_sEntity );

    int LeftSize = (CriptedLineLength - 8) / 2;
    int RightSize = CriptedLineLength - 8 - LeftSize;

      CString        sTemp = m_sEntity.Right(RightSize + 8);
      // Extract the string number
      CString        sDate( sTemp, 8 );

      // Extract the year
      CString        sYear = sDate.Left( 4 );
      // Extract the day
      CString        sDay = m_sEntity.Right(2);
      // Extract the month
      sTemp = m_sEntity.Right(4);
      CString        sMonth( sTemp, 2 );
      return CTime( atoi( sYear ), atoi( sMonth ), atoi( sDay ), 0, 0, 0 );
}

ZBDate ZBCriptedLine::GetDate()
{
      // Decript the entity
      CriptEntity( m_sEntity );

    int LeftSize = (CriptedLineLength - 8) / 2;
    int RightSize = CriptedLineLength - 8 - LeftSize;

      CString        sTemp = m_sEntity.Right(RightSize + 8);
      // Extract the string number
      CString        sDate( sTemp, 8 );

      // Extract the year
      CString        sYear = sDate.Left( 4 );
      // Extract the day
      CString        sDay = m_sEntity.Right(2);
      // Extract the month
      sTemp = m_sEntity.Right(4);
      CString        sMonth( sTemp, 2 );
      return CTime( atoi( sYear ), atoi( sMonth ), atoi( sDay ), 0, 0, 0 );
}




