/****************************************************************************
 * ==> PSS_BasicModelProperties --------------------------------------------*
 ****************************************************************************
 * Description : Provides the basic model properties                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_BasicModelProperties.h"

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
IMPLEMENT_SERIAL(PSS_BasicModelProperties, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_BasicModelProperties
//---------------------------------------------------------------------------
PSS_BasicModelProperties::PSS_BasicModelProperties(int id) :
    CODIntProperty(id),
    CPropertyContainer< IODPropertyContainer, CODPropertyAccessor<PSS_BasicModelProperties> >()
{
    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_BasicModelProperties::PSS_BasicModelProperties(const PSS_BasicModelProperties& other) :
    CODIntProperty(other.GetId()),
    CPropertyContainer< IODPropertyContainer, CODPropertyAccessor<PSS_BasicModelProperties> >()
{
    *this = other;
    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_BasicModelProperties::~PSS_BasicModelProperties()
{}
//---------------------------------------------------------------------------
PSS_BasicModelProperties& PSS_BasicModelProperties::operator = (const PSS_BasicModelProperties& other)
{
    SetModelName(other.GetModelName());
    SetModelDescription(other.GetModelDescription());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::operator == (const PSS_BasicModelProperties& other) const
{
    return (GetModelName() == other.GetModelName() && GetModelDescription() == other.GetModelDescription());
}
//---------------------------------------------------------------------------
void PSS_BasicModelProperties::Merge(CODProperty* pProp, DWORD changeType)
{
    PSS_BasicModelProperties* pOrientationProp = dynamic_cast<PSS_BasicModelProperties*>(pProp);

    if (pOrientationProp)
    {
        if (changeType & IE_CT_Model_Name)
            m_ModelName = pOrientationProp->GetModelName();

        if (changeType & IE_CT_Model_Description)
            m_ModelDescription = pOrientationProp->GetModelDescription();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Model_Description_ID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_BasicModelProperties* pOrientationProp = dynamic_cast<PSS_BasicModelProperties*>(pProp);

        if (pOrientationProp)
            return (*this == *pOrientationProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::GetValue(const int propId, int& value) const
{
    if (propId >= M_Model_Name_ID && propId <= M_Model_Description_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::GetValue(const int propId, UINT& value) const
{
    if (propId >= M_Model_Name_ID && propId <= M_Model_Description_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::GetValue(const int propId, DWORD& value) const
{
    if (propId >= M_Model_Name_ID && propId <= M_Model_Description_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::GetValue(const int propId, float& value) const
{
    if (propId >= M_Model_Name_ID && propId <= M_Model_Description_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Model_Name_ID:        value = m_ModelName;        break;
        case M_Model_Description_ID: value = m_ModelDescription; break;
        default:                     return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::SetValue(const int propId, const int value)
{
    if (propId >= M_Model_Name_ID && propId <= M_Model_Description_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::SetValue(const int propId, const UINT value)
{
    if (propId >= M_Model_Name_ID && propId <= M_Model_Description_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::SetValue(const int propId, const DWORD value)
{
    if (propId >= M_Model_Name_ID && propId <= M_Model_Description_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::SetValue(const int propId, const float value)
{
    if (propId >= M_Model_Name_ID && propId <= M_Model_Description_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicModelProperties::SetValue(const int propId, LPCTSTR pValue)
{
    switch (propId)
    {
        case M_Model_Name_ID:        m_ModelName        = pValue; break;
        case M_Model_Description_ID: m_ModelDescription = pValue; break;
        default:                     return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_BasicModelProperties::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        PUT_SCHEMA(ar, PSS_BasicModelProperties);
        ar << m_ModelName;
        ar << m_ModelDescription;
    }
    else
    {
        UINT schema;
        GET_SCHEMA(ar, schema);
        ar >> m_ModelName;
        ar >> m_ModelDescription;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_BasicModelProperties::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_BasicModelProperties::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
bool PSS_BasicModelProperties::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        bool success = true;

        if (success)
            success = RegisterProperty(M_Model_Name_ID,
                                       IDS_Z_MODEL_NAME_NAME,
                                       IDS_Z_MODEL_NAME_DESC,
                                       _PropertyAccessor(&PSS_BasicModelProperties::GetModelName,
                                                         &PSS_BasicModelProperties::SetModelName),
                                       VT_BSTR,
                                       PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Model_Description_ID,
                                       IDS_Z_MODEL_DESCRIPTION_NAME,
                                       IDS_Z_MODEL_DESCRIPTION_DESC,
                                       _PropertyAccessor(&PSS_BasicModelProperties::GetModelDescription,
                                                         &PSS_BasicModelProperties::SetModelDescription),
                                       VT_BSTR,
                                       PROP_DIRECT);

        if (!success)
            PSS_BasicModelProperties::GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
