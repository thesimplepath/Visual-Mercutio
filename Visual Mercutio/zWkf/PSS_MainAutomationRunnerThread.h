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

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_AutomationCollections.h"
#include "PSS_ThinThread.h"

// forward class declaration
class ZBSymbol;
class ZBLinkSymbol;
class ZDProcessGraphModelMdl;
class PSS_AutomationMachine;
class PSS_StateMachineCollection;
class PSS_Log;

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
        PSS_MainAutomationRunnerThread(PSS_AutomationMachine* pAutomationMachine, int timeout = -1, PSS_Log* pLog = NULL);

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
        virtual inline void SetLog(PSS_Log* pLog);

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
        * Called while thread is strating
        */
        virtual void StartWork();

        /**
        * Called every iteration while thread is running
        */
        virtual void DoWork();

        /**
        * Called while thread is shutting down
        */
        virtual void EndWork();

    private:
        PSS_AutomationMachine*    m_pAutomationMachine;
        PSS_StateMachineHandleSet m_MachineHandleSet;
        PSS_Log*                  m_pLog;
        int                       m_Timeout;
        int                       m_LoopCounter;
        int                       m_WaitingCounter;
        int                       m_IsPausedCounter;
};

//---------------------------------------------------------------------------
// PSS_MainAutomationRunnerThread
//---------------------------------------------------------------------------
void PSS_MainAutomationRunnerThread::SetLog(PSS_Log* pLog)
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
