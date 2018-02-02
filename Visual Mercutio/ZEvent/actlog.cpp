//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
#include <StdAfx.h>

// ActLog
#include "ActLog.h"


ZUActivityLog::ZUActivityLog (CString LogFileName, BOOL UseDatabase)
  : m_LogFileName(LogFileName), m_UseDatabase(UseDatabase),
	m_pActivityLogDatabase(NULL), m_pActivityLogFile(NULL)
{
}

BOOL ZUActivityLog::Create (CString LogFileName, BOOL UseDatabase)
{
	m_UseDatabase = UseDatabase;
  	m_LogFileName = LogFileName;
	return ZUActivityLog::Initialize();
}


BOOL ZUActivityLog::Initialize ()
{
  	if (m_LogFileName.IsEmpty())
  		return FALSE;
	if (m_UseDatabase)
		m_pActivityLogDatabase = new ZUActivityLogDatabase( m_LogFileName );
	else
		m_pActivityLogFile = new ZUActivityLogFile( m_LogFileName );

	return TRUE;
}

ZUActivityLog::~ZUActivityLog()
{
	if (m_UseDatabase && m_pActivityLogDatabase)
	{
		m_pActivityLogDatabase->Close();
		delete m_pActivityLogDatabase;
		m_pActivityLogDatabase = NULL;
	}
	else
		if (m_pActivityLogFile)
		{
			m_pActivityLogFile->Close();
			delete m_pActivityLogFile;
			m_pActivityLogFile = NULL;
		}
}




BOOL ZUActivityLog::Close ()
{
	if (m_UseDatabase && m_pActivityLogDatabase)
	{
		return m_pActivityLogDatabase->Close();
	}
	else
		if (m_pActivityLogFile)
			return m_pActivityLogFile->Close();
	return FALSE;
}


BOOL ZUActivityLog::AppendToLog (ZBEventActivity& EventActivity)
{
	if (m_UseDatabase && m_pActivityLogDatabase)
	{
		return m_pActivityLogDatabase->AppendToLog( EventActivity );
	}
	else
		if (m_pActivityLogFile)
			return m_pActivityLogFile->AppendToLog( EventActivity );
	return FALSE;
}


BOOL ZUActivityLog::ClearLog()
{
	if (m_UseDatabase && m_pActivityLogDatabase)
	{
		return m_pActivityLogDatabase->ClearLog();
	}
	else
		if (m_pActivityLogFile)
			return m_pActivityLogFile->ClearLog();
	return FALSE;
}
