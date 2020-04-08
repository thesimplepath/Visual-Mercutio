/****************************************************************************
 * ==> PSS_SoapData_DistributionMap ----------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing a distribution map                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_DistributionMapH
#define PSS_SoapData_DistributionMapH

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
* SOAP data containing a distribution map
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_DistributionMap
{
    public:
        int         m_PdAttribID;
        int         m_AttribDefID;
        std::string m_MData;
        int         m_Mlop;

        /**
        * Constructor
        */
        PSS_SoapData_DistributionMap() :
            m_PdAttribID(-1),
            m_AttribDefID(-1),
            m_Mlop(-1)
        {}

        /**
        * Constructor
        *@param pdAttribID - attribute identifier
        *@param attribDefID - attribute def identifier
        *@param mData - data
        *@param mlop - operation
        */
        PSS_SoapData_DistributionMap(int pdAttribID, int attribDefID, const PSS_String16& mData, int mlop) :
            m_PdAttribID(pdAttribID),
            m_AttribDefID(attribDefID),
            m_MData(PSS_StringTools::ConvertTo(mData)),
            m_Mlop(mlop)
        {}
};

#endif