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
#include "pPublishMessengerInfo.h"

// processsoft
#include "zConversion\PSS_Encoding.h"
#include "pPublishSettings.h"
#include "zSoapException.h"

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
        string wdsl_urn = pPublishSettings::m_ServerService;

        // initialize objects
        string url = pPublishSettings::m_Url;
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
std::string pPublishMessengerInfo::GetLanguage()
{
    SOAPDebugger::SetFile( _T( "c:\\psssoap_getlanguage.log" ) );

    try
    {
        // defs
        string wdsl_urn = pPublishSettings::m_ServerService;

        // initialize objects
        string url = pPublishSettings::m_Url;
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
int pPublishMessengerInfo::Authenticate(const std::string& login, const std::string& passwd)
{
    SOAPDebugger::SetFile( _T( "c:\\psssoap_authenticate.log" ) );

    try
    {
        // defs
        string wdsl_urn = pPublishSettings::m_ServerService;

        // initialize objects
        string url = pPublishSettings::m_Url;
        SOAPProxy proxy( url.c_str() );

        // pubAuth

        // RS-MODIF 04.08.2005: erreur de publication sous XP
        // authenticate.SetSoapAction( _T( "http://soapinterop.org/" ) );

        // SOAPMethod authenticate( _T( "Authenticate" ), wdsl_urn.c_str() );
        SOAPMethod authenticate( _T( "Authenticate" ), wdsl_urn.c_str(), _T( "http://" ) );

        authenticate.AddParameter( _T( "login" ) ).SetValue( login.c_str() );
        authenticate.AddParameter( _T( "passwd" ) ).SetValue(PSS_Encoding::MD5Encode( passwd, 32 ).c_str() );

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
