/****************************************************************************
 * ==> PSS_SoapData_Workgroup ----------------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing a workgroup                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_Workgroup
#define PSS_SoapData_WorkgroupH

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
* SOAP data containing a workgroup
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_Workgroup
{
    public:
        std::string m_WkGrpID;
        std::string m_WkGrpParent;
        std::string m_WkGrpName;
        std::string m_Mission;
        std::string m_DayCost;

        /**
        * Constructor
        */
        PSS_SoapData_Workgroup()
        {}

        /**
        * Constructor
        *@param wkGrpID - workgroup identifier
        *@param wkGrpParent - parent group
        *@param wkGrpName - group name
        *@param mission - mission
        *@param dayCost - day cost
        */
        PSS_SoapData_Workgroup(const PSS_String16& wkGrpID,
                               const PSS_String16& wkGrpParent,
                               const PSS_String16& wkGrpName,
                               const PSS_String16& mission,
                               const PSS_String16& dayCost) :
            m_WkGrpID    (PSS_StringTools::ConvertTo(wkGrpID)),
            m_WkGrpParent(PSS_StringTools::ConvertTo(wkGrpParent)),
            m_WkGrpName  (PSS_StringTools::ConvertTo(wkGrpName)),
            m_Mission    (PSS_StringTools::ConvertTo(mission)),
            m_DayCost    (PSS_StringTools::ConvertTo(dayCost))
        {}
};

#endif
