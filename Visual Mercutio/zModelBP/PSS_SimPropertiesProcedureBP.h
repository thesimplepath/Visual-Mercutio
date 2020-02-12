/****************************************************************************
 * ==> PSS_SimPropertiesProcedureBP ----------------------------------------*
 ****************************************************************************
 * Description : Provides the simulation properties for procedure           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SimPropertiesProcedureBPH
#define PSS_SimPropertiesProcedureBPH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_SimPropertiesProcedureBP
    #define PSS_SimPropertiesProcedureBP ZBBPSimPropertiesProcedure
#endif

// processsoft
#include "PSS_AnnualNumberPropertiesBP.h"

// resources
#include "PSS_PropIDs.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Sim_Procedure_Activation_ID         1
#define M_Sim_Procedure_Cost_ID               2
#define M_Sim_Procedure_Workload_Forecast_ID  3
#define M_Sim_Procedure_Cost_Forecast_ID      4
#define M_Sim_Procedure_Workload_Per_Activ_ID 5
#define M_Sim_Procedure_Cost_Per_Activ_ID     6
//---------------------------------------------------------------------------

/**
* Simulation properties for procedure
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SimPropertiesProcedureBP : public CObject
{
    DECLARE_SERIAL(PSS_SimPropertiesProcedureBP)

    public:
        /**
        * Change type
        *@note These items may be combinated
        */
        enum IEChangeType
        {
            IE_CT_Change_Sim_Procedure_Activation                  = 0x0001,
            IE_CT_Change_Sim_Procedure_Cost                        = 0x0002,
            IE_CT_Change_Sim_Procedure_Workload_Forecast           = 0x0004,
            IE_CT_Change_Sim_Procedure_Cost_Forecast               = 0x0008,
            IE_CT_Change_Sim_Procedure_Workload_Per_Activ_Forecast = 0x0010,
            IE_CT_Change_Sim_Procedure_Cost_Per_Activ_Forecast     = 0x0020,
            IE_CT_All                                              = OD_CHANGE_ALL
        };

        PSS_SimPropertiesProcedureBP();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SimPropertiesProcedureBP(const PSS_SimPropertiesProcedureBP& other);

        virtual ~PSS_SimPropertiesProcedureBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_SimPropertiesProcedureBP& operator = (const PSS_SimPropertiesProcedureBP& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_SimPropertiesProcedureBP& other) const;

        /**
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual inline PSS_SimPropertiesProcedureBP* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(PSS_SimPropertiesProcedureBP* pProp, DWORD changeFlags = IE_CT_All);

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(PSS_SimPropertiesProcedureBP* pProp);

        /**
        * Gets the procedure activation
        *@return the procedure activation
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcedureActivation();

        /**
        * Sets the procedure activation
        *@param value - the procedure activation
        */
        virtual inline void SetProcedureActivation(const double value);

        /**
        * Gets the procedure cost
        *@return the procedure cost
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcedureCost();

        /**
        * Sets the procedure cost
        *@param value - the procedure cost
        */
        virtual inline void SetProcedureCost(const double value);

        /**
        * Gets the procedure workload forecast
        *@return the procedure workload forecast
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcedureWorkloadForecast();

        /**
        * Sets the procedure workload forecast
        *@param value - the procedure workload forecast
        */
        virtual inline void SetProcedureWorkloadForecast(const double value);

        /**
        * Gets the procedure cost forecast
        *@return the procedure cost forecast
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcedureCostForecast();

        /**
        * Sets the procedure cost forecast
        *@param value - the procedure cost forecast
        */
        virtual inline void SetProcedureCostForecast(const double value);

        /**
        * Gets the procedure workload per activity forecast
        *@return the procedure workload per activity forecast
        */
        virtual inline double GetProcedureWorkloadPerActivity() const;

        /**
        * Sets the procedure workload per activity forecast
        *@param value - the procedure workload per activity forecast
        */
        virtual inline void SetProcedureWorkloadPerActivity(const double value);

        /**
        * Gets the procedure cost per activity forecast
        *@return the procedure cost per activity forecast
        */
        virtual inline double GetProcedureCostPerActivity() const;

        /**
        * Sets the procedure cost per activity forecast
        *@param value - the procedure cost per activity forecast
        */
        virtual inline void SetProcedureCostPerActivity(const double value);

        /**
        * Gets the property value
        *@param propId - the property identifier
        *@param[out] value - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GetValue(const int propId, int&     value) const;
        virtual BOOL GetValue(const int propId, UINT&    value) const;
        virtual BOOL GetValue(const int propId, DWORD&   value) const;
        virtual BOOL GetValue(const int propId, float&   value) const;
        virtual BOOL GetValue(const int propId, double&  value) const;
        virtual BOOL GetValue(const int propId, CString& value) const;

        /**
        * Sets the property value
        *@param propId - the property identifier
        *@param value/pValue - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetValue(const int propId, const int    value);
        virtual BOOL SetValue(const int propId, const UINT   value);
        virtual BOOL SetValue(const int propId, const DWORD  value);
        virtual BOOL SetValue(const int propId, const float  value);
        virtual BOOL SetValue(const int propId, const double value);
        virtual BOOL SetValue(const int propId, LPCTSTR      pValue);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        PSS_AnnualNumberPropertiesBP m_ProcedureActivation;
        PSS_AnnualNumberPropertiesBP m_ProcedureCost;
        PSS_AnnualNumberPropertiesBP m_ProcedureWorkloadForecast;
        PSS_AnnualNumberPropertiesBP m_ProcedureCostForecast;
        double                       m_ProcedureWorkloadPerActivity;
        double                       m_ProcedureCostPerActivity;
};

//---------------------------------------------------------------------------
// PSS_SimPropertiesProcedureBP
//---------------------------------------------------------------------------
PSS_SimPropertiesProcedureBP* PSS_SimPropertiesProcedureBP::Dup() const
{
    return new PSS_SimPropertiesProcedureBP(*this);
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_SimPropertiesProcedureBP::GetProcedureActivation()
{
    return m_ProcedureActivation;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcedureBP::SetProcedureActivation(const double value)
{
    m_ProcedureActivation = value;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_SimPropertiesProcedureBP::GetProcedureCost()
{
    return m_ProcedureCost;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcedureBP::SetProcedureCost(const double value)
{
    m_ProcedureCost = value;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_SimPropertiesProcedureBP::GetProcedureWorkloadForecast()
{
    return m_ProcedureWorkloadForecast;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcedureBP::SetProcedureWorkloadForecast(const double value)
{
    m_ProcedureWorkloadForecast = value;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_SimPropertiesProcedureBP::GetProcedureCostForecast()
{
    return m_ProcedureCostForecast;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcedureBP::SetProcedureCostForecast(const double value)
{
    m_ProcedureCostForecast = value;
}
//---------------------------------------------------------------------------
double PSS_SimPropertiesProcedureBP::GetProcedureWorkloadPerActivity() const
{
    return m_ProcedureWorkloadPerActivity;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcedureBP::SetProcedureWorkloadPerActivity(const double value)
{
    m_ProcedureWorkloadPerActivity = value;
}
//---------------------------------------------------------------------------
double PSS_SimPropertiesProcedureBP::GetProcedureCostPerActivity() const
{
    return m_ProcedureCostPerActivity;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcedureBP::SetProcedureCostPerActivity(const double value)
{
    m_ProcedureCostPerActivity = value;
}
//---------------------------------------------------------------------------

#endif
