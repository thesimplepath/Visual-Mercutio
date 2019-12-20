/****************************************************************************
 * ==> PSS_ExtFilePropertyMgr ----------------------------------------------*
 ****************************************************************************
 * Description : Provides an external file properties manager               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExtFilePropertyMgrH
#define PSS_ExtFilePropertyMgrH

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
#include "PSS_ExtFiles.h"
#include "PSS_ExtFileProperties.h"

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
class AFX_EXT_CLASS PSS_ExtFilePropertyMgr
{
    public:
        PSS_ExtFilePropertyMgr();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ExtFilePropertyMgr(const PSS_ExtFilePropertyMgr& other);

        virtual ~PSS_ExtFilePropertyMgr();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ExtFilePropertyMgr& operator = (const PSS_ExtFilePropertyMgr& other);

        /**
        * Gets the external file object reference
        *@return the external file object reference
        */
        virtual inline PSS_ExtFiles& GetExtFiles();

        /**
        * Gets the external file counter
        *@return the external file counter
        */
        virtual inline std::size_t GetExtFileCount() const;

        /**
        * Adds a new external file
        *@return the newly added external file, -1 on error
        */
        virtual inline int AddNewExtFile();

        /**
        * Adds an external file
        *@param pProp - the external file properties to add
        *@return the newly added external file, -1 on error
        */
        virtual inline int AddExtFile(PSS_ExtFileProperties* pProp);

        /**
        * Deletes an external file
        *@param index - the external file index to delete
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteExtFile(std::size_t index);

        /**
        * Deletes an external file
        *@param file - the file name
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteExtFile(const CString& fileName);

        /**
        * Deletes an external file
        *@param pProp - the external file properties
        *@return true on success, otherwise false
        */
        virtual inline bool DeleteExtFile(PSS_ExtFileProperties* pProp);

        /**
        * Removes all the external files
        */
        virtual inline void RemoveAllExtFiles();

        /**
        * Removes the empty external files
        */
        virtual inline void RemoveAllEmptyExtFiles();

        /**
        * Checks if an external file exists
        *@param fileName - the file name
        *@return true on success, otherwise false
        */
        virtual inline bool ExtFileExist(const CString& fileName) const;

        /**
        * Locates the external file properties from its file name
        *@param fileName - the file name
        *@return the file properties, NULL if not found or on error
        */
        virtual inline PSS_ExtFileProperties* LocateExtFile(const CString& fileName) const;

        /**
        * Gets the external file properties at index
        *@param index - the index
        *@return the file properties, NULL if not found or on error
        */
        virtual inline PSS_ExtFileProperties* GetExtFileProperty(std::size_t index) const;

        /**
        * Locates the first empty element index
        *@return the first empty element index, -1 if not found or on error
        */
        virtual inline int LocateFirstEmptyExtFile() const;

        /**
        * Gets the file title at index
        *@return the file title, empty string if not found or on error
        */
        virtual inline CString GetFileTitle(std::size_t index) const;

        /**
        * Sets the file title at index
        *@param index - the index
        *@param value - the file title
        */
        virtual inline void SetFileTitle(std::size_t index, const CString& value);

        /**
        * Gets the file name at index
        *@return the file name, empty string if not found or on error
        */
        virtual inline CString GetFileName(std::size_t index) const;

        /**
        * Sets the file name at index
        *@param index - the index
        *@param value - the file name
        */
        virtual inline void SetFileName(std::size_t index, const CString& value);

        /**
        * Gets the insertion type at index
        *@return the insertion type, empty string if not found or on error
        */
        virtual inline int GetInsertionType(std::size_t index) const;

        /**
        * Sets the insertion type at index
        *@param index - the index
        *@param value - the insertion type
        */
        virtual inline void SetInsertionType(std::size_t index, const int value);

        /**
        * Gets the activation type at index
        *@return the activation type, empty string if not found or on error
        */
        virtual inline int GetActivationType(std::size_t index) const;

        /**
        * Sets the activation type at index
        *@param index - the index
        *@param value - the activation type
        */
        virtual inline void SetActivationType(std::size_t index, const int value);

        /**
        * Does a standard external file insertion
        *@param showDialog - if true, the insert app dialog may be shown
        *@return true on success, otherwise false
        */
        virtual bool DoInsertExtFile(bool showDialog = true);

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
        virtual bool ProcessMenuCommand(int            menuCommand,
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
        * Called when a new external file is added
        *@param prop - the property containing the external file
        *@param value - the external file value
        *@param props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the owning symbol should be refreshed immediately
        */
        virtual void OnAddNewExtFile(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

        /**
        * Called when an external file is deleted
        *@param prop - the property containing the external file
        *@param value - the external file value
        *@param props - the property set at which the property belongs
        *@param[in, out] refresh - if true, the owning symbol should be refreshed immediately
        */
        virtual void OnDelCurrentExtFile(ZBProperty& prop, CString& value, ZBPropertySet& props, bool& refresh);

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
        PSS_ExtFiles        m_ExternalFiles;
};

//---------------------------------------------------------------------------
// PSS_ExtFilePropertyMgr
//---------------------------------------------------------------------------
PSS_ExtFiles& PSS_ExtFilePropertyMgr::GetExtFiles()
{
    return m_ExternalFiles;
}
//---------------------------------------------------------------------------
std::size_t PSS_ExtFilePropertyMgr::GetExtFileCount() const
{
    return m_ExternalFiles.GetExtFileCount();
}
//---------------------------------------------------------------------------
int PSS_ExtFilePropertyMgr::AddNewExtFile()
{
    return m_ExternalFiles.AddNewExtFile();
}
//---------------------------------------------------------------------------
int PSS_ExtFilePropertyMgr::AddExtFile(PSS_ExtFileProperties* pProp)
{
    return m_ExternalFiles.AddExtFile(pProp);
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::DeleteExtFile(std::size_t index)
{
    return m_ExternalFiles.DeleteExtFile(index);
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::DeleteExtFile(const CString& fileName)
{
    return m_ExternalFiles.DeleteExtFile(fileName);
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::DeleteExtFile(PSS_ExtFileProperties* pProp)
{
    return m_ExternalFiles.DeleteExtFile(pProp);
}
//---------------------------------------------------------------------------
void PSS_ExtFilePropertyMgr::RemoveAllExtFiles()
{
    m_ExternalFiles.RemoveAllExtFiles();
}
//---------------------------------------------------------------------------
void PSS_ExtFilePropertyMgr::RemoveAllEmptyExtFiles()
{
    m_ExternalFiles.RemoveAllEmptyExtFiles();
}
//---------------------------------------------------------------------------
bool PSS_ExtFilePropertyMgr::ExtFileExist(const CString& fileName) const
{
    return m_ExternalFiles.ExtFileExist(fileName);
}
//---------------------------------------------------------------------------
PSS_ExtFileProperties* PSS_ExtFilePropertyMgr::LocateExtFile(const CString& fileName) const
{
    return m_ExternalFiles.LocateExtFile(fileName);
}
//---------------------------------------------------------------------------
PSS_ExtFileProperties* PSS_ExtFilePropertyMgr::GetExtFileProperty(std::size_t index) const
{
    return m_ExternalFiles.GetProperty(index);
}
//---------------------------------------------------------------------------
int PSS_ExtFilePropertyMgr::LocateFirstEmptyExtFile() const
{
    return m_ExternalFiles.LocateFirstEmptyExtFile();
}
//---------------------------------------------------------------------------
CString PSS_ExtFilePropertyMgr::GetFileTitle(std::size_t index) const
{
    return m_ExternalFiles.GetFileTitle(index);
}
//---------------------------------------------------------------------------
void PSS_ExtFilePropertyMgr::SetFileTitle(std::size_t index, const CString& value)
{
    m_ExternalFiles.SetFileTitle(index, value);
}
//---------------------------------------------------------------------------
CString PSS_ExtFilePropertyMgr::GetFileName(std::size_t index) const
{
    return m_ExternalFiles.GetFileName(index);
}
//---------------------------------------------------------------------------
void PSS_ExtFilePropertyMgr::SetFileName(std::size_t index, const CString& value)
{
    m_ExternalFiles.SetFileName(index, value);
}
//---------------------------------------------------------------------------
int PSS_ExtFilePropertyMgr::GetInsertionType(std::size_t index) const
{
    return m_ExternalFiles.GetInsertionType(index);
}
//---------------------------------------------------------------------------
void PSS_ExtFilePropertyMgr::SetInsertionType(std::size_t index, const int value)
{
    m_ExternalFiles.SetInsertionType(index, value);
}
//---------------------------------------------------------------------------
int PSS_ExtFilePropertyMgr::GetActivationType(std::size_t index) const
{
    return m_ExternalFiles.GetActivationType(index);
}
//---------------------------------------------------------------------------
void PSS_ExtFilePropertyMgr::SetActivationType(std::size_t index, const int value)
{
    m_ExternalFiles.SetActivationType(index, value);
}
//---------------------------------------------------------------------------

#endif
