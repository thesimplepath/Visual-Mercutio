// SplashWinThread.cpp : implementation file
//

#include "stdafx.h"
#include "SplashWinThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZSplashWinThread

IMPLEMENT_DYNCREATE(ZSplashWinThread, CWinThread)

ZSplashWinThread::ZSplashWinThread(size_t MaxTime /*= 20*/, bool IncludeProgress /* = true */, CWnd* pParentWnd /*= NULL*/)
: m_MaxTime(MaxTime), m_nResID(0), m_IncludeProgress(IncludeProgress), m_pParentWnd(pParentWnd)
{
	m_bAutoDelete = FALSE;
}

ZSplashWinThread::ZSplashWinThread(LPCTSTR szFilename, size_t MaxTime /*= 20*/, bool IncludeProgress /* = true */, CWnd* pParentWnd /*= NULL*/)
: m_MaxTime(MaxTime), m_BitmapFile(szFilename), m_nResID(0), m_IncludeProgress(IncludeProgress), m_pParentWnd(pParentWnd)
{
	m_bAutoDelete = FALSE;
	// kill event starts out in the signaled state
	m_hEventKill = CreateEvent(NULL, TRUE, FALSE, NULL);
}

ZSplashWinThread::ZSplashWinThread(UINT nResID, size_t MaxTime /*= 20*/, bool IncludeProgress /* = true */, CWnd* pParentWnd /*= NULL*/)
: m_MaxTime(MaxTime), m_nResID(nResID), m_IncludeProgress(IncludeProgress), m_pParentWnd(pParentWnd)
{
	m_bAutoDelete = FALSE;
	// kill event starts out in the signaled state
	m_hEventKill = CreateEvent(NULL, TRUE, FALSE, NULL);
}


ZSplashWinThread::~ZSplashWinThread()
{
	CloseHandle(m_hEventKill);
}

void ZSplashWinThread::Delete()
{
	// calling the base here won't do anything but it is a good habit
	CWinThread::Delete();
}

void ZSplashWinThread::KillThread()
{
	// Note: this function is called in the context of other threads,
	//  not the thread itself.

	// reset the m_hEventKill which signals the thread to shutdown
	SetEvent(m_hEventKill);

	m_pMainWnd = NULL;
	// allow thread to run at higher priority during kill process
	SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
	WaitForSingleObject(m_hThread, 1000);
}

BOOL ZSplashWinThread::InitInstance()
{
	m_StartTime = COleDateTime::GetCurrentTime();

	// Initialize the window
	if (m_nResID != 0)
		m_SplashWnd.LoadBitmapImage( m_nResID );
	else
		m_SplashWnd.LoadBitmapImage( m_BitmapFile );

	if (!m_SplashWnd.CreateSplashWindow( m_IncludeProgress, (m_pParentWnd == NULL) ? CWnd::GetDesktopWindow() : m_pParentWnd ))
		return FALSE;

	m_pMainWnd = &m_SplashWnd;
	// Display the window
	return m_SplashWnd.Display();
}


int ZSplashWinThread::ExitInstance()
{
	m_SplashWnd.EndDisplay();
	return CWinThread::ExitInstance();
}


void ZSplashWinThread::SetProgress(size_t value)
{
	m_SplashWnd.SetProgress( value );
}

void ZSplashWinThread::SetText(const CString value)
{
	m_SplashWnd.SetText( value );
}

void ZSplashWinThread::SetText(UINT nResID)
{
	m_SplashWnd.SetText( nResID );
}

void ZSplashWinThread::AssignParentWindow(CWnd* pParentWnd)
{
	m_SplashWnd.AssignParentWindow( pParentWnd );
}


int ZSplashWinThread::Run()
{
    // The message loop lasts until we get a WM_QUIT message,
    // upon which we shall return from the function.

    // block-local variable 
    DWORD	result; 
    MSG		msg;
	HANDLE	pHandles[1];
	bool	HasBeenKilled = false;
	pHandles[0] = m_hEventKill;

    while (HasBeenKilled == false && m_pMainWnd != NULL)
    {
        // Read all of the messages in this next loop, 
        // removing each message as we read it.
        while (m_pMainWnd != NULL && PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        { 
            // If it's a quit message, we're out of here.
            if (msg.message == WM_QUIT)  
                return 1; 
            // Otherwise, dispatch the message.
            DispatchMessage(&msg);
        } // End of PeekMessage while loop.

		COleDateTimeSpan	DiffTime( COleDateTime::GetCurrentTime() - m_StartTime );

		if ( (HasBeenKilled == false) && (DiffTime.GetSeconds() > (LONG)m_MaxTime) )
		{
			TRACE("OVERTIME END REQUESTED");
			KillThread();
			HasBeenKilled = true;
		}

		// Process the changes
		// Could call a process virtual method

        // Wait for any message sent or posted to this queue 
        // or for one of the passed handles be set to signaled.
        result = MsgWaitForMultipleObjects( 1, // Number of objects in the array
											pHandles, // Handle of events
											FALSE, // Wait option
											INFINITE, // time-out
											QS_ALLINPUT); 

        // The result tells us the type of event we have.
        if ((result == (WAIT_OBJECT_0 + 1)) || (result == WAIT_TIMEOUT))
        {
            // New messages have arrived. 
            // Continue to the top of the always while loop to 
            // dispatch them and resume waiting.
            continue;
        } 
        else 
        { 
            // One of the handles became signaled. 
            // DoStuff (result - WAIT_OBJECT_0) ; 
			HasBeenKilled = true;
			break;
        } // End of else clause.

    } // End of the always while loop. 

	return 1;
}



/////////////////////////////////////////////////////////////////////////////
// ZSplashWinThread message handlers


BEGIN_MESSAGE_MAP(ZSplashWinThread, CWinThread)
	//{{AFX_MSG_MAP(ZSplashWinThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


