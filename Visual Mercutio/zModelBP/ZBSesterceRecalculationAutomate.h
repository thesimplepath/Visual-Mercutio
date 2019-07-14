// ZBSesterceRecalculationAutomate.h: interface for the ZBSesterceRecalculationAutomate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSesterceRecalculationAutomate_H__1CC9AE94_368B_41BE_90E1_527CD3EC61F8__INCLUDED_)
#define AFX_ZBSesterceRecalculationAutomate_H__1CC9AE94_368B_41BE_90E1_527CD3EC61F8__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "ZBBPAutomate.h"

// forward class declaration
class ZBBPProcedureSymbol;

class ZBSesterceRecalculationAutomate : public ZBBPAutomate
{
public:

    ZBSesterceRecalculationAutomate( ZDProcessGraphModelMdl* pModel = NULL, ZILog* pLog = NULL );
    virtual ~ZBSesterceRecalculationAutomate();

    //////////////////////////////////////////////////////////////////////
    // Automation basic call-back
    virtual bool OnStart    ( ZILog* pLog );
    virtual bool OnStop        ( ZILog* pLog );
    virtual bool OnPause    ( ZILog* pLog );
    virtual bool OnResume    ( ZILog* pLog );

    //////////////////////////////////////////////////////////////////////
    // Status call-back
    virtual bool OnObjectIsFinished                (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);
    virtual bool OnObjectIsPaused                (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);
    virtual bool OnObjectIsWaitingForOtherLinks    (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

    //////////////////////////////////////////////////////////////////////
    // Navigation call-back
    virtual bool OnBeforeRequestMoveForward        (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);
    virtual bool OnNextSymbolAfterMoveForward    (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);
    virtual bool OnBeforeMoveForward            (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);
    virtual bool OnAfterMoveForward                (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);
    virtual bool OnBeforeMoveBackward            (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);
    virtual bool OnAfterMoveBackward            (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

    //////////////////////////////////////////////////////////////////////
    // Exception call-back
    virtual bool OnReachMaximumLoopCounter                    ( ZILog* pLog );
    virtual bool OnReachMaximumWaitingForOtherLinksCounter    ( ZILog* pLog );
    virtual bool OnReachMaximumInPauseCounter                ( ZILog* pLog );
    virtual bool OnObjectError(PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);

private:

    double CalculateSumOfOutDeliverables( CODEdgeArray&            LeavingEdges,
                                          size_t                LeavingLinkCount,
                                          ZBBPProcedureSymbol*    pProcedure,
                                          ZBBPProcedureSymbol*    pLocalProcedureBefore );
};

#endif // !defined(AFX_ZBSesterceRecalculationAutomate_H__1CC9AE94_368B_41BE_90E1_527CD3EC61F8__INCLUDED_)