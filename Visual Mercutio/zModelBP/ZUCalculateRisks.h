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
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif

// forward class declaration
class PSS_Log;
class PSS_BasicSymbol;
class ZBSymbol;
class PSS_LinkSymbol;
class ZBBPDoorSymbol;
class ZBBPPageSymbol;
class ZBBPProcedureSymbol;
class ZBBPProcessSymbol;
class ZBBPStartSymbol;
class ZBBPStopSymbol;
class ZBDeliverableLinkSymbol;
class ZDProcessGraphModelMdl;
class ZDProcessGraphModelMdlBP;
class ZDProcessGraphModelController;

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
                     ZDProcessGraphModelMdl*    pModel = NULL,
                     PSS_Log*                    pLog = NULL);

    virtual ~ZUCalculateRisks();

    bool Calculate(CODComponent& Symbol);

    // Returns the PSS_Log pointer on the log used for checking the symbol
    PSS_Log* GetLog()
    {
        return m_pLog;
    };

    /* Each concrete derived ZIBasicSymbolVisitor class
       must implement Visit to implement the appropriate
       algorithm
       In this concrete class the Visit will check the
       BasicSymbol passes as an argument */
    virtual bool Visit(CODComponent& Symbol);

private:

    bool CheckDoorSymbol(ZBBPDoorSymbol* pSymbol);
    bool CheckPageSymbol(ZBBPPageSymbol* pSymbol);
    bool CheckProcedureSymbol(ZBBPProcedureSymbol* pSymbol);
    bool CheckProcessSymbol(ZBBPProcessSymbol* pSymbol);
    bool CheckStartSymbol(ZBBPStartSymbol* pSymbol);
    bool CheckStopSymbol(ZBBPStopSymbol* pSymbol);
    bool CheckDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol);
    bool CheckSymbol(ZBSymbol* pSymbol);
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

    ZDProcessGraphModelMdl*    m_pModel;

    size_t                    m_OrangeCounter;
    size_t                    m_RedCounter;
};

#endif
