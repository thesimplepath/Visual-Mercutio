/****************************************************************************
 * ==> PSS_ExtractModelAttributes ------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which navigates through the model and *
 *               extract unique symbol                                      *
 *               attributes                                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExtractModelAttributesH
#define PSS_ExtractModelAttributesH

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
#include "zModel\PSS_ModelNavigation.h"
#include "zProperty\PSS_Property.h"
#include "PSS_ProcessGraphModelMdl.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Navigates through the model and extract unique symbol attributes
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ExtractModelAttributes : public PSS_ModelNavigation
{
    public:
        /**
        * Constructor
        *@param pModel - the model to navigate, can be NULL
        *@param pClass - the custom data class, can be NULL
        */
        PSS_ExtractModelAttributes(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);

        virtual ~PSS_ExtractModelAttributes();

        /**
        * Called when the navigation starts
        *@return true if the navigation is allowed to continue, otherwise false
        */
        virtual bool OnStart();

        /**
        * Called when the navigation ends
        *@return true on success, otherwise false
        */
        virtual bool OnFinish();

        /**
        * Called when a symbol is visited
        *@param pSymbol - the symbol to visit
        *@return true if the symbol is allowed to be visited, otherwise false
        */
        virtual bool OnSymbol(PSS_Symbol* pSymbol);

        /**
        * Called when a link symbol is visited
        *@param pLink - the link symbol to visit
        *@return true if the symbol is allowed to be visited, otherwise false
        */
        virtual bool OnLink(PSS_LinkSymbol* pLink);

    private:
        PSS_Properties::IPropertySet* m_pPropertySet;
        int                           m_IDArray[500];

        /**
        * Processes the attributes
        *@param[out] propSet - the property set to populate with the result
        */
        void ProcessAttrib(PSS_Properties::IPropertySet& propSet);

        /**
        * Checks if a key exists
        *@param key - the key to check
        *@return true if the key exists, otherwise false
        */
        bool KeyExist(int key);
};

#endif
