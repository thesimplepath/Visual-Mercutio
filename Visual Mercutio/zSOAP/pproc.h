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

#ifndef __PPROC_HDR_
#define __PPROC_HDR_

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
class AFX_EXT_CLASS pproc
{
    public:
        int         m_ProcID;
        std::string m_WkGrpID;
        int         m_ProcType;        // 0 = start, 1 = stop, 2 = normal
        int         m_DoubleSign;      // 0 = no, 1 = yes, by any employee of this group, 2 = yes, by chief of this group
        int         m_ProcIDProcessus; // 0 = processus, x = all others parent processus

        pproc()
        {}

        pproc(int procID, const PSS_String16& wkGrpID, int procType, int doubleSign, int procIDProcessus) :
            m_ProcID(procID),
            m_WkGrpID(PSS_StringTools::ConvertTo(wkGrpID)),
            m_ProcType(procType),
            m_DoubleSign(doubleSign),
            m_ProcIDProcessus(procIDProcessus)
        {}
};

#endif
