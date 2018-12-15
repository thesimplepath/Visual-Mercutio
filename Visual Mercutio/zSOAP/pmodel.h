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

#ifndef __PMODEL_HDR_
#define __PMODEL_HDR_

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zConversion\String16.h"
string convertTo( String16 inStr );

#ifdef _ZSOAPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS pmodel
{
public:

    pmodel()
    {
    }

    pmodel ( String16 modelname, String16 modelref, String16 startdate, String16 enddate )
    {
        this->modelname    = convertTo( modelname );
        this->modelref    = convertTo( modelref );
        this->startdate    = convertTo( startdate );
        this->enddate    = convertTo( enddate );
    }

    string modelname;    // Name of the model
    string modelref;    // Model ref (GIID) used to group versions
    string startdate;    // JMR-MODIF - Le 21 juin 2006 - Variable de début de validité.
    string enddate;        // JMR-MODIF - Le 21 juin 2006 - Variable de fin de validité.
};

#endif