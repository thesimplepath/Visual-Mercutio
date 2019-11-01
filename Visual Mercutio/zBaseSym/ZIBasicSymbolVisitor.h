/****************************************************************************
 * ==> PSS_BasicSymbolVisitor ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol interface which can navigate through     *
 *               other symbol classes and visit them                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BasicSymbolVisitorH
#define PSS_BasicSymbolVisitorH

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

#ifdef _ZBASESYMEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Symbol interface which can navigate through other symbols and visit them
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BasicSymbolVisitor
{
    public:
        PSS_BasicSymbolVisitor();
        virtual ~PSS_BasicSymbolVisitor();

        /**
        * Visits the target symbol
        *@param symbol - target symbol to visit
        *@return true if visit succeeded, otherwise false
        */
        virtual bool Visit(CODComponent& symbol) = 0;
};

#endif
