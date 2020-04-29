/****************************************************************************
 * ==> PSS_ExtAppProperties ------------------------------------------------*
 ****************************************************************************
 * Description : Provides external application properties                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ExtAppProperties.h"

// resources
#include "zModelRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

using namespace sfl;

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ExtAppProperties, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ExtAppProperties
//---------------------------------------------------------------------------
PSS_ExtAppProperties::PSS_ExtAppProperties() :
    CObject(),
    m_PriorityLevel(0),
    m_WindowStartMode(0)
{}
//---------------------------------------------------------------------------
PSS_ExtAppProperties::PSS_ExtAppProperties(const PSS_ExtAppProperties& other)
{
    m_CommandTitle            = other.GetCommandTitle();
    m_CommandLine             = other.GetCommandLine();
    m_CommandParameters       = other.GetCommandParameters();
    m_CommandStartupDirectory = other.GetCommandStartupDirectory();
    m_PriorityLevel           = other.GetPriorityLevel();
    m_WindowStartMode         = other.GetWindowStartMode();
}
//---------------------------------------------------------------------------
PSS_ExtAppProperties::~PSS_ExtAppProperties()
{}
//---------------------------------------------------------------------------
PSS_ExtAppProperties& PSS_ExtAppProperties::operator = (const PSS_ExtAppProperties& other)
{
    SetCommandTitle           (other.GetCommandTitle());
    SetCommandLine            (other.GetCommandLine());
    SetCommandParameters      (other.GetCommandParameters());
    SetCommandStartupDirectory(other.GetCommandStartupDirectory());
    SetPriorityLevel          (other.GetPriorityLevel());
    SetWindowStartMode        (other.GetWindowStartMode());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::operator == (const PSS_ExtAppProperties& other) const
{
    return (GetCommandTitle()            == other.GetCommandTitle()            &&
            GetCommandLine()             == other.GetCommandLine()             &&
            GetCommandParameters()       == other.GetCommandParameters()       &&
            GetCommandStartupDirectory() == other.GetCommandStartupDirectory() &&
            GetPriorityLevel()           == other.GetPriorityLevel()           &&
            GetWindowStartMode()         == other.GetWindowStartMode());
}
//---------------------------------------------------------------------------
void PSS_ExtAppProperties::Merge(PSS_ExtAppProperties* pProp, DWORD changeFlags)
{
    if (pProp)
    {
        if (changeFlags & IE_CT_Command_Title)
            m_CommandTitle = pProp->GetCommandTitle();

        if (changeFlags & IE_CT_Command_Line)
            m_CommandLine = pProp->GetCommandLine();

        if (changeFlags & IE_CT_Command_Param)
            m_CommandParameters = pProp->GetCommandParameters();

        if (changeFlags & IE_CT_Command_StartupDir)
            m_CommandStartupDirectory = pProp->GetCommandStartupDirectory();

        if (changeFlags & IE_CT_Priority_Level)
            m_PriorityLevel = pProp->GetPriorityLevel();

        if (changeFlags & IE_CT_Window_StartMode)
            m_WindowStartMode = pProp->GetWindowStartMode();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::IsEqual(PSS_ExtAppProperties* pProp)
{
    if (pProp)
        return (*this == *pProp);

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_ExtAppProperties::SetCommandTitle(LPCTSTR pValue)
{
    if (pValue)
        m_CommandTitle = pValue;
    else
        THROW("Invalid command title pointer");
}
//---------------------------------------------------------------------------
void PSS_ExtAppProperties::SetCommandLine(LPCTSTR pValue)
{
    if (pValue)
        m_CommandLine = pValue;
    else
        THROW("Invalid command line pointer");
}
//---------------------------------------------------------------------------
void PSS_ExtAppProperties::SetCommandParameters(LPCTSTR pValue)
{
    if (pValue)
        m_CommandParameters = pValue;
    else
        THROW("Invalid command parameters pointer");
}
//---------------------------------------------------------------------------
void PSS_ExtAppProperties::SetCommandStartupDirectory(LPCTSTR pValue)
{
    if (pValue)
        m_CommandStartupDirectory = pValue;
    else
        THROW("Invalid command startup directory pointer");
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Command_Title_ID:
        case M_Command_Line_ID:
        case M_Command_Param_ID:
        case M_Command_StartupDir_ID: throw new CODPropertyConversionException();
        case M_Priority_Level_ID:     value = m_PriorityLevel;   break;
        case M_Window_StartMode_ID:   value = m_WindowStartMode; break;
        default:                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_Command_Title_ID:
        case M_Command_Line_ID:
        case M_Command_Param_ID:
        case M_Command_StartupDir_ID: throw new CODPropertyConversionException();
        case M_Priority_Level_ID:     value = UINT(m_PriorityLevel);   break;
        case M_Window_StartMode_ID:   value = UINT(m_WindowStartMode); break;
        default:                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Command_Title_ID:
        case M_Command_Line_ID:
        case M_Command_Param_ID:
        case M_Command_StartupDir_ID:
        case M_Priority_Level_ID:
        case M_Window_StartMode_ID:   throw new CODPropertyConversionException();
        default:                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Command_Title_ID:
        case M_Command_Line_ID:
        case M_Command_Param_ID:
        case M_Command_StartupDir_ID:
        case M_Priority_Level_ID:
        case M_Window_StartMode_ID:   throw new CODPropertyConversionException();
        default:                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Command_Title_ID:      value = m_CommandTitle;            break;
        case M_Command_Line_ID:       value = m_CommandLine;             break;
        case M_Command_Param_ID:      value = m_CommandParameters;       break;
        case M_Command_StartupDir_ID: value = m_CommandStartupDirectory; break;
        default:                      throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Command_Title_ID:
        case M_Command_Line_ID:
        case M_Command_Param_ID:
        case M_Command_StartupDir_ID: throw new CODPropertyConversionException();
        case M_Priority_Level_ID:     m_PriorityLevel   = value; break;
        case M_Window_StartMode_ID:   m_WindowStartMode = value; break;
        default:                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_Command_Title_ID:
        case M_Command_Line_ID:
        case M_Command_Param_ID:
        case M_Command_StartupDir_ID: throw new CODPropertyConversionException();
        case M_Priority_Level_ID:     m_PriorityLevel   = int(value);
        case M_Window_StartMode_ID:   m_WindowStartMode = int(value);
        default:                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Command_Title_ID:
        case M_Command_Line_ID:
        case M_Command_Param_ID:
        case M_Command_StartupDir_ID:
        case M_Priority_Level_ID:
        case M_Window_StartMode_ID:   throw new CODPropertyConversionException();
        default:                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Command_Title_ID:
        case M_Command_Line_ID:
        case M_Command_Param_ID:
        case M_Command_StartupDir_ID:
        case M_Priority_Level_ID:
        case M_Window_StartMode_ID:   throw new CODPropertyConversionException();
        default:                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ExtAppProperties::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Command_Title_ID:      m_CommandTitle            = pValue; break;
        case M_Command_Line_ID:       m_CommandLine             = pValue; break;
        case M_Command_Param_ID:      m_CommandParameters       = pValue; break;
        case M_Command_StartupDir_ID: m_CommandStartupDirectory = pValue; break;
        default:                      throw new CODPropertyConversionException();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ExtAppProperties::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar << m_CommandTitle;
        ar << m_CommandLine;
        ar << m_CommandParameters;
        ar << m_CommandStartupDirectory;
        ar << m_PriorityLevel;
        ar << m_WindowStartMode;
    }
    else
    {
        ar >> m_CommandTitle;
        ar >> m_CommandLine;
        ar >> m_CommandParameters;
        ar >> m_CommandStartupDirectory;
        ar >> m_PriorityLevel;
        ar >> m_WindowStartMode;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ExtAppProperties::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ExtAppProperties::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);

        dc << _T("Title = ")               << m_CommandTitle            << _T("\n");
        dc << _T("Command line = ")        << m_CommandLine             << _T("\n");
        dc << _T("Command param = ")       << m_CommandParameters       << _T("\n");
        dc << _T("Command startup dir = ") << m_CommandStartupDirectory << _T("\n");
        dc << _T("Priority = ")            << m_PriorityLevel           << _T("\n");
        dc << _T("Window mode = ")         << m_WindowStartMode         << _T("\n");
    }
#endif
//---------------------------------------------------------------------------
void PSS_ExtAppProperties::SetCommandTitleEx(const CString& value)
{
    SetCommandTitle(value);
}
//---------------------------------------------------------------------------
void PSS_ExtAppProperties::SetCommandLineEx(const CString& value)
{
    SetCommandLine(value);
}
//---------------------------------------------------------------------------
void PSS_ExtAppProperties::SetCommandParametersEx(const CString& value)
{
    SetCommandParameters(value);
}
//---------------------------------------------------------------------------
void PSS_ExtAppProperties::SetCommandStartupDirectoryEx(const CString& value)
{
    SetCommandStartupDirectory(value);
}
//---------------------------------------------------------------------------
