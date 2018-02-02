/////////////////////////////////////////////////////////////////////////////
//@doc ZBLanguageProp
//@module ZBBasicProp.h | Interface of the <c ZBLanguageProp> class.
// 
// zForms
// Copyright 2001 Advanced Dedicated Software, Inc. All rights reserved.
// 
// 
// Author: Dominique Aigroz
// Created: 03/2001
// 
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBLanguageProp_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBLanguageProp_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

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
#include "zLanguageDef.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 31 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// Orientation change flags

//@topic Basic Properties Change Flags 
//@flag Z_CHANGE_LANGUAGE | Change the language.
#define Z_CHANGE_LANGUAGE	0x0001

/////////////////////////////////////////////////////////////////////////////
// Orientation property IDs

//@topic Basic Property Identifiers | Identify the properties
// contained by <c ZBLanguageProp> objects. 
//@flag Z_LANGUAGE | Identifier for the language property.
#define Z_LANGUAGE			1

/////////////////////////////////////////////////////////////////////////////
// ZBLanguageProp
//
//@class Determines the language.
//
// This class is both a property and a container for properties. It implements
// the <c IODPropertyContainer> interface for getting and setting values that
// it contains. 
//
//@base public | CODIntProperty
//@base public | CPropertyContainer<lt>IODPropertyContainer, sfl::CODIntPropertyAccessor<lt>ZBLanguageProp<gt> <gt>

class AFX_EXT_CLASS ZBLanguageProp : public CODIntProperty,
									 public sfl::CPropertyContainer<IODPropertyContainer, CODPropertyAccessor<ZBLanguageProp> >
{
	DECLARE_SERIAL( ZBLanguageProp )

// Construction/Destruction
public:

	//@cmember
	/* Constructor. */
	ZBLanguageProp( int nId = ZS_BP_PROP_LANGUAGE );

	//@cmember
	/* Copy constructor. */
	ZBLanguageProp( const ZBLanguageProp& propBasic );

	//@cmember
	/* Destructor. */
	virtual ~ZBLanguageProp();

// Operations
public:

	//@cmember
	/* Compare the property identifier with another identifier. */
	virtual BOOL CompareId( const int nId ) const;

	//@cmember
	/* Assigns another property to this property. */
	ZBLanguageProp& operator=( const ZBLanguageProp& propBasic );

	//@cmember
	/* Compares two orientation properties. */
	BOOL operator==( const ZBLanguageProp propBasic ) const;

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
	/* Gets the language value. */
	Language GetLanguage() const;
	int GetLanguageInt() const;

	//@cmember
	/* Sets the language value. */
	void SetLanguage( const Language value );
	void SetLanguageInt( const int value );

public:

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

public:

	/////////////////////////////////////////////////////////////////////////
	// IODObject interface

	BEGIN_GUID_MAP(ZBLanguageProp)
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
	/* The language. */
	Language m_Language;
};

/////////////////////////////////////////////////////////////////////////////
// ZBLanguageProp inline methods

//@mfunc Add a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBLanguageProp::AddRef()
{
	return CODIntProperty::AddRef();
}

//@mfunc Release a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBLanguageProp::Release()
{
	return CODIntProperty::Release();
}

inline Language ZBLanguageProp::GetLanguage() const
{
	return m_Language;
}

inline int ZBLanguageProp::GetLanguageInt() const
{
	return static_cast<int>( m_Language );
}

inline void ZBLanguageProp::SetLanguage( const Language value )
{
	m_Language = value;
}

inline void ZBLanguageProp::SetLanguageInt( const int value )
{
	m_Language = static_cast<Language>( value );
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline CODProperty* ZBLanguageProp::Dup()
{
	return new ZBLanguageProp( *this );
}

#endif // !defined(AFX_ZBLanguageProp_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)