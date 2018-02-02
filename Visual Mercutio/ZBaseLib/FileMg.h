//## begin module%36754E7300B0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%36754E7300B0.cm

//## begin module%36754E7300B0.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%36754E7300B0.cp

//## Module: FileMg%36754E7300B0; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FileMg.h

#ifndef FileMg_h
#define FileMg_h 1

//## begin module%36754E7300B0.additionalIncludes preserve=no
//## end module%36754E7300B0.additionalIncludes

//## begin module%36754E7300B0.includes preserve=yes
// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%36754E7300B0.includes

// File
#include "File.h"

// Mfc
#include "Mfc.h"

//## begin module%36754E7300B0.declarations preserve=no
//## end module%36754E7300B0.declarations

//## begin module%36754E7300B0.additionalDeclarations preserve=yes
#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif
//## end module%36754E7300B0.additionalDeclarations

// JMR-MODIF - Le 27 juin 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//## Class: ZFileManager%37A8A55202C9
// Contains a list of files. Implement methods to copy,
// move, delete files.
//## Category: ZBaseLib::File \rClasses%37A8A5450311
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%37A8A552028D;ZFile { -> }

class AFX_EXT_CLASS ZFileManager : public CObject	//## Inherits: <unnamed>%37A8A55202DD
{
public:

	//## begin ZFileManager%37A8A55202C9.initialDeclarations preserve=yes
	DECLARE_SERIAL( ZFileManager )

	// Inherited feature
	typedef CObject inherited;
	//## end ZFileManager%37A8A55202C9.initialDeclarations

public:

	//## Constructors (generated)
	ZFileManager();

	//## Destructor (generated)
	~ZFileManager();

	//## Other Operations (specified)
	//## Operation: Serialize%938959775
	// Serialization function required for MFC mecanism.
	virtual void Serialize( CArchive& ar );

	//## Operation: AddFile%938959776
	// Add a new file.
	void AddFile( CString FileName, AttachementType Attachement = InsertedFile );

	//## Operation: AddFile%938959785
	// Add a new file.
	void AddFile( ZFile* File );

	//## Operation: GetCount%938959786
	// Return the number of elements of the History manager.
	size_t GetCount();

	//## Operation: RemoveAllFiles%938959787
	// Remove all files.
	void RemoveAllFiles();

	//## Operation: GetAt%938959788
	// Returns the file pointer at the index position.
	ZFile* GetAt( int Index );

	//## Operation: RemoveFile%938959777
	// Remove a specific file. Specify the index position.
	BOOL RemoveFile( int Index );

	//## Operation: RemoveFile%938959778
	// Remove a specific file. Specify the index position.
	BOOL RemoveFile( ZFile* File );

	//## Operation: RemoveFile%938959779
	// Remove a specific file. Specify the index position.
	BOOL RemoveFile( const CString& FileName );

	//## Operation: FindFile%938959780
	// Search if a specific file exists.
	ZFile* FindFile( const CString& FileName );

	//## Operation: FindFile%938959781
	// Search if a specific file exists.
	ZFile* FindFile( ZFile* File );

	//## Operation: GetTemporaryFileName%938959782
	// Creates a temporary filename. It is possible to specify:
	//	- the drive
	//	- the directory
	//	- the start filename
	//	- the extension
	CString GetTemporaryFileName( char drive = 0, CString prefix = _T( "" ) );

	//## Operation: GetTemporaryFileName%938959783
	// Creates a temporary filename. It is possible to specify:
	//	- the drive
	//	- the directory
	//	- the start filename
	//	- the extension
	CString GetTemporaryFileName( CString path		= _T( "" ),
								  CString prefix	= _T( "" ),
								  CString ext		= _T( "" ) );

	//## Operation: GetTemporaryPath%938959784
	CString GetTemporaryPath();

	// Additional Public Declarations
	//## begin ZFileManager%37A8A55202C9.public preserve=yes
	//## end ZFileManager%37A8A55202C9.public

// Additional Protected Declarations
protected:

	//## begin ZFileManager%37A8A55202C9.protected preserve=yes
	//## end ZFileManager%37A8A55202C9.protected

private:

	//## Constructors (generated)
	ZFileManager( const ZFileManager &right );

	//## Assignment Operation (generated)
	const ZFileManager & operator=( const ZFileManager &right );

// Implementation
private:

	// Additional Implementation Declarations
	//## begin ZFileManager%37A8A55202C9.implementation preserve=yes
	//## end ZFileManager%37A8A55202C9.implementation

// Data Members for Class Attributes
private:

	//## Attribute: FileArray%37A8A5530150
	// Contains the file.
	//## begin ZFileManager::FileArray%37A8A5530150.attr preserve=no  public: CObArray {U} 
	CObArray m_FileArray;
	//## end ZFileManager::FileArray%37A8A5530150.attr

	// Additional Private Declarations
	//## begin ZFileManager%37A8A55202C9.private preserve=yes
	//## end ZFileManager%37A8A55202C9.private
};

//## begin ZFileManager%37A8A55202C9.postscript preserve=yes
//## end ZFileManager%37A8A55202C9.postscript

//## Other Operations (inline)
inline void ZFileManager::AddFile( ZFile* File )
{
	//## begin ZFileManager::AddFile%938959785.body preserve=yes
	m_FileArray.Add( (CObject*)File );
	//## end ZFileManager::AddFile%938959785.body
}

inline size_t ZFileManager::GetCount()
{
	//## begin ZFileManager::GetCount%938959786.body preserve=yes
	return m_FileArray.GetSize();
	//## end ZFileManager::GetCount%938959786.body
}

inline void ZFileManager::RemoveAllFiles()
{
	//## begin ZFileManager::RemoveAllFiles%938959787.body preserve=yes
	for ( size_t i = 0; i < GetCount(); ++i )
	{
		delete GetAt( i );
	}

	m_FileArray.RemoveAll();
	//## end ZFileManager::RemoveAllFiles%938959787.body
}

inline ZFile* ZFileManager::GetAt( int Index )
{
	//## begin ZFileManager::GetAt%938959788.body preserve=yes
	return (ZFile*)m_FileArray.GetAt( Index );
	//## end ZFileManager::GetAt%938959788.body
}

//## begin module%36754E7300B0.epilog preserve=yes
//## end module%36754E7300B0.epilog

#endif

// Detached code regions:
// WARNING: this code will be lost if code is regenerated.

#if 0
//## begin ZFileManager%36754E300385.initialDeclarations preserve=no
//## end ZFileManager%36754E300385.initialDeclarations

//## begin ZFileManager::AddFile%913659119.body preserve=no
//## end ZFileManager::AddFile%913659119.body

//## begin ZFileManager::GetCount%913659120.body preserve=no
//## end ZFileManager::GetCount%913659120.body

//## begin ZFileManager::RemoveAllFiles%913659121.body preserve=no
//## end ZFileManager::RemoveAllFiles%913659121.body

//## begin ZFileManager::GetAt%913659122.body preserve=no
//## end ZFileManager::GetAt%913659122.body
#endif