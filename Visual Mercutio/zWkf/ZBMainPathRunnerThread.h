#if !defined(AFX_ZBMainPathRunnerThread_H__E8B82D08_88FE_4C53_991E_88017EFE6A65__INCLUDED_)
#define AFX_ZBMainPathRunnerThread_H__E8B82D08_88FE_4C53_991E_88017EFE6A65__INCLUDED_

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
class ZBPathMachine;
class ZBStateMachineCollection;
class ZILog;



///////////////////////////////////////////////////////////////////////////
// Collection definitions




/////////////////////////////////////////////////////////////////////////////
// ZBMainPathRunnerThread thread

class ZBMainPathRunnerThread : public PSS_ThinThread
{
protected:
    ZBMainPathRunnerThread();    // protected constructor used by dynamic creation     

public:
    ZBMainPathRunnerThread(ZBPathMachine* pAutomationMachine, int ElapseTime = -1, ZILog* pLog = NULL);
    virtual ~ZBMainPathRunnerThread();

    BOOL StartThread();
    void SetLog( ZILog* pLog )
    {
        m_pLog = pLog;
    };

protected: 

    /////////////////////////////////////////////////////////////////////////////
    // CThinThread operations

    // override to do startup
    virtual void StartWork();
    // override to do work
    virtual void DoWork();  
    // override to do shutdown
    virtual void EndWork(); 

private:
    ZBPathMachine*                m_pPathMachine;

    int                            m_ElapseTime;
    ZBStateMachineHandleSet        m_MachineHandleSet;

    // Logging variables
    ZILog* m_pLog;
    // Loop counter
    int m_LoopCounter;
    int m_WaitingCounter;
    int m_IsPausedCounter;


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZBMainPathRunnerThread_H__E8B82D08_88FE_4C53_991E_88017EFE6A65__INCLUDED_)
