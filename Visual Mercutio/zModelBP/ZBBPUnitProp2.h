/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPUnitProperties2
//@module ZBBPUnitProp2.h | Interface of the <c ZBBPUnitProperties2> class.
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
// <nl>Description:  ZBBPUnitProperties2 unit properties
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ZBBPUnitProp2_H__
#define __ZBBPUnitProp2_H__

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

// JMR-MODIF - Le 26 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Process change flags

//@topic Process Properties Change Flags | Different aspects of the Process
// properties that can be changed individually.
//@flag Z_CHANGE_UNIT_NAME | Change the unit name.
#define Z_CHANGE_UNIT_NAME                0x0001
//@flag Z_CHANGE_UNIT_COST | Change the unit cost.
#define Z_CHANGE_UNIT_COST                0x0002
//@flag Z_CHANGE_UNIT_GUID | Change the unit guid.
#define Z_CHANGE_UNIT_GUID                0x0004
//@flag Z_CHANGE_UNIT_DOUBLE_VALIDATION | Change the unit double validation type.
#define Z_CHANGE_UNIT_DOUBLE_VALIDATION    0x0008

/////////////////////////////////////////////////////////////////////////////
// Fill property IDs

//@topic Fill Property Identifiers | Identify the properties contained by
// <c ZBBPUnitProperties2> objects. The ZBBPUnitProperties2 class is a property
// container for these sub-properties. These property identifiers are
// unique within a process properties container. These identifiers are used
// in conjunction with the <c IODPropertyContainer> interface implemented
// by the process property container.
//@flag Z_UNIT_NAME | Identifier for the unit name.
#define Z_UNIT_NAME                        1
//@flag Z_UNIT_COST | Identifier for the unit cost.
#define Z_UNIT_COST                        2
//@flag Z_UNIT_GUID | Identifier for unit GUID.
#define Z_UNIT_GUID                        3
//@flag Z_UNIT_DOUBLE_VALIDATION | Identifier for unit double validation type.
#define Z_UNIT_DOUBLE_VALIDATION        4

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties2
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
//@base public | CPropertyContainer<lt>IODPropertyContainer, sfl::CODIntPropertyAccessor<lt>ZBBPUnitProperties2<gt> <gt>
//

class AFX_EXT_CLASS ZBBPUnitProperties2 : public CObject
{
    DECLARE_SERIAL( ZBBPUnitProperties2 )

// Construction/Destruction
public:

    //@cmember
    /* Constructor. */
    ZBBPUnitProperties2();

    //@cmember
    /* Copy constructor. */
    ZBBPUnitProperties2( const ZBBPUnitProperties2& propProcess );

    //@cmember
    /* Destructor. */
    virtual ~ZBBPUnitProperties2();

public:

    //@cmember
    /* Gets the unit name. */
    CString GetUnitName() const;

    //@cmember
    /* Sets the unit name. */
    void SetUnitName( LPCTSTR lpszValue );

    //@cmember
    /* Gets the unit cost. */
    float GetUnitCost() const;

    //@cmember
    /* Sets the unit cost. */
    void SetUnitCost( const float Value );

    //@cmember
    /* Gets the unit guid. */
    CString GetUnitGUID() const;

    //@cmember
    /* Sets the unit guid. */
    void SetUnitGUID( LPCTSTR lpszValue );

    //@cmember
    /* Gets the unit guid. */
    int GetUnitDoubleValidationType() const;

    //@cmember
    /* Sets the unit guid. */
    void SetUnitDoubleValidationType( const int Value );

    void GetUnitDoubleValidationTypeStringArray( CStringArray& sar ) const;
    int ConvertUnitDoubleValidationString2Type( const CString Type ) const;
    CString GetUnitDoubleValidationTypeString( const int Value ) const;

// Operations
public:

    //@cmember
    /* Sets this set of fill properties equal to another. */
    ZBBPUnitProperties2& operator=( const ZBBPUnitProperties2& propProcess );

    //@cmember
    /* Determines if another set of fill properties is equal to this one. */
    BOOL operator==( const ZBBPUnitProperties2 propProcess ) const;

    //@cmember
    /* Makes a copy of this properties object. */
    virtual ZBBPUnitProperties2* Dup();

    //@cmember
    /* Merges another set of properties with this one. */
    virtual void Merge( ZBBPUnitProperties2* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL );

    //@cmember
    /* Determines if another set of properties is equal to this one. */
    virtual BOOL IsEqual( ZBBPUnitProperties2* pProp );

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

    /////////////////////////////////////////////////////////////////////////
    // Internal helper functions subject to change.
private:

    /* Additional mutators for use with CODIntPropertyAccessor */
    void SetUnitNameEx( const CString value );
    void SetUnitGUIDEx( const CString value );
    
// Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

// Attributes
protected:

    //@cmember
    /* The unit name. */
    CString m_UnitName;

    /* The unit cost. */
    float m_UnitCost;

    /* The unit guid. */
    CString m_UnitGUID;

    /* The double validation type. */
    int m_DoubleValidationType;
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPUnitProperties2 inline methods

//@mfunc Gets the task list.
//@rdesc The task list.
inline CString ZBBPUnitProperties2::GetUnitName() const
{
    return m_UnitName;
}

//@mfunc Gets the decision list.
//@rdesc The decision list.
inline float ZBBPUnitProperties2::GetUnitCost() const
{
    return m_UnitCost;
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
inline void ZBBPUnitProperties2::SetUnitCost( const float Value )
{
    m_UnitCost = Value;
}

//@mfunc Gets the unit guid.
//@rdesc The unit guid.
inline CString ZBBPUnitProperties2::GetUnitGUID() const
{
    return m_UnitGUID;
}

//@mfunc Gets the decision list.
//@rdesc The decision list.
inline int ZBBPUnitProperties2::GetUnitDoubleValidationType() const
{
    return m_DoubleValidationType;
}

//@mfunc Sets the decision list.
//@rdesc void
//@parm The new decision list.
inline void ZBBPUnitProperties2::SetUnitDoubleValidationType( const int Value )
{
    m_DoubleValidationType = Value;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline ZBBPUnitProperties2* ZBBPUnitProperties2::Dup()
{
    return new ZBBPUnitProperties2( *this );
}

#endif // __ZBBPUnitProp2_H__