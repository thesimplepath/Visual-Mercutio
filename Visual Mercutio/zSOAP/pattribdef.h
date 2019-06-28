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

#ifndef __PATTRIBDEF_HDR_
#define __PATTRIBDEF_HDR_

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

/**
* Converts a string to xml (ANSI7) string
*@param str - string to convert
*@return converted string
*/
std::string ConvertTo(const PSS_String16& str);

// todo FIXME -cCheck -oJean: changed the class member names (updated with m_), see what is the impact on Messenger
class AFX_EXT_CLASS pattribdef
{
    public:
        int         m_AttribDefID;
        int         m_AttribGrpID;
        std::string m_AttribDefName;
        int         m_AttribDefType;
        int         m_AttribDefFreq;

        pattribdef() :
            m_AttribDefID(0),
            m_AttribGrpID(0),
            m_AttribDefType(0),
            m_AttribDefFreq(0)
        {}

        pattribdef(int attribDefID, int attribGrpID, PSS_String16 attribDefName, int attribDefType, int attribDefFreq) :
            m_AttribDefID(attribDefID),
            m_AttribGrpID(attribGrpID),
            m_AttribDefName(PSS_StringTools::ConvertTo(attribDefName)),
            m_AttribDefType(attribDefType),
            m_AttribDefFreq(attribDefFreq)
        {}
};

#endif
