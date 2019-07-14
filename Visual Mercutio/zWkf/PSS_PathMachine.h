/****************************************************************************
 * ==> PSS_PathMachine -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a path machine                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PathMachine
#define PSS_PathMachineH

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

// forward class declaration
class ZBSymbol;
class ZBLinkSymbol;
class ZDProcessGraphModelMdl;
class PSS_MainPathRunnerThread;
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
* Path machine
*@author Dominique Aigroz, Jean-Milost Reymond
*@note The state machine is owned by this class, because the main thread is only a worker dealing with the state class
*/
class AFX_EXT_CLASS PSS_PathMachine
{
    friend class PSS_MainPathRunnerThread;

    public:
        /**
        * Path move status
        */
        enum IEPathMoveStatus
        {
            IE_PS_Error,
            IE_PS_IsWaitingForLinks,
            IE_PS_IsPaused,
            IE_PS_CanMoveForward,
            IE_PS_IsFinished
        };

    public:
        /**
        * Constructor
        *@param pModel - model, can be NULL
        *@param pSymbol - symbol, can be NULL
        *@param pLog - logger, can be NULL
        *@param maxLoop - maximum loop counter, -1 to set to infinite
        *@param maxPaused - maximum paused counter, -1 to set to infinite
        *@param maxWaitingForOtherLinks - maximum waiting for other links counter, -1 to set to infinite
        */
        PSS_PathMachine(ZDProcessGraphModelMdl* pModel                  =  NULL,
                        ZBSymbol*               pSymbol                 =  NULL,
                        ZILog*                  pLog                    =  NULL,
                        int                     maxLoop                 = -1,
                        int                     maxPaused               = -1,
                        int                     maxWaitingForOtherLinks = -1);

        virtual ~PSS_PathMachine();

        /**
        * Assigns a model
        *@param pModel - model to assign
        */
        virtual inline void AssignModel(ZDProcessGraphModelMdl* pModel);

        /**
        * Gets the model used by the path machine
        *@return the model used by the path machine
        */
        virtual inline ZDProcessGraphModelMdl* GetModel();

