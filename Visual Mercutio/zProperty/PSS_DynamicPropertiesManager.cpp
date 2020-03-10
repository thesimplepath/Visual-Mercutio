/****************************************************************************
 * ==> PSS_DynamicPropertiesManager ----------------------------------------*
 ****************************************************************************
 * Description : Provides a dynamic properties manager                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DynamicPropertiesManager.h"

// std
#include <memory>

// resources
#include "PSS_PropIDs.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const int g_CategoryStep = 40;
const int g_ItemStep     = 1;
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_DynamicPropertyInfo, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DynamicPropertyInfo
//---------------------------------------------------------------------------
PSS_DynamicPropertyInfo::PSS_DynamicPropertyInfo(PSS_Property* pProperty, CRuntimeClass* pSelectableClass) :
    CObject(),
    m_pSelectableClass(pSelectableClass),
    m_pProperty(pProperty),
    m_SymbolRef(-1)
{}
//---------------------------------------------------------------------------
PSS_DynamicPropertyInfo::PSS_DynamicPropertyInfo(PSS_Property* pProperty, const CString& symbolName, int refNumber) :
    CObject(),
    m_pSelectableClass(NULL),
    m_pProperty(pProperty),
    m_SymbolName(symbolName),
    m_SymbolRef(refNumber)
{}
//---------------------------------------------------------------------------
PSS_DynamicPropertyInfo::~PSS_DynamicPropertyInfo()
{
    if (m_pProperty)
        delete m_pProperty;

    if (m_pSelectableClass)
        delete m_pSelectableClass;
}
//---------------------------------------------------------------------------
PSS_DynamicPropertyInfo& PSS_DynamicPropertyInfo::operator = (const PSS_DynamicPropertyInfo& other)
{
    m_SymbolName = other.m_SymbolName;
    m_SymbolRef  = other.m_SymbolRef;

    if (m_pSelectableClass)
        delete m_pSelectableClass;

    // allocated a new runtime class structure
    if (other.m_pSelectableClass)
        m_pSelectableClass = new CRuntimeClass(*other.m_pSelectableClass);
    else
        m_pSelectableClass = new CRuntimeClass();

    // assign a copy of the property object
    m_pProperty = other.m_pProperty->Dup();

    return *this;
}
//---------------------------------------------------------------------------
void PSS_DynamicPropertyInfo::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // save the running class, if there is
        if (m_pSelectableClass)
        {
            ar << int(1);
            m_pSelectableClass->Store(ar);
        }
        else
            ar << int(0);

        // save the property
        ar << m_pProperty;

        // save the symbol name and ref number
        ar << m_SymbolName;
        ar << m_SymbolRef;
    }
    else
    {
        // load the runting class, if there is
        int value;
        ar >> value;

        if (value == 1)
        {
            UINT schema;

            if ((m_pSelectableClass = CRuntimeClass::Load(ar, &schema)) == NULL)
                AfxThrowArchiveException(CArchiveException::badClass, _T(""));
        }
        else
            m_pSelectableClass = NULL;

        // load the property
        ar >> m_pProperty;

        // load the symbol name and ref number
        ar >> m_SymbolName;
        ar >> m_SymbolRef;
    }
}
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_DynamicPropertiesManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_DynamicPropertiesManager
//---------------------------------------------------------------------------
PSS_DynamicPropertiesManager::PSS_DynamicPropertiesManager()
{}
//---------------------------------------------------------------------------
PSS_DynamicPropertiesManager::PSS_DynamicPropertiesManager(const PSS_DynamicPropertiesManager& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_DynamicPropertiesManager::~PSS_DynamicPropertiesManager()
{
    FreePropertiesSet();
}
//---------------------------------------------------------------------------
PSS_DynamicPropertiesManager& PSS_DynamicPropertiesManager::operator = (const PSS_DynamicPropertiesManager& other)
{
    IDynamicPropertiesInfoIterator it(&other.m_Set);

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        AddDynamicProperty(pProp->Dup());

    return *this;
}
//---------------------------------------------------------------------------
PSS_DynamicPropertiesManager* PSS_DynamicPropertiesManager::Dup() const
{
    return new PSS_DynamicPropertiesManager(*this);
}
//---------------------------------------------------------------------------
void PSS_DynamicPropertiesManager::CreatePropertyList(const CString& category, CStringArray& propList)
{
    IDynamicPropertiesInfoIterator it(&m_Set);

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->m_pProperty && pProp->m_pProperty->GetCategory() == category)
            propList.Add(pProp->m_pProperty->GetLabel());
}
//---------------------------------------------------------------------------
PSS_Property* PSS_DynamicPropertiesManager::RegisterProperty(const CString&       category,
                                                             const CString&       item,
                                                             const CString&       description,
                                                             PSS_Property::IEType dataType,
                                                             PSS_StringFormat&    strFormat,
                                                             CRuntimeClass*       pSelectableClass)
{
    const int     categoryID = GetCategoryID(category);
    const int     itemID     = GetNextItemID(category);
    PSS_Property* pProp      = CreateProperty(category, categoryID, item, itemID, description, dataType, strFormat);

    if (pProp)
    {
        // set the attribute as dynamic
        pProp->SetDynamic();
        AddDynamicProperty(pProp, pSelectableClass);

        return pProp;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_Property* PSS_DynamicPropertiesManager::RegisterProperty(const CString&       category,
                                                             const CString&       item,
                                                             const CString&       description,
                                                             PSS_Property::IEType dataType,
                                                             PSS_StringFormat&    strFormat,
                                                             const CString&       symbolName,
                                                             int                  refNumber)
{
    const int     categoryID = GetCategoryID(category);
    const int     itemID     = GetNextItemID(category);
    PSS_Property* pProp      = CreateProperty(category, categoryID, item, itemID, description, dataType, strFormat);

    if (pProp)
    {
        // set the attribute as dynamic
        pProp->SetDynamic();
        AddDynamicProperty(pProp, symbolName, refNumber);

        return pProp;
    }

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_DynamicPropertiesManager::UnregisterProperty(int categoryID, int itemID)
{
    IDynamicPropertiesInfoIterator it(&m_Set);

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->m_pProperty                                &&
            pProp->m_pProperty->GetCategoryID() == categoryID &&
            pProp->m_pProperty->GetItemID()     == itemID)
        {
            delete pProp;
            it.Remove();

            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
int PSS_DynamicPropertiesManager::GetNextCategoryID() const
{
    int maxCatID = ZS_BP_DYNAMICPROP_START;

    IDynamicPropertiesInfoIterator it(&m_Set);

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->m_pProperty)
            maxCatID = __max(maxCatID, pProp->m_pProperty->GetCategoryID());

    return maxCatID + g_CategoryStep;
}
//---------------------------------------------------------------------------
int PSS_DynamicPropertiesManager::GetNextItemID(const CString& category) const
{
    int maxItemID = 0;

    IDynamicPropertiesInfoIterator it(&m_Set);

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->m_pProperty && pProp->m_pProperty->GetCategory() == category)
            maxItemID = __max(maxItemID, pProp->m_pProperty->GetItemID());

    return maxItemID + g_ItemStep;
}
//---------------------------------------------------------------------------
int PSS_DynamicPropertiesManager::GetNextItemID(int categoryID)
{
    int maxItemID = 0;

    IDynamicPropertiesInfoIterator it(&m_Set);

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->m_pProperty && pProp->m_pProperty->GetCategoryID() == categoryID)
            maxItemID = __max(maxItemID, pProp->m_pProperty->GetItemID());

    return maxItemID + g_ItemStep;
}
//---------------------------------------------------------------------------
void PSS_DynamicPropertiesManager::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // serialize the size
        ar << m_Set.GetSize();

        IDynamicPropertiesInfoIterator it(&m_Set);

        for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
            ar << pProp;
    }
    else
    {
        int size;
        ar >> size;

        PSS_DynamicPropertyInfo* pProp;

        for (int i = 0; i < size; ++i)
        {
            ar >> pProp;
            AddDynamicProperty(pProp);
        }
    }
}
//---------------------------------------------------------------------------
PSS_Property* PSS_DynamicPropertiesManager::CreateProperty(const CString&       category,
                                                           int                  categoryID,
                                                           const CString&       item,
                                                           int                  itemID,
                                                           const CString&       description,
                                                           PSS_Property::IEType dataType,
                                                           PSS_StringFormat&    strFormat)
{
    std::unique_ptr<PSS_Property> pProp;

    switch (dataType)
    {
        case PSS_Property::IE_T_EditString:
        case PSS_Property::IE_T_EditStringReadOnly:
        case PSS_Property::IE_T_EditMultiline:
        case PSS_Property::IE_T_EditMultilineReadOnly:
            pProp.reset(new PSS_Property(category,
                                         categoryID,
                                         item,
                                         itemID,
                                         description,
                                         _T(""),
                                         dataType,
                                         true,
                                         strFormat));
            break;

        case PSS_Property::IE_T_EditDate:
        case PSS_Property::IE_T_EditDateReadOnly:
        {
            PSS_Date dt;

            pProp.reset(new PSS_Property(category,
                                         categoryID,
                                         item,
                                         itemID,
                                         description,
                                         dt,
                                         dataType,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_Date)));
            break;
        }

        case PSS_Property::IE_T_EditTime:
        case PSS_Property::IE_T_EditTimeReadOnly:
        {
            PSS_TimeSpan ts;

            pProp.reset(new PSS_Property(category,
                                         categoryID,
                                         item,
                                         itemID,
                                         description,
                                         ts,
                                         dataType,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_Time1)));
            break;
        }

        case PSS_Property::IE_T_EditDuration:
        case PSS_Property::IE_T_EditDurationReadOnly:
        {
            PSS_Duration dr;

            pProp.reset(new PSS_Property(category,
                                         categoryID,
                                         item,
                                         itemID,
                                         description,
                                         dr,
                                         dataType,
                                         true,
                                         PSS_StringFormat(PSS_StringFormat::IE_FT_Duration7)));
            break;
        }

        case PSS_Property::IE_T_EditNumber:
        case PSS_Property::IE_T_EditNumberReadOnly:
            pProp.reset(new PSS_Property(category,
                                         categoryID,
                                         item,
                                         itemID,
                                         description,
                                         0.0,
                                         dataType,
                                         true,
                                         strFormat));
            break;

        case PSS_Property::IE_T_EditMenu:
        case PSS_Property::IE_T_EditMenuReadOnly:
        case PSS_Property::IE_T_EditIntelli:
        case PSS_Property::IE_T_EditIntelliReadOnly:
        case PSS_Property::IE_T_ComboString:
        case PSS_Property::IE_T_ComboStringReadOnly:
        case PSS_Property::IE_T_ComboNumber:
        case PSS_Property::IE_T_ComboNumberReadOnly:
        case PSS_Property::IE_T_EditFont:
        case PSS_Property::IE_T_EditFile:
        case PSS_Property::IE_T_EditDirectory:
        case PSS_Property::IE_T_EditMultiFiles:
        case PSS_Property::IE_T_EditMultiDirectories:
        case PSS_Property::IE_T_EditExtended:
        case PSS_Property::IE_T_EditExtendedReadOnly:
            break;
    }

    return pProp.release();
}
//---------------------------------------------------------------------------
void PSS_DynamicPropertiesManager::FreePropertiesSet()
{
    IDynamicPropertiesInfoIterator it(&m_Set);

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp)
            delete pProp;

    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_DynamicPropertiesManager::AddDynamicProperty(PSS_Property* pProperty, CRuntimeClass* pSelectableClass)
{
    std::unique_ptr<PSS_DynamicPropertyInfo> pProp(new PSS_DynamicPropertyInfo(pProperty, pSelectableClass));
    AddDynamicProperty(pProp.get());
    pProp.release();
}
//---------------------------------------------------------------------------
void PSS_DynamicPropertiesManager::AddDynamicProperty(PSS_Property*  pProperty,
                                                      const CString& symbolName,
                                                      int            refNumber)
{
    std::unique_ptr<PSS_DynamicPropertyInfo> pProp(new PSS_DynamicPropertyInfo(pProperty, symbolName, refNumber));
    AddDynamicProperty(pProp.get());
    pProp.release();
}
//---------------------------------------------------------------------------
int PSS_DynamicPropertiesManager::GetCategoryID(const CString& category)
{
    int categoryID;

    PSS_DynamicPropertyInfo* pPropInfo = FindPropertyCategory(category);

    if (pPropInfo)
        categoryID = pPropInfo->m_pProperty->GetCategoryID();
    else
        categoryID = GetNextCategoryID();

    return categoryID;
}
//---------------------------------------------------------------------------
PSS_DynamicPropertyInfo* PSS_DynamicPropertiesManager::FindPropertyCategory(const CString& category)
{
    IDynamicPropertiesInfoIterator it(&m_Set);

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->m_pProperty && pProp->m_pProperty->GetCategory() == category)
            return pProp;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_DynamicPropertyInfo* PSS_DynamicPropertiesManager::FindPropertyCategory(int categoryID)
{
    IDynamicPropertiesInfoIterator it(&m_Set);

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->m_pProperty && pProp->m_pProperty->GetCategoryID() == categoryID)
            return pProp;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_DynamicPropertyInfo* PSS_DynamicPropertiesManager::FindPropertyItem(const CString& category, const CString& itemName)
{
    IDynamicPropertiesInfoIterator it(&m_Set);

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->m_pProperty                            &&
            pProp->m_pProperty->GetCategory() == category &&
            pProp->m_pProperty->GetLabel()    == itemName)
            return pProp;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_DynamicPropertyInfo* PSS_DynamicPropertiesManager::FindPropertyItem(int categoryID, const CString& itemName)
{
    IDynamicPropertiesInfoIterator it(&m_Set);

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->m_pProperty                                &&
            pProp->m_pProperty->GetCategoryID() == categoryID &&
            pProp->m_pProperty->GetLabel()      == itemName)
            return pProp;

    return NULL;
}
//---------------------------------------------------------------------------
PSS_DynamicPropertyInfo* PSS_DynamicPropertiesManager::FindPropertyItem(int categoryID, int itemID)
{
    IDynamicPropertiesInfoIterator it(&m_Set);

    for (PSS_DynamicPropertyInfo* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        if (pProp->m_pProperty                                &&
            pProp->m_pProperty->GetCategoryID() == categoryID &&
            pProp->m_pProperty->GetItemID()     == itemID)
            return pProp;

    return NULL;
}
//---------------------------------------------------------------------------
