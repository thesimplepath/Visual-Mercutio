/****************************************************************************
 * ==> PSS_SoapPublisher_Workgroup -----------------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish a workgroup                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SoapPublisher_Workgroup.h"

// processsoft
#include "PSS_SoapData_Settings.h"
#include "PSS_SoapException.h"

//---------------------------------------------------------------------------
// PSS_SoapPublisher_Workgroup
//---------------------------------------------------------------------------
PSS_SoapPublisher_Workgroup::PSS_SoapPublisher_Workgroup()
{
    m_Alias = _T("");
}
//---------------------------------------------------------------------------
PSS_SoapPublisher_Workgroup::~PSS_SoapPublisher_Workgroup()
{}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_Workgroup::Reset()
{
    m_DataSet.clear();
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_Workgroup::Add(const PSS_SoapData_Workgroup& data)
{
    m_DataSet.insert(m_DataSet.end(), data);
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_Workgroup::AddAlias(const CString& alias)
{
    m_Alias = alias;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublisher_Workgroup::Send()
{
    SOAPDebugger::SetFile(_T("c:\\psssoap_pubwkg.log"));

    bool result = true;

    try
    {
        TRACE(_T("pPublishWorkgroup.send()\n"));

        // create the SOAP proxy
        SOAPProxy proxy(PSS_SoapData_Settings::m_Url.c_str());

        // open the SOAP protocol
        SOAPMethod pubWorkgroup(_T("pubWorkgroup"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

        // add data count
        pubWorkgroup.AddParameter(_T("wkgnbr")).SetValue(int(m_DataSet.size()));

        SOAPArray<PSS_SoapData_Workgroup> workgroups;

        // populate the SOAP data array
        for (std::list<PSS_SoapData_Workgroup>::iterator it = m_DataSet.begin(); it != m_DataSet.end(); ++it)
            workgroups.Add(*it);

        // add data set
        SOAPParameter& p = pubWorkgroup.AddParameter(_T("wkg"));
        p << workgroups;

        // add alias
        pubWorkgroup.AddParameter(_T("alias")).SetValue(m_Alias);

        // send the data to SOAP proxy and check the result
        if (int(proxy.Execute(pubWorkgroup).GetReturnValue()) < 0)
            result = false;
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n" ), ex.What().Str());
        result = false;
    }

    SOAPDebugger::Close();
    return result;
}
//---------------------------------------------------------------------------
