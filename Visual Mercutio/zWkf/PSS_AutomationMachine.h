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
#include "PSS_StateMachineCollection.h"
#include "PSS_StateObject.h"

// class name mapping
#ifndef PSS_Symbol
    #define PSS_Symbol ZBSymbol
#endif
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_Symbol;
class PSS_LinkSymbol;
class PSS_ProcessGraphModelMdl;
class PSS_MainAutomationRunnerThread;
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
        PSS_AutomationMachine(PSS_ProcessGraphModelMdl* pModel                  =  NULL,
                              PSS_Log*                  pLog                    =  NULL,
                              int                       maxLoop                 = -1,
                              int                       maxPaused               = -1,
                              int                       maxWaitingForOtherLinks = -1,
                              bool                      allowUncompletePath     =  false);

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
        PSS_AutomationMachine(PSS_Symbol*               pSymbol,
                              PSS_ProcessGraphModelMdl* pModel                  =  NULL,
                              PSS_Log*                  pLog                    =  NULL,
                              int                       maxLoop                 = -1,
                              int                       maxPaused               = -1,
                              int                       maxWaitingForOtherLinks = -1,
                              bool                      allowUncompletePath     =  false);

        virtual ~PSS_AutomationMachine();

        /**
        * Assigns a model
        *@param pModel - model to assign
        */
        virtual inline void AssignModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Gets the model used by the automation machine
        *@return the model used by the automation machine
        */
        virtual inline PSS_ProcessGraphModelMdl* GetModel() const;

        /**
        * Gets the start symbol
        *@return start symbol
        */
        virtual inline PSS_Symbol* GetStartSymbol() const;

        /**
        * Sets the start symbol
        *@param pSymbol - symbol
        */
        virtual inline void SetStartSymbol(PSS_Symbol* pSymbol);

        /**
        * Gets the state machine collection
        *@return the state machine collection
        */
        virtual inline PSS_StateMachineCollection& GetStateMachineCollection();

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
        virtual inline int AddStateMachine(PSS_StateMachine* pStateMachine);

        /**
        * Gets the machine set to use with the iterator
        *@return the machine set to use with the iterator
        */
        virtual inline       PSS_StateMachineSet& GetStateMachineSet();
        virtual inline const PSS_StateMachineSet& GetStateMachineSetConst() const;

        /**
        * Gets the state machine
        *@param hStateMachine - state machine handle to get
        *@return the state machine, NULL if not found or on error
        */
        virtual inline PSS_StateMachine* GetStateMachine(PSS_StateMachineHandle hStateMachine);

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
        * Pauses the state machine
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
        *      the symbol and link pointer and the direction attributes if there is one
        */
        virtual IEAutomationMoveStatus RequestMoveForward(PSS_StateObject*   pState,
                                                          PSS_StateMachine*  pStateMachine,
                                                          PSS_SymbolSet&     symbolSet,
                                                          PSS_StateLinksSet& stateLinkSet,
                                                          PSS_Log*           pLog);

        /**
        * Called when state machine is starting
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnStart(PSS_Log* pLog);

        /**
        * Called when state machine is shutting down
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnStop(PSS_Log* pLog);

        /**
        * Called when state machine is paused
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnPause(PSS_Log* pLog);

        /**
        * Called when state machine is resumed
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnResume(PSS_Log* pLog);

        /**
        * Called when object is finished
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnObjectIsFinished(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called when object is paused
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnObjectIsPaused(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called when object is waiting for other links
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnObjectIsWaitingForOtherLinks(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called before a move forward request is processed
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnBeforeRequestMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called when next symbol is received after a move forward request was processed
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnNextSymbolAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called before the state machine moves forward
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnBeforeMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called after the state machine moves forward
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called before the state machine moves backward
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnBeforeMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called after the state machine moves backward
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnAfterMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called on object error
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnObjectError(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called while maximum loop counter is reached
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnReachMaxLoopCounter(PSS_Log* pLog);

        /**
        * Called while maximum waiting for other links counter is reached
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnReachMaxWaitingForOtherLinksCounter(PSS_Log* pLog);

        /**
        * Called while maximum in pause counter is reached
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnReachMaxInPauseCounter(PSS_Log* pLog);

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
        virtual inline PSS_Log* GetLog();

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
        PSS_StateMachineCollection m_StateMachineCollection;
        PSS_StateMachineCollection m_FinishedStateMachineCollection;
        PSS_ProcessGraphModelMdl*  m_pModel;

        /**
        * Copies the node array to the symbol set
        *@param nodes - node array
        *@param symbolSet - symbol set
        *@return the symbol set item count
        */
        virtual std::size_t CopyNodeArrayToSymbolSet(CODNodeArray& nodes, PSS_SymbolSet& symbolSet);

        /**
        * Copies the edge array to the state link set
        *@param edges - edge array
        *@param direction - link direction
        *@param stateLinkSet - state link set
        *@return the state link set item count
        */
        virtual std::size_t CopyEdgeArrayToStateLinksSet(CODEdgeArray&                  edges,
                                                         PSS_StateLink::IELinkDirection direction,
                                                         PSS_StateLinksSet&             stateLinkSet);

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
        PSS_Symbol*                     m_pSymbol;
        PSS_Log*                        m_pLog;
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
        bool MergeAllStateObjects(PSS_StateMachineCollection& collection);

        /**
        * Merges the state machines
        *@param srcIndex - source index
        *@param dstIndex - destination index
        *@param[in, out] collection - state machine collection to copy to
        *@param deleteDestination - if true, destination will be deleted after the merge
        *@return true on success, otherwise false
        */
        bool MergeStateMachine(std::size_t                 srcIndex,
                               std::size_t                 dstIndex,
                               PSS_StateMachineCollection& collection,
                               bool                        deleteDestination = false);

        /**
        * Merges the sources state machines
        *@param pStateMachineToMerge - state machines to merge
        *@return merged state machine, NULL on error
        */
        PSS_StateMachine* MergeSourceStateMachines(PSS_StateMachine* pStateMachineToMerge);

        /**
        * Finds the original state machine
        *@param pStateMachineToLocate - state machine to locate
        *@return state machine, NULL if not found or on error
        */
        PSS_StateMachine* FindOriginalStateMachine(PSS_StateMachine* pStateMachineToLocate);

        /**
        * Moves the finished state machine
        *@param pFinishedStateMachine - finished state machine to move
        *@return true on success, otherwise false
        */
        bool MoveFinishedStateMachine(PSS_StateMachine* pFinishedStateMachine);

        /**
        * Gets the state machine collection
        *@return the collection
        */
        inline PSS_StateMachineCollection& GetFinishedStateMachineCollection();

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
        inline int AddFinishedStateMachine(PSS_StateMachine* pStateMachine);

        /**
        * Gets the finished state machine set to use with the iterator
        *@return the finished state machine set to use with the iterator
        */
        inline       PSS_StateMachineSet& GetFinishedStateMachineSet();
        inline const PSS_StateMachineSet& GetFinishedStateMachineSetConst() const;

        /**
        * Gets the finished state machine
        *@param hStateMachine - state machine handle
        *@return the finished state machine, NULL if not found or on error
        */
        inline PSS_StateMachine* GetFinishedStateMachine(PSS_StateMachineHandle hStateMachine);
};

