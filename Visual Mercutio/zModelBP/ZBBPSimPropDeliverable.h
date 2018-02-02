/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropDeliverable.h : Declaration of ZBBPSimPropertiesDeliverable
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
// Created:		 05/2001
// Description:  ZBBPSimPropertiesDeliverable simulation properties for deliverables
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_ZBBPZBBPSimPropDeliverable_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPZBBPSimPropDeliverable_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

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
#include "ZBBPAnnualNumberProp.h"

/////////////////////////////////////////////////////////////////////////////
// Orientation change flags

//@topic Basic Properties Change Flags 
//@flag Z_CHANGE_SIM_DELIV_COST | Change the deliverable cost.
#define Z_CHANGE_SIM_DELIV_COST					0x0001
//@flag Z_CHANGE_SIM_DELIV_WORKLOAD_FORECAST | Change the deliverable workload forecast.
#define Z_CHANGE_SIM_DELIV_WORKLOAD_FORECAST	0x0002

/////////////////////////////////////////////////////////////////////////////
// Orientation property IDs

//@topic Basic Property Identifiers | Identify the properties
// contained by <c ZBBPSimPropertiesDeliverable> objects. The ZBBPSimPropertiesDeliverable
// class is a property container for these sub-properties. These
// identifiers are used in conjunction with the <c IODPropertyContainer>
// interface implemented by the orientation property container.
//@flag Z_SIM_DELIV_COST | Identifier for the deliverable cost.
#define Z_SIM_DELIV_COST					1
//@flag Z_SIM_DELIV_WORKLOAD_FORECAST | Identifier for the deliverable workload forecast.
#define Z_SIM_DELIV_WORKLOAD_FORECAST		2

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
// ZBBPSimPropertiesDeliverable
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
//@base public | CObject
//


class AFX_EXT_CLASS ZBBPSimPropertiesDeliverable : public CObject
{
	DECLARE_SERIAL(ZBBPSimPropertiesDeliverable)

// Construction/Destruction
public:
	//@cmember
	/* Constructor. */
	ZBBPSimPropertiesDeliverable();
	//@cmember
	/* Copy constructor. */
	ZBBPSimPropertiesDeliverable(const ZBBPSimPropertiesDeliverable& propBasic);
	//@cmember
	/* Destructor. */
	virtual ~ZBBPSimPropertiesDeliverable();

// Attributes
protected:

	//@cmember
	/* the deliverable cost. */
	ZBBPAnnualNumberProperties m_Cost;

	//@cmember
	/* the deliverable workload forecast. */
	ZBBPAnnualNumberProperties m_WorkloadForecast;

public:
	//@cmember
	/* Gets the deliverable cost. */
	ZBBPAnnualNumberProperties& GetCost();

	//@cmember
	/* Sets the deliverable cost. */
	void SetCost(const double value);

	//@cmember
	/* Gets the deliverable workload forecast. */
	ZBBPAnnualNumberProperties& GetWorkloadForecast();

	//@cmember
	/* Sets the deliverable workload forecast. */
	void SetWorkloadForecast(const double value);


// Operations
public:

	//@cmember
	/* Assigns another property to this property. */
	ZBBPSimPropertiesDeliverable& operator=(const ZBBPSimPropertiesDeliverable& propBasic);

	//@cmember
	/* Compares two orientation properties. */
	BOOL operator==(const ZBBPSimPropertiesDeliverable propBasic) const;

	//@cmember
	/* Makes a copy of this properties object. */
	virtual ZBBPSimPropertiesDeliverable* Dup();
	//@cmember
	/* Merges another set of properties with this one. */
	virtual void Merge(ZBBPSimPropertiesDeliverable* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL);
	//@cmember
	/* Determines if another set of properties is equal to this one. */
	virtual BOOL IsEqual(ZBBPSimPropertiesDeliverable* pProp);

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
// ZBBPSimPropertiesDeliverable inline methods

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline ZBBPAnnualNumberProperties& ZBBPSimPropertiesDeliverable::GetCost()
{
	return m_Cost;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPSimPropertiesDeliverable::SetCost(const double value)
{
	m_Cost = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline ZBBPAnnualNumberProperties& ZBBPSimPropertiesDeliverable::GetWorkloadForecast()
{
	return m_WorkloadForecast;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPSimPropertiesDeliverable::SetWorkloadForecast(const double value)
{
	m_WorkloadForecast = value;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline ZBBPSimPropertiesDeliverable* ZBBPSimPropertiesDeliverable::Dup()
{
	return new ZBBPSimPropertiesDeliverable(*this);
}

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesDeliverable member variable descriptions

/////////////////////////////////////////////////////////////////////////////


#endif // !defined(AFX_ZBBPZBBPSimPropDeliverable_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
