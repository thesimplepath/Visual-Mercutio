/****************************************************************************
 * ==> PSS_SoapPublisher_ModelAttributes -----------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish the model attributes              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublisher_ModelAttributesH
#define PSS_SoapPublisher_ModelAttributesH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_SoapData_ModelAttributes.h"

#ifdef _ZSOAPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

USING_EASYSOAP_NAMESPACE
BEGIN_EASYSOAP_NAMESPACE

/**
* SOAP serialization and deserialization for published model attributes
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_ModelAttributes>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("pattribdef"), _T("urn:xml-soap-emessenger"));
        }

        /**
        * Serializes a SOAP agent content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_ModelAttributes& data)
        {
            param.AddParameter(_T("attribdefid"))   << data.m_AttribDefID;
            param.AddParameter(_T("attribgrpid"))   << data.m_AttribGrpID;
            param.AddParameter(_T("attribdefname")) << data.m_AttribDefName.c_str();
            param.AddParameter(_T("attribdeftype")) << data.m_AttribDefType;
            param.AddParameter(_T("attribdefreq"))  << data.m_AttribDefFreq;

            return param;
        }

        /**
        * Deserializes a SOAP agent content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_ModelAttributes& data)
        {
            SOAPString tmp;

            param.GetParameter(_T("attribdefid"))   >>      data.m_AttribDefID;
            param.GetParameter(_T("attribgrpid"))   >>      data.m_AttribGrpID;
            param.GetParameter(_T("attribdefname")) >> tmp; data.m_AttribDefName = tmp.Str();
            param.GetParameter(_T("attribdeftype")) >>      data.m_AttribDefType;
            param.GetParameter(_T("attribdefreq"))  >>      data.m_AttribDefFreq;

            return param;
        }
};

/**
* SOAP model attribute agent array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_ModelAttributes> > : public SOAPArrayTypeTraits
{};

/**
* SOAP protocol to publish the model attributes
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublisher_ModelAttributes
{
    public:
        PSS_SoapPublisher_ModelAttributes();
        virtual ~PSS_SoapPublisher_ModelAttributes();

        /**
        * Resets the data (empty the lists)
        */
        virtual void Reset();

        /**
        * Adds a SOAP data
        *@param data - SOAP data to add
        */
        virtual void Add(const PSS_SoapData_ModelAttributes& data);

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
        CString                            m_Alias;
        list<PSS_SoapData_ModelAttributes> m_DataSet;
};

END_EASYSOAP_NAMESPACE

#endif
