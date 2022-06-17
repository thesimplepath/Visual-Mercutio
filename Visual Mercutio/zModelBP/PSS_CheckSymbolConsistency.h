/****************************************************************************
 * ==> PSS_CheckSymbolConsistency ------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to check the symbol consistency       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CheckSymbolConsistencyH
#define PSS_CheckSymbolConsistencyH

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
#ifndef PSS_ProcessGraphModelMdlBP
    #define PSS_ProcessGraphModelMdlBP ZDProcessGraphModelMdlBP
#endif

// forward class declaration
class PSS_Log;
class PSS_BasicSymbol;
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
class PSS_ProcessGraphModelMdlBP;
class PSS_ProcessGraphModelController;

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
* Navigator to check the symbol consistency
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_CheckSymbolConsistency : public PSS_BasicSymbolVisitor
{
    public:
        /**
        * Constructor
        *@param pModel - the model to navigate
        *@param pClass - the custom data class, can be NULL
        */
        PSS_CheckSymbolConsistency(PSS_ProcessGraphModelMdl* pModel = NULL, PSS_Log* pLog = NULL);

        virtual ~PSS_CheckSymbolConsistency();

        /**
        * Checks the symbol
        *@param component - the symbol component
        *@param modelIsClean - if TRUE, the model is clean
        *@return true on success, otherwise false
        */
        virtual bool CheckSymbol(CODComponent& component, BOOL modelIsClean);

        /**
        * Starts the logging
        */
        virtual inline void StartLogging();

        /**
        * Stops the logging
        */
        virtual inline void StopLogging();

        /**
        * Checks if the logging is enabled
        *@return true if the logging is enabled, otherwise false
        */
        virtual inline bool IsLogging() const;

        /**
        * Gets the logger used for checking the symbol
        *@return the logger used for checking the symbol
        */
        virtual inline PSS_Log* GetLog();

        /**
        * Visits the target symbol
        *@param component - target symbol component to visit
        *@return true if visit succeeded, otherwise false
        */
        virtual bool Visit(CODComponent& component);

    private:
        PSS_ProcessGraphModelMdl* m_pModel;
        PSS_Log*                  m_pLog;
        int*                      m_pIDArray;
        int                       m_RefIDSize;
        std::size_t               m_ErrorCounter;
        std::size_t               m_WarningCounter;
        bool                      m_IsLogging;

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

        /**
        * Checks if the symbol name contains invalid chars
        *@param pSymbol - the symbol to check
        *@param path - the symbol path
        *@return true if the symbol name contains invalid chars, otherwise false
        */
        bool CheckInvalidCharInSymbolName(PSS_BasicSymbol* pSymbol, const CString& path);

        /**
        * Checks if the symbol reference is unique
        *@param pSymbol - the symbol to check
        *@return true if the symbol reference is unique, otherwise false
        */
        bool CheckUniqueRef(PSS_BasicSymbol* pSymbol);

        /**
        * Checks if the rules exist in the referential
        *@param pSymbol - symbol owning the rules
        *@return true if the rules exist, otherwise false
        */
        bool RulesExist(PSS_Symbol* pSymbol);

        /**
        * Checks if the rules exist in the referential
        *@param pSymbol - symbol owning the rules
        *@return true if the rules exist, otherwise false
        */
        bool RulesExist(PSS_LinkSymbol* pSymbol);

        /**
        * Checks if a reference exists
        *@param ref - the reference to check
        *@return true if the reference exists, otherwise false
        */
        bool RefExist(int ref);
};

//---------------------------------------------------------------------------
// PSS_CheckSymbolConsistency
//---------------------------------------------------------------------------
void PSS_CheckSymbolConsistency::StartLogging()
{
    m_IsLogging = true;
}
//---------------------------------------------------------------------------
void PSS_CheckSymbolConsistency::StopLogging()
{
    m_IsLogging = false;
}
//---------------------------------------------------------------------------
bool PSS_CheckSymbolConsistency::IsLogging() const
{
    return m_IsLogging;
}
//---------------------------------------------------------------------------
PSS_Log* PSS_CheckSymbolConsistency::GetLog()
{
    return m_pLog;
}
//---------------------------------------------------------------------------

#endif
