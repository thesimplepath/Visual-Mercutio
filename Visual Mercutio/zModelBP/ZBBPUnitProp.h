/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPUnitProperties
//@module ZBBPUnitProp.h | Interface of the <c ZBBPUnitProperties> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         05/2001
// <nl>Description:  ZBBPUnitProperties unit properties
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __ZBBPUnitProp_H__
#define __ZBBPUnitProp_H__


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zPropertyIds.h"

/////////////////////////////////////////////////////////////////////////////
// Process change flags

//@topic Process Properties Change Flags | Different aspects of the Process
// properties that can be changed individually.
//@flag Z_CHANGE_UNIT_NAME | Change the unit name.
#define Z_CHANGE_UNIT_NAME 0x0001
//@flag Z_CHANGE_UNIT_COST | Change the unit cost.
#define Z_CHANGE_UNIT_COST 0x0002
//@flag Z_CHANGE_UNIT_GUID | Change the unit guid.
#define Z_CHANGE_UNIT_GUID 0x0004

/////////////////////////////////////////////////////////////////////////////
// Fill property IDs

//@topic Fill Property Identifiers | Identify the properties contained by
// <c ZBBPUnitProperties> objects. The ZBBPUnitProperties class is a property
// container for these sub-properties. These property identifiers are
// unique within a process properties container. These identifiers are used
// in conjunction with the <c IODPropertyContainer> interface implemented
// by the process property container.
//@flag Z_UNIT_NAME | Identifier for the task list property.
#define Z_UNIT_NAME                     1
//@flag Z_UNIT_COST | Identifier for the decision list property.
#define Z_UNIT_COST                2
//@flag Z_UNIT_GUID | Identifier for unit GUID.
#define Z_UNIT_GUID                3

///////////////////////////////////////////////////////
// process defaults


#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties
//
//@class This set of properties determines how a component is filled. Normally,
// the component is either not filled or filled with a solid color. You can also
// specify hatching and patterns.
//
// This class is both a property and a container for properties. It implements
// the <c IODPropertyContainer> interface for getting and setting values that
// it contains. Each sub-property contained by process property objects has a
// unique identifier (see <t Process Property Identifiers>) for getting and
// setting each value. There are also methods to directly set each property.
//
//@base public | CODIntProperty
//@base public | CPropertyContainer<lt>IODPropertyContainer, sfl::CODIntPropertyAccessor<lt>ZBBPUnitProperties<gt> <gt>
//





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
    //@cmember
    /* Compare the property identifier with another identifier. */
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

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties member variable descriptions

/////////////////////////////////////////////////////////////////////////////


#endif // __ZBBPUnitProp_H__

/////////////////////////////////////////////////////////////////////////////
