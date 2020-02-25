/****************************************************************************
 * ==> PSS_InputAttributes -------------------------------------------------*
 ****************************************************************************
 * Description : Provides the input attributes                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InputAttributesH
#define PSS_InputAttributesH

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
#ifndef PSS_InputAttribute
    #define PSS_InputAttribute ZBInputAttribute
#endif
#ifndef PSS_InputAttributeManager
    #define PSS_InputAttributeManager ZBInputAttributeManager
#endif

#ifdef _ZMODELBPEXPORT
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
* Input attribute
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InputAttribute : public CObject
{
    DECLARE_SERIAL(PSS_InputAttribute)

    public:
        PSS_InputAttribute();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_InputAttribute(const PSS_InputAttribute& other);

        virtual ~PSS_InputAttribute();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_InputAttribute& operator = (const PSS_InputAttribute& other);

        /**
        * Checks if the content of another object is equal to this one
        *@param other - the other object to compare with
        *@return TRUE if the other object content is equal, otherwise FALSE
        */
        inline BOOL operator == (const PSS_InputAttribute& other);

        /**
        * Checks if the content of another object differs from this one
        *@param other - the other object to compare with
        *@return TRUE if the other object content differs, otherwise FALSE
        */
        inline BOOL operator != (const PSS_InputAttribute& other);

        /**
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual PSS_InputAttribute* Dup() const;

        /**
        * Gets the category identifier
        *@return the category identifier
        */
        virtual inline int GetCategoryID() const;

        /**
        * Sets the category identifier
        *@param value - the category identifier
        */
        virtual inline void SetCategoryID(int value);

        /**
        * Gets the item identifier
        *@return the item identifier
        */
        virtual inline int GetItemID() const;

        /**
        * Sets the item identifier
        *@param value - the item identifier
        */
        virtual inline void SetItemID(int value);

        /**
        * Gets the symbol reference
        *@return the symbol reference
        */
        virtual inline int GetSymbolRef() const;

        /**
        * Sets the symbol reference
        *@param value - the symbol reference
        */
        virtual inline void SetSymbolRef(int value);

        /**
        * Gets the default value
        *@return the default value
        */
        virtual inline CString GetDefaultValue() const;

        /**
        * Sets the default value
        *@param value - the default value
        */
        virtual inline void SetDefaultValue(const CString& value);

        /**
        * Gets the flag
        *@return the flag
        */
        virtual inline int GetFlag() const;

        /**
        * Sets the flag
        *@param value - the flag
        */
        virtual inline void SetFlag(int value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CString m_DefaultValue;
        int     m_CategoryID;
        int     m_ItemID;
        int     m_SymbolRef;
        int     m_Flag;
};

//---------------------------------------------------------------------------
// PSS_InputAttribute
//---------------------------------------------------------------------------
BOOL PSS_InputAttribute::operator == (const PSS_InputAttribute& other)
{
    return (GetCategoryID() == other.GetCategoryID() &&
            GetItemID()     == other.GetItemID());
}
//---------------------------------------------------------------------------
BOOL PSS_InputAttribute::operator != (const PSS_InputAttribute& other)
{
    return (GetCategoryID() != other.GetCategoryID() ||
            GetItemID()     != other.GetItemID());
}
//---------------------------------------------------------------------------
int PSS_InputAttribute::GetCategoryID() const
{
    return m_CategoryID;
}
//---------------------------------------------------------------------------
void PSS_InputAttribute::SetCategoryID(int value)
{
    m_CategoryID = value;
}
//---------------------------------------------------------------------------
int PSS_InputAttribute::GetItemID() const
{
    return m_ItemID;
}
//---------------------------------------------------------------------------
void PSS_InputAttribute::SetItemID(int value)
{
    m_ItemID = value;
}
//---------------------------------------------------------------------------
int PSS_InputAttribute::GetSymbolRef() const
{
    return m_SymbolRef;
}
//---------------------------------------------------------------------------
void PSS_InputAttribute::SetSymbolRef(int value)
{
    m_SymbolRef = value;
}
//---------------------------------------------------------------------------
CString PSS_InputAttribute::GetDefaultValue() const
{
    return m_DefaultValue;
}
//---------------------------------------------------------------------------
void PSS_InputAttribute::SetDefaultValue(const CString& value)
{
    m_DefaultValue = value;
}
//---------------------------------------------------------------------------
int PSS_InputAttribute::GetFlag() const
{
    return m_Flag;
}
//---------------------------------------------------------------------------
void PSS_InputAttribute::SetFlag(int value)
{
    m_Flag = value;
}
//---------------------------------------------------------------------------

/**
* Input attribute manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InputAttributeManager : public CObject
{
    DECLARE_SERIAL(PSS_InputAttributeManager)

    public:
        typedef CCArray_T <PSS_InputAttribute*, PSS_InputAttribute*> IInputAttributeSet;
        typedef Iterator_T<PSS_InputAttribute*>                      IInputAttributeIterator;

        PSS_InputAttributeManager();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_InputAttributeManager(const PSS_InputAttributeManager& other);

        virtual ~PSS_InputAttributeManager();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_InputAttributeManager& operator = (const PSS_InputAttributeManager& other);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual PSS_InputAttributeManager* Dup() const;

        /**
        * Gets the input attribute set
        *@return the input attribute set
        */
        virtual inline IInputAttributeSet& GetInputAttributeSet();

        /**
        * Deletes all the input attributes
        */
        virtual void DeleteAllInputAttributes();

        /**
        * Gets the input attribute at index
        *@param index - the index
        *@return the input attribute, NULL if not found or on error
        */
        virtual inline PSS_InputAttribute* GetInputAttributeAt(std::size_t index);

        /**
        * Gets the input attribute count
        *@return the input attribute count
        */
        virtual inline std::size_t GetInputAttributeCount() const;

        /**
        * Adds an input attribute
        *@param pInputAttribute - the input attribute to add
        *@param replaceExisting - if true, the attribute will replace the existing one, if any
        */
        virtual void AddInputAttribute(PSS_InputAttribute* pInputAttribute, bool replaceExisting = true);

        /**
        * Checks if the input attribute exists
        *@param pInputAttribute - the input attribute to check
        *@return true if the input attribute exists, otherwise false
        */
        virtual bool Exist(PSS_InputAttribute* pInputAttribute);

        /**
        * Deletes an input attribute
        *@param pInputAttribute - the input attribute to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteInputAttribute(PSS_InputAttribute* pInputAttribute);

        /**
        * Finds an input attribute
        *@param categoryID - the category identifier
        *@param itemID - the item identifier
        *@param symbolRef - the symbol reference
        *@return the input attribute, NULL if not found or on error
        */
        virtual PSS_InputAttribute* FindInputAttribute(int categoryID, int itemID, int symbolRef);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        IInputAttributeSet m_Set;

        /**
        * Replaces the input attribute
        *@param pInputAttribute - the input attribute
        */
        void ReplaceInputAttribute(PSS_InputAttribute* pInputAttribute);
};

//---------------------------------------------------------------------------
// PSS_InputAttributeManager
//---------------------------------------------------------------------------
PSS_InputAttributeManager::IInputAttributeSet& PSS_InputAttributeManager::GetInputAttributeSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------
PSS_InputAttribute* PSS_InputAttributeManager::GetInputAttributeAt(std::size_t index)
{
    if (index < GetInputAttributeCount())
        return m_Set.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------
std::size_t PSS_InputAttributeManager::GetInputAttributeCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------

#endif
