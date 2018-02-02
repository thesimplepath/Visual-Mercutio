// ZBMainPathRunnerThread.cpp : implementation file
//

#include "stdafx.h"
#include "ZBMainPathRunnerThread.h"

#include "ZBPathMachine.h"
#include "ZBStateMachine.h"
#include "ZBStateMachineCollection.h"
#include "zModel\ProcGraphModelMdl.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

// Include files for log
#include "zBaseLib\ZILog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// ZBMainPathRunnerThread


ZBMainPathRunnerThread::ZBMainPathRunnerThread()
: m_pPathMachine(NULL), 
  m_ElapseTime(-1),
  m_pLog(NULL)
{
}

ZBMainPathRunnerThread::ZBMainPathRunnerThread(ZBPathMachine* pAutomationMachine, 
														   int ElapseTime /*= -1*/, 
														   ZILog* pLog /*= NULL*/ )
: m_pPathMachine(pAutomationMachine), 
  m_ElapseTime(ElapseTime),
  m_pLog(pLog)
{
}

ZBMainPathRunnerThread::~ZBMainPathRunnerThread()
{
}

BOOL ZBMainPathRunnerThread::StartThread()
{
	// Create the thread only if the context has been correctly assigned
	if (!m_pPathMachine || !m_pPathMachine->GetModel())
		return FALSE;
	// Comment the next following two line for having a multi-threaded operation
	Start( (void*)this );
	return TRUE;
/*
	return CreateThread( 0, // dwCreateFlags
						 0, // nStackSize
					     NULL, // lpSecurityAttrs
					     m_ElapseTime); // nMilliSecs
*/
}

void ZBMainPathRunnerThread::StartWork()
{
	ASSERT(m_pPathMachine && m_pPathMachine->GetModel());

	// First, delete all state machines
	m_pPathMachine->DeleteAllStateMachines();
	m_pPathMachine->DeleteAllFinishedStateMachines();

	if (!m_pPathMachine->GetSymbol())
		return;
	// Create a model state machine for each start symbol
	StateMachineHandle hStateMachine = 
		m_pPathMachine->GetStateMachineCollection().CreateNewStateMachine( m_pPathMachine->GetSymbol(), // The start symbol
																		   NULL );	 // No link before
	if (hStateMachine == -1)
	{
		// Log error
		return;
	}
	m_MachineHandleSet.Add( hStateMachine );

	// Call the derived method
	m_pPathMachine->OnStart( m_pLog );
	// Initialize internal variabes
	m_LoopCounter = 0;
	m_WaitingCounter = 0;
	m_IsPausedCounter = 0;
}


