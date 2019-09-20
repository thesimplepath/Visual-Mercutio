/****************************************************************************
 * ==> PSS_FieldColumnManager ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a field column manager                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FieldColumnManager.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_FieldColumnManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_FieldColumnManager
//---------------------------------------------------------------------------
PSS_FieldColumnManager::PSS_FieldColumnManager() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_FieldColumnManager::PSS_FieldColumnManager(const PSS_FieldColumnManager& other) :
    CObject()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_FieldColumnManager::~PSS_FieldColumnManager()
{}
//---------------------------------------------------------------------------
const PSS_FieldColumnManager& PSS_FieldColumnManager::operator = (const PSS_FieldColumnManager& other)
{
    for (std::size_t i = 0; i < other.GetCount(); ++i)
        if (other.GetColumnAt(i))
            AddColumn(other.GetColumnAt(i)->Clone());

    return *this;
}
//---------------------------------------------------------------------------
PSS_FieldColumnManager* PSS_FieldColumnManager::Clone() const
{
    return new PSS_FieldColumnManager(*this);
}
//---------------------------------------------------------------------------
void PSS_FieldColumnManager::AddColumn(PSS_FieldColumn* pColumn)
{
    if (!pColumn)
        return;

    m_ColumnArray.Add(pColumn);
}
//---------------------------------------------------------------------------
void PSS_FieldColumnManager::AddColumn(const CString& headerName, const CStringArray& values)
{
    AddColumn(new PSS_FieldColumn(headerName, values));
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::RemoveColumn(PSS_FieldColumn* pColumn)
{
    const std::size_t count = GetCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_FieldColumn* pCurCol = GetColumnAt(i);

        if (pCurCol && pCurCol == pColumn)
            return RemoveColumnAt(i);
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::RemoveColumn(const CString& headerName)
{
    const std::size_t count = GetCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_FieldColumn* pCurCol = GetColumnAt(i);

        if (pCurCol && pCurCol->GetHeaderName() == headerName)
            return RemoveColumnAt(i);
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_FieldColumnManager::RemoveAll()
{
    const std::size_t count = GetCount();

    // delete columns
    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_FieldColumn* pCurCol = GetColumnAt(i);

        if (pCurCol)
            delete pCurCol;
    }

    // remove all items
    m_ColumnArray.RemoveAll();
}
//---------------------------------------------------------------------------
PSS_FieldColumn* PSS_FieldColumnManager::SearchColumn(const CString& headerName)
{
    const std::size_t count = GetCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_FieldColumn* pCurCol = GetColumnAt(i);

        if (pCurCol && pCurCol->GetHeaderName() == headerName)
            return GetColumnAt(i);
    }

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::ColumnExists(PSS_FieldColumn* pColumn)
{
    const std::size_t count = GetCount();

    for (size_t i = 0; i < count; ++i)
    {
        PSS_FieldColumn* pCurCol = GetColumnAt(i);

        if (pCurCol && pCurCol == pColumn)
            return true;
    }

    return false;
}
//---------------------------------------------------------------------------
PSS_FieldColumn* PSS_FieldColumnManager::GetColumnAt(std::size_t index) const
{
    if (index < GetCount())
        return static_cast<PSS_FieldColumn*>(m_ColumnArray.GetAt(index));

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_FieldColumnManager::InsertColumnAt(PSS_FieldColumn* pColumn, std::size_t index)
{
    if (!pColumn)
        return;

    m_ColumnArray.InsertAt(index, pColumn);
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::RemoveColumnAt(std::size_t index)
{
    if (index < GetCount())
    {
        PSS_FieldColumn* pColumn = GetColumnAt(index);

        // delete column
        if (pColumn)
            delete pColumn;

        // remove column item
        m_ColumnArray.RemoveAt(index);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::GetRowValues(CStringArray& values, std::size_t index)
{
    values.RemoveAll();

    const std::size_t count = GetCount();

    // no columns, return false
    if (!count)
        return false;

    // check the row index, if out of bounds, return false
    if (GetColumnAt(0)->GetValueCount() < index)
        return false;

    // iterate through all columns and fill the array with the row value
    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_FieldColumn* pColumn = GetColumnAt(i);

        if (!pColumn)
            return false;

        values.Add(pColumn->GetValueAt(index));
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::GetCellValue(const CString& columnName, std::size_t rowIndex, CString& value)
{
    PSS_FieldColumn* pFieldColumn = SearchColumn(columnName);

    if (pFieldColumn)
    {
        if (!(rowIndex < pFieldColumn->GetValueCount()))
            return false;

        value = pFieldColumn->GetValueAt(rowIndex);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::GetCellValue(std::size_t columnIndex, size_t rowIndex, CString& value)
{
    PSS_FieldColumn* pFieldColumn = GetColumnAt(columnIndex);

    if (pFieldColumn)
    {
        if (!(rowIndex < pFieldColumn->GetValueCount()))
            return false;

        value = pFieldColumn->GetValueAt(rowIndex);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::SetCellValue(const CString& columnName, std::size_t rowIndex, const CString& value)
{
    PSS_FieldColumn* pFieldColumn = SearchColumn(columnName);

    if (pFieldColumn)
    {
        if (!(rowIndex < pFieldColumn->GetValueCount()))
            return false;

        pFieldColumn->SetValueAt(value, rowIndex);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::SetCellValue(std::size_t columnIndex, std::size_t rowIndex, const CString& value)
{
    PSS_FieldColumn* pFieldColumn = GetColumnAt(columnIndex);

    if (pFieldColumn)
    {
        if (!(rowIndex < pFieldColumn->GetValueCount()))
            return false;

        pFieldColumn->SetValueAt(value, rowIndex);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::AutoSizeColumn(const CString& headerName)
{
    PSS_FieldColumn* pFieldColumn = SearchColumn(headerName);

    if (pFieldColumn)
    {
        pFieldColumn->AutoSizeColumn();
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::AutoSizeColumn(PSS_FieldColumn* pColumn)
{
    if (pColumn)
    {
        pColumn->AutoSizeColumn();
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::AutoSizeColumnAt(std::size_t index)
{
    PSS_FieldColumn* pFieldColumn = GetColumnAt(index);

    if (pFieldColumn)
    {
        pFieldColumn->AutoSizeColumn();
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::AutoSizeAllColumns()
{
    const std::size_t count = GetCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_FieldColumn* pColumn = GetColumnAt(i);

        if (pColumn)
            pColumn->AutoSizeColumn();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::SizeColumn(const CString& headerName, std::size_t width)
{
    PSS_FieldColumn* pFieldColumn = SearchColumn(headerName);

    if (pFieldColumn)
    {
        pFieldColumn->SetWidth(width);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::SizeColumn(PSS_FieldColumn* pColumn, std::size_t width)
{
    if (pColumn)
    {
        pColumn->SetWidth(width);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::SizeColumnAt(std::size_t index, std::size_t width)
{
    PSS_FieldColumn* pFieldColumn = GetColumnAt(index);

    if (pFieldColumn)
    {
        pFieldColumn->SetWidth(width);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::SizeAllColumns(std::size_t width)
{
    const std::size_t count = GetCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_FieldColumn* pColumn = GetColumnAt(i);

        if (pColumn)
            pColumn->SetWidth(width);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::GetHeaderNames(CStringArray& headerNames)
{
    headerNames.RemoveAll();

    const std::size_t count = GetCount();

    // no columns, return false
    if (!count)
        return false;

    // iterate through all columns and fill the array with the row value
    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_FieldColumn* pColumn = GetColumnAt(i);

        if (!pColumn)
            return false;

        headerNames.Add(pColumn->GetHeaderName());
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::CreateColumnWithHeaderNames(const CStringArray& headerNames)
{
    const std::size_t headerCount = std::size_t(headerNames.GetSize());

    for (std::size_t i = 0; i < headerCount; ++i)
    {
        std::unique_ptr<PSS_FieldColumn> pFieldColumn(new PSS_FieldColumn(headerNames.GetAt(i)));

        if (!pFieldColumn.get())
            return false;

        AddColumn(pFieldColumn.get());
        pFieldColumn.release();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::AddRowValues(const CStringArray& rowValues)
{
    if (!GetCount())
        return false;

    const std::size_t rowCount = std::size_t(rowValues.GetSize());

    for (std::size_t i = 0; i < rowCount; ++i)
    {
        PSS_FieldColumn* pColumn = GetColumnAt(i);

        if (!pColumn)
            return false;

        pColumn->AddValue(rowValues.GetAt(i));
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::InsertRowValuesAt(const CStringArray& rowValues, std::size_t index)
{
    if (!(index < GetCount()))
        return false;

    const std::size_t rowCount = std::size_t(rowValues.GetSize());

    for (std::size_t i = 0; i < rowCount; ++i)
    {
        PSS_FieldColumn* pColumn = GetColumnAt(i);

        if (!pColumn)
            return false;
        
        GetColumnAt(i)->InsertValueAt(rowValues.GetAt(i), index);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::SetRowValuesAt(const CStringArray& rowValues, std::size_t index)
{
    if (!(index < GetCount()))
        return false;

    const std::size_t rowCount = std::size_t(rowValues.GetSize());

    for (std::size_t i = 0; i < rowCount; ++i)
    {
        PSS_FieldColumn* pColumn = GetColumnAt(i);

        if (!pColumn)
            return false;
        
        GetColumnAt(i)->SetValueAt(rowValues.GetAt(i), index);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::RemoveColumnValues(const CString& headerName)
{
    PSS_FieldColumn* pFieldColumn = SearchColumn(headerName);

    if (pFieldColumn)
    {
        pFieldColumn->FreeValueArray();
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::RemoveColumnValues(PSS_FieldColumn* pColumn)
{
    if (pColumn)
    {
        pColumn->FreeValueArray();
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_FieldColumnManager::RemoveAllValues()
{
    const std::size_t count = GetCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_FieldColumn* pColumn = GetColumnAt(i);

        if (pColumn)
            pColumn->FreeValueArray();
    }
}
//---------------------------------------------------------------------------
bool PSS_FieldColumnManager::RemoveColumnValuesAt(std::size_t index)
{
    PSS_FieldColumn* pFieldColumn = GetColumnAt(index);

    if (pFieldColumn)
    {
        pFieldColumn->FreeValueArray();
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_FieldColumnManager::Serialize(CArchive& ar)
{
    m_ColumnArray.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FieldColumnManager::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FieldColumnManager::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
