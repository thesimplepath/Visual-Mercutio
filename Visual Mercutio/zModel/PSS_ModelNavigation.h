/****************************************************************************
 * ==> PSS_ModelNavigation -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic model navigator                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModelNavigationH
#define PSS_ModelNavigationH

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
#include "zBaseSym\PSS_BasicSymbolVisitor.h"

// class name mapping
#ifndef PSS_Symbol
    #define PSS_Symbol ZBSymbol
#endif
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_Symbol;
class PSS_LinkSymbol;
class PSS_ProcessGraphModelMdl;
class PSS_Log;

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
* Generic navigator which allows to navigate through the model symbols
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ModelNavigation : public PSS_BasicSymbolVisitor
{
    public:
        /**
        * Constructor
        *@param pModel - the model to navigate, can be NULL
        *@param pClass - the custom data class, can be NULL
        */
        PSS_ModelNavigation(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);

        virtual ~PSS_ModelNavigation();

        /**
        * Navigates through the model
        *@param pModel - the model to navigate
        *@param pClass - the custom data class
        *@return true if the navigation may continue, false if the navigation should stop
        */
        virtual bool Navigate(PSS_ProcessGraphModelMdl* pModel, void* pClass);
        virtual bool Navigate(PSS_ProcessGraphModelMdl* pModel);
        virtual bool Navigate();

        /**
        * Sets the logger
        *@param pLog - the logger to set
        */
        virtual inline void SetLog(PSS_Log* pLog);

        /**
        * Visits the target symbol
        *@param symbol - target symbol to visit
        *@return true if visit succeeded, otherwise false
        */
        virtual bool Visit(CODComponent& symbol);

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

    protected:
        PSS_ProcessGraphModelMdl* m_pModel;
        PSS_Log*                  m_pLog;
        void*                     m_pClass;
};

//---------------------------------------------------------------------------
// PSS_ModelNavigation
//---------------------------------------------------------------------------
void PSS_ModelNavigation::SetLog(PSS_Log* pLog)
{
    m_pLog = pLog;
}
//---------------------------------------------------------------------------

#endif
