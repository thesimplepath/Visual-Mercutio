/****************************************************************************
 * ==> PSS_FieldColumn -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a field column                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FieldColumn.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_FieldColumn, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_FieldColumn
//---------------------------------------------------------------------------
PSS_FieldColumn::PSS_FieldColumn() :
    CObject(),
    m_Width(60)
{}
//---------------------------------------------------------------------------
PSS_FieldColumn::PSS_FieldColumn(const CString& headerName, const CStringArray& values) :
    CObject(),
    m_HeaderName(headerName),
    m_Width(60)
{
    const std::size_t valueCount = std::size_t(values.GetSize());

    // copy values
    for (std::size_t i = 0; i < valueCount; ++i)
        AddValue(values.GetAt(i));
}
//---------------------------------------------------------------------------
PSS_FieldColumn::PSS_FieldColumn(const CString& headerName, std::size_t width) :
    CObject(),
    m_HeaderName(headerName),
    m_Width(width)
{}
//---------------------------------------------------------------------------
PSS_FieldColumn::PSS_FieldColumn(const PSS_FieldColumn& other) :
    CObject(),
    m_Width(60)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_FieldColumn::~PSS_FieldColumn()
{}
//---------------------------------------------------------------------------
const PSS_FieldColumn& PSS_FieldColumn::operator = (const PSS_FieldColumn& other)
{
    m_HeaderName = other.m_HeaderName;
    m_Width      = other.m_Width;

    const std::size_t valueCount = std::size_t(other.GetValueCount());

    for (std::size_t i = 0; i < valueCount; ++i)
        AddValue(other.GetValueAt(i));

    return *this;
}
//---------------------------------------------------------------------------
PSS_FieldColumn* PSS_FieldColumn::Clone() const
{
    return new PSS_FieldColumn(*this);
}
//---------------------------------------------------------------------------
CString PSS_FieldColumn::GetValueAt(std::size_t index) const
{
    if (index < GetValueCount())
        return m_ValueArray.GetAt(index);

    return "";
}
//---------------------------------------------------------------------------
void PSS_FieldColumn::AddValue(const CString& value)
{
    m_ValueArray.Add(value);
}
//---------------------------------------------------------------------------
void PSS_FieldColumn::InsertValueAt(const CString& value, std::size_t index)
{
    m_ValueArray.InsertAt(index, value);
}
//---------------------------------------------------------------------------
void PSS_FieldColumn::SetValueAt(const CString& value, std::size_t index)
{
    if (index < GetValueCount())
        m_ValueArray.SetAt(index, value);
}
//---------------------------------------------------------------------------
bool PSS_FieldColumn::RemoveValue(const CString& value)
{
    const std::size_t valueCount = std::size_t(GetValueCount());

    for (std::size_t i = 0; i < valueCount; ++i)
        if (GetValueAt(i) == value)
        {
            RemoveValueAt(i);
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_FieldColumn::RemoveValueAt(std::size_t index)
{
    if (index < GetValueCount())
    {
        m_ValueArray.RemoveAt(index);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_FieldColumn::FreeValueArray()
{
    m_ValueArray.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_FieldColumn::AutoSizeColumn()
{
    m_Width = 40;
}
//---------------------------------------------------------------------------
int PSS_FieldColumn::GetValueRow(const CString& value)
{
    const std::size_t valueCount = std::size_t(GetValueCount());

    for (std::size_t i = 0; i < valueCount; ++i)
        if (GetValueAt(i) == value)
            return int(i);

    return -1;
}
//---------------------------------------------------------------------------
void PSS_FieldColumn::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_HeaderName;
        ar << WORD(m_Width);
    }
    else
    {
        // read the elements
        ar >> m_HeaderName;

        WORD wValue;
        ar >> wValue;
        m_Width = std::size_t(wValue);
    }

    m_ValueArray.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FieldColumn::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_FieldColumn::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
