/****************************************************************************
 * ==> PSS_ErrorLine -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an error line for logger                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ErrorLine.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ErrorLine
//---------------------------------------------------------------------------
PSS_ErrorLine::PSS_ErrorLine(const CString& message,
                             int            line,
                             int            error,
                             int            type) :
    m_ErrorMessage(message),
    m_LineNumber(line),
    m_ErrorNumber(error),
    m_ErrorType(type)
{
    // build the string
    BuildString();
}
//---------------------------------------------------------------------------
PSS_ErrorLine::PSS_ErrorLine(UINT messageID,
                             int  line,
                             int  error,
                             int  type) :
    m_LineNumber(line),
    m_ErrorNumber(error),
    m_ErrorType(type)
{
    m_ErrorMessage.LoadString(messageID);

    // build the string
    BuildString();
}
//---------------------------------------------------------------------------
PSS_ErrorLine& PSS_ErrorLine::operator = (const PSS_ErrorLine& other)
{
    m_ErrorMessage = other.m_ErrorMessage;
    m_LineNumber   = other.m_LineNumber;
    m_ErrorNumber  = other.m_ErrorNumber;
    m_ErrorType    = other.m_ErrorType;

    // build the string
    BuildString();

    return *this;
}
//---------------------------------------------------------------------------
