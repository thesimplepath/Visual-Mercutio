// **************************************************************************************************************
// *                                          Classe pprestations                                                *
// **************************************************************************************************************
// * JMR-MODIF - Le 30 mars 2006 - Création de la classe pprestations.                                            *
// **************************************************************************************************************
// * Cette classe contient les attributs de publication des prestations pour Messenger. Elle effectue également *
// * la conversion des chaînes de caractères au format string.                                                    *
// **************************************************************************************************************

#ifndef __PPRESTATIONS_HDR_
#define __PPRESTATIONS_HDR_

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
class AFX_EXT_CLASS pprestations
{
public:
    std::string m_PrestationID;
    std::string m_PrestationParent;
    std::string m_PrestationTitle;

    pprestations()
    {}

    pprestations(const PSS_String16& prestationID,
                 const PSS_String16& prestationParent,
                 const PSS_String16& prestationTitle) :
        m_PrestationID    (PSS_StringTools::ConvertTo(prestationID)),
        m_PrestationParent(PSS_StringTools::ConvertTo(prestationParent)),
        m_PrestationTitle (PSS_StringTools::ConvertTo(prestationTitle))
    {}
};

#endif // __PPRESTATIONS_HDR_