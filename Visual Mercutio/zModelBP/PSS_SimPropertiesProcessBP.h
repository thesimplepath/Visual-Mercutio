/****************************************************************************
 * ==> PSS_SimPropertiesProcessBP ------------------------------------------*
 ****************************************************************************
 * Description : Provides the simulation properties for process             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SimPropertiesProcessBPH
#define PSS_SimPropertiesProcessBPH

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
#ifndef PSS_SimPropertiesProcessBP
    #define PSS_SimPropertiesProcessBP ZBBPSimPropertiesProcess
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
#define M_Sim_Process_Workload_Forecast_ID      1
#define M_Sim_Process_Cost_Forecast_ID          2
#define M_Sim_Process_Cost_HMO_ID               3
#define M_Sim_Process_Sum_Deliveries_ID         4
#define M_Sim_Process_Workload_By_Deliveries_ID 5
#define M_Sim_Process_Cost_By_Deliveries_ID     6
//---------------------------------------------------------------------------

/**
* Simulation properties for process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SimPropertiesProcessBP : public CObject
{
    DECLARE_SERIAL(PSS_SimPropertiesProcessBP)

    public:
        /**
        * Change type
        *@note These items may be combined
        */
        enum class IEChangeType
        {
            IE_CT_Change_Sim_Process_Workload_Forecast = 0x0001,
            IE_CT_Change_Sim_Process_Cost_Forecast     = 0x0002,
            IE_CT_Change_Sim_Process_Cost_HMO          = 0x0004,
            IE_CT_All                                  = OD_CHANGE_ALL
        };

        PSS_SimPropertiesProcessBP();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SimPropertiesProcessBP(const PSS_SimPropertiesProcessBP& other);

        virtual ~PSS_SimPropertiesProcessBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_SimPropertiesProcessBP& operator = (const PSS_SimPropertiesProcessBP& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_SimPropertiesProcessBP& other) const;

        /**
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual inline PSS_SimPropertiesProcessBP* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(PSS_SimPropertiesProcessBP* pProp, DWORD changeFlags = (DWORD)IEChangeType::IE_CT_All);

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(PSS_SimPropertiesProcessBP* pProp);

        /**
        * Gets the process workload forecast
        *@return the process workload forecast
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcessWorkloadForecast();

        /**
        * Sets the process workload forecast
        *@param value - the process workload forecast
        */
        virtual inline void SetProcessWorkloadForecast(const double value);

        /**
        * Gets the process cost forecast
        *@return the process cost forecast
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcessCostForecast();

        /**
        * Sets the process cost forecast
        *@param value - the process cost forecast
        */
        virtual inline void SetProcessCostForecast(const double value);

        /**
        * Gets the process cost HMO
        *@return the process cost HMO
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetProcessCostHMO();

        /**
        * Sets the process cost HMO
        *@param value - the process cost HMO
        */
        virtual inline void SetProcessCostHMO(const double value);

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
        PSS_AnnualNumberPropertiesBP m_ProcessWorkloadForecast;
        PSS_AnnualNumberPropertiesBP m_ProcessCostForecast;
        PSS_AnnualNumberPropertiesBP m_ProcessCostHMO;
};

//---------------------------------------------------------------------------
// PSS_SimPropertiesProcessBP
//---------------------------------------------------------------------------
PSS_SimPropertiesProcessBP* PSS_SimPropertiesProcessBP::Dup() const
{
    return new PSS_SimPropertiesProcessBP(*this);
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_SimPropertiesProcessBP::GetProcessWorkloadForecast()
{
    return m_ProcessWorkloadForecast;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcessBP::SetProcessWorkloadForecast(const double value)
{
    m_ProcessWorkloadForecast = value;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_SimPropertiesProcessBP::GetProcessCostForecast()
{
    return m_ProcessCostForecast;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcessBP::SetProcessCostForecast(const double value)
{
    m_ProcessCostForecast = value;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_SimPropertiesProcessBP::GetProcessCostHMO()
{
    return m_ProcessCostHMO;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesProcessBP::SetProcessCostHMO(const double value)
{
    m_ProcessCostHMO = value;
}
//---------------------------------------------------------------------------

#endif
