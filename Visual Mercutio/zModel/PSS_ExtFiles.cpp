/****************************************************************************
 * ==> PSS_ExtFiles --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an external file manager                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ExtFiles.h"

// processsoft
#include "PSS_ExtFileProperties.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Constant definitions
//---------------------------------------------------------------------------
const int g_LastExtFileIDProperties = ZS_BP_PROP_EXTFILE + 39;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ExtFiles, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ExtFiles
//---------------------------------------------------------------------------
PSS_ExtFiles::PSS_ExtFiles(CODSymbolComponent* pParent) :
    CObject(),
    m_pParent(pParent)
{}
//---------------------------------------------------------------------------
PSS_ExtFiles::PSS_ExtFiles(const PSS_ExtFiles& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_ExtFiles::~PSS_ExtFiles()
{
    RemoveAllExtFiles();
}
//---------------------------------------------------------------------------
PSS_ExtFiles& PSS_ExtFiles::operator = (const PSS_ExtFiles& other)
{
    IPropIterator it(&const_cast<PSS_ExtFiles&>(other).GetExtFileSet());

    // copy the members
    for (PSS_ExtFileProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        AddExtFile(pProp->Dup());

    m_pParent = other.m_pParent;

    return *this;
}
//---------------------------------------------------------------------------
PSS_ExtFiles* PSS_ExtFiles::Dup() const
{
    return new PSS_ExtFiles(*this);
}
//---------------------------------------------------------------------------
void PSS_ExtFiles::SetParent(CODSymbolComponent* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
bool PSS_ExtFiles::CreateInitialProperties()
{
    if (GetExtFileCount() > 0)
        return true;

    PSS_ExtFileProperties* pProps = new PSS_ExtFileProperties;

    if (AddExtFile(pProps) >= 0)
        return true;

    return false;
}
//---------------------------------------------------------------------------
int PSS_ExtFiles::AddNewExtFile()
{
    PSS_ExtFileProperties* pProps = new PSS_ExtFileProperties;

    return AddExtFile(pProps);
}
//---------------------------------------------------------------------------
int PSS_ExtFiles::AddExtFile(PSS_ExtFileProperties* pProperty)
{
    if (pProperty)
    {
        m_Set.Add(pProperty);

        // return the index
        return GetExtFileCount() - 1;
    }

    return -1;
}
//---------------------------------------------------------------------------
bool PSS_ExtFiles::DeleteExtFile(std::size_t index)
{
    if (index < GetExtFileCount())
    {
        PSS_ExtFileProperties* pProperty = GetProperty(index);

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
bool PSS_ExtFiles::DeleteExtFile(const CString& fileName)
{
    IPropIterator it(&m_Set);

    // iterate through the deliverable set and check if file name was found
    for (PSS_ExtFileProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetFileName() == fileName)
        {
            delete pProp;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ExtFiles::DeleteExtFile(PSS_ExtFileProperties* pProperty)
{
    IPropIterator it(&m_Set);

    for (PSS_ExtFileProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProperty == pProp)
        {
            delete pProp;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
void PSS_ExtFiles::RemoveAllExtFiles()
{
    IPropIterator it(&m_Set);

    for (PSS_ExtFileProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    // remove all elements
    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_ExtFiles::RemoveAllEmptyExtFiles()
{
    IPropIterator it(&m_Set);

    for (PSS_ExtFileProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->IsEmpty())
        {
            delete pProp;
            it.Remove();
        }
}
//---------------------------------------------------------------------------
bool PSS_ExtFiles::ExtFileExist(const CString& fileName) const
{
    IPropIterator it(&m_Set);

    // iterate through the set and search for a matching string
    for (PSS_ExtFileProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetFileName() == fileName)
            return true;

    return false;
}
//---------------------------------------------------------------------------
PSS_ExtFileProperties* PSS_ExtFiles::LocateExtFile(const CString& fileName) const
{
    IPropIterator it(&m_Set);

    // iterate through the deliverable set and check if a matching file name was found
    for (PSS_ExtFileProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->GetFileName() == fileName)
            return pProp;

    return NULL;
}
//---------------------------------------------------------------------------
int PSS_ExtFiles::LocateFirstEmptyExtFile() const
{
    IPropIterator it(&m_Set);
    int           index = 0;

    for (PSS_ExtFileProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext(), ++index)
        if (pProp->IsEmpty())
            return index;

    return -1;
}
//---------------------------------------------------------------------------
CString PSS_ExtFiles::GetFileTitle(std::size_t index) const
{
    if (index < GetExtFileCount())
        return m_Set.GetAt(index)->GetFileTitle();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ExtFiles::SetFileTitle(std::size_t index, const CString& value)
{
    if (index < GetExtFileCount())
        m_Set.GetAt(index)->SetFileTitle(value);
}
//---------------------------------------------------------------------------
CString PSS_ExtFiles::GetFileName(std::size_t index) const
{
    if (index < GetExtFileCount())
        return m_Set.GetAt(index)->GetFileName();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_ExtFiles::SetFileName(std::size_t index, const CString& value)
{
    if (index < GetExtFileCount())
        m_Set.GetAt(index)->SetFileName(value);
}
//---------------------------------------------------------------------------
int PSS_ExtFiles::GetInsertionType(std::size_t index) const
{
    if (index < GetExtFileCount())
        return m_Set.GetAt(index)->GetInsertionType();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_ExtFiles::SetInsertionType(std::size_t index, const int value)
{
    if (index < GetExtFileCount())
        m_Set.GetAt(index)->SetInsertionType(value);
}
//---------------------------------------------------------------------------
int PSS_ExtFiles::GetActivationType(std::size_t index) const
{
    if (index < GetExtFileCount())
        return m_Set.GetAt(index)->GetActivationType();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_ExtFiles::SetActivationType(std::size_t index, const int value)
{
    if (index < GetExtFileCount())
        m_Set.GetAt(index)->SetActivationType(value);
}
//---------------------------------------------------------------------------
void PSS_ExtFiles::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // serialize the set size
        ar << m_Set.GetSize();

        IPropIterator it(&m_Set);

        for (PSS_ExtFileProperties* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            ar << pProp;
    }
    else
    {
        RemoveAllExtFiles();

        // read the set size
        int count;
        ar >> count;

        PSS_ExtFileProperties* pProp;

        for (int i = 0; i < count; ++i)
        {
            ar >> pProp;
            AddExtFile(pProp);
        }
    }
}
//---------------------------------------------------------------------------
