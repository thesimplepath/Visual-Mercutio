// ******************************************************************************************************
// *                                           Classe ZDTextFile                                        *
// ******************************************************************************************************
// * JMR-MODIF - Le 27 juin 2007 - Ajout de la classe ZDTextFile.                                        *
// ******************************************************************************************************
// * Cette classe effectue les opération de base pour la manipulation de fichiers textes.                *
// ******************************************************************************************************

#if !defined(AFX_ZDTEXTFILE_H__FD01758E_A71B_4991_A12C_0A6DE2D381EF__INCLUDED_)
#define AFX_ZDTEXTFILE_H__FD01758E_A71B_4991_A12C_0A6DE2D381EF__INCLUDED_

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

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZDTextFile
{
public:

    ZDTextFile( CString Filename = _T( "" ) );
    virtual ~ZDTextFile();

    // Open the text file class in write mode.
    virtual BOOL OpenWrite( CString Filename );

    // Open the text file class in read mode.
    virtual BOOL OpenRead( CString Filename );

    // Returns one line of the file buffer.
    // Once the return value is zero, the file has been
    // completely processed.
    // If the return code is -1, an error occured.
    int ReadLine( CString& Line, bool RemoveNewLineChar = false );

    // Writes one line of the file buffer.
    BOOL WriteLine( CString& Line, bool AddNewLineChar = false );

    // Open the file in write mode with creation.
    BOOL OpenFileWrite();

    // Open the file in read mode.
    BOOL OpenFileRead();

    // Close the file.
    BOOL CloseFile();

    //////////////////////////////////////////////////////////////////////
    // Writing information operators
    ZDTextFile& operator<<( const char* cpChar );
    ZDTextFile& operator<<( float value );
    ZDTextFile& operator<<( double value );
    ZDTextFile& operator<<( DWORD value );
    ZDTextFile& operator<<( UINT value );
    ZDTextFile& operator<<( WORD value );
    ZDTextFile& operator<<( short value );
    ZDTextFile& operator<<( LONG value );

    ZDTextFile& operator>>( CString& value );

private:

    ZDTextFile( const ZDTextFile &right );

    const ZDTextFile & operator=( const ZDTextFile &right );

    // Read a char buffer from the file.
    // Once the return value is zero, the file has been
    // completely processed.
    // If the return code is -1, an error occured.
    int ReadFileBuffer();

private:

    // Defines the filename used to import/export the information
    CString    m_Filename;

    // CFile object
    CFile    m_File;

    // This pointer is used when extracting the line from the file.
    char*    m_pCurrent;

    // Pointer to the next valid return line.
    char*    m_pNext;

    // Used to read information from file.
    char    m_FileBuffer[300];
};

#endif // !defined(AFX_ZDTEXTFILE_H__FD01758E_A71B_4991_A12C_0A6DE2D381EF__INCLUDED_)