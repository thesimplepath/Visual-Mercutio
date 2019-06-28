/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module XXXClass.h | Interface of the <c XXXClass> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Gaya
// <nl>Created:         03/2002
// <nl>Description:  XXXClass frame window support
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __PPUBLISHMODEL_HDR_
#define __PPUBLISHMODEL_HDR_

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "pmodel.h"
#include "pproc.h"
#include "pdeliv.h"
#include "ppdattr.h"
#include "pinput.h"
#include "pdistrib.h"
#include "pdistribmap.h"

#ifdef _ZSOAPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 15 septembre 2005 - Ajout de la décoration Unicode _T( ) pour les chaînes de caractères de cette classe.

//Define serializers / soap mapping

/////////////////////////////////////////////
// pproc soap mapping
BEGIN_EASYSOAP_NAMESPACE

template<>
class SOAPTypeTraits<pproc>
{
    public:
        static void GetType(SOAPQName& qname)
        {
            qname.Set(_T("pproc"), _T("urn:xml-soap-emessenger"));
        }

        static SOAPParameter& Serialize(SOAPParameter& param, const pproc& val)
        {
            param.AddParameter(_T("procid"))          << val.m_ProcID;
            param.AddParameter(_T("wkgid"))           << val.m_WkGrpID.c_str();
            param.AddParameter(_T("proctype"))        << val.m_ProcType;
            param.AddParameter(_T("doublesign"))      << val.m_DoubleSign;
            param.AddParameter(_T("procidprocessus")) << val.m_ProcIDProcessus;
            return param;
        }

        static const SOAPParameter& Deserialize(const SOAPParameter& param, pproc& val)
        {
            SOAPString tmp;

            param.GetParameter(_T("procid"))          >>      val.m_ProcID;
            param.GetParameter(_T("wkgid"))           >> tmp; val.m_WkGrpID = tmp.Str();
            param.GetParameter(_T("proctype"))        >>      val.m_ProcType;
            param.GetParameter(_T("doublesign"))      >>      val.m_DoubleSign;
            param.GetParameter(_T("procidprocessus")) >>      val.m_ProcIDProcessus;
            return param;
        }
};

template<>
class SOAPTypeTraits< SOAPArray<pproc> > : public SOAPArrayTypeTraits
{};

/////////////////////////////////////////////
// pdeliv soap mapping
template<>
class SOAPTypeTraits<pdeliv>
{
    public:
        static void GetType(SOAPQName& qname)
        {
            qname.Set(_T("pdeliv"), _T("urn:xml-soap-emessenger"));
        }

        static SOAPParameter& Serialize(SOAPParameter& param, const pdeliv& val)
        {
            param.AddParameter(_T("delivid"))          << val.m_DelivID;
            param.AddParameter(_T("procidsrc"))        << val.m_ProcIDSrc;
            param.AddParameter(_T("procidtrg"))        << val.m_ProcIDTrg;
            param.AddParameter(_T("delivname"))        << val.m_DelivName.c_str();
            param.AddParameter(_T("lateral"))          << val.m_Lateral;
            param.AddParameter(_T("lateraldirection")) << val.m_LateralDirection;
            param.AddParameter(_T("doublesign"))       << val.m_DoubleSign;

            return param;
        }

        static const SOAPParameter& Deserialize(const SOAPParameter& param, pdeliv& val)
        {
            SOAPString tmp;

            param.GetParameter(_T("delivid"))          >>      val.m_DelivID;
            param.GetParameter(_T("procidsrc"))        >>      val.m_ProcIDSrc;
            param.GetParameter(_T("procidtrg"))        >>      val.m_ProcIDTrg;
            param.GetParameter(_T("delivname"))        >> tmp; val.m_DelivName = tmp.Str();
            param.GetParameter(_T("lateral"))          >>      val.m_Lateral;
            param.GetParameter(_T("lateraldirection")) >>      val.m_LateralDirection;
            param.GetParameter(_T("doublesign"))       >>      val.m_DoubleSign;

            return param;
        }
};

