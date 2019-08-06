//## begin module%36500BDD017F.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36500BDD017F.cm

//## begin module%36500BDD017F.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%36500BDD017F.cp

//## Module: ExpRT%36500BDD017F; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ExpRT.cpp

//## begin module%36500BDD017F.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%36500BDD017F.additionalIncludes

//## begin module%36500BDD017F.includes preserve=yes
// ZANumbrd
#include "ZANumbrd.h"
#include "ZATwoSts.h"

#include "MsgBox.h"
//## end module%36500BDD017F.includes

// ExpRT
#include "ExpRT.h"
//## begin module%36500BDD017F.declarations preserve=no
//## end module%36500BDD017F.declarations

//## begin module%36500BDD017F.additionalDeclarations preserve=yes
#include "ZDDoc.h"
// DocData
#include "DocData.h"


// Class ZUDocumentExport 




ZUDocumentExport::ZUDocumentExport(CString Filename, ZDDocument* pDoc, BOOL GenerateHeader, ESynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, PSS_StatusBar* pStatusBar)
  //## begin ZUDocumentExport::ZUDocumentExport%911215686.hasinit preserve=no
  //## end ZUDocumentExport::ZUDocumentExport%911215686.hasinit
  //## begin ZUDocumentExport::ZUDocumentExport%911215686.initialization preserve=yes
  : ZUExport( Filename, GenerateHeader, SeparatorType, Schema, PropagationMode, EmptyWhenZero, pStatusBar ),
      m_pDoc( pDoc )
  //## end ZUDocumentExport::ZUDocumentExport%911215686.initialization
{
  //## begin ZUDocumentExport::ZUDocumentExport%911215686.body preserve=yes
  //## end ZUDocumentExport::ZUDocumentExport%911215686.body
}


ZUDocumentExport::~ZUDocumentExport()
{
  //## begin ZUDocumentExport::~ZUDocumentExport%.body preserve=yes
  //## end ZUDocumentExport::~ZUDocumentExport%.body
}



//## Other Operations (implementation)
CString ZUDocumentExport::GetExportedLine (CObject* pObj)
{
  //## begin ZUDocumentExport::GetExportedLine%911215687.body preserve=yes
    CString    LineBuffer;

    switch (GetSeparatorType())
    {
        case E_SS_Comma:
        {
            LineBuffer.Format( "%s,%s\r\n", (const char*)((PlanFinObject*)pObj)->GetObjectName(), (const char*)((PlanFinObject*)pObj)->GetUnformatedObject() );
             break;
        }

        case E_SS_SemiColumn:
        {
            LineBuffer.Format( "%s;%s\r\n", (const char*)((PlanFinObject*)pObj)->GetObjectName(), (const char*)((PlanFinObject*)pObj)->GetUnformatedObject() );
             break;
        }

        case E_SS_Quote:
        {
            LineBuffer.Format( "\"%s\" \"%s\"\r\n", (const char*)((PlanFinObject*)pObj)->GetObjectName(), (const char*)((PlanFinObject*)pObj)->GetUnformatedObject() );
             break;
        }

        case E_SS_Automatic:
        case E_SS_Tab:
        default:
        {
            LineBuffer.Format( "%s\t%s\r\n", (const char*)((PlanFinObject*)pObj)->GetObjectName(), (const char*)((PlanFinObject*)pObj)->GetUnformatedObject() );
             break;
         }
    }
    return LineBuffer;
  //## end ZUDocumentExport::GetExportedLine%911215687.body
}

BOOL ZUDocumentExport::IsExportedField (CObject* pObj) const
{
  //## begin ZUDocumentExport::IsExportedField%911215688.body preserve=yes
    // If the object is exportable
    if (!((PlanFinObject*)pObj)->IsKindOf(RUNTIME_CLASS(PLFNAscii)) && 
        !((PlanFinObject*)pObj)->IsKindOf(RUNTIME_CLASS(PLFNAutoNumbered)) &&
        !((PlanFinObject*)pObj)->IsKindOf(RUNTIME_CLASS(PLFNTwoStates)))
        return FALSE;
    if (pObj->IsKindOf(RUNTIME_CLASS(PLFNText)) && ((PLFNText*)pObj)->GetIsStatic())
        return FALSE;
    return TRUE;
  //## end ZUDocumentExport::IsExportedField%911215688.body
}

