/****************************************************************************
 * ==> PSS_SoapPublisher_Prestations ---------------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish the prestations                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublisher_PrestationsH
#define PSS_SoapPublisher_PrestationsH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zConversion\PSS_String16.h"
#include "PSS_SoapData_Prestations.h"

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
* SOAP serialization and deserialization for published prestations
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_Prestations>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("pprestations"), _T("urn:xml-soap-emessenger"));
        }

        /**
        * Serializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_Prestations& data)
        {
            param.AddParameter(_T("prestationid"))     << data.m_PrestationID.c_str();
            param.AddParameter(_T("prestationparent")) << data.m_PrestationParent.c_str();
            param.AddParameter(_T("prestationtitle"))  << data.m_PrestationTitle.c_str();

            return param;
        }

        /**
        * Deserializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_Prestations& data)
        {
            SOAPString tmp;

            param.GetParameter(_T("prestationid"))     >> tmp; data.m_PrestationID     = tmp.Str();
            param.GetParameter(_T("prestationparent")) >> tmp; data.m_PrestationParent = tmp.Str();
            param.GetParameter(_T("prestationtitle"))  >> tmp; data.m_PrestationTitle  = tmp.Str();

            return param;
        }
};

/**
* SOAP prestations data array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_Prestations> > : public SOAPArrayTypeTraits
{};

/**
* SOAP protocol to publish the prestations
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS pPublishPrestations
{
    public:
        pPublishPrestations();
        virtual ~pPublishPrestations();

        /**
        * Resets the data (empty the lists)
        */
        virtual void Reset();

        /**
        * Adds a SOAP data
        *@param data - SOAP data to add
        */
        virtual void Set(const PSS_SoapData_Prestations& data);

        /**
        * Adds required alias for publication
        *@param alias - alias to add
        */
        virtual void AddAlias(const CString& alias);

        /**
        * Sends data
        *@return true on success, otherwise false
        */
        virtual bool Send();

    private:
        CString                             m_Alias;
        std::list<PSS_SoapData_Prestations> m_DataSet;
};

END_EASYSOAP_NAMESPACE

#endif
