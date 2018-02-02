#if !defined(AFX_ZBMAINAUTOMATIONRUNNERTHREAD_H__E8B82D08_88FE_4C53_991E_88017EFE6A65__INCLUDED_)
#define AFX_ZBMAINAUTOMATIONRUNNERTHREAD_H__E8B82D08_88FE_4C53_991E_88017EFE6A65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZBMainAutomationRunnerThread.h : header file
//



#include "CThinThread.h" 
#include "AutomationCollections.h"


/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBSymbol;
class ZBLinkSymbol;
class ZDProcessGraphModelMdl;
class ZBAutomationMachine;
class ZBStateMachineCollection;
class ZILog;



///////////////////////////////////////////////////////////////////////////
// Collection definitions




/////////////////////////////////////////////////////////////////////////////
// ZBMainAutomationRunnerThread thread

class ZBMainAutomationRunnerThread : public CThinThread
{
protected:
	ZBMainAutomationRunnerThread();    // protected constructor used by dynamic creation     

public:
	ZBMainAutomationRunnerThread(ZBAutomationMachine* pAutomationMachine, int ElapseTime = -1, ZILog* pLog = NULL);
	virtual ~ZBMainAutomationRunnerThread();

	BOOL StartThread();
	void SetLog( ZILog* pLog )
	{
		m_pLog = pLog;
	};

	// Counter functions
	int GetLoopCounter() const
	{
		return m_LoopCounter;
	};
	void ResetLoopCounter()
	{
		m_LoopCounter = 0;
	};

	int GetWaitingCounter() const
	{
		return m_WaitingCounter;
	};
	void ResetWaitingCounter()
	{
		m_WaitingCounter = 0;
	};

	int GetIsPausedCounter() const
	{
		return m_IsPausedCounter;
	};
	void ResetIsPausedCounter()
	{
		m_IsPausedCounter = 0;
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
	ZBAutomationMachine*		m_pAutomationMachine;

	int							m_ElapseTime;
	ZBStateMachineHandleSet		m_MachineHandleSet;

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

#endif // !defined(AFX_ZBMAINAUTOMATIONRUNNERTHREAD_H__E8B82D08_88FE_4C53_991E_88017EFE6A65__INCLUDED_)
