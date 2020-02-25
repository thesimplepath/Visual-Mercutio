/****************************************************************************
 * ==> PSS_DurationRecalculationAutomate -----------------------------------*
 ****************************************************************************
 * Description : Provides the duration recalculation automate               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DurationRecalculationAutomateH
#define PSS_DurationRecalculationAutomateH

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
#include "PSS_AutomateBP.h"

// old class name mapping
#ifndef PSS_ProcedureSymbolBP
    #define PSS_ProcedureSymbolBP ZBBPProcedureSymbol
#endif

// forward class declaration
class PSS_ProcedureSymbolBP;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Duration recalculation automate
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_DurationRecalculationAutomate : public PSS_AutomateBP
{
    public:
        /**
        * Constructor
        *@param pSymbol - the symbol
        *@param pModel - the model
        *@param pLog - the log to use to show messages
        */
        PSS_DurationRecalculationAutomate(PSS_Symbol*               pSymbol,
                                          PSS_ProcessGraphModelMdl* pModel = NULL,
                                          PSS_Log*                  pLog   = NULL);

        virtual ~PSS_DurationRecalculationAutomate();

        /**
        * Called when the automation starts
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnStart(PSS_Log* pLog);

        /**
        * Called when the automation stops
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnStop(PSS_Log* pLog);

        /**
        * Called when the automation is paused
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnPause(PSS_Log* pLog);

        /**
        * Called when the automation is resumed
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnResume(PSS_Log* pLog);

        /**
        * Called when the automation finished to perform an object
        *@param pState - the reached state
        *@param pStateMachine - the state machine
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnObjectIsFinished(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called when the automation is paused on an object
        *@param pState - the current state on pause
        *@param pStateMachine - the state machine
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnObjectIsPaused(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called when the object is waiting for other links
        *@param pState - the state
        *@param pStateMachine - the state machine
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnObjectIsWaitingForOtherLinks(PSS_StateObject*  pState,
                                                    PSS_StateMachine* pStateMachine,
                                                    PSS_Log*          pLog);

        /**
        * Called before the automate requests to move forward
        *@param pState - the state
        *@param pStateMachine - the state machine
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnBeforeRequestMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called when the next symbol is reached after the automate moves forward
        *@param pState - the state
        *@param pStateMachine - the state machine
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnNextSymbolAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called before the automate moves forward
        *@param pState - the state
        *@param pStateMachine - the state machine
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnBeforeMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called after the automate moves forward
        *@param pState - the state
        *@param pStateMachine - the state machine
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnAfterMoveForward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called before the automate moves backward
        *@param pState - the state
        *@param pStateMachine - the state machine
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnBeforeMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called after the automate moves backward
        *@param pState - the state
        *@param pStateMachine - the state machine
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnAfterMoveBackward(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called when an object raised an error
        *@param pState - the state
        *@param pStateMachine - the state machine
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnObjectError(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

        /**
        * Called when the maximum loop counter is reached
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnReachMaximumLoopCounter(PSS_Log* pLog);

        /**
        * Called when the maximum in pause counter is reached
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnReachMaximumInPauseCounter(PSS_Log* pLog);

        /**
        * Called when the maximum waiting for other links counter is reached
        *@param pLog - the log to use to show messages
        *@return true on success, otherwise false
        */
        virtual bool OnReachMaximumWaitingForOtherLinksCounter(PSS_Log* pLog);

        /**
        * Increments the pass
        */
        virtual inline void IncrementPass();

    protected:
        /**
        * Gets the pass
        *@return the pass
        */
        virtual inline int GetPass() const;

    private:
        int m_Pass;

        /**
        * Sets the lateral deliverables case duration
        *@param leavingEdges - the leaving edges
        *@param leavingLinkCount - the leaving link count
        *@param pProcedure - the procedure
        *@param pLog - the log to use to show messages
        */
        bool SetCaseDurationOfLateralDeliverables(CODEdgeArray&          leavingEdges,
                                                  std::size_t            leavingLinkCount,
                                                  PSS_ProcedureSymbolBP* pProcedure,
                                                  PSS_Log*               pLog);

        /**
        * Sets the down deliverables case duration
        *@param pState - the state object
        *@param leavingEdges - the leaving edges
        *@param leavingLinkCount - the leaving link count
        *@param pProcedure - the procedure
        *@param pLog - the log to use to show messages
        */
        bool SetCaseDurationOfDownDeliverables(PSS_StateObject*       pState,
                                               CODEdgeArray&          leavingEdges,
                                               std::size_t            leavingLinkCount,
                                               PSS_ProcedureSymbolBP* pProcedure,
                                               PSS_Log*               pLog);

        /**
        * Sets the down deliverables case duration
        *@param pState - the state object
        *@param leavingEdges - the leaving edges
        *@param leavingLinkCount - the leaving link count
        *@param pLog - the log to use to show messages
        */
        bool SetStartSymbolCaseDurationOfDownDeliverables(PSS_StateObject* pState,
                                                          CODEdgeArray&    leavingEdges,
                                                          std::size_t      leavingLinkCount,
                                                          PSS_Log*         pLog);

        /**
        * Sets the procedure case duration
        *@param pState - the state object
        *@param leavingEdges - the leaving edges
        *@param leavingLinkCount - the leaving link count
        *@param pProcedure - the procedure
        *@param pLog - the log to use to show messages
        */
        bool SetCaseDurationOfProcedure(PSS_StateObject*       pState,
                                        CODEdgeArray&          leavingEdges,
                                        std::size_t            leavingLinkCount,
                                        PSS_ProcedureSymbolBP* pProcedure,
                                        PSS_Log*               pLog);
};

//---------------------------------------------------------------------------
// PSS_DurationRecalculationAutomate
//---------------------------------------------------------------------------
void PSS_DurationRecalculationAutomate::IncrementPass()
{
    ++m_Pass;
}
//---------------------------------------------------------------------------
int PSS_DurationRecalculationAutomate::GetPass() const
{
    return m_Pass;
}
//---------------------------------------------------------------------------

#endif
