//## begin module%37E7FB9C0275.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%37E7FB9C0275.cm

//## begin module%37E7FB9C0275.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%37E7FB9C0275.cp

//## Module: GFDataF%37E7FB9C0275; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\GFDataF.cpp

//## begin module%37E7FB9C0275.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%37E7FB9C0275.additionalIncludes

//## begin module%37E7FB9C0275.includes preserve=yes
//## end module%37E7FB9C0275.includes

// GFDataF
#include "GFDataF.h"
//## begin module%37E7FB9C0275.declarations preserve=no
//## end module%37E7FB9C0275.declarations

//## begin module%37E7FB9C0275.additionalDeclarations preserve=yes
#include "ZBTokenizer.h"
// BObjUtil
#include "BObjUtil.h"


const    char    FieldNameKey[] = "$$FieldName$$";
const    char    FieldDescriptionKey[] = "$$FieldDescription$$";
const    char    FieldUserHelpKey[] = "$$FieldUserHelp$$";
const    char    FieldReadOnlyKey[] = "$$FieldReadOnly$$";
const    char    FieldListSortedKey[] = "$$FieldListSorted$$";
const    char    FieldClassNameKey[] = "$$FieldClassName$$";
const    char    FieldMultiColumnKey[] = "$$FieldIsMultiColumn$$";
const    char    FieldHeaderNameKey[] = "$$FieldHeaderName$$";
//## end module%37E7FB9C0275.additionalDeclarations


// Class ZUFieldDefinitionDataFeed 





ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed (CString Filename, ZBFieldRepository* pFieldRepository, ZAObjectDefinition* pObjectDefinition, BOOL GenerateHeader, ESynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, ZIStatusBar* pStatusBar)
  //## begin ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed%937950157.hasinit preserve=no
  //## end ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed%937950157.hasinit
  //## begin ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed%937950157.initialization preserve=yes
  : ZUExport( Filename, GenerateHeader, SeparatorType, Schema, PropagationMode, EmptyWhenZero, pStatusBar ),
    m_pSourceFieldRepository(pFieldRepository), m_pObjectDefinition(pObjectDefinition)
  //## end ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed%937950157.initialization
{
  //## begin ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed%937950157.body preserve=yes
  //## end ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed%937950157.body
}

ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed (CString Filename, ZBFieldRepository* pFieldRepository, BOOL GenerateHeader, ESynchronizationSeparatorType SeparatorType, CString Schema, int PropagationMode, BOOL EmptyWhenZero, ZIStatusBar* pStatusBar)
  //## begin ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed%938030360.hasinit preserve=no
  //## end ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed%938030360.hasinit
  //## begin ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed%938030360.initialization preserve=yes
  : ZUExport( Filename, GenerateHeader, SeparatorType, Schema, PropagationMode, EmptyWhenZero, pStatusBar ),
    m_pSourceFieldRepository(pFieldRepository), m_pObjectDefinition(NULL)
  //## end ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed%938030360.initialization
{
  //## begin ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed%938030360.body preserve=yes
  //## end ZUFieldDefinitionDataFeed::ZUFieldDefinitionDataFeed%938030360.body
}


ZUFieldDefinitionDataFeed::~ZUFieldDefinitionDataFeed()
{
  //## begin ZUFieldDefinitionDataFeed::~ZUFieldDefinitionDataFeed%.body preserve=yes
    DeleteLineArray();
  //## end ZUFieldDefinitionDataFeed::~ZUFieldDefinitionDataFeed%.body
}



//## Other Operations (implementation)
CString ZUFieldDefinitionDataFeed::GetExportedLine (CObject* pObj)
{
  //## begin ZUFieldDefinitionDataFeed::GetExportedLine%937950158.body preserve=yes
    ZAObjectDefinition*        pObjectDefinition = (ZAObjectDefinition*)pObj;
    if (!pObjectDefinition)
        return "";

    ZAHistoryField*            pObjectHistory;
    if (m_pSourceFieldRepository)
    {
        pObjectHistory = m_pSourceFieldRepository->FindFieldHistory( pObjectDefinition->GetFieldName() );
    }
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

    // Add the field name
    Tokenizer.AddToken( FieldNameKey );
    Tokenizer.AddToken( pObjectDefinition->GetFieldName() );
    Line = Tokenizer.GetString();
    Line += "\r\n";
    Tokenizer.ClearAllTokens();

    // Add the field description
    Tokenizer.AddToken( FieldDescriptionKey );
    Tokenizer.AddToken( pObjectDefinition->GetDescription() );
    Line += Tokenizer.GetString();
    Line += "\r\n";
    Tokenizer.ClearAllTokens();

    // Add the field user description
    Tokenizer.AddToken( FieldUserHelpKey );
    Tokenizer.AddToken( pObjectDefinition->GetHelpUserDescription() );
    Line += Tokenizer.GetString();
    Line += "\r\n";
    Tokenizer.ClearAllTokens();

    // Add the read only flag
    Tokenizer.AddToken( FieldReadOnlyKey );
    Tokenizer.AddToken( (pObjectHistory && pObjectHistory->IsReadOnly()) ? "1" : "0" );
    Line += Tokenizer.GetString();
    Line += "\r\n";
    Tokenizer.ClearAllTokens();

    // Add the read only flag
    Tokenizer.AddToken( FieldListSortedKey );
    Tokenizer.AddToken( (pObjectHistory && pObjectDefinition->IsSorted()) ? "1" : "0" );
    Line += Tokenizer.GetString();
    Line += "\r\n";
    Tokenizer.ClearAllTokens();

    // Add the class name 
    Tokenizer.AddToken( FieldClassNameKey );
    Tokenizer.AddToken( pObjectDefinition->GetClassName() );
    Line += Tokenizer.GetString();
    Line += "\r\n";
    Tokenizer.ClearAllTokens();

    

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
  //## end ZUFieldDefinitionDataFeed::GetExportedLine%937950158.body
}

