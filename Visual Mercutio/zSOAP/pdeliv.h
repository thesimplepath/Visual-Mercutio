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

#ifndef __PDELIV_HDR_
#define __PDELIV_HDR_

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
class AFX_EXT_CLASS pdeliv
{
    public:
        int         m_DelivID;
        int         m_ProcIDSrc;
        int         m_ProcIDTrg;
        std::string m_DelivName;
        int         m_Lateral;          // 0 = normal, 1 = lateral starts here
        int         m_LateralDirection; // 0 = top, 1 = right, 2 = bottom, 3 = left
        int         m_DoubleSign;       // 0 = no,  1 = employees, 2 = chiefs

        pdeliv()
        {}

        pdeliv(int                 delivID,
               int                 procIDSrc,
               int                 procIDTrg,
               const PSS_String16& delivName,
               int                 lateral,
               int                 lateralDirection,
               int                 doubleSign) :
            m_DelivID(delivID),
            m_ProcIDSrc(procIDSrc),
            m_ProcIDTrg(procIDTrg),
            m_DelivName(PSS_StringTools::ConvertTo(delivName)),
            m_Lateral(lateral),
            m_LateralDirection(lateralDirection),
            m_DoubleSign(doubleSign)
        {}
};

#endif