//---------------------------------------------------------------------------
// PSS_AutomationMachine
//---------------------------------------------------------------------------
void PSS_AutomationMachine::AssignModel(PSS_ProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;
    m_StateMachineCollection.AssignModel(pModel);
};
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_AutomationMachine::GetModel() const
{
    return m_pModel;
}
//---------------------------------------------------------------------------
PSS_Symbol* PSS_AutomationMachine::GetStartSymbol() const
{
    return m_pSymbol;
}
//---------------------------------------------------------------------------
void PSS_AutomationMachine::SetStartSymbol(PSS_Symbol* pSymbol)
{
    m_pSymbol = pSymbol;
}
//---------------------------------------------------------------------------
PSS_StateMachineCollection& PSS_AutomationMachine::GetStateMachineCollection()
{
    return m_StateMachineCollection;
}
//---------------------------------------------------------------------------
std::size_t PSS_AutomationMachine::GetStateMachineCount() const
{
    return m_StateMachineCollection.GetStateMachineCount();
};
//---------------------------------------------------------------------------
int PSS_AutomationMachine::AddStateMachine(PSS_StateMachine* pStateMachine)
{
    return m_StateMachineCollection.AddStateMachine(pStateMachine);
};
//---------------------------------------------------------------------------
PSS_StateMachineSet& PSS_AutomationMachine::GetStateMachineSet()
{
    return m_StateMachineCollection.GetStateMachineSet();
};
//---------------------------------------------------------------------------
const PSS_StateMachineSet& PSS_AutomationMachine::GetStateMachineSetConst() const
{
    return m_StateMachineCollection.GetStateMachineSetConst();
}
//---------------------------------------------------------------------------
PSS_StateMachine* PSS_AutomationMachine::GetStateMachine(PSS_StateMachineHandle hStateMachine)
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
PSS_Log* PSS_AutomationMachine::GetLog()
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
PSS_StateMachineCollection& PSS_AutomationMachine::GetFinishedStateMachineCollection()
{
    return m_FinishedStateMachineCollection;
}
//---------------------------------------------------------------------------
std::size_t PSS_AutomationMachine::GetFinishedStateMachineCount() const
{
    return m_FinishedStateMachineCollection.GetStateMachineCount();
}
//---------------------------------------------------------------------------
int PSS_AutomationMachine::AddFinishedStateMachine(PSS_StateMachine* pStateMachine)
{
    return m_FinishedStateMachineCollection.AddStateMachine(pStateMachine);
}
//---------------------------------------------------------------------------
PSS_StateMachineSet& PSS_AutomationMachine::GetFinishedStateMachineSet()
{
    return m_FinishedStateMachineCollection.GetStateMachineSet();
}
//---------------------------------------------------------------------------
const PSS_StateMachineSet& PSS_AutomationMachine::GetFinishedStateMachineSetConst() const
{
    return m_FinishedStateMachineCollection.GetStateMachineSetConst();
}
//---------------------------------------------------------------------------
PSS_StateMachine* PSS_AutomationMachine::GetFinishedStateMachine(PSS_StateMachineHandle hStateMachine)
{
    return m_FinishedStateMachineCollection.GetStateMachine(hStateMachine);
}
//---------------------------------------------------------------------------

#endif
