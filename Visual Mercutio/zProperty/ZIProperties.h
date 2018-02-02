// ZIProperties.h: interface for the ZIProperties class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZIPROPERTIES_H__8CDA6F76_EF29_411F_B784_FF18A26F71AE__INCLUDED_)
#define AFX_ZIPROPERTIES_H__8CDA6F76_EF29_411F_B784_FF18A26F71AE__INCLUDED_

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

#include "ZBProperty.h"

#ifdef _ZPROPERTYEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 15 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Collection definition

using namespace sfl;

//@type ZBPropertySet | An array of ZBProperty pointers.
//@iex typedef CCArray_T<ZBProperty*,ZBProperty*> ZBPropertySet;
typedef CCArray_T<ZBProperty*, ZBProperty*> ZBPropertySet;

//@type ZBPropertyIterator | An iterator for ZBPropertySet collections.
//@iex typedef Iterator_T<ZBProperty*> ZBPropertyIterator;
typedef Iterator_T<ZBProperty*> ZBPropertyIterator;

//////////////////////////////////////////////////////////////////////
// Utility function for swaping two internal property items
AFX_EXT_API bool SwapInternalPropertyItem( ZBProperty&		SrcProperty,
										   ZBProperty&		DstProperty,
										   bool				Top2Down,
										   ZBPropertySet&	Properties,
										   int				CategoryID );

// Define the interface for properties
// A class who owns properties must implement 
// these interfaces

class AFX_EXT_CLASS ZIProperties
{
public:

	ZIProperties();
	virtual ~ZIProperties();

	// Return true if the object has properties
	virtual bool HasProperties() const = 0;

	// Called to retreive properties for the object
	virtual bool FillProperties( ZBPropertySet& PropSet, bool NumericValue = false, bool GroupValue = false ) = 0;

	// Called to save new changes to object's properties
	virtual bool SaveProperties( ZBPropertySet& PropSet ) = 0;

	// Called to retreive a property for the object
	virtual bool FillProperty( ZBProperty& Property ) = 0;

	// Called to save a property for the object
	virtual bool SaveProperty( ZBProperty& Property ) = 0;

	// Called to check the property value
	virtual bool CheckPropertyValue( ZBProperty& Property, CString& value, ZBPropertySet& Properties ) = 0;

	// Called to process the extended input for the property value
	virtual bool ProcessExtendedInput( ZBProperty&		Property,
									   CString&			value,
									   ZBPropertySet&	Properties,
									   bool&			Refresh ) = 0;

	// Called to process the a menu command for the property value
	virtual bool ProcessMenuCommand( int			MenuCommand,
									 ZBProperty&	Property,
									 CString&		value,
									 ZBPropertySet&	Properties,
									 bool&			Refresh ) = 0;

	// Called before the property changed
	virtual bool OnPrePropertyChanged( CString NewValue, ZBProperty& Property, ZBPropertySet& Properties ) = 0;

	// Called after the property changed
	virtual bool OnPostPropertyChanged( ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh ) = 0;

	// Called when an internal drag&drop of property occured
	virtual bool OnDropInternalPropertyItem( ZBProperty&	SrcProperty,
											 ZBProperty&	DstProperty,
											 bool			Top2Down,
											 ZBPropertySet&	Properties ) = 0;
	
	// Called to create the properties
	virtual bool CreateSymbolProperties() = 0;

	// Called to know if properties can be edited
	virtual bool IsPropertiesReadOnly() const = 0;
};

#endif // !defined(AFX_ZIPROPERTIES_H__8CDA6F76_EF29_411F_B784_FF18A26F71AE__INCLUDED_)