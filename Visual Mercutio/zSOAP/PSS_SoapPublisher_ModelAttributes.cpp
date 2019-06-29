/****************************************************************************
 * ==> PSS_SoapPublisher_ModelAttributes -----------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish the model attributes              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SoapPublisher_ModelAttributes.h"

// processsoft
#include "PSS_SoapData_Settings.h"
#include "zSoapException.h"

//---------------------------------------------------------------------------
// PSS_SoapPublisher_ModelAttributes
//---------------------------------------------------------------------------
PSS_SoapPublisher_ModelAttributes::PSS_SoapPublisher_ModelAttributes()
{
    m_Alias = _T("");
}
//---------------------------------------------------------------------------
PSS_SoapPublisher_ModelAttributes::~PSS_SoapPublisher_ModelAttributes()
{}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_ModelAttributes::Reset()
{
    m_DataSet.clear();
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_ModelAttributes::Add(const PSS_SoapData_ModelAttributes& data)
{
    m_DataSet.insert(m_DataSet.end(), data);
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_ModelAttributes::AddAlias(const CString& alias)
{
    m_Alias = alias;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublisher_ModelAttributes::Send()
{
    SOAPDebugger::SetFile(_T("c:\\psssoap_pubattribdef.log"));

    bool result = true;

    try
    {
        // create the SOAP proxy
        SOAPProxy proxy(PSS_SoapData_Settings::m_Url.c_str());

        // open the SOAP protocol
        SOAPMethod pubAttribDef(_T("pubAttribDef"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

        // add data count
        pubAttribDef.AddParameter(_T("attribdefnbr")).SetValue(int(m_DataSet.size()));

        SOAPArray<PSS_SoapData_ModelAttributes> attribDefs;

        // populate the SOAP data array
        for (std::list<PSS_SoapData_ModelAttributes>::iterator it = m_DataSet.begin(); it != m_DataSet.end(); ++it)
            attribDefs.Add(*it);

        // add data set
        SOAPParameter& p = pubAttribDef.AddParameter(_T("attribdefs"));
        p << attribDefs;

        // add alias
        pubAttribDef.AddParameter(_T("alias")).SetValue(m_Alias);

        // send the data to SOAP proxy and check the result
        if (int(proxy.Execute(pubAttribDef).GetReturnValue()) < 0)
        {
            TRACE(_T("Pub Attrib Def failed\n"));
            result = false;
        }
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
