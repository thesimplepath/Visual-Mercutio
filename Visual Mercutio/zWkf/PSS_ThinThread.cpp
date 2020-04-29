/****************************************************************************
 * ==> PSS_ThinThread ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a thin thread system                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h" 
#include "PSS_ThinThread.h" 

// Windows
#include <process.h>

//---------------------------------------------------------------------------
// PSS_ThinThread
//---------------------------------------------------------------------------
PSS_ThinThread::PSS_ThinThread() :
    m_pWorkEvent(NULL),
    m_pExitEvent(NULL),
    m_hSecondThread(NULL),
    m_ThreadID(0),
    m_Timeout(0),
    m_EndThread(FALSE),
    m_SecondThreadActive(FALSE)
{
    // create a signaled, manual-reset event to synchronize destruction
    m_pExitEvent = new CEvent(TRUE, TRUE);
    PSS_Assert(m_pExitEvent); 

    // create a non-signaled, auto-reset event to wait on for work cycle
    m_pWorkEvent = new CEvent();
    PSS_Assert(m_pWorkEvent);
}
//---------------------------------------------------------------------------
PSS_ThinThread::~PSS_ThinThread()
{
    if (m_pWorkEvent)
        delete m_pWorkEvent;

    if (m_pExitEvent)
        delete m_pExitEvent;

    TRACE("End CThinThread\n");
}
//---------------------------------------------------------------------------
BOOL PSS_ThinThread::CreateThread(DWORD flags, UINT stackSize, LPSECURITY_ATTRIBUTES pSecurityAttrs, UINT timeout)
{
    m_SecondThreadActive = TRUE;
    m_EndThread          = FALSE;
    m_Timeout            = timeout;

    // exit event is reset until process is done
    m_pExitEvent->ResetEvent(); 

    // start second thread 
    m_hSecondThread = ::CreateThread(pSecurityAttrs,
                                     DWORD(stackSize),
                                     LPTHREAD_START_ROUTINE(Start),
                                     LPVOID(this),
                                     DWORD(flags),
                                     LPDWORD(&m_ThreadID));

    return (m_hSecondThread ? TRUE : FALSE);
}
//---------------------------------------------------------------------------
int PSS_ThinThread::Run()
{
    // sync on the work event
    CSingleLock csl(m_pWorkEvent);

    // do derived startup
    StartWork();
    TRACE("StartWork PSS_ThinThread\n");

    // loop until done
    while (!m_EndThread)
    {
        // wait for event or timeout
        csl.Lock(m_Timeout);
        csl.Unlock();

        if (!m_EndThread)
        {
            // do derived work
            DoWork();
            TRACE("DoWork PSS_ThinThread\n");
        }
    }

    // do derived shutdown
    EndWork();
    TRACE("EndWork PSS_ThinThread\n");

    // set not waiting signal
    m_pExitEvent->SetEvent();

    m_SecondThreadActive = FALSE;

    return 0;
}
//---------------------------------------------------------------------------
void PSS_ThinThread::StartWork()
{}
//---------------------------------------------------------------------------
void PSS_ThinThread::EndWork()
{}
//---------------------------------------------------------------------------
void PSS_ThinThread::KillSecondThread()
{
    // start up the other thread so it can complete. When it does, it will set the exit event
    // and the object can be destructed.
    m_EndThread = TRUE; 

    m_pWorkEvent->SetEvent(); 

    CSingleLock csl(m_pExitEvent); 

    // wait for 2nd thread to finish 
    csl.Lock();
    csl.Unlock();

    TRACE("KillThread2 CThinThread\n");
}
//---------------------------------------------------------------------------
unsigned __stdcall PSS_ThinThread::Start(void* pThread)
{ 
    TRACE("static start PSS_ThinThread\n");
    return static_cast<PSS_ThinThread*>(pThread)->Run();
}
//---------------------------------------------------------------------------
