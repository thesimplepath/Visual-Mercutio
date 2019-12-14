/****************************************************************************
 * ==> PSS_SoapPublishModelGenerateFiles -----------------------------------*
 ****************************************************************************
 * Description : Publish the model generated files to Messenger through a   *
 *               SOAP protocol, and check the publication validity          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapPublishModelGenerateFilesH
#define PSS_SoapPublishModelGenerateFilesH

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
#include "zBaseLib\PSS_KeepStringUsage.h"
#include "zModel\ZUModelNavigation.h"
#include "zModelWeb\PSS_PublishModelGenerateDialog.h"
#include "zSOAP\PSS_SoapPublisher_File.h"

// forward class declaration
class ZBPublishMessengerModelInformation;
class ZBInfoModelGraphicGeneration;

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
* Publish the model generated files to Messenger through a SOAP protocol
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapPublishModelGenerateFiles : public ZUModelNavigation, public PSS_KeepStringUsage
{
    public:
        /**
        * Constructor
        *@param pInfo - info to publish
        *@param pModel - owning model, can be NULL
        *@param pClass - owning class, can be NULL
        */
        PSS_SoapPublishModelGenerateFiles(PSS_ProcessGraphModelMdl*           pModel = NULL,
                                          void*                               pClass = NULL,
                                          ZBPublishMessengerModelInformation* pInfo  = NULL);

        virtual ~PSS_SoapPublishModelGenerateFiles();

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
        * Called when symbol files should be added to publication
        *@param pSymbol - symbol for which files sould be added
        *@return true on success, otherwise false
        */
        virtual bool OnSymbol(PSS_Symbol* pSymbol);

        /**
        * Called when link files should be added to publication
        *@param pLink - link for which files sould be added
        *@return true on success, otherwise false
        */
        virtual bool OnLink(PSS_LinkSymbol* pLink);

    private:
        PSS_PublishModelGenerateDialog      m_FileGenerateWindow;
        ZBPublishMessengerModelInformation* m_pModelInfo;
        ZBInfoModelGraphicGeneration*       m_pInfo;
        PSS_SoapPublisher_File              m_PubFile;
        CString                             m_RootHtmlFileName;
        CString                             m_RootName;
        CString                             m_TargetDirectory;

        /**
        * Publishes the model images
        *@param pModel - model from which images should be published
        *@return true on success, otherwise false
        */
        bool PublishModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Creates a html page from a model
        *@param pModel - model from which html page should be created
        *@param imageFileName - image file name
        *@return true on success, otherwise false
        */
        bool CreateHtmlPage(PSS_ProcessGraphModelMdl* pModel, const CString& imageFileName);

        /**
        * Builds a file name for the model image
        *@param pModel - model for which file name should be created
        *@return file name, empty string on error
        */
        CString BuildModelImageFileName(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Builds a file name for the model html page
        *@param pModel - model for which html page file name should be created
        *@return file name, empty string on error
        */
        CString BuildModelHTMLFileName(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Parses a model file name
        *@param modelName - model name to parse
        *@return parsed file name, empty string on error
        */
        CString ParseModelName(const CString& modelName);
};

#endif