BOOL ZUFieldDefinitionDataFeed::ProcessLine (CString Line)
{
  //## begin ZUFieldDefinitionDataFeed::ProcessLine%937950159.body preserve=yes
      // The line we received is exactly the same we exported
    CString    Key;
    CString    Value;


    ZBTokenizer    Tokenizer;

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

      // Extract the key
    Key = Tokenizer.GetFirstToken( Line );
    // If no Key, end
    if (Key.IsEmpty())
        return FALSE;
      // Extract the value
    Value = Tokenizer.GetNextToken();

    FieldExport*    pFieldExport = new FieldExport( Key, Value );
    m_LineArray.Add( (CObject*)pFieldExport );
    return TRUE;      
  //## end ZUFieldDefinitionDataFeed::ProcessLine%937950159.body
}

CString ZUFieldDefinitionDataFeed::GetHeaderLine ()
{
  //## begin ZUFieldDefinitionDataFeed::GetHeaderLine%937950160.body preserve=yes
    return "";
  //## end ZUFieldDefinitionDataFeed::GetHeaderLine%937950160.body
}

double ZUFieldDefinitionDataFeed::ForecastedTotalObject ()
{
  //## begin ZUFieldDefinitionDataFeed::ForecastedTotalObject%937950164.body preserve=yes
    return 0;
  //## end ZUFieldDefinitionDataFeed::ForecastedTotalObject%937950164.body
}

BOOL ZUFieldDefinitionDataFeed::DoExportLoop ()
{
  //## begin ZUFieldDefinitionDataFeed::DoExportLoop%937950165.body preserve=yes
    // If not object to export, do nothing
    if (!m_pObjectDefinition)
        return FALSE;
    // Only one object to export
    CString Line;
    Line = GetExportedLine( (CObject*)m_pObjectDefinition );
    WriteLine ( Line );
      return TRUE;
  //## end ZUFieldDefinitionDataFeed::DoExportLoop%937950165.body
}

BOOL ZUFieldDefinitionDataFeed::PreImport ()
{
  //## begin ZUFieldDefinitionDataFeed::PreImport%937950166.body preserve=yes
    DeleteLineArray();
    return TRUE;
  //## end ZUFieldDefinitionDataFeed::PreImport%937950166.body
}

BOOL ZUFieldDefinitionDataFeed::PostImport ()
{
  //## begin ZUFieldDefinitionDataFeed::PostImport%938372467.body preserve=yes
    CString    FieldName;
    CString    Description;
    CString    HelpUser;
    CString    ClassName;
    CString    HeaderNames;
    BOOL    ReadOnly = FALSE;
    BOOL    Sorted = TRUE;
    BOOL    IsMultiColumn = FALSE;
    int        i = 0;
    BOOL    HasBeenAssigned = TRUE;
    // Run through line objects and find the fields
    for (; i < m_LineArray.GetSize() && m_LineArray.GetAt(i) && HasBeenAssigned ; ++i)
    {
        HasBeenAssigned = FALSE;
        if (((FieldExport*)m_LineArray.GetAt(i))->m_Key == FieldNameKey)
        {
            HasBeenAssigned = TRUE;
            FieldName = ((FieldExport*)m_LineArray.GetAt(i))->m_Value;
        }
        else
        if (((FieldExport*)m_LineArray.GetAt(i))->m_Key == FieldDescriptionKey)
        {
            HasBeenAssigned = TRUE;
            Description = ((FieldExport*)m_LineArray.GetAt(i))->m_Value;
        }
        else
        if (((FieldExport*)m_LineArray.GetAt(i))->m_Key == FieldUserHelpKey)
        {
            HasBeenAssigned = TRUE;
            HelpUser = ((FieldExport*)m_LineArray.GetAt(i))->m_Value;
        }
        else
        if (((FieldExport*)m_LineArray.GetAt(i))->m_Key == FieldReadOnlyKey)
        {
            HasBeenAssigned = TRUE;
            ReadOnly = (((FieldExport*)m_LineArray.GetAt(i))->m_Value == "1") ? 1 : 0;
        }
        else
        if (((FieldExport*)m_LineArray.GetAt(i))->m_Key == FieldListSortedKey)
        {
            HasBeenAssigned = TRUE;
            Sorted = (((FieldExport*)m_LineArray.GetAt(i))->m_Value == "1") ? 1 : 0;
        }
        else
        if (((FieldExport*)m_LineArray.GetAt(i))->m_Key == FieldClassNameKey)
        {
            HasBeenAssigned = TRUE;
            ClassName = ((FieldExport*)m_LineArray.GetAt(i))->m_Value;
        }
        else
        if (((FieldExport*)m_LineArray.GetAt(i))->m_Key == FieldMultiColumnKey)
        {
            HasBeenAssigned = TRUE;
            IsMultiColumn = (((FieldExport*)m_LineArray.GetAt(i))->m_Value == "1") ? 1 : 0;
        }
        else
        if (((FieldExport*)m_LineArray.GetAt(i))->m_Key == FieldHeaderNameKey)
        {
            HasBeenAssigned = TRUE;
            HeaderNames = ((FieldExport*)m_LineArray.GetAt(i))->m_Value;
        }

    }
    // No fieldname found, error
    if (FieldName.IsEmpty())
        return FALSE;
    ZAObjectDefinition* pObjectDefinition = m_pSourceFieldRepository->FindField( FieldName );
    if (!pObjectDefinition)
    {
        // Otherwise, create the class and add it to the repository
        pObjectDefinition = new ZAObjectDefinition;
        if (!pObjectDefinition)
            return FALSE;
        pObjectDefinition->SetFieldName( FieldName );
        if (ClassName.IsEmpty())
            pObjectDefinition->SetpObject( NULL );
        else
        {
            // Set the class name
            pObjectDefinition->SetClassName( ClassName );
            // Create a new object with the class name
            PlanFinObject* pObj = ZBObjectUtility::ConstructObject( ClassName );
            // Set the fieldname
            pObj->SetObjectName( FieldName );
            // Assign it
            pObjectDefinition->SetpObject( pObj );
        }
        // Add the field to the repository
        m_pSourceFieldRepository->AddField( pObjectDefinition );
    }

    // Assign values to object definition
    pObjectDefinition->SetDescription( Description ); 
    pObjectDefinition->SetHelpUserDescription( HelpUser );
    pObjectDefinition->SetSorted( Sorted );

    // If we have values to add to history
    --i;    // Go back to the previous element
    if (m_LineArray.GetSize() >= i)
    {
        // and after, run through the rest and add it to the history
        for (; i < m_LineArray.GetSize(); ++i)
        {
            if (m_LineArray.GetAt(i))
                m_pSourceFieldRepository->AddFieldHistoryValue( FieldName, ((FieldExport*)m_LineArray.GetAt(i))->m_Key );
        }

        ZAHistoryField*            pObjectHistory;
        pObjectHistory = m_pSourceFieldRepository->FindFieldHistory( FieldName );
        if (pObjectHistory)
            pObjectHistory->SetReadOnly( ReadOnly );
    }
    return TRUE;
  //## end ZUFieldDefinitionDataFeed::PostImport%938372467.body
}

void ZUFieldDefinitionDataFeed::DeleteLineArray ()
{
  //## begin ZUFieldDefinitionDataFeed::DeleteLineArray%938372466.body preserve=yes
    for (int i = 0; i < m_LineArray.GetSize(); ++i)
    {
        if (m_LineArray.GetAt(i))
            delete (FieldExport*)m_LineArray.GetAt(i);
    }
    m_LineArray.RemoveAll();
  //## end ZUFieldDefinitionDataFeed::DeleteLineArray%938372466.body
}

// Additional Declarations
  //## begin ZUFieldDefinitionDataFeed%37E7FA7C02FD.declarations preserve=yes
  //## end ZUFieldDefinitionDataFeed%37E7FA7C02FD.declarations

//## begin module%37E7FB9C0275.epilog preserve=yes
ZUFieldDefinitionDataFeed::FieldExport::FieldExport( const CString Key /*= ""*/, const CString Value /*= ""*/)
: m_Key(Key), m_Value(Value)
{
}

ZUFieldDefinitionDataFeed::FieldExport::~FieldExport()
{
}
//## end module%37E7FB9C0275.epilog
