// ZBGenericErrorLine.cpp: implementation of the ZBGenericErrorLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBGenericErrorLine.h"
#include "ZBTokenizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBGenericErrorLine::ZBGenericErrorLine(const CString message /*= ""*/, 
									   int line /*= -1*/, 
									   int error /*= -1*/, 
									   int type /*= -1*/)
: ZIErrorLine( message, line, error, type )
{
}

ZBGenericErrorLine::~ZBGenericErrorLine()
{

}

ZBGenericErrorLine::ZBGenericErrorLine(const ZBGenericErrorLine& src)
{
	*this = src;
}

ZBGenericErrorLine& ZBGenericErrorLine::operator=(const ZBGenericErrorLine& src)
{
	// Call the base class assignement operator
	ZIErrorLine::operator=( (const ZIErrorLine&)src);
	return *this;
}

void ZBGenericErrorLine::BuildString()
{
	ZBTokenizer	Tokenizer(';');
	// Add the error type
	Tokenizer.AddToken(	(GetErrorType() == 0) ? "warning" : "error" );
	// Add the line number
	Tokenizer.AddToken(	GetLineNumber() );
	// Add the error number
	Tokenizer.AddToken(	GetErrorNumber() );
	// Add the error message
	Tokenizer.AddToken(	GetErrorMessage() );
	// Assign the string
	AssignString( Tokenizer.GetString() );
}

void ZBGenericErrorLine::Parse()
{
	ZBTokenizer	Tokenizer(';');

  	// Extract the type
	CString TypeStr = Tokenizer.GetFirstToken( (const char*)this );
	if (TypeStr == "warning")
		SetErrorType( 0 );
	else
		SetErrorType( 1 );

  	// Extract the line number
	CString LineNumberStr = Tokenizer.GetNextToken();
	SetLineNumber( atoi(LineNumberStr) );

  	// Extract the error number
	CString ErrorNumberStr = Tokenizer.GetNextToken();
	SetErrorNumber( atoi(ErrorNumberStr) );

	// Extract and set the error message
	SetErrorMessage( Tokenizer.GetNextToken() );

}
