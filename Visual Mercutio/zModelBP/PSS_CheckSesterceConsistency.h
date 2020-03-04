/****************************************************************************
 * ==> PSS_CheckSesterceConsistency ----------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to check Sesterce consistency         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CheckSesterceConsistencyH
#define PSS_CheckSesterceConsistencyH

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
#ifndef PSS_DoorSymbolBP
    #define PSS_DoorSymbolBP ZBBPDoorSymbol
#endif
#ifndef PSS_PageSymbolBP
    #define PSS_PageSymbolBP ZBBPPageSymbol
#endif
#ifndef PSS_ProcedureSymbolBP
    #define PSS_ProcedureSymbolBP ZBBPProcedureSymbol
#endif
#ifndef PSS_ProcessSymbolBP
    #define PSS_ProcessSymbolBP ZBBPProcessSymbol
#endif
#ifndef PSS_StartSymbolBP
    #define PSS_StartSymbolBP ZBBPStartSymbol
#endif
#ifndef PSS_StopSymbolBP
    #define PSS_StopSymbolBP ZBBPStopSymbol
#endif
#ifndef PSS_DeliverableLinkSymbolBP
    #define PSS_DeliverableLinkSymbolBP ZBDeliverableLinkSymbol
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_Log;
class PSS_Symbol;
class PSS_LinkSymbol;
class PSS_DoorSymbolBP;
class PSS_PageSymbolBP;
class PSS_ProcedureSymbolBP;
class PSS_ProcessSymbolBP;
class PSS_StartSymbolBP;
class PSS_StopSymbolBP;
class PSS_DeliverableLinkSymbolBP;
class PSS_ProcessGraphModelMdl;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Navigator to check Messenger valid unit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_CheckSesterceConsistency : public PSS_BasicSymbolVisitor
{
    public:
        /**
        * Constructor
        *@param pModel - the model to navigate
        *@param pClass - the custom data class, can be NULL
        */
        PSS_CheckSesterceConsistency(PSS_ProcessGraphModelMdl* pModel = NULL, PSS_Log* pLog = NULL);

        virtual ~PSS_CheckSesterceConsistency();

        /**
        * Checks the model
        *@return true on success, otherwise false
        */
        virtual bool CheckModel();

        /**
        * Gets the error counter
        *@return the error counter
        */
        virtual inline std::size_t GetErrorCounter() const;

        /**
        * Gets the warning counter
        *@return the warning counter
        */
        virtual inline std::size_t GetWarningCounter() const;

        /**
        * Visits the target symbol
        *@param component - target symbol component to visit
        *@return true if visit succeeded, otherwise false
        */
        virtual bool Visit(CODComponent& component);

    private:
        PSS_ProcessGraphModelMdl* m_pModel;
        PSS_Log*                  m_pLog;
        std::size_t               m_ErrorCounter;
        std::size_t               m_WarningCounter;

        /**
        * Checks a door symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckDoorSymbol(PSS_DoorSymbolBP* pSymbol);

        /**
        * Checks a page symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckPageSymbol(PSS_PageSymbolBP* pSymbol);

        /**
        * Checks a procedure symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);

        /**
        * Checks a process symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckProcessSymbol(PSS_ProcessSymbolBP* pSymbol);

        /**
        * Checks a start symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckStartSymbol(PSS_StartSymbolBP* pSymbol);

        /**
        * Checks a stop symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckStopSymbol(PSS_StopSymbolBP* pSymbol);

        /**
        * Checks a deliverable symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol);

        /**
        * Checks a symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckSymbol(PSS_Symbol* pSymbol);

        /**
        * Checks a link symbol
        *@param pLink - the link symbol to check
        *@return true on success, otherwise false
        */
        bool CheckLink(PSS_LinkSymbol* pLink);
};

//---------------------------------------------------------------------------
// PSS_CheckSesterceConsistency
//---------------------------------------------------------------------------
std::size_t PSS_CheckSesterceConsistency::GetErrorCounter() const
{
    return m_ErrorCounter;
}
//---------------------------------------------------------------------------
std::size_t PSS_CheckSesterceConsistency::GetWarningCounter() const
{
    return m_WarningCounter;
}
//---------------------------------------------------------------------------

#endif
