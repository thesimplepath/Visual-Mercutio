/****************************************************************************
 * ==> PSS_SoapPublisher_Prestations ---------------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish the prestations                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SoapPublisher_Prestations.h"

// processsoft
#include "PSS_SoapData_Settings.h"
#include "PSS_SoapException.h"

//---------------------------------------------------------------------------
// PSS_SoapPublisher_Prestations
//---------------------------------------------------------------------------
pPublishPrestations::pPublishPrestations()
{
    m_Alias = _T("");
}
//---------------------------------------------------------------------------
pPublishPrestations::~pPublishPrestations()
{}
//---------------------------------------------------------------------------
void pPublishPrestations::Reset()
{
    m_DataSet.clear();
}
//---------------------------------------------------------------------------
void pPublishPrestations::Set(const PSS_SoapData_Prestations& data)
{
    m_DataSet.insert(m_DataSet.end(), data);
}
//---------------------------------------------------------------------------
void pPublishPrestations::AddAlias(const CString& alias)
{
    m_Alias = alias;
}
//---------------------------------------------------------------------------
bool pPublishPrestations::Send()
{
    SOAPDebugger::SetFile(_T("c:\\psssoap_pubprestations.log"));

    bool result = true;

    try
    {
        TRACE(_T("pPublishPrestations.send()"));

        // create the SOAP proxy
        SOAPProxy proxy(PSS_SoapData_Settings::m_Url.c_str());

        // open the SOAP protocol
        SOAPMethod pubPrestations(_T("pubPrestations"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

        // add prestations count
        pubPrestations.AddParameter(_T("prestationsnbr")).SetValue(int(m_DataSet.size()));

        SOAPArray<PSS_SoapData_Prestations> prestations;

        // populate the SOAP data array
        for (std::list<PSS_SoapData_Prestations>::iterator it = m_DataSet.begin(); it != m_DataSet.end(); ++it)
            prestations.Add(*it);

        // add data set
        SOAPParameter& p = pubPrestations.AddParameter(_T("prestations"));
        p << prestations;

        // add alias
        pubPrestations.AddParameter(_T("alias")).SetValue(m_Alias);

        // send the data to SOAP proxy and check the result
        if (int(proxy.Execute(pubPrestations).GetReturnValue()) < 0)
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
