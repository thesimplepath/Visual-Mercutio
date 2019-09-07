/****************************************************************************
 * ==> PSS_PLFNMultiColumn -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a financial plan multi-columns object             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PLFNMultiColumnH
#define PSS_PLFNMultiColumnH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PLFNMultiColumn
    //#define PSS_PLFNMultiColumn PLFNMultiColumn
#endif

// processsoft
#include "ZAObject.h"
#include "ZBFldClM.h"

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
* Financial plan multi-columns object
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PLFNMultiColumn : public PlanFinObject
{
    DECLARE_SERIAL(PSS_PLFNMultiColumn)

    public:
        typedef PlanFinObject inherited;

        PSS_PLFNMultiColumn();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PLFNMultiColumn(const PSS_PLFNMultiColumn& other);

        virtual ~PSS_PLFNMultiColumn();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNMultiColumn& operator = (const PSS_PLFNMultiColumn& other);

        /**
        * Copy operator
        *@param pOther - other object to copy from
        *@return copy of itself
        */
        const PSS_PLFNMultiColumn& operator = (const PSS_PLFNMultiColumn* pOther);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PlanFinObject* Clone() const;

        /**
        * Copies the object content
        *@param pSrc - source object to copy from
        */
        virtual void CopyObject(PlanFinObject* pSrc);

        /**
        * Gets the right sub-menu
        *@return the right sub-menu identifier
        */
        virtual inline UINT GetRightSubMenu() const;

        /**
        * Gets the tab list that should be shown when the user asks for object properties
        *@return the tab list identifier
        */
        virtual inline UINT GetPropertyTabs() const;

        /**
        * Draws the object with the current DC
        *@param pDC - device context to draw to
        *@param pView - view
        */
        virtual void DrawObject(CDC* pDC, ZIView* pView);

        /**
        * Gets the column count
        *@return the column count
        */
        virtual inline std::size_t GetColumnCount() const;

        /**
        * Adds a new column in the column array
        *@param pColumn - column to add
        */
        virtual inline void AddColumn(ZBFieldColumn* pColumn);

        /**
        * Adds a new column in the column array
        *@param headerName - header name
        *@param values - values
        */
        virtual inline void AddColumn(const CString& headerName, const CStringArray& values);

        /**
        * Removes a specific column from the manager
        *@param headerName - header name
        *@return true on success, otherwise false
        */
        virtual inline bool RemoveColumn(const CString& headerName);

        /**
        * Removes a specific column from the manager
        *@param pColumn - column
        *@return true on success, otherwise false
        */
        virtual inline bool RemoveColumn(ZBFieldColumn* pColumn);

        /**
        * Removes all the columns
        */
        virtual inline void RemoveAllColumns();

        /**
        * Finds a column by its header name
        *@param headerName - header name
        *@return the column, NULL if not found on error
        */
        virtual inline ZBFieldColumn* FindColumn(const CString& headerName);

        /**
        * Finds a column by its column pointer
        *@param pColumn - column
        *@return true if the column was found, otherwise false
        */
        virtual inline bool FindColumn(ZBFieldColumn* pColumn);

        /**
        * Gets a column at a specific position
        *@param index - index
        *@return the column, NULL if not found or on error
        */
        virtual inline ZBFieldColumn* GetColumnAt(std::size_t index) const;

        /**
        * Inserts a new column at a specific position
        *@param pColumn - column to insert
        *@param index - index
        */
        virtual inline void InsertColumnAt(ZBFieldColumn* pColumn, std::size_t index);

        /**
        * Removes a column at a specific position
        *@param index - index
        *@return true on success, otherwise false
        */
        virtual inline bool RemoveColumnAt(std::size_t index);

        /**
        * Gets row values
        *@param[out] rowValues - row values to populate
        *@param rowIndex - row index
        *@return true on success, otherwise false
        */
        virtual inline bool GetRowValues(CStringArray& rowValues, std::size_t rowIndex);

        /**
        * Gets the value of a specific column and row
        *@param columnName - column name
        *@param rowIndex - row index
        *@param[out] value - value
        *@return true on success, otherwise false
        */
        virtual inline bool GetColumnRowValue(const CString& columnName, std::size_t rowIndex, CString& value);

        /**
        * Gets the value of a specific column and row
        *@param columnIndex - column index
        *@param rowIndex - row index
        *@param[out] value - value
        *@return true on success, otherwise false
        */
        virtual inline bool GetColumnRowValue(std::size_t columnIndex, std::size_t rowIndex, CString& value);

        /**
        * Sets a value to a specific column and row
        *@param columnName - column name
        *@param rowIndex - row index
        *@param[out] value - value
        *@return true on success, otherwise false
        */
        virtual inline bool SetColumnRowValue(const CString& columnName, std::size_t rowIndex, const CString& value);

        /**
        * Sets a value to a specific column and row
        *@param columnIndex - column index
        *@param rowIndex - row index
        *@param[out] value - value
        *@return true on success, otherwise false
        */
        virtual inline bool SetColumnRowValue(std::size_t columnIndex, std::size_t rowIndex, const CString& value);

        /**
        * Checks if the object is selected
        *@param point - hit point in pixels
        *@return TRUE if the object is selected, otherwise FALSE
        */
        virtual inline BOOL IsSelected(const CPoint& point) const;

        /**
        * Auto-sizes a specific column from the manager
        *@param headerName - header name
        *@return true on success, otherwise false
        */
        virtual inline bool AutoSizeColumn(const CString& headerName);

        /**
        * Auto-sizes a specific column from the manager
        *@param pColumn - column
        *@return true on success, otherwise false
        */
        virtual inline bool AutoSizeColumn(ZBFieldColumn* pColumn);

        /**
        * Auto-sizes a specific column from the manager
        *@param index - column index
        *@return true on success, otherwise false
        */
        virtual inline bool AutoSizeColumnAt(std::size_t index);

        /**
        * Auto-sizes all the columns from the manager
        *@return true on success, otherwise false
        */
        virtual inline bool AutoSizeAllColumns();

        /**
        * Sizes a specific column from the manager
        *@param headerName - header name
        *@param width - column width in pixels
        *@return true on success, otherwise false
        */
        virtual inline bool SizeColumn(const CString& HeaderName, std::size_t width);

        /**
        * Sizes a specific column from the manager
        *@param pColumn - column
        *@param width - column width in pixels
        *@return true on success, otherwise false
        */
        virtual inline bool SizeColumn(ZBFieldColumn* pColumn, std::size_t width);

        /**
        * Sizes a specific column from the manager
        *@param index - index
        *@param width - column width in pixels
        *@return true on success, otherwise false
        */
        virtual inline bool SizeColumnAt(std::size_t index, std::size_t width);

        /**
        * Sizes all the columns from the manager
        *@param width - columns width in pixels
        *@return true on success, otherwise false
        */
        virtual inline bool SizeAllColumns(std::size_t width);

        /**
        * Gets the header names
        *@param[out] headerNames - string array to populate with header names
        *@return true on success, otherwise false
        */
        virtual inline bool GetHeaderNames(CStringArray& headerNames);

        /**
        * Creates new columns with the header names filled in a string value array
        *@param headerNames - header names
        *@return true on success, otherwise false
        */
        virtual inline bool CreateColumnWithHeaderNames(const CStringArray& headerNames);

        /**
        * Adds a complete row values from a string value array
        *@param rowValues - row values
        *@return true on success, otherwise false
        */
        virtual inline bool AddRowValues(const CStringArray& rowValues);

        /**
        * Inserts a complete row values at a specific index from a string value array
        *@param rowValues - row values
        *@param rowIndex - row index
        *@return true on success, otherwise false
        *@note The values will be replaced if the row already exists
        */
        virtual inline bool InsertRowValuesAt(const CStringArray& rowValues, std::size_t rowIndex);

        /**
        * Sets a complete row values at a specific index from a string value array
        *@param rowValues - row values
        *@param rowIndex - row index
        *@return true on success, otherwise false
        *@note The values will be replaced if the row already exists
        */
        virtual inline bool SetRowValuesAt(const CStringArray& rowValues, std::size_t rowIndex);

        /**
        * Removes all values of a specific column from the manager
        *@param headerName - header name
        *@return true on success, otherwise false
        */
        virtual inline bool RemoveColumnValues(const CString& headerName);

        /**
        * Removes all values of a specific column from the manager
        *@param pColumn - column
        *@return true on success, otherwise false
        */
        virtual inline bool RemoveColumnValues(ZBFieldColumn* pColumn);

        /**
        * Removes all the values of all columns
        */
        virtual inline void RemoveAllValues();

        /**
        * Removes all values of a column at a specific position
        *@param index - index
        *@return true on success, otherwise false
        */
        virtual inline bool RemoveColumnValuesAt(std::size_t index);

        /**
        * Gets if the header is shown
        *@return TRUE if the header is shown, otherwise FALSE
        */
        virtual inline const BOOL GetShowHeader() const;

        /**
        * Sets if the header is shown
        *@param value - if TRUE, the header is shown
        */
        virtual inline void SetShowHeader(BOOL value);

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
        ZBFieldColumnManager m_MultiColumnManager;
        BOOL                 m_ShowHeader;
};

