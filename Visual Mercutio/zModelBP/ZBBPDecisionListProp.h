/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPDecisionListProperties
//@module ZBBPDecisionListProp.h | Interface of the <c ZBBPDecisionListProperties> class.
// 
// zForms<tm>
// <nl>Copyright <cp> 2001 Advanced Dedicated Software, Inc. All rights reserved.
// 
// 
// Author: Dominique Aigroz
// <nl>Created: 03/2001
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef __ZBBPDecisionListProp_H__
#define __ZBBPDecisionListProp_H__

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "PSS_PropIDs.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 13 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Process change flags

//@topic Process Properties Change Flags | Different aspects of the Process
// properties that can be changed individually.
//@flag Z_CHANGE_DECISION_LIST | Change the decision list.
#define Z_CHANGE_DECISION_LIST 0x0001

/////////////////////////////////////////////////////////////////////////////
// Fill property IDs

//@topic Fill Property Identifiers | Identify the properties contained by
// <c ZBBPDecisionListProperties> objects. The ZBBPDecisionListProperties class is a property
// container for these sub-properties. These property identifiers are
// unique within a process properties container. These identifiers are used
// in conjunction with the <c IODPropertyContainer> interface implemented
// by the process property container.
//@flag Z_DECISION_LIST | Identifier for the decision list property.
#define Z_DECISION_LIST 1

/////////////////////////////////////////////////////////////////////////////
// ZBBPDecisionListProperties
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
//@base public | CPropertyContainer<lt>IODPropertyContainer, sfl::CODIntPropertyAccessor<lt>ZBBPDecisionListProperties<gt> <gt>

class AFX_EXT_CLASS ZBBPDecisionListProperties : public CODIntProperty,
                                                 public sfl::CPropertyContainer<IODPropertyContainer, CODPropertyAccessor<ZBBPDecisionListProperties> >
{
    DECLARE_SERIAL( ZBBPDecisionListProperties )

// Construction/Destruction
public:

    //@cmember
    /* Constructor. */
    ZBBPDecisionListProperties( int nId = ZS_BP_PROP_DECISIONLIST );

    //@cmember
    /* Copy constructor. */
    ZBBPDecisionListProperties( const ZBBPDecisionListProperties& propProcess );

    //@cmember
    /* Destructor. */
    virtual ~ZBBPDecisionListProperties();

public:

    //@cmember
    /* Gets the decision list. */
    CString GetDecisionList() const;

    //@cmember
    /* Sets the task list. */
    void SetDecisionList( LPCTSTR lpszValue );

// Operations
public:
    /**
    * Checks if the identifier is in the property identifier range
    *@param id - the identifier to check
    *@return TRUE if the identifier is in the range, otherwise FALSE
    */
    virtual BOOL CompareId( const int nId ) const;

    //@cmember
    /* Sets this set of fill properties equal to another. */
    ZBBPDecisionListProperties& operator=( const ZBBPDecisionListProperties& propProcess );

    //@cmember
    /* Determines if another set of fill properties is equal to this one. */
    BOOL operator==( const ZBBPDecisionListProperties propProcess ) const;

    //@cmember
    /* Makes a copy of this properties object. */
    virtual CODProperty* Dup();

    //@cmember
    /* Merges another set of properties with this one. */
    virtual void Merge( CODProperty* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL );

    //@cmember
    /* Determines if another set of properties is equal to this one. */
    virtual BOOL IsEqual( CODProperty* pProp );

    // The GUID map implements the QueryGuid function
    BEGIN_GUID_MAP(ZBBPDecisionListProperties)
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
    virtual BOOL GetValue( const int nPropId, CString& strValue ) const;

    //@cmember
    /* Gets the value of the given integer property. */
    virtual BOOL GetValue( const int nPropId, int& nValue ) const;

    //@cmember
    /* Gets the value of the given unsigned integer property. */
    virtual BOOL GetValue( const int nPropId, UINT& nValue ) const;

    //@cmember
    /* Gets the value of the given DWORD property. */
    virtual BOOL GetValue( const int nPropId, DWORD& dwValue ) const;

    //@cmember
    /* Gets the value of the given float property. */
    virtual BOOL GetValue( const int nPropId, float& fValue ) const;

    //@cmember
    /* Sets the value of the given string property. */
    virtual BOOL SetValue( const int nPropId, LPCTSTR lpszValue );

    //@cmember
    /* Sets the value of the given integer property. */
    virtual BOOL SetValue( const int nPropId, const int nValue );

    //@cmember
    /* Sets the value of the given unsigned integer property. */
    virtual BOOL SetValue( const int nPropId, const UINT nValue );

    //@cmember
    /* Sets the value of the given unsigned DWORD property. */
    virtual BOOL SetValue( const int nPropId, const DWORD dwValue );

    //@cmember
    /* Sets the value of the given float property. */
    virtual BOOL SetValue( const int nPropId, const float fValue );

    //@cmember
    /* Serializes the line properties. */
    virtual void Serialize( CArchive& ar );

private:

    /* Additional mutators for use with CODIntPropertyAccessor */
    void SetDecisionListEx( const CString value );

    /* Registers the fill property meta-data. */
    bool RegisterProperties();
    
// Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

// Attributes
protected:

    //@cmember
    /* The decision list. */
    CString m_DecisionList;
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPDecisionListProperties inline methods

//@mfunc Add a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPDecisionListProperties::AddRef()
{
    return CODIntProperty::AddRef();
}

//@mfunc Release a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPDecisionListProperties::Release()
{
    return CODIntProperty::Release();
}

//@mfunc Gets the decision list.
//@rdesc The decision list.
inline CString ZBBPDecisionListProperties::GetDecisionList() const
{
    return m_DecisionList;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline CODProperty* ZBBPDecisionListProperties::Dup()
{
    return new ZBBPDecisionListProperties(*this);
}

#endif // __ZBBPDecisionListProp_H__