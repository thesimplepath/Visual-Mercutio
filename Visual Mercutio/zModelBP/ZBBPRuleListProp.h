/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPRuleListProperties
//@module XXXClass.h | Interface of the <c ZBBPRuleListProperties> class.
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
// <nl>Created:         04/2002
// <nl>Description:  ZBBPRuleListProperties manages a list of rules
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ZBBPRuleListProp_H__
#define __ZBBPRuleListProp_H__

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zPropertyIds.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 22 novembre 2006 - Ajout des décorations unicode _T(), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Process change flags

//@topic Process Properties Change Flags | Different aspects of the Process
// properties that can be changed individually.
//@flag Z_CHANGE_RULE_LIST | Change the rule list.
#define    Z_CHANGE_RULE_LIST    0x0001

/////////////////////////////////////////////////////////////////////////////
// Fill property IDs

//@topic Fill Property Identifiers | Identify the properties contained by
// <c ZBBPRuleListProperties> objects. The ZBBPRuleListProperties class is a property
// container for these sub-properties. These property identifiers are
// unique within a process properties container. These identifiers are used
// in conjunction with the <c IODPropertyContainer> interface implemented
// by the process property container.
//@flag Z_RULE_LIST | Identifier for the rule list property.
#define    Z_RULE_LIST            1

/////////////////////////////////////////////////////////////////////////////
// ZBBPRuleListProperties

//@class This set of properties determines how a component is filled. Normally,
// the component is either not filled or filled with a solid color. You can also
// specify hatching and patterns.
//
// This class is both a property and a container for properties. It implements
// the <c IODPropertyContainer> interface for getting and setting values that
// it contains. Each sub-property contained by process property objects has a
// unique identifier (see <t Process Property Identifiers>) for getting and
// setting each value. There are also methods to directly set each property.

//@base public | CODIntProperty
//@base public | CPropertyContainer<lt>IODPropertyContainer, sfl::CODIntPropertyAccessor<lt>ZBBPRuleListProperties<gt> <gt>

class AFX_EXT_CLASS ZBBPRuleListProperties : public CODIntProperty,
                                             public sfl::CPropertyContainer<IODPropertyContainer, CODPropertyAccessor<ZBBPRuleListProperties> >
{
    DECLARE_SERIAL( ZBBPRuleListProperties )

// Construction/Destruction
public:

    //@cmember
    /* Constructor. */
    ZBBPRuleListProperties( int nId = ZS_BP_PROP_RULELIST );

    //@cmember
    /* Copy constructor. */
    ZBBPRuleListProperties( const ZBBPRuleListProperties& propProcess );

    //@cmember
    /* Destructor. */
    virtual ~ZBBPRuleListProperties();

// Operations
public:

    //@cmember
    /* Sets this set of fill properties equal to another. */
    ZBBPRuleListProperties& operator=( const ZBBPRuleListProperties& propProcess );

    //@cmember
    /* Determines if another set of fill properties is equal to this one. */
    BOOL operator==( const ZBBPRuleListProperties propProcess ) const;

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
    BEGIN_GUID_MAP(ZBBPRuleListProperties)
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
    /* Compare the property identifier with another identifier. */
    virtual BOOL CompareId( const int nId ) const;

    //@cmember
    /* Gets the task list. */
    CString GetRuleList() const;

    //@cmember
    /* Sets the task list. */
    void SetRuleList( LPCTSTR lpszValue );

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

// Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

private:

    /* Additional mutators for use with CODIntPropertyAccessor */
    void SetRuleListEx( const CString value );

    /* Registers the fill property meta-data. */
    bool RegisterProperties();

// Attributes
protected:

    //@cmember
    /* The task list. */
    CString m_RuleList;
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPRuleListProperties inline methods

//@mfunc Add a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPRuleListProperties::AddRef()
{
    return CODIntProperty::AddRef();
}

//@mfunc Release a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPRuleListProperties::Release()
{
    return CODIntProperty::Release();
}

//@mfunc Gets the task list.
//@rdesc The task list.
inline CString ZBBPRuleListProperties::GetRuleList() const
{
    return m_RuleList;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline CODProperty* ZBBPRuleListProperties::Dup()
{
    return new ZBBPRuleListProperties( *this );
}

#endif // __ZBBPRuleListProp_H__