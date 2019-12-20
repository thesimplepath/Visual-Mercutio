/****************************************************************************
 * ==> PSS_ExtApps ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an external application manager                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExtAppsH
#define PSS_ExtAppsH

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
#ifndef PSS_ExtApps
    #define PSS_ExtApps ZBExtApps
#endif

// old class name mapping
#ifndef PSS_ExtAppProperties
    #define PSS_ExtAppProperties ZBExtAppProperties
#endif

// forward class declaration
class PSS_ExtAppProperties;

#ifdef _ZMODELEXPORT
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
* External application manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ExtApps : public CObject
{
    DECLARE_SERIAL(PSS_ExtApps)

    public:
        typedef CCArray_T <PSS_ExtAppProperties*, PSS_ExtAppProperties*> IPropSet;
        typedef Iterator_T<PSS_ExtAppProperties*>                        IPropIterator;

        /**
        * Constructor
        *@param pParent - the parent symbol object, ignored if NULL
        */
        PSS_ExtApps(CODSymbolComponent* pParent = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ExtApps(const PSS_ExtApps& other);

        virtual ~PSS_ExtApps();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ExtApps& operator = (const PSS_ExtApps& other);

        /**
        * Creates a duplicate copy of this object
        *@return the duplicate copy of this object
        */
        virtual PSS_ExtApps* Dup() const;

        /**
        * Sets the parent symbol object
        *@param pParent - the parent symbol object, ignored if NULL
        */
        virtual void SetParent(CODSymbolComponent* pParent);

        /**
        * Creates the initial properties
        *@return true on success, otherwise false
        */
        virtual bool CreateInitialProperties();

        /**
        * Adds a new external application
        *@return the new added external application index, -1 on error
        */
        virtual int AddNewExtApp();

        /**
        * Adds an external application
        *@param pProp - the property containing the external application to add
        *@return the new added external application index, -1 on error
        */
        virtual int AddExtApp(PSS_ExtAppProperties* pProp);

        /**
        * Deletes an external application
        *@param index - the external application index to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteExtApp(std::size_t index);

        /**
        * Deletes an external application
        *@param commandTitle - the command title of the external application to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteExtApp(const CString& commandTitle);

        /**
        * Deletes an external application
        *@param pPropToDel - the property containing the external application to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteExtApp(PSS_ExtAppProperties* pPropToDel);

        /**
        * Remove all elements
        */
        virtual void RemoveAllExtApps();

        /**
        * Removes only empty elements
        */
        virtual void RemoveAllEmptyExtApps();

        /**
        * Checks if an external application exists
        *@param commandTitle - the command title of the external application to delete
        *@return true if the external application exists, otherwise false
        */
        virtual bool ExtAppExist(const CString& commandTitle) const;

        /**
        * Locates the external application properties
        *@param commandTitle - the command title of the external application to delete
        *@return the external application properties, NULL if not found or on error
        */
        virtual PSS_ExtAppProperties* LocateExtApp(const CString& commandTitle) const;

        /**
        * Gets the external application set
        *@return the external application set
        */
        virtual inline IPropSet& GetExtAppSet();

        /**
        * Gets the external application counter
        *@return the external application counter
        */
        virtual inline std::size_t GetExtAppCount() const;

        /**
        * Gets the property as index
        *@param index - the index
        *@return the property, NULL if not found or on error
        */
        virtual inline PSS_ExtAppProperties* GetProperty(std::size_t index) const;

        /**
        * Gets the first empty element index
        *@return the first empty element index, -1 if not found or on error
        */
        virtual int LocateFirstEmptyExtApp() const;

        /**
        * Gets the command title at index
        *@param index - the index
        *@return the command title, empty string if not found or on error
        */
        virtual CString GetCommandTitle(std::size_t index) const;

        /**
        * Sets the command title at index
        *@param index - the index
        *@param value - the command title value
        */
        virtual void SetCommandTitle(std::size_t index, const CString& value);

        /**
        * Gets the command line at index
        *@param index - the index
        *@return the command line, empty string if not found or on error
        */
        virtual CString GetCommandLine(std::size_t index) const;

        /**
        * Sets the command line at index
        *@param index - the index
        *@param value - the command line value
        */
        virtual void SetCommandLine(std::size_t index, const CString& value);

        /**
        * Gets the command parameters at index
        *@param index - the index
        *@return the command parameters, empty string if not found or on error
        */
        virtual CString GetCommandParameters(std::size_t index) const;

        /**
        * Sets the command parameters at index
        *@param index - the index
        *@param value - the command parameters value
        */
        virtual void SetCommandParameters(std::size_t index, const CString& value);

        /**
        * Gets the command startup directory at index
        *@param index - the index
        *@return the command startup directory, empty string if not found or on error
        */
        virtual CString GetCommandStartupDirectory(std::size_t index) const;

        /**
        * Sets the command startup directory at index
        *@param index - the index
        *@param value - the command startup directory value
        */
        virtual void SetCommandStartupDirectory(std::size_t Index, const CString& value);

        /**
        * Gets the priority level at index
        *@param index - the index
        *@return the priority level
        */
        virtual int GetPriorityLevel(std::size_t index) const;

        /**
        * Sets the priority level at index
        *@param index - the index
        *@param value - the priority level
        */
        virtual void SetPriorityLevel(std::size_t index, const int value);

        /**
        * Gets the window start mode at index
        *@param index - the index
        *@return the window start mode
        */
        virtual int GetWindowStartMode(std::size_t index) const;

        /**
        * Sets the window start mode at index
        *@param index - the index
        *@param value - the window start mode
        */
        virtual void SetWindowStartMode(std::size_t index, const int value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CODSymbolComponent* m_pParent;
        IPropSet            m_Set;
};

//---------------------------------------------------------------------------
// PSS_ExtApps
//---------------------------------------------------------------------------
PSS_ExtApps::IPropSet& PSS_ExtApps::GetExtAppSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------
std::size_t PSS_ExtApps::GetExtAppCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------
PSS_ExtAppProperties* PSS_ExtApps::GetProperty(std::size_t index) const
{
    if (index < GetExtAppCount())
        return m_Set.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------

#endif
