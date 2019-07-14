// ZBDurationRecalculationAutomate.h: interface for the ZBDurationRecalculationAutomate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBDurationRecalculationAutomate_H__1CC9AE94_368B_41BE_90E1_527CD3EC61F8__INCLUDED_)
#define AFX_ZBDurationRecalculationAutomate_H__1CC9AE94_368B_41BE_90E1_527CD3EC61F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZBBPAutomate.h"

//////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBBPProcedureSymbol;

// JMR-MODIF - Le 4 septembre 2006 - Ajout des décorations unicode _T(), nettoyage du code inutile. (En commentaires)

class ZBDurationRecalculationAutomate : public ZBBPAutomate
{
public:

    ZBDurationRecalculationAutomate( ZBSymbol*                    pSymbol,
                                     ZDProcessGraphModelMdl*    pModel    = NULL,
                                     ZILog*                        pLog    = NULL );

    virtual ~ZBDurationRecalculationAutomate();

    //////////////////////////////////////////////////////////////////////
    // Automation basic call-back
    virtual bool OnStart    ( ZILog* pLog );
    virtual bool OnStop        ( ZILog* pLog );
    virtual bool OnPause    ( ZILog* pLog );
    virtual bool OnResume    ( ZILog* pLog );

    //////////////////////////////////////////////////////////////////////
    // Status call-back
    virtual bool OnObjectIsFinished    (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog );
    virtual bool OnObjectIsPaused    (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog );

    virtual bool OnObjectIsWaitingForOtherLinks(PSS_StateObject*  pState,
                                                PSS_StateMachine* pStateMachine,
                                                ZILog*            pLog);

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
    virtual bool OnObjectError                    (PSS_StateObject* pState, PSS_StateMachine* pStateMachine, ZILog* pLog);
    virtual bool OnReachMaximumLoopCounter        ( ZILog* pLog );
    virtual bool OnReachMaximumInPauseCounter    ( ZILog* pLog );

    virtual bool OnReachMaximumWaitingForOtherLinksCounter( ZILog* pLog );

    void IncrementPass()
    {
        ++m_Pass;
    };

protected:

    int GetPass() const
    {
        return m_Pass;
    };

private:

    bool SetCaseDurationOfLateralDeliverables( CODEdgeArray&        LeavingEdges,
                                               size_t                LeavingLinkCount,
                                               ZBBPProcedureSymbol*    pProcedure,
                                               ZILog*                pLog );

    bool SetCaseDurationOfDownDeliverables(PSS_StateObject*            pState,
                                            CODEdgeArray&            LeavingEdges,
                                            size_t                    LeavingLinkCount,
                                            ZBBPProcedureSymbol*    pProcedure,
                                            ZILog*                    pLog );

    bool SetStartSymbolCaseDurationOfDownDeliverables(PSS_StateObject*    pState,
                                                       CODEdgeArray&    LeavingEdges,
                                                       size_t            LeavingLinkCount,
                                                       ZILog*            pLog );

    bool SetCaseDurationOfProcedure(PSS_StateObject*            pState,
                                     CODEdgeArray&            LeavingEdges,
                                     size_t                    LeavingLinkCount,
                                     ZBBPProcedureSymbol*    pProcedure,
                                     ZILog*                    pLog );

private:

    int m_Pass;
};

#endif
