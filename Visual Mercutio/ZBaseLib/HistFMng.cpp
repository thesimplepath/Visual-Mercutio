//## begin module%363481C90252.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%363481C90252.cm

//## begin module%363481C90252.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%363481C90252.cp

//## Module: HistFMng%363481C90252; Package body
//## Subsystem: ZFile modules%3620C63F0009
//## Source file: z:\adsoft~1\zfile\HistFMng.cpp

//## begin module%363481C90252.additionalIncludes preserve=no
#include "StdAfx.h"
//## end module%363481C90252.additionalIncludes

//## begin module%363481C90252.includes preserve=yes
//## end module%363481C90252.includes

// HistFMng
#include "HistFMng.h"
//## begin module%363481C90252.declarations preserve=no
//## end module%363481C90252.declarations

//## begin module%363481C90252.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZAHistoryFieldManager, CObject, def_Version)
//## end module%363481C90252.additionalDeclarations

// Class ZAHistoryFieldManager 

ZAHistoryFieldManager::ZAHistoryFieldManager()
  //## begin ZAHistoryFieldManager::ZAHistoryFieldManager%.hasinit preserve=no
  //## end ZAHistoryFieldManager::ZAHistoryFieldManager%.hasinit
  //## begin ZAHistoryFieldManager::ZAHistoryFieldManager%.initialization preserve=yes
  //## end ZAHistoryFieldManager::ZAHistoryFieldManager%.initialization
{
  //## begin ZAHistoryFieldManager::ZAHistoryFieldManager%.body preserve=yes
  //## end ZAHistoryFieldManager::ZAHistoryFieldManager%.body
}

ZAHistoryFieldManager::~ZAHistoryFieldManager()
{
  //## begin ZAHistoryFieldManager::~ZAHistoryFieldManager%.body preserve=yes
  	FreeList();
  //## end ZAHistoryFieldManager::~ZAHistoryFieldManager%.body
}

//## Other Operations (implementation)
void ZAHistoryFieldManager::AddFieldHistoryValue ( const CString& FieldName, const CString& Value )
{
	//## begin ZAHistoryFieldManager::AddFieldHistoryValue%909410998.body preserve=yes
	BOOL Done = FALSE;

	for ( int i = 0; i < m_FieldHistoryArray.GetSize(); ++i )
	{
		if ( ( (ZAHistoryField*)( m_FieldHistoryArray[i] ) )->GetFieldName() == FieldName )
		{
			( (ZAHistoryField*)( m_FieldHistoryArray[i] ) )->AddFieldValue( Value );
			Done = TRUE;
		}
	}

	// If not done, this field does not exists, thus create it.
	if ( Done == FALSE )
	{
		ZAHistoryField* pNewField = new ZAHistoryField;
		
		pNewField->SetFieldName( FieldName );
		pNewField->AddFieldValue( Value );
		m_FieldHistoryArray.Add( pNewField );
	}
	//## end ZAHistoryFieldManager::AddFieldHistoryValue%909410998.body
}

BOOL ZAHistoryFieldManager::RemoveFieldHistory ( const CString& FieldName )
{
	//## begin ZAHistoryFieldManager::RemoveFieldHistory%909410999.body preserve=yes
	for ( int i = 0; i < m_FieldHistoryArray.GetSize(); ++i )
	{
		if ( ( (ZAHistoryField*)( m_FieldHistoryArray[i] ) )->GetFieldName() == FieldName )
		{
			// First free memory pointed at location
			delete ( (ZAHistoryField*)( m_FieldHistoryArray[i] ) );

			// Second remove the element from the array
			m_FieldHistoryArray.RemoveAt( i );	

			return TRUE;
  		}
	}

	return FALSE;
	//## end ZAHistoryFieldManager::RemoveFieldHistory%909410999.body
}

BOOL ZAHistoryFieldManager::RemoveFieldHistoryValue ( const CString& FieldName, const CString& Value )
{
	//## begin ZAHistoryFieldManager::RemoveFieldHistoryValue%909411000.body preserve=yes
	for ( int i = 0; i < m_FieldHistoryArray.GetSize(); ++i )
	{
		if ( ( (ZAHistoryField*)( m_FieldHistoryArray[i] ) )->GetFieldName() == FieldName )
		{
			return ( (ZAHistoryField*)( m_FieldHistoryArray[i] ) )->RemoveFieldValue( Value );
		}
	}

	return FALSE;
	//## end ZAHistoryFieldManager::RemoveFieldHistoryValue%909411000.body
}

ZAHistoryField* ZAHistoryFieldManager::FindField ( const CString& FieldName )
{
	//## begin ZAHistoryFieldManager::FindField%909411001.body preserve=yes
	for ( int i = 0; i < m_FieldHistoryArray.GetSize(); ++i )
	{
		if ( ( (ZAHistoryField*)( m_FieldHistoryArray[i] ) )->GetFieldName() == FieldName )
		{
			return ( (ZAHistoryField*)( m_FieldHistoryArray[i] ) );
		}
	}

	return NULL;
	//## end ZAHistoryFieldManager::FindField%909411001.body
}

CStringArray* ZAHistoryFieldManager::GetFieldHistory ( const CString& FieldName )
{
	//## begin ZAHistoryFieldManager::GetFieldHistory%909411002.body preserve=yes
	for ( int i = 0; i < m_FieldHistoryArray.GetSize(); ++i )
	{
		if ( ( (ZAHistoryField*)( m_FieldHistoryArray[i] ) )->GetFieldName() == FieldName )
		{
			return &(CStringArray&)( (ZAHistoryField*)( m_FieldHistoryArray[i] ) )->GetValueArray();
		}
	}

	return NULL;
	//## end ZAHistoryFieldManager::GetFieldHistory%909411002.body
}

void ZAHistoryFieldManager::Serialize ( CArchive& ar )
{
	//## begin ZAHistoryFieldManager::Serialize%909411003.body preserve=yes
	m_FieldHistoryArray.Serialize( ar );
	//## end ZAHistoryFieldManager::Serialize%909411003.body
}

void ZAHistoryFieldManager::FreeList ()
{
	//## begin ZAHistoryFieldManager::FreeList%909411005.body preserve=yes
	// Free all file objects allocated 
	for ( int i = 0; i < m_FieldHistoryArray.GetSize(); ++i )
		delete ( (ZAHistoryField*)( m_FieldHistoryArray[i] ) );
	
	m_FieldHistoryArray.RemoveAll();
	//## end ZAHistoryFieldManager::FreeList%909411005.body
}

// Additional Declarations
//## begin ZAHistoryFieldManager%36347DBE0290.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// ZAHistoryFieldManager diagnostics

#ifdef _DEBUG
void ZAHistoryFieldManager::AssertValid() const
{
	CObject::AssertValid();
}

void ZAHistoryFieldManager::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );
}
#endif //_DEBUG

//## end ZAHistoryFieldManager%36347DBE0290.declarations
//## begin module%363481C90252.epilog preserve=yes
//## end module%363481C90252.epilog