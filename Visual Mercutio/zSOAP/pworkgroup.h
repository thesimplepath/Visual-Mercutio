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
class AFX_EXT_CLASS pworkgroup
{
    public:
        std::string m_WkGrpID;
        std::string m_WkGrpParent;
        std::string m_WkGrpName;
        std::string m_Mission;
        std::string m_DayCost;

        pworkgroup()
        {}

        pworkgroup(const PSS_String16& wkGrpID,
                   const PSS_String16& wkGrpParent,
                   const PSS_String16& wkGrpName,
                   const PSS_String16& mission,
                   const PSS_String16& dayCost) :
            m_WkGrpID    (PSS_StringTools::ConvertTo(wkGrpID)),
            m_WkGrpParent(PSS_StringTools::ConvertTo(wkGrpParent)),
            m_WkGrpName  (PSS_StringTools::ConvertTo(wkGrpName)),
            m_Mission    (PSS_StringTools::ConvertTo(mission)),
            m_DayCost    (PSS_StringTools::ConvertTo(dayCost))
        {}
};

#endif
