// ZUUserGroupCalculateTotals.cpp: implementation of the ZUUserGroupCalculateTotals class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ZUUserGroupCalculateTotals.h"

#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModel\PSS_UserGroupEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 9 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUUserGroupCalculateTotals::ZUUserGroupCalculateTotals(PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                       void*                    pClass    /*= NULL*/)
    : ZUProcessNavigation(pModel, pClass)
{}

ZUUserGroupCalculateTotals::~ZUUserGroupCalculateTotals()
{
    EmptySet();
}

bool ZUUserGroupCalculateTotals::OnStart()
{
    // Start by casting the unit name string
    ZBUserGroupCalculateTotalsInformation* pInfo = static_cast<ZBUserGroupCalculateTotalsInformation*>(m_pClass);

    if (!pInfo)
    {
        return false;
    }

    // Assigns the attributes
    m_Consolidated = pInfo->m_Consolidated;
    m_pGroup = pInfo->m_pGroup;

    if (!m_pGroup)
    {
        return false;
    }

    // Initialize the set with group unit
    CreateInitialGroupSet();

    return true;
}

bool ZUUserGroupCalculateTotals::OnFinish()
{
    return true;
}

bool ZUUserGroupCalculateTotals::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    // Calculate totals only for local symbols
    if (!pSymbol->IsLocal())
    {
        return true;
    }

    // If the symbol's unit name is not empty
    // then find the right elements corresponding to the same unit
    if (!pSymbol->GetUnitName().IsEmpty())
    {
        _ZBUserGroupTotal* pTotal = FindTotal(pSymbol->GetUnitName());

        if (pTotal)
        {
            AddProcedureToTotal(pSymbol, *pTotal);

            // If consolidation is required,
            // then totalize all childs together
            if (m_Consolidated)
            {
                // Add to the root unit group
                _ZBUserGroupTotal* pRootTotal = FindTotal(m_pGroup->GetEntityName());
                AddProcedureToTotal(pSymbol, *pRootTotal);

                // Sets the iterator
                ZBUserGroupTotalIterator i(&m_TotalSet);

                for (_ZBUserGroupTotal* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext())
                {
                    // Do not consolidate for the same group
                    if (pElement != pTotal)
                    {
                        // Locate the group pointed by the element's unit
                        PSS_UserGroupEntity* pSymbolGroup = m_pGroup->FindFirstGroup(pElement->m_GroupName, true);

                        // If found and if the unit name pointed by the symbol is 
                        // part of the group, then add the procedure total also
                        if (pSymbolGroup && pSymbolGroup->GroupExist(pSymbol->GetUnitName(), true))
                        {
                            AddProcedureToTotal(pSymbol, *pElement);
                        }
                    }
                }
            }
        }
    }

    return true;
}

void ZUUserGroupCalculateTotals::AddProcedureToTotal(PSS_ProcedureSymbolBP* pSymbol, _ZBUserGroupTotal& Total)
{
    ASSERT(pSymbol);

    if ((double)pSymbol->GetProcedureCost() > 0)
    {
        Total.m_ProcedureCost += pSymbol->GetProcedureCost();
    }

    if ((double)pSymbol->GetProcedureWorkloadForecast() > 0)
    {
        Total.m_ProcedureWorkloadForecast += pSymbol->GetProcedureWorkloadForecast();
    }

    if ((double)pSymbol->GetProcedureCostForecast() > 0)
    {
        Total.m_ProcedureCostForecast += pSymbol->GetProcedureCostForecast();
    }

    if ((double)pSymbol->GetProcedureWorkloadPerActivity() > 0)
    {
        Total.m_ProcedureWorkloadPerActivity += pSymbol->GetProcedureWorkloadPerActivity();
    }

    if ((double)pSymbol->GetProcedureCostPerActivity() > 0)
    {
        Total.m_ProcedureCostPerActivity += pSymbol->GetProcedureCostPerActivity();
    }
}

void ZUUserGroupCalculateTotals::CreateInitialGroupSet()
{
    EmptySet();

    CStringArray GroupNameArray;

    // Add the root name to the array
    GroupNameArray.Add(m_pGroup->GetEntityName());

    size_t Count = m_pGroup->FillGroupNameArray(GroupNameArray);

    for (size_t i = 0; i < Count; ++i)
    {
        // add a new element to the table
        _ZBUserGroupTotal* pElement = new _ZBUserGroupTotal(GroupNameArray.GetAt(i));
        m_TotalSet.Add(pElement);
    }
}

void ZUUserGroupCalculateTotals::EmptySet()
{
    // Sets the iterator
    ZBUserGroupTotalIterator i(&m_TotalSet);

    for (_ZBUserGroupTotal* pTotal = i.GetFirst(); pTotal != NULL; pTotal = i.GetNext())
    {
        delete pTotal;
    }

    m_TotalSet.RemoveAll();
}

_ZBUserGroupTotal* ZUUserGroupCalculateTotals::FindTotal(const CString GroupName)
{
    // Sets the iterator
    ZBUserGroupTotalIterator i(&m_TotalSet);

    for (_ZBUserGroupTotal* pTotal = i.GetFirst(); pTotal != NULL; pTotal = i.GetNext())
    {
        // If the same group, return the cost
        if (pTotal->m_GroupName == GroupName)
        {
            return pTotal;
        }
    }

    // If not found, add a new element to the table
    _ZBUserGroupTotal* pElement = new _ZBUserGroupTotal(GroupName);
    m_TotalSet.Add(pElement);

    return pElement;
}

PSS_AnnualNumberPropertiesBP* ZUUserGroupCalculateTotals::GetProcedureCost(const CString GroupName)
{
    // Sets the iterator
    ZBUserGroupTotalIterator i(&m_TotalSet);

    for (_ZBUserGroupTotal* pTotal = i.GetFirst(); pTotal != NULL; pTotal = i.GetNext())
    {
        // If the same group, return the cost
        if (pTotal->m_GroupName == GroupName)
        {
            return &(pTotal->m_ProcedureCost);
        }
    }

    return NULL;
}

PSS_AnnualNumberPropertiesBP* ZUUserGroupCalculateTotals::GetProcedureWorkloadForecast(const CString GroupName)
{
    // Sets the iterator
    ZBUserGroupTotalIterator i(&m_TotalSet);

    for (_ZBUserGroupTotal* pTotal = i.GetFirst(); pTotal != NULL; pTotal = i.GetNext())
    {
        // If the same group, return the cost
        if (pTotal->m_GroupName == GroupName)
        {
            return &(pTotal->m_ProcedureWorkloadForecast);
        }
    }

    return NULL;
}

PSS_AnnualNumberPropertiesBP* ZUUserGroupCalculateTotals::GetProcedureCostForecast(const CString GroupName)
{
    // Sets the iterator
    ZBUserGroupTotalIterator i(&m_TotalSet);

    for (_ZBUserGroupTotal* pTotal = i.GetFirst(); pTotal != NULL; pTotal = i.GetNext())
    {
        // If the same group, return the cost
        if (pTotal->m_GroupName == GroupName)
        {
            return &(pTotal->m_ProcedureCostForecast);
        }
    }

    return NULL;
}

double ZUUserGroupCalculateTotals::GetProcedureWorkloadPerActivity(const CString GroupName) const
{
    // Sets the iterator
    ZBUserGroupTotalIterator i(&m_TotalSet);

    for (_ZBUserGroupTotal* pTotal = i.GetFirst(); pTotal != NULL; pTotal = i.GetNext())
    {
        // If the same group, return the cost
        if (pTotal->m_GroupName == GroupName)
        {
            return pTotal->m_ProcedureWorkloadPerActivity;
        }
    }

    return 0;
}

double ZUUserGroupCalculateTotals::GetProcedureCostPerActivity(const CString GroupName) const
{
    // Sets the iterator
    ZBUserGroupTotalIterator i(&m_TotalSet);

    for (_ZBUserGroupTotal* pTotal = i.GetFirst(); pTotal != NULL; pTotal = i.GetNext())
    {
        // If the same group, return the cost
        if (pTotal->m_GroupName == GroupName)
        {
            return pTotal->m_ProcedureCostPerActivity;
        }
    }

    return 0;
}
