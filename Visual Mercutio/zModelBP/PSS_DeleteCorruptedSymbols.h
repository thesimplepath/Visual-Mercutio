/****************************************************************************
 * ==> PSS_DeleteCorruptedSymbols ------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to delete the corrupted symbols       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DeleteCorruptedSymbolsH
#define PSS_DeleteCorruptedSymbolsH

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
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "PSS_DoorSymbolBP.h"
#include "PSS_PageSymbolBP.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_ProcessSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "PSS_StopSymbolBP.h"
#include "PSS_PackageSymbolBP.h"
#include "PSS_DeliverableLinkSymbolBP.h"
#include "PSS_ProcessGraphModelMdlBP.h"

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
* Navigator to delete the corrupted symbols, e.g door without clone, duplicate
* without attached local symbol, label without link, ...
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_DeleteCorruptedSymbols
{
    public:
        PSS_DeleteCorruptedSymbols();
        virtual ~PSS_DeleteCorruptedSymbols();

        /**
        * Checks the model
        *@param pRootModel - the root model to search from
        *@return true on success, otherwise false
        */
        virtual void CheckModel(PSS_ProcessGraphModelMdlBP* pRootModel);

        /**
        * Gets the corrupted symbol list
        *@return the corrupted symbol list
        */
        virtual CODComponentSet* GetCorruptedSymbolList();

    private:
        CODComponentSet m_CorruptedSymbols;

        /**
        * Checks if a symbol is corrupted
        *@param pSymbol - the symbol to check
        *@return TRUE if the symbol is corrupted, otherwise FALSE
        */
        BOOL IsCorrupted(PSS_ProcessSymbolBP*         pSymbol);
        BOOL IsCorrupted(PSS_ProcedureSymbolBP*       pSymbol);
        BOOL IsCorrupted(PSS_StartSymbolBP*           pSymbol);
        BOOL IsCorrupted(PSS_StopSymbolBP*            pSymbol);
        BOOL IsCorrupted(PSS_DoorSymbolBP*            pSymbol);
        BOOL IsCorrupted(PSS_PageSymbolBP*            pSymbol);
        BOOL IsCorrupted(PSS_PackageSymbolBP*         pSymbol);
        BOOL IsCorrupted(PSS_DeliverableLinkSymbolBP* pSymbol);
};

#endif
