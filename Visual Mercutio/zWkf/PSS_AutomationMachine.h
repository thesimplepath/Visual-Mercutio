/****************************************************************************
 * ==> PSS_AutomationMachine -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an automation machine                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_AutomationMachineH
#define PSS_AutomationMachineH

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
#include "ZBStateMachineCollection.h"
#include "ZBStateObject.h"

// forward class declaration
class ZBSymbol;
class ZBLinkSymbol;
class ZDProcessGraphModelMdl;
class PSS_MainAutomationRunnerThread;
class ZILog;

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
* Automation machine
*@author Dominique Aigroz, Jean-Milost Reymond
*@note The state machine is owned by this class, because the main thread is only a worker dealing with the state class
*/
class AFX_EXT_CLASS PSS_AutomationMachine
{
    friend class PSS_MainAutomationRunnerThread;

    public:
        /**
        * Automation move status
        */
        enum IEAutomationMoveStatus
        {
            IE_AS_Error,
            IE_AS_IsWaitingForLinks,
            IE_AS_IsPaused,
            IE_AS_CanMoveForward,
            IE_AS_IsFinished
        };

        /**
        * Constructor
        *@param pModel - model, can be NULL
        *@param pLog - logger, can be NULL
        *@param maxLoop - maximum loop counter, -1 to set to infinite
        *@param maxPaused - maximum paused counter, -1 to set to infinite
        *@param maxWaitingForOtherLinks - maximum waiting for other links counter, -1 to set to infinite
        *@param allowUncompletePath - if true, a path can be broken when object are waiting on other objects
        */
        PSS_AutomationMachine(ZDProcessGraphModelMdl* pModel                  =  NULL,
                              ZILog*                  pLog                    =  NULL,
                              int                     maxLoop                 = -1,
                              int                     maxPaused               = -1,
                              int                     maxWaitingForOtherLinks = -1,
                              bool                    allowUncompletePath     =  false);

        /**
        * Constructor
        *@param pSymbol - model symbol
        *@param pModel - model, can be NULL
        *@param pLog - logger, can be NULL
        *@param maxLoop - maximum loop counter, -1 to set to infinite
        *@param maxPaused - maximum paused counter, -1 to set to infinite
        *@param maxWaitingForOtherLinks - maximum waiting for other links counter, -1 to set to infinite
        *@param allowUncompletePath - if true, a path can be broken when object are waiting on other objects
        */
        PSS_AutomationMachine(ZBSymbol*               pSymbol,
                              ZDProcessGraphModelMdl* pModel                  =  NULL,
                              ZILog*                  pLog                    =  NULL,
                              int                     maxLoop                 = -1,
                              int                     maxPaused               = -1,
                              int                     maxWaitingForOtherLinks = -1,
                              bool                    allowUncompletePath     =  false);

        virtual ~PSS_AutomationMachine();

        /**
        * Assigns a model
        *@param pModel - model to assign
        */
        virtual inline void AssignModel(ZDProcessGraphModelMdl* pModel);

        /**
        * Gets the model used by the automation machine
        *@return the model used by the automation machine
        */
        virtual inline ZDProcessGraphModelMdl* GetModel() const;

        /**
        * Gets the start symbol
        *@return start symbol
        */
        virtual inline ZBSymbol* GetStartSymbol() const;

        /**
        * Sets the start symbol
        *@param pSymbol - symbol
        */
        virtual inline void SetStartSymbol(ZBSymbol* pSymbol);

        /**
        * Gets the state machine collection
        *@return the state machine collection
        */
        virtual inline ZBStateMachineCollection& GetStateMachineCollection();

        /**
        * Gets the state machine count
        *@return the state machine count
        */
        virtual inline std::size_t GetStateMachineCount() const;

        /**
        * Adds a new state machine
        *@param pStateMAchine - state machine to add
        *@return state machine count, -1 on error
        */
        virtual inline int AddStateMachine(ZBStateMachine* pStateMachine);

