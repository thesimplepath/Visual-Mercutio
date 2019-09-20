// ZBInputScenario.cpp: implementation of the ZBInputScenario class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBInputScenario.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_SERIAL(ZBInputScenario, CObject, g_DefVersion)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBInputScenario::ZBInputScenario(const CString Name /*= ""*/)
    : m_Name(Name)
{}

ZBInputScenario::~ZBInputScenario()
{}

void ZBInputScenario::Initialize(const CString Name)
{
    m_Name = Name;
}


ZBInputScenario::ZBInputScenario(const ZBInputScenario &right)
{
    *this = right;
}

const ZBInputScenario & ZBInputScenario::operator=(const ZBInputScenario &right)
{
    for (size_t i = 0; i < right.GetFieldCount(); ++i)
    {
        PSS_FieldInputScenario*    pElement = right.GetFieldAt(i);
        if (pElement)
            AddField(pElement->Clone());
    }
    return *this;
}


ZBInputScenario* ZBInputScenario::Clone()
{
    ZBInputScenario*    pNewObject = new ZBInputScenario(*this);
    return pNewObject;
}

inline void    ZBInputScenario::RemoveAllField()
{
    for (size_t i = 0; i < GetFieldCount(); ++i)
    {
        PSS_FieldInputScenario*    pElement = GetFieldAt(i);
        if (pElement)
            delete pElement;
    }
    m_InputFieldSet.RemoveAll();
}

size_t    ZBInputScenario::GetScenarioForUser(const CString Username, ZBInputScenario& Scenario)
{
    Scenario.RemoveAllField();
    for (size_t i = 0; i < GetFieldCount(); ++i)
    {
        PSS_FieldInputScenario*    pElement = GetFieldAt(i);
        // If same user, add the element
        if (pElement && pElement->GetUserName() == Username)
            Scenario.AddField(pElement->Clone());
    }
    return Scenario.GetFieldCount();
}

bool    ZBInputScenario::AddField(const CString Fieldname, const CString Username /*= ""*/, int Order /*= -1*/)
{
    PSS_FieldInputScenario*    pElement = new PSS_FieldInputScenario(Fieldname, Username, Order);
    if (pElement)
    {
        if (AddField(pElement))
            return true;
        // Otherwise, delete the allocated element
        delete pElement;
    }
    // Error
    return false;
}

PSS_FieldInputScenario*    ZBInputScenario::FindFieldname(const CString Fieldname) const
{
    for (size_t i = 0; i < GetFieldCount(); ++i)
    {
        PSS_FieldInputScenario*    pElement = GetFieldAt(i);
        if (pElement && pElement->GetFieldName() == Fieldname)
            return pElement;
    }
    return NULL;
}

int ZBInputScenario::FindFieldnameIndex(const CString Fieldname) const
{
    for (size_t i = 0; i < GetFieldCount(); ++i)
    {
        PSS_FieldInputScenario*    pElement = GetFieldAt(i);
        if (pElement && pElement->GetFieldName() == Fieldname)
            return i;
    }
    return -1;
}

bool ZBInputScenario::DeleteFieldname(const CString Fieldname)
{
    int    Index = FindFieldnameIndex(Fieldname);
    if (Index == -1)
        return false;
    return DeleteFieldnameAt(Index);
}

bool ZBInputScenario::DeleteFieldnameAt(size_t Index)
{
    if (Index < GetFieldCount())
    {
        PSS_FieldInputScenario*    pElement = GetFieldAt(Index);
        if (pElement)
            delete pElement;
        m_InputFieldSet.RemoveAt(Index);
    }
    return false;
}


void ZBInputScenario::Serialize(CArchive& ar)
{
    m_InputFieldSet.Serialize(ar);

    if (ar.IsStoring())
    {    // Write the elements
        ar << m_Name;
    }
    else
    {    // Read the elements
        ar >> m_Name;
    }
}
