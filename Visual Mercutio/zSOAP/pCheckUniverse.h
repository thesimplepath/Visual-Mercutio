// **************************************************************************************************************
// *                                       Classe pCheckUniverse                                                *
// **************************************************************************************************************
// * JMR-MODIF - Le 21 juin 2006 - Création de la classe pCheckUniverse.                                        *
// **************************************************************************************************************
// * Cette classe prend en charge la publication des univers vers Messenger.                                    *
// **************************************************************************************************************

#ifndef __PCHECKUNIVERSE_HDR_
#define __PCHECKUNIVERSE_HDR_

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zConversion\PSS_String16.h"
#include "zConversion\PSS_StringTools.h"
#include "puniverse.h"

#ifdef _ZSOAPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

string convertTo(PSS_String16 str);

/////////////////////////////////////////////
//Define serializers / soap mapping

// pproc soap mapping
BEGIN_EASYSOAP_NAMESPACE

template<>
class SOAPTypeTraits<puniverse>
{
    public:
        static void GetType(SOAPQName& qname)
        {
            qname.Set( _T("puniverse"), _T("urn:xml-soap-emessenger"));
        }

        static SOAPParameter& Serialize(SOAPParameter& param, const puniverse& val)
        {
            param.AddParameter(_T("guidSystem"))     << val.m_GuidSystem.c_str();
            param.AddParameter(_T("guidPrestation")) << val.m_GuidPrestation.c_str();
            param.AddParameter(_T("guidWorkgroup"))  << val.m_GuidWorkgroup.c_str();

            return param;
        }

        static const SOAPParameter& Deserialize(const SOAPParameter& param, puniverse& val)
        {
            SOAPString tmp;

            param.GetParameter(_T("guidSystem")) >> tmp;
            val.m_GuidSystem = tmp.Str();

            param.GetParameter(_T("guidPrestation")) >> tmp;
            val.m_GuidPrestation = tmp.Str();

            param.GetParameter(_T("guidWorkgroup")) >> tmp;
            val.m_GuidWorkgroup = tmp.Str();

            return param;
        }
};

template<>
class SOAPTypeTraits< SOAPArray<puniverse> > : public SOAPArrayTypeTraits
{};

class AFX_EXT_CLASS pCheckUniverse
{
    public:

        pCheckUniverse();
        ~pCheckUniverse();

        void reset();
        void addUniverse(puniverse universe);
        void addAlias(const CString& alias);

        bool check();

    private:
        CString         m_Alias;
        list<puniverse> m_universe;
};

END_EASYSOAP_NAMESPACE

#endif
