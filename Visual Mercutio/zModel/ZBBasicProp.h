/////////////////////////////////////////////////////////////////////////////
//@doc ZBBasicProperties
//@module ZBBasicProp.h | Interface of the <c ZBBasicProperties> class.
// 
// zForms
// Copyright 2001 Advanced Dedicated Software, Inc. All rights reserved.
// 
// 
// Author: Dominique Aigroz
// Created: 03/2001
// 
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBBasicProp_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBasicProp_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

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

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 17 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Orientation change flags

//@topic Basic Properties Change Flags 
//@flag Z_CHANGE_SYMBOL_NAME | Change the symbol name.
#define Z_CHANGE_SYMBOL_NAME			0x0001
//@flag Z_CHANGE_SYMBOL_DESCRIPTION | Change the symbol description.
#define Z_CHANGE_SYMBOL_DESCRIPTION		0x0002
//@flag Z_CHANGE_SYMBOL_NUMBER | Change the symbol number.
#define Z_CHANGE_SYMBOL_NUMBER			0x0004
// JMR-MODIF - Le 22 juillet 2007 - Ajout du drapeau pour le niveau de risque.
#define Z_CHANGE_SYMBOL_RISK_LEVEL		0x0008

/////////////////////////////////////////////////////////////////////////////
// Orientation property IDs

//@topic Basic Property Identifiers | Identify the properties
// contained by <c ZBBasicProperties> objects. The ZBBasicProperties
// class is a property container for these sub-properties. These
// identifiers are used in conjunction with the <c IODPropertyContainer>
// interface implemented by the orientation property container.
//@flag Z_SYMBOL_NAME | Identifier for the symbol name property.
#define Z_SYMBOL_NAME					1
//@flag Z_SYMBOL_DESCRIPTION | Identifier for the symbol description property.
#define Z_SYMBOL_DESCRIPTION			2
//@flag Z_SYMBOL_NUMBER | Identifier for the symbol number property.
#define Z_SYMBOL_NUMBER					3
// JMR-MODIF - Le 22 jullet 2007 - Ajout du drapeau pour le niveau du risque.
#define Z_SYMBOL_RISK_LEVEL				4

/////////////////////////////////////////////////////////////////////////////
// ZBBasicProperties
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
//@base public | CPropertyContainer<lt>IODPropertyContainer, sfl::CODIntPropertyAccessor<lt>ZBBasicProperties<gt> <gt>

