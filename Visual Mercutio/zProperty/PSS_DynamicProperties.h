/****************************************************************************
 * ==> PSS_DynamicProperties -----------------------------------------------*
 ****************************************************************************
 * Description : Provides the dynamic properties                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DynamicPropertiesH
#define PSS_DynamicPropertiesH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_DynamicProperties
    #define PSS_DynamicProperties ZBDynamicProperties
#endif

// processsoft
#include "ZIProperties.h"

// forward class declaration
class PSS_BasicSymbol;

#ifdef _ZPROPERTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// scope symbols in stingray foundation library
using namespace sfl;

/**
* Dynamic properties
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DynamicProperties : public CObject,
                                            public ZIProperties
{
    DECLARE_SERIAL(PSS_DynamicProperties)

    public:
        PSS_DynamicProperties();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DynamicProperties(const PSS_DynamicProperties& other);

        virtual ~PSS_DynamicProperties();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DynamicProperties& operator = (const PSS_DynamicProperties& other);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual PSS_DynamicProperties* Dup() const;

        /**
        * Creates the properties
        *@return true on success, otherwise false
        */
        virtual bool CreateSymbolProperties();

        /**
        * Checks if the object contains properties
        *@return true if if the object contains properties, otherwise false
        */
        virtual inline bool HasProperties() const;

        /**
        * Checks if the properties are read-only
        *@return true if the properties are read-only, otherwise false
        */
        virtual inline bool IsPropertiesReadOnly() const;

        /**
        * Fills an array with the object properties
        *@param[in, out] propSet - property set to fill with the object properties, filled set on function ends
        *@param numericValues - if true, only properties containing a numeric values will be filled
        *@param groupValues - if true, values will be grouped
        *@return true on success, otherwise false
        */
        virtual bool FillProperties(ZBPropertySet& propSet, bool numericValues = false, bool groupValues = false);

        /**
       * Saves the changes to object properties
       *@param[in, out] propSet - property set to fill with the saved properties
       *@return true on success, otherwise false
       */
        virtual bool SaveProperties(ZBPropertySet& propSet);

        /**
        * Fills an object property
        *@param[in, out] prop - property to fill, filled property on function ends
        *@return true on success, otherwise false
        */
        virtual bool FillProperty(PSS_Property& prop);

        /**
        * Saves an object property
        *@param[in, out] prop - property to save, saved property on function ends
        *@return true on success, otherwise false
        */
        virtual bool SaveProperty(PSS_Property& prop);

        /**
        * Checks the property value
        *@param[in, out] prop - property to check
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@return true if the property value was checked successfully, otherwise false
        */
        virtual bool CheckPropertyValue(PSS_Property& prop, CString& value, ZBPropertySet& props);

        /**
        * Processes the extended input for the property value
        *@param[in, out] prop - property
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@param[in, out] refresh - if true, the object will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessExtendedInput(PSS_Property& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Processes the menu command for the property value
        *@param menuCmdID - menu command identifier to process
        *@param[in, out] prop - property
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@param[in, out] refresh - if true, the object will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessMenuCommand(int            menuCmdID,
                                        PSS_Property&  prop,
                                        CString&       value,
                                        ZBPropertySet& props,
                                        bool&          refresh);

        /**
        * Adds a dynamic property
        *@parap pProperty - the dynamic property to add
        */
        virtual void AddDynamicProperty(PSS_Property* pProperty);

        /**
        * Checks if a property exists
        *@parap pProperty - the property to check
        *@return true if the property exists, otherwise false
        */
        virtual bool Exist(PSS_Property* pProperty);

        /**
        * Deletes a property
        *@parap pProperty - the property to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteProperty(PSS_Property* pProperty);

        /**
        * Frees the properties set
        */
        virtual void FreePropertiesSet();

        /**
        * Called before the property changes
        *@param newValue - the new value
        *@param[in, out] prop - the changing property
        *@param[in, out] props - the property set at which the changing property belongs
        *@return true if the property is allowed to change, otherwise false
        */
        virtual bool OnPrePropertyChanged(const CString& newValue, PSS_Property& prop, ZBPropertySet& props);

        /**
        * Called after the property changed
        *@param[in, out] prop - the changing property
        *@param[in, out] props - the property set at which the changing property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately
        *@return true if the property changed, otherwise false
        */
        virtual bool OnPostPropertyChanged(PSS_Property& prop, ZBPropertySet& props, bool& refresh);

        /**
        * Called when an internal property drag&drop occurred in the symbol
        *@param[in, out] srcProperty - the source property
        *@param[in, out] dstProperty - the destination property
        *@param top2Down - if true, the drag&drop happens from top to down
        *@param[in, out] props - the property set at which the drag&dropped properties belong
        *@return true if item was dropped, otherwise false
        */
        virtual bool OnDropInternalPropertyItem(PSS_Property&  srcProp,
                                                PSS_Property&  dstProp,
                                                bool           top2Down,
                                                ZBPropertySet& props);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        typedef CCArray_T <PSS_Property*, PSS_Property*> IDynamicPropertiesSet;
        typedef Iterator_T<PSS_Property*>                IDynamicPropertiesIterator;

        IDynamicPropertiesSet m_Set;
};

//---------------------------------------------------------------------------
// PSS_DynamicProperties
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::HasProperties() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DynamicProperties::IsPropertiesReadOnly() const
{
    return false;
}
//---------------------------------------------------------------------------

#endif
