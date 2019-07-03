/****************************************************************************
 * ==> PSS_SoapPublisher_MessengerInfo -------------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish the Messenger info                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SoapPublisher_MessengerInfo.h"

// processsoft
#include "zConversion\PSS_Encoding.h"
#include "PSS_SoapData_Settings.h"
#include "PSS_SoapException.h"

//---------------------------------------------------------------------------
// PSS_SoapPublisher_MessengerInfo
//---------------------------------------------------------------------------
PSS_SoapPublisher_MessengerInfo::PSS_SoapPublisher_MessengerInfo()
{}
//---------------------------------------------------------------------------
PSS_SoapPublisher_MessengerInfo::~PSS_SoapPublisher_MessengerInfo()
{}
//---------------------------------------------------------------------------
int PSS_SoapPublisher_MessengerInfo::GetVersion()
{
    SOAPDebugger::SetFile(_T("c:\\psssoap_messengerversion.log"));

    try
    {
        // create the SOAP proxy
        SOAPProxy proxy(PSS_SoapData_Settings::m_Url.c_str());

        // open the SOAP protocol
        SOAPMethod pubGetVersion(_T("pubGetVersion"), PSS_SoapData_Settings::m_ServerService.c_str(), _T("http://"));

        // execute the query and get the result
        const int result = proxy.Execute(pubGetVersion).GetReturnValue();

        SOAPDebugger::Close();
        return result;
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
    }

    SOAPDebugger::Close();
    return -1;
}
//---------------------------------------------------------------------------
std::string PSS_SoapPublisher_MessengerInfo::GetLanguage()
{
    SOAPDebugger::SetFile(_T("c:\\psssoap_getlanguage.log"));

    try
    {
        // create the SOAP proxy
        SOAPProxy proxy(PSS_SoapData_Settings::m_Url.c_str());

        // open the SOAP protocol
        SOAPMethod pubGetLanguage(_T("pubGetLanguage"), PSS_SoapData_Settings::m_ServerService.c_str(), _T("http://"));

        SOAPString result;

        // execute the query and get the result
        proxy.Execute(pubGetLanguage).GetReturnValue() >> result;

        // close the soap proxy
        SOAPDebugger::Close();
        return result.Str();
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
    }

    SOAPDebugger::Close();
    return _T("??");
}
//---------------------------------------------------------------------------
int PSS_SoapPublisher_MessengerInfo::Authenticate(const std::string& login, const std::string& password)
{
    SOAPDebugger::SetFile(_T("c:\\psssoap_authenticate.log"));

    try
    {
        // create the SOAP proxy
        SOAPProxy proxy(PSS_SoapData_Settings::m_Url.c_str());

        // open the SOAP protocol
        SOAPMethod authenticate(_T("Authenticate"), PSS_SoapData_Settings::m_ServerService.c_str(), _T("http://"));

        // Set the login and password
        authenticate.AddParameter(_T("login")).SetValue(login.c_str());
        authenticate.AddParameter(_T("passwd")).SetValue(PSS_Encoding::MD5Encode(password, 32).c_str());

        int result;

        // execute the query and get the result
        proxy.Execute( authenticate ).GetReturnValue() >> result;

        SOAPDebugger::Close();
        return result;
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
    }

    SOAPDebugger::Close();
    return -1;
}
//---------------------------------------------------------------------------