BOOL ZUDocumentExport::ProcessLine (CString Line)
{
  //## begin ZUDocumentExport::ProcessLine%911215689.body preserve=yes
      // The line we received is exactly the same we exported
    CString    Name;
    CString    Value;

    char*    pCurrent = Line.GetBuffer(Line.GetLength()+2);
    char*    pNext;      

    char    SeparatorChar;
    switch (GetSeparatorType())
    {
        case E_SS_Tab:
        {
            SeparatorChar = '\t';
            break;
        }

        case E_SS_Comma:
        {
            SeparatorChar = ',';
            break;
        }

        case E_SS_SemiColumn:
        {
            SeparatorChar = ';';
            break;
        }

        case E_SS_Quote:
        {
            SeparatorChar = '"';

            // skip the first Quote char
            if (*pCurrent != '"')
                return FALSE;

            ++pCurrent;
            break;
        }

        case E_SS_Automatic:
        default:
        {
            SeparatorChar = '\t';
            break;
        }
    }

      // Extract the object name
    // Locates the separator char 
    pNext = strchr( pCurrent, SeparatorChar );
    if (!pNext)
        return FALSE;

    // Where next is found, put end of string char.
    *pNext = 0x00;
    
    // Copy the name
    Name = pCurrent;
    // Sets current to the next char after the next pointer
    pCurrent = ++pNext;

    // If Quote, skips the "
    if (GetSeparatorType() == E_SS_Quote)
    {
          // Find the first quote char
        pNext = strchr( pCurrent, SeparatorChar );
        if (!pNext)
            return FALSE;
        pCurrent = ++pNext;
          // Find the end quote char
        pNext = strchr( pCurrent, SeparatorChar );
        if (!pNext)
            return FALSE;
        // Where next is found, put end of string char.
        *pNext = 0x00;
    }
      // Extract the object value
    // It is the last field, just copy it
    Value = pCurrent;
    
    // Call the document to change the object value
      for (size_t i = 0; i < m_pDoc->GetDocumentDataCount(); ++i)
        m_pDoc->GetDocumentDataAt(i)->AssignObjectValue( Name, Value, 0, GetPropagationMode(), GetEmptyWhenZero() );
    return TRUE;
  //## end ZUDocumentExport::ProcessLine%911215689.body
}

CString ZUDocumentExport::GetHeaderLine ()
{
    switch (GetSeparatorType())
    {
        case E_SS_Automatic:
        case E_SS_Tab:        return "Nom\tValeur\r\n";
        case E_SS_Comma:      return "Nom,Valeur\r\n";
        case E_SS_SemiColumn: return "Nom;Valeur\r\n";
        case E_SS_Quote:      return "\"Nom\" \"Valeur\"\r\n";
        default:              break;
    }

    return "Nom\tValeur\r\n";
}

BOOL ZUDocumentExport::Import ()
{
  //## begin ZUDocumentExport::Import%922203344.body preserve=yes
      return ZUExport::Import();
  //## end ZUDocumentExport::Import%922203344.body
}

BOOL ZUDocumentExport::Export ()
{
  //## begin ZUDocumentExport::Export%922203345.body preserve=yes
      return ZUExport::Export();
  //## end ZUDocumentExport::Export%922203345.body
}

