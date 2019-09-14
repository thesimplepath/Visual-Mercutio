/****************************************************************************
 * ==> PSS_EncryptedLine  --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an encrypted text line                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_EncryptedLine.h"

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const int g_EncryptedLineLength = 100;
const int g_EncryptedItemCount  = 25;  // multiply by 4 must give g_EncryptedLineLength
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_EncryptedLine, CObject);
//---------------------------------------------------------------------------
// PSS_EncryptedLine 
//---------------------------------------------------------------------------
PSS_EncryptedLine::PSS_EncryptedLine() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_EncryptedLine::PSS_EncryptedLine(const PSS_EncryptedLine& other) :
    CObject()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_EncryptedLine::~PSS_EncryptedLine()
{
    std::srand(unsigned(::time(NULL)));
    GenerateRandomLine();
}
//---------------------------------------------------------------------------
const PSS_EncryptedLine& PSS_EncryptedLine::operator = (const PSS_EncryptedLine& other)
{
    m_Entity = other.m_Entity;
    return *this;
}
//---------------------------------------------------------------------------
CString PSS_EncryptedLine::GenerateRandomLine()
{
    m_Entity = GenerateRandomLine(g_EncryptedLineLength);

    // encrypt the entity
    EncryptEntity(m_Entity);
    
    return m_Entity;
}
//---------------------------------------------------------------------------
CString PSS_EncryptedLine::GenerateLine(const CString& value)
{
    char buffer[5];
    std::sprintf(buffer, "%03d", value.GetLength());

    m_Entity  = buffer;
    m_Entity += value;

    const int len = value.GetLength() + 3;

    if (len < g_EncryptedLineLength)
        // add random char
        for (int i = len; i < g_EncryptedLineLength; ++i)
        {
            std::sprintf(buffer, "%1.1d", std::rand());
            m_Entity += buffer[0];
        }

    // encrypt the entity
    EncryptEntity(m_Entity);

    return m_Entity;
}
//---------------------------------------------------------------------------
CString PSS_EncryptedLine::GenerateLine(const ZBDate& date)
{
    const int leftSize = (g_EncryptedLineLength - 8) / 2;
    m_Entity           = GenerateRandomLine(leftSize);

    char buffer[20];
    std::sprintf(buffer, "%04d%02d%02d", date.GetYear(), date.GetMonth(), date.GetDay());
    m_Entity += buffer;

    const int     rightSize = g_EncryptedLineLength  - 8 - leftSize;
          CString rightLine = GenerateRandomLine(rightSize);
    m_Entity               += rightLine;

    EncryptEntity(m_Entity);

    return m_Entity;
}
//---------------------------------------------------------------------------
CString PSS_EncryptedLine::GenerateLine(const CTime& time)
{
    const int leftSize = (g_EncryptedLineLength - 8) / 2;
    m_Entity           = GenerateRandomLine(leftSize);

    char buffer[20];
    std::sprintf(buffer, "%04d%02d%02d", time.GetYear(), time.GetMonth(), time.GetDay());
    m_Entity += buffer;

    const int rightSize = g_EncryptedLineLength - 8 - leftSize;
    CString   rightLine = GenerateRandomLine(rightSize);
    m_Entity           += rightLine;

    EncryptEntity(m_Entity);

    return m_Entity;
}
//---------------------------------------------------------------------------
CString PSS_EncryptedLine::GenerateLine(int value)
{
    const int leftSize = (g_EncryptedLineLength - 10) / 2;
    m_Entity           = GenerateRandomLine(leftSize);
  
    char buffer[30];

    // add the counter
    std::sprintf(buffer, "%10.10d", value);
    buffer[10]  = 0x00;
    m_Entity   += buffer;

    const int     rightSize = g_EncryptedLineLength - 10 - leftSize;
          CString rightLine = GenerateRandomLine(rightSize);
    m_Entity               += rightLine;

    EncryptEntity(m_Entity);

    return m_Entity;
}
//---------------------------------------------------------------------------
CString PSS_EncryptedLine::GetString()
{
    // decrypt the entity
    EncryptEntity(m_Entity);

    const CString length = m_Entity.Left(3);
    const int     len    = std::atoi(length);
    const CString temp   = m_Entity.Mid(3, len);

    return temp;
}
//---------------------------------------------------------------------------
int PSS_EncryptedLine::GetInt()
{
    // decrypt the entity
    EncryptEntity(m_Entity);

    const int     leftSize  = (g_EncryptedLineLength - 10) / 2;
    const int     rightSize =  g_EncryptedLineLength - 10  - leftSize;
    const CString temp      =  m_Entity.Right(rightSize + 10);

    // extract the string number
    const CString sNum(temp, 10);

    return std::atoi(sNum);
}
//---------------------------------------------------------------------------
ZBDate PSS_EncryptedLine::GetDate()
{
    // decrypt the entity
    EncryptEntity(m_Entity);

    const int     leftSize  = (g_EncryptedLineLength - 8) / 2;
    const int     rightSize =  g_EncryptedLineLength - 8  - leftSize;
          CString temp      =  m_Entity.Right(rightSize + 8);

    // extract the string number
    const CString date(temp, 8);

    // extract the year
    const CString year = date.Left(4);

    // extract the day
    const CString day = m_Entity.Right(2);

    // extract the month
    temp = m_Entity.Right(4);
    const CString month(temp, 2);

    return CTime(std::atoi(year), std::atoi(month), std::atoi(day), 0, 0, 0);
}
//---------------------------------------------------------------------------
CTime PSS_EncryptedLine::GetTime()
{
    // decrypt the entity
    EncryptEntity(m_Entity);

    const int     leftSize  = (g_EncryptedLineLength - 8) / 2;
    const int     rightSize =  g_EncryptedLineLength - 8  - leftSize;
          CString temp      =  m_Entity.Right(rightSize + 8);

    // extract the string number
    const CString date(temp, 8);

    // extract the year
    const CString year = date.Left(4);

    // extract the day
    const CString day = m_Entity.Right(2);

    // extract the month
    temp = m_Entity.Right(4);
    const CString month(temp, 2);

    return CTime(std::atoi(year), std::atoi(month), std::atoi(day), 0, 0, 0);
}
//---------------------------------------------------------------------------
void PSS_EncryptedLine::EncryptEntity(const CString& line)
{
    CString encryptedLine = line;

    char* pCpKey = encryptedLine.GetBuffer(encryptedLine.GetLength() + 1);

    for (; *pCpKey; ++pCpKey)
        *pCpKey ^= 140;

    encryptedLine.ReleaseBuffer();
}
//---------------------------------------------------------------------------
CString PSS_EncryptedLine::GenerateRandomLine(int size)
{
    const int count     = size / 4;
    const int leftCount = size - (count * 4);
    CString   line;
    char      buffer[30];

    for (int i = 0; i < count; ++i)
    {
        std::sprintf(buffer, "%04.04d", std::rand());
        buffer[4]  = 0x00;
        line      += buffer;
    }

    for (int i = 0; i < leftCount; ++i)
    {
        sprintf(buffer, "%1.1d", std::rand());
        line += buffer[0];
    }

    return line;
}
//---------------------------------------------------------------------------
