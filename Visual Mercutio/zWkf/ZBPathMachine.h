// ZBPathMachine.h: interface for the ZBPathMachine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBPathMachine_H__1CC9AE94_368B_41BE_90E1_527CD3EC61F8__INCLUDED_)
#define AFX_ZBPathMachine_H__1CC9AE94_368B_41BE_90E1_527CD3EC61F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZBStateMachineCollection.h"
#include "ZBStateObject.h"
#include "AutomationCollections.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBSymbol;
class ZBLinkSymbol;
class ZDProcessGraphModelMdl;
class ZBMainPathRunnerThread;
class ZILog;



#ifdef _ZWKFEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS



class AFX_EXT_CLASS ZBPathMachine // : public CObject  
{
    friend class ZBMainPathRunnerThread; // generates the automation

public:
	enum PathMoveStatus { PS_Error,
						  PS_IsWaitingForLinks,
						  PS_IsPaused,
						  PS_CanMoveForward,
						  PS_IsFinished };

public:
	ZBPathMachine( ZDProcessGraphModelMdl* pModel = NULL, 
				   ZBSymbol* pSymbol = NULL,
				   ZILog* pLog = NULL, 
				   int MaximumLoop = -1, // Maximum loop counter, default is infinite
				   int MaximumPaused = -1, // Maximum paused counter, default is infinite
				   int MaximumWaitingForOtherLinks = -1); // Maximum waiting for other links counter, default is infinite
	virtual ~ZBPathMachine();

	//////////////////////////////////////////////////////////////////////
	// Initialization operations
	void AssignModel( ZDProcessGraphModelMdl* pModel )
	{
		m_pModel = pModel;
		m_StateMachineCollection.AssignModel( pModel );
	};
	// Return the model used by the automation machine
	ZDProcessGraphModelMdl* GetModel()
	{
		return m_pModel;
	};
	ZBSymbol* GetSymbol()
	{
		return m_pSymbol;
	};

	// Returns the collection
    ZBStateMachineCollection& GetStateMachineCollection()
	{
		return m_StateMachineCollection;
	};

	// Return the counter of state machines
	size_t	GetStateMachineCount() const 
	{
		return m_StateMachineCollection.GetStateMachineCount();
	};
	// Add a new state machine
	int AddStateMachine( ZBStateMachine* pStateMachine )
	{
		return m_StateMachineCollection.AddStateMachine( pStateMachine );
	};
	// Get the machine set to use with the iterator
	ZBStateMachineSet& GetStateMachineSet()
	{
		return m_StateMachineCollection.GetStateMachineSet();
	};
	const ZBStateMachineSet& GetStateMachineSetConst() const
	{
		return m_StateMachineCollection.GetStateMachineSetConst();
	};

	ZBStateMachine* GetStateMachine( StateMachineHandle hStateMachine )
	{
		return m_StateMachineCollection.GetStateMachine( hStateMachine );
	};

	//////////////////////////////////////////////////////////////////////
	// Maximum loop operations
	int GetMaximumLoop() const;
	void SetMaximumLoop( int value );
	int GetMaximumPaused() const;
	void SetMaximumPaused( int value );
	int GetMaximumWaitingForOtherLinks() const;
	void SetMaximumWaitingForOtherLinks( int value );

	//////////////////////////////////////////////////////////////////////
	// File operations
	bool LoadStateFromFile( const CString Filename );
	bool SaveStateToFile( const CString Filename );

	//////////////////////////////////////////////////////////////////////
	// Automation operations
	bool Start( int ElapseTime = -1 );
	bool Stop();
	bool Pause();
	bool Resume();


	//////////////////////////////////////////////////////////////////////
	// Workflow operations

	// This operation must fill sets of symbol and link corresponding to the 
	// the symbol and link pointer and the direction 
	// attributes if there is one.
	// Return the move status
	virtual ZBPathMachine::PathMoveStatus 
					RequestMoveForward( ZBStateObject* pState, 
										ZBStateMachine* pStateMachine, 
										ZBSymbolSet& SymbolSet,
										ZBStateLinksSet& StateLinkSet, 
										ZILog* pLog )
	{
		// Does nothing in the base class
		// Must be implemented in the derived class
		return PS_Error;
	};


