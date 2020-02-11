// **************************************************************************************************************
// *                                             Classe ZUCalculateRisks                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 21 juillet 2007 - Ajout de la classe ZUCalculateRisks.                                        *
// **************************************************************************************************************
// * Cette classe permet de calculer le niveau des risques dans le modèle.                                        *
// **************************************************************************************************************

#if !defined(AFX_ZUCALCULATERISKS_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUCALCULATERISKS_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
class ZBBPStartSymbol;
class ZBBPStopSymbol;
class ZBDeliverableLinkSymbol;
class PSS_ProcessGraphModelMdl;
class PSS_ProcessGraphModelMdlBP;
class PSS_ProcessGraphModelController;

class ZUCalculateRisks : public PSS_BasicSymbolVisitor
{
public:

    ZUCalculateRisks(int                        OrangeSeverity,
                     int                        RedSeverity,
                     float                        OrangeUE,
                     float                        RedUE,
                     float                        OrangePOA,
                     float                        RedPOA,
                     BOOL                        OrangeAction,
                     BOOL                        OrangeNoAction,
                     BOOL                        RedAction,
                     BOOL                        RedNoAction,
                     BOOL                        DefaultColors,
                     PSS_ProcessGraphModelMdl*    pModel = NULL,
                     PSS_Log*                    pLog = NULL);

    virtual ~ZUCalculateRisks();

    bool Calculate(CODComponent& Symbol);

    // Returns the PSS_Log pointer on the log used for checking the symbol
    PSS_Log* GetLog()
    {
        return m_pLog;
    };

    /**
    * Visits the target symbol
    *@param symbol - target symbol to visit
    *@return true if visit succeeded, otherwise false
    */
    virtual bool Visit(CODComponent& symbol);

private:

    bool CheckDoorSymbol(PSS_DoorSymbolBP* pSymbol);
    bool CheckPageSymbol(PSS_PageSymbolBP* pSymbol);
    bool CheckProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);
    bool CheckProcessSymbol(PSS_ProcessSymbolBP* pSymbol);
    bool CheckStartSymbol(ZBBPStartSymbol* pSymbol);
    bool CheckStopSymbol(ZBBPStopSymbol* pSymbol);
    bool CheckDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol);
    bool CheckSymbol(PSS_Symbol* pSymbol);
    bool CheckLink(PSS_LinkSymbol* pLink);

private:

    int                        m_OrangeSeverity;
    int                        m_RedSeverity;

    float                    m_OrangeUE;
    float                    m_RedUE;
    float                    m_OrangePOA;
    float                    m_RedPOA;

    BOOL                    m_OrangeAction;
    BOOL                    m_OrangeNoAction;
    BOOL                    m_RedAction;
    BOOL                    m_RedNoAction;
    BOOL                    m_DefaultColors;

    PSS_Log*                    m_pLog;

    PSS_ProcessGraphModelMdl*    m_pModel;

    size_t                    m_OrangeCounter;
    size_t                    m_RedCounter;
};

#endif
