/****************************************************************************
 * ==> PSS_ExtFiles --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an external file manager                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExtFilesH
#define PSS_ExtFilesH

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
#ifndef PSS_ExtFiles
    #define PSS_ExtFiles ZBExtFiles
#endif

// old class name mapping
#ifndef PSS_ExtFileProperties
    #define PSS_ExtFileProperties ZBExtFileProperties
#endif

// forward class declaration
class PSS_ExtFileProperties;

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
* External file manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ExtFiles : public CObject
{
    DECLARE_SERIAL(PSS_ExtFiles)

    public:
        typedef CCArray_T <PSS_ExtFileProperties*, PSS_ExtFileProperties*> IPropSet;
        typedef Iterator_T<PSS_ExtFileProperties*>                         IPropIterator;

        /**
        * Constructor
        *@param pParent - the parent symbol object, ignored if NULL
        */
        PSS_ExtFiles(CODSymbolComponent* pParent = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ExtFiles(const PSS_ExtFiles& other);

        virtual ~PSS_ExtFiles();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ExtFiles& operator = (const PSS_ExtFiles& other);

        /**
        * Creates a duplicate copy of this object
        *@return the duplicate copy of this object
        */
        virtual PSS_ExtFiles* Dup() const;

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
        * Adds a new external file
        *@return the new added external file index, -1 on error
        */
        virtual int AddNewExtFile();

        /**
        * Adds an external file
        *@param pProp - the property containing the external file to add
        *@return the new added external file index, -1 on error
        */
        virtual int AddExtFile(PSS_ExtFileProperties* pProperty);

        /**
        * Deletes an external file
        *@param index - the external file index to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteExtFile(std::size_t index);

        /**
        * Deletes an external file
        *@param fileName - the external file name to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteExtFile(const CString& fileName);

        /**
        * Deletes an external file
        *@param pPropToDel - the property containing the external file to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteExtFile(PSS_ExtFileProperties* pProperty);

        /**
        * Remove all elements
        */
        virtual void RemoveAllExtFiles();

        /**
        * Removes only empty elements
        */
        virtual void RemoveAllEmptyExtFiles();

        /**
        * Checks if an external file exists
        *@param fileName - the external file name to delete
        *@return true if the external application exists, otherwise false
        */
        virtual bool ExtFileExist(const CString& fileName) const;

        /**
        * Locates the external file properties
        *@param fileName - the external file name to delete
        *@return the external file name properties, NULL if not found or on error
        */
        virtual PSS_ExtFileProperties* LocateExtFile(const CString& fileName) const;

        /**
        * Gets the external file set
        *@return the external file set
        */
        virtual inline IPropSet& GetExtFileSet();

        /**
        * Gets the external file counter
        *@return the external file counter
        */
        virtual inline std::size_t GetExtFileCount() const;

        /**
        * Gets the property as index
        *@param index - the index
        *@return the property, NULL if not found or on error
        */
        virtual inline PSS_ExtFileProperties* GetProperty(std::size_t index) const;

        /**
        * Gets the first empty element index
        *@return the first empty element index, -1 if not found or on error
        */
        virtual int LocateFirstEmptyExtFile() const;

        /**
        * Gets the file title at index
        *@param index - the index
        *@return the file title, empty string if not found or on error
        */
        virtual CString GetFileTitle(std::size_t index) const;

        /**
        * Sets the file title at index
        *@param index - the index
        *@param value - the file title value
        */
        virtual void SetFileTitle(std::size_t index, const CString& value);

        /**
        * Gets the file name at index
        *@param index - the index
        *@return the file name, empty string if not found or on error
        */
        virtual CString GetFileName(std::size_t index) const;

        /**
        * Sets the file name at index
        *@param index - the index
        *@param value - the file title value
        */
        virtual void SetFileName(std::size_t index, const CString& value);

        /**
        * Gets the insertion type at index
        *@param index - the index
        *@return the insertion type, empty string if not found or on error
        */
        virtual int GetInsertionType(std::size_t index) const;

        /**
        * Sets the insertion type at index
        *@param index - the index
        *@param value - the insertion type value
        */
        virtual void SetInsertionType(std::size_t index, const int value);

        /**
        * Gets the activation type at index
        *@param index - the index
        *@return the activation type, empty string if not found or on error
        */
        virtual int GetActivationType(std::size_t index) const;

        /**
        * Sets the activation type at index
        *@param index - the index
        *@param value - the activation type value
        */
        virtual void SetActivationType(std::size_t index, const int value);

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
// PSS_ExtFiles
//---------------------------------------------------------------------------
PSS_ExtFiles::IPropSet& PSS_ExtFiles::GetExtFileSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------
std::size_t PSS_ExtFiles::GetExtFileCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------
PSS_ExtFileProperties* PSS_ExtFiles::GetProperty(std::size_t index) const
{
    if (index < GetExtFileCount())
        return m_Set.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------

#endif
