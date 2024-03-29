/****************************************************************************
 * ==> PSS_ExtractModelLogicalPrestationsAssigned --------------------------*
 ****************************************************************************
 * Description : Provides a navigator which navigates through the model and *
 *               determines which prestation is attributed to which symbol. *
 *               From this list it's possible to rebuild the existing link  *
 *               hierarchy between the symbols and the prestations          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExtractModelLogicalPrestationsAssignedH
#define PSS_ExtractModelLogicalPrestationsAssignedH

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
#ifndef PSS_PrestationsEntity
    #define PSS_PrestationsEntity ZBPrestationsEntity
#endif

// forward class declaration
class PSS_PrestationsEntity;

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
* Navigates through the model and determines which prestation is attributed to which symbol
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ExtractModelLogicalPrestationsAssigned : public PSS_ModelNavigation
{
    public:
        /**
        * Constructor
        *@param pModel - the model to navigate, can be NULL
        *@param pClass - the custom data class, can be NULL
        */
        PSS_ExtractModelLogicalPrestationsAssigned(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);

        virtual ~PSS_ExtractModelLogicalPrestationsAssigned();

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
        PSS_PrestationsEntity* m_pPrestationsEntity;
        CODComponentSet        m_Set;
};

//---------------------------------------------------------------------------
// PSS_ExtractModelLogicalPrestationsAssigned
//---------------------------------------------------------------------------
CODComponentSet& PSS_ExtractModelLogicalPrestationsAssigned::GetComponentSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------

#endif
