/****************************************************************************
 * ==> PSS_ProcessConceptorNavigation --------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will navigate through the       *
 *               processes and write the Conceptor info to the report       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessConceptorNavigationH
#define PSS_ProcessConceptorNavigationH

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
* Navigator which will navigate through the processes and write the Conceptor info to the report
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ProcessConceptorNavigation : public PSS_ProcessNavigation
{
    public:
        /**
        * Constructor
        *@param pModel - the model, can be NULL
        *@param pClass - the custom data class, can be NULL
        */
        PSS_ProcessConceptorNavigation(PSS_ProcessGraphModelMdl* pModel              = NULL,
                                       void*                     pClass              = NULL,
                                       PSS_ProcessGraphModelMdl* pRootModel          = NULL,
                                       const CString&            domainName          = _T(""),
                                       const CString&            unitName            = _T(""),
                                       BOOL                      includeSynthesis    = TRUE,
                                       BOOL                      includeDetail       = TRUE,
                                       BOOL                      includeDeliverables = TRUE);

        virtual ~PSS_ProcessConceptorNavigation();

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
        virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pProcedure);

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
        PSS_ProcessSymbolBP*      m_pPreviousProcess;
        PSS_ProcessGraphModelMdl* m_pRootModel;
        CGXStyle                  m_BlueStyle;
        CGXStyle                  m_OrangeStyle;
        CGXStyle                  m_GrayStyle;
        CGXStyle                  m_BlackBorderStyle;
        CGXStyle                  m_LeftOnlyBlackBorderStyle;
        CGXStyle                  m_RightOnlyBlackBorderStyle;
        CGXStyle                  m_TopOnlyBlackBorderStyle;
        CGXStyle                  m_BottomOnlyBlackBorderStyle;
        CString                   m_DomainName;
        CString                   m_UnitName;
        CString                   m_CurrentProcessName;
        BOOL                      m_IncludeSynthesis;
        BOOL                      m_IncludeDetail;
        BOOL                      m_IncludeDeliverables;
        bool                      m_First;

        /**
        * Shows the process
        *@return true on success, otherwise false
        */
        bool ShowProcess();

        /**
        * Starts the selection
        *@param nodes - the selected nodes
        *@return true on success, otherwise false
        */
        bool StartSection(CODNodeArray& nodes);
};

#endif
