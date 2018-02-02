/////////////////////////////////////////////////////////////////////////////
//@doc ZBModuleVersion
//@module ZBModuleVersion.cpp | Implementation of the <c ZBModuleVersion> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 10/2002
// 
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ZBModuleVersion.h"

// JMR-MODIF - Le 28 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (en commentaires)

ZBModuleVersion::ZBModuleVersion()
{
	// RAW version info data
	m_pVersionInfo = NULL;
}

//////////////////
// Destroy: delete version info
//
ZBModuleVersion::~ZBModuleVersion()
{
	delete [] m_pVersionInfo;
}

//////////////////
// Get file version info for a given module
// Allocates storage for all info, fills "this" with
// VS_FIXEDFILEINFO, and sets codepage.
//
bool ZBModuleVersion::GetFileVersionInfo( LPCTSTR modulename )
{
	// Default = ANSI code page
	m_translation.charset = 1252;
	memset( (VS_FIXEDFILEINFO*)this, 0, sizeof( VS_FIXEDFILEINFO ) );

	// Get module handle
	TCHAR filename[_MAX_PATH];
	HMODULE hModule = ::GetModuleHandle( modulename );

	if ( hModule==NULL && modulename!=NULL )
	{
		return FALSE;
	}

	// Get module file name
	DWORD len = GetModuleFileName( hModule, filename, sizeof( filename ) / sizeof( filename[0] ) );

	if ( len <= 0 )
	{
		return FALSE;
	}

	// Read file version info
	DWORD dwDummyHandle; // will always be set to zero
	len = GetFileVersionInfoSize( filename, &dwDummyHandle );

	if ( len <= 0 )
	{
		return FALSE;
	}

	// Allocate version info
	m_pVersionInfo = new BYTE[len];

	if ( !::GetFileVersionInfo( filename, 0, len, m_pVersionInfo ) )
	{
		return FALSE;
	}

	LPVOID lpvi;
	UINT iLen;

	if ( !VerQueryValue(m_pVersionInfo, _T( "\\" ), &lpvi, &iLen ) )
	{
		return FALSE;
	}

	// Copy fixed info to myself, which am derived from VS_FIXEDFILEINFO
	*(VS_FIXEDFILEINFO*)this = *(VS_FIXEDFILEINFO*)lpvi;

	// Get translation info
	if ( VerQueryValue( m_pVersionInfo, _T( "\\VarFileInfo\\Translation" ), &lpvi, &iLen ) && iLen >= 4 )
	{
		m_translation = *(TRANSLATION*)lpvi;
		TRACE( _T( "code page = %d\n" ), m_translation.charset );
	}

	return dwSignature == VS_FFI_SIGNATURE;
}

//////////////////
// Get string file info.
// Key name is something like "CompanyName".
// returns the value as a CString.
//
CString ZBModuleVersion::GetValue( LPCTSTR lpKeyName )
{
	CString sVal;

	if ( m_pVersionInfo )
	{
		// To get a string value must pass query in the form
		//
		// "\StringFileInfo\<langID><codepage>\keyname"
		//
		 // where <langID><codepage> is the languageID concatenated with the
		 // code page, in hex. Wow.
		//
		CString query;

		query.Format( _T( "\\StringFileInfo\\%04x%04x\\%s" ),
					   m_translation.langID,
					   m_translation.charset,
					   lpKeyName);

		LPCTSTR		pVal;
		UINT		iLenVal;

		if ( VerQueryValue( m_pVersionInfo, (LPTSTR)(LPCTSTR)query, (LPVOID*)&pVal, &iLenVal ) )
		{
			sVal = pVal;
		}
	}

	return sVal;
}

// typedef for DllGetVersion proc
typedef HRESULT (CALLBACK* DLLGETVERSIONPROC)(DLLVERSIONINFO *);

/////////////////
// Get DLL Version by calling DLL's DllGetVersion proc
//
bool ZBModuleVersion::DllGetVersion( LPCTSTR modulename, DLLVERSIONINFO& dvi )
{
	HINSTANCE hinst = LoadLibrary( modulename );

	if ( !hinst )
	{
		return FALSE;
	}

	// Must use GetProcAddress because the DLL might not implement 
	// DllGetVersion. Depending upon the DLL, the lack of implementation of the 
	// function may be a version marker in itself.
	//
	DLLGETVERSIONPROC pDllGetVersion =
		(DLLGETVERSIONPROC)GetProcAddress( hinst, _T( "DllGetVersion" ) );

	if ( !pDllGetVersion )
	{
		return FALSE;
	}

	memset( &dvi, 0, sizeof( dvi ) );	// clear
	dvi.cbSize = sizeof( dvi );			// set size for Windows

	return SUCCEEDED( (*pDllGetVersion)( &dvi ) );
}
