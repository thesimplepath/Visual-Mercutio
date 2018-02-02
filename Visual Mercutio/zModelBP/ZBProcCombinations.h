/////////////////////////////////////////////////////////////////////////////
//@doc ZBProcCombinations
//@module ZBProcCombinations.h | Interface of the <c ZBProcCombinations> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:		 06/2001
// <nl>Description:  ZBProcCombinations procedure combinations
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBProcCombinations_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)
#define AFX_ZBProcCombinations_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 6 fàvrier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBBPCombinationProperties;

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBBPCombinationPropertiesSet | An array of ZBSymbolEntity pointers.
//@iex typedef CCArray_T<ZBBPCombinationProperties*,ZBBPCombinationProperties*> ZBBPCombinationPropertiesSet;
typedef CCArray_T<ZBBPCombinationProperties*, ZBBPCombinationProperties*> ZBBPCombinationPropertiesSet;

//@type ZBBPCombinationPropertiesIterator | An iterator for ZBBPCombinationPropertiesSet collections.
//@iex typedef Iterator_T<ZBBPCombinationProperties*> ZBBPCombinationPropertiesIterator;
typedef Iterator_T<ZBBPCombinationProperties*> ZBBPCombinationPropertiesIterator;

/////////////////////////////////////////////////////////////////////////////
// ZBProcCombinations class

class AFX_EXT_CLASS ZBProcCombinations : public CObject
{
	DECLARE_SERIAL( ZBProcCombinations )

public:

	ZBProcCombinations( CODSymbolComponent* pParent = NULL );
	virtual ~ZBProcCombinations();

	// Copy constructor.
	ZBProcCombinations( const ZBProcCombinations& src );

	// Assignment operator.
	ZBProcCombinations& operator=( const ZBProcCombinations& src );

	// Create a duplicate copy of this object.
	virtual ZBProcCombinations* Dup() const;

	// Sets the parent symbol object
	void SetParent( CODSymbolComponent* pParent );

	// Create the initial properties
	bool CreateInitialProperties();

	// Add a new empty combination,
	// and return the index of the new added combination
	// Return -1 if the function fails
	int AddNewCombination();

	// Add a new combination,
	// and return the index of the new added combination
	// Return -1 if the function fails
	int AddCombination( ZBBPCombinationProperties* pProperty );

	// Delete a combination
	bool DeleteCombination( size_t Index );
	bool DeleteCombination( ZBBPCombinationProperties* pProperty );

	// Return true if the combination name already exists
	bool CombinationNameExist( const CString Name ) const;

	// Return the next valid name
	CString GetNextCombinationValidName() const;

	// Build the string with all available deliverables
	CString GetAvailableDeliverables( const CString AllDeliverables ) const;

	// Build the string with all allocated deliverables
	CString GetAllocatedDeliverables() const;

	// Return true if a specific deliverable is in the specified string
	bool IsDeliverableInString( const CString Deliverables, const CString Value ) const;

	// Retreive the right combination properties containing a specific deliverable
	ZBBPCombinationProperties* LocateCombinationOfDeliverable( const CString DeliverableName ) const;

	// Retreive the right combination properties index containing a specific deliverable
	// if not found, return -1
	int LocateCombinationIndexOfDeliverable( const CString DeliverableName ) const;

	// Retreive the right combination properties containing a specific master
	ZBBPCombinationProperties* LocateCombinationOfMaster( const CString Master ) const;

	// Retreive the right combination properties index containing a specific master
	// if not found, return -1
	int LocateCombinationIndexOfMaster( const CString Master ) const;

	// Replace an old deliverable by a new one
	// return true if done
	bool ReplaceDeliverable( const CString OldDeliverableName, const CString NewDeliverableName );

	// Delete a deliverable from all combinations, including the master
	// return true if done
	bool DeleteDeliverableFromAllCombinations( const CString DeliverableName );

	ZBBPCombinationPropertiesSet& GetCombinationSet()
	{
		return m_Set;
	};

	// Return the counter of combinations
	size_t GetCombinationCount() const 
	{
		return m_Set.GetSize();
	};

	ZBBPCombinationProperties* GetProperty( size_t Index ) const
	{
		if ( Index < GetCombinationCount() )
		{
			return m_Set.GetAt( Index );
		}

		return NULL;
	};

	void RemoveAllCombinations();

	// Gets the combination name at the specific Index.
	CString GetCombinationName( size_t Index ) const;

	//@cmember
	// Sets the combination name at the specific Index.
	void SetCombinationName( size_t Index, CString Value );

	//@cmember
	// Gets the list of deliberables at the specific Index.
	CString GetCombinationDeliverables(size_t Index) const;

	//@cmember
	/* Sets the list of deliberables at the specific Index. */
	void SetCombinationDeliverables( size_t Index, CString Value );

	//@cmember
	// Add a deliverable to the list of deliberables at the specific Index.
	bool AddCombinationDeliverable( size_t Index, CString Value );

	//@cmember
	// Remove a deliverable to the list of deliberables at the specific Index.
	bool RemoveCombinationDeliverable( size_t Index, CString Value );

	//@cmember
	// Remove all deliverables to the list of deliberables at the specific Index.
	bool RemoveAllCombinationDeliverable( size_t Index );

	//@cmember
	// Gets the combination percentage at the specific Index.
	float GetCombinationActivationPerc( size_t Index ) const;

	//@cmember
	// Sets the combination percentage at the specific Index.
	void SetCombinationActivationPerc( size_t Index, const float value );

	// Gets the combination master name at the specific Index.
	CString GetCombinationMaster( size_t Index ) const;

	//@cmember
	// Sets the combination master name at the specific Index.
	void SetCombinationMaster( size_t Index, CString Value );

	// Serializes the combinations.
	virtual void Serialize( CArchive& ar );

private:

	CODSymbolComponent*				m_pParent;
	ZBBPCombinationPropertiesSet	m_Set;
};

#endif // !defined(AFX_ZBProcCombinations_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)