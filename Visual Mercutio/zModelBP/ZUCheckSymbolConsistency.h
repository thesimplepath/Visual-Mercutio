// ZUCheckSymbolConsistency.h: interface for the ZUCheckSymbolConsistency class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUCHECKSYMBOLCONSISTENCY_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUCHECKSYMBOLCONSISTENCY_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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
class ZBBPProcessSymbol;
class ZBBPStartSymbol;
class ZBBPStopSymbol;
class ZBDeliverableLinkSymbol;
class PSS_ProcessGraphModelMdl;
class PSS_ProcessGraphModelMdlBP;
class PSS_ProcessGraphModelController;

// JMR-MODIF - Le 2 octobre 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZUCheckSymbolConsistency : public PSS_BasicSymbolVisitor
{
public:

    ZUCheckSymbolConsistency(PSS_ProcessGraphModelMdl*    pModel = NULL,
                             PSS_Log*                    pLog = NULL);

    virtual ~ZUCheckSymbolConsistency();

    // JMR-MODIF - Le 5 novembre 2006 - Ajout du paramètre ModelIsClean.
    bool CheckSymbol(CODComponent& Symbol, BOOL ModelIsClean);

    // Logging functions
    void StartLogging()
    {
        m_IsLogging = true;
    };

    void StopLogging()
    {
        m_IsLogging = false;
    };

    bool IsLogging() const
    {
        return m_IsLogging;
    };

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
    bool CheckProcessSymbol(ZBBPProcessSymbol* pSymbol);
    bool CheckStartSymbol(ZBBPStartSymbol* pSymbol);
    bool CheckStopSymbol(ZBBPStopSymbol* pSymbol);
    bool CheckDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol);
    bool CheckSymbol(PSS_Symbol* pSymbol);
    bool CheckLink(PSS_LinkSymbol* pLink);

    bool CheckInvalidCharInSymbolName(PSS_BasicSymbol* pSymbol, CString Path);
    bool CheckUniqueRef(PSS_BasicSymbol* pSymbol);
    bool RefExist(int ref);

    void DeleteCorruptedSymbol(PSS_Symbol*                  m_Symbol,
                               PSS_ProcessGraphModelMdlBP* m_StartRootModel = NULL);

private:

    bool                    m_IsLogging;

    PSS_Log*                    m_pLog;

    int*                    m_pIDArray;
    int                        m_RefIDSize;

    PSS_ProcessGraphModelMdl*    m_pModel;

    size_t                    m_ErrorCounter;
    size_t                    m_WarningCounter;
};

#endif
