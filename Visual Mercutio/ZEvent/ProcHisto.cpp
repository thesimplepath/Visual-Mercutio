//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
#include <StdAfx.h>

// ProcHisto
#include "ProcHisto.h"


ZDProcessHistoryDb::ZDProcessHistoryDb (CString DatabaseFileName, DatabaseType DatabaseTp)
  : m_DatabaseFileName(DatabaseFileName), m_DatabaseTp(DatabaseTp),
	m_pProcessHistoDAO(NULL)
{
}

BOOL ZDProcessHistoryDb::Create (CString DatabaseFileName, DatabaseType DatabaseTp)
{
  	m_DatabaseFileName = DatabaseFileName;
	m_DatabaseTp = DatabaseTp;
	return ZDProcessHistoryDb::Initialize();
}


BOOL ZDProcessHistoryDb::Initialize ()
{
  	if (m_DatabaseFileName.IsEmpty())
  		return FALSE;
	switch (m_DatabaseTp)
	{
		case DAODatabase:
		{
			m_pProcessHistoDAO = new ZDProcessHistoryDAO( m_DatabaseFileName );
			break;
		}
		case ODBCDatabase:
		{
			ASSERT( FALSE );	// Not yet implemented
			return FALSE;
		}

	}
	return TRUE;
}

ZDProcessHistoryDb::~ZDProcessHistoryDb()
{
	switch (m_DatabaseTp)
	{
		case DAODatabase:
		{
			if (m_pProcessHistoDAO)
			{
				m_pProcessHistoDAO->Close();
				delete m_pProcessHistoDAO;
				m_pProcessHistoDAO = NULL;
			}
			break;
		}
		case ODBCDatabase:
		{
			ASSERT( FALSE );	// Not yet implemented
			break;
		}

	}
}




BOOL ZDProcessHistoryDb::Close ()
{
	switch (m_DatabaseTp)
	{
		case DAODatabase:
		{
			if (m_pProcessHistoDAO)
				return m_pProcessHistoDAO->Close();
			break;
		}
		case ODBCDatabase:
		{
			ASSERT( FALSE );	// Not yet implemented
			break;
		}
	}
	return FALSE;
}


BOOL ZDProcessHistoryDb::AppendEventToHistoric (ZBEventActivity& EventActivity)
{
	switch (m_DatabaseTp)
	{
		case DAODatabase:
		{
			if (m_pProcessHistoDAO)
				return m_pProcessHistoDAO->AppendEventToHistoric( EventActivity );
			break;
		}
		case ODBCDatabase:
		{
			ASSERT( FALSE );	// Not yet implemented
			break;
		}
	}
	return FALSE;
}


