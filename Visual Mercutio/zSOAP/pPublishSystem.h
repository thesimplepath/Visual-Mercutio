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

#ifndef __PPUBLISHSYSTEM_HDR_
#define __PPUBLISHSYSTEM_HDR_

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zConversion\PSS_String16.h"
#include "psystem.h"

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
class SOAPTypeTraits<psystem>
{
    public:
        static void GetType(SOAPQName& qname)
        {
            qname.Set(_T("psystem"), _T("urn:xml-soap-emessenger"));
        }

        static SOAPParameter& Serialize(SOAPParameter& param, const psystem& val)
        {
            param.AddParameter(_T("systemid"))     << val.m_SystemID.c_str();
            param.AddParameter(_T("systemparent")) << val.m_SystemParent.c_str();
            param.AddParameter(_T("systemtitle"))  << val.m_SystemTitle.c_str();
            param.AddParameter(_T("command"))      << val.m_Command.c_str();
            param.AddParameter(_T("parameters"))   << val.m_Parameters.c_str();
            param.AddParameter(_T("directory"))    << val.m_Directory.c_str();
            param.AddParameter(_T("priority"))     << val.m_Priority;
            param.AddParameter(_T("windowst"))     << val.m_Windowst;

            return param;
        }

        static const SOAPParameter& Deserialize(const SOAPParameter& param, psystem& val)
        {
            SOAPString tmp;

            param.GetParameter(_T("systemid"))     >> tmp; val.m_SystemID     = tmp.Str();
            param.GetParameter(_T("systemparent")) >> tmp; val.m_SystemParent = tmp.Str();
            param.GetParameter(_T("systemtitle"))  >> tmp; val.m_SystemTitle  = tmp.Str();
            param.GetParameter(_T("command"))      >> tmp; val.m_Command      = tmp.Str();
            param.GetParameter(_T("parameters"))   >> tmp; val.m_Parameters   = tmp.Str();
            param.GetParameter(_T("directory"))    >> tmp; val.m_Directory    = tmp.Str();
            param.GetParameter(_T("priority"))     >>      val.m_Priority;
            param.GetParameter(_T("windowst"))     >>      val.m_Windowst;

            return param;
        }
};

template<>
class SOAPTypeTraits< SOAPArray<psystem> > : public SOAPArrayTypeTraits
{};

class AFX_EXT_CLASS pPublishSystem
{
    public:
        pPublishSystem();
        ~pPublishSystem();

        void reset();
        void addSystem( psystem syst );

        void addAlias(const CString& alias);

        bool send();

    private:
        CString       m_Alias;
        list<psystem> m_systems;
};

END_EASYSOAP_NAMESPACE

#endif
