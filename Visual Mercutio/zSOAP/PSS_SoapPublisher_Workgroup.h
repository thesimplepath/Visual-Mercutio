/****************************************************************************
 * ==> PSS_SoapPublisher_Workgroup -----------------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish a workgroup                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublisher_WorkgroupH
#define PSS_SoapPublisher_WorkgroupH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_SoapData_Workgroup.h"

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
* SOAP serialization and deserialization for published workgroup
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_Workgroup>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("pworkgroup"), _T("urn:xml-soap-emessenger"));
        }

        /**
        * Serializes a SOAP agent content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_Workgroup& data)
        {
            param.AddParameter(_T("wkgid"))     << data.m_WkGrpID.c_str();
            param.AddParameter(_T("wkgparent")) << data.m_WkGrpParent.c_str();
            param.AddParameter(_T("wkgname"))   << data.m_WkGrpName.c_str();
            param.AddParameter(_T("mission"))   << data.m_Mission.c_str();
            param.AddParameter(_T("daycost"))   << data.m_DayCost.c_str();

            return param;
        }

        /**
        * Deserializes a SOAP agent content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_Workgroup& data)
        {
            SOAPString tmp;

            param.GetParameter(_T("wkgid"))     >> tmp; data.m_WkGrpID     = tmp.Str();
            param.GetParameter(_T("wkgparent")) >> tmp; data.m_WkGrpParent = tmp.Str();
            param.GetParameter(_T("wkgname"))   >> tmp; data.m_WkGrpName   = tmp.Str();
            param.GetParameter(_T("mission"))   >> tmp; data.m_Mission     = tmp.Str();
            param.GetParameter(_T("daycost"))   >> tmp; data.m_DayCost     = tmp.Str();

            return param;
        }
};

/**
* SOAP workgroup data array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_Workgroup> > : public SOAPArrayTypeTraits
{};

/**
* SOAP protocol to publish the workgroup
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublisher_Workgroup
{
    public:
        PSS_SoapPublisher_Workgroup();
        virtual ~PSS_SoapPublisher_Workgroup();

        /**
        * Resets the data (empty the lists)
        */
        virtual void Reset();

        /**
        * Adds a SOAP data
        *@param data - SOAP data to add
        */
        virtual void Add(const PSS_SoapData_Workgroup& data);

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
        CString                           m_Alias;
        std::list<PSS_SoapData_Workgroup> m_DataSet;
};

END_EASYSOAP_NAMESPACE

#endif
