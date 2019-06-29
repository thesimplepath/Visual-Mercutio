/****************************************************************************
 * ==> PSS_SoapException ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides the soap exceptions                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <afx.h>
#include "stdafx.h"
#include "PSS_SoapException.h"

 //---------------------------------------------------------------------------
 // PSS_SoapException
 //---------------------------------------------------------------------------
PSS_SoapException::PSS_SoapException(int         exceptionCode,
                                     const char* exceptionInfo,
                                     const char* exceptionRaisedInFile,
                                     int         exceptionRaisedAtLine)
{
    m_Code     = exceptionCode;
    m_Message  = _T("");
    m_Info     = exceptionInfo ? exceptionInfo : _T("");
    m_FileName = exceptionRaisedInFile ? exceptionRaisedInFile: _T("");
    m_FileLine = exceptionRaisedAtLine;

    // automatic dump
    Dump();
}
//---------------------------------------------------------------------------
int PSS_SoapException::GetCode() const
{
    return m_Code;
}
//---------------------------------------------------------------------------
const CString PSS_SoapException::GetMessage() const
{
    return m_Message;
}
//---------------------------------------------------------------------------
const CString PSS_SoapException::GetInfo() const
{
    return m_Info;
}
//---------------------------------------------------------------------------
const CString PSS_SoapException::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
int PSS_SoapException::GetFileLine() const
{
    return m_FileLine;
}
//---------------------------------------------------------------------------
void PSS_SoapException::Dump()
{
    char tmpStr[256];

    OutputDebugString(_T("zSoapException caught:\n"));

    std::sprintf(tmpStr, _T("Ex %3d : \"%s\"\n"), m_Code, m_Message);
    OutputDebugString(tmpStr);

    std::sprintf(tmpStr, _T("       : (%s)\n"), m_Info);
    OutputDebugString(tmpStr);

    std::sprintf(tmpStr, _T("File   : %s (%d)\n"), m_FileName, m_FileLine);
    OutputDebugString(tmpStr);
}
//---------------------------------------------------------------------------
CString PSS_SoapException::getMessageByCode(int code)
{
    if (code < 0)
        return _T("");

    CString s;
    s.LoadString(UINT(code));

    return s;
}
//---------------------------------------------------------------------------
