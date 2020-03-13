/****************************************************************************
 * ==> PSS_Properties ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the properties interface                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertiesH
#define PSS_PropertiesH

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

// processsoft
#include "PSS_Property.h"

#ifdef _ZPROPERTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

using namespace sfl;

/**
* Properties interface. Every class owning properties should implement this interface
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Properties
{
    public:
        typedef CCArray_T <PSS_Property*, PSS_Property*> IPropertySet;
        typedef Iterator_T<PSS_Property*>                IPropertyIterator;

        PSS_Properties();
        virtual ~PSS_Properties();

        /**
        * Checks if the object contains properties
        *@return true if the object contains properties, otherwise false
        */
        virtual bool HasProperties() const = 0;

        /**
        * Fills an array with the symbol properties
        *@param[in, out] propSet - property set to fill with the symbol properties, filled set on function ends
        *@param numericValues - if true, only properties containing a numeric values will be filled
        *@param groupValues - if true, values will be grouped
        *@return true on success, otherwise false
        */
        virtual bool FillProperties(IPropertySet& propSet, bool numericValues = false, bool groupValues = false) = 0;

        /**
        * Saves the changes to object properties
        *@param[in, out] propSet - property set to fill with the saved properties
        *@return true on success, otherwise false
        */
        virtual bool SaveProperties(IPropertySet& propSet) = 0;

        /**
        * Fills a symbol property
        *@param[in, out] prop - property to fill, filled property on function ends
        *@return true on success, otherwise false
        */
        virtual bool FillProperty(PSS_Property& prop) = 0;

        /**
        * Saves a symbol property
        *@param[in, out] prop - property to save, saved property on function ends
        *@return true on success, otherwise false
        */
        virtual bool SaveProperty(PSS_Property& prop) = 0;

        /**
        * Checks the property value
        *@param[in, out] prop - property to check
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@return true if the property value was checked successfully, otherwise false
        */
        virtual bool CheckPropertyValue(PSS_Property& prop, CString& value, IPropertySet& props) = 0;

        /**
        * Processes the extended input for the property value
        *@param[in, out] prop - property
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessExtendedInput(PSS_Property& prop, CString& value, IPropertySet& props, bool& refresh) = 0;

        /**
        * Processes the menu command for the property value
        *@param menuCmdID - menu command identifier to process
        *@param[in, out] prop - property
        *@param[in, out] value - property value
        *@param[in, out] props - property set at which the property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessMenuCommand(int           menuCmdID,
                                        PSS_Property& prop,
                                        CString&      value,
                                        IPropertySet& props,
                                        bool&         refresh) = 0;

        /**
        * Creates the symbol properties
        *@return true on success, otherwise false
        */
        virtual bool CreateSymbolProperties() = 0;

        /**
        * Checks if the properties are read-only
        *@return true if the properties are read-only, otherwise false
        */
        virtual bool IsPropertiesReadOnly() const = 0;

        /**
        * Called before the property changes
        *@param newValue - the new value
        *@param[in, out] prop - the changing property
        *@param[in, out] props - the property set at which the changing property belongs
        *@return true if the property is allowed to change, otherwise false
        */
        virtual bool OnPrePropertyChanged(const CString& newValue, PSS_Property& prop, IPropertySet& props) = 0;

        /**
        * Called after the property changed
        *@param[in, out] prop - the changing property
        *@param[in, out] props - the property set at which the changing property belongs
        *@param[in, out] refresh - if true, the symbol will be refreshed immediately
        *@return true if the property changed, otherwise false
        */
        virtual bool OnPostPropertyChanged(PSS_Property& prop, IPropertySet& props, bool& refresh) = 0;

        /**
        * Called when an internal property drag&drop occurred in the symbol
        *@param[in, out] srcProperty - the source property
        *@param[in, out] dstProperty - the destination property
        *@param top2Down - if true, the drag&drop happens from top to down
        *@param[in, out] props - the property set at which the drag&dropped properties belong
        *@return true if item was dropped, otherwise false
        */
        virtual bool OnDropInternalPropertyItem(PSS_Property& srcProperty,
                                                PSS_Property& dstProperty,
                                                bool          top2Down,
                                                IPropertySet& props) = 0;
};

/**
* Swaps two internal property items
*@author Dominique Aigroz, Jean-Milost Reymond
*/
AFX_EXT_API bool SwapInternalPropertyItem(PSS_Property&                 srcProperty,
                                          PSS_Property&                 dstProperty,
                                          bool                          top2Down,
                                          PSS_Properties::IPropertySet& props,
                                          int                           categoryID);

#endif
