// Source file: UserQueueManager.cpp

#include <StdAfx.h>

#include "UserQueueManager.h"
#include "zBaseLib\ZBTokenizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Class ZBUserQueueManager 


ZBUserQueueManager::ZBUserQueueManager()
{
}

ZBUserQueueManager::~ZBUserQueueManager()
{
}

BOOL ZBUserQueueManager::Create( const CString Directory )
{
	m_Directory = Directory;
	
	// Make the queue directory lower case.
	m_Directory.MakeLower();

	if (!m_UserDirectoryManager.SetDirectory( Directory ))
		return FALSE;
	return TRUE;
}

ZBEventActivity* ZBUserQueueManager::DispatchToUserQueue( const CString Filename )
{
	ZBEventActivity*	pEventActivity = (ZBEventActivity*)m_EventActivityFile.ImportActivityFromFile( Filename );
	if (!pEventActivity)
		return NULL;
	TRACE1("DISPATCH TO USER QUEUE IN WITH FILENAME = %s\n", (const char*)Filename);

	// Check the directory structure
	// of senders and receivers
	if (!CheckDirectory( *pEventActivity ))
	{
		delete pEventActivity;
		return NULL;
	}
	if (pEventActivity->GetActivityEventType() == LogActivityEvent)
	{
		// In case of log, do nothing
		return pEventActivity;
	}
	if (pEventActivity->GetActivityEventType() == DeleteToDoEvent)
	{
		ProceedDeleteMessage( *pEventActivity );
		return pEventActivity;
	}
	// Create place the new event to the receiver queue
	ForwardToUserQueue( *pEventActivity );
	if (pEventActivity->GetActivityEventType() == ToDoActivity)
	{
		// Remove the old event if exists, from the sender queue
		RemoveAssociatedEventFromUserQueue( *pEventActivity );
	}
	return pEventActivity;
}


BOOL	ZBUserQueueManager::CheckDirectory( ZBEventActivity& EventActivity )
{
	// For multi-user mode, run through all senders
	ZBTokenizer	Tokenizer( ';' );
	CString	Token = Tokenizer.GetFirstToken( EventActivity.GetSender() );
	while (!Token.IsEmpty())
	{
		// Dispatch to the first
		if (!m_UserDirectoryManager.UserExist( Token ))
			m_UserDirectoryManager.CreateUser( Token );
		Token = Tokenizer.GetNextToken();
	}

	// For multi-user mode, run through all receivers
	Token = Tokenizer.GetFirstToken( EventActivity.GetReceiver() );
	while (!Token.IsEmpty())
	{
		// Dispatch to the first
		if (!m_UserDirectoryManager.UserExist( Token ))
			m_UserDirectoryManager.CreateUser( Token );
		Token = Tokenizer.GetNextToken();
	}
	return TRUE;
}

BOOL	ZBUserQueueManager::ForwardToUserQueue( ZBEventActivity& EventActivity )
{
	// For multi-user mode, run through all receivers
	ZBTokenizer	Tokenizer( ';' );
	CString	Token = Tokenizer.GetFirstToken( EventActivity.GetReceiver() );
	while (!Token.IsEmpty())
	{
		// Dispatch to the 
		CString	Filename = BuildUserActivityEventFilename( EventActivity.GetFilename() + EventActivity.GetFileExtension(), Token );
		m_EventActivityFile.ExportActivityToFile( Filename, &EventActivity );
		TRACE("FORWARDED TO USER QUEUE\n");
		Token = Tokenizer.GetNextToken();
	}
	return TRUE;
}

