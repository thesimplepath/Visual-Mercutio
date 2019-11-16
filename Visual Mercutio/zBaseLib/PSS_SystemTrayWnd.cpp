/****************************************************************************
 * ==> PSS_SystemTrayWnd ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a system tray window                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SystemTrayWnd.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
UINT PSS_SystemTrayWnd::m_EventID = 4567;
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_SystemTrayWnd, CWnd)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SystemTrayWnd, CWnd)
    //{{AFX_MSG_MAP(PSS_SystemTrayWnd)
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SystemTrayWnd
//---------------------------------------------------------------------------
PSS_SystemTrayWnd::PSS_SystemTrayWnd() :
    CWnd()
{
    Initialise();
}
//---------------------------------------------------------------------------
PSS_SystemTrayWnd::PSS_SystemTrayWnd(CWnd* pParent, UINT callbackMessage, LPCTSTR pToolTip, HICON hIcon, UINT id)
{
    Initialise();
    Create(pParent, callbackMessage, pToolTip, hIcon, id);
}
//---------------------------------------------------------------------------
PSS_SystemTrayWnd::~PSS_SystemTrayWnd()
{
    RemoveIcon();
    m_IconList.RemoveAll();
    DestroyWindow();
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::Create(CWnd* pParent, UINT callbackMessage, LPCTSTR pToolTip, HICON hIcon, UINT id)
{
    // this is only for Windows 95 (or higher)
    VERIFY(m_Enabled = (GetVersion() & 0xff) >= 4);

    if (!m_Enabled)
        return FALSE;

    // make sure to avoid conflict with other messages
    ASSERT(callbackMessage >= WM_USER);

    // tray only supports tooltip text up to 64 characters
    ASSERT(std::_tcslen(pToolTip) <= 64);

    // create an invisible window
    CWnd::CreateEx(0, AfxRegisterWndClass(0), _T(""), WS_POPUP, 0, 0, 10, 10, NULL, 0);

    // load up the NOTIFYICONDATA structure
    m_NotifyIconData.cbSize = sizeof(NOTIFYICONDATA);

    m_NotifyIconData.hWnd             = pParent->GetSafeHwnd() ? pParent->GetSafeHwnd() : m_hWnd;
    m_NotifyIconData.uID              = id;
    m_NotifyIconData.hIcon            = hIcon;
    m_NotifyIconData.uFlags           = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    m_NotifyIconData.uCallbackMessage = callbackMessage;
    std::_tcscpy(m_NotifyIconData.szTip, pToolTip);

    if (m_Menu.LoadMenu(m_NotifyIconData.uID))
        m_pSubMenu = m_Menu.GetSubMenu(0);

    // set the tray icon
    VERIFY(m_Enabled = Shell_NotifyIcon(NIM_ADD, &m_NotifyIconData));

    return m_Enabled;
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::SetTooltipText(LPCTSTR pszTip)
{
    if (!m_Enabled)
        return FALSE;

    m_NotifyIconData.uFlags = NIF_TIP;
    std::_tcscpy(m_NotifyIconData.szTip, pszTip);

    return Shell_NotifyIcon(NIM_MODIFY, &m_NotifyIconData);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::SetTooltipText(UINT nID)
{
    CString text;
    VERIFY(text.LoadString(nID));

    return SetTooltipText(text);
}
//---------------------------------------------------------------------------
CString PSS_SystemTrayWnd::GetTooltipText() const
{
    CString text;

    if (m_Enabled)
        text = m_NotifyIconData.szTip;

    return text;
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::SetIcon(HICON hIcon)
{
    if (!m_Enabled) return FALSE;

    m_NotifyIconData.uFlags = NIF_ICON;
    m_NotifyIconData.hIcon  = hIcon;

    return Shell_NotifyIcon(NIM_MODIFY, &m_NotifyIconData);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::SetIcon(LPCTSTR pIconName)
{
    HICON hIcon = AfxGetApp()->LoadIcon(pIconName);

    return SetIcon(hIcon);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::SetIcon(UINT iconID)
{
    HICON hIcon = AfxGetApp()->LoadIcon(iconID);

    return SetIcon(hIcon);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::SetStandardIcon(LPCTSTR pIconName)
{
    HICON hIcon = ::LoadIcon(NULL, pIconName);

    return SetIcon(hIcon);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::SetStandardIcon(UINT iconID)
{
    HICON hIcon = ::LoadIcon(NULL, MAKEINTRESOURCE(iconID));

    return SetIcon(hIcon);
}
//---------------------------------------------------------------------------
HICON PSS_SystemTrayWnd::GetIcon() const
{
    return (m_Enabled ? m_NotifyIconData.hIcon : NULL);
}
//---------------------------------------------------------------------------
void PSS_SystemTrayWnd::HideIcon()
{
    if (m_Enabled && !m_Hidden)
    {
        m_NotifyIconData.uFlags = NIF_ICON;
        ::Shell_NotifyIcon(NIM_DELETE, &m_NotifyIconData);
        m_Hidden = TRUE;
    }
}
//---------------------------------------------------------------------------
void PSS_SystemTrayWnd::ShowIcon()
{
    if (m_Enabled && m_Hidden)
    {
        m_NotifyIconData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        ::Shell_NotifyIcon(NIM_ADD, &m_NotifyIconData);
        m_Hidden = FALSE;
    }
}
//---------------------------------------------------------------------------
void PSS_SystemTrayWnd::RemoveIcon()
{
    if (!m_Enabled)
        return;

    m_NotifyIconData.uFlags = 0;
    ::Shell_NotifyIcon(NIM_DELETE, &m_NotifyIconData);
    m_Enabled = FALSE;
}
//---------------------------------------------------------------------------
void PSS_SystemTrayWnd::MoveToRight()
{
    HideIcon();
    ShowIcon();
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::SetIconList(UINT firstIconID, UINT lastIconID)
{
    if (firstIconID > lastIconID)
        return FALSE;

    const UINT     iconArraySize = lastIconID - firstIconID + 1;
    const CWinApp* pApp          = AfxGetApp();
    ASSERT(pApp != 0);

    m_IconList.RemoveAll();

    try
    {
        for (UINT i = firstIconID; i <= lastIconID; ++i)
            m_IconList.Add(pApp->LoadIcon(i));
    }
    catch (CMemoryException* pException)
    {
        pException->ReportError();
        pException->Delete();
        m_IconList.RemoveAll();
        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::SetIconList(HICON* pIconList, UINT iconCount)
{
    m_IconList.RemoveAll();

    try
    {
        for (UINT i = 0; i <= iconCount; ++i)
            m_IconList.Add(pIconList[i]);
    }
    catch (CMemoryException* pException)
    {
        pException->ReportError();
        pException->Delete();
        m_IconList.RemoveAll();
        return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::Animate(UINT delay, int duration)
{
    StopAnimation();

    m_CurrentIcon     = 0;
    m_StartTime       = COleDateTime::GetCurrentTime();
    m_AnimationPeriod = duration;
    m_hSavedIcon      = GetIcon();

    // setup a timer for the animation
    m_TimerID = SetTimer(m_EventID, delay, NULL);

    return m_TimerID;
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::StepAnimation()
{
    if (!m_IconList.GetSize())
        return FALSE;

    ++m_CurrentIcon;

    if (m_CurrentIcon >= m_IconList.GetSize())
        m_CurrentIcon = 0;

    return SetIcon(m_IconList[m_CurrentIcon]);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::StopAnimation()
{
    BOOL result = FALSE;

    if (m_TimerID)
        result = KillTimer(m_TimerID);

    m_TimerID = 0;

    if (m_hSavedIcon)
        SetIcon(m_hSavedIcon);

    m_hSavedIcon = NULL;

    return result;
}
//---------------------------------------------------------------------------
void PSS_SystemTrayWnd::GetMenuDefaultItem(UINT& item, BOOL& byPos) const
{
    item  = m_DefaultMenuItemID;
    byPos = m_DefaultMenuItemByPos;
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::SetMenuDefaultItem(UINT item, BOOL byPos)
{
    if ((m_DefaultMenuItemID == item) && (m_DefaultMenuItemByPos == byPos))
        return TRUE;

    m_DefaultMenuItemID    = item;
    m_DefaultMenuItemByPos = byPos;

    ::SetMenuDefaultItem(m_pSubMenu->m_hMenu, m_DefaultMenuItemID, m_DefaultMenuItemByPos);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::CheckMenuItem(UINT item, BOOL status)
{
    ::CheckMenuItem(m_pSubMenu->m_hMenu, item, status ? MF_CHECKED | MF_BYPOSITION : MF_UNCHECKED | MF_BYPOSITION);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::EnableMenuItem(UINT item, BOOL status)
{
    ::EnableMenuItem(m_pSubMenu->m_hMenu, item, status ? MF_ENABLED | MF_BYPOSITION : MF_DISABLED | MF_BYPOSITION);
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::SetMenuTextItem(UINT item, const CString& text)
{
    ::ModifyMenu(m_pSubMenu->m_hMenu, item, MF_BYPOSITION | MF_STRING, 0, static_cast<LPCSTR>(text));
    ::DrawMenuBar(GetSafeHwnd());

    return TRUE;
}
//---------------------------------------------------------------------------
CWnd* PSS_SystemTrayWnd::GetNotificationWnd() const
{
    return CWnd::FromHandle(m_NotifyIconData.hWnd);
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::SetNotificationWnd(CWnd* pWnd)
{
    if (!m_Enabled)
        return FALSE;

    // make sure Notification window is valid
    ASSERT(pWnd && ::IsWindow(pWnd->GetSafeHwnd()));

    m_NotifyIconData.hWnd   = pWnd->GetSafeHwnd();
    m_NotifyIconData.uFlags = 0;

    return Shell_NotifyIcon(NIM_MODIFY, &m_NotifyIconData);
}
//---------------------------------------------------------------------------
LRESULT PSS_SystemTrayWnd::OnTrayNotification(UINT wParam, LONG lParam)
{
    // return quickly if its not for this tray icon
    if (wParam != m_NotifyIconData.uID)
        return 0L;

    CWnd* pTarget = AfxGetMainWnd();

    // no main window assigned
    if (!pTarget)
        return 1;

    // dispatch clicked button
    switch (LOWORD(lParam))
    {
        case WM_RBUTTONUP:
        {
            // clicking with right button brings up a context menu. Make choosen menu item the default one (bold font)
            ::SetMenuDefaultItem(m_pSubMenu->m_hMenu, m_DefaultMenuItemID, m_DefaultMenuItemByPos);

            // show and track the popup menu
            CPoint pos;
            GetCursorPos(&pos);

            pTarget->SetForegroundWindow();
            ::TrackPopupMenu(m_pSubMenu->m_hMenu, 0, pos.x, pos.y, 0, pTarget->GetSafeHwnd(), NULL);

            // see "PRB: Menus for Notification Icons Don't Work Correctly"
            pTarget->PostMessage(WM_NULL, 0, 0);

            break;
        }

        case WM_LBUTTONDBLCLK:
        {
            // double click received, the default action is to execute default menu item
            pTarget->SetForegroundWindow();

            UINT uItem;

            if (m_DefaultMenuItemByPos)
                uItem = m_pSubMenu->GetMenuItemID(m_DefaultMenuItemID);
            else
                uItem = m_DefaultMenuItemID;

            pTarget->SendMessage(WM_COMMAND, uItem, 0);

            break;
        }
    }

    return 1;
}
//---------------------------------------------------------------------------
void PSS_SystemTrayWnd::Initialise()
{
    std::memset(&m_NotifyIconData, 0, sizeof(m_NotifyIconData));

    m_hSavedIcon           = NULL;
    m_pSubMenu             = NULL;
    m_DefaultMenuItemID    = 0;
    m_TimerID              = 0;
    m_CurrentIcon          = 0;
    m_AnimationPeriod      = 0;
    m_Enabled              = FALSE;
    m_Hidden               = FALSE;
    m_DefaultMenuItemByPos = TRUE;
}
//---------------------------------------------------------------------------
void PSS_SystemTrayWnd::OnTimer(UINT eventID)
{
    ASSERT(eventID == m_EventID);

    COleDateTime     currentTime = COleDateTime::GetCurrentTime();
    COleDateTimeSpan period      = currentTime - m_StartTime;

    if (m_AnimationPeriod > 0 && m_AnimationPeriod < period.GetTotalSeconds())
    {
        StopAnimation();
        return;
    }

    StepAnimation();
}
//---------------------------------------------------------------------------
LRESULT PSS_SystemTrayWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == m_NotifyIconData.uCallbackMessage)
        return OnTrayNotification(wParam, lParam);

    return CWnd::WindowProc(message, wParam, lParam);
}
//---------------------------------------------------------------------------
