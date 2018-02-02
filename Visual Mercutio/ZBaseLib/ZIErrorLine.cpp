// ZIErrorLine.cpp: implementation of the ZIErrorLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZIErrorLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZIErrorLine::ZIErrorLine( const CString message /*= ""*/, 
						  int line /*= -1*/, 
						  int error /*= -1*/, 
						  int type /*= -1*/)
{
	m_ErrorMessage = message;
	m_LineNumber = line;
	m_ErrorNumber = error;
	m_ErrorType = type;
	// And build the string
	BuildString();
}

ZIErrorLine::ZIErrorLine( UINT nIDSmessage, 
						  int line /*= -1*/, 
						  int error /*= -1*/, 
						  int type /*= -1*/)
{
	m_ErrorMessage.LoadString( nIDSmessage );
	m_LineNumber = line;
	m_ErrorNumber = error;
	m_ErrorType = type;
	// And build the string
	BuildString();
}


ZIErrorLine& ZIErrorLine::operator=(const ZIErrorLine& src)
{
	m_ErrorMessage = src.m_ErrorMessage;
	m_LineNumber = src.m_LineNumber;
	m_ErrorNumber = src.m_ErrorNumber;
	m_ErrorType = src.m_ErrorType;
	// And build the string
	BuildString();
	return *this;
}
