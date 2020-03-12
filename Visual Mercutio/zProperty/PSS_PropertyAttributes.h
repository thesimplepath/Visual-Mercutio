/****************************************************************************
 * ==> PSS_PropertyAttributes ----------------------------------------------*
 ****************************************************************************
 * Description : Provides the property attributes                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertyAttributesH
#define PSS_PropertyAttributesH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "ZIProperties.h"

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
* Property attributes
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PropertyAttributes
{
    public:
        /**
        * Property attribute
        */
        class AFX_EXT_CLASS IAttribute
        {
            public:
                /**
                * Constructor
                *@param categoryID - the category identifier
                *@param itemID - the item identifier
                */
                IAttribute(int categoryID = -1, int itemID = -1);

                /**
                * Copy constructor
                *@param other - other object to copy from
                */
                IAttribute(IAttribute& other);

                virtual inline ~IAttribute();

                /**
                * Copy operator
                *@param other - other object to copy from
                *@return copy of itself
                */
                const IAttribute& operator = (const IAttribute& other);

                /**
                * Stores from the archive to the attribute
                *@param ar - the archive
                *@param attribute - the attribute
                *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
                */
                AFX_EXT_API friend CArchive& operator >> (CArchive& ar, IAttribute& attribute);

                /**
                * Stores the attribute to the archive
                *@param ar - the archive
                *@param attribute - the attribute
                *@return archive, to allow operator to be chained with other items, e.g a << b << c
                */
                AFX_EXT_API friend CArchive& operator << (CArchive& ar, const IAttribute& attribute);

                /**
                * Clones the object
                *@return the cloned object, NULL on error
                */
                virtual IAttribute* Clone();

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

            private:
                int m_CategoryID;
                int m_ItemID;
        };

        typedef CCArray_T <IAttribute*, IAttribute*> IAttributeSet;
        typedef Iterator_T<IAttribute*>              IAttributeIterator;

        PSS_PropertyAttributes();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PropertyAttributes(PSS_PropertyAttributes& other);

        virtual ~PSS_PropertyAttributes();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PropertyAttributes& operator = (const PSS_PropertyAttributes& other);

        /**
        * Stores from the archive to the attributes
        *@param ar - the archive
        *@param attributes - the attributes
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_PropertyAttributes& attributes);

        /**
        * Stores the attributes to the archive
        *@param ar - the archive
        *@param attributes - the attributes
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, const PSS_PropertyAttributes& attributes);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_PropertyAttributes* Clone();

        /**
        * Loads the states from the initialization file
        *@param iniFile - the initialization file name
        *@param objectID - the object identifier
        *@return true on success, otherwise false
        */
        virtual bool LoadStateFromIniFile(const CString& iniFile, int objectID);

        /**
        * Saves the states to the initialization file
        *@param iniFile - the initialization file name
        *@param objectID - the object identifier
        *@return true on success, otherwise false
        */
        virtual bool SaveStateToIniFile(const CString& iniFile, int objectID);

        /**
        * Deletes the attributes from the initialization file
        *@param iniFile - the initialization file name
        *@param objectID - the object identifier
        *@return true on success, otherwise false
        */
        virtual bool DeleteAttributesFromIniFile(const CString& iniFile, int objectID);

        /**
        * Gets the attribute set
        *@return the attribute set
        */
        virtual inline       IAttributeSet& GetAttributeSet();
        virtual inline const IAttributeSet& GetAttributeSet() const;

        /**
        * Removes all the attributes
        */
        virtual void RemoveAllAttributes();

        /**
        * Gets the attribute count
        *@return the attribute count
        */
        virtual inline std::size_t GetAttributeCount() const;

        /**
        * Gets the attribute at index
        *@return the attribute at index
        */
        virtual inline IAttribute* GetAttributeAt(std::size_t index);

        /**
        * Adds an attribute
        *@param pAttribute - the attribute to add
        */
        virtual void AddAttribute(IAttribute* pAttribute);

        /**
        * Adds an attribute
        *@param categoryID - the category identifier
        *@param itemID - the item identifier
        */
        virtual inline void AddAttribute(int categoryID, int itemID = -1);

        /**
        * Adds an attribute at index
        *@param index - the index
        *@param pAttribute - the attribute to add
        */
        virtual void AddAttributeAt(std::size_t index, IAttribute* pAttribute);

        /**
        * Adds an attribute at index
        *@param index - the index
        *@param categoryID - the category identifier
        *@param itemID - the item identifier
        */
        virtual inline void AddAttributeAt(std::size_t index, int categoryID, int itemID = -1);

        /**
        * Deletes an attribute
        *@param categoryID - the category identifier
        *@param itemID - the item identifier
        */
        virtual bool DeleteAttribute(int categoryID, int itemID);

        /**
        * Deletes all the attributes belonging to a category
        *@param categoryID - the category identifier
        */
        virtual void DeleteCategoryAttribute(int categoryID);

        /**
        * Deletes an attribute at index
        *@param index - the index
        */
        virtual bool DeleteAttributeAt(std::size_t index);

        /**
        * Finds an attribute
        *@param categoryID - the category identifier
        *@param itemID - the item identifier
        *@return the attribute, NULL if not found or on error
        */
        virtual IAttribute* FindAttribute(int categoryID, int itemID);

        /**
        * Checks if an attribute exists
        *@param categoryID - the category identifier
        *@param itemID - the item identifier
        *@return true if the attribute exists, otherwise false
        */
        virtual inline bool AttributeExist(int categoryID, int itemID);

        /**
        * Checks if the argument matches an attribute
        *@param propAttributes - the property attributes to search in
        *@param argument - the argument to search
        *@param caseSensitive - if true, the search will be case sensitive
        *@param partialSearch - if true, the search will be partial
        *@return true the argument matches an attribute, otherwise false
        */
        virtual bool Match(ZBPropertySet& propAttributes,
                           const CString& argument,
                           bool           caseSensitive = false,
                           bool           partialSearch = false);

        /**
        * Gets the attributes as a string
        *@param pPropAttributes - the property attributes to search in
        *@param keepOnlyNotEmpty - if true, only the filled attributes will be kept
        *@return the attributes as a string
        */
        virtual CString GetString(ZBPropertySet* pPropAttributes, bool keepOnlyNotEmpty = true);

        /**
        * Gets if the title text is shown
        *@return true if the title text is shown, otherwise false
        */
        virtual inline bool GetShowTitleText() const;

        /**
        * Sets if the title text is shown
        *@param value - if true, the title text will be shown
        */
        virtual inline void SetShowTitleText(bool value);

    private:
        IAttributeSet m_AttributeSet;
        bool          m_ShowTitleText;
};

