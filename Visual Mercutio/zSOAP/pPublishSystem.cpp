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
#include "pPublishSystem.h"

#include "zSoapException.h"

// JMR-MODIF - Le 15 septembre 2005 - Ajout des décorations Unicode _T(), nettoyage du code inutile.(En commentaires)

/////////////////////////////////////////////////////////////////////////////////
//Default constructor
pPublishSystem::pPublishSystem()
{
    // JMR-MODIF - Le 21 juin 2006 - Ajout de l'initialisation de la variable m_Alias.
    m_Alias = _T( "" );
}

/////////////////////////////////////////////////////////////////////////////////
//Default destructor
pPublishSystem::~pPublishSystem()
{
}

/////////////////////////////////////////////////////////////////////////////////
//reset data (empty lists)
void pPublishSystem::reset()
{
    m_systems.clear();
}

/////////////////////////////////////////////////////////////////////////////////
//add new procedure
void pPublishSystem::addSystem( psystem syst )
{
    m_systems.insert( m_systems.end(), syst );
}

// JMR-MODIF - Le 21 juin 2006 - Cette fonction permet d'ajouter l'alias, nécessaire pour la publication.
void pPublishSystem::addAlias(const CString& alias)
{
    m_Alias = alias;
}

/////////////////////////////////////////////////////////////////////////////////
//send data to urn:emessenger , method: pubSystem
//    out:returns true on success
bool pPublishSystem::send()
{
    SOAPDebugger::SetFile( _T( "c:\\psssoap_pubsystem.log" ) );

    bool RetValue = true;

    try
    {
        TRACE( _T( "pPublishSystem.send()" ) );

        // Defs
        string wdsl_urn = pPublishSettings::m_ModelService;

        // Initialize objects
        string url = pPublishSettings::m_Url;
        SOAPProxy proxy( url.c_str() );

        // Send
        SOAPMethod pubSystem( _T( "pubSystem" ), wdsl_urn.c_str(), _T( "http://" ) );
        pubSystem.AddParameter( _T( "systemnbr" ) ).SetValue( (int)m_systems.size() );

        SOAPArray<psystem> systems;
        list<psystem>::iterator systemi;

        for ( systemi =  m_systems.begin(); systemi != m_systems.end(); ++systemi )
        {
            systems.Add( *systemi );
        }

        SOAPParameter& p = pubSystem.AddParameter( _T( "system" ) );
        p << systems;

        // JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
        pubSystem.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

        if ( (int)proxy.Execute( pubSystem ).GetReturnValue() < 0 )
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
