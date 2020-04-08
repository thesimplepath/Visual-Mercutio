/****************************************************************************
 * ==> PSS_SoapData_Process ------------------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing the process                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_ProcessH
#define PSS_SoapData_ProcessH

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
* SOAP data containing the process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_Process
{
    public:
        int         m_ProcID;
        std::string m_WkGrpID;
        int         m_ProcType;
        int         m_DoubleSign;
        int         m_ProcIDProcessus;

        /**
        * Constructor
        */
        PSS_SoapData_Process() :
            m_ProcID(-1),
            m_ProcType(-1),
            m_DoubleSign(-1),
            m_ProcIDProcessus(-1)
        {}

        /**
        * Constructor
        *@param procID - process identifier
        *@param wkGrpID - workflow group identifier
        *@param procType - process type (0 = start, 1 = stop, 2 = normal)
        *@param doubleSign - double sign(0 = no, 1 = yes, by any employee of this group, 2 = yes, by chief of this group)
        *@param procIDProcessus - processus identifier (0 = processus, x = all others parent processus)
        */
        PSS_SoapData_Process(int procID, const PSS_String16& wkGrpID, int procType, int doubleSign, int procIDProcessus) :
            m_ProcID(procID),
            m_WkGrpID(PSS_StringTools::ConvertTo(wkGrpID)),
            m_ProcType(procType),
            m_DoubleSign(doubleSign),
            m_ProcIDProcessus(procIDProcessus)
        {}
};

#endif