//---------------------------------------------------------------------------
// PSS_PropertyAttributes::IAttribute
//---------------------------------------------------------------------------
PSS_PropertyAttributes::IAttribute::~IAttribute()
{}
//---------------------------------------------------------------------------
int PSS_PropertyAttributes::IAttribute::GetCategoryID() const
{
    return m_CategoryID;
}
//---------------------------------------------------------------------------
void PSS_PropertyAttributes::IAttribute::SetCategoryID(int value)
{
    m_CategoryID = value;
}
//---------------------------------------------------------------------------
int PSS_PropertyAttributes::IAttribute::GetItemID() const
{
    return m_ItemID;
}
//---------------------------------------------------------------------------
void PSS_PropertyAttributes::IAttribute::SetItemID(int value)
{
    m_ItemID = value;
}
//---------------------------------------------------------------------------
// PSS_PropertyAttributes
//---------------------------------------------------------------------------
PSS_PropertyAttributes::IAttributeSet& PSS_PropertyAttributes::GetAttributeSet()
{
    return m_AttributeSet;
}
//---------------------------------------------------------------------------
const PSS_PropertyAttributes::IAttributeSet& PSS_PropertyAttributes::GetAttributeSet() const
{
    return m_AttributeSet;
}
//---------------------------------------------------------------------------
std::size_t PSS_PropertyAttributes::GetAttributeCount() const
{
    return m_AttributeSet.GetSize();
}
//---------------------------------------------------------------------------
PSS_PropertyAttributes::IAttribute* PSS_PropertyAttributes::GetAttributeAt(std::size_t index)
{
    if (index < GetAttributeCount())
        return m_AttributeSet.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_PropertyAttributes::AddAttribute(int categoryID, int itemID)
{
    AddAttribute(new IAttribute(categoryID, itemID));
}
//---------------------------------------------------------------------------
void PSS_PropertyAttributes::AddAttributeAt(std::size_t index, int categoryID, int itemID)
{
    if (index < GetAttributeCount())
        AddAttributeAt(index, new IAttribute(categoryID, itemID));
    else
        AddAttribute(categoryID, itemID);
}
//---------------------------------------------------------------------------
bool PSS_PropertyAttributes::AttributeExist(int categoryID, int itemID)
{
    return FindAttribute(categoryID, itemID);
}
//---------------------------------------------------------------------------
bool PSS_PropertyAttributes::GetShowTitleText() const
{
    return m_ShowTitleText;
}
//---------------------------------------------------------------------------
void PSS_PropertyAttributes::SetShowTitleText(bool value)
{
    m_ShowTitleText = value;
}
//---------------------------------------------------------------------------

#endif
