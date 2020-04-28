/****************************************************************************
 * ==> PSS_ProcCombinations ------------------------------------------------*
 ****************************************************************************
 * Description : Provides the procedures for combinations                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcCombinations.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "PSS_CombinationPropertiesBP.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int g_LastCombinationIDProperties = ZS_BP_PROP_COMBINATION + 39;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ProcCombinations, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ProcCombinations
//---------------------------------------------------------------------------
PSS_ProcCombinations::PSS_ProcCombinations(CODSymbolComponent* pParent) :
    CObject(),
    m_pParent(pParent)
{}
//---------------------------------------------------------------------------
PSS_ProcCombinations::PSS_ProcCombinations(const PSS_ProcCombinations& other) :
    CObject(),
    m_pParent(NULL)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ProcCombinations::~PSS_ProcCombinations()
{
    RemoveAllCombinations();
}
//---------------------------------------------------------------------------
PSS_ProcCombinations& PSS_ProcCombinations::operator = (const PSS_ProcCombinations& other)
{
    ICombinationPropertiesIterator it(&const_cast<PSS_ProcCombinations&>(other).GetCombinationSet());

    // copy the members
    for (PSS_CombinationPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        AddCombination(pProp->Dup());

    m_pParent = other.m_pParent;

    return *this;
}
//---------------------------------------------------------------------------
PSS_ProcCombinations* PSS_ProcCombinations::Dup() const
{
    return new PSS_ProcCombinations(*this);
}
//---------------------------------------------------------------------------
bool PSS_ProcCombinations::CreateInitialProperties()
{
    if (GetCombinationCount() > 0)
        return true;

    std::unique_ptr<PSS_CombinationPropertiesBP> pProps(new PSS_CombinationPropertiesBP());

    if (AddCombination(pProps.get()) >= 0)
    {
        pProps.release();
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcCombinations::SetParent(CODSymbolComponent* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
int PSS_ProcCombinations::AddNewCombination()
{
    std::unique_ptr<PSS_CombinationPropertiesBP> pProps(new PSS_CombinationPropertiesBP());

    const int index = AddCombination(pProps.get());
    pProps.release();

    return index;
}
//---------------------------------------------------------------------------
int PSS_ProcCombinations::AddCombination(PSS_CombinationPropertiesBP* pProperty)
{
    if (pProperty)
    {
        // if no combination name specified, set one by default
        if (pProperty->GetCombinationName().IsEmpty())
            pProperty->SetCombinationName(GetNextCombinationValidName());

        m_Set.Add(pProperty);

        // return the index
        return GetCombinationCount() - 1;
    }

    return -1;
}
//---------------------------------------------------------------------------
bool PSS_ProcCombinations::DeleteCombination(std::size_t index)
{
    if (index < GetCombinationCount())
    {
        PSS_CombinationPropertiesBP* pProperty = GetProperty(index);

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
bool PSS_ProcCombinations::DeleteCombination(PSS_CombinationPropertiesBP* pProperty)
{
    ICombinationPropertiesIterator it(&m_Set);

    for (PSS_CombinationPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProperty == pProp)
        {
            delete pProp;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcCombinations::CombinationNameExist(const CString& name) const
{
    ICombinationPropertiesIterator it(&m_Set);

    // iterate through the combinations and build the string
    for (PSS_CombinationPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCombinationName() == name)
            return true;

    return false;
}
//---------------------------------------------------------------------------
CString PSS_ProcCombinations::GetNextCombinationValidName() const
{
    CString str;
    int     i = 1;

    do
    {
        str.Format(_T("Comb %d"), i);
        ++i;
    }
    while (CombinationNameExist(str));

    return str;
}
//---------------------------------------------------------------------------
CString PSS_ProcCombinations::GetAvailableDeliverables(const CString& allDeliverables) const
{
    // get the allocated deliverables
    CString AllocatedDeliverables = GetAllocatedDeliverables();

    // initialize the tokens with ; as separator
    PSS_Tokenizer srcToken;
    PSS_Tokenizer dstToken;
    CString       str = srcToken.GetFirstToken(allDeliverables);

    // iterate through all deliverables and check if one is available
    while (!str.IsEmpty())
    {
        // if the token is not in the allocated deliverable string, add it to the destination token string
        if (!IsDeliverableInString(AllocatedDeliverables, str))
            dstToken.AddToken(str);

        // get the next token
        str = srcToken.GetNextToken();
    }

    // return the available deliverables string
    return dstToken.GetString();
}
//---------------------------------------------------------------------------
CString PSS_ProcCombinations::GetAllocatedDeliverables() const
{
    // Initialize the token with ; as separator
    PSS_Tokenizer token;

    ICombinationPropertiesIterator it(&m_Set);

    // iterate through the set and build the string
    for (PSS_CombinationPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        // add the deliverables
        token.AddToken(pProp->GetCombinationDeliverables());

    // return the built string
    return token.GetString();
}
//---------------------------------------------------------------------------
bool PSS_ProcCombinations::IsDeliverableInString(const CString& deliverables, const CString& value) const
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
PSS_CombinationPropertiesBP* PSS_ProcCombinations::LocateCombinationOfDeliverable(const CString& deliverableName) const
{
    const int index = LocateCombinationIndexOfDeliverable(deliverableName);

    if (index == -1)
        return NULL;

    return GetProperty(index);
}
//---------------------------------------------------------------------------
int PSS_ProcCombinations::LocateCombinationIndexOfDeliverable(const CString& deliverableName) const
{
    ICombinationPropertiesIterator it(&m_Set);
    int                            index = 0;

    // iterate through the deliverables and check if found the deliverable name
    for (PSS_CombinationPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext(), ++index)
        if (IsDeliverableInString(pProp->GetCombinationDeliverables(), deliverableName))
            return index;

    return -1;
}
//---------------------------------------------------------------------------
PSS_CombinationPropertiesBP* PSS_ProcCombinations::LocateCombinationOfMaster(const CString& master) const
{
    const int index = LocateCombinationIndexOfMaster(master);

    if (index == -1)
        return NULL;

    return GetProperty(index);
}
//---------------------------------------------------------------------------
int PSS_ProcCombinations::LocateCombinationIndexOfMaster(const CString& master) const
{
    ICombinationPropertiesIterator it(&m_Set);
    int                            index = 0;

    // iterate through the deliverables and check if found the deliverable name
    for (PSS_CombinationPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext(), ++index)
        if (!pProp->GetCombinationMaster().IsEmpty() && pProp->GetCombinationMaster() == master)
            return index;

    return -1;
}
//---------------------------------------------------------------------------
bool PSS_ProcCombinations::ReplaceDeliverable(const CString& oldDeliverableName, const CString& newDeliverableName)
{
    const int index  = LocateCombinationIndexOfDeliverable(oldDeliverableName);
    bool      result = false;

    if (index != -1)
    {
        // remove the old deliverable
        if (!RemoveCombinationDeliverable(index, oldDeliverableName))
            return false;

        // add the new name and return the status
        result = AddCombinationDeliverable(index, newDeliverableName);
    }

    PSS_CombinationPropertiesBP* pCombination = LocateCombinationOfMaster(oldDeliverableName);

    if (pCombination)
    {
        // set the new deliverable name
        pCombination->SetCombinationMaster(newDeliverableName);
        result = true;
    }

    return result;
}
//---------------------------------------------------------------------------
bool PSS_ProcCombinations::DeleteDeliverableFromAllCombinations(const CString& deliverableName)
{
    const int index  = LocateCombinationIndexOfDeliverable(deliverableName);
    bool      result = false;

    if (index != -1)
        // remove the old deliverable
        if (!RemoveCombinationDeliverable(index, deliverableName))
            return false;

    PSS_CombinationPropertiesBP* pCombination = LocateCombinationOfMaster(deliverableName);

    if (pCombination)
    {
        // set the new deliverable name
        pCombination->SetCombinationMaster(_T(""));
        result = true;
    }

    return result;
}
//---------------------------------------------------------------------------
void PSS_ProcCombinations::RemoveAllCombinations()
{
    ICombinationPropertiesIterator it(&m_Set);

    for (PSS_CombinationPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    // remove all elements
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
CString PSS_ProcCombinations::GetCombinationName(std::size_t index) const
{
    if (index < GetCombinationCount())
        return m_Set.GetAt(index)->GetCombinationName();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcCombinations::SetCombinationName(std::size_t index, const CString& value)
{
    if (index < GetCombinationCount())
        m_Set.GetAt(index)->SetCombinationName(value);
}
//---------------------------------------------------------------------------
CString PSS_ProcCombinations::GetCombinationDeliverables(std::size_t index) const
{
    if (index < GetCombinationCount())
        return m_Set.GetAt(index)->GetCombinationDeliverables();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcCombinations::SetCombinationDeliverables(std::size_t index, const CString& value)
{
    if (index < GetCombinationCount())
        m_Set.GetAt(index)->SetCombinationDeliverables(value);
}
//---------------------------------------------------------------------------
bool PSS_ProcCombinations::AddCombinationDeliverable(std::size_t index, const CString& value)
{
    const CString deliverables = GetCombinationDeliverables(index);

    // initialize the token with ; as separator
    PSS_Tokenizer token;

    CString str   = token.GetFirstToken(deliverables);
    bool    found = false;

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

        // set the new deliverable complete string
        SetCombinationDeliverables(index, token.GetString());
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcCombinations::RemoveCombinationDeliverable(std::size_t index, const CString& value)
{
    const CString deliverables = GetCombinationDeliverables(index);

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
            // if not the same, can be added to the destination token
            dstToken.AddToken(str);

        // get the next token
        str = srcToken.GetNextToken();
    }

    // if found, set the new string
    if (found)
    {
        // set the new deliverable string
        SetCombinationDeliverables(index, dstToken.GetString());
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcCombinations::RemoveAllCombinationDeliverable(std::size_t index)
{
    SetCombinationDeliverables(index, _T(""));
    return true;
}
//---------------------------------------------------------------------------
float PSS_ProcCombinations::GetCombinationActivationPerc(std::size_t index) const
{
    if (index < GetCombinationCount())
        return m_Set.GetAt(index)->GetCombinationActivationPerc();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_ProcCombinations::SetCombinationActivationPerc(std::size_t index, const float value)
{
    if (index < GetCombinationCount())
        m_Set.GetAt(index)->SetCombinationActivationPerc(value);
}
//---------------------------------------------------------------------------
CString PSS_ProcCombinations::GetCombinationMaster(std::size_t index) const
{
    if (index < GetCombinationCount())
        return m_Set.GetAt(index)->GetCombinationMaster();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ProcCombinations::SetCombinationMaster(std::size_t index, const CString& value)
{
    if (index < GetCombinationCount())
        m_Set.GetAt(index)->SetCombinationMaster(value);
}
//---------------------------------------------------------------------------
void PSS_ProcCombinations::Serialize(CArchive& ar)
{
    // Only if the object is serialize from and to a document
    if (ar.m_pDocument)
        if (ar.IsStoring())
        {
            TRACE("PSS_ProcCombinations::Serialize - Start save\n");

            // serialize the size
            ar << int(m_Set.GetSize());

            ICombinationPropertiesIterator it(&m_Set);

            for (PSS_CombinationPropertiesBP* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                ar << pProp;

            TRACE("PSS_ProcCombinations::Serialize - End save\n");
        }
        else
        {
            TRACE("PSS_ProcCombinations::Serialize - Start read\n");

            RemoveAllCombinations();

            // read the size
            int count;
            ar >> count;

            PSS_CombinationPropertiesBP* pProp;

            for (int i = 0; i < count; ++i)
            {
                ar >> pProp;
                AddCombination(pProp);
            }

            TRACE("PSS_ProcCombinations::Serialize - End read\n");
        }
}
//---------------------------------------------------------------------------
