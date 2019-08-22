/****************************************************************************
 * ==> PSS_HistoryField ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a history field                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HistoryFieldH
#define PSS_HistoryFieldH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_HistoryField
    #define PSS_HistoryField ZAHistoryField
#endif

// mfc
#include "mfc.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* History field
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_HistoryField : public CObject
{
    DECLARE_SERIAL(PSS_HistoryField)

    public:
        typedef CObject inherited;

        PSS_HistoryField();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_HistoryField(const PSS_HistoryField& other);

        virtual ~PSS_HistoryField();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_HistoryField & operator = (const PSS_HistoryField& other);

        /**
        * Clones the history field
        *@return the cloned history field, NULL on error
        */
        virtual PSS_HistoryField* Clone();

        /**
        * Gets the value count
        *@return the value count
        */
        virtual inline std::size_t GetCount() const;

        /**
        * Adds a new historic value in the field value history array
        *@param value - field value
        */
        virtual void AddFieldValue(const CString& value);

        /**
        * Removes a specific historic value from the manager
        *@param value - historic value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL RemoveFieldValue(const CString& value);

        /**
        * Gets the value array
        *@return the value array
        */
        virtual inline const CStringArray& GetValueArray() const;

        /**
        * Checks if the field history is read-only
        *@return TRUE if the field history is read-only, otherwise FALSE
        */
        virtual inline BOOL IsReadOnly() const;

        /**
        * Sets the field history as read-only
        *@param value - if TRUE, the field history will be read-only
        */
        virtual inline void SetReadOnly(BOOL value);

        /**
        * Gets the field name
        *@return the field name
        */
        virtual inline const CString GetFieldName() const;

        /**
        * Sets the field name
        *@param value - the field name
        */
        virtual inline void SetFieldName(const CString& value);

        /**
        * Removes the history
        */
        virtual void FreeList();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    private:
        CStringArray m_FieldValueHistoryArray;
        CString      m_FieldName;
        BOOL         m_ReadOnly;
};

//---------------------------------------------------------------------------
// PSS_HistoryField
//---------------------------------------------------------------------------
std::size_t PSS_HistoryField::GetCount() const
{
    return m_FieldValueHistoryArray.GetSize();
}
//---------------------------------------------------------------------------
const CStringArray& PSS_HistoryField::GetValueArray() const
{
    return m_FieldValueHistoryArray;
}
//---------------------------------------------------------------------------
BOOL PSS_HistoryField::IsReadOnly() const
{
    return m_ReadOnly;
}
//---------------------------------------------------------------------------
void PSS_HistoryField::SetReadOnly(BOOL value)
{
    m_ReadOnly = value;
}
//---------------------------------------------------------------------------
const CString PSS_HistoryField::GetFieldName() const
{
    return m_FieldName;
}
//---------------------------------------------------------------------------
void PSS_HistoryField::SetFieldName(const CString& value)
{
    m_FieldName = value;
}
//---------------------------------------------------------------------------

#endif
