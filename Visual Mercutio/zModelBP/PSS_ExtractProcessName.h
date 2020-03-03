/****************************************************************************
 * ==> PSS_ExtractProcessName ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to find and extract all process names *
 *               of a Mercutio model                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExtractProcessNameH
#define PSS_ExtractProcessNameH

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
#ifndef PSS_ProcessSymbolBP
    #define PSS_ProcessSymbolBP ZBBPProcessSymbol
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declarations
class PSS_ProcessSymbolBP;
class PSS_ProcessGraphModelMdl;
class PSS_Log;

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
* Navigator to find and extract all process names of a Mercutio model
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ExtractProcessName : public PSS_BasicSymbolVisitor
{
    public:
        /**
        * Constructor
        *@param pModel - the model
        *@param pLog - the log
        */
        PSS_ExtractProcessName(PSS_ProcessGraphModelMdl* pModel = NULL, PSS_Log* pLog = NULL);

        virtual ~PSS_ExtractProcessName();

        /**
        * Fills the process name array
        *@param pArray - the array to fill with the process names
        *@param firstIndexToSort - the first index from which the items should be sorted
        *@return true on success, otherwise false
        */
        virtual bool FillProcessNameArray(CStringArray* pArray, int firstIndexToSort = 0);

        /**
        * Visits the target symbol
        *@param component - target symbol component to visit
        *@return true if visit succeeded, otherwise false
        */
        virtual bool Visit(CODComponent& component);

    private:
        PSS_Log*                  m_pLog;
        PSS_ProcessGraphModelMdl* m_pModel;
        CStringArray*             m_pArray;

        /**
        * Adds a process symbol
        *@param pSymbol - the symbol to add
        *@return true on success, otherwise false
        */
        bool AddProcessSymbol(PSS_ProcessSymbolBP* pSymbol);

        /**
        * Checks if a process exists
        *@param strArray - the array containing the process names
        *@param processName - the process name to find
        *@return true on success, otherwise false
        */
        bool Exist(const CStringArray& strArray, const CString& processName);

        /**
        * Sorts the process names
        *@param first - the first index from which the items should be sorted
        */
        void Sort(int first = 0);
};

#endif
