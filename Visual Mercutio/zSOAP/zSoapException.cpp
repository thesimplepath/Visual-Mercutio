#include <afx.h>
#include "stdafx.h"
#include "zSoapException.h"

// JMR-MODIF - Le 15 septembre 2005 - Ajout des décorations Unicode _T(), nettoyage du code inutile.(En commentaires)

ZBSoapException::ZBSoapException( int			mExceptionCode,
								  const char*	mExceptionInfo,
								  const char*	mExceptionRaisedInFile,
								  int			mExceptionRaisedAtLine )
{
	m_code = mExceptionCode;

	m_message = _T( "" );
	
	if ( mExceptionInfo == NULL )
	{
		m_info = _T( "" );
	}
	else
	{
		m_info = mExceptionInfo;
	}
	
	if ( mExceptionRaisedInFile == NULL )
	{
		m_filename = _T( "" );
	}
	else
	{
		m_filename = mExceptionRaisedInFile;
	}
	
	m_fileline = mExceptionRaisedAtLine;

	// Automatic dump
	dump();
}

int ZBSoapException::getCode() const
{
	return m_code;
}

const CString ZBSoapException::getMessage() const
{
	return m_message;
}

const CString ZBSoapException::getInfo() const
{
	return m_info;
}

const CString ZBSoapException::getFileName() const
{
	return m_filename;
}

int ZBSoapException::getFileLine() const
{
	return m_fileline;
}

void ZBSoapException::dump()
{
	char tmpStr[256];

	OutputDebugString( _T( "zSoapException caught:\n" ) );

	sprintf( tmpStr, _T( "Ex %3d : \"%s\"\n" ), m_code,m_message );
	OutputDebugString( tmpStr );

	sprintf( tmpStr, _T( "       : (%s)\n" ), m_info );
	OutputDebugString( tmpStr );

	sprintf( tmpStr, _T( "File   : %s (%d)\n" ), m_filename, m_fileline );
	OutputDebugString( tmpStr );
}

CString ZBSoapException::getMessageByCode( int mcode )
{
	if ( mcode < 0 )
	{
		return _T( "" );
	}

	CString s;
	s.LoadString( (UINT)mcode );

	return s;
}
