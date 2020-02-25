/****************************************************************************
 * ==> PSS_InputAttributes -------------------------------------------------*
 ****************************************************************************
 * Description : Provides the input attributes                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InputAttributes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_InputAttribute, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_InputAttribute
//---------------------------------------------------------------------------
PSS_InputAttribute::PSS_InputAttribute() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_InputAttribute::PSS_InputAttribute(const PSS_InputAttribute& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_InputAttribute::~PSS_InputAttribute()
{}
//---------------------------------------------------------------------------
PSS_InputAttribute& PSS_InputAttribute::operator = (const PSS_InputAttribute& other)
{
    m_DefaultValue = other.m_DefaultValue;
    m_CategoryID   = other.m_CategoryID;
    m_ItemID       = other.m_ItemID;
    m_SymbolRef    = other.m_SymbolRef;
    m_Flag         = other.m_Flag;

    return *this;
}
//---------------------------------------------------------------------------
PSS_InputAttribute* PSS_InputAttribute::Dup() const
{
    return new PSS_InputAttribute(*this);
}
//---------------------------------------------------------------------------
void PSS_InputAttribute::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE("PSS_InputAttribute::Serialize - Start save\n");

        ar << m_CategoryID;
        ar << m_ItemID;
        ar << m_SymbolRef;
        ar << m_DefaultValue;
        ar << m_Flag;

        TRACE("PSS_InputAttribute::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_InputAttribute::Serialize - Start read\n");

        ar >> m_CategoryID;
        ar >> m_ItemID;
        ar >> m_SymbolRef;
        ar >> m_DefaultValue;
        ar >> m_Flag;

        TRACE("PSS_InputAttribute::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_InputAttributeManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_InputAttributeManager
//---------------------------------------------------------------------------
PSS_InputAttributeManager::PSS_InputAttributeManager() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_InputAttributeManager::PSS_InputAttributeManager(const PSS_InputAttributeManager& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_InputAttributeManager::~PSS_InputAttributeManager()
{
    DeleteAllInputAttributes();
}
//---------------------------------------------------------------------------
PSS_InputAttributeManager& PSS_InputAttributeManager::operator = (const PSS_InputAttributeManager& other)
{
    IInputAttributeIterator it(&other.m_Set);

    for (PSS_InputAttribute* pInputAttrib = it.GetFirst(); pInputAttrib; pInputAttrib = it.GetNext())
        AddInputAttribute(pInputAttrib->Dup());

    return *this;
}
//---------------------------------------------------------------------------
PSS_InputAttributeManager* PSS_InputAttributeManager::Dup() const
{
    return new PSS_InputAttributeManager(*this);
}
//---------------------------------------------------------------------------
void PSS_InputAttributeManager::DeleteAllInputAttributes()
{
    IInputAttributeIterator it(&m_Set);

    for (PSS_InputAttribute* pInputAttrib = it.GetFirst(); pInputAttrib; pInputAttrib = it.GetNext())
        delete pInputAttrib;

    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_InputAttributeManager::AddInputAttribute(PSS_InputAttribute* pInputAttribute, bool replaceExisting)
{
    if (!pInputAttribute)
        return;

    if (!Exist(pInputAttribute))
        m_Set.Add(pInputAttribute);
    else
    if (replaceExisting)
    {
        ReplaceInputAttribute(pInputAttribute);

        PSS_InputAttribute* pOldAttribute = pInputAttribute;

        // don't forget to delete the object since it's no longer assigned to the set,
        // and update the pointer to the existing object
        pInputAttribute = FindInputAttribute(pInputAttribute->GetCategoryID(),
                                             pInputAttribute->GetItemID(),
                                             pInputAttribute->GetSymbolRef());

        delete pOldAttribute;
    }
}
//---------------------------------------------------------------------------
bool PSS_InputAttributeManager::Exist(PSS_InputAttribute* pInputAttribute)
{
    if (!pInputAttribute)
        return false;

    return FindInputAttribute(pInputAttribute->GetCategoryID(),
                              pInputAttribute->GetItemID(),
                              pInputAttribute->GetSymbolRef());
}
//---------------------------------------------------------------------------
bool PSS_InputAttributeManager::DeleteInputAttribute(PSS_InputAttribute* pInputAttribute)
{
    IInputAttributeIterator it(&m_Set);

    for (PSS_InputAttribute* pInputAttrib = it.GetFirst(); pInputAttrib; pInputAttrib = it.GetNext())
        if (pInputAttrib == pInputAttribute)
        {
            delete pInputAttrib;
            it.Remove();
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
PSS_InputAttribute* PSS_InputAttributeManager::FindInputAttribute(int categoryID, int itemID, int symbolRef)
{
    IInputAttributeIterator it(&m_Set);

    for (PSS_InputAttribute* pInputAttrib = it.GetFirst(); pInputAttrib; pInputAttrib = it.GetNext())
        if (pInputAttrib->GetCategoryID() == categoryID &&
            pInputAttrib->GetItemID()     == itemID     &&
            pInputAttrib->GetSymbolRef()  == symbolRef)
            return pInputAttrib;

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_InputAttributeManager::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        TRACE("PSS_InputAttributeManager::Serialize - Start save\n");

        // serialize the size
        ar << int(m_Set.GetSize());

        IInputAttributeIterator it(&m_Set);

        for (PSS_InputAttribute* pInputAttrib = it.GetFirst(); pInputAttrib; pInputAttrib = it.GetNext())
            ar << pInputAttrib;

        TRACE("PSS_InputAttributeManager::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_InputAttributeManager::Serialize - Start read\n");

        int size;
        ar >> size;

        PSS_InputAttribute* pInputAttrib;

        for (int i = 0; i < int(size); ++i)
        {
            ar >> pInputAttrib;
            AddInputAttribute(pInputAttrib);
        }

        TRACE("PSS_InputAttributeManager::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
void PSS_InputAttributeManager::ReplaceInputAttribute(PSS_InputAttribute* pInputAttribute)
{
    PSS_InputAttribute* pAttr = FindInputAttribute(pInputAttribute->GetCategoryID(),
                                                   pInputAttribute->GetItemID(),
                                                   pInputAttribute->GetSymbolRef());

    if (pAttr)
        *pAttr = *pInputAttribute;
}
//---------------------------------------------------------------------------
