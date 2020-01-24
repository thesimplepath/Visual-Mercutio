/****************************************************************************
 * ==> PSS_UnitPropertiesBP ------------------------------------------------*
 ****************************************************************************
 * Description : Provides the unit properties                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UnitPropertiesBPH
#define PSS_UnitPropertiesBPH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_UnitPropertiesBP
    #define PSS_UnitPropertiesBP ZBBPUnitProperties
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
#define M_Unit_Name 1
#define M_Unit_Cost 2
#define M_Unit_GUID 3
//---------------------------------------------------------------------------

/**
* Unit properties
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UnitPropertiesBP : public CODIntProperty,
                                           public sfl::CPropertyContainer< IODPropertyContainer,
                                                                           CODPropertyAccessor<PSS_UnitPropertiesBP> >
{
    DECLARE_SERIAL(PSS_UnitPropertiesBP)

    /// generated guid map
    BEGIN_GUID_MAP(PSS_UnitPropertiesBP)
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
        PSS_UnitPropertiesBP(int propID = ZS_BP_PROP_UNIT);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_UnitPropertiesBP(const PSS_UnitPropertiesBP& other);

        virtual ~PSS_UnitPropertiesBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_UnitPropertiesBP& operator = (const PSS_UnitPropertiesBP& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_UnitPropertiesBP& other) const;

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
// PSS_UnitPropertiesBP
//---------------------------------------------------------------------------
ULONG PSS_UnitPropertiesBP::AddRef()
{
    return CODIntProperty::AddRef();
}
//---------------------------------------------------------------------------
ULONG PSS_UnitPropertiesBP::Release()
{
    return CODIntProperty::Release();
}
//---------------------------------------------------------------------------
CODProperty* PSS_UnitPropertiesBP::Dup() const
{
    return new PSS_UnitPropertiesBP(*this);
}
//---------------------------------------------------------------------------
CString PSS_UnitPropertiesBP::GetUnitName() const
{
    return m_UnitName;
}
//---------------------------------------------------------------------------
float PSS_UnitPropertiesBP::GetUnitCost() const
{
    return m_UnitCost;
}
//---------------------------------------------------------------------------
void PSS_UnitPropertiesBP::SetUnitCost(const float Value)
{
    m_UnitCost = Value;
}
//---------------------------------------------------------------------------

#endif
