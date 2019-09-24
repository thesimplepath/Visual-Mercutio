/****************************************************************************
 * ==> PSS_FolderStamp -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a folder stamp                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FolderStamp.h"

 //---------------------------------------------------------------------------
 // PSS_FolderStamp
 //---------------------------------------------------------------------------
PSS_FolderStamp::PSS_FolderStamp() :
    PSS_Stamp()
{}
//---------------------------------------------------------------------------
PSS_FolderStamp::PSS_FolderStamp(const PSS_FolderStamp& other) :
    PSS_Stamp()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_FolderStamp::~PSS_FolderStamp()
{}
//---------------------------------------------------------------------------
const PSS_FolderStamp& PSS_FolderStamp::operator = (const PSS_FolderStamp& other)
{
    PSS_Stamp::operator = ((inherited&)other);

    m_FolderName           = other.m_FolderName;
    m_FolderDescription    = other.m_FolderDescription;
    m_CreationUserName     = other.m_CreationUserName;
    m_ModificationUserName = other.m_ModificationUserName;
    m_Password             = other.m_Password;
    m_Key1                 = other.m_Key1;
    m_CreationDate         = other.m_CreationDate;
    m_ModificationDate     = other.m_ModificationDate;

    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_FolderStamp& stamp)
{
    ar >> (PSS_Stamp&)stamp;

    if (stamp.GetInternalVersion() >= 11)
    {
        ar >> stamp.m_FolderName;
        ar >> stamp.m_FolderDescription;
        ar >> stamp.m_CreationUserName;

        CTime time;

        // not yet in PSS_Date
        if (stamp.GetInternalVersion() < 14)
        {
            ar >> time;

            if (time.GetTime() >= 0)
                stamp.SetCreationDate(time);
        }
        else
            ar >> stamp.m_CreationDate;

        ar >> stamp.m_ModificationUserName;

        // not yet in PSS_Date
        if (stamp.GetInternalVersion() < 14)
        {
            ar >> time;

            if (time.GetTime() >= 0)
                stamp.SetModificationDate(time);
        }
        else
            ar >> stamp.m_ModificationDate;

        if (stamp.GetInternalVersion() < 13)
        {
            LONG    value;
            CString str;

            ar >> value;
            stamp.SetPublishVersion(value);

            ar >> time;

            if (time.GetTime() >= 0)
                stamp.SetPublishDate(time);

            ar >> str;
            stamp.SetPublishUser(str);
        }
    }

    if (stamp.GetInternalVersion() >= 14)
        ar >> stamp.m_Password;

    if (stamp.GetInternalVersion() >= 15)
        ar >> stamp.m_Key1;

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_FolderStamp& stamp)
{
    ar << (PSS_Stamp&)stamp;
    ar << stamp.m_FolderName;
    ar << stamp.m_FolderDescription;
    ar << stamp.m_CreationUserName;
    ar << stamp.m_CreationDate;
    ar << stamp.m_ModificationUserName;
    ar << stamp.m_ModificationDate;
    ar << stamp.m_Password;
    ar << stamp.m_Key1;

    return ar;
}
//---------------------------------------------------------------------------
PSS_FolderStamp* PSS_FolderStamp::Clone()
{
    std::unique_ptr<PSS_FolderStamp> pNewStamp(new PSS_FolderStamp(*this));
    return pNewStamp.release();
}
//---------------------------------------------------------------------------
BOOL PSS_FolderStamp::ReadFromFile(const CString& fileName)
{
    BOOL           result = FALSE;
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);

    loadArchive.m_pDocument  = NULL;
    loadArchive.m_bForceFlat = FALSE;

    WORD stamp = 0;

    TRY
    {
        loadArchive >> stamp;
    }
    CATCH (CArchiveException, e)
    {
        return FALSE;
    }
    END_CATCH

    // check if the stamp has been set correctly for next generation of files
    if (stamp == 0xFFFF)
    {
        loadArchive >> *this;
        result = TRUE;
    }

    loadArchive.Close();
    file.Close();

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_FolderStamp::ClearPassword()
{
    m_Password.Empty();
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_FolderStamp::SetPassword(const CString& password)
{
    m_Password = password;
    return TRUE;
}
//---------------------------------------------------------------------------
