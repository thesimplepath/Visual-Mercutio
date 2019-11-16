/****************************************************************************
 * ==> PSS_FieldInputScenario ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a field input scenario                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FieldInputScenario.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_FieldInputScenario, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_FieldInputScenario
//---------------------------------------------------------------------------
PSS_FieldInputScenario::PSS_FieldInputScenario(const CString& fieldName, const CString& userName, int order) :
    CObject(),
    m_FieldName(fieldName),
    m_UserName(userName),
    m_Order(order)
{}
//---------------------------------------------------------------------------
PSS_FieldInputScenario::PSS_FieldInputScenario(const PSS_FieldInputScenario& other) :
    CObject(),
    m_Order(-1)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_FieldInputScenario::~PSS_FieldInputScenario()
{}
//---------------------------------------------------------------------------
const PSS_FieldInputScenario& PSS_FieldInputScenario::operator = (const PSS_FieldInputScenario& other)
{
    m_FieldName = other.m_FieldName;
    m_UserName  = other.m_UserName;
    m_Order     = other.m_Order;

    return *this;
}
//---------------------------------------------------------------------------
PSS_FieldInputScenario* PSS_FieldInputScenario::Clone() const
{
    return new PSS_FieldInputScenario(*this);
}
//---------------------------------------------------------------------------
void PSS_FieldInputScenario::Initialize(const CString& fieldName, const CString& userName, int order)
{
    m_FieldName = fieldName;
    m_UserName  = userName;
    m_Order     = order;
}
//---------------------------------------------------------------------------
void PSS_FieldInputScenario::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << DWORD(m_Order);
        ar << m_UserName;
        ar << m_FieldName;
    }
    else
    {
        // read the elements
        DWORD dwValue;
        ar >> dwValue;
        m_Order = int(dwValue);

        ar >> m_UserName;
        ar >> m_FieldName;
    }
}
//---------------------------------------------------------------------------
