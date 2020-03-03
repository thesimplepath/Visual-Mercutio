/****************************************************************************
 * ==> PSS_UserGroupCalculateTotals ----------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to calculate the user group totals    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserGroupCalculateTotalsH
#define PSS_UserGroupCalculateTotalsH

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
#include "PSS_ProcessNavigation.h"
#include "PSS_AnnualNumberPropertiesBP.h"

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

class AFX_EXT_CLASS ZBUserGroupCalculateTotalsInformation
{
public:

    ZBUserGroupCalculateTotalsInformation(bool Consolidated, PSS_UserGroupEntity* pGroup = NULL)
    {
        m_Consolidated = Consolidated;
        m_pGroup = pGroup;
    };

    virtual ~ZBUserGroupCalculateTotalsInformation()
    {};

public:

    bool                 m_Consolidated;
    PSS_UserGroupEntity* m_pGroup;
};

/////////////////////////////////////////////////////////////////////////////
// ZBUserGroupCalculateTotalsInformation

class _ZBUserGroupTotal
{
public:
    _ZBUserGroupTotal(const CString GroupName = _T(""))
        : m_GroupName(GroupName)
    {
        m_ProcedureCost = 0;
        m_ProcedureWorkloadForecast = 0;
        m_ProcedureCostForecast = 0;
        m_ProcedureWorkloadPerActivity = 0;
        m_ProcedureCostPerActivity = 0;
    };

    virtual ~_ZBUserGroupTotal()
    {};

public:

    CString                       m_GroupName;
    PSS_AnnualNumberPropertiesBP  m_ProcedureCost;
    PSS_AnnualNumberPropertiesBP  m_ProcedureWorkloadForecast;
    PSS_AnnualNumberPropertiesBP  m_ProcedureCostForecast;
    double                        m_ProcedureWorkloadPerActivity;
    double                        m_ProcedureCostPerActivity;
};

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBUserGroupTotalSet | An array of _ZBUserGroupTotal pointers.
//@iex typedef CCArray_T<_ZBUserGroupTotal*,_ZBUserGroupTotal*> ZBUserGroupTotalSet;
typedef CCArray_T<_ZBUserGroupTotal*, _ZBUserGroupTotal*> ZBUserGroupTotalSet;

//@type ZBUserGroupTotalIterator | An iterator for ZBUserGroupTotalSet collections.
//@iex typedef Iterator_T<_ZBUserGroupTotal*> ZBUserEntityIterator;
typedef Iterator_T<_ZBUserGroupTotal*> ZBUserGroupTotalIterator;

/**
* Navigator to calculate the user group totals
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZUUserGroupCalculateTotals : public PSS_ProcessNavigation
{
public:
    //*@param pClass - the custom data class, can be NULL
    ZUUserGroupCalculateTotals(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);
    virtual ~ZUUserGroupCalculateTotals();

    PSS_AnnualNumberPropertiesBP* GetProcedureCost(const CString GroupName);
    PSS_AnnualNumberPropertiesBP* GetProcedureWorkloadForecast(const CString GroupName);
    PSS_AnnualNumberPropertiesBP* GetProcedureCostForecast(const CString GroupName);
    double GetProcedureWorkloadPerActivity(const CString GroupName) const;
    double GetProcedureCostPerActivity(const CString GroupName) const;

    // Call-back methods
    virtual bool OnStart();
    virtual bool OnFinish();
    virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);


private:

    void AddProcedureToTotal(PSS_ProcedureSymbolBP* pSymbol, _ZBUserGroupTotal& Total);
    void CreateInitialGroupSet();
    void EmptySet();
    _ZBUserGroupTotal* FindTotal(const CString GroupName);

private:

    CString              m_UnitName;
    bool                 m_Consolidated;
    PSS_UserGroupEntity* m_pGroup;
    ZBUserGroupTotalSet  m_TotalSet;
};

#endif
