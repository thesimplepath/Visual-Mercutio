/****************************************************************************
 * ==> PSS_GenericErrorLine ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic error line                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GenericErrorLine.h"

// processsoft
#include "PSS_Tokenizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_GenericErrorLine
//---------------------------------------------------------------------------
PSS_GenericErrorLine::PSS_GenericErrorLine(const CString& message, int line, int error, int type) :
    PSS_ErrorLine(message, line, error, type)
{}
//---------------------------------------------------------------------------
PSS_GenericErrorLine::PSS_GenericErrorLine(const PSS_GenericErrorLine& other) :
    PSS_ErrorLine()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_GenericErrorLine::~PSS_GenericErrorLine()
{}
//---------------------------------------------------------------------------
PSS_GenericErrorLine& PSS_GenericErrorLine::operator = (const PSS_GenericErrorLine& other)
{
    // call the base class assignement operator
    PSS_ErrorLine::operator = ((const PSS_ErrorLine&)other);
    return *this;
}
//---------------------------------------------------------------------------
void PSS_GenericErrorLine::BuildString()
{
    PSS_Tokenizer tokenizer(';');

    // add the error type
    tokenizer.AddToken(!GetErrorType() ? "warning" : "error");

    // add the line number
    tokenizer.AddToken(GetLineNumber());

    // add the error number
    tokenizer.AddToken(GetErrorNumber());

    // add the error message
    tokenizer.AddToken(GetErrorMessage());

    // assign the string
    AssignString(tokenizer.GetString());
}
//---------------------------------------------------------------------------
void PSS_GenericErrorLine::Parse()
{
    PSS_Tokenizer tokenizer(';');

    // extract the type
    const CString typeStr = tokenizer.GetFirstToken((const char*)this);

    if (typeStr == "warning")
        SetErrorType(0);
    else
        SetErrorType(1);

    // extract the line number
    const CString lineNumberStr = tokenizer.GetNextToken();
    SetLineNumber(std::atoi(lineNumberStr));

    // extract the error number
    const CString ErrorNumberStr = tokenizer.GetNextToken();
    SetErrorNumber(std::atoi(ErrorNumberStr));

    // extract and set the error message
    SetErrorMessage(tokenizer.GetNextToken());
}
//---------------------------------------------------------------------------
