/****************************************************************************
 * ==> PSS_SplashController ------------------------------------------------*
 ****************************************************************************
 * Description : Splash screen controller, allows to run a splash screen    *
 *               inside a thread, and to show and hide it                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SplashController.h"

// resources
#include "ZSplashRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Gloabl defines
//---------------------------------------------------------------------------
const UINT g_TimerID = 777;
//---------------------------------------------------------------------------
// PSS_SplashController
//---------------------------------------------------------------------------
PSS_SplashController::PSS_SplashController() :
    m_pThread(NULL)
{}
//---------------------------------------------------------------------------
PSS_SplashController::~PSS_SplashController()
{
    Hide();

    if (m_pThread)
        delete m_pThread;
}
//---------------------------------------------------------------------------
bool PSS_SplashController::Show(LPCTSTR pFileName, std::size_t maxTime, bool includeProgress, CWnd* pParent)
{
    // already running?
    if (m_pThread)
        return true;

    m_pThread = new PSS_SplashWndThread(pFileName, maxTime, includeProgress, pParent);

    if (!m_pThread)
        return false;

    // create thread in a suspended state, so the priority can be set before it starts
    if (!m_pThread->CreateThread(CREATE_SUSPENDED))
    {
        delete m_pThread;
        m_pThread = NULL;
        return false;
    }

    // to make the sample more sprightly, set the below thread priority a little higher. It has been set at idle priority
    // to keep from bogging down other apps that may also be running
    VERIFY(m_pThread->SetThreadPriority(THREAD_PRIORITY_IDLE));

    // run the thread
    m_pThread->ResumeThread();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SplashController::Show(UINT resID, std::size_t maxTime, bool includeProgress, CWnd* pParent)
{
    // already running?
    if (m_pThread)
        return true;

    m_pThread = new PSS_SplashWndThread(resID, maxTime, includeProgress, pParent);

    if (!m_pThread)
        return false;

    // create thread in a suspended state, so the priority can be set before it starts
    if (!m_pThread->CreateThread(CREATE_SUSPENDED))
    {
        delete m_pThread;
        m_pThread = NULL;
        return false;
    }

    // to make the sample more sprightly, set the below thread priority a little higher. It has been set at idle priority
    // to keep from bogging down other apps that may also be running
    VERIFY(m_pThread->SetThreadPriority(THREAD_PRIORITY_IDLE));

    // run the thread
    m_pThread->ResumeThread();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SplashController::Hide()
{
    // no longer running?
    if (!m_pThread)
        return true;

    // kill the thread
    m_pThread->KillThread();
    
    TRACE("PSS_SplashController - splash screen is closed\n");

    return true;
}
//---------------------------------------------------------------------------
void PSS_SplashController::SetProgress(std::size_t value)
{
    // no longer running?
    if (!m_pThread)
        return;

    m_pThread->SetProgress(value);
}
//---------------------------------------------------------------------------
void PSS_SplashController::SetText(const CString& value)
{
    // no longer running?
    if (!m_pThread)
        return;

    m_pThread->SetText(value);
}
//---------------------------------------------------------------------------
void PSS_SplashController::SetText(UINT resID)
{
    // no longer running?
    if (!m_pThread)
        return;

    m_pThread->SetText(resID);
}
//---------------------------------------------------------------------------
void PSS_SplashController::SetParent(CWnd* pParent)
{
    // no longer running?
    if (!m_pThread)
        return;

    m_pThread->SetParent(pParent);
}
//---------------------------------------------------------------------------
