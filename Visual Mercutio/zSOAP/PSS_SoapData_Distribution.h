/****************************************************************************
 * ==> PSS_SoapData_Distribution -------------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing a distribution                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_DistributionH
#define PSS_SoapData_DistributionH

// change the definition of AFX_EXT... to make it import
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
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* SOAP data containing a distribution
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_Distribution
{
    public:
        std::string m_WkGrpID;
        int         m_AttribDefID;
        int         m_Mop;
        std::string m_MData;

        /**
        * Constructor
        */
        PSS_SoapData_Distribution()
        {}

        /**
        * Constructor
        *@param wkGrpID - workflow group identifier
        *@param attribDefID - attribute identifier
        *@param mop - operation
        *@param mData - data
        */
        PSS_SoapData_Distribution(const PSS_String16& wkGrpID, int attribDefID, int mop, const PSS_String16& mData) :
            m_WkGrpID(PSS_StringTools::ConvertTo(wkGrpID)),
            m_AttribDefID(attribDefID),
            m_Mop(mop),
            m_MData(PSS_StringTools::ConvertTo(mData))
        {}
 };

#endif