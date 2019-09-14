/****************************************************************************
 * ==> PSS_EncryptedEvaluationAppInfoFile ----------------------------------*
 ****************************************************************************
 * Description : Provides an encrypted evaluation application info file     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_EncryptedEvaluationAppInfoFile.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
const std::size_t g_ProductKeyIndexFile       = 7;
const std::size_t g_InstallationDateIndexFile = 9;
const std::size_t g_LastDateUsageIndexFile    = 14;
const std::size_t g_ValidDateIndexFile        = 18;
const std::size_t g_DayCountIndexFile         = 22;
const char        g_InvalidNoProductKey[]     = "xp0?";
//---------------------------------------------------------------------------
// PSS_EncryptedEvaluationAppInfoFile
//---------------------------------------------------------------------------
PSS_EncryptedEvaluationAppInfoFile::PSS_EncryptedEvaluationAppInfoFile(const CString& fileName) :
    PSS_EncryptedInfoFile(fileName),
    m_DayCount(60)
{}
//---------------------------------------------------------------------------
PSS_EncryptedEvaluationAppInfoFile::~PSS_EncryptedEvaluationAppInfoFile()
{}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedEvaluationAppInfoFile::Initialize(const CString& fileName)
{
    SetFileName(fileName);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedEvaluationAppInfoFile::CreateEmpty(const CString& fileName)
{
    CreateEmptyFile(fileName);
    WriteProductKey(g_InvalidNoProductKey);
    WriteInstallationDate(ZBDate(time_t(0)));
    WriteDayCount(60);
    return !GetErrorStatus();
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedEvaluationAppInfoFile::InitializeFirstUse(int dayCount)
{
    if (!WriteInstallationDate(ZBDate::GetToday()))
        return FALSE;

    if (!WriteLastDateUsage(ZBDate::GetToday()))
        return FALSE;

    if (dayCount != -1)
        if (!WriteDayCount(dayCount))
            return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedEvaluationAppInfoFile::CheckProductKey(const CString& productKey)
{
    const CString key = ReadProductKey();

    if (GetErrorStatus() == TRUE)
        return FALSE;

    return (key == productKey);
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedEvaluationAppInfoFile::CheckExpiration()
{
    if (!ReadFileInfo())
        return FALSE;

    if (GetErrorStatus() == TRUE)
        return FALSE;

    m_LastDateUsage = GetDate(g_LastDateUsageIndexFile);
    ZBDate today    = ZBDate::GetToday();

    // check if today is earlier than the last usage date
    if (today < m_LastDateUsage)
        return FALSE;

    m_InstallationDate = GetDate(g_InstallationDateIndexFile);
    m_DayCount         = GetInt(g_DayCountIndexFile);

    ZBDate endDate = m_InstallationDate + COleDateTimeSpan(m_DayCount);

    // check if the expiration date has been reached
    if (endDate > today)
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_EncryptedEvaluationAppInfoFile::ReadProductKey()
{
    if (!ReadFileInfo())
        return m_ProductKey = g_InvalidNoProductKey;

    m_ProductKey = GetString(g_ProductKeyIndexFile);

    if (GetErrorStatus())
        m_ProductKey = g_InvalidNoProductKey;

    return m_ProductKey;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedEvaluationAppInfoFile::WriteProductKey(const CString& value)
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
ZBDate PSS_EncryptedEvaluationAppInfoFile::ReadInstallationDate()
{
    if (!ReadFileInfo())
        return m_InstallationDate = 0;

    m_InstallationDate = GetDate(g_InstallationDateIndexFile);

    if (GetErrorStatus())
        m_InstallationDate = 0;

    return m_InstallationDate;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedEvaluationAppInfoFile::WriteInstallationDate(const ZBDate& value)
{
    ReadEntityTable();

    if (GetErrorStatus())
        return FALSE;

    SetDate(m_InstallationDate, g_InstallationDateIndexFile);

    if (GetErrorStatus())
        return FALSE;

    if (!WriteFileInfo())
    {
        m_InstallationDate = 0;
        return FALSE;
    }

    // set the value
    m_InstallationDate = value;
    return TRUE;
}
//---------------------------------------------------------------------------
ZBDate PSS_EncryptedEvaluationAppInfoFile::ReadLastDateUsage()
{
    if (!ReadFileInfo())
        return m_LastDateUsage = 0;

    m_LastDateUsage = GetDate(g_LastDateUsageIndexFile);

    if (GetErrorStatus())
        m_LastDateUsage = 0;

    return m_LastDateUsage;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedEvaluationAppInfoFile::WriteLastDateUsage(const ZBDate& value)
{
    ReadEntityTable();

    if (GetErrorStatus())
        return FALSE;

    SetDate(m_LastDateUsage, g_LastDateUsageIndexFile);

    if (GetErrorStatus())
        return FALSE;

    if (!WriteFileInfo())
    {
        m_LastDateUsage = 0;
        return FALSE;
    }

    // set the value
    m_LastDateUsage = value;
    return TRUE;
}
//---------------------------------------------------------------------------
ZBDate PSS_EncryptedEvaluationAppInfoFile::ReadValidDate()
{
    if (!ReadFileInfo())
        return m_ValidDate = 0;

    m_ValidDate = GetDate(g_ValidDateIndexFile);

    if (GetErrorStatus())
        m_ValidDate = 0;

    return m_ValidDate;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedEvaluationAppInfoFile::WriteValidDate(ZBDate value)
{
    ReadEntityTable();

    if (GetErrorStatus())
        return FALSE;

    SetDate(m_ValidDate, g_ValidDateIndexFile);

    if (GetErrorStatus())
        return FALSE;

    if (!WriteFileInfo())
    {
        m_ValidDate = 0;
        return FALSE;
    }

    // set the value
    m_ValidDate = value;
    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_EncryptedEvaluationAppInfoFile::ReadDayCount()
{
    if (!ReadFileInfo())
        return m_DayCount = -1;

    m_DayCount = GetInt(g_DayCountIndexFile);

    if (GetErrorStatus())
        m_DayCount = -1;

    return m_DayCount;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedEvaluationAppInfoFile::WriteDayCount(int value)
{
    ReadEntityTable();

    if (GetErrorStatus())
    {
        m_DayCount = -1;
        return FALSE;
    }

    SetInt(value, g_DayCountIndexFile);

    if (GetErrorStatus())
    {
        m_DayCount = -1;
        return FALSE;
    }

    if (!WriteFileInfo())
    {
        m_DayCount = -1;
        return FALSE;
    }

    // set the value
    m_DayCount = value;
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedEvaluationAppInfoFile::ReadFileInfo()
{
    ReadEntityTable();
    return !GetErrorStatus();
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedEvaluationAppInfoFile::WriteFileInfo()
{
    WriteEntityTable();
    return !GetErrorStatus();
}
//---------------------------------------------------------------------------
