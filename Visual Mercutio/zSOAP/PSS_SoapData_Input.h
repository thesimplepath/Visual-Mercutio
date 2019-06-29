/****************************************************************************
 * ==> PSS_SoapData_Input --------------------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing inputs                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_InputH
#define PSS_SoapData_InputH

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
* SOAP data containing inputs
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_Input
{
    public:
        int         m_PdAttribID;
        int         m_AttribDefID;
        std::string m_MDefVal;
        int         m_MFlag;
        int         m_ConstraintID;

        /**
        * Constructor
        */
        PSS_SoapData_Input()
        {}

        /**
        * Constructor
        *@param pdAttribID - attribute identifier
        *@param attribDefID - attribute def identifier
        *@param mDefVal - default value
        *@param mFlag - flags
        *@param constraintID - constraint identifier
        */
        PSS_SoapData_Input(int pdAttribID, int attribDefID, const PSS_String16& mDefVal, int mFlag, int constraintID) :
            m_PdAttribID(pdAttribID),
            m_AttribDefID(attribDefID),
            m_MDefVal(PSS_StringTools::ConvertTo(mDefVal)),
            m_MFlag(mFlag),
            m_ConstraintID(constraintID)
        {}
 };

#endif