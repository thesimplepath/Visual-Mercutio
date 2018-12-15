/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropDeliverable2.h : Declaration of ZBBPCostPropertiesDeliverable2
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
// Description:  ZBBPCostPropertiesDeliverable2 cost properties for deliverables
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_ZBBPZBBPCostPropDeliverable2_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPZBBPCostPropDeliverable2_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

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

#include "zPropertyIds.h"

/////////////////////////////////////////////////////////////////////////////
// Orientation change flags

//@topic Basic Properties Change Flags 
//@flag Z_CHANGE_COST_PROCESSING_TIME | Change the processing time.
#ifndef Z_CHANGE_COST_PROCESSING_TIME            
#define Z_CHANGE_COST_PROCESSING_TIME                0x0001
#endif 
//@flag Z_CHANGE_COST_IN_WORKLOAD_PERCENT | Change the input workload percent.
#ifndef Z_CHANGE_COST_IN_WORKLOAD_PERCENT        
#define Z_CHANGE_COST_IN_WORKLOAD_PERCENT            0x0002
#endif 
//@flag Z_CHANGE_COST_OUT_WORKLOAD_PERCENT | Change the output workload percent.
#ifndef Z_CHANGE_COST_OUT_WORKLOAD_PERCENT        
#define Z_CHANGE_COST_OUT_WORKLOAD_PERCENT            0x0004
#endif 
//@flag Z_CHANGE_COST_UNITARY_COST | Change the unitary cost.
#ifndef Z_CHANGE_COST_UNITARY_COST                    
#define Z_CHANGE_COST_UNITARY_COST                    0x0008
#endif 
//@flag Z_CHANGE_COST_CASE_DURATION | Change the stock duration.
#ifndef Z_CHANGE_COST_CASE_DURATION                    
#define Z_CHANGE_COST_CASE_DURATION                0x0010
#endif
//@flag Z_CHANGE_COST_TARGET_DURATION | Change the target duration.
#ifndef Z_CHANGE_COST_TARGET_DURATION                    
#define Z_CHANGE_COST_TARGET_DURATION                0x0020
#endif
//@flag Z_CHANGE_COST_GREENLINE_DURATION | Change the greenline duration.
#ifndef Z_CHANGE_COST_GREENLINE_DURATION                    
#define Z_CHANGE_COST_GREENLINE_DURATION            0x0040
#endif
//@flag Z_CHANGE_COST_CASE_DURATIONMAX | Change the stock duration duration.
#ifndef Z_CHANGE_COST_CASE_DURATIONMAX                    
#define Z_CHANGE_COST_CASE_DURATIONMAX                0x0080
#endif

/////////////////////////////////////////////////////////////////////////////
// Orientation property IDs

//@topic Basic Property Identifiers | Identify the properties
// contained by <c ZBBPCostPropertiesDeliverable2> objects. The ZBBPCostPropertiesDeliverable2
// class is a property container for these sub-properties. These
// identifiers are used in conjunction with the <c IODPropertyContainer>
// interface implemented by the orientation property container.
//@flag Z_COST_PROCESSING_TIME | Identifier for the processing time.
#ifndef Z_COST_PROCESSING_TIME            
#define Z_COST_PROCESSING_TIME                1
#endif 
//@flag Z_COST_IN_WORKLOAD_PERCENT | Identifier for the input workload percent.
#ifndef Z_COST_IN_WORKLOAD_PERCENT        
#define Z_COST_IN_WORKLOAD_PERCENT            2
#endif 
//@flag Z_COST_OUT_WORKLOAD_PERCENT | Identifier for the output workload percent.
#ifndef Z_COST_OUT_WORKLOAD_PERCENT        
#define Z_COST_OUT_WORKLOAD_PERCENT            3
#endif 
//@flag Z_COST_UNITARY_COST | Identifier for the unitary cost.
#ifndef Z_COST_UNITARY_COST                
#define Z_COST_UNITARY_COST                    4
#endif 
//@flag Z_COST_CASE_DURATION | Identifier for the stock duration.
#ifndef Z_COST_CASE_DURATION                    
#define Z_COST_CASE_DURATION                5
#endif
//@flag Z_COST_TARGET_DURATION | Identifier for the target duration.
#ifndef Z_COST_TARGET_DURATION                    
#define Z_COST_TARGET_DURATION                6
#endif
//@flag Z_COST_GREENLINE_DURATION | Identifier for the greenline duration.
#ifndef Z_COST_GREENLINE_DURATION                    
#define Z_COST_GREENLINE_DURATION            7
#endif
//@flag Z_COST_CASE_DURATIONMAX | Identifier for the stock duration maximum.
#ifndef Z_COST_CASE_DURATIONMAX                    
#define Z_COST_CASE_DURATIONMAX                8
#endif

