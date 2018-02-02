// **************************************************************************************************************
// *									 Classe pPublishPrestations												*
// **************************************************************************************************************
// * JMR-MODIF - Le 30 mars 2006 - Création de la classe pPublishPrestations.									*
// **************************************************************************************************************
// * Cette classe prend en charge la publication des prestations vers Messenger.								*
// **************************************************************************************************************

#include "stdafx.h"

#include "pPublishSettings.h"
#include "pPublishPrestations.h"

#include "zSoapException.h"

/////////////////////////////////////////////////////////////////////////////////
//Default constructor
pPublishPrestations::pPublishPrestations()
{
	// JMR-MODIF - Le 21 juin 2006 - Ajout de l'initialisation de la variable m_Alias.
	m_Alias = _T( "" );
}

/////////////////////////////////////////////////////////////////////////////////
//Default destructor
pPublishPrestations::~pPublishPrestations()
{
}

/////////////////////////////////////////////////////////////////////////////////
//reset data (empty lists)
void pPublishPrestations::reset()
{
	m_prestations.clear();
}

/////////////////////////////////////////////////////////////////////////////////
//add new procedure
void pPublishPrestations::addPrestation( pprestations prest )
{
	m_prestations.insert( m_prestations.end(), prest );
}

// JMR-MODIF - Le 21 juin 2006 - Cette fonction permet d'ajouter l'alias, nécessaire pour la publication.
void pPublishPrestations::addAlias( CString Alias )
{
	m_Alias = Alias;
}

/////////////////////////////////////////////////////////////////////////////////
//send data to urn:emessenger , method: pubSystem
//	out:returns true on success
bool pPublishPrestations::send()
{
	SOAPDebugger::SetFile( _T( "c:\\psssoap_pubprestations.log" ) );

	bool RetValue = true;

	try
	{
		TRACE( _T( "pPublishPrestations.send()" ) );

		// Defs
		string wdsl_urn = pPublishSettings::modelservice;

		// Initialize objects
		string url = pPublishSettings::url;
		SOAPProxy proxy( url.c_str() );

		// Send
		SOAPMethod pubPrestations( _T( "pubPrestations" ), wdsl_urn.c_str(), _T( "http://" ) );
		pubPrestations.AddParameter( _T( "prestationsnbr" ) ).SetValue( (int)m_prestations.size() );

		SOAPArray<pprestations> prestations;
		list<pprestations>::iterator prestationsi;

		for ( prestationsi =  m_prestations.begin(); prestationsi != m_prestations.end(); ++prestationsi )
		{
			prestations.Add( *prestationsi );
		}

		SOAPParameter& p = pubPrestations.AddParameter( _T( "prestations" ) );
		p << prestations;

		// JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
		pubPrestations.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

		if ( (int)proxy.Execute( pubPrestations ).GetReturnValue() < 0 )
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
