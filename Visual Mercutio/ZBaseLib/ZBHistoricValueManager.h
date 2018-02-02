/////////////////////////////////////////////////////////////////////////////
//@doc ZBHistoricValueManager
//@module ZBHistoricValueManager.h | Interface of the <c ZBHistoricValueManager> class.
//
// Advanced Dedicated Software Classes
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software,
// All rights reserved.
// Contact:
// mailto:dominique.aigroz@adsoft-form.com
// http://www.adsoft-form.com
//
// This source code is part of the zForms library.
// See these sources for detailed information regarding
// zForms libraries.
//
// Author:       Dom
// <nl>Created:		 03/2000
// <nl>Description:  ZBHistoricValueManager is a manager of ZBHistoricValue
//

#ifndef ZBHistoricValueManager_h
#define ZBHistoricValueManager_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%363481D50050.includes

// ZBHistoricValue
#include "ZBHistoricValue.h"


#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS



/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;


///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBHistoricValueSet | An array of ZBHistoricValue pointers.
//@iex typedef CCArray_T<ZBHistoricValue*,ZBHistoricValue*> ZBHistoricValueSet;
typedef CCArray_T<ZBHistoricValue*,ZBHistoricValue*> ZBHistoricValueSet;

//@type ZBHistoricValueIterator | An iterator for ZBHistoricValueSet collections.
//@iex typedef Iterator_T<ZBHistoricValue*> ZBHistoricValueIterator;
typedef Iterator_T<ZBHistoricValue*> ZBHistoricValueIterator;



class AFX_EXT_CLASS ZBHistoricValueManager
{
public:
	// Constructors
	ZBHistoricValueManager();
	// Copy constructor
	ZBHistoricValueManager(const ZBHistoricValueManager &right);
	// Assignment Operator
	const ZBHistoricValueManager & operator=(const ZBHistoricValueManager &right);
    // Destructor
    ~ZBHistoricValueManager();

	// Add an historic value
	void Add( ZBHistoricValue* pValue );
	// Remove an historic value
	bool Remove( ZBHistoricValue* pValue );
	//	Add a new historic value into the manager.
	void AddHistoryValue (const CString& FieldName, const CString& Value);

	//	Remove a specific historic value from the manager.
	bool RemoveFullHistory (const CString& FieldName);

	//	Remove a specific historic value from the manager.
	bool RemoveHistoryValue (const CString& FieldName, const CString& Value);

	// Search if a specific fields exists.	Return the index if found
	// otherwise, return -1
	int FindHistoricEntityIndex( const CString& FieldName ) const;
	// Search if a specific fields exists.
	ZBHistoricValue* FindHistoricEntity( const CString& FieldName ) const
	{
		int Index = FindHistoricEntityIndex( FieldName );
		return (Index != -1) ? GetHistoricEntityAt(Index) : NULL;
	};

	//	Get the pointer of the field history.
	CStringArray* GetFieldHistory (const CString& FieldName);


	//	Return the number of elements of the History manager.
	size_t GetCount() const;

	ZBHistoricValueSet& GetHistoricEntitySet()
	{
		return m_HistoricValueSet;
	};
	const ZBHistoricValueSet& GetHistoricEntitySetConst() const
	{
		return m_HistoricValueSet;
	};

	//	remove the history.
	void FreeHistoric ();

private:
	// Remove the historic value at a specific index .
	void RemoveAt( size_t Index );
	// Return the historic value at a specific index .
	ZBHistoricValue* GetHistoricEntityAt( size_t Index ) const;

private:

	// Contains all fields history.
	ZBHistoricValueSet m_HistoricValueSet;


};

// Class ZBHistoricValueManager 


inline size_t ZBHistoricValueManager::GetCount () const
{
  	return m_HistoricValueSet.GetSize();
}

inline ZBHistoricValue* ZBHistoricValueManager::GetHistoricEntityAt( size_t Index ) const
{
	return (Index < GetCount()) ? m_HistoricValueSet.GetAt(Index) : NULL;
}

inline void ZBHistoricValueManager::Add( ZBHistoricValue* pValue )
{
	m_HistoricValueSet.Add( pValue );
}

// Global operator for serialization
#ifdef _DEBUG
CDumpContext& AFXAPI operator<<(CDumpContext& dc,ZBHistoricValueManager src);
#endif

CArchive& AFXAPI operator<<(CArchive& ar, ZBHistoricValueManager src);
CArchive& AFXAPI operator>>(CArchive& ar, ZBHistoricValueManager& src);


#endif
