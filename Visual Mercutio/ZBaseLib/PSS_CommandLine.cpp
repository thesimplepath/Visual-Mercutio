/****************************************************************************
 * ==> PSS_CommandLine -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an encapsulated command line                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_CommandLine.h"

// processsoft
#include "ZUFileLauncher.h"

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
    m_pProcessInfo(NULL)
    m_CommandLine(commandLine),
    m_StartupDir(startupDir),
    m_Arguments(arguments),
    m_Priority(priority),
    m_HasBeenLaunched(FALSE)
{}
//---------------------------------------------------------------------------
PSS_CommandLine::PSS_CommandLine(const PSS_CommandLine& other)
{
    *this = right;
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
    m_CommandLine      = other.m_CommandLine;
    m_StartupDirectory = other.m_StartupDirectory;
    m_Arguments        = other.m_Arguments;
    m_Priority         = other.m_Priority;

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
    ZUFileLauncher fileLauncher(m_CommandLine, FLMopen, m_Arguments, m_StartupDir);
    return fileLauncher.Launch();
}
//---------------------------------------------------------------------------
void PSS_CommandLine::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_CommandLine;
        ar << m_StartupDirectory;
        ar << m_Arguments;
        ar << m_Priority;
    }
    else
    {
        // read the elements
        ar >> m_CommandLine;
        ar >> m_StartupDirectory;
        ar >> m_Arguments;
        ar >> m_Priority;
    }
}
//---------------------------------------------------------------------------
