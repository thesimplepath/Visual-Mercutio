//## begin module%3821259D03D7.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3821259D03D7.cm

//## begin module%3821259D03D7.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%3821259D03D7.cp

//## Module: GFValueF%3821259D03D7; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\GFValueF.cpp

//## begin module%3821259D03D7.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%3821259D03D7.additionalIncludes

//## begin module%3821259D03D7.includes preserve=yes
//## end module%3821259D03D7.includes

// GFValueF
#include "GFValueF.h"
//## begin module%3821259D03D7.declarations preserve=no
//## end module%3821259D03D7.declarations

//## begin module%3821259D03D7.additionalDeclarations preserve=yes
#include "ZBTokenizer.h"
// BObjUtil
#include "BObjUtil.h"
//## end module%3821259D03D7.additionalDeclarations


// Class ZUFieldValueDataFeed 




ZUFieldValueDataFeed::ZUFieldValueDataFeed (CString Filename, ZBFieldRepository* pFieldRepository, ZAObjectDefinition* pObjectDefinition, BOOL GenerateHeader, ESynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, ZIStatusBar* pStatusBar)
  //## begin ZUFieldValueDataFeed::ZUFieldValueDataFeed%941696498.hasinit preserve=no
  //## end ZUFieldValueDataFeed::ZUFieldValueDataFeed%941696498.hasinit
  //## begin ZUFieldValueDataFeed::ZUFieldValueDataFeed%941696498.initialization preserve=yes
  : ZUExport( Filename, GenerateHeader, SeparatorType, Schema, PropagationMode, EmptyWhenZero, pStatusBar ),
    m_pSourceFieldRepository(pFieldRepository),
    m_pObjectDefinition(pObjectDefinition)
  //## end ZUFieldValueDataFeed::ZUFieldValueDataFeed%941696498.initialization
{
  //## begin ZUFieldValueDataFeed::ZUFieldValueDataFeed%941696498.body preserve=yes
  //## end ZUFieldValueDataFeed::ZUFieldValueDataFeed%941696498.body
}

ZUFieldValueDataFeed::ZUFieldValueDataFeed (CString Filename, CStringArray* pValueArray, BOOL GenerateHeader, ESynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, ZIStatusBar* pStatusBar)
  //## begin ZUFieldValueDataFeed::ZUFieldValueDataFeed%941696510.hasinit preserve=no
  //## end ZUFieldValueDataFeed::ZUFieldValueDataFeed%941696510.hasinit
  //## begin ZUFieldValueDataFeed::ZUFieldValueDataFeed%941696510.initialization preserve=yes
  : ZUExport( Filename, GenerateHeader, SeparatorType, Schema, PropagationMode, EmptyWhenZero, pStatusBar ),
    m_pValueArray(pValueArray)
  //## end ZUFieldValueDataFeed::ZUFieldValueDataFeed%941696510.initialization
{
  //## begin ZUFieldValueDataFeed::ZUFieldValueDataFeed%941696510.body preserve=yes
  //## end ZUFieldValueDataFeed::ZUFieldValueDataFeed%941696510.body
}


ZUFieldValueDataFeed::~ZUFieldValueDataFeed()
{
  //## begin ZUFieldValueDataFeed::~ZUFieldValueDataFeed%.body preserve=yes
  //## end ZUFieldValueDataFeed::~ZUFieldValueDataFeed%.body
}



//## Other Operations (implementation)
CString ZUFieldValueDataFeed::GetExportedLine (CObject* pObj)
{
  //## begin ZUFieldValueDataFeed::GetExportedLine%941696500.body preserve=yes
    ZAObjectDefinition*        pObjectDefinition = (ZAObjectDefinition*)pObj;
    if (!pObjectDefinition || !m_pSourceFieldRepository)
        return "";

    ZAHistoryField*            pObjectHistory = m_pSourceFieldRepository->FindFieldHistory( pObjectDefinition->GetFieldName() );

    ZBTokenizer    Tokenizer;
    CString        Line;

    switch (GetSeparatorType())
    {
        case E_SS_Comma:
        {
            Tokenizer.SetSeparator( ',' );
            break;
        }

        case E_SS_SemiColumn:
        {
            Tokenizer.SetSeparator( ';' );
            break;
        }

        case E_SS_Automatic:
        case E_SS_Tab:
        default:
        {
            Tokenizer.SetSeparator( '\t' );
            break;
        }
    }
    // Export the field history
    for (size_t i = 0; pObjectHistory && i < pObjectHistory->GetCount(); ++i)
    {
        // Add the field history value
        Tokenizer.AddToken( pObjectHistory->GetValueArray().GetAt(i) );
        Line += Tokenizer.GetString();
        Line += "\r\n";
        Tokenizer.ClearAllTokens();
    }
    return Line;
  //## end ZUFieldValueDataFeed::GetExportedLine%941696500.body
}

BOOL ZUFieldValueDataFeed::ProcessLine (CString Line)
{
  //## begin ZUFieldValueDataFeed::ProcessLine%941696501.body preserve=yes

    // If no value array, do nothing
    if (!m_pValueArray)
        return FALSE;

    // The line we receive is one history value
    m_pValueArray->Add( Line );
    return TRUE;
  //## end ZUFieldValueDataFeed::ProcessLine%941696501.body
}

CString ZUFieldValueDataFeed::GetHeaderLine ()
{
  //## begin ZUFieldValueDataFeed::GetHeaderLine%941696502.body preserve=yes
    return "";
  //## end ZUFieldValueDataFeed::GetHeaderLine%941696502.body
}

double ZUFieldValueDataFeed::ForecastedTotalObject ()
{
  //## begin ZUFieldValueDataFeed::ForecastedTotalObject%941696505.body preserve=yes
    return 0;
  //## end ZUFieldValueDataFeed::ForecastedTotalObject%941696505.body
}

BOOL ZUFieldValueDataFeed::DoExportLoop ()
{
  //## begin ZUFieldValueDataFeed::DoExportLoop%941696506.body preserve=yes
    // If not object to export, do nothing
    if (!m_pObjectDefinition || !m_pSourceFieldRepository)
        return FALSE;
    // Only one object to export
    CString Line;
    Line = GetExportedLine( (CObject*)m_pObjectDefinition );
    WriteLine ( Line );
      return TRUE;
  //## end ZUFieldValueDataFeed::DoExportLoop%941696506.body
}

// Additional Declarations
  //## begin ZUFieldValueDataFeed%38212538024B.declarations preserve=yes
  //## end ZUFieldValueDataFeed%38212538024B.declarations

//## begin module%3821259D03D7.epilog preserve=yes
//## end module%3821259D03D7.epilog