BOOL ZUDocumentExport::ExportAdditionalInfo ()
{
  //## begin ZUDocumentExport::ExportAdditionalInfo%922203346.body preserve=yes
      if (m_pDoc->GetDocumentStamp().GetDocumentFileType() == ProcessDocumentFileType)
      {
          WriteLine ( BuildLine (g_ExportProcessNameKey, m_pDoc->GetDocumentStamp().GetTitle()) );
        WriteLine ( BuildLine (g_ExportTemplateNameKey, "") );
        WriteLine ( BuildLine (g_ExportProcessExchangeFileNameKey, m_pDoc->GetDocumentStamp().GetKey1()) );
    }
    else
    {
          WriteLine ( BuildLine (g_ExportProcessNameKey, "") );
        WriteLine ( BuildLine (g_ExportTemplateNameKey, m_pDoc->GetDocumentStamp().GetTitle()) );
    }
      WriteLine ( BuildLine (g_ExportFolderNameKey, m_pDoc->GetDocumentStamp().GetFolderName()) );
    // If only keep FLF, do not export the filename
    if (m_pDoc->GetKeepOnlyFLF())
          WriteLine ( BuildLine (g_ExportFileNameKey, "") );
    else
          WriteLine ( BuildLine (g_ExportFileNameKey, m_pDoc->GetPathName()) );
    WriteLine ( BuildLine (g_ExportKeepOnlyFLFKey, (m_pDoc->GetKeepOnlyFLF()==TRUE) ? "1" : "0") );
      return TRUE;
  //## end ZUDocumentExport::ExportAdditionalInfo%922203346.body
}

BOOL ZUDocumentExport::ImportAdditionalInfo ()
{
  //## begin ZUDocumentExport::ImportAdditionalInfo%922203347.body preserve=yes
      return TRUE;
  //## end ZUDocumentExport::ImportAdditionalInfo%922203347.body
}

BOOL ZUDocumentExport::PreImport ()
{
  //## begin ZUDocumentExport::PreImport%922203360.body preserve=yes
    // Saves the current schema name
    // to be able to restore it after import.
    m_PreviousSchema = m_pDoc->GetCurrentSchema();
    // Change the schema only if it is not the
    // same as the current
    if (!GetSchemaName().IsEmpty() && m_PreviousSchema != GetSchemaName())
        m_pDoc->ChangeCurrentSchema( GetSchemaName(), TRUE );
    return TRUE;
  //## end ZUDocumentExport::PreImport%922203360.body
}

BOOL ZUDocumentExport::PostImport ()
{
  //## begin ZUDocumentExport::PostImport%922203361.body preserve=yes
    // Restore the previous Schema name
    // only if it was not the
    // same as the current
    if (!GetSchemaName().IsEmpty() && m_PreviousSchema != GetSchemaName())
        m_pDoc->ChangeCurrentSchema( m_PreviousSchema, TRUE );

    // Start the timer to clear color on field
    m_pDoc->StartCalcTimer();
    return TRUE;
  //## end ZUDocumentExport::PostImport%922203361.body
}

double ZUDocumentExport::ForecastedTotalObject ()
{
  //## begin ZUDocumentExport::ForecastedTotalObject%922203366.body preserve=yes
      return (double)m_pDoc->GetObjectCount();
  //## end ZUDocumentExport::ForecastedTotalObject%922203366.body
}

BOOL ZUDocumentExport::DoExportLoop ()
{
  //## begin ZUDocumentExport::DoExportLoop%922203368.body preserve=yes
    // For each object, assign 
    // the new corresponding font handle
    PlanFinObject  *pObj;
    CString            Line;
    double            Count = 0;
    // Initialize the object counter
    m_ObjectCounter = 1;

      for (size_t i = 0; i < m_pDoc->GetDocumentDataCount(); ++i)
      {
        if( (pObj=m_pDoc->GetDocumentDataAt(i)->GetHead()) != NULL )
        {
            do
            {
                // If the object is exportable
                if (IsExportedField( pObj ))
                {
                    Line = GetExportedLine ( pObj );
                    WriteLine ( Line );
                }
                if (m_pStatusBar)
                    m_pStatusBar->SetCurrentPercentage( (int) ((++Count / (double)m_pDoc->GetObjectCount()) * 100) );
                ++m_ObjectCounter;
            }
            while( (pObj=m_pDoc->GetDocumentDataAt(i)->GetNext( )) != NULL );
        }
    }
    return TRUE;
  //## end ZUDocumentExport::DoExportLoop%922203368.body
}

// Additional Declarations
  //## begin ZUDocumentExport%36500BAE01A9.declarations preserve=yes
  //## end ZUDocumentExport%36500BAE01A9.declarations

//## begin module%36500BDD017F.epilog preserve=yes
//## end module%36500BDD017F.epilog