template<>
class SOAPTypeTraits< SOAPArray<pdeliv> > : public SOAPArrayTypeTraits
{};

/////////////////////////////////////////////
// pmodel soap mapping
template<>
class SOAPTypeTraits<pmodel>
{
    public:
        static void GetType(SOAPQName& qname)
        {
            qname.Set(_T("pmodel"), _T("urn:xml-soap-emessenger"));
        }

        static SOAPParameter& Serialize(SOAPParameter& param, const pmodel& val)
        {
            param.AddParameter(_T("modelname")) << val.m_ModelName.c_str();
            param.AddParameter(_T("modelref"))  << val.m_ModelRef.c_str();
            param.AddParameter(_T("startdate")) << val.m_StartDate.c_str();
            param.AddParameter(_T("enddate"))   << val.m_EndDate.c_str();

            return param;
        }

        static const SOAPParameter& Deserialize(const SOAPParameter& param, pmodel& val)
        {
            SOAPString tmp;

            param.GetParameter(_T("modelname")) >>tmp; val.m_ModelName = tmp.Str();
            param.GetParameter(_T("modelref"))  >>tmp; val.m_ModelRef  = tmp.Str();
            param.GetParameter(_T("startdate")) >>tmp; val.m_StartDate = tmp.Str();
            param.GetParameter(_T("enddate"))   >>tmp; val.m_EndDate   = tmp.Str();

            return param;
        }
};

template<>
class SOAPTypeTraits< SOAPArray<pmodel> > : public SOAPArrayTypeTraits
{};

/////////////////////////////////////////////
// ppdattr soap mapping
template<>
class SOAPTypeTraits<ppdattr>
{
    public:
        static void GetType(SOAPQName& qname)
        {
            qname.Set(_T("ppdattr"), _T("urn:xml-soap-emessenger"));
        }

        static SOAPParameter& Serialize( SOAPParameter& param, const ppdattr& val )
        {
            param.AddParameter(_T("pdattribid"))  << val.m_PdAttribID;
            param.AddParameter(_T("prow"))        << val.m_Prow;
            param.AddParameter(_T("attribdefid")) << val.m_AttribDefID;
            param.AddParameter(_T("mvalue"))      << val.m_MValue.c_str();

            return param;
        }

        static const SOAPParameter& Deserialize(const SOAPParameter& param, ppdattr& val)
        {
            SOAPString tmp;

            param.GetParameter(_T("pdattribid"))  >>     val.m_PdAttribID;
            param.GetParameter(_T("prow"))        >>     val.m_Prow;
            param.GetParameter(_T("attribdefid")) >>     val.m_AttribDefID;
            param.GetParameter(_T("mvalue"))      >>tmp; val.m_MValue = tmp.Str();

            return param;
        }
};

template<>
class SOAPTypeTraits< SOAPArray<ppdattr> > : public SOAPArrayTypeTraits
{};

/////////////////////////////////////////////
// pdistrib soap mapping
template<>
class SOAPTypeTraits<pdistrib>
{
    public:
        static void GetType(SOAPQName& qname)
        {
            qname.Set(_T("pdistrib"), _T("urn:xml-soap-emessenger"));
        }

        static SOAPParameter& Serialize(SOAPParameter& param, const pdistrib& val)
        {
            param.AddParameter(_T("wkgid"))       << val.m_WkGrpID.c_str();
            param.AddParameter(_T("attribdefid")) << val.m_AttribDefID;
            param.AddParameter(_T("mop"))         << val.m_Mop;
            param.AddParameter(_T("mdata"))       << val.m_MData.c_str();

            return param;
        }

        static const SOAPParameter& Deserialize(const SOAPParameter& param, pdistrib& val)
        {
            SOAPString tmp;

            param.GetParameter(_T("wkgid"))       >> tmp; val.m_WkGrpID = tmp.Str();
            param.GetParameter(_T("attribdefid")) >>      val.m_AttribDefID;
            param.GetParameter(_T("mop"))         >>      val.m_Mop;
            param.GetParameter(_T("mdata"))       >> tmp; val.m_MData = tmp.Str();

            return param;
        }
};

