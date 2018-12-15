// **************************************************************************************************************
// *                                      Classe ZUBuildSymbolNewName                                            *
// **************************************************************************************************************
// * Cette classe permet la création d'un nom valide et unique pour les symboles.                                *
// **************************************************************************************************************

#if !defined(AFX_ZUBuildSymbolNewName_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUBuildSymbolNewName_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

#include "zBaseSym\ZIBasicSymbolVisitor.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 22 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZUBuildSymbolNewName : public ZIBasicSymbolVisitor
{
public:

    ZUBuildSymbolNewName( const CString BaseName = _T( "" ) );
    virtual ~ZUBuildSymbolNewName();

    CString GetNextAvailableSymbolName( CODModel& Model, int RefNumber );

    /* Each concrete derived ZIBasicSymbolVisitor class
       must implement Visit to implement the appropriate 
       algorithm 
       In this concrete class the Visit will check the
       BasicSymbol passes as an argument */
    virtual bool Visit( CODComponent& Symbol );

private:

    // JMR-MODIF - Le 23 mai 2006 - Ajout du paramètre RefNumber.
    void _GetNextAvailableSymbolName( CODModel& Model );

private:

    bool    m_Found;
    CString    m_SymbolName;
    CString    m_BaseName;
};

#endif // !defined(AFX_ZUBuildSymbolNewName_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)