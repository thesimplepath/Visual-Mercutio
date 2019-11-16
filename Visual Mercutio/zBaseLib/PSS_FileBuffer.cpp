/****************************************************************************
 * ==> PSS_FileBuffer ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file buffer                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FileBuffer.h"

// processsoft
#include "PSS_FileManager.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_FileBuffer, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_FileBuffer
//---------------------------------------------------------------------------
PSS_FileBuffer::PSS_FileBuffer(const CString& fileName) :
    m_pBuffer(NULL),
    m_Size(0)
{
    if (!fileName.IsEmpty())
        CreateBufferFromFile(fileName);
}
//---------------------------------------------------------------------------
PSS_FileBuffer::PSS_FileBuffer(PSS_File& File) :
    m_pBuffer(NULL),
    m_Size(0)
{
    CreateBufferFromFile(File);
}
//---------------------------------------------------------------------------
PSS_FileBuffer::PSS_FileBuffer(const PSS_FileBuffer& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_FileBuffer::~PSS_FileBuffer()
{
    // the fully qualified name is required to avoid pure virtual function calling
    PSS_FileBuffer::Close();
}
//---------------------------------------------------------------------------
const PSS_FileBuffer& PSS_FileBuffer::operator = (const PSS_FileBuffer& other)
{
    Close();

    m_File = other.m_File;
    m_Size = other.m_Size;

    try
    {
        if (m_Size)
            m_pBuffer = std::malloc(m_Size);

        if (m_pBuffer)
            std::memcpy(m_pBuffer, ((PSS_FileBuffer&)other).GetFileBuffer(), other.GetBufferSize());
    }
    catch (...)
    {
        if (m_pBuffer)
            std::free(m_pBuffer);

        m_Size = 0;
    }

    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_FileBuffer& fileBuffer)
{
    fileBuffer.Close();

    ar >> fileBuffer.m_File;
    ar >> fileBuffer.m_Size;

    // found serialized binary information?
    if (fileBuffer.m_Size > 0)
    {
        fileBuffer.m_pBuffer = std::malloc(fileBuffer.m_Size);

        if (fileBuffer.m_pBuffer)
        {
            // clear the buffer
            std::memset(fileBuffer.m_pBuffer, 0, fileBuffer.m_Size);

            // read binary information
            ar.Read(fileBuffer.m_pBuffer, fileBuffer.m_Size);
        }
    }

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_FileBuffer& fileBuffer)
{
    ar << fileBuffer.m_File;
    ar << fileBuffer.m_Size;

    // do serialize binary information?
    if (fileBuffer.m_Size > 0)
        // write binary information
        ar.Write(fileBuffer.m_pBuffer, fileBuffer.m_Size);

    return ar;
}
//---------------------------------------------------------------------------
BOOL PSS_FileBuffer::CreateBufferFromFile(const CString& fileName)
{
    return CreateBufferFromFile(PSS_File(fileName));
}
//---------------------------------------------------------------------------
BOOL PSS_FileBuffer::CreateBufferFromFile(PSS_File& File)
{
    m_File = File;
    return CreateBufferFromFile();
}
//---------------------------------------------------------------------------
BOOL PSS_FileBuffer::CreateBufferFromFile()
{
    // file exists?
    if (!m_File.Exist())
        return FALSE;

    // rebuild all data members
    m_File.Rebuild();

    CFile file;

    TRY
    {
        // open file in read mode
        if (!file.Open(m_File.GetCompleteFileName(), CFile::modeRead | CFile::typeBinary))
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

    CFileStatus rStatus;

    // file is now opened, get its status
    if (!file.GetStatus(rStatus))
        return FALSE;

    Close();

    // allocate a new buffer with the file size
    m_pBuffer = std::malloc(std::size_t(rStatus.m_size + 1));

    if (!m_pBuffer)
        return FALSE;

    // clear the buffer
    std::memset(m_pBuffer, 0, std::size_t(rStatus.m_size + 1));
    m_Size = std::size_t(rStatus.m_size + 1);

    // read chars from the file
    const UINT readChar = file.Read(m_pBuffer, UINT(rStatus.m_size));

    // check the number of char read from file
    if (readChar != rStatus.m_size)
    {
        Close();
        return FALSE;
    }

    // otherwise, everthing ok, close the file
    TRY
    {
        file.Close();
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << _T("File could not be opened ") << e->m_cause << _T("\n");
        #endif
    }
    END_CATCH

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_FileBuffer::CreateFileFromBuffer(const CString& fileName)
{
    CFile file;

    TRY
    {
        // open a file in read mode
        if (!file.Open(fileName, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate))
            return _T("");
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << _T("File could not be opened ") << e->m_cause << _T("\n");
        #endif

        return _T("");
    }
    END_CATCH

    TRY
    {
        // write the buffer to the file
        file.Write(m_pBuffer, m_Size - 1);
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << _T("File could not be opened ") << e->m_cause << _T("\n");
        #endif

        file.Close();
        return _T("");
    }
    END_CATCH

    // otherwise, everthing ok, close the file
    TRY
    {
        file.Close();
    }
    CATCH (CFileException, e)
    {
        #ifdef _DEBUG
            afxDump << _T("File could not be opened ") << e->m_cause << _T("\n");
        #endif
    }
    END_CATCH

    return fileName;
}
//---------------------------------------------------------------------------
CString PSS_FileBuffer::CreateFileFromBuffer(PSS_File& File)
{
    return CreateFileFromBuffer(File.GetCompleteFileName());
}
//---------------------------------------------------------------------------
CString PSS_FileBuffer::CreateFileFromBuffer()
{
    return CreateFileFromBuffer(m_File);
}
//---------------------------------------------------------------------------
CString PSS_FileBuffer::CreateTemporaryFileFromBuffer()
{
    PSS_FileManager fileManager;

    return CreateFileFromBuffer
            (fileManager.GetTemporaryFileName(fileManager.GetTemporaryPath(),
                                              _T(""),
                                              m_File.GetFileExt()));
}
//---------------------------------------------------------------------------
void PSS_FileBuffer::Close()
{
    if (m_pBuffer)
        std::free(m_pBuffer);

    m_pBuffer = NULL;
    m_Size    = 0;
}
//---------------------------------------------------------------------------
PSS_FileBuffer* PSS_FileBuffer::Clone()
{
    std::unique_ptr<PSS_FileBuffer> pFileBuffer(new PSS_FileBuffer(*this));
    return pFileBuffer.release();
}
//---------------------------------------------------------------------------
void PSS_FileBuffer::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
        ar << *this;
    else
        ar >> *this;
}
//---------------------------------------------------------------------------
