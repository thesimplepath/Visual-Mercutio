/****************************************************************************
 * ==> PSS_FieldColumn -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a field column                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FieldColumnH
#define PSS_FieldColumnH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_FieldColumn
    #define PSS_FieldColumn ZBFieldColumn
#endif

// mfc
#include "Mfc.h"

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
* Field column
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FieldColumn : public CObject
{
    DECLARE_SERIAL(PSS_FieldColumn)

    public:
        typedef CObject inherited;

        PSS_FieldColumn();

        /**
        * Constructor
        *@param headerName - header name
        *@param values - values
        */
        PSS_FieldColumn(const CString& headerName, const CStringArray& values);

        /**
        * Constructor
        *@param headerName - header name
        *@param width - width
        */
        PSS_FieldColumn(const CString& headerName, std::size_t width = 40);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FieldColumn(const PSS_FieldColumn& other);

        virtual ~PSS_FieldColumn();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FieldColumn& operator = (const PSS_FieldColumn& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_FieldColumn* Clone() const;

        /**
        * Gets the value count
        *@return the value count
        */
        virtual inline std::size_t GetValueCount() const;

        /**
        * Gets the value at index
        *@param index - index
        *@return the value at index, empty string if not found or on error
        */
        virtual CString GetValueAt(std::size_t index) const;

        /**
        * Adds a new value
        *@param value - value
        */
        virtual void AddValue(const CString& value);

        /**
        * Inserts a new value at index
        *@param value - value
        *@param index - index
        */
        virtual void InsertValueAt(const CString& value, std::size_t index);

        /**
        * Sets a new value at index
        *@param value - value
        *@param index - index
        */
        virtual void SetValueAt(const CString& value, std::size_t index);

        /**
        * Removes a value
        *@param value - value to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveValue(const CString& value);

        /**
        * Removes a value at index
        *@param index - index
        *@return true on success, otherwise false
        */
        virtual bool RemoveValueAt(std::size_t index);

        /**
        * Gets the value array
        *@return the value array
        */
        virtual inline const CStringArray& GetValueArray() const;

        /**
        * Removes all the values
        */
        virtual void FreeValueArray();

        /**
        * Auto-sizes the column
        */
        virtual void AutoSizeColumn();

        /**
        * Gets the row index matching with a value
        *@return the row index matching with a value, -1 if not found or on error
        */
        virtual int GetValueRow(const CString& value);

        /**
        * Gets the column header name
        *@return the column header name
        */
        virtual inline const CString GetHeaderName() const;

        /**
        * Sets the column header name
        *@param value - the column header name
        */
        virtual inline void SetHeaderName(const CString& value);

        /**
        * Gets the column width
        *@return the column width
        */
        virtual inline const std::size_t GetWidth() const;

        /**
        * Sets the column width
        *@param value - the column width
        */
        virtual inline void SetWidth(std::size_t value);

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
        CString      m_HeaderName;
        CStringArray m_ValueArray;
        std::size_t  m_Width;
};

//---------------------------------------------------------------------------
// PSS_FieldColumn
//---------------------------------------------------------------------------
std::size_t PSS_FieldColumn::GetValueCount() const
{
    return m_ValueArray.GetSize();
}
//---------------------------------------------------------------------------
const CStringArray& PSS_FieldColumn::GetValueArray() const
{
    return m_ValueArray;
}
//---------------------------------------------------------------------------
const CString PSS_FieldColumn::GetHeaderName() const
{
    return m_HeaderName;
}
//---------------------------------------------------------------------------
void PSS_FieldColumn::SetHeaderName(const CString& value)
{
    m_HeaderName = value;
}
//---------------------------------------------------------------------------
const std::size_t PSS_FieldColumn::GetWidth() const
{
    return m_Width;
}
//---------------------------------------------------------------------------
void PSS_FieldColumn::SetWidth(std::size_t value)
{
    m_Width = value;
}
//---------------------------------------------------------------------------

#endif
