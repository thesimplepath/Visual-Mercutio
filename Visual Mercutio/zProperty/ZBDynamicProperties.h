// ZBDynamicProperties.h: interface for the ZBDynamicProperties class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBDynamicProperties_H__87B2BA20_42F8_4B9C_BE5D_8BFBD66596F3__INCLUDED_)
#define AFX_ZBDynamicProperties_H__87B2BA20_42F8_4B9C_BE5D_8BFBD66596F3__INCLUDED_

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

// ZIProperties
#include "ZIProperties.h"

// forward class declaration
class PSS_BasicSymbol;

#ifdef _ZPROPERTYEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 27 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBDynamicPropertiesSet | An array of ZBProperty pointers.
//@iex typedef CCArray_T<ZBProperty*,ZBProperty*> ZBDynamicPropertiesSet;
typedef CCArray_T<ZBProperty*, ZBProperty*> ZBDynamicPropertiesSet;

//@type ZBProperty | An iterator for ZBDynamicPropertiesSet collections.
//@iex typedef Iterator_T<ZIProperties*> ZBDynamicPropertiesIterator;
typedef Iterator_T<ZBProperty*> ZBDynamicPropertiesIterator;

class AFX_EXT_CLASS ZBDynamicProperties : public CObject,
                                          public ZIProperties
{
    DECLARE_SERIAL( ZBDynamicProperties )

public:

    ZBDynamicProperties();
    virtual ~ZBDynamicProperties();

    /* Copy constructor. */
    ZBDynamicProperties( const ZBDynamicProperties& src );

    /* Assignment operator. */
    ZBDynamicProperties& operator=( const ZBDynamicProperties& src );

    /* Create a duplicate copy of this object. */
    virtual ZBDynamicProperties* Dup() const;

    /* Serializes the symbol. */
    virtual void Serialize( CArchive& ar );

    ///////////////////////////////////////////////////////
    // ZIProperties methods

    // Return true if the object has properties
    virtual bool HasProperties() const
    {
        return true;
    };

    // Call to retreive properties for the object
    virtual bool FillProperties( ZBPropertySet& PropSet, bool NumericValue = false, bool GroupValue = false );

    // Call to save new changes to object's properties
    virtual bool SaveProperties( ZBPropertySet& PropSet );

    // Called to retreive a property for the object
    virtual bool FillProperty( ZBProperty& Property );

    // Called to save a property for the object
    virtual bool SaveProperty( ZBProperty& Property );

    // Called to check the property value
    virtual bool CheckPropertyValue( ZBProperty& Property, CString& value, ZBPropertySet& Properties );

    // Called to process the extended input for the property value
    virtual bool ProcessExtendedInput( ZBProperty&        Property,
                                       CString&            value,
                                       ZBPropertySet&    Properties,
                                       bool&            Refresh );

    // Called to process the a menu command for the property value
    virtual bool ProcessMenuCommand( int            MenuCommand,
                                     ZBProperty&    Property,
                                     CString&        value,
                                     ZBPropertySet&    Properties,
                                     bool&            Refresh );

    // Called before the property changed
    virtual bool OnPrePropertyChanged( CString NewValue, ZBProperty& Property, ZBPropertySet& Properties );

    // Called after the property changed
    virtual bool OnPostPropertyChanged( ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh );

    // Called when an internal drag&drop of property occured
    virtual bool OnDropInternalPropertyItem( ZBProperty&    SrcProperty,
                                             ZBProperty&    DstProperty,
                                             bool            Top2Down,
                                             ZBPropertySet&    Properties );

    // Call to create the properties
    virtual bool CreateSymbolProperties();

    // Call to know if properties can be edited
    virtual bool IsPropertiesReadOnly() const
    {
        return false;
    };

    void FreePropertiesSet();
    void AddDynamicProperty( ZBProperty* pProperty );
    bool Exist( ZBProperty* pProperty );
    bool DeleteProperty( ZBProperty* pProperty );

private:

    ZBDynamicPropertiesSet m_Set;
};

#endif // !defined(AFX_ZBDynamicProperties_H__87B2BA20_42F8_4B9C_BE5D_8BFBD66596F3__INCLUDED_)