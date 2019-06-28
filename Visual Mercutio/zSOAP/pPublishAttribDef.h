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

#ifndef __PPUBLISHATTRIBDEF_HDR_
#define __PPUBLISHATTRIBDEF_HDR_

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "pattribdef.h"

#ifdef _ZSOAPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 15 septembre 2005 - Ajout des décorations Unicode _T(), nettoyage du code inutile.(En commentaires)

USING_EASYSOAP_NAMESPACE

//Define serializers / soap mapping

/////////////////////////////////////////////
// pattribdef soap mapping
BEGIN_EASYSOAP_NAMESPACE

template<>
class SOAPTypeTraits<pattribdef>
{
    public:
        static void GetType(SOAPQName& qname)
        {
            qname.Set(_T("pattribdef"), _T("urn:xml-soap-emessenger"));
        }

        static SOAPParameter& Serialize(SOAPParameter& param, const pattribdef& val)
        {
            param.AddParameter(_T("attribdefid"))   << val.m_AttribDefID;
            param.AddParameter(_T("attribgrpid"))   << val.m_AttribGrpID;
            param.AddParameter(_T("attribdefname")) << val.m_AttribDefName.c_str();
            param.AddParameter(_T("attribdeftype")) << val.m_AttribDefType;
            param.AddParameter(_T("attribdefreq"))  << val.m_AttribDefFreq;

            return param;
        }
    
        static const SOAPParameter& Deserialize(const SOAPParameter& param, pattribdef& val)
        {
            SOAPString tmp;

            param.GetParameter(_T("attribdefid"))   >>      val.m_AttribDefID;
            param.GetParameter(_T("attribgrpid"))   >>      val.m_AttribGrpID;
            param.GetParameter(_T("attribdefname")) >> tmp; val.m_AttribDefName=tmp.Str();
            param.GetParameter(_T("attribdeftype")) >>      val.m_AttribDefType;
            param.GetParameter(_T("attribdefreq"))  >>      val.m_AttribDefFreq;

            return param;
        }
};

template<>
class SOAPTypeTraits< SOAPArray<pattribdef> > : public SOAPArrayTypeTraits
{};

class AFX_EXT_CLASS pPublishAttribDef
{
    public:
        pPublishAttribDef();
        ~pPublishAttribDef();

        void reset();
        void addAttribDef(pattribdef attribdef);

        // JMR-MODIF - Le 21 juin 2006 - Ajout de la fonction addAlias.
        void addAlias(const CString& alias);

        bool send();

    private:
        CString          m_Alias;
        list<pattribdef> m_attribdefs;
};

END_EASYSOAP_NAMESPACE

#endif
