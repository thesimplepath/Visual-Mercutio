/****************************************************************************
 * ==> PSS_SoapPublisher_System --------------------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish a system                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublisher_SystemH
#define PSS_SoapPublisher_SystemH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zConversion\PSS_String16.h"
#include "PSS_SoapData_System.h"

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
* SOAP serialization and deserialization for published system
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_System>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("psystem"), _T("urn:xml-soap-emessenger"));
        }

        /**
        * Serializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_System& data)
        {
            param.AddParameter(_T("systemid"))     << data.m_SystemID.c_str();
            param.AddParameter(_T("systemparent")) << data.m_SystemParent.c_str();
            param.AddParameter(_T("systemtitle"))  << data.m_SystemTitle.c_str();
            param.AddParameter(_T("command"))      << data.m_Command.c_str();
            param.AddParameter(_T("parameters"))   << data.m_Parameters.c_str();
            param.AddParameter(_T("directory"))    << data.m_Directory.c_str();
            param.AddParameter(_T("priority"))     << data.m_Priority;
            param.AddParameter(_T("windowst"))     << data.m_Windowst;

            return param;
        }

        /**
        * Deserializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_System& data)
        {
            SOAPString tmp;

            param.GetParameter(_T("systemid"))     >> tmp; data.m_SystemID     = tmp.Str();
            param.GetParameter(_T("systemparent")) >> tmp; data.m_SystemParent = tmp.Str();
            param.GetParameter(_T("systemtitle"))  >> tmp; data.m_SystemTitle  = tmp.Str();
            param.GetParameter(_T("command"))      >> tmp; data.m_Command      = tmp.Str();
            param.GetParameter(_T("parameters"))   >> tmp; data.m_Parameters   = tmp.Str();
            param.GetParameter(_T("directory"))    >> tmp; data.m_Directory    = tmp.Str();
            param.GetParameter(_T("priority"))     >>      data.m_Priority;
            param.GetParameter(_T("windowst"))     >>      data.m_Windowst;

            return param;
        }
};

/**
* SOAP system data array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_System> > : public SOAPArrayTypeTraits
{};

/**
* SOAP protocol to publish the system
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublisher_System
{
    public:
        PSS_SoapPublisher_System();
        virtual ~PSS_SoapPublisher_System();

        /**
        * Resets the data (empty the lists)
        */
        virtual void Reset();

        /**
        * Adds a SOAP data
        *@param data - SOAP data to add
        */
        virtual void Add(const PSS_SoapData_System& data);

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
        CString                        m_Alias;
        std::list<PSS_SoapData_System> m_DataSet;
};

END_EASYSOAP_NAMESPACE

#endif
