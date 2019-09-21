/****************************************************************************
 * ==> PSS_HistoricValueManager --------------------------------------------*
 ****************************************************************************
 * Description : Provides an historic value manager                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"

// ZBHistoricValueManager
#include "PSS_HistoricValueManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_HistoricValueManager
//---------------------------------------------------------------------------
PSS_HistoricValueManager::PSS_HistoricValueManager()
{}
//---------------------------------------------------------------------------
PSS_HistoricValueManager::PSS_HistoricValueManager(const PSS_HistoricValueManager& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_HistoricValueManager::~PSS_HistoricValueManager()
{
    PSS_HistoricValueManager::ClearHistoric();
}
//---------------------------------------------------------------------------
const PSS_HistoricValueManager& PSS_HistoricValueManager::operator = (const PSS_HistoricValueManager& other)
{
    // set the iterator to the right entity set
    PSS_HistoricValueIterator i(&other.GetHistoricEntitySetConst());

    for (PSS_HistoricValue* pHistoricValue = i.GetFirst(); pHistoricValue; pHistoricValue = i.GetNext())
        Add(pHistoricValue->Clone());

    return *this;
}
//---------------------------------------------------------------------------
void PSS_HistoricValueManager::AddHistoryValue(const CString& fieldName, const CString& value)
{
    PSS_HistoricValue* pHistoricValue = SearchHistoricEntity(fieldName);

    // if not found, create a new entity
    if (!pHistoricValue)
    {
        pHistoricValue = new PSS_HistoricValue(fieldName);
        ASSERT(pHistoricValue);

        // Add it to the array of entity value
        m_HistoricValueSet.Add(pHistoricValue);
    }

    // add the new historic value to the field        
    pHistoricValue->AddHistoricValue(value);
}
//---------------------------------------------------------------------------
bool PSS_HistoricValueManager::Remove(PSS_HistoricValue* pValue)
{
    if (!pValue)
        return false;

    const int index = SearchHistoricEntityIndex(pValue->GetEntityName());

    if (index == -1)
        return false;

    RemoveAt(index);
    return true;
}
//---------------------------------------------------------------------------
bool PSS_HistoricValueManager::RemoveHistoryValue(const CString& fieldName, const CString& value)
{
    PSS_HistoricValue* pHistoricValue = SearchHistoricEntity(fieldName);

    if (pHistoricValue)
        return pHistoricValue->RemoveHistoricValue(value);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_HistoricValueManager::RemoveFullHistory(const CString& fieldName)
{
    PSS_HistoricValue* pHistoricValue = SearchHistoricEntity(fieldName);

    if (pHistoricValue)
    {
        pHistoricValue->ClearHistoric();
        return true;
    }

    return true;
}
//---------------------------------------------------------------------------
int PSS_HistoricValueManager::SearchHistoricEntityIndex(const CString& fieldName) const
{
    int index = 0;

    PSS_HistoricValueIterator i(&GetHistoricEntitySetConst());

    for (PSS_HistoricValue* pHistoricValue = i.GetFirst(); pHistoricValue; pHistoricValue = i.GetNext(), ++index)
        if (pHistoricValue->GetEntityName() == fieldName)
            return index;

    return -1;
}
//---------------------------------------------------------------------------
CStringArray* PSS_HistoricValueManager::GetFieldHistory(const CString& fieldName)
{
    PSS_HistoricValue* pHistoricValue = SearchHistoricEntity(fieldName);

    if (pHistoricValue)
        return const_cast<CStringArray*>(&(pHistoricValue->GetValueArray()));

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_HistoricValueManager::ClearHistoric()
{
    PSS_HistoricValueIterator i(&GetHistoricEntitySet());

    // delete all allocated file objects
    for (PSS_HistoricValue* pHistoricValue = i.GetFirst(); pHistoricValue; pHistoricValue = i.GetNext())
        delete pHistoricValue;

    m_HistoricValueSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_HistoricValueManager::RemoveAt(std::size_t index)
{
    PSS_HistoricValue* pValue = GetHistoricEntityAt(index);

    if (pValue)
    {
        delete pValue;
        m_HistoricValueSet.RemoveAt(index);
    }
}
//---------------------------------------------------------------------------
CArchive& AFXAPI operator << (CArchive& ar, const PSS_HistoricValueManager& historicManager)
{
    const int count = historicManager.GetCount();
    ar << count;

    PSS_HistoricValueIterator i(&historicManager.GetHistoricEntitySetConst());

    // serialize all values
    for (PSS_HistoricValue* pHistoricValue = i.GetFirst(); pHistoricValue; pHistoricValue = i.GetNext())
        ar << *pHistoricValue;

    return ar;
}
//---------------------------------------------------------------------------
CArchive& AFXAPI operator>>(CArchive& ar, PSS_HistoricValueManager& historicManager)
{
    int count;
    ar >> count;

    // serialize all values
    for (int i = 0; i < count; i++)
    {
        std::unique_ptr<PSS_HistoricValue> pHistoricEntity(new PSS_HistoricValue());
        ar >> *pHistoricEntity;
        historicManager.Add(pHistoricEntity.get());
        pHistoricEntity.release();
    }

    return ar;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    CDumpContext& AFXAPI operator<<(CDumpContext& dc, const PSS_HistoricValueManager& historicManager)
    {
        dc << "\nZBHistoricValueManager Object:";
        dc << "\n\tCount = " << (long)historicManager.GetCount();

        PSS_HistoricValueIterator i(&historicManager.GetHistoricEntitySetConst());

        for (PSS_HistoricValue* pHistoricValue = i.GetFirst(); pHistoricValue; pHistoricValue = i.GetNext())
            dc << "\n\tName = " << pHistoricValue->GetEntityName();

        return dc;
    }
#endif
//---------------------------------------------------------------------------
