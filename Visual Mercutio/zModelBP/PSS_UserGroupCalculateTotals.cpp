/****************************************************************************
 * ==> PSS_UserGroupCalculateTotals ----------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to calculate the user group totals    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UserGroupCalculateTotals.h"

// processsoft
#include "zModel\PSS_UserGroupEntity.h"
#include "PSS_ProcedureSymbolBP.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_UserGroupCalculateTotals
//---------------------------------------------------------------------------
PSS_UserGroupCalculateTotals::PSS_UserGroupCalculateTotals(PSS_ProcessGraphModelMdl* pModel, void* pClass) :
    PSS_ProcessNavigation(pModel, pClass),
    m_pGroup(NULL),
    m_Consolidated(false)
{}
//---------------------------------------------------------------------------
PSS_UserGroupCalculateTotals::~PSS_UserGroupCalculateTotals()
{
    EmptySet();
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP* PSS_UserGroupCalculateTotals::GetProcedureCost(const CString& groupName)
{
    IUserGroupTotalIterator it(&m_TotalSet);

    // iterate through the groups
    for (IUserGroupTotal* pTotal = it.GetFirst(); pTotal; pTotal = it.GetNext())
        // if the group was found, return the cost
        if (pTotal->m_GroupName == groupName)
            return &(pTotal->m_ProcedureCost);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP* PSS_UserGroupCalculateTotals::GetProcedureWorkloadForecast(const CString& groupName)
{
    IUserGroupTotalIterator it(&m_TotalSet);

    // iterate through the groups
    for (IUserGroupTotal* pTotal = it.GetFirst(); pTotal; pTotal = it.GetNext())
        // if the group was found, return the workload forecast
        if (pTotal->m_GroupName == groupName)
            return &(pTotal->m_ProcedureWorkloadForecast);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP* PSS_UserGroupCalculateTotals::GetProcedureCostForecast(const CString& groupName)
{
    IUserGroupTotalIterator it(&m_TotalSet);

    // iterate through the groups
    for (IUserGroupTotal* pTotal = it.GetFirst(); pTotal; pTotal = it.GetNext())
        // if the group was found, return the cost forecast
        if (pTotal->m_GroupName == groupName)
            return &(pTotal->m_ProcedureCostForecast);

    return NULL;
}
//---------------------------------------------------------------------------
double PSS_UserGroupCalculateTotals::GetProcedureWorkloadPerActivity(const CString& groupName) const
{
    IUserGroupTotalIterator it(&m_TotalSet);

    // iterate through the groups
    for (IUserGroupTotal* pTotal = it.GetFirst(); pTotal; pTotal = it.GetNext())
        // if the group was found, return the workload per activity
        if (pTotal->m_GroupName == groupName)
            return pTotal->m_ProcedureWorkloadPerActivity;

    return 0;
}
//---------------------------------------------------------------------------
double PSS_UserGroupCalculateTotals::GetProcedureCostPerActivity(const CString& groupName) const
{
    // Sets the iterator
    IUserGroupTotalIterator it(&m_TotalSet);

    // iterate through the groups
    for (IUserGroupTotal* pTotal = it.GetFirst(); pTotal; pTotal = it.GetNext())
        // if the group was found, return the cost per activity
        if (pTotal->m_GroupName == groupName)
            return pTotal->m_ProcedureCostPerActivity;

    return 0;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupCalculateTotals::OnStart()
{
    IInfo* pInfo = static_cast<IInfo*>(m_pClass);

    if (!pInfo)
        return false;

    // assign the attributes
    m_Consolidated = pInfo->m_Consolidated;
    m_pGroup       = pInfo->m_pGroup;

    if (!m_pGroup)
        return false;

    // initialize the group unit set
    CreateInitialGroupSet();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupCalculateTotals::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_UserGroupCalculateTotals::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    // calculate totals only for local symbols
    if (!pSymbol->IsLocal())
        return true;

    // if the symbol unit name is not empty, find the elements matching with it
    if (!pSymbol->GetUnitName().IsEmpty())
    {
        IUserGroupTotal* pTotal = FindTotal(pSymbol->GetUnitName());

        if (pTotal)
        {
            AddProcedureToTotal(pSymbol, *pTotal);

            // if a consolidation is required, totalize all children together
            if (m_Consolidated)
            {
                // add to the root unit group
                IUserGroupTotal* pRootTotal = FindTotal(m_pGroup->GetEntityName());

                if (pRootTotal)
                    AddProcedureToTotal(pSymbol, *pRootTotal);
                else
                    THROW("Cannot find the root group");

                // Sets the iterator
                IUserGroupTotalIterator it(&m_TotalSet);

                for (IUserGroupTotal* pElement = it.GetFirst(); pElement; pElement = it.GetNext())
                    // do not consolidate for the same group
                    if (pElement != pTotal)
                    {
                        // get the group pointed by the element unit
                        PSS_UserGroupEntity* pSymbolGroup = m_pGroup->FindFirstGroup(pElement->m_GroupName, true);

                        // if found and if the unit name linked with the symbol belongs to the group,
                        // add the procedure total
                        if (pSymbolGroup && pSymbolGroup->GroupExist(pSymbol->GetUnitName(), true))
                            AddProcedureToTotal(pSymbol, *pElement);
                    }
            }
        }
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_UserGroupCalculateTotals::AddProcedureToTotal(PSS_ProcedureSymbolBP* pSymbol, IUserGroupTotal& total)
{
    PSS_Assert(pSymbol);

    if (double(pSymbol->GetProcedureCost() > 0))
        total.m_ProcedureCost += pSymbol->GetProcedureCost();

    if (double(pSymbol->GetProcedureWorkloadForecast() > 0))
        total.m_ProcedureWorkloadForecast += pSymbol->GetProcedureWorkloadForecast();

    if (double(pSymbol->GetProcedureCostForecast() > 0))
        total.m_ProcedureCostForecast += pSymbol->GetProcedureCostForecast();

    if (double(pSymbol->GetProcedureWorkloadPerActivity() > 0))
        total.m_ProcedureWorkloadPerActivity += pSymbol->GetProcedureWorkloadPerActivity();

    if (double(pSymbol->GetProcedureCostPerActivity() > 0))
        total.m_ProcedureCostPerActivity += pSymbol->GetProcedureCostPerActivity();
}
//---------------------------------------------------------------------------
void PSS_UserGroupCalculateTotals::CreateInitialGroupSet()
{
    EmptySet();

    CStringArray GroupNameArray;

    // add the root name to the array
    GroupNameArray.Add(m_pGroup->GetEntityName());

    const std::size_t count = m_pGroup->FillGroupNameArray(GroupNameArray);

    for (std::size_t i = 0; i < count; ++i)
    {
        // add a new element to the table
        std::unique_ptr<IUserGroupTotal> pElement(new IUserGroupTotal(GroupNameArray.GetAt(i)));
        m_TotalSet.Add(pElement.get());
        pElement.release();
    }
}
//---------------------------------------------------------------------------
void PSS_UserGroupCalculateTotals::EmptySet()
{
    IUserGroupTotalIterator it(&m_TotalSet);

    for (IUserGroupTotal* pTotal = it.GetFirst(); pTotal; pTotal = it.GetNext())
        delete pTotal;

    m_TotalSet.RemoveAll();
}
//---------------------------------------------------------------------------
PSS_UserGroupCalculateTotals::IUserGroupTotal* PSS_UserGroupCalculateTotals::FindTotal(const CString& groupName)
{
    IUserGroupTotalIterator it(&m_TotalSet);

    // iterate through the groups
    for (IUserGroupTotal* pTotal = it.GetFirst(); pTotal; pTotal = it.GetNext())
        // if the group was found, return the cost
        if (pTotal->m_GroupName == groupName)
            return pTotal;

    // if not found, add a new element to the table
    std::unique_ptr<IUserGroupTotal> pElement(new IUserGroupTotal(groupName));
    m_TotalSet.Add(pElement.get());

    return pElement.release();
}
//---------------------------------------------------------------------------
