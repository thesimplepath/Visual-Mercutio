/****************************************************************************
 * ==> PSS_Security --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the security basic features                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Security.h"

// processsoft
#include "zBaseLib\PSS_RegisterSetup.h"
#include "PSS_StopPrintDialog.h"
#include "PSS_EvaluationWarnDialog.h"

// Windows
#include <ShellApi.h>

//---------------------------------------------------------------------------
// Constant definition
//---------------------------------------------------------------------------
const int     g_CurrentVersion  = 1;
const int     g_PosDateStart    = 2;
const int     g_PosDateLast     = 8;
const int     g_PosCounterStart = 11;
const int     g_PosCounterLast  = 17;
const int     g_PosVersion      = 18;
const CString g_LastDate        = _T("LastDate");
const CString g_LastCounter     = _T("LastCounter");
const CString g_InitialValue    = _T("@@Initial$$Value");
const CString g_CheckString     = _T("VERS");
//---------------------------------------------------------------------------
// PSS_SecurityEntity
//---------------------------------------------------------------------------
PSS_SecurityEntity::PSS_SecurityEntity()
{}
//---------------------------------------------------------------------------
PSS_SecurityEntity::PSS_SecurityEntity(const CString& entity)
    : m_Entity(entity)
{}
//---------------------------------------------------------------------------
PSS_SecurityEntity::~PSS_SecurityEntity()
{
    std::srand(unsigned(time(NULL)));
    GenerateRandomEntity();
}
//---------------------------------------------------------------------------
CString PSS_SecurityEntity::GenerateRandomEntity()
{
    char buffer[20];
    ::sprintf_s(buffer, 20, "%04d%04d%04d", std::rand(), std::rand(), std::rand());
    m_Entity = buffer;

    EncryptEntity();

    return m_Entity;
}
//---------------------------------------------------------------------------
int PSS_SecurityEntity::GetCounter()
{
    // decrypt the entity
    EncryptEntity();

    const CString temp = m_Entity.Right(8);

    // extract the string number
    const CString strNum(temp, 4);

    return std::atoi(strNum);
}
//---------------------------------------------------------------------------
CString PSS_SecurityEntity::GenerateCounter(int counter)
{
    char buffer[20];
    ::sprintf_s(buffer, 20, "%04.04d", std::rand());

    // bug with the format length, cut it artificially
    buffer[4] = 0x00;
    m_Entity = buffer;

    // add the counter
    ::sprintf_s(buffer, 20, "%04.04d", counter);
    buffer[4] = 0x00;
    m_Entity += buffer;

    ::sprintf_s(buffer, 20, "%04.04d", std::rand());
    buffer[4] = 0x00;
    m_Entity += buffer;

    EncryptEntity();

    return m_Entity;
}
//---------------------------------------------------------------------------
CTime PSS_SecurityEntity::GetDate()
{
    // decrypt the entity
    EncryptEntity();

    // extract the day
    const CString day = m_Entity.Right(2);

    CString temp;

    // extract the month
    temp = m_Entity.Right(4);
    const CString month(temp, 2);

    // extract the year
    temp = m_Entity.Right(8);
    const CString year(temp, 4);

    return CTime(std::atoi(year), std::atoi(month), std::atoi(day), 0, 0, 0);
}
//---------------------------------------------------------------------------
CString PSS_SecurityEntity::GenerateDate(const CTime& date)
{
    char buffer[20];
    ::sprintf_s(buffer, 20, "%04.04d", std::rand());

    // bug with the format length, cut it artificially
    buffer[4] = 0x00;
    m_Entity  = buffer;

    ::sprintf_s(buffer, 20, "%04d%02d%02d", date.GetYear(), date.GetMonth(), date.GetDay());
    m_Entity += buffer;

    EncryptEntity();

    return m_Entity;
}
//---------------------------------------------------------------------------
int PSS_SecurityEntity::GetVersion()
{
    // decrypt the entity
    EncryptEntity();

    const CString temp  = m_Entity.Right(8);
    const CString check = m_Entity.Right(4);

    if (check != g_CheckString)
        return 0;

    // extract the string number
    const CString num(temp, 4);

    return std::atoi(num);
}
//---------------------------------------------------------------------------
CString PSS_SecurityEntity::GenerateVersion(int version)
{
    char buffer[20];
    ::sprintf_s(buffer, 20, "%04.04d", std::rand());

    // bug with the format length, cut it artificially
    buffer[4] = 0x00;
    m_Entity  = buffer;

    // Add the version
    ::sprintf_s(buffer, 20, "%04.04d", version);
    buffer[4]  = 0x00;
    m_Entity  += buffer;

    // add a stamp to differentiate new version
    m_Entity += g_CheckString;

    EncryptEntity();

    return m_Entity;
}
//---------------------------------------------------------------------------
void PSS_SecurityEntity::EncryptEntity()
{
    char* pKey = m_Entity.GetBuffer(30);

    for (; *pKey; ++pKey)
        *pKey ^= 140;

    m_Entity.ReleaseBuffer();
}
//---------------------------------------------------------------------------
// PSS_Security
//---------------------------------------------------------------------------
PSS_Security::PSS_Security() :
    m_Error(FALSE)
{}
//---------------------------------------------------------------------------
PSS_Security::PSS_Security(const CString&  fileName, const CString& appRegistryKey, const CString& appPID) :
    m_FileName(fileName),
    m_Key(appRegistryKey),
    m_PID(appPID),
    m_Error(FALSE)
{}
//---------------------------------------------------------------------------
PSS_Security::~PSS_Security()
{}
//---------------------------------------------------------------------------
int PSS_Security::GetCurrentVersion() const
{
    return g_CurrentVersion;
}
//---------------------------------------------------------------------------
BOOL PSS_Security::SetLastUseDate(const CTime& date)
{
    if (!LoadSecurityTable())
        return FALSE;

    // save the last used date
    m_SecurityEntityTable[g_PosDateLast].GenerateDate(date);

    return WriteEntityTable();
}
//---------------------------------------------------------------------------
BOOL PSS_Security::SetLastUseCounter(int counter)
{
    if (!LoadSecurityTable())
        return FALSE;

    // save the last counter
    m_SecurityEntityTable[g_PosCounterLast].GenerateCounter(counter);

    return WriteEntityTable();
}
//---------------------------------------------------------------------------
int PSS_Security::GetCounterSpan()
{
    if (!LoadSecurityTable())
        return -1;

    // get the initial counter
    const int start = m_SecurityEntityTable[g_PosCounterStart].GetCounter();

    // get the last counter
    const int last = m_SecurityEntityTable[g_PosCounterLast].GetCounter();

    return last - start;
}
//---------------------------------------------------------------------------
CTimeSpan PSS_Security::GetTimeSpan()
{
    if (!LoadSecurityTable())
        return CTimeSpan(25000);

    // get the initial date
    const CTime start = m_SecurityEntityTable[g_PosDateStart].GetDate();

    // get the last date
    const CTime last = m_SecurityEntityTable[g_PosDateLast].GetDate();

    // check if the start date and the last date is coherent
    if (last < start)
        // return 1 million of ellapsed days
        return CTimeSpan(1000000, 0, 0, 0);

    return last - start;
}
//---------------------------------------------------------------------------
BOOL PSS_Security::IncrementCounter()
{
    if (!LoadSecurityTable())
        return FALSE;

    // get the last counter
    const int last = m_SecurityEntityTable[g_PosCounterLast].GetCounter();

    // save the incremented counter
    m_SecurityEntityTable[g_PosCounterLast].GenerateCounter(last + 1);

    return WriteEntityTable();
}
//---------------------------------------------------------------------------
int PSS_Security::GetVersion()
{
    if (!LoadSecurityTable())
        return -1;

    // get the last counter
    const int version = m_SecurityEntityTable[g_PosVersion].GetVersion();

    if (GetError())
        return -1;

    return version;
}
//---------------------------------------------------------------------------
BOOL PSS_Security::SetVersion(int version)
{
    if (!LoadSecurityTable())
        return FALSE;

    // write the version
    m_SecurityEntityTable[g_PosVersion].GenerateVersion(version);

    return WriteEntityTable();
}
//---------------------------------------------------------------------------
void PSS_Security::ShowWarning()
{
    PSS_EvaluationWarnDialog dialog;
    dialog.DoModal();
}
//---------------------------------------------------------------------------
void PSS_Security::ShowStopWnd()
{
    PSS_StopPrintDialog dialog;

    if (dialog.DoModal() != IDCHANGE)
        return;

    // set the product code to the registry
    PSS_RegisterSetup registry;
    registry.CreateEntry(HKEY_LOCAL_MACHINE, m_Key, m_PID, dialog.GetCode());
}
//---------------------------------------------------------------------------
BOOL PSS_Security::Create()
{
    // populate the security entity table
    for (int i = 0; i < 20; ++i)
        m_SecurityEntityTable[i].GenerateRandomEntity();

    // save the initial date
    m_SecurityEntityTable[g_PosDateStart].GenerateDate(CTime::GetCurrentTime());

    // save the last used date
    m_SecurityEntityTable[g_PosDateLast].GenerateDate(CTime::GetCurrentTime());

    // save the initial counter
    m_SecurityEntityTable[g_PosCounterStart].GenerateCounter(0);

    // save the last counter
    m_SecurityEntityTable[g_PosCounterLast].GenerateCounter(0);

    // write the version
    m_SecurityEntityTable[g_PosVersion].GenerateVersion(g_CurrentVersion);
    WriteEntityTable();

    return !GetError();
}
//---------------------------------------------------------------------------
BOOL PSS_Security::WriteEntityTable()
{
    if (!m_SecurityFile.Open((const char*)GetSecurityFileName(), CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive))
    {
        SetError(TRUE);
        return !GetError();
    }

    TRY
    {
        for (int i = 0; i < 20; ++i)
            m_SecurityFile.WriteString(m_SecurityEntityTable[i].GetEntity() + "\n");
    }
    CATCH (CFileException, e)
    {
        SetError(TRUE);
    }
    END_CATCH

    TRY
    {
        m_SecurityFile.Close();
    }
    CATCH (CFileException, e)
    {
        SetError(TRUE);
    }
    END_CATCH

    return !GetError();
}
//---------------------------------------------------------------------------
BOOL PSS_Security::LoadSecurityTable()
{
    SetError(FALSE);

    // open the file
    if (!m_SecurityFile.Open((const char*)GetSecurityFileName(), CFile::modeRead | CFile::shareDenyWrite))
    {
        SetError(TRUE);
        return !m_Error;
    }

    for (int i = 0; i < 20; ++i)
    {
        CString str;

        TRY
        {
            m_SecurityFile.ReadString(str);
        }
        CATCH(CFileException, e)
        {
            SetError(TRUE);
            break;
        }
        END_CATCH

        m_SecurityEntityTable[i].SetEntity(str);
    }

    TRY
    {
        m_SecurityFile.Close();
    }
    CATCH(CFileException, e)
    {
        SetError(TRUE);
    }
    END_CATCH

    return !m_Error;
}
//---------------------------------------------------------------------------
CString PSS_Security::GetSecurityFileName() const
{
    char winDir[100];
    ::GetWindowsDirectory(winDir, sizeof(winDir));

    CString completeFileName(winDir);
    completeFileName += "\\" + m_FileName;

    return completeFileName;
}
//---------------------------------------------------------------------------
