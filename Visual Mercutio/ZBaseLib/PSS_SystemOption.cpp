/****************************************************************************
 * ==> PSS_SystemOption ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a system options manager                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_SystemOption.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_SystemOption
//---------------------------------------------------------------------------
PSS_SystemOption::PSS_SystemOption(const CString& iniFile, const CString& sectionName) :
    m_IniFile(iniFile),
    m_SectionName(sectionName)
{}
//---------------------------------------------------------------------------
PSS_SystemOption::PSS_SystemOption(const PSS_SystemOption& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_SystemOption::~PSS_SystemOption()
{}
//---------------------------------------------------------------------------
const PSS_SystemOption& PSS_SystemOption::operator = (const PSS_SystemOption& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_SystemOption::Create(const CString& iniFile, const CString& sectionName)
{
    m_IniFile     = iniFile;
    m_SectionName = sectionName;

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_SystemOption::ReadOption(const CString& entityKey, LPCTSTR pDefaultValue)
{
    char buffer[300];

    if (!::GetPrivateProfileString((const char*)m_SectionName,
                                   (const char*)entityKey,
                                   pDefaultValue ? pDefaultValue : _T(""),
                                   buffer,
                                   sizeof(buffer),
                                   (const char*)m_IniFile))
        return pDefaultValue;

    return CString(buffer);
}
//---------------------------------------------------------------------------
CString PSS_SystemOption::ReadOption(const CString& entityKey, const CString& defaultValue)
{
    char buffer[300];

    if (!::GetPrivateProfileString((const char*)m_SectionName,
                                   (const char*)entityKey,
                                   (const char*)defaultValue,
                                   buffer,
                                   sizeof(buffer),
                                   (const char*)m_IniFile))
        return defaultValue;

    return CString(buffer);
}
//---------------------------------------------------------------------------
bool PSS_SystemOption::ReadOption(const CString& entityKey, bool defaultValue)
{
    char buffer[50];
    char defaultValueBuffer[50];

    std::sprintf(defaultValueBuffer, _T("%d"), int(defaultValue));

    if (!::GetPrivateProfileString((const char*)m_SectionName,
                                   (const char*)entityKey,
                                   defaultValueBuffer,
                                   buffer,
                                   sizeof(buffer),
                                   (const char*)m_IniFile))
        return defaultValue;

    return (std::atoi(buffer) == 0) ? false : true;
}
//---------------------------------------------------------------------------
int PSS_SystemOption::ReadOption(const CString& entityKey, int defaultValue)
{
    char buffer[50];
    char defaultValueBuffer[50];

    std::sprintf(defaultValueBuffer, _T("%d"), defaultValue);

    if (!::GetPrivateProfileString((const char*)m_SectionName,
                                   (const char*)entityKey,
                                   defaultValueBuffer,
                                   buffer,
                                   sizeof(buffer),
                                   (const char*)m_IniFile))
        return defaultValue;

    return std::atoi(buffer);
}
//---------------------------------------------------------------------------
float PSS_SystemOption::ReadOption(const CString& entityKey, float defaultValue)
{
    char buffer[50];
    char defaultValueBuffer[50];

    std::sprintf(defaultValueBuffer, _T("%f"), defaultValue);

    if (!::GetPrivateProfileString((const char*)m_SectionName,
                                   (const char*)entityKey,
                                   defaultValueBuffer,
                                   buffer,
                                   sizeof(buffer),
                                   (const char*)m_IniFile))
        return defaultValue;

    return float(std::atof(buffer));
}
//---------------------------------------------------------------------------
double PSS_SystemOption::ReadOption(const CString& entityKey, double defaultValue)
{
    char buffer[50];
    char defaultValueBuffer[50];

    std::sprintf(defaultValueBuffer, _T("%f"), defaultValue);

    if (!::GetPrivateProfileString((const char*)m_SectionName,
                                   (const char*)entityKey,
                                   defaultValueBuffer,
                                   buffer,
                                   sizeof(buffer),
                                   (const char*)m_IniFile))
        return defaultValue;

    return std::atof(buffer);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemOption::WriteOption(const CString& entityKey, LPCTSTR pValue)
{
    return ::WritePrivateProfileString((const char*)m_SectionName,
                                       (const char*)entityKey,
                                       pValue ? pValue : _T(""),
                                       (const char*)m_IniFile);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemOption::WriteOption(const CString& entityKey, const CString& value)
{
    return ::WritePrivateProfileString((const char*)m_SectionName,
                                       (const char*)entityKey,
                                       (const char*)value,
                                       (const char*)m_IniFile);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemOption::WriteOption(const CString& entityKey, bool value)
{
    char valueBuffer[50];
    std::sprintf(valueBuffer, _T("%d"), int(value));

    return ::WritePrivateProfileString((const char*)m_SectionName,
                                       (const char*)entityKey,
                                       (const char*)valueBuffer,
                                       (const char*)m_IniFile);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemOption::WriteOption(const CString& entityKey, int value)
{
    char valueBuffer[50];
    std::sprintf(valueBuffer, _T("%d"), value);

    return ::WritePrivateProfileString((const char*)m_SectionName,
                                       (const char*)entityKey,
                                       (const char*)valueBuffer,
                                       (const char*)m_IniFile);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemOption::WriteOption(const CString& entityKey, double value)
{
    char valueBuffer[50];
    std::sprintf(valueBuffer, _T("%f"), value);

    return ::WritePrivateProfileString((const char*)m_SectionName,
                                       (const char*)entityKey,
                                       (const char*)valueBuffer,
                                       (const char*)m_IniFile);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemOption::WriteOption(const CString& entityKey, float value)
{
    char valueBuffer[50];
    std::sprintf(valueBuffer, _T("%f"), value);

    return ::WritePrivateProfileString((const char*)m_SectionName,
                                       (const char*)entityKey,
                                       (const char*)valueBuffer,
                                       (const char*)m_IniFile);
}
//---------------------------------------------------------------------------
