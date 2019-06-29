/****************************************************************************
 * ==> PSS_SoapPublisher_Model ---------------------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish the model                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SoapPublisher_Model.h"

// processsoft
#include "PSS_SoapData_Settings.h"
#include "PSS_SoapException.h"

//---------------------------------------------------------------------------
// PSS_SoapPublisher_Model
//---------------------------------------------------------------------------
PSS_SoapPublisher_Model::PSS_SoapPublisher_Model()
{
    m_Alias = _T("");
}
//---------------------------------------------------------------------------
PSS_SoapPublisher_Model::~PSS_SoapPublisher_Model()
{}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_Model::Reset()
{
    m_DataSet_Proc.clear();
    m_DataSet_Deliv.clear();
    m_DataSet_SymAttr.clear();
    m_DataSet_Distrib.clear();
    m_DataSet_DistribMap.clear();
    m_DataSet_Inputs.clear();
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_Model::SetModel(const PSS_SoapData_Model& model)
{
    m_Model = model;
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_Model::Add(const PSS_SoapData_Process& data)
{
    m_DataSet_Proc.insert(m_DataSet_Proc.end(), data);
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_Model::Add(const PSS_SoapData_Deliverable& data)
{
    m_DataSet_Deliv.insert(m_DataSet_Deliv.end(), data);
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_Model::Add(const PSS_SoapData_SymbolAttributes& data)
{
    m_DataSet_SymAttr.insert(m_DataSet_SymAttr.end(), data);
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_Model::Add(const PSS_SoapData_Distribution& data)
{
    m_DataSet_Distrib.insert(m_DataSet_Distrib.end(), data);
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_Model::Add(const PSS_SoapData_DistributionMap& data)
{
    m_DataSet_DistribMap.insert(m_DataSet_DistribMap.end(), data);
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_Model::Add(const PSS_SoapData_Input& data)
{
    m_DataSet_Inputs.insert(m_DataSet_Inputs.end(), data);
}
//---------------------------------------------------------------------------
void PSS_SoapPublisher_Model::AddAlias(const CString& alias)
{
    m_Alias = alias;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublisher_Model::Send()
{
    SOAPDebugger::SetFile(_T("c:\\psssoap.log"));

    TRACE(_T("pPublishModel::send()\n"));
    TRACE(_T("pPublishModel::send().init\n"));

    // create the SOAP proxy
    SOAPProxy proxy(PSS_SoapData_Settings::m_Url.c_str());

    try
    {
        TRACE(_T("pPublishModel::send().pubInit\n"));

        // open the SOAP protocol
        SOAPMethod pubInit(_T("pubInit"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

        // add alias
        pubInit.AddParameter(_T("alias")).SetValue(m_Alias);

        // send the data to SOAP proxy and check the result
        if (int(proxy.Execute(pubInit).GetReturnValue()) < 0)
            throw PSS_SoapException(IDS_PUBINITSERVERFAIL, NULL, __FILE__, __LINE__);
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
        return false;
    }

    int modelID = -1;

    try
    {
        TRACE(_T("pPublishModel::send().pubModel\n"));

        // open the SOAP protocol
        SOAPMethod pubModel(_T("pubModel"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

        // add parameter
        SOAPParameter& mdl = pubModel.AddParameter();
        mdl << m_Model;

        // add alias
        pubModel.AddParameter(_T("alias")).SetValue(m_Alias);

        // send the data to SOAP proxy
        modelID = proxy.Execute(pubModel).GetReturnValue();

        // check the result
        if (modelID < 0)
            throw PSS_SoapException(IDS_PUBMODELSERVERFAIL, m_Model.m_ModelName.c_str(), __FILE__, __LINE__);
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
        return false;
    }

    try
    {
        TRACE(_T("pPublishModel::send().pubProc\n"));

        // model contains processes?
        if (m_DataSet_Proc.size() > 0)
        {
            // open the SOAP protocol
            SOAPMethod pubProc(_T("pubProc"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

            // add model identifier and procedure number
            pubProc.AddParameter(_T("modelid")).SetValue(modelID);
            pubProc.AddParameter(_T("procnbr")).SetValue(int(m_DataSet_Proc.size()));

            SOAPArray<PSS_SoapData_Process> procs;

            // populate the SOAP data array
            for (std::list<PSS_SoapData_Process>::iterator it = m_DataSet_Proc.begin(); it != m_DataSet_Proc.end(); ++it)
                procs.Add(*it);

            // add data set
            SOAPParameter& p = pubProc.AddParameter(_T("proc"));
            p << procs;

            // add alias
            pubProc.AddParameter(_T("alias")).SetValue(m_Alias);

            // send the data to SOAP proxy and check the result
            if (int(proxy.Execute(pubProc).GetReturnValue()) < 0)
                throw PSS_SoapException(IDS_PUBPROCSERVERFAIL, m_Model.m_ModelName.c_str(), __FILE__, __LINE__);
        }
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
        return false;
    }

    try
    {
        TRACE(_T("pPublishModel::send().pubDeliv\n"));

        // model contains deliverables?
        if (m_DataSet_Deliv.size() > 0)
        {
            // open the SOAP protocol
            SOAPMethod pubDeliv(_T("pubDeliv"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

            // add model identifier and deliveries count
            pubDeliv.AddParameter(_T("modelid")).SetValue(modelID);
            pubDeliv.AddParameter(_T("delivnbr")).SetValue(int(m_DataSet_Deliv.size()));
            
            SOAPArray<PSS_SoapData_Deliverable> delivs;

            // populate the SOAP data array
            for (std::list<PSS_SoapData_Deliverable>::iterator it = m_DataSet_Deliv.begin(); it != m_DataSet_Deliv.end(); ++it)
                delivs.Add(*it);

            // add data set
            SOAPParameter& q = pubDeliv.AddParameter(_T("deliv"));
            q << delivs;

            // add alias
            pubDeliv.AddParameter(_T("alias")).SetValue(m_Alias);

            // send the data to SOAP proxy and check the result
            if (int(proxy.Execute(pubDeliv).GetReturnValue()) < 0)
                throw PSS_SoapException(IDS_PUBDELIVSERVERFAIL, m_Model.m_ModelName.c_str(), __FILE__, __LINE__);
        }
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
        return false;
    }

    try
    {
        TRACE(_T("pPublishModel::send().pubPdattr\n"));

        // model contains symbol attributes?
        if (m_DataSet_SymAttr.size() > 0)
        {
            // open the SOAP protocol
            SOAPMethod pubPdattr(_T("pubPdattr"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

            // add model identifier
            pubPdattr.AddParameter(_T("modelid")).SetValue(modelID);

            SOAPArray<PSS_SoapData_SymbolAttributes> pdattrs;

            std::list<PSS_SoapData_SymbolAttributes>::iterator it   = m_DataSet_SymAttr.begin();
            SOAPParameter&                                     size = pubPdattr.AddParameter("pdattrnbr");
            SOAPParameter&                                     r    = pubPdattr.AddParameter("pdattr");

            // add alias
            pubPdattr.AddParameter(_T("alias")).SetValue(m_Alias);

            // populate the SOAP data array
            do
            {
                pdattrs.Empty();

                int x = 0;

                // limit the sending data to 10'000 chunks, otherwise a memory overflow may happen
                do
                {
                    pdattrs.Add(*it);
                    ++it;
                    ++x;
                }
                while ((it != m_DataSet_SymAttr.end()) && (x < 10000));

                size.SetValue(x);

                // add the next data chunk
                r.SetNull();
                r << pdattrs;

                // send the data to SOAP proxy and check the result
                if (int(proxy.Execute( pubPdattr ).GetReturnValue()) < 0)
                    throw PSS_SoapException(IDS_PUBPDATTRSERVERFAIL, m_Model.m_ModelName.c_str(), __FILE__, __LINE__);
            }
            while (it != m_DataSet_SymAttr.end());
        }
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
        return false;
    }

    try
    {
        TRACE(_T("pPublishModel::send().pubDistrib\n"));

        // model contains distributions?
        if (m_DataSet_Distrib.size() > 0)
        {
            // open the SOAP protocol
            SOAPMethod pubDistrib(_T("pubDistrib"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

            pubDistrib.AddParameter(_T("modelid")).SetValue(modelID);
            pubDistrib.AddParameter(_T("distribnbr")).SetValue(int(m_DataSet_Distrib.size()));
            
            SOAPArray<PSS_SoapData_Distribution> distribs;

            // populate the SOAP data array
            for (std::list<PSS_SoapData_Distribution>::iterator it = m_DataSet_Distrib.begin(); it != m_DataSet_Distrib.end(); ++it)
                distribs.Add(*it);

            // add data set
            SOAPParameter& s = pubDistrib.AddParameter(_T("distrib"));
            s << distribs;

            // add alias
            pubDistrib.AddParameter(_T("alias")).SetValue(m_Alias);

            // send the data to SOAP proxy and check the result
            if (int(proxy.Execute(pubDistrib).GetReturnValue()) < 0)
                throw PSS_SoapException(IDS_PUBDISTRIBSERVERFAIL, m_Model.m_ModelName.c_str(), __FILE__, __LINE__);
        }
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
        return false;
    }

    try
    {
        TRACE(_T("pPublishModel::send().pubDistribmap\n"));

        // model contains distribution map?
        if (m_DataSet_DistribMap.size() > 0)
        {
            // open the SOAP protocol
            SOAPMethod pubDistribmap(_T("pubDistribmap"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

            pubDistribmap.AddParameter(_T("modelid")).SetValue(modelID);
            pubDistribmap.AddParameter(_T("distribmapnbr")).SetValue(int(m_DataSet_DistribMap.size()));

            SOAPArray<PSS_SoapData_DistributionMap> distribmaps;

            // populate the SOAP data array
            for (std::list<PSS_SoapData_DistributionMap>::iterator it = m_DataSet_DistribMap.begin();
                    it != m_DataSet_DistribMap.end(); ++it)
                distribmaps.Add(*it);

            // add data set
            SOAPParameter& u = pubDistribmap.AddParameter(_T("distribmap"));
            u << distribmaps;

            // add alias
            pubDistribmap.AddParameter(_T("alias")).SetValue(m_Alias);

            // send the data to SOAP proxy and check the result
            if (int(proxy.Execute(pubDistribmap).GetReturnValue()) < 0)
                throw PSS_SoapException(IDS_PUBDISTRIBMAPSERVERFAIL, m_Model.m_ModelName.c_str(), __FILE__, __LINE__);
        }
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
        return false;
    }

    try
    {
        TRACE(_T("pPublishModel::send().pubInput\n"));

        // model contains inputs?
        if (m_DataSet_Inputs.size() > 0)
        {
            // open the SOAP protocol
            SOAPMethod pubInput(_T("pubInput"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

            pubInput.AddParameter(_T("modelid")).SetValue(modelID);
            pubInput.AddParameter(_T("inputnbr")).SetValue(int(m_DataSet_Inputs.size()));
            
            SOAPArray<PSS_SoapData_Input> inputs;

            // populate the SOAP data array
            for (std::list<PSS_SoapData_Input>::iterator it = m_DataSet_Inputs.begin(); it != m_DataSet_Inputs.end(); ++it)
                inputs.Add(*it);

            // add data set
            SOAPParameter& t = pubInput.AddParameter(_T("input"));
            t << inputs;

            // add alias
            pubInput.AddParameter(_T("alias")).SetValue(m_Alias);

            // send the data to SOAP proxy and check the result
            if (int(proxy.Execute(pubInput).GetReturnValue()) < 0)
                throw PSS_SoapException(IDS_PUBINPUTSERVERFAIL, m_Model.m_ModelName.c_str(), __FILE__, __LINE__);
        }
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
        return false;
    }

    try
    {
        TRACE(_T("pPublishModel::send().pubDone\n"));

        // notify that publication was processed
        SOAPMethod pubDone(_T("pubDone"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

        // send the data to SOAP proxy and check the result
        if (int(proxy.Execute(pubDone).GetReturnValue()) < 0)
            throw PSS_SoapException(IDS_PUBDONESERVERFAIL, m_Model.m_ModelName.c_str(), __FILE__, __LINE__);
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
        return false;
    }

    TRACE(_T("pPublishModel::send().complete\n"));
    return true;
}
//---------------------------------------------------------------------------
int PSS_SoapPublisher_Model::GetModelVersion(const std::string& modelref )
{
    SOAPDebugger::SetFile(_T("c:\\psssoap.log"));

    try
    {
        TRACE(_T("pPublishModel::getModelVersion %s\n"), modelref.c_str());

        // create the SOAP proxy
        SOAPProxy proxy(PSS_SoapData_Settings::m_Url.c_str());

        // open the SOAP protocol
        SOAPMethod pubGetModelVersion(_T("pubGetModelVersion"), PSS_SoapData_Settings::m_ModelService.c_str(), _T("http://"));

        // set model reference and alias
        pubGetModelVersion.AddParameter(_T("modelref")).SetValue(modelref.c_str());
        pubGetModelVersion.AddParameter(_T("alias")).SetValue(m_Alias);

        // execute the query and return the result
        return proxy.Execute(pubGetModelVersion).GetReturnValue();
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
    }

    return -1;
}
//---------------------------------------------------------------------------
