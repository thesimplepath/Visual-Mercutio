/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropProcedure2.h : Declaration of ZBBPCostPropertiesProcedure2
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
// Created:         05/2001
// Description:  ZBBPCostPropertiesProcedure2 cost properties for procedure
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBBPZBBPCostPropProcedure2_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPZBBPCostPropProcedure2_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

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

// JMR-MODIF - Le 26 novembre 2006 - Ajout des décorations unicode _T(), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Orientation change flags

//@topic Basic Properties Change Flags 
//@flag Z_CHANGE_COST_MULTIPLIER | Change the cost multiplier factor.
#ifndef Z_CHANGE_COST_MULTIPLIER
#define Z_CHANGE_COST_MULTIPLIER                    0x0001
#endif

//@flag Z_CHANGE_COST_PROCESSING_TIME | Change the processing time.
#ifndef Z_CHANGE_COST_PROCESSING_TIME
#define Z_CHANGE_COST_PROCESSING_TIME                0x0002
#endif

//@flag Z_CHANGE_COST_UNITARY_COST | Change the unitary cost.
#ifndef Z_CHANGE_COST_UNITARY_COST
#define Z_CHANGE_COST_UNITARY_COST                    0x0004
#endif

//@flag Z_CHANGE_COST_PROCESSING_DURATION | Change the processing duration.
#ifndef Z_CHANGE_COST_PROCESSING_DURATION
#define Z_CHANGE_COST_PROCESSING_DURATION            0x0008
#endif

//@flag Z_CHANGE_COST_PROCESSING_DURATIONMAX | Change the processing duration maximum.
#ifndef Z_CHANGE_COST_PROCESSING_DURATIONMAX
#define Z_CHANGE_COST_PROCESSING_DURATIONMAX        0x0010
#endif

/////////////////////////////////////////////////////////////////////////////
// Orientation property IDs

//@topic Basic Property Identifiers | Identify the properties
// contained by <c ZBBPCostPropertiesProcedure2> objects. The ZBBPCostPropertiesProcedure2
// class is a property container for these sub-properties. These
// identifiers are used in conjunction with the <c IODPropertyContainer>
// interface implemented by the orientation property container.
//@flag Z_COST_MULTIPLIER | Identifier for the cost multiplier factor.
#ifndef Z_COST_MULTIPLIER
#define Z_COST_MULTIPLIER                    1
#endif

//@flag Z_COST_PROCESSING_TIME | Identifier for the processing time.
#ifndef Z_COST_PROCESSING_TIME
#define Z_COST_PROCESSING_TIME                2
#endif

//@flag Z_COST_UNITARY_COST | Identifier for the unitary cost.
#ifndef Z_COST_UNITARY_COST
#define Z_COST_UNITARY_COST                    3
#endif

//@flag Z_COST_PROCESSING_DURATION | Identifier for the processing duration.
#ifndef Z_COST_PROCESSING_DURATION
#define Z_COST_PROCESSING_DURATION            4
#endif

//@flag Z_COST_PROCESSING_DURATIONMAX | Identifier for the processing duration.maximum
#ifndef Z_COST_PROCESSING_DURATIONMAX
#define Z_COST_PROCESSING_DURATIONMAX        5
#endif

/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropertiesProcedure2
//
//@class Determines the orientation of a label or component in relation to
// its container. The orientation is defined by an OD_CONTROL_POINT value
// that indicates a location in the container object. Horizontal and vertical
// offset values can also be specified.
//
// This class is both a property and a container for properties. It implements
// the <c IODPropertyContainer> interface for getting and setting values that
// it contains. Each sub-property contained by orientation property objects
// has a unique identifier (see <t Orientation Property Identifiers>) for
// getting and setting each value. There are also methods to directly set
// each property.
//
//@base public | CODIntProperty
//@base public | CPropertyContainer<lt>IODPropertyContainer, sfl::CODIntPropertyAccessor<lt>ZBBPCostPropertiesProcedure2<gt> <gt>

class AFX_EXT_CLASS ZBBPCostPropertiesProcedure2 : public CObject
{
    DECLARE_SERIAL( ZBBPCostPropertiesProcedure2 )

// Construction/Destruction
public:

    //@cmember
    /* Constructor. */
    ZBBPCostPropertiesProcedure2();

    //@cmember
    /* Copy constructor. */
    ZBBPCostPropertiesProcedure2( const ZBBPCostPropertiesProcedure2& propBasic );

    //@cmember
    /* Destructor. */
    virtual ~ZBBPCostPropertiesProcedure2();

// Operations
public:

    //@cmember
    /* Assigns another property to this property. */
    ZBBPCostPropertiesProcedure2& operator=( const ZBBPCostPropertiesProcedure2& propBasic );

