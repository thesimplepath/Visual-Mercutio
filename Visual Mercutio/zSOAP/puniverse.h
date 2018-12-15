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

class AFX_EXT_CLASS puniverse
{
public:

    puniverse()
    {
    };

    puniverse( String16    guidSystem,
               String16    guidPrestation,
               String16    guidWorkgroup )
    {
        this->guidSystem        = convertTo( guidSystem );
        this->guidPrestation    = convertTo( guidPrestation );
        this->guidWorkgroup        = convertTo( guidWorkgroup );
    }

    string    guidSystem;
    string    guidPrestation;
    string    guidWorkgroup;
};

#endif // __PUNIVERSE_HDR_