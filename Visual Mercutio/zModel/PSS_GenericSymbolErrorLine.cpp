/****************************************************************************
 * ==> PSS_GenericSymbolErrorLine ------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic symbol error line                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GenericSymbolErrorLine.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_GenericSymbolErrorLine
//---------------------------------------------------------------------------
PSS_GenericSymbolErrorLine::PSS_GenericSymbolErrorLine(const CString& message) :
    PSS_ErrorLine(message, -1)
{
    BuildString();
}
//---------------------------------------------------------------------------
PSS_GenericSymbolErrorLine::PSS_GenericSymbolErrorLine(const CString& message,
                                                       const CString& symbolname,
                                                       const CString& symbolpath,
                                                       int            error,
                                                       int            type) :
    PSS_ErrorLine(message, -1, error, type),
    m_SymbolName(symbolname),
    m_SymbolPath(symbolpath)
{
    BuildString();
}
//---------------------------------------------------------------------------
PSS_GenericSymbolErrorLine::PSS_GenericSymbolErrorLine(UINT           messageID,
                                                       const CString& symbolname,
                                                       const CString& symbolpath,
                                                       int            error,
                                                       int            type) :
    PSS_ErrorLine(messageID, -1, error, type),
    m_SymbolName(symbolname),
    m_SymbolPath(symbolpath)
{
    BuildString();
}
//---------------------------------------------------------------------------
PSS_GenericSymbolErrorLine::PSS_GenericSymbolErrorLine(const PSS_GenericSymbolErrorLine& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_GenericSymbolErrorLine::~PSS_GenericSymbolErrorLine()
{}
//---------------------------------------------------------------------------
PSS_GenericSymbolErrorLine& PSS_GenericSymbolErrorLine::operator = (const PSS_GenericSymbolErrorLine& other)
{
    PSS_ErrorLine::operator = ((const PSS_ErrorLine&)other);

    m_SymbolName = other.m_SymbolName;
    m_SymbolPath = other.m_SymbolPath;

    return *this;
}
//---------------------------------------------------------------------------
void PSS_GenericSymbolErrorLine::BuildString()
{
    PSS_Tokenizer tokenizer(';');

    // add the error type
    if (GetErrorType() == -1)
        tokenizer.AddToken(_T(" "));
    else
    {
        CString s;

        switch (GetErrorType())
        {
            case 0:  s = _T("warning"); break;
            case 1:  s = _T("error");   break;
            default: s = _T(".");       break;
        }

        tokenizer.AddToken(s);

        // add the symbol name
        tokenizer.AddToken(GetSymbolName());

        // add the symbol path
        tokenizer.AddToken(_T("[") + GetSymbolPath() + _T("]"));
    }

    // add the error message
    tokenizer.AddToken(GetErrorMessage());

    // assign the string
    AssignString(tokenizer.GetString());
}
//---------------------------------------------------------------------------
void PSS_GenericSymbolErrorLine::Parse()
{
    PSS_Tokenizer tokenizer(';');

    // extract the type
    const CString typeStr = tokenizer.GetFirstToken(GetBuffer(GetLength() + 1));

    if (typeStr == _T(" "))
        // extract the message
        SetErrorMessage(tokenizer.GetNextToken());
    else
    {
        if (typeStr == _T("warning"))
            SetErrorType(0);
        else
        if (typeStr == _T("error"))
            SetErrorType(1);
        else
        if (typeStr == _T("."))
            SetErrorType(2);
        else
            SetErrorType(2);

        // extract and set the symbol name
        SetSymbolName(tokenizer.GetNextToken());

        // extract and set the symbol path
        const CString path = tokenizer.GetNextToken();

        if ((path.GetLength() - 2) > 0)
            SetSymbolPath(path.Mid(1, path.GetLength() - 2));

        // extract and set the error message
        SetErrorMessage(tokenizer.GetNextToken());
    }

    ReleaseBuffer(-1);
}
//---------------------------------------------------------------------------
