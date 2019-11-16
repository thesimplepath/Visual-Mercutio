/****************************************************************************
 * ==> PSS_FieldColumnManager ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a field column manager                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FieldColumnManagerH
#define PSS_FieldColumnManagerH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_FieldColumnManager
    #define PSS_FieldColumnManager ZBFieldColumnManager
#endif

// mfc
#include "Mfc.h"

// processsoft
#include "PSS_FieldColumn.h"

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
* Field column manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FieldColumnManager : public CObject
{
    DECLARE_SERIAL(PSS_FieldColumnManager)

    public:
        typedef CObject inherited;

        PSS_FieldColumnManager();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FieldColumnManager(const PSS_FieldColumnManager& other);

        virtual ~PSS_FieldColumnManager();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FieldColumnManager& operator = (const PSS_FieldColumnManager& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_FieldColumnManager* Clone() const;

        /**
        * Gets the column count
        *@return the column count
        */
        virtual inline std::size_t GetCount() const;

        /**
        * Adds a new column
        *@param pColumn - column to add
        */
        virtual void AddColumn(PSS_FieldColumn* pColumn);

        /**
        * Adds a new column
        *@param headerName - header name
        *@param values - values
        */
        virtual void AddColumn(const CString& headerName, const CStringArray& values);

        /**
        * Removes a specific column from the manager
        *@param pColumn - column to add
        *@return true on success, otherwise false
        */
        virtual bool RemoveColumn(PSS_FieldColumn* pColumn);

        /**
        * Removes a specific column from the manager
        *@param headerName - header name
        *@return true on success, otherwise false
        */
        virtual bool RemoveColumn(const CString& headerName);

        /**
        * Removes all the columns
        */
        virtual void RemoveAll();

        /**
        * Searches a column
        *@param headerName - header name
        *@return the column, NULL if not found or on error
        */
        virtual PSS_FieldColumn* SearchColumn(const CString& headerName);

        /**
        * Checks if a column exists
        *@param pColumn - column to search
        *@return true if the column exists, otherwise false
        */
        virtual bool ColumnExists(PSS_FieldColumn* pColumn);

        /**
        * Gets a column at index
        *@param index - index
        *@return the column, NULL if not found or on error
        */
        virtual PSS_FieldColumn* GetColumnAt(std::size_t index) const;

        /**
        * Inserts a new column at index
        *@param pColumn - column to insert
        *@param index - index
        */
        virtual void InsertColumnAt(PSS_FieldColumn* pColumn, std::size_t index);

        /**
        * Removes a column at index
        *@param index - index
        *@return true on success, otherwise false
        */
        virtual bool RemoveColumnAt(std::size_t index);

        /**
        * Gets a row at index
        *@param[out] values - array to fill with row values
        *@param index - index
        *@return true on success, otherwise false
        */
        virtual bool GetRowValues(CStringArray& values, std::size_t index);

        /**
        * Gets a cell value
        *@param columnName - column name
        *@param rowIndex - row index
        *@param[out] value - cell value
        *@return true on success, otherwise false
        */
        virtual bool GetCellValue(const CString& columnName, std::size_t rowIndex, CString& value);

        /**
        * Gets a cell value
        *@param columnIndex - column index
        *@param rowIndex - row index
        *@param[out] value - cell value
        *@return true on success, otherwise false
        */
        virtual bool GetCellValue(std::size_t columnIndex, std::size_t rowIndex, CString& value);

        /**
        * Sets a cell value
        *@param columnName - column name
        *@param rowIndex - row index
        *@param[out] value - cell value
        *@return true on success, otherwise false
        */
        virtual bool SetCellValue(const CString& columnName, std::size_t rowIndex, const CString& value);

        /**
        * Sets a cell value
        *@param columnName - column name
        *@param rowIndex - row index
        *@param[out] value - cell value
        *@return true on success, otherwise false
        */
        virtual bool SetCellValue(std::size_t columnIndex, std::size_t rowIndex, const CString& value);

        /**
        * Auto-sizes a column
        *@param headerName - header name
        *@return true on success, otherwise false
        */
        virtual bool AutoSizeColumn(const CString& headerName);

        /**
        * Auto-sizes a column
        *@param pColumn - column
        *@return true on success, otherwise false
        */
        virtual bool AutoSizeColumn(PSS_FieldColumn* pColumn);

        /**
        * Auto-sizes a column at index
        *@param index - index
        *@return true on success, otherwise false
        */
        virtual bool AutoSizeColumnAt(std::size_t index);

        /**
        * Auto-sizes all the columns
        *@return true on success, otherwise false
        */
        virtual bool AutoSizeAllColumns();

        /**
        * Sizes a column
        *@param headerName - header name
        *@param width - column width
        *@return true on success, otherwise false
        */
        virtual bool SizeColumn(const CString& headerName, std::size_t width);

        /**
        * Sizes a column
        *@param pColumn - column
        *@param width - column width
        *@return true on success, otherwise false
        */
        virtual bool SizeColumn(PSS_FieldColumn* pColumn, std::size_t width);

        /**
        * Sizes a column at index
        *@param index - index
        *@param width - column width
        *@return true on success, otherwise false
        */
        virtual bool SizeColumnAt(std::size_t index, std::size_t width);

        /**
        * Sizes all the columns
        *@param width - column width
        *@return true on success, otherwise false
        */
        virtual bool SizeAllColumns(std::size_t width);

        /**
        * Gets the header names
        *@param[out] headerNames - array to populate with the header names
        *@return true on success, otherwise false
        */
        virtual bool GetHeaderNames(CStringArray& headerNames);

        /**
        * Creates new columns with the header names filled in a string value array
        *@param headerNames - header names
        *@return true on success, otherwise false
        */
        virtual bool CreateColumnWithHeaderNames(const CStringArray& headerNames);

        /**
        * Adds a row
        *@param rowValues - row values
        *@return true on success, otherwise false
        */
        virtual bool AddRowValues(const CStringArray& rowValues);

        /**
        * Inserts a row at index, replaces it if already exists
        *@param rowValues - row values
        *@param index - index
        *@return true on success, otherwise false
        */
        virtual bool InsertRowValuesAt(const CStringArray& rowValues, std::size_t index);

        /**
        * Sets a row at index, replaces it if already exists
        *@param rowValues - row values
        *@param index - index
        *@return true on success, otherwise false
        */
        virtual bool SetRowValuesAt(const CStringArray& rowValues, std::size_t index);

        /**
        * Removes all the column values
        *@param headerName - heander name
        *@return true on success, otherwise false
        */
        virtual bool RemoveColumnValues(const CString& headerName);

        /**
        * Removes all the column values
        *@param pColumn - column
        *@return true on success, otherwise false
        */
        virtual bool RemoveColumnValues(PSS_FieldColumn* pColumn);

        /**
        * Removes all the columns values
        */
        virtual void RemoveAllValues();

        /**
        * Removes all the column values at index
        *@param index - index
        *@return true on success, otherwise false
        */
        virtual bool RemoveColumnValuesAt(std::size_t index);

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
        CObArray m_ColumnArray;
};

//---------------------------------------------------------------------------
// PSS_FieldColumnManager
//---------------------------------------------------------------------------
std::size_t PSS_FieldColumnManager::GetCount() const
{
    return m_ColumnArray.GetSize();
}
//---------------------------------------------------------------------------

#endif
