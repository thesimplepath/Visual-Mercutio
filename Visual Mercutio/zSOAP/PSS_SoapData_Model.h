/****************************************************************************
 * ==> PSS_SoapData_Model --------------------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing models                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_ModelH
#define PSS_SoapData_ModelH

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
* SOAP data containing models
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_Model
{
    public:
        std::string m_ModelName;
        std::string m_ModelRef;
        std::string m_StartDate;
        std::string m_EndDate;

        /**
        * Constructor
        */
        PSS_SoapData_Model()
        {}

        /**
        * Constructor
        *@param modelName - model name
        *@param modelRef - model reference (GIID) used for groups version
        *@param startDate - validity start date
        *@param endDate - expiration date
        */
        PSS_SoapData_Model(const PSS_String16& modelName,
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
