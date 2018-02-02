//## begin module%37EC7D040335.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%37EC7D040335.cm

//## begin module%37EC7D040335.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%37EC7D040335.cp

//## Module: FieldRep%37EC7D040335; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FieldRep.h

#ifndef FieldRep_h
#define FieldRep_h 1

//## begin module%37EC7D040335.additionalIncludes preserve=no
//## end module%37EC7D040335.additionalIncludes

//## begin module%37EC7D040335.includes preserve=yes
#ifdef _AFXEXT
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
#endif
//## end module%37EC7D040335.includes

// GFldDoc
#include "GFldDoc.h"
//## begin module%37EC7D040335.declarations preserve=no
//## end module%37EC7D040335.declarations

//## begin module%37EC7D040335.additionalDeclarations preserve=yes
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
//## end module%37EC7D040335.additionalDeclarations

//## Class: ZBFieldRepository%37EC7ACB0296
//## Category: ZBaseLib::History Field manager%36347B0E0308
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%37EC7B880003;ZDGlobalFieldDocument { -> }

class AFX_EXT_CLASS ZBFieldRepository 
{
	//## begin ZBFieldRepository%37EC7ACB0296.initialDeclarations preserve=yes
	//## end ZBFieldRepository%37EC7ACB0296.initialDeclarations

public:
	
	//## Constructors (generated)
	ZBFieldRepository();

	//## Destructor (generated)
	~ZBFieldRepository();
	
	//## Other Operations (specified)
	//## Operation: InitializeEmpty%938959792
	// Initialize and empty repository.
	BOOL InitializeEmpty ();

	//## Operation: OpenRepository%938242425
	// Open and Initialize the field repository.
	BOOL OpenRepository ( const CString Filename, BOOL ReadOnly = TRUE );

	//## Operation: CloseRepository%938242426
	// Close the repository and if necessary, save changes.
	BOOL CloseRepository ();

	//## Operation: SaveRepositoryToFile%938959793
	// Save the repository to a file.
	BOOL SaveRepositoryToFile ( const CString Filename );

	//## Operation: ReloadRepository%939925866
	// Reload the repository.
	BOOL ReloadRepository ( BOOL SaveBefore = FALSE );

	//## Operation: AddFieldHistoryValue%938242427
	// Add a new historic value into the FieldHistoryArray.
	void AddFieldHistoryValue ( const CString& FieldName, const CString& Value );

	//## Operation: RemoveFieldHistory%938242428
	// Remove a specific historic value from the manager.
	BOOL RemoveFieldHistory ( const CString& FieldName );

	//## Operation: RemoveFieldHistoryValue%938242429
	// Remove a specific historic value from the manager.
	BOOL RemoveFieldHistoryValue ( const CString& FieldName, const CString& Value );

	//## Operation: FindFieldHistory%938242430
	// Search if a specific fields exists.
	ZAHistoryField* FindFieldHistory ( const CString& FieldName );

	//## Operation: GetFieldHistory%938242431
	// Get the pointer of the field history.
	CStringArray* GetFieldHistory ( const CString& FieldName );

	//## Operation: GetFieldHistoryCount%938242432
	// Return the number of elements of the History manager.
	size_t GetFieldHistoryCount ();

	//## Operation: GetFieldCount%938242433
	// Return the number of elements of the Global field
	// manager.
	size_t GetFieldCount ();

	//## Operation: AddField%938242434
	// Add a new field.
	// Returns the index of the added field.
	int AddField ( ZAObjectDefinition* Field );

	//## Operation: DeleteField%938242435
	// Delete a field.
	BOOL DeleteField ( const CString& Name );

	//## Operation: DeleteAllField%938242436
	// Delete all field.
	BOOL DeleteAllField ();

	//## Operation: FindField%938242437
	// Find if a field exists.
	ZAObjectDefinition* FindField ( const CString& Name );

	//## Operation: GetFieldAt%938242438
	// Get the object at a specific location.
	ZAObjectDefinition* GetFieldAt ( int Index );

	//## Operation: GetDescription%938242439
	// Get the description of a field.
	CString GetDescription ( const CString& Name );

	//## Operation: GetClassName%938242440
	// Get the class name of a field.
	CString GetClassName ( const CString& Name );

	//## Operation: GetFieldNameArray%938242441
	// Returns the fieldname array of all fields contained in
	// the manager.
	const CStringArray& GetFieldNameArray ();

	//## Operation: CopyFieldDefinition%938242442
	// Copy the field definition of the ObjectDefinition to the
	// PlanfinObject.
	void CopyFieldDefinition ( const CString Name, PlanFinObject* pObj, ZDDocument* pDoc );

	//## Operation: IsValid%938242444
	// If valid, return true.
	BOOL IsValid () const;

	//## Operation: Import%939069932
	// Import a field repository and merge fields with the
	// source.
	BOOL Import ( ZBFieldRepository& FieldRepository, BOOL ReplaceExisting = FALSE );

	// Additional Public Declarations
	//## begin ZBFieldRepository%37EC7ACB0296.public preserve=yes
	//## end ZBFieldRepository%37EC7ACB0296.public

protected:
	
