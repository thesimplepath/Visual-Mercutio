/****************************************************************************
 * ==> PSS_SoapPublisher_File ----------------------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish the files                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef __PPUBLISHFILE_HDR_
#define __PPUBLISHFILE_HDR_

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_SoapData_File.h"

#ifdef _ZSOAPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

BEGIN_EASYSOAP_NAMESPACE

/**
* SOAP serialization and deserialization for published files
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_File>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("pfile"), _T("urn:xml-soap-pssfile"));
        }

        /**
        * Serializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_File& data)
        {
            param.AddParameter(_T("len"))    << int(data.m_Len);
            param.AddParameter(_T("folder")) << int(data.m_Folder);
            param.AddParameter(_T("crc"))    << int(data.m_Crc);
            param.AddParameter(_T("doc"))    << data.m_Doc.c_str();
            param.AddParameter(_T("fname"))  << data.m_FileName.c_str();

            return param;
        }

        /**
        * Deserializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_File& data)
        {
            SOAPString tmp;
            int        v;

            param.GetParameter(_T("len"))    >> v;   data.m_Len      = v;
            param.GetParameter(_T("folder")) >>      data.m_Folder;
            param.GetParameter(_T("crc"))    >> v;   data.m_Crc      = v;
            param.GetParameter(_T("doc"))    >> tmp; data.m_Doc      = tmp.Str();
            param.GetParameter(_T("fname"))  >> tmp; data.m_FileName = tmp.Str();

            return param;
        }
};

/**
* SOAP process data array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_File> > : public SOAPArrayTypeTraits
{};

/**
* SOAP serialization and deserialization for published files
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublisher_File
{
    public:
        PSS_SoapPublisher_File();
        virtual ~PSS_SoapPublisher_File();

        /**
        * Adds a file
        *@param file - file to add
        *@return true on success, otherwise false
        */
        virtual bool Add(const PSS_SoapData_File& file);

        /**
        * Checks if the file has changed on the server recently
        *@param folder - folder name
        *@param fileName - file name
        *@param day - day
        *@param month - month
        *@param year - year
        *@param hour - hour
        *@param min - minutes
        *@param sec - seconds
        *@return 0 if file hasn't changed, 1 if a recent file is available, -1 if old file available
        */
        virtual int HasChanged(int                folder, 
                               const std::string& fileName, 
                               int                day,
                               int                month,
                               int                year,
                               int                hour,
                               int                min,
                               int                sec);

        /**
        * Downloads and gets the file from the server
        *@param folder - folder name
        *@param fileName - file name to download and get
        *@return downloaded file
        */
        virtual PSS_SoapData_File GetFile(int folder, const std::string& fileName);
};

END_EASYSOAP_NAMESPACE

#endif
