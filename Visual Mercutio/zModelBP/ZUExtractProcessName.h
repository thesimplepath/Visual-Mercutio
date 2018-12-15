/////////////////////////////////////////////////////////////////////////////
//@doc ZUExtractProcessName
//@module ZUExtractProcessName.h | Interface of the <c ZUExtractProcessName> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         07/2001
// <nl>Description:  ZUExtractProcessName extract all process names of a Mercutio model
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUExtractProcessName_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUExtractProcessName_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

/////////////////////////////////////////////////////////////////////////////
// Forward declaration
class ZILog;
class ZBBPProcessSymbol;
class ZDProcessGraphModelMdl;

#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 8 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZUExtractProcessName : public ZIBasicSymbolVisitor
{
public:

    ZUExtractProcessName( ZDProcessGraphModelMdl* pModel = NULL, ZILog* pLog = NULL );
    virtual ~ZUExtractProcessName();

    // JMR-MODIF - Le 29 mars 2006 - Ajout du paramètre FirstElementToSort.
    bool FillProcessNameArray( CStringArray* pArray, int FirstElementToSort = 0 );

    /* Each concrete derived ZIBasicSymbolVisitor class
       must implement Visit to implement the appropriate 
       algorithm 
       In this concrete class the Visit will check the
       BasicSymbol passes as an argument */
    virtual bool Visit( CODComponent& Symbol );

private:

    bool AddProcessSymbol( ZBBPProcessSymbol* pSymbol );
    bool Exist( CStringArray& Array, const CString ProcessName );

    // JMR-MODIF - Le 8 mars 2006 - Ajout de la fonction Sort.
    // JMR-MODIF - Le 29 mars 2006 - Ajout du paramètre First.
    void Sort( int First = 0 );

private:

    ZILog*                    m_pLog;
    ZDProcessGraphModelMdl* m_pModel;
    CStringArray*            m_pArray;
};

#endif // !defined(AFX_ZUExtractProcessName_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)