class AFX_EXT_CLASS ZBBasicProperties : public CODIntProperty,
										public sfl::CPropertyContainer<IODPropertyContainer, CODPropertyAccessor<ZBBasicProperties> >
{
	DECLARE_SERIAL( ZBBasicProperties )

// Construction/Destruction
public:

	//@cmember
	/* Constructor. */
	ZBBasicProperties( int nId = ZS_BP_PROP_BASIC );

	//@cmember
	/* Copy constructor. */
	ZBBasicProperties( const ZBBasicProperties& propBasic );

	//@cmember
	/* Destructor. */
	virtual ~ZBBasicProperties();

// Operations
public:

	//@cmember
	/* Compare the property identifier with another identifier. */
	virtual BOOL CompareId( const int nId ) const;

	//@cmember
	/* Assigns another property to this property. */
	ZBBasicProperties& operator=( const ZBBasicProperties& propBasic );

	//@cmember
	/* Compares two orientation properties. */
	BOOL operator==( const ZBBasicProperties propBasic ) const;

	//@cmember
	/* Makes a copy of this properties object. */
	virtual CODProperty* Dup();

	//@cmember
	/* Merges another set of properties with this one. */
	virtual void Merge( CODProperty* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL );

	//@cmember
	/* Determines if another set of properties is equal to this one. */
	virtual BOOL IsEqual( CODProperty* pProp );

public:

	//@cmember
	/* Gets the control point that defines the orientation value. */
	CString GetSymbolName() const;

	//@cmember
	/* Sets the control point that defines the orientation value. */
	void SetSymbolName( const CString value );

	//@cmember
	/* Gets the horizontal spacing between container control point and component. */
	CString GetSymbolDescription() const;

	//@cmember
	/* Sets the horizontal spacing between container control point and component. */
	void SetSymbolDescription( const CString value );

	//@cmember
	/* Gets the vertical spacing between container control point and component. */
	int GetSymbolNumber() const;
	CString GetSymbolNumberStr() const;

	//@cmember
	/* Sets the vertical spacing between container control point and component. */
	void SetSymbolNumber( const int value );
	void SetSymbolNumber( const CString valueStr );

	// JMR-MODIF - Le 22 juillet 2007 - Ajout des fonctions concernant le niveau du risque.
	CString GetSymbolRiskLevel() const;
	void SetSymbolRiskLevel( const CString RiskLevel );

	/////////////////////////////////////////////////////////////////////////
	// IODObject interface
	BEGIN_GUID_MAP(ZBBasicProperties)
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
	/* Serializes the orientation properties. */
	virtual void Serialize( CArchive& ar );

// Implementation
public:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

private:

	/* Registers the basic property meta-data. */
	bool RegisterProperties();

// Attributes
protected:

	//@cmember
	/* Name of the symbol. */
	CString	m_SymbolName;

	//@cmember
	/* Description of the symbol. */
	CString	m_SymbolDescription;

	//@cmember
	/* Unique number of the symbol. */
	int		m_SymbolNumber;

	// JMR-MODIF - Le 22 juillet 2007 - Ajout du paramètre m_SymbolRiskLevel.
	CString	m_SymbolRiskLevel;
};

/////////////////////////////////////////////////////////////////////////////
// ZBBasicProperties inline methods

//@mfunc Add a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBasicProperties::AddRef()
{
	return CODIntProperty::AddRef();
}

//@mfunc Release a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBasicProperties::Release()
{
	return CODIntProperty::Release();
}

//@mfunc Gets the control point that defines the orientation value.
//@rdesc A control point value that defines the orientation.
inline CString ZBBasicProperties::GetSymbolName() const
{
	return m_SymbolName;
}

//@mfunc Sets the control point that defines the orientation value.
//@rdesc void
//@parm A control point value that defines the orientation.
inline void ZBBasicProperties::SetSymbolName( const CString value )
{
	m_SymbolName = value;
}

//@mfunc Gets the horizontal spacing between container control point and component.
//@rdesc Spacing value.
inline CString ZBBasicProperties::GetSymbolDescription() const
{
	return m_SymbolDescription;
}

//@mfunc Sets the horizontal spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBasicProperties::SetSymbolDescription( const CString value )
{
	m_SymbolDescription = value;
}

//@mfunc Gets the vertical spacing between container control point and component.
//@rdesc Spacing value.
inline int ZBBasicProperties::GetSymbolNumber() const
{
	return m_SymbolNumber;
}

//@mfunc Sets the vertical spacing between container control point and component.
//@rdesc void
//@parm Spacing value.
inline void ZBBasicProperties::SetSymbolNumber( const int value )
{
	m_SymbolNumber = value;
}

// JMR-MODIF - Le 22 juillet 2007 - Cette fonction permet d'obtenir le niveau du risque du symbole.
inline CString ZBBasicProperties::GetSymbolRiskLevel() const
{
	return m_SymbolRiskLevel;
}

// JMR-MODIF - Le 22 juillet 2007 - Cette fonction permet de définir le niveau du risque du symbole.
inline void ZBBasicProperties::SetSymbolRiskLevel( const CString RiskLevel )
{
	m_SymbolRiskLevel = RiskLevel;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline CODProperty* ZBBasicProperties::Dup()
{
	return new ZBBasicProperties( *this );
}

#endif // !defined(AFX_ZBBasicProp_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)