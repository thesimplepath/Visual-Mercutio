/****************************************************************************
 * ==> PSS_SoapPublisher_File ----------------------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish the files                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SoapPublisher_File.h"

// processsoft
#include "PSS_SoapPublisher_Settings.h"
#include "zSoapException.h"

//---------------------------------------------------------------------------
// PSS_SoapPublisher_File
//---------------------------------------------------------------------------
PSS_SoapPublisher_File::PSS_SoapPublisher_File()
{}
//---------------------------------------------------------------------------
PSS_SoapPublisher_File::~PSS_SoapPublisher_File()
{}
//---------------------------------------------------------------------------
bool PSS_SoapPublisher_File::Add(const PSS_SoapData_File& file)
{
    SOAPDebugger::SetFile(_T("c:\\psssoap_pufile.log"));

    bool result = true;

    try
    {
        // create the SOAP proxy
        SOAPProxy proxy(PSS_SoapPublisher_Settings::m_Url.c_str());

        // open the SOAP protocol
        SOAPMethod pubFile(_T("pubFile"), PSS_SoapPublisher_Settings::m_FileService.c_str(), _T("http://"));

        // add the file
        SOAPParameter& ref = pubFile.AddParameter(_T("mfile"));
        ref << file;

        // send the data to SOAP proxy and check the result
        if (int(proxy.Execute(pubFile).GetReturnValue()) < 0)
        {
            TRACE(_T("Pub file failed\n"));
            result = false;
        }
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
int PSS_SoapPublisher_File::HasChanged(int                folder,
                                       const std::string& filename,
                                       int                day,
                                       int                month,
                                       int                year,
                                       int                hour,
                                       int                min,
                                       int                sec)
{
    return 0;
}
//---------------------------------------------------------------------------
PSS_SoapData_File PSS_SoapPublisher_File::GetFile(int folder, const std::string& filename)
{
    SOAPDebugger::SetFile(_T("c:\\psssoap.log"));
    PSS_SoapData_File result;

    try
    {
        //not from config engine at time....pPublishSettings::service;
        std::string wdslUrn = _T("urn:pssfile");

        // create the SOAP proxy
        SOAPProxy proxy(PSS_SoapPublisher_Settings::m_Url.c_str());

        // open the SOAP protocol
        SOAPMethod getFile(_T("pubGetFile"), wdslUrn.c_str(), _T("http://"));

        // set folder and file name
        getFile.AddParameter(_T("mfolder")).SetValue(folder);
        getFile.AddParameter(_T("mfilename")).SetValue(filename.c_str());

        // execute the query
        const SOAPResponse& resp = proxy.Execute(getFile);

        // get file data
        resp.GetReturnValue() >> result;
    }
    catch (SOAPException& ex)
    {
        TRACE(_T("Caught SOAP exception:%s\n"), ex.What().Str());
        return PSS_SoapData_File();
    }

    return result;
}
//---------------------------------------------------------------------------
