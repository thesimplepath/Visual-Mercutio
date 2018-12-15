//## begin module%387B026101F4.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%387B026101F4.cm

//## begin module%387B026101F4.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%387B026101F4.cp

//## Module: SysVar%387B026101F4; Package body
//## Subsystem: ZWinUtil%36DEE1730346
//## Source file: z:\adsoft~1\ZWinUtil\SysVar.cpp

//## begin module%387B026101F4.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%387B026101F4.additionalIncludes

//## begin module%387B026101F4.includes preserve=yes
//## end module%387B026101F4.includes

// SysVar
#include "SysVar.h"
//## begin module%387B026101F4.declarations preserve=no
//## end module%387B026101F4.declarations

//## begin module%387B026101F4.additionalDeclarations preserve=yes
//## end module%387B026101F4.additionalDeclarations


// Class ZSystemVar 



ZSystemVar::ZSystemVar (ZDDocument* pDoc, ZProcess* pProcess)
  //## begin ZSystemVar::ZSystemVar%947585841.hasinit preserve=no
  //## end ZSystemVar::ZSystemVar%947585841.hasinit
  //## begin ZSystemVar::ZSystemVar%947585841.initialization preserve=yes
  : m_pDoc(pDoc), m_pProcess(pProcess) 
  //## end ZSystemVar::ZSystemVar%947585841.initialization
{
  //## begin ZSystemVar::ZSystemVar%947585841.body preserve=yes
  //## end ZSystemVar::ZSystemVar%947585841.body
}


ZSystemVar::~ZSystemVar()
{
  //## begin ZSystemVar::~ZSystemVar%.body preserve=yes
  //## end ZSystemVar::~ZSystemVar%.body
}



//## Other Operations (implementation)
void ZSystemVar::Initialize (ZDDocument* pDoc, ZProcess* pProcess)
{
  //## begin ZSystemVar::Initialize%947585842.body preserve=yes
    m_pDoc = pDoc;
    m_pProcess = pProcess;
  //## end ZSystemVar::Initialize%947585842.body
}

CString ZSystemVar::Parse (CString Line)
{
  //## begin ZSystemVar::Parse%947585843.body preserve=yes
    CString    FinalLine;
    int        Pos = 0;
    int        StartPos = 0;
    int        EndPos = 0;

    // Parse the line and replace system variable by its content.
    while (true)
    {
        CString    Keyword = FindKeyword( Line, &StartPos, &EndPos );
        if (Keyword.IsEmpty())
        {
            // Copy the rest of the line
            FinalLine += Line;
            break;
        }
        // Has variable a translation
        CString    Content = GetVariableContent( Keyword );
        // If no equivalence, copy the line until the EndPos 
        // And set the line from the StartPos
        // This because it is possible to have a couple of $$ char without
        // a keyword and after another couple of $$
        if (Content.IsEmpty())
        {
            FinalLine += Line.Left( EndPos );
            Line = Line.Right( Line.GetLength() - EndPos );
        }
        else
        {
            FinalLine += Line.Left( StartPos );
            FinalLine += Content;
            Line = Line.Right( Line.GetLength() - (EndPos + 2) );
        }
    }
    return FinalLine;
  //## end ZSystemVar::Parse%947585843.body
}

CString ZSystemVar::GetVariableContent (const CString Variable)
{
  //## begin ZSystemVar::GetVariableContent%947585844.body preserve=yes
    if (Variable == szToday)
    {
        ZBDate    Today;
        Today.SetToday();
        return Today.GetStandardFormatedDate();
    }
    else
    if (Variable == szFilename)
    {
        if (m_pDoc)
        {
            return m_pDoc->GetPathName();
        }
        // Otherwise, return empty string
    }
    else
    if (Variable == szExchFilename)
    {
        if (m_pDoc)
        {
            return (m_pDoc->GetDocOptions().GetIsSynchronizeExchangeFeedFile()) ? m_pDoc->GetDocOptions().BuildSynchronizationFileName( m_pDoc->GetPathName() ) : "";
        }
        // Otherwise, return empty string
    }
    else
    if (Variable == szProcExchFilename)
    {
        if (m_pDoc)
        {
//            return (m_pDoc->GetProcessDocumentOptions().GetIsSynchronizeExchangeFeedFile()) ? m_pDoc->GetProcessDocumentOptions().BuildSynchronizationFileName( m_pDoc->GetPathName() ) : "";
        }
    }
    else
    if (Variable == szAuthor)
    {
        if (m_pDoc)
        {
            return m_pDoc->GetDocumentStamp().GetCreationUserName();
        }
        // Otherwise, return empty string
    }
    else
    if (Variable == szModifier)
    {
        if (m_pDoc)
        {
            return m_pDoc->GetDocumentStamp().GetModificationUserName();
        }
        // Otherwise, return empty string
    }
    else
    if (Variable == szCreationDate)
    {
        if (m_pDoc)
        {
            return ((ZBDate&)m_pDoc->GetDocumentStamp().GetCreationDate()).GetStandardFormatedDate();
        }
        // Otherwise, return empty string
    }
    else
    if (Variable == szModificationDate)
    {
        if (m_pDoc)
        {
            return ((ZBDate&)m_pDoc->GetDocumentStamp().GetModificationDate()).GetStandardFormatedDate();
        }
        // Otherwise, return empty string
    }
    else
    if (Variable == szPublishDate)
    {
        if (m_pDoc)
        {
            return ((ZBDate&)m_pDoc->GetDocumentStamp().GetPublishDate()).GetStandardFormatedDate();
        }
        // Otherwise, return empty string
    }
    else
    if (Variable == szFileVer)
    {
        if (m_pDoc)
        {
            char    szBuf[5];
            sprintf( szBuf, "%l", m_pDoc->GetDocumentStamp().GetPublishVersion());
            return szBuf;
        }
        // Otherwise, return empty string
    }
    return "";
  //## end ZSystemVar::GetVariableContent%947585844.body
}

CString ZSystemVar::FindKeyword (const CString& Line, int* StartPos, int* EndPos)
{
  //## begin ZSystemVar::FindKeyword%947609381.body preserve=yes
    CString    Keyword;
    int        StartP = 0;
    int        EndP = 0;

    StartP = Line.Find( "$$" );
    if (StartP != -1)
    {
        EndP = Line.Find( "$$", StartP + 2 );
        if (EndP != -1)
        {
            Keyword = Line.Mid( StartP, EndP - StartP + 2 );
            *StartPos = StartP;
            *EndPos = EndP;
        }
    }
    return Keyword;
  //## end ZSystemVar::FindKeyword%947609381.body
}

// Additional Declarations
  //## begin ZSystemVar%387AFE9F0147.declarations preserve=yes
  //## end ZSystemVar%387AFE9F0147.declarations

//## begin module%387B026101F4.epilog preserve=yes
//## end module%387B026101F4.epilog
