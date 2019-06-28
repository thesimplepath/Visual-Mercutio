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

// processsoft
#include "zConversion\PSS_String16.h"
#include "zConversion\PSS_StringTools.h"

#ifdef _ZSOAPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// todo FIXME -cCheck -oJean: changed the class member names (updated with m_), see what is the impact on Messenger
class AFX_EXT_CLASS pmodel
{
    public:
        std::string m_ModelName; // model name
        std::string m_ModelRef;  // Model ref (GIID) used for groups version
        std::string m_StartDate; // validity start date
        std::string m_EndDate;   // expiration date

        pmodel()
        {}

        pmodel(const PSS_String16& modelName,
               const PSS_String16& modelRef,
               const PSS_String16& startDate,
               const PSS_String16& endDate) :
            m_ModelName(PSS_StringTools::ConvertTo(modelName)),
            m_ModelRef (PSS_StringTools::ConvertTo(modelRef)),
            m_StartDate(PSS_StringTools::ConvertTo(startDate)),
            m_EndDate  (PSS_StringTools::ConvertTo(endDate))
        {}
};

#endif