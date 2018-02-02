/************************************************************************************************************
 *													Classe ZFile											*
 ************************************************************************************************************
 * Cette classe fournit les outils concernant les opérations de base sur les fichiers, tels que le test de	*
 * l'existence d'un fichier, etc...																			*
 ************************************************************************************************************/

//## begin module%36754E5F004D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%36754E5F004D.cm

//## begin module%36754E5F004D.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%36754E5F004D.cp

//## Module: File%36754E5F004D; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\File.h

#ifndef File_h
#define File_h 1

//## begin module%36754E5F004D.additionalIncludes preserve=no
//## end module%36754E5F004D.additionalIncludes

//## begin module%36754E5F004D.includes preserve=yes
// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%36754E5F004D.includes

// Mfc
#include "Mfc.h"
//## begin module%36754E5F004D.declarations preserve=no
//## end module%36754E5F004D.declarations

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 24 avril 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//## begin module%36754E5F004D.additionalDeclarations preserve=yes
enum AttachementType
{
	InsertedFile,
	HyperLinkFile,
	IncludeFileDynamic,
	AttachementUndefined
};
//## end module%36754E5F004D.additionalDeclarations

//## Class: ZFile%37A8A5510200
// Implements a file.
//## Category: ZBaseLib::File \rClasses%37A8A5450311
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZFile : public CObject	//## Inherits: <unnamed>%37A8A5510264
{
	//## begin ZFile%37A8A5510200.initialDeclarations preserve=yes
	DECLARE_SERIAL( ZFile )

public:

	// Inherited feature
	typedef CObject inherited;
	//## end ZFile%37A8A5510200.initialDeclarations

public:

	//## Constructors (generated)
	ZFile();
	ZFile( const ZFile &right );

	//## Constructors (specified)
	//## Operation: ZFile%933795303
	//	The default contructor.
	ZFile( CString FileName, AttachementType Attachement = InsertedFile );

	//## Destructor (generated)
	~ZFile();

	//## Assignment Operation (generated)
	const ZFile& operator=( const ZFile &right );

	//## Equality Operations (generated)
	int operator==( const ZFile &right ) const;
	int operator!=( const ZFile &right ) const;

	//## Other Operations (specified)
	//## Operation: ReBuild%940749602
	// ReBuild the filename.
	void ReBuild();

	//## Operation: SetCompleteFileName%933795304
	// Sets the complete filename.
	void SetCompleteFileName( const CString value, AttachementType Attachement = InsertedFile );

	//## Operation: GetCompleteFileName%933795305
	// Gets the complete filename.
	CString GetCompleteFileName();

	//## Operation: SetFileName%933795306
	// Sets the filename and rebuild the complete filename.
	void SetFileName( const CString value, AttachementType Attachement = InsertedFile );

	//## Operation: GetFileName%933795307
	// Gets the filename.
	CString GetFileName();

	//## Operation: SetFilePath%933795308
	// Sets the filename path and rebuild the complete filename.
	void SetFilePath( const CString value );

	//## Operation: GetFilePath%933795309
	// Gets the filename path.
	CString GetFilePath();

	//## Operation: SetFileDrive%933795310
	// Sets the filename drive and rebuild the complete filename.
	void SetFileDrive( const char value );

	//## Operation: GetFileDrive%933795311
	// Gets the filename drive.
	const char GetFileDrive();

	//## Operation: operator >>%933795312
	// Store from the archive to the object Stamp.
	AFX_EXT_API friend CArchive& operator >> ( CArchive& ar, ZFile& File );

	//## Operation: operator <<%933795313
	// Store the object Stamp to the archive.
	AFX_EXT_API friend CArchive& operator << ( CArchive& ar, ZFile& File );

	//## Operation: Clone%933795314
	// Clone the file object.
	ZFile* Clone();

	//## Operation: GetDisplayName%933795315
	CString GetDisplayName();

	//## Operation: GetIconIndex%933795316
	int GetIconIndex();

	//## Operation: GetFileTitle%933795317
	CString GetFileTitle();

	//## Operation: GetFileExt%933795318
	CString GetFileExt();

	//## Operation: GetDescription%933795319
	CString GetDescription();

	//## Operation: Exist%933795320
	static BOOL Exist( CString Filename );
	BOOL Exist();

	//## Operation: IsReadOnly%941091645
	// Return true if the file is read-only.
	BOOL IsReadOnly();

	//## Operation: SetReadOnly%941091646
	// Set the read-only flag, dependent of the parameter.
	BOOL SetReadOnly( BOOL ReadOnly = TRUE );

	//## Operation: IsArchive%941091647
	// Return true if the file is archive.
	BOOL IsArchive();

	//## Operation: SetArchive%941091648
	// Set the archive flag, dependent of the parameter.
	BOOL SetArchive( BOOL Archive = TRUE );

	static BOOL GetLastWriteTime( CString Filename, SYSTEMTIME& tm );
	BOOL GetLastWriteTime( SYSTEMTIME& tm );

	//## Get and Set Operations for Class Attributes (generated)

	//## Attribute: AttachementType%37A8A5520247
	const AttachementType GetAttachementType() const;
	void SetAttachementType( AttachementType value );

	// Additional Public Declarations
	//## begin ZFile%37A8A5510200.public preserve=yes
	//## end ZFile%37A8A5510200.public

protected:

	// Data Members for Class Attributes

	//## Attribute: FileName%37A8A552022A
	// The complete filename.
	//## begin ZFile::FileName%37A8A552022A.attr preserve=no  public: CString {U}
	CString m_FileName;
	//## end ZFile::FileName%37A8A552022A.attr

	// Additional Protected Declarations
	//## begin ZFile%37A8A5510200.protected preserve=yes
	//## end ZFile%37A8A5510200.protected

private:

	// Data Members for Class Attributes

	//## begin ZFile::AttachementType%37A8A5520247.attr preserve=no  public: AttachementType {U}
	AttachementType m_AttachementType;
	//## end ZFile::AttachementType%37A8A5520247.attr

	//## Attribute: szDrive%37A8A5520251
	// contains the drive.
	//## begin ZFile::szDrive%37A8A5520251.attr preserve=no  private: char[_MAX_DRIVE] {U}
	char m_szDrive[_MAX_DRIVE];
	//## end ZFile::szDrive%37A8A5520251.attr

	//## Attribute: szDir%37A8A5520252
	// contains the directory.
	//## begin ZFile::szDir%37A8A5520252.attr preserve=no  private: char[_MAX_DIR] {U}
	char m_szDir[_MAX_DIR];
	//## end ZFile::szDir%37A8A5520252.attr

	//## Attribute: szFname%37A8A5520253
	// contains the filename.
	//## begin ZFile::szFname%37A8A5520253.attr preserve=no  private: char[_MAX_FNAME] {U}
	char m_szFname[_MAX_FNAME];
	//## end ZFile::szFname%37A8A5520253.attr

	//## Attribute: szExt%37A8A5520283
	// contains the extension.
	//## begin ZFile::szExt%37A8A5520283.attr preserve=no  private: char[_MAX_EXT] {U}
	char m_szExt[_MAX_EXT];
	//## end ZFile::szExt%37A8A5520283.attr

	// Additional Private Declarations
	//## begin ZFile%37A8A5510200.private preserve=yes
	//## end ZFile%37A8A5510200.private

private:

	//## implementation
	static HANDLE GetFileHandle ( CString Filename );
};

//## begin ZFile%37A8A5510200.postscript preserve=yes
//## end ZFile%37A8A5510200.postscript

// Class ZFile

//## Other Operations (inline)
inline ZFile* ZFile::Clone()
{
	//## begin ZFile::Clone%933795314.body preserve=yes
	ZFile* pFile = new ZFile( *this );
	return pFile;
	//## end ZFile::Clone%933795314.body
}

//## Get and Set Operations for Class Attributes (inline)
inline const AttachementType ZFile::GetAttachementType() const
{
	//## begin ZFile::GetAttachementType%37A8A5520247.get preserve=no
	return m_AttachementType;
	//## end ZFile::GetAttachementType%37A8A5520247.get
}

inline void ZFile::SetAttachementType( AttachementType value )
{
	//## begin ZFile::SetAttachementType%37A8A5520247.set preserve=no
	m_AttachementType = value;
	//## end ZFile::SetAttachementType%37A8A5520247.set
}

#endif