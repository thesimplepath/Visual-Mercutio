/****************************************************************************
 * ==> PSS_SesterceRecalculationAutomate -----------------------------------*
 ****************************************************************************
 * Description : Provides the Sesterce recalculation automate               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SesterceRecalculationAutomateH
#define PSS_SesterceRecalculationAutomateH

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
* Sesterce recalculation automate
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SesterceRecalculationAutomate : public PSS_AutomateBP
{
    public:
        /**
        * Constructor
        *@param pModel - the model
        *@param pLog - the log to use to show messages
        */
        PSS_SesterceRecalculationAutomate(PSS_ProcessGraphModelMdl* pModel = NULL, PSS_Log* pLog = NULL);

        virtual ~PSS_SesterceRecalculationAutomate();

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
        virtual bool OnObjectIsWaitingForOtherLinks(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, PSS_Log* pLog);

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

    private:
        /**
        * Calculates the sum of output deliverables
        *@param leavingEdges - the leaving edges
        *@param leavingLinkCount - the leaving link count
        *@param pProcedure - the procedure
        *@param pLocalProcedureBefore - the local procedure before the symbol
        *@return the sum of output deliverables
        */
        double CalculateSumOfOutDeliverables(CODEdgeArray&          leavingEdges,
                                             std::size_t            leavingLinkCount,
                                             PSS_ProcedureSymbolBP* pProcedure,
                                             PSS_ProcedureSymbolBP* pLocalProcedureBefore);
};

#endif
