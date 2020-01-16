/****************************************************************************
 * ==> PSS_BuildGenericSymbolNewName ---------------------------------------*
 ****************************************************************************
 * Description : Provides a helper which creates an unique and valid name   *
 *               for each generic symbols                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BuildGenericSymbolNewNameH
#define PSS_BuildGenericSymbolNewNameH

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
* Helper which creates an unique and valid name for each generic symbols
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BuildGenericSymbolNewName : public PSS_BasicSymbolVisitor
{
    public:
        /**
        * Constructor
        *@param baseName - the base name
        */
        PSS_BuildGenericSymbolNewName(const CString& baseName = _T(""));

        virtual ~PSS_BuildGenericSymbolNewName();

        /**
        * Gets the next available symbol name
        *@param model - the model
        *@return the next available symbol name
        */
        virtual CString GetNextAvailableSymbolName(CODModel& model);

        /**
        * Visits the target symbol
        *@param symbol - target symbol to visit
        *@return true if visit succeeded, otherwise false
        */
        virtual bool Visit(CODComponent& symbol);

    private:
        CString m_GenericSymbolName;
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
