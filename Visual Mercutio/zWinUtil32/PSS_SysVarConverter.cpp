/****************************************************************************
 * ==> PSS_SysVarConverter -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a system variables converter to its content       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_SysVarConverter.h"

//---------------------------------------------------------------------------
// PSS_SysVarConverter
//---------------------------------------------------------------------------
PSS_SysVarConverter::PSS_SysVarConverter(PSS_Document* pDoc, PSS_Process* pProcess) :
    m_pDoc(pDoc),
    m_pProcess(pProcess)
{}
//---------------------------------------------------------------------------
PSS_SysVarConverter::PSS_SysVarConverter(const PSS_SysVarConverter& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_SysVarConverter::~PSS_SysVarConverter()
{}
//---------------------------------------------------------------------------
const PSS_SysVarConverter& PSS_SysVarConverter::operator = (const PSS_SysVarConverter& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_SysVarConverter::Initialize(PSS_Document* pDoc, PSS_Process* pProcess)
{
    m_pDoc     = pDoc;
    m_pProcess = pProcess;
}
//---------------------------------------------------------------------------
CString PSS_SysVarConverter::Parse(const CString& line)
{
    int     pos         = 0;
    int     startPos    = 0;
    int     endPos      = 0;
    CString lineToParse = line;
    CString finalLine;

    // parse the line and replace system variable by its content
    while (true)
    {
        const CString keyword = FindKeyword(lineToParse, &startPos, &endPos);

        if (keyword.IsEmpty())
        {
            // copy the line remaining part
            finalLine += lineToParse;
            break;
        }

        // check if variable has a translation
        const CString content = GetVariableContent(keyword);

        // if no equivalence, copy the line until the end pos is reached, and set the line from the start pos,
        // because it's possible to have a couple of $$ char without a keyword, and after another couple of $$
        if (content.IsEmpty())
        {
            finalLine   += lineToParse.Left(endPos);
            lineToParse  = lineToParse.Right(lineToParse.GetLength() - endPos);
        }
        else
        {
            finalLine   += lineToParse.Left(startPos);
            finalLine   += content;
            lineToParse  = lineToParse.Right(lineToParse.GetLength() - (endPos + 2));
        }
    }

    return finalLine;
}
//---------------------------------------------------------------------------
CString PSS_SysVarConverter::GetVariableContent(const CString& variable)
{
    if (variable == g_Today)
    {
        PSS_Date today;
        today.SetToday();
        return today.GetStandardFormattedDate();
    }
    else
    if (variable == g_FileName)
    {
        if (m_pDoc)
            return m_pDoc->GetPathName();
    }
    else
    if (variable == g_ExchFileName)
    {
        if (m_pDoc)
            return (m_pDoc->GetDocOptions().GetIsSynchronizeExchangeFeedFile()) ? m_pDoc->GetDocOptions().BuildSynchronizationFileName(m_pDoc->GetPathName()) : "";
    }
    else
    if (variable == g_Author)
    {
        if (m_pDoc)
            return m_pDoc->GetDocumentStamp().GetCreationUserName();
    }
    else
    if (variable == g_Modifier)
    {
        if (m_pDoc)
            return m_pDoc->GetDocumentStamp().GetModificationUserName();
    }
    else
    if (variable == g_CreationDate)
    {
        if (m_pDoc)
            return ((PSS_Date&)m_pDoc->GetDocumentStamp().GetCreationDate()).GetStandardFormattedDate();
    }
    else
    if (variable == g_ModificationDate)
    {
        if (m_pDoc)
            return ((PSS_Date&)m_pDoc->GetDocumentStamp().GetModificationDate()).GetStandardFormattedDate();
    }
    else
    if (variable == g_PublishDate)
    {
        if (m_pDoc)
            return ((PSS_Date&)m_pDoc->GetDocumentStamp().GetPublishDate()).GetStandardFormattedDate();
    }
    else
    if (variable == g_FileVer)
        if (m_pDoc)
        {
            char buffer[5];
            ::sprintf_s(buffer, 5, "%ld", m_pDoc->GetDocumentStamp().GetPublishVersion());
            return buffer;
        }

    return "";
}
//---------------------------------------------------------------------------
CString PSS_SysVarConverter::FindKeyword(const CString& line, int* pStartPos, int* pEndPos)
{
    PSS_Assert(pStartPos);
    PSS_Assert(pEndPos);

    const int     start = line.Find("$$");
          CString keyword;

    if (start != -1)
    {
        const int end = line.Find("$$", start + 2);

        if (end != -1)
        {
             keyword   = line.Mid(start, end - start + 2);
            *pStartPos = start;
            *pEndPos   = end;
        }
    }

    return keyword;
}
//---------------------------------------------------------------------------
