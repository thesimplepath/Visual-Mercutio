/****************************************************************************
 * ==> PSS_ProcedureCalculateTotals ----------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator to calculates the procedure totals    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcedureCalculateTotalsH
#define PSS_ProcedureCalculateTotalsH

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

/**
* Navigator to calculates the procedure totals
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcedureCalculateTotals : public PSS_ProcessNavigation
{
    public:
        /**
        * Constructor
        *@param pModel - the model
        *@param pClass - the class
        */
        PSS_ProcedureCalculateTotals(PSS_ProcessGraphModelMdl* pModel = NULL, void* pClass = NULL);

        virtual ~PSS_ProcedureCalculateTotals();

        /**
        * Gets the procedure cost
        *@return the procedure cost
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcedureCost();

        /**
        * Gets the procedure workload forecast
        *@return the procedure workload forecast
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcedureWorkloadForecast();

        /**
        * Gets the procedure cost forecast
        *@return the procedure cost forecast
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcedureCostForecast();

        /**
        * Gets the procedure workload per activity
        *@return the procedure workload per activity
        */
        virtual inline double GetProcedureWorkloadPerActivity() const;

        /**
        * Gets the procedure cost per activity
        *@return the procedure cost per activity
        */
        virtual inline double GetProcedureCostPerActivity() const;

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
        * Called when a door symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnDoorSymbol(PSS_DoorSymbolBP* pSymbol);

        /**
        * Called when a page symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnPageSymbol(PSS_PageSymbolBP* pSymbol);

        /**
        * Called when a procedure symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol);

        /**
        * Called when a process symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol);

        /**
        * Called when a start symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnStartSymbol(PSS_StartSymbolBP* pSymbol);

        /**
        * Called when a stop symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnStopSymbol(PSS_StopSymbolBP* pSymbol);

        /**
        * Called when a deliverable link symbol is visited
        *@param pSymbol - the visited symbol
        *@return true on success, otherwise false
        */
        virtual bool OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol);

    private:
        /**
        * The procedure calculate totals information
        *@author Dominique Aigroz, Jean-Milost Reymond
        */
        class IInfo
        {
            public:
                PSS_UserGroupEntity* m_pGroup;
                CString              m_UnitName;
                bool                 m_Consolidated;

                /**
                * Constructor
                *@param unitName - the unit name
                *@param consolidated - if true, the model was consolidated
                *@param pGroup - the user group
                */
                IInfo(const CString&       unitName,
                      bool                 consolidated,
                      PSS_UserGroupEntity* pGroup = NULL);

                ~IInfo();
        };

        PSS_UserGroupEntity*         m_pGroup;
        PSS_AnnualNumberPropertiesBP m_ProcedureCost;
        PSS_AnnualNumberPropertiesBP m_ProcedureWorkloadForecast;
        PSS_AnnualNumberPropertiesBP m_ProcedureCostForecast;
        CString                      m_UnitName;
        double                       m_ProcedureWorkloadPerActivity;
        double                       m_ProcedureCostPerActivity;
        bool                         m_Consolidated;
};

//---------------------------------------------------------------------------
// PSS_ProcedureCalculateTotals
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_ProcedureCalculateTotals::GetProcedureCost()
{
    return m_ProcedureCost;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_ProcedureCalculateTotals::GetProcedureWorkloadForecast()
{
    return m_ProcedureWorkloadForecast;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_ProcedureCalculateTotals::GetProcedureCostForecast()
{
    return m_ProcedureCostForecast;
}
//---------------------------------------------------------------------------
double PSS_ProcedureCalculateTotals::GetProcedureWorkloadPerActivity() const
{
    return m_ProcedureWorkloadPerActivity;
}
//---------------------------------------------------------------------------
double PSS_ProcedureCalculateTotals::GetProcedureCostPerActivity() const
{
    return m_ProcedureCostPerActivity;
}
//---------------------------------------------------------------------------

#endif
