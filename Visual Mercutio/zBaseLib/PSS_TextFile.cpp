/****************************************************************************
 * ==> PSS_TextFile --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic text file                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_TextFile.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_TextFile
//---------------------------------------------------------------------------
PSS_TextFile::PSS_TextFile(const CString& fileName) :
    m_FileName(fileName),
    m_pCurrent(NULL),
    m_pNext(NULL)
{
    std::memset(m_FileBuffer, 0x0, 300);
}
//---------------------------------------------------------------------------
PSS_TextFile::PSS_TextFile(const PSS_TextFile& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_TextFile::~PSS_TextFile()
{}
//---------------------------------------------------------------------------
const PSS_TextFile& PSS_TextFile::operator = (const PSS_TextFile& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_TextFile& PSS_TextFile::operator >> (CString& value)
{
    if (!ReadLine(value))
        value = _T("");

    const int index = value.Find(_T("\n"));

    if (index > 0)
    {
        CString copy = _T("");

        for (int i = 0; i < value.GetLength() - 2; ++i)
            copy += value.GetAt(i);

        value = copy;
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_TextFile& PSS_TextFile::operator << (const char* pChar)
{
    if (pChar)
        WriteLine(CString(pChar));

    return *this;
}
//---------------------------------------------------------------------------
PSS_TextFile& PSS_TextFile::operator << (float value)
{
    CString str;
    str.Format(_T("%f"), value);
    WriteLine(str);

    return *this;
}
//---------------------------------------------------------------------------
PSS_TextFile& PSS_TextFile::operator << (double value)
{
    CString str;
    str.Format(_T("%f"), value);
    WriteLine(str);

    return *this;
}
//---------------------------------------------------------------------------
PSS_TextFile& PSS_TextFile::operator << (DWORD value)
{
    CString str;
    str.Format(_T("%d"), value);
    WriteLine(str);

    return *this;
}
//---------------------------------------------------------------------------
PSS_TextFile& PSS_TextFile::operator << (UINT value)
{
    CString str;
    str.Format(_T("%d"), value);
    WriteLine(str);

    return *this;
}
//---------------------------------------------------------------------------
PSS_TextFile& PSS_TextFile::operator << (WORD value)
{
    CString str;
    str.Format(_T("%d"), value);
    WriteLine(str);

    return *this;
}
//---------------------------------------------------------------------------
PSS_TextFile& PSS_TextFile::operator << (short value)
{
    CString str;
    str.Format(_T("%d"), value);
    WriteLine(str);

    return *this;
}
//---------------------------------------------------------------------------
PSS_TextFile& PSS_TextFile::operator << (LONG value)
{
    CString str;
    str.Format(_T("%ld"), value);
    WriteLine(str);

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_TextFile::OpenRead(const CString& fileName)
{
    m_FileName = fileName;
    return OpenFileRead();
}
//---------------------------------------------------------------------------
BOOL PSS_TextFile::OpenWrite(const CString& fileName)
{
    m_FileName = fileName;
    return OpenFileWrite();
}
//---------------------------------------------------------------------------
BOOL PSS_TextFile::OpenFileRead()
{
    TRY
    {
        // open a file in read mode
        if (!m_File.Open(m_FileName, CFile::modeRead | CFile::typeBinary))
            return FALSE;
    }
    CATCH(CFileException, e)
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
BOOL PSS_TextFile::OpenFileWrite()
{
    TRY
    {
        // open a file in write mode
        if (!m_File.Open(m_FileName, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate))
            return FALSE;
    }
    CATCH(CFileException, e)
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
int PSS_TextFile::ReadLine(CString& line, bool removeNewLineChar)
{
    // is buffer empty?
    if (!m_pCurrent)
        // read data from the file and fill the buffer
        if (ReadFileBuffer() <= 0)
            return 0;

    // the buffer is filled and a new occurence was found
    if (m_pCurrent)
        // next return char found?
        if ((m_pNext = std::strchr(m_pCurrent, '\n')))
        {
            char previousChar = 0;

            if (removeNewLineChar)
                // where \n is found, put end of string char
                *(m_pNext - 1) = 0x00;
            else
            {
                // save the previous char
                previousChar   = *(m_pNext + 1);
                *(m_pNext + 1) = 0x00;
            }

            // copy the line to the output
            line = m_pCurrent;

            // put back the char
            if (!removeNewLineChar)
                *(m_pNext + 1) = previousChar;

            // set current char to the next one after the \n pointer
            m_pCurrent = m_pNext + 1;
        }
        else
        {
            // if the next buffer should be read, and the previous buffer should be merged with the new one
            const CString endLine(m_pCurrent);

            // read data from the file and fill the buffer
            if (ReadFileBuffer() <= 0)
                return 0;

            // build the final line with the end of string char and the beginning of the new read buffer.
            // Locate the next return char
            if (!(m_pNext = std::strchr(m_pCurrent, '\n')))
                return 0;

            // where \n is found, put end of string char
            if (m_pNext != m_pCurrent)
            {
                if (removeNewLineChar)
                    *(m_pNext - 1) = 0x00;
                else
                    *(m_pNext + 1) = 0x00;

                // Copy the line to buffer
                line = endLine + m_pCurrent;
            }
            else
                // copy the line to buffer
                line = endLine.Left(endLine.GetLength() - 1);

            // set the next char following the \n char the current one
            m_pCurrent = m_pNext + 1;
        }

    return line.GetLength();
}
//---------------------------------------------------------------------------
BOOL PSS_TextFile::WriteLine(const CString& line, bool addNewLineChar)
{
    TRY
    {
        if (addNewLineChar)
            m_File.Write(line + _T("\r\n"), line.GetLength());
        else
            m_File.Write(line, line.GetLength());
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
BOOL PSS_TextFile::CloseFile()
{
    TRY
    {
        m_File.Close();
    }
    CATCH(CFileException, e)
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
int PSS_TextFile::ReadFileBuffer()
{
    // read info from the file
    const int readChar = m_File.Read(m_FileBuffer, sizeof(m_FileBuffer) - 1);

    // If char read
    if (readChar)
        // keep the current char
        m_pCurrent = m_FileBuffer;

    // set end of line
    m_FileBuffer[readChar] = 0x00;

    // return the number of read chars
    return readChar;
}
//---------------------------------------------------------------------------
