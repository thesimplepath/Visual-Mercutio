/****************************************************************************
 * ==> PSS_ExtractModelLogicalSystemAssigned -------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which navigates through the model and *
 *               determines which system is attributed to which symbol.     *
 *               From this list it's possible to rebuild the existing link  *
 *               hierarchy between the symbols and the logical systems      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExtractModelLogicalSystemAssignedH
#define PSS_ExtractModelLogicalSystemAssignedH

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

// class name mapping
#ifndef PSS_SystemEntity
    #define PSS_SystemEntity ZBSystemEntity
#endif

// forward class declaration
class PSS_SystemEntity;

#ifdef _ZMODELEXPORT
    //put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Navigates through the model and determines which logical system is attributed to which symbol
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ExtractModelLogicalSystemAssigned : public PSS_ModelNavigation
{
    public:
        /**
        * Constructor
        *@param pModel - the model to navigate, can be NULL
        *@param pClass - the custom data class, can be NULL
        */
        PSS_ExtractModelLogicalSystemAssigned(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);

        virtual ~PSS_ExtractModelLogicalSystemAssigned();

        /**
        * Gets the component set
        *@return the component set
        */
        virtual inline CODComponentSet& GetComponentSet();

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
        PSS_SystemEntity* m_pLogicalSystem;
        CODComponentSet   m_Set;
};

//---------------------------------------------------------------------------
// PSS_ExtractModelLogicalSystemAssigned
//---------------------------------------------------------------------------
CODComponentSet& PSS_ExtractModelLogicalSystemAssigned::GetComponentSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------

#endif