/////////////////////////////////////////////////////////////////////////////
// Orientation defaults

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
// ZBBPCostPropertiesDeliverable2
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
//@base public | CPropertyContainer<lt>IODPropertyContainer, sfl::CODIntPropertyAccessor<lt>ZBBPCostPropertiesDeliverable2<gt> <gt>
//


class AFX_EXT_CLASS ZBBPCostPropertiesDeliverable2 : public CObject
{
    DECLARE_SERIAL(ZBBPCostPropertiesDeliverable2)

// Construction/Destruction
public:
    //@cmember
    /* Constructor. */
    ZBBPCostPropertiesDeliverable2();
    //@cmember
    /* Copy constructor. */
    ZBBPCostPropertiesDeliverable2(const ZBBPCostPropertiesDeliverable2& propBasic);
    //@cmember
    /* Destructor. */
    virtual ~ZBBPCostPropertiesDeliverable2();

// Attributes
protected:

    //@cmember
    /* the processing time. */
    double m_ProcessingTime;

    //@cmember
    /* the input workload percent. */
    float m_InWorkloadPercent;

    //@cmember
    /* the output workload percent. */
    float m_OutWorkloadPercent;

    //@cmember
    /* the unitary cost. */
    float m_UnitaryCost;

    //@cmember
    /* the stock duration. */
    double m_CaseDuration;

    //@cmember
    /* the stock duration maximum. */
    double m_CaseDurationMax;

    //@cmember
    /* the target duration. */
    double m_TargetDuration;

    //@cmember
    /* the greenline duration. */
    double m_GreenLineDuration;

public:
    //@cmember
    /* Gets the processing time. */
    double GetProcessingTime() const;

    //@cmember
    /* Sets the processing time. */
    void SetProcessingTime(const double value);

    //@cmember
    // Gets the input workload percent.
    float GetInWorkloadPercent() const;

    //@cmember
    // Sets the input workload percent.
    void SetInWorkloadPercent(const float value);

    //@cmember
    /* Gets the output workload percent. */
    float GetOutWorkloadPercent() const;

    //@cmember
    /* Sets the output workload percent. */
    void SetOutWorkloadPercent(const float value);

    //@cmember
    /* Gets the unitary cost. */
    float GetUnitaryCost() const;

    //@cmember
    /* Sets the unitary cost. */
    void SetUnitaryCost(const float value);

    //@cmember
    /* Gets the stock duration. */
    double GetCaseDuration() const;

    //@cmember
    /* Sets the stock duration. */
    void SetCaseDuration(const double value);

    //@cmember
    /* Gets the stock duration maximum. */
    double GetCaseDurationMax() const;

    //@cmember
    /* Sets the stock duration maximum. */
    void SetCaseDurationMax(const double value);

    //@cmember
    /* Gets the target duration. */
    double GetTargetDuration() const;

    //@cmember
    /* Sets the target duration. */
    void SetTargetDuration(const double value);

    //@cmember
    /* Gets the greenline duration. */
    double GetGreenLineDuration() const;

    //@cmember
    /* Sets the greenline duration. */
    void SetGreenLineDuration(const double value);

// Operations
public:
    //@cmember
    /* Assigns another property to this property. */
    ZBBPCostPropertiesDeliverable2& operator=(const ZBBPCostPropertiesDeliverable2& propBasic);

