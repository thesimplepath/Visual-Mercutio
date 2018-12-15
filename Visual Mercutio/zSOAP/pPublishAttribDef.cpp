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
#include "pPublishAttribDef.h"

#include "zSoapException.h"

// JMR-MODIF - Le 15 septembre 2005 - Ajout des décorations Unicode _T(), nettoyage du code inutile.(En commentaires)

/////////////////////////////////////////////////////////////////////////////////
// Default constructor
pPublishAttribDef::pPublishAttribDef()
{
    // JMR-MODIF - Le 21 juin 2006 - Ajout de l'initialisation de la variable m_Alias.
    m_Alias = _T( "" );
}

/////////////////////////////////////////////////////////////////////////////////
// Default destructor
pPublishAttribDef::~pPublishAttribDef()
{
}

/////////////////////////////////////////////////////////////////////////////////
// reset data (empty lists)
void pPublishAttribDef::reset()
{
    m_attribdefs.clear();
}
    
/////////////////////////////////////////////////////////////////////////////////
// add new procedure
void pPublishAttribDef::addAttribDef( pattribdef attribdef )
{
    m_attribdefs.insert( m_attribdefs.end(), attribdef );
}

// JMR-MODIF - Le 21 juin 2006 - Cette fonction permet d'ajouter l'alias, nécessaire pour la publication.
void pPublishAttribDef::addAlias( CString Alias )
{
    m_Alias = Alias;
}

/////////////////////////////////////////////////////////////////////////////////
// send data to urn:emessenger , method: sndModel
// out:returns true on success
bool pPublishAttribDef::send()
{
    SOAPDebugger::SetFile( _T( "c:\\psssoap_pubattribdef.log" ) );

    bool RetValue = true;

    try
    {
        // Defs
        string wdsl_urn = pPublishSettings::modelservice;

        // Initialize objects
        string url = pPublishSettings::url;
        SOAPProxy proxy( url.c_str() );

        // Proc
        SOAPMethod pubAttribDef( _T( "pubAttribDef" ), wdsl_urn.c_str(), _T( "http://" ) );
        pubAttribDef.AddParameter( _T( "attribdefnbr" ) ).SetValue( (int)m_attribdefs.size() );

        SOAPArray<pattribdef> attribdef;
        list<pattribdef>::iterator attribdefi;

        for ( attribdefi =  m_attribdefs.begin(); attribdefi != m_attribdefs.end(); ++attribdefi )
        {
            attribdef.Add( *attribdefi );
        }

        SOAPParameter& p = pubAttribDef.AddParameter( _T( "attribdefs" ) );
        p << attribdef;

        // JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
        pubAttribDef.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

        if ( (int)proxy.Execute( pubAttribDef ).GetReturnValue() < 0 )
        {
            TRACE( _T( "Pub Attrib Def failed\n" ) );
            RetValue = false;
        }
    }
    catch ( SOAPException& ex )
    {
        TRACE( _T( "Caught SOAP exception:%s\n" ),ex.What().Str() );
        RetValue = false;
    }

    SOAPDebugger::Close();
    return RetValue;
}
