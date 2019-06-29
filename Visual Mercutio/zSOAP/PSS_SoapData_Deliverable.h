/****************************************************************************
 * ==> PSS_SoapData_Deliverable --------------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing a deliverable                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_DeliverableH
#define PSS_SoapData_DeliverableH

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
* SOAP data containing a deliverable
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_Deliverable
{
    public:
        int         m_DelivID;
        int         m_ProcIDSrc;
        int         m_ProcIDTrg;
        std::string m_DelivName;
        int         m_Lateral;
        int         m_LateralDirection;
        int         m_DoubleSign;

        /**
        * Constructor
        */
        PSS_SoapData_Deliverable()
        {}

        /**
        * Constructor
        *@param delivID - delivery identifier
        *@param procIDSrc - source process identifier
        *@param procIDTrg - target process identifier
        *@param delivName - delivery name
        *@param lateral - lateral (0 = normal, 1 = lateral starts here)
        *@param lateralDirection - lateral direction (0 = top, 1 = right, 2 = bottom, 3 = left)
        *@param doubleSign - double sign (0 = no, 1 = employees, 2 = chiefs)
        */
        PSS_SoapData_Deliverable(int                 delivID,
                                 int                 procIDSrc,
                                 int                 procIDTrg,
                                 const PSS_String16& delivName,
                                 int                 lateral,
                                 int                 lateralDirection,
                                 int                 doubleSign) :
            m_DelivID(delivID),
            m_ProcIDSrc(procIDSrc),
            m_ProcIDTrg(procIDTrg),
            m_DelivName(PSS_StringTools::ConvertTo(delivName)),
            m_Lateral(lateral),
            m_LateralDirection(lateralDirection),
            m_DoubleSign(doubleSign)
        {}
};

#endif