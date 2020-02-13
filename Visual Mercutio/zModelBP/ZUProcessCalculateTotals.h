/////////////////////////////////////////////////////////////////////////////
//@doc ZUProcessCalculateTotals
//@module ZUProcessCalculateTotals.h | Interface of the <c ZUProcessCalculateTotals> class.
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
// <nl>Description:  ZUProcessCalculateTotals navigates through the process and
//                     calculates the procedure totals
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUProcessCalculateTotals_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUProcessCalculateTotals_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

// JMR-MODIF - Le 14 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZUProcessCalculateTotals

class AFX_EXT_CLASS ZUProcessCalculateTotals : public ZUProcessNavigation
{
public:

    ZUProcessCalculateTotals(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);
    virtual ~ZUProcessCalculateTotals();

    double GetProcedureCost() const
    {
        return m_ProcedureCost;
    };

    double GetProcedureWorkloadForecast() const
    {
        return m_ProcedureWorkloadForecast;
    };

    double GetProcedureCostForecast() const
    {
        return m_ProcedureCostForecast;
    };

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();
    virtual bool OnDoorSymbol(PSS_DoorSymbolBP* pSymbol);
    virtual bool OnPageSymbol(PSS_PageSymbolBP* pSymbol);
    virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);
    virtual bool OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol);
    virtual bool OnStartSymbol(PSS_StartSymbolBP* pSymbol);
    virtual bool OnStopSymbol(ZBBPStopSymbol* pSymbol);
    virtual bool OnDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol);

private:

    double m_ProcedureCost;
    double m_ProcedureWorkloadForecast;
    double m_ProcedureCostForecast;
};

#endif
