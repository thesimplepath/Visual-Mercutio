// **********************************************************************************************************
// *                                  Classe ZUDeleteCorruptedSymbols                                        *
// **********************************************************************************************************
// * JMR-MODIF - Le 19 octobre 2006 - Ajout de la classe ZUDeleteCorruptedSymbols.                            *
// **********************************************************************************************************
// * Cette classe contrôle et détruit les symboles corrompus, par exemple : Porte sans clone, copie sans    *
// * symbole local rattaché, label sans lien, etc...                                                        *
// **********************************************************************************************************

#if !defined(AFX_ZUDeleteCorruptedSymbols_H__78F947C3_2DC6_4808_A357_392EF1C0512F__INCLUDED_)
#define AFX_ZUDeleteCorruptedSymbols_H__78F947C3_2DC6_4808_A357_392EF1C0512F__INCLUDED_

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

#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"

#include "PSS_DoorSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "ZBBPStopSymbol.h"
#include "PSS_PackageSymbolBP.h"
#include "ZBDeliverableLinkSymbol.h"

#include "PSS_ProcessGraphModelMdlBP.h"

#include "zBaseLib\PSS_Log.h"

#include "zModel\PSS_GenericSymbolErrorLine.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class ZUDeleteCorruptedSymbols
{
public:

    ZUDeleteCorruptedSymbols();
    ~ZUDeleteCorruptedSymbols();

    void CheckModel(PSS_ProcessGraphModelMdlBP* m_StartRootModel);

    CODComponentSet* GetCorruptedSymbolList();

private:

    BOOL IsCorrupted(PSS_ProcessSymbolBP* m_Symbol);
    BOOL IsCorrupted(PSS_ProcedureSymbolBP* m_Symbol);
    BOOL IsCorrupted(PSS_StartSymbolBP* m_Symbol);
    BOOL IsCorrupted(ZBBPStopSymbol* m_Symbol);
    BOOL IsCorrupted(PSS_DoorSymbolBP* m_Symbol);
    BOOL IsCorrupted(PSS_PageSymbolBP* m_Symbol);
    BOOL IsCorrupted(PSS_PackageSymbolBP* m_Symbol);
    BOOL IsCorrupted(ZBDeliverableLinkSymbol* m_Symbol);

private:
    CODComponentSet CorruptedSymbols;
};

#endif
