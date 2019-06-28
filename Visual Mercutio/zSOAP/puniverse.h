// **************************************************************************************************************
// *                                           Classe puniverse                                                    *
// **************************************************************************************************************
// * JMR-MODIF - Le 21 juin 2006 - Création de la classe puniverse.                                                *
// **************************************************************************************************************
// * Cette classe contient les attributs de publication des univers pour le test de validité des référentiels.    *
// **************************************************************************************************************

#ifndef __PUNIVERSE_HDR_
#define __PUNIVERSE_HDR_

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

#ifdef _ZSOAPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// todo FIXME -cCheck -oJean: changed the class member names (updated with m_), see what is the impact on Messenger
class AFX_EXT_CLASS puniverse
{
    public:
        std::string m_GuidSystem;
        std::string m_GuidPrestation;
        std::string m_GuidWorkgroup;

        puniverse()
        {};

        puniverse(const PSS_String16& guidSystem,
                  const PSS_String16& guidPrestation,
                  const PSS_String16& guidWorkgroup) :
            m_GuidSystem    (PSS_StringTools::ConvertTo(guidSystem)),
            m_GuidPrestation(PSS_StringTools::ConvertTo(guidPrestation)),
            m_GuidWorkgroup (PSS_StringTools::ConvertTo(guidWorkgroup))
        {}
};

#endif
