/****************************************************************************
 * ==> PSS_File ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic file                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "File.h"

// std
#include <io.h>

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_File, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_File
//---------------------------------------------------------------------------
PSS_File::PSS_File() :
    m_AttachementType(IE_AT_InsertedFile)
{}
//---------------------------------------------------------------------------
PSS_File::PSS_File(const CString& fileName, IEAttachementType attachement) :
    m_FileName(fileName),
    m_AttachementType(attachement)
{
    // if file:// defined, remove it
    if (m_FileName.Left(7).CompareNoCase(_T("file://")) == 0)
        m_FileName = m_FileName.Right(m_FileName.GetLength() - 7);

    _splitpath(m_FileName, m_Drive, m_Dir, m_FileNameBuffer, m_FileExt);
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
    m_FileName        = other.m_FileName;
    m_AttachementType = other.m_AttachementType;

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
CArchive& operator>>(CArchive& ar, PSS_File& File)
{
    ar >> File.m_FileName;

    WORD wValue;
    ar >> wValue;
    File.m_AttachementType = (AttachementType)wValue;

    // Build completely all file components
    File.ReBuild();

    return ar;
    //## end ZFile::operator >>%933795312.body
}
//---------------------------------------------------------------------------
CArchive& operator<<(CArchive& ar, ZFile& File)
{
    //## begin ZFile::operator <<%933795313.body preserve=yes
    ar << File.m_FileName;
    ar << (WORD)File.m_AttachementType;

    return ar;
    //## end ZFile::operator <<%933795313.body
}
//---------------------------------------------------------------------------

//## Other Operations (implementation)
void ZFile::ReBuild()
{
    //## begin ZFile::ReBuild%940749602.body preserve=yes
    _splitpath(m_FileName, m_szDrive, m_szDir, m_szFname, m_szExt);
    CString s(m_szDir);

    // If \\ at the end of path, remove it
    // JMR-MODIF - Le 18 avril 2006 - Teste si la chaîne est vide avant de tenter d'extraire un caractère.
    while (!s.IsEmpty() && s.GetAt(s.GetLength() - 1) == '\\')
    {
        s = s.Left(s.GetLength() - 1);
    }

    // Rebuild the filename
    m_FileName = m_szDrive;
    m_FileName += s;
    m_FileName += _T("\\");
    m_FileName += m_szFname;
    m_FileName += m_szExt;
    //## end ZFile::ReBuild%940749602.body
}

CString ZFile::GetCompleteFileName() const
{
    return m_FileName;
}

void ZFile::SetCompleteFileName(const CString& fileName, IEAttachementType attachement)
{
    m_FileName        = fileName;
    m_AttachementType = Attachement;

    std::_splitpath(m_FileName, m_szDrive, m_szDir, m_szFname, m_szExt);
}

CString ZFile::GetFileName() const
{
    //## begin ZFile::GetFileName%933795307.body preserve=yes
    CString str;
    str.Format(_T("%s%s"), m_szFname, m_szExt);

    return str;
    //## end ZFile::GetFileName%933795307.body
}

void ZFile::SetFileName(const CString& fileName, IEAttachementType attachement)
{
    m_FileName  = m_szDrive;
    m_FileName += m_szDir;
    m_FileName += fileName;
}

CString ZFile::GetFilePath() const
{
    CString str;
    str.Format(_T("%s%s"), m_szDrive, m_szDir);

    return str;
}

void ZFile::SetFilePath(const CString& path)
{
    m_FileName = m_szDrive;
    m_FileName += path;
    m_FileName += m_szFname;
    m_FileName += m_szExt;
}

const char ZFile::GetFileDrive() const
{
    return m_FileName[0];
}

void ZFile::SetFileDrive(const char drive)
{
    m_FileName  = drive;
    m_FileName += _T(":");
    m_FileName += m_szDir;
    m_FileName += m_szFname;
    m_FileName += m_szExt;
}

CString ZFile::GetShowName() const
{
    //## begin ZFile::GetDisplayName%933795315.body preserve=yes
    SHFILEINFO sfi;

    ::SHGetFileInfo(m_FileName, 0, &sfi, sizeof(SHFILEINFO), SHGFI_DISPLAYNAME);

    return sfi.szDisplayName;
    //## end ZFile::GetDisplayName%933795315.body
}

int ZFile::GetIconIndex() const
{
    //## begin ZFile::GetIconIndex%933795316.body preserve=yes
    SHFILEINFO sfi;

    ::SHGetFileInfo(m_FileName, 0, &sfi, sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    return sfi.iIcon;
    //## end ZFile::GetIconIndex%933795316.body
}

CString ZFile::GetFileTitle() const
{
    //## begin ZFile::GetFileTitle%933795317.body preserve=yes
    return m_szFname;
    //## end ZFile::GetFileTitle%933795317.body
}

CString ZFile::GetFileExt() const
{
    //## begin ZFile::GetFileExt%933795318.body preserve=yes
    return m_szExt;
    //## end ZFile::GetFileExt%933795318.body
}

CString ZFile::GetDescription() const
{
    //## begin ZFile::GetDescription%933795319.body preserve=yes
    SHFILEINFO sfi;

    ::SHGetFileInfo(m_FileName, 0, &sfi, sizeof(SHFILEINFO), SHGFI_TYPENAME);

    return sfi.szTypeName;
    //## end ZFile::GetDescription%933795319.body
}

BOOL ZFile::Exist() const
{
    return ZFile::Exist(GetCompleteFileName());
}

BOOL ZFile::Exist(const CString& fileName) const
{
    // Check for existence
    if ((_access(Filename, 0)) != -1)
    {
        WIN32_FIND_DATA fd;

        CString    szFindPath = Filename;
        int        nSlash = szFindPath.ReverseFind(_T('\\'));
        int        nLength = szFindPath.GetLength();

        if (nSlash == nLength - 1)
        {
            if (nLength == 3)
            {
                if (szFindPath.GetAt(1) == _T(':'))
                {
                    return TRUE;
                }
            }
            else
            {
                szFindPath = szFindPath.Left(nSlash);
            }
        }

        HANDLE hFind = FindFirstFile(szFindPath, &fd);

        if (hFind != INVALID_HANDLE_VALUE)
        {
            FindClose(hFind);
        }

        return hFind != INVALID_HANDLE_VALUE;
    }

    return FALSE;
}

HANDLE ZFile::GetFileHandle(CString Filename)
{
    HANDLE hFile = CreateFile(Filename,
                              GENERIC_READ,
                              0,
                              NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        return hFile;
    }

    return NULL;
}

BOOL ZFile::IsReadOnly() const
{
    //## begin ZFile::IsReadOnly%941091645.body preserve=yes
    CFileStatus rStatus;
    CFile::GetStatus(GetCompleteFileName(), rStatus);

    return rStatus.m_attribute & CFile::readOnly;
    //## end ZFile::IsReadOnly%941091645.body
}

BOOL ZFile::SetReadOnly(BOOL ReadOnly)
{
    //## begin ZFile::SetReadOnly%941091646.body preserve=yes
    // First, read the file status
    CFileStatus rStatus;
    CFile::GetStatus(GetCompleteFileName(), rStatus);

    // If no need to change
    if ((ReadOnly == TRUE && ((rStatus.m_attribute & CFile::readOnly) == 0)) ||
        (ReadOnly == FALSE && ((rStatus.m_attribute & CFile::readOnly) == 1)))
    {
        // Otherwise, sets the new file status
        if (ReadOnly == TRUE)
        {
            rStatus.m_attribute |= CFile::readOnly;
        }
        else
        {
            rStatus.m_attribute &= ~CFile::readOnly;
        }

        TRY
        {
            CFile::SetStatus(GetCompleteFileName(), rStatus);
        }
            CATCH(CFileException, e)
        {
            return FALSE;
        }
        END_CATCH
    }

    return TRUE;
    //## end ZFile::SetReadOnly%941091646.body
}

BOOL ZFile::IsArchive() const
{
    //## begin ZFile::IsArchive%941091647.body preserve=yes
    CFileStatus rStatus;
    CFile::GetStatus(GetCompleteFileName(), rStatus);

    return rStatus.m_attribute & CFile::archive;
    //## end ZFile::IsArchive%941091647.body
}

BOOL ZFile::SetArchive(BOOL Archive)
{
    //## begin ZFile::SetArchive%941091648.body preserve=yes
    // First, read the file status
    CFileStatus rStatus;
    CFile::GetStatus(GetCompleteFileName(), rStatus);

    // If no need to change
    if ((Archive == TRUE && ((rStatus.m_attribute & CFile::archive) == 0)) ||
        (Archive == FALSE && ((rStatus.m_attribute & CFile::archive) == 1)))
    {
        // Otherwise, sets the new file status
        if (Archive == TRUE)
        {
            rStatus.m_attribute |= CFile::archive;
        }
        else
        {
            rStatus.m_attribute &= ~CFile::archive;
        }

        TRY
        {
            CFile::SetStatus(GetCompleteFileName(), rStatus);
        }
            CATCH(CFileException, e)
        {
            return FALSE;
        }
        END_CATCH
    }

    return TRUE;
    //## end ZFile::SetArchive%941091648.body
}

BOOL ZFile::GetLastWriteTime(SYSTEMTIME& tm)
{
    return ZFile::GetLastWriteTime(GetCompleteFileName(), tm);
}

BOOL ZFile::GetLastWriteTime(CString Filename, SYSTEMTIME& tm)
{
    FILETIME ftCreate, ftAccess, ftWrite, ftLocal;

    HANDLE hFile = ZFile::GetFileHandle(Filename);

    if (hFile == NULL)
    {
        return FALSE;
    }

    // Retrieve the file times for the file.
    if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
    {
        return FALSE;
    }

    // Convert the last-write time to local time.
    if (!FileTimeToLocalFileTime(&ftWrite, &ftLocal))
    {
        return FALSE;
    }

    // Convert the local file time from UTC to system time.
    FileTimeToSystemTime(&ftLocal, &tm);

    // Close the file handle before leaving the function
    // otherwise, we have an open handle to a file and the system
    // will not be able to access the file further
    CloseHandle(hFile);

    return TRUE;
}

// Additional Declarations

//## begin ZFile%37A8A5510200.declarations preserve=yes
//## end ZFile%37A8A5510200.declarations

//## begin module%36754E560054.epilog preserve=yes
//## end module%36754E560054.epilog
