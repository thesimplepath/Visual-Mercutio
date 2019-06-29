/****************************************************************************
 * ==> PSS_SoapPublisher_MessengerUniverse ---------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish the Messenger universe            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SoapPublisher_MessengerUniverse.h"

// processsoft
#include "PSS_SoapPublisher_Settings.h"
#include "zSoapException.h"

//---------------------------------------------------------------------------
// PSS_SoapPublisher_MessengerUniverse
//---------------------------------------------------------------------------
PSS_SoapPublisher_MessengerUniverse::PSS_SoapPublisher_MessengerUniverse()
{
    m_Alias = _T("");
}
//---------------------------------------------------------------------------
PSS_SoapPublisher_MessengerUniverse::~PSS_SoapPublisher_MessengerUniverse()
{}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_MessengerUniverse::Reset()
{
    m_DataSet.clear();
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_MessengerUniverse::Add(const PSS_SoapData_MessengerUniverse& data)
{
    m_DataSet.insert(m_DataSet.end(), data);
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_MessengerUniverse::AddAlias(const CString& alias)
{
    m_Alias = alias;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublisher_MessengerUniverse::Send()
{
    SOAPDebugger::SetFile(_T("c:\\psssoap_pubcheckuniverse.log"));

    bool result = true;

    try
    {
        TRACE(_T("pCheckUniverse.send()"));

        // create the SOAP proxy
        SOAPProxy proxy(PSS_SoapPublisher_Settings::m_Url.c_str());

        // open the SOAP protocol
        SOAPMethod messengerUniverse(_T("pubCheckUniverse"), PSS_SoapPublisher_Settings::m_ModelService.c_str(), _T("http://"));

        // add data count
        messengerUniverse.AddParameter(_T("universenbr")).SetValue(int(m_DataSet.size()));

        SOAPArray<PSS_SoapData_MessengerUniverse> universes;

        // populate the SOAP data array
        for (list<PSS_SoapData_MessengerUniverse>::iterator it = m_DataSet.begin(); it != m_DataSet.end(); ++it)
            universes.Add(*it);

        // add data set
        SOAPParameter& p = messengerUniverse.AddParameter(_T("universe"));
        p << universes;

        // add alias
        messengerUniverse.AddParameter(_T("alias")).SetValue(m_Alias);

        // send the data to SOAP proxy and check the result
        if (int(proxy.Execute(messengerUniverse).GetReturnValue()) < 0)
            result = false;
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
        result = false;
    }

    SOAPDebugger::Close();

    return result;
}
//---------------------------------------------------------------------------
