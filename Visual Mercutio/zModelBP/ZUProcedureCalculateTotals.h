/////////////////////////////////////////////////////////////////////////////
//@doc ZUProcedureCalculateTotals
//@module ZUProcedureCalculateTotals.h | Interface of the <c ZUProcedureCalculateTotals> class.
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
// <nl>Description:  ZUProcedureCalculateTotals navigates through the process and
//                     write process information to the grid
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUProcedureCalculateTotals_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUProcedureCalculateTotals_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

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

// processsoft
#include "ZUProcessNavigation.h"
#include "PSS_AnnualNumberPropertiesBP.h"

// class name mapping
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif

// forward class declaration
class PSS_UserGroupEntity;

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
// ZBProcedureCalculateTotalsInformation

class AFX_EXT_CLASS ZBProcedureCalculateTotalsInformation
{
public:

    ZBProcedureCalculateTotalsInformation(const CString        UnitName,
                                          bool                    Consolidated,
                                          PSS_UserGroupEntity*    pGroup = NULL)
    {
        m_UnitName = UnitName;
        m_Consolidated = Consolidated;
        m_pGroup = pGroup;
    };

    virtual ~ZBProcedureCalculateTotalsInformation()
    {};

    CString              m_UnitName;
    bool                 m_Consolidated;
    PSS_UserGroupEntity* m_pGroup;
};

/////////////////////////////////////////////////////////////////////////////
// ZUProcedureCalculateTotals
//

class AFX_EXT_CLASS ZUProcedureCalculateTotals : public ZUProcessNavigation
{
public:

    //*@param pClass - the custom data class, can be NULL
    ZUProcedureCalculateTotals(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);
    virtual ~ZUProcedureCalculateTotals();

    PSS_AnnualNumberPropertiesBP& GetProcedureCost()
    {
        return m_ProcedureCost;
    };

    PSS_AnnualNumberPropertiesBP& GetProcedureWorkloadForecast()
    {
        return m_ProcedureWorkloadForecast;
    };

    PSS_AnnualNumberPropertiesBP& GetProcedureCostForecast()
    {
        return m_ProcedureCostForecast;
    };

    double GetProcedureWorkloadPerActivity() const
    {
        return m_ProcedureWorkloadPerActivity;
    };

    double GetProcedureCostPerActivity() const
    {
        return m_ProcedureCostPerActivity;
    };

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();
    virtual bool OnDoorSymbol(ZBBPDoorSymbol* pSymbol);
    virtual bool OnPageSymbol(ZBBPPageSymbol* pSymbol);
    virtual bool OnProcedureSymbol(ZBBPProcedureSymbol* pSymbol);
    virtual bool OnProcessSymbol(ZBBPProcessSymbol* pSymbol);
    virtual bool OnStartSymbol(ZBBPStartSymbol* pSymbol);
    virtual bool OnStopSymbol(ZBBPStopSymbol* pSymbol);
    virtual bool OnDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol);

private:
    CString                      m_UnitName;
    bool                         m_Consolidated;
    PSS_UserGroupEntity*         m_pGroup;
    PSS_AnnualNumberPropertiesBP m_ProcedureCost;
    PSS_AnnualNumberPropertiesBP m_ProcedureWorkloadForecast;
    PSS_AnnualNumberPropertiesBP m_ProcedureCostForecast;
    double                       m_ProcedureWorkloadPerActivity;
    double                       m_ProcedureCostPerActivity;
};

#endif
