//    Advanced Dedicated Software
//    Dominique AIGROZ
// Source file: ZBCriptedLine.cpp

#include "StdAfx.h"

// ZBCriptedLine
#include "ZBCriptedLine.h"

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const int CriptedLineLength   = 100;
const int CriptedNumberOfItem = 25;  // multiply by 4 must give CriptedLineLength
//---------------------------------------------------------------------------
// StdAfx
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(ZBCriptedLine, CObject);
//---------------------------------------------------------------------------
// ZBCriptedLine 
//---------------------------------------------------------------------------
ZBCriptedLine::ZBCriptedLine()
{}
//---------------------------------------------------------------------------
ZBCriptedLine::ZBCriptedLine(const ZBCriptedLine& right)
{
    *this = right;
}
//---------------------------------------------------------------------------
ZBCriptedLine::~ZBCriptedLine()
{
    std::srand(unsigned(time(NULL)));
    GenerateRandomLine();
}
//---------------------------------------------------------------------------
const ZBCriptedLine& ZBCriptedLine::operator=(const ZBCriptedLine& right)
{
    m_sEntity = right.m_sEntity;
    return *this;
}
//---------------------------------------------------------------------------
void ZBCriptedLine::CriptEntity(const CString& line)
{
    CString cryptedLine = line;

    char* pCpKey = cryptedLine.GetBuffer(cryptedLine.GetLength() + 1);
      
    for (; *pCpKey; ++pCpKey)
        *pCpKey ^= 140;

    cryptedLine.ReleaseBuffer();
}
//---------------------------------------------------------------------------
CString ZBCriptedLine::GenerateRandomLine(int size)
{
    const int count     = size / 4;
    const int leftCount = size - (count * 4);
    CString   line;
    char      szBuf[30];

    for (int i = 0; i < count; ++i)
    {
        sprintf(szBuf, "%04.04d", std::rand());
        szBuf[4]  = 0x00;
        line     += szBuf;
    }

    for (int i = 0; i < leftCount; ++i)
    {
        sprintf(szBuf, "%1.1d", std::rand());
        line += szBuf[0];
    }

    return line;
}
//---------------------------------------------------------------------------
CString ZBCriptedLine::GenerateRandomLine()
{
    m_sEntity = GenerateRandomLine(CriptedLineLength);

    // and finally, cript the entity
    CriptEntity(m_sEntity);
    
    return m_sEntity;
}
//---------------------------------------------------------------------------
CString ZBCriptedLine::GenerateLine(const CString& value)
{
    char szBuf[5];
    sprintf(szBuf, "%03d", value.GetLength());

    m_sEntity  = szBuf;
    m_sEntity += value;

    const int len = value.GetLength() + 3;

    if (len < CriptedLineLength)
        // add random char
        for (int i = len; i < CriptedLineLength; ++i)
        {
            sprintf(szBuf, "%1.1d", std::rand());
            m_sEntity += szBuf[0];
        }

    // and finally, cript the entity
    CriptEntity(m_sEntity);

    return m_sEntity;
}
//---------------------------------------------------------------------------
CString ZBCriptedLine::GenerateLine(CTime& date)
{
    const int leftSize = (CriptedLineLength - 8) / 2;
    m_sEntity = GenerateRandomLine(leftSize);

    char szBuf[20];
    sprintf(szBuf, "%04d%02d%02d", date.GetYear(),  date.GetMonth(), date.GetDay());
    m_sEntity += szBuf;

    const int     rightSize = CriptedLineLength - 8 - leftSize;
          CString rightLine = GenerateRandomLine(rightSize);
    m_sEntity              += rightLine;

    CriptEntity(m_sEntity);

    return m_sEntity;
}
//---------------------------------------------------------------------------
CString ZBCriptedLine::GenerateLine(ZBDate& date)
{
    const int leftSize = (CriptedLineLength - 8) / 2;
    m_sEntity = GenerateRandomLine(leftSize);

    char szBuf[20];
    sprintf(szBuf, "%04d%02d%02d", date.GetYear(), date.GetMonth(), date.GetDay());
    m_sEntity += szBuf;

    const int     rightSize = CriptedLineLength - 8 - leftSize;
          CString rightLine = GenerateRandomLine(rightSize);
    m_sEntity              += rightLine;

    CriptEntity(m_sEntity);

    return m_sEntity;
}
//---------------------------------------------------------------------------
CString ZBCriptedLine::GenerateLine(int value)
{
    const int leftSize = (CriptedLineLength - 10) / 2;
    m_sEntity = GenerateRandomLine(leftSize);
  
    char szBuf[30];

    // add the counter
    sprintf(szBuf, "%10.10d", value);
    szBuf[10]  = 0x00;
    m_sEntity += szBuf;

    const int     rightSize = CriptedLineLength - 10 - leftSize;
          CString rightLine = GenerateRandomLine(rightSize);
    m_sEntity              += rightLine;

    CriptEntity(m_sEntity);

    return m_sEntity;
}
//---------------------------------------------------------------------------
CString ZBCriptedLine::GetString()
{
    // decript the entity
    CriptEntity(m_sEntity);
    const CString length = m_sEntity.Left(3);
    const int     len    = std::atoi(length);
    const CString sTemp  = m_sEntity.Mid(3, len);

    return sTemp;
}
//---------------------------------------------------------------------------
int ZBCriptedLine::GetInt()
{
    // decript the entity
    CriptEntity(m_sEntity);

    const int     leftSize  = (CriptedLineLength - 10) / 2;
    const int     rightSize =  CriptedLineLength - 10 - leftSize;
    const CString sTemp     = m_sEntity.Right(rightSize + 10);

    // extract the string number
    const CString sNum(sTemp, 10);

    return std::atoi(sNum);
}
//---------------------------------------------------------------------------
CTime ZBCriptedLine::GetCTime()
{
    // decript the entity
    CriptEntity( m_sEntity );

    const int     leftSize  = (CriptedLineLength - 8) / 2;
    const int     rightSize =  CriptedLineLength - 8 - leftSize;
          CString sTemp     = m_sEntity.Right(rightSize + 8);

    // extract the string number
    const CString sDate(sTemp, 8);

    // extract the year
    const CString sYear = sDate.Left(4);

    // extract the day
    const CString sDay = m_sEntity.Right(2);

    // extract the month
    sTemp = m_sEntity.Right(4);
    const CString sMonth(sTemp, 2);

    return CTime(std::atoi(sYear), std::atoi(sMonth), std::atoi(sDay), 0, 0, 0);
}
//---------------------------------------------------------------------------
ZBDate ZBCriptedLine::GetDate()
{
    // decript the entity
    CriptEntity(m_sEntity);

    const int     leftSize  = (CriptedLineLength - 8) / 2;
    const int     rightSize =  CriptedLineLength - 8 - leftSize;
          CString sTemp     = m_sEntity.Right(rightSize + 8);

    // extract the string number
    const CString sDate(sTemp, 8);

    // extract the year
    const CString sYear = sDate.Left(4);

    // extract the day
    const CString sDay = m_sEntity.Right(2);

    // extract the month
    sTemp = m_sEntity.Right(4);
    const CString sMonth(sTemp, 2);

    return CTime(std::atoi(sYear), std::atoi(sMonth), std::atoi(sDay), 0, 0, 0);
}
//---------------------------------------------------------------------------
