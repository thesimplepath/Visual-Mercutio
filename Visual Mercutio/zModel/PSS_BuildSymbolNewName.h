/****************************************************************************
 * ==> PSS_BuildSymbolNewName ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a helper which creates an unique and valid name   *
 *               for each symbols                                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BuildSymbolNewNameH
#define PSS_BuildSymbolNewNameH

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

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Helper which creates an unique and valid name for each symbols
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BuildSymbolNewName : public PSS_BasicSymbolVisitor
{
    public:
        /**
        * Constructor
        *@param baseName - the base name
        */
        PSS_BuildSymbolNewName(const CString& baseName = _T(""));

        virtual ~PSS_BuildSymbolNewName();

        /**
        * Gets the next available symbol name
        *@param model - the model
        *@param refNumber - the reference number
        *@return the next available symbol name
        */
        virtual CString GetNextAvailableSymbolName(CODModel& model, int refNumber);

        /**
        * Visits a symbol
        *@param symbol - the symbol component to visit
        *@return true if the visit process should continue to next symbol, false if should be stopped
        *@note Each concrete derived ZIBasicSymbolVisitor class must implement the Visit() function
        *      to implement the appropriate algorithm. In the current class Visit() will check if the
        *      BasicSymbol() passes as an argument
        */
        virtual bool Visit(CODComponent& symbol);

    private:
        CString m_SymbolName;
        CString m_BaseName;
        bool    m_Found;

        /**
        * Gets the next available symbol name
        *@param model - the model
        *@return the next available symbol name
        */
        void GetNextAvailableSymbolNamePvt(CODModel& model);
};

#endif
