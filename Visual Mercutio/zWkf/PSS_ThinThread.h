/****************************************************************************
 * ==> PSS_ThinThread ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a thin thread system                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ThinThreadH 
#define PSS_ThinThreadH 

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH 
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include <afxmt.h> 

#ifdef _ZWKFEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Thin thread system
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ThinThread
{ 
    public: 
        PSS_ThinThread();
        virtual ~PSS_ThinThread();

        /**
        * Creates a new thread
        *@param flags - create flags
        *@param stackSize - stack size
        *@param pSecurityAttrs - security attributes, can be NULL
        *@param timeout - time to wait before timeout, in milliseconds
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateThread(DWORD                 flags          = 0,
                                  UINT                  stackSize      = 0,
                                  LPSECURITY_ATTRIBUTES pSecurityAttrs = NULL,
                                  UINT                  timeout        = INFINITE);

        /**
        * Gets second thread handle
        *@return second thread handle
        */
        virtual inline HANDLE GetHandle() const;

        /**
        * Gets if second thread is busy
        *@return TRUE if second thread is busy, otherwise FALSE
        */
        virtual inline BOOL IsBusy() const;

        /**
        * Stops the thread
        */
        virtual inline void Stop();

    protected: 
        CEvent* m_pWorkEvent;
        CEvent* m_pExitEvent;
        HANDLE  m_hSecondThread;
        DWORD   m_ThreadID;
        int     m_Timeout;
        BOOL    m_EndThread;
        BOOL    m_SecondThreadActive;

        /**
        * Runs the thread (this is equivalent to the thread main loop)
        *@return 0 on success, otherwise error code
        */
        virtual int Run();

        /**
        * Called when thread start to work
        */
        virtual void StartWork();

        /**
        * Called when thread is working
        */
        virtual void DoWork() = 0;

        /**
        * Called when thread is shutdown
        */
        virtual void EndWork();

        /**
        * Gets the cycle control event
        *@return the cycle control event, NULL if not found or on error
        */
        virtual inline CEvent* GetEvent() const;

        /**
        * Gets the timeout time
        *@return the timeout time in milliseconds
        */
        virtual inline int GetTimeout() const;

        /**
        * Sets the cycle time
        *@param time - cycle time in milliseconds
        */
        virtual inline void SetTimeout(int time);

        /**
        * Kills the second thread
        */
        virtual void KillSecondThread();

        /**
        * Statically starts a thread
        *@param pThread - thread to start
        *@return 0 on success, otherwise error code
        *@note WARNING pThread must be of type PSS_ThinThread, no typecast check is performed
        */
        static unsigned __stdcall Start(void* pThread);
};

//---------------------------------------------------------------------------
// PSS_ThinThread
//---------------------------------------------------------------------------
HANDLE PSS_ThinThread::GetHandle() const
{
    return m_hSecondThread;
};
//---------------------------------------------------------------------------
BOOL PSS_ThinThread::IsBusy() const
{
    return m_SecondThreadActive;
};
//---------------------------------------------------------------------------
void PSS_ThinThread::Stop()
{
    m_EndThread = TRUE;
};
//---------------------------------------------------------------------------
CEvent* PSS_ThinThread::GetEvent() const
{
    return m_pWorkEvent;
};
//---------------------------------------------------------------------------
int PSS_ThinThread::GetTimeout() const
{
    return m_Timeout;
};
//---------------------------------------------------------------------------
void PSS_ThinThread::SetTimeout(int time)
{
    m_Timeout = time;
}
//---------------------------------------------------------------------------

#endif
