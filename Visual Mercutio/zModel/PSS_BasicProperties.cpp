/****************************************************************************
 * ==> PSS_BasicProperties -------------------------------------------------*
 ****************************************************************************
 * Description : Provides the basic properties                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_BasicProperties.h"

// processsoft
#include "zModel\PSS_ProcessGraphModelDoc.h"

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
IMPLEMENT_SERIAL(PSS_BasicProperties, CODIntProperty, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_BasicProperties
//---------------------------------------------------------------------------
PSS_BasicProperties::PSS_BasicProperties(int id) :
    CODIntProperty(id),
    CPropertyContainer< IODPropertyContainer, CODPropertyAccessor<PSS_BasicProperties> >(),
    m_SymbolNumber(-1)
{
    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_BasicProperties::PSS_BasicProperties(const PSS_BasicProperties& other) :
    CODIntProperty(other.GetId()),
    CPropertyContainer< IODPropertyContainer, CODPropertyAccessor<PSS_BasicProperties> >()
{
    *this = other;
    VERIFY(RegisterProperties());
}
//---------------------------------------------------------------------------
PSS_BasicProperties::~PSS_BasicProperties()
{}
//---------------------------------------------------------------------------
PSS_BasicProperties& PSS_BasicProperties::operator = (const PSS_BasicProperties& other)
{
    SetSymbolName       (other.GetSymbolName());
    SetSymbolDescription(other.GetSymbolDescription());
    SetSymbolNumber     (other.GetSymbolNumber());
    SetSymbolRiskLevel  (other.GetSymbolRiskLevel());

    return *this;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::operator == (const PSS_BasicProperties& other) const
{
    return (GetSymbolName()        == other.GetSymbolName()        &&
            GetSymbolDescription() == other.GetSymbolDescription() &&
            GetSymbolNumber()      == other.GetSymbolNumber()      &&
            GetSymbolRiskLevel()   == other.GetSymbolRiskLevel());
}
//---------------------------------------------------------------------------
void PSS_BasicProperties::Merge(CODProperty* pProp, DWORD changeFlags)
{
    PSS_BasicProperties* pBasicProps = dynamic_cast<PSS_BasicProperties*>(pProp);

    if (pBasicProps)
    {
        if (changeFlags & IE_CT_Symbol_Name)
            m_SymbolName = pBasicProps->GetSymbolName();

        if (changeFlags & IE_CT_Symbol_Description)
            m_SymbolDescription = pBasicProps->GetSymbolDescription();

        if (changeFlags & IE_CT_Symbol_Number)
            m_SymbolNumber = pBasicProps->GetSymbolNumber();

        if (changeFlags & IE_CT_Symbol_Risk_Level)
            m_SymbolRiskLevel = pBasicProps->GetSymbolRiskLevel();
    }
}
//---------------------------------------------------------------------------
CString PSS_BasicProperties::GetSymbolNumberStr() const
{
    CString number;

    if (GetValue(M_Symbol_Number_ID, number))
        return number;

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_BasicProperties::SetSymbolNumber(const CString value)
{
    SetValue(M_Symbol_Number_ID, value);
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::CompareId(const int id) const
{
    const int idMin = m_nId;
    const int idMax = m_nId + M_Symbol_Risk_Level_ID;

    return (id >= idMin && id <= idMax);
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::IsEqual(CODProperty* pProp)
{
    if (GetId() == pProp->GetId())
    {
        PSS_BasicProperties* pBasicProp = dynamic_cast<PSS_BasicProperties*>(pProp);

        if (pBasicProp)
            return (*this == *pBasicProp);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::GetValue(const int propId, int& value) const
{
    switch (propId)
    {
        case M_Symbol_Number_ID:      value = m_SymbolNumber; break;
        case M_Symbol_Name_ID:
        case M_Symbol_Description_ID:
        case M_Symbol_Risk_Level_ID:  throw new CODPropertyConversionException();
        default:                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::GetValue(const int propId, UINT& value) const
{
    if (propId >= M_Symbol_Name_ID && propId <= M_Symbol_Risk_Level_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::GetValue(const int propId, DWORD& value) const
{
    if (propId >= M_Symbol_Name_ID && propId <= M_Symbol_Risk_Level_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::GetValue(const int propId, float& value) const
{
    if (propId >= M_Symbol_Name_ID && propId <= M_Symbol_Risk_Level_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::GetValue(const int propId, CString& value) const
{
    switch (propId)
    {
        case M_Symbol_Name_ID:        value = m_SymbolName;                   break;
        case M_Symbol_Description_ID: value = m_SymbolDescription;            break;
        case M_Symbol_Number_ID:      value.Format(_T("%d"), m_SymbolNumber); break;
        case M_Symbol_Risk_Level_ID:  value = m_SymbolRiskLevel;              break;
        default:                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::SetValue(const int propId, const int value)
{
    switch (propId)
    {
        case M_Symbol_Number_ID:      m_SymbolNumber = value; break;
        case M_Symbol_Name_ID:
        case M_Symbol_Description_ID:
        case M_Symbol_Risk_Level_ID:  throw new CODPropertyConversionException();
        default:                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::SetValue(const int propId, const UINT value)
{
    if (propId >= M_Symbol_Name_ID && propId <= M_Symbol_Risk_Level_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::SetValue(const int propId, const DWORD value)
{
    if (propId >= M_Symbol_Name_ID && propId <= M_Symbol_Risk_Level_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::SetValue(const int propId, const float value)
{
    if (propId >= M_Symbol_Name_ID && propId <= M_Symbol_Risk_Level_ID)
        throw new CODPropertyConversionException();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_BasicProperties::SetValue(const int propId, LPCTSTR pValue)
{
    switch (propId)
    {
        case M_Symbol_Name_ID:        m_SymbolName        = pValue;            break;
        case M_Symbol_Description_ID: m_SymbolDescription = pValue;            break;
        case M_Symbol_Number_ID:      m_SymbolNumber      = std::atoi(pValue); break;
        case M_Symbol_Risk_Level_ID:  m_SymbolRiskLevel   = pValue;            break;
        default:                      return FALSE;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_BasicProperties::Serialize(CArchive& ar)
{
    CODIntProperty::Serialize(ar);

    PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

    if (ar.IsStoring())
    {
        PUT_SCHEMA(ar, PSS_BasicProperties);

        ar << m_SymbolName;
        ar << m_SymbolDescription;
        ar << m_SymbolNumber;

        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 27)
            ar << m_SymbolRiskLevel;
    }
    else
    {
        UINT schema;
        GET_SCHEMA(ar, schema);

        ar >> m_SymbolName;
        ar >> m_SymbolDescription;
        ar >> m_SymbolNumber;

        if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() >= 27)
            ar >> m_SymbolRiskLevel;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_BasicProperties::AssertValid() const
    {
        CODIntProperty::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_BasicProperties::Dump(CDumpContext& dc) const
    {
        CODIntProperty::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
bool PSS_BasicProperties::RegisterProperties()
{
    static bool propsRegistered = false;

    if (!propsRegistered)
    {
        bool success = true;

        if (success)
            success = RegisterProperty(M_Symbol_Name_ID,
                                       IDS_Z_SYMBOL_NAME_NAME,
                                       IDS_Z_SYMBOL_NAME_DESC,
                                       _PropertyAccessor(&PSS_BasicProperties::GetSymbolName,
                                                         &PSS_BasicProperties::SetSymbolName),
                                       VT_BSTR,
                                       PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Symbol_Description_ID,
                                       IDS_Z_SYMBOL_DESCRIPTION_NAME,
                                       IDS_Z_SYMBOL_DESCRIPTION_DESC,
                                       _PropertyAccessor(&PSS_BasicProperties::GetSymbolDescription,
                                                         &PSS_BasicProperties::SetSymbolDescription),
                                       VT_BSTR,
                                       PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Symbol_Number_ID,
                                       IDS_Z_SYMBOL_NUMBER_NAME,
                                       IDS_Z_SYMBOL_NUMBER_DESC,
                                       _PropertyAccessor(&PSS_BasicProperties::GetSymbolNumber,
                                                         &PSS_BasicProperties::SetSymbolNumber),
                                       VT_INT,
                                       PROP_DIRECT);

        if (success)
            success = RegisterProperty(M_Symbol_Risk_Level_ID,
                                       IDS_Z_SYMBOL_RISK_LEVEL_NAME,
                                       IDS_Z_SYMBOL_RISK_LEVEL_DESC,
                                       _PropertyAccessor(&PSS_BasicProperties::GetSymbolRiskLevel,
                                                         &PSS_BasicProperties::SetSymbolRiskLevel),
                                       VT_BSTR,
                                       PROP_DIRECT);

        if (!success)
            PSS_BasicProperties::GetPropertyMap().DeleteAll();

        propsRegistered = success;
    }

    return propsRegistered;
}
//---------------------------------------------------------------------------
