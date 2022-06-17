/****************************************************************************
 * ==> PSS_TextItemListPropertiesBP ----------------------------------------*
 ****************************************************************************
 * Description : Provides the text item list properties for banking process *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_TextItemListPropertiesBP.h"

// resources
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

using namespace sfl;

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_TextItemListPropertiesBP, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_TextItemListPropertiesBP
//---------------------------------------------------------------------------
PSS_TextItemListPropertiesBP::PSS_TextItemListPropertiesBP(int propID) :
    CODIntProperty(propID)
{
    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_TextItemListPropertiesBP::PSS_TextItemListPropertiesBP(const PSS_TextItemListPropertiesBP& other) :
    CODIntProperty(other.GetId())
{
    m_TextItemList  = other.GetTextItemList();

    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_TextItemListPropertiesBP::~PSS_TextItemListPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_TextItemListPropertiesBP& PSS_TextItemListPropertiesBP::operator = (const PSS_TextItemListPropertiesBP& other)
{
    SetId(other.GetId());
    SetTextItemList(other.GetTextItemList());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::operator == (const PSS_TextItemListPropertiesBP& other) const
{
    return (GetTextItemList() == other.GetTextItemList());
}
//---------------------------------------------------------------------------
void PSS_TextItemListPropertiesBP::Merge(CODProperty* pProp, DWORD changeFlags)
{
    PSS_TextItemListPropertiesBP* pProcessProps = dynamic_cast<PSS_TextItemListPropertiesBP*>(pProp);

    if (pProcessProps)
        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_TextItem_List)
            m_TextItemList = pProcessProps->GetTextItemList();
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::CompareId(const int id) const
{
    int idMin = m_nId;
    int idMax = m_nId + M_TextItem_List_ID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_TextItemListPropertiesBP* pProcessProp = dynamic_cast<PSS_TextItemListPropertiesBP*>(pProp);

        if (pProcessProp)
            return (*this == *pProcessProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_TextItemListPropertiesBP::SetTextItemList(LPCTSTR pValue)
{
    if (pValue)
        m_TextItemList = pValue;
    else
        THROW("PSS_TextItemListPropertiesBP - Invalid decision list");
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_TextItem_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_TextItem_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_TextItem_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_TextItem_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_TextItem_List_ID: value = m_TextItemList; break;
        default:                                         return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_TextItem_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_TextItem_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_TextItem_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_TextItem_List_ID: throw new CODPropertyConversionException();
        default:                 return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_TextItemListPropertiesBP::SetValue(const int propId, LPCTSTR pValue)
{
    switch (propId)
    {
        case M_TextItem_List_ID: m_TextItemList = pValue; break;
        default:                                          return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_TextItemListPropertiesBP::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_TextItemListPropertiesBP::Serialize - Start save\n");

        PUT_SCHEMA(ar, PSS_TextItemListPropertiesBP);
        ar << m_TextItemList;

        TRACE("PSS_TextItemListPropertiesBP::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_TextItemListPropertiesBP::Serialize - Start read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);

        ar >> m_TextItemList;

        TRACE("PSS_TextItemListPropertiesBP::Serialize - End read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_TextItemListPropertiesBP::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_TextItemListPropertiesBP::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);

        dc << "Text Item list = " << m_TextItemList << "\n";
    }
#endif
//---------------------------------------------------------------------------
void PSS_TextItemListPropertiesBP::SetTextItemListEx(const CString value)
{
    SetTextItemList(value);
}
//---------------------------------------------------------------------------
bool PSS_TextItemListPropertiesBP::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        const bool success = RegisterProperty(M_TextItem_List_ID,
                                              IDS_Z_TEXTITEM_LIST_NAME,
                                              IDS_Z_TEXTITEM_LIST_DESC,
                                              _PropertyAccessor(&PSS_TextItemListPropertiesBP::GetTextItemList,
                                                                &PSS_TextItemListPropertiesBP::SetTextItemListEx),
                                              VT_BSTR,
                                              PROP_DIRECT);

        if (!success)
            GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
