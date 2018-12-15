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

#ifndef __PWORKGROUP_HDR_
#define __PWORKGROUP_HDR_

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zConversion\String16.h"
string convertTo( String16 inStr );

#ifdef _ZSOAPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS pworkgroup
{
public:

    pworkgroup()
    {
    }

    // JMR-MODIF - Le 24 mai 2006 - Ajout du paramètre mission.
    // JMR-MODIF - Le 6 décembre 2006 - Ajout du paramètre daycost.
    pworkgroup( String16 wkgid, String16 wkgparent, String16 wkgname, String16 mission, String16 daycost )
    {
        this->wkgid        = convertTo( wkgid );
        this->wkgparent    = convertTo( wkgparent );
        this->wkgname    = convertTo( wkgname );
        this->mission    = convertTo( mission );
        this->daycost    = convertTo( daycost );
    }

    string    wkgid;
    string    wkgparent;
    string    wkgname;
    string    mission;    // JMR-MODIF - Le 24 mai 2006 - Ajout de la variable mission.
    string    daycost;    // JMR-MODIF - Le 6 décembre 2006 - Ajout de la variable daycost.
};

#endif