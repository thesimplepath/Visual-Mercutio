/****************************************************************************
 * ==> PSS_SoapPublisher_Model ---------------------------------------------*
 ****************************************************************************
 * Description : SOAP protocol to publish the model                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublisher_ModelH
#define PSS_SoapPublisher_ModelH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_SoapData_Model.h"
#include "PSS_SoapData_Process.h"
#include "PSS_SoapData_Deliverable.h"
#include "PSS_SoapData_SymbolAttributes.h"
#include "PSS_SoapData_Distribution.h"
#include "PSS_SoapData_DistributionMap.h"
#include "PSS_SoapData_Input.h"

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
* SOAP serialization and deserialization for published processes
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_Process>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("pproc"), _T("urn:xml-soap-emessenger"));
        }

        /**
        * Serializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_Process& data)
        {
            param.AddParameter(_T("procid"))          << data.m_ProcID;
            param.AddParameter(_T("wkgid"))           << data.m_WkGrpID.c_str();
            param.AddParameter(_T("proctype"))        << data.m_ProcType;
            param.AddParameter(_T("doublesign"))      << data.m_DoubleSign;
            param.AddParameter(_T("procidprocessus")) << data.m_ProcIDProcessus;
            return param;
        }

        /**
        * Deserializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_Process& data)
        {
            SOAPString tmp;

            param.GetParameter(_T("procid"))          >>      data.m_ProcID;
            param.GetParameter(_T("wkgid"))           >> tmp; data.m_WkGrpID = tmp.Str();
            param.GetParameter(_T("proctype"))        >>      data.m_ProcType;
            param.GetParameter(_T("doublesign"))      >>      data.m_DoubleSign;
            param.GetParameter(_T("procidprocessus")) >>      data.m_ProcIDProcessus;
            return param;
        }
};

/**
* SOAP process data array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_Process> > : public SOAPArrayTypeTraits
{};

/**
* SOAP serialization and deserialization for published deliveries
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_Deliverable>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("pdeliv"), _T("urn:xml-soap-emessenger"));
        }

        /**
        * Serializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_Deliverable& data)
        {
            param.AddParameter(_T("delivid"))          << data.m_DelivID;
            param.AddParameter(_T("procidsrc"))        << data.m_ProcIDSrc;
            param.AddParameter(_T("procidtrg"))        << data.m_ProcIDTrg;
            param.AddParameter(_T("delivname"))        << data.m_DelivName.c_str();
            param.AddParameter(_T("lateral"))          << data.m_Lateral;
            param.AddParameter(_T("lateraldirection")) << data.m_LateralDirection;
            param.AddParameter(_T("doublesign"))       << data.m_DoubleSign;

            return param;
        }

        /**
        * Deserializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_Deliverable& data)
        {
            SOAPString tmp;

            param.GetParameter(_T("delivid"))          >>      data.m_DelivID;
            param.GetParameter(_T("procidsrc"))        >>      data.m_ProcIDSrc;
            param.GetParameter(_T("procidtrg"))        >>      data.m_ProcIDTrg;
            param.GetParameter(_T("delivname"))        >> tmp; data.m_DelivName = tmp.Str();
            param.GetParameter(_T("lateral"))          >>      data.m_Lateral;
            param.GetParameter(_T("lateraldirection")) >>      data.m_LateralDirection;
            param.GetParameter(_T("doublesign"))       >>      data.m_DoubleSign;

            return param;
        }
};

/**
* SOAP delivery data array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_Deliverable> > : public SOAPArrayTypeTraits
{};

/**
* SOAP serialization and deserialization for published models
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_Model>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("pmodel"), _T("urn:xml-soap-emessenger"));
        }

        /**
        * Serializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_Model& data)
        {
            param.AddParameter(_T("modelname")) << data.m_ModelName.c_str();
            param.AddParameter(_T("modelref"))  << data.m_ModelRef.c_str();
            param.AddParameter(_T("startdate")) << data.m_StartDate.c_str();
            param.AddParameter(_T("enddate"))   << data.m_EndDate.c_str();

            return param;
        }

        /**
        * Deserializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_Model& data)
        {
            SOAPString tmp;

            param.GetParameter(_T("modelname")) >>tmp; data.m_ModelName = tmp.Str();
            param.GetParameter(_T("modelref"))  >>tmp; data.m_ModelRef  = tmp.Str();
            param.GetParameter(_T("startdate")) >>tmp; data.m_StartDate = tmp.Str();
            param.GetParameter(_T("enddate"))   >>tmp; data.m_EndDate   = tmp.Str();

            return param;
        }
};

/**
* SOAP model data array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_Model> > : public SOAPArrayTypeTraits
{};

/**
* SOAP serialization and deserialization for published symbol attributes
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_SymbolAttributes>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("ppdattr"), _T("urn:xml-soap-emessenger"));
        }

        /**
        * Serializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_SymbolAttributes& data)
        {
            param.AddParameter(_T("pdattribid"))  << data.m_PdAttribID;
            param.AddParameter(_T("prow"))        << data.m_Prow;
            param.AddParameter(_T("attribdefid")) << data.m_AttribDefID;
            param.AddParameter(_T("mvalue"))      << data.m_MValue.c_str();

            return param;
        }

        /**
        * Deserializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_SymbolAttributes& data)
        {
            SOAPString tmp;

            param.GetParameter(_T("pdattribid"))  >>     data.m_PdAttribID;
            param.GetParameter(_T("prow"))        >>     data.m_Prow;
            param.GetParameter(_T("attribdefid")) >>     data.m_AttribDefID;
            param.GetParameter(_T("mvalue"))      >>tmp; data.m_MValue = tmp.Str();

            return param;
        }
};

/**
* SOAP symbol attributes data array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_SymbolAttributes> > : public SOAPArrayTypeTraits
{};

/**
* SOAP serialization and deserialization for published distributions
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_Distribution>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("pdistrib"), _T("urn:xml-soap-emessenger"));
        }

        /**
        * Serializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_Distribution& data)
        {
            param.AddParameter(_T("wkgid"))       << data.m_WkGrpID.c_str();
            param.AddParameter(_T("attribdefid")) << data.m_AttribDefID;
            param.AddParameter(_T("mop"))         << data.m_Mop;
            param.AddParameter(_T("mdata"))       << data.m_MData.c_str();

            return param;
        }

        /**
        * Deserializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_Distribution& data)
        {
            SOAPString tmp;

            param.GetParameter(_T("wkgid"))       >> tmp; data.m_WkGrpID = tmp.Str();
            param.GetParameter(_T("attribdefid")) >>      data.m_AttribDefID;
            param.GetParameter(_T("mop"))         >>      data.m_Mop;
            param.GetParameter(_T("mdata"))       >> tmp; data.m_MData = tmp.Str();

            return param;
        }
};

/**
* SOAP symbol distribution data array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_Distribution> > : public SOAPArrayTypeTraits
{};

/**
* SOAP serialization and deserialization for published distribution maps
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_DistributionMap>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("pdistribmap"), _T("urn:xml-soap-emessenger"));
        }

        /**
        * Serializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_DistributionMap& data)
        {
            param.AddParameter(_T("pdattribid"))  << data.m_PdAttribID;
            param.AddParameter(_T("attribdefid")) << data.m_AttribDefID;
            param.AddParameter(_T("mdata"))       << data.m_MData.c_str();
            param.AddParameter(_T("mlop"))        << data.m_Mlop;

            return param;
        }

        /**
        * Deserializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_DistributionMap& data)
        {
            SOAPString tmp;

            param.GetParameter(_T("pdattribid"))  >>      data.m_PdAttribID;
            param.GetParameter(_T("attribdefid")) >>      data.m_AttribDefID;
            param.GetParameter(_T("mdata"))       >> tmp; data.m_MData = tmp.Str();
            param.GetParameter(_T("mlop"))        >>      data.m_Mlop;

            return param;
        }
};

/**
* SOAP symbol distribution map data array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_DistributionMap> > : public SOAPArrayTypeTraits
{};

/**
* SOAP serialization and deserialization for published inputs
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits<PSS_SoapData_Input>
{
    public:
        /**
        * Gets type
        *@param qName - type name
        */
        static void GetType(SOAPQName& qName)
        {
            qName.Set(_T("pinput"), _T("urn:xml-soap-emessenger"));
        }

        /**
        * Serializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to serialize
        */
        static SOAPParameter& Serialize(SOAPParameter& param, const PSS_SoapData_Input& data)
        {    
            //param.AddParameter(_T("modelid"))      << data.m_ModelID;
            param.AddParameter(_T("pdattribid"))   << data.m_PdAttribID;
            param.AddParameter(_T("attribdefid"))  << data.m_AttribDefID;
            param.AddParameter(_T("mdefval"))      << data.m_MDefVal.c_str();
            param.AddParameter(_T("mflag"))        << data.m_MFlag;
            param.AddParameter(_T("constraintid")) << data.m_ConstraintID;

            return param;
        }

        /**
        * Deserializes a SOAP data content
        *@param param - SOAP parameters
        *@param data - SOAP data to deserialize
        */
        static const SOAPParameter& Deserialize(const SOAPParameter& param, PSS_SoapData_Input& data)
        {
            SOAPString tmp;

            //param.GetParameter(_T("modelid"))      >>      data.m_ModelID;
            param.GetParameter(_T("pdattribid"))   >>      data.m_PdAttribID;
            param.GetParameter(_T("attribdefid"))  >>      data.m_AttribDefID;
            param.GetParameter(_T("mdefval"))      >> tmp; data.m_MDefVal = tmp.Str();
            param.GetParameter(_T("mflag"))        >>      data.m_MFlag;
            param.GetParameter(_T("constraintid")) >>      data.m_ConstraintID;

            return param;
        }
};

