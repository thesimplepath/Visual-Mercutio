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

#define Z_CHANGE_UNIT_NAME 0x0001
#define Z_CHANGE_UNIT_COST 0x0002
#define Z_CHANGE_UNIT_GUID 0x0004

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define Z_UNIT_NAME 1
#define Z_UNIT_COST 2
#define Z_UNIT_GUID 3
//---------------------------------------------------------------------------

/**
* Unit properties
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZBBPUnitProperties : public CODIntProperty,
                public sfl::CPropertyContainer<IODPropertyContainer, CODPropertyAccessor<ZBBPUnitProperties> >
{
    DECLARE_SERIAL(ZBBPUnitProperties)

// Construction/Destruction
public:
    //@cmember
    /* Constructor. */
    ZBBPUnitProperties(int nId = ZS_BP_PROP_UNIT);
    //@cmember
    /* Copy constructor. */
    ZBBPUnitProperties(const ZBBPUnitProperties& propProcess);
    //@cmember
    /* Destructor. */
    virtual ~ZBBPUnitProperties();

// Attributes
protected:
    //@cmember
    /* The unit name. */
    CString m_UnitName;
    /* The unit cost. */
    float m_UnitCost;

public:
    //@cmember
    /* Gets the unit name. */
    CString GetUnitName() const;

    //@cmember
    /* Sets the unit name. */
    void SetUnitName(LPCTSTR lpszValue);

    //@cmember
    /* Gets the unit cost. */
    float GetUnitCost() const;

    //@cmember
    /* Sets the unit cost. */
    void SetUnitCost(const float Value);

// Operations
public:
    /**
    * Compares the property identifier with another identifier
    *@param id - the property identifier to compare with
    *@return TRUE if the property identifiers are equals, otherwise FALSE
    */
    virtual BOOL CompareId(const int nId) const;

    //@cmember
    /* Sets this set of fill properties equal to another. */
    ZBBPUnitProperties& operator=(const ZBBPUnitProperties& propProcess);

    //@cmember
    /* Determines if another set of fill properties is equal to this one. */
    BOOL operator==(const ZBBPUnitProperties propProcess) const;

    //@cmember
    /* Makes a copy of this properties object. */
    virtual CODProperty* Dup();
    //@cmember
    /* Merges another set of properties with this one. */
    virtual void Merge(CODProperty* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL);
    //@cmember
    /* Determines if another set of properties is equal to this one. */
    virtual BOOL IsEqual(CODProperty* pProp);

    // The GUID map implements the QueryGuid function
    BEGIN_GUID_MAP(ZBBPUnitProperties)
        GUID_ENTRY(IODPropertyContainer)
        GUID_ENTRY(sfl::IPropertyContainer)
        GUID_CHAIN_ENTRY(CODIntProperty)
    END_GUID_MAP

    //@cmember
    /* Add a reference to this object. */
    ULONG STDMETHODCALLTYPE AddRef();
    //@cmember
    /* Release a reference to this object. */
    ULONG STDMETHODCALLTYPE Release();

    /////////////////////////////////////////////////////////////////////////
    // IODPropertyContainer interface

    //@cmember
    /* Gets the value of the given string property. */
    virtual BOOL GetValue(const int nPropId, CString& strValue) const;
    //@cmember
    /* Gets the value of the given integer property. */
    virtual BOOL GetValue(const int nPropId, int& nValue) const;
    //@cmember
    /* Gets the value of the given unsigned integer property. */
    virtual BOOL GetValue(const int nPropId, UINT& nValue) const;
    //@cmember
    /* Gets the value of the given DWORD property. */
    virtual BOOL GetValue(const int nPropId, DWORD& dwValue) const;
    //@cmember
    /* Gets the value of the given float property. */
    virtual BOOL GetValue(const int nPropId, float& fValue) const;

    //@cmember
    /* Sets the value of the given string property. */
    virtual BOOL SetValue(const int nPropId, LPCTSTR lpszValue);
    //@cmember
    /* Sets the value of the given integer property. */
    virtual BOOL SetValue(const int nPropId, const int nValue);
    //@cmember
    /* Sets the value of the given unsigned integer property. */
    virtual BOOL SetValue(const int nPropId, const UINT nValue);
    //@cmember
    /* Sets the value of the given unsigned DWORD property. */
    virtual BOOL SetValue(const int nPropId, const DWORD dwValue);
    //@cmember
    /* Sets the value of the given float property. */
    virtual BOOL SetValue(const int nPropId, const float fValue);

    //@cmember
    /* Serializes the line properties. */
    virtual void Serialize(CArchive& ar);

    /////////////////////////////////////////////////////////////////////////
    // Internal helper functions subject to change.
private:

    /* Additional mutators for use with CODIntPropertyAccessor */
    void SetUnitNameEx(const CString value);
    /* Registers the fill property meta-data. */
    bool RegisterProperties();
    
// Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties inline methods

//@mfunc Add a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPUnitProperties::AddRef()
{
    return CODIntProperty::AddRef();
}

//@mfunc Release a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPUnitProperties::Release()
{
    return CODIntProperty::Release();
}

//@mfunc Gets the task list.
//@rdesc The task list.
inline CString ZBBPUnitProperties::GetUnitName() const
{
    return m_UnitName;
}

//@mfunc Gets the decision list.
//@rdesc The decision list.
inline float ZBBPUnitProperties::GetUnitCost() const
{
    return m_UnitCost;
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
inline void ZBBPUnitProperties::SetUnitCost(const float Value)
{
    m_UnitCost = Value;
}


//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline CODProperty* ZBBPUnitProperties::Dup()
{
    return new ZBBPUnitProperties(*this);
}

#endif
