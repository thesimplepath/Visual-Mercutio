/****************************************************************************
 * ==> PSS_SplashWndThread -------------------------------------------------*
 ****************************************************************************
 * Description : Threaded splash screen window                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SplashWndThread.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_SplashWndThread, CWinThread)
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SplashWndThread, CWinThread)
    //{{AFX_MSG_MAP(PSS_SplashWndThread)
        // NOTE the ClassWizard will add and remove mapping macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SplashWndThread
//---------------------------------------------------------------------------
PSS_SplashWndThread::PSS_SplashWndThread(LPCTSTR pFileName, std::size_t maxTime, bool includeProgress, CWnd* pParent) :
    CWinThread(),
    m_pParent(pParent),
    m_hEventKill(0),
    m_hEventDead(0),
    m_BitmapFile(pFileName),
    m_MaxTime(maxTime),
    m_ResID(0),
    m_IncludeProgress(includeProgress)
{
    m_bAutoDelete = FALSE;

    // kill event starts out in the signaled state
    m_hEventKill = ::CreateEvent(NULL, TRUE, FALSE, NULL);
}
//---------------------------------------------------------------------------
PSS_SplashWndThread::PSS_SplashWndThread(UINT resID, std::size_t maxTime, bool includeProgress, CWnd* pParent) :
    CWinThread(),
    m_pParent(pParent),
    m_hEventKill(0),
    m_hEventDead(0),
    m_MaxTime(maxTime),
    m_ResID(resID),
    m_IncludeProgress(includeProgress)
{
    m_bAutoDelete = FALSE;

    // kill event starts out in the signaled state
    m_hEventKill = CreateEvent(NULL, TRUE, FALSE, NULL);
}
//---------------------------------------------------------------------------
PSS_SplashWndThread::PSS_SplashWndThread(std::size_t maxTime, bool includeProgress, CWnd* pParent) :
    CWinThread(),
    m_pParent(pParent),
    m_hEventKill(0),
    m_hEventDead(0),
    m_MaxTime(maxTime),
    m_ResID(0),
    m_IncludeProgress(includeProgress)
{
    m_bAutoDelete = FALSE;
}
//---------------------------------------------------------------------------
PSS_SplashWndThread::~PSS_SplashWndThread()
{
    CloseHandle(m_hEventKill);
}
//---------------------------------------------------------------------------
BOOL PSS_SplashWndThread::InitInstance()
{
    m_StartTime = COleDateTime::GetCurrentTime();

    // initialize the window
    if (m_ResID)
        m_SplashWnd.LoadBitmapImage(m_ResID);
    else
        m_SplashWnd.LoadBitmapImage(m_BitmapFile);

    if (!m_SplashWnd.CreateSplashWindow(m_IncludeProgress, m_pParent ? m_pParent : CWnd::GetDesktopWindow()))
        return FALSE;

    m_pMainWnd = &m_SplashWnd;

    // show the window
    return m_SplashWnd.Show();
}
//---------------------------------------------------------------------------
int PSS_SplashWndThread::ExitInstance()
{
    m_SplashWnd.Hide();
    return CWinThread::ExitInstance();
}
//---------------------------------------------------------------------------
void PSS_SplashWndThread::SetProgress(std::size_t value)
{
    m_SplashWnd.SetProgress(value);
}
//---------------------------------------------------------------------------
void PSS_SplashWndThread::SetText(const CString& value)
{
    m_SplashWnd.SetText(value);
}
//---------------------------------------------------------------------------
void PSS_SplashWndThread::SetText(UINT resID)
{
    m_SplashWnd.SetText(resID);
}
//---------------------------------------------------------------------------
void PSS_SplashWndThread::SetParent(CWnd* pParent)
{
    m_SplashWnd.SetParent(pParent);
}
//---------------------------------------------------------------------------
void PSS_SplashWndThread::KillThread()
{
    // reset the m_hEventKill which signals the thread to shutdown
    SetEvent(m_hEventKill);
    m_pMainWnd = NULL;

    // allow thread to run at higher priority during kill process
    SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
    ::WaitForSingleObject(m_hThread, 1000);
}
//---------------------------------------------------------------------------
int PSS_SplashWndThread::Run()
{
    DWORD result; 
    MSG   msg;
    bool  hasBeenKilled = false;

    HANDLE handles[1];
    handles[0] = m_hEventKill;

    // main thread loop
    while (!hasBeenKilled && m_pMainWnd)
    {
        // read messages
        while (m_pMainWnd && ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // received a quit message?
            if (msg.message == WM_QUIT)
                return 1;

            // dispatch the message
            ::DispatchMessage(&msg);
        }

        // calculate elapsed time
        const COleDateTimeSpan diffTime(COleDateTime::GetCurrentTime() - m_StartTime);

        // thread was killed or do stop?
        if (!hasBeenKilled && (diffTime.GetSeconds() > LONG(m_MaxTime)))
        {
            TRACE("PSS_SplashWndThread - overtime end requested\n");
            KillThread();
            hasBeenKilled = true;
        }

        // wait for any message sent or posted to this queue or for one of the passed handles be set to signaled
        result = ::MsgWaitForMultipleObjects(1, handles, FALSE, INFINITE, QS_ALLINPUT); 

        // check received event type
        if ((result == (WAIT_OBJECT_0 + 1)) || (result == WAIT_TIMEOUT))
            // received new messages, process them
            continue;
        else 
        { 
            // one of the handles became signaled
            hasBeenKilled = true;
            break;
        }
    }

    return 1;
}
//---------------------------------------------------------------------------
void PSS_SplashWndThread::Delete()
{
    // calling the base here won't do anything but it is a good habit
    CWinThread::Delete();
}
//---------------------------------------------------------------------------
