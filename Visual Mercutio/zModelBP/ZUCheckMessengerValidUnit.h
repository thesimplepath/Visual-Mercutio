/////////////////////////////////////////////////////////////////////////////
//@doc ZUCheckMessengerValidUnit
//@module ZUCheckMessengerValidUnit.h | Interface of the <c ZUCheckMessengerValidUnit> class.
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
// <nl>Description:  ZUCheckMessengerValidUnit navigates through the process and
//                     write process information to the grid
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUCheckMessengerValidUnit_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUCheckMessengerValidUnit_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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
#include "ZUProcessNavigation.h"

// class name mapping
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif

// forward class declaration
class PSS_UserGroupEntity;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 20 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZUCheckMessengerValidUnit

class AFX_EXT_CLASS ZUCheckMessengerValidUnit : public ZUProcessNavigation
{
public:

    ZUCheckMessengerValidUnit(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);
    virtual ~ZUCheckMessengerValidUnit();

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();
    virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);
    virtual bool OnStartSymbol(PSS_StartSymbolBP* pSymbol);
    virtual bool OnStopSymbol(PSS_StopSymbolBP* pSymbol);
};

#endif