        /**
        * Gets the machine set to use with the iterator
        *@return the machine set to use with the iterator
        */
        virtual inline       ZBStateMachineSet& GetStateMachineSet();
        virtual inline const ZBStateMachineSet& GetStateMachineSetConst() const;

        /**
        * Gets the state machine
        *@param hStateMachine - state machine handle to get
        *@return the state machine, NULL if not found or on error
        */
        virtual inline ZBStateMachine* GetStateMachine(StateMachineHandle hStateMachine);

        /**
        * Gets the maximum loop counter
        *@return the maximum loop counter
        */
        virtual inline int GetMaxLoop() const;
 
        /**
        * Sets the maximum loop counter
        *@param value - maximum loop counter
        */
        virtual inline void SetMaxLoop(int value);

        /**
        * Gets the maximum paused counter
        *@return the maximum paused counter
        */
        virtual inline int GetMaxPaused() const;

        /**
        * Sets the maximum paused counter
        *@param value - maximum paused counter
        */
        virtual inline void SetMaxPaused(int value);

        /**
        * Gets the maximum waiting for other links counter
        *@return the maximum waiting for other links counter
        */
        virtual inline int GetMaxWaitingForOtherLinks() const;

        /**
        * Sets the maximum waiting for other links counter
        *@param value - maximum waiting for other links counter
        */
        virtual inline void SetMaxWaitingForOtherLinks(int value);

        /**
        * Gets if uncomplete path is allowed
        *@return true if uncomplete path is allowed, otherwise false
        */
        virtual inline bool AllowUncompletePath() const;

        /**
        * Sets if uncomplete path is allowed
        *@param value - if true, uncomplete path is allowed
        */
        virtual inline void SetAllowUncompletePath(bool value = true);

        /**
        * Gets the loop counter
        *@return the loop counter, -1 if infinite
        */
        virtual int GetLoopCounter() const;

        /**
        * Resets the loop counter
        */
        virtual void ResetLoopCounter();

        /**
        * Gets the waiting counter
        *@return the waiting counter, -1 if infinite
        */
        virtual int GetWaitingCounter() const;

        /**
        * Resets the waiting counter
        */
        virtual void ResetWaitingCounter();

        /**
        * Gets the is paused counter
        *@return the is paused counter, -1 if infinite
        */
        virtual int GetIsPausedCounter() const;

        /**
        * Resets the is paused counter
        */
        virtual void ResetIsPausedCounter();

        /**
        * Starts the state machine
        *@param timeout - timeout value, -1 for infinite
        *@return true on success, otherwise false
        */
        virtual bool Start(int timeout = -1);

        /**
        * Stops the state machine
        *@return true on success, otherwise false
        */
        virtual bool Stop();

        /**
        * pauses the state machine
        *@return true on success, otherwise false
        */
        virtual bool Pause();

        /**
        * Resumes the state machine
        *@return true on success, otherwise false
        */
        virtual bool Resume();

        /**
        * Requests a move forward on the state machine
        *@param pState - state
        *@param pStateMachine - state machine
        *@param symbolSet - symbol set
        *@param stateLinkSet - state link set
        *@param pLog - logger
        *@return the move status
        *@note This operation must fill sets of symbol and link corresponding to the
        *      the symbol and link pointer and the direction attributes if there is one.
        */
        virtual IEAutomationMoveStatus RequestMoveForward(ZBStateObject*   pState,
                                                          ZBStateMachine*  pStateMachine,
                                                          ZBSymbolSet&     symbolSet,
                                                          ZBStateLinksSet& stateLinkSet,
                                                          ZILog*           pLog);

