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

#include "pPublishSettings.h"
#include "pPublishMessengerInfo.h"

#include "zSoapException.h"

// JMR-MODIF - Le 15 septembre 2005 - Ajout des décorations Unicode _T(), nettoyage du code inutile.(En commentaires)

string md5encode( string data, long nEncryptLength );

pPublishMessengerInfo::pPublishMessengerInfo()
{
}

pPublishMessengerInfo::~pPublishMessengerInfo()
{
}

////////////////////////////////////////////////////////////
// returns server version
int pPublishMessengerInfo::GetVersion()
{
	SOAPDebugger::SetFile( _T( "c:\\psssoap_messengerversion.log" ) );

	try
	{
		// defs
		string wdsl_urn = pPublishSettings::serverservice;

		// initialize objects
		string url = pPublishSettings::url;
		SOAPProxy proxy( url.c_str() );

		// pubInit
		SOAPMethod pubGetVersion( _T( "pubGetVersion" ), wdsl_urn.c_str(), _T( "http://" ) );

		int ret = proxy.Execute( pubGetVersion ).GetReturnValue();

		SOAPDebugger::Close();
		return ret;
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
	}

	SOAPDebugger::Close();
	return -1;
}

////////////////////////////////////////////////////////////
// returns ISO code for installed server version 
string pPublishMessengerInfo::GetLanguage()
{
	SOAPDebugger::SetFile( _T( "c:\\psssoap_getlanguage.log" ) );

	try
	{
		// defs
		string wdsl_urn = pPublishSettings::serverservice;		

		// initialize objects
		string url = pPublishSettings::url;
		SOAPProxy proxy( url.c_str() );

		// pubInit
		SOAPMethod pubGetLanguage( _T( "pubGetLanguage" ), wdsl_urn.c_str(), _T( "http://" ) );	
		SOAPString ret;

		proxy.Execute( pubGetLanguage ).GetReturnValue() >> ret;

		SOAPDebugger::Close();
		return ret.Str();
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
	}

	SOAPDebugger::Close();
	return _T( "??" );
}

////////////////////////////////////////////////////////////
// authenticate on server (administrator only)
int pPublishMessengerInfo::Authenticate( string login, string passwd )
{
	SOAPDebugger::SetFile( _T( "c:\\psssoap_authenticate.log" ) );

	try
	{
		// defs
		string wdsl_urn = pPublishSettings::serverservice;

		// initialize objects
		string url = pPublishSettings::url;
		SOAPProxy proxy( url.c_str() );

		// pubAuth

		// RS-MODIF 04.08.2005: erreur de publication sous XP
		// authenticate.SetSoapAction( _T( "http://soapinterop.org/" ) );

		// SOAPMethod authenticate( _T( "Authenticate" ), wdsl_urn.c_str() );
		SOAPMethod authenticate( _T( "Authenticate" ), wdsl_urn.c_str(), _T( "http://" ) );

		authenticate.AddParameter( _T( "login" ) ).SetValue( login.c_str() );
		authenticate.AddParameter( _T( "passwd" ) ).SetValue( md5encode( passwd, 32 ).c_str() );

		int ret;

		proxy.Execute( authenticate ).GetReturnValue() >> ret;

		SOAPDebugger::Close();
		return ret;
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
	}

	SOAPDebugger::Close();
	return -1;
}
