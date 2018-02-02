// **************************************************************************************************************
// *									   Classe pCheckUniverse												*
// **************************************************************************************************************
// * JMR-MODIF - Le 21 juin 2006 - Création de la classe pCheckUniverse.										*
// **************************************************************************************************************
// * Cette classe prend en charge la publication des univers vers Messenger.									*
// **************************************************************************************************************

#include "stdafx.h"

#include "pPublishSettings.h"
#include "pCheckUniverse.h"

#include "zSoapException.h"

/////////////////////////////////////////////////////////////////////////////////
//Default constructor
pCheckUniverse::pCheckUniverse()
{
	m_Alias = _T( "" );
}

/////////////////////////////////////////////////////////////////////////////////
//Default destructor
pCheckUniverse::~pCheckUniverse()
{
}

/////////////////////////////////////////////////////////////////////////////////
//reset data (empty lists)
void pCheckUniverse::reset()
{
	m_universe.clear();
}

/////////////////////////////////////////////////////////////////////////////////
//add new procedure
void pCheckUniverse::addUniverse( puniverse universe )
{
	m_universe.insert( m_universe.end(), universe );
}

void pCheckUniverse::addAlias( CString Alias )
{
	m_Alias = Alias;
}

/////////////////////////////////////////////////////////////////////////////////
// Send data to urn:emessenger , method: pubCheckUniverse
//	out:returns true on success
bool pCheckUniverse::check()
{
	SOAPDebugger::SetFile( _T( "c:\\psssoap_pubcheckuniverse.log" ) );

	bool RetValue = true;

	try
	{
		TRACE( _T( "pCheckUniverse.check()" ) );

		// Defs
		string wdsl_urn = pPublishSettings::modelservice;

		// Initialize objects
		string url = pPublishSettings::url;
		SOAPProxy proxy( url.c_str() );

		// Send
		SOAPMethod checkUniverse( _T( "pubCheckUniverse" ), wdsl_urn.c_str(), _T( "http://" ) );
		checkUniverse.AddParameter( _T( "universenbr" ) ).SetValue( (int)m_universe.size() );

		SOAPArray<puniverse> universea;
		list<puniverse>::iterator universei;

		for ( universei = m_universe.begin(); universei != m_universe.end(); ++universei )
		{
			universea.Add( *universei );
		}

		SOAPParameter& p = checkUniverse.AddParameter( _T( "universe" ) );
		p << universea;

		checkUniverse.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

		if ( (int)proxy.Execute( checkUniverse ).GetReturnValue() < 0 )
		{
			RetValue = false;
		}
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
		RetValue = false;
	}

	SOAPDebugger::Close();

	return RetValue;
}
