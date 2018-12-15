// ZBCriptedFileEvaluationAppInfo.cpp: implementation of the ZBCriptedFileEvaluationAppInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBCriptedFileEvaluationAppInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const size_t ProductKeyIndexFile = 7;
const size_t InstallationDateIndexFile = 9;
const size_t LastDateUsageIndexFile = 14;
const size_t ValidDateIndexFile = 18;
const size_t TotalDaysIndexFile = 22;

const char     InvalidNoProductKey[] = "xp0?";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBCriptedFileEvaluationAppInfo::ZBCriptedFileEvaluationAppInfo(const CString Filename /*= ""*/)
: ZBCriptedFileInfo(Filename), m_TotalDays(60)
{

}

ZBCriptedFileEvaluationAppInfo::~ZBCriptedFileEvaluationAppInfo()
{

}


BOOL    ZBCriptedFileEvaluationAppInfo::Initialize( const CString Filename )
{
    ZBCriptedFileInfo::SetFilename( Filename );
    return TRUE;
}

BOOL    ZBCriptedFileEvaluationAppInfo::CreateEmpty( const CString Filename )
{
    ZBCriptedFileInfo::CreateEmptyFile( Filename );
    ZBCriptedFileEvaluationAppInfo::WriteProductKey( InvalidNoProductKey );
    ZBCriptedFileEvaluationAppInfo::WriteInstallationDate( ZBDate( time_t(0) ) );
    ZBCriptedFileEvaluationAppInfo::WriteTotalDays( 60 );
    return !ZBCriptedFileInfo::GetErrorStatus();
}


BOOL    ZBCriptedFileEvaluationAppInfo::InitializeFirstUse( int NumberOfDays /*= -1*/ )
{
    if (!WriteInstallationDate( ZBDate::GetToday() ))
        return FALSE;
    if (!WriteLastDateUsage( ZBDate::GetToday() ))
        return FALSE;

    if (NumberOfDays != -1)
    {
        if (!WriteTotalDays( NumberOfDays ))
            return FALSE;
    }
    return TRUE;
}

BOOL    ZBCriptedFileEvaluationAppInfo::CheckProductKey( CString ProductKey )
{
    CString Key = LoadProductKey();
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        return FALSE;
    return Key == ProductKey;
}

BOOL    ZBCriptedFileEvaluationAppInfo::CheckExpiration()
{
    if (!ReadFileInfo())
        return FALSE;
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        return FALSE;
    m_LastDateUsage = ZBCriptedFileInfo::GetDate( LastDateUsageIndexFile );
    ZBDate    Today = ZBDate::GetToday();
    // Check if today is earlier than the last usage date
    if (Today < m_LastDateUsage)
        return FALSE; // Error
    m_InstallationDate = ZBCriptedFileInfo::GetDate( InstallationDateIndexFile );
    m_TotalDays = ZBCriptedFileInfo::GetInt( TotalDaysIndexFile );

    ZBDate    EndDate = m_InstallationDate + COleDateTimeSpan( m_TotalDays );
    // Check if the expiration date has been reached
    if (EndDate > Today)
        return FALSE; // Error

    return TRUE;
}



BOOL    ZBCriptedFileEvaluationAppInfo::ReadFileInfo()
{
    ZBCriptedFileInfo::LoadEntityTable();
    return !ZBCriptedFileInfo::GetErrorStatus();
}

BOOL    ZBCriptedFileEvaluationAppInfo::WriteFileInfo()
{
    ZBCriptedFileInfo::WriteEntityTable();
    return !ZBCriptedFileInfo::GetErrorStatus();
}



CString    ZBCriptedFileEvaluationAppInfo::LoadProductKey()
{
    if (!ReadFileInfo())
        return m_ProductKey = InvalidNoProductKey;
    m_ProductKey = ZBCriptedFileInfo::GetString( ProductKeyIndexFile );
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        m_ProductKey = InvalidNoProductKey;
    return m_ProductKey;
}

