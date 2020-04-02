/****************************************************************************
 * ==> PSS_SynthesisNavigation ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will navigate through the       *
 *               processes and write the synthesis info to the report       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SynthesisNavigationH
#define PSS_SynthesisNavigationH

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
* Navigator which will navigate through the processes and write the synthesis info to the report
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SynthesisNavigation : public PSS_ProcessNavigation
{
    public:
        /**
        * Constructor
        *@param pModel - the model, can be NULL
        *@param pClass - the custom data class, can be NULL
        *@param pRootModel - the root model, can be NULL
        *@param domainName - the domain name
        *@param unitName - the unit name
        */
        PSS_SynthesisNavigation(PSS_ProcessGraphModelMdl* pModel     = NULL,
                                void*                     pClass     = NULL,
                                PSS_ProcessGraphModelMdl* pRootModel = NULL,
                                const CString&            domainName = _T(""),
                                const CString&            unitName   = _T(""));

        virtual ~PSS_SynthesisNavigation();

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
        PSS_OStreamGrid*          m_pOStream;
        PSS_ProcessGraphModelMdl* m_pRootModel;
        CGXStyle                  m_BlueStyle;
        CString                   m_DomainName;
        CString                   m_UnitName;
        CString                   m_CurrentProcessName;
};

#endif
