/****************************************************************************
 * ==> PSS_CostPropertiesProcedureBP ---------------------------------------*
 ****************************************************************************
 * Description : Provides the cost properties for procedures                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CostPropertiesProcedureBPH
#define PSS_CostPropertiesProcedureBPH

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
#ifndef PSS_CostPropertiesProcedureBP
    #define PSS_CostPropertiesProcedureBP ZBBPCostPropertiesProcedure2
#endif

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
#define M_Cost_Proc_Multiplier_ID              1
#define M_Cost_Proc_Processing_Time_ID         2
#define M_Cost_Proc_Unitary_Cost_ID            3
#define M_Cost_Proc_Processing_Duration_ID     4
#define M_Cost_Proc_Processing_Duration_Max_ID 5
//---------------------------------------------------------------------------

/**
* Cost properties for procedures
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CostPropertiesProcedureBP : public CObject
{
    DECLARE_SERIAL(PSS_CostPropertiesProcedureBP)

    public:
        /**
        * Change type
        *@note These items may be combined
        */
        enum class IEChangeType
        {
            IE_CT_Change_Cost_Multiplier              = 0x0001,
            IE_CT_Change_Cost_Processing_Time         = 0x0002,
            IE_CT_Change_Cost_Unitary_Cost            = 0x0004,
            IE_CT_Change_Cost_Processing_Duration     = 0x0008,
            IE_CT_Change_Cost_Processing_Duration_Max = 0x0010,
            IE_CT_All                                 = OD_CHANGE_ALL
        };

        PSS_CostPropertiesProcedureBP();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_CostPropertiesProcedureBP(const PSS_CostPropertiesProcedureBP& other);

        virtual ~PSS_CostPropertiesProcedureBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_CostPropertiesProcedureBP& operator = (const PSS_CostPropertiesProcedureBP& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_CostPropertiesProcedureBP& other) const;

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual inline PSS_CostPropertiesProcedureBP* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(PSS_CostPropertiesProcedureBP* pProp, DWORD changeFlags = (DWORD)IEChangeType::IE_CT_All);

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(PSS_CostPropertiesProcedureBP* pProp);

        /**
        * Gets the cost multiplier factor
        *@return the cost multiplier factor
        */
        virtual inline float GetMultiplier() const;

        /**
        * Sets the cost multiplier factor
        *@param value - the cost multiplier factor
        */
        virtual inline void SetMultiplier(const float value);

        /**
        * Gets the processing time
        *@return the processing time
        */
        virtual inline double GetProcessingTime() const;

        /**
        * Sets the processing time
        *@param value - the processing time
        */
        virtual inline void SetProcessingTime(const double value);

        /**
        * Gets the unitary cost
        *@return the unitary cost
        */
        virtual inline float GetUnitaryCost() const;

        /**
        * Sets the unitary cost
        *@param value - the unitary cost
        */
        virtual inline void SetUnitaryCost(const float value);

        /**
        * Gets the processing time
        *@return the processing time
        */
        virtual inline double GetProcessingDuration() const;

        /**
        * Sets the processing time
        *@param value - the processing time
        */
        virtual inline void SetProcessingDuration(const double value);

        /**
        * Gets the processing maximum time
        *@return the processing maximum time
        */
        virtual inline double GetProcessingDurationMax() const;

        /**
        * Sets the processing maximum time
        *@param value - the processing maximum time
        */
        virtual inline void SetProcessingDurationMax(const double value);

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
        double m_ProcessingTime;
        double m_ProcessingDuration;
        double m_ProcessingDurationMax;
        float  m_Multiplier;
        float  m_UnitaryCost;
};

//---------------------------------------------------------------------------
// PSS_CostPropertiesProcedureBP
//---------------------------------------------------------------------------
PSS_CostPropertiesProcedureBP* PSS_CostPropertiesProcedureBP::Dup() const
{
    return new PSS_CostPropertiesProcedureBP(*this);
}
//---------------------------------------------------------------------------
float PSS_CostPropertiesProcedureBP::GetMultiplier() const
{
    return m_Multiplier;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesProcedureBP::SetMultiplier(const float value)
{
    m_Multiplier = value;
}
//---------------------------------------------------------------------------
double PSS_CostPropertiesProcedureBP::GetProcessingTime() const
{
    return m_ProcessingTime;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesProcedureBP::SetProcessingTime(const double value)
{
    m_ProcessingTime = value;
}
//---------------------------------------------------------------------------
float PSS_CostPropertiesProcedureBP::GetUnitaryCost() const
{
    return m_UnitaryCost;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesProcedureBP::SetUnitaryCost(const float value)
{
    m_UnitaryCost = value;
}
//---------------------------------------------------------------------------
double PSS_CostPropertiesProcedureBP::GetProcessingDuration() const
{
    return m_ProcessingDuration;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesProcedureBP::SetProcessingDuration(const double value)
{
    m_ProcessingDuration = value;
}
//---------------------------------------------------------------------------
double PSS_CostPropertiesProcedureBP::GetProcessingDurationMax() const
{
    return m_ProcessingDurationMax;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesProcedureBP::SetProcessingDurationMax(const double value)
{
    m_ProcessingDurationMax = value;
}
//---------------------------------------------------------------------------

#endif