        /**
        * Called when state machine is starting
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnStart(ZILog* pLog);

        /**
        * Called when state machine is shutting down
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnStop(ZILog* pLog);

        /**
        * Called when state machine is paused
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnPause(ZILog* pLog);

        /**
        * Called when state machine is resumed
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnResume(ZILog* pLog);

        /**
        * Called when object is finished
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnObjectIsFinished(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called when object is paused
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnObjectIsPaused(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called when object is waiting for other links
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnObjectIsWaitingForOtherLinks(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called before a move forward request is processed
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnBeforeRequestMoveForward(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called when next symbol is received after a move forward request was processed
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnNextSymbolAfterMoveForward(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called before the state machine moves forward
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnBeforeMoveForward(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called after the state machine moves forward
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnAfterMoveForward(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called before the state machine moves backward
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnBeforeMoveBackward(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called after the state machine moves backward
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnAfterMoveBackward(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called on object error
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnObjectError(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called while maximum loop counter is reached
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnReachMaxLoopCounter(ZILog* pLog);

        /**
        * Called while maximum waiting for other links counter is reached
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnReachMaxWaitingForOtherLinksCounter(ZILog* pLog);

        /**
        * Called while maximum in pause counter is reached
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnReachMaxInPauseCounter(ZILog* pLog);

        /**
        * Starts logging
        */
        virtual inline void StartLogging();

        /**
        * Stops logging
        */
        virtual inline void StopLogging();

        /**
        * Check if logging
        *@return true if logging, otherwise false
        */
        virtual inline bool IsLogging() const;

        /**
        * Gets the log
        *@return the log used for checking the symbol
        */
        virtual inline ZILog* GetLog();

        /**
        * Gets the error counter
        *@return the error counter
        */
        virtual inline std::size_t GetErrorCounter() const;

        /**
        * Sets the error counter
        *@param value - error counter
        */
        virtual inline void SetErrorCounter(std::size_t value);

        /**
        * Increments the error counter
        */
        virtual inline void IncrementErrorCounter();

        /**
        * Resets the error counter
        */
        virtual inline void ResetErrorCounter();

        /**
        * Gets the warning counter
        *@return the warning counter
        */
        virtual inline std::size_t GetWarningCounter() const;

        /**
        * Sets the warning counter
        *@param value - warning counter
        */
        virtual inline void SetWarningCounter(std::size_t value);

        /**
        * Increments the warning counter
        */
        virtual inline void IncrementWarningCounter();

        /**
        * Resets the warning counter
        */
        virtual inline void ResetWarningCounter();

    protected:
        ZBStateMachineCollection m_StateMachineCollection;
        ZBStateMachineCollection m_FinishedStateMachineCollection;
        ZDProcessGraphModelMdl*  m_pModel;

        /**
        * Copies the node array to the symbol set
        *@param nodes - node array
        *@param symbolSet - symbol set
        *@return the symbol set item count
        */
        virtual std::size_t CopyNodeArrayToSymbolSet(CODNodeArray& nodes, ZBSymbolSet& symbolSet);

        /**
        * Copies the edge array to the state link set
        *@param edges - edge array
        *@param direction - link direction
        *@param stateLinkSet - state link set
        *@return the state link set item count
        */
        virtual std::size_t CopyEdgeArrayToStateLinksSet(CODEdgeArray&              edges,
                                                         ZBStateLink::LinkDirection direction,
                                                         ZBStateLinksSet&           stateLinkSet);

        /**
        * Deletes all the state machines
        */
        virtual inline void DeleteAllStateMachines();

        /**
        * Deletes all the finished state machines
        */
        virtual inline void DeleteAllFinishedStateMachines();

    private:
        PSS_MainAutomationRunnerThread* m_pMainThread;
        ZBSymbol*                       m_pSymbol;
        ZILog*                          m_pLog;
        std::size_t                     m_ErrorCounter;
        std::size_t                     m_WarningCounter;
        int                             m_MaxLoop;
        int                             m_MaxPaused;
        int                             m_MaxWaitingForOtherLinks;
        bool                            m_IsLogging;
        bool                            m_AllowUncompletePath;

