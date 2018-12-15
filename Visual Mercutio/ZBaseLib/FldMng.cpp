//## begin module%363DC9EF0240.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%363DC9EF0240.cm

//## begin module%363DC9EF0240.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%363DC9EF0240.cp

//## Module: FldMng%363DC9EF0240; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FldMng.cpp

//## begin module%363DC9EF0240.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%363DC9EF0240.additionalIncludes

//## begin module%363DC9EF0240.includes preserve=yes
//## end module%363DC9EF0240.includes

// FldMng
#include "FldMng.h"
//## begin module%363DC9EF0240.declarations preserve=no
//## end module%363DC9EF0240.declarations

//## begin module%363DC9EF0240.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL( ZAGlobalFieldManager, CObject, def_Version )
//## end module%363DC9EF0240.additionalDeclarations

// Class ZAGlobalFieldManager 

ZAGlobalFieldManager::ZAGlobalFieldManager()
  //## begin ZAGlobalFieldManager::ZAGlobalFieldManager%.hasinit preserve=no
  //## end ZAGlobalFieldManager::ZAGlobalFieldManager%.hasinit
  //## begin ZAGlobalFieldManager::ZAGlobalFieldManager%.initialization preserve=yes
  //## end ZAGlobalFieldManager::ZAGlobalFieldManager%.initialization
{
  //## begin ZAGlobalFieldManager::ZAGlobalFieldManager%.body preserve=yes
  //## end ZAGlobalFieldManager::ZAGlobalFieldManager%.body
}

ZAGlobalFieldManager::~ZAGlobalFieldManager()
{
  //## begin ZAGlobalFieldManager::~ZAGlobalFieldManager%.body preserve=yes
      FreeList();
  //## end ZAGlobalFieldManager::~ZAGlobalFieldManager%.body
}

void ZAGlobalFieldManager::FreeList ()
{
    //## begin ZAGlobalFieldManager::FreeList%910019983.body preserve=yes
    // Free all file objects allocated 
    for ( int i = 0; i < m_GlobalFieldArray.GetSize(); ++i )
    {
          delete ( (ZAObjectDefinition*)( m_GlobalFieldArray[i] ) );
    }

    m_GlobalFieldArray.RemoveAll();
    //## end ZAGlobalFieldManager::FreeList%910019983.body
}

int ZAGlobalFieldManager::AddField ( ZAObjectDefinition* Field )
{
    //## begin ZAGlobalFieldManager::AddField%910019976.body preserve=yes
    return m_GlobalFieldArray.Add( Field );
    //## end ZAGlobalFieldManager::AddField%910019976.body
}

BOOL ZAGlobalFieldManager::DeleteField ( const CString& Name )
{
    //## begin ZAGlobalFieldManager::DeleteField%910019977.body preserve=yes
    for ( int i = 0; i < m_GlobalFieldArray.GetSize(); ++i )
    {
        if ( ( (ZAObjectDefinition*)( m_GlobalFieldArray[i] ) )->GetFieldName() == Name )
          {
            // First free memory pointed at location
            delete ( (ZAObjectDefinition*)( m_GlobalFieldArray[i] ) );

            // Second remove the element from the array
              m_GlobalFieldArray.RemoveAt( i );    
              return TRUE;
          }
    }

    return FALSE;
    //## end ZAGlobalFieldManager::DeleteField%910019977.body
}

BOOL ZAGlobalFieldManager::DeleteAllField ()
{
    //## begin ZAGlobalFieldManager::DeleteAllField%919498957.body preserve=yes
    m_GlobalFieldArray.RemoveAll();

    return m_GlobalFieldArray.GetSize() == 0;
    //## end ZAGlobalFieldManager::DeleteAllField%919498957.body
}

ZAObjectDefinition* ZAGlobalFieldManager::FindField ( const CString& Name )
{
    //## begin ZAGlobalFieldManager::FindField%910019978.body preserve=yes
    for ( int i = 0; i < m_GlobalFieldArray.GetSize(); ++i )
        if ( ( (ZAObjectDefinition*)( m_GlobalFieldArray[i] ) )->GetFieldName() == Name )
            return (ZAObjectDefinition*)m_GlobalFieldArray[i];

    return NULL;
    //## end ZAGlobalFieldManager::FindField%910019978.body
}