	// Additional Protected Declarations
	//## begin ZBFieldRepository%37EC7ACB0296.protected preserve=yes
	//## end ZBFieldRepository%37EC7ACB0296.protected

private:
	
	//## Constructors (generated)
	ZBFieldRepository( const ZBFieldRepository &right );

	//## Assignment Operation (generated)
	const ZBFieldRepository & operator=( const ZBFieldRepository &right );

private:

	// Data Members for Class Attributes
	
	//## Attribute: GlobalFieldManager%37EC7B080171
	// This is the manager of global field definition.
	//## begin ZBFieldRepository::GlobalFieldManager%37EC7B080171.attr preserve=no  private: ZAGlobalFieldManager {U} 
	ZAGlobalFieldManager* m_GlobalFieldManager;
	//## end ZBFieldRepository::GlobalFieldManager%37EC7B080171.attr

	//## Attribute: HistoryValueManager%37EC7B0C01B3
	// This is the manager of history field values.
	//## begin ZBFieldRepository::HistoryValueManager%37EC7B0C01B3.attr preserve=no  private: ZAHistoryFieldManager {U} 
	ZAHistoryFieldManager* m_HistoryValueManager;
	//## end ZBFieldRepository::HistoryValueManager%37EC7B0C01B3.attr

	//## Attribute: Document%37EC7B51020D
	// The document used to serialize the history field manager
	// and the global repository manager.
	//## begin ZBFieldRepository::Document%37EC7B51020D.attr preserve=no  private: ZDGlobalFieldDocument {U}
	ZDGlobalFieldDocument* m_Document;
	//## end ZBFieldRepository::Document%37EC7B51020D.attr

	//## Attribute: ReadOnly%37EC7D6E025B
	// If open repository is read only.
	//## begin ZBFieldRepository::ReadOnly%37EC7D6E025B.attr preserve=no  private: BOOL {U}
	BOOL m_ReadOnly;
	//## end ZBFieldRepository::ReadOnly%37EC7D6E025B.attr

	//## Attribute: IsValid%37EC8726021C
	//## begin ZBFieldRepository::IsValid%37EC8726021C.attr preserve=no  private: BOOL {U} FALSE
	BOOL m_IsValid;
	//## end ZBFieldRepository::IsValid%37EC8726021C.attr

	//## Attribute: Filename%3806222900EE
	// Keeps the repository filename.
	//## begin ZBFieldRepository::Filename%3806222900EE.attr preserve=no  private: CString {U}
	CString m_Filename;
	//## end ZBFieldRepository::Filename%3806222900EE.attr

	// Additional Private Declarations
	//## begin ZBFieldRepository%37EC7ACB0296.private preserve=yes
	//## end ZBFieldRepository%37EC7ACB0296.private

private:  //## implementation
	
	// Additional Implementation Declarations
	//## begin ZBFieldRepository%37EC7ACB0296.implementation preserve=yes
	//## end ZBFieldRepository%37EC7ACB0296.implementation
};

//## begin ZBFieldRepository%37EC7ACB0296.postscript preserve=yes
//## end ZBFieldRepository%37EC7ACB0296.postscript

// Class ZBFieldRepository 

//## Other Operations (inline)
inline void ZBFieldRepository::AddFieldHistoryValue ( const CString& FieldName, const CString& Value )
{
	//## begin ZBFieldRepository::AddFieldHistoryValue%938242427.body preserve=yes
	if ( m_HistoryValueManager != NULL )
	{
		m_HistoryValueManager->AddFieldHistoryValue( FieldName, Value );
	}
	//## end ZBFieldRepository::AddFieldHistoryValue%938242427.body
}

inline BOOL ZBFieldRepository::RemoveFieldHistory ( const CString& FieldName )
{
	//## begin ZBFieldRepository::RemoveFieldHistory%938242428.body preserve=yes
	if ( m_HistoryValueManager != NULL )
	{
		return m_HistoryValueManager->RemoveFieldHistory( FieldName );
	}
	else return FALSE;
	//## end ZBFieldRepository::RemoveFieldHistory%938242428.body
}

inline BOOL ZBFieldRepository::RemoveFieldHistoryValue ( const CString& FieldName, const CString& Value )
{
	//## begin ZBFieldRepository::RemoveFieldHistoryValue%938242429.body preserve=yes
	if ( m_HistoryValueManager != NULL )
	{
		return m_HistoryValueManager->RemoveFieldHistoryValue( FieldName, Value );
	}
	else return FALSE;
	//## end ZBFieldRepository::RemoveFieldHistoryValue%938242429.body
}

inline ZAHistoryField* ZBFieldRepository::FindFieldHistory ( const CString& FieldName )
{
	//## begin ZBFieldRepository::FindFieldHistory%938242430.body preserve=yes
	if ( m_HistoryValueManager != NULL )
	{
		return m_HistoryValueManager->FindField( FieldName );
	}
	else return NULL;
	//## end ZBFieldRepository::FindFieldHistory%938242430.body
}

