//## begin module%363481D50050.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%363481D50050.cm

//## begin module%363481D50050.cp preserve=no
//## end module%363481D50050.cp

//## Module: HistFMng%363481D50050; Package specification
//## Subsystem: ZFile modules%3620C63F0009
//## Source file: z:\adsoft~1\zfile\HistFMng.h

#ifndef HistFMng_h
#define HistFMng_h 1

//## begin module%363481D50050.additionalIncludes preserve=no
//## end module%363481D50050.additionalIncludes

//## begin module%363481D50050.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%363481D50050.includes

// Mfc
#include "Mfc.h"
// HistFld
#include "HistFld.h"
//## begin module%363481D50050.declarations preserve=no
//## end module%363481D50050.declarations

//## begin module%363481D50050.additionalDeclarations preserve=yes
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
//## end module%363481D50050.additionalDeclarations

//## Class: ZAHistoryFieldManager%36347DBE0290
//	Manage the field history for the document.
//## Category: PlanFin::History Field manager%36347B0E0308
//## Subsystem: ZFile modules%3620C63F0009
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3634896D0164;ZAHistoryField { -> }

class AFX_EXT_CLASS ZAHistoryFieldManager : public CObject  //## Inherits: <unnamed>%36347E1E02D4
{
protected:

	// Additional Protected Declarations
	//## begin ZAHistoryFieldManager%36347DBE0290.protected preserve=yes
	DECLARE_SERIAL( ZAHistoryFieldManager )
	//## end ZAHistoryFieldManager%36347DBE0290.protected

//## begin ZAHistoryFieldManager%36347DBE0290.initialDeclarations preserve=yes
public:

	// Inherited feature
	typedef CObject inherited;
	//## end ZAHistoryFieldManager%36347DBE0290.initialDeclarations

public:
	
	//## Constructors (generated)
	ZAHistoryFieldManager();

	//## Destructor (generated)
	~ZAHistoryFieldManager();

	//## Other Operations (specified)
	//## Operation: AddFieldHistoryValue%909410998
	// Add a new historic value into the FieldHistoryArray.
	void AddFieldHistoryValue ( const CString& FieldName, const CString& Value );

	//## Operation: RemoveFieldHistory%909410999
	// Remove a specific historic value from the manager.
	BOOL RemoveFieldHistory ( const CString& FieldName );

	//## Operation: RemoveFieldHistoryValue%909411000
	// Remove a specific historic value from the manager.
	BOOL RemoveFieldHistoryValue ( const CString& FieldName, const CString& Value );

	//## Operation: FindField%909411001
	// Search if a specific fields exists.
	ZAHistoryField* FindField ( const CString& FieldName );

	//## Operation: GetFieldHistory%909411002
	// Get the pointer of the field history.
	CStringArray* GetFieldHistory ( const CString& FieldName );

	//## Operation: Serialize%909411003
	// Serialization function required for MFC mecanism.
	virtual void Serialize ( CArchive& ar );

	//## Operation: GetCount%909411004
	// Return the number of elements of the History manager.
	size_t GetCount ();

	//## Operation: FreeList%909411005
	// remove the history.
	void FreeList ();

	// Additional Public Declarations

//## begin ZAHistoryFieldManager%36347DBE0290.public preserve=yes
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif
//## end ZAHistoryFieldManager%36347DBE0290.public

private:
	
	//## Constructors (generated)
	ZAHistoryFieldManager( const ZAHistoryFieldManager &right );

	//## Assignment Operation (generated)
	const ZAHistoryFieldManager & operator=( const ZAHistoryFieldManager &right );

private:

	// Data Members for Class Attributes

	//## Attribute: FieldHistoryArray%36347F620013
	// Contains all fields history.
	//## begin ZAHistoryFieldManager::FieldHistoryArray%36347F620013.attr preserve=no  public: CObArray {U} 
	CObArray m_FieldHistoryArray;
	//## end ZAHistoryFieldManager::FieldHistoryArray%36347F620013.attr

	// Additional Private Declarations
	//## begin ZAHistoryFieldManager%36347DBE0290.private preserve=yes
	//## end ZAHistoryFieldManager%36347DBE0290.private

private:  //## implementation
	
	// Additional Implementation Declarations
	//## begin ZAHistoryFieldManager%36347DBE0290.implementation preserve=yes
	//## end ZAHistoryFieldManager%36347DBE0290.implementation
};

//## begin ZAHistoryFieldManager%36347DBE0290.postscript preserve=yes
//## end ZAHistoryFieldManager%36347DBE0290.postscript

// Class ZAHistoryFieldManager 

//## Other Operations (inline)
inline size_t ZAHistoryFieldManager::GetCount ()
{
	//## begin ZAHistoryFieldManager::GetCount%909411004.body preserve=yes
	return m_FieldHistoryArray.GetSize();
	//## end ZAHistoryFieldManager::GetCount%909411004.body
}

//## begin module%363481D50050.epilog preserve=yes
//## end module%363481D50050.epilog
#endif