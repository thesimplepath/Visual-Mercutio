/****************************************************************************
 * ==> PSS_UnitPropertiesBP_Beta1 ------------------------------------------*
 ****************************************************************************
 * Description : Provides the unit properties (beta 1)                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UnitPropertiesBP_Beta1H
#define PSS_UnitPropertiesBP_Beta1H

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_UnitPropertiesBP_Beta1
    #define PSS_UnitPropertiesBP_Beta1 ZBBPUnitProperties
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
#define M_Unit_Name_Beta1_ID 1
#define M_Unit_Cost_Beta1_ID 2
#define M_Unit_GUID_Beta1_ID 3
//---------------------------------------------------------------------------

/**
* Unit properties (beta 1)
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UnitPropertiesBP_Beta1 : public CODIntProperty,
                                                 public sfl::CPropertyContainer< IODPropertyContainer,
                                                                                 CODPropertyAccessor<PSS_UnitPropertiesBP_Beta1> >
{
    DECLARE_SERIAL(PSS_UnitPropertiesBP_Beta1)

    /// generated guid map
    BEGIN_GUID_MAP(PSS_UnitPropertiesBP_Beta1)
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
            IE_CT_Change_Unit_Name = 0x0001,
            IE_CT_Change_Unit_Cost = 0x0002,
            IE_CT_Change_Unit_GUID = 0x0004,
            IE_CT_All              = OD_CHANGE_ALL
        };

        /**
        * Constructor
        *@param propID - property identifier
        */
        PSS_UnitPropertiesBP_Beta1(int propID = ZS_BP_PROP_UNIT);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UnitPropertiesBP_Beta1(const PSS_UnitPropertiesBP_Beta1& other);

        virtual ~PSS_UnitPropertiesBP_Beta1();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_UnitPropertiesBP_Beta1& operator = (const PSS_UnitPropertiesBP_Beta1& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_UnitPropertiesBP_Beta1& other) const;

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
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual inline CODProperty* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(CODProperty* pProperty, DWORD changeFlags = IE_CT_All);

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
        * Gets the unit name
        *@return the unit name
        */
        virtual inline CString GetUnitName() const;

        /**
        * Sets the unit name
        *@param pValue - the unit name
        */
        virtual void SetUnitName(LPCTSTR pValue);

        /**
        * Gets the unit cost
        *@return the unit cost
        */
        virtual inline float GetUnitCost() const;

        /**
        * Sets the unit cost
        *@param value - the unit cost
        */
        virtual inline void SetUnitCost(const float Value);

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
        CString m_UnitName;
        float   m_UnitCost;

    private:
        /**
        * Sets the unit name (advanced)
        *@param value - the unit name
        */
        void SetUnitNameEx(const CString value);

        /**
        * Registers the fill property meta-data
        *@return true on success, otherwise false
        */
        bool RegisterProperties();
};

//---------------------------------------------------------------------------
// PSS_UnitPropertiesBP_Beta1
//---------------------------------------------------------------------------
ULONG PSS_UnitPropertiesBP_Beta1::AddRef()
{
    return CODIntProperty::AddRef();
}
//---------------------------------------------------------------------------
ULONG PSS_UnitPropertiesBP_Beta1::Release()
{
    return CODIntProperty::Release();
}
//---------------------------------------------------------------------------
CODProperty* PSS_UnitPropertiesBP_Beta1::Dup() const
{
    return new PSS_UnitPropertiesBP_Beta1(*this);
}
//---------------------------------------------------------------------------
CString PSS_UnitPropertiesBP_Beta1::GetUnitName() const
{
    return m_UnitName;
}
//---------------------------------------------------------------------------
float PSS_UnitPropertiesBP_Beta1::GetUnitCost() const
{
    return m_UnitCost;
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP_Beta1::SetUnitCost(const float Value)
{
    m_UnitCost = Value;
}
//---------------------------------------------------------------------------

#endif
