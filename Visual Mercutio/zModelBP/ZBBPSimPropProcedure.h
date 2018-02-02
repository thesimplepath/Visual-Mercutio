/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropProcedure.h : Declaration of ZBBPSimPropertiesProcedure
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
// Description:  ZBBPSimPropertiesProcedure simulation properties for procedure
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBBPZBBPSimPropProcedure_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPZBBPSimPropProcedure_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

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
#include "ZBBPAnnualNumberProp.h"

#ifdef _ZMODELBPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 14 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Orientation change flags

//@topic Basic Properties Change Flags 
//@flag Z_CHANGE_SIM_PROCEDURE_ACTIVATION | Change the procedure activation.
#define Z_CHANGE_SIM_PROCEDURE_ACTIVATION					0x0001
//@flag Z_CHANGE_SIM_PROCEDURE_COST | Change the standard procedure time.
#define Z_CHANGE_SIM_PROCEDURE_COST							0x0002
//@flag Z_CHANGE_SIM_PROCEDURE_WORKLOAD_FORECAST | Change the procedure workload forecast.
#define Z_CHANGE_SIM_PROCEDURE_WORKLOAD_FORECAST			0x0004
//@flag Z_CHANGE_SIM_PROCEDURE_COST_FORECAST | Change the procedure cost forecast.
#define Z_CHANGE_SIM_PROCEDURE_COST_FORECAST				0x0008
//@flag Z_CHANGE_SIM_PROCEDURE_WORKLOAD_P_ACTIV_FORECAST | Change the procedure workload per activity forecast.
#define Z_CHANGE_SIM_PROCEDURE_WORKLOAD_P_ACTIV_FORECAST	0x0010
//@flag Z_CHANGE_SIM_PROCEDURE_COST_P_ACTIV_FORECAST | Change the procedure cost per activity forecast.
#define Z_CHANGE_SIM_PROCEDURE_COST_P_ACTIV_FORECAST		0x0020

/////////////////////////////////////////////////////////////////////////////
// Orientation property IDs

//@topic Basic Property Identifiers | Identify the properties
// contained by <c ZBBPSimPropertiesProcedure> objects. The ZBBPSimPropertiesProcedure
// class is a property container for these sub-properties. These
// identifiers are used in conjunction with the <c IODPropertyContainer>
// interface implemented by the orientation property container.
//@flag Z_SIM_PROCEDURE_ACTIVATION | Identifier for the procedure activation.
#define Z_SIM_PROCEDURE_ACTIVATION							1
//@flag Z_SIM_PROCEDURE_COST | Identifier for the standard procedure time.
#define Z_SIM_PROCEDURE_COST								2
//@flag Z_SIM_PROCEDURE_WORKLOAD_FORECAST | Identifier for the procedure workload forecast.
#define Z_SIM_PROCEDURE_WORKLOAD_FORECAST					3
//@flag Z_SIM_PROCEDURE_COST_FORECAST | Identifier for the procedure cost forecast.
#define Z_SIM_PROCEDURE_COST_FORECAST						4
//@flag Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV | Identifier for the procedure workload per activity forecast.
#define Z_SIM_PROCEDURE_WORKLOAD_P_ACTIV					5
//@flag Z_SIM_PROCEDURE_COST_P_ACTIV | Identifier for the procedure cost per activity forecast.
#define Z_SIM_PROCEDURE_COST_P_ACTIV						6

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesProcedure
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

class AFX_EXT_CLASS ZBBPSimPropertiesProcedure : public CObject
{
	DECLARE_SERIAL( ZBBPSimPropertiesProcedure )

// Construction/Destruction
public:

	//@cmember
	/* Constructor. */
	ZBBPSimPropertiesProcedure();

	//@cmember
	/* Copy constructor. */
	ZBBPSimPropertiesProcedure( const ZBBPSimPropertiesProcedure& propBasic );

	//@cmember
	/* Destructor. */
	virtual ~ZBBPSimPropertiesProcedure();

// Operations
public:

	//@cmember
	/* Assigns another property to this property. */
	ZBBPSimPropertiesProcedure& operator=( const ZBBPSimPropertiesProcedure& propBasic );

	//@cmember
	/* Compares two orientation properties. */
	BOOL operator==( const ZBBPSimPropertiesProcedure propBasic ) const;

	//@cmember
	/* Makes a copy of this properties object. */
	virtual ZBBPSimPropertiesProcedure* Dup();

	//@cmember
	/* Merges another set of properties with this one. */
	virtual void Merge( ZBBPSimPropertiesProcedure* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL );

	//@cmember
	/* Determines if another set of properties is equal to this one. */
	virtual BOOL IsEqual( ZBBPSimPropertiesProcedure* pProp );

public:

	//@cmember
	/* Gets the procedure activation. */
	ZBBPAnnualNumberProperties& GetProcedureActivation();