BOOL	ZBUserQueueManager::RemoveAssociatedEventFromUserQueue( ZBEventActivity& EventActivity )
{
	ZBEventActivity*	pEventActivity = NULL;
	// For multi-user mode, run through all senders
	ZBTokenizer	Tokenizer( ';' );
	CString	Token = Tokenizer.GetFirstToken( EventActivity.GetSender() );
	while (!Token.IsEmpty())
	{
		CString	Filename = BuildUserActivityEventFilename( EventActivity.GetFilename() + EventActivity.GetFileExtension(ToDoActivity), Token );
		// Import file first
		pEventActivity = (ZBEventActivity*)m_EventActivityFile.ImportActivityFromFile( Filename );
		// If it is a todo activity, therefore remove the associated message
		if (pEventActivity && pEventActivity->GetActivityEventType() == ToDoActivity && 
			Token != pEventActivity->GetSender())
		{
			TRACE("REMOVE ASSIOCIATED EVENT\n");
			delete pEventActivity;
			pEventActivity = NULL;
			RemoveEventFilename( Filename );
		}
		if (pEventActivity)
			delete pEventActivity;
		Token = Tokenizer.GetNextToken();
	}
	pEventActivity = NULL;

	return TRUE;
}


BOOL	ZBUserQueueManager::RemoveEventFromUserQueue( ZBEventActivity& EventActivity, CString User )
{
	// For multi-user mode, run through all users
	ZBTokenizer	Tokenizer( ';' );
	CString	Token = Tokenizer.GetFirstToken( User );
	while (!Token.IsEmpty())
	{
		if (!RemoveFromUserQueue( EventActivity, Token ))
			return FALSE;
		Token = Tokenizer.GetNextToken();
	}
	return TRUE;
}

BOOL	ZBUserQueueManager::RemoveEventFromReceiverQueue( ZBEventActivity& EventActivity )
{
	// For multi-user mode, run through all receiver
	ZBTokenizer	Tokenizer( ';' );
	CString	Token = Tokenizer.GetFirstToken( EventActivity.GetReceiver() );
	while (!Token.IsEmpty())
	{
		if (!RemoveFromUserQueue( EventActivity, Token ))
			return FALSE;
		Token = Tokenizer.GetNextToken();
	}
	return TRUE;
}

BOOL	ZBUserQueueManager::RemoveEventFromSenderQueue( ZBEventActivity& EventActivity )
{
	// For multi-user mode, run through all senders
	ZBTokenizer	Tokenizer( ';' );
	CString	Token = Tokenizer.GetFirstToken( EventActivity.GetSender() );
	while (!Token.IsEmpty())
	{
		if (!RemoveFromUserQueue( EventActivity, Token ))
			return FALSE;
		Token = Tokenizer.GetNextToken();
	}
	return TRUE;
}

BOOL	ZBUserQueueManager::RemoveFromUserQueue( ZBEventActivity& EventActivity, CString User )
{
	CString	Filename = BuildUserActivityEventFilename( EventActivity.GetFilename() + EventActivity.GetFileExtension(), User );
	return RemoveEventFilename( Filename );
}		   

BOOL	ZBUserQueueManager::ProceedDeleteMessage( ZBEventActivity& EventActivity )
{
	// For multi-user mode, run through all senders
	ZBTokenizer	Tokenizer( ';' );
	CString	Token = Tokenizer.GetFirstToken( EventActivity.GetReceiver() );
	while (!Token.IsEmpty())
	{
		CString	Filename = BuildUserActivityEventFilename( EventActivity.GetFilename() + EventActivity.GetFileExtension(ToDoActivity), Token );
		RemoveEventFilename( Filename );
		Token = Tokenizer.GetNextToken();
	}
	return TRUE;
}		   

CString	ZBUserQueueManager::BuildUserActivityEventFilename( CString Filename, const CString User )
{
	CString	Directory = m_UserDirectoryManager.BuildUserDirectory( User );
	return Directory + "\\" + Filename;
}


BOOL	ZBUserQueueManager::RemoveEventFilename( const CString Filename )
{
	// Test if the file exists
	CFileStatus status;
	if (CFile::GetStatus( Filename, status ))
	{
		// Physically remove the file
		for (int i = 0; i < 10; ++i)
		{
			TRY
			{
				CFile::Remove( Filename );
				TRACE1("FILENAME REMOVED %s\n", (const char*)Filename);
				return TRUE;
			}
			CATCH( CFileException, e )
			{
				::Sleep( 100 );
			}
			END_CATCH
		}
	}
	TRACE1("PROBLEM REMOVEING FILENAME %s\n", (const char*)Filename);
	return FALSE;
}