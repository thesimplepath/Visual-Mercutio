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
#include "pPublishWorkgroup.h"

// processsoft
#include "PSS_SoapPublisher_Settings.h"
#include "zSoapException.h"

/////////////////////////////////////////////////////////////////////////////////
// Default constructor.
pPublishWorkgroup::pPublishWorkgroup()
{
    // JMR-MODIF - Le 21 juin 2006 - Ajout de l'initialisation de la variable m_Alias.
    m_Alias = _T( "" );
}

/////////////////////////////////////////////////////////////////////////////////
// Default destructor.
pPublishWorkgroup::~pPublishWorkgroup()
{
}

/////////////////////////////////////////////////////////////////////////////////
// Reset data. (empty lists)
void pPublishWorkgroup::reset()
{
    m_workgroups.clear();
}

/////////////////////////////////////////////////////////////////////////////////
// Add new procedure.
void pPublishWorkgroup::addWorkgroup( pworkgroup wkg )
{
    m_workgroups.insert( m_workgroups.end(), wkg );
}

// JMR-MODIF - Le 21 juin 2006 - Cette fonction permet d'ajouter l'alias, nécessaire pour la publication.
void pPublishWorkgroup::addAlias(const CString& alias)
{
    m_Alias = alias;
}

/////////////////////////////////////////////////////////////////////////////////
// Send data to urn:emessenger , method: pubWorkgroup
// out:returns true on success
bool pPublishWorkgroup::send()
{
    SOAPDebugger::SetFile( _T( "c:\\psssoap_pubwkg.log" ) );

    bool RetValue = true;

    try
    {
        TRACE( _T( "pPublishWorkgroup.send()\n" ) );

        // Defs
        string wdsl_urn = PSS_SoapPublisher_Settings::m_ModelService;

        // Initialize objects
        string url = PSS_SoapPublisher_Settings::m_Url;
        SOAPProxy proxy( url.c_str() );

        // Send
        SOAPMethod pubWorkgroup( _T( "pubWorkgroup" ), wdsl_urn.c_str(), _T( "http://" ) );
        pubWorkgroup.AddParameter( _T( "wkgnbr" ) ).SetValue( (int)m_workgroups.size() );

        SOAPArray<pworkgroup> workgroups;
        list<pworkgroup>::iterator workgroupi;

        for ( workgroupi = m_workgroups.begin(); workgroupi != m_workgroups.end(); ++workgroupi )
        {
            workgroups.Add( *workgroupi );
        }

        SOAPParameter& p = pubWorkgroup.AddParameter( _T( "wkg" ) );
        p << workgroups;

        // JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
        pubWorkgroup.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

        if ( (int)proxy.Execute( pubWorkgroup ).GetReturnValue() < 0 )
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