        /**
        * Merges all the state objects
        *@param[in, out] collection - state machine collection to copy to
        *@return true on success, otherwise false
        */
        bool MergeAllStateObjects(ZBStateMachineCollection& collection);

        /**
        * Merges the state machines
        *@param srcIndex - source index
        *@param dstIndex - destination index
        *@param[in, out] collection - state machine collection to copy to
        *@param deleteDestination - if true, destination will be deleted after the merge
        *@return true on success, otherwise false
        */
        bool MergeStateMachine(std::size_t               srcIndex,
                               std::size_t               dstIndex,
                               ZBStateMachineCollection& collection,
                               bool                      deleteDestination = false);

        /**
        * Merges the sources state machines
        *@param pStateMachineToMerge - state machines to merge
        *@return merged state machine, NULL on error
        */
        ZBStateMachine* MergeSourceStateMachines(ZBStateMachine* pStateMachineToMerge);

        /**
        * Finds the original state machine
        *@param pStateMachineToLocate - state machine to locate
        *@return state machine, NULL if not found or on error
        */
        ZBStateMachine* FindOriginalStateMachine(ZBStateMachine* pStateMachineToLocate);

        /**
        * Moves the finished state machine
        *@param pFinishedStateMachine - finished state machine to move
        *@return true on success, otherwise false
        */
        bool MoveFinishedStateMachine(ZBStateMachine* pFinishedStateMachine);

        /**
        * Gets the state machine collection
        *@return the collection
        */
        inline ZBStateMachineCollection& GetFinishedStateMachineCollection();

        /**
        * Gets the finished state machine count
        *@return the counter of state machines
        */
        inline std::size_t GetFinishedStateMachineCount() const;

        /**
        * Adds a new state machine
        *@param pStateMachine - state machine to add
        *@return the state machine count
        */
        inline int AddFinishedStateMachine(ZBStateMachine* pStateMachine);

        /**
        * Gets the finished state machine set to use with the iterator
        *@return the finished state machine set to use with the iterator
        */
        inline       ZBStateMachineSet& GetFinishedStateMachineSet();
        inline const ZBStateMachineSet& GetFinishedStateMachineSetConst() const;

        /**
        * Gets the finished state machine
        *@param hStateMachine - state machine handle
        *@return the finished state machine, NULL if not found or on error
        */
        inline ZBStateMachine* GetFinishedStateMachine(StateMachineHandle hStateMachine);
};

