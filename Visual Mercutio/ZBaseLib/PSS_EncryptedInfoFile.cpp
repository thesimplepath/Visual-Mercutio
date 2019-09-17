/****************************************************************************
 * ==> PSS_EncryptedInfoFile  ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic encrypted info file                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_EncryptedInfoFile.h"

// processsoft
#include "PSS_File.h"

//---------------------------------------------------------------------------
// PSS_EncryptedInfoFile
//---------------------------------------------------------------------------
PSS_EncryptedInfoFile::PSS_EncryptedInfoFile(std::size_t tableEntries) :
    m_TableEntries(tableEntries),
    m_Error(FALSE)
{
    AllocateEntityTable();
}
//---------------------------------------------------------------------------
PSS_EncryptedInfoFile::PSS_EncryptedInfoFile(const CString& fileName, std::size_t tableEntries) :
    m_FileName(fileName),
    m_TableEntries(tableEntries),
    m_Error(FALSE)
{
    AllocateEntityTable();
}
//---------------------------------------------------------------------------
PSS_EncryptedInfoFile::~PSS_EncryptedInfoFile()
{}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedInfoFile::CreateEmpty()
{
    if (!EntityTableExist())
        if (!AllocateEntityTable())
            return FALSE;

    CString text;

    // create the first area
    for (std::size_t i = 0; i < m_TableEntries; ++i)
        m_EntityTable[i].GenerateRandomLine();

    WriteEntityTable();
    return !GetErrorStatus();
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedInfoFile::CreateEmptyFile(const CString& fileName)
{
    m_FileName = fileName;
    return CreateEmpty();
}
//---------------------------------------------------------------------------
CString PSS_EncryptedInfoFile::GetString(std::size_t index)
{
    if (index >= m_TableEntries)
    {
        SetErrorStatus(TRUE);
        return "";
    }

    return m_EntityTable[index].GetString();

}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedInfoFile::SetString(const CString& value, std::size_t index)
{
    if (index >= m_TableEntries)
    {
        SetErrorStatus(TRUE);
        return FALSE;
    }

    if (!EntityTableExist())
    {
        if (!AllocateEntityTable())
            return FALSE;
    }

    m_EntityTable[index].GenerateLine(value);
    return TRUE;
}
//---------------------------------------------------------------------------
CTime PSS_EncryptedInfoFile::GetTime(std::size_t index)
{
    if (index >= m_TableEntries)
    {
        SetErrorStatus(TRUE);
        return 0;
    }

    return m_EntityTable[index].GetTime();
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedInfoFile::SetTime(const CTime& value, std::size_t index)
{
    if (index >= m_TableEntries)
    {
        SetErrorStatus(TRUE);
        return FALSE;
    }

    if (!EntityTableExist())
        if (!AllocateEntityTable())
            return FALSE;

    m_EntityTable[index].GenerateLine(value);
    return TRUE;
}
//---------------------------------------------------------------------------
PSS_Date PSS_EncryptedInfoFile::GetDate(std::size_t index)
{
    if (index >= m_TableEntries)
    {
        SetErrorStatus(TRUE);
        return PSS_Date(time_t(0));
    }

    return m_EntityTable[index].GetDate();
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedInfoFile::SetDate(const PSS_Date& value, std::size_t index)
{
    if (index >= m_TableEntries)
    {
        SetErrorStatus(TRUE);
        return FALSE;
    }

    if (!EntityTableExist())
    {
        if (!AllocateEntityTable())
            return FALSE;
    }

    m_EntityTable[index].GenerateLine(value);
    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_EncryptedInfoFile::GetInt(std::size_t index)
{
    if (index >= m_TableEntries)
    {
        SetErrorStatus(TRUE);
        return 0;
    }

    return m_EntityTable[index].GetInt();
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedInfoFile::SetInt(int value, std::size_t index)
{
    if (index >= m_TableEntries)
    {
        SetErrorStatus(TRUE);
        return FALSE;
    }

    if (!EntityTableExist())
        if (!AllocateEntityTable())
            return FALSE;

    m_EntityTable[index].GenerateLine(value);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedInfoFile::SetValidFileDate()
{
    HANDLE hFile = ::CreateFile((const char*)m_FileName,
                                GENERIC_WRITE,
                                FILE_SHARE_WRITE,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_HIDDEN,
                                NULL);

    if (hFile == INVALID_HANDLE_VALUE)
        return FALSE;

    FILETIME fileTime;
    ::DosDateTimeToFileTime(0x12c1, 0x5000, &fileTime);
    ::SetFileTime(static_cast<HANDLE>(hFile), &fileTime, &fileTime, &fileTime);
    ::CloseHandle(hFile);
    ::SetFileAttributes((const char*)m_FileName, FILE_ATTRIBUTE_HIDDEN);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedInfoFile::IsFileDateValid()
{
    HANDLE hFile = ::CreateFile((const char*)m_FileName,
                                GENERIC_READ,
                                FILE_SHARE_READ,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_HIDDEN,
                                NULL);

    // user changed the file name manually?
    if (hFile == INVALID_HANDLE_VALUE)
        return FALSE;

    FILETIME fileTime, dummyTime;
    ::GetFileTime(hFile, &fileTime, &dummyTime, &dummyTime);
    ::CloseHandle(hFile);

    WORD date;
    WORD time;

    // set a default date to hide the file modifications
    ::FileTimeToDosDateTime(&fileTime, &date, &time);

    // check if the filename has the same date and time
    if (date != 0x12c1 && time != 0x5000)
        // if not the user has changed manually the filename
        return FALSE;

    // the file date is valid
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedInfoFile::AllocateEntityTable()
{
    if (m_EntityTable.GetSize() || !m_TableEntries)
        return FALSE;

    for (std::size_t i = 0; i < m_TableEntries; ++i)
        m_EntityTable.Add(PSS_EncryptedLine());

    return m_EntityTable.GetSize();
}
//---------------------------------------------------------------------------
void PSS_EncryptedInfoFile::ReadEntityTable()
{
    if (!EntityTableExist())
        if (!AllocateEntityTable())
        {
            SetErrorStatus(TRUE);
            return;
        }

    PSS_File File(m_FileName);

    // file exists?
    if (!File.Exist())
    {
        SetErrorStatus(TRUE);
        return;
    }

    m_FileStream.open((const char*)m_FileName, std::ios::in, _SH_DENYNO);

    if (m_FileStream.rdstate() == std::ios::badbit || m_FileStream.rdstate() == std::ios::failbit)
    {
        SetErrorStatus(TRUE);
        return;
    }

    for (std::size_t i = 0; i < m_TableEntries; ++i)
    {
        char temp[1000];
        m_FileStream.getline(temp, sizeof(temp));
        m_EntityTable[i].SetEntity(temp);
    }

    m_FileStream.close();

    // is the default date correct?
    if (!IsFileDateValid())
    {
        SetErrorStatus(TRUE);
        return;
    }
}
//---------------------------------------------------------------------------
void PSS_EncryptedInfoFile::WriteEntityTable()
{
    if (!EntityTableExist())
    {
        SetErrorStatus(TRUE);
        return;
    }

    // remove hidden file attribute before open the file in write mode. Otherwise, open fails
    ::SetFileAttributes((const char*)m_FileName, ::GetFileAttributes((const char*)m_FileName) & ~FILE_ATTRIBUTE_HIDDEN);
      m_FileStream.open((const char*)m_FileName, std::ios::trunc | std::ios::out, _SH_DENYNO);
    
    if (m_FileStream.rdstate() == std::ios::badbit || m_FileStream.rdstate() == std::ios::failbit)
    {
        SetErrorStatus(TRUE);
        return;
    }

    for (std::size_t i = 0; i < m_TableEntries; ++i)
        m_FileStream << m_EntityTable[i].GetEntity() << std::endl;

    m_FileStream.close();

    // set a default date to hide the file modifications
    if (!SetValidFileDate())
    {
        SetErrorStatus(TRUE);
        return;
    }
}
//---------------------------------------------------------------------------
