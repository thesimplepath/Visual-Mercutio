//## begin module%382BBDE80137.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%382BBDE80137.cm

//## begin module%382BBDE80137.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%382BBDE80137.cp

//## Module: FLFDataF%382BBDE80137; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FLFDataF.cpp

//## begin module%382BBDE80137.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%382BBDE80137.additionalIncludes

//## begin module%382BBDE80137.includes preserve=yes
//## end module%382BBDE80137.includes

// FLFDataF
#include "FLFDataF.h"
//## begin module%382BBDE80137.declarations preserve=no
//## end module%382BBDE80137.declarations

//## begin module%382BBDE80137.additionalDeclarations preserve=yes
#include "ZBTokenizer.h"
//## end module%382BBDE80137.additionalDeclarations


// Class ZUFLFDataFeed 







ZUFLFDataFeed::ZUFLFDataFeed()
  //## begin ZUFLFDataFeed::ZUFLFDataFeed%.hasinit preserve=no
  //## end ZUFLFDataFeed::ZUFLFDataFeed%.hasinit
  //## begin ZUFLFDataFeed::ZUFLFDataFeed%.initialization preserve=yes
  : m_KeepOnlyFLF(FALSE)
  //## end ZUFLFDataFeed::ZUFLFDataFeed%.initialization
{
  //## begin ZUFLFDataFeed::ZUFLFDataFeed%.body preserve=yes
  //## end ZUFLFDataFeed::ZUFLFDataFeed%.body
}


ZUFLFDataFeed::~ZUFLFDataFeed()
{
  //## begin ZUFLFDataFeed::~ZUFLFDataFeed%.body preserve=yes
  //## end ZUFLFDataFeed::~ZUFLFDataFeed%.body
}



//## Other Operations (implementation)
BOOL ZUFLFDataFeed::ProcessLine (CString Line)
{
  //## begin ZUFLFDataFeed::ProcessLine%942391394.body preserve=yes
      // The line we received is exactly the same we exported
    CString    Key;
    CString    Value;


    ZBTokenizer    Tokenizer;

    switch (GetSeparatorType())
    {
        case E_SS_Comma:
        {
            Tokenizer.SetSeparator(',');
            break;
        }

        case E_SS_SemiColumn:
        {
            Tokenizer.SetSeparator(';');
            break;
        }

        case E_SS_Automatic:
        case E_SS_Tab:
        default:
        {
            Tokenizer.SetSeparator('\t');
            break;
        }
    }

      // Extract the key
    Key = Tokenizer.GetFirstToken( Line );
    // If no Key, end
    if (Key.IsEmpty())
        return FALSE;
      // Extract the value
    Value = Tokenizer.GetNextToken();

    if (!Key.CompareNoCase(g_ExportProcessNameKey))
        m_ProcessName = Value;
    else
    if (!Key.CompareNoCase(g_ExportTemplateNameKey))
        m_FormName = Value;
    else
    if (!Key.CompareNoCase(g_ExportFolderNameKey))
        m_FolderName = Value;
    else
    if (!Key.CompareNoCase(g_ExportFileNameKey))
        m_FileName = Value;
    else
    if (Key.CompareNoCase(g_ExportProcessExchangeFileNameKey))
        m_ProcessExchangeFileName = Value;
    else
    if (Key.CompareNoCase(g_ExportKeepOnlyFLFKey))
        m_KeepOnlyFLF = atoi( Value );

    return TRUE;      
  //## end ZUFLFDataFeed::ProcessLine%942391394.body
}

BOOL ZUFLFDataFeed::ImportAdditionalInfo ()
{
  //## begin ZUFLFDataFeed::ImportAdditionalInfo%942391397.body preserve=yes
    return TRUE;
  //## end ZUFLFDataFeed::ImportAdditionalInfo%942391397.body
}

BOOL ZUFLFDataFeed::PreImport ()
{
  //## begin ZUFLFDataFeed::PreImport%942391398.body preserve=yes
    return TRUE;
  //## end ZUFLFDataFeed::PreImport%942391398.body
}

// Additional Declarations
  //## begin ZUFLFDataFeed%382BBC9E03AA.declarations preserve=yes
  //## end ZUFLFDataFeed%382BBC9E03AA.declarations

//## begin module%382BBDE80137.epilog preserve=yes
//## end module%382BBDE80137.epilog
