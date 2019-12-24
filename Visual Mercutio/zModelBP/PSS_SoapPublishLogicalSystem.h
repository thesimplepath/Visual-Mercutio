/****************************************************************************
 * ==> PSS_SoapPublishLogicalSystem ----------------------------------------*
 ****************************************************************************
 * Description : Publish the logical system to Messenger through a SOAP     *
 *               protocol, and check the publication validity               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublishLogicalSystemH
#define PSS_SoapPublishLogicalSystemH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zSOAP\PSS_SoapPublisher_System.h"

// old class name mapping
#ifndef PSS_LogicalSystemEntity
    #define PSS_LogicalSystemEntity ZBLogicalSystemEntity
#endif

// forward class declaration
class PSS_LogicalSystemEntity;
class ZBPublishMessengerModelInformation;
class PSS_Log;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Publish the logical system to Messenger through a SOAP protocol, and check the publication validity
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublishLogicalSystem
{
    public:
        /**
        * Constructor
        *@param pInfo - info to publish
        *@param pLog - logger, can be NULL
        */
        PSS_SoapPublishLogicalSystem(ZBPublishMessengerModelInformation* pInfo, PSS_Log* pLog = NULL);

        virtual ~PSS_SoapPublishLogicalSystem();

        /**
        * Publishes a logical system and check its validity
        *@return true on success, otherwise false
        */
        bool Publish();

    private:
        ZBPublishMessengerModelInformation* m_pInfo;
        PSS_SoapPublisher_System            m_PubSys;
        PSS_Log*                            m_pLog;

        /**
        * Publishes a logical system
        *@param pSystem - logical system to publish
        */
        void PublishLogicalSystem(PSS_LogicalSystemEntity* pSystem);
};

#endif