BOOL    ZBCriptedFileEvaluationAppInfo::WriteProductKey( CString value )
{
    ZBCriptedFileInfo::LoadEntityTable();
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
    {
        m_ProductKey = InvalidNoProductKey;
        return FALSE;
    }
    ZBCriptedFileInfo::SetString( value, ProductKeyIndexFile );
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        return FALSE;
    if (!WriteFileInfo())
    {
        m_ProductKey = InvalidNoProductKey;
        return FALSE;
    }
    // finally assign the value
    m_ProductKey = value;
    return TRUE;
}

ZBDate    ZBCriptedFileEvaluationAppInfo::LoadInstallationDate()
{
    if (!ReadFileInfo())
        return m_InstallationDate = 0;
    m_InstallationDate = ZBCriptedFileInfo::GetDate( InstallationDateIndexFile );
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        m_InstallationDate = 0;
    return m_InstallationDate;
}

BOOL    ZBCriptedFileEvaluationAppInfo::WriteInstallationDate( ZBDate value )
{
    ZBCriptedFileInfo::LoadEntityTable();
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        return FALSE;
    ZBCriptedFileInfo::SetDate( m_InstallationDate, InstallationDateIndexFile );
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        return FALSE;
    if (!WriteFileInfo())
    {
        m_InstallationDate = 0;
        return FALSE;
    }
    // finally assign the value
    m_InstallationDate = value;
    return TRUE;
}

ZBDate    ZBCriptedFileEvaluationAppInfo::LoadLastDateUsage()
{
    if (!ReadFileInfo())
        return m_LastDateUsage = 0;
    m_LastDateUsage = ZBCriptedFileInfo::GetDate( LastDateUsageIndexFile );
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        m_LastDateUsage = 0;
    return m_LastDateUsage;
}

BOOL    ZBCriptedFileEvaluationAppInfo::WriteLastDateUsage( ZBDate value )
{
    ZBCriptedFileInfo::LoadEntityTable();
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        return FALSE;
    ZBCriptedFileInfo::SetDate( m_LastDateUsage, LastDateUsageIndexFile );
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        return FALSE;
    if (!WriteFileInfo())
    {
        m_LastDateUsage = 0;
        return FALSE;
    }
    // finally assign the value
    m_LastDateUsage = value;
    return TRUE;
}

ZBDate    ZBCriptedFileEvaluationAppInfo::LoadValidDate()
{
    if (!ReadFileInfo())
        return m_ValidDate = 0;
    m_ValidDate = ZBCriptedFileInfo::GetDate( ValidDateIndexFile );
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        m_ValidDate = 0;
    return m_ValidDate;
}

BOOL    ZBCriptedFileEvaluationAppInfo::WriteValidDate( ZBDate value )
{
    ZBCriptedFileInfo::LoadEntityTable();
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        return FALSE;
    ZBCriptedFileInfo::SetDate( m_ValidDate, ValidDateIndexFile );
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        return FALSE;
    if (!WriteFileInfo())
    {
        m_ValidDate = 0;
        return FALSE;
    }
    // finally assign the value
    m_ValidDate = value;
    return TRUE;
}


int        ZBCriptedFileEvaluationAppInfo::LoadTotalDays()
{
    if (!ReadFileInfo())
        return m_TotalDays = -1;
    m_TotalDays = ZBCriptedFileInfo::GetInt( TotalDaysIndexFile );
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
        m_TotalDays = -1;
    return m_TotalDays;
}

BOOL    ZBCriptedFileEvaluationAppInfo::WriteTotalDays( int value )
{
    ZBCriptedFileInfo::LoadEntityTable();
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
    {
        m_TotalDays = -1;
        return FALSE;
    }
    ZBCriptedFileInfo::SetInt( value, TotalDaysIndexFile );
    if (ZBCriptedFileInfo::GetErrorStatus() == TRUE)
    {
        m_TotalDays = -1;
        return FALSE;
    }
    if (!WriteFileInfo())
    {
        m_TotalDays = -1;
        return FALSE;
    }
    // finally assign the value
    m_TotalDays = value;
    return TRUE;
}