    //@cmember
    /* Compares two orientation properties. */
    BOOL operator==(const ZBBPCostPropertiesDeliverable2 propBasic) const;

    //@cmember
    /* Makes a copy of this properties object. */
    virtual ZBBPCostPropertiesDeliverable2* Dup();
    //@cmember
    /* Merges another set of properties with this one. */
    virtual void Merge(ZBBPCostPropertiesDeliverable2* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL);
    //@cmember
    /* Determines if another set of properties is equal to this one. */
    virtual BOOL IsEqual(ZBBPCostPropertiesDeliverable2* pProp);

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
    /* Gets the value of the given double property. */
    virtual BOOL GetValue(const int nPropId, double& dValue) const;

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
    /* Sets the value of the given double property. */
    virtual BOOL SetValue(const int nPropId, const double dValue);

    //@cmember
    /* Serializes the orientation properties. */
    virtual void Serialize(CArchive& ar);


// Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropertiesDeliverable2 inline methods

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline double ZBBPCostPropertiesDeliverable2::GetProcessingTime() const
{
    return m_ProcessingTime;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPCostPropertiesDeliverable2::SetProcessingTime(const double value)
{
    m_ProcessingTime = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline float ZBBPCostPropertiesDeliverable2::GetInWorkloadPercent() const
{
    return m_InWorkloadPercent;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPCostPropertiesDeliverable2::SetInWorkloadPercent(const float value)
{
    m_InWorkloadPercent = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline float ZBBPCostPropertiesDeliverable2::GetOutWorkloadPercent() const
{
    return m_OutWorkloadPercent;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPCostPropertiesDeliverable2::SetOutWorkloadPercent(const float value)
{
    m_OutWorkloadPercent = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline float ZBBPCostPropertiesDeliverable2::GetUnitaryCost() const
{
    return m_UnitaryCost;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPCostPropertiesDeliverable2::SetUnitaryCost(const float value)
{
    m_UnitaryCost = value;
}

//@mfunc Gets the stock duration.
//@rdesc stock duration value.
inline double ZBBPCostPropertiesDeliverable2::GetCaseDuration() const
{
    return m_CaseDuration;
}

//@mfunc Sets the stock duration.
//@rdesc void
//@parm stock duration value.
inline void ZBBPCostPropertiesDeliverable2::SetCaseDuration(const double value)
{
    m_CaseDuration = value;
}


//@mfunc Gets the stock duration maximum.
//@rdesc stock duration maximum value.
inline double ZBBPCostPropertiesDeliverable2::GetCaseDurationMax() const
{
    return m_CaseDurationMax;
}

//@mfunc Sets the stock duration maximum.
//@rdesc void
//@parm stock duration maximum value.
inline void ZBBPCostPropertiesDeliverable2::SetCaseDurationMax(const double value)
{
    m_CaseDurationMax = value;
}



//@mfunc Gets the target duration.
//@rdesc target duration value.
inline double ZBBPCostPropertiesDeliverable2::GetTargetDuration() const
{
    return m_TargetDuration;
}

//@mfunc Sets the target duration.
//@rdesc void
//@parm target duration value.
inline void ZBBPCostPropertiesDeliverable2::SetTargetDuration(const double value)
{
    m_TargetDuration = value;
}

//@mfunc Gets the greenline duration.
//@rdesc greenline duration value.
inline double ZBBPCostPropertiesDeliverable2::GetGreenLineDuration() const
{
    return m_GreenLineDuration;
}

//@mfunc Sets the greenline duration.
//@rdesc void
//@parm greenline duration value.
inline void ZBBPCostPropertiesDeliverable2::SetGreenLineDuration(const double value)
{
    m_GreenLineDuration = value;
}



//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline ZBBPCostPropertiesDeliverable2* ZBBPCostPropertiesDeliverable2::Dup()
{
    return new ZBBPCostPropertiesDeliverable2(*this);
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropertiesDeliverable2 member variable descriptions

/////////////////////////////////////////////////////////////////////////////


#endif // !defined(AFX_ZBBPZBBPCostPropDeliverable2_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
