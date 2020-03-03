/****************************************************************************
 * ==> PSS_SoapPublishModelDefinition --------------------------------------*
 ****************************************************************************
 * Description : Publish the model definitions to Messenger through a SOAP  *
 *               protocol, and check the publication validity               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublishModelDefinitionH
#define PSS_SoapPublishModelDefinitionH

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
#include "zProperty\ZIProperties.h"
#include "zSOAP\PSS_SoapPublisher_Model.h"
#include "PSS_PublishMessengerModelInformation.h"
#include "PSS_ProcessNavigation.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_ProcessGraphModelDoc;
class PSS_PublishMessengerModelInformation;

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
* Publish the model definitions to Messenger through a SOAP protocol
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublishModelDefinition : public PSS_ProcessNavigation
{
    public:
        /**
        * Constructor
        *@param pInfo - the info to publish
        *@param pModel - the model to navigate, can be NULL
        *@param pClass - thecustom data class, can be NULL
        */
        PSS_SoapPublishModelDefinition(PSS_PublishMessengerModelInformation* pInfo,
                                       PSS_ProcessGraphModelMdl*             pModel = NULL,
                                       void*                                 pClass = NULL);

        virtual ~PSS_SoapPublishModelDefinition();

        /**
        * Called when a publication is starting
        *@return true on success, otherwise false
        */
        virtual bool OnStart();

        /**
        * Called when a publication is finished
        *@return true on success, otherwise false
        */
        virtual bool OnFinish();

        /**
        * Called when door symbol definitions should be added to publication
        *@param pSymbol - symbol for which definitions sould be added
        *@return true on success, otherwise false
        */
        virtual bool OnDoorSymbol(PSS_DoorSymbolBP* pSymbol);

        /**
        * Called when page symbol definitions should be added to publication
        *@param pSymbol - symbol for which definitions sould be added
        *@return true on success, otherwise false
        */
        virtual bool OnPageSymbol(PSS_PageSymbolBP* pSymbol);

        /**
        * Called when procedure symbol definitions should be added to publication
        *@param pSymbol - symbol for which definitions sould be added
        *@return true on success, otherwise false
        */
        virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);

        /**
        * Called when process symbol definitions should be added to publication
        *@param pSymbol - symbol for which definitions sould be added
        *@return true on success, otherwise false
        */
        virtual bool OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol);

        /**
        * Called when start symbol definitions should be added to publication
        *@param pSymbol - symbol for which definitions sould be added
        *@return true on success, otherwise false
        */
        virtual bool OnStartSymbol(PSS_StartSymbolBP* pSymbol);

        /**
        * Called when stop symbol definitions should be added to publication
        *@param pSymbol - symbol for which definitions sould be added
        *@return true on success, otherwise false
        */
        virtual bool OnStopSymbol(PSS_StopSymbolBP* pSymbol);

        /**
        * Called when deliverable link symbol definitions should be added to publication
        *@param pSymbol - symbol for which definitions sould be added
        *@return true on success, otherwise false
        */
        virtual bool OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol);

    private:
        PSS_PublishMessengerModelInformation* m_pInfo;
        PSS_SoapPublisher_Model               m_PubMdl;
        PSS_ProcessGraphModelDoc*             m_pDoc;
        CString                               m_MessengerAddress;
        int                                   m_CounterRow;

        /**
        * Gets the parent symbol reference
        *@param pSymbol - symbol for which the parent reference should be get
        *@param parentID - parent identifier
        *@param pParentModel - parent model, can be NULL
        *@return the parent symbol reference
        */
        int GetParentSymbolReference(PSS_Symbol* pSymbol, int parentID = 0, PSS_ProcessGraphModelMdl* pParentModel = NULL);

        /**
        * Publishes the properties
        *@param propSet - properties to publish
        */
        void Publish(int ref, const ZBPropertySet& propSet);

        /**
        * Publishes the property
        *@param pProp - property to publish
        */
        void Publish(int ref, ZBProperty* pProp);
};

#endif
