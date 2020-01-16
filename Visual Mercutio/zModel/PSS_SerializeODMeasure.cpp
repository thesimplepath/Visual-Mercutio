/****************************************************************************
 * ==> PSS_SerializeODMeasure ----------------------------------------------*
 ****************************************************************************
 * Description : Provides an Objective View component measure serializer    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SerializeODMeasure.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_SerializeODMeasure
//---------------------------------------------------------------------------
PSS_SerializeODMeasure::PSS_SerializeODMeasure()
{}
//---------------------------------------------------------------------------
PSS_SerializeODMeasure::~PSS_SerializeODMeasure()
{}
//---------------------------------------------------------------------------
void PSS_SerializeODMeasure::SerializeReadODMeasure(CArchive& ar, CODMeasure& measure)
{
    if (!ar.IsStoring())
    {
        DWORD wValue;
        ar >> wValue;
        measure.SetUnits(OD_UNIT_OF_MEASURE(wValue));

        float fValue;
        ar >> fValue;
        measure = fValue;
    }
}
//---------------------------------------------------------------------------
void PSS_SerializeODMeasure::SerializeWriteODMeasure(CArchive& ar, const CODMeasure& measure)
{
    if (ar.IsStoring())
    {
        ar << DWORD(measure.GetUnits());
        ar << float(measure);
    }
}
//---------------------------------------------------------------------------
