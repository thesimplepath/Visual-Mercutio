/****************************************************************************
 * ==> PSS_MainPathRunnerThread --------------------------------------------*
 ****************************************************************************
 * Description : The main path runner thread                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MainPathRunnerThreadH
#define PSS_MainPathRunnerThreadH

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

// class name mapping
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class ZBSymbol;
class PSS_LinkSymbol;
class PSS_ProcessGraphModelMdl;
class PSS_PathMachine;
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
* Main path runner thread
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_MainPathRunnerThread : public PSS_ThinThread
{
    public:
        /**
        * Constructor
        *@param pAutomationMachine - automation machine to use
        *@param timeout - timeout time, -1 for infinite
        *@param pLog - logger, can be NULL
        */
        PSS_MainPathRunnerThread(PSS_PathMachine* pAutomationMachine, int timeout = -1, PSS_Log* pLog = NULL);

        virtual ~PSS_MainPathRunnerThread();

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

    protected:
        /**
        * Protected constructor used by dynamic creation 
        */
        PSS_MainPathRunnerThread();

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
        PSS_PathMachine*          m_pPathMachine;
        PSS_StateMachineHandleSet m_MachineHandleSet;
        PSS_Log*                  m_pLog;
        int                       m_Timeout;
        int                       m_LoopCounter;
        int                       m_WaitingCounter;
        int                       m_IsPausedCounter;
};

//---------------------------------------------------------------------------
// PSS_MainPathRunnerThread
//---------------------------------------------------------------------------
void PSS_MainPathRunnerThread::SetLog(PSS_Log* pLog)
{
    m_pLog = pLog;
};
//---------------------------------------------------------------------------

#endif
