/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPProcessProp
//@module ZBBPProcessProp.h | Interface of the <c ZBBPProcessProp> class.
// 
// zForms<tm>
// <nl>Copyright <cp> 2001 Advanced Dedicated Software, Inc. All rights reserved.
// 
// 
// Author: Dominique Aigroz
// <nl>Created: 03/2001
// 
/////////////////////////////////////////////////////////////////////////////
#ifndef __ZBBPProcessProp_H__
#define __ZBBPProcessProp_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

// JMR-MODIF - Le 21 février 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Process change flags

//@topic Process Properties Change Flags | Different aspects of the Process
// properties that can be changed individually.
//@flag Z_CHANGE_MANAGEMENT_CASE | Change the management name.
#define Z_CHANGE_MANAGEMENT_CASE    0x0001

/////////////////////////////////////////////////////////////////////////////
// Fill property IDs

//@topic Fill Property Identifiers | Identify the properties contained by
// <c ZBBPProcessProperties> objects. The ZBBPProcessProperties class is a property
// container for these sub-properties. These property identifiers are
// unique within a process properties container. These identifiers are used
// in conjunction with the <c IODPropertyContainer> interface implemented
// by the process property container.
//@flag Z_MANAGEMENT_CASE | Identifier for the management case property.
#define Z_MANAGEMENT_CASE    1

/////////////////////////////////////////////////////////////////////////////
// ZBBPProcessProperties
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
//@base public | CPropertyContainer<lt>IODPropertyContainer, sfl::CODIntPropertyAccessor<lt>ZBBPProcessProperties<gt> <gt>
//

class AFX_EXT_CLASS ZBBPProcessProperties : public CODIntProperty,
                                            public sfl::CPropertyContainer<IODPropertyContainer,
                                                                           CODPropertyAccessor<ZBBPProcessProperties> >
{
    DECLARE_SERIAL( ZBBPProcessProperties )

// Construction/Destruction
public:

    //@cmember
    /* Constructor. */
    ZBBPProcessProperties( int nId = ZS_BP_PROP_PROCESS );

    //@cmember
    /* Copy constructor. */
    ZBBPProcessProperties( const ZBBPProcessProperties& propProcess );

    //@cmember
    /* Destructor. */
    virtual ~ZBBPProcessProperties();

// Operations
public:

    //@cmember
    /* Compare the property identifier with another identifier. */
    virtual BOOL CompareId( const int nId ) const;

    //@cmember
    /* Sets this set of fill properties equal to another. */
    ZBBPProcessProperties& operator=( const ZBBPProcessProperties& propProcess );

    //@cmember
    /* Determines if another set of fill properties is equal to this one. */
    BOOL operator==( const ZBBPProcessProperties propProcess ) const;

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
    BEGIN_GUID_MAP(ZBBPProcessProperties)
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

public:

    //@cmember
    /* Gets the management case. */
    CString GetManagementCase() const;

    //@cmember
    /* Sets the management case. */
    void SetManagementCase( LPCTSTR lpszName );

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

// Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

private:

    /* Additional mutators for use with CODIntPropertyAccessor */
    void SetManagementCaseEx( const CString name );

    /* Registers the fill property meta-data. */
    bool RegisterProperties();

// Attributes
protected:

    //@cmember
    /* The management case. */
    CString m_ManagementCase;
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPProcessProperties inline methods

//@mfunc Add a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPProcessProperties::AddRef()
{
    return CODIntProperty::AddRef();
}

//@mfunc Release a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPProcessProperties::Release()
{
    return CODIntProperty::Release();
}

//@mfunc Gets the management case name.
//@rdesc The management case name.
inline CString ZBBPProcessProperties::GetManagementCase() const
{
    return m_ManagementCase;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline CODProperty* ZBBPProcessProperties::Dup()
{
    return new ZBBPProcessProperties( *this );
}

#endif // __ZBBPProcessProp_H__