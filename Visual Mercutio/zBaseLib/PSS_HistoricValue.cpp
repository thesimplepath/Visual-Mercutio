/****************************************************************************
 * ==> PSS_HistoricValue ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an historic value, which keeps an historic for a  *
 *               specific name                                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_HistoricValue.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_HistoricValue
//---------------------------------------------------------------------------
PSS_HistoricValue::PSS_HistoricValue(const CString& entityName) :
    m_EntityName(entityName)
{}
//---------------------------------------------------------------------------
PSS_HistoricValue::PSS_HistoricValue(const PSS_HistoricValue& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_HistoricValue::~PSS_HistoricValue()
{
    m_ValueHistoryArray.RemoveAll();
    m_EntityName.Empty();
}
//---------------------------------------------------------------------------
const PSS_HistoricValue& PSS_HistoricValue::operator = (const PSS_HistoricValue& other)
{
    const int valueCount = other.m_ValueHistoryArray.GetSize();

    // copy the values
    for (int i = 0; i < valueCount; ++i)
        m_ValueHistoryArray.Add(other.m_ValueHistoryArray[i]);

    m_EntityName = other.m_EntityName;

    return *this;
}
//---------------------------------------------------------------------------
PSS_HistoricValue* PSS_HistoricValue::Clone() const
{
    return new PSS_HistoricValue(*this);
}
//---------------------------------------------------------------------------
int PSS_HistoricValue::SearchHistoricValueIndex(const CString& value) const
{
    const int valueCount = m_ValueHistoryArray.GetSize();

    for (int i = 0; i < valueCount; ++i)
        if (m_ValueHistoryArray[i] == value)
            return i;

    return -1;
}
//---------------------------------------------------------------------------
void PSS_HistoricValue::AddHistoricValue(const CString& value)
{
    // check if the value already exists
    if (HistoricValueExist(value))
        return;

    // if not, add it
    m_ValueHistoryArray.Add(value);
}
//---------------------------------------------------------------------------
bool PSS_HistoricValue::RemoveHistoricValue(const CString& value)
{
    const int index = SearchHistoricValueIndex(value);

    if (index != -1)
        m_ValueHistoryArray.RemoveAt(index);

    return (index != -1);
}
//---------------------------------------------------------------------------
void PSS_HistoricValue::ClearHistoric()
{
    m_ValueHistoryArray.RemoveAll();
}
//---------------------------------------------------------------------------
CArchive& AFXAPI operator << (CArchive& ar, const PSS_HistoricValue& historic)
{
    const int count = historic.GetCount();
    ar << count;

    // serialize all values
    for (int i = 0; i < count; ++i)
        ar << historic.GetValueAt(i);

    return ar << historic.GetEntityName();
}
//---------------------------------------------------------------------------
CArchive& AFXAPI operator >> (CArchive& ar, PSS_HistoricValue& historic)
{
    int count;
    ar >> count;

    CString str;

    // serialize all values
    for (int i = 0; i < count; ++i)
        ar >> str;

    historic.AddHistoricValue(str);

    ar >> str;
    historic.SetEntityName(str);

    return ar;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    CDumpContext& AFXAPI operator << (CDumpContext& dc, const PSS_HistoricValue& historic)
    {
        dc << "\nZBHistoricValue Object:";
        dc << "\n\tCount = " << long(historic.GetCount());
        dc << "\n\tName = "  << historic.GetEntityName();

        return dc;
    }
#endif
//---------------------------------------------------------------------------
