/****************************************************************************
 * ==> PSS_SoapPublishPrestations ------------------------------------------*
 ****************************************************************************
 * Description : Publish the prestations to Messenger through a SOAP        *
 *               protocol, and check the publication validity               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublishPrestationsH
#define PSS_SoapPublishPrestationsH

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
#include "zBaseLib\PSS_Log.h"
#include "zModel\ZBLogicalPrestationsEntity.h"
#include "zModel\ProcGraphModelDoc.h"
#include "zModel\ZBGenericSymbolErrorLine.h"
#include "zSOAP\PSS_SoapPublisher_Prestations.h"
#include "ZBPublishMessengerModelInformation.h"

// forward class declaration
class ZBLogicalPrestationsEntity;
class ZBPublishMessengerModelInformation;

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
* Publish the model prestations to Messenger through a SOAP protocol
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublishPrestations
{
    public:
        /**
        * Constructor
        *@param pInfo - info to publish
        *@param pLog - logger, can be NULL
        */
        PSS_SoapPublishPrestations(ZBPublishMessengerModelInformation* pInfo, PSS_Log* pLog = NULL);

        virtual ~PSS_SoapPublishPrestations();

        /**
        * Publishes the prestations and check their validity
        *@return true on success, otherwise false
        */
        bool Publish();

    private:
        ZBPublishMessengerModelInformation* m_pInfo;
        pPublishPrestations                 m_Prestations;
        PSS_Log*                            m_pLog;

        /**
        * Publishes the prestations and check their validity
        *@param pPrestations - prestations to publish
        *@return true on success, otherwise false
        */
        void PublishPrestations(ZBLogicalPrestationsEntity* pPrestations);
};

#endif
