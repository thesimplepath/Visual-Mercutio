/****************************************************************************
 * ==> PSS_InputScenario ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an input scenario                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InputScenario.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_InputScenario, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_InputScenario
//---------------------------------------------------------------------------
PSS_InputScenario::PSS_InputScenario(const CString& name) :
    m_Name(name)
{}
//---------------------------------------------------------------------------
PSS_InputScenario::PSS_InputScenario(const PSS_InputScenario& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_InputScenario::~PSS_InputScenario()
{}
//---------------------------------------------------------------------------
const PSS_InputScenario& PSS_InputScenario::operator = (const PSS_InputScenario& other)
{
    const std::size_t fieldCount = other.GetFieldCount();

    for (std::size_t i = 0; i < fieldCount; ++i)
    {
        PSS_FieldInputScenario* pElement = other.GetFieldAt(i);

        if (pElement)
            AddField(pElement->Clone());
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_InputScenario* PSS_InputScenario::Clone() const
{
    return new PSS_InputScenario(*this);
}
//---------------------------------------------------------------------------
void PSS_InputScenario::Initialize(const CString& name)
{
    m_Name = name;
}
//---------------------------------------------------------------------------
void PSS_InputScenario::RemoveAllField()
{
    const std::size_t fieldCount = GetFieldCount();

    for (std::size_t i = 0; i < fieldCount; ++i)
    {
        PSS_FieldInputScenario* pElement = GetFieldAt(i);

        if (pElement)
            delete pElement;
    }

    m_InputFieldSet.RemoveAll();
}
//---------------------------------------------------------------------------
PSS_FieldInputScenario* PSS_InputScenario::SearchFieldName(const CString& fieldName) const
{
    const std::size_t fieldCount = GetFieldCount();

    for (std::size_t i = 0; i < fieldCount; ++i)
    {
        PSS_FieldInputScenario* pElement = GetFieldAt(i);

        if (pElement && pElement->GetFieldName() == fieldName)
            return pElement;
    }

    return NULL;
}
//---------------------------------------------------------------------------
int PSS_InputScenario::SearchFieldNameIndex(const CString& fieldName) const
{
    const std::size_t fieldCount = GetFieldCount();

    for (std::size_t i = 0; i < fieldCount; ++i)
    {
        PSS_FieldInputScenario* pElement = GetFieldAt(i);

        if (pElement && pElement->GetFieldName() == fieldName)
            return i;
    }

    return -1;
}
//---------------------------------------------------------------------------
bool PSS_InputScenario::AddField(const CString& fieldName, const CString& userName, int order)
{
    PSS_FieldInputScenario* pElement = new PSS_FieldInputScenario(fieldName, userName, order);

    if (pElement)
    {
        if (AddField(pElement))
            return true;

        // delete the allocated element
        delete pElement;
    }

    // error
    return false;
}
//---------------------------------------------------------------------------
bool PSS_InputScenario::DeleteFieldName(const CString& fieldName)
{
    const int index = SearchFieldNameIndex(fieldName);

    if (index == -1)
        return false;

    return DeleteFieldNameAt(index);
}
//---------------------------------------------------------------------------
bool PSS_InputScenario::DeleteFieldNameAt(std::size_t index)
{
    if (index < GetFieldCount())
    {
        PSS_FieldInputScenario* pElement = GetFieldAt(index);

        if (pElement)
            delete pElement;

        m_InputFieldSet.RemoveAt(index);
    }

    return false;
}
//---------------------------------------------------------------------------
std::size_t PSS_InputScenario::GetScenarioForUser(const CString& userName, PSS_InputScenario& scenario)
{
    scenario.RemoveAllField();

    for (std::size_t i = 0; i < GetFieldCount(); ++i)
    {
        PSS_FieldInputScenario* pElement = GetFieldAt(i);

        // if same user, add the element
        if (pElement && pElement->GetUserName() == userName)
            scenario.AddField(pElement->Clone());
    }

    return scenario.GetFieldCount();
}
//---------------------------------------------------------------------------
void PSS_InputScenario::Serialize(CArchive& ar)
{
    m_InputFieldSet.Serialize(ar);

    if (ar.IsStoring())
        // write the elements
        ar << m_Name;
    else
        // read the elements
        ar >> m_Name;
}
//---------------------------------------------------------------------------
