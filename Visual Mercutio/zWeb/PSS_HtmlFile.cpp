/****************************************************************************
 * ==> PSS_HtmlFile --------------------------------------------------------*
 ****************************************************************************
 * Description : Html file                                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_HtmlFile.h"

// std
#include <memory>

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_HtmlFile
//---------------------------------------------------------------------------
PSS_HtmlFile::PSS_HtmlFile(const CString& fileName) :
    m_pCurrent(NULL),
    m_pNext(NULL),
    m_FileName(fileName)
{
    std::memset(&m_FileBuffer, 0x0, 300);
}
//---------------------------------------------------------------------------
PSS_HtmlFile::~PSS_HtmlFile()
{}
//---------------------------------------------------------------------------
PSS_HtmlFile::PSS_HtmlFile(const PSS_HtmlFile& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
const PSS_HtmlFile& PSS_HtmlFile::operator = (const PSS_HtmlFile& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_HtmlFile& PSS_HtmlFile::operator << (const char* pValue)
{
    WriteLine(CString(pValue));
    return *this;
}
//---------------------------------------------------------------------------
PSS_HtmlFile& PSS_HtmlFile::operator << (float value)
{
    CString s;
    s.Format(_T("%f"), value);
    WriteLine(s);

    return *this;
}
//---------------------------------------------------------------------------
PSS_HtmlFile& PSS_HtmlFile::operator << (double value)
{
    CString s;
    s.Format(_T("%f"), value);
    WriteLine(s);

    return *this;
}
//---------------------------------------------------------------------------
PSS_HtmlFile& PSS_HtmlFile::operator << (DWORD value)
{
    CString s;
    s.Format(_T("%d"), value);
    WriteLine( s );

    return *this;
}
//---------------------------------------------------------------------------
PSS_HtmlFile& PSS_HtmlFile::operator << (UINT value)
{
    CString s;
    s.Format(_T("%d"), value);
    WriteLine(s);

    return *this;
}
//---------------------------------------------------------------------------
PSS_HtmlFile& PSS_HtmlFile::operator << (WORD value)
{
    CString s;
    s.Format(_T("%d"), value);
    WriteLine(s);

    return *this;
}
//---------------------------------------------------------------------------
PSS_HtmlFile& PSS_HtmlFile::operator << (short value)
{
    CString s;
    s.Format(_T("%d"), value);
    WriteLine(s);

    return *this;
}
//---------------------------------------------------------------------------
PSS_HtmlFile& PSS_HtmlFile::operator << (LONG value)
{
    CString s;
    s.Format(_T("%ld"), value);
    WriteLine(s);

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_HtmlFile::Create(const CString& fileName)
{
    m_FileName = fileName;
    return OpenFileCreate();
}
//---------------------------------------------------------------------------
BOOL PSS_HtmlFile::OpenFileCreate()
{
    TRY
    {
        // construct a CFile object in read mode
        if (!m_File.Open(m_FileName, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate))
            return FALSE;
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << _T("File could not be opened ") << e->m_cause << _T("\n");
        #endif

        return FALSE;
    }
    END_CATCH

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_HtmlFile::OpenFileRead()
{
    TRY
    {
        // construct a CFile object in read mode
        if (!m_File.Open(m_FileName, CFile::modeRead | CFile::typeBinary))
            return FALSE;
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << _T("File could not be opened ") << e->m_cause << _T("\n");
        #endif

        return FALSE;
    }
    END_CATCH

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_HtmlFile::CloseFile()
{
    TRY
    {
        m_File.Close();
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << "File could not be opened " << e->m_cause << "\n";
        #endif

        return FALSE;
    }
    END_CATCH

    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_HtmlFile::ReadLine(CString& line, bool removeNewLineChar)
{
    // is buffer empty?
    if (!m_pCurrent)
    {
        // read information from the file and fill the buffer
        if (ReadFileBuffer() <= 0)
            return 0;
    }
    // the buffer is filled and a new occurence is available
    else
    {
        // next return char found?
        if ((m_pNext = strchr(m_pCurrent, '\n')))
        {
            // used to save the previous char
            char prevChar = 0;

            if (removeNewLineChar)
                // carriage return was found, put end of string char
                *(m_pNext - 1) = 0x00;
            else
            {
                prevChar = *(m_pNext + 1);
                *(m_pNext + 1) = 0x00;
            }

            // copy the line in buffer
            line = m_pCurrent;

            // put back the char
            if (!removeNewLineChar)
                *(m_pNext + 1) = prevChar;

            // set current to the next char after the carriage return
            m_pCurrent = m_pNext + 1;
        }
        else
        {
            // read the next buffer and merge with the previous one
            const CString endLine(m_pCurrent);

            // read info from the file and fill the buffer
            if (ReadFileBuffer() <= 0)
                return 0;

            // add the carriage return and concatenate the next line. Locate the next return char
            if (!(m_pNext = strchr(m_pCurrent, '\n')))
                return 0;

            // carriage return is found, put end of string char
            if (m_pNext != m_pCurrent)
            {
                // used to save the previous char
                char prevChar = 0;

                if (removeNewLineChar)
                    *(m_pNext - 1) = 0x00;
                else
                    *(m_pNext + 1) = 0x00;

                // copy the line to output
                line = endLine + m_pCurrent;
            }
            else
                // copy the line to buffer
                line = endLine.Left(endLine.GetLength() - 1);

            // set current offset to the next char after the carriage return
            m_pCurrent = m_pNext + 1;
        }
    }

    return line.GetLength();
}
//---------------------------------------------------------------------------
BOOL PSS_HtmlFile::WriteLine(const CString& line, bool addNewLineChar)
{
    CString lineToWrite = line;

    TRY
    {
        if (addNewLineChar)
            lineToWrite += _T("\r\n");

        m_File.Write(lineToWrite, lineToWrite.GetLength());
    }
    CATCH(CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << _T("Could not write to file") << e->m_cause << _T("\n");
        #endif

        return FALSE;
    }
    END_CATCH

    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_HtmlFile::ReadFileBuffer()
{
    // read info from the file
    const int readChar = m_File.Read(m_FileBuffer, sizeof(m_FileBuffer) - 1);

    if (readChar)
        m_pCurrent = m_FileBuffer;

    // Set end of line
    m_FileBuffer[readChar] = 0x00;

    // return the number of char read
    return readChar;
}
//---------------------------------------------------------------------------