	//////////////////////////////////////////////////////////////////////
	// Call back operations
	virtual bool OnStart(ZILog* pLog)
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnStop(ZILog* pLog)
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnPause(ZILog* pLog)
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnResume(ZILog* pLog)
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};

	//////////////////////////////////////////////////////////////////////
	// Status call-back
	virtual bool OnObjectIsFinished( ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog )
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnObjectIsPaused( ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog )
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnObjectIsWaitingForOtherLinks( ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog )
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};

	//////////////////////////////////////////////////////////////////////
	// Navigation call-back
	virtual bool OnBeforeRequestMoveForward( ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog )
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnNextSymbolAfterMoveForward( ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog )
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnBeforeMoveForward( ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog )
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnAfterMoveForward( ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog )
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnBeforeMoveBackward( ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog )
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnAfterMoveBackward( ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog )
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};

	//////////////////////////////////////////////////////////////////////
	// Exception call-back
	virtual bool OnObjectError(ZBStateObject* pState, ZBStateMachine* pStateMachine, ZILog* pLog)
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnReachMaximumLoopCounter(ZILog* pLog)
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnReachMaximumWaitingForOtherLinksCounter(ZILog* pLog)
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};
	virtual bool OnReachMaximumInPauseCounter(ZILog* pLog)
	{
		// Does nothing in the base class
		// Might be implemented in the derived class
		return true;
	};

	//////////////////////////////////////////////////////////////////////
	// Logging functions
	void StartLogging()
	{
		m_IsLogging = true;
	};
	void StopLogging()
	{
		m_IsLogging = false;
	};
	bool IsLogging() const
	{
		return m_IsLogging;
	};
	// Returns the ZILog pointer on the log used for checking the symbol
	ZILog* GetLog()
	{
		return m_pLog;
	};


	//////////////////////////////////////////////////////////////////////
	// Error and Warning counter
	size_t	GetErrorCounter() const
	{
		return m_ErrorCounter;
	};
	void SetErrorCounter( size_t value )
	{
		m_ErrorCounter = value;
	};
	void IncrementErrorCounter()
	{
		++m_ErrorCounter;
	};
	void ResetErrorCounter()
	{
		m_ErrorCounter = 0;
	};

	size_t	GetWarningCounter() const
	{
		return m_WarningCounter;
	};
	void SetWarningCounter( size_t value )
	{
		m_WarningCounter = value;
	};
	void IncrementWarningCounter()
	{
		++m_WarningCounter;
	};
	void ResetWarningCounter()
	{
		m_WarningCounter = 0;
	};

protected:
	//////////////////////////////////////////////////////////////////////
	// Helper functions
	size_t CopyNodeArrayToSymbolSet( CODNodeArray& Nodes, ZBSymbolSet& SymbolSet );
	size_t CopyEdgeArrayToStateLinksSet( CODEdgeArray& Edges, ZBStateLink::LinkDirection Direction, ZBStateLinksSet& StateLinkSet );

	void DeleteAllStateMachines()
	{
		m_StateMachineCollection.DeleteAllStateMachines();
	};
	void DeleteAllFinishedStateMachines()
	{
		m_FinishedStateMachineCollection.DeleteAllStateMachines();
	};

private:
	bool MergeAllStateObjects( ZBStateMachineCollection& Collection );
	bool MergeStateMachine( size_t i, size_t j, ZBStateMachineCollection& Collection, bool DeleteDestination = false );
	ZBStateMachine* MergeSourceStateMachines( ZBStateMachine* pStateMachineToMerge );
	ZBStateMachine* FindOriginalStateMachine( ZBStateMachine* pStateMachineToLocate );
	bool MoveFinishedStateMachine( ZBStateMachine* pFinishedStateMachine );


	// Returns the collection
    ZBStateMachineCollection& GetFinishedStateMachineCollection()
	{
		return m_FinishedStateMachineCollection;
	};

	// Return the counter of state machines
	size_t	GetFinishedStateMachineCount() const 
	{
		return m_FinishedStateMachineCollection.GetStateMachineCount();
	};
	// Add a new state machine
	int AddFinishedStateMachine( ZBStateMachine* pStateMachine )
	{
		return m_FinishedStateMachineCollection.AddStateMachine( pStateMachine );
	};
	// Get the machine set to use with the iterator
	ZBStateMachineSet& GetFinishedStateMachineSet()
	{
		return m_FinishedStateMachineCollection.GetStateMachineSet();
	};
	const ZBStateMachineSet& GetFinishedStateMachineSetConst() const
	{
		return m_FinishedStateMachineCollection.GetStateMachineSetConst();
	};

	ZBStateMachine* GetFinishedStateMachine( StateMachineHandle hStateMachine )
	{
		return m_FinishedStateMachineCollection.GetStateMachine( hStateMachine );
	};

protected:
	// We own the state machine, because the main thread is only a worker
	// dealing with the state class.
    ZBStateMachineCollection	m_StateMachineCollection;
    ZBStateMachineCollection	m_FinishedStateMachineCollection;
	ZDProcessGraphModelMdl*		m_pModel;

private:
	ZBMainPathRunnerThread* m_pMainThread;
	ZBSymbol*				m_pSymbol;
	// Logging variables
	bool m_IsLogging;
	ZILog* m_pLog;

	int m_MaximumLoop;
	int m_MaximumPaused;
	int m_MaximumWaitingForOtherLinks;

	size_t	m_ErrorCounter;
	size_t	m_WarningCounter;

};


inline int ZBPathMachine::GetMaximumLoop() const 
{
	return m_MaximumLoop;
}
inline void ZBPathMachine::SetMaximumLoop( int value )
{
	m_MaximumLoop = value;
}


inline int ZBPathMachine::GetMaximumPaused() const 
{
	return m_MaximumPaused;
}
inline void ZBPathMachine::SetMaximumPaused( int value )
{
	m_MaximumPaused = value;
}


inline int ZBPathMachine::GetMaximumWaitingForOtherLinks() const 
{
	return m_MaximumWaitingForOtherLinks;
}
inline void ZBPathMachine::SetMaximumWaitingForOtherLinks( int value )
{
	m_MaximumWaitingForOtherLinks = value;
}

#endif // !defined(AFX_ZBPathMachine_H__1CC9AE94_368B_41BE_90E1_527CD3EC61F8__INCLUDED_)