//---------------------------------------------------------------------------
// PSS_PLFNMultiColumn
//---------------------------------------------------------------------------
UINT PSS_PLFNMultiColumn::GetRightSubMenu() const
{
    return g_MultiColumnRightSubMenu;
}
//---------------------------------------------------------------------------
UINT PSS_PLFNMultiColumn::GetPropertyTabs() const
{
    return (PropertyGeneralBasicPage | PropertySizePage | PropertyMultiColumnPage);
}
//---------------------------------------------------------------------------
std::size_t PSS_PLFNMultiColumn::GetColumnCount() const
{
    return m_MultiColumnManager.GetCount();
}
//---------------------------------------------------------------------------
void PSS_PLFNMultiColumn::AddColumn(ZBFieldColumn* pColumn)
{
    m_MultiColumnManager.AddColumn(pColumn);
}
//---------------------------------------------------------------------------
void PSS_PLFNMultiColumn::AddColumn(const CString& headerName, const CStringArray& values)
{
    m_MultiColumnManager.AddColumn(headerName, values);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::RemoveColumn(const CString& headerName)
{
    return m_MultiColumnManager.RemoveColumn(headerName);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::RemoveColumn(ZBFieldColumn* pColumn)
{
    return m_MultiColumnManager.RemoveColumn(pColumn);
}
//---------------------------------------------------------------------------
void PSS_PLFNMultiColumn::RemoveAllColumns()
{
    m_MultiColumnManager.RemoveAll();
}
//---------------------------------------------------------------------------
ZBFieldColumn* PSS_PLFNMultiColumn::FindColumn(const CString& headerName)
{
    return m_MultiColumnManager.FindColumn(headerName);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::FindColumn(ZBFieldColumn* pColumn)
{
    return m_MultiColumnManager.FindColumn(pColumn);
}
//---------------------------------------------------------------------------
ZBFieldColumn* PSS_PLFNMultiColumn::GetColumnAt(std::size_t index) const
{
    return m_MultiColumnManager.GetColumnAt(index);
}
//---------------------------------------------------------------------------
void PSS_PLFNMultiColumn::InsertColumnAt(ZBFieldColumn* pColumn, std::size_t index)
{
    m_MultiColumnManager.InsertColumnAt(pColumn, index);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::RemoveColumnAt(std::size_t index)
{
    return m_MultiColumnManager.RemoveColumnAt(index);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::GetRowValues(CStringArray& rowValues, std::size_t rowIndex)
{
    return m_MultiColumnManager.GetRowValues(rowValues, rowIndex);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::GetColumnRowValue(const CString& columnName, std::size_t rowIndex, CString& value)
{
    return m_MultiColumnManager.GetColumnRowValue(columnName, rowIndex, value);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::GetColumnRowValue(std::size_t columnIndex, std::size_t rowIndex, CString& value)
{
    return m_MultiColumnManager.GetColumnRowValue(columnIndex, rowIndex, value);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::SetColumnRowValue(const CString& columnName, std::size_t rowIndex, const CString& value)
{
    return m_MultiColumnManager.SetColumnRowValue(columnName, rowIndex, value);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::SetColumnRowValue(std::size_t columnIndex, std::size_t rowIndex, const CString& value)
{
    return m_MultiColumnManager.SetColumnRowValue(columnIndex, rowIndex, value);
}
//---------------------------------------------------------------------------
BOOL PSS_PLFNMultiColumn::IsSelected(const CPoint& point) const
{
    return m_rctObject.PtInRect(point);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::AutoSizeColumn(const CString& headerName)
{
    return m_MultiColumnManager.AutoSizeColumn(headerName);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::AutoSizeColumn(ZBFieldColumn* pColumn)
{
    return m_MultiColumnManager.AutoSizeColumn(pColumn);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::AutoSizeColumnAt(std::size_t index)
{
    return m_MultiColumnManager.AutoSizeColumnAt(index);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::AutoSizeAllColumns()
{
    return m_MultiColumnManager.AutoSizeAllColumns();
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::SizeColumn(const CString& headerName, std::size_t width)
{
    return m_MultiColumnManager.SizeColumn(headerName, width);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::SizeColumn(ZBFieldColumn* pColumn, std::size_t width)
{
    return m_MultiColumnManager.SizeColumn(pColumn, width);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::SizeColumnAt(std::size_t index, std::size_t width)
{
    return m_MultiColumnManager.SizeColumnAt(index, width);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::SizeAllColumns(std::size_t width)
{
    return m_MultiColumnManager.SizeAllColumns(width);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::GetHeaderNames(CStringArray& headerNames)
{
    return m_MultiColumnManager.GetHeaderNames(headerNames);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::CreateColumnWithHeaderNames(const CStringArray& headerNames)
{
    return m_MultiColumnManager.CreateColumnWithHeaderNames(headerNames);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::AddRowValues(const CStringArray& rowValues)
{
    return m_MultiColumnManager.AddRowValues(rowValues);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::InsertRowValuesAt(const CStringArray& rowValues, std::size_t rowIndex)
{
    return m_MultiColumnManager.InsertRowValuesAt(rowValues, rowIndex);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::SetRowValuesAt(const CStringArray& rowValues, size_t rowIndex)
{
    return m_MultiColumnManager.SetRowValuesAt(rowValues, rowIndex);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::RemoveColumnValues(const CString& headerName)
{
    return m_MultiColumnManager.RemoveColumnValues(headerName);
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::RemoveColumnValues(ZBFieldColumn* pColumn)
{
    return m_MultiColumnManager.RemoveColumnValues(pColumn);
}
//---------------------------------------------------------------------------
void PSS_PLFNMultiColumn::RemoveAllValues()
{
    m_MultiColumnManager.RemoveAllValues();
}
//---------------------------------------------------------------------------
bool PSS_PLFNMultiColumn::RemoveColumnValuesAt(std::size_t index)
{
    return m_MultiColumnManager.RemoveColumnValuesAt(index);
}
//---------------------------------------------------------------------------
const BOOL PSS_PLFNMultiColumn::GetShowHeader() const
{
    return m_ShowHeader;
}
//---------------------------------------------------------------------------
void PSS_PLFNMultiColumn::SetShowHeader(BOOL value)
{
    m_ShowHeader = value;
}
//---------------------------------------------------------------------------

#endif
