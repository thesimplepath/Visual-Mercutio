/****************************************************************************
 * ==> PSS_EncryptedApplicationTypeInfoFile --------------------------------*
 ****************************************************************************
 * Description : Provides an encrypted application type info file           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_EncryptedApplicationTypeInfoFile.h"

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
// PSS_EncryptedApplicationTypeInfoFile
//---------------------------------------------------------------------------
PSS_EncryptedApplicationTypeInfoFile::PSS_EncryptedApplicationTypeInfoFile(const CString& fileName) :
    PSS_EncryptedInfoFile(fileName),
    m_ApplicationType(IE_IT_Unknown)
{}
//---------------------------------------------------------------------------
PSS_EncryptedApplicationTypeInfoFile::~PSS_EncryptedApplicationTypeInfoFile()
{}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedApplicationTypeInfoFile::Initialize(const CString& fileName)
{
    SetFileName(fileName);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedApplicationTypeInfoFile::CreateEmpty(const CString& fileName)
{
    CreateEmptyFile(fileName);
    WriteApplicationType(IE_IT_Unknown);
    WriteProductKey(g_InvalidNoProductKey);
    return !GetErrorStatus();
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedApplicationTypeInfoFile::CheckProductKey(const CString& productKey)
{
    const CString key = ReadProductKey();

    if (GetErrorStatus())
        return FALSE;

    return (key == productKey);
}
//---------------------------------------------------------------------------
PSS_EncryptedApplicationTypeInfoFile::IEType PSS_EncryptedApplicationTypeInfoFile::ReadApplicationType()
{
    if (!ReadFileInfo())
        return IE_IT_Unknown;

    m_ApplicationType = IEType(GetInt(g_ApplicationTypeIndexFile));

    if (GetErrorStatus())
        m_ApplicationType = IE_IT_Unknown;

    return m_ApplicationType;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedApplicationTypeInfoFile::WriteApplicationType(IEType value)
{
    ReadEntityTable();

    if (GetErrorStatus())
        return FALSE;

    SetInt(int(value), g_ApplicationTypeIndexFile);

    if (GetErrorStatus())
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
CString PSS_EncryptedApplicationTypeInfoFile::ReadProductKey()
{
    if (!ReadFileInfo())
        return m_ProductKey = g_InvalidNoProductKey;

    m_ProductKey = GetString(g_ProductKeyIndexFile);

    if (GetErrorStatus())
        m_ProductKey = g_InvalidNoProductKey;

    return m_ProductKey;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedApplicationTypeInfoFile::WriteProductKey(const CString& value)
{
    ReadEntityTable();

    if (GetErrorStatus())
    {
        m_ProductKey = g_InvalidNoProductKey;
        return FALSE;
    }

    SetString(value, g_ProductKeyIndexFile);

    if (GetErrorStatus())
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
BOOL PSS_EncryptedApplicationTypeInfoFile::ReadFileInfo()
{
    ReadEntityTable();
    return !GetErrorStatus();
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedApplicationTypeInfoFile::WriteFileInfo()
{
    WriteEntityTable();
    return !GetErrorStatus();
}
//---------------------------------------------------------------------------