        /**
        * Gets the start symbol
        *@return start symbol
        */
        virtual inline ZBSymbol* GetSymbol();

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
        virtual IEPathMoveStatus RequestMoveForward(PSS_StateObject*   pState,
                                                    PSS_StateMachine*  pStateMachine,
                                                    PSS_SymbolSet&     symbolSet,
                                                    PSS_StateLinksSet& stateLinkSet,
                                                    ZILog*             pLog);

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
        virtual bool OnObjectIsFinished(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called when object is paused
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnObjectIsPaused(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called when object is waiting for other links
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnObjectIsWaitingForOtherLinks(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called before a move forward request is processed
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnBeforeRequestMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called when next symbol is received after a move forward request was processed
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnNextSymbolAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called before the state machine moves forward
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnBeforeMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called after the state machine moves forward
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called before the state machine moves backward
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnBeforeMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called after the state machine moves backward
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnAfterMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

        /**
        * Called on object error
        *@param pState - state
        *@param pStateMachine - state machine
        *@param pLog - logger
        *@return true on success, otherwise false
        */
        virtual bool OnObjectError(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

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
        PSS_StateMachineCollection m_StateMachineCollection;
        PSS_StateMachineCollection m_FinishedStateMachineCollection;
        ZDProcessGraphModelMdl*    m_pModel;

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
        PSS_MainPathRunnerThread* m_pMainThread;
        ZBSymbol*                 m_pSymbol;
        ZILog*                    m_pLog;
        std::size_t               m_ErrorCounter;
        std::size_t               m_WarningCounter;
        int                       m_MaxLoop;
        int                       m_MaxPaused;
        int                       m_MaxWaitingForOtherLinks;
        bool                      m_IsLogging;

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
// PSS_PathMachine
//---------------------------------------------------------------------------
void PSS_PathMachine::AssignModel(ZDProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;
    m_StateMachineCollection.AssignModel(pModel);
}
//---------------------------------------------------------------------------
ZDProcessGraphModelMdl* PSS_PathMachine::GetModel()
{
    return m_pModel;
}
//---------------------------------------------------------------------------
ZBSymbol* PSS_PathMachine::GetSymbol()
{
    return m_pSymbol;
}
//---------------------------------------------------------------------------
PSS_StateMachineCollection& PSS_PathMachine::GetStateMachineCollection()
{
    return m_StateMachineCollection;
}
//---------------------------------------------------------------------------
std::size_t PSS_PathMachine::GetStateMachineCount() const
{
    return m_StateMachineCollection.GetStateMachineCount();
}
//---------------------------------------------------------------------------
int PSS_PathMachine::AddStateMachine(PSS_StateMachine* pStateMachine)
{
    return m_StateMachineCollection.AddStateMachine(pStateMachine);
}
//---------------------------------------------------------------------------
PSS_StateMachineSet& PSS_PathMachine::GetStateMachineSet()
{
    return m_StateMachineCollection.GetStateMachineSet();
}
//---------------------------------------------------------------------------
const PSS_StateMachineSet& PSS_PathMachine::GetStateMachineSetConst() const
{
    return m_StateMachineCollection.GetStateMachineSetConst();
}
//---------------------------------------------------------------------------
PSS_StateMachine* PSS_PathMachine::GetStateMachine(PSS_StateMachineHandle hStateMachine)
{
    return m_StateMachineCollection.GetStateMachine(hStateMachine);
}
//---------------------------------------------------------------------------
int PSS_PathMachine::GetMaxLoop() const
{
    return m_MaxLoop;
}
//---------------------------------------------------------------------------
void PSS_PathMachine::SetMaxLoop(int value)
{
    m_MaxLoop = value;
}
//---------------------------------------------------------------------------
int PSS_PathMachine::GetMaxPaused() const
{
    return m_MaxPaused;
}
//---------------------------------------------------------------------------
void PSS_PathMachine::SetMaxPaused(int value)
{
    m_MaxPaused = value;
}
//---------------------------------------------------------------------------
int PSS_PathMachine::GetMaxWaitingForOtherLinks() const
{
    return m_MaxWaitingForOtherLinks;
}
//---------------------------------------------------------------------------
void PSS_PathMachine::SetMaxWaitingForOtherLinks(int value)
{
    m_MaxWaitingForOtherLinks = value;
}
//---------------------------------------------------------------------------
void PSS_PathMachine::StartLogging()
{
    m_IsLogging = true;
}
//---------------------------------------------------------------------------
void PSS_PathMachine::StopLogging()
{
    m_IsLogging = false;
}
//---------------------------------------------------------------------------
bool PSS_PathMachine::IsLogging() const
{
    return m_IsLogging;
}
//---------------------------------------------------------------------------
ZILog* PSS_PathMachine::GetLog()
{
    return m_pLog;
}
//---------------------------------------------------------------------------
std::size_t PSS_PathMachine::GetErrorCounter() const
{
    return m_ErrorCounter;
}
//---------------------------------------------------------------------------
void PSS_PathMachine::SetErrorCounter(std::size_t value)
{
    m_ErrorCounter = value;
}
//---------------------------------------------------------------------------
void PSS_PathMachine::IncrementErrorCounter()
{
    ++m_ErrorCounter;
}
//---------------------------------------------------------------------------
void PSS_PathMachine::ResetErrorCounter()
{
    m_ErrorCounter = 0;
}
//---------------------------------------------------------------------------
std::size_t PSS_PathMachine::GetWarningCounter() const
{
    return m_WarningCounter;
}
//---------------------------------------------------------------------------
void PSS_PathMachine::SetWarningCounter(std::size_t value)
{
    m_WarningCounter = value;
}
//---------------------------------------------------------------------------
void PSS_PathMachine::IncrementWarningCounter()
{
    ++m_WarningCounter;
}
//---------------------------------------------------------------------------
void PSS_PathMachine::ResetWarningCounter()
{
    m_WarningCounter = 0;
}
//---------------------------------------------------------------------------
void PSS_PathMachine::DeleteAllStateMachines()
{
    m_StateMachineCollection.DeleteAllStateMachines();
}
//---------------------------------------------------------------------------
void PSS_PathMachine::DeleteAllFinishedStateMachines()
{
    m_FinishedStateMachineCollection.DeleteAllStateMachines();
}
//---------------------------------------------------------------------------
PSS_StateMachineCollection& PSS_PathMachine::GetFinishedStateMachineCollection()
{
    return m_FinishedStateMachineCollection;
}
//---------------------------------------------------------------------------
std::size_t PSS_PathMachine::GetFinishedStateMachineCount() const
{
    return m_FinishedStateMachineCollection.GetStateMachineCount();
}
//---------------------------------------------------------------------------
int PSS_PathMachine::AddFinishedStateMachine(PSS_StateMachine* pStateMachine)
{
    return m_FinishedStateMachineCollection.AddStateMachine(pStateMachine);
}
//---------------------------------------------------------------------------
PSS_StateMachineSet& PSS_PathMachine::GetFinishedStateMachineSet()
{
    return m_FinishedStateMachineCollection.GetStateMachineSet();
}
//---------------------------------------------------------------------------
const PSS_StateMachineSet& PSS_PathMachine::GetFinishedStateMachineSetConst() const
{
    return m_FinishedStateMachineCollection.GetStateMachineSetConst();
}
//---------------------------------------------------------------------------
PSS_StateMachine* PSS_PathMachine::GetFinishedStateMachine(PSS_StateMachineHandle hStateMachine)
{
    return m_FinishedStateMachineCollection.GetStateMachine(hStateMachine);
}
//---------------------------------------------------------------------------

#endif
