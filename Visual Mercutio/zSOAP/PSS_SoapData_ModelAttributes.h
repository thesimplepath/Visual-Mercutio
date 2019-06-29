/****************************************************************************
 * ==> PSS_SoapData_ModelAttributes ----------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing the model attributes                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_ModelAttributesH
#define PSS_SoapData_ModelAttributesH

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
* SOAP data containing the model attributes
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_ModelAttributes
{
    public:
        int         m_AttribDefID;
        int         m_AttribGrpID;
        std::string m_AttribDefName;
        int         m_AttribDefType;
        int         m_AttribDefFreq;

        /**
        * Constructor
        */
        PSS_SoapData_ModelAttributes() :
            m_AttribDefID(0),
            m_AttribGrpID(0),
            m_AttribDefType(0),
            m_AttribDefFreq(0)
        {}

        /**
        * Constructor
        *@param attribDefID - attribute definition identifier
        *@param attribGrpID - group identifier at which this attribute belongs
        *@param attribDefName - attribute definition name
        *@param attribDefType - attribute definition type
        *@param attribDefFreq - attribute definition frequence
        */
        PSS_SoapData_ModelAttributes(int                 attribDefID,
                                     int                 attribGrpID,
                                     const PSS_String16& attribDefName,
                                     int                 attribDefType,
                                     int                 attribDefFreq) :
            m_AttribDefID(attribDefID),
            m_AttribGrpID(attribGrpID),
            m_AttribDefName(PSS_StringTools::ConvertTo(attribDefName)),
            m_AttribDefType(attribDefType),
            m_AttribDefFreq(attribDefFreq)
        {}
};

#endif
