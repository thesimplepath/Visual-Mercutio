/****************************************************************************
 * ==> PSS_KeyFile ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file containing keys for licenses               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_KeyFile.h"

 //---------------------------------------------------------------------------
 // PSS_KeyEntity
 //---------------------------------------------------------------------------
PSS_KeyEntity::PSS_KeyEntity()
{}
//---------------------------------------------------------------------------
PSS_KeyEntity::~PSS_KeyEntity()
{
    std::srand((unsigned)time(NULL));
    GenerateRandomEntity();
}
//---------------------------------------------------------------------------
CString PSS_KeyEntity::GenerateRandomEntity()
{
    char buffer[60];
    ::sprintf_s(buffer,
                60,
                _T("%04d-%04d-%04d-%04d-%04d"),
                std::rand(),
                std::rand(),
                std::rand(),
                std::rand(),
                std::rand());

    m_Entity = buffer;
    return m_Entity;
}
//---------------------------------------------------------------------------
bool PSS_KeyEntity::IsEqual(const PSS_KeyEntity& entity) const
{
    return false;
}
//---------------------------------------------------------------------------
void PSS_KeyEntity::EncryptEntity()
{
    char* pKey = m_Entity.GetBuffer(60);

    for (; *pKey; ++pKey)
        *pKey ^= 100;

    m_Entity.ReleaseBuffer();
}
//---------------------------------------------------------------------------
// PSS_KeyFile
//---------------------------------------------------------------------------
PSS_KeyFile::PSS_KeyFile() :
    m_Count(1000)
{}
//---------------------------------------------------------------------------
PSS_KeyFile::PSS_KeyFile(const CString& fileName) :
    m_FileName(fileName),
    m_Count(0)
{}
//---------------------------------------------------------------------------
PSS_KeyFile::PSS_KeyFile(const CString& fileName, const CString& clearFileName, int count) :
    m_FileName(fileName),
    m_ClearFileName(clearFileName),
    m_Count(count)
{}
//---------------------------------------------------------------------------
PSS_KeyFile::~PSS_KeyFile()
{}
//---------------------------------------------------------------------------
BOOL PSS_KeyFile::GenerateFile()
{
    // create the first area
    for (int i = 0; i < m_Count; ++i)
        m_KeyEntityTable[i].GenerateRandomEntity();

    if (!WriteEntityTable(GetClearFileName()))
        return FALSE;

    for(int i = 0; i < m_Count; ++i)
        m_KeyEntityTable[i].EncryptEntity();

    return WriteEntityTable(GetFileName());
}
//---------------------------------------------------------------------------
BOOL PSS_KeyFile::IsKeyValid(const CString& key)
{
    if (!LoadSecurityTable(GetFileName()))
        return FALSE;

    for (int i = 0; i < m_Count; ++i)
    {
        m_KeyEntityTable[i].EncryptEntity();

        if (m_KeyEntityTable[i].GetEntity() == key)
            return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_KeyFile::WriteEntityTable(const CString& fileName)
{
    if (!m_SecurityFile.Open(fileName, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive))
        return FALSE;

    BOOL error = FALSE;

    TRY
    {
        for (int i = 0; i < m_Count; ++i)
            m_SecurityFile.WriteString(m_KeyEntityTable[i].GetEntity() + _T("\n"));
    }
    CATCH (CFileException, e)
    {
        error = TRUE;
    }
    END_CATCH

    TRY
    {
        m_SecurityFile.Close();
    }
    CATCH (CFileException, e)
    {
        error = TRUE;
    }
    END_CATCH

    return !error;
}
//---------------------------------------------------------------------------
BOOL PSS_KeyFile::LoadSecurityTable(const CString& fileName)
{
    // open the file
    if (!m_SecurityFile.Open(fileName, CFile::modeRead | CFile::shareDenyWrite))
        return FALSE;

    const int  maxElement = sizeof(m_KeyEntityTable) / sizeof(PSS_KeyEntity);
          BOOL error      = FALSE;
          BOOL end        = FALSE;
               m_Count    = 0;

    while (!end)
    {
        CString str;

        TRY
        {
            if (!m_SecurityFile.ReadString(str))
                end = TRUE;
        }
        CATCH (CFileException, e)
        {
            error = TRUE;
            break;
        }
        END_CATCH

        if (m_Count < maxElement)
            m_KeyEntityTable[m_Count].SetEntity(str);

        ++m_Count;
    }

    TRY
    {
        m_SecurityFile.Close();
    }
    CATCH (CFileException, e)
    {
        error = TRUE;
    }
    END_CATCH

    return !error;
}
//---------------------------------------------------------------------------