template<>
class SOAPTypeTraits< SOAPArray<pdistrib> > : public SOAPArrayTypeTraits
{};

/////////////////////////////////////////////
// pdistribmap soap mapping
template<>
class SOAPTypeTraits<pdistribmap>
{
    public:
        static void GetType(SOAPQName& qname)
        {
            qname.Set(_T("pdistribmap"), _T("urn:xml-soap-emessenger"));
        }

        static SOAPParameter& Serialize(SOAPParameter& param, const pdistribmap& val)
        {
            param.AddParameter(_T("pdattribid"))  << val.m_PdAttribID;
            param.AddParameter(_T("attribdefid")) << val.m_AttribDefID;
            param.AddParameter(_T("mdata"))       << val.m_MData.c_str();
            param.AddParameter(_T("mlop"))        << val.m_Mlop;

            return param;
        }

        static const SOAPParameter& Deserialize(const SOAPParameter& param, pdistribmap& val)
        {
            SOAPString tmp;

            param.GetParameter(_T("pdattribid"))  >>      val.m_PdAttribID;
            param.GetParameter(_T("attribdefid")) >>      val.m_AttribDefID;
            param.GetParameter(_T("mdata"))       >> tmp; val.m_MData = tmp.Str();
            param.GetParameter(_T("mlop"))        >>      val.m_Mlop;

            return param;
        }
};

template<>
class SOAPTypeTraits< SOAPArray<pdistribmap> > : public SOAPArrayTypeTraits
{};

/////////////////////////////////////////////
// pinput soap mapping
template<>
class SOAPTypeTraits<pinput>
{
    public:

        static void GetType(SOAPQName& qname)
        {
            qname.Set(_T("pinput"), _T("urn:xml-soap-emessenger"));
        }

        static SOAPParameter& Serialize(SOAPParameter& param, const pinput& val)
        {    
            //param.AddParameter(_T("modelid"))      << val.m_ModelID;
            param.AddParameter(_T("pdattribid"))   << val.m_PdAttribID;
            param.AddParameter(_T("attribdefid"))  << val.m_AttribDefID;
            param.AddParameter(_T("mdefval"))      << val.m_MDefVal.c_str();
            param.AddParameter(_T("mflag"))        << val.m_MFlag;
            param.AddParameter(_T("constraintid")) << val.m_ConstraintID;

            return param;
        }

        static const SOAPParameter& Deserialize(const SOAPParameter& param, pinput& val)
        {
            SOAPString tmp;

            //param.GetParameter(_T("modelid"))      >>      val.m_ModelID;
            param.GetParameter(_T("pdattribid"))   >>      val.m_PdAttribID;
            param.GetParameter(_T("attribdefid"))  >>      val.m_AttribDefID;
            param.GetParameter(_T("mdefval"))      >> tmp; val.m_MDefVal = tmp.Str();
            param.GetParameter(_T("mflag"))        >>      val.m_MFlag;
            param.GetParameter(_T("constraintid")) >>      val.m_ConstraintID;

            return param;
        }
};

template<>
class SOAPTypeTraits< SOAPArray<pinput> > : public SOAPArrayTypeTraits
{};

class AFX_EXT_CLASS pPublishModel
{
    public:
        pPublishModel();
        ~pPublishModel();

        void reset();
    
        void setModel(pmodel model);
        void addProc(pproc proc);
        void addDeliv(pdeliv deliv);
        void addAttr(ppdattr pdattr);
        void addDistrib(pdistrib distrib);
        void addDistribmap(pdistribmap distribmap);
        void addInput(pinput inputs);

        void addAlias(const CString& alias);

        bool send();

        int getModelVersion(const std::string& model);

    private:
        CString           m_Alias;
        pmodel            m_model;
        list<pproc>       m_procs;
        list<pdeliv>      m_delivs;
        list<ppdattr>     m_pdattrs;
        list<pdistrib>    m_distribs;
        list<pdistribmap> m_distribmaps;
        list<pinput>      m_inputs;
};

END_EASYSOAP_NAMESPACE

#endif
