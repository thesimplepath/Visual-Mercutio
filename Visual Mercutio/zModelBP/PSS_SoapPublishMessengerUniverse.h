/****************************************************************************
 * ==> PSS_SoapPublishMessengerUniverse ------------------------------------*
 ****************************************************************************
 * Description : Publish the Messenger universe to Messenger through a SOAP *
 *               protocol, and check the publication validity               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublishMessengerUniverseH
#define PSS_SoapPublishMessengerUniverseH

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
#include "zSOAP\PSS_SoapPublisher_MessengerUniverse.h"

// forward class declaration
class PSS_PublishMessengerModelInformation;
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
* Publish the Messenger universe to Messenger through a SOAP protocol, and check the publication validity
*@author Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublishMessengerUniverse
{
    public:
        /**
        * Constructor
        *@param pInfo - info to publish
        *@param pLog - logger, can be NULL
        */
        PSS_SoapPublishMessengerUniverse(PSS_PublishMessengerModelInformation* pInfo, PSS_Log* pLog = NULL);

        virtual ~PSS_SoapPublishMessengerUniverse();

        /**
        * Publishes the referential GUIDS and check their validity
        *@return true on success, otherwise false
        */
        bool Publish();

    private:
        PSS_PublishMessengerModelInformation* m_pInfo;
        PSS_SoapPublisher_MessengerUniverse   m_PubMngUni;
        PSS_Log*                              m_pLog;
};

#endif
