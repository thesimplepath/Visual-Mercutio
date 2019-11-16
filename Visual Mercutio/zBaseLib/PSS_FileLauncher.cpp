/****************************************************************************
 * ==> PSS_FileLauncher ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file launcher                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FileLauncher.h"

// windows
#include <vdmdbg.h>

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Callback enumeration functions
//---------------------------------------------------------------------------
BOOL CALLBACK ActivateAppEnum(HWND hwnd, LPARAM lParam)
{
    DWORD id;

    ::GetWindowThreadProcessId(hwnd, &id);

    if (id == DWORD(lParam))
    {
        ::SetActiveWindow(hwnd);
        ::SetForegroundWindow(hwnd);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL CALLBACK Activate16AppEnum(HWND hwnd, LPARAM lParam)
{
    DWORD       id;
    const DWORD thread = GetWindowThreadProcessId(hwnd, &id);

    ::SetActiveWindow(hwnd);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL CALLBACK TerminateAppEnum(HWND hwnd, LPARAM lParam)
{
    DWORD id;

    ::GetWindowThreadProcessId(hwnd, &id);

    if (id == DWORD(lParam))
        PostMessage(hwnd, WM_CLOSE, 0, 0);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL CALLBACK Terminate16AppEnum(HWND hwnd, LPARAM lParam)
{
    DWORD       id;
    const DWORD thread = GetWindowThreadProcessId(hwnd, &id);

    PostMessage(hwnd, WM_CLOSE, 0, 0);

    return TRUE;
}
//---------------------------------------------------------------------------
// PSS_FileLauncher
//---------------------------------------------------------------------------
PSS_FileLauncher::PSS_FileLauncher(const CString& fileName,
                                   IEMode         mode,
                                   const CString& parameters,
                                   const CString& directory) :
    m_FileName(fileName),
    m_Mode(mode),
    m_Parameters(parameters),
    m_Directory(directory),
    m_ErrorCode(NULL)
{
    ZeroMemory(&m_ShellInfoExecute, sizeof(m_ShellInfoExecute));
}
//---------------------------------------------------------------------------
PSS_FileLauncher::~PSS_FileLauncher()
{}
//---------------------------------------------------------------------------
BOOL PSS_FileLauncher::Initialize(const CString& fileName,
                                  IEMode         mode,
                                  const CString& parameters,
                                  const CString& directory)
{
    m_FileName   = fileName;
    m_Mode       = mode;
    m_Parameters = parameters;
    m_Directory  = directory;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_FileLauncher::Launch(const CString& fileName,
                              IEMode         mode,
                              const CString& parameters,
                              const CString& directory)
{
    m_FileName   = fileName;
    m_Mode       = mode;
    m_Parameters = parameters;
    m_Directory  = directory;

    return Launch();
}
//---------------------------------------------------------------------------
BOOL PSS_FileLauncher::Launch()
{
    m_ErrorCode = ::ShellExecute(::GetDesktopWindow(),
                                 (const char*)GetModeVerbString(),
                                 (const char*)m_FileName,
                                 (const char*)m_Parameters,
                                 (const char*)m_Directory,
                                 SW_SHOWDEFAULT);

    return !IsError();
}
//---------------------------------------------------------------------------
BOOL PSS_FileLauncher::Close()
{
    if (IsError() || !HasBeenLaunched())
        return TRUE;

    // TerminateAppEnum() posts WM_CLOSE to all windows whose PID matches the processes
    ::EnumWindows(WNDENUMPROC(TerminateAppEnum), LPARAM(m_ShellInfoExecute.hProcess));

    BOOL result;

    // wait on the handle. If it signals, great. If it times out, then kill it
    if (WaitForSingleObject(m_ShellInfoExecute.hProcess, 1000) != WAIT_OBJECT_0)
        result = (TerminateProcess(m_ShellInfoExecute.hProcess, 0) ? TRUE : FALSE);
    else
        result = TRUE;

    CloseHandle(m_ShellInfoExecute.hProcess);

    return result;
}
//---------------------------------------------------------------------------
BOOL PSS_FileLauncher::ActivateApplication()
{
    if (IsError() || !HasBeenLaunched())
        return FALSE;

    // ActivateAppEnum() activates the application
    ::EnumWindows(WNDENUMPROC(ActivateAppEnum), LPARAM(m_ShellInfoExecute.hProcess));

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_FileLauncher::HasBeenLaunched() const
{
    if (!m_ShellInfoExecute.hProcess)
        return FALSE;

    // check if the process still exists
    DWORD exitCode;

    if (GetExitCodeProcess(m_ShellInfoExecute.hProcess, &exitCode))
        if (exitCode == STILL_ACTIVE)
            return TRUE;

    // not running or never launched
    return FALSE;
}
//---------------------------------------------------------------------------
CString PSS_FileLauncher::GetErrorString() const
{
    switch (m_Mode)
    {
        case 0:                      return "The operating system is out of memory or resources.";
        case ERROR_BAD_FORMAT:       return "The .exe file is invalid (non-Win32® .exe or error in .exe image.";
        case SE_ERR_ACCESSDENIED:    return "The operating system denied access to the specified file.";
        case SE_ERR_ASSOCINCOMPLETE: return "The file name association is incomplete or invalid.";
        case SE_ERR_DDEBUSY:         return "The DDE transaction could not be completed because other DDE transactions were being processed.";
        case SE_ERR_DDEFAIL:         return "The DDE transaction failed.";
        case SE_ERR_DDETIMEOUT:      return "The DDE transaction could not be completed because the request timed out.";
        case SE_ERR_DLLNOTFOUND:     return "The specified dynamic-link library was not found.";
        case SE_ERR_FNF:             return "The specified file was not found.";
        case SE_ERR_NOASSOC:         return "There is no application associated with the given file name extension. This error will also be returned if you attempt to print a file that is not printable.";
        case SE_ERR_OOM:             return "There was not enough memory to complete the operation.";
        case SE_ERR_PNF:             return "The specified path was not found.";
        case SE_ERR_SHARE:           return "A sharing violation occurred.";
    }

    return "";
}
//---------------------------------------------------------------------------
CString PSS_FileLauncher::GetModeVerbString() const
{
    switch (m_Mode)
    {
        case IE_FM_Edit:       return "edit";
        case IE_FM_Explore:    return "explore";
        case IE_FM_Open:       return "open";
        case IE_FM_Print:      return "print";
        case IE_FM_Properties: return "properties";
    }

    return "";
}
//---------------------------------------------------------------------------
