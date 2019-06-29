/****************************************************************************
 * ==> PSS_SoapData_System -------------------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing a system                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_SystemH
#define PSS_SoapData_SystemH

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
* SOAP data containing a system
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_System
{
    public:
        std::string m_SystemID;
        std::string m_SystemParent;
        std::string m_SystemTitle;
        std::string m_Command;
        std::string m_Parameters;
        std::string m_Directory;
        int         m_Priority;
        int         m_Windowst;

        /**
        * Constructor
        */
        PSS_SoapData_System()
        {}

        /**
        * Constructor
        *@param systemID - system identifier
        *@param systemParent - parent system
        *@param systemTitle - system title
        *@param command - command
        *@param parameters - parameters
        *@param directory - directory
        *@param priority - priority
        *@param windowst - window status
        */
        PSS_SoapData_System(const PSS_String16& systemID,
                            const PSS_String16& systemParent,
                            const PSS_String16& systemTitle,
                            const PSS_String16& command,
                            const PSS_String16& parameters,
                            const PSS_String16& directory,
                            int                 priority,
                            int                 windowst) :
            m_SystemID    (PSS_StringTools::ConvertTo(systemID)),
            m_SystemParent(PSS_StringTools::ConvertTo(systemParent)),
            m_SystemTitle (PSS_StringTools::ConvertTo(systemTitle)),
            m_Command     (PSS_StringTools::ConvertTo(command)),
            m_Parameters  (PSS_StringTools::ConvertTo(parameters)),
            m_Directory   (PSS_StringTools::ConvertTo(directory)),
            m_Priority    (priority),
            m_Windowst    (windowst)
        {}
};

#endif
