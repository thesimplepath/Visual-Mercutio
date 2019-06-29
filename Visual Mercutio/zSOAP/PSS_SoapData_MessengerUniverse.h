/****************************************************************************
 * ==> PSS_SoapData_MessengerUniverse --------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing the Messenger universe                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_MessengerUniverseH
#define PSS_SoapData_MessengerUniverseH

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
* SOAP data containing the Messenger universe
*@author Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_MessengerUniverse
{
    public:
        std::string m_GuidSystem;
        std::string m_GuidPrestation;
        std::string m_GuidWorkgroup;

        /**
        * Constructor
        */
        PSS_SoapData_MessengerUniverse()
        {};

        /**
        * Constructor
        *@param guidSystem - system GUID
        *@param guidPrestation - prestation GUID
        *@param guidWorkgroup - workgroup GUID
        */
        PSS_SoapData_MessengerUniverse(const PSS_String16& guidSystem,
                                       const PSS_String16& guidPrestation,
                                       const PSS_String16& guidWorkgroup) :
            m_GuidSystem    (PSS_StringTools::ConvertTo(guidSystem)),
            m_GuidPrestation(PSS_StringTools::ConvertTo(guidPrestation)),
            m_GuidWorkgroup (PSS_StringTools::ConvertTo(guidWorkgroup))
        {}
};

#endif
