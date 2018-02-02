// ThinThread.cpp : implementation file 

// Copyright (C) 1997 by The Windward Group, All Rights Reserved 

#include "stdafx.h" 

#include "CThinThread.h" 

#include <process.h> /* _beginthread, _endthread */ 

///////////////////////////////////////////////////////////////////////////// 

// ThinThread 

CThinThread::CThinThread() 
: m_b2ndThread(FALSE), m_bEndThread(FALSE), m_nCycleTime(0), m_ThreadID(0) 
{ 

	// Create a signaled, manual-reset event to synchronize destruction 
	m_pExitEvent = new CEvent(TRUE, TRUE); 
	ASSERT(m_pExitEvent); 

	// Create a non-signaled, auto-reset event to wait on for work cycle 
	m_pWorkEvent = new CEvent(); 
	ASSERT(m_pWorkEvent); 

} 

BOOL CThinThread::CreateThread(DWORD dwCreateFlags, 
							   UINT nStackSize, 
							   LPSECURITY_ATTRIBUTES lpSecurityAttrs, 
							   UINT nMilliSecs) 

{ 

	m_b2ndThread = TRUE; 
	m_bEndThread = FALSE; 
	m_nCycleTime = nMilliSecs;
	

	// exit event is reset until we're done 
	m_pExitEvent->ResetEvent(); 

	// Start second thread 
//	unsigned usThreadAddr; 
//	m_hThread2 = reinterpret_cast<HANDLE> 
//						(_beginthreadex(lpSecurityAttrs, nStackSize, Start, 
//						 this, 1, &usThreadAddr)); 
//	return reinterpret_cast<unsigned long> (m_hThread2); 

	m_hThread2 = ::CreateThread(lpSecurityAttrs,     // Security attributes. 
								(DWORD)nStackSize,                 // stack size. 
								(LPTHREAD_START_ROUTINE)Start,		// Thread procedure. 
								(LPVOID)this,						// Parameter to pass. 
								(DWORD)dwCreateFlags,              // creation flags. 
								(LPDWORD)&m_ThreadID); 
	return (m_hThread2 != NULL) ? TRUE : FALSE; 
} 

CThinThread::~CThinThread() 
{ 
	delete m_pWorkEvent; 
	m_pWorkEvent = NULL;
	delete m_pExitEvent; 
	m_pExitEvent = NULL;
	TRACE("End CThinThread\n");
} 

void CThinThread::KillThread2() 
{ 

	// Start up the other thread so it can complete. 
	// When it does, it will set the exit event and the object can 
	// be destructed. 
	m_bEndThread = TRUE; 

	m_pWorkEvent->SetEvent(); 

	CSingleLock csl(m_pExitEvent); 

	csl.Lock(); // wait for 2nd thread to finish 
	csl.Unlock(); 

	TRACE("KillThread2 CThinThread\n");

} 

int CThinThread::Run() 
{ 

	CSingleLock csl(m_pWorkEvent); // synch on the work event 

	StartWork(); // do derived startup 
	TRACE("StartWork CThinThread\n");

	while (!m_bEndThread) // loop until we're done 
	{ 

		csl.Lock(m_nCycleTime); // wait for event or timeout 

		csl.Unlock(); 

		if (!m_bEndThread) 
		{
			DoWork(); // then do derived work 
			TRACE("DoWork CThinThread\n");
		}

	} 

	EndWork(); // do derived shutdown 
	TRACE("EndWork CThinThread\n");

	m_pExitEvent->SetEvent(); // set not waiting signal 

	m_b2ndThread = FALSE; 

//	CloseHandle(m_hThread2); 

//	_endthreadex(0); 

	return 0; 

} 

unsigned int __stdcall CThinThread::Start(void* pv) 
{ 
//	CThinThread* pMT = static_cast<CThinThread*> (pv); 

	TRACE("static Start CThinThread\n");
	return static_cast<CThinThread*>(pv)->Run(); 
} 

