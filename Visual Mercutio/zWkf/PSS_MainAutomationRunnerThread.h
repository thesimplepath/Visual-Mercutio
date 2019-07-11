/****************************************************************************
 * ==> PSS_MainAutomationRunnerThread --------------------------------------*
 ****************************************************************************
 * Description : The main automation runner thread                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MainAutomationRunnerThreadH
#define PSS_MainAutomationRunnerThreadH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "PSS_AutomationCollections.h"
#include "PSS_ThinThread.h"

// forward class declaration
class ZBSymbol;
class ZBLinkSymbol;
class ZDProcessGraphModelMdl;
class PSS_AutomationMachine;
class ZBStateMachineCollection;
class ZILog;

/**
* Main automation runner thread
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_MainAutomationRunnerThread : public PSS_ThinThread
{
    public:
        /**
        * Constructor
        *@param pAutomationMachine - automation machine to use
        *@param timeout - timeout time, -1 for infinite
        *@param pLog - logger, can be NULL
        */
        PSS_MainAutomationRunnerThread(PSS_AutomationMachine* pAutomationMachine, int timeout = -1, ZILog* pLog = NULL);
        virtual ~PSS_MainAutomationRunnerThread();

        /**
        * Starts the thread
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL StartThread();

        /**
        * Sets the logger to use
        *@param pLog - logger
        */
        virtual inline void SetLog(ZILog* pLog);

        /**
        * Gets the loop counter
        *@return the loop counter
        */
        virtual inline int GetLoopCounter() const;

        /**
        * Resets the loop counter
        */
        virtual inline void ResetLoopCounter();

        /**
        * Gets the waiting counter
        *@return the waiting counter
        */
        virtual inline int GetWaitingCounter() const;

        /**
        * Resets the waiting counter
        */
        virtual inline void ResetWaitingCounter();

        /**
        * Gets the is paused counter
        *@return the is paused counter
        */
        virtual inline int GetIsPausedCounter() const;

        /**
        * Resets the is paused counter
        */
        virtual inline void ResetIsPausedCounter();

    protected:
        /**
        * Protected constructor used by dynamic creation
        */
        PSS_MainAutomationRunnerThread();

        /**
        * Called when thread is strating
        */
        virtual void StartWork();

        /**
        * Called when thread is working, on each loop
        */
        virtual void DoWork();

        /**
        * Called when thread is shutting down
        */
        virtual void EndWork();

    private:
        PSS_AutomationMachine*  m_pAutomationMachine;
        ZBStateMachineHandleSet m_MachineHandleSet;
        ZILog*                  m_pLog;
        int                     m_Timeout;
        int                     m_LoopCounter;
        int                     m_WaitingCounter;
        int                     m_IsPausedCounter;
};

//---------------------------------------------------------------------------
// PSS_MainAutomationRunnerThread
//---------------------------------------------------------------------------
void PSS_MainAutomationRunnerThread::SetLog(ZILog* pLog)
{
    m_pLog = pLog;
}
//---------------------------------------------------------------------------
int PSS_MainAutomationRunnerThread::GetLoopCounter() const
{
    return m_LoopCounter;
}
//---------------------------------------------------------------------------
void PSS_MainAutomationRunnerThread::ResetLoopCounter()
{
    m_LoopCounter = 0;
}
//---------------------------------------------------------------------------
int PSS_MainAutomationRunnerThread::GetWaitingCounter() const
{
    return m_WaitingCounter;
}
//---------------------------------------------------------------------------
void PSS_MainAutomationRunnerThread::ResetWaitingCounter()
{
    m_WaitingCounter = 0;
}
//---------------------------------------------------------------------------
int PSS_MainAutomationRunnerThread::GetIsPausedCounter() const
{
    return m_IsPausedCounter;
}
//---------------------------------------------------------------------------
void PSS_MainAutomationRunnerThread::ResetIsPausedCounter()
{
    m_IsPausedCounter = 0;
}
//---------------------------------------------------------------------------

#endif
