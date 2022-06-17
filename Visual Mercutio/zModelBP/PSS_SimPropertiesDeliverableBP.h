/****************************************************************************
 * ==> PSS_SimPropertiesDeliverableBP --------------------------------------*
 ****************************************************************************
 * Description : Provides the simulation properties for deliverable         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SimPropertiesDeliverableBPH
#define PSS_SimPropertiesDeliverableBPH

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
#ifndef PSS_SimPropertiesDeliverableBP
    #define PSS_SimPropertiesDeliverableBP ZBBPSimPropertiesDeliverable
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
#define M_Sim_Deliv_Cost_ID              1
#define M_Sim_Deliv_Workload_Forecast_ID 2
//---------------------------------------------------------------------------

/**
* Simulation properties for deliverable
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SimPropertiesDeliverableBP : public CObject
{
    DECLARE_SERIAL(PSS_SimPropertiesDeliverableBP)

    public:
        /**
        * Change type
        *@note These items may be combined
        */
        enum class IEChangeType
        {
            IE_CT_Change_Sim_Deliv_Cost              = 0x0001,
            IE_CT_Change_Sim_Deliv_Workload_Forecast = 0x0002,
            IE_CT_All                                = OD_CHANGE_ALL
        };

        PSS_SimPropertiesDeliverableBP();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SimPropertiesDeliverableBP(const PSS_SimPropertiesDeliverableBP& other);

        virtual ~PSS_SimPropertiesDeliverableBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_SimPropertiesDeliverableBP& operator = (const PSS_SimPropertiesDeliverableBP& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_SimPropertiesDeliverableBP& other) const;

        /**
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual inline PSS_SimPropertiesDeliverableBP* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(PSS_SimPropertiesDeliverableBP* pProperty, DWORD changeFlags = (DWORD)IEChangeType::IE_CT_All);

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(PSS_SimPropertiesDeliverableBP* pProp);

        /**
        * Gets the deliverable cost
        *@return the deliverable cost
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetCost();

        /**
        * Sets the deliverable cost
        *@param value - the deliverable cost
        */
        virtual inline void SetCost(const double value);

        /**
        * Gets the deliverable workload forecast
        *@return the deliverable workload forecast
        */
        virtual inline PSS_AnnualNumberPropertiesBP& GetWorkloadForecast();

        /**
        * Sets the deliverable workload forecast
        *@param value - the deliverable workload forecast
        */
        virtual inline void SetWorkloadForecast(const double value);

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
        PSS_AnnualNumberPropertiesBP m_Cost;
        PSS_AnnualNumberPropertiesBP m_WorkloadForecast;
};

//---------------------------------------------------------------------------
// PSS_SimPropertiesDeliverableBP
//---------------------------------------------------------------------------
PSS_SimPropertiesDeliverableBP* PSS_SimPropertiesDeliverableBP::Dup() const
{
    return new PSS_SimPropertiesDeliverableBP(*this);
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_SimPropertiesDeliverableBP::GetCost()
{
    return m_Cost;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesDeliverableBP::SetCost(const double value)
{
    m_Cost = value;
}
//---------------------------------------------------------------------------
PSS_AnnualNumberPropertiesBP& PSS_SimPropertiesDeliverableBP::GetWorkloadForecast()
{
    return m_WorkloadForecast;
}
//---------------------------------------------------------------------------
void PSS_SimPropertiesDeliverableBP::SetWorkloadForecast(const double value)
{
    m_WorkloadForecast = value;
}
//---------------------------------------------------------------------------

#endif