//---------------------------------------------------------------------------
// PSS_AutomationMachine
//---------------------------------------------------------------------------
void PSS_AutomationMachine::AssignModel(ZDProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;
    m_StateMachineCollection.AssignModel(pModel);
};
//---------------------------------------------------------------------------
ZDProcessGraphModelMdl* PSS_AutomationMachine::GetModel() const
{
    return m_pModel;
}
//---------------------------------------------------------------------------
ZBSymbol* PSS_AutomationMachine::GetStartSymbol() const
{
    return m_pSymbol;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::SetStartSymbol(ZBSymbol* pSymbol)
{
    m_pSymbol = pSymbol;
}
//---------------------------------------------------------------------------
ZBStateMachineCollection& PSS_AutomationMachine::GetStateMachineCollection()
{
    return m_StateMachineCollection;
}
//---------------------------------------------------------------------------
std::size_t PSS_AutomationMachine::GetStateMachineCount() const
{
    return m_StateMachineCollection.GetStateMachineCount();
};
//---------------------------------------------------------------------------
int PSS_AutomationMachine::AddStateMachine(ZBStateMachine* pStateMachine)
{
    return m_StateMachineCollection.AddStateMachine(pStateMachine);
};
//---------------------------------------------------------------------------
ZBStateMachineSet& PSS_AutomationMachine::GetStateMachineSet()
{
    return m_StateMachineCollection.GetStateMachineSet();
};
//---------------------------------------------------------------------------
const ZBStateMachineSet& PSS_AutomationMachine::GetStateMachineSetConst() const
{
    return m_StateMachineCollection.GetStateMachineSetConst();
}
//---------------------------------------------------------------------------
ZBStateMachine* PSS_AutomationMachine::GetStateMachine(StateMachineHandle hStateMachine)
{
    return m_StateMachineCollection.GetStateMachine(hStateMachine);
}
//---------------------------------------------------------------------------
int PSS_AutomationMachine::GetMaxLoop() const
{
    return m_MaxLoop;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::SetMaxLoop(int value)
{
    m_MaxLoop = value;
}
//---------------------------------------------------------------------------
int PSS_AutomationMachine::GetMaxPaused() const
{
    return m_MaxPaused;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::SetMaxPaused(int value)
{
    m_MaxPaused = value;
}
//---------------------------------------------------------------------------
int PSS_AutomationMachine::GetMaxWaitingForOtherLinks() const
{
    return m_MaxWaitingForOtherLinks;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::SetMaxWaitingForOtherLinks(int value)
{
    m_MaxWaitingForOtherLinks = value;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::AllowUncompletePath() const
{
    return m_AllowUncompletePath;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::SetAllowUncompletePath(bool value)
{
    m_AllowUncompletePath = value;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::StartLogging()
{
    m_IsLogging = true;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::StopLogging()
{
    m_IsLogging = false;
}
//---------------------------------------------------------------------------
bool PSS_AutomationMachine::IsLogging() const
{
    return m_IsLogging;
}
//---------------------------------------------------------------------------
ZILog* PSS_AutomationMachine::GetLog()
{
    return m_pLog;
}
//---------------------------------------------------------------------------
std::size_t PSS_AutomationMachine::GetErrorCounter() const
{
    return m_ErrorCounter;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::SetErrorCounter(std::size_t value)
{
    m_ErrorCounter = value;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::IncrementErrorCounter()
{
    ++m_ErrorCounter;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::ResetErrorCounter()
{
    m_ErrorCounter = 0;
}
//---------------------------------------------------------------------------
std::size_t PSS_AutomationMachine::GetWarningCounter() const
{
    return m_WarningCounter;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::SetWarningCounter(std::size_t value)
{
    m_WarningCounter = value;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::IncrementWarningCounter()
{
    ++m_WarningCounter;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::ResetWarningCounter()
{
    m_WarningCounter = 0;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::DeleteAllStateMachines()
{
    m_StateMachineCollection.DeleteAllStateMachines();
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::DeleteAllFinishedStateMachines()
{
    m_FinishedStateMachineCollection.DeleteAllStateMachines();
}
//---------------------------------------------------------------------------
ZBStateMachineCollection& PSS_AutomationMachine::GetFinishedStateMachineCollection()
{
    return m_FinishedStateMachineCollection;
}
//---------------------------------------------------------------------------
std::size_t PSS_AutomationMachine::GetFinishedStateMachineCount() const
{
    return m_FinishedStateMachineCollection.GetStateMachineCount();
}
//---------------------------------------------------------------------------
int PSS_AutomationMachine::AddFinishedStateMachine(ZBStateMachine* pStateMachine)
{
    return m_FinishedStateMachineCollection.AddStateMachine(pStateMachine);
}
//---------------------------------------------------------------------------
ZBStateMachineSet& PSS_AutomationMachine::GetFinishedStateMachineSet()
{
    return m_FinishedStateMachineCollection.GetStateMachineSet();
}
//---------------------------------------------------------------------------
const ZBStateMachineSet& PSS_AutomationMachine::GetFinishedStateMachineSetConst() const
{
    return m_FinishedStateMachineCollection.GetStateMachineSetConst();
}
//---------------------------------------------------------------------------
ZBStateMachine* PSS_AutomationMachine::GetFinishedStateMachine(StateMachineHandle hStateMachine)
{
    return m_FinishedStateMachineCollection.GetStateMachine(hStateMachine);
}
//---------------------------------------------------------------------------

#endif
