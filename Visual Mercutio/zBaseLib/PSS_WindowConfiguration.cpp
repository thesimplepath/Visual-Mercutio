/****************************************************************************
 * ==> PSS_WindowConfiguration ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a windows position and state configuration system *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_WindowConfiguration.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const char   g_WindowsConfigSectionName[] = "WindowsConfigValues";
static TCHAR g_Format[]                   = _T("%u,%u,%d,%d,%d,%d,%d,%d,%d,%d");
//---------------------------------------------------------------------------
// PSS_WindowConfiguration
//---------------------------------------------------------------------------
PSS_WindowConfiguration::PSS_WindowConfiguration(const CString& iniFile)
{
    Create(iniFile);
}
//---------------------------------------------------------------------------
PSS_WindowConfiguration::PSS_WindowConfiguration(const PSS_WindowConfiguration& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_WindowConfiguration::~PSS_WindowConfiguration()
{}
//---------------------------------------------------------------------------
const PSS_WindowConfiguration& PSS_WindowConfiguration::operator = (const PSS_WindowConfiguration& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_WindowConfiguration::Create(const CString& iniFile)
{
    m_SystemOption.Create(iniFile, g_WindowsConfigSectionName);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WindowConfiguration::SaveWindowPosition(CWnd* pWnd, const CString& wndName, BOOL positionOnly)
{
    if (pWnd)
    {
        WINDOWPLACEMENT wp;
        wp.length = sizeof(wp);

        if (pWnd->GetWindowPlacement(&wp))
        {
            wp.flags = 0;

            if (pWnd->IsZoomed())
                wp.flags |= WPF_RESTORETOMAXIMIZED;

            if (!pWnd->IsWindowVisible())
                wp.showCmd = SW_HIDE;

            // write to the .ini file
            WriteWindowPlacement(&wp, wndName);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WindowConfiguration::RestoreWindowPosition(CWnd* pWnd, const CString& wndName, BOOL positionOnly)
{
    if (pWnd)
    {
        WINDOWPLACEMENT wp;

        if (ReadWindowPlacement(&wp, wndName))
            pWnd->SetWindowPlacement(&wp);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WindowConfiguration::SaveWindowDesktop(CWnd* pDesktopWnd, const CString& wndName, BOOL positionOnly)
{
    // not implemented
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WindowConfiguration::RestoreWindowDesktop(CWnd* pDesktopWnd, const CString& wndName, BOOL positionOnly)
{
    // not implemented
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_WindowConfiguration::ReadWindowPlacement(LPWINDOWPLACEMENT pWP, const CString& wndName)
{
    const CString strBuffer = m_SystemOption.ReadOption(szIniWindowBufferEntry + wndName, _T(""));

    if (strBuffer.IsEmpty())
        return FALSE;

    WINDOWPLACEMENT wp;

    const int read = std::_stscanf(strBuffer,
                                   g_Format,
                                   &wp.flags,
                                   &wp.showCmd,
                                   &wp.ptMinPosition.x,
                                   &wp.ptMinPosition.y,
                                   &wp.ptMaxPosition.x,
                                   &wp.ptMaxPosition.y,
                                   &wp.rcNormalPosition.left,
                                   &wp.rcNormalPosition.top,
                                   &wp.rcNormalPosition.right,
                                   &wp.rcNormalPosition.bottom);

    if (read != 10)
        return FALSE;

    wp.length = sizeof(wp);
    *pWP = wp;

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_WindowConfiguration::WriteWindowPlacement(LPWINDOWPLACEMENT pWP, const CString& wndName)
{
    if (!pWP)
        return;

    TCHAR buffer[sizeof(_T("-32767")) * 8 + sizeof(_T("65535")) * 2];

    ::wsprintf(buffer,
               g_Format,
               pWP->flags,
               pWP->showCmd,
               pWP->ptMinPosition.x,
               pWP->ptMinPosition.y,
               pWP->ptMaxPosition.x,
               pWP->ptMaxPosition.y,
               pWP->rcNormalPosition.left,
               pWP->rcNormalPosition.top,
               pWP->rcNormalPosition.right,
               pWP->rcNormalPosition.bottom);

    m_SystemOption.WriteOption(szIniWindowBufferEntry + wndName, buffer);
}
//---------------------------------------------------------------------------
