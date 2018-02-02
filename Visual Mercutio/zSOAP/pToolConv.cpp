/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module XXXClass.cpp | Implementation of the <c XXXClass> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Gaya
// <nl>Created: 03/2002
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "zConversion\String16.h"
#include "zConversion\zUtf.h"
#include "zConversion\zIso8859.h"

// 0 = no, 1 = utf-8, 2 = iso8859
static int doCharacterConversionMethod = 1;

string base64encode( const unsigned char *pcBuffIn, long nLenIn );

// JMR-MODIF - Le 14 septembre 2005 - Ajout des décorations Unicode _T(), nettoyage du code inutile.(En commentaires)

////////////////////////////////////////////////////////////
// to xml (ansi7) string converter
string convertTo( String16 inStr )
{
	if ( inStr.length() ==0 )
	{
		return _T( "" );
	}

	string outStr = _T( "" );

	if ( doCharacterConversionMethod == 0 )
	{
		// Do not convert
		throw _T( "convertTo (0):not implemented" );
	}
	else if ( doCharacterConversionMethod == 1 )
	{
		// Convert utf8
		const wchar_t *ptr = inStr;

		// End of Temporary fix
		string tmp = zUtf::UTF16toUTF8( inStr );

		char xxx[111];
		sprintf( xxx, _T( "L=%d" ), tmp.length() );
		OutputDebugString( xxx );
		OutputDebugString( _T( "<\n" ) );

		outStr = base64encode( (unsigned char*)tmp.c_str(), tmp.length() );
	}
	else if ( doCharacterConversionMethod == 2 )
	{
		// Convert iso 8859
		throw _T( "convertTo(2):not implemented" );
	}

	return outStr;
}

////////////////////////////////////////////////////////////
// from xml (ansi7) string converter
String16 convertFrom( string inStr )
{
	if ( inStr.length() == 0 ) return String16( _T( "" ) );

	if ( doCharacterConversionMethod == 0 )
	{
		// Do not convert
		throw _T( "convertFrom (0):not implemented" );
	}
	else if ( doCharacterConversionMethod == 1 )
	{
		// Convert utf8
		return zUtf::UTF8toUTF16( inStr );
	}
	else if ( doCharacterConversionMethod == 2 )
	{
		// Convert iso 8859
		throw _T( "convertFrom (2):not implemented" );
	}

	return String16( _T( "" ) );
}
