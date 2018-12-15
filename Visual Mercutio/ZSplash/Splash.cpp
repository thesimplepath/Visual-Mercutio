// Splash.cpp : implementation file
//

#include "stdafx.h"
#include "Splash.h"

#include "ZSplashRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const    UINT    TimerID = 777;

/////////////////////////////////////////////////////////////////////////////
// ZSplash

ZSplash::ZSplash()
: m_pThread(NULL)
{
}

ZSplash::~ZSplash()
{
    EndDisplay();
    if (m_pThread != NULL)
        delete m_pThread;
    m_pThread = NULL;
}


bool ZSplash::Display( LPCTSTR szFilename, size_t MaxTime /* = 20 */, bool IncludeProgress /* = true */, CWnd* pParentWnd /* = NULL */ ) 
{
    // Already running
    if (m_pThread != NULL)
        return true;
    m_pThread = new ZSplashWinThread( szFilename, MaxTime, IncludeProgress, pParentWnd );
    if (m_pThread == NULL)
        return false;

    // Create Thread in a suspended state so we can set the Priority
    // before it starts getting away from us
    if (!m_pThread->CreateThread(CREATE_SUSPENDED))
    {
        delete m_pThread;
        m_pThread = NULL;
        return false;
    }

    // If you want to make the sample more sprightly, set the thread priority here
    // a little higher. It has been set at idle priority to keep from bogging down
    // other apps that may also be running.
    VERIFY(m_pThread->SetThreadPriority(THREAD_PRIORITY_IDLE));
    // Now the thread can run wild
    m_pThread->ResumeThread();

    return true;
}

bool ZSplash::Display( UINT nResID, size_t MaxTime /* = 20 */, bool IncludeProgress /* = true */, CWnd* pParentWnd /* = NULL */ ) 
{
    // Already running
    if (m_pThread != NULL)
        return true;
    m_pThread = new ZSplashWinThread( nResID, MaxTime, IncludeProgress, pParentWnd );
    if (m_pThread == NULL)
        return false;

    // Create Thread in a suspended state so we can set the Priority
    // before it starts getting away from us
    if (!m_pThread->CreateThread(CREATE_SUSPENDED))
    {
        delete m_pThread;
        m_pThread = NULL;
        return false;
    }

    // If you want to make the sample more sprightly, set the thread priority here
    // a little higher. It has been set at idle priority to keep from bogging down
    // other apps that may also be running.
    VERIFY(m_pThread->SetThreadPriority(THREAD_PRIORITY_IDLE));
    // Now the thread can run wild
    m_pThread->ResumeThread();

    return true;
}

bool ZSplash::EndDisplay() 
{
    // Not running anymore
    if (m_pThread == NULL)
        return true;
    // Now kill the thread
    m_pThread->KillThread();
    TRACE("END DISPLAY\n");
    return true;
}


void ZSplash::SetProgress(size_t value)
{
    // Not running anymore
    if (m_pThread == NULL)
        return;
    m_pThread->SetProgress( value );
}


void ZSplash::SetText(const CString value)
{
    // Not running anymore
    if (m_pThread == NULL)
        return;
    m_pThread->SetText( value );
}

void ZSplash::SetText(UINT nResID)
{
    // Not running anymore
    if (m_pThread == NULL)
        return;
    m_pThread->SetText( nResID );
}

void ZSplash::AssignParentWindow(CWnd* pParentWnd)
{
    // Not running anymore
    if (m_pThread == NULL)
        return;
    m_pThread->AssignParentWindow( pParentWnd );
}
