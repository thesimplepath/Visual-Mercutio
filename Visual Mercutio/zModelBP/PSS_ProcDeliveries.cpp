/****************************************************************************
 * ==> PSS_ProcDeliveries --------------------------------------------------*
 ****************************************************************************
 * Description : Provides the procedures for deliveries                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcDeliveries.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "PSS_DeliveriesPropertiesBP.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int g_LastDeliveryIDProperties = ZS_BP_PROP_DELIVERIES + 39;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ProcDeliveries, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ProcDeliveries
//---------------------------------------------------------------------------
PSS_ProcDeliveries::PSS_ProcDeliveries(CODSymbolComponent* pParent) :
    CObject(),
    m_pParent(pParent)
{}
//---------------------------------------------------------------------------
PSS_ProcDeliveries::PSS_ProcDeliveries(const PSS_ProcDeliveries& other) :
    CObject(),
    m_pParent(NULL)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ProcDeliveries::~PSS_ProcDeliveries()
{
    RemoveAllDeliveries();
}
//---------------------------------------------------------------------------
PSS_ProcDeliveries& PSS_ProcDeliveries::operator = (const PSS_ProcDeliveries& other)
{
    IDeliveriesPropertiesIterator it(&const_cast<PSS_ProcDeliveries&>(other).GetDeliverySet());

    // copy the members
    for (PSS_DeliveriesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        AddDelivery(pProp->Dup());

    m_pParent = other.m_pParent;

    return *this;
}
//---------------------------------------------------------------------------
PSS_ProcDeliveries* PSS_ProcDeliveries::Dup() const
{
    return new PSS_ProcDeliveries(*this);
}
//---------------------------------------------------------------------------
bool PSS_ProcDeliveries::CreateInitialProperties()
{
    if (GetDeliveriesCount() > 0)
        return true;

    std::unique_ptr<PSS_DeliveriesPropertiesBP> pProps(new PSS_DeliveriesPropertiesBP());

    if (AddDelivery(pProps.get()) >= 0)
    {
        pProps.release();
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcDeliveries::SetParent(CODSymbolComponent* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
int PSS_ProcDeliveries::AddNewDelivery()
{
    std::unique_ptr<PSS_DeliveriesPropertiesBP> pProps(new PSS_DeliveriesPropertiesBP());

    const int result = AddDelivery(pProps.get());
    pProps.release();

    return result;
}
//---------------------------------------------------------------------------
int PSS_ProcDeliveries::AddDelivery(PSS_DeliveriesPropertiesBP* pProperty)
{
    if (pProperty)
    {
        // if no delivery name defined, set one by default
        if (pProperty->GetDeliveryName().IsEmpty())
            pProperty->SetDeliveryName(GetNextDeliveryValidName());

        m_Set.Add(pProperty);

        // return the index
        return GetDeliveriesCount() - 1;
    }

    return -1;
}
//---------------------------------------------------------------------------
bool PSS_ProcDeliveries::DeleteDelivery(std::size_t index)
{
    if (index < GetDeliveriesCount())
    {
        PSS_DeliveriesPropertiesBP* pProperty = GetProperty(index);

        if (pProperty)
        {
            delete pProperty;
            m_Set.RemoveAt(index);
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcDeliveries::DeleteDelivery(PSS_DeliveriesPropertiesBP* pProperty)
{
    IDeliveriesPropertiesIterator it(&m_Set);

    for (PSS_DeliveriesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProperty == pProp)
        {
            delete pProp;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcDeliveries::DeliveryNameExist(const CString& name) const
{
    IDeliveriesPropertiesIterator it(&m_Set);

    // iterate through the set and build the string
    for (PSS_DeliveriesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetDeliveryName() == name)
            return true;

    return false;
}
//---------------------------------------------------------------------------
CString PSS_ProcDeliveries::GetNextDeliveryValidName() const
{
    CString str;
    int     i = 1;

    do
    {
        str.Format(_T("Livr %d"), i);
        ++i;
    }
    while (DeliveryNameExist(str) == true);

    return str;
}
//---------------------------------------------------------------------------
CString PSS_ProcDeliveries::GetAvailableDeliverables(const CString& allDeliverables) const
{
    // get the allocated deliverables
    const CString allocatedDeliverables = GetAllocatedDeliverables();

    // initialize the tokens with ; as separator
    PSS_Tokenizer srcToken;
    PSS_Tokenizer dstToken;
    CString       str = srcToken.GetFirstToken(allDeliverables);

    // iterate through all deliverables and check wich one is available
    while (!str.IsEmpty())
    {
        // if the token is not in the allocated deliverable string, add it to the destination token string
        if (!IsDeliverableInString(allocatedDeliverables, str))
            dstToken.AddToken(str);

        // get the next token
        str = srcToken.GetNextToken();
    }

    // return the available deliverables string
    return dstToken.GetString();
}
//---------------------------------------------------------------------------
CString PSS_ProcDeliveries::GetAllocatedDeliverables() const
{
    // initialize the token with ; as separator
    PSS_Tokenizer token;

    IDeliveriesPropertiesIterator it(&m_Set);

    // iterate through the set and build the string
    for (PSS_DeliveriesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        // add the deliverables
        token.AddToken(pProp->GetDeliveryDeliverables());

    // return the built string
    return token.GetString();
}
//---------------------------------------------------------------------------
bool PSS_ProcDeliveries::IsDeliverableInString(const CString& deliverables, const CString& value) const
{
    // initialize the token with ; as separator
    PSS_Tokenizer token;
    CString       str = token.GetFirstToken(deliverables);

    // iterate through all tokens
    while (!str.IsEmpty())
    {
        // if the deliverable was found, return true
        if (str == value)
            return true;

        // get the next token
        str = token.GetNextToken();
    }

    return false;
}
//---------------------------------------------------------------------------
PSS_DeliveriesPropertiesBP* PSS_ProcDeliveries::LocateDeliveryOfDeliverable(const CString& deliverableName) const
{
    const int index = LocateDeliveryIndexOfDeliverable(deliverableName);

    if (index == -1)
        return NULL;

    return GetProperty(index);
}
//---------------------------------------------------------------------------
int PSS_ProcDeliveries::LocateDeliveryIndexOfDeliverable(const CString& deliverableName) const
{
    IDeliveriesPropertiesIterator it(&m_Set);
    int                           index = 0;

    // iterate through the deliverables and check if found a matching deliverable
    for (PSS_DeliveriesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext(), ++index)
        if (IsDeliverableInString(pProp->GetDeliveryDeliverables(), deliverableName))
            return index;

    return -1;
}
//---------------------------------------------------------------------------
PSS_DeliveriesPropertiesBP* PSS_ProcDeliveries::LocateDeliveryOfMain(const CString& main) const
{
    const int index = LocateDeliveryIndexOfMain(main);

    if (index == -1)
        return NULL;

    return GetProperty(index);
}
//---------------------------------------------------------------------------
int PSS_ProcDeliveries::LocateDeliveryIndexOfMain(const CString& main) const
{
    IDeliveriesPropertiesIterator it(&m_Set);
    int                           index = 0;

    // iterate through the deliverables and check if a matching deliverable was found
    for (PSS_DeliveriesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext(), ++index)
        if (!pProp->GetDeliveryMain().IsEmpty() && pProp->GetDeliveryMain() == main)
            return index;

    return -1;
}
//---------------------------------------------------------------------------
bool PSS_ProcDeliveries::ReplaceDeliverable(const CString& oldDeliverableName, const CString& newDeliverableName)
{
    const int index  = LocateDeliveryIndexOfDeliverable(oldDeliverableName);
    bool      result = false;

    if (index != -1)
    {
        // remove the old deliverable
        if (!RemoveDeliveryDeliverable(index, oldDeliverableName))
            return false;

        // add the new name and return the status
        result = AddDeliveryDeliverable(index, newDeliverableName);
    }

    PSS_DeliveriesPropertiesBP* pDelivery = LocateDeliveryOfMain(oldDeliverableName);

    if (pDelivery)
    {
        // set the new deliverable name
        pDelivery->SetDeliveryMain(newDeliverableName);
        result = true;
    }

    return result;
}
//---------------------------------------------------------------------------
bool PSS_ProcDeliveries::DeleteDeliverableFromAllDeliveries(const CString& deliverableName)
{
    const int index  = LocateDeliveryIndexOfDeliverable(deliverableName);
    bool      result = false;

    if (index != -1)
        // remove the old deliverable
        if (!RemoveDeliveryDeliverable(index, deliverableName))
            return false;

    PSS_DeliveriesPropertiesBP* pDelivery = LocateDeliveryOfMain(deliverableName);

    if (pDelivery)
    {
        // set the new deliverable name
        pDelivery->SetDeliveryMain(_T(""));
        result = true;
    }

    return result;
}
//---------------------------------------------------------------------------
void PSS_ProcDeliveries::RemoveAllDeliveries()
{
    IDeliveriesPropertiesIterator it(&m_Set);

    for (PSS_DeliveriesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    // remove all elements
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
CString PSS_ProcDeliveries::GetDeliveryName(std::size_t index) const
{
    if (index < GetDeliveriesCount())
        return m_Set.GetAt(index)->GetDeliveryName();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcDeliveries::SetDeliveryName(std::size_t index, const CString& value)
{
    if (index < GetDeliveriesCount())
        m_Set.GetAt(index)->SetDeliveryName(value);
}
//---------------------------------------------------------------------------
CString PSS_ProcDeliveries::GetDeliveryDeliverables(std::size_t index) const
{
    if (index < GetDeliveriesCount())
        return m_Set.GetAt(index)->GetDeliveryDeliverables();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcDeliveries::SetDeliveryDeliverables(std::size_t index, const CString& value)
{
    if (index < GetDeliveriesCount())
        m_Set.GetAt(index)->SetDeliveryDeliverables(value);
}
//---------------------------------------------------------------------------
bool PSS_ProcDeliveries::AddDeliveryDeliverable(std::size_t index, const CString& value)
{
    const CString deliverables = GetDeliveryDeliverables(index);

    // initialize the token with ; as separator
    PSS_Tokenizer token;
    CString       str   = token.GetFirstToken(deliverables);
    bool          found = false;

    // iterate through all tokens
    while (!str.IsEmpty())
    {
        // if the deliverable was found, set the found flag to true
        if (str == value)
        {
            found = true;
            break;
        }

        // get the next token
        str = token.GetNextToken();
    }

    // if not found, add it
    if (!found)
    {
        token.InitializeString(deliverables);
        token.AddToken(value);

        // set the new deliverable string
        SetDeliveryDeliverables(index, token.GetString());
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcDeliveries::RemoveDeliveryDeliverable(std::size_t index, const CString& value)
{
    const CString deliverables = GetDeliveryDeliverables(index);

    // initialize the tokens with ; as separator
    PSS_Tokenizer srcToken;
    PSS_Tokenizer dstToken;
    CString       str   = srcToken.GetFirstToken(deliverables);
    bool          found = false;

    // iterate through all tokens
    while (!str.IsEmpty())
    {
        // if the deliverable was found, set the found flag to true and skip it
        if (str == value)
            found = true;
        else
            // otherwise, can be added to the destination token
            dstToken.AddToken(str);

        // get the next token
        str = srcToken.GetNextToken();
    }

    // if found, set the string
    if (found)
    {
        // set the new deliverable string
        SetDeliveryDeliverables(index, dstToken.GetString());
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcDeliveries::RemoveAllDeliveryDeliverable(std::size_t index)
{
    SetDeliveryDeliverables(index, _T(""));
    return true;
}
//---------------------------------------------------------------------------
float PSS_ProcDeliveries::GetDeliveryQuantity(std::size_t index) const
{
    if (index < GetDeliveriesCount())
        return m_Set.GetAt(index)->GetDeliveryQuantity();

    return 0.0f;
}
//---------------------------------------------------------------------------
void PSS_ProcDeliveries::SetDeliveryQuantity(std::size_t index, const float value)
{
    if (index < GetDeliveriesCount())
        m_Set.GetAt(index)->SetDeliveryQuantity(value);
}
//---------------------------------------------------------------------------
float PSS_ProcDeliveries::GetDeliveryPercentage(std::size_t index) const
{
    if (index < GetDeliveriesCount())
        return m_Set.GetAt(index)->GetDeliveryPercentage();

    return 0.0f;
}
//---------------------------------------------------------------------------
void PSS_ProcDeliveries::SetDeliveryPercentage(std::size_t index, const float value)
{
    if (index < GetDeliveriesCount())
        m_Set.GetAt(index)->SetDeliveryPercentage(value);
}
//---------------------------------------------------------------------------
CString PSS_ProcDeliveries::GetDeliveryMain(std::size_t index) const
{
    if (index < GetDeliveriesCount())
        return m_Set.GetAt(index)->GetDeliveryMain();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcDeliveries::SetDeliveryMain(std::size_t index, const CString& value)
{
    if (index < GetDeliveriesCount())
        m_Set.GetAt(index)->SetDeliveryMain(value);
}
//---------------------------------------------------------------------------
void PSS_ProcDeliveries::Serialize(CArchive& ar)
{
    // only if the object is serialize from or to a document
    if (ar.m_pDocument)
        if (ar.IsStoring())
        {
            TRACE("PSS_ProcDeliveries::Serialize - Start save\n");

            // serialize the size
            ar << int(m_Set.GetSize());

            IDeliveriesPropertiesIterator it(&m_Set);

            for (PSS_DeliveriesPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                ar << pProp;

            TRACE("PSS_ProcDeliveries::Serialize - End save\n");
        }
        else
        {
            TRACE("PSS_ProcDeliveries::Serialize - Start read\n");

            RemoveAllDeliveries();

            // read the size
            int count;
            ar >> count;

            PSS_DeliveriesPropertiesBP* pProp;

            for (int i = 0; i < count; ++i)
            {
                ar >> pProp;
                AddDelivery(pProp);
            }

            TRACE("PSS_ProcDeliveries::Serialize - End read\n");
        }
}
//---------------------------------------------------------------------------
