/****************************************************************************
 * ==> PSS_ExtAppPropertyMgr -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an external application properties manager        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExtAppPropertyMgrH
#define PSS_ExtAppPropertyMgrH

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
#include "zProperty\ZIProperties.h"
#include "PSS_ExtAppProperties.h"
#include "PSS_ExtApps.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* External application properties manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ExtAppPropertyMgr
{
    public:
        /**
        * Constructor
        *@param pSymbol - the owning symbol
        */
        PSS_ExtAppPropertyMgr(CODSymbolComponent* pSymbol = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ExtAppPropertyMgr(const PSS_ExtAppPropertyMgr& other);

        virtual ~PSS_ExtAppPropertyMgr();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ExtAppPropertyMgr& operator = (const PSS_ExtAppPropertyMgr& other);

        /**
        * Gets the external application object reference
        *@return the external application object reference
        */
        virtual inline PSS_ExtApps& GetExtApps();

        /**
        * Gets the external application counter
        *@return the external application counter
        */
        virtual inline std::size_t GetExtAppCount() const;

        /**
        * Adds a new external application
        *@return the newly added external application, -1 on error
        */
        virtual inline int AddNewExtApp();

        /**
        * Adds an external application
        *@param pProp - the external application properties to add
        *@return the newly added external application, -1 on error
        */
        virtual inline int AddExtApp(PSS_ExtAppProperties* pProp);

        /**
        * Deletes an external application
        *@param index - the external application index to delete
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteExtApp(std::size_t index);

        /**
        * Deletes an external application
        *@param commandTitle - the command title
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteExtApp(const CString& commandTitle);

        /**
        * Deletes an external application
        *@param pProp - the external application properties
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteExtApp(PSS_ExtAppProperties* pProp);

        /**
        * Removes all the external applications
        */
        virtual inline void RemoveAllExtApps();

        /**
        * Removes the empty external applications
        */
        virtual inline void RemoveAllEmptyExtApps();

        /**
        * Checks if an external application exists
        *@param commandTitle - the command title
        *@return true on success, otherwise false
        */
        virtual inline bool ExtAppExist(const CString& commandTitle) const;

        /**
        * Locates the external application properties from its command title
        *@param commandTitle - the command title
        *@return the application properties, NULL if not found or on error
        */
        virtual inline PSS_ExtAppProperties* LocateExtApp(const CString& commandTitle) const;

        /**
        * Gets the external application properties at index
        *@param index - the index
        *@return the application properties, NULL if not found or on error
        */
        virtual inline PSS_ExtAppProperties* GetExtAppProperty(std::size_t index) const;

        /**
        * Locates the first empty element index
        *@return the first empty element index, -1 if not found or on error
        */
        virtual inline int LocateFirstEmptyExtApp() const;

        /**
        * Gets the file title at index
        *@param index - the index
        *@return the file title, empty string if not found or on error
        */
        virtual inline CString GetCommandTitle(std::size_t index) const;

        /**
        * Sets the file title at index
        *@param index - the index
        *@param value - the file title value
        */
        virtual inline void SetCommandTitle(std::size_t index, const CString& value);

        /**
        * Gets the command line at index
        *@param index - the index
        *@return the command line, empty string if not found or on error
        */
        virtual inline CString GetCommandLine(std::size_t index) const;

        /**
        * Sets the command line at index
        *@param index - the index
        *@param value - the command line value
        */
        virtual inline void SetCommandLine(std::size_t index, const CString& value);

        /**
        * Gets the command parameters at index
        *@param index - the index
        *@return the command parameters, empty string if not found or on error
        */
        virtual inline CString GetCommandParameters(std::size_t index) const;

        /**
        * Sets the command parameters at index
        *@param index - the index
        *@param value - the command parameters value
        */
        virtual inline void SetCommandParameters(std::size_t index, const CString& value);

        /**
        * Gets the startup directory at index
        *@param index - the index
        *@return the startup directory, empty string if not found or on error
        */
        virtual inline CString GetCommandStartupDirectory(std::size_t index) const;

        /**
        * Sets the command startup directory at index
        *@param index - the index
        *@param value - the command startup directory value
        */
        virtual inline void SetCommandStartupDirectory(std::size_t index, const CString& value);

        /**
        * Gets the priority level at index
        *@param index - the index
        *@return the priority level at index
        */
        virtual inline int GetPriorityLevel(std::size_t index) const;

        /**
        * Sets the priority level at index
        *@param index - the index
        *@param value - the priority level value
        */
        virtual inline void SetPriorityLevel(std::size_t index, const int value);

        /**
        * Gets the window start mode at index
        *@param index - the index
        *@return the window start mode at index
        */
        virtual inline int GetWindowStartMode(std::size_t index) const;

        /**
        * Sets the window start mode at index
        *@param index - the index
        *@param value - the window start mode value
        */
        virtual inline void SetWindowStartMode(std::size_t index, const int value);

        /**
        * Does a standard external application insertion
        *@param showDialog - if true, the insert app dialog may be shown
        *@return true on success, otherwise false
        */
        virtual bool DoInsertExtApp(bool showDialog = true);

        /**
        * Checks if the item to drop is accepted by the manager
        *@param pObj - the dropped object
        *@param point - the drop point
        *@return true if the manager accepts the item to drop, otherwise false
        */
        virtual bool AcceptDropItem(CObject* pObj, const CPoint& point);

        /**
        * Drops an item
        *@param pObj - the dropped object
        *@param point - the drop point
        *@return true on success, otherwise false
        */
        virtual bool DropItem(CObject* pObj, const CPoint& point);

        /**
        * Creates the owning symbol properties
        *@return true on success, otherwise false
        */
        virtual bool CreateSymbolProperties();

        /**
        * Fills an array with the owning symbol properties
        *@param[in, out] propSet - property set to fill with the owning symbol properties, filled set on function ends
        *@param numericValues - if true, only properties containing a numeric values will be filled
        *@param groupValues - if true, values will be grouped
        *@return true on success, otherwise false
        */
        virtual bool FillProperties(ZBPropertySet& propSet, bool numericValue = false, bool groupValue = false);

        /**
        * Fills an array with the owning symbol properties for Messenger
        *@param[in, out] propSet - property set to fill with the owning symbol properties, filled set on function ends
        *@param numericValues - if true, only properties containing a numeric values will be filled
        *@param groupValues - if true, values will be grouped
        *@return true on success, otherwise false
        */
        virtual bool FillPropertiesMessenger(ZBPropertySet& propSet, bool numericValue = false, bool groupValue = false);

        /**
        * Save the changes to object properties
        *@param propSet - property set to fill with the saved properties
        *@return true on success, otherwise false
        */
        virtual bool SaveProperties(ZBPropertySet& propSet);

        /**
        * Fills the owning symbol property
        *@param[in, out] prop - property to fill, filled property on function ends
        *@return true on success, otherwise false
        */
        virtual bool FillProperty(ZBProperty& prop);

        /**
        * Saves the owning symbol property
        *@param[in, out] prop - property to save, saved property on function ends
        *@return true on success, otherwise false
        */
        virtual bool SaveProperty(ZBProperty& prop);

        /**
        * Checks the property value
        *@param prop - property to check
        *@param value - property value
        *@param props - property set at which the property belongs
        *@return true if the property value was checked successfully, otherwise false
        */
        virtual bool CheckPropertyValue(ZBProperty& prop, CString& value, ZBPropertySet& props);

        /**
        * Processes the extended input for the property value
        *@param prop - property
        *@param value - property value
        *@param props - property set at which the property belongs
        *@param[in, out] refresh - if true, the owning symbol will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessExtendedInput(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Processes the menu command for the property value
        *@param menuCmdID - menu command identifier to process
        *@param prop - property
        *@param value - property value
        *@param props - property set at which the property belongs
        *@param[in, out] refresh - if true, the owning symbol will be refreshed immediately after the process is terminated
        *@return true on success, otherwise false
        */
        virtual bool ProcessMenuCommand(int            menuCmdID,
                                        ZBProperty&    prop,
                                        CString&       value,
                                        ZBPropertySet& props,
                                        bool&          refresh);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Called when a new external application is added
        *@param prop - the property containing the external application
        *@param value - the external application value
        *@param props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the owning symbol should be refreshed immediately
        */
        virtual void OnAddNewExtApp(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when an external application is deleted
        *@param prop - the property containing the external application
        *@param value - the external application value
        *@param props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the owning symbol should be refreshed immediately
        */
        virtual void OnDelCurrentExtApp(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called before a property changes
        *@param newValue - the new property value
        *@param prop - the changing property
        *@param props - the property set at which the property belongs
        *@return true if the property is allowed to change, otherwise false
        */
        virtual bool OnPrePropertyChanged(const CString& newValue, ZBProperty& prop, ZBPropertySet& props);

        /**
        * Called after a property changed
        *@param prop - the property which value has changed
        *@param props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the owning symbol should be refreshed immediately
        *@return true if the property changed, otherwise false
        */
        virtual bool OnPostPropertyChanged(ZBProperty& prop, ZBPropertySet& props, bool& refresh);

    protected:
        CODSymbolComponent* m_pSymbol;
        PSS_ExtApps         m_ExternalApplications;
};

//---------------------------------------------------------------------------
// PSS_ExtAppPropertyMgr
//---------------------------------------------------------------------------
PSS_ExtApps& PSS_ExtAppPropertyMgr::GetExtApps()
{
    return m_ExternalApplications;
}
//---------------------------------------------------------------------------
std::size_t PSS_ExtAppPropertyMgr::GetExtAppCount() const
{
    return m_ExternalApplications.GetExtAppCount();
}
//---------------------------------------------------------------------------
int PSS_ExtAppPropertyMgr::AddNewExtApp()
{
    return m_ExternalApplications.AddNewExtApp();
}
//---------------------------------------------------------------------------
int PSS_ExtAppPropertyMgr::AddExtApp(PSS_ExtAppProperties* pProp)
{
    return m_ExternalApplications.AddExtApp(pProp);
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::DeleteExtApp(std::size_t index)
{
    return m_ExternalApplications.DeleteExtApp(index);
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::DeleteExtApp(const CString& commandTitle)
{
    return m_ExternalApplications.DeleteExtApp(commandTitle);
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::DeleteExtApp(PSS_ExtAppProperties* pProp)
{
    return m_ExternalApplications.DeleteExtApp(pProp);
}
//---------------------------------------------------------------------------
void PSS_ExtAppPropertyMgr::RemoveAllExtApps()
{
    m_ExternalApplications.RemoveAllExtApps();
}
//---------------------------------------------------------------------------
void PSS_ExtAppPropertyMgr::RemoveAllEmptyExtApps()
{
    m_ExternalApplications.RemoveAllEmptyExtApps();
}
//---------------------------------------------------------------------------
bool PSS_ExtAppPropertyMgr::ExtAppExist(const CString& commandTitle) const
{
    return m_ExternalApplications.ExtAppExist(commandTitle);
}
//---------------------------------------------------------------------------
PSS_ExtAppProperties* PSS_ExtAppPropertyMgr::LocateExtApp(const CString& commandTitle) const
{
    return m_ExternalApplications.LocateExtApp(commandTitle);
}
//---------------------------------------------------------------------------
PSS_ExtAppProperties* PSS_ExtAppPropertyMgr::GetExtAppProperty(std::size_t index) const
{
    return m_ExternalApplications.GetProperty(index);
}
//---------------------------------------------------------------------------
int PSS_ExtAppPropertyMgr::LocateFirstEmptyExtApp() const
{
    return m_ExternalApplications.LocateFirstEmptyExtApp();
}
//---------------------------------------------------------------------------
CString PSS_ExtAppPropertyMgr::GetCommandTitle(std::size_t index) const
{
    return m_ExternalApplications.GetCommandTitle(index);
}
//---------------------------------------------------------------------------
void PSS_ExtAppPropertyMgr::SetCommandTitle(std::size_t index, const CString& value)
{
    m_ExternalApplications.SetCommandTitle(index, value);
}
//---------------------------------------------------------------------------
CString PSS_ExtAppPropertyMgr::GetCommandLine(std::size_t index) const
{
    return m_ExternalApplications.GetCommandLine(index);
}
//---------------------------------------------------------------------------
void PSS_ExtAppPropertyMgr::SetCommandLine(std::size_t index, const CString& value)
{
    m_ExternalApplications.SetCommandLine(index, value);
}
//---------------------------------------------------------------------------
CString PSS_ExtAppPropertyMgr::GetCommandParameters(std::size_t index) const
{
    return m_ExternalApplications.GetCommandParameters(index);
}
//---------------------------------------------------------------------------
void PSS_ExtAppPropertyMgr::SetCommandParameters(std::size_t index, const CString& value)
{
    m_ExternalApplications.SetCommandParameters(index, value);
}
//---------------------------------------------------------------------------
CString PSS_ExtAppPropertyMgr::GetCommandStartupDirectory(std::size_t index) const
{
    return m_ExternalApplications.GetCommandStartupDirectory(index);
}
//---------------------------------------------------------------------------
void PSS_ExtAppPropertyMgr::SetCommandStartupDirectory(std::size_t index, const CString& value)
{
    m_ExternalApplications.SetCommandStartupDirectory(index, value);
}
//---------------------------------------------------------------------------
int PSS_ExtAppPropertyMgr::GetPriorityLevel(std::size_t index) const
{
    return m_ExternalApplications.GetPriorityLevel(index);
}
//---------------------------------------------------------------------------
void PSS_ExtAppPropertyMgr::SetPriorityLevel(std::size_t index, const int value)
{
    m_ExternalApplications.SetPriorityLevel(index, value);
}
//---------------------------------------------------------------------------
int PSS_ExtAppPropertyMgr::GetWindowStartMode(std::size_t index) const
{
    return m_ExternalApplications.GetWindowStartMode(index);
}
//---------------------------------------------------------------------------
void PSS_ExtAppPropertyMgr::SetWindowStartMode(std::size_t index, const int value)
{
    m_ExternalApplications.SetWindowStartMode(index, value);
}
//---------------------------------------------------------------------------

#endif
