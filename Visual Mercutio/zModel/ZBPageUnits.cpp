// ZBPageUnits.cpp: implementation of the ZBPageUnits class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBPageUnits.h"

#include "ZUSerializeODMeasure.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

IMPLEMENT_SERIAL( ZBPageUnits, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBPageUnits::ZBPageUnits()
    : m_units( 0 )
{
}

ZBPageUnits::~ZBPageUnits()
{
}

ZBPageUnits::ZBPageUnits( const ZBPageUnits &right )
{
    *this = right;
}

ZBPageUnits::ZBPageUnits( const CODRuler &right )
{
    *this = right;
}

const ZBPageUnits& ZBPageUnits::operator=( const ZBPageUnits &right )
{
    m_units = right.GetUnitOfMeasure();

    const_cast<ZBPageUnits&>( right ).GetLogicalUnitMeasure( m_logXUnit, m_logYUnit );
    const_cast<ZBPageUnits&>( right ).GetMeasurementScale( m_ScaleFrom, m_ScaleTo );

    return *this;
}

const ZBPageUnits& ZBPageUnits::operator=( const CODRuler &right )
{
    m_units = right.GetUnitOfMeasure();

    const_cast<CODRuler&>( right ).GetLogicalUnitMeasure( m_logXUnit, m_logYUnit );
    const_cast<CODRuler&>( right ).GetMeasurementScale( m_ScaleFrom, m_ScaleTo );

    return *this;
}

/////////////////////////////////////////////////////////////////////////////
// ZBPageUnits serialization

void ZBPageUnits::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        ar << (DWORD)m_units;

        ZUSerializeODMeasure::SerializeWriteODMeasure( ar, m_ScaleFrom );
        ZUSerializeODMeasure::SerializeWriteODMeasure( ar, m_ScaleTo );
        ZUSerializeODMeasure::SerializeWriteODMeasure( ar, m_logXUnit );
        ZUSerializeODMeasure::SerializeWriteODMeasure( ar, m_logYUnit );
    }
    else
    {
        DWORD wValue;
        ar >> wValue;
        m_units = (OD_UNIT_OF_MEASURE)wValue;

        ZUSerializeODMeasure::SerializeReadODMeasure( ar, m_ScaleFrom );
        ZUSerializeODMeasure::SerializeReadODMeasure( ar, m_ScaleTo );
        ZUSerializeODMeasure::SerializeReadODMeasure( ar, m_logXUnit );
        ZUSerializeODMeasure::SerializeReadODMeasure( ar, m_logYUnit );
    }
}
