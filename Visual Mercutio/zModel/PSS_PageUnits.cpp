/****************************************************************************
 * ==> PSS_PageUnits -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides page units                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PageUnits.h"

// processsoft
#include "PSS_SerializeODMeasure.h"

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
PSS_PageUnits::PSS_PageUnits(const PSS_PageUnits& other) :
    CObject(),
    m_Units(0)
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_PageUnits::PSS_PageUnits(const CODRuler& other) :
    CObject(),
    m_Units(0)
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

        PSS_SerializeODMeasure::SerializeWriteODMeasure(ar, m_ScaleFrom);
        PSS_SerializeODMeasure::SerializeWriteODMeasure(ar, m_ScaleTo);
        PSS_SerializeODMeasure::SerializeWriteODMeasure(ar, m_LogXUnit);
        PSS_SerializeODMeasure::SerializeWriteODMeasure(ar, m_LogYUnit);
    }
    else
    {
        DWORD wValue;
        ar >> wValue;
        m_Units = OD_UNIT_OF_MEASURE(wValue);

        PSS_SerializeODMeasure::SerializeReadODMeasure(ar, m_ScaleFrom);
        PSS_SerializeODMeasure::SerializeReadODMeasure(ar, m_ScaleTo);
        PSS_SerializeODMeasure::SerializeReadODMeasure(ar, m_LogXUnit);
        PSS_SerializeODMeasure::SerializeReadODMeasure(ar, m_LogYUnit);
    }
}
//---------------------------------------------------------------------------
