/****************************************************************************
 * ==> PSS_GridProcessNavigation -------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will navigate through a process *
 *               and write the information to the report grid               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GridProcessNavigationH
#define PSS_GridProcessNavigationH

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
#include "zModelBP\PSS_ProcessNavigation.h"

// forward class declaration
class PSS_OStreamGrid;

#ifdef _ZREPORTBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Navigator which will navigate through a process and write the information to the report grid
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_GridProcessNavigation : public PSS_ProcessNavigation
{
    public:
        /**
        * Constructor
        *@param pModel - the model, can be NULL
        *@param pClass - the custom data class, can be NULL
        */
        PSS_GridProcessNavigation(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);

        virtual ~PSS_GridProcessNavigation();

        /**
        * Called when the navigation starts
        *@return true on success, otherwise false
        */
        virtual bool OnStart();

        /**
        * Called when the navigation ends
        *@return true on success, otherwise false
        */
        virtual bool OnFinish();

        /**
        * Called when a door symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnDoorSymbol(PSS_DoorSymbolBP* pSymbol);

        /**
        * Called when a page symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnPageSymbol(PSS_PageSymbolBP* pSymbol);

        /**
        * Called when a procedure symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);

        /**
        * Called when a process symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol);

        /**
        * Called when a start symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnStartSymbol(PSS_StartSymbolBP* pSymbol);

        /**
        * Called when a stop symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnStopSymbol(PSS_StopSymbolBP* pSymbol);

        /**
        * Called when a deliverable link symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol);

        /**
        * Called when a symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnSymbol(PSS_Symbol* pSymbol);

        /**
        * Called when a link symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnLink(PSS_LinkSymbol* pLink);

    private:
        PSS_OStreamGrid* m_pOStream;
};

#endif
