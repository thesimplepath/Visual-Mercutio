/****************************************************************************
 * ==> PSS_ExtractCategoryAttributes ---------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which navigates through the model and *
 *               extracts unique attribute categories                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExtractCategoryAttributesH
#define PSS_ExtractCategoryAttributesH

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
#include "zProperty\ZIProperties.h"
#include "zProperty\ZBProperty.h"
#include "zModel\ZUModelNavigation.h"

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
* Navigates through the model and extracts unique attribute categories
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ExtractCategoryAttributes : public ZUModelNavigation,
                                                    public PSS_KeepStringUsage
{
    public:
        /**
        * Constructor
        *@param pModel - the model
        *@param pStaticArray - the static array
        *@param pDynamicArray - the dynamic array
        *@param pClass - the class
        */
        PSS_ExtractCategoryAttributes(PSS_ProcessGraphModelMdl* pModel        = NULL,
                                      CStringArray*             pStaticArray  = NULL,
                                      CStringArray*             pDynamicArray = NULL,
                                      void*                     pClass        = NULL);

        virtual ~PSS_ExtractCategoryAttributes();

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
        CStringArray* m_pDynamicArray;
        CStringArray* m_pStaticArray;

        /**
        * Fills the attribute category
        *@param[out] propSet - the property set to populate with the result
        */
        void FillAttribCategory(ZBPropertySet& propSet);
};

#endif
