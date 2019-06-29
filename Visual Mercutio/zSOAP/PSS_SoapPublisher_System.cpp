/****************************************************************************
 * ==> PSS_SoapPublisher_System --------------------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish a system                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SoapPublisher_System.h"

// processsoft
#include "PSS_SoapPublisher_Settings.h"
#include "zSoapException.h"

//---------------------------------------------------------------------------
// PSS_SoapPublisher_System
//---------------------------------------------------------------------------
PSS_SoapPublisher_System::PSS_SoapPublisher_System()
{
    m_Alias = _T("");
}
//---------------------------------------------------------------------------
PSS_SoapPublisher_System::~PSS_SoapPublisher_System()
{}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_System::Reset()
{
    m_DataSet.clear();
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_System::Add(const PSS_SoapData_System& data)
{
    m_DataSet.insert(m_DataSet.end(), data);
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_System::AddAlias(const CString& alias)
{
    m_Alias = alias;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublisher_System::Send()
{
    SOAPDebugger::SetFile(_T("c:\\psssoap_pubsystem.log"));

    bool result = true;

    try
    {
        TRACE(_T("pPublishSystem.send()"));

        // create the SOAP proxy
        SOAPProxy proxy(PSS_SoapPublisher_Settings::m_Url.c_str());

        // open the SOAP protocol
        SOAPMethod pubSystem(_T("pubSystem"), PSS_SoapPublisher_Settings::m_ModelService.c_str(), _T("http://"));

        // add the system number
        pubSystem.AddParameter(_T("systemnbr")).SetValue(int(m_DataSet.size()));

        SOAPArray<PSS_SoapData_System> systems;

        // populate the SOAP data array
        for (list<PSS_SoapData_System>::iterator it = m_DataSet.begin(); it != m_DataSet.end(); ++it)
            systems.Add(*it);

        // add data set
        SOAPParameter& p = pubSystem.AddParameter(_T("system"));
        p << systems;

        // add alias
        pubSystem.AddParameter(_T("alias")).SetValue(m_Alias);

        // send the data to SOAP proxy and check the result
        if ( (int)proxy.Execute( pubSystem ).GetReturnValue() < 0 )
        {
            result = false;
        }
    }
    catch ( SOAPException& ex )
    {
        TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
        result = false;
    }

    SOAPDebugger::Close();

    return result;
}
//---------------------------------------------------------------------------
