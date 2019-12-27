/****************************************************************************
 * ==> PSS_PageUnits -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides page units                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PageUnits.h"

// processsoft
#include "ZUSerializeODMeasure.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_PageUnits, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_PageUnits
//---------------------------------------------------------------------------
PSS_PageUnits::PSS_PageUnits() :
    CObject(),
    m_Units(0)
{}
//---------------------------------------------------------------------------
PSS_PageUnits::PSS_PageUnits(const PSS_PageUnits& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PageUnits::PSS_PageUnits(const CODRuler& other)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PageUnits::~PSS_PageUnits()
{}
//---------------------------------------------------------------------------
const PSS_PageUnits& PSS_PageUnits::operator = (const PSS_PageUnits& other)
{
    m_Units = other.GetUnitOfMeasure();

    const_cast<PSS_PageUnits&>(other).GetLogicalUnitMeasure(m_LogXUnit,  m_LogYUnit);
    const_cast<PSS_PageUnits&>(other).GetMeasurementScale  (m_ScaleFrom, m_ScaleTo);

    return *this;
}
//---------------------------------------------------------------------------
const PSS_PageUnits& PSS_PageUnits::operator = (const CODRuler& other)
{
    m_Units = other.GetUnitOfMeasure();

    const_cast<CODRuler&>(other).GetLogicalUnitMeasure(m_LogXUnit,  m_LogYUnit);
    const_cast<CODRuler&>(other).GetMeasurementScale  (m_ScaleFrom, m_ScaleTo);

    return *this;
}
//---------------------------------------------------------------------------
void PSS_PageUnits::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar << DWORD(m_Units);

        ZUSerializeODMeasure::SerializeWriteODMeasure(ar, m_ScaleFrom);
        ZUSerializeODMeasure::SerializeWriteODMeasure(ar, m_ScaleTo);
        ZUSerializeODMeasure::SerializeWriteODMeasure(ar, m_LogXUnit);
        ZUSerializeODMeasure::SerializeWriteODMeasure(ar, m_LogYUnit);
    }
    else
    {
        DWORD wValue;
        ar >> wValue;
        m_Units = OD_UNIT_OF_MEASURE(wValue);

        ZUSerializeODMeasure::SerializeReadODMeasure(ar, m_ScaleFrom);
        ZUSerializeODMeasure::SerializeReadODMeasure(ar, m_ScaleTo);
        ZUSerializeODMeasure::SerializeReadODMeasure(ar, m_LogXUnit);
        ZUSerializeODMeasure::SerializeReadODMeasure(ar, m_LogYUnit);
    }
}
//---------------------------------------------------------------------------
