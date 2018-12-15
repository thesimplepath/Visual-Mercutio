/////////////////////////////////////////////////////////////////////////////
//@doc ZUCheckValidUnit
//@module ZUCheckValidUnit.h | Interface of the <c ZUCheckValidUnit> class.
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
// <nl>Description:  ZUCheckValidUnit navigates through the process and
//                     write process information to the grid
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUCheckValidUnit_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUCheckValidUnit_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

#include "ZUProcessNavigation.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 21 juillet 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZBUserGroupEntity;

/////////////////////////////////////////////////////////////////////////////
// ZUCheckValidUnit

class AFX_EXT_CLASS ZUCheckValidUnit : public ZUProcessNavigation
{
public:

    ZUCheckValidUnit( ZDProcessGraphModelMdl* pModel = NULL, void* pClass = NULL );
    virtual ~ZUCheckValidUnit();

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();
    virtual bool OnProcedureSymbol( ZBBPProcedureSymbol* pSymbol );
    virtual bool OnStartSymbol( ZBBPStartSymbol* pSymbol );
    virtual bool OnStopSymbol( ZBBPStopSymbol* pSymbol );
};

#endif // !defined(AFX_ZUCheckValidUnit_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)