void ZBMainPathRunnerThread::DoWork()
{
	ZBStateMachineCollection Collection;
	m_pPathMachine->MergeAllStateObjects( Collection );

	if (Collection.GetStateMachineCount() == 0)
	{
		// Now it is finished
		Stop();
		return;
	}

	++m_LoopCounter;
	if (m_pPathMachine->GetMaximumLoop() != -1 &&
		m_LoopCounter > m_pPathMachine->GetMaximumLoop())
	{
		// Stop the worker thread
		Stop();
		// Call the virtual function for advise
		m_pPathMachine->OnReachMaximumLoopCounter(m_pLog);
		return;
	}
	// For each state machine,
	// do the work
	ZBStateMachineIterator i(&Collection.GetStateMachineSetConst());
	for (ZBStateMachine* pStateMachine = i.GetFirst(); pStateMachine; pStateMachine = i.GetNext())
	{
		// Call the call-back function
		if (!m_pPathMachine->OnBeforeRequestMoveForward( pStateMachine->GetCurrentStateObject(), 
															   pStateMachine, 
															   m_pLog ))
			return;
		
		ZBSymbolSet SymbolSet;
		ZBStateLinksSet StateLinkSet;
		switch (m_pPathMachine->RequestMoveForward( pStateMachine->GetCurrentStateObject(), 
														  pStateMachine, 
														  SymbolSet,
														  StateLinkSet, 
														  m_pLog ))
		{
			case ZBPathMachine::PS_IsWaitingForLinks:
			{
				// Call the call-back for waiting for other links object
				m_pPathMachine->OnObjectIsWaitingForOtherLinks( pStateMachine->GetCurrentStateObject(), 
																	  pStateMachine, 
																	  m_pLog );
				// Increment the waiting counter
				++m_WaitingCounter;
				if (m_pPathMachine->GetMaximumWaitingForOtherLinks() != -1 &&
					m_WaitingCounter > m_pPathMachine->GetMaximumWaitingForOtherLinks())
				{
					// Stop the worker thread
					Stop();
					// Call the virtual function for advise
					m_pPathMachine->OnReachMaximumWaitingForOtherLinksCounter(m_pLog);
					return;
				}
				break;
			}
			case ZBPathMachine::PS_IsPaused:
			{
				// Call the call-back for in paused object
				m_pPathMachine->OnObjectIsPaused( pStateMachine->GetCurrentStateObject(), 
													    pStateMachine, 
														m_pLog );
				// Increment the pause counter
				++m_IsPausedCounter;
				if (m_pPathMachine->GetMaximumPaused() != -1 &&
					m_IsPausedCounter > m_pPathMachine->GetMaximumPaused())
				{
					// Stop the worker thread
					Stop();
					// Call the virtual function for advise
					m_pPathMachine->OnReachMaximumInPauseCounter(m_pLog);
					return;
				}
				break;
			}
			case ZBPathMachine::PS_IsFinished:
			{
				// Call the call-back function
				if (!m_pPathMachine->OnBeforeMoveForward( pStateMachine->GetCurrentStateObject(), 
														  pStateMachine,
														  m_pLog ))
					return;
				// Call the call-back for finished object
				m_pPathMachine->OnObjectIsFinished( pStateMachine->GetCurrentStateObject(), 
													pStateMachine, 
													m_pLog );
				// Does nothing 
				if (!m_pPathMachine->MoveFinishedStateMachine( pStateMachine ))
				{
					// Stop the worker thread
					Stop();
					return;
				}
				break;
			}
			case ZBPathMachine::PS_CanMoveForward:
			{
				// Call the call-back function
				if (!m_pPathMachine->OnBeforeMoveForward( pStateMachine->GetCurrentStateObject(), 
														  pStateMachine,
														  m_pLog ))
					return;
				// Now, push the new symbol set and the associated state links 
				if (SymbolSet.GetSize() == 1)
				{
					// No more demultiplication, just push the new symbol on the stack

					// First, locate the original state machine 
					// and merge them if necessary
					ZBStateMachine* pOriginalStateMachine = 
										m_pPathMachine->MergeSourceStateMachines( pStateMachine );
					// Call the call-back function
					if (!m_pPathMachine->OnAfterMoveForward( pOriginalStateMachine->GetCurrentStateObject(), 
															 pOriginalStateMachine, 
															 m_pLog ))
						return;

					// Then, push the symbol and the state link
					if (pOriginalStateMachine)
						pOriginalStateMachine->PushSymbol( SymbolSet.GetAt(0),
														   StateLinkSet.GetAt(0) );

					// Call the call-back function
					if (!m_pPathMachine->OnNextSymbolAfterMoveForward( pOriginalStateMachine->GetCurrentStateObject(), 
																	   pOriginalStateMachine,
																	   m_pLog ))
						return;

				}
				else
				if (SymbolSet.GetSize() > 1)
				{
					// Now for each symbol, create a new state machine

					// First, locate the original state machine 
					// and merge them if necessary
					ZBStateMachine* pOriginalStateMachine = 
										m_pPathMachine->MergeSourceStateMachines( pStateMachine );
					// Then, push the symbol and the state link
					if (pOriginalStateMachine)
					{
						// For each symbol, create a new state machine.
						// Except for the first one where we continue to 
						// use the existing.

						// Retreive the current state object of the current state machine
						ZBStateObject* pInitialStateObject = pOriginalStateMachine->GetCurrentStateObject();

						// Call the call-back function
						if (!m_pPathMachine->OnAfterMoveForward( pOriginalStateMachine->GetCurrentStateObject(), 
																 pOriginalStateMachine,
																 m_pLog ))
							return;

						// Then, push the first symbol and the first state link
						// on the existing state machine
						pOriginalStateMachine->PushSymbol( SymbolSet.GetAt(0),
														   StateLinkSet.GetAt(0) );
						// Call the call-back function
						if (!m_pPathMachine->OnNextSymbolAfterMoveForward( pOriginalStateMachine->GetCurrentStateObject(), 
																		   pOriginalStateMachine,
																		   m_pLog ))
							return;

						// For all others, create a new state machine.
						// The starter point is a clone of the current state object
						for	(int i = 1; i < SymbolSet.GetSize(); ++i)
						{
							// Create a model state machine for each state object
							StateMachineHandle hStateMachine = 
								m_pPathMachine->GetStateMachineCollection().CreateNewStateMachine( pInitialStateObject->Clone() );	 
							if (hStateMachine == -1)
							{
								// Log error
								// Stop the worker thread
								Stop();
								return;
							}
							m_MachineHandleSet.Add( hStateMachine );
							// And now push the state link and the symbol
							// to the newly created state machine
							ZBStateMachine* pNewStateMachine = m_pPathMachine->GetStateMachine( hStateMachine );
							if (!pNewStateMachine)
							{
								// Log error
								// Stop the worker thread
								Stop();
								return;
							}
							pNewStateMachine->PushSymbol( SymbolSet.GetAt(i), StateLinkSet.GetAt(i) );
							// Call the call-back function
							if (!m_pPathMachine->OnNextSymbolAfterMoveForward( pNewStateMachine->GetCurrentStateObject(), 
																			   pNewStateMachine,
																			   m_pLog ))
								return;
						}
					}

				}

				break;
			}
			case ZBPathMachine::PS_Error:
			default:
				// Error and Unknown state generates the end of the work
			{
				// Call the call-back for error on object
				m_pPathMachine->OnObjectError( pStateMachine->GetCurrentStateObject(), 
											   pStateMachine, 
											   m_pLog );
				// Stop the worker thread
				Stop();
				return;
			}

		}

	} // End state machine loop
}



void ZBMainPathRunnerThread::EndWork()
{
	// Call the derived method
	m_pPathMachine->OnStop( m_pLog );
}





