/****************************************************************************
 * ==> PSS_File ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic file                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_File.h"

// std
#include <io.h>

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_File, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_File
//---------------------------------------------------------------------------
PSS_File::PSS_File() :
    CObject(),
    m_AttachmentType(IE_AT_InsertedFile)
{}
//---------------------------------------------------------------------------
PSS_File::PSS_File(const CString& fileName, IEAttachmentType attachment) :
    CObject(),
    m_FileName(fileName),
    m_AttachmentType(attachment)
{
    // if file:// defined, remove it
    if (!m_FileName.Left(7).CompareNoCase(_T("file://")))
        m_FileName = m_FileName.Right(m_FileName.GetLength() - 7);

    ::_splitpath(m_FileName, m_Drive, m_Dir, m_FileNameBuffer, m_FileExt);
}
//---------------------------------------------------------------------------
PSS_File::PSS_File(const PSS_File& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_File::~PSS_File()
{}
//---------------------------------------------------------------------------
const PSS_File& PSS_File::operator = (const PSS_File& other)
{
    m_FileName       = other.m_FileName;
    m_AttachmentType = other.m_AttachmentType;

    return *this;
}
//---------------------------------------------------------------------------
int PSS_File::operator == (const PSS_File& other) const
{
    return m_FileName == other.m_FileName;
}
//---------------------------------------------------------------------------
int PSS_File::operator!=(const PSS_File& other) const
{
    return m_FileName != other.m_FileName;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_File& file)
{
    ar >> file.m_FileName;

    WORD value;
    ar >> value;
    file.m_AttachmentType = PSS_File::IEAttachmentType(value);

    // build completely all file components
    file.Rebuild();

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_File& file)
{
    ar << file.m_FileName;
    ar << WORD(file.m_AttachmentType);

    return ar;
}
//---------------------------------------------------------------------------
void PSS_File::Rebuild()
{
    ::_splitpath(m_FileName, m_Drive, m_Dir, m_FileNameBuffer, m_FileExt);
    CString str(m_Dir);

    // if \\ at the end of path, remove it
    while (!str.IsEmpty() && str.GetAt(str.GetLength() - 1) == '\\')
        str = str.Left(str.GetLength() - 1);

    // rebuild the file name
    m_FileName  = m_Drive;
    m_FileName += str;
    m_FileName += _T("\\");
    m_FileName += m_FileNameBuffer;
    m_FileName += m_FileExt;
}
//---------------------------------------------------------------------------
CString PSS_File::GetCompleteFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_File::SetCompleteFileName(const CString& fileName, IEAttachmentType attachment)
{
    m_FileName       = fileName;
    m_AttachmentType = attachment;

    ::_splitpath(m_FileName, m_Drive, m_Dir, m_FileNameBuffer, m_FileExt);
}
//---------------------------------------------------------------------------
CString PSS_File::GetFileName() const
{
    CString str;
    str.Format(_T("%s%s"), m_FileNameBuffer, m_FileExt);

    return str;
}
//---------------------------------------------------------------------------
void PSS_File::SetFileName(const CString& fileName, IEAttachmentType attachement)
{
    m_FileName  = m_Drive;
    m_FileName += m_Dir;
    m_FileName += fileName;
}
//---------------------------------------------------------------------------
CString PSS_File::GetFilePath() const
{
    CString str;
    str.Format(_T("%s%s"), m_Drive, m_Dir);

    return str;
}
//---------------------------------------------------------------------------
void PSS_File::SetFilePath(const CString& path)
{
    m_FileName  = m_Drive;
    m_FileName += path;
    m_FileName += m_FileNameBuffer;
    m_FileName += m_FileExt;
}
//---------------------------------------------------------------------------
const char PSS_File::GetFileDrive() const
{
    return m_FileName[0];
}
//---------------------------------------------------------------------------
void PSS_File::SetFileDrive(const char drive)
{
    m_FileName  = drive;
    m_FileName += _T(":");
    m_FileName += m_Dir;
    m_FileName += m_FileNameBuffer;
    m_FileName += m_FileExt;
}
//---------------------------------------------------------------------------
CString PSS_File::GetDisplayName() const
{
    SHFILEINFO sfi;
    ::SHGetFileInfo(m_FileName, 0, &sfi, sizeof(SHFILEINFO), SHGFI_DISPLAYNAME);

    return sfi.szDisplayName;
}
//---------------------------------------------------------------------------
int PSS_File::GetIconIndex() const
{
    SHFILEINFO sfi;
    ::SHGetFileInfo(m_FileName, 0, &sfi, sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    return sfi.iIcon;
}
//---------------------------------------------------------------------------
CString PSS_File::GetFileTitle() const
{
    return m_FileNameBuffer;
}
//---------------------------------------------------------------------------
CString PSS_File::GetFileExt() const
{
    return m_FileExt;
}
//---------------------------------------------------------------------------
CString PSS_File::GetDescription() const
{
    SHFILEINFO sfi;
    ::SHGetFileInfo(m_FileName, 0, &sfi, sizeof(SHFILEINFO), SHGFI_TYPENAME);

    return sfi.szTypeName;
}
//---------------------------------------------------------------------------
BOOL PSS_File::Exist(const CString& fileName)
{
    // check for existence
    if ((::_access(fileName, 0)) != -1)
    {
        ::WIN32_FIND_DATA fd;
        CString           findPath = fileName;
        const int         slash    = findPath.ReverseFind(_T('\\'));
        const int         length   = findPath.GetLength();

        if (slash == length - 1)
            if (length == 3)
            {
                if (findPath.GetAt(1) == _T(':'))
                    return TRUE;
            }
            else
                findPath = findPath.Left(slash);

        HANDLE hFind = FindFirstFile(findPath, &fd);

        if (hFind != INVALID_HANDLE_VALUE)
            FindClose(hFind);

        return hFind != INVALID_HANDLE_VALUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_File::Exist() const
{
    return Exist(GetCompleteFileName());
}
//---------------------------------------------------------------------------
BOOL PSS_File::IsReadOnly() const
{
    CFileStatus rStatus;
    CFile::GetStatus(GetCompleteFileName(), rStatus);

    return rStatus.m_attribute & CFile::readOnly;
}
//---------------------------------------------------------------------------
BOOL PSS_File::SetReadOnly(BOOL readOnly)
{
    // read the file status
    CFileStatus rStatus;
    CFile::GetStatus(GetCompleteFileName(), rStatus);

    // no need to change?
    if (( readOnly && ((rStatus.m_attribute & CFile::readOnly) == 0)) ||
        (!readOnly && ((rStatus.m_attribute & CFile::readOnly) == 1)))
    {
        // otherwise, set the new file status
        if (readOnly)
            rStatus.m_attribute |=  CFile::readOnly;
        else
            rStatus.m_attribute &= ~CFile::readOnly;

        TRY
        {
            CFile::SetStatus(GetCompleteFileName(), rStatus);
        }
        CATCH (CFileException, e)
        {
            return FALSE;
        }
        END_CATCH
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_File::IsArchive() const
{
    CFileStatus rStatus;
    CFile::GetStatus(GetCompleteFileName(), rStatus);

    return rStatus.m_attribute & CFile::archive;
}
//---------------------------------------------------------------------------
BOOL PSS_File::SetArchive(BOOL archive)
{
    // read the file status
    CFileStatus rStatus;
    CFile::GetStatus(GetCompleteFileName(), rStatus);

    // no need to change?
    if (( archive && ((rStatus.m_attribute & CFile::archive) == 0)) ||
        (!archive && ((rStatus.m_attribute & CFile::archive) == 1)))
    {
        // otherwise, set the new file status
        if (archive)
            rStatus.m_attribute |=  CFile::archive;
        else
            rStatus.m_attribute &= ~CFile::archive;

        TRY
        {
            CFile::SetStatus(GetCompleteFileName(), rStatus);
        }
        CATCH (CFileException, e)
        {
            return FALSE;
        }
        END_CATCH
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_File::GetLastWriteTime(const CString& fileName, SYSTEMTIME& tm)
{
    FILETIME ftCreate, ftAccess, ftWrite, ftLocal;

    HANDLE hFile = GetFileHandle(fileName);

    if (!hFile)
        return FALSE;

    // get the file times for the file
    if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
        return FALSE;

    // convert the last-write time to local time
    if (!FileTimeToLocalFileTime(&ftWrite, &ftLocal))
        return FALSE;

    // convert the local file time from UTC to system time
    FileTimeToSystemTime(&ftLocal, &tm);

    // close the file handle before leaving the function, otherwise the handle remains open to the file
    // and the system will not be able to access the file further
    CloseHandle(hFile);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_File::GetLastWriteTime(SYSTEMTIME& tm) const
{
    return GetLastWriteTime(GetCompleteFileName(), tm);
}
//---------------------------------------------------------------------------
HANDLE PSS_File::GetFileHandle(const CString& fileName)
{
    HANDLE hFile = ::CreateFile(fileName,
                                GENERIC_READ,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);

    if (hFile != INVALID_HANDLE_VALUE)
        return hFile;

    return NULL;
}
//---------------------------------------------------------------------------
