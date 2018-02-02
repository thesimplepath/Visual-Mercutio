/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module XXXClass.h | Interface of the <c XXXClass> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Gaya
// <nl>Created:		 03/2002
// <nl>Description:  XXXClass frame window support
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __PPUBLISHFILE_HDR_
#define __PPUBLISHFILE_HDR_

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "pfile.h"

#ifdef _ZSOAPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 15 septembre 2005 - Ajout de la décoration Unicode _T( ) pour les chaînes de caractères de cette classe.

//Define serializers / soap mapping

/////////////////////////////////////////////
// pfile soap mapping
BEGIN_EASYSOAP_NAMESPACE

template<>
class SOAPTypeTraits<pfile>
{
public:

	static void GetType( SOAPQName& qname )
	{
		qname.Set( _T( "pfile" ), _T( "urn:xml-soap-pssfile" ) );
	}

	static SOAPParameter& Serialize( SOAPParameter& param, const pfile& val )
	{		
		param.AddParameter( _T( "len" ) )		<< (int)val.len;
		param.AddParameter( _T( "folder" ) )	<< (int)val.folder;		
		param.AddParameter( _T( "crc" ) )		<< (int)val.crc;
		param.AddParameter( _T( "doc" ) )		<< val.doc.c_str();
		param.AddParameter( _T( "fname" ) )		<< val.fname.c_str();

		return param;
	}
	
	static const SOAPParameter& Deserialize( const SOAPParameter& param, pfile& val )
	{
		SOAPString tmp;
		int v;

		param.GetParameter( _T( "len" ) )		>> v;
		val.len = v;
		param.GetParameter( _T( "folder" ) )	>> val.folder;
		param.GetParameter( _T( "crc" ) )		>> v;
		val.crc = v;
		param.GetParameter( _T( "doc" ) )		>> tmp;
		val.doc = tmp.Str();
		param.GetParameter( _T( "fname" ) )		>> tmp;
		val.fname = tmp.Str();		
		return param;
	}
};

template<>
class SOAPTypeTraits< SOAPArray<pfile> > : public SOAPArrayTypeTraits
{
};

class AFX_EXT_CLASS pPublishFile
{
public:

	pPublishFile();
	~pPublishFile();

	bool pubFile( pfile mfile );
	int pubHasChanged( int mfolder, string mfilename, int mday, int mmonth, int myear, int mhour, int mmin, int msec );
	pfile pubGetFile( int mfolder, string mfilename );
};

END_EASYSOAP_NAMESPACE

#endif