/////////////////////////////////////////////////////////////////////////////
//@doc ZBHistoricValueManager
//@module ZBHistoricValueManager.cpp | Implementation of the <c ZBHistoricValueManager> class.
// 
// zForms<tm>
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software, Inc. 
// All rights reserved.
// Contact:
// mailto:dominique.aigroz@adsoft-form.com
// http://www.adsoft-form.com
// 
// 

#include "StdAfx.h"

// ZBHistoricValueManager
#include "ZBHistoricValueManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// Class ZBHistoricValueManager 


ZBHistoricValueManager::ZBHistoricValueManager()
{
}


ZBHistoricValueManager::~ZBHistoricValueManager()
{
  	FreeHistoric();
}

ZBHistoricValueManager::ZBHistoricValueManager(const ZBHistoricValueManager &right)
{
	*this = right;
}


const ZBHistoricValueManager & ZBHistoricValueManager::operator=(const ZBHistoricValueManager &right)
{
	// Sets the iterator to the right entity set
	ZBHistoricValueIterator i(&right.GetHistoricEntitySetConst());
	for (ZBHistoricValue* pHistoValue = i.GetFirst(); pHistoValue != NULL; pHistoValue = i.GetNext())
	{
		Add( pHistoValue->Clone() );
	}
	return *this;
}

void ZBHistoricValueManager::AddHistoryValue (const CString& FieldName, const CString& Value)
{
	ZBHistoricValue* pHistoValue = FindHistoricEntity( FieldName );
	// If not found, create a new entity
	if (!pHistoValue)
	{
  		pHistoValue = new ZBHistoricValue( FieldName );
		ASSERT( pHistoValue != NULL );
		// Add it to the array of entity value
  		m_HistoricValueSet.Add( pHistoValue );
	}
	// Add a new historic value to the field		
	pHistoValue->AddHistoricValue( Value );
}

bool ZBHistoricValueManager::Remove( ZBHistoricValue* pValue )
{
	if (!pValue)
		return false;
	int Index = FindHistoricEntityIndex( pValue->GetEntityName() );
	if (Index == -1)
		return false;

	RemoveAt( Index );
	return true;
}

void ZBHistoricValueManager::RemoveAt( size_t Index )
{
	ZBHistoricValue* pValue = GetHistoricEntityAt( Index );
	if (pValue)
	{
		delete pValue;
		m_HistoricValueSet.RemoveAt( Index );
	}
}

bool ZBHistoricValueManager::RemoveFullHistory (const CString& FieldName)
{
	ZBHistoricValue* pHistoValue = FindHistoricEntity( FieldName );
	if (pHistoValue)
	{
		pHistoValue->FreeHistoric();
		return true;
	}
  	return true;
}

bool ZBHistoricValueManager::RemoveHistoryValue (const CString& FieldName, const CString& Value)
{
	ZBHistoricValue* pHistoValue = FindHistoricEntity( FieldName );
	if (pHistoValue)
	{
		return pHistoValue->RemoveHistoricValue( Value );
	}
  	return true;
}

int ZBHistoricValueManager::FindHistoricEntityIndex( const CString& FieldName ) const
{
	int nIdx = 0;
	ZBHistoricValueIterator i(&GetHistoricEntitySetConst());
	for (ZBHistoricValue* pHistoValue = i.GetFirst(); pHistoValue != NULL; pHistoValue = i.GetNext(), ++nIdx)
	{
		if (pHistoValue->GetEntityName() == FieldName)
			return nIdx;
	}
  	return -1;
}

CStringArray* ZBHistoricValueManager::GetFieldHistory (const CString& FieldName)
{
	ZBHistoricValue* pHistoValue = FindHistoricEntity( FieldName );
	if (pHistoValue)
	{
		return const_cast<CStringArray*>(&(pHistoValue->GetValueArray()));
	}

  	return NULL;
}

void ZBHistoricValueManager::FreeHistoric ()
{
	// Free all file objects allocated 
	ZBHistoricValueIterator i(&GetHistoricEntitySet());
	for (ZBHistoricValue* pHistoValue = i.GetFirst(); pHistoValue != NULL; pHistoValue = i.GetNext())
	{
		delete pHistoValue;
	}
  	m_HistoricValueSet.RemoveAll();
}



/////////////////////////////////////////////////////////////////////////////
// ZBHistoricValueManager serialization

#ifdef _DEBUG
CDumpContext& AFXAPI operator<<(CDumpContext& dc, ZBHistoricValueManager right)
{
	dc << "\nZBHistoricValueManager Object:";
	dc << "\n\tCount = " << (long)right.GetCount();
	ZBHistoricValueIterator i(&right.GetHistoricEntitySetConst());
	for (ZBHistoricValue* pHistoValue = i.GetFirst(); pHistoValue != NULL; pHistoValue = i.GetNext())
	{
		dc << "\n\tName = " << pHistoValue->GetEntityName();
	}
	return dc;
}
#endif // _DEBUG


CArchive& AFXAPI operator<<(CArchive& ar, ZBHistoricValueManager right)
{
	int Count = right.GetCount();
	ar << Count;

	// Serialize all values
	ZBHistoricValueIterator i(&right.GetHistoricEntitySetConst());
	for (ZBHistoricValue* pHistoValue = i.GetFirst(); pHistoValue != NULL; pHistoValue = i.GetNext())
	{
		ar << *pHistoValue;
	}
	return ar;

}

CArchive& AFXAPI operator>>(CArchive& ar, ZBHistoricValueManager& right)
{
	int Count;
	ar >> Count;
	// Serialize all values

	for (int i=0; i < Count; i++)
	{
		ZBHistoricValue* pHistoricEntity = new ZBHistoricValue;
		ar >> *pHistoricEntity;
		right.Add(pHistoricEntity);
	}
	return ar;
}