    //@cmember
    /* Compares two orientation properties. */
    BOOL operator==( const ZBBPCostPropertiesProcedure2 propBasic ) const;

    //@cmember
    /* Makes a copy of this properties object. */
    virtual ZBBPCostPropertiesProcedure2* Dup();

    //@cmember
    /* Merges another set of properties with this one. */
    virtual void Merge( ZBBPCostPropertiesProcedure2* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL );

    //@cmember
    /* Determines if another set of properties is equal to this one. */
    virtual BOOL IsEqual( ZBBPCostPropertiesProcedure2* pProp );

public:

    //@cmember
    /* Gets the cost multiplier factor. */
    float GetMultiplier() const;

    //@cmember
    /* Sets the cost multiplier factor. */
    void SetMultiplier( const float value );

    //@cmember
    /* Gets the processing time. */
    double GetProcessingTime() const;

    //@cmember
    /* Sets the processing time. */
    void SetProcessingTime( const double value );

    //@cmember
    /* Gets the unitary cost. */
    float GetUnitaryCost() const;

    //@cmember
    /* Sets the unitary cost. */
    void SetUnitaryCost( const float value );

    //@cmember
    /* Gets the processing time. */
    double GetProcessingDuration() const;

    //@cmember
    /* Sets the processing time. */
    void SetProcessingDuration( const double value );

    //@cmember
    /* Gets the processing time maximum. */
    double GetProcessingDurationMax() const;

    //@cmember
    /* Sets the processing time maximum. */
    void SetProcessingDurationMax( const double value );

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
    /* Gets the value of the given double property. */
    virtual BOOL GetValue( const int nPropId, double& dValue ) const;

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
    /* Sets the value of the given double property. */
    virtual BOOL SetValue( const int nPropId, const double dValue );

    //@cmember
    /* Serializes the orientation properties. */
    virtual void Serialize( CArchive& ar );

// Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

// Attributes
protected:

    //@cmember
    /* the cost multiplier factor. */
    float m_Multiplier;

    //@cmember
    /* the processing time. */
    double m_ProcessingTime;

    //@cmember
    /* the unitary cost. */
    float m_UnitaryCost;

    //@cmember
    /* the processing duration. */
    double m_ProcessingDuration;

    //@cmember
    /* the processing duration maximum. */
    double m_ProcessingDurationMax;
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropertiesProcedure2 inline methods

//@mfunc Gets the multiplier.
//@rdesc multiplier value.
inline float ZBBPCostPropertiesProcedure2::GetMultiplier() const
{
    return m_Multiplier;
}

//@mfunc Sets the multiplier.
//@rdesc void
//@parm multiplier value.
inline void ZBBPCostPropertiesProcedure2::SetMultiplier( const float value )
{
    m_Multiplier = value;
}

//@mfunc Gets the processing time.
//@rdesc processing time value.
inline double ZBBPCostPropertiesProcedure2::GetProcessingTime() const
{
    return m_ProcessingTime;
}

//@mfunc Sets the processing time.
//@rdesc void
//@parm processing time value.
inline void ZBBPCostPropertiesProcedure2::SetProcessingTime( const double value )
{
    m_ProcessingTime = value;
}

//@mfunc Gets unitary cost.
//@rdesc unitary cost value.
inline float ZBBPCostPropertiesProcedure2::GetUnitaryCost() const
{
    return m_UnitaryCost;
}

//@mfunc Sets the unitary cost.
//@rdesc void
//@parm unitary cost value.
inline void ZBBPCostPropertiesProcedure2::SetUnitaryCost( const float value )
{
    m_UnitaryCost = value;
}

//@mfunc Gets the processing duration.
//@rdesc processing duration value.
inline double ZBBPCostPropertiesProcedure2::GetProcessingDuration() const
{
    return m_ProcessingDuration;
}

//@mfunc Sets the processing duration.
//@rdesc void
//@parm processing duration value.
inline void ZBBPCostPropertiesProcedure2::SetProcessingDuration( const double value )
{
    m_ProcessingDuration = value;
}

//@mfunc Gets the processing duration maximum.
//@rdesc processing duration maximum value.
inline double ZBBPCostPropertiesProcedure2::GetProcessingDurationMax() const
{
    return m_ProcessingDurationMax;
}

//@mfunc Sets the processing duration maximum.
//@rdesc void
//@parm processing duration maximum value.
inline void ZBBPCostPropertiesProcedure2::SetProcessingDurationMax( const double value )
{
    m_ProcessingDurationMax = value;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline ZBBPCostPropertiesProcedure2* ZBBPCostPropertiesProcedure2::Dup()
{
    return new ZBBPCostPropertiesProcedure2( *this );
}

#endif // !defined(AFX_ZBBPZBBPCostPropProcedure2_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)