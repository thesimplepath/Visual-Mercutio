// **************************************************************************************************************
// *                                     Classe pPublishPrestations                                                *
// **************************************************************************************************************
// * JMR-MODIF - Le 30 mars 2006 - Création de la classe pPublishPrestations.                                    *
// **************************************************************************************************************
// * Cette classe prend en charge la publication des prestations vers Messenger.                                *
// **************************************************************************************************************

#ifndef __PPUBLISHPRESTATIONS_HDR_
#define __PPUBLISHPRESTATIONS_HDR_

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zConversion\PSS_String16.h"
#include "pprestations.h"

#ifdef _ZSOAPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////
//Define serializers / soap mapping

// pproc soap mapping
BEGIN_EASYSOAP_NAMESPACE

template<>
class SOAPTypeTraits<pprestations>
{
    public:

        static void GetType(SOAPQName& qname)
        {
            qname.Set(_T("pprestations"), _T("urn:xml-soap-emessenger"));
        }

        static SOAPParameter& Serialize(SOAPParameter& param, const pprestations& val)
        {
            param.AddParameter(_T("prestationid"))     << val.m_PrestationID.c_str();
            param.AddParameter(_T("prestationparent")) << val.m_PrestationParent.c_str();
            param.AddParameter(_T("prestationtitle"))  << val.m_PrestationTitle.c_str();

            return param;
        }

        static const SOAPParameter& Deserialize(const SOAPParameter& param, pprestations& val)
        {
            SOAPString tmp;

            param.GetParameter(_T("prestationid"))     >> tmp; val.m_PrestationID     = tmp.Str();
            param.GetParameter(_T("prestationparent")) >> tmp; val.m_PrestationParent = tmp.Str();
            param.GetParameter(_T("prestationtitle"))  >> tmp; val.m_PrestationTitle  = tmp.Str();

            return param;
        }
};

template<>
class SOAPTypeTraits< SOAPArray<pprestations> > : public SOAPArrayTypeTraits
{};

class AFX_EXT_CLASS pPublishPrestations
{
    public:
        pPublishPrestations();
        ~pPublishPrestations();

        void reset();
        void addPrestation(pprestations wkg);

        void addAlias(const CString& alias);

        bool send();

    private:
        CString            m_Alias;
        list<pprestations> m_prestations;
};

END_EASYSOAP_NAMESPACE

#endif
