// ******************************************************************************************************
// *										   Classe ZDHtmlFile										*
// ******************************************************************************************************
// * Cette classe effectue les opération de base pour la manipulation de fichiers html.					*
// ******************************************************************************************************

#if !defined(AFX_ZDHTMLFILE_H__FD01758E_A71B_4991_A12C_0A6DE2D381EF__INCLUDED_)
#define AFX_ZDHTMLFILE_H__FD01758E_A71B_4991_A12C_0A6DE2D381EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZWEBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 26 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZDHtmlFile
{
public:

	ZDHtmlFile( CString Filename = _T( "" ) );
	virtual ~ZDHtmlFile();

	// Create the HTML file class.
	virtual BOOL Create( CString Filename );

	// Returns one line of the file buffer.
	// Once the return value is zero, the file has been
	// completely processed.
	// If the return code is -1, an error occured.
	int ReadLine ( CString& Line, bool RemoveNewLineChar = false );

	// Writes one line of the file buffer.
	BOOL WriteLine( CString& Line, bool AddNewLineChar = false );

	// Open the file in write mode with creation.
	BOOL OpenFileCreate();

	// Open the file in read mode.
	BOOL OpenFileRead();

	// Close the file.
	BOOL CloseFile();

	//////////////////////////////////////////////////////////////////////
	// Writing information operators
	ZDHtmlFile& operator<<( const char* cpChar );
	ZDHtmlFile& operator<<( float value );
	ZDHtmlFile& operator<<( double value );
	ZDHtmlFile& operator<<( DWORD value );
	ZDHtmlFile& operator<<( UINT value );
	ZDHtmlFile& operator<<( WORD value );
	ZDHtmlFile& operator<<( short value );
	ZDHtmlFile& operator<<( LONG value );

private:

	ZDHtmlFile( const ZDHtmlFile &right );

	const ZDHtmlFile & operator=( const ZDHtmlFile &right );

	// Read a char buffer from the file.
	// Once the return value is zero, the file has been
	// completely processed.
	// If the return code is -1, an error occured.
	int ReadFileBuffer();

private:

	// Defines the filename used to import/export the information
	CString	m_Filename;

	// CFile object
	CFile	m_File;

	// This pointer is used when extracting the line from the file.
	char*	m_pCurrent;

	// Pointer to the next valid return line.
	char*	m_pNext;

	// Used to read information from file.
	char	m_FileBuffer[300];
};

#endif // !defined(AFX_ZDHTMLFILE_H__FD01758E_A71B_4991_A12C_0A6DE2D381EF__INCLUDED_)