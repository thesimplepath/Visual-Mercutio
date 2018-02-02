// ZUSerializeODMeasure.cpp: implementation of the ZUSerializeODMeasure class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUSerializeODMeasure.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUSerializeODMeasure::ZUSerializeODMeasure()
{

}

ZUSerializeODMeasure::~ZUSerializeODMeasure()
{

}



void ZUSerializeODMeasure::SerializeWriteODMeasure(CArchive& ar, CODMeasure& Measure)
{
	if (ar.IsStoring())
	{
		ar << (DWORD)Measure.GetUnits();
		ar << (float)Measure;
	}
}

void ZUSerializeODMeasure::SerializeReadODMeasure(CArchive& ar, CODMeasure& Measure)
{
	if (!ar.IsStoring())
	{
		DWORD	wValue;
		ar >> wValue;
		Measure.SetUnits( (OD_UNIT_OF_MEASURE)wValue );

		float	fValue;
		ar >> fValue;
		Measure = fValue;
	}
}
