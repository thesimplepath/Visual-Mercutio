/////////////////////////////////////////////////////////////////////////////
//@doc zIso8859
//@module zIso8859.cpp | Implementation of the <c zIso8859> class.
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

#include "zIso8859.h"

// JMR-MODIF - Le 10 janvier 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// ISO 8859 Converter

//ISO 8859 mapping table
class kl
{
public:

	kl( const char* k1, const char* k2 )
	{
		key1 = k1;
		key2 = k2;

		if ( k1 != NULL )
		{
			quickSearch += key1;
		}
	}

	static int convertAt( char car )
	{
		char tmp[2];

		tmp[0] = car;
		tmp[1] = 0;

		return quickSearch.find( tmp );
	}

public:

	const char* key1;
	const char* key2;

	static std::string quickSearch;
};

std::string kl::quickSearch = _T( "" );

//Mapping table
kl dictionary[] =
{
	kl( _T( "\x001" ), _T( "%#001" ) ),		kl( _T( "\x002" ), _T( "%#002" ) ),
	kl( _T( "\x003" ), _T( "%#003" ) ),		kl( _T( "\x004" ), _T( "%#004" ) ),
	kl( _T( "\x005" ), _T( "%#005" ) ),		kl( _T( "\x006" ), _T( "%#006" ) ),
	kl( _T( "\x007" ), _T( "%#007" ) ),		kl( _T( "\x008" ), _T( "%#008" ) ),
	kl( _T( "\x009" ), _T( "%#009" ) ),		kl( _T( "\x00a" ), _T( "%#010" ) ),
	kl( _T( "\x00b" ), _T( "%#011" ) ),		kl( _T( "\x00c" ), _T( "%#012" ) ),
	kl( _T( "\x00d" ), _T( "%#013" ) ),		kl( _T( "\x00e" ), _T( "%#014" ) ),
	kl( _T( "\x00f" ), _T( "%#015" ) ),		kl( _T( "\x010" ), _T( "%#016" ) ),
	kl( _T( "\x011" ), _T( "%#017" ) ),		kl( _T( "\x012" ), _T( "%#018" ) ),
	kl( _T( "\x013" ), _T( "%#019" ) ),		kl( _T( "\x014" ), _T( "%#020" ) ),
	kl( _T( "\x015" ), _T( "%#021" ) ),		kl( _T( "\x016" ), _T( "%#022" ) ),
	kl( _T( "\x017" ), _T( "%#023" ) ),		kl( _T( "\x018" ), _T( "%#024" ) ),
	kl( _T( "\x019" ), _T( "%#025" ) ),		kl( _T( "\x01a" ), _T( "%#026" ) ),
	kl( _T( "\x01b" ), _T( "%#027" ) ),		kl( _T( "\x01c" ), _T( "%#028" ) ),
	kl( _T( "\x01d" ), _T( "%#029" ) ),		kl( _T( "\x01e" ), _T( "%#030" ) ),
	kl( _T( "\x01f" ), _T( "%#031" ) ),

	kl( _T( "!" ), _T( "&excl;" ) ),		kl( _T( "\"" ), _T( "&quot;;" ) ),
	kl( _T( "#" ), _T( "&num;" ) ),			kl( _T( "$" ), _T( "&dollar;" ) ),
	kl( _T( "%" ), _T( "&percnt;" ) ),		kl( _T( "&" ), _T( "&amp;" ) ),
	kl( _T( "'" ), _T( "&apos;" ) ),		kl( _T( "(" ), _T( "&lpar;" ) ),
	kl( _T( ")" ), _T( "&rpar;" ) ),		kl( _T( "*" ), _T( "&ast;" ) ),
	kl( _T( "+" ), _T( "&plus;" ) ),		kl( _T( "," ), _T( "&comma;" ) ),
	kl( _T( "-" ), _T( "&minus;" ) ),		kl( _T( "." ), _T( "&period;" ) ),
	kl( _T( "/" ), _T( "&sol;" ) ),			kl( _T( ":" ), _T( "&colon;" ) ),
	kl( _T( ";" ), _T( "&semi;" ) ),		kl( _T( "<" ) , _T( "&lt;" ) ),
	kl( _T( "=" ), _T( "&equals;" ) ),		kl( _T( ">" ), _T( "&gt;" ) ),
	kl( _T( "?" ), _T( "&quest;" ) ),		kl( _T( "@" ) , _T( "&commat;" ) ),

	kl( _T( "[" ), _T( "&lsqb;" ) ),		kl( _T( "\\" ), _T( "&bsol;" ) ),
	kl( _T( "]" ), _T( "&rsqb;" ) ),		kl( _T( "^" ), _T( "&circ;" ) ),
	kl( _T( "_" ), _T( "&lowbar;" ) ),		kl( _T( "\x060" ), _T( "&grave;" ) ),

	kl( _T( "{" ), _T( "&lcub;" ) ),		kl( _T( "\x07c" ), _T( "&verbar;" ) ),
	kl( _T( "}" ), _T( "&rcub;" ) ),		kl( _T( "~" ), _T( "&tilde;" ) ),

	kl( _T( "\x082" ), _T( "&lsquor;" ) ),	kl( _T( "\x083" ), _T( "&fnof;" ) ),
	kl( _T( "\x084" ), _T( "&ldquor;" ) ),	kl( _T( "\x085" ), _T( "&hellip;" ) ),
	kl( _T( "\x086" ), _T( "&dagger;" ) ),	kl( _T( "\x087" ), _T( "&Dagger;" ) ),

	kl( _T( "\x089" ), _T( "&permil;" ) ),	kl( _T( "\x08a" ), _T( "&Scaron;" ) ),
	kl( _T( "\x08b" ), _T( "&lsaquo;" ) ),	kl( _T( "\x08c" ), _T( "&EOlig;" ) ),

	kl( _T( "\x091" ), _T( "&lsquo;" ) ),	kl( _T( "\x092" ), _T( "&rsquo;" ) ),
	kl( _T( "\x093" ), _T( "&ldquo;" ) ),	kl( _T( "\x094" ), _T( "&rdquo;" ) ),
	kl( _T( "\x095" ), _T( "&bull;" ) ),	kl( _T( "\x096" ), _T( "&ndash;" ) ),
	kl( _T( "\x097" ), _T( "&mdash;" ) ),	kl( _T( "\x098" ), _T( "&tilde;" ) ),

	kl( _T( "\x099" ), _T( "&trade;" ) ),	kl( _T( "\x09a" ), _T( "&scaron;" ) ),
	kl( _T( "\x09b" ), _T( "&rsaquo;" ) ),	kl( _T( "\x09c" ), _T( "&eolig;" ) ),
	kl( _T( "\x09f" ), _T( "&Yuml;" ) ),

	kl( _T( "\x0a0" ), _T( "&nbsp;" ) ),	kl( _T( "\x0a1" ), _T( "&iexcl;" ) ),
	kl( _T( "\x0a2" ), _T( "&cent;" ) ),	kl( _T( "\x0a3" ), _T( "&pound;" ) ),
	kl( _T( "\x0a4" ), _T( "&curren;" ) ),	kl( _T( "\x0a5" ), _T( "&yen;" ) ),
	kl( _T( "\x0a6" ), _T( "&brvbar;" ) ),	kl( _T( "\x0a7" ), _T( "&sect;" ) ),
	kl( _T( "\x0a8" ), _T( "&uml;" ) ),		kl( _T( "\x0a9" ), _T( "&copy;" ) ),
	kl( _T( "\x0aa" ), _T( "&ordf;" ) ),	kl( _T( "\x0ab" ), _T( "&laquo;" ) ),
	kl( _T( "\x0ac" ), _T( "&not;" ) ),		kl( _T( "\x0ad" ), _T( "&shy;" ) ),
	kl( _T( "\x0ae" ), _T( "&reg;" ) ),		kl( _T( "\x0af" ), _T( "&macr;" ) ),

	kl( _T( "\x0b0" ), _T( "&deg;" ) ),		kl( _T( "\x0b1" ), _T( "&plusmn;" ) ),
	kl( _T( "\x0b2" ), _T( "&sup2;" ) ),	kl( _T( "\x0b3" ), _T( "&sup3;" ) ),
	kl( _T( "\x0b4" ), _T( "&acute;" ) ),	kl( _T( "\x0b5" ), _T( "&micro;" ) ),
	kl( _T( "\x0b6" ), _T( "&para;" ) ),	kl( _T( "\x0b7" ), _T( "&middot;" ) ),
	kl( _T( "\x0b8" ), _T( "&cedil;" ) ),	kl( _T( "\x0b9" ), _T( "&sup1;" ) ),
	kl( _T( "\x0ba" ), _T( "&ordm;" ) ),	kl( _T( "\x0bb" ), _T( "&raquo;" ) ),
	kl( _T( "\x0bc" ), _T( "&frac14;" ) ),	kl( _T( "\x0bd" ), _T( "&half;" ) ),
	kl( _T( "\x0be" ), _T( "&frac34;" ) ),	kl( _T( "\x0bf" ), _T( "&iquest;" ) ),

	kl( _T( "À" ), _T( "&Agrave;" ) ),		kl( _T( "Á" ), _T( "&Aacute;" ) ),
	kl( _T( "Â" ), _T( "&Acirc;" ) ),		kl( _T( "Ã" ), _T( "&Atilde;" ) ),
	kl( _T( "Ä" ), _T( "&Auml;" ) ),		kl( _T( "Å" ), _T( "&Aring;" ) ),
	kl( _T( "Æ" ), _T( "&AElig;" ) ),		kl( _T( "Ç" ), _T( "&Ccedil;" ) ),
	kl( _T( "É" ), _T( "&Egrave;" ) ),		kl( _T( "É" ), _T( "&Eacute;" ) ),
	kl( _T( "Ê" ), _T( "&Ecirc;" ) ),		kl( _T( "Ë" ), _T( "&Auml;" ) ),
	kl( _T( "Ì" ), _T( "&Igrave;" ) ),		kl( _T( "Í" ), _T( "&Iacute;" ) ),
	kl( _T( "Î" ), _T( "&Icirc;" ) ),		kl( _T( "Ï" ), _T( "&Iuml;" ) ),

	kl( _T( "Ð" ), _T( "&ETH;" ) ),			kl( _T( "Ñ" ), _T( "&Ntilde;" ) ),
	kl( _T( "Ò" ), _T( "&Ograve;" ) ),		kl( _T( "Ó" ), _T( "&Oacute;" ) ),
	kl( _T( "Ô" ), _T( "&Ocirc;" ) ),		kl( _T( "Õ" ), _T( "&Otilde;" ) ),
	kl( _T( "Ö" ), _T( "&Ouml;" ) ),		kl( _T( "×" ), _T( "&times;" ) ),
	kl( _T( "Ø" ), _T( "&Oslash;" ) ),		kl( _T( "Ù" ), _T( "&Ugrave;" ) ),
	kl( _T( "Ú" ), _T( "&Uacute;" ) ),		kl( _T( "Û" ), _T( "&Ucirc;" ) ),
	kl( _T( "Ü" ), _T( "&Uuml;" ) ),		kl( _T( "Ý" ), _T( "&Yacute;" ) ),
	kl( _T( "Þ" ), _T( "&THORN;" ) ),		kl( _T( "ß" ), _T( "&szlig;" ) ),

	kl( _T( "à" ), _T( "&agrave;" ) ),		kl( _T( "á" ), _T( "&aacute;" ) ),
	kl( _T( "â" ), _T( "&acirc;" ) ),		kl( _T( "ã" ), _T( "&atilde;" ) ),
	kl( _T( "ä" ), _T( "&auml;" ) ),		kl( _T( "å" ), _T( "&aring;" ) ),
	kl( _T( "æ" ), _T( "&aelig;" ) ),		kl( _T( "ç" ), _T( "&ccedil;" ) ),
	kl( _T( "è" ), _T( "&egrave;" ) ),		kl( _T( "é" ), _T( "&eacute;" ) ),
	kl( _T( "ê" ), _T( "&ecirc;" ) ),		kl( _T( "ë" ), _T( "&euml;" ) ),
	kl( _T( "ì" ), _T( "&igrave;" ) ),		kl( _T( "í" ), _T( "&iacute;" ) ),
	kl( _T( "î" ), _T( "&icirc;" ) ),		kl( _T( "ï" ), _T( "&iuml;" ) ),

	kl( _T( "ð" ), _T( "&eth;" ) ),			kl( _T( "ñ" ), _T( "&ntilde;" ) ),
	kl( _T( "ò" ), _T( "&ograve;" ) ),		kl( _T( "ó" ), _T( "&oacute;" ) ),
	kl( _T( "ô" ), _T( "&ocirc;" ) ),		kl( _T( "õ" ), _T( "&otilde;" ) ),
	kl( _T( "ö" ), _T( "&ouml;" ) ),		kl( _T( "÷" ), _T( "&divide;" ) ),
	kl( _T( "ø" ), _T( "&oslash;" ) ),		kl( _T( "ù" ), _T( "&ugrave;" ) ),
	kl( _T( "ú" ), _T( "&uacute;" ) ),		kl( _T( "û" ), _T( "&ucirc;" ) ),
	kl( _T( "ü" ), _T( "&uuml;" ) ),		kl( _T( "ý" ), _T( "&yacute;" ) ),
	kl( _T( "þ" ), _T( "&thorn;" ) ),		kl( _T( "ÿ" ), _T( "&yuml;" ) ),

	kl( NULL, NULL )
};

std::string zIso8859::ANSItoISO8859( std::string& inStr )
{
	std::string outStr = _T( "" );

	int l = inStr.length();

	for ( int i = 0; i < l; i++ )
	{
		int pos = kl::convertAt( inStr[i] );

		if ( pos >= 0 )
		{
			outStr += dictionary[pos].key2;
		}
		else
		{
			outStr += inStr[i];
		}
	}

	return outStr;
}

std::string zIso8859::ISO8859toANSI( std::string& inStr )
{
	int pos = 0;

	while ( pos >= 0 )
	{
		for ( int i = 0; dictionary[i].key1 != NULL; i++ )
		{
			printf( _T( "%d\n" ), i );

			pos = inStr.find( dictionary[i].key2 );

			if ( pos >= 0 )
			{
				inStr.replace( (int)pos, (int)strlen( dictionary[i].key2 ), dictionary[i].key1 );
				break;
			}
		}
	}

	return inStr;
}
