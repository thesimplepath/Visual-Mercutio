#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#if defined(__cplusplus)
extern "C" {
#endif

HANDLE 
PoolCreateThread(
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    DWORD dwStackSize,
    LPTHREAD_START_ROUTINE lpStartAddress,
    LPVOID lpParameter,
    DWORD dwCreationFlags,
    LPDWORD lpThreadId
    );

BOOL 
PoolTerminateThread(
    HANDLE hThread,
    DWORD dwExitCode
    );

#if defined(__cplusplus)
}
#endif

#ifndef INTERFACE_ONLY

#define MAX_THREAD (MAX_CONN+5)
///////////////////////////////////////////////////////////////////////////////////
//class CHttpThread

class CHttpThread {

public:
	CHttpThread();
	virtual ~CHttpThread();

public:
	HANDLE Start( LPTHREAD_START_ROUTINE StartProc, LPVOID param, DWORD dwCreationFlags);
	BOOL Stop();
	BOOL Terminate( DWORD dwExitCode);
	int ThreadRoutine();
	HANDLE GetHandle() { return m_hThread;}
protected:
	HANDLE m_hThread;
	DWORD m_ThreadId;

public:
	void SetAbortEvent();
	void SetInUseFlag() { m_InUse = TRUE;}
	BOOL GetInUseFlag() { return m_InUse;}
protected:
	HANDLE m_AbortEvent;
	HANDLE m_ContinueEvent;
	BOOL m_AbortSet;
	LPVOID m_Param;
	LPTHREAD_START_ROUTINE m_StartProc;
	BOOL m_InUse;
};

class CHttpSection {
public:
	CHttpSection() { InitializeCriticalSection (&m_Sec); }
	~CHttpSection() { DeleteCriticalSection (&m_Sec); }
	void Enter() { EnterCriticalSection(&m_Sec); }		  
	void Leave() { LeaveCriticalSection(&m_Sec); }		  
protected:
	CRITICAL_SECTION m_Sec;           
};

class CHttpThreadPool {
public:
	CHttpThreadPool();
	virtual ~CHttpThreadPool();

public:
	HANDLE Start( LPTHREAD_START_ROUTINE StartProc, LPVOID param, DWORD dwCreationFlags);
	DWORD StopAll();
	BOOL Terminate( HANDLE hThread, DWORD dwExitCode);
	CHttpThread m_Pool[MAX_THREAD];
	CHttpSection m_Section;
};

#endif

#endif