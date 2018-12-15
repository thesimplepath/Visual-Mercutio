/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropProcedure.h : Declaration of ZBBPCostPropertiesProcedure
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
// Description:  ZBBPCostPropertiesProcedure cost properties for procedure
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_ZBBPZBBPCostPropProcedure_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPZBBPCostPropProcedure_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

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
//@flag Z_CHANGE_COST_MULTIPLIER | Change the cost multiplier factor.
#define Z_CHANGE_COST_MULTIPLIER                    0x0001
//@flag Z_CHANGE_COST_PROCESSING_TIME | Change the processing time.
#define Z_CHANGE_COST_PROCESSING_TIME                0x0002
//@flag Z_CHANGE_COST_UNITARY_COST | Change the unitary cost.
#define Z_CHANGE_COST_UNITARY_COST                    0x0004

/*
//@flag Z_CHANGE_COST_IN_WORKLOAD_PERCENT | Change the input workload percent.
#define Z_CHANGE_COST_IN_WORKLOAD_PERCENT            0x0004
//@flag Z_CHANGE_COST_OUT_WORKLOAD_PERCENT | Change the output workload percent.
#define Z_CHANGE_COST_OUT_WORKLOAD_PERCENT            0x0008
*/

/////////////////////////////////////////////////////////////////////////////
// Orientation property IDs

//@topic Basic Property Identifiers | Identify the properties
// contained by <c ZBBPCostPropertiesProcedure> objects. The ZBBPCostPropertiesProcedure
// class is a property container for these sub-properties. These
// identifiers are used in conjunction with the <c IODPropertyContainer>
// interface implemented by the orientation property container.
//@flag Z_COST_MULTIPLIER | Identifier for the cost multiplier factor.
#define Z_COST_MULTIPLIER                    1
//@flag Z_COST_PROCESSING_TIME | Identifier for the processing time.
#define Z_COST_PROCESSING_TIME                2
//@flag Z_COST_UNITARY_COST | Identifier for the unitary cost.
#define Z_COST_UNITARY_COST                    3

/*
//@flag Z_COST_IN_WORKLOAD_PERCENT | Identifier for the input workload percent.
#define Z_COST_IN_WORKLOAD_PERCENT            3
//@flag Z_COST_OUT_WORKLOAD_PERCENT | Identifier for the output workload percent.
#define Z_COST_OUT_WORKLOAD_PERCENT            4
*/

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
// ZBBPCostPropertiesProcedure
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
//@base public | CPropertyContainer<lt>IODPropertyContainer, sfl::CODIntPropertyAccessor<lt>ZBBPCostPropertiesProcedure<gt> <gt>
//


class AFX_EXT_CLASS ZBBPCostPropertiesProcedure : public CODIntProperty, 
                                        public sfl::CPropertyContainer<IODPropertyContainer, CODPropertyAccessor<ZBBPCostPropertiesProcedure> >
{
    DECLARE_SERIAL(ZBBPCostPropertiesProcedure)

// Construction/Destruction
public:
    //@cmember
    /* Constructor. */
    ZBBPCostPropertiesProcedure(int nId = ZS_BP_PROP_PROCEDURE_COST);
    //@cmember
    /* Copy constructor. */
    ZBBPCostPropertiesProcedure(const ZBBPCostPropertiesProcedure& propBasic);
    //@cmember
    /* Destructor. */
    virtual ~ZBBPCostPropertiesProcedure();

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


public:
    //@cmember
    /* Gets the cost multiplier factor. */
    float GetMultiplier() const;

    //@cmember
    /* Sets the cost multiplier factor. */
    void SetMultiplier(const float value);

    //@cmember
    /* Gets the processing time. */
    double GetProcessingTime() const;

    //@cmember
    /* Sets the processing time. */
    void SetProcessingTime(const double value);

    //@cmember
    /* Gets the unitary cost. */
    float GetUnitaryCost() const;

    //@cmember
    /* Sets the unitary cost. */
    void SetUnitaryCost(const float value);


// Operations
public:
    //@cmember
    /* Compare the property identifier with another identifier. */
    virtual BOOL CompareId(const int nId) const;

    //@cmember
    /* Assigns another property to this property. */
    ZBBPCostPropertiesProcedure& operator=(const ZBBPCostPropertiesProcedure& propBasic);

    //@cmember
    /* Compares two orientation properties. */
    BOOL operator==(const ZBBPCostPropertiesProcedure propBasic) const;

    //@cmember
    /* Makes a copy of this properties object. */
    virtual CODProperty* Dup();
    //@cmember
    /* Merges another set of properties with this one. */
    virtual void Merge(CODProperty* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL);
    //@cmember
    /* Determines if another set of properties is equal to this one. */
    virtual BOOL IsEqual(CODProperty* pProp);

    /////////////////////////////////////////////////////////////////////////
    // IODObject interface

    BEGIN_GUID_MAP(ZBBPCostPropertiesProcedure)
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

    /////////////////////////////////////////////////////////////////////////
    // Internal helper functions subject to change.
private:

    /* Registers the basic property meta-data. */
    bool RegisterProperties();

// Implementation
public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropertiesProcedure inline methods

//@mfunc Add a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPCostPropertiesProcedure::AddRef()
{
    return CODIntProperty::AddRef();
}

//@mfunc Release a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPCostPropertiesProcedure::Release()
{
    return CODIntProperty::Release();
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline float ZBBPCostPropertiesProcedure::GetMultiplier() const
{
    return m_Multiplier;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPCostPropertiesProcedure::SetMultiplier(const float value)
{
    m_Multiplier = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline double ZBBPCostPropertiesProcedure::GetProcessingTime() const
{
    return m_ProcessingTime;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPCostPropertiesProcedure::SetProcessingTime(const double value)
{
    m_ProcessingTime = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline float ZBBPCostPropertiesProcedure::GetUnitaryCost() const
{
    return m_UnitaryCost;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPCostPropertiesProcedure::SetUnitaryCost(const float value)
{
    m_UnitaryCost = value;
}


//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline CODProperty* ZBBPCostPropertiesProcedure::Dup()
{
    return new ZBBPCostPropertiesProcedure(*this);
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPCostPropertiesProcedure member variable descriptions

/////////////////////////////////////////////////////////////////////////////


#endif // !defined(AFX_ZBBPZBBPCostPropProcedure_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
