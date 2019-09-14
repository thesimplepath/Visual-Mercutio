/****************************************************************************
 * ==> PSS_CryptedApplicationTypeInfoFile ----------------------------------*
 ****************************************************************************
 * Description : Provides a crypted application type info file              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CryptedApplicationTypeInfoFile.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
const std::size_t g_ApplicationTypeIndexFile = 5;
const std::size_t g_ProductKeyIndexFile      = 7;
const char        g_InvalidNoProductKey[]    = "xp0?ws5";
//---------------------------------------------------------------------------
// PSS_CryptedApplicationTypeInfoFile
//---------------------------------------------------------------------------
PSS_CryptedApplicationTypeInfoFile::PSS_CryptedApplicationTypeInfoFile(const CString& fileName) :
    ZBCriptedFileInfo(fileName),
    m_ApplicationType(IE_IT_Unknown)
{}
//---------------------------------------------------------------------------
PSS_CryptedApplicationTypeInfoFile::~PSS_CryptedApplicationTypeInfoFile()
{}
//---------------------------------------------------------------------------
BOOL PSS_CryptedApplicationTypeInfoFile::Initialize(const CString& fileName)
{
    ZBCriptedFileInfo::SetFilename(fileName);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedApplicationTypeInfoFile::CreateEmpty(const CString& fileName)
{
    ZBCriptedFileInfo::CreateEmptyFile(fileName);
    WriteApplicationType(IE_IT_Unknown);
    WriteProductKey(g_InvalidNoProductKey);
    return !ZBCriptedFileInfo::GetErrorStatus();
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedApplicationTypeInfoFile::CheckProductKey(const CString& productKey)
{
    const CString key = ReadProductKey();

    if (ZBCriptedFileInfo::GetErrorStatus())
        return FALSE;

    return (key == productKey);
}
//---------------------------------------------------------------------------
PSS_CryptedApplicationTypeInfoFile::IEType PSS_CryptedApplicationTypeInfoFile::ReadApplicationType()
{
    if (!ReadFileInfo())
        return IE_IT_Unknown;

    m_ApplicationType = IEType(ZBCriptedFileInfo::GetInt(g_ApplicationTypeIndexFile));

    if (ZBCriptedFileInfo::GetErrorStatus())
        m_ApplicationType = IE_IT_Unknown;

    return m_ApplicationType;
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedApplicationTypeInfoFile::WriteApplicationType(IEType value)
{
    ZBCriptedFileInfo::LoadEntityTable();

    if (ZBCriptedFileInfo::GetErrorStatus())
        return FALSE;

    ZBCriptedFileInfo::SetInt(int(value), g_ApplicationTypeIndexFile);

    if (ZBCriptedFileInfo::GetErrorStatus())
        return FALSE;

    if (!WriteFileInfo())
    {
        m_ApplicationType = IE_IT_Unknown;
        return FALSE;
    }

    // set the value
    m_ApplicationType = value;
    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_CryptedApplicationTypeInfoFile::ReadProductKey()
{
    if (!ReadFileInfo())
        return m_ProductKey = g_InvalidNoProductKey;

    m_ProductKey = ZBCriptedFileInfo::GetString(g_ProductKeyIndexFile);

    if (ZBCriptedFileInfo::GetErrorStatus())
        m_ProductKey = g_InvalidNoProductKey;

    return m_ProductKey;
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedApplicationTypeInfoFile::WriteProductKey(const CString& value)
{
    ZBCriptedFileInfo::LoadEntityTable();

    if (ZBCriptedFileInfo::GetErrorStatus())
    {
        m_ProductKey = g_InvalidNoProductKey;
        return FALSE;
    }

    ZBCriptedFileInfo::SetString(value, g_ProductKeyIndexFile);

    if (ZBCriptedFileInfo::GetErrorStatus())
        return FALSE;

    if (!WriteFileInfo())
    {
        m_ProductKey = g_InvalidNoProductKey;
        return FALSE;
    }

    // set the value
    m_ProductKey = value;
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedApplicationTypeInfoFile::ReadFileInfo()
{
    ZBCriptedFileInfo::LoadEntityTable();
    return !ZBCriptedFileInfo::GetErrorStatus();
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedApplicationTypeInfoFile::WriteFileInfo()
{
    ZBCriptedFileInfo::WriteEntityTable();
    return !ZBCriptedFileInfo::GetErrorStatus();
}
//---------------------------------------------------------------------------
