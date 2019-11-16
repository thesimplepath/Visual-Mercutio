/****************************************************************************
 * ==> PSS_HistoryFieldManager ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a history field manager for the document          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_HistoryFieldManager.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_HistoryFieldManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_HistoryFieldManager
//---------------------------------------------------------------------------
PSS_HistoryFieldManager::PSS_HistoryFieldManager()
{}
//---------------------------------------------------------------------------
PSS_HistoryFieldManager::~PSS_HistoryFieldManager()
{
    FreeList();
}
//---------------------------------------------------------------------------
void PSS_HistoryFieldManager::AddFieldHistoryValue(const CString& fieldName, const CString& value)
{
    const int  historyCount = m_FieldHistoryArray.GetSize();
          BOOL done         = FALSE;

    for (int i = 0; i < historyCount; ++i)
        if (((PSS_HistoryField*)(m_FieldHistoryArray[i]))->GetFieldName() == fieldName)
        {
            ((PSS_HistoryField*)(m_FieldHistoryArray[i]))->AddFieldValue(value);
            done = TRUE;
        }

    // if not done, this field does not exists, so create it
    if (done == FALSE)
    {
        std::unique_ptr<PSS_HistoryField> pNewField(new PSS_HistoryField());

        pNewField->SetFieldName(fieldName);
        pNewField->AddFieldValue(value);
        m_FieldHistoryArray.Add(pNewField.get());
        pNewField.release();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_HistoryFieldManager::RemoveFieldHistoryValue(const CString& fieldName, const CString& value)
{
    const int historyCount = m_FieldHistoryArray.GetSize();

    for (int i = 0; i < historyCount; ++i)
        if (((PSS_HistoryField*)(m_FieldHistoryArray[i]))->GetFieldName() == fieldName)
            return ((PSS_HistoryField*)(m_FieldHistoryArray[i]))->RemoveFieldValue(value);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_HistoryFieldManager::RemoveFieldHistory(const CString& fieldName)
{
    const int historyCount = m_FieldHistoryArray.GetSize();

    for (int i = 0; i < historyCount; ++i)
        if (((PSS_HistoryField*)(m_FieldHistoryArray[i]))->GetFieldName() == fieldName)
        {
            // delete history item
            delete m_FieldHistoryArray[i];

            // remove the item from the array
            m_FieldHistoryArray.RemoveAt(i);

            return TRUE;
        }

    return FALSE;
}
//---------------------------------------------------------------------------
PSS_HistoryField* PSS_HistoryFieldManager::FindField(const CString& fieldName)
{
    const int historyCount = m_FieldHistoryArray.GetSize();

    for (int i = 0; i < historyCount; ++i)
        if (((PSS_HistoryField*)(m_FieldHistoryArray[i]))->GetFieldName() == fieldName)
            return ((PSS_HistoryField*)(m_FieldHistoryArray[i]));

    return NULL;
}
//---------------------------------------------------------------------------
CStringArray* PSS_HistoryFieldManager::GetFieldHistory(const CString& fieldName)
{
    const int historyCount = m_FieldHistoryArray.GetSize();

    for (int i = 0; i < historyCount; ++i)
        if (((PSS_HistoryField*)(m_FieldHistoryArray[i]))->GetFieldName() == fieldName)
            return &(CStringArray&)((PSS_HistoryField*)(m_FieldHistoryArray[i]))->GetValueArray();

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_HistoryFieldManager::Serialize(CArchive& ar)
{
    m_FieldHistoryArray.Serialize(ar);
}
//---------------------------------------------------------------------------
void PSS_HistoryFieldManager::FreeList()
{
    const int historyCount = m_FieldHistoryArray.GetSize();

    // delete all allocated file objects
    for (int i = 0; i < historyCount; ++i)
        delete m_FieldHistoryArray[i];

    m_FieldHistoryArray.RemoveAll();
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void ZAHistoryFieldManager::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void ZAHistoryFieldManager::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