inline CStringArray* ZBFieldRepository::GetFieldHistory ( const CString& FieldName )
{
	//## begin ZBFieldRepository::GetFieldHistory%938242431.body preserve=yes
	if ( m_HistoryValueManager != NULL )
	{
		return m_HistoryValueManager->GetFieldHistory( FieldName );
	}
	else return NULL;
	//## end ZBFieldRepository::GetFieldHistory%938242431.body
}

inline size_t ZBFieldRepository::GetFieldHistoryCount ()
{
	//## begin ZBFieldRepository::GetFieldHistoryCount%938242432.body preserve=yes
	if ( m_HistoryValueManager != NULL )
	{
		return m_HistoryValueManager->GetCount();
	}
	else return 0;
	//## end ZBFieldRepository::GetFieldHistoryCount%938242432.body
}

inline size_t ZBFieldRepository::GetFieldCount ()
{
	//## begin ZBFieldRepository::GetFieldCount%938242433.body preserve=yes
	if ( m_GlobalFieldManager != NULL )
	{
		return m_GlobalFieldManager->GetCount();
	}
	else return 0;
	//## end ZBFieldRepository::GetFieldCount%938242433.body
}

inline int ZBFieldRepository::AddField ( ZAObjectDefinition* Field )
{
	//## begin ZBFieldRepository::AddField%938242434.body preserve=yes
	if ( m_GlobalFieldManager != NULL )
	{
		return m_GlobalFieldManager->AddField( Field );
	}
	else return 0;
	//## end ZBFieldRepository::AddField%938242434.body
}

inline BOOL ZBFieldRepository::DeleteField ( const CString& Name )
{
	//## begin ZBFieldRepository::DeleteField%938242435.body preserve=yes
	if ( m_GlobalFieldManager != NULL )
	{
		return m_GlobalFieldManager->DeleteField( Name );
	}
	else return FALSE;
	//## end ZBFieldRepository::DeleteField%938242435.body
}

inline BOOL ZBFieldRepository::DeleteAllField ()
{
	//## begin ZBFieldRepository::DeleteAllField%938242436.body preserve=yes
	if ( m_GlobalFieldManager != NULL )
	{
		return m_GlobalFieldManager->DeleteAllField();
	}
	else return FALSE;
	//## end ZBFieldRepository::DeleteAllField%938242436.body
}

inline ZAObjectDefinition* ZBFieldRepository::FindField ( const CString& Name )
{
	//## begin ZBFieldRepository::FindField%938242437.body preserve=yes
	if ( m_GlobalFieldManager != NULL )
	{
		return m_GlobalFieldManager->FindField( Name );
	}
	else return NULL;
	//## end ZBFieldRepository::FindField%938242437.body
}

inline ZAObjectDefinition* ZBFieldRepository::GetFieldAt ( int Index )
{
	//## begin ZBFieldRepository::GetFieldAt%938242438.body preserve=yes
	if ( m_GlobalFieldManager != NULL )
	{
		return m_GlobalFieldManager->GetAt( Index );
	}
	else return NULL;
	//## end ZBFieldRepository::GetFieldAt%938242438.body
}

inline CString ZBFieldRepository::GetDescription ( const CString& Name )
{
	//## begin ZBFieldRepository::GetDescription%938242439.body preserve=yes
	if ( m_GlobalFieldManager != NULL )
	{
		return m_GlobalFieldManager->GetDescription( Name );
	}
	else return "";
	//## end ZBFieldRepository::GetDescription%938242439.body
}

inline CString ZBFieldRepository::GetClassName ( const CString& Name )
{
	//## begin ZBFieldRepository::GetClassName%938242440.body preserve=yes
	if ( m_GlobalFieldManager != NULL )
	{
		return m_GlobalFieldManager->GetClassName( Name );
	}
	else return "";
	//## end ZBFieldRepository::GetClassName%938242440.body
}

inline const CStringArray& ZBFieldRepository::GetFieldNameArray ()
{
	//## begin ZBFieldRepository::GetFieldNameArray%938242441.body preserve=yes
	return m_GlobalFieldManager->GetFieldNameArray();
	//## end ZBFieldRepository::GetFieldNameArray%938242441.body
}

inline void ZBFieldRepository::CopyFieldDefinition ( const CString Name, PlanFinObject* pObj, ZDDocument* pDoc )
{
	//## begin ZBFieldRepository::CopyFieldDefinition%938242442.body preserve=yes
	if ( m_GlobalFieldManager != NULL )
	{
		m_GlobalFieldManager->CopyFieldDefinition( Name, pObj, pDoc );
	}
	//## end ZBFieldRepository::CopyFieldDefinition%938242442.body
}

inline BOOL ZBFieldRepository::IsValid () const
{
	//## begin ZBFieldRepository::IsValid%938242444.body preserve=yes
	return m_IsValid;
	//## end ZBFieldRepository::IsValid%938242444.body
}

//## begin module%37EC7D040335.epilog preserve=yes
//## end module%37EC7D040335.epilog

#endif