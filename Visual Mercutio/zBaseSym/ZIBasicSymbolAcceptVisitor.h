/****************************************************************************
 * ==> PSS_BasicSymbolAcceptVisitor ----------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol interface which can accept visitors      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BasicSymbolAcceptVisitorH
#define PSS_BasicSymbolAcceptVisitorH

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

// forward declaration
class ZIBasicSymbolVisitor;

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
* Symbol interface which can accept visitors
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BasicSymbolAcceptVisitor
{
    public:
        PSS_BasicSymbolAcceptVisitor();
        virtual ~PSS_BasicSymbolAcceptVisitor();

        /**
        * Checks if visitor is accepted
        *@param visitor - visitor
        *@return true if visitor is accepted, otherwise false
        */
        virtual bool AcceptVisitor(ZIBasicSymbolVisitor& visitor) = 0;
};

#endif
