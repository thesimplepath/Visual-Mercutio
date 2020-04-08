/****************************************************************************
 * ==> PSS_SymbolStamp -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol stamp                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SymbolStamp.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_SymbolStamp, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_SymbolStamp
//---------------------------------------------------------------------------
PSS_SymbolStamp::PSS_SymbolStamp() :
    CObject(),
    m_SymbolVersion(1)
{}
//---------------------------------------------------------------------------
PSS_SymbolStamp::PSS_SymbolStamp(const PSS_SymbolStamp& other) :
    CObject(),
    m_SymbolVersion(1)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_SymbolStamp::~PSS_SymbolStamp()
{}
//---------------------------------------------------------------------------
const PSS_SymbolStamp& PSS_SymbolStamp::operator = (const PSS_SymbolStamp& other)
{
    m_Name                = other.m_Name;
    m_Description         = other.m_Description;
    m_ClassName           = other.m_ClassName;
    m_Category            = other.m_Category;
    m_Author              = other.m_Author;
    m_CreationDate        = other.m_CreationDate;
    m_ModificationDate    = other.m_ModificationDate;
    m_SymbolVersion       = other.m_SymbolVersion;
    m_InternalFileVersion = other.m_InternalFileVersion;

    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_SymbolStamp& stamp)
{
    ar >> stamp.m_InternalFileVersion;
    ar >> stamp.m_Name;
    ar >> stamp.m_Description;
    ar >> stamp.m_ClassName;
    ar >> stamp.m_Category;
    ar >> stamp.m_SymbolVersion;
    ar >> stamp.m_Author;
    ar >> stamp.m_CreationDate;
    ar >> stamp.m_ModificationDate;

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_SymbolStamp& stamp)
{
    ar << stamp.m_InternalFileVersion;
    ar << stamp.m_Name;
    ar << stamp.m_Description;
    ar << stamp.m_ClassName;
    ar << stamp.m_Category;
    ar << stamp.m_SymbolVersion;
    ar << stamp.m_Author;
    ar << stamp.m_CreationDate;
    ar << stamp.m_ModificationDate;

    return ar;
}
//---------------------------------------------------------------------------
PSS_SymbolStamp* PSS_SymbolStamp::Clone() const
{
    return new PSS_SymbolStamp(*this);
}
//---------------------------------------------------------------------------
DWORD PSS_SymbolStamp::IncrementPublishVersionOfFile(const CString& fileName)
{
    // if unable to read file, return error
    if (!ReadFromFile(fileName))
        return -1;

    // increment the file version
    ++m_SymbolVersion;

    // write the new version to the file. If unable to write file, return error
    if (!WriteToFile(fileName))
        return -1;

    return m_SymbolVersion;
}
//---------------------------------------------------------------------------
DWORD PSS_SymbolStamp::DecrementPublishVersionOfFile(const CString& fileName)
{
    // if unable to read file, return error
    if (!ReadFromFile(fileName))
        return -1;

    // decrement the file version
    if (m_SymbolVersion)
        --m_SymbolVersion;
    else
        return -1;

    // write the new version to the file. If unable to write file, return error
    if (!WriteToFile(fileName))
        return -1;

    return m_SymbolVersion;
}
//---------------------------------------------------------------------------
DWORD PSS_SymbolStamp::GetPublishVersionOfFile(const CString& fileName)
{
    // if the file was read successfully, return the published version
    if (ReadFromFile(fileName))
        return m_SymbolVersion;

    return -1;
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolStamp::SetPublishVersionOfFile(const CString& fileName, DWORD version)
{
    // if unable to read file, return error
    if (!ReadFromFile(fileName))
        return FALSE;

    // set the new file version
    m_SymbolVersion = version;

    // write the new version to the file. If unable to write file, return error
    if (!WriteToFile(fileName))
        return FALSE;

    return m_SymbolVersion;
}
//---------------------------------------------------------------------------
void PSS_SymbolStamp::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
        ar << *this;
    else
        ar >> *this;
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolStamp::ReadFromFile(const CString& fileName)
{
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    // create the archive
    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);

    loadArchive.m_pDocument  = NULL;
    loadArchive.m_bForceFlat = FALSE;

    TRY
    {
        loadArchive >> *this;
    }
    CATCH (CArchiveException, e)
    {
        loadArchive.Close();
        file.Close();
        return FALSE;
    }
    END_CATCH

    // close the archive
    loadArchive.Close();
    file.Close();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SymbolStamp::WriteToFile(const CString& fileName)
{
    CFile          file;
    CFileException fe;

    // read the file
    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    // file is open, read the status
    CFileStatus rStatus;

    if (!file.GetStatus(rStatus))
        return FALSE;

    // create the archive
    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);

    loadArchive.m_pDocument  = NULL;
    loadArchive.m_bForceFlat = FALSE;

    PSS_SymbolStamp dummyStamp;

    TRY
    {
        loadArchive >> dummyStamp;
    }
    CATCH (CArchiveException, e)
    {
        loadArchive.Close();
        file.Close();
        return FALSE;
    }
    END_CATCH

    // read the remaining information
    void* pFileBuffer;

    // allocate a new buffer with the file size
    pFileBuffer = std::malloc(std::size_t(rStatus.m_size));

    if (!pFileBuffer)
        return FALSE;

    try
    {
        // clear the buffer
        std::memset(pFileBuffer, 0, std::size_t(rStatus.m_size));

        UINT effectiveSize = 0;

        TRY
        {
            // read the information
            effectiveSize = loadArchive.Read(pFileBuffer, UINT(rStatus.m_size));
        }
        CATCH (CFileException, e)
        {
            std::free(pFileBuffer);

            // close the file and the archive
            loadArchive.Close();
            file.Close();

            return FALSE;
        }
        END_CATCH

        // close the file and the archive
        loadArchive.Close();
        file.Close();

        // write the new stamp
        if (!file.Open(fileName, CFile::modeWrite | CFile::shareDenyWrite, &fe))
            return FALSE;

        // create the save archive
        CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);

        saveArchive.m_pDocument = NULL;
        saveArchive.m_bForceFlat = FALSE;

        TRY
        {
            saveArchive << *this;
        }
        CATCH (CArchiveException, e)
        {
            saveArchive.Close();
            file.Close();
            return FALSE;
        }
        END_CATCH

        TRY
        {
            // save the information
            saveArchive.Write(pFileBuffer, effectiveSize);
        }
        CATCH (CFileException, e)
        {
            std::free(pFileBuffer);

            // close the file and the archive
            saveArchive.Close();
            file.Close();

            return FALSE;
        }
        END_CATCH

        saveArchive.Flush();

        // close the file and the archive
        saveArchive.Close();
        file.Close();
    }
    catch (...)
    {
        std::free(pFileBuffer);
        throw;
    }

    // free the buffer
    std::free(pFileBuffer);

    return TRUE;
}
//---------------------------------------------------------------------------
