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

#include "zConversion\String16.h"

#ifdef _ZSOAPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

string convertTo( String16 inStr );

class AFX_EXT_CLASS pprestations
{
public:

    pprestations()
    {
    }

    pprestations( String16    prestationid,
                  String16    prestationparent,
                  String16    prestationtitle )
    {
        this->prestationid        = convertTo( prestationid );
        this->prestationparent    = convertTo( prestationparent );
        this->prestationtitle    = convertTo( prestationtitle );
    }

    string    prestationid;
    string    prestationparent;
    string    prestationtitle;
};

#endif // __PPRESTATIONS_HDR_