ZAObjectDefinition* ZAGlobalFieldManager::GetAt ( int Index )
{
    //## begin ZAGlobalFieldManager::GetAt%910019979.body preserve=yes
    if ( Index < m_GlobalFieldArray.GetSize() )
        return (ZAObjectDefinition*)m_GlobalFieldArray[Index];

    return NULL;
    //## end ZAGlobalFieldManager::GetAt%910019979.body
}

CString ZAGlobalFieldManager::GetDescription ( const CString& Name )
{
    //## begin ZAGlobalFieldManager::GetDescription%910019980.body preserve=yes
    ZAObjectDefinition* pObject;
    
    if ( pObject = FindField( Name ) )
        return pObject->GetDescription();

    return "";
    //## end ZAGlobalFieldManager::GetDescription%910019980.body
}

CString ZAGlobalFieldManager::GetClassName ( const CString& Name )
{
    //## begin ZAGlobalFieldManager::GetClassName%910019981.body preserve=yes
    ZAObjectDefinition* pObject;
    
    if ( pObject = FindField( Name ) )
        return pObject->GetClassName();

    return "";
    //## end ZAGlobalFieldManager::GetClassName%910019981.body
}

const CStringArray& ZAGlobalFieldManager::GetFieldNameArray ()
{
    //## begin ZAGlobalFieldManager::GetFieldNameArray%910019982.body preserve=yes
    m_FieldNameArray.RemoveAll();

    for ( int i = 0; i < m_GlobalFieldArray.GetSize(); ++i )
        m_FieldNameArray.Add( ( (ZAObjectDefinition*)( m_GlobalFieldArray[i] ) )->GetFieldName() );

    return m_FieldNameArray;
    //## end ZAGlobalFieldManager::GetFieldNameArray%910019982.body
}

void ZAGlobalFieldManager::CopyFieldDefinition ( const CString Name, PlanFinObject* pObj, ZDDocument* pDoc )
{
    //## begin ZAGlobalFieldManager::CopyFieldDefinition%910104707.body preserve=yes
    ZAObjectDefinition* pObjectDef = FindField( Name );

    if ( pObjectDef )
    {
        pObj->SetFormatType( pObjectDef->GetpObject()->GetFormatType() );
        pObj->SetJustify( pObjectDef->GetpObject()->GetJustify(NULL) );
        pObj->SethStyle( pObjectDef->GetpObject()->GethStyle() );
        pObj->SetiAngle( pObjectDef->GetpObject()->GetiAngle(), pDoc );
        pObj->SetbIsVisible( pObjectDef->GetpObject()->GetbIsVisible() );
        pObj->SetbMustBePrinted( pObjectDef->GetpObject()->GetbMustBePrinted() );
        pObj->SetColor( pObjectDef->GetpObject()->GetColor() );
        pObj->SetFillColor( pObjectDef->GetpObject()->GetFillColor() );
        pObj->SethFont( pObjectDef->GetpObject()->GethFont() );
        pObj->SethStyle( pObjectDef->GetpObject()->GethStyle() );
        pObj->SetEmptyStyle( pObjectDef->GetpObject()->GetEmptyStyle() );
        pObj->SetDefaultValue( pObjectDef->GetpObject()->GetDefaultValue() );
        pObj->ConvertFormatedObject( ((PlanFinObject*)pObjectDef->GetpObject())->GetUnformatedObject() );
    }
    //## end ZAGlobalFieldManager::CopyFieldDefinition%910104707.body
}

// Additional Declarations

//## begin ZAGlobalFieldManager%363DC8B30079.declarations preserve=yes

/////////////////////////////////////////////////////////////////////////////
// ZAGlobalFieldManager diagnostics

#ifdef _DEBUG
void ZAGlobalFieldManager::AssertValid() const
{
    CObject::AssertValid();
}

void ZAGlobalFieldManager::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG
//## end ZAGlobalFieldManager%363DC8B30079.declarations

//## Other Operations (implementation)
void ZAGlobalFieldManager::Serialize ( CArchive& ar )
{
  //## begin ZAGlobalFieldManager::Serialize%910019974.body preserve=yes
      m_GlobalFieldArray.Serialize( ar );
  //## end ZAGlobalFieldManager::Serialize%910019974.body
}

//## begin module%363DC9EF0240.epilog preserve=yes
//## end module%363DC9EF0240.epilog