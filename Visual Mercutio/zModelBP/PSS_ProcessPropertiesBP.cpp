/****************************************************************************
 * ==> PSS_ProcessPropertiesBP ---------------------------------------------*
 ****************************************************************************
 * Description : Provides the process properties for banking process        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessPropertiesBP.h"

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
IMPLEMENT_SERIAL(PSS_ProcessPropertiesBP, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ProcessPropertiesBP
//---------------------------------------------------------------------------
PSS_ProcessPropertiesBP::PSS_ProcessPropertiesBP(int propID) :
    CODIntProperty(propID)
{
    m_ManagementCase = _T("");

    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_ProcessPropertiesBP::PSS_ProcessPropertiesBP(const PSS_ProcessPropertiesBP& other) :
    CODIntProperty(other.GetId())
{
    m_ManagementCase = other.GetManagementCase();

    RegisterProperties();
}
//---------------------------------------------------------------------------
PSS_ProcessPropertiesBP::~PSS_ProcessPropertiesBP()
{}
//---------------------------------------------------------------------------
PSS_ProcessPropertiesBP& PSS_ProcessPropertiesBP::operator = (const PSS_ProcessPropertiesBP& other)
{
    SetId(other.GetId());
    SetManagementCase(other.GetManagementCase());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::operator == (const PSS_ProcessPropertiesBP& other) const
{
    return (GetManagementCase() == other.GetManagementCase());
}
//---------------------------------------------------------------------------
void PSS_ProcessPropertiesBP::Merge(CODProperty* pProp, DWORD changeFlags)
{
    PSS_ProcessPropertiesBP* pProcessProps = dynamic_cast<PSS_ProcessPropertiesBP*>(pProp);

    if (pProcessProps)
        if (changeFlags & (DWORD)IEChangeType::IE_CT_Change_Management_Case)
            m_ManagementCase = pProcessProps->GetManagementCase();
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Management_Case_ID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_ProcessPropertiesBP* pProcessProp = dynamic_cast<PSS_ProcessPropertiesBP*>(pProp);

        if (pProcessProp)
            return (*this == *pProcessProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_ProcessPropertiesBP::SetManagementCase(LPCTSTR pName)
{
    if (pName)
        m_ManagementCase = pName;
    else
        THROW("PSS_ProcessPropertiesBP - Invalid management case name");
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Management_Case_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::GetValue(const int propId, UINT& value) const
{
    switch (propId)
    {
        case M_Management_Case_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::GetValue(const int propId, DWORD& value) const
{
    switch (propId)
    {
        case M_Management_Case_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::GetValue(const int propId, float& value) const
{
    switch (propId)
    {
        case M_Management_Case_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Management_Case_ID: value = m_ManagementCase; break;
        default:                                             return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Management_Case_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::SetValue(const int propId, const UINT value)
{
    switch (propId)
    {
        case M_Management_Case_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::SetValue(const int propId, const DWORD value)
{
    switch (propId)
    {
        case M_Management_Case_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::SetValue(const int propId, const float value)
{
    switch (propId)
    {
        case M_Management_Case_ID: throw new CODPropertyConversionException();
        default:                   return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessPropertiesBP::SetValue(const int propId, LPCTSTR pValue)
{
    if (!pValue)
        return FALSE;

    switch (propId)
    {
        case M_Management_Case_ID: m_ManagementCase = pValue; break;
        default:                                              return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ProcessPropertiesBP::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    if (ar.IsStoring())
    {
        TRACE("PSS_ProcessPropertiesBP::Serialize - Start save\n");

        PUT_SCHEMA(ar, PSS_ProcessPropertiesBP);

        ar << m_ManagementCase;

        TRACE("PSS_ProcessPropertiesBP::Serialize - End save\n");
    }
    else
    {
        TRACE("PSS_ProcessPropertiesBP::Serialize - Start read\n");

        UINT schema;
        GET_SCHEMA(ar, schema);

        ar >> m_ManagementCase;

        TRACE("PSS_ProcessPropertiesBP::Serialize : End read\n");
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessPropertiesBP::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessPropertiesBP::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);
        dc << _T("Management case name = ") << m_ManagementCase << _T("\n");
    }
#endif
//---------------------------------------------------------------------------
void PSS_ProcessPropertiesBP::SetManagementCaseEx(const CString name)
{
    SetManagementCase(name);
}
//---------------------------------------------------------------------------
bool PSS_ProcessPropertiesBP::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        const bool success = RegisterProperty(M_Management_Case_ID,
                                              IDS_Z_MANAGEMENT_CASE_NAME,
                                              IDS_Z_MANAGEMENT_CASE_DESC,
                                              _PropertyAccessor(&PSS_ProcessPropertiesBP::GetManagementCase,
                                                                &PSS_ProcessPropertiesBP::SetManagementCaseEx),
                                              VT_BSTR,
                                              PROP_DIRECT);

        if (!success)
            GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
