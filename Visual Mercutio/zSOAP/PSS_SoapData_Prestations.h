/****************************************************************************
 * ==> PSS_SoapData_Prestations --------------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing prestations                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_PrestationsH
#define PSS_SoapData_PrestationsH

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
* SOAP data containing prestations
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_Prestations
{
    public:
        std::string m_PrestationID;
        std::string m_PrestationParent;
        std::string m_PrestationTitle;

        /**
        * Constructor
        */
        PSS_SoapData_Prestations()
        {}

        /**
        * Constructor
        *@param prestationID - prestation identifier
        *@param prestationParent - prestation parent
        *@param prestationTitle - prestation title
        */
        PSS_SoapData_Prestations(const PSS_String16& prestationID,
                                 const PSS_String16& prestationParent,
                                 const PSS_String16& prestationTitle) :
            m_PrestationID    (PSS_StringTools::ConvertTo(prestationID)),
            m_PrestationParent(PSS_StringTools::ConvertTo(prestationParent)),
            m_PrestationTitle (PSS_StringTools::ConvertTo(prestationTitle))
        {}
};

#endif
