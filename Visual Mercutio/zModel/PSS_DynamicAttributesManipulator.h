/****************************************************************************
 * ==> PSS_DynamicAttributesManipulator ------------------------------------*
 ****************************************************************************
 * Description : Provides a dynamic attributes manipulator                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DynamicAttributesManipulatorH
#define PSS_DynamicAttributesManipulatorH

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

// class name mapping
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif
#ifndef PSS_Symbol
    #define PSS_Symbol ZBSymbol
#endif
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif

// forward class declaration
class PSS_ProcessGraphModelMdl;
class ZBProperty;
class ZBDynamicPropertiesManager;
class PSS_BasicSymbol;
class PSS_Symbol;
class PSS_LinkSymbol;

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
* Dynamic attributes manipulator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DynamicAttributesManipulator
{
    public:
        PSS_DynamicAttributesManipulator();
        virtual ~PSS_DynamicAttributesManipulator();

        /**
        * Gets the categories
        *@param pModel - the model owning the categories
        *@param[out] staticAttributes - the static attributes
        *@param[out] dynamicAttributes - the dynamic attributes
        */
        static void GetCategories(PSS_ProcessGraphModelMdl* pModel,
                                  CStringArray&             staticAttributes,
                                  CStringArray&             dynamicAttributes);

        /**
        * Assigns a property
        *@param pModel - the model to which the property should be added
        *@param pProperty - the property to add
        *@param pRTClass - the property runtime class
        */
        static bool AssignProperty(PSS_ProcessGraphModelMdl* pModel, ZBProperty* pProperty, CRuntimeClass* pRTClass = NULL);

        /**
        * Assigns a dynamic property on a symbol
        *@param pDynamicPropertiesManager - the dynamic properties manager
        *@param pSymbol - the symbol to add to
        */
        static bool AssignDynamicPropertyOnSymbol(ZBDynamicPropertiesManager* pDynamicPropertiesManager, PSS_Symbol* pSymbol);

        /**
        * Assigns a dynamic property on a link symbol
        *@param pDynamicPropertiesManager - the dynamic properties manager
        *@param pSymbol - the link symbol to add to
        */
        static bool AssignDynamicPropertyOnSymbol(ZBDynamicPropertiesManager* pDynamicPropertiesManager, PSS_LinkSymbol* pSymbol);

        /**
        * Reassigns a property
        *@param pModel - the model owning the property to reassign
        *@param pProperty - the property to reassign
        */
        static bool ReassignProperty(PSS_ProcessGraphModelMdl* pModel, ZBProperty* pProperty);

        /**
        * Deletes a property
        *@param pModel - the model owning the property to delete
        *@param pProperty - the property to delete
        */
        static bool DeleteProperty(PSS_ProcessGraphModelMdl* pModel, ZBProperty* pProperty);

        /**
        * Extracts an unique attribute
        *@param pModel - the model owning the property to extract
        *@param[out] set - the property set to populate with the results
        */
        static void ExtractUniqueAttributes(PSS_ProcessGraphModelMdl* pModel, ZBPropertySet& set);

    private:
        /**
        * Assigns a dynamic property on a symbol
        *@param pDynamicPropertiesManager - the dynamic properties manager
        *@param pSymbol - the symbol to add to
        *@param className - the class name
        */
        static bool AssignDynamicPropertyOnSymbol(ZBDynamicPropertiesManager* pDynamicPropertiesManager,
                                                  PSS_BasicSymbol*            pSymbol,
                                                  const CString&              className);
};

#endif
