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
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

#include "ZBBPDoorSymbol.h"
#include "ZBBPPageSymbol.h"
#include "ZBBPProcedureSymbol.h"
#include "ZBBPProcessSymbol.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"
#include "ZBBPPackageSymbol.h"
#include "ZBDeliverableLinkSymbol.h"

#include "ProcGraphModelMdlBP.h"

#include "zBaseLib\ZILog.h"

#include "zModel\ZBGenericSymbolErrorLine.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
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

    void CheckModel( ZDProcessGraphModelMdlBP* m_StartRootModel );

    CODComponentSet* GetCorruptedSymbolList();

private:

    BOOL IsCorrupted( ZBBPProcessSymbol* m_Symbol );
    BOOL IsCorrupted( ZBBPProcedureSymbol* m_Symbol );
    BOOL IsCorrupted( ZBBPStartSymbol* m_Symbol );
    BOOL IsCorrupted( ZBBPStopSymbol* m_Symbol );
    BOOL IsCorrupted( ZBBPDoorSymbol* m_Symbol );
    BOOL IsCorrupted( ZBBPPageSymbol* m_Symbol );
    BOOL IsCorrupted( ZBBPPackageSymbol* m_Symbol );
    BOOL IsCorrupted( ZBDeliverableLinkSymbol* m_Symbol );

private:

    CODComponentSet CorruptedSymbols;
};

#endif // !defined(AFX_ZUDeleteCorruptedSymbols_H__78F947C3_2DC6_4808_A357_392EF1C0512F__INCLUDED_)