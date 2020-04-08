/****************************************************************************
 * ==> PSS_CommandLine -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an encapsulated command line                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_CommandLine.h"

// processsoft
#include "PSS_FileLauncher.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_CommandLine, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_CommandLine
//---------------------------------------------------------------------------
PSS_CommandLine::PSS_CommandLine(const CString& commandLine,
                                 const CString& startupDir,
                                 const CString& arguments,
                                 DWORD          priority) :
    m_pProcessInfo(NULL),
    m_CommandLine(commandLine),
    m_StartupDir(startupDir),
    m_Arguments(arguments),
    m_Priority(priority),
    m_HasBeenLaunched(FALSE)
{}
//---------------------------------------------------------------------------
PSS_CommandLine::PSS_CommandLine(const PSS_CommandLine& other) :
    m_pProcessInfo(NULL),
    m_Priority(0),
    m_HasBeenLaunched(FALSE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_CommandLine::~PSS_CommandLine()
{
    if (m_pProcessInfo)
        delete m_pProcessInfo;
}
//---------------------------------------------------------------------------
const PSS_CommandLine& PSS_CommandLine::operator = (const PSS_CommandLine& other)
{
    m_CommandLine = other.m_CommandLine;
    m_StartupDir  = other.m_StartupDir;
    m_Arguments   = other.m_Arguments;
    m_Priority    = other.m_Priority;

    return *this;
}
//---------------------------------------------------------------------------
void PSS_CommandLine::Initialize(const CString& commandLine,
                                 const CString& startupDir,
                                 const CString& arguments,
                                 DWORD          priority)
{
    m_CommandLine = commandLine;
    m_StartupDir  = startupDir;
    m_Arguments   = arguments;
    m_Priority    = priority;
}
//---------------------------------------------------------------------------
BOOL PSS_CommandLine::Launch()
{
    PSS_FileLauncher fileLauncher(m_CommandLine, PSS_FileLauncher::IE_FM_Open, m_Arguments, m_StartupDir);
    return fileLauncher.Launch();
}
//---------------------------------------------------------------------------
void PSS_CommandLine::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_CommandLine;
        ar << m_StartupDir;
        ar << m_Arguments;
        ar << m_Priority;
    }
    else
    {
        // read the elements
        ar >> m_CommandLine;
        ar >> m_StartupDir;
        ar >> m_Arguments;
        ar >> m_Priority;
    }
}
//---------------------------------------------------------------------------
