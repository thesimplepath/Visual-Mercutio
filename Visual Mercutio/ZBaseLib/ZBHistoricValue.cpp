/////////////////////////////////////////////////////////////////////////////
//@doc ZBHistoricValue
//@module ZBHistoricValue.cpp | Implementation of the <c ZBHistoricValue> class.
// 
// zForms<tm>
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software, Inc. 
// All rights reserved.
// Contact:
// mailto:dominique.aigroz@adsoft-form.com
// http://www.adsoft-form.com
// 
// 

#include <StdAfx.h>

// ZBHistoricValue
#include "ZBHistoricValue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Class ZBHistoricValue 

ZBHistoricValue::ZBHistoricValue( const CString EntityName /*= ""*/ )
	: m_EntityName( EntityName )
{
}

ZBHistoricValue::ZBHistoricValue( const ZBHistoricValue &right )
{
	*this = right;
}

ZBHistoricValue::~ZBHistoricValue()
{
	// JMR-MODIF - Ajout du code de nettoyage de la mémoire.
	m_ValueHistoryArray.RemoveAll();
	m_EntityName.Empty();
}

const ZBHistoricValue & ZBHistoricValue::operator=( const ZBHistoricValue &right )
{
  	// copy the values
  	for ( int i = 0; i < right.m_ValueHistoryArray.GetSize(); ++i )
  		m_ValueHistoryArray.Add( right.m_ValueHistoryArray[i] );

	m_EntityName = right.m_EntityName;

	return *this;
}

int ZBHistoricValue::FindHistoricValue (const CString& Value) const
{
  	for ( int i = 0; i < m_ValueHistoryArray.GetSize(); ++i )
  		if ( m_ValueHistoryArray[i] == Value )
  			return i;

	return -1;
}

void ZBHistoricValue::AddHistoricValue ( const CString Value )
{
  	// Tests if the value already exists
	if ( HistoricValueExist( Value ) )
		return;

	// If not, add it
  	m_ValueHistoryArray.Add( Value );
}

bool ZBHistoricValue::RemoveHistoricValue ( const CString& Value )
{
	int Index = FindHistoricValue( Value );

	if ( Index != -1 )
		m_ValueHistoryArray.RemoveAt( Index );

	return ( Index != -1 ) ? true : false;
}

void ZBHistoricValue::FreeHistoric ()
{
  	m_ValueHistoryArray.RemoveAll();
}

ZBHistoricValue* ZBHistoricValue::Clone ()
{
	ZBHistoricValue* pObject = new ZBHistoricValue( *this );
	return pObject;
}

/////////////////////////////////////////////////////////////////////////////
// ZBHistoricValue serialization

#ifdef _DEBUG
CDumpContext& AFXAPI operator<<( CDumpContext& dc, ZBHistoricValue right )
{
	dc << "\nZBHistoricValue Object:";
	dc << "\n\tCount = " << (long)right.GetCount();

	return dc << "\n\tName = " << right.GetEntityName();

}
#endif // _DEBUG

CArchive& AFXAPI operator<<( CArchive& ar, ZBHistoricValue right )
{
	int Count = right.GetCount();
	ar << Count;

	// Serialize all values
    for ( int i = 0; i < Count; ++i )
		ar << right.GetValueAt( i );

	return ar << right.GetEntityName();
}

CArchive& AFXAPI operator>>( CArchive& ar, ZBHistoricValue& right )
{
	int Count;
	CString str;
	ar >> Count;

	// Serialize all values
    for ( int i = 0; i < Count; ++i )
		ar >> str;
		right.AddHistoricValue( str );

	ar >> str;
	right.SetEntityName( str );
	return ar;
}
