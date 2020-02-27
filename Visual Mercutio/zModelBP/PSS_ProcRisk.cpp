/****************************************************************************
 * ==> PSS_ProcRisk --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the procedures for risks                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcRisk.h"

// processsoft
#include "PSS_RiskPropertiesBP.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int g_LastDeliveryIDProperties = ZS_BP_PROP_RISK + 39;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ProcRisk, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ProcRisk
//---------------------------------------------------------------------------
PSS_ProcRisk::PSS_ProcRisk(CODSymbolComponent* pParent) :
    CObject(),
    m_pParent(pParent)
{}
//---------------------------------------------------------------------------
PSS_ProcRisk::PSS_ProcRisk(const PSS_ProcRisk& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ProcRisk::~PSS_ProcRisk()
{
    RemoveAllRisks();
}
//---------------------------------------------------------------------------
PSS_ProcRisk& PSS_ProcRisk::operator = (const PSS_ProcRisk& other)
{
    IRiskPropertiesIterator it(&const_cast<PSS_ProcRisk&>(other).GetRiskSet());

    // copy the members
    for (PSS_RiskPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        AddRisk(pProp->Dup());

    m_pParent = other.m_pParent;

    return *this;
}
//---------------------------------------------------------------------------
PSS_ProcRisk* PSS_ProcRisk::Dup() const
{
    return new PSS_ProcRisk(*this);
}
//---------------------------------------------------------------------------
bool PSS_ProcRisk::CreateInitialProperties()
{
    if (GetRiskCount() > 0)
        return true;

    std::unique_ptr<PSS_RiskPropertiesBP> pProps(new PSS_RiskPropertiesBP());

    if (AddRisk(pProps.get()) >= 0)
    {
        pProps.release();
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcRisk::SetParent(CODSymbolComponent* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
int PSS_ProcRisk::AddNewRisk()
{
    std::unique_ptr<PSS_RiskPropertiesBP> pProps(new PSS_RiskPropertiesBP());

    const int index = AddRisk(pProps.get());
    pProps.release();

    return index;
}
//---------------------------------------------------------------------------
int PSS_ProcRisk::AddRisk(PSS_RiskPropertiesBP* pProperty)
{
    if (pProperty)
    {
        // if no risk name defined, set one by default
        if (pProperty->GetRiskName().IsEmpty())
            pProperty->SetRiskName(GetNextRiskValidName());

        m_Set.Add(pProperty);

        // return the index
        return GetRiskCount() - 1;
    }

    return -1;
}
//---------------------------------------------------------------------------
bool PSS_ProcRisk::DeleteRisk(std::size_t index)
{
    if (index < GetRiskCount())
    {
        PSS_RiskPropertiesBP* pProperty = GetProperty(index);

        if (pProperty)
        {
            m_Set.RemoveAt(index);
            delete pProperty;
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcRisk::DeleteRisk(PSS_RiskPropertiesBP* pProperty)
{
    IRiskPropertiesIterator it(&m_Set);

    for (PSS_RiskPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProperty == pProp)
        {
            it.Remove();
            delete pProp;
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcRisk::RiskNameExist(const CString& name) const
{
    IRiskPropertiesIterator it(&m_Set);

    // iterate through the risks and build the string
    for (PSS_RiskPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetRiskName() == name)
            return true;

    return false;
}
//---------------------------------------------------------------------------
CString PSS_ProcRisk::GetNextRiskValidName() const
{
    CString str;
    int     i = 1;

    do
    {
        str.Format(_T("Risque %d"), i);
        ++i;
    }
    while (RiskNameExist(str));

    return str;
}
//---------------------------------------------------------------------------
void PSS_ProcRisk::RemoveAllRisks()
{
    IRiskPropertiesIterator it(&m_Set);

    for (PSS_RiskPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    // remove all elements
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
CString PSS_ProcRisk::GetRiskName(std::size_t index) const
{
    if (index < GetRiskCount())
        return m_Set.GetAt(index)->GetRiskName();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcRisk::SetRiskName(std::size_t index, const CString& value)
{
    if (index < GetRiskCount())
        m_Set.GetAt(index)->SetRiskName(value);
}
//---------------------------------------------------------------------------
CString PSS_ProcRisk::GetRiskDesc(std::size_t index) const
{
    if (index < GetRiskCount())
        return m_Set.GetAt(index)->GetRiskDesc();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcRisk::SetRiskDesc(std::size_t index, const CString& value)
{
    if (index < GetRiskCount())
        m_Set.GetAt(index)->SetRiskDesc(value);
}
//---------------------------------------------------------------------------
CString PSS_ProcRisk::GetRiskType(std::size_t index) const
{
    if (index < GetRiskCount())
        return m_Set.GetAt(index)->GetRiskType();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcRisk::SetRiskType(std::size_t index, const CString& value)
{
    if (index < GetRiskCount())
        m_Set.GetAt(index)->SetRiskType(value);
}
//---------------------------------------------------------------------------
int PSS_ProcRisk::GetRiskImpact(std::size_t index) const
{
    if (index < GetRiskCount())
        return m_Set.GetAt(index)->GetRiskImpact();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_ProcRisk::SetRiskImpact(std::size_t index, int value)
{
    if (index < GetRiskCount())
        m_Set.GetAt(index)->SetRiskImpact(value);
}
//---------------------------------------------------------------------------
int PSS_ProcRisk::GetRiskProbability(std::size_t index) const
{
    if (index < GetRiskCount())
        return m_Set.GetAt(index)->GetRiskProbability();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_ProcRisk::SetRiskProbability(std::size_t index, int value)
{
    if (index < GetRiskCount())
        m_Set.GetAt(index)->SetRiskProbability(value);
}
//---------------------------------------------------------------------------
int PSS_ProcRisk::GetRiskSeverity(std::size_t index) const
{
    if (index < GetRiskCount())
        return m_Set.GetAt(index)->GetRiskSeverity();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_ProcRisk::SetRiskSeverity(std::size_t index, int value)
{
    if (index < GetRiskCount())
        m_Set.GetAt(index)->SetRiskSeverity(value);
}
//---------------------------------------------------------------------------
float PSS_ProcRisk::GetRiskUE(std::size_t index) const
{
    if (index < GetRiskCount())
        return m_Set.GetAt(index)->GetRiskUE();

    return 0.0f;
}
//---------------------------------------------------------------------------
void PSS_ProcRisk::SetRiskUE(std::size_t index, float value)
{
    if (index < GetRiskCount())
        m_Set.GetAt(index)->SetRiskUE(value);
}
//---------------------------------------------------------------------------
float PSS_ProcRisk::GetRiskPOA(std::size_t index) const
{
    if (index < GetRiskCount())
        return m_Set.GetAt(index)->GetRiskPOA();

    return 0.0f;
}
//---------------------------------------------------------------------------
void PSS_ProcRisk::SetRiskPOA(std::size_t index, float value)
{
    if (index < GetRiskCount())
        m_Set.GetAt(index)->SetRiskPOA(value);
}
//---------------------------------------------------------------------------
bool PSS_ProcRisk::GetRiskAction(std::size_t index) const
{
    if (index < GetRiskCount())
        return m_Set.GetAt(index)->GetRiskAction();

    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcRisk::SetRiskAction(std::size_t index, bool value)
{
    if (index < GetRiskCount())
        m_Set.GetAt(index)->SetRiskAction(value);
}
//---------------------------------------------------------------------------
void PSS_ProcRisk::Serialize(CArchive& ar)
{
    // only if the object is serialize from or to a document
    if (ar.m_pDocument)
        if (ar.IsStoring())
        {
            TRACE(_T("PSS_ProcRisk::Serialize - Start save\n"));

            // serialize the size
            ar << int(m_Set.GetSize());

            IRiskPropertiesIterator it(&m_Set);

            for (PSS_RiskPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                ar << pProp;

            TRACE(_T("PSS_ProcRisk::Serialize - End save\n"));
        }
        else
        {
            TRACE(_T("PSS_ProcRisk::Serialize - Start read\n"));

            RemoveAllRisks();

            // read the size
            int count;
            ar >> count;

            PSS_RiskPropertiesBP* pProp;

            for (int i = 0; i < count; ++i)
            {
                ar >> pProp;
                AddRisk(pProp);
            }

            TRACE(_T("PSS_ProcRisk::Serialize - End read\n"));
        }
}
//---------------------------------------------------------------------------
