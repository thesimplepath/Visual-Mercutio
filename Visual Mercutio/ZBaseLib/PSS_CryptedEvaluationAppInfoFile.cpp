/****************************************************************************
 * ==> PSS_CryptedEvaluationAppInfoFile ------------------------------------*
 ****************************************************************************
 * Description : Provides a crypted evaluation application info file        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CryptedEvaluationAppInfoFile.h"

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
// PSS_CryptedEvaluationAppInfoFile
//---------------------------------------------------------------------------
PSS_CryptedEvaluationAppInfoFile::PSS_CryptedEvaluationAppInfoFile(const CString& fileName)
    : ZBCriptedFileInfo(fileName),
    m_DayCount(60)
{}
//---------------------------------------------------------------------------
PSS_CryptedEvaluationAppInfoFile::~PSS_CryptedEvaluationAppInfoFile()
{}
//---------------------------------------------------------------------------
BOOL PSS_CryptedEvaluationAppInfoFile::Initialize(const CString& fileName)
{
    ZBCriptedFileInfo::SetFilename(fileName);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedEvaluationAppInfoFile::CreateEmpty(const CString& fileName)
{
    ZBCriptedFileInfo::CreateEmptyFile(fileName);
    WriteProductKey(g_InvalidNoProductKey);
    WriteInstallationDate(ZBDate(time_t(0)));
    WriteDayCount(60);
    return !ZBCriptedFileInfo::GetErrorStatus();
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedEvaluationAppInfoFile::InitializeFirstUse(int dayCount)
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
BOOL PSS_CryptedEvaluationAppInfoFile::CheckProductKey(const CString& productKey)
{
    const CString key = ReadProductKey();

    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        return FALSE;

    return (key == productKey);
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedEvaluationAppInfoFile::CheckExpiration()
{
    if (!ReadFileInfo())
        return FALSE;

    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        return FALSE;

    m_LastDateUsage = ZBCriptedFileInfo::GetDate(g_LastDateUsageIndexFile);
    ZBDate today    = ZBDate::GetToday();

    // check if today is earlier than the last usage date
    if (today < m_LastDateUsage)
        return FALSE;

    m_InstallationDate = ZBCriptedFileInfo::GetDate(g_InstallationDateIndexFile);
    m_DayCount         = ZBCriptedFileInfo::GetInt(g_DayCountIndexFile);

    ZBDate endDate = m_InstallationDate + COleDateTimeSpan(m_DayCount);

    // check if the expiration date has been reached
    if (endDate > today)
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_CryptedEvaluationAppInfoFile::ReadProductKey()
{
    if (!ReadFileInfo())
        return m_ProductKey = g_InvalidNoProductKey;

    m_ProductKey = ZBCriptedFileInfo::GetString(g_ProductKeyIndexFile);

    if (ZBCriptedFileInfo::GetErrorStatus())
        m_ProductKey = g_InvalidNoProductKey;

    return m_ProductKey;
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedEvaluationAppInfoFile::WriteProductKey(const CString& value)
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
ZBDate PSS_CryptedEvaluationAppInfoFile::ReadInstallationDate()
{
    if (!ReadFileInfo())
        return m_InstallationDate = 0;

    m_InstallationDate = ZBCriptedFileInfo::GetDate(g_InstallationDateIndexFile);

    if (ZBCriptedFileInfo::GetErrorStatus())
        m_InstallationDate = 0;

    return m_InstallationDate;
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedEvaluationAppInfoFile::WriteInstallationDate(const ZBDate& value)
{
    ZBCriptedFileInfo::LoadEntityTable();

    if (ZBCriptedFileInfo::GetErrorStatus())
        return FALSE;

    ZBCriptedFileInfo::SetDate(m_InstallationDate, g_InstallationDateIndexFile);

    if (ZBCriptedFileInfo::GetErrorStatus())
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
ZBDate PSS_CryptedEvaluationAppInfoFile::ReadLastDateUsage()
{
    if (!ReadFileInfo())
        return m_LastDateUsage = 0;

    m_LastDateUsage = ZBCriptedFileInfo::GetDate(g_LastDateUsageIndexFile);

    if (ZBCriptedFileInfo::GetErrorStatus())
        m_LastDateUsage = 0;

    return m_LastDateUsage;
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedEvaluationAppInfoFile::WriteLastDateUsage(const ZBDate& value)
{
    ZBCriptedFileInfo::LoadEntityTable();

    if (ZBCriptedFileInfo::GetErrorStatus())
        return FALSE;

    ZBCriptedFileInfo::SetDate(m_LastDateUsage, g_LastDateUsageIndexFile);

    if (ZBCriptedFileInfo::GetErrorStatus())
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
ZBDate PSS_CryptedEvaluationAppInfoFile::ReadValidDate()
{
    if (!ReadFileInfo())
        return m_ValidDate = 0;

    m_ValidDate = ZBCriptedFileInfo::GetDate(g_ValidDateIndexFile);

    if (ZBCriptedFileInfo::GetErrorStatus())
        m_ValidDate = 0;

    return m_ValidDate;
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedEvaluationAppInfoFile::WriteValidDate(ZBDate value)
{
    ZBCriptedFileInfo::LoadEntityTable();

    if (ZBCriptedFileInfo::GetErrorStatus())
        return FALSE;

    ZBCriptedFileInfo::SetDate(m_ValidDate, g_ValidDateIndexFile);

    if (ZBCriptedFileInfo::GetErrorStatus())
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
int PSS_CryptedEvaluationAppInfoFile::ReadDayCount()
{
    if (!ReadFileInfo())
        return m_DayCount = -1;

    m_DayCount = ZBCriptedFileInfo::GetInt(g_DayCountIndexFile);

    if (ZBCriptedFileInfo::GetErrorStatus())
        m_DayCount = -1;

    return m_DayCount;
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedEvaluationAppInfoFile::WriteDayCount(int value)
{
    ZBCriptedFileInfo::LoadEntityTable();

    if (ZBCriptedFileInfo::GetErrorStatus())
    {
        m_DayCount = -1;
        return FALSE;
    }

    ZBCriptedFileInfo::SetInt(value, g_DayCountIndexFile);

    if (ZBCriptedFileInfo::GetErrorStatus())
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
BOOL PSS_CryptedEvaluationAppInfoFile::ReadFileInfo()
{
    ZBCriptedFileInfo::LoadEntityTable();
    return !ZBCriptedFileInfo::GetErrorStatus();
}
//---------------------------------------------------------------------------
BOOL PSS_CryptedEvaluationAppInfoFile::WriteFileInfo()
{
    ZBCriptedFileInfo::WriteEntityTable();
    return !ZBCriptedFileInfo::GetErrorStatus();
}
//---------------------------------------------------------------------------
