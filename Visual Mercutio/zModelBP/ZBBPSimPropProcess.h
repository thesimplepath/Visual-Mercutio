/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropProcess.h : Declaration of ZBBPSimPropertiesProcess
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
// Description:  ZBBPSimPropertiesProcess simulation properties for process
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBBPZBBPSimPropProcess_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPZBBPSimPropProcess_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

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

#include "ZBBPAnnualNumberProp.h"
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

// JMR-MODIF - Le 28 septembre 2005 - Ajout de la décoration unicode _T( ), nettoyage du code inutilisé.

/////////////////////////////////////////////////////////////////////////////
// Orientation change flags

//@topic Basic Properties Change Flags 
//@flag Z_CHANGE_SIM_PROCESS_WORKLOAD_FORECAST | Change the process workload forecast.
#define Z_CHANGE_SIM_PROCESS_WORKLOAD_FORECAST            0x0001
//@flag Z_CHANGE_SIM_PROCESS_COST_FORECAST | Change the process cost forecast.
#define Z_CHANGE_SIM_PROCESS_COST_FORECAST                0x0002
// JMR-MODIF - Le 14 mars 2006 - Ajout de la déclaration pour la gestion du coût HMO.
#define Z_CHANGE_SIM_PROCESS_COST_HMO                    0x0004

/////////////////////////////////////////////////////////////////////////////
// Orientation property IDs

//@topic Basic Property Identifiers | Identify the properties
// contained by <c ZBBPSimPropertiesProcess> objects. The ZBBPSimPropertiesProcess
// class is a property container for these sub-properties. These
// identifiers are used in conjunction with the <c IODPropertyContainer>
// interface implemented by the orientation property container.
//@flag Z_SIM_PROCESS_WORKLOAD_FORECAST | Identifier for the process workload forecast.
#define Z_SIM_PROCESS_WORKLOAD_FORECAST                    1
//@flag Z_SIM_PROCESS_COST_FORECAST | Identifier for the process cost forecast.
#define Z_SIM_PROCESS_COST_FORECAST                        2
// JMR-MODIF - Le 14 mars 2006 - Ajout de la définition pour le coût HMO.
#define Z_SIM_PROCESS_COST_HMO                            3
//@flag Z_SIM_PROCESS_SUM_DELIVERIES | Identifier for the sum of the deliveries.
#define Z_SIM_PROCESS_SUM_DELIVERIES                    4
//@flag Z_SIM_PROCESS_WORKLOAD_BY_DELIVERIES | Identifier for the workload by deliveries.
#define Z_SIM_PROCESS_WORKLOAD_BY_DELIVERIES            5
//@flag Z_SIM_PROCESS_COST_BY_DELIVERIES | Identifier for the cost by deliveries.
#define Z_SIM_PROCESS_COST_BY_DELIVERIES                6

/////////////////////////////////////////////////////////////////////////////
// ZBBPSimPropertiesProcess
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
//@base public | CPropertyContainer<lt>IODPropertyContainer, sfl::CODIntPropertyAccessor<lt>ZBBPSimPropertiesProcess<gt> <gt>
//
class AFX_EXT_CLASS ZBBPSimPropertiesProcess : public CObject
{
    DECLARE_SERIAL( ZBBPSimPropertiesProcess )

// Construction/Destruction
public:

    //@cmember
    /* Constructor. */
    ZBBPSimPropertiesProcess();

    //@cmember
    /* Copy constructor. */
    ZBBPSimPropertiesProcess( const ZBBPSimPropertiesProcess& propBasic );

    //@cmember
    /* Destructor. */
    virtual ~ZBBPSimPropertiesProcess();

    /////////////////////////////////////////////////////////////////////////
    // Operations

    //@cmember
    /* Assigns another property to this property. */
    ZBBPSimPropertiesProcess& operator=( const ZBBPSimPropertiesProcess& propBasic );

    //@cmember
    /* Compares two orientation properties. */
    BOOL operator==( const ZBBPSimPropertiesProcess propBasic ) const;

    //@cmember
    /* Makes a copy of this properties object. */
    virtual ZBBPSimPropertiesProcess* Dup();
    //@cmember
    /* Merges another set of properties with this one. */
    virtual void Merge( ZBBPSimPropertiesProcess* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL );
    //@cmember
    /* Determines if another set of properties is equal to this one. */
    virtual BOOL IsEqual( ZBBPSimPropertiesProcess* pProp );

    //@cmember
    /* Gets the process workload forecast. */
    ZBBPAnnualNumberProperties& GetProcessWorkloadForecast();

    //@cmember
    /* Sets the process workload forecast. */
    void SetProcessWorkloadForecast( const double value );

    //@cmember
    /* Gets the process cost forecast. */
    ZBBPAnnualNumberProperties& GetProcessCostForecast();

    //@cmember
    /* Sets the process cost forecast. */
    void SetProcessCostForecast( const double value );

    // JMR-MODIF - Le 14 mars 2006 - Ajout de la fonction pour l'obtention du coût HMO.
    ZBBPAnnualNumberProperties& GetProcessCost();

    // JMR-MODIF - Le 14 mars 2006 - Ajout de la fonction pour la déclaration du coût HMO.
    void SetProcessCost( const double value );

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
    /* the process workload forecast. */
    ZBBPAnnualNumberProperties    m_ProcessWorkloadForecast;

    //@cmember
    /* the process cost forecast. */
    ZBBPAnnualNumberProperties    m_ProcessCostForecast;

    // JMR-MODIF - Le 14 mars 2006 - Ajout de la variable m_ProcessCost, pour la gestion du coût HMO.
    ZBBPAnnualNumberProperties    m_ProcessCost;
};

/////////////////////////////////////////////////////////////////////////////

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline ZBBPAnnualNumberProperties& ZBBPSimPropertiesProcess::GetProcessWorkloadForecast()
{
    return m_ProcessWorkloadForecast;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBPSimPropertiesProcess::SetProcessWorkloadForecast( const double value )
{
    m_ProcessWorkloadForecast = value;
}

//@mfunc Gets the process cost forecast.
//@rdesc process cost forecast.
inline ZBBPAnnualNumberProperties& ZBBPSimPropertiesProcess::GetProcessCostForecast()
{
    return m_ProcessCostForecast;
}

//@mfunc Sets the process cost forecast.
//@rdesc void
//@parm process cost forecast.
inline void ZBBPSimPropertiesProcess::SetProcessCostForecast( const double value )
{
    m_ProcessCostForecast = value;
}

// JMR-MODIF - Le 14 mars 2006 - Ajout de la fonction pour l'obtention du coût HMO.
inline ZBBPAnnualNumberProperties& ZBBPSimPropertiesProcess::GetProcessCost()
{
    return m_ProcessCost;
}

// JMR-MODIF - Le 14 mars 2006 - Ajout de la fonction pour la déclaration du coût HMO.
inline void ZBBPSimPropertiesProcess::SetProcessCost( const double value )
{
    m_ProcessCost = value;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline ZBBPSimPropertiesProcess* ZBBPSimPropertiesProcess::Dup()
{
    return new ZBBPSimPropertiesProcess( *this );
}

#endif // !defined(AFX_ZBBPZBBPSimPropProcess_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)