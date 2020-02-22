/////////////////////////////////////////////////////////////////////////////
//@doc ZUProcessClearDurationFigures
//@module ZUProcessClearDurationFigures.h | Interface of the <c ZUProcessClearDurationFigures> class.
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
// <nl>Description:  ZUProcessClearDurationFigures navigates through the process and
//                     clear all number used for the duration calculation
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUProcessClearDurationFigures_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUProcessClearDurationFigures_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "ZUProcessNavigation.h"

#ifdef _ZMODELBPEXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZUProcessClearDurationFigures : public ZUProcessNavigation
{
public:
    ZUProcessClearDurationFigures(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);
    virtual ~ZUProcessClearDurationFigures();

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();
    virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);
    virtual bool OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol);
};

#endif