/**
* SOAP input data array
*@author Dominique Aigroz, Jean-Milost Reymond
*/
template<>
class SOAPTypeTraits< SOAPArray<PSS_SoapData_Input> > : public SOAPArrayTypeTraits
{};

/**
* SOAP protocol to publish the model data
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublisher_Model
{
    public:
        PSS_SoapPublisher_Model();
        virtual ~PSS_SoapPublisher_Model();

        /**
        * Resets the data (empty the lists)
        */
        virtual void Reset();

        /**
        * Sets the model
        *@param model - model
        */
        virtual void SetModel(const PSS_SoapData_Model& model);

        /**
        * Adds a SOAP data
        *@param data - SOAP data to add
        */
        virtual void Add(const PSS_SoapData_Process&          data);
        virtual void Add(const PSS_SoapData_Deliverable&      data);
        virtual void Add(const PSS_SoapData_SymbolAttributes& data);
        virtual void Add(const PSS_SoapData_Distribution&     data);
        virtual void Add(const PSS_SoapData_DistributionMap&  data);
        virtual void Add(const PSS_SoapData_Input&            data);

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

        /**
        * Gets the model version
        *@param model - model name
        *@return model version
        */
        virtual int GetModelVersion(const std::string& model);

    private:
        CString                                  m_Alias;
        PSS_SoapData_Model                       m_Model;
        std::list<PSS_SoapData_Process>          m_DataSet_Proc;
        std::list<PSS_SoapData_Deliverable>      m_DataSet_Deliv;
        std::list<PSS_SoapData_SymbolAttributes> m_DataSet_SymAttr;
        std::list<PSS_SoapData_Distribution>     m_DataSet_Distrib;
        std::list<PSS_SoapData_DistributionMap>  m_DataSet_DistribMap;
        std::list<PSS_SoapData_Input>            m_DataSet_Inputs;
};

END_EASYSOAP_NAMESPACE

#endif
