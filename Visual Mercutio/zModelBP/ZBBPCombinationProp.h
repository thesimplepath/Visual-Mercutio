/////////////////////////////////////////////////////////////////////////////
//@doc ZBBPCombinationProperties
//@module ZBBPCombinationProp.h | Interface of the <c ZBBPCombinationProperties> class.
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
// <nl>Created:         03/2001
// <nl>Description:  ZBBPCombinationProperties combination property
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ZBBPCombinationProp_H__
#define __ZBBPCombinationProp_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "PSS_PropIDs.h"

/////////////////////////////////////////////////////////////////////////////
// Process change flags

//@topic Process Properties Change Flags | Different aspects of the Process
// properties that can be changed individually.
//@flag Z_CHANGE_COMBINATION_NAME | Change the task list.
#define Z_CHANGE_COMBINATION_NAME                0x0001
//@flag Z_CHANGE_COMBINATION_DELIVERABLES | Change the decision list.
#define Z_CHANGE_COMBINATION_DELIVERABLES        0x0002
//@flag Z_CHANGE_COMBINATION_ACTIVATION_PERC | Change the decision list.
#define Z_CHANGE_COMBINATION_ACTIVATION_PERC    0x0004
//@flag Z_CHANGE_COMBINATION_MASTER | Change the master deliverable for this combination.
#define Z_CHANGE_COMBINATION_MASTER    0x0008

/////////////////////////////////////////////////////////////////////////////
// Fill property IDs

//@topic Fill Property Identifiers | Identify the properties contained by
// <c ZBBPCombinationProperties> objects. The ZBBPCombinationProperties class is a property
// container for these sub-properties. These property identifiers are
// unique within a process properties container. These identifiers are used
// in conjunction with the <c IODPropertyContainer> interface implemented
// by the process property container.
//@flag Z_COMBINATION_NAME | Identifier for the task list property.
#define Z_COMBINATION_NAME                        1
//@flag Z_COMBINATION_DELIVERABLES | Identifier for the decision list property.
#define Z_COMBINATION_DELIVERABLES                2
//@flag Z_COMBINATION_ACTIVATION_PERC | Identifier for the decision list property.
#define Z_COMBINATION_ACTIVATION_PERC            3
//@flag Z_COMBINATION_MASTER | Identifier for the master deliverable for this combination.
#define Z_COMBINATION_MASTER                    4

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

// JMR-MODIF - Le 6 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZBBPCombinationProperties
//
//@class This set of properties determines how a component is filled. Normally,
// the component is either not filled or filled with a solid color. You can also
// specify hatching and patterns.
//
//
//@base public | CObject
//

class AFX_EXT_CLASS ZBBPCombinationProperties : public CObject
{
    DECLARE_SERIAL( ZBBPCombinationProperties )

// Construction/Destruction
public:

    //@cmember
    // Constructor.
    ZBBPCombinationProperties();

    //@cmember
    // Copy constructor.
    ZBBPCombinationProperties( const ZBBPCombinationProperties& propProcess );

    //@cmember
    // Destructor.
    virtual ~ZBBPCombinationProperties();

// Operations
public:

    //@cmember
    // Sets this set of fill properties equal to another.
    ZBBPCombinationProperties& operator=( const ZBBPCombinationProperties& propProcess );

    //@cmember
    // Determines if another set of fill properties is equal to this one.
    BOOL operator==( const ZBBPCombinationProperties propProcess ) const;

    //@cmember
    // Makes a copy of this properties object.
    virtual ZBBPCombinationProperties* Dup();

    //@cmember
    // Merges another set of properties with this one.
    virtual void Merge( ZBBPCombinationProperties* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL );

    //@cmember
    // Determines if another set of properties is equal to this one.
    virtual BOOL IsEqual( ZBBPCombinationProperties* pProp );

public:

    //@cmember
    // Gets the combination name.
    CString GetCombinationName() const;

