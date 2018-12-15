/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPTextItemListProperties
//@module ZBBPTextItemListProp.h | Interface of the <c ZBBPTextItemListProperties> class.
// 
// zForms<tm>
// <nl>Copyright <cp> 2001 Advanced Dedicated Software, Inc. All rights reserved.
// 
// 
// Author: Dominique Aigroz
// <nl>Created: 03/2001
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef __ZBBPTextItemListProp_H__
#define __ZBBPTextItemListProp_H__


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
//@flag Z_CHANGE_TEXTITEM_LIST | Change the decision list.
#define Z_CHANGE_TEXTITEM_LIST 0x0001

/////////////////////////////////////////////////////////////////////////////
// Fill property IDs

//@topic Fill Property Identifiers | Identify the properties contained by
// <c ZBBPTextItemListProperties> objects. The ZBBPTextItemListProperties class is a property
// container for these sub-properties. These property identifiers are
// unique within a process properties container. These identifiers are used
// in conjunction with the <c IODPropertyContainer> interface implemented
// by the process property container.
//@flag Z_TEXTITEM_LIST | Identifier for the decision list property.
#define Z_TEXTITEM_LIST                1

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
// ZBBPTextItemListProperties
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
//@base public | CPropertyContainer<lt>IODPropertyContainer, sfl::CODIntPropertyAccessor<lt>ZBBPTextItemListProperties<gt> <gt>
//





class AFX_EXT_CLASS ZBBPTextItemListProperties : public CODIntProperty, 
                public sfl::CPropertyContainer<IODPropertyContainer, CODPropertyAccessor<ZBBPTextItemListProperties> >
{
    DECLARE_SERIAL(ZBBPTextItemListProperties)

// Construction/Destruction
public:
    //@cmember
    /* Constructor. */
    ZBBPTextItemListProperties(int nId = ZS_BP_PROP_TEXTITEMLIST);
    //@cmember
    /* Copy constructor. */
    ZBBPTextItemListProperties(const ZBBPTextItemListProperties& propProcess);
    //@cmember
    /* Destructor. */
    virtual ~ZBBPTextItemListProperties();

// Attributes
protected:
    //@cmember
    /* The decision list. */
    CString m_TextItemList;

public:
    //@cmember
    /* Gets the decision list. */
    CString GetTextItemList() const;

    //@cmember
    /* Sets the task list. */
    void SetTextItemList(LPCTSTR lpszValue);


// Operations
public:
    //@cmember
    /* Compare the property identifier with another identifier. */
    virtual BOOL CompareId(const int nId) const;

    //@cmember
    /* Sets this set of fill properties equal to another. */
    ZBBPTextItemListProperties& operator=(const ZBBPTextItemListProperties& propProcess);

    //@cmember
    /* Determines if another set of fill properties is equal to this one. */
    BOOL operator==(const ZBBPTextItemListProperties propProcess) const;

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
    BEGIN_GUID_MAP(ZBBPTextItemListProperties)
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
    void SetTextItemListEx(const CString value);
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
// ZBBPTextItemListProperties inline methods

//@mfunc Add a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPTextItemListProperties::AddRef()
{
    return CODIntProperty::AddRef();
}

//@mfunc Release a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPTextItemListProperties::Release()
{
    return CODIntProperty::Release();
}

//@mfunc Gets the decision list.
//@rdesc The decision list.
inline CString ZBBPTextItemListProperties::GetTextItemList() const
{
    return m_TextItemList;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline CODProperty* ZBBPTextItemListProperties::Dup()
{
    return new ZBBPTextItemListProperties(*this);
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPTextItemListProperties member variable descriptions

/////////////////////////////////////////////////////////////////////////////


#endif // __ZBBPTextItemListProp_H__

/////////////////////////////////////////////////////////////////////////////
