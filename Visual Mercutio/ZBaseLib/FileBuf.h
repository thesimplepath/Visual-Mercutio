//## begin module%37F64290030B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%37F64290030B.cm

//## begin module%37F64290030B.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%37F64290030B.cp

//## Module: FileBuf%37F64290030B; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FileBuf.h

#ifndef FileBuf_h
#define FileBuf_h 1

//## begin module%37F64290030B.additionalIncludes preserve=no
//## end module%37F64290030B.additionalIncludes

//## begin module%37F64290030B.includes preserve=yes
// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%37F64290030B.includes

// File
#include "File.h"

// Mfc
#include "Mfc.h"

//## begin module%37F64290030B.declarations preserve=no
//## end module%37F64290030B.declarations

//## begin module%37F64290030B.additionalDeclarations preserve=yes
#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif
//## end module%37F64290030B.additionalDeclarations

// JMR-MODIF - Le 27 juin 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//## Class: ZBFileBuffer%37F63DEC0032
// This class encapsulates a file.
//## Category: ZBaseLib::Document classes%37E93F0B00CB
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%37F643270380;ZFile { -> }

class AFX_EXT_CLASS ZBFileBuffer : public CObject	//## Inherits: <unnamed>%37F641E80269
{
public:

	//## begin ZBFileBuffer%37F63DEC0032.initialDeclarations preserve=yes
	// Inherited feature
	typedef CObject inherited;
	//## end ZBFileBuffer%37F63DEC0032.initialDeclarations

protected:

	//## begin ZBFileBuffer%37F63DEC0032.initialDeclarations preserve=yes
	DECLARE_SERIAL( ZBFileBuffer )
	//## end ZBFileBuffer%37F63DEC0032.initialDeclarations

public:

	//## Constructors (generated)
	ZBFileBuffer( const ZBFileBuffer &right );

	//## Constructors (specified)
	//## Operation: ZBFileBuffer%938884129
	// The default constructor.
	ZBFileBuffer( const CString Filename = _T( "" ) );

	//## Operation: ZBFileBuffer%938884130
	// The default constructor.
	ZBFileBuffer( ZFile& File );

	//## Destructor (generated)
	virtual ~ZBFileBuffer();

	//## Assignment Operation (generated)
	const ZBFileBuffer & operator=( const ZBFileBuffer &right );

//## Other Operations (specified)
public:

	//## Operation: CreateBufferFromFile%938884131
	// From a file, create the class.
	BOOL CreateBufferFromFile( const CString Filename );

	//## Operation: CreateBufferFromFile%938884132
	// From a file, create the class.
	BOOL CreateBufferFromFile( ZFile& File );

	//## Operation: CreateBufferFromFile%938933073
	// From a file, create the class.
	BOOL CreateBufferFromFile();

	//## Operation: CreateFileFromBuffer%938884133
	// Create a file based on the file buffer. This function
	// returns the filename just created.
	CString CreateFileFromBuffer();

	//## Operation: CreateFileFromBuffer%938933074
	// Create a file based on the file buffer. This function
	// returns the filename just created.
	CString CreateFileFromBuffer( const CString Filename );

	//## Operation: CreateFileFromBuffer%938933075
	// Create a file based on the file buffer. This function
	// returns the filename just created.
	CString CreateFileFromBuffer( ZFile& File );

	//## Operation: CreateTemporaryFileFromBuffer%938959772
	// Create a file based on the file buffer. This function
	// returns the filename just created.
	CString CreateTemporaryFileFromBuffer();

	//## Operation: GetFileBuffer%938884139
	// Return the file buffer.
	void* GetFileBuffer();

	//## Operation: Clear%938884137
	// Clear the class.
	void Clear();

	//## Operation: Clone%938884138
	// Clone this.
	ZBFileBuffer* Clone();

	//## Operation: operator >>%938884134
	// Store from the archive to the object Stamp.
	AFX_EXT_API friend CArchive& operator >> ( CArchive& ar, ZBFileBuffer& FileBuffer );

	//## Operation: operator <<%938884135
	// Store the object Stamp to the archive.
	AFX_EXT_API friend CArchive& operator << ( CArchive& ar, ZBFileBuffer& FileBuffer );

	//## Operation: Serialize%938884136
	// Serialize file buffer information.
	virtual void Serialize( CArchive& ar );

//## Get and Set Operations for Class Attributes (generated)
public:

	//## Attribute: BufferSize%37F6FBA50147
	// Represents the buffer size.
	const size_t& GetBufferSize() const;

// Additional Public Declarations
public:

	//## begin ZBFileBuffer%37F63DEC0032.public preserve=yes
	//## end ZBFileBuffer%37F63DEC0032.public

// Additional Protected Declarations
protected:

	//## begin ZBFileBuffer%37F63DEC0032.protected preserve=yes
	//## end ZBFileBuffer%37F63DEC0032.protected

//## implementation
private:

	// Additional Implementation Declarations
	//## begin ZBFileBuffer%37F63DEC0032.implementation preserve=yes
	//## end ZBFileBuffer%37F63DEC0032.implementation

// Data Members for Class Attributes
private:

	//## Attribute: FileBuffer%37F6414A033E
	// The file buffer containing the file contents.
	//## begin ZBFileBuffer::FileBuffer%37F6414A033E.attr preserve=no  private: void* {U}
	void* m_FileBuffer;
	//## end ZBFileBuffer::FileBuffer%37F6414A033E.attr

	//## Attribute: File%37F642E2039F
	// Keep the filename.
	//## begin ZBFileBuffer::File%37F642E2039F.attr preserve=no  private: ZFile {U}
	ZFile m_File;
	//## end ZBFileBuffer::File%37F642E2039F.attr

	//## begin ZBFileBuffer::BufferSize%37F6FBA50147.attr preserve=no  public: size_t {U}
	size_t m_BufferSize;
	//## end ZBFileBuffer::BufferSize%37F6FBA50147.attr

	// Additional Private Declarations
	//## begin ZBFileBuffer%37F63DEC0032.private preserve=yes
	//## end ZBFileBuffer%37F63DEC0032.private
};

//## begin ZBFileBuffer%37F63DEC0032.postscript preserve=yes
//## end ZBFileBuffer%37F63DEC0032.postscript

// Class ZBFileBuffer

//## Other Operations (inline)
inline void* ZBFileBuffer::GetFileBuffer()
{
	//## begin ZBFileBuffer::GetFileBuffer%938884139.body preserve=yes
	return m_FileBuffer;
	//## end ZBFileBuffer::GetFileBuffer%938884139.body
}

//## Get and Set Operations for Class Attributes (inline)
inline const size_t& ZBFileBuffer::GetBufferSize() const
{
	//## begin ZBFileBuffer::GetBufferSize%37F6FBA50147.get preserve=no
	return m_BufferSize;
	//## end ZBFileBuffer::GetBufferSize%37F6FBA50147.get
}

//## begin module%37F64290030B.epilog preserve=yes
//## end module%37F64290030B.epilog

#endif