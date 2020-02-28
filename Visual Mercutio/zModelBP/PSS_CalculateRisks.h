/****************************************************************************
 * ==> PSS_CalculateRisks --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a Risk calculator                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CalculateRisksH
#define PSS_CalculateRisksH

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
* Risk calculator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_CalculateRisks : public PSS_BasicSymbolVisitor
{
    public:
        /**
        * Constructor
        *@param orangeSeverity - the orange severity level
        *@param redSeverity - the red severity level
        *@param orangeUE - the orange unitary estimation value
        *@param redUE - the red unitary estimation value
        *@param orangePOA - the orange annual operating loss (perte operationnelle annuelle in French) value
        *@param redPOA - the red annual operating loss (perte operationnelle annuelle in French) value
        *@param orangeAction - if TRUE, the orange action alarm will be enabled
        *@param orangeNoAction - if TRUE, the orange no action alarm will be enabled
        *@param redAction - if TRUE, the red action alarm will be enabled
        *@param redNoAction - if TRUE, the red no action alarm will be enabled
        *@param defaultColors - if TRUE, the default color will be used
        *@param pModel - the model
        *@param pLog - the log
        */
        PSS_CalculateRisks(int                       orangeSeverity,
                           int                       redSeverity,
                           float                     orangeUE,
                           float                     redUE,
                           float                     orangePOA,
                           float                     redPOA,
                           BOOL                      orangeAction,
                           BOOL                      orangeNoAction,
                           BOOL                      redAction,
                           BOOL                      redNoAction,
                           BOOL                      defaultColors,
                           PSS_ProcessGraphModelMdl* pModel = NULL,
                           PSS_Log*                  pLog   = NULL);

        virtual ~PSS_CalculateRisks();

        /**
        * Calculates the risks
        *@param component - the symbol component on which the risks should be calculated
        *@return true on success, otherwise false
        */
        virtual bool Calculate(CODComponent& component);

        /**
        * Gets the log used to check the symbol
        *@return the log used to check the symbol
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
        float                     m_OrangeUE;
        float                     m_RedUE;
        float                     m_OrangePOA;
        float                     m_RedPOA;
        std::size_t               m_OrangeCounter;
        std::size_t               m_RedCounter;
        int                       m_OrangeSeverity;
        int                       m_RedSeverity;
        BOOL                      m_OrangeAction;
        BOOL                      m_OrangeNoAction;
        BOOL                      m_RedAction;
        BOOL                      m_RedNoAction;
        BOOL                      m_DefaultColors;

        /**
        * Checks the door symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckDoorSymbol(PSS_DoorSymbolBP* pSymbol);

        /**
        * Checks the page symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckPageSymbol(PSS_PageSymbolBP* pSymbol);

        /**
        * Checks the procedure symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);

        /**
        * Checks the process symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckProcessSymbol(PSS_ProcessSymbolBP* pSymbol);

        /**
        * Checks the start symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckStartSymbol(PSS_StartSymbolBP* pSymbol);

        /**
        * Checks the stop symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckStopSymbol(PSS_StopSymbolBP* pSymbol);

        /**
        * Checks the deliverable link symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol);

        /**
        * Checks the symbol
        *@param pSymbol - the symbol to check
        *@return true on success, otherwise false
        */
        bool CheckSymbol(PSS_Symbol* pSymbol);

        /**
        * Checks the link
        *@param pLink - the link to check
        *@return true on success, otherwise false
        */
        bool CheckLink(PSS_LinkSymbol* pLink);
};

//---------------------------------------------------------------------------
// PSS_CalculateRisks
//---------------------------------------------------------------------------
PSS_Log* PSS_CalculateRisks::GetLog()
{
    return m_pLog;
}
//---------------------------------------------------------------------------

#endif
