/****************************************************************************
 * ==> PSS_DeliveriesPropertiesBP ------------------------------------------*
 ****************************************************************************
 * Description : Provides the deliveries properties for banking process     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DeliveriesPropertiesBPH
#define PSS_DeliveriesPropertiesBPH

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
#ifndef PSS_DeliveriesPropertiesBP
    #define PSS_DeliveriesPropertiesBP ZBBPDeliveriesProperties
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
#define M_Delivery_Name_ID         1
#define M_Delivery_Deliverables_ID 2
#define M_Delivery_Quantity_ID     3
#define M_Delivery_Percentage_ID   4
#define M_Delivery_Main_ID         5
//---------------------------------------------------------------------------

/**
* Deliveries properties for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DeliveriesPropertiesBP : public CObject
{
    DECLARE_SERIAL(PSS_DeliveriesPropertiesBP)

    public:
        /**
        * Change type
        *@note These items may be combined
        */
        enum class IEChangeType
        {
            IE_CT_Change_Delivery_Name         = 0x0001,
            IE_CT_Change_Delivery_Deliverables = 0x0002,
            IE_CT_Change_Delivery_Quantity     = 0x0004,
            IE_CT_Change_Delivery_Percentage   = 0x0008,
            IE_CT_Change_Delivery_Main         = 0x0010,
            IE_CT_All                          = OD_CHANGE_ALL
        };

        PSS_DeliveriesPropertiesBP();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DeliveriesPropertiesBP(const PSS_DeliveriesPropertiesBP& other);

        virtual ~PSS_DeliveriesPropertiesBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DeliveriesPropertiesBP& operator = (const PSS_DeliveriesPropertiesBP& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_DeliveriesPropertiesBP& other) const;

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual inline PSS_DeliveriesPropertiesBP* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(PSS_DeliveriesPropertiesBP* pProp, DWORD changeFlags = (DWORD)IEChangeType::IE_CT_All);

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(PSS_DeliveriesPropertiesBP* pProp);

        /**
        * Gets the delivery name
        *@return the delivery name
        */
        virtual inline CString GetDeliveryName() const;

        /**
        * Sets the delivery name
        *@param pValue - the delivery name
        */
        virtual void SetDeliveryName(LPCTSTR pValue);

        /**
        * Gets the delivery deliverables
        *@return the delivery deliverables
        */
        virtual inline CString GetDeliveryDeliverables() const;

        /**
        * Sets the delivery deliverables
        *@param pValue - the delivery deliverables
        */
        virtual void SetDeliveryDeliverables(LPCTSTR pValue);

        /**
        * Checks if the deliverable contains delivery
        *@return true if the deliverable contains delivery, otherwise false
        */
        virtual bool IsDeliverableInDelivery(LPCTSTR pValue);

        /**
        * Gets the delivery quantity
        *@return the delivery quantity
        */
        virtual inline float GetDeliveryQuantity() const;

        /**
        * Sets the delivery quantity
        *@param value - the delivery quantity
        */
        virtual inline void SetDeliveryQuantity(const float value);

        /**
        * Gets the delivery percentage
        *@return the delivery percentage
        */
        virtual inline float GetDeliveryPercentage() const;

        /**
        * Sets the delivery percentage
        *@param value - the delivery percentage
        */
        virtual inline void SetDeliveryPercentage(const float value);

        /**
        * Gets the maindelivery
        *@return the main delivery
        */
        virtual inline CString GetDeliveryMain() const;

        /**
        * Sets the main delivery
        *@param pValue - the main delivery
        */
        virtual void SetDeliveryMain(LPCTSTR pValue);

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
        virtual BOOL GetValue(const int propId, CString& value) const;

        /**
        * Sets the property value
        *@param propId - the property identifier
        *@param value/pValue - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetValue(const int propId, const int   value);
        virtual BOOL SetValue(const int propId, const UINT  value);
        virtual BOOL SetValue(const int propId, const DWORD value);
        virtual BOOL SetValue(const int propId, const float value);
        virtual BOOL SetValue(const int propId, LPCTSTR     pValue);

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
        CString m_DeliveryName;
        CString m_DeliveryDeliverables;
        CString m_DeliveryMain;
        float   m_DeliveryQuantity;
        float   m_DeliveryPercentage;

    private:
        /**
        * Sets the delivery name (advanced)
        *@param value - the delivery name
        */
        void SetDeliveryNameEx(const CString value);

        /**
        * Sets the delivery deliverables (advanced)
        *@param value - the delivery deliverables
        */
        void SetDeliveryDeliverablesEx(const CString value);

        /**
        * Sets the main delivery (advanced)
        *@param value - the main delivery
        */
        void SetDeliveryMainEx(const CString value);
};

//---------------------------------------------------------------------------
// PSS_DeliveriesPropertiesBP
//---------------------------------------------------------------------------
PSS_DeliveriesPropertiesBP* PSS_DeliveriesPropertiesBP::Dup() const
{
    return new PSS_DeliveriesPropertiesBP(*this);
}
//---------------------------------------------------------------------------
CString PSS_DeliveriesPropertiesBP::GetDeliveryName() const
{
    return m_DeliveryName;
}
//---------------------------------------------------------------------------
CString PSS_DeliveriesPropertiesBP::GetDeliveryDeliverables() const
{
    return m_DeliveryDeliverables;
}
//---------------------------------------------------------------------------
float PSS_DeliveriesPropertiesBP::GetDeliveryQuantity() const
{
    return m_DeliveryQuantity;
}
//---------------------------------------------------------------------------
void PSS_DeliveriesPropertiesBP::SetDeliveryQuantity(const float value)
{
    m_DeliveryQuantity = value;
}
//---------------------------------------------------------------------------
float PSS_DeliveriesPropertiesBP::GetDeliveryPercentage() const
{
    return m_DeliveryPercentage;
}
//---------------------------------------------------------------------------
void PSS_DeliveriesPropertiesBP::SetDeliveryPercentage(const float value)
{
    m_DeliveryPercentage = value;
}
//---------------------------------------------------------------------------
CString PSS_DeliveriesPropertiesBP::GetDeliveryMain() const
{
    return m_DeliveryMain;
}
//---------------------------------------------------------------------------

#endif
