/****************************************************************************
 * ==> PSS_ProcessGraphModelViewport ---------------------------------------*
 ****************************************************************************
 * Description : Provides a graphic process model viewport                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessGraphModelViewportH
#define PSS_ProcessGraphModelViewportH

#if _MSC_VER >= 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// stingray studio
#include "Views/OdRulerWrapper.h"

// processsoft
#include "zBaseLib\PSS_DocumentPageSetup.h"
#include "ZBPageUnits.h"

// class name mapping
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_ProcessGraphModelController;
class PSS_ProcessGraphModelMdl;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// scope symbols in stingray foundation library
using namespace sfl;

/**
* Graphic process model viewport
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessGraphModelViewport : public CODBufferedRulerViewport
{
    public:
        PSS_ProcessGraphModelViewport();
        virtual ~PSS_ProcessGraphModelViewport();

        /**
        * Resizes the viewport
        *@param pPageSetup - the document page setup
        */
        virtual void SizeVp(PSS_DocumentPageSetup* pPageSetup);

        /**
        * Updates the page look according to the model settings
        *@param pPageSetup - the document page setup
        */
        virtual void UpdatePageLook(PSS_DocumentPageSetup* pPageSetup);

        /**
        * Gets the model
        *@return the model
        */
        virtual PSS_ProcessGraphModelMdl* GetModel();

        /**
        * Gets the model controller
        *@return the model controller
        */
        virtual PSS_ProcessGraphModelController* GetModelController();
 
        /**
        * Sets the ruler
        *@param ruler - the ruler
        */
        virtual void SetRuler(const CODRuler& ruler);

        /**
        * Sets the page units
        *@param pageUnits - the page units
        */
        virtual void SetPageUnits(const ZBPageUnits& pageUnits);

        /**
        * Assigns a new controller
        *@param pCtlr - the new controller to assign
        *@param pModel - the model
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AssignNewController(PSS_ProcessGraphModelController* pCtlr, PSS_ProcessGraphModelMdl* pModel);

        /**
        * Exports the model to an image file
        *@param fileName - the image file name to export to
        *@param dc - the device context
        *@return true on success, otherwise false
        */
        virtual bool ExportModelToImageFile(const CString& fileName, CDC& dc);

        /**
        * Creates an image object from a file extension
        *@param fileName - the file name
        *@return the image object, NULL on error
        */
        static SECImage* CreateImageObjectFromFileExtension(const CString& fileName);

        /**
        * Loads an image from a file
        *@param fileName - the file name
        *@return the loaded image, NULL on error
        */
        static SECImage* LoadImageFromFile(const CString& fileName);

        /**
        * Called when the viewport is initially updated
        */
        virtual void OnInitialUpdate();

        /**
        * Called when the viewport is updated
        *@param pSubject - the subject
        *@param pMsg - the message
        */
        virtual void OnUpdate(IMvcSubject* pSubject, IMvcMessage* pMsg);

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ProcessGraphModelViewport)
        virtual BOOL CreateController();
        //}}AFX_VIRTUAL

    protected:
        /**
        * Centers the viewport origin
        */
        virtual void CenterOrigin();
};

#endif
