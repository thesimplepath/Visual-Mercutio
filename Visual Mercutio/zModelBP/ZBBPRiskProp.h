// **************************************************************************************************************
// *                                           Classe ZBBPRiskProperties                                        *
// **************************************************************************************************************
// * JMR-MODIF - Le 20 mai 2007 - Ajout de la classe ZBBPRiskProperties.                                        *
// **************************************************************************************************************
// * Cette classe représente une propriété de type risque.                                                        *
// **************************************************************************************************************

#ifndef __ZBBPRiskProp_H__
#define __ZBBPRiskProp_H__

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

/////////////////////////////////////////////////////////////////////////////
// Process change flags

//@topic Risk Properties Change Flags | Different aspects of the Risk
// properties that can be changed individually.
//@flag Z_CHANGE_RISK_NAME | Change the name of this risk.
#define Z_CHANGE_RISK_NAME            0x0001
//@flag Z_CHANGE_RISK_DESC | Change the description for this risk.
#define Z_CHANGE_RISK_DESC            0x0002
//@flag Z_CHANGE_RISK_TYPE | Change the type for this risk.
#define Z_CHANGE_RISK_TYPE            0x0004
//@flag Z_CHANGE_RISK_IMPACT | Change the impact for this risk.
#define Z_CHANGE_RISK_IMPACT        0x0008
//@flag Z_CHANGE_RISK_PROBABILITY | Change the probability for this risk.
#define Z_CHANGE_RISK_PROBABILITY    0x0016
//@flag Z_CHANGE_RISK_SEVERITY | Change the severity for this risk.
#define Z_CHANGE_RISK_SEVERITY        0x0032
//@flag Z_CHANGE_RISK_UE | Change the unit estimate for this risk.
#define Z_CHANGE_RISK_UE            0x0064
//@flag Z_CHANGE_RISK_POA | Change the annual operational loss for this risk.
#define Z_CHANGE_RISK_POA            0x0128
//@flag Z_CHANGE_RISK_ACTION | Change the action for this risk.
#define Z_CHANGE_RISK_ACTION        0x0256

/////////////////////////////////////////////////////////////////////////////
// Fill property IDs

//@topic Fill Property Identifiers | Identify the properties contained by
// <ZBBPRiskProperties> objects. The ZBBPRiskProperties class is a property
// container for these sub-properties. These property identifiers are
// unique within a process properties container. These identifiers are used
// in conjunction with the <IODPropertyContainer> interface implemented
// by the process property container.
//@flag Z_RISK_NAME | Identifier for the name for this risk.
#define Z_RISK_NAME                    1
//@flag Z_RISK_DESC | Identifier for the description for this risk.
#define Z_RISK_DESC                    2
//@flag Z_RISK_TYPE | Identifier for the type for this risk.
#define Z_RISK_TYPE                    3
//@flag Z_RISK_IMPACT | Identifier for the impact for this risk.
#define Z_RISK_IMPACT                4
//@flag Z_RISK_PROBABILITY | Identifier for the probability for this risk.
#define Z_RISK_PROBABILITY            5
//@flag Z_RISK_SEVERITY | Identifier for the severity for this risk.
#define Z_RISK_SEVERITY                6
//@flag Z_RISK_UE | Identifier for the unit estimate for this risk.
#define Z_RISK_UE                    7
//@flag Z_RISK_POA | Identifier for the annual operational loss for this risk.
#define Z_RISK_POA                    8
//@flag Z_RISK_ACTION | Identifier for the action for this risk.
#define Z_RISK_ACTION                9

class AFX_EXT_CLASS ZBBPRiskProperties : public CObject
{
    DECLARE_SERIAL( ZBBPRiskProperties )

public:

    ZBBPRiskProperties();
    ZBBPRiskProperties( const ZBBPRiskProperties& propRisk );

    virtual ~ZBBPRiskProperties();

public:

    ZBBPRiskProperties& operator=( const ZBBPRiskProperties& propRisk );

    BOOL operator==( const ZBBPRiskProperties propRisk ) const;

    virtual ZBBPRiskProperties* Dup();

    virtual void Merge( ZBBPRiskProperties* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL );

    virtual BOOL IsEqual( ZBBPRiskProperties* pProp );

public:

    CString GetRiskName() const;
    void SetRiskName( LPCTSTR lpszValue );

    CString GetRiskDesc() const;
    void SetRiskDesc( LPCTSTR lpszValue );

    CString GetRiskType() const;
    void SetRiskType( LPCTSTR lpszValue );

    int GetRiskImpact() const;
    void SetRiskImpact( const int value );

    int GetRiskProbability() const;
    void SetRiskProbability( const int value );

    int GetRiskSeverity() const;
    void SetRiskSeverity( const int value );

    float GetRiskUE() const;
    void SetRiskUE( const float value );

    float GetRiskPOA() const;
    void SetRiskPOA( const float value );

    bool GetRiskAction() const;
    void SetRiskAction( const bool value );

    /////////////////////////////////////////////////////////////////////////
    // GetValue and SetValue functions

    virtual BOOL GetValue( const int nPropId, CString& strValue ) const;
    virtual BOOL GetValue( const int nPropId, int& nValue ) const;
    virtual BOOL GetValue( const int nPropId, UINT& nValue ) const;
    virtual BOOL GetValue( const int nPropId, DWORD& dwValue ) const;
    virtual BOOL GetValue( const int nPropId, float& fValue ) const;
    virtual BOOL GetValue( const int nPropId, bool& bValue ) const;
    virtual BOOL SetValue( const int nPropId, LPCTSTR lpszValue );
    virtual BOOL SetValue( const int nPropId, const int nValue );
    virtual BOOL SetValue( const int nPropId, const UINT nValue );
    virtual BOOL SetValue( const int nPropId, const DWORD dwValue );
    virtual BOOL SetValue( const int nPropId, const float fValue );
    virtual BOOL SetValue( const int nPropId, const bool bValue );

    virtual void Serialize( CArchive& ar );

private:

    // Fonctions internes pour les conversions de valeurs.
    void SetRiskNameEx( const CString value );
    void SetRiskDescEx( const CString value );
    void SetRiskTypeEx( const CString value );

public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

    CString    m_RiskName;
    CString    m_RiskDesc;
    CString    m_RiskType;

    int        m_RiskImpact;
    int        m_RiskProbability;
    int        m_RiskSeverity;

    float    m_RiskUE;
    float    m_RiskPOA;

    bool    m_RiskAction;
};

// Cette fonction permet d'effectuer un duplicata de l'objet instancié.
inline ZBBPRiskProperties* ZBBPRiskProperties::Dup()
{
    return new ZBBPRiskProperties( *this );
}

// Obtient le nom du risque.
inline CString ZBBPRiskProperties::GetRiskName() const
{
    return m_RiskName;
}

// Obtient la description du risque.
inline CString ZBBPRiskProperties::GetRiskDesc() const
{
    return m_RiskDesc;
}

// Obtient le type du risque.
inline CString ZBBPRiskProperties::GetRiskType() const
{
    return m_RiskType;
}

// Obtient la valeur de l'impact du risque.
inline int ZBBPRiskProperties::GetRiskImpact() const
{
    return m_RiskImpact;
}

// Indique la valeur de l'impact du risque.
inline void ZBBPRiskProperties::SetRiskImpact( const int value )
{
    m_RiskImpact = value;
}

// Obtient la valeur de la probabilité du risque.
inline int ZBBPRiskProperties::GetRiskProbability() const
{
    return m_RiskProbability;
}

// Indique la valeur de la probabilité du risque.
inline void ZBBPRiskProperties::SetRiskProbability( const int value )
{
    m_RiskProbability = value;
}

// Obtient la valeur de la sévérité du risque.
inline int ZBBPRiskProperties::GetRiskSeverity() const
{
    return m_RiskSeverity;
}

// Indique la valeur de la sévérité du risque.
inline void ZBBPRiskProperties::SetRiskSeverity( const int value )
{
    m_RiskSeverity = value;
}

// Obtient la valeur de l'estimation unitaire du risque.
inline float ZBBPRiskProperties::GetRiskUE() const
{
    return m_RiskUE;
}

// Indique la valeur de l'estimation unitaire du risque.
inline void ZBBPRiskProperties::SetRiskUE( const float value )
{
    m_RiskUE = value;
}

// Obtient la valeur de la perte opérationnelle annuelle du risque.
inline float ZBBPRiskProperties::GetRiskPOA() const
{
    return m_RiskPOA;
}

// Indique la valeur de la perte opérationnelle annuelle du risque.
inline void ZBBPRiskProperties::SetRiskPOA( const float value )
{
    m_RiskPOA = value;
}

// Obtient la valeur de l'action du risque.
inline bool ZBBPRiskProperties::GetRiskAction() const
{
    return m_RiskAction;
}

// Indique la valeur de l'action du risque.
inline void ZBBPRiskProperties::SetRiskAction( const bool value )
{
    m_RiskAction = value;
}

#endif //__ZBBPRiskProp_H__