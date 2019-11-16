/****************************************************************************
 * ==> PSS_HistoryField ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a history field                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_HistoryField.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_HistoryField, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_HistoryField
//---------------------------------------------------------------------------
PSS_HistoryField::PSS_HistoryField() :
    m_ReadOnly(FALSE)
{}
//---------------------------------------------------------------------------
PSS_HistoryField::PSS_HistoryField(const PSS_HistoryField& other) :
    m_ReadOnly(FALSE)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_HistoryField::~PSS_HistoryField()
{}
//---------------------------------------------------------------------------
const PSS_HistoryField& PSS_HistoryField::operator = (const PSS_HistoryField& other)
{
    const int historyCount = other.m_FieldValueHistoryArray.GetSize();

    // copy the values
    for (int i = 0; i < historyCount; ++i)
        m_FieldValueHistoryArray.Add(other.m_FieldValueHistoryArray[i]);

    m_ReadOnly  = other.m_ReadOnly;
    m_FieldName = other.m_FieldName;

    return *this;
}
//---------------------------------------------------------------------------
PSS_HistoryField* PSS_HistoryField::Clone()
{
    std::unique_ptr<PSS_HistoryField> pObject(new PSS_HistoryField(*this));
    return pObject.release();
}
//---------------------------------------------------------------------------
void PSS_HistoryField::AddFieldValue(const CString& value)
{
    const int historyCount = m_FieldValueHistoryArray.GetSize();

    // check if the value already exists
    for (int i = 0; i < historyCount; ++i)
        if (m_FieldValueHistoryArray[i] == value)
            return;

    m_FieldValueHistoryArray.Add(value);
}
//---------------------------------------------------------------------------
BOOL PSS_HistoryField::RemoveFieldValue(const CString& value)
{
    const int historyCount = m_FieldValueHistoryArray.GetSize();

    // check if the value already exists
    for (int i = 0; i < historyCount; ++i)
        if (m_FieldValueHistoryArray[i] == value)
        {
            m_FieldValueHistoryArray.RemoveAt(i);
            return TRUE;
        }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_HistoryField::FreeList()
{
    m_FieldValueHistoryArray.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_HistoryField::Serialize(CArchive& ar)
{
    m_FieldValueHistoryArray.Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
        ar << WORD(m_ReadOnly);
        ar << m_FieldName;
    }
    else
    {
        // read the elements
        WORD wValue;
        ar >> wValue;
        m_ReadOnly = wValue;

        ar >> m_FieldName;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryField::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HistoryField::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
