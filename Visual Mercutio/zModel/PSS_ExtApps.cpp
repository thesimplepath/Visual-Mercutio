/****************************************************************************
 * ==> PSS_ExtApps ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an external application manager                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ExtApps.h"

// processsoft
#include "PSS_ExtAppProperties.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int LastExtAppIDProperties = ZS_BP_PROP_EXTAPP + 39;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ExtApps, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ExtApps
//---------------------------------------------------------------------------
PSS_ExtApps::PSS_ExtApps(CODSymbolComponent* pParent) :
    CObject(),
    m_pParent(pParent)
{}
//---------------------------------------------------------------------------
PSS_ExtApps::PSS_ExtApps(const PSS_ExtApps& other) :
    CObject(),
    m_pParent(NULL)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ExtApps::~PSS_ExtApps()
{
    // NOTE use the fully qualified name here to avoid to call a pure virtual function during the destruction
    PSS_ExtApps::RemoveAllExtApps();
}
//---------------------------------------------------------------------------
PSS_ExtApps& PSS_ExtApps::operator = (const PSS_ExtApps& other)
{
    m_pParent = other.m_pParent;

    IPropIterator it(&const_cast<PSS_ExtApps&>(other).GetExtAppSet());

    // copy the members
    for (PSS_ExtAppProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        AddExtApp(pProp->Dup());

    return *this;
}
//---------------------------------------------------------------------------
PSS_ExtApps* PSS_ExtApps::Dup() const
{
    return new PSS_ExtApps(*this);
}
//---------------------------------------------------------------------------
void PSS_ExtApps::SetParent(CODSymbolComponent* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
bool PSS_ExtApps::CreateInitialProperties()
{
    // already created?
    if (GetExtAppCount() > 0)
        return true;

    std::unique_ptr<PSS_ExtAppProperties> pProps(new PSS_ExtAppProperties());

    if (AddExtApp(pProps.get()) >= 0)
    {
        pProps.release();
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
int PSS_ExtApps::AddNewExtApp()
{
    std::unique_ptr<PSS_ExtAppProperties> pProps(new PSS_ExtAppProperties());

    const int result = AddExtApp(pProps.get());
    pProps.release();

    return result;
}
//---------------------------------------------------------------------------
int PSS_ExtApps::AddExtApp(PSS_ExtAppProperties* pProperty)
{
    if (pProperty)
    {
        m_Set.Add(pProperty);

        // return the index
        return GetExtAppCount() - 1;
    }

    return -1;
}
//---------------------------------------------------------------------------
bool PSS_ExtApps::DeleteExtApp(std::size_t index)
{
    if (index < GetExtAppCount())
    {
        PSS_ExtAppProperties* pProperty = GetProperty(index);

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
bool PSS_ExtApps::DeleteExtApp(const CString& commandTitle)
{
    IPropIterator it(&m_Set);

    // iterate through the deliverable set and check if found a matching command title
    for (PSS_ExtAppProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCommandTitle() == commandTitle)
        {
            delete pProp;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ExtApps::DeleteExtApp(PSS_ExtAppProperties* pPropToDel)
{
    IPropIterator it(&m_Set);

    for (PSS_ExtAppProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
    {
        if (pPropToDel == pProp)
        {
            it.Remove();
            delete pProp;
            return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_ExtApps::RemoveAllExtApps()
{
    IPropIterator it(&m_Set);

    for (PSS_ExtAppProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    // remove all elements
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_ExtApps::RemoveAllEmptyExtApps()
{
    IPropIterator it(&m_Set);

    for (PSS_ExtAppProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->IsEmpty())
        {
            delete pProp;
            it.Remove();
        }
}
//---------------------------------------------------------------------------
bool PSS_ExtApps::ExtAppExist(const CString& commandTitle) const
{
    IPropIterator it(&m_Set);

    // iterate through the set and search for a matching string
    for (PSS_ExtAppProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCommandTitle() == commandTitle)
            return true;

    return false;
}
//---------------------------------------------------------------------------
PSS_ExtAppProperties* PSS_ExtApps::LocateExtApp(const CString& commandTitle) const
{
    IPropIterator it(&m_Set);

    // iterate through the deliverable set and search for a matching string
    for (PSS_ExtAppProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetCommandTitle() == commandTitle)
            return pProp;

    return NULL;
}
//---------------------------------------------------------------------------
int PSS_ExtApps::LocateFirstEmptyExtApp() const
{
    IPropIterator it(&m_Set);
    int           index = 0;

    for (PSS_ExtAppProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext(), ++index)
        if (pProp->IsEmpty())
            return index;

    return -1;
}
//---------------------------------------------------------------------------
CString PSS_ExtApps::GetCommandTitle(std::size_t index) const
{
    if (index < GetExtAppCount())
        return m_Set.GetAt(index)->GetCommandTitle();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ExtApps::SetCommandTitle(std::size_t index, const CString& value)
{
    if (index < GetExtAppCount())
        m_Set.GetAt(index)->SetCommandTitle(value);
}
//---------------------------------------------------------------------------
CString PSS_ExtApps::GetCommandLine(std::size_t index) const
{
    if (index < GetExtAppCount())
        return m_Set.GetAt(index)->GetCommandLine();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ExtApps::SetCommandLine(std::size_t index, const CString& value)
{
    if (index < GetExtAppCount())
        m_Set.GetAt(index)->SetCommandLine(value);
}
//---------------------------------------------------------------------------
CString PSS_ExtApps::GetCommandParameters(std::size_t index) const
{
    if (index < GetExtAppCount())
        return m_Set.GetAt(index)->GetCommandParameters();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ExtApps::SetCommandParameters(std::size_t index, const CString& value)
{
    if (index < GetExtAppCount())
        m_Set.GetAt(index)->SetCommandParameters(value);
}
//---------------------------------------------------------------------------
CString PSS_ExtApps::GetCommandStartupDirectory(std::size_t index) const
{
    if (index < GetExtAppCount())
        return m_Set.GetAt(index)->GetCommandStartupDirectory();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ExtApps::SetCommandStartupDirectory(std::size_t index, const CString& value)
{
    if (index < GetExtAppCount())
        m_Set.GetAt(index)->SetCommandStartupDirectory(value);
}
//---------------------------------------------------------------------------
int PSS_ExtApps::GetPriorityLevel(std::size_t index) const
{
    if (index < GetExtAppCount())
        return m_Set.GetAt(index)->GetPriorityLevel();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_ExtApps::SetPriorityLevel(std::size_t index, const int value)
{
    if (index < GetExtAppCount())
        m_Set.GetAt(index)->SetPriorityLevel(value);
}
//---------------------------------------------------------------------------
int PSS_ExtApps::GetWindowStartMode(std::size_t index) const
{
    if (index < GetExtAppCount())
        return m_Set.GetAt(index)->GetWindowStartMode();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_ExtApps::SetWindowStartMode(std::size_t index, const int value)
{
    if (index < GetExtAppCount())
        m_Set.GetAt(index)->SetWindowStartMode(value);
}
//---------------------------------------------------------------------------
void PSS_ExtApps::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // serialize the set size
        ar << m_Set.GetSize();

        IPropIterator it(&m_Set);

        for (PSS_ExtAppProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            ar << pProp;
    }
    else
    {
        RemoveAllExtApps();

        int count;

        // read the set size
        ar >> count;

        PSS_ExtAppProperties* pProp;

        for (int i = 0; i < count; ++i)
        {
            ar >> pProp;
            AddExtApp(pProp);
        }
    }
}
//---------------------------------------------------------------------------
