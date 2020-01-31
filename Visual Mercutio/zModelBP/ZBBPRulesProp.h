// **************************************************************************************************************
// *                                        Classe ZBBPRulesProp                                                *
// **************************************************************************************************************
// * JMR-MODIF - Le 20 novembre 2006 - Ajout de la classe ZBBPRulesProp.                                        *
// **************************************************************************************************************
// * Cette classe représente une propriété de type règle.                                                        *
// **************************************************************************************************************

#ifndef __ZBBPRulesProp_H__
#define __ZBBPRulesProp_H__

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

//@topic Process Properties Change Flags | Different aspects of the Process
// properties that can be changed individually.
//@flag Z_CHANGE_RULE_NAME | Change the name of this rule.
#define Z_CHANGE_RULE_NAME            0x0001

//@flag Z_CHANGE_RULE_DESCRIPTION | Change the description for this rule.
#define Z_CHANGE_RULE_DESCRIPTION    0x0002

//@flag Z_CHANGE_RULE_GUID | Change the GUID for this rule.
#define Z_CHANGE_RULE_GUID            0x0004

/////////////////////////////////////////////////////////////////////////////
// Fill property IDs

//@topic Fill Property Identifiers | Identify the properties contained by
// <c ZBBPRulesProperties> objects. The ZBBPRulesProperties class is a property
// container for these sub-properties. These property identifiers are
// unique within a process properties container. These identifiers are used
// in conjunction with the <c IODPropertyContainer> interface implemented
// by the process property container.
//@flag Z_RULE_NAME | Identifier for the name of this Rule.
#define Z_RULE_NAME                1

//@flag Z_RULE_DESCRIPTION | Identifier for the description for this rule.
#define Z_RULE_DESCRIPTION        2

//@flag Z_RULE_IDENTIFIER | Identifier for the rule ID.
#define Z_RULE_IDENTIFIER        3

class AFX_EXT_CLASS ZBBPRulesProperties : public CObject
{
    DECLARE_SERIAL( ZBBPRulesProperties )

public:

    ZBBPRulesProperties();
    ZBBPRulesProperties( const ZBBPRulesProperties& propProcess );

    virtual ~ZBBPRulesProperties();

public:

    ZBBPRulesProperties& operator=( const ZBBPRulesProperties& propProcess );

    BOOL operator==( const ZBBPRulesProperties propProcess ) const;

    virtual ZBBPRulesProperties* Dup() const;

    virtual void Merge( ZBBPRulesProperties* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL );

    virtual BOOL IsEqual( ZBBPRulesProperties* pProp );

public:

    CString GetRuleName() const;
    void SetRuleName( LPCTSTR lpszValue );

    CString GetRuleDescription() const;
    void SetRuleDescription( LPCTSTR lpszValue );

    CString GetRuleGUID() const;
    void SetRuleGUID( LPCTSTR lpszValue );

    /////////////////////////////////////////////////////////////////////////
    // GetValue and SetValue functions

    virtual BOOL GetValue( const int nPropId, CString& strValue ) const;
    virtual BOOL GetValue( const int nPropId, int& nValue ) const;
    virtual BOOL GetValue( const int nPropId, UINT& nValue ) const;
    virtual BOOL GetValue( const int nPropId, DWORD& dwValue ) const;
    virtual BOOL GetValue( const int nPropId, float& fValue ) const;
    virtual BOOL SetValue( const int nPropId, LPCTSTR lpszValue );
    virtual BOOL SetValue( const int nPropId, const int nValue );
    virtual BOOL SetValue( const int nPropId, const UINT nValue );
    virtual BOOL SetValue( const int nPropId, const DWORD dwValue );
    virtual BOOL SetValue( const int nPropId, const float fValue );

    virtual void Serialize( CArchive& ar );

private:

    void SetRuleNameEx( const CString value );
    void SetRuleDescriptionEx( const CString value );
    void SetRuleGUIDEx( const CString value );

public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

    CString m_RuleName;
    CString m_RuleDescription;
    CString m_RuleGUID;
};

// Cette fonction permet d'effectuer un duplicata de l'objet instancié.
inline ZBBPRulesProperties* ZBBPRulesProperties::Dup() const
{
    return new ZBBPRulesProperties( *this );
}

// Obtient le nom de la règle
inline CString ZBBPRulesProperties::GetRuleName() const
{
    return m_RuleName;
}

// Obtient la description de la règle
inline CString ZBBPRulesProperties::GetRuleDescription() const
{
    return m_RuleDescription;
}

// Obtient le GUID de la règle
inline CString ZBBPRulesProperties::GetRuleGUID() const
{
    return m_RuleGUID;
}

#endif //__ZBBPRulesProp_H__