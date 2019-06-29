/****************************************************************************
 * ==> PSS_SoapPublisher_MessengerUniverse ---------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish the Messenger universe            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublisher_MessengerUniverseH
#define PSS_SoapPublisher_MessengerUniverseH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zConversion\PSS_String16.h"
#include "zConversion\PSS_StringTools.h"
#include "PSS_SoapData_MessengerUniverse.h"

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
* SOAP serialization and deserialization for published Messenger universes
*@author Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_MessengerUniverse>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("puniverse"), _T("urn:xml-soap-emessenger"));
        }

        /**
        * Serializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_MessengerUniverse& data)
        {
            param.AddParameter(_T("guidSystem"))     << data.m_GuidSystem.c_str();
            param.AddParameter(_T("guidPrestation")) << data.m_GuidPrestation.c_str();
            param.AddParameter(_T("guidWorkgroup"))  << data.m_GuidWorkgroup.c_str();

            return param;
        }

        /**
        * Deserializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_MessengerUniverse& data)
        {
            SOAPString tmp;

            param.GetParameter(_T("guidSystem"))     >> tmp; data.m_GuidSystem     = tmp.Str();
            param.GetParameter(_T("guidPrestation")) >> tmp; data.m_GuidPrestation = tmp.Str();
            param.GetParameter(_T("guidWorkgroup"))  >> tmp; data.m_GuidWorkgroup  = tmp.Str();

            return param;
        }
};

/**
* SOAP Messenger universe data array
*@author Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_MessengerUniverse> > : public SOAPArrayTypeTraits
{};

/**
* SOAP protocol to publish the Messenger universes
*@author Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublisher_MessengerUniverse
{
    public:

        PSS_SoapPublisher_MessengerUniverse();
        virtual ~PSS_SoapPublisher_MessengerUniverse();

        /**
        * Resets the data (empty the lists)
        */
        virtual void Reset();

        /**
        * Adds a SOAP data
        *@param data - SOAP data to add
        */
        virtual void Add(const PSS_SoapData_MessengerUniverse& data);

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
        CString                              m_Alias;
        list<PSS_SoapData_MessengerUniverse> m_DataSet;
};

END_EASYSOAP_NAMESPACE

#endif