	//@cmember
	/* Sets the procedure activation. */
	void SetProcedureActivation( const double value );

	//@cmember
	/* Gets the standard procedure time. */
	ZBBPAnnualNumberProperties& GetProcedureCost();

	//@cmember
	/* Sets the standard procedure time. */
	void SetProcedureCost( const double value );

	//@cmember
	/* Gets the procedure workload forecast. */
	ZBBPAnnualNumberProperties& GetProcedureWorkloadForecast();

	//@cmember
	/* Sets the procedure workload forecast. */
	void SetProcedureWorkloadForecast( const double value );

	//@cmember
	/* Gets the procedure cost forecast. */
	ZBBPAnnualNumberProperties& GetProcedureCostForecast();

	//@cmember
	/* Sets the procedure cost forecast. */
	void SetProcedureCostForecast( const double value );

	//@cmember
	/* Gets the procedure workload per activity forecast. */
	double GetProcedureWorkloadPerActivity() const;

	//@cmember
	/* Sets the procedure workload per activity forecast. */
	void SetProcedureWorkloadPerActivity( const double value );

	//@cmember
	/* Gets the procedure cost per activity forecast. */
	double GetProcedureCostPerActivity() const;

	//@cmember
	/* Sets the procedure cost per activity forecast. */
	void SetProcedureCostPerActivity( const double value );

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
	/* the procedure activation. */
	ZBBPAnnualNumberProperties	m_ProcedureActivation;

	//@cmember
	/* the standard procedure time. */
	ZBBPAnnualNumberProperties	m_ProcedureCost;

	//@cmember
	/* the procedure workload forecast. */
	ZBBPAnnualNumberProperties	m_ProcedureWorkloadForecast;

	//@cmember
	/* the procedure cost forecast. */
	ZBBPAnnualNumberProperties	m_ProcedureCostForecast;

	//@cmember
	/* the procedure workload per activity forecast. */
	double						m_ProcedureWorkloadPerActivity;

	//@cmember
	/* the procedure cost per activity forecast. */
	double						m_ProcedureCostPerActivity;
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesProcedure inline methods

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline ZBBPAnnualNumberProperties& ZBBPSimPropertiesProcedure::GetProcedureActivation()
{
	return m_ProcedureActivation;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPSimPropertiesProcedure::SetProcedureActivation( const double value )
{
	m_ProcedureActivation = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline ZBBPAnnualNumberProperties& ZBBPSimPropertiesProcedure::GetProcedureCost()
{
	return m_ProcedureCost;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPSimPropertiesProcedure::SetProcedureCost( const double value )
{
	m_ProcedureCost = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline ZBBPAnnualNumberProperties& ZBBPSimPropertiesProcedure::GetProcedureWorkloadForecast()
{
	return m_ProcedureWorkloadForecast;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPSimPropertiesProcedure::SetProcedureWorkloadForecast( const double value )
{
	m_ProcedureWorkloadForecast = value;
}

//@mfunc Gets the procedure cost forecast.
//@rdesc procedure cost forecast.
inline ZBBPAnnualNumberProperties& ZBBPSimPropertiesProcedure::GetProcedureCostForecast()
{
	return m_ProcedureCostForecast;
}

//@mfunc Sets the procedure cost forecast.
//@rdesc void
//@parm procedure cost forecast.
inline void ZBBPSimPropertiesProcedure::SetProcedureCostForecast( const double value )
{
	m_ProcedureCostForecast = value;
}


//@mfunc Gets the procedure workload per activity forecast.
//@rdesc procedure workload per activity forecast.
inline double ZBBPSimPropertiesProcedure::GetProcedureWorkloadPerActivity() const
{
	return m_ProcedureWorkloadPerActivity;
}

//@mfunc Sets the procedure workload per activity forecast.
//@rdesc void
//@parm procedure workload per activity forecast.
inline void ZBBPSimPropertiesProcedure::SetProcedureWorkloadPerActivity( const double value )
{
	m_ProcedureWorkloadPerActivity = value;
}


//@mfunc Gets the procedure cost per activity forecast.
//@rdesc procedure cost per activity forecast.
inline double ZBBPSimPropertiesProcedure::GetProcedureCostPerActivity() const
{
	return m_ProcedureCostPerActivity;
}

//@mfunc Sets the procedure cost per activity forecast.
//@rdesc void
//@parm procedure cost per activity forecast.
inline void ZBBPSimPropertiesProcedure::SetProcedureCostPerActivity( const double value )
{
	m_ProcedureCostPerActivity = value;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline ZBBPSimPropertiesProcedure* ZBBPSimPropertiesProcedure::Dup()
{
	return new ZBBPSimPropertiesProcedure(*this);
}

#endif // !defined(AFX_ZBBPZBBPSimPropProcedure_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)