/****************************************************************************
 * ==> PSS_LanguageProperties ----------------------------------------------*
 ****************************************************************************
 * Description : Provides the language properties                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_LanguageProperties.h"

// resources
#include "PSS_ResIDs.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

using namespace sfl;

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_LanguageProperties, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_LanguageProperties
//---------------------------------------------------------------------------
PSS_LanguageProperties::PSS_LanguageProperties(int id) :
    CODIntProperty(id),
    sfl::CPropertyContainer< IODPropertyContainer, CODPropertyAccessor<PSS_LanguageProperties> >(),
    m_Language(E_LN_French)
{
    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_LanguageProperties::PSS_LanguageProperties(const PSS_LanguageProperties& other) :
    CODIntProperty(other.GetId()),
    sfl::CPropertyContainer< IODPropertyContainer, CODPropertyAccessor<PSS_LanguageProperties> >(),
    m_Language(E_LN_French)
{
    *this = other;

    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_LanguageProperties::~PSS_LanguageProperties()
{}
//---------------------------------------------------------------------------
PSS_LanguageProperties& PSS_LanguageProperties::operator = (const PSS_LanguageProperties& other)
{
    SetLanguage(other.GetLanguage());
    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::operator == (const PSS_LanguageProperties& other) const
{
    return (GetLanguage() == other.GetLanguage());
}
//---------------------------------------------------------------------------
void PSS_LanguageProperties::Merge(CODProperty* pProp, DWORD changeFlags)
{
    PSS_LanguageProperties* pLanguageProp = static_cast<PSS_LanguageProperties*>(pProp);

    if (pLanguageProp)
        if (changeFlags & IE_CT_Language)
            m_Language = pLanguageProp->GetLanguage();
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Language_ID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_LanguageProperties* pLanguageProp = dynamic_cast<PSS_LanguageProperties*>(pProp);

        if (pLanguageProp)
            return (*this == *pLanguageProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Language_ID: value = m_Language; break;
        default:            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::GetValue(const int propId, UINT& value) const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Language_ID: value = static_cast<DWORD>(m_Language); break;
        default:            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Language_ID: value = static_cast<float>(m_Language); break;
        default:            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::GetValue(const int propId, CString& value) const
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Language_ID: m_Language = static_cast<ELanguage>(value); return TRUE;
        default:                                                        return FALSE;
    }
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::SetValue(const int propId, const UINT value)
{
    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Language_ID: m_Language = static_cast<ELanguage>(static_cast<int>(value)); break;
        default:            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Language_ID: m_Language = static_cast<ELanguage>(static_cast<int>(value)); break;
        default:            return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_LanguageProperties::SetValue(const int propId, LPCTSTR pValue)
{
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_LanguageProperties::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        PUT_SCHEMA(ar, PSS_LanguageProperties);
        ar << int(m_Language);
    }
    else
    {
        UINT nSchema;
        GET_SCHEMA(ar, nSchema);

        int value;
        ar >> value;
        m_Language = static_cast<ELanguage>(value);
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_LanguageProperties::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_LanguageProperties::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
bool PSS_LanguageProperties::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        bool success = true;

        if (success)
        {
            success = RegisterProperty(M_Language_ID,
                                       IDS_Z_LANGUAGE_NAME,
                                       IDS_Z_LANGUAGE_DESC,
                                       _PropertyAccessor(&PSS_LanguageProperties::GetLanguageInt,
                                                         &PSS_LanguageProperties::SetLanguageInt),
                                       VT_INT,
                                       PROP_DIRECT);
        }

        if (!success)
            GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
