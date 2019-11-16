/****************************************************************************
 * ==> PSS_Point -----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a point                                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Point.h"

 // processsoft
#include "PSS_BaseDocument.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_Point
//---------------------------------------------------------------------------
PSS_Point::PSS_Point() :
    CPoint()
{}
//---------------------------------------------------------------------------
PSS_Point::~PSS_Point()
{}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_Point& point)
{
    PSS_BaseDocument* pDocument = dynamic_cast<PSS_BaseDocument*>(ar.m_pDocument);

    if (pDocument && pDocument->GetDocumentStamp().GetInternalVersion() <= 12)
    {
        WORD wTemp;
        ar >> wTemp;
        point.x = int(wTemp);

        ar >> wTemp;
        point.y = int(wTemp);
    }
    else
    {
        DWORD dwTemp;
        ar >> dwTemp;
        point.x = int(dwTemp);

        ar >> dwTemp;
        point.y = int(dwTemp);
    }

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_Point& point)
{
    ar << DWORD(point.x);
    ar << DWORD(point.y);

    return ar;
}
//---------------------------------------------------------------------------
void PSS_Point::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
        // write the elements
        ar << *this;
    else
        // read the elements
        ar >> *this;
}
//---------------------------------------------------------------------------
