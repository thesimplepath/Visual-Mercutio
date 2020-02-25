/****************************************************************************
 * ==> PSS_CostPropertiesDeliverableBP_Beta1 -------------------------------*
 ****************************************************************************
 * Description : Provides the cost properties for deliverables (beta 1)     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CostPropertiesDeliverableBP_Beta1H
#define PSS_CostPropertiesDeliverableBP_Beta1H

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
#ifndef PSS_CostPropertiesDeliverableBP_Beta1
    #define PSS_CostPropertiesDeliverableBP_Beta1 ZBBPCostPropertiesDeliverable
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
#define M_Cost_Deliv_Processing_Time_Beta1_ID      1
#define M_Cost_Deliv_In_Workload_Percent_Beta1_ID  2
#define M_Cost_Deliv_Out_Workload_Percent_Beta1_ID 3
#define M_Cost_Deliv_Unitary_Cost_Beta1_ID         4
//---------------------------------------------------------------------------

/**
* Cost properties for deliverables (beta 1)
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CostPropertiesDeliverableBP_Beta1 : public CODIntProperty,
                                                            public sfl::CPropertyContainer< IODPropertyContainer,
                                                                                            CODPropertyAccessor<PSS_CostPropertiesDeliverableBP_Beta1> >
{
    DECLARE_SERIAL(PSS_CostPropertiesDeliverableBP_Beta1)

    /// generated guid map
    BEGIN_GUID_MAP(PSS_CostPropertiesDeliverableBP_Beta1)
        GUID_ENTRY(IODPropertyContainer)
        GUID_ENTRY(sfl::IPropertyContainer)
        GUID_CHAIN_ENTRY(CODIntProperty)
    END_GUID_MAP

    public:
        /**
        * Change type
        *@note These items may be combinated
        */
        enum IEChangeType
        {
            IE_CT_Change_Cost_Processing_Time      = 0x0001,
            IE_CT_Change_Cost_In_Workload_Percent  = 0x0002,
            IE_CT_Change_Cost_Out_Workload_Percent = 0x0004,
            IE_CT_Change_Cost_Unitary_Cost         = 0x0008,
            IE_CT_All                              = OD_CHANGE_ALL
        };

        /**
        * Constructor
        *@param propID - property identifier
        */
        PSS_CostPropertiesDeliverableBP_Beta1(int propID = ZS_BP_PROP_DELIVERABLE_COST);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_CostPropertiesDeliverableBP_Beta1(const PSS_CostPropertiesDeliverableBP_Beta1& other);

        virtual ~PSS_CostPropertiesDeliverableBP_Beta1();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_CostPropertiesDeliverableBP_Beta1& operator = (const PSS_CostPropertiesDeliverableBP_Beta1& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_CostPropertiesDeliverableBP_Beta1& other) const;

        /**
        * Adds a reference to this object
        *@return the updated reference count
        */
        virtual inline ULONG STDMETHODCALLTYPE AddRef();

        /**
        * Releases a reference from this object
        *@return the updated reference count
        */
        virtual inline ULONG STDMETHODCALLTYPE Release();

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual inline CODProperty* Dup();

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(CODProperty* pProp, DWORD changeFlags = IE_CT_All);

        /**
        * Checks if the identifier is in the property identifier range
        *@param id - the identifier to check
        *@return TRUE if the identifier is in the range, otherwise FALSE
        */
        virtual BOOL CompareId(const int id) const;

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(CODProperty* pProp);

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
        * Gets the input workload percent
        *@return the input workload percent
        */
        virtual inline float GetInWorkloadPercent() const;

        /**
        * Sets the input workload percent
        *@param value - the input workload percent
        */
        virtual inline void SetInWorkloadPercent(const float value);

        /**
        * Gets the output workload percent
        *@return the output workload percent
        */
        virtual inline float GetOutWorkloadPercent() const;

        /**
        * Sets the output workload percent
        *@param value - the output workload percent
        */
        virtual inline void SetOutWorkloadPercent(const float value);

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
        float  m_InWorkloadPercent;
        float  m_OutWorkloadPercent;
        float  m_UnitaryCost;

    private:
        /**
        * Registers the basic property meta-data
        *@return true on success, otherwise false
        */
        bool RegisterProperties();
};

//---------------------------------------------------------------------------
// PSS_CostPropertiesDeliverableBP_Beta1
//---------------------------------------------------------------------------
ULONG PSS_CostPropertiesDeliverableBP_Beta1::AddRef()
{
    return CODIntProperty::AddRef();
}
//---------------------------------------------------------------------------
ULONG PSS_CostPropertiesDeliverableBP_Beta1::Release()
{
    return CODIntProperty::Release();
}
//---------------------------------------------------------------------------
CODProperty* PSS_CostPropertiesDeliverableBP_Beta1::Dup()
{
    return new PSS_CostPropertiesDeliverableBP_Beta1(*this);
}
//---------------------------------------------------------------------------
double PSS_CostPropertiesDeliverableBP_Beta1::GetProcessingTime() const
{
    return m_ProcessingTime;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesDeliverableBP_Beta1::SetProcessingTime(const double value)
{
    m_ProcessingTime = value;
}
//---------------------------------------------------------------------------
float PSS_CostPropertiesDeliverableBP_Beta1::GetInWorkloadPercent() const
{
    return m_InWorkloadPercent;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesDeliverableBP_Beta1::SetInWorkloadPercent(const float value)
{
    m_InWorkloadPercent = value;
}
//---------------------------------------------------------------------------
float PSS_CostPropertiesDeliverableBP_Beta1::GetOutWorkloadPercent() const
{
    return m_OutWorkloadPercent;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesDeliverableBP_Beta1::SetOutWorkloadPercent(const float value)
{
    m_OutWorkloadPercent = value;
}
//---------------------------------------------------------------------------
float PSS_CostPropertiesDeliverableBP_Beta1::GetUnitaryCost() const
{
    return m_UnitaryCost;
}
//---------------------------------------------------------------------------
void PSS_CostPropertiesDeliverableBP_Beta1::SetUnitaryCost(const float value)
{
    m_UnitaryCost = value;
}
//---------------------------------------------------------------------------

#endif
