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

// scope symbols in stingray foundation library
using namespace sfl;

/**
* Navigator to calculate the user group totals
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserGroupCalculateTotals : public PSS_ProcessNavigation
{
    public:
        /**
        * User group calculate totals information
        */
        class AFX_EXT_CLASS IInfo
        {
            public:
                PSS_UserGroupEntity* m_pGroup;
                bool                 m_Consolidated;

                /**
                * Constructor
                *@param consolidated - if true, the model should be consolidated
                *@param pGroup - the group for which the totals should be calculated
                */
                inline IInfo(bool consolidated, PSS_UserGroupEntity* pGroup = NULL);

                inline ~IInfo();
        };

        /**
        * Constructor
        *@param pModel - the model to navigate
        *@param pClass - the custom data class, can be NULL
        */
        PSS_UserGroupCalculateTotals(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);

        virtual ~PSS_UserGroupCalculateTotals();

        /**
        * Gets the procedure cost
        *@param groupName - the group name for which the procedure cost should be get
        *@return the the procedure cost, NULL if not found or on error
        */
        virtual PSS_AnnualNumberPropertiesBP* GetProcedureCost(const CString& groupName);

        /**
        * Gets the procedure workload forecast
        *@param groupName - the group name for which the procedure workload forecast should be get
        *@return the the procedure workload forecast, NULL if not found or on error
        */
        virtual PSS_AnnualNumberPropertiesBP* GetProcedureWorkloadForecast(const CString& groupName);

        /**
        * Gets the procedure cost forecast
        *@param groupName - the group name for which the procedure cost forecast should be get
        *@return the the procedure cost forecast, NULL if not found or on error
        */
        virtual PSS_AnnualNumberPropertiesBP* GetProcedureCostForecast(const CString& groupName);

        /**
        * Gets the procedure workload per activity
        *@param groupName - the group name for which the procedure workload per activity should be get
        *@return the the procedure workload per activity
        */
        virtual double GetProcedureWorkloadPerActivity(const CString& groupName) const;

        /**
        * Gets the procedure cost per activity
        *@param groupName - the group name for which the procedure cost per activity should be get
        *@return the the procedure cost per activity
        */
        virtual double GetProcedureCostPerActivity(const CString& groupName) const;

        /**
        * Called when the navigation starts
        *@return true on success, otherwise false
        */
        virtual bool OnStart();

        /**
        * Called when the navigation ends
        *@return true on success, otherwise false
        */
        virtual bool OnFinish();

        /**
        * Called when a procedure symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);

    private:
        /**
        * User group total
        */
        class IUserGroupTotal
        {
            public:
                PSS_AnnualNumberPropertiesBP m_ProcedureCost;
                PSS_AnnualNumberPropertiesBP m_ProcedureWorkloadForecast;
                PSS_AnnualNumberPropertiesBP m_ProcedureCostForecast;
                CString                      m_GroupName;
                double                       m_ProcedureWorkloadPerActivity;
                double                       m_ProcedureCostPerActivity;

                /**
                * Constructor
                *@param groupName - the group name
                */
                inline IUserGroupTotal(const CString& groupName = _T(""));

                inline ~IUserGroupTotal();
        };

        typedef CCArray_T <IUserGroupTotal*, IUserGroupTotal*> IUserGroupTotalSet;
        typedef Iterator_T<IUserGroupTotal*>                   IUserGroupTotalIterator;

        PSS_UserGroupEntity* m_pGroup;
        IUserGroupTotalSet   m_TotalSet;
        CString              m_UnitName;
        bool                 m_Consolidated;

        /**
        * Adds the procedure to the total
        *@param pSymbol - the procedure to add
        *@param[in, out] total - the total
        */
        void AddProcedureToTotal(PSS_ProcedureSymbolBP* pSymbol, IUserGroupTotal& total);

        /**
        * Creates the initial group set
        */
        void CreateInitialGroupSet();

        /**
        * Empties the group set
        */
        void EmptySet();

        /**
        * Finds the total
        *@param groupName - the group name for which the total should be found
        *@return the total, NULL if not found or on error
        */
        IUserGroupTotal* FindTotal(const CString& groupName);
};

//---------------------------------------------------------------------------
// PSS_UserGroupCalculateTotals::IInfo
//---------------------------------------------------------------------------
PSS_UserGroupCalculateTotals::IInfo::IInfo(bool consolidated, PSS_UserGroupEntity* pGroup) :
    m_pGroup(pGroup),
    m_Consolidated(consolidated)
{}
//---------------------------------------------------------------------------
PSS_UserGroupCalculateTotals::IInfo::~IInfo()
{}
//---------------------------------------------------------------------------
// PSS_UserGroupCalculateTotals::IUserGroupTotal
//---------------------------------------------------------------------------
PSS_UserGroupCalculateTotals::IUserGroupTotal::IUserGroupTotal(const CString& groupName) :
    m_ProcedureCost(0.0),
    m_ProcedureWorkloadForecast(0.0),
    m_ProcedureCostForecast(0.0),
    m_GroupName(groupName),
    m_ProcedureWorkloadPerActivity(0.0),
    m_ProcedureCostPerActivity(0.0)
{}
//---------------------------------------------------------------------------
PSS_UserGroupCalculateTotals::IUserGroupTotal::~IUserGroupTotal()
{}
//---------------------------------------------------------------------------

#endif