    //@cmember
    // Sets the combination name.
    void SetCombinationName( LPCTSTR lpszValue );

    //@cmember
    // Gets the list of deliberables.
    CString GetCombinationDeliverables() const;

    //@cmember
    // Sets the list of deliberables.
    void SetCombinationDeliverables( LPCTSTR lpszValue );

    //@cmember
    // Gets the combination percentage.
    float GetCombinationActivationPerc() const;

    //@cmember
    // Sets the combination percentage.
    void SetCombinationActivationPerc( const float value );

    // Returns true if the deliverable is defined in the combination
    bool IsDeliverableInCombination( LPCTSTR lpszValue );

    // Gets the combination master name.
    CString GetCombinationMaster() const;

    //@cmember
    // Sets the combination master name.
    void SetCombinationMaster( LPCTSTR lpszValue );

    /////////////////////////////////////////////////////////////////////////
    // GetValue and SetValue functions

    //@cmember
    // Gets the value of the given string property.
    virtual BOOL GetValue( const int nPropId, CString& strValue ) const;

    //@cmember
    // Gets the value of the given integer property.
    virtual BOOL GetValue( const int nPropId, int& nValue ) const;

    //@cmember
    // Gets the value of the given unsigned integer property.
    virtual BOOL GetValue( const int nPropId, UINT& nValue ) const;

    //@cmember
    // Gets the value of the given DWORD property.
    virtual BOOL GetValue( const int nPropId, DWORD& dwValue ) const;

    //@cmember
    // Gets the value of the given float property.
    virtual BOOL GetValue( const int nPropId, float& fValue ) const;

    //@cmember
    // Sets the value of the given string property.
    virtual BOOL SetValue( const int nPropId, LPCTSTR lpszValue );

    //@cmember
    // Sets the value of the given integer property.
    virtual BOOL SetValue( const int nPropId, const int nValue );

    //@cmember
    // Sets the value of the given unsigned integer property.
    virtual BOOL SetValue( const int nPropId, const UINT nValue );

    //@cmember
    // Sets the value of the given unsigned DWORD property.
    virtual BOOL SetValue( const int nPropId, const DWORD dwValue );

    //@cmember
    // Sets the value of the given float property.
    virtual BOOL SetValue( const int nPropId, const float fValue );

    //@cmember
    // Serializes the line properties.
    virtual void Serialize( CArchive& ar );

private:

    // Additional mutators for use with CODIntPropertyAccessor.
    void SetCombinationNameEx( const CString value );
    void SetCombinationDeliverablesEx( const CString value );
    void SetCombinationMasterEx( const CString value );

// Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

// Attributes
protected:

    //@cmember
    // The combination name.
    CString    m_CombinationName;

    // The deliverable list.
    CString    m_CombinationDeliverables;

    // The combination master deliverable.
    CString    m_CombinationMaster;

    // The activation percentage.
    float    m_CombinationActivationPerc;
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPCombinationProperties inline methods

inline CString ZBBPCombinationProperties::GetCombinationName() const
{
    return m_CombinationName;
}

inline CString ZBBPCombinationProperties::GetCombinationDeliverables() const
{
    return m_CombinationDeliverables;
}

inline CString ZBBPCombinationProperties::GetCombinationMaster() const
{
    return m_CombinationMaster;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline ZBBPCombinationProperties* ZBBPCombinationProperties::Dup()
{
    return new ZBBPCombinationProperties( *this );
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline float ZBBPCombinationProperties::GetCombinationActivationPerc() const
{
    return m_CombinationActivationPerc;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPCombinationProperties::SetCombinationActivationPerc( const float value )
{
    m_CombinationActivationPerc = value;
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPCombinationProperties member variable descriptions

/////////////////////////////////////////////////////////////////////////////
#endif // __ZBBPCombinationProp_H__
/////////////////////////////////////////////////////////